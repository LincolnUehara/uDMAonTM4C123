/*
 * main.c
 */

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "uDMA.h"
#include "UART0.h"

/*
 * Variables used in main.c
 */
static char UART0message[FIFO_TRIGGER_SIZE];
static bool UART0received;
static bool UART0sent;

int main(){

	/*
	 * TIVA on 80 MHz
	 */
	SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ |
			SYSCTL_OSC_MAIN);

	/*
	 * Initializing.
	 */
	uDMAInit();
	UART0Init(&UART0received, &UART0sent, UART0message);
	IntMasterEnable();

	while(1){

		/*
		 * If received message from UART, set the variables
                 * and resent the message.
		 */
		if(UART0received == true){

            		UART0received = false;
    			UART0sent = false;
    			UART0SendMessage(UART0message);
		}

    		/*
    		 * If message was sent, flush the buffer and set the variable.
    		 */
    		if(UART0sent == true){
    			for(int i = 0 ; i < FIFO_TRIGGER_SIZE; i++){
    				UART0message[i] = '\0';
    			}
    			UART0sent = false;
    		}
	}
}
