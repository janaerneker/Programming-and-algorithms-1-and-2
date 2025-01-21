#ifndef  __PROGTEST__ 
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <stdint.h>

using namespace std;

#endif /* __PROGTEST__ */

bool BINtoCSV ( const char * inFileName, const char * outFileName )
{
   	ifstream inf(inFileName, ifstream::binary);
 	if(!inf)
 	{
 		return false;
 	}
 
 	char headerChar, tmpCharacter;
 	int tmpInt=0, sizeOfContent=0, numberOfRows=0, numberOfCells=0, sizeOfRow=0, numberOfCharacters=0;
 	int positionRows=0, positionCells=0, positionCharacters=0, rowSize=0;
 	
 	inf.read(&headerChar, 1);
 	if(headerChar!='H')
 	{
 		inf.close();
 		return false;
 	}
 	headerChar='\0';
 	inf.read((char*) &sizeOfContent, 4);
 	inf.read((char*) &numberOfRows, 4);
 	inf.read((char*) &numberOfCells, 4);
 	int actualPosition=inf.tellg();
 	inf.seekg (0,inf.end);
 	int sizeOfFile=inf.tellg();
 	//cout << "file: " << sizeOfFile << endl;
 	//cout << "content: " << sizeOfContent << endl;
 	if(sizeOfContent!=sizeOfFile-13){
 		inf.close();	
 		return false;
 	}
 	inf.seekg (actualPosition);
 	//cout << "velikost: " << sizeOfContent << endl;
 	//cout << "pocet zaznamu: " << numberOfRows << endl;
 	//cout << "pocet bunek v jednom zaznamu: " << numberOfCells << endl;

 	ofstream onf(outFileName);
	if(!onf)
	{
		return false;
	}
 	//radky
 	while(positionRows!=numberOfRows)
 	{

 		inf.read(&headerChar, 1);
 		if(headerChar!='R')
 		{
 			inf.close();
 			onf.close();
 			return false;
 		}
 		headerChar='\0';
		inf.read((char*) &sizeOfRow, 4);
		
		//bunky
		while(positionCells!=numberOfCells)
		{
			positionCells++;
			inf.read(&headerChar, 1);
			rowSize++;

			if(headerChar=='I' && positionCells!=numberOfCells)
			{
				inf.read((char*) &tmpInt, 4);
				rowSize+=4;
				onf << tmpInt << ";";
				tmpInt=0;

			}
			else if(headerChar=='I')
			{

				inf.read((char*) &tmpInt, 4);
				rowSize+=4;
				onf << tmpInt;
				tmpInt=0;

			}
			else if(headerChar=='S')
			{
				inf.read((char*) &numberOfCharacters, 4);	
				rowSize+=4;
				
				//znaky
				while(positionCharacters!=numberOfCharacters)
				{
					inf.read(&tmpCharacter, 1);
					rowSize++;
					onf << tmpCharacter;
					tmpCharacter='\0';
					positionCharacters++;
				}
				
				if(positionCells!=numberOfCells)
				{
					onf << ";";
				}
				positionCharacters=0;
				numberOfCharacters=0;
			}
			else
			{
 				inf.close();
 				onf.close();
 				return false;
 			}

 			headerChar='\0';
		}
		if(rowSize!=sizeOfRow)
		{
			inf.close();
 			onf.close();
 			return false;
		}
		rowSize=0;
		positionCells=0;
 		onf << endl;
 		sizeOfRow=0;
 		positionRows++;
	}
	inf.close();
	onf.close();
	if (onf.fail() ) return false;
   return true;
}

