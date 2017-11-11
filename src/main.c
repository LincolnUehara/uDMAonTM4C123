/*
 * main.c
 */

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_uart.h"
#include "inc/hw_gpio.h"
#include "inc/hw_types.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "driverlib/udma.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/udma.h"
#include "communication.h"

/*
 * Defines and variables used.
 */
#define RED_LED   GPIO_PIN_1
#define BLUE_LED  GPIO_PIN_2
#define GREEN_LED GPIO_PIN_3
static char message[BUFFER_SIZE];
static bool received = false;

int main()
{
	/* TIVA on 80 MHz */
	SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ |
			SYSCTL_OSC_MAIN);

	/* Enable and configure the GPIO port for the LED operation. */
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, RED_LED | BLUE_LED | GREEN_LED);

	/* Initializing. */
	commInit(&received, message);

	while(1){

		/*
		 * If received command from UART, process it.
		 */
    	if(received == true){

			/*
			 *
			 */
			if(message[0] == 'R')
				GPIOPinWrite(GPIO_PORTF_BASE,
				    RED_LED | BLUE_LED | GREEN_LED, RED_LED);
			if(message[0] == 'G')
				GPIOPinWrite(GPIO_PORTF_BASE,
					RED_LED | BLUE_LED | GREEN_LED, GREEN_LED);
			if(message[0] == 'B')
				GPIOPinWrite(GPIO_PORTF_BASE,
				    RED_LED | BLUE_LED | GREEN_LED, BLUE_LED);

			/*
			 * TODO: Implement.
			 */
			/* commSendMessage(message, sizeof(message)); */
			commReportMessage();
			received = false;
		}else;
	}
}
