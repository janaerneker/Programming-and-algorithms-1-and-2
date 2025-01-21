#ifndef __PROGTEST__
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
 
using namespace std;
  
#endif /* __PROGTEST__ */
  
struct MyString
{
    MyString ();
    MyString ( const char * c );
    ~MyString ();
    MyString & operator=( const MyString & myStr );
    MyString & operator=( const char * c );
    // int CompareString( const char * x ) const;
    int CompareString( const MyString & myStr ) const;
  
     char           *       content;
     int                    length;
};
  
MyString::MyString()
 {
    this->content = NULL;
    this->length = 0;
 }
  
MyString::MyString( const char * c )
 {
    length = strlen(c);
    content = new char[length+1];
  
    /*for (int i = 0; i < length; i++)
    {
        content[i]=c[i];
    }*/
    memcpy(content, c, sizeof(char) * length);
    content[length] = 0;
 }
  
MyString::~MyString()
 {
    if(content != NULL)
     {
        delete [] content;
        content = NULL;
        length = 0;
     }
 }
  
MyString & MyString::operator= ( const MyString & myStr )
 {
    if(&myStr == this)
    {
        return *this;
    }
  
    if(content != NULL)
     {
        delete [] content;
        content = NULL;
        length = 0;
     }
  
    if(myStr.length > 0)
     {
        length = myStr.length;
        content = new char[length+1];
  
        /*for (int i = 0; i < length+1; i++)
        {
            content[i]=myStr.content[i];
        }*/
        memcpy(content, myStr.content, sizeof(char) * (length + 1) );
     }
  
    return *this;
 }
  
MyString & MyString::operator= ( const char * c )
 {
    if(content != NULL)
     {
        delete [] content;
        content = NULL;
        length = 0;
     }
  
    length = strlen(c);
    content = new char[length+1];
  
    /*for (int i = 0; i < length; i++)
    {
        content[i]=c[i];
    }*/
    memcpy(content, c, sizeof(char) * length);
    content[length] = 0;
  
    return *this;
 }
  
int MyString::CompareString ( const MyString & myStr ) const
 {
    int n = strcmp ( content, myStr.content );
    return n;
 }
  
//-----------------------------------------------------------------------------------------------------
  
struct Content
{  
    Content();
    ~Content();
    bool FindString ( const char * c, int & indexFound, int & positionToInsert ) const;
    MyString * AddString ( const char * c );
  
    MyString ** data;
    int countOfString;
    int sizeOfData;
};
  
Content::Content()
{
    data = NULL;
    countOfString = 0;
    sizeOfData=0;
}
  
Content::~Content()
{
    for (int i = 0; i < countOfString; ++i)
    {
        delete data[i];
    }
  
    delete [] data;
  
    countOfString = 0;
    data = NULL;
}
  
bool Content::FindString ( const char * c, int & indexFound, int & positionToInsert ) const
{
    int leftIndex = 0, rightIndex = countOfString - 1;
  
//binary search
    while(leftIndex <= rightIndex)
    {
        // cout << "leftIndex: " << leftIndex << endl;
        // cout << "rightIndex: " << leftIndex << endl;
 
        int pivot = (leftIndex + rightIndex) / 2;
  
        int cmp = (*data[pivot]).CompareString(c);
  
        if(cmp > 0)
        {
            rightIndex = pivot - 1;
        }
        else if(cmp < 0)
        {
            leftIndex = pivot + 1;
        }
        else
        {
            indexFound = pivot;
            return true;
        }
        
  
    }
    positionToInsert = leftIndex;
    return false;
}
  
