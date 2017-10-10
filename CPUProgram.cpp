/*--------------------------------------------------------------------------*/
/*  HW05																	*/
/*--------------------------------------------------------------------------*/
/*  CPUProgram.cpp															*/
/*--------------------------------------------------------------------------*/
/*																			*/
/*  Created by Ahmet Mert Gülbahçe on 12.11.2016.							*/
/*																			*/
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/*								Includes									*/
/*--------------------------------------------------------------------------*/
#include "CPUProgram.h"


/*--------------------------------------------------------------------------*/
/*						Function Implementations							*/
/*--------------------------------------------------------------------------*/
CPUProgram::CPUProgram(const int optionValue) : option(optionValue)
{ /* bilerek bos birakildi */ }

// parametre olarak dosya ismi alir ve dosyadan okudugu argumanlari class
// icindeki AllLines arrayi icine atar ve satiri parcalarina ayiran
// fonksiyon olan getElements i cagirir.
void CPUProgram::ReadFile(const string fileName)
{
	ifstream file;
	string tmpStr;
	
	file.open(fileName);
	
	int i;
	for (i = 0; !file.eof(); i++)
	{
		getline(file, tmpStr);
		tmpStr = makeUpper(tmpStr);
		AllLines.push_back(tmpStr);
	}
	
	file.close();
	
	// donguden ciktiginda toplam satir sayisini class elemani olan
	// tmpSize a atar.
	numberOfLines = i;
	
	getElements();
}

// getLine fonksiyonu satir numarasini parametre olarak alarak odevde
// istenen formatta instruction olarak return eder.
string CPUProgram::getLine(const int line) const
{
	string str;
	
	// instructionda sadece komut varsa
	if (checkElement(element1[line]) == 0 && checkElement(element2[line]) == 0)
	{
		str += commands[line];
		return str;
	}
	// instructionda komuttan sonra 2 tane elaman varsa
	if ((checkElement(element1[line]) != 0 && checkElement(element2[line]) != 0))
	{
		str += commands[line];
		str += " ";
		str += element1[line];
		str += ", ";
		str += element2[line];
		return str;
	}
	// instructionda komuttan sonra tek eleman varsa
	if (checkElement(element1[line]) != 0 && checkElement(element2[line]) == 0)
	{
		str += commands[line];
		str += " ";
		str += element1[line];
		return str;
	}
	
	return str;
}

// private olusturulan vectorleri tekrar kullanilmadan once silen fonksiyon
void CPUProgram::clearVectors()
{
	commands.clear();
	element1.clear();
	element2.clear();
}

