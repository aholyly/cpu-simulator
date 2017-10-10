/*--------------------------------------------------------------------------*/
/*  HW05																	*/
/*--------------------------------------------------------------------------*/
/*  CPU.cpp																	*/
/*--------------------------------------------------------------------------*/
/*																			*/
/*  Created by Ahmet Mert Gülbahçe on 12.11.2016.							*/
/*																			*/
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/*								Includes									*/
/*--------------------------------------------------------------------------*/
#include "CPU.h"


/*--------------------------------------------------------------------------*/
/*						Function Implementations							*/
/*--------------------------------------------------------------------------*/

// contructor parametre almaz ve icindeki registerlara sifir atar.
CPU::CPU(const int optionValue) : option(optionValue), memory(optionValue)
{
	setRegister();
}

// private kismindan PC degerini alir ve return eder.
int CPU::getPC() const
{
	return PC;
}

// parametre olarak bir deger alir ve bu degeri PC ye atar
void CPU::setPC(const int value)
{
	PC = value;
}

int CPU::getRegister(const int index) const
{
	return reg[index];
}

// parametre olarak register ismini string olarak alir ve bulundugu
// indexteki degerini return eder.
int CPU::getRegister(const string regName) const
{
	if (regName == "R1")
		return reg[0];
	if (regName == "R2")
		return reg[1];
	if (regName == "R3")
		return reg[2];
	if (regName == "R4")
		return reg[3];
	if (regName == "R5")
		return reg[4];
	return -1;
}

// parametre almazsa register degerlerini 0 olarak atama yapar.
void CPU::setRegister()
{
	reg[0] = 0; reg[1] = 0; reg[2] = 0; reg[3] = 0; reg[4] = 0;
}

// parametre olarak register ismini string olarak alir ve registerin degerini
// int olarak aldigi parametre ile degistirir.
void CPU::setRegister(const string regName, const int value)
{
	if (regName == "R1")
		reg[0] = value;
	if (regName == "R2")
		reg[1] = value;
	if (regName == "R3")
		reg[2] = value;
	if (regName == "R4")
		reg[3] = value;
	if (regName == "R5")
		reg[4] = value;
}

// memory objesinin indexindeki memory degerini return eder.
int CPU::getMemory(int index)
{
	return memory.getMem(index);
}

// memory objesinin indexindeki degeri value degeri ile degistirir.
void CPU::setMemory(const int index, const int value)
{
	memory.setMem(index, value);
}

// parametre olarak aldigi opsiyona gore registerlari ekrana basar.
void CPU::print() const
{
	if (option == 1 || option == 2)
	{
		cout << instruction << endl;
		for (int i = 0; i < 5; i++)
		{
			cout << "[" << i << "] -> " << getRegister(i) << endl;
		}
		if (option == 2)
			memory.printAll();
	}
}

// fonsiyona gelen instruction stringini kullanarak once getElements fonksiyonu
// ile bu stringi parcalarina ayirarak komutlari yerine getiren fonksiyon olan
// doInstructions fonksiyonuna parametre olarak gonderir ve komutlar yerine
// getirilir.
void CPU::execute(const string inst, Memory &memo)
{
	instruction = inst;
	memory = memo;
	getElements();
	doInstructions();
	memo = memory;
}

// return 1: halt komutu bulundu
// return 0; halt komutu bulunmadi
int CPU::halted()
{
	if (hlt == 1)
		return 1;
	return 0;
}

// parametre olarak aldigi instructioni parcalarina ayirir ve ayirdigi bu
// elemanlari gerekli degiskene atar.
void CPU::getElements()
{
	string temp;
	int lineSize = instruction.length();
	
	// satirdaki ilk kelimenin bulundugu ve komutlarin oldugu
	// stringe atildigi kisim
	int found;
	int initialOfCommand = instruction.find_first_not_of(' ');
	int firstSpaceAfterCommand = instruction.find_first_of(' ',initialOfCommand);
	
	if (firstSpaceAfterCommand == -1)
	{
		command = instruction.substr(initialOfCommand,lineSize);
		return;
	}
	else
		command = instruction.substr(initialOfCommand,firstSpaceAfterCommand-initialOfCommand);
	
	// satirda "," var ise
	int commaIndex = instruction.find_first_of(',');
	if (commaIndex != -1)
	{
		// komuttan sonraki ilk kelimeden virgule kadar olan kismi
		// element1 e atanmasi kismi
		int initialOfElement1 = instruction.find_first_not_of(' ',firstSpaceAfterCommand);
		temp.clear();
		temp = instruction.substr(initialOfElement1,commaIndex-initialOfElement1);
		found = temp.find_first_of(' ');
		element1 = temp.substr(0,found);
		
		// eger virgulden hemen sonra satir sonu var ise
		// ikinci elemanin bos oldugu atanir.
		if (lineSize- commaIndex == 1)
		{
			element2 = "";
		}
		else
		{
			// virgulden sonra satir sonuna kadar olan kisim bulunur ve
			// aradaki bosluklar atilarak en son element2 ye atanir.
			temp.clear();
			temp = instruction.substr(commaIndex+1,lineSize-commaIndex-1);
			found = temp.find_first_not_of(' ');
			if(found == -1)
			{
				element2 = "";
			}
			else{
				element2 = temp.substr(found,lineSize-found);
				found = element2.find_first_of(' ');
				temp.clear();
				temp = element2.substr(0,found);
				element2 = temp;
			}
		}
	}
	// satirda virgul yok ise komuttan sonraki ilk harften sonra satir
	// satir kadar olan kisim alinir ve bosluklar silinerek
	// element1 e atanir.
	else if (firstSpaceAfterCommand != -1)
	{
		int initialOfElement1 = instruction.find_first_not_of(' ',firstSpaceAfterCommand);
		temp.clear();
		temp = instruction.substr(initialOfElement1,lineSize-initialOfElement1);
		found = temp.find_first_of(' ');
		element1 = temp.substr(0,found);
		element2 = "";
	}
}