MyString * Content::AddString ( const char * c )
{
  int indexFound, positionToInsert;
  
    //jestli uz tam je -> nepotrebuju vkladat
    
    if(FindString(c, indexFound, positionToInsert))
    {
        return data[indexFound];
    }
    //neni tam, kontroluju velikost pole
    else
    {
        if (data==NULL)
        {
            //zacatek
            sizeOfData = 500;
            data = new MyString * [sizeOfData];
            positionToInsert=0;
        }
        else
        {
            if(sizeOfData == countOfString)
            {
                MyString **tmp = new MyString *[sizeOfData*2];
 
                if(positionToInsert != 0)
                {
                    memcpy(tmp, data, sizeof(MyString*) * positionToInsert);
                }
 
                if(positionToInsert != sizeOfData)
                {
                    memcpy(tmp+positionToInsert+1, data+positionToInsert, sizeof(MyString*) * (countOfString - positionToInsert));
                }
 
                delete [] data;
                data = tmp;
                sizeOfData*= 2;
            }
            else if(positionToInsert != countOfString)
            {
                MyString ** tmp = new MyString * [countOfString- positionToInsert ];
 
                memcpy(tmp, data+positionToInsert, sizeof(MyString*) * (countOfString-positionToInsert));
                memcpy(data+positionToInsert+1, tmp, sizeof(MyString*) * (countOfString-positionToInsert));
 
                delete [] tmp;
            }
        }
        /*else if(countOfString+2>sizeOfData)
        {
            //realokace
            MyString **tmp = new MyString *[sizeOfData*2];
            for (int i = 0; i < countOfString; i++)
            {
                tmp[i] = data[i];
            }
  
            delete [] data;
            sizeOfData*=2;
            this->data = tmp;
        }
  
        for(int i = countOfString+1; i>positionToInsert; i--)
        {
            data[i]=data[i-1];
        }*/
  
        MyString * tmpString = new MyString(c);
        data[positionToInsert] = tmpString;
        countOfString++;
  
        return data[positionToInsert];
    }
}
  
//-----------------------------------------------------------------------------------------------------
  
struct Domicile
{
    Domicile( const MyString  * date, const MyString  * street, const MyString * city );
  
    const MyString   * date;
    const MyString   * street;
    const MyString   * city;
};
  
Domicile::Domicile( const MyString  * date, const MyString  * street, const MyString * city )
: date(date), street(street), city(city) {}
  
  
//-----------------------------------------------------------------------------------------------------
  
struct Inhabitant
{
    Inhabitant(const MyString * id,
            const MyString * name,
            const MyString * surname);
    ~Inhabitant();
    bool FindDomicile ( const MyString & c, int & indexFound, int & positionToInsert ) const;
    bool AddDomicile ( Domicile * & dom );
    
  
    const MyString * id;
    const MyString * name;
    const MyString * surname;
  
    Domicile ** domiciles;
    int countOfDomiciles;
};
  
Inhabitant::Inhabitant(const MyString * id,
                    const MyString * name,
                    const MyString * surname): id(id), name(name), surname(surname)
{
    domiciles = NULL;
    countOfDomiciles = 0;
}
  
Inhabitant::~Inhabitant()
{
    for (int i = 0; i < countOfDomiciles; i++)
    {
        delete domiciles[i];
    }
  
    delete[] domiciles;
}
  
bool Inhabitant::FindDomicile ( const MyString & c, int & indexFound, int & positionToInsert ) const
{
    int leftIndex = 0, rightIndex = countOfDomiciles - 1;
  
//binary search
    while(leftIndex <= rightIndex)
    {
 
        // cout << "leftIndex: " << leftIndex << endl;
        // cout << "rightIndex: " << leftIndex << endl;
 
        int pivot = (leftIndex + rightIndex) / 2;
  
        int cmp = (*domiciles[pivot]->date).CompareString(c);
  
        if(cmp > 0)
        {
            rightIndex = pivot - 1;
        }
        else if(cmp < 0)
        {
            leftIndex = pivot + 1;
        }
        else
        {
            indexFound = pivot;
            return true;
        }
        
  
    }
    positionToInsert = leftIndex;
    return false;
}
  
bool Inhabitant::AddDomicile ( Domicile * & dom )
{
    int indexFound, positionToInsert;
  
  
    if (countOfDomiciles==0)
    {
        //zacatek
        domiciles = new Domicile * [1];    
        domiciles[0] = dom;
        countOfDomiciles++;
        return true;
    }
    else
    {
        if(FindDomicile(*(dom->date), indexFound, positionToInsert))
        {
            return false;
        }
        else
        {
            //jinak vlozim novyho
            //rozsiruju o 1
 
            Domicile ** tmp = new Domicile * [countOfDomiciles + 1];
 
            if(positionToInsert != 0)
            {
                memcpy(tmp, domiciles, sizeof(Domicile*) * positionToInsert);
            }
 
            if(positionToInsert != countOfDomiciles)
            {
                memcpy(tmp+positionToInsert+1, domiciles+positionToInsert, sizeof(Domicile*) * (countOfDomiciles - positionToInsert));
            }
 
            delete [] domiciles;
            domiciles = tmp;    
 
            /*Domicile ** tmp = new Domicile * [countOfDomiciles + 1];
            for (int i = 0; i < positionToInsert; i++)
            {
                tmp[i]=domiciles[i];
            }
  
            tmp[positionToInsert] = dom;
  
            for(int i = positionToInsert; i<countOfDomiciles; i++)
            {
                tmp[i+1]=domiciles[i];
            }
  
                delete [] domiciles;
                domiciles = tmp; */      
        }
    }
     
    domiciles[positionToInsert] = dom;
    countOfDomiciles++;
    return true;
}
  