// bu private fonksiyon class icindeki AllLines string arrayindeki
// instructioni parcalarina ayirarak commands, element1, element2
// stringlerine atayan fonksiyondur.
void CPUProgram::getElements()
{
	int i = 0;
	string temp;
	while (i < size())
	{
		int lineSize = AllLines[i].length();
		
		// satirdaki tab ile yapilmis bosluklari space boslugu ile degistiren dongu
		for (int j = 0; j < lineSize; ++j)
		{
			// 9: tab karakteri
			if (AllLines[i][j] == 9)
			{
				// 32: space karakteri
				AllLines[i][j] = 32;
			}
		}
		
		int found;
		// satirda ; var ise
		if (AllLines[i].find_first_of(';') != -1)
		{
			int semicolonIndex = AllLines[i].find_first_of(';');
			
			// satirdaki ilk kelimenin bulundugu ve komutlarin oldugu
			// stringe atildigi kisim
			int initialOfCommand = AllLines[i].find_first_not_of(' ');
			int firstSpaceAfterCommand = AllLines[i].find_first_of(' ',initialOfCommand);
			
			if (firstSpaceAfterCommand == -1)
				commands.push_back( AllLines[i].substr(initialOfCommand,semicolonIndex) );
			else
				commands.push_back( AllLines[i].substr(initialOfCommand,firstSpaceAfterCommand-initialOfCommand) );
			
			if (commands[i].substr(0,3) == "HLT")
			{
				element1.push_back("");
				element2.push_back("");
			}
			else
			{
				// satirda ";"'den once "," var ise
				int commaIndex = AllLines[i].find_first_of(',');
				if (commaIndex != -1 && commaIndex < semicolonIndex)
				{
					// komuttan sonraki ilk kelimeden virgule kadar olan kismi
					// element1 e atanmasi kismi
					int initialOfElement1 = AllLines[i].find_first_not_of(' ',firstSpaceAfterCommand);
					temp.clear();
					temp = AllLines[i].substr(initialOfElement1,commaIndex-initialOfElement1);
					found = temp.find_first_of(' ');
					element1.push_back( temp.substr(0,found) );
					
					// eger virgul ile noktali virgul art arda ise
					// ikinci elemanin bos oldugu atanir.
					if (semicolonIndex- commaIndex == 1)
					{
						element2.push_back("");
					}
					else
					{
						// virgulden sonra noktali virgule kadar olan kisim bulunur ve
						// aradaki bosluklar atilarak en son element2 ye atanir.
						temp.clear();
						temp = AllLines[i].substr(commaIndex+1,semicolonIndex-commaIndex-1);
						found = temp.find_first_not_of(' ');
						if(found == -1)
						{
							element2.push_back("");
						}
						else
						{
							element2.push_back( temp.substr(found,semicolonIndex-found) );
							found = element2[i].find_first_of(' ');
							temp.clear();
							temp = element2[i].substr(0,found);
							element2[i] = temp;
						}
					}
				}
				// satirda virgul yok ise komuttan sonraki ilk harften sonra noktali
				// virgule kadar olan kisim alinir ve bosluklar silinerek
				// element1 e atanir.
				else if(firstSpaceAfterCommand != -1)
				{
					int initialOfElement1 = AllLines[i].find_first_not_of(' ',firstSpaceAfterCommand);
					temp.clear();
					temp = AllLines[i].substr(initialOfElement1,semicolonIndex-initialOfElement1);
					found = temp.find_first_of(' ');
					element1.push_back( temp.substr(0,found) );
					element2.push_back("");
				}
			}
		}
		// satirda noktali virgul yok ise
		else
		{
			// satirdaki ilk kelimenin bulundugu ve komutlarin oldugu
			// stringe atildigi kisim
			
			int initialOfCommand = AllLines[i].find_first_not_of(' ');
			int firstSpaceAfterCommand = AllLines[i].find_first_of(' ',initialOfCommand);
			
			if (firstSpaceAfterCommand == -1)
				commands.push_back( AllLines[i].substr(initialOfCommand,lineSize) );
			else
				commands.push_back( AllLines[i].substr(initialOfCommand,firstSpaceAfterCommand-initialOfCommand) );
			
			if (commands[i].substr(0,3) == "HLT")
			{
				element1.push_back("");
				element2.push_back("");
			}
			else
			{
				// satir "," var ise
				int commaIndex = AllLines[i].find_first_of(',');
				if (commaIndex != -1 && commaIndex < lineSize)
				{
					// komuttan sonraki ilk kelimeden virgule kadar olan kismi
					// element1 e atanmasi kismi
					int initialOfElement1 = AllLines[i].find_first_not_of(' ',firstSpaceAfterCommand);
					temp.clear();
					temp = AllLines[i].substr(initialOfElement1,commaIndex-initialOfElement1);
					found = temp.find_first_of(' ');
					element1.push_back( temp.substr(0,found) );
					
					// eger virgulden hemen sonra satir sonu var ise
					// ikinci elemanin bos oldugu atanir.
					if (lineSize- commaIndex == 1)
					{
						element2.push_back("");
					}
					else
					{
						// virgulden sonra satir sonuna kadar olan kisim bulunur ve
						// aradaki bosluklar atilarak en son element2 ye atanir.
						temp.clear();
						temp = AllLines[i].substr(commaIndex+1,lineSize-commaIndex-1);
						found = temp.find_first_not_of(' ');
						if(found == -1)
						{
							element2.push_back("");
						}
						else{
							element2.push_back (temp.substr(found,lineSize-found) );
							found = element2[i].find_first_of(' ');
							temp.clear();
							temp = element2[i].substr(0,found);
							element2[i] = temp;
						}
					}
				}
				// satirda virgul yok ise komuttan sonraki ilk harften sonra satir
				// satir kadar olan kisim alinir ve bosluklar silinerek
				// element1 e atanir.
				else if (firstSpaceAfterCommand != -1)
				{
					int initialOfElement1 = AllLines[i].find_first_not_of(' ',firstSpaceAfterCommand);
					temp.clear();
					temp = AllLines[i].substr(initialOfElement1,lineSize-initialOfElement1);
					found = temp.find_first_of(' ');
					element1.push_back( temp.substr(0,found) );
					element2.push_back("");
				}
			}
		}
		i++;
	}
}

