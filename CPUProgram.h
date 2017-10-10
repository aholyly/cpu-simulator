/*--------------------------------------------------------------------------*/
/*  HW05																	*/
/*--------------------------------------------------------------------------*/
/*  CPUProgram.h															*/
/*--------------------------------------------------------------------------*/
/*																			*/
/*  Created by Ahmet Mert Gülbahçe on 12.11.2016.							*/
/*																			*/
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/*								Defines										*/
/*--------------------------------------------------------------------------*/
#ifndef CPUProgram_h
#define CPUProgram_h


/*--------------------------------------------------------------------------*/
/*								Includes									*/
/*--------------------------------------------------------------------------*/
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

// -----------------
// class CPUProgram
// -----------------
class CPUProgram
{
public:
	CPUProgram(const int optionValue);
	CPUProgram(){};
	void ReadFile(const string fileName);
	string getLine(const int line) const;
	int size() const{return numberOfLines;};
	void setSize(const int sizeValue){numberOfLines = sizeValue;};
	int getOption() const{return option;};
	void setOption(const int optionValue){option = optionValue;};
	void clearVectors();
	int checkError() const;
	void getElements();
	string makeUpper(string str) const;
	int convertToInt(const string str) const;
	int checkElement(string str) const;
	const string operator[](const int index);
	CPUProgram operator+(const string instruction) const;
	CPUProgram operator+=(const string instruction);
	friend ostream& operator<<(ostream& out, const CPUProgram& obj);
	CPUProgram operator+(const CPUProgram& obj2);
	bool operator==(const CPUProgram& obj2) const;
	bool operator!=(const CPUProgram& obj2) const;
	bool operator<(const CPUProgram& obj2) const;
	bool operator>(const CPUProgram& obj2) const;
	bool operator<=(const CPUProgram& obj2) const;
	bool operator>=(const CPUProgram& obj2) const;
	CPUProgram operator--(int ignoreMe);
	CPUProgram operator--();
	CPUProgram operator()(const int index1, const int index2);
private:
	int option;
	int numberOfLines;
	vector <string> AllLines;
	vector <string> commands;
	vector <string> element1;
	vector <string> element2;
};

#endif /* CPUProgram_h */

/*---------------------------------------------------------------------------*/
/* 							End of CPUProgram.h								 */
/*---------------------------------------------------------------------------*/