//-----------------------------------------------------------------------------------------------------
  
struct Register
{
    Register();
    ~Register();
    bool FindID(const MyString & c, int & indexFound, int & positionToInsert)const;
    bool AddInhabitant( Inhabitant * & inh );
    friend class CRegister;
    
    Inhabitant ** inhabitants;
    int countOfInhabitants;
    int countOfShared;
};
  
Register::Register()
{
    inhabitants=NULL;
    countOfInhabitants=0;
    countOfShared=0;
}
  
Register::~Register()
{
    for (int i = 0; i < countOfInhabitants; i++)
    {
        delete inhabitants[i];
    }
  
    delete [] inhabitants;
}
  
bool Register::FindID(const MyString & c, int & indexFound, int & positionToInsert)const
{
    int leftIndex = 0, rightIndex = countOfInhabitants - 1, pivot, cmp;
    
    //binary search
    while(leftIndex <= rightIndex)
    {  
        // cout << "leftIndex: " << leftIndex << endl;
        // cout << "rightIndex: " << leftIndex << endl;
        pivot = (leftIndex + rightIndex) / 2;
  
    
        cmp = (*inhabitants[pivot]->id).CompareString(c);
        if(cmp > 0)
        {
            rightIndex = pivot - 1;
        }
        else if(cmp < 0)
        {
            leftIndex = pivot + 1;
        }
        else
        {
            indexFound = pivot;
            return true;
        }
    }
    positionToInsert = leftIndex;
    return false;
}
  
bool Register::AddInhabitant( Inhabitant * & inh )
{
    int indexFound, positionToInsert;
  
    if (countOfInhabitants==0)
    {
        //zacatek
        inhabitants = new Inhabitant * [1];
        inhabitants[0] = inh;
        countOfInhabitants++;
        return true;
    }
    else
    {
        if(FindID(*(inh->id), indexFound, positionToInsert))
        {
            //je-li uz clovek s timto ID v databazi -> return false
            return false;
        }
        else
        {
            //jinak vlozim novyho
         
 
            Inhabitant ** tmp = new Inhabitant*[countOfInhabitants+1];
 
            if(positionToInsert!= 0)
            {
                memcpy(tmp, inhabitants, sizeof(Inhabitant*) * positionToInsert);
            }
            if(positionToInsert != countOfInhabitants)
            {
                memcpy(tmp+positionToInsert+1, inhabitants+positionToInsert, sizeof(Inhabitant*) * (countOfInhabitants - positionToInsert));
            }
            delete [] inhabitants;
            inhabitants = tmp;  
 
 
 
            /*Inhabitant ** tmp = new Inhabitant*[countOfInhabitants+1];
            for (int i = 0; i < positionToInsert; i++)
            {
                tmp[i]=inhabitants[i];
            }
        
            tmp[positionToInsert] = inh;
  
            for(int i = positionToInsert; i<countOfInhabitants; i++)
            {  
                tmp[i+1]=inhabitants[i];
            }
  
                delete [] inhabitants;
                inhabitants = tmp;*/ 
        }
    }
     
    inhabitants[positionToInsert] = inh;
    countOfInhabitants++;
    /*for (int i = 0; i < countOfInhabitants; i++)
    {
        cout << "i: " << i << " " << inhabitants[i]->id->content << endl;
    }*/
  
    return true;
}
  
//-----------------------------------------------------------------------------------------------------
  
