/*
 * communication.c
 */

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <inc/tm4c123gh6pm.h>
#include <inc/hw_memmap.h>
#include <inc/hw_gpio.h>
#include <inc/hw_uart.h>
#include <inc/hw_types.h>
#include <driverlib/rom.h>
#include <driverlib/gpio.h>
#include <driverlib/pin_map.h>
#include <driverlib/sysctl.h>
#include <driverlib/interrupt.h>
#include <driverlib/uart.h>
#include <driverlib/udma.h>
#include <driverlib/timer.h>
#include <utils/uartstdio.h>
#include <utils/ustdlib.c>
#include "communication.h"

/*
 * Variables and pointers used.
 */
DEFINE_COMMUNICATION_PERIPHERALS(intStatus);
DEFINE_COMMUNICATION_PERIPHERALS(perError);
static char bufferRx[BUFFER_SIZE]; /* TODO: unsigned[?] */
static char *messagePointer;
static bool *receivedMessage;

/*
 * Initialization of communication by UART/uDMA.
 *
 * \param receivedFlag is the address of the received flag.
 * \param messageBuffer is the address to the message string.
 *
 * It receives pointers for flag and software buffer for
 * communication purposes.
 */
void commInit(bool *receivedFlag, char messageBuffer[]){

	/*
	 * Initialize flags for receiving message and each
	 * peripheral.
	 */
	receivedMessage = receivedFlag;
	*receivedMessage = false;
	messagePointer = &messageBuffer[0];
	commTIMER0_Init();
	commUART_Init();
	commUDMA_Init();
}

/*
 * Initialization of UART peripheral.
 */
void commUART_Init(void){

	/*
	 * Configure UART communication on TIVA.
	 * Configure it to operate even if the CPU is in sleep.
	 * Pins PA0 (Rx) and PA1 (Tx) are used.
	 */
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
	SysCtlPeripheralSleepEnable(SYSCTL_PERIPH_UART0);
	GPIOPinConfigure(GPIO_PA0_U0RX);
	GPIOPinConfigure(GPIO_PA1_U0TX);
	GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
	UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

	/*
	 * Setting baud rate as 115200 bps.
	 */
	UARTStdioConfig(0, 115200, 16000000);

	/*
	 * Setting FIFO Level trigger.
	 * TODO: To be implemented
	 */
	/* UARTFIFOEnable(UART0_BASE); */
    /* UARTFIFOLevelSet(UART0_BASE, UART_FIFO_TX1_8, UART_FIFO_RX7_8); */

	/*
	 * Enable the UART peripheral interrupts.
	 * The uDMA controller will cause an interrupt on the
	 * UART interrupt signal when a uDMA transfer is complete.
	 */
	IntEnable(INT_UART0);
	UARTIntEnable(UART0_BASE, UART_INT_RT | UART_INT_RX);

	/*
	 * Enable the UART for operation
	 */
	UARTEnable(UART0_BASE);
}

/*
 * Initialization of uDMA peripheral.
 */
