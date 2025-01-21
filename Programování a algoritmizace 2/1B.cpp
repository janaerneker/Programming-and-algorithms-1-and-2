#ifndef __PROGTEST__
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

#endif /* __PROGTEST__ */

struct Student
{
public:
	string name;
	int grade1;
	int grade2;
	
	Student(string name, int grade1, int grade2);
	friend ostream& operator<<(ostream& stream, Student a);
	bool operator<(const Student& a) const
	{
        return name < a.name;
    }

};

Student::Student(string name="", int grade1=0, int grade2=0)
{
	this->name=name;
	this->grade1=grade1;
	this->grade2=grade2;
}

ostream& operator<<(ostream& stream, Student a){
	return stream << a.name << " " << a.grade1 << " " << a.grade2 << endl;
}

bool joinFiles  ( const char * inFile1,
                  const char * inFile2,
                  const char * outFile )
{	
 	ifstream inf1(inFile1);
 	ifstream inf2(inFile2);
 	
	if(!inf1 || !inf2){
 		return false;
 	}

 	unsigned int i = 0;
 	string tmpLine, tmpName, tmpRest;
 	int tmpGrade=-1;
 	stringstream tmp;
 	vector<Student> file1;
 	vector<Student> file2;

 	while(getline(inf1, tmpLine))
 	{
 		
 		if(tmpLine.length()==0){
 			continue;
 		}
 		tmp << tmpLine;
 		
 		tmp >> tmpName >> tmpGrade >> tmpRest;
 		
 		if(tmpRest.length()>0 || (tmpGrade<0 && tmpName!="") || (tmpName=="" && tmpGrade!=0))
 		{
			inf1.close();
 			return false;
 		}
 		
 		for (unsigned int j = 0; j < (file1.size()); j++)
 		{
 			if(tmpName==file1[j].name){
 				return false;
 			}
 		}
 		
 		file1.push_back(Student());
 		
 		file1[i].name=tmpName;
 		file1[i].grade1=tmpGrade;
 		
 		i++;
 		tmpName="";
 		tmpGrade=-1;
 		tmpRest="";
 		tmpLine="";
 		tmp.clear();
 	}
 		inf1.close();

i=0;

	while(getline(inf2, tmpLine))
 		{
 		
 		if(tmpLine.length()==0){
 			continue;
 		}
 		tmp << tmpLine;
 		
 		tmp >> tmpName >> tmpGrade >> tmpRest;
 		
 		if(tmpRest.length()>0 || (tmpGrade<0 && tmpName!="") || (tmpName=="" && tmpGrade!=0))
 		{
			inf2.close();
 			return false;
 		}
 		
 		for(unsigned int j = 0; j < (file2.size()); j++)
 		{
 			if(tmpName==file2[j].name){
 				return false;
 			}
 		}
 		
 		file2.push_back(Student());
 		
 		file2[i].name=tmpName;
 		file2[i].grade2=tmpGrade;
 		
 		i++;
 		tmpName="";
 		tmpGrade=-1;
 		tmpRest="";
 		tmpLine="";
 		tmp.clear();
 		}
 		inf2.close();
 		
i=0;

int vektor1 = file1.size();
int pozice = file1.size();
int flag=0;

for (unsigned int i = 0; i < (file2.size()); i++)
{
	
	for (int j = 0; j < vektor1; j++)
	{
	
	if(file1[j].name==file2[i].name)
	{
		file1[j].grade2=file2[i].grade2;
		flag=1;
	} 
	}

	if(flag==0){
		file1.push_back(Student());
		file1[pozice].name=file2[i].name;
 		file1[pozice].grade2=file2[i].grade2;
 		pozice++;
		}	
	flag=0;		
}

sort(file1.begin(), file1.end());

ofstream onf(outFile);
if(!onf){
	return false;
}

for (unsigned int i = 0; i < (file1.size()); i++)
{
	onf << file1[i];
}
	
 	return true;
}

#ifndef __PROGTEST__
int main( int argc, char * argv [] )
{

  if( joinFiles( "A", "B", "c.txt" ) == false ) cout << "chyba6" << endl;
	
	return 0;
}
#endif /* __PROGTEST__ */