class CRegister    
 {
   public:
    // default constructor
    CRegister ();
    // copy constructor
    CRegister ( const CRegister & reg );
    // destructor
    ~CRegister ();
    // operator =
    CRegister & operator=( const CRegister & reg );
                        
                        
    
  
    bool                     Add                           ( const char      * id,
                                                             const char      * name,
                                                             const char      * surname,
                                                             const char      * date,
                                                             const char      * street,
                                                             const char      * city );
    bool                     Resettle                      ( const char      * id,
                                                             const char      * date,
                                                             const char      * street,
                                                             const char      * city );
    bool                     Print                         ( ostream         & os,
                                                             const char      * id ) const;
  
    friend struct MyString;
    friend struct Content;
    friend struct Domicile;
    friend struct Inhabitant;
    friend struct Register;
   private:
  
    Content * ids;
    Content * vocabulary;
    Content * dates;
  
    Register ** registers;
    int countOfRegisters;
    int * countOfReference;
 };
  
//vytvori prazdnou instanci registru
CRegister::CRegister ()
{  
    this->ids=NULL;
    this->vocabulary=NULL;
    this->dates=NULL;
  
    this->registers=NULL;
    countOfRegisters=0;
    countOfReference = new int(0);
}
  
//vytvori hlubokou kopii registru
CRegister::CRegister ( const CRegister & reg )
{
    //je-li prazdnej -> pouze vytvori prazdnej
    if(reg.countOfRegisters==0)
    {
        this->ids=NULL;
        this->vocabulary=NULL;
        this->dates=NULL;
  
        this->registers=NULL;
        countOfRegisters=0;
        countOfReference = new int(0);
  
    }
    //neni-li prazdnej -> zkopiruje registr a zvysi pocet sdileni o 1
    else
    {
        this->ids = reg.ids;
        this->vocabulary=reg.vocabulary;
        this->dates=reg.dates;
  
        registers = new Register * [reg.countOfRegisters];
 
        /*for (int i = 0; i < reg.countOfRegisters; i++)
        {
            registers[i]=reg.registers[i];
        }*/
        memcpy(registers, reg.registers, sizeof(Register*) * reg.countOfRegisters);
        countOfRegisters = reg.countOfRegisters;
  
        countOfReference = reg.countOfReference;
        (*countOfReference)++;
  
        for (int i = 0; i < countOfRegisters; i++)
        {
            registers[i] -> countOfShared++;
        }
  
    }
}
  
//uvolni prostredky alokovane instanci
CRegister::~CRegister ()
{
    //je-li sdilenej -> pouze snizim pocet sdileni
    if((*countOfReference) != 0)
     {
        (*countOfReference)--;
     }
    //neni-li sdilenej -> muzu smazat
    else
     {
        delete ids;
        delete vocabulary;
        delete dates;
        delete countOfReference;
     }
  
     for (int i = 0; i < countOfRegisters; i++)
     {
        //je-li sdilenej -> snizim pocet sdileni o 1
        if(registers[i]->countOfShared!=0)
         {
            registers[i]->countOfShared--;
         }
        else
         {
            //neni sdilenej -> smazu
            delete registers[i];
         }
     }
  
    delete[] registers;
}
  
//hluboka kopie jedne instance do druhe
CRegister & CRegister::operator=( const CRegister & reg )
{
    //smazu puvodni obsah
  
    //je-li sdilenej -> pouze snizim pocet sdileni
    if((*countOfReference) != 0)
     {
        (*countOfReference)--;
     }
    //neni-li sdilenej -> muzu smazat
    else
     {
        delete ids;
        delete vocabulary;
        delete dates;
        delete countOfReference;
     }
  
     for (int i = 0; i < countOfRegisters; i++)
     {
        //je-li sdilenej -> snizim pocet sdileni o 1
        if(registers[i]->countOfShared!=0)
         {
            registers[i]->countOfShared--;
         }
         //neni-li sdilenej -> smazu
        else
         {
            delete registers[i];
         }
     }
  
    delete[] registers;
  
    //zkopiruju registr
  
    //je-li prazdnej -> pouze vytvori prazdnej
    if(reg.countOfRegisters==0)
    {
        this->ids=NULL;
        this->vocabulary=NULL;
        this->dates=NULL;
  
        this->registers=NULL;
        countOfRegisters=0;
        countOfReference = new int(0);
  
    }
    //neni-li prazdnej -> zkopiruje registr
    else
    {
        this->ids = reg.ids;
        this->vocabulary=reg.vocabulary;
        this->dates=reg.dates;
  
        registers = new Register * [reg.countOfRegisters];
        /*for (int i = 0; i < reg.countOfRegisters; i++)
        {
            registers[i]=reg.registers[i];
        }*/
        memcpy(registers, reg.registers, sizeof(Register*) * reg.countOfRegisters);
        countOfRegisters = reg.countOfRegisters;
  
        countOfReference = reg.countOfReference;
        (*countOfReference)++;
  
        for (int i = 0; i < countOfRegisters; i++)
        {
            registers[i] -> countOfShared++;
        }
    }
  
    return *this;
}
  
