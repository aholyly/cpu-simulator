/*--------------------------------------------------------------------------*/
/*  HW05																	*/
/*--------------------------------------------------------------------------*/
/*  Memory.cpp																*/
/*--------------------------------------------------------------------------*/
/*																			*/
/*  Created by Ahmet Mert Gülbahçe on 12.11.2016.							*/
/*																			*/
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/*								Includes									*/
/*--------------------------------------------------------------------------*/
#include "Memory.h"


/*--------------------------------------------------------------------------*/
/*						Function Implementations							*/
/*--------------------------------------------------------------------------*/

// constructor olarak opsiyon degeri alir ve tum memory
// degerlerini sifirlar.
Memory::Memory(int optionValue) : option(optionValue)
{
	setMem();
}

// indexteki memory degerini return eder.
int Memory::getMem(const int index) const
{
	return memory[index];
}

// tum memory degerlerini sifirlar.
void Memory::setMem()
{
	for (int i = 0; i < 50; i++)
		memory[i] = 0;
}

// indexteki memory degerini value degeri ile degistirir.
void Memory::setMem(const int index, const int value)
{
	memory[index] = (unsigned int)value;
}

// memory deki tum elemanlari ekrana yazdirir.
void Memory::printAll() const
{
	for (int i = 0; i < 50; i++)
	{
		cout << "[" << i << "] -> " << getMem(i) << endl;
	}
}

/*---------------------------------------------------------------------------*/
/* 							End of Memory.cpp								 */
/*---------------------------------------------------------------------------*/