void commUDMA_Init(){

	/*
	 * Starting DMA Configuration.
	 */
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UDMA);
	uDMAEnable();

	/*
	 * Point at the control table to use for channel
	 * control structures.
	 */
	uDMAControlBaseSet(DMAcontroltable);

	/*
	 * Assign the uDMA channel to the peripherals and
	 * disable all the attributes in case any was set.
	 */
	uDMAChannelAssign(UDMA_CH8_UART0RX);
	uDMAChannelAssign(UDMA_CH9_UART0TX);
	uDMAChannelAttributeDisable(UDMA_CH8_UART0RX,
			UDMA_ATTR_USEBURST | UDMA_ATTR_ALTSELECT |
			UDMA_ATTR_HIGH_PRIORITY | UDMA_ATTR_REQMASK);
	uDMAChannelAttributeDisable(UDMA_CH9_UART0TX,
			UDMA_ATTR_USEBURST | UDMA_ATTR_ALTSELECT |
			UDMA_ATTR_HIGH_PRIORITY | UDMA_ATTR_REQMASK);

	/*
	 * Set the channel control.
	 * In this case we are working with string of char values,
	 * so we use UDMA_SIZE_8. No increment is used on source,
	 * because it will be pointing to UART_O_DR register, and
	 * increment of 8 bits are used because we will fill a
	 * string of char values "bufferRx".
	 */
	uDMAChannelControlSet(UDMA_CH8_UART0RX | UDMA_PRI_SELECT,
			UDMA_SIZE_8 | UDMA_SRC_INC_NONE | UDMA_DST_INC_8 |
			UDMA_ARB_1);
	uDMAChannelControlSet(UDMA_CH9_UART0TX | UDMA_PRI_SELECT,
			UDMA_SIZE_8 | UDMA_SRC_INC_8 | UDMA_DST_INC_NONE |
			UDMA_ARB_1);

	/*
	 * Enable the uDMA interface for both TX and RX channels.
	 */
	UARTDMAEnable(UART0_BASE, UART_DMA_RX | UART_DMA_TX);

	/*
	 * Set up the transfer parameters and enable the uDMA
	 * channel for RX.
	 * "UDMA_CH9_UART0TX" is not enabled until there is data
	 * to be sent on commSendMessage API.
	 */
	uDMAChannelTransferSet(UDMA_CH8_UART0RX | UDMA_PRI_SELECT,
			UDMA_MODE_AUTO, (void *)(UART0_BASE + UART_O_DR),
			&bufferRx, sizeof(bufferRx));
    uDMAChannelEnable(UDMA_CH8_UART0RX);
}

/*
 * Initialization of Timer0 peripheral.
 * TODO: To be implemented.
 */
void commTIMER0_Init(void){

	/*
	 * Configuring the 32-bit periodic timers.
	 */
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
	TimerConfigure(TIMER0_BASE, TIMER_CFG_ONE_SHOT_UP);
	TimerLoadSet(TIMER0_BASE, TIMER_A, UDMA_TIMING);

	/*
	 * Enable the Timers for timeout interrupt.
	 */
	/* IntEnable(INT_TIMER0A); */
	/* TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT); */
}

/*
 * Interrupt handler for uDMA/UART.
 */
void commInterrupt(void){

	/*
	 * Obtain the status of each peripheral.
	 */
	intStatus.UART = UARTIntStatus(UART0_BASE, 1);
	intStatus.uDMA = uDMAIntStatus();

	/*
	 * Check if interrupt was generated by Rx/uDMA.
	 */
	if(intStatus.uDMA & UART0RX_INTERRUPT){

		/*
		 * Transfer data to main.c variable.
		 */
		commTransferData();

		/*
		 * Set the receiving for next message.
		 */
		uDMAChannelTransferSet(UDMA_CH8_UART0RX | UDMA_PRI_SELECT,
				UDMA_MODE_AUTO, (void *)(UART0_BASE + UART_O_DR),
				&bufferRx, sizeof(bufferRx));
		uDMAChannelEnable(UDMA_CH8_UART0RX);

		/*
		 * Clear interrupts. Only clear next to end of interrupt
		 * because commTransferData API processing time is variable.
		 */
		uDMAIntClear(intStatus.uDMA);
		UARTIntClear(UART0_BASE, intStatus.UART);
	}

	/*
	 * Check if interrupt was generated by Tx/uDMA.
	 */
	if(intStatus.uDMA & UART0TX_INTERRUPT){

		/*
		 * Just clear all the interrupts.
		 */
		uDMAIntClear(intStatus.uDMA);
		UARTIntClear(UART0_BASE, intStatus.UART);
	}

	/*
	 * If none of previous flags was set, just clear the
	 * interrupts. "else" is not applicable here.
	 */
	if((intStatus.uDMA != UART0RX_INTERRUPT)
		&& (intStatus.uDMA != UART0TX_INTERRUPT)){

		uDMAIntClear(intStatus.uDMA);
		UARTIntClear(UART0_BASE, intStatus.UART);
	}
}