bool CRegister::Add( const char     * id,
                    const char      * name,
                    const char      * surname,
                    const char      * date,
                    const char      * street,
                    const char      * city )
{
    int indexFound, positionToInsert, freeRegisterIndex;
    MyString tmpString;
    tmpString = id;
    //koukam se, jestli to neni prvni zadana osoba do registru - jestli neni prazdny
    if (countOfRegisters==0)
    {
        //prazdny registr -> vytvorim novej
        ids = new Content();
        vocabulary = new Content();
        dates = new Content();    
  
        Register ** tmpReg = new Register * [1];
        delete [] registers;
        registers = tmpReg;
  
        registers[0] = new Register();
        countOfRegisters++;
  
        freeRegisterIndex=0;
    }
    else
    {
        //neni prazdny -> musim najit nesdileny registr a v kazdem z aktualnich registru hledat, jestli tam toto ID jiz neni
        bool freeRegister=false;
  
        // cout << countOfRegisters << endl;   
        for (int i = 0; i < countOfRegisters; i++)
        {  
           if(registers[i]->FindID(tmpString, indexFound, positionToInsert))
           {
                return false;
           }
  
           if(registers[i] -> countOfShared==0)
             {
                freeRegister = true;
                freeRegisterIndex = i;
                break;
             }
        }
 
             //nenajdu-li nesdileny registr -> vytvorim novej
            if(freeRegister==false)
            {
                Register ** tmpReg = new Register * [countOfRegisters+1];
  
                if(countOfRegisters != 0)
                {
                    memcpy(tmpReg, registers, sizeof(Register *) * countOfRegisters);
                    // for (int i = 0; i < countOfRegisters; i++)
                    // {
                    //     tmpReg[i]=registers[i];
                    // }
                }
  
                delete [] registers;
                registers = tmpReg;
  
                registers[countOfRegisters] = new Register();
                countOfRegisters++;    
                freeRegisterIndex = countOfRegisters-1;            
            }
    }
  
    //vkladam zaznam
  
    Domicile * tmpDom = new Domicile( dates->AddString(date), vocabulary->AddString(street), vocabulary->AddString(city) );
    Inhabitant * tmpInh = new Inhabitant( ids->AddString(id), vocabulary->AddString(name), vocabulary->AddString(surname) );
    tmpInh->AddDomicile(tmpDom);    
  
    registers[freeRegisterIndex]->AddInhabitant(tmpInh);
  
    return true;
}
  
 bool CRegister::Resettle( const char      * id,
                           const char      * date,
                           const char      * street,
                           const char      * city )
 {
    int indexFound, positionToInsert, indexFoundDate, positionToInsertDate, positionOfInh, positionOfRegistr, flag=0, unsharedIndex;
    //hledam cloveka
    MyString tmpString;
    tmpString = id;
 
    Inhabitant *tmpInh;
 
    for (int i = 0; i < countOfRegisters; i++)
    {
        
        if(registers[i] -> FindID(tmpString, indexFound, positionToInsert))
        {
            flag=1;
            positionOfRegistr=i;
            positionOfInh=indexFound;
            // break;
 
            tmpInh = registers[positionOfRegistr]->inhabitants[positionOfInh];
 
        
                if(tmpInh->FindDomicile(date, indexFoundDate, positionToInsertDate))
                {
                    //tento den se jiz prestehoval
                    return false;
                }
                else
                {
                    //muzu vkladat
                    flag=1;
                }
    
        }
    }
 
  
    if(flag==0)
    {
        return false;
    }
    flag=0;
  
    //budu vkladat
    Domicile * tmpDom = new Domicile( dates->AddString(date), vocabulary->AddString(street), vocabulary->AddString(city) );
  
    //zjistuju, jestli je registr sdileny
    if(registers[positionOfRegistr]->countOfShared!=0)
    {
        //registr je sdileny, musim osobu ulozit do jinyho registru
    
  
        //hledam nesdileny registr
        for (int i = 0; i < countOfRegisters; i++)
        {
            if(registers[i]->countOfShared==0)
            {
                //nasel nesdileny registr
                flag=1;
                unsharedIndex=i;
            }
        }
  
    }
    else
    {
        //registr neni sdileny -> muzu vkladat
        tmpInh->AddDomicile(tmpDom);
        return true;
    }
  
    //budu muset vkladat novou osobu
    Inhabitant * tmpInhab = new Inhabitant( registers[positionOfRegistr]->inhabitants[positionOfInh]->id, registers[positionOfRegistr]->inhabitants[positionOfInh]->name, registers[positionOfRegistr]->inhabitants[positionOfInh]->surname );
    tmpInhab->AddDomicile(tmpDom);
  
  
    if (flag==0)
    {
        //registr je sdileny a nemam zadny nesdileny -> musim vytvorit novy
        Register ** tmpReg = new Register * [countOfRegisters+1];
  
        if(countOfRegisters != 0)
        {
            memcpy(tmpReg, registers, sizeof(Register *) * countOfRegisters);
            // for (int i = 0; i < countOfRegisters; i++)
            // {
            //     tmpReg[i]=registers[i];
            // }
        }
  
        delete [] registers;
        registers = tmpReg;
        registers[countOfRegisters] = new Register();
        countOfRegisters++;
        unsharedIndex=countOfRegisters-1;
    }
  
    registers[unsharedIndex]->AddInhabitant(tmpInhab);
  
    //cout << "---------------" << endl;
    return true;
 }
  
