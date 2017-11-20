/*
 * debug.c
 */

#include <stdint.h>
#include <stdbool.h>
#include "driverlib/gpio.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "debug.h"


/*
 * Enable and configure the GPIO port for the LED operation.
 */
void debugInit(void){

	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, RED | BLUE | GREEN);
}

/*
 * Turn on the chosen color.
 *
 * /param color is the defined LED on debug.h
 */
void debugLED(uint32_t color){

	if(color == RED)GPIOPinWrite(GPIO_PORTF_BASE, WHITE, RED);
	if(color == BLUE)GPIOPinWrite(GPIO_PORTF_BASE, WHITE, BLUE);
	if(color == GREEN)GPIOPinWrite(GPIO_PORTF_BASE, WHITE, GREEN);
	if(color == YELLOW)GPIOPinWrite(GPIO_PORTF_BASE, WHITE, YELLOW);
	if(color == MAGENTA)GPIOPinWrite(GPIO_PORTF_BASE, WHITE, MAGENTA);
	if(color == CYAN)GPIOPinWrite(GPIO_PORTF_BASE, WHITE, CYAN);
	if(color == WHITE)GPIOPinWrite(GPIO_PORTF_BASE, WHITE, WHITE);
}

/*
 * Print report message for debugging purposes.
 * This API will disable al the interrupts and send from
 * ordinary UART's printf.
 * TODO: This API will be properly implemented.
 */
void commReportMessage1(void){

	/*
	 * Disable master interrupt and clear all of them.
	 */
	/*
	IntMasterDisable();
	uDMAIntClear(intStatus.uDMA);
	UARTIntClear(UART0_BASE, intStatus.UART);
	*/

	/*
	 * Send the message and wait.
	 */
	/*
	UARTprintf("An unexpected flag occurred:\n");
	UARTprintf("UART interrupt flags: %X\n", intStatus.UART);
	UARTprintf("uDMA interrupt flags: %X\n", intStatus.uDMA);
	UARTprintf("Timer0 interrupt flags: %X\n", intStatus.TIMER0);
	UARTprintf("Errors on uDMA Handler: %d\n", perError.uDMA);
	while(UARTBusy(UART0_BASE));
	*/

	/*
	 * Enable the master interrupt before leaving.
	 */
	/* IntMasterEnable(); */
}

/*
 * Print report message for debugging purposes.
 * This API will use uDMA to send the message.
 * TODO: This API will be properly implemented.
 */
void commReportMessage2(void){

	/*
	 * Create a char buffer and pointer to store the text.
	 * Note: Static here maintain the previous value.
	 */
	/*
	char message[300];
	char *pointer;
	pointer = &message[0];
	*/

	/*
	 * Flush any information that is inside the variables.
	 */
	/*
	for(int i=0;i<300;i++)message[i]='\0';
	*/

	/*
	 * Messages to be sent.
	 * First merge into information strings and then merge into the final message.
	 */
	/*
	pointer += usprintf(pointer, "Below is described status of interrupts and errors:\n");
	pointer += usprintf(pointer, "UART interrupt flags: %X\n", intStatus.UART);
	pointer += usprintf(pointer, "uDMA interrupt flags: %X\n", intStatus.uDMA);
	pointer += usprintf(pointer, "Timer0 interrupt flags: %X\n", intStatus.TIMER0);
	pointer += usprintf(pointer, "Errors on uDMA Handler: %d\n", perError.uDMA);
	*/

	/*
	 * Send the message.
	 */
	/*
	commSendMessage(message, sizeof(message));
	*/
}
