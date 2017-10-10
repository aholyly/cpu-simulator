/*--------------------------------------------------------------------------*/
/*  HW05																	*/
/*--------------------------------------------------------------------------*/
/*  Computer.cpp															*/
/*--------------------------------------------------------------------------*/
/*																			*/
/*  Created by Ahmet Mert Gülbahçe on 12.11.2016.							*/
/*																			*/
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/*								Includes									*/
/*--------------------------------------------------------------------------*/
#include "Computer.h"


/*--------------------------------------------------------------------------*/
/*						Function Implementations							*/
/*--------------------------------------------------------------------------*/

// constructor; CPU, CPUProgram, Memory tiplerinde birer obje ve opsiyon
// degeri alarak opsiyon degerine gore class icinde yukaridaki tiplerde birer
// oble olusturur. Daha sonra class icindeki objelere parametre olarak aldigi
// diger objelerin atamasini yapar.
Computer::Computer(CPU aCPU, CPUProgram aCPUProgram, Memory aMemory, int optionValue)
{
	option = optionValue;
	setCPU(aCPU);
	setCPUProgram(aCPUProgram);
	setMemory(aMemory);
}

// constructor opsiyon degeri arak bu degere gore asagidaki tiplerde
// objeler olusturur.
Computer::Computer(int optionValue)
	: option(optionValue)
{ /* bilerek bos birakildi */}

// class icindeki CPUProgram objesini return eder.
CPUProgram Computer::getCPUProgram()
{
	return myCPUProgram;
}

// class icindeki CPUProgram objesini, parametre olarak aldigi degisken
// ile degistirir.
void Computer::setCPUProgram(CPUProgram aProgram)
{
	myCPUProgram = aProgram;
}

// class icindeki CPU objesini return eder.
CPU Computer::getCPU()
{
	return myCPU;
}

// class icindeki CPU objesini, parametre olarak aldigi degisken ile degistirir.
void Computer::setCPU(CPU aCPU)
{
	myCPU = aCPU;
}

// class icindeki Memory objesini return eder.
Memory Computer::getMemory()
{
	return myMemory;
}

// class icindeki Memory objesini, parametre olarak aldigi degisken ile degistirir.
void Computer::setMemory(Memory aMemory)
{
	myMemory = aMemory;
}

// CPU, CPUProgram ve Memory objelerini kullanarak programin ana islevi olan
// execute islemini gerceklestirir.
void Computer::execute()
{
	// programda hata olmadigi ve program hlt komutuna gelmedigi zaman calisir
	while(!myCPU.halted() && !myCPUProgram.checkError())
	{
		string instructon = myCPUProgram.getLine(myCPU.getPC() -1 );
		myCPU.execute(instructon, myMemory);
		myCPU.print();
		myCPU.setPC(myCPU.getPC() + 1);
	}
}

/*---------------------------------------------------------------------------*/
/* 							End of Computer.cpp								 */
/*---------------------------------------------------------------------------*/