/*
 * Import data and flush buffer.
 */
void commTransferData(void){

	/*
	 * Transfer the data to the buffer of main function.
	 */
	for(int i = 0 ; i < BUFFER_SIZE ; i++){
		*messagePointer = bufferRx[i];
		messagePointer++;
	}

	/*
	 * Set the flag indicating that some message arrived
	 * and clear the bufferRx to not polute uDMA side.
	 */
	*receivedMessage = true;
	for(int i = (BUFFER_SIZE-1) ; i >= 0 ; i--){
		bufferRx[i] = '\0';
		messagePointer--;
	}
}

/*
 * Report status message.
 */
void commReportMessage(void){

	/*
	 * TODO: Avail if is better to create every time or
	 * create a static variable.
	 * Note: Static here maintain the previous value.
	 */
	//char information[5][60];
	char message[300];
	char *pointer;
	pointer = &message[0];

	/*
	 * Flush any information that is inside the variables.
	 */
	//for(int i=0;i<4;i++)for(int j=0;j<50;j++)information[i][j]='\0';
	for(int i=0;i<300;i++)message[i]='\0';

	/*
	 * Messages to be sent.
	 * First merge into information strings and then merge into the final message.
	 */
	/*
	usprintf(information[0], "\nBelow is described status of interrupts and errors:");
	usprintf(information[1], "\nUART interrupt flags: %X", intStatus.UART);
	usprintf(information[2], "\nuDMA interrupt flags: %X", intStatus.uDMA);
	usprintf(information[3], "\nTimer0 interrupt flags: %X", intStatus.TIMER0);
	usprintf(information[4], "\nErrors on uDMA Handler: %d", perError.uDMA);
	for(int i = 0 ; i < 5 ; i++)
		strcat(message, information[i]);
	*/

	pointer += usprintf(pointer, "Below is described status of interrupts and errors:\n");
	pointer += usprintf(pointer, "UART interrupt flags: %X\n", intStatus.UART);
	pointer += usprintf(pointer, "uDMA interrupt flags: %X\n", intStatus.uDMA);
	pointer += usprintf(pointer, "Timer0 interrupt flags: %X\n", intStatus.TIMER0);
	pointer += usprintf(pointer, "Errors on uDMA Handler: %d\n", perError.uDMA);

	/*
	 * Send the message.
	 */
	commSendMessage(message, sizeof(message));
}

/*
 * Send a string vector of the argument.
 *
 * \param TxMessageBuffer is the address of the message string.
 * \param dataLength is the length of the message to be sent.
 *
 * It receives the message string address and send it through
 * uDMA. Use "sizeof()" function to facilitate length count.
 */
void commSendMessage(char TxMessageBuffer[], uint16_t dataLength){

	uDMAChannelTransferSet(UDMA_CH9_UART0TX | UDMA_PRI_SELECT,
		UDMA_MODE_BASIC, TxMessageBuffer,
		(void *)(UART0_BASE + UART_O_DR), dataLength);

	uDMAChannelEnable(UDMA_CH9_UART0TX);
}

/*
 * The interrupt handler for uDMA errors. This interrupt will occur if the
 * uDMA encounters a bus error while trying to perform a transfer. This
 * handler just increments a counter if an error occurs.
 */
void commErrorHandler(void){

    if(uDMAErrorStatusGet()){

        uDMAErrorStatusClear();
        perError.uDMA++;
    }
}

/*
 * Enables interrupt.
 * TODO: To be implemented.
 */
void commEnableInterrupt(void) {

}

/*
 * Disables interrupt.
 * TODO: To be implemented.
 */
void commDisableInterrupt(void) {

}
