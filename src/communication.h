/*
 * communication.h
 *
 *  Created on: Nov 2, 2017
 *      Author: lin
 */

#ifndef SRC_COMMUNICATION_H_
#define SRC_COMMUNICATION_H_

/*
 * If building with a C++ compiler, make all of the definitions in this header
 * have a C binding.
 */
#ifdef __cplusplus
extern "C"
{
#endif

/*
 * The control table used by the uDMA controller.  This table must be aligned
 * to a 1024 byte boundary.
 */
#if defined(ewarm)
#pragma data_alignment=1024
uint8_t DMAcontroltable[1024];
#elif defined(ccs)
#pragma DATA_ALIGN(DMAcontroltable, 1024)
uint8_t DMAcontroltable[1024];
#else
uint8_t DMAcontroltable[1024] __attribute__ ((aligned(1024)));
#endif

/*
 * Defines for communication.c.
 */
#define BUFFER_SIZE 16
#define UDMA_TIMING (BUFFER_SIZE*10*2)
#define UART0RX_INTERRUPT		0x00000100		/* Check DMACHIS register. */
#define UART0TX_INTERRUPT		0x00000200
#define UART0FIFO_INTERRUPT     0x00000010      /* Check UARTRIS or UARTMIS register*/

/*
 * Struct for store information about peripherals used in communication.h.
 */
typedef struct {
    uint32_t UART;
    uint32_t uDMA;
    uint32_t TIMER0;
}CommunicationPeripherals;

/*
 * Function that declares a initialized struct.
 */
#define DEFINE_COMMUNICATION_PERIPHERALS(name)   \
	CommunicationPeripherals name = {            \
        .UART = 0,                               \
        .uDMA = 0,                               \
        .TIMER0 = 0,                             \
    }

/*
 * Prototypes for the APIs.
 */
extern void commInit(bool *receivedAddress, char messageBuffer[]);
extern void commUART_Init(void);
extern void commUDMA_Init(void);
extern void commTIMER0_Init(void);
extern void commInterrupt(void);
extern void commTransferData(void);
extern void commReportMessage(void);
extern void commConcatenateMessage(char message[], char information[][50], int pieces);
extern void commProcessMsg(unsigned char *message);
extern void commSendMessage(char TxMessageBuffer[], uint16_t dataLength);
extern void commErrorHandler(void);
extern void commEnableInterrupt(void);
extern void commDisableInterrupt(void);
extern void commShowReport(void);

/*
 * Mark the end of the C bindings section for C++ compilers.
 */
#ifdef __cplusplus
}
#endif

#endif /* SRC_COMMUNICATION_H_ */
