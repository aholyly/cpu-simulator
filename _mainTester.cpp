/*--------------------------------------------------------------------------*/
/*  HW05																	*/
/*--------------------------------------------------------------------------*/
/*  _mainTester.cpp															*/
/*--------------------------------------------------------------------------*/
/*																			*/
/*  Created by Ahmet Mert Gülbahçe on 12.11.2016.							*/
/*																			*/
/*--------------------------------------------------------------------------*/

#include "requiredIncs.h"

int main(int argc, const char * argv[]) {
	
	//////////////////////////////////////////////////////////////////////////
	//command line parameters
	const char* filename = argv[1];
	int option = atoi(argv[2]);
	//////////////////////////////////////////////////////////////////////////

	if(argc != 2)
	{
		cout << "Usage:" << endl << argv[0] << " <filename>" << endl;
		cout << "filename: is a text file full of commands" << endl;
		exit(1);
	}
	
	
	//////////////////////////////////////////////////////////////////////////
	//Testing class CPUProgram
	//op []
	cout << "-------" << endl;
	CPUProgram myCPUProgram(option);
	myCPUProgram.ReadFile(filename);
	cout << myCPUProgram[0] << endl;
	cout << myCPUProgram[myCPUProgram.size() - 1] << endl;
	
	//op +
	cout << "-------" << endl;
	cout << ((myCPUProgram + "MOV R1, #45")[myCPUProgram.size() ]) << endl;
	
	//op +=
	cout << "-------" << endl;
	myCPUProgram += "MOV R2, #50";
	cout << myCPUProgram[myCPUProgram.size() - 1] << endl;
	
	//op + <<
	cout << "-------" << endl;
	CPUProgram myOtherCPUProgram(option);
	myOtherCPUProgram.ReadFile(filename);
	cout << (myCPUProgram + myOtherCPUProgram) << endl;
	
	//op COMP --
	cout << "-------" << endl;
	cout << (myCPUProgram == myOtherCPUProgram ? "DONE" : "FAIL") << endl;
	cout << (myCPUProgram <= myOtherCPUProgram ? "DONE" : "FAIL") << endl;
	cout << (myCPUProgram > myOtherCPUProgram ? "FAIL" : "DONE") << endl;
	
	--myOtherCPUProgram;
	cout << "-------" << endl;
	cout << (myCPUProgram != myOtherCPUProgram ? "DONE" : "FAIL") << endl;
	cout << (myCPUProgram >= myOtherCPUProgram ? "DONE" : "FAIL") << endl;
	cout << (myCPUProgram < myOtherCPUProgram ? "FAIL" : "DONE") << endl;
	
	//op ()
	cout << "-------" << endl;
	cout << myCPUProgram(5, 10) << endl;
	
	//error check
	cout << "-------" << endl;
	cout << myCPUProgram[myCPUProgram.size()] << endl;
	myCPUProgram += "";
	cout << myCPUProgram[myCPUProgram.size() - 1] << endl;
	cout << "-------" << endl;
	//////////////////////////////////////////////////////////////////////////
	
    return 0;
}

/*---------------------------------------------------------------------------*/
/* 							End of _mainTester.cpp							 */
/*---------------------------------------------------------------------------*/