// parametre olarak aldigi komut ve elemanlari kullanarak programin yerine getirmesi
// gereken komutlarin uygulandigi fonksiyon.
void CPU::doInstructions() 
{
	int adressIndex;
	
	// adres ise adresin indexi bulunur
	if (checkElement(element1) == 3)
		adressIndex = convertToInt(element1.substr(1));
	if (checkElement(element2) == 3)
		adressIndex = convertToInt(element2.substr(1));
	
	// komut MOV ise
	if (command == "MOV")
	{
		if (checkElement(element1) == 1)
		{
			// ilk eleman register, ikinci eleman da register ise
			if (checkElement(element2) == 1)
				setRegister(element1, getRegister(element2));
			// ilk eleman register, ikinci eleman sabit sayi ise
			if (checkElement(element2) == 2)
				setRegister(element1, convertToInt(element2));
			// ilk eleman register, ikinci eleman adres ise
			if (checkElement(element2) == 3)
				setMemory(adressIndex,getRegister(element1));
		}
		if (checkElement(element1) == 3)
		{
			// ilk eleman adres, ikinci eleman register ise
			if (checkElement(element2) == 1)
				setRegister(element2, getMemory(adressIndex));
			// ilk eleman adres, ikinci eleman sabit sayi ise
			if (checkElement(element2) == 2)
				setMemory(adressIndex, convertToInt(element2));
		}
	}
	// komut ADD ise
	if (command == "ADD")
	{
		// ilk eleman register olacagi icin ikinci elemanin hangi eleman oldugunu
		// kontrol eder
		if (checkElement(element2) == 1)
			setRegister(element1, getRegister(element1) + getRegister(element2));
		if (checkElement(element2) == 2)
			setRegister(element1, getRegister(element1) + convertToInt(element2));
		if (checkElement(element2) == 3)
			setRegister(element1, getRegister(element1) + getMemory(adressIndex));
	}
	// komut SUB ise
	if (command == "SUB")
	{
		// ilk eleman register olacagi icin ikinci elemanin hangi eleman oldugunu
		// kontrol eder
		if (checkElement(element2) == 1)
			setRegister(element1, getRegister(element1) - getRegister(element2));
		if (checkElement(element2) == 2)
			setRegister(element1, getRegister(element1) - convertToInt(element2));
		if (checkElement(element2) == 3)
			setRegister(element1, getRegister(element1) - getMemory(adressIndex));
	}
	// komut PRN ise
	if (command == "PRN")
	{
		// hangi elemanin ekrana basilacagini kontrol eder
		if (checkElement(element1) == 1)
			cout << getRegister(element1) << endl;
		if (checkElement(element1) == 2)
			cout << convertToInt(element2) << endl;
		if (checkElement(element1) == 3)
			cout << getMemory(adressIndex) << endl;
	}
	// komut HLT ise
	if (command == "HLT")
		hlt = 1;
	// komut JMP ise
	if (command == "JMP")
	{
		// ilk eleman register ve ikici eleman sabit ise
		if (checkElement(element1) == 1 && checkElement(element2) == 2)
		{
			// register'in degeri 0 ise
			if (getRegister(element1) == 0)
				setPC(convertToInt(element2)-1);
		}
		if (checkElement(element1) == 2 && checkElement(element2) == 0)
			setPC(convertToInt(element1)-1);
	}
	if (command == "JPN")
	{
		// ilk eleman register ve ikici eleman sabit ise
		if (checkElement(element1) == 1 && checkElement(element2) == 2)
		{
			// register'in degeri 0 veya daha kucukse ise
			if (getRegister(element1) <= 0)
				setPC(convertToInt(element2)-1);
		}
	}
	print();
}

// Parametre olarak aldigi stringin icindeki sayi degerini kurtarip gerekli
// islemler ile int bir degere ceviren fonksiyon
// return : string teki sayi degerinin int olarak ciktisi
int CPU::convertToInt(const string str)
{
	int size = str.length();
	int number, result = 0;
	int i;
	
	for (i = 0; i < size-1; ++i)
	{
		number = ((int)str[i] - 48);
		
		for (int j = size-1-i; j > 0; --j)
		{
			number *= 10;
		}
		result += number;
	}
	return result+((int)str[i] - 48);
}

// Parametre olarak aldigi stringin nasil bir deger oldugunu bulan fonksiyon
// return 1 : register(R1,R2,R3,R4,R5'ten biri)
// return 0 : eleman yok
// return 2 : sabit sayi
// return -1 : yanlis bir degerse
int CPU::checkElement(const string str)
{
	if (str == "")
		return 0; //eleman olmamasi durumu
	else if (str == "R1" || str == "R2" || str == "R3" || str == "R4" || str == "R5")
		return 1; //register olma durumu
	else if ((int) str.find_first_not_of("0123456789") == -1)
		return 2; //sayi olma durumu
	else if (str[0] == '#' && (int) str.substr(1).find_first_not_of("0123456789") == -1)
		return 3 ; //adres olma durumu
	else
		return -1; //hata durumu
}

/*---------------------------------------------------------------------------*/
/* 							End of CPU.cpp									 */
/*---------------------------------------------------------------------------*/
