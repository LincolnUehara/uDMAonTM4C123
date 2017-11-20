/*
 * processing.h
 */

#ifndef SRC_PROCESSING_H_
#define SRC_PROCESSING_H_

/*
 * If building with a C++ compiler, make all of the definitions in this header
 * have a C binding.
 */
#ifdef __cplusplus
extern "C"
{
#endif

/*
 * Prototypes for the APIs.
 */
extern void commProcessMsg(unsigned char *message);

/*
 * Mark the end of the C bindings section for C++ compilers.
 */
#ifdef __cplusplus
}
#endif

#endif /* SRC_PROCESSING_H_ */