bool CSVtoBIN ( const char * inFileName, const char * outFileName )
{
 	ifstream inf(inFileName);
 	if(!inf){
 		return false;
 	}
 	int cell=0, flag=0, isDig=0, nonDig=0, non=0;
 	int32_t sizeOfContent=0, numberOfRows=0, numberOfCells=0, sizeOfRow=0;
 	string tmpLine, tmpBlock;
 	stringstream tmpStream, tmpBlockStream;
 	char tmpCharacter;
 	ofstream onf(outFileName, ofstream::binary);
 	if(!onf){
 		return false;
 	}
 	//prazdna hlavicka
 	onf.write("H", 1);
 	onf.write((char*) &sizeOfContent, 4);
 	onf.write((char*) &numberOfRows, 4);
 	onf.write((char*) &numberOfCells, 4);
	
	//radek
	while(getline(inf,tmpLine))
 	{
 		tmpStream << tmpLine;
 		//hlavicka zaznamu prazdna
 		onf.write("R", 1);
 		sizeOfContent++;
 		int32_t positionHeaderOfRow=onf.tellp();
 		//cout << "pozice hlavicky zaznamu: " << positionHeaderOfRow << endl;
 		onf.write((char*) &sizeOfRow, 4);
 		sizeOfContent+=4;
 		numberOfRows++;
 		
 		//bunka
 		while(getline(tmpStream, tmpBlock,';')){
 			tmpBlockStream << tmpBlock;
 			
 			//znak
 			while(tmpBlockStream.get(tmpCharacter)){
 				if(isdigit(tmpCharacter)==0 && tmpCharacter!='-'){
 					nonDig++;
 					//cout << "nonDigit: " << nonDig << endl;
 				}else if(tmpCharacter=='-' && nonDig!=0 && isDig!=0){
 					nonDig++;
 				}else{
 					isDig++;
 					//cout << "isDig: " << isDig << endl;	
 				}
 			}
 			tmpBlockStream.clear();
 			if(nonDig==0 && isDig==0){
 				non++; 
 				onf.write("S", 1);
 				sizeOfContent++;
 				sizeOfRow++;
 				int32_t tmpInt = 0;
 				onf.write((char*) &tmpInt, 4);
 				sizeOfContent+=4;
 				sizeOfRow+=4;
 				onf.write(tmpBlock.data(), tmpBlock.size());
 				sizeOfContent+=0;
 				sizeOfRow+=0;
 			}else if(nonDig==0){
 				onf.write("I", 1);
 				sizeOfContent++;
 				sizeOfRow++;
 				int32_t tmpInt = atoi(tmpBlock.c_str());
 				onf.write((char*) &tmpInt, 4);
 				sizeOfContent+=4;
 				sizeOfRow+=4;
 				tmpInt=0;
 			}else{
 				onf.write("S", 1);
 				sizeOfContent++;
 				sizeOfRow++;
 				int32_t tmpInt = tmpBlock.size();
 				onf.write((char*) &tmpInt, 4);
 				sizeOfContent+=4;
 				sizeOfRow+=4;
 				onf.write(tmpBlock.data(), tmpBlock.size());
 				sizeOfContent+=tmpBlock.size();
 				sizeOfRow+=tmpBlock.size();
 				tmpInt=0;
 			}
 			nonDig=0;
 			isDig=0;
 			//cout << "obsah slozky: " << tmpBlock << endl; 
 			cell++; 
 		}
 		flag++;
 		if(flag==1){
 			numberOfCells=cell;
 		}
 		//cout << "pocet bunek: " <<numberOfCells << endl;
 		if(cell!=numberOfCells && non!=numberOfCells-1){
 			inf.close();
 			onf.close();
 			return false;
 		}else if(non==numberOfCells-1){
 			onf.write("S", 1);
 				sizeOfContent++;
 				sizeOfRow++;
 				int32_t tmpInt = 0;
 				onf.write((char*) &tmpInt, 4);
 				sizeOfContent+=4;
 				sizeOfRow+=4;
 				onf.write(tmpBlock.data(), tmpBlock.size());
 				sizeOfContent+=0;
 				sizeOfRow+=0;
 		}
 		//skutecna hlavicka zaznamu
 		int actualPosition=onf.tellp();
 		onf.seekp(positionHeaderOfRow);
 		onf.write((char*) &sizeOfRow, 4);
 		sizeOfRow=0;
 		onf.seekp(actualPosition);
 		positionHeaderOfRow=0;
 		
 		cell=0;
 		tmpStream.clear();
 	}
 	//skutecna hlavicka souboru
 	onf.seekp(1);
 	//cout << "velikost obsahu: " << sizeOfContent << endl;
 	//cout << "pocet radku: " << numberOfRows << endl;
 	//cout << "pocet bunek: " << numberOfCells << endl;
 	onf.write((char*) &sizeOfContent, 4);
 	onf.write((char*) &numberOfRows, 4);
 	onf.write((char*) &numberOfCells, 4);

 	inf.close();
	onf.close();
	if (onf.fail() ) return false;
   	return true;
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
 {
   cout << "0" << endl;
   if(CSVtoBIN ( "in_0.csv", "out_0.bin" )==false) cout << "chyba0" << endl;
   cout << "1" << endl;
   if(CSVtoBIN ( "in_1.csv", "out_1.bin" )==false) cout << "chyba1" << endl;
   cout << "2" << endl;
   if(CSVtoBIN ( "in_2.csv", "out_2.bin" )==false) cout << "chyba2" << endl;
   cout << "3" << endl;
   if(CSVtoBIN ( "in_3.csv", "out_3.bin" )==false) cout << "chyba3" << endl;
   cout << "4" << endl;
   if(BINtoCSV("in_Nespravny_vstup_(bin)_01.bin", "out_6.csv")==false) cout << "chyba4" << endl;
   cout << "5" << endl;
   if(BINtoCSV("in_5.bin", "out_5.csv")==false) cout << "chyba5" << endl;
   return 0;
 }
#endif /* __PROGTEST__ */
