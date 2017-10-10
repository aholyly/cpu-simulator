void CPUProgramDyn::getElements()
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
				AllLines[i] = AllLines[i].substr(initialOfCommand,semicolonIndex);
			else
				AllLines[i] = AllLines[i].substr(initialOfCommand,firstSpaceAfterCommand-initialOfCommand);
			
			if (commands[i].substr(0,3) == "HLT")
			{
				element1[i] = "";
				element2[i] = "";
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
					element1[i] = temp.substr(0,found);
					
					// eger virgul ile noktali virgul art arda ise
					// ikinci elemanin bos oldugu atanir.
					if (semicolonIndex- commaIndex == 1)
					{
						element2[i] = "";
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
							element2[i] = "";
						}
						else
						{
							element2[i] = temp.substr(found,semicolonIndex-found);
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
					element1[i] = temp.substr(0,found);
					element2[i] = "";
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
				AllLines[i] = AllLines[i].substr(initialOfCommand,lineSize);
			else
				AllLines[i] = AllLines[i].substr(initialOfCommand,firstSpaceAfterCommand-initialOfCommand);
			
			if (commands[i].substr(0,3) == "HLT")
			{
				element1[i] = "";
				element2[i] = "";
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
					element1[i] = temp.substr(0,found);
					
					// eger virgulden hemen sonra satir sonu var ise
					// ikinci elemanin bos oldugu atanir.
					if (lineSize- commaIndex == 1)
					{
						element2[i] = "";
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
							element2[i] = "";
						}
						else{
							element2[i] = temp.substr(found,lineSize-found);
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
					element1[i] = temp.substr(0,found);
					element2[i] = "";
				}
			}
		}
		i++;
	}
}