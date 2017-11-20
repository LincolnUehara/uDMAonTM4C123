/*
 * debug.h
 */

#ifndef SRC_DEBUG_H_
#define SRC_DEBUG_H_

/*
 * If building with a C++ compiler, make all of the definitions in this header
 * have a C binding.
 */
#ifdef __cplusplus
extern "C"
{
#endif

/*
 * Defines used for debugLED function.
 */
#define RED       GPIO_PIN_1
#define BLUE      GPIO_PIN_2
#define GREEN     GPIO_PIN_3
#define YELLOW    ( RED | GREEN )
#define MAGENTA   ( RED | BLUE )
#define CYAN      ( GREEN | BLUE )
#define WHITE     ( RED | GREEN | BLUE )

/*
 * Prototypes for the APIs.
 */
extern void debugInit(void);
extern void debugLED(uint32_t color);
extern void commReportMessage1(void);
extern void commReportMessage2(void);

/*
 * Mark the end of the C bindings section for C++ compilers.
 */
#ifdef __cplusplus
}
#endif

#endif /* SRC_DEBUG_H_ */
