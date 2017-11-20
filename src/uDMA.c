/*
 * uDMA.c
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdint.h>
#include <inc/hw_uart.h>
#include <inc/hw_memmap.h>
#include <driverlib/udma.h>
#include <driverlib/sysctl.h>
#include "uDMA.h"

/*
 * Initialization of uDMA peripheral.
 */
void uDMAInit(void){

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
}

void uDMAInitUART0(void){

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
	 * It is used UDMA_ARB_8 to match with BUFFER_SIZE and
	 * UART_FIFO_RX4_8.
	 */
	uDMAChannelControlSet(UDMA_CH8_UART0RX | UDMA_PRI_SELECT,
			UDMA_SIZE_8 | UDMA_SRC_INC_NONE | UDMA_DST_INC_8 |
			UDMA_ARB_8);
	uDMAChannelControlSet(UDMA_CH9_UART0TX | UDMA_PRI_SELECT,
			UDMA_SIZE_8 | UDMA_SRC_INC_8 | UDMA_DST_INC_NONE |
			UDMA_ARB_8);
}

/*
 * Prepares the receiving for next data.
 *
 * \param RxMessageBuffer is the address of the buffer where the
 * data will be stored.
 * \param dataLength is the length of the message to be received.
 */
void uDMAReceiveUART0(char RxMessageBuffer[], uint16_t dataLength){

	uDMAChannelAttributeEnable(UDMA_CH8_UART0RX,
		UDMA_ATTR_USEBURST);
	uDMAChannelTransferSet(UDMA_CH8_UART0RX | UDMA_PRI_SELECT,
		UDMA_MODE_BASIC, (void *)(UART0_BASE + UART_O_DR),
		&RxMessageBuffer[0], dataLength);
	uDMAChannelEnable(UDMA_CH8_UART0RX);
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
void uDMASendUART0(char TxMessageBuffer[], uint16_t dataLength){

	uDMAChannelAttributeEnable(UDMA_CH9_UART0TX,
		UDMA_ATTR_USEBURST);
	uDMAChannelTransferSet(UDMA_CH9_UART0TX | UDMA_PRI_SELECT,
		UDMA_MODE_BASIC, &TxMessageBuffer[0],
		(void *)(UART0_BASE + UART_O_DR), dataLength);
	uDMAChannelEnable(UDMA_CH9_UART0TX);
}

/*
 * The interrupt handler for uDMA errors. This interrupt will occur if the
 * uDMA encounters a bus error while trying to perform a transfer. This
 * handler just increments a counter if an error occurs.
 */
void uDMAErrorHandler(void){

    if(uDMAErrorStatusGet()){

        uDMAErrorStatusClear();
        /* TODO: This will be properly implemented. */
        /* perError.uDMA++; */
    }
}
