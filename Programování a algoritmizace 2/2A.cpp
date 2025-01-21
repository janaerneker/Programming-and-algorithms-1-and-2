#ifndef __PROGTEST__
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cstdio>

using namespace std;

#endif /* __PROGTEST__ */

struct Line
{

    string name;
    string address;
    string companyName;
    string companyAddress;

    Line(const string & name, const string & address, const string & companyName, const string & companyAddress);
};


Line::Line(const string & name, const string & address, const string & companyName, const string & companyAddress)
{
    this->name=name;
    this->address=address;
    this->companyName=companyName;
    this->companyAddress=companyAddress;
}



class CCompanyIndex
 {
public:
                             CCompanyIndex ( void );
                            ~CCompanyIndex ( void );
    bool                     Add           ( const string & oName,
                                             const string & oAddr,
                                             const string & cName,
                                             const string & cAddr );
    bool                     Del           ( const string & oName,
                                             const string & oAddr );
    bool                     Search        ( const string & oName,
                                             const string & oAddr,
                                             string       & cName,
                                             string       & cAddr ) const;
    // todo
private:
    Line ** array;
    int companiesCount;
    int arraySize;

    bool FindLine(const string & oName, const string & oAddr, int & index, int & position) const; 
 };

CCompanyIndex::CCompanyIndex()
{
    companiesCount = 0;
    arraySize = 1000;
    array = new Line*[arraySize];
    
}

CCompanyIndex::~CCompanyIndex()
{
    for (int i = 0; i < companiesCount; i++)
    {
        delete array[i];
    }

    delete [] array;
}


bool CCompanyIndex::FindLine(const string & oName, const string & oAddr, int & indexFound, int & positionToInsert) const {
    int leftIndex = 0, rightIndex = companiesCount - 1;

    while(leftIndex <= rightIndex){
        int pivot = (leftIndex + rightIndex) / 2;

        int compareName = oName.compare(array[pivot]->name); 

        if(compareName < 0){
            rightIndex = pivot - 1;
        } else if(compareName > 0){
            leftIndex = pivot + 1;
        } else {
            
            int compareAddress = oAddr.compare(array[pivot]->address);

            if(compareAddress < 0){
                rightIndex = pivot - 1;
            } else if(compareAddress > 0){
                leftIndex = pivot + 1;
            } else {
                indexFound = pivot;
                return true;
            }
        }

    }
    positionToInsert = leftIndex;
    return false;
}

bool CCompanyIndex::Add(const string & oName, const string & oAddr, const string & cName, const string & cAddr)
{
    int indexFound, positionToInsert;
    
    //realokace
    if (companiesCount + 2 > arraySize){
        Line **tmp = new Line *[arraySize*2];
        for (int i = 0; i < companiesCount; i++){
            tmp[i] = array[i];
        }

        delete [] array;
        arraySize*=2;
        this->array = tmp;
    }

    //duplikat
    if(FindLine(oName, oAddr, indexFound, positionToInsert)){
        return false;
    }

    //posunuti pole o 1
    for(int i = companiesCount+1; i>positionToInsert; i--)
    {
        array[i]=array[i-1];
    } 
    this->array[positionToInsert] = new Line(oName, oAddr, cName, cAddr);
companiesCount++;

cout << "companiesCount: " << companiesCount << endl;

return true;
}

bool CCompanyIndex::Del(const string & oName, const string & oAddr)
{
    int indexFound, positionToInsert;

    if(FindLine(oName, oAddr, indexFound, positionToInsert)){
        delete array[indexFound];
        for(int i=indexFound; i<=companiesCount; i++){
            array[i]= array[i+1];
        }
        companiesCount--;

        cout << "companiesCount: " << companiesCount << endl;
        
        return true;
    }else{
        return false;
    }

return true;
}

bool CCompanyIndex::Search(const string & oName, const string & oAddr, string & cName, string & cAddr) const
{
    int indexFound, positionToInsert; 

    if(FindLine(oName, oAddr, indexFound, positionToInsert)){
        cName = array[indexFound]->companyName;
        cAddr = array[indexFound]->companyAddress;

        return true;
    } else {
        return false;
    }

return true;
}



 #ifndef __PROGTEST__
 int main( int argc, char * argv [] ){

/*bool   status;
string cName, cAddress;
CCompanyIndex  b1;

status = b1 . Add ( "Smith", "Oak road", "ACME, Ltd.", "One ACME road" );
// status = true
cout << status << endl;

status = b1 . Add ( "Brown", "Second street", "MakroHard, Inc.", "Soft street" );
// status = true
cout << status << endl;

status = b1 . Add ( "Hacker", "5-th avenue", "Forks and Knives, Ltd.", "Cutlery avenue" );
// status = true
cout << status << endl;

status = b1 . Add ( "Hacker", "7-th avenue", "Child toys, Inc.", "Red light district" );
// status = true
cout << status << endl;

status = b1 . Search ( "Brown", "Second street", cName, cAddress );
// status = true, cName = "MakroHard, Inc.", cAddress="Soft street"
cout << status << endl;
cout << "cName: " << cName << endl;
cout << "cAddress: " << cAddress << endl;

status = b1 . Search ( "Hacker", "Oak road", cName, cAddress );
// status = false
cout << status << endl;

status = b1 . Search ( "Smith", "Oak road", cName, cAddress );
// status = true, cName = "ACME, Ltd.", cAddress="One ACME road"
cout << status << endl;
cout << "cName: " << cName << endl;
cout << "cAddress: " << cAddress << endl;

status = b1 . Del ( "Smith", "Oak road" );
//status = true
cout << status << endl;

status = b1 . Search ( "Smith", "Oak road", cName, cAddress );
// status = false
cout << status << endl;

CCompanyIndex  b2;
status = b2 . Add ( "Smith", "Michigan avenue", "ACME, Ltd.", "One ACME road" );
// status = true
cout << status << endl;

status = b2 . Search ( "Smith", "Michigan avenue", cName, cAddress );
// status = true, cName = "ACME, Ltd.", cAddress="One ACME road"
cout << status << endl;

status = b2 . Del ( "Smith", "Michigan avenue" );
// status = true
cout << status << endl;

status = b2 . Search ( "Smith", "Michigan avenue", cName, cAddress );
// status = false
cout << status << endl;


status = b2 . Del ( "Smith", "Michigan avenue" );
// status = false
cout << status << endl;

status = b2 . Add ( "Smith", "Michigan avenue", "Forks and Knives, Ltd.", "Cutlery avenue" );
// status = true
cout << status << endl;

status = b2 . Search ( "Smith", "Michigan avenue", cName, cAddress );
// status = true, cName = "Forks and Knives, Ltd.", cAddress="Cutlery avenue"
cout << status << endl;
cout << "cName: " << cName << endl;
cout << "cAddress: " << cAddress << endl;

status = b2 . Add ( "Smith", "Michigan avenue", "Child toys, Inc.", "Red light district" );
// status = false
cout << status << endl;

status = b2 . Add ( "Smith", "Michigan avenue", "MakroHard, Inc.", "Soft street" );
// status = false
cout << status << endl;

status = b2 . Del ( "Smith", "Michigan avenue" );
// status = true
cout << status << endl;

status = b2 . Search ( "Smith", "Michigan avenue", cName, cAddress );
// status = false
cout << status << endl;*/

    return 0;
 }
 #endif /* __PROGTEST__ */