// instruction, register ve sabit sayi degerlerini yazim ve mantiksal hatalara
// gore dogru olup olmadigini kontrol eden fonksiyon.
// return 1 : hata var - return 0 : hata yok
int CPUProgram::checkError() const
{
	int i = 0, errorCounter = 0;
	
	if (option != 0 && option != 1 && option != 2)
	{
		cerr << "WRONG INPUT PARAMETER" << endl;
		return 1;
	}
	
	while (i < size())
	{
		int error = 1;
		if (commands[i] == "MOV")
		{
			if ((checkElement(element1[i]) == 1 && (checkElement(element2[i]) == 1 ||
													checkElement(element2[i]) == 2 ||
													checkElement(element2[i]) == 3)) ||
				(checkElement(element1[i]) == 3 && (checkElement(element2[i]) == 1 ||
													checkElement(element2[i]) == 2)))
				error = 0;
		}
		if (commands[i] == "ADD")
		{
			if ((checkElement(element1[i]) == 1 && (checkElement(element2[i]) == 1 ||
													checkElement(element2[i]) == 2 ||
													checkElement(element2[i]) == 3)))
				error = 0;
		}
		if (commands[i] == "SUB")
		{
			if ((checkElement(element1[i]) == 1 && (checkElement(element2[i]) == 1 ||
													checkElement(element2[i]) == 2 ||
													checkElement(element2[i]) == 3)))
				error = 0;
		}
		if (commands[i] == "JMP")
		{
			if (checkElement(element1[i]) == 1 && checkElement(element2[i]) == 2)
			{
				if (convertToInt(element2[i]) <= size())
					error = 0;
			}
			if (checkElement(element1[i]) == 2 && checkElement(element2[i]) == 0)
			{
				if (convertToInt(element2[i]) <= size())
					error = 0;
			}
		}
		if (commands[i] == "JPN")
		{
			if (checkElement(element1[i]) == 1 && checkElement(element2[i]) == 2)
			{
				if (convertToInt(element2[i]) <= size())
					error = 0;
			}
		}
		if (commands[i] == "PRN")
		{
			if (checkElement(element1[i]) == 1 && checkElement(element2[i]) == 0)
				error = 0;
			if (checkElement(element1[i]) == 2 && checkElement(element2[i]) == 0)
				error = 0;
			if (checkElement(element1[i]) == 3 && checkElement(element2[i]) == 0)
				error = 0;
		}
		if (commands[i] == "HLT" && checkElement(element1[i]) == 0 && checkElement(element2[i]) == 0)
			error = 0;
		
		if (error == 1)
			cerr << "UNDEFINED COMMAND AT LINE: " << i+1 << endl;
		else
			errorCounter++;
		
		if (errorCounter == size())
			return 0;
		i++;
	}
	
	return 1;
}

// Parametre olarak aldigi stringin tum elemanlarini buyuk harfe ceviren fonksiyon
// return : aldigi stringin buyuk harfe donusturulmus hali
string CPUProgram::makeUpper(string str) const
{
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] = char(((int)str[i]) - 32);
	}
	return str;
}

// Parametre olarak aldigi stringin icindeki sayi degerini kurtarip gerekli
// islemler ile int bir degere ceviren fonksiyon
// return : string teki sayi degerinin int olarak ciktisi
int CPUProgram::convertToInt(const string str) const
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
int CPUProgram::checkElement(const string str) const
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

/* -----------------------------------------------------------------------*/
/*							OPERATOR OVERLOADINGS						  */
/* -----------------------------------------------------------------------*/

// operator []
// return: indexteki string
const string CPUProgram::operator[](const int index)
{
	// girilen index satir sayisindan fazlaysa hata mesaji verir
	if ( index >= size() )
	{
		cerr << "YOU ARE OUT OF LINES" << endl;
		return "ERROR";
	}
	
	// hata yoksa indexte bulunan instruction return edilir.
	return getLine(index);
}

