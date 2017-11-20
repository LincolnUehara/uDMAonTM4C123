/*
 * uDMA.h
 */

#ifndef SRC_UDMA_H_
#define SRC_UDMA_H_

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
 * DMA Channel Interrupt Status (DMACHIS) flags.
 */
#define UDMA_UART0_RX		0x00000100
#define UDMA_UART0_TX		0x00000200

/*
 * Struct for store information about peripherals interrupt
 * and function that declares a initialized struct.
 */
typedef struct {
    uint32_t RAW;
    uint32_t MASKED;
    uint32_t uDMA;
}PeripheralInterrupt;

#define DEFINE_PERIPHERAL_INTERRUPT(name)       \
		PeripheralInterrupt name = {            \
        .RAW = 0,                               \
        .MASKED = 0,                            \
        .uDMA = 0,                              \
    }

/*
 * Prototypes for the APIs.
 */
extern void uDMAInit(void);
extern void uDMAInitUART0(void);
extern void uDMAReceiveUART0(char RxMessageBuffer[], uint16_t dataLength);
extern void uDMASendUART0(char TxMessageBuffer[], uint16_t dataLength);
extern void uDMAErrorHandler(void);

/*
 * Mark the end of the C bindings section for C++ compilers.
 */
#ifdef __cplusplus
}
#endif

#endif /* SRC_UDMA_H_ */