bool CRegister::Print( ostream & os, const char * id ) const
{
    int indexFound, positionToInsert, flag=0;
    int IDIndexFound[100], IDRegisterIndex[100];
    int records=0;
    
        //hledam cloveka, kteremu patri id
        for (int i = 0; i < countOfRegisters; i++)
        {
            if(registers[i]->FindID(id, indexFound, positionToInsert))
            {
                IDIndexFound[records]=indexFound;
                IDRegisterIndex[records]=i;
                records++;
                flag=1;
            }
        }
        //clovek nenalezen
        if(flag==0)
        {
            return false;
        }
Inhabitant * tmpInh = new Inhabitant (registers[IDRegisterIndex[0]]->inhabitants[IDIndexFound[0]]->id, registers[IDRegisterIndex[0]]->inhabitants[IDIndexFound[0]]->name, registers[IDRegisterIndex[0]]->inhabitants[IDIndexFound[0]]->surname);
        

        //osobni udaje
        os << registers[IDRegisterIndex[0]]->inhabitants[IDIndexFound[0]]->id->content << " "
            << registers[IDRegisterIndex[0]]->inhabitants[IDIndexFound[0]]->name->content << " "
            << registers[IDRegisterIndex[0]]->inhabitants[IDIndexFound[0]]->surname->content << endl;
    
         
        //bydliste
            for (int i = 0; i < records; i++)
            {
                for (int j = 0; j < registers[IDRegisterIndex[i]]->inhabitants[IDIndexFound[i]]->countOfDomiciles; j++)
                {
                    Domicile * tmpDom = new Domicile( registers[IDRegisterIndex[i]]->inhabitants[IDIndexFound[i]]->domiciles[j]->date, registers[IDRegisterIndex[i]]->inhabitants[IDIndexFound[i]]->domiciles[j]->street, registers[IDRegisterIndex[i]]->inhabitants[IDIndexFound[i]]->domiciles[j]->city);
                    tmpInh->AddDomicile(tmpDom);
                }   
            }

            for (int i = 0; i < tmpInh->countOfDomiciles; i++)
            {
                 os << tmpInh->domiciles[i]->date->content << " "
                       << tmpInh->domiciles[i]->street->content << " "
                       << tmpInh->domiciles[i]->city->content << " " << endl;
            }
      

    delete tmpInh;
    return true;
}
  
//-----------------------------------------------------------------------------------------------------
  
#ifndef __PROGTEST__
 
int main ( int argc, char * argv [] )
 {
    
  
   return 0;
 }
#endif /* __PROGTEST__ */