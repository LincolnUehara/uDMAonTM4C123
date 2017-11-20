/*
 * UART0.h
 */

#ifndef SRC_UART0_H_
#define SRC_UART0_H_

/*
 * If building with a C++ compiler, make all of the definitions in this header
 * have a C binding.
 */
#ifdef __cplusplus
extern "C"
{
#endif

/*
 * Constant used in UART0.h
 */
#define FIFO_TRIGGER_SIZE       8

/*
 * Prototypes for the APIs.
 */
extern void UART0Init(bool *received, bool *sent,
		char RxBuffer[]);
extern void UART0Interrupt(void);
extern void UART0SendMessage(char TxBuffer[]);
extern void UART0_CheckAndSend(void);

/*
 * Mark the end of the C bindings section for C++ compilers.
 */
#ifdef __cplusplus
}
#endif

#endif /* SRC_UART0_H_ */
