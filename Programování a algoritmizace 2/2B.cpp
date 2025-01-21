#ifndef __PROGTEST__
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cstdio>

#endif /* __PROGTEST__ */

using namespace std;

struct Record
{
    string name;
    string addr;
    Record * theirRelations[30];
    int sizeOfRelations;
    int numberOfRelations;

    Record(const string & name, const string & addr);
};

Record::Record(const string & name, const string & addr){
    this->name=name;
    this->addr=addr;
    numberOfRelations=0;
    sizeOfRelations=50;
    
}
class CIterator
 {
   public:

    bool           AtEnd          ( void ) const;
    void           Next           ( void );
    const string & Name           ( void ) const;
    const string & Address        ( void ) const;
    // todo
    CIterator(int indexMax);
    ~CIterator();
    friend class CCompanyIndex;

    Record **finalReturn;
    int actualIndex;
    int indexMax;
    };

 CIterator::CIterator(int indexMax)
{
    actualIndex = 0;
    this->indexMax = indexMax;
    finalReturn = new Record*[indexMax];
} 

CIterator::~CIterator()
{
    for (int i = 0; i < indexMax; i++)
    {
        delete finalReturn[i];
    }
    delete [] finalReturn;
}

 bool CIterator::AtEnd() const{
    if(actualIndex==indexMax)
    {
        return true;
    }
    else
    {
        return false;
    }
 }

 void CIterator::Next(){
    actualIndex++;
 }

 const string & CIterator::Name () const{
    return finalReturn[actualIndex]->name;
 }

 const string & CIterator::Address () const{
    return finalReturn[actualIndex]->addr;
 }


class CCompanyIndex
 {
public:
                             CCompanyIndex ( void );
                            ~CCompanyIndex ( void );
    bool         Add              ( const string & oName,
                                    const string & oAddr,
                                    const string & cName,
                                    const string & cAddr );
    bool         Del              ( const string & oName,
                                    const string & oAddr,
                                    const string & cName,
                                    const string & cAddr );
                                                
    CIterator  * SearchOwner      ( const string & oName,
                                    const string & oAddr ) const;

    CIterator  * SearchCompany    ( const string & cName,
                                    const string & cAddr ) const;
    // todo

private:
    Record ** owners;
    Record ** companies;
    int sizeOwners;
    int numberOfOwners;
    int sizeCompanies;
    int numberOfCompanies;
     
    bool FindRecord(const string & name, const string & addr, int & indexFound, int & positionToInsert, Record ** array, const int & numberOfRecords) const;
 };

CCompanyIndex::CCompanyIndex()
{
    numberOfOwners = 0;
    numberOfCompanies = 0;
    sizeOwners = 1000;
    sizeCompanies = 1000;
    owners = new Record *[sizeOwners];
    companies = new Record *[sizeCompanies];
    
}

CCompanyIndex::~CCompanyIndex()
{
    for (int i = 0; i < numberOfCompanies; i++)
    {
        delete companies[i];
    }

    delete [] companies;

    for (int i = 0; i < numberOfOwners; i++)
    {
        delete owners[i];
    }

    delete [] owners;
}


