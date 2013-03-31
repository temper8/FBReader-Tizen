/*
 * mem.cpp
 *
 *  Created on: 27.12.2011
 *      Author: Alex
 */

#include "mem.h"
#include <FBase.h>

unsigned char *newMem1(unsigned size){
	AppLog("newMem1 %d",size);
return new unsigned char[size];
}

void freeMem1(unsigned char *ptr){
	AppLog("freeMem1");
	delete[] ptr;
}

class mem {
public:
	static unsigned char *newMem(unsigned size);
	static void freeMem(unsigned char *ptr);
	mem();
	virtual ~mem();
};

unsigned char *mem::newMem(unsigned size){
	return new unsigned char[size];
}

void mem::freeMem(unsigned char *ptr){
	delete[] ptr;
}

mem::mem() {
	// TODO Auto-generated constructor stub

}

mem::~mem() {
	// TODO Auto-generated destructor stub
}

extern "C"
{
unsigned char *newMem(unsigned size){
	AppLog("newMem");
	return newMem1(size);
}

void freeMem(unsigned char *ptr){
	AppLog("freeMem");
	freeMem1(ptr);
}
}