// operator + (CPUProgram + string)
// return: eski CPUProgram'a string eklenerek yeni bir CPUProgram dondurur
CPUProgram CPUProgram::operator+(const string instruction) const
{
	if (instruction == "")
	{
		cerr << "NO ENTERED INSTRUCTION FOUND" << endl;
		return *this;
	}
	else
	{
		CPUProgram tmpProg = *this;
		
		tmpProg.setSize(size() + 1);
		tmpProg.AllLines.push_back(instruction);
		tmpProg.clearVectors();
		tmpProg.getElements();

		return tmpProg;
	}
}

// operator +=
// return: eski CPUProgram'a string eklenerek eski CPUProgram'i return eder.
CPUProgram CPUProgram::operator+=(const string instruction)
{
	if (instruction == "")
	{
		cerr << "NO ENTERED INSTRUCTION FOUND" << endl;
		return *this;
	}
	else
	{
		setSize(size() + 1);
		AllLines.push_back(instruction);
		clearVectors();
		getElements();
	
		return *this;
	}
}

// opetor <<
// return: obje icindeki tum instructionlari ekrana basan ostream referansi
ostream& operator<<(ostream& out, const CPUProgram& obj)
{
	for (int i = 0; i < obj.size(); i++)
	{
		out << obj.getLine(i);
		if (i != obj.size() - 1)
			out << endl;
	}
	
	return out;
}

// operator + (CPUProgram + CPUProgram)
// return iki CPUProgram'in toplanarak sol elemana eklenip return edilmesi
CPUProgram CPUProgram::operator+(const CPUProgram& obj2)
{
	setSize( size() + obj2.size() );
	
	for (int i = 0; i < obj2.size(); i++)
	{
		AllLines.push_back(obj2.AllLines[i]);
	}
	
	clearVectors();
	getElements();
	
	return *this;
}

// operator ==
bool CPUProgram::operator==(const CPUProgram& obj2) const
{
	if ( size() == obj2.size() )
		return true;
	else
		return false;
}

// operator !=
bool CPUProgram::operator!=(const CPUProgram& obj2) const
{
	if ( size() != obj2.size() )
		return true;
	else
		return false;
}

// operator <
bool CPUProgram::operator<(const CPUProgram& obj2) const
{
	if ( size() < obj2.size() )
		return true;
	else
		return false;
}

// operator >
bool CPUProgram::operator>(const CPUProgram& obj2) const
{
	if ( size() > obj2.size() )
		return true;
	else
		return false;
}

// operator <=
bool CPUProgram::operator<=(const CPUProgram& obj2) const
{
	if ( size() <= obj2.size() )
		return true;
	else
		return false;
}

// operator >=
bool CPUProgram::operator>=(const CPUProgram& obj2) const
{
	if ( size() >= obj2.size() )
		return true;
	else
		return false;
}

// operator -- (CPUProgram--)
CPUProgram CPUProgram::operator--(int ignoreMe)
{
	CPUProgram tmpProg = *this;
	AllLines.pop_back();
	commands.pop_back();
	element1.pop_back();
	element2.pop_back();
	
	return tmpProg;
}

// operator -- (--CPUProgram)
CPUProgram CPUProgram::operator--()
{
	AllLines.pop_back();
	commands.pop_back();
	element1.pop_back();
	element2.pop_back();
	
	return *this;
}

// operator ()
// return: arguman olarak aldigi index1 ve index2 arasindaki instructionlari
// alarak yeni obje ile dondurur.
CPUProgram CPUProgram::operator()(const int index1, const int index2)
{
	if ( index1 >= size() || index2 >= size() || index1 < 0 || index2 < 0)
	{
		cerr << "ENTERED NUMBER IS NOT VALID" << endl;
		return CPUProgram(getOption());
	}
	else
	{
		CPUProgram tmpProg;
		tmpProg.setOption( getOption() );
		int lineCount = (index1 <= index2) ? index1 : index2;
		int loopCount = 0;
		tmpProg.setSize(abs(index1-index2)+1);
		while( loopCount <= abs(index1 - index2) )
		{
			tmpProg.AllLines.push_back(AllLines[lineCount]);
			loopCount++;
			lineCount++;
		}
		tmpProg.getElements();
		
		return tmpProg;
	}
}

/*---------------------------------------------------------------------------*/
/* 							End of CPUProgram.cpp							 */
/*---------------------------------------------------------------------------*/
