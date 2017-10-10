/*--------------------------------------------------------------------------*/
/*  HW05																	*/
/*--------------------------------------------------------------------------*/
/*  Computer.h																*/
/*--------------------------------------------------------------------------*/
/*																			*/
/*  Created by Ahmet Mert Gülbahçe on 12.11.2016.							*/
/*																			*/
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/*								Defines										*/
/*--------------------------------------------------------------------------*/
#ifndef Computer_h
#define Computer_h


/*--------------------------------------------------------------------------*/
/*								Includes									*/
/*--------------------------------------------------------------------------*/
#include <iostream>
#include "CPUProgram.h"
#include "CPU.h"
#include "Memory.h"


// ---------------
// class Computer
// ---------------
class Computer
{
public:
	Computer(CPU, CPUProgram, Memory, int);
	Computer(int);
	Computer(){};
	CPUProgram getCPUProgram();
	CPU getCPU();
	Memory getMemory();
	void setCPUProgram(CPUProgram);
	void setCPU(CPU);
	void setMemory(Memory);
	void execute();
private:
	int option;
	string fileName;
	CPUProgram myCPUProgram;
	CPU myCPU;
	Memory myMemory;
};

#endif /* Computer_h */

/*---------------------------------------------------------------------------*/
/* 							End of Computer.h								 */
/*---------------------------------------------------------------------------*/
