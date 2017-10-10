/*--------------------------------------------------------------------------*/
/*  HW05																	*/
/*--------------------------------------------------------------------------*/
/*  CPU.h																	*/
/*--------------------------------------------------------------------------*/
/*																			*/
/*  Created by Ahmet Mert Gülbahçe on 12.11.2016.							*/
/*																			*/
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/*								Defines										*/
/*--------------------------------------------------------------------------*/
#ifndef CPU_h
#define CPU_h

/*--------------------------------------------------------------------------*/
/*								Includes									*/
/*--------------------------------------------------------------------------*/
#include <iostream>
#include <string>
#include "Memory.h"

using namespace std;

// ----------
// class CPU
// ----------
class CPU
{
public:
	CPU(const int optionValue);
	CPU(){};
	int getPC() const;
	void setPC(const int value);
	int getRegister(const int index) const;
	int getRegister(const string regName) const;
	void setRegister();
	void setRegister(const string regName, const int value);
	int getMemory(int index);
	void setMemory(const int index, const int value);
	void print() const;
	void execute(const string instruction, Memory&);
	int halted();
	int convertToInt(const string str);
	int checkElement(const string str);
private:
	int PC = 1;
	int reg[5];
	int hlt = 0;
	int option;
	Memory memory;
	string instruction, command, element1, element2;
	void getElements();
	void doInstructions();
};


#endif /* CPU_h */

/*---------------------------------------------------------------------------*/
/* 							End of CPU.h									 */
/*---------------------------------------------------------------------------*/