bool CCompanyIndex::FindRecord(const string & name, const string & addr, int & indexFound, int & positionToInsert, Record ** array, const int & numberOfRecords) const {
    int leftIndex = 0, rightIndex = numberOfRecords - 1;

    while(leftIndex <= rightIndex){
        int pivot = (leftIndex + rightIndex) / 2;

        int compareName = name.compare(array[pivot]->name); 

        if(compareName < 0){
            rightIndex = pivot - 1;
        } else if(compareName > 0){
            leftIndex = pivot + 1;
        } else {
            
            int compareAddress = addr.compare(array[pivot]->addr);

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
    int ownerIndexFound, ownerPositionToInsert, companyIndexFound, companyPositionToInsert, cIndexFound, cPositionToInsert, oIndexFound, oPositionToInsert;
    
    //realokace
    if (numberOfOwners + 2 > sizeOwners){
        Record **tmp = new Record *[sizeOwners*2];
        for (int i = 0; i < numberOfOwners; i++){
            tmp[i] = owners[i];
        }

        delete [] owners;
        sizeOwners*=2;
        this->owners = tmp;
    }

    if (numberOfCompanies + 2 > sizeCompanies){
        Record **tmp = new Record *[sizeCompanies*2];
        for (int i = 0; i < numberOfCompanies; i++){
            tmp[i] = companies[i];
        }

        delete [] companies;
        sizeCompanies*=2;
        this->companies = tmp;
    }

    //hleda vlastnika
    if(FindRecord(oName, oAddr, ownerIndexFound, ownerPositionToInsert, owners, numberOfOwners)){
        //ownerIndexFound=pozice zaznamu -> kouknu do jeho pole, jestli uz tam je zadana firma...

        if(FindRecord(cName, cAddr, cIndexFound, cPositionToInsert, owners[ownerIndexFound]->theirRelations, owners[ownerIndexFound]->numberOfRelations)){
            //...je tam, takze jde o duplikat=> vracim false
            return false;
        }
        else if(FindRecord(cName, cAddr, companyIndexFound, companyPositionToInsert, companies, numberOfCompanies)){
            //...je uz zadana s jinym majitelem, companyIndexFound=pozice firmy v poli -> priradim firmu k majiteli, firme priradim jeho

            for(int i = owners[ownerIndexFound]->numberOfRelations + 1; i>cPositionToInsert; i--)
            {
                owners[ownerIndexFound]->theirRelations[i]=owners[ownerIndexFound]->theirRelations[i-1];
            } 
            owners[ownerIndexFound]->theirRelations[cPositionToInsert] = companies[companyIndexFound];
            owners[ownerIndexFound]->numberOfRelations+=1;
            //prip. realokace
            FindRecord(oName, oAddr, oIndexFound, oPositionToInsert, companies[companyIndexFound]->theirRelations, companies[companyIndexFound]->numberOfRelations);
            for(int i = companies[companyIndexFound]->numberOfRelations + 1; i>oPositionToInsert; i--)
            {
                companies[companyIndexFound]->theirRelations[i]=companies[companyIndexFound]->theirRelations[i-1];
            } 
            companies[companyIndexFound]->theirRelations[oPositionToInsert] = owners[ownerIndexFound];
            companies[companyIndexFound]->numberOfRelations+=1;
            cout << "lezu do 1) if 2) else if" << endl;
            return true;
        }
        else
        {
            //...neni tam, takze zadany vlastnik je v databazi, ale neni tam tato firma, companyPositionToInsert=pozici pro vlozeni firmy=> vytvarim novou firmu do jeho pole firem tedy pridavam zadanou firmu
           
            for(int i = numberOfCompanies + 1; i>companyPositionToInsert; i--)
            {
                companies[i]=companies[i-1];
            } 
            companies[companyPositionToInsert] = new Record(cName, cAddr);
            numberOfCompanies+=1;
            companies[companyPositionToInsert]->theirRelations[0] = owners[ownerIndexFound];
            companies[companyPositionToInsert]->numberOfRelations+=1;
            
            for(int i = owners[ownerIndexFound]->numberOfRelations + 1; i>cPositionToInsert; i--)
            {
                owners[ownerIndexFound]->theirRelations[i]=owners[ownerIndexFound]->theirRelations[i-1];
            } 
            owners[ownerIndexFound]->theirRelations[cPositionToInsert] = companies[companyPositionToInsert];
            owners[ownerIndexFound]->numberOfRelations+=1;
            cout << "lezu do if else" << endl;
            return true;
        }
    }
    else
    {
        //ownerPositionToInsert=misto, kam budu vkladat 
         for(int i = numberOfOwners + 1; i>ownerPositionToInsert; i--)
            {
                owners[i]=owners[i-1];
            } 
            owners[ownerPositionToInsert] = new Record(oName, oAddr);
            numberOfOwners+=1;
        
        if(FindRecord(cName, cAddr, companyIndexFound, companyPositionToInsert, companies, numberOfCompanies))
        {
            //...firma jiz je v databazi, companyIndexFound=pozice firmy -> prirazuju vlastnikovi firmu, firme prirazuji vlastnika
            owners[ownerPositionToInsert]->theirRelations[0] = companies[companyIndexFound];
            owners[ownerPositionToInsert]->numberOfRelations+=1;

            FindRecord(oName, oAddr, oIndexFound, oPositionToInsert, companies[companyIndexFound]->theirRelations, companies[companyIndexFound]->numberOfRelations);
            for(int i = companies[companyIndexFound]->numberOfRelations + 1; i>oPositionToInsert; i--)
            {
                companies[companyIndexFound]->theirRelations[i]=companies[companyIndexFound]->theirRelations[i-1];
            } 
            companies[companyIndexFound]->theirRelations[oPositionToInsert] = owners[ownerPositionToInsert];
            companies[companyIndexFound]->numberOfRelations+=1;
            cout << "lezu do else if" << endl;
            return true;
        }
        else
        {
            //...firma neni v databazi, companyPositionToInsert=pozice, kam vlozim novou firmu, te priradim na zacatek vlastnika, vlastnikovi priradim na zacatek firmu
            for(int i = numberOfCompanies + 1; i>companyPositionToInsert; i--)
            {
                companies[i]=companies[i-1];
            } 
            companies[companyPositionToInsert] = new Record(cName, cAddr);
            numberOfCompanies+=1;

            companies[companyPositionToInsert]->theirRelations[0] = owners[ownerPositionToInsert];
            companies[companyPositionToInsert]->numberOfRelations+=1;

            owners[ownerPositionToInsert]->theirRelations[0] = companies[companyPositionToInsert];
            owners[ownerPositionToInsert]->numberOfRelations+=1;
            cout << "lezu do else else" << endl;
            return true;
        }
    }
    cout << "nelezu nikam" << endl;
return true;
}

bool CCompanyIndex::Del(const string & oName, const string & oAddr, const string & cName, const string & cAddr )
{
    int ownerIndexFound, ownerPositionToInsert, companyIndexFound, companyPositionToInsert, cIndexFound, cPositionToInsert, oIndexFound, oPositionToInsert;

//mazu z vlastniku
    if(FindRecord(oName, oAddr, ownerIndexFound, ownerPositionToInsert, owners, numberOfOwners)){
        if(FindRecord(cName, cAddr, cIndexFound, cPositionToInsert, owners[ownerIndexFound]->theirRelations, owners[ownerIndexFound]->numberOfRelations))
        {
            
                //delete owners[ownerIndexFound]->theirRelations[cIndexFound];
                owners[ownerIndexFound]->numberOfRelations--;  

                for(int i=cIndexFound; i<=owners[ownerIndexFound]->numberOfRelations; i++)
                {
                owners[ownerIndexFound]->theirRelations[i] = owners[ownerIndexFound]->theirRelations[i+1];
                }
        }
        else
        {
            return false;
        }
    }else{
        return false;
    }

//mazu z firem

    if(FindRecord(cName, cAddr, companyIndexFound, companyPositionToInsert, companies, numberOfCompanies))
    {
        if(FindRecord(oName, oAddr, oIndexFound, oPositionToInsert, companies[companyIndexFound]->theirRelations, companies[companyIndexFound]->numberOfRelations))
        {
            
                //delete companies[companyIndexFound]->theirRelations[oIndexFound];
                companies[companyIndexFound]->numberOfRelations--;

                for(int i=oIndexFound; i<=companies[companyIndexFound]->numberOfRelations; i++)
                {
                companies[companyIndexFound]->theirRelations[i] = companies[companyIndexFound]->theirRelations[i+1];
                }
        }
        else
        {
            return false;
        }
    }else{
        return false;
    }
    if(owners[ownerIndexFound]->numberOfRelations==0)
            {
                delete owners[ownerIndexFound];
                numberOfOwners--;
                for (int i = ownerIndexFound; i <= numberOfOwners; i++)
                {
                    owners[i]=owners[i+1];
                }
            }
    if(companies[companyIndexFound]->numberOfRelations==0)
            {
                delete companies[companyIndexFound];
                numberOfCompanies--;
                for (int i = companyIndexFound; i <= numberOfCompanies; i++)
                {
                    companies[i]=companies[i+1];
                }
            }
return true;
}

CIterator* CCompanyIndex::SearchOwner( const string & oName, const string & oAddr ) const{ 

    int ownerIndexFound, ownerPositionToInsert;

    if(FindRecord(oName, oAddr, ownerIndexFound, ownerPositionToInsert, owners, numberOfOwners)){

        CIterator* pointerArray = new CIterator(owners[ownerIndexFound]->numberOfRelations);
            for(int i = 0; i < owners[ownerIndexFound]->numberOfRelations; i++) {

                pointerArray->finalReturn[i] = new Record(owners[ownerIndexFound]->theirRelations[i]->name, owners[ownerIndexFound]->theirRelations[i]->addr);
            }
            return pointerArray;
    }
    else
    {
        return NULL;
    }
    return NULL;    
}

CIterator* CCompanyIndex::SearchCompany( const string & cName, const string & cAddr ) const{

    int companyIndexFound, companyPositionToInsert;

    if(FindRecord(cName, cAddr, companyIndexFound, companyPositionToInsert, companies, numberOfCompanies)){

        CIterator* pointerArray = new CIterator(companies[companyIndexFound]->numberOfRelations);
            for(int i = 0; i < companies[companyIndexFound]->numberOfRelations; i++) {

                pointerArray->finalReturn[i] = new Record(companies[companyIndexFound]->theirRelations[i]->name, companies[companyIndexFound]->theirRelations[i]->addr);
            }
            return pointerArray;
    }
    else
    {
        return NULL;
    }
    return NULL;   
}

#ifndef __PROGTEST__
void  showResults ( CIterator * it )
 {
   while ( ! it -> AtEnd () )
    {
      cout << it -> Name () << ",  " << it -> Address () << endl;
      it -> Next ();
    }
 }

 int main( int argc, char * argv [] ){

CIterator * it;
bool        status;
CCompanyIndex  b1;
status = b1 . Add ( "Smith", "Oak road", "ACME, Ltd.", "One ACME road" );
// status = true
cout << "1. " << status << endl;

status = b1 . Add ( "Brown", "Second street", "ACME, Ltd.", "Mountain road" );
// status = true
cout << "2. " << status << endl;

status = b1 . Add ( "Hacker", "5-th avenue", "Forks and Knives, Ltd.", "Cutlery avenue" );
// status = true
cout << "3. " << status << endl;

status = b1 . Add ( "Hacker", "7-th avenue", "Child toys, Inc.", "Red light district" );
// status = true
cout << "4. " << status << endl;

status = b1 . Add ( "Smith", "Oak road", "ACME, Ltd.", "Mountain road" );
// status = true
cout << "5. " << status << endl;

status = b1 . Add ( "Hacker", "5-th avenue", "ACME, Ltd.", "One ACME road" );
// status = true
cout << "6. " << status << endl;

status = b1 . Add ( "Hacker", "7-th avenue", "ACME, Ltd.", "Mountain road" );
// status = true
cout << "7. " << status << endl;

it = b1 . SearchOwner ( "Brown", "Second street" );
showResults ( it );
/*
----8<----8<----8<----8<----
ACME, Ltd., Mountain road
----8<----8<----8<----8<----
*/
delete it;

it = b1 . SearchOwner ( "Hacker", "Oak road" );
// it = NULL
cout << "8. " << it << endl;

it = b1 . SearchOwner ( "Hacker", "7-th avenue" );
showResults ( it );
/*
----8<----8<----8<----8<----
Child toys, Inc., Red light district
ACME, Ltd., Mountain road
----8<----8<----8<----8<----
*/
delete it;
it = b1 . SearchCompany ( "ACME, Ltd.", "Mountain road" );
showResults ( it );
/*
----8<----8<----8<----8<----
Hacker, 7-th avenue
Brown, Second street
Smith, Oak road
----8<----8<----8<----8<----
*/
delete it;
it = b1 . SearchCompany ( "Child toys, Inc.", "Mountain road" );
// it = NULL
cout << "9. " << it << endl;

status = b1 . Del ( "Smith", "Oak road", "Child toys, Inc.", "Red light district" );
// status = false
cout << "10. " << status << endl;

status = b1 . Del ( "Smith", "Oak road", "ACME, Ltd.", "Mountain road" );
// status = true
cout << "11. " << status << endl;

it = b1 . SearchOwner ( "Smith", "Oak road" );
showResults ( it );
/*
----8<----8<----8<----8<----
ACME, Ltd., One ACME road
----8<----8<----8<----8<----
*/
delete it;
status = b1 . Add ( "Smith", "Oak road", "ACME, Ltd.", "One ACME road" );
// status = false
cout << "12. " << status << endl;


    return 0;
 }
 #endif /* __PROGTEST__ */
