/*
 * mem.h
 *
 *  Created on: 27.12.2011
 *      Author: Alex
 */

#ifndef MEM_H_
#define MEM_H_

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus
unsigned char *newMem(unsigned size);
void freeMem(unsigned char *ptr);
#ifdef __cplusplus
}
#endif // __cplusplus




#endif /* MEM_H_ */
