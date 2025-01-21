#ifndef __PROGTEST__
#include <new>
#include <cstring>
#include <stdint.h>



#include <iostream>
#include <iomanip>
using namespace std;
#endif /* __PROGTEST__ */

class CDegChar
 {
   public:
    // default constructor
    CDegChar (void);
    // copy constructor 
    CDegChar (const CDegChar & cchar);
    // destructor
     ~CDegChar ();
    // operator =
     CDegChar & operator=(const CDegChar & cchar);
    // operator += 
     CDegChar & operator+=(uint16_t dchar);
    // operator -= 
     CDegChar & operator-=(uint16_t dchar);
    // operator ==
      bool operator==(const CDegChar & cchar) const;
    // operator []
       bool operator[](uint16_t dchar) const;
    // Size ()
       int Size () const;
    // FindDegChar()
       bool FindDegChar(const uint16_t & dchar, int & indexFound, int & positionToInsert) const;


   private:
    // todo
    uint16_t smallArray[6];
    uint16_t *array;
    int position;
    int countOfElements;
    int arraySize;
 };

 //--------------------------------------------------------------------------------------------------------
 //default constructor

 CDegChar::CDegChar()
 {
    this->position=0;
    this->countOfElements=0;
    this->arraySize=13;
    array = new uint16_t[arraySize];
    for (int i = 0; i < 6; i++)
    {
        smallArray[i]=0;
    }

 }

 //--------------------------------------------------------------------------------------------------------
 //copy constructor

 CDegChar::CDegChar(const CDegChar & cchar)
 {
    position=cchar.position;
    countOfElements=cchar.countOfElements;

    for (int i = 0; i < 6; ++i)
    {
        smallArray[i]=cchar.smallArray[i];
    }
    array = new uint16_t[position];
    for (int i = 0; i < position; i++)
    {
        array[i]=cchar.array[i];
    }
 }

//--------------------------------------------------------------------------------------------------------
 //destructor

 CDegChar::~CDegChar ()
 {
    delete [] array;
 }



 //--------------------------------------------------------------------------------------------------------
 //operator =

 CDegChar & CDegChar::operator=(const CDegChar & cchar)
 {
    delete [] this->array;
    
    position=cchar.position;
    countOfElements=cchar.countOfElements;

    for (int i = 0; i < 6; ++i)
    {
        smallArray[i]=cchar.smallArray[i];
    }
    array = new uint16_t[position];
    for (int i = 0; i < position; i++)
    {
        array[i]=cchar.array[i];
    }

    return *this;
 }

 //--------------------------------------------------------------------------------------------------------
 //operator+=

 CDegChar & CDegChar::operator+=(uint16_t dchar)
 {
    int indexFound=0, positionToInsert=0;

    if(dchar>32 && dchar<127)
    {
        if( (smallArray[(dchar-32)/16] & 2<<((dchar-32)%16)) == 2<<((dchar-32)%16) )
        {
            return *this;
        }
        else
        {
            smallArray[(dchar-32)/16]=smallArray[(dchar-32)/16] | 2<<((dchar-32)%16);
            countOfElements++;
        }
    }
    else
    {
        if( FindDegChar(dchar, indexFound, positionToInsert) == true )
        {
            return *this;
        }
        else
        {
            //realokace
            if (position == arraySize)
            {
                uint16_t *tmp = new uint16_t[arraySize+1];
                for (int i = 0; i < position; i++)
                {
                    tmp[i] = array[i];
                }
                delete [] array;
                arraySize+=1;
                array = tmp;
            }

            
             for(int i = countOfElements; i>positionToInsert; i--)
            {
                array[i]=array[i-1];
            } 

            array[positionToInsert]=dchar;
            countOfElements++;
            position++;
        }
    }
    return *this;
 }

 //--------------------------------------------------------------------------------------------------------
 //operator-=

 CDegChar & CDegChar::operator-=(uint16_t dchar)
 {
    int indexFound=0, positionToInsert=0;

    if(dchar>32 && dchar<127)
    {
        if( (smallArray[(dchar-32)/16] & 2<<((dchar-32)%16)) != 2<<((dchar-32)%16) )
        {
            return *this;
        }
        else
        {
            smallArray[(dchar-32)/16]=smallArray[(dchar-32)/16] & ~(2<<((dchar-32)%16));
            countOfElements--;
        }
        
    }
    else
    {
        if( FindDegChar(dchar, indexFound, positionToInsert) == false )
        {
            return *this;
        }
        else
        {
            
            countOfElements--;
            position--;

            for(int i=indexFound; i<=countOfElements; i++)
            {
                array[i]= array[i+1];
            }
        }
    }
    return *this;
 }
 //--------------------------------------------------------------------------------------------------------
 //operator==

 bool CDegChar::operator==(const CDegChar & cchar) const
 {

    if(countOfElements==cchar.countOfElements && position==cchar.position)
    {
        for (int i = 0; i < 6; i++)
        {
            if (smallArray[i]!=cchar.smallArray[i])
            {
                return false;
            }
        }
        for (int i = 0; i < position; i++)
        {
            if (array[i]!=cchar.array[i])
            {
                return false;
            }
        }
        return true;
    }
    else
    {
        return false;
    }
    return true;
 }

 //--------------------------------------------------------------------------------------------------------
 //operator[]

 bool CDegChar::operator[](uint16_t dchar) const
 {
    int indexFound=0, positionToInsert=0;

    if(dchar>32 && dchar<127)
    {
        if( (smallArray[(dchar-32)/16] & 2<<((dchar-32)%16)) == 2<<((dchar-32)%16))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        if( FindDegChar(dchar, indexFound, positionToInsert) == true )
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    return true;
 }

 //--------------------------------------------------------------------------------------------------------
 //Size()

 int CDegChar::Size () const
 {
    return this->countOfElements;
 }

//--------------------------------------------------------------------------------------------------------
//Find()

bool CDegChar::FindDegChar(const uint16_t & dchar, int & indexFound, int & positionToInsert) const
{
    int leftIndex = 0, rightIndex = position - 1;

    while(leftIndex <= rightIndex)
    {
        int pivot = (leftIndex + rightIndex) / 2; 

        if(dchar < this->array[pivot])
        {
            rightIndex = pivot - 1;
        } 
        else if(dchar > this->array[pivot])
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

 #ifndef __PROGTEST__
int main ( int argc, char * argv [] )
 {
    bool status;
int size;
 
CDegChar char0, char1, char2, char3, char4, char5, char6, char7, char8, char9;
CDegChar char10, char11, char12, char13, char14, char15, char16, char17, char18, char19;
CDegChar char20, char21, char22, char23, char24, char25, char26, char27, char28, char29;
CDegChar char30, char31, char32, char33, char34, char35, char36, char37, char38, char39;
CDegChar char40, char41, char42, char43, char44, char45, char46, char47, char48, char49;
CDegChar char50, char51, char52, char53, char54, char55, char56, char57, char58, char59;
CDegChar char60, char61, char62, char63, char64, char65, char66, char67, char68, char69;
CDegChar char70, char71, char72, char73, char74, char75, char76, char77, char78, char79;
CDegChar char80, char81, char82, char83, char84, char85, char86, char87, char88, char89;
CDegChar char90, char91, char92, char93, char94, char95, char96, char97, char98, char99;
 
//test 0
char72 -= 14782;
size = char72.Size();
cout << "test 0 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 1
char85 = char66;
status = char85 == char66;
cout << "test 1 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 2
char31 += 62690;
size = char31.Size();
cout << "test 2 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 3
char50 -= 27528;
size = char50.Size();
cout << "test 3 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 4
char59 = char21;
status = char59 == char21;
cout << "test 4 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 5
CDegChar char100 = char82;
status = char100 == char82;
cout << "test 5 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 6
status = char3[62136];
cout << "test 6 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 7
char79 += 3030;
size = char79.Size();
cout << "test 7 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 8
status = char62 == char84;
cout << "test 8 - out: " << status << " - ref: 1 - match: " << (status == true) << endl;
 
//test 9
char17 += 30266;
size = char17.Size();
cout << "test 9 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 10
char39 -= 32448;
size = char39.Size();
cout << "test 10 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 11
char85 -= 60798;
size = char85.Size();
cout << "test 11 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 12
char89 += 49620;
size = char89.Size();
cout << "test 12 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 13
char50 += 2722;
size = char50.Size();
cout << "test 13 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 14
status = char26[52296];
cout << "test 14 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 15
char29 += 40614;
size = char29.Size();
cout << "test 15 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 16
char50 = char39;
status = char50 == char39;
cout << "test 16 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 17
char10 -= 62090;
size = char10.Size();
cout << "test 17 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 18
char69 -= 9040;
size = char69.Size();
cout << "test 18 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 19
status = char79 == char2;
cout << "test 19 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 20
char25 = char76;
status = char25 == char76;
cout << "test 20 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 21
status = char40[54770];
cout << "test 21 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 22
char20 -= 19416;
size = char20.Size();
cout << "test 22 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 23
char48 += 36726;
size = char48.Size();
cout << "test 23 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 24
CDegChar char101 = char41;
status = char101 == char41;
cout << "test 24 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 25
char40 += 36104;
size = char40.Size();
cout << "test 25 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 26
status = char87[58982];
cout << "test 26 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 27
CDegChar char102 = char56;
status = char102 == char56;
cout << "test 27 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 28
char12 = char78;
status = char12 == char78;
cout << "test 28 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 29
char101 += 11094;
size = char101.Size();
cout << "test 29 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 30
char3 -= 7052;
size = char3.Size();
cout << "test 30 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 31
char78 -= 39354;
size = char78.Size();
cout << "test 31 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 32
char51 = char61;
status = char51 == char61;
cout << "test 32 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 33
char72 = char98;
status = char72 == char98;
cout << "test 33 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 34
char8 -= 3924;
size = char8.Size();
cout << "test 34 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 35
status = char51[54818];
cout << "test 35 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 36
char93 -= 44488;
size = char93.Size();
cout << "test 36 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 37
status = char31 == char5;
cout << "test 37 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 38
status = char100[14492];
cout << "test 38 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 39
char1 += 58890;
size = char1.Size();
cout << "test 39 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 40
char38 -= 19664;
size = char38.Size();
cout << "test 40 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 41
status = char47 == char38;
cout << "test 41 - out: " << status << " - ref: 1 - match: " << (status == true) << endl;
 
//test 42
status = char52[40804];
cout << "test 42 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 43
char73 -= 29042;
size = char73.Size();
cout << "test 43 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 44
char42 += 15704;
size = char42.Size();
cout << "test 44 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 45
char31 += 20214;
size = char31.Size();
cout << "test 45 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 46
char97 -= 52140;
size = char97.Size();
cout << "test 46 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 47
char51 = char64;
status = char51 == char64;
cout << "test 47 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 48
CDegChar char103 = char7;
status = char103 == char7;
cout << "test 48 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 49
char80 -= 45916;
size = char80.Size();
cout << "test 49 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 50
CDegChar char104 = char80;
status = char104 == char80;
cout << "test 50 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 51
status = char72 == char83;
cout << "test 51 - out: " << status << " - ref: 1 - match: " << (status == true) << endl;
 
//test 52
char99 = char92;
status = char99 == char92;
cout << "test 52 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 53
char89 -= 15674;
size = char89.Size();
cout << "test 53 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 54
char12 = char20;
status = char12 == char20;
cout << "test 54 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 55
CDegChar char105 = char6;
status = char105 == char6;
cout << "test 55 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 56
status = char51 == char3;
cout << "test 56 - out: " << status << " - ref: 1 - match: " << (status == true) << endl;
 
//test 57
status = char91[18416];
cout << "test 57 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 58
CDegChar char106 = char13;
status = char106 == char13;
cout << "test 58 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 59
CDegChar char107 = char45;
status = char107 == char45;
cout << "test 59 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 60
status = char88 == char107;
cout << "test 60 - out: " << status << " - ref: 1 - match: " << (status == true) << endl;
 
//test 61
CDegChar char108 = char102;
status = char108 == char102;
cout << "test 61 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 62
char60 += 20088;
size = char60.Size();
cout << "test 62 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 63
char38 -= 60054;
size = char38.Size();
cout << "test 63 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 64
char104 -= 21452;
size = char104.Size();
cout << "test 64 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 65
char23 += 24314;
size = char23.Size();
cout << "test 65 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 66
char107 -= 3712;
size = char107.Size();
cout << "test 66 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 67
char60 = char61;
status = char60 == char61;
cout << "test 67 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 68
char74 -= 54164;
size = char74.Size();
cout << "test 68 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 69
status = char60[38754];
cout << "test 69 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 70
char75 += 20488;
size = char75.Size();
cout << "test 70 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 71
status = char97 == char84;
cout << "test 71 - out: " << status << " - ref: 1 - match: " << (status == true) << endl;
 
//test 72
char54 -= 51420;
size = char54.Size();
cout << "test 72 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 73
status = char101[58186];
cout << "test 73 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 74
status = char76[23312];
cout << "test 74 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 75
char2 = char48;
status = char2 == char48;
cout << "test 75 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 76
char22 += 15268;
size = char22.Size();
cout << "test 76 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 77
char80 += 60082;
size = char80.Size();
cout << "test 77 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 78
char58 -= 63384;
size = char58.Size();
cout << "test 78 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 79
char11 = char108;
status = char11 == char108;
cout << "test 79 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 80
status = char7[46060];
cout << "test 80 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 81
status = char97[54682];
cout << "test 81 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 82
char26 += 28064;
size = char26.Size();
cout << "test 82 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 83
char87 += 20958;
size = char87.Size();
cout << "test 83 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 84
char95 += 14772;
size = char95.Size();
cout << "test 84 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 85
char86 = char32;
status = char86 == char32;
cout << "test 85 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 86
char38 -= 34088;
size = char38.Size();
cout << "test 86 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 87
status = char28[54534];
cout << "test 87 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 88
char98 = char36;
status = char98 == char36;
cout << "test 88 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 89
char37 -= 30186;
size = char37.Size();
cout << "test 89 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 90
char95 += 34352;
size = char95.Size();
cout << "test 90 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 91
CDegChar char109 = char14;
status = char109 == char14;
cout << "test 91 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 92
status = char47[42842];
cout << "test 92 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 93
status = char5[47712];
cout << "test 93 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 94
char107 += 38302;
size = char107.Size();
cout << "test 94 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 95
char24 -= 8308;
size = char24.Size();
cout << "test 95 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 96
char59 += 29122;
size = char59.Size();
cout << "test 96 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 97
char101 -= 13800;
size = char101.Size();
cout << "test 97 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 98
status = char1[52422];
cout << "test 98 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 99
char98 += 32700;
size = char98.Size();
cout << "test 99 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 100
char4 -= 44970;
size = char4.Size();
cout << "test 100 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 101
char106 -= 23280;
size = char106.Size();
cout << "test 101 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 102
status = char24[56174];
cout << "test 102 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 103
char35 += 15492;
size = char35.Size();
cout << "test 103 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 104
char39 += 2322;
size = char39.Size();
cout << "test 104 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 105
char79 -= 61816;
size = char79.Size();
cout << "test 105 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 106
char82 += 10646;
size = char82.Size();
cout << "test 106 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 107
char86 -= 57036;
size = char86.Size();
cout << "test 107 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 108
char43 += 42490;
size = char43.Size();
cout << "test 108 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 109
char24 -= 16768;
size = char24.Size();
cout << "test 109 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 110
CDegChar char110 = char29;
status = char110 == char29;
cout << "test 110 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 111
CDegChar char111 = char69;
status = char111 == char69;
cout << "test 111 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 112
char88 += 36214;
size = char88.Size();
cout << "test 112 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 113
char62 = char110;
status = char62 == char110;
cout << "test 113 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 114
CDegChar char112 = char17;
status = char112 == char17;
cout << "test 114 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 115
status = char103 == char72;
cout << "test 115 - out: " << status << " - ref: 1 - match: " << (status == true) << endl;
 
//test 116
status = char51[29660];
cout << "test 116 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 117
CDegChar char113 = char83;
status = char113 == char83;
cout << "test 117 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 118
CDegChar char114 = char90;
status = char114 == char90;
cout << "test 118 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 119
char76 -= 23874;
size = char76.Size();
cout << "test 119 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 120
char22 = char82;
status = char22 == char82;
cout << "test 120 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 121
status = char17[23622];
cout << "test 121 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 122
char114 = char110;
status = char114 == char110;
cout << "test 122 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 123
status = char8[49962];
cout << "test 123 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 124
char31 -= 9328;
size = char31.Size();
cout << "test 124 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 125
char1 -= 21230;
size = char1.Size();
cout << "test 125 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 126
char23 += 47620;
size = char23.Size();
cout << "test 126 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 127
status = char91[50322];
cout << "test 127 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 128
char64 -= 33528;
size = char64.Size();
cout << "test 128 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 129
CDegChar char115 = char80;
status = char115 == char80;
cout << "test 129 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 130
status = char4[8962];
cout << "test 130 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 131
status = char103 == char61;
cout << "test 131 - out: " << status << " - ref: 1 - match: " << (status == true) << endl;
 
//test 132
CDegChar char116 = char62;
status = char116 == char62;
cout << "test 132 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 133
char111 = char102;
status = char111 == char102;
cout << "test 133 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 134
char29 += 856;
size = char29.Size();
cout << "test 134 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 135
char71 -= 19702;
size = char71.Size();
cout << "test 135 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 136
char11 -= 25004;
size = char11.Size();
cout << "test 136 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 137
char43 -= 44634;
size = char43.Size();
cout << "test 137 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 138
status = char4[44384];
cout << "test 138 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 139
CDegChar char117 = char52;
status = char117 == char52;
cout << "test 139 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 140
char46 += 32202;
size = char46.Size();
cout << "test 140 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 141
char56 += 38800;
size = char56.Size();
cout << "test 141 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 142
status = char92[14478];
cout << "test 142 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 143
status = char85 == char68;
cout << "test 143 - out: " << status << " - ref: 1 - match: " << (status == true) << endl;
 
//test 144
char49 -= 32050;
size = char49.Size();
cout << "test 144 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 145
char108 -= 35864;
size = char108.Size();
cout << "test 145 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 146
CDegChar char118 = char39;
status = char118 == char39;
cout << "test 146 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 147
char117 += 20386;
size = char117.Size();
cout << "test 147 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 148
char76 += 38216;
size = char76.Size();
cout << "test 148 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 149
char104 -= 48038;
size = char104.Size();
cout << "test 149 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 150
CDegChar char119 = char101;
status = char119 == char101;
cout << "test 150 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 151
CDegChar char120 = char106;
status = char120 == char106;
cout << "test 151 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 152
char70 = char31;
status = char70 == char31;
cout << "test 152 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 153
char49 -= 20098;
size = char49.Size();
cout << "test 153 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 154
char50 -= 18856;
size = char50.Size();
cout << "test 154 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 155
char112 += 50054;
size = char112.Size();
cout << "test 155 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 156
status = char55[62844];
cout << "test 156 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 157
char82 -= 61546;
size = char82.Size();
cout << "test 157 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 158
char4 -= 8880;
size = char4.Size();
cout << "test 158 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 159
char93 += 5678;
size = char93.Size();
cout << "test 159 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 160
status = char101[50756];
cout << "test 160 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 161
char62 += 28114;
size = char62.Size();
cout << "test 161 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 162
char14 -= 11576;
size = char14.Size();
cout << "test 162 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 163
char83 += 26710;
size = char83.Size();
cout << "test 163 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 164
char0 -= 15500;
size = char0.Size();
cout << "test 164 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 165
char98 += 61114;
size = char98.Size();
cout << "test 165 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 166
status = char83[45376];
cout << "test 166 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 167
char41 += 41470;
size = char41.Size();
cout << "test 167 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 168
char89 += 24660;
size = char89.Size();
cout << "test 168 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 169
char119 += 6946;
size = char119.Size();
cout << "test 169 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 170
status = char34 == char56;
cout << "test 170 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 171
char107 += 11046;
size = char107.Size();
cout << "test 171 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 172
status = char39 == char87;
cout << "test 172 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 173
char113 = char12;
status = char113 == char12;
cout << "test 173 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 174
char113 += 50640;
size = char113.Size();
cout << "test 174 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 175
char118 += 60366;
size = char118.Size();
cout << "test 175 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 176
status = char65 == char37;
cout << "test 176 - out: " << status << " - ref: 1 - match: " << (status == true) << endl;
 
//test 177
char8 += 38514;
size = char8.Size();
cout << "test 177 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 178
char20 -= 26200;
size = char20.Size();
cout << "test 178 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 179
CDegChar char121 = char92;
status = char121 == char92;
cout << "test 179 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 180
char36 -= 20706;
size = char36.Size();
cout << "test 180 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 181
char82 += 30600;
size = char82.Size();
cout << "test 181 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 182
CDegChar char122 = char86;
status = char122 == char86;
cout << "test 182 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 183
char85 -= 59730;
size = char85.Size();
cout << "test 183 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 184
char86 += 32440;
size = char86.Size();
cout << "test 184 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 185
status = char48[2006];
cout << "test 185 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 186
char112 = char0;
status = char112 == char0;
cout << "test 186 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 187
char111 += 37434;
size = char111.Size();
cout << "test 187 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 188
CDegChar char123 = char38;
status = char123 == char38;
cout << "test 188 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 189
char36 -= 21948;
size = char36.Size();
cout << "test 189 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 190
char20 += 64938;
size = char20.Size();
cout << "test 190 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 191
char22 -= 33008;
size = char22.Size();
cout << "test 191 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 192
char49 += 47470;
size = char49.Size();
cout << "test 192 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 193
char104 += 12932;
size = char104.Size();
cout << "test 193 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 194
char12 += 63250;
size = char12.Size();
cout << "test 194 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 195
char7 += 14200;
size = char7.Size();
cout << "test 195 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 196
char69 = char81;
status = char69 == char81;
cout << "test 196 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 197
char53 = char118;
status = char53 == char118;
cout << "test 197 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 198
char94 += 13306;
size = char94.Size();
cout << "test 198 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 199
status = char84[42880];
cout << "test 199 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 200
status = char86[48446];
cout << "test 200 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 201
char104 = char79;
status = char104 == char79;
cout << "test 201 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 202
char67 -= 23650;
size = char67.Size();
cout << "test 202 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 203
CDegChar char124 = char70;
status = char124 == char70;
cout << "test 203 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 204
status = char74[49476];
cout << "test 204 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 205
char48 += 58578;
size = char48.Size();
cout << "test 205 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 206
char98 += 20536;
size = char98.Size();
cout << "test 206 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 207
status = char74 == char19;
cout << "test 207 - out: " << status << " - ref: 1 - match: " << (status == true) << endl;
 
//test 208
CDegChar char125 = char41;
status = char125 == char41;
cout << "test 208 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 209
char35 -= 48488;
size = char35.Size();
cout << "test 209 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 210
char89 += 39494;
size = char89.Size();
cout << "test 210 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 211
char49 -= 52028;
size = char49.Size();
cout << "test 211 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 212
char24 -= 4394;
size = char24.Size();
cout << "test 212 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 213
char60 -= 19056;
size = char60.Size();
cout << "test 213 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 214
CDegChar char126 = char24;
status = char126 == char24;
cout << "test 214 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 215
char24 -= 27290;
size = char24.Size();
cout << "test 215 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 216
char87 -= 50848;
size = char87.Size();
cout << "test 216 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 217
status = char88[16094];
cout << "test 217 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 218
char99 -= 51892;
size = char99.Size();
cout << "test 218 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 219
char67 -= 53506;
size = char67.Size();
cout << "test 219 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 220
char124 = char70;
status = char124 == char70;
cout << "test 220 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 221
char11 -= 12806;
size = char11.Size();
cout << "test 221 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 222
char63 += 5628;
size = char63.Size();
cout << "test 222 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 223
status = char65 == char116;
cout << "test 223 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 224
char88 += 16176;
size = char88.Size();
cout << "test 224 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 225
status = char115[15534];
cout << "test 225 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 226
status = char29 == char126;
cout << "test 226 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 227
char72 -= 24658;
size = char72.Size();
cout << "test 227 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 228
CDegChar char127 = char47;
status = char127 == char47;
cout << "test 228 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 229
char80 += 12660;
size = char80.Size();
cout << "test 229 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 230
char99 += 30402;
size = char99.Size();
cout << "test 230 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 231
char6 -= 48872;
size = char6.Size();
cout << "test 231 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 232
CDegChar char128 = char44;
status = char128 == char44;
cout << "test 232 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 233
status = char85[60210];
cout << "test 233 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 234
char97 -= 21016;
size = char97.Size();
cout << "test 234 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 235
char82 += 64182;
size = char82.Size();
cout << "test 235 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 236
char74 -= 14956;
size = char74.Size();
cout << "test 236 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 237
char20 = char119;
status = char20 == char119;
cout << "test 237 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 238
char87 -= 49184;
size = char87.Size();
cout << "test 238 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 239
char119 += 42590;
size = char119.Size();
cout << "test 239 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 240
status = char110[63540];
cout << "test 240 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 241
char116 += 64642;
size = char116.Size();
cout << "test 241 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 242
status = char64[20392];
cout << "test 242 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 243
status = char61[390];
cout << "test 243 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 244
char110 += 52092;
size = char110.Size();
cout << "test 244 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 245
char102 += 15978;
size = char102.Size();
cout << "test 245 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 246
char32 -= 18608;
size = char32.Size();
cout << "test 246 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 247
status = char122[62510];
cout << "test 247 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 248
status = char46[48196];
cout << "test 248 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 249
char32 += 23506;
size = char32.Size();
cout << "test 249 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 250
char58 = char58;
status = char58 == char58;
cout << "test 250 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 251
char64 = char116;
status = char64 == char116;
cout << "test 251 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 252
char84 += 21132;
size = char84.Size();
cout << "test 252 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 253
char23 += 31930;
size = char23.Size();
cout << "test 253 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 254
char19 += 5952;
size = char19.Size();
cout << "test 254 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 255
char100 += 49150;
size = char100.Size();
cout << "test 255 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 256
char66 -= 38484;
size = char66.Size();
cout << "test 256 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 257
char126 += 18722;
size = char126.Size();
cout << "test 257 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 258
char112 -= 64712;
size = char112.Size();
cout << "test 258 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 259
char121 = char117;
status = char121 == char117;
cout << "test 259 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 260
char29 -= 3996;
size = char29.Size();
cout << "test 260 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 261
char71 += 59658;
size = char71.Size();
cout << "test 261 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 262
status = char83 == char54;
cout << "test 262 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 263
char84 -= 18894;
size = char84.Size();
cout << "test 263 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 264
char73 += 50788;
size = char73.Size();
cout << "test 264 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 265
char40 -= 1138;
size = char40.Size();
cout << "test 265 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 266
char0 -= 11352;
size = char0.Size();
cout << "test 266 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 267
char9 += 18934;
size = char9.Size();
cout << "test 267 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 268
char105 -= 17068;
size = char105.Size();
cout << "test 268 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 269
status = char22[50010];
cout << "test 269 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
    //test 270
char125 += 34400;
size = char125.Size();
cout << "test 270 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 271
CDegChar char129 = char108;
status = char129 == char108;
cout << "test 271 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 272
status = char106 == char25;
cout << "test 272 - out: " << status << " - ref: 1 - match: " << (status == true) << endl;
 
//test 273
char71 -= 37008;
size = char71.Size();
cout << "test 273 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 274
char104 = char35;
status = char104 == char35;
cout << "test 274 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 275
char33 = char100;
status = char33 == char100;
cout << "test 275 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 276
char36 -= 8754;
size = char36.Size();
cout << "test 276 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 277
char22 += 13592;
size = char22.Size();
cout << "test 277 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 278
char38 += 31158;
size = char38.Size();
cout << "test 278 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 279
char84 -= 1388;
size = char84.Size();
cout << "test 279 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 280
char76 += 29978;
size = char76.Size();
cout << "test 280 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 281
status = char20[13088];
cout << "test 281 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 282
char116 += 62814;
size = char116.Size();
cout << "test 282 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 283
char63 += 54068;
size = char63.Size();
cout << "test 283 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 284
CDegChar char130 = char19;
status = char130 == char19;
cout << "test 284 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 285
CDegChar char131 = char108;
status = char131 == char108;
cout << "test 285 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 286
char17 += 49658;
size = char17.Size();
cout << "test 286 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 287
char18 = char6;
status = char18 == char6;
cout << "test 287 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 288
char16 -= 56126;
size = char16.Size();
cout << "test 288 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 289
char81 += 55956;
size = char81.Size();
cout << "test 289 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 290
status = char70[35426];
cout << "test 290 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 291
status = char20[7944];
cout << "test 291 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 292
char3 -= 8294;
size = char3.Size();
cout << "test 292 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 293
status = char32[8156];
cout << "test 293 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 294
char128 -= 26186;
size = char128.Size();
cout << "test 294 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 295
char62 -= 64016;
size = char62.Size();
cout << "test 295 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 296
char95 += 56590;
size = char95.Size();
cout << "test 296 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 297
char100 += 58020;
size = char100.Size();
cout << "test 297 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 298
status = char111 == char130;
cout << "test 298 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 299
char83 += 26264;
size = char83.Size();
cout << "test 299 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 300
char49 -= 31030;
size = char49.Size();
cout << "test 300 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 301
char57 += 43756;
size = char57.Size();
cout << "test 301 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 302
char7 += 30874;
size = char7.Size();
cout << "test 302 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 303
char85 += 44192;
size = char85.Size();
cout << "test 303 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 304
char82 += 56542;
size = char82.Size();
cout << "test 304 - out: " << size << " - ref: 4 - match: " << (size == 4) << endl;
 
//test 305
char7 += 32948;
size = char7.Size();
cout << "test 305 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 306
char2 += 32514;
size = char2.Size();
cout << "test 306 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 307
char8 -= 37928;
size = char8.Size();
cout << "test 307 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 308
CDegChar char132 = char85;
status = char132 == char85;
cout << "test 308 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 309
status = char58[47986];
cout << "test 309 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 310
char122 -= 36696;
size = char122.Size();
cout << "test 310 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 311
status = char29[18678];
cout << "test 311 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 312
CDegChar char133 = char52;
status = char133 == char52;
cout << "test 312 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 313
char74 = char100;
status = char74 == char100;
cout << "test 313 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 314
status = char105[20454];
cout << "test 314 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 315
char63 += 46428;
size = char63.Size();
cout << "test 315 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 316
status = char84[6602];
cout << "test 316 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 317
char121 += 58256;
size = char121.Size();
cout << "test 317 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 318
char19 = char128;
status = char19 == char128;
cout << "test 318 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 319
status = char103[32804];
cout << "test 319 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 320
char121 += 22834;
size = char121.Size();
cout << "test 320 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 321
status = char78[6168];
cout << "test 321 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 322
char127 -= 63670;
size = char127.Size();
cout << "test 322 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 323
char97 -= 53356;
size = char97.Size();
cout << "test 323 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 324
char3 -= 64538;
size = char3.Size();
cout << "test 324 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 325
char85 += 42528;
size = char85.Size();
cout << "test 325 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 326
char115 -= 17502;
size = char115.Size();
cout << "test 326 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 327
status = char16 == char91;
cout << "test 327 - out: " << status << " - ref: 1 - match: " << (status == true) << endl;
 
//test 328
status = char52[43650];
cout << "test 328 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 329
char78 += 21928;
size = char78.Size();
cout << "test 329 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 330
char4 += 16262;
size = char4.Size();
cout << "test 330 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 331
status = char33[41340];
cout << "test 331 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 332
CDegChar char134 = char122;
status = char134 == char122;
cout << "test 332 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 333
char74 -= 34934;
size = char74.Size();
cout << "test 333 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 334
char58 = char60;
status = char58 == char60;
cout << "test 334 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 335
status = char110[3546];
cout << "test 335 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 336
status = char94[13024];
cout << "test 336 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 337
status = char38 == char105;
cout << "test 337 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 338
char97 += 54516;
size = char97.Size();
cout << "test 338 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 339
char52 += 4162;
size = char52.Size();
cout << "test 339 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 340
char55 -= 18024;
size = char55.Size();
cout << "test 340 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 341
char5 -= 30534;
size = char5.Size();
cout << "test 341 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 342
char66 += 3132;
size = char66.Size();
cout << "test 342 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 343
char117 += 1578;
size = char117.Size();
cout << "test 343 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 344
status = char107[33648];
cout << "test 344 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 345
char62 -= 32238;
size = char62.Size();
cout << "test 345 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 346
status = char68[8452];
cout << "test 346 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 347
char88 = char79;
status = char88 == char79;
cout << "test 347 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 348
char53 = char93;
status = char53 == char93;
cout << "test 348 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 349
char96 += 17430;
size = char96.Size();
cout << "test 349 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 350
char9 += 39756;
size = char9.Size();
cout << "test 350 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 351
char88 -= 60538;
size = char88.Size();
cout << "test 351 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 352
char31 -= 6656;
size = char31.Size();
cout << "test 352 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 353
status = char60[45502];
cout << "test 353 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 354
char127 += 33556;
size = char127.Size();
cout << "test 354 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 355
status = char37[44258];
cout << "test 355 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 356
CDegChar char135 = char114;
status = char135 == char114;
cout << "test 356 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 357
status = char69 == char127;
cout << "test 357 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 358
char24 += 50514;
size = char24.Size();
cout << "test 358 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 359
char51 += 2744;
size = char51.Size();
cout << "test 359 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 360
char0 += 982;
size = char0.Size();
cout << "test 360 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 361
char28 -= 11788;
size = char28.Size();
cout << "test 361 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 362
char86 += 44602;
size = char86.Size();
cout << "test 362 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 363
char31 -= 5824;
size = char31.Size();
cout << "test 363 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 364
CDegChar char136 = char76;
status = char136 == char76;
cout << "test 364 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 365
status = char54[39338];
cout << "test 365 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 366
char82 -= 52464;
size = char82.Size();
cout << "test 366 - out: " << size << " - ref: 4 - match: " << (size == 4) << endl;
 
//test 367
char104 -= 30062;
size = char104.Size();
cout << "test 367 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 368
char122 -= 7812;
size = char122.Size();
cout << "test 368 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 369
char80 = char112;
status = char80 == char112;
cout << "test 369 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 370
char100 -= 50040;
size = char100.Size();
cout << "test 370 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 371
char22 -= 41878;
size = char22.Size();
cout << "test 371 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 372
char100 -= 8396;
size = char100.Size();
cout << "test 372 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 373
char68 += 20474;
size = char68.Size();
cout << "test 373 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 374
char82 += 29568;
size = char82.Size();
cout << "test 374 - out: " << size << " - ref: 5 - match: " << (size == 5) << endl;
 
//test 375
char75 -= 63806;
size = char75.Size();
cout << "test 375 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 376
char53 -= 4244;
size = char53.Size();
cout << "test 376 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 377
CDegChar char137 = char72;
status = char137 == char72;
cout << "test 377 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 378
status = char99 == char104;
cout << "test 378 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 379
CDegChar char138 = char88;
status = char138 == char88;
cout << "test 379 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 380
status = char94[9696];
cout << "test 380 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 381
char104 -= 38686;
size = char104.Size();
cout << "test 381 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 382
char119 += 12276;
size = char119.Size();
cout << "test 382 - out: " << size << " - ref: 4 - match: " << (size == 4) << endl;
 
//test 383
char19 -= 26434;
size = char19.Size();
cout << "test 383 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 384
char62 += 51560;
size = char62.Size();
cout << "test 384 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 385
char113 += 5702;
size = char113.Size();
cout << "test 385 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 386
char26 += 30524;
size = char26.Size();
cout << "test 386 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 387
char59 = char94;
status = char59 == char94;
cout << "test 387 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 388
char125 -= 38512;
size = char125.Size();
cout << "test 388 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 389
char77 += 60654;
size = char77.Size();
cout << "test 389 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 390
char107 -= 39940;
size = char107.Size();
cout << "test 390 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 391
char3 -= 36498;
size = char3.Size();
cout << "test 391 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 392
char78 -= 21752;
size = char78.Size();
cout << "test 392 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 393
char16 += 33558;
size = char16.Size();
cout << "test 393 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 394
char124 = char20;
status = char124 == char20;
cout << "test 394 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 395
char116 -= 13178;
size = char116.Size();
cout << "test 395 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 396
char64 -= 19712;
size = char64.Size();
cout << "test 396 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 397
status = char22 == char104;
cout << "test 397 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 398
char46 -= 7700;
size = char46.Size();
cout << "test 398 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 399
char38 -= 17378;
size = char38.Size();
cout << "test 399 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 400
status = char19[18056];
cout << "test 400 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 401
status = char117[3558];
cout << "test 401 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 402
char51 += 2908;
size = char51.Size();
cout << "test 402 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 403
char33 = char125;
status = char33 == char125;
cout << "test 403 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 404
status = char85 == char74;
cout << "test 404 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 405
char114 += 21134;
size = char114.Size();
cout << "test 405 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 406
char110 -= 63012;
size = char110.Size();
cout << "test 406 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 407
status = char20 == char108;
cout << "test 407 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 408
status = char59[56856];
cout << "test 408 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 409
char35 -= 63158;
size = char35.Size();
cout << "test 409 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 410
status = char121[26220];
cout << "test 410 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 411
char124 = char5;
status = char124 == char5;
cout << "test 411 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 412
status = char83[35872];
cout << "test 412 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 413
status = char109[57950];
cout << "test 413 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 414
char55 -= 25652;
size = char55.Size();
cout << "test 414 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 415
char123 -= 22658;
size = char123.Size();
cout << "test 415 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 416
char93 -= 23464;
size = char93.Size();
cout << "test 416 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 417
status = char81[32134];
cout << "test 417 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 418
char90 += 30588;
size = char90.Size();
cout << "test 418 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 419
status = char4 == char118;
cout << "test 419 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 420
char93 -= 38064;
size = char93.Size();
cout << "test 420 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 421
CDegChar char139 = char43;
status = char139 == char43;
cout << "test 421 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 422
char96 += 7130;
size = char96.Size();
cout << "test 422 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 423
status = char92 == char13;
cout << "test 423 - out: " << status << " - ref: 1 - match: " << (status == true) << endl;
 
//test 424
char30 = char55;
status = char30 == char55;
cout << "test 424 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 425
char139 = char75;
status = char139 == char75;
cout << "test 425 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 426
status = char123[48706];
cout << "test 426 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 427
status = char69[19560];
cout << "test 427 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 428
CDegChar char140 = char83;
status = char140 == char83;
cout << "test 428 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 429
status = char99[41650];
cout << "test 429 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 430
status = char124[3992];
cout << "test 430 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 431
CDegChar char141 = char46;
status = char141 == char46;
cout << "test 431 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 432
char136 -= 42274;
size = char136.Size();
cout << "test 432 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 433
char6 += 2248;
size = char6.Size();
cout << "test 433 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 434
CDegChar char142 = char7;
status = char142 == char7;
cout << "test 434 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 435
CDegChar char143 = char56;
status = char143 == char56;
cout << "test 435 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 436
status = char75 == char113;
cout << "test 436 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 437
char139 -= 4532;
size = char139.Size();
cout << "test 437 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 438
char109 -= 1026;
size = char109.Size();
cout << "test 438 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 439
CDegChar char144 = char99;
status = char144 == char99;
cout << "test 439 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 440
char89 -= 45668;
size = char89.Size();
cout << "test 440 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 441
char116 -= 57458;
size = char116.Size();
cout << "test 441 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 442
status = char97 == char104;
cout << "test 442 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 443
char98 -= 17910;
size = char98.Size();
cout << "test 443 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 444
status = char17[28332];
cout << "test 444 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 445
CDegChar char145 = char131;
status = char145 == char131;
cout << "test 445 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 446
status = char127[60646];
cout << "test 446 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 447
char46 -= 46684;
size = char46.Size();
cout << "test 447 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 448
char7 += 52938;
size = char7.Size();
cout << "test 448 - out: " << size << " - ref: 4 - match: " << (size == 4) << endl;
 
//test 449
char141 -= 56464;
size = char141.Size();
cout << "test 449 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 450
char23 += 398;
size = char23.Size();
cout << "test 450 - out: " << size << " - ref: 4 - match: " << (size == 4) << endl;
 
//test 451
char44 += 45348;
size = char44.Size();
cout << "test 451 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 452
char112 -= 65074;
size = char112.Size();
cout << "test 452 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 453
char123 -= 49432;
size = char123.Size();
cout << "test 453 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 454
status = char132 == char67;
cout << "test 454 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 455
status = char138[12652];
cout << "test 455 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 456
char47 += 37146;
size = char47.Size();
cout << "test 456 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 457
char11 += 65312;
size = char11.Size();
cout << "test 457 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 458
CDegChar char146 = char110;
status = char146 == char110;
cout << "test 458 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 459
CDegChar char147 = char28;
status = char147 == char28;
cout << "test 459 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 460
char143 += 8598;
size = char143.Size();
cout << "test 460 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 461
char56 += 14028;
size = char56.Size();
cout << "test 461 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 462
char127 += 56826;
size = char127.Size();
cout << "test 462 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 463
char9 -= 55680;
size = char9.Size();
cout << "test 463 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 464
char145 += 5950;
size = char145.Size();
cout << "test 464 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 465
CDegChar char148 = char24;
status = char148 == char24;
cout << "test 465 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 466
char41 -= 10160;
size = char41.Size();
cout << "test 466 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 467
char134 += 40750;
size = char134.Size();
cout << "test 467 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 468
char25 = char95;
status = char25 == char95;
cout << "test 468 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 469
CDegChar char149 = char91;
status = char149 == char91;
cout << "test 469 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 470
status = char102 == char31;
cout << "test 470 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 471
CDegChar char150 = char20;
status = char150 == char20;
cout << "test 471 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 472
char135 -= 17936;
size = char135.Size();
cout << "test 472 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 473
char12 -= 39182;
size = char12.Size();
cout << "test 473 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 474
char122 += 52900;
size = char122.Size();
cout << "test 474 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 475
char49 -= 55730;
size = char49.Size();
cout << "test 475 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 476
char45 -= 62104;
size = char45.Size();
cout << "test 476 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 477
char148 = char69;
status = char148 == char69;
cout << "test 477 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 478
status = char111 == char126;
cout << "test 478 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 479
char119 += 38042;
size = char119.Size();
cout << "test 479 - out: " << size << " - ref: 5 - match: " << (size == 5) << endl;
 
//test 480
status = char86 == char71;
cout << "test 480 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 481
status = char73[6366];
cout << "test 481 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 482
status = char91[60596];
cout << "test 482 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
    //test 483
char0 -= 56066;
size = char0.Size();
cout << "test 483 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 484
char35 += 41000;
size = char35.Size();
cout << "test 484 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 485
status = char114[60422];
cout << "test 485 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 486
char105 -= 38908;
size = char105.Size();
cout << "test 486 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 487
char131 = char125;
status = char131 == char125;
cout << "test 487 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 488
char49 += 45360;
size = char49.Size();
cout << "test 488 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 489
char67 -= 54958;
size = char67.Size();
cout << "test 489 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 490
status = char120[57540];
cout << "test 490 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 491
char120 += 10834;
size = char120.Size();
cout << "test 491 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 492
status = char57[29624];
cout << "test 492 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 493
char107 += 16598;
size = char107.Size();
cout << "test 493 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 494
char28 -= 20236;
size = char28.Size();
cout << "test 494 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 495
status = char104 == char1;
cout << "test 495 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 496
char63 += 12224;
size = char63.Size();
cout << "test 496 - out: " << size << " - ref: 4 - match: " << (size == 4) << endl;
 
//test 497
char31 += 4734;
size = char31.Size();
cout << "test 497 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 498
char96 -= 60116;
size = char96.Size();
cout << "test 498 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 499
CDegChar char151 = char144;
status = char151 == char144;
cout << "test 499 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 500
status = char4[49774];
cout << "test 500 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 501
char102 = char85;
status = char102 == char85;
cout << "test 501 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 502
char106 += 47122;
size = char106.Size();
cout << "test 502 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 503
char35 -= 44152;
size = char35.Size();
cout << "test 503 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 504
char56 = char57;
status = char56 == char57;
cout << "test 504 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 505
CDegChar char152 = char31;
status = char152 == char31;
cout << "test 505 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 506
CDegChar char153 = char115;
status = char153 == char115;
cout << "test 506 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 507
char58 = char45;
status = char58 == char45;
cout << "test 507 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 508
CDegChar char154 = char112;
status = char154 == char112;
cout << "test 508 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 509
char108 += 9790;
size = char108.Size();
cout << "test 509 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 510
char85 = char136;
status = char85 == char136;
cout << "test 510 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 511
status = char80 == char75;
cout << "test 511 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 512
char96 -= 60936;
size = char96.Size();
cout << "test 512 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 513
char25 -= 31590;
size = char25.Size();
cout << "test 513 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 514
char154 = char71;
status = char154 == char71;
cout << "test 514 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 515
char2 += 59722;
size = char2.Size();
cout << "test 515 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 516
char39 += 39184;
size = char39.Size();
cout << "test 516 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 517
char65 -= 18446;
size = char65.Size();
cout << "test 517 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 518
char49 = char83;
status = char49 == char83;
cout << "test 518 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 519
char147 += 4274;
size = char147.Size();
cout << "test 519 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 520
char111 = char129;
status = char111 == char129;
cout << "test 520 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 521
char98 += 62518;
size = char98.Size();
cout << "test 521 - out: " << size << " - ref: 4 - match: " << (size == 4) << endl;
 
//test 522
status = char125[41452];
cout << "test 522 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 523
char35 -= 7066;
size = char35.Size();
cout << "test 523 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 524
char7 = char142;
status = char7 == char142;
cout << "test 524 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 525
CDegChar char155 = char69;
status = char155 == char69;
cout << "test 525 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 526
char63 += 21258;
size = char63.Size();
cout << "test 526 - out: " << size << " - ref: 5 - match: " << (size == 5) << endl;
 
//test 527
char121 += 24016;
size = char121.Size();
cout << "test 527 - out: " << size << " - ref: 4 - match: " << (size == 4) << endl;
 
//test 528
status = char108 == char60;
cout << "test 528 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 529
CDegChar char156 = char99;
status = char156 == char99;
cout << "test 529 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 530
CDegChar char157 = char24;
status = char157 == char24;
cout << "test 530 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 531
char141 += 33532;
size = char141.Size();
cout << "test 531 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 532
char146 -= 64490;
size = char146.Size();
cout << "test 532 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 533
char147 += 17456;
size = char147.Size();
cout << "test 533 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 534
CDegChar char158 = char5;
status = char158 == char5;
cout << "test 534 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 535
char122 -= 60762;
size = char122.Size();
cout << "test 535 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 536
char136 -= 14432;
size = char136.Size();
cout << "test 536 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 537
CDegChar char159 = char100;
status = char159 == char100;
cout << "test 537 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 538
char107 -= 40138;
size = char107.Size();
cout << "test 538 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 539
status = char109[33424];
cout << "test 539 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 540
char134 += 24462;
size = char134.Size();
cout << "test 540 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 541
status = char52 == char24;
cout << "test 541 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 542
status = char1[27698];
cout << "test 542 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 543
char108 -= 34584;
size = char108.Size();
cout << "test 543 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 544
CDegChar char160 = char33;
status = char160 == char33;
cout << "test 544 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 545
char72 = char19;
status = char72 == char19;
cout << "test 545 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 546
char125 += 61512;
size = char125.Size();
cout << "test 546 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 547
CDegChar char161 = char100;
status = char161 == char100;
cout << "test 547 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 548
status = char11[44818];
cout << "test 548 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 549
status = char65 == char50;
cout << "test 549 - out: " << status << " - ref: 1 - match: " << (status == true) << endl;
 
//test 550
status = char125[40854];
cout << "test 550 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 551
status = char4[19660];
cout << "test 551 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 552
char37 += 27642;
size = char37.Size();
cout << "test 552 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 553
status = char84[16256];
cout << "test 553 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 554
char67 += 13630;
size = char67.Size();
cout << "test 554 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 555
char151 += 31892;
size = char151.Size();
cout << "test 555 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 556
char83 += 5218;
size = char83.Size();
cout << "test 556 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 557
char148 -= 45320;
size = char148.Size();
cout << "test 557 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 558
char30 -= 23142;
size = char30.Size();
cout << "test 558 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 559
char153 -= 8668;
size = char153.Size();
cout << "test 559 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 560
char133 += 53322;
size = char133.Size();
cout << "test 560 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 561
char98 = char149;
status = char98 == char149;
cout << "test 561 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 562
char123 -= 63246;
size = char123.Size();
cout << "test 562 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 563
status = char135[17572];
cout << "test 563 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 564
status = char92[18354];
cout << "test 564 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 565
char22 -= 47256;
size = char22.Size();
cout << "test 565 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 566
char46 += 29494;
size = char46.Size();
cout << "test 566 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 567
status = char143[27884];
cout << "test 567 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 568
status = char106[41626];
cout << "test 568 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 569
char86 -= 24224;
size = char86.Size();
cout << "test 569 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 570
char67 += 46814;
size = char67.Size();
cout << "test 570 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 571
char142 -= 41652;
size = char142.Size();
cout << "test 571 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 572
char80 += 35074;
size = char80.Size();
cout << "test 572 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 573
char52 -= 42536;
size = char52.Size();
cout << "test 573 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 574
char50 += 10758;
size = char50.Size();
cout << "test 574 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 575
CDegChar char162 = char15;
status = char162 == char15;
cout << "test 575 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 576
status = char70[57688];
cout << "test 576 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 577
char22 -= 17142;
size = char22.Size();
cout << "test 577 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 578
char137 -= 20396;
size = char137.Size();
cout << "test 578 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 579
char115 += 62554;
size = char115.Size();
cout << "test 579 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 580
char136 -= 11104;
size = char136.Size();
cout << "test 580 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 581
char15 -= 31390;
size = char15.Size();
cout << "test 581 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 582
char118 -= 2420;
size = char118.Size();
cout << "test 582 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 583
status = char121[11970];
cout << "test 583 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 584
CDegChar char163 = char64;
status = char163 == char64;
cout << "test 584 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 585
char137 -= 57892;
size = char137.Size();
cout << "test 585 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 586
char103 -= 41778;
size = char103.Size();
cout << "test 586 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 587
char15 += 27160;
size = char15.Size();
cout << "test 587 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 588
char141 = char155;
status = char141 == char155;
cout << "test 588 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 589
char28 += 37484;
size = char28.Size();
cout << "test 589 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 590
char102 += 9754;
size = char102.Size();
cout << "test 590 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 591
char85 += 22560;
size = char85.Size();
cout << "test 591 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 592
char106 -= 7774;
size = char106.Size();
cout << "test 592 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 593
char155 = char133;
status = char155 == char133;
cout << "test 593 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 594
status = char142[46210];
cout << "test 594 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 595
char138 += 26536;
size = char138.Size();
cout << "test 595 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 596
status = char114 == char159;
cout << "test 596 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 597
char73 = char22;
status = char73 == char22;
cout << "test 597 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 598
char43 += 30314;
size = char43.Size();
cout << "test 598 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 599
char15 -= 57520;
size = char15.Size();
cout << "test 599 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 600
char109 += 27694;
size = char109.Size();
cout << "test 600 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 601
char74 += 37956;
size = char74.Size();
cout << "test 601 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 602
status = char36[5074];
cout << "test 602 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 603
char131 -= 35640;
size = char131.Size();
cout << "test 603 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 604
status = char117[56918];
cout << "test 604 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 605
char40 = char109;
status = char40 == char109;
cout << "test 605 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 606
char106 += 46266;
size = char106.Size();
cout << "test 606 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 607
char163 += 44864;
size = char163.Size();
cout << "test 607 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 608
char81 -= 14334;
size = char81.Size();
cout << "test 608 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 609
status = char99[28244];
cout << "test 609 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 610
status = char155[290];
cout << "test 610 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 611
char35 = char13;
status = char35 == char13;
cout << "test 611 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 612
CDegChar char164 = char26;
status = char164 == char26;
cout << "test 612 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 613
status = char145[24978];
cout << "test 613 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 614
CDegChar char165 = char66;
status = char165 == char66;
cout << "test 614 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 615
char85 = char81;
status = char85 == char81;
cout << "test 615 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 616
CDegChar char166 = char123;
status = char166 == char123;
cout << "test 616 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 617
status = char62[49614];
cout << "test 617 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 618
char110 -= 40548;
size = char110.Size();
cout << "test 618 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 619
char47 += 48242;
size = char47.Size();
cout << "test 619 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 620
CDegChar char167 = char58;
status = char167 == char58;
cout << "test 620 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 621
char44 += 9492;
size = char44.Size();
cout << "test 621 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 622
char43 += 14050;
size = char43.Size();
cout << "test 622 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 623
char101 -= 5512;
size = char101.Size();
cout << "test 623 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 624
status = char164[26854];
cout << "test 624 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 625
char19 -= 25180;
size = char19.Size();
cout << "test 625 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 626
status = char48[27338];
cout << "test 626 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 627
char65 -= 10384;
size = char65.Size();
cout << "test 627 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 628
char87 += 48526;
size = char87.Size();
cout << "test 628 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 629
char59 += 40228;
size = char59.Size();
cout << "test 629 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 630
char42 += 55858;
size = char42.Size();
cout << "test 630 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 631
status = char86 == char50;
cout << "test 631 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 632
char86 += 29110;
size = char86.Size();
cout << "test 632 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 633
char41 += 23916;
size = char41.Size();
cout << "test 633 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 634
char10 -= 44314;
size = char10.Size();
cout << "test 634 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 635
status = char0 == char133;
cout << "test 635 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 636
status = char103 == char71;
cout << "test 636 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 637
char98 -= 43828;
size = char98.Size();
cout << "test 637 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 638
char19 -= 35714;
size = char19.Size();
cout << "test 638 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 639
char64 -= 27304;
size = char64.Size();
cout << "test 639 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 640
status = char164[6278];
cout << "test 640 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 641
status = char108[3708];
cout << "test 641 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 642
char54 -= 40298;
size = char54.Size();
cout << "test 642 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 643
char117 -= 29616;
size = char117.Size();
cout << "test 643 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 644
char43 -= 23342;
size = char43.Size();
cout << "test 644 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 645
char36 += 36676;
size = char36.Size();
cout << "test 645 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 646
status = char16[35538];
cout << "test 646 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 647
char78 += 44600;
size = char78.Size();
cout << "test 647 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 648
char103 += 40278;
size = char103.Size();
cout << "test 648 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 649
char95 += 46476;
size = char95.Size();
cout << "test 649 - out: " << size << " - ref: 4 - match: " << (size == 4) << endl;
 
//test 650
status = char55[31674];
cout << "test 650 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 651
status = char122 == char64;
cout << "test 651 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 652
status = char119[50942];
cout << "test 652 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 653
char83 -= 35156;
size = char83.Size();
cout << "test 653 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 654
CDegChar char168 = char74;
status = char168 == char74;
cout << "test 654 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 655
CDegChar char169 = char15;
status = char169 == char15;
cout << "test 655 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 656
char89 += 45210;
size = char89.Size();
cout << "test 656 - out: " << size << " - ref: 4 - match: " << (size == 4) << endl;
 
//test 657
char83 += 17568;
size = char83.Size();
cout << "test 657 - out: " << size << " - ref: 4 - match: " << (size == 4) << endl;
 
//test 658
char58 -= 21726;
size = char58.Size();
cout << "test 658 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 659
char25 -= 22708;
size = char25.Size();
cout << "test 659 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 660
status = char168[14082];
cout << "test 660 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 661
status = char69[44072];
cout << "test 661 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 662
status = char147[26630];
cout << "test 662 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 663
char84 += 17404;
size = char84.Size();
cout << "test 663 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 664
char17 -= 28906;
size = char17.Size();
cout << "test 664 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 665
char127 += 64816;
size = char127.Size();
cout << "test 665 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 666
status = char136[37550];
cout << "test 666 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 667
CDegChar char170 = char143;
status = char170 == char143;
cout << "test 667 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 668
char136 += 4448;
size = char136.Size();
cout << "test 668 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 669
CDegChar char171 = char4;
status = char171 == char4;
cout << "test 669 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 670
status = char16[20938];
cout << "test 670 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 671
char128 += 31632;
size = char128.Size();
cout << "test 671 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 672
char148 -= 27790;
size = char148.Size();
cout << "test 672 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 673
char148 = char59;
status = char148 == char59;
cout << "test 673 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 674
status = char150[4402];
cout << "test 674 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 675
char160 += 12312;
size = char160.Size();
cout << "test 675 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 676
char28 += 61622;
size = char28.Size();
cout << "test 676 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 677
char55 += 10348;
size = char55.Size();
cout << "test 677 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 678
char84 -= 13338;
size = char84.Size();
cout << "test 678 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 679
char82 += 15904;
size = char82.Size();
cout << "test 679 - out: " << size << " - ref: 6 - match: " << (size == 6) << endl;
 
//test 680
status = char99[48222];
cout << "test 680 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 681
status = char37[34356];
cout << "test 681 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 682
char62 -= 25218;
size = char62.Size();
cout << "test 682 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 683
status = char159 == char73;
cout << "test 683 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 684
char43 += 14214;
size = char43.Size();
cout << "test 684 - out: " << size << " - ref: 4 - match: " << (size == 4) << endl;
 
//test 685
char145 -= 63868;
size = char145.Size();
cout << "test 685 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 686
char66 = char131;
status = char66 == char131;
cout << "test 686 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 687
char52 -= 1712;
size = char52.Size();
cout << "test 687 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 688
status = char146 == char49;
cout << "test 688 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 689
char167 += 35396;
size = char167.Size();
cout << "test 689 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 690
status = char166 == char1;
cout << "test 690 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 691
char23 += 53560;
size = char23.Size();
cout << "test 691 - out: " << size << " - ref: 5 - match: " << (size == 5) << endl;
 
//test 692
char89 -= 23638;
size = char89.Size();
cout << "test 692 - out: " << size << " - ref: 4 - match: " << (size == 4) << endl;
 
//test 693
status = char153 == char129;
cout << "test 693 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 694
char2 += 17082;
size = char2.Size();
cout << "test 694 - out: " << size << " - ref: 4 - match: " << (size == 4) << endl;
 
//test 695
char79 += 5440;
size = char79.Size();
cout << "test 695 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 696
char159 += 22014;
size = char159.Size();
cout << "test 696 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 697
char65 += 42068;
size = char65.Size();
cout << "test 697 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 698
char161 = char31;
status = char161 == char31;
cout << "test 698 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 699
status = char138[39624];
cout << "test 699 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 700
status = char37[40742];
cout << "test 700 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 701
char123 += 48540;
size = char123.Size();
cout << "test 701 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 702
status = char110 == char160;
cout << "test 702 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 703
char34 += 43472;
size = char34.Size();
cout << "test 703 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 704
status = char9[8142];
cout << "test 704 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 705
char117 = char13;
status = char117 == char13;
cout << "test 705 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 706
char90 -= 10866;
size = char90.Size();
cout << "test 706 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 707
char31 = char6;
status = char31 == char6;
cout << "test 707 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 708
char102 += 16374;
size = char102.Size();
cout << "test 708 - out: " << size << " - ref: 4 - match: " << (size == 4) << endl;
 
//test 709
char96 += 12460;
size = char96.Size();
cout << "test 709 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 710
char87 -= 2394;
size = char87.Size();
cout << "test 710 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 711
char134 = char2;
status = char134 == char2;
cout << "test 711 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 712
char84 -= 59294;
size = char84.Size();
cout << "test 712 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 713
char23 += 6772;
size = char23.Size();
cout << "test 713 - out: " << size << " - ref: 6 - match: " << (size == 6) << endl;
 
//test 714
status = char169 == char34;
cout << "test 714 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 715
char90 = char64;
status = char90 == char64;
cout << "test 715 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 716
CDegChar char172 = char154;
status = char172 == char154;
cout << "test 716 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 717
char85 -= 18482;
size = char85.Size();
cout << "test 717 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 718
status = char60[4888];
cout << "test 718 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 719
char141 += 28598;
size = char141.Size();
cout << "test 719 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 720
char68 -= 62316;
size = char68.Size();
cout << "test 720 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 721
status = char160[47898];
cout << "test 721 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 722
char166 -= 45344;
size = char166.Size();
cout << "test 722 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 723
CDegChar char173 = char93;
status = char173 == char93;
cout << "test 723 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 724
status = char7[25226];
cout << "test 724 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 725
char66 -= 21328;
size = char66.Size();
cout << "test 725 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 726
char39 -= 63310;
size = char39.Size();
cout << "test 726 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 727
char76 -= 29156;
size = char76.Size();
cout << "test 727 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 728
CDegChar char174 = char58;
status = char174 == char58;
cout << "test 728 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 729
status = char47[28990];
cout << "test 729 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 730
status = char84[59540];
cout << "test 730 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 731
char87 -= 28770;
size = char87.Size();
cout << "test 731 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 732
char15 += 48392;
size = char15.Size();
cout << "test 732 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 733
char52 -= 54886;
size = char52.Size();
cout << "test 733 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 734
char129 -= 52700;
size = char129.Size();
cout << "test 734 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 735
status = char10[27722];
cout << "test 735 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 736
char5 = char38;
status = char5 == char38;
cout << "test 736 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 737
status = char21 == char122;
cout << "test 737 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 738
CDegChar char175 = char154;
status = char175 == char154;
cout << "test 738 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 739
CDegChar char176 = char33;
status = char176 == char33;
cout << "test 739 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 740
char138 = char143;
status = char138 == char143;
cout << "test 740 - out: " << status << " - ref: 1 - match: " << status << endl;
 
    //test 741
char158 += 58666;
size = char158.Size();
cout << "test 741 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 742
char132 += 11888;
size = char132.Size();
cout << "test 742 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 743
char48 -= 25838;
size = char48.Size();
cout << "test 743 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 744
status = char153 == char80;
cout << "test 744 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 745
char175 = char48;
status = char175 == char48;
cout << "test 745 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 746
status = char160[27896];
cout << "test 746 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 747
CDegChar char177 = char59;
status = char177 == char59;
cout << "test 747 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 748
char85 -= 58626;
size = char85.Size();
cout << "test 748 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 749
char87 += 45608;
size = char87.Size();
cout << "test 749 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 750
char74 += 42502;
size = char74.Size();
cout << "test 750 - out: " << size << " - ref: 4 - match: " << (size == 4) << endl;
 
//test 751
status = char159[6652];
cout << "test 751 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 752
char39 += 48874;
size = char39.Size();
cout << "test 752 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 753
char171 += 9008;
size = char171.Size();
cout << "test 753 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 754
char175 -= 28846;
size = char175.Size();
cout << "test 754 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 755
CDegChar char178 = char65;
status = char178 == char65;
cout << "test 755 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 756
CDegChar char179 = char136;
status = char179 == char136;
cout << "test 756 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 757
status = char173[25436];
cout << "test 757 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 758
char128 += 8138;
size = char128.Size();
cout << "test 758 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 759
status = char82 == char23;
cout << "test 759 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 760
char97 -= 51854;
size = char97.Size();
cout << "test 760 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 761
char159 -= 52772;
size = char159.Size();
cout << "test 761 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 762
char20 += 32562;
size = char20.Size();
cout << "test 762 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 763
char138 += 63000;
size = char138.Size();
cout << "test 763 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 764
char84 -= 61110;
size = char84.Size();
cout << "test 764 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 765
char84 -= 48748;
size = char84.Size();
cout << "test 765 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 766
char64 += 16922;
size = char64.Size();
cout << "test 766 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 767
status = char79[9248];
cout << "test 767 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 768
char91 += 23134;
size = char91.Size();
cout << "test 768 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 769
status = char88 == char42;
cout << "test 769 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 770
char153 = char11;
status = char153 == char11;
cout << "test 770 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 771
char2 = char81;
status = char2 == char81;
cout << "test 771 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 772
char145 -= 30086;
size = char145.Size();
cout << "test 772 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 773
status = char43[53116];
cout << "test 773 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 774
status = char90[4714];
cout << "test 774 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 775
char92 -= 11440;
size = char92.Size();
cout << "test 775 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 776
char5 += 10286;
size = char5.Size();
cout << "test 776 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 777
char90 += 32836;
size = char90.Size();
cout << "test 777 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 778
char127 -= 61394;
size = char127.Size();
cout << "test 778 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 779
status = char84[5944];
cout << "test 779 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 780
char58 += 55894;
size = char58.Size();
cout << "test 780 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 781
char97 -= 54924;
size = char97.Size();
cout << "test 781 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 782
char68 += 53434;
size = char68.Size();
cout << "test 782 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 783
char165 -= 31552;
size = char165.Size();
cout << "test 783 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 784
char63 += 29694;
size = char63.Size();
cout << "test 784 - out: " << size << " - ref: 6 - match: " << (size == 6) << endl;
 
//test 785
char27 -= 55892;
size = char27.Size();
cout << "test 785 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 786
char167 += 23842;
size = char167.Size();
cout << "test 786 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 787
status = char70[8392];
cout << "test 787 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 788
status = char48[23846];
cout << "test 788 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 789
char110 += 5020;
size = char110.Size();
cout << "test 789 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 790
CDegChar char180 = char46;
status = char180 == char46;
cout << "test 790 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 791
status = char133[47638];
cout << "test 791 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 792
status = char56 == char6;
cout << "test 792 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 793
char88 -= 45690;
size = char88.Size();
cout << "test 793 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 794
status = char97 == char16;
cout << "test 794 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 795
CDegChar char181 = char107;
status = char181 == char107;
cout << "test 795 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 796
status = char51 == char163;
cout << "test 796 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 797
char103 += 46640;
size = char103.Size();
cout << "test 797 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 798
status = char104 == char68;
cout << "test 798 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 799
char23 = char134;
status = char23 == char134;
cout << "test 799 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 800
status = char162[27474];
cout << "test 800 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 801
char10 -= 26808;
size = char10.Size();
cout << "test 801 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 802
status = char4 == char86;
cout << "test 802 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 803
status = char82[39948];
cout << "test 803 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 804
char86 += 29754;
size = char86.Size();
cout << "test 804 - out: " << size << " - ref: 4 - match: " << (size == 4) << endl;
 
//test 805
status = char97 == char14;
cout << "test 805 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 806
char129 += 64382;
size = char129.Size();
cout << "test 806 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 807
char154 = char119;
status = char154 == char119;
cout << "test 807 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 808
char77 -= 43170;
size = char77.Size();
cout << "test 808 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 809
status = char97 == char92;
cout << "test 809 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 810
status = char142[19622];
cout << "test 810 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 811
char107 -= 26908;
size = char107.Size();
cout << "test 811 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 812
char120 = char34;
status = char120 == char34;
cout << "test 812 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 813
char16 = char177;
status = char16 == char177;
cout << "test 813 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 814
char164 -= 21838;
size = char164.Size();
cout << "test 814 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 815
CDegChar char182 = char84;
status = char182 == char84;
cout << "test 815 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 816
char165 -= 29056;
size = char165.Size();
cout << "test 816 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 817
status = char128 == char102;
cout << "test 817 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 818
char47 += 7828;
size = char47.Size();
cout << "test 818 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 819
status = char89 == char113;
cout << "test 819 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 820
CDegChar char183 = char123;
status = char183 == char123;
cout << "test 820 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 821
char48 += 31556;
size = char48.Size();
cout << "test 821 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 822
char106 -= 26322;
size = char106.Size();
cout << "test 822 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 823
char25 -= 14904;
size = char25.Size();
cout << "test 823 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 824
status = char41 == char110;
cout << "test 824 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 825
status = char159 == char162;
cout << "test 825 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 826
status = char12[38842];
cout << "test 826 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 827
char119 += 11840;
size = char119.Size();
cout << "test 827 - out: " << size << " - ref: 6 - match: " << (size == 6) << endl;
 
//test 828
char104 -= 766;
size = char104.Size();
cout << "test 828 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 829
char7 += 62804;
size = char7.Size();
cout << "test 829 - out: " << size << " - ref: 4 - match: " << (size == 4) << endl;
 
//test 830
char78 += 29730;
size = char78.Size();
cout << "test 830 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 831
char33 += 25544;
size = char33.Size();
cout << "test 831 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 832
char147 += 48166;
size = char147.Size();
cout << "test 832 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 833
char11 += 16028;
size = char11.Size();
cout << "test 833 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 834
char104 -= 9226;
size = char104.Size();
cout << "test 834 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 835
status = char141[8912];
cout << "test 835 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 836
char105 -= 44238;
size = char105.Size();
cout << "test 836 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 837
status = char132[50532];
cout << "test 837 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 838
char163 += 20338;
size = char163.Size();
cout << "test 838 - out: " << size << " - ref: 4 - match: " << (size == 4) << endl;
 
//test 839
char172 += 13144;
size = char172.Size();
cout << "test 839 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 840
char9 = char43;
status = char9 == char43;
cout << "test 840 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 841
char52 = char12;
status = char52 == char12;
cout << "test 841 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 842
status = char56[7770];
cout << "test 842 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 843
status = char132 == char159;
cout << "test 843 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 844
char162 -= 21662;
size = char162.Size();
cout << "test 844 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 845
status = char100[11124];
cout << "test 845 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 846
status = char40 == char40;
cout << "test 846 - out: " << status << " - ref: 1 - match: " << (status == true) << endl;
 
//test 847
char120 = char167;
status = char120 == char167;
cout << "test 847 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 848
char42 += 23494;
size = char42.Size();
cout << "test 848 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 849
status = char143[39612];
cout << "test 849 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 850
status = char99 == char142;
cout << "test 850 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 851
status = char140[40432];
cout << "test 851 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 852
char137 += 14958;
size = char137.Size();
cout << "test 852 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 853
char141 += 26500;
size = char141.Size();
cout << "test 853 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 854
CDegChar char184 = char123;
status = char184 == char123;
cout << "test 854 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 855
char80 -= 63582;
size = char80.Size();
cout << "test 855 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 856
char141 -= 62004;
size = char141.Size();
cout << "test 856 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 857
status = char64 == char137;
cout << "test 857 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 858
char18 -= 31144;
size = char18.Size();
cout << "test 858 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 859
char67 = char129;
status = char67 == char129;
cout << "test 859 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 860
char118 += 42364;
size = char118.Size();
cout << "test 860 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 861
char114 -= 24682;
size = char114.Size();
cout << "test 861 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 862
char134 -= 21168;
size = char134.Size();
cout << "test 862 - out: " << size << " - ref: 4 - match: " << (size == 4) << endl;
 
//test 863
status = char38[1582];
cout << "test 863 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 864
char4 += 30276;
size = char4.Size();
cout << "test 864 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 865
char83 -= 56786;
size = char83.Size();
cout << "test 865 - out: " << size << " - ref: 4 - match: " << (size == 4) << endl;
 
//test 866
char149 -= 23864;
size = char149.Size();
cout << "test 866 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 867
char24 = char63;
status = char24 == char63;
cout << "test 867 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 868
char35 = char170;
status = char35 == char170;
cout << "test 868 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 869
char138 += 24250;
size = char138.Size();
cout << "test 869 - out: " << size << " - ref: 4 - match: " << (size == 4) << endl;
 
//test 870
status = char70[57664];
cout << "test 870 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 871
CDegChar char185 = char145;
status = char185 == char145;
cout << "test 871 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 872
status = char106[55850];
cout << "test 872 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 873
status = char11[26480];
cout << "test 873 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 874
status = char101[45550];
cout << "test 874 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 875
char121 += 58628;
size = char121.Size();
cout << "test 875 - out: " << size << " - ref: 5 - match: " << (size == 5) << endl;
 
//test 876
char19 -= 11154;
size = char19.Size();
cout << "test 876 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 877
status = char76[22008];
cout << "test 877 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 878
char101 -= 14358;
size = char101.Size();
cout << "test 878 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 879
char178 += 8012;
size = char178.Size();
cout << "test 879 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 880
status = char159 == char46;
cout << "test 880 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 881
CDegChar char186 = char0;
status = char186 == char0;
cout << "test 881 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 882
CDegChar char187 = char92;
status = char187 == char92;
cout << "test 882 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 883
char160 += 38488;
size = char160.Size();
cout << "test 883 - out: " << size << " - ref: 4 - match: " << (size == 4) << endl;
 
//test 884
status = char38 == char44;
cout << "test 884 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 885
status = char161 == char68;
cout << "test 885 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 886
char45 -= 9562;
size = char45.Size();
cout << "test 886 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 887
char132 -= 53344;
size = char132.Size();
cout << "test 887 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 888
char65 += 9118;
size = char65.Size();
cout << "test 888 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 889
status = char128[34420];
cout << "test 889 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 890
char182 = char105;
status = char182 == char105;
cout << "test 890 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 891
status = char130[27624];
cout << "test 891 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 892
status = char1[64198];
cout << "test 892 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 893
char90 = char4;
status = char90 == char4;
cout << "test 893 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 894
char18 -= 28074;
size = char18.Size();
cout << "test 894 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 895
char162 += 45296;
size = char162.Size();
cout << "test 895 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 896
char157 = char124;
status = char157 == char124;
cout << "test 896 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 897
status = char6[57988];
cout << "test 897 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 898
char7 -= 26386;
size = char7.Size();
cout << "test 898 - out: " << size << " - ref: 4 - match: " << (size == 4) << endl;
 
//test 899
char140 += 26488;
size = char140.Size();
cout << "test 899 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 900
status = char186 == char111;
cout << "test 900 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 901
char116 -= 42188;
size = char116.Size();
cout << "test 901 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 902
char131 -= 41978;
size = char131.Size();
cout << "test 902 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 903
status = char68[55168];
cout << "test 903 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 904
char24 -= 44350;
size = char24.Size();
cout << "test 904 - out: " << size << " - ref: 6 - match: " << (size == 6) << endl;
 
//test 905
char5 -= 21652;
size = char5.Size();
cout << "test 905 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 906
status = char90[52322];
cout << "test 906 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 907
status = char48[51464];
cout << "test 907 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 908
char77 += 21094;
size = char77.Size();
cout << "test 908 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 909
char101 += 31196;
size = char101.Size();
cout << "test 909 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 910
char55 -= 2122;
size = char55.Size();
cout << "test 910 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 911
char85 = char96;
status = char85 == char96;
cout << "test 911 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 912
status = char90[28430];
cout << "test 912 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 913
char174 = char21;
status = char174 == char21;
cout << "test 913 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 914
char101 -= 65458;
size = char101.Size();
cout << "test 914 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 915
char90 = char153;
status = char90 == char153;
cout << "test 915 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 916
char94 = char78;
status = char94 == char78;
cout << "test 916 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 917
char89 -= 50412;
size = char89.Size();
cout << "test 917 - out: " << size << " - ref: 4 - match: " << (size == 4) << endl;
 
//test 918
status = char24[55962];
cout << "test 918 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 919
char70 -= 63136;
size = char70.Size();
cout << "test 919 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 920
char25 -= 11998;
size = char25.Size();
cout << "test 920 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 921
status = char182[31412];
cout << "test 921 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 922
status = char87 == char47;
cout << "test 922 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 923
CDegChar char188 = char125;
status = char188 == char125;
cout << "test 923 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 924
char140 -= 15204;
size = char140.Size();
cout << "test 924 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 925
char25 -= 48498;
size = char25.Size();
cout << "test 925 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 926
char146 -= 63832;
size = char146.Size();
cout << "test 926 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 927
char67 += 15094;
size = char67.Size();
cout << "test 927 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 928
char82 += 42924;
size = char82.Size();
cout << "test 928 - out: " << size << " - ref: 7 - match: " << (size == 7) << endl;
 
//test 929
char32 += 11354;
size = char32.Size();
cout << "test 929 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 930
char129 -= 50016;
size = char129.Size();
cout << "test 930 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 931
CDegChar char189 = char153;
status = char189 == char153;
cout << "test 931 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 932
status = char180[48074];
cout << "test 932 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 933
char167 -= 28048;
size = char167.Size();
cout << "test 933 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 934
status = char171 == char99;
cout << "test 934 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 935
status = char177 == char138;
cout << "test 935 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 936
char114 = char67;
status = char114 == char67;
cout << "test 936 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 937
char83 -= 33304;
size = char83.Size();
cout << "test 937 - out: " << size << " - ref: 4 - match: " << (size == 4) << endl;
 
//test 938
status = char15[60086];
cout << "test 938 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 939
status = char145[60012];
cout << "test 939 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 940
char18 += 24090;
size = char18.Size();
cout << "test 940 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 941
char69 += 61472;
size = char69.Size();
cout << "test 941 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 942
status = char69[38494];
cout << "test 942 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 943
char7 += 43060;
size = char7.Size();
cout << "test 943 - out: " << size << " - ref: 5 - match: " << (size == 5) << endl;
 
//test 944
char159 += 27778;
size = char159.Size();
cout << "test 944 - out: " << size << " - ref: 4 - match: " << (size == 4) << endl;
 
//test 945
status = char35[32680];
cout << "test 945 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 946
char174 -= 61830;
size = char174.Size();
cout << "test 946 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 947
status = char7[31612];
cout << "test 947 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 948
char139 += 44650;
size = char139.Size();
cout << "test 948 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 949
char177 -= 30896;
size = char177.Size();
cout << "test 949 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 950
char73 -= 58414;
size = char73.Size();
cout << "test 950 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 951
char103 += 27716;
size = char103.Size();
cout << "test 951 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 952
char36 -= 52178;
size = char36.Size();
cout << "test 952 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 953
char27 = char121;
status = char27 == char121;
cout << "test 953 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 954
status = char177 == char159;
cout << "test 954 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 955
status = char159[652];
cout << "test 955 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 956
char22 += 60602;
size = char22.Size();
cout << "test 956 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 957
char160 = char52;
status = char160 == char52;
cout << "test 957 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 958
status = char40[45054];
cout << "test 958 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 959
char133 = char52;
status = char133 == char52;
cout << "test 959 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 960
char173 -= 47394;
size = char173.Size();
cout << "test 960 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 961
char106 -= 11464;
size = char106.Size();
cout << "test 961 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 962
status = char72[55590];
cout << "test 962 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 963
char78 = char142;
status = char78 == char142;
cout << "test 963 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 964
char93 -= 22794;
size = char93.Size();
cout << "test 964 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 965
char63 -= 39888;
size = char63.Size();
cout << "test 965 - out: " << size << " - ref: 6 - match: " << (size == 6) << endl;
 
//test 966
char17 += 14798;
size = char17.Size();
cout << "test 966 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 967
status = char143 == char87;
cout << "test 967 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 968
status = char48[29810];
cout << "test 968 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 969
char131 -= 23640;
size = char131.Size();
cout << "test 969 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 970
status = char96[14838];
cout << "test 970 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 971
status = char1[62124];
cout << "test 971 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 972
char20 = char38;
status = char20 == char38;
cout << "test 972 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 973
char125 += 46688;
size = char125.Size();
cout << "test 973 - out: " << size << " - ref: 4 - match: " << (size == 4) << endl;
 
//test 974
status = char52 == char143;
cout << "test 974 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 975
char181 -= 15476;
size = char181.Size();
cout << "test 975 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 976
status = char87 == char45;
cout << "test 976 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 977
char148 += 29160;
size = char148.Size();
cout << "test 977 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 978
char107 -= 14534;
size = char107.Size();
cout << "test 978 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 979
char166 -= 56252;
size = char166.Size();
cout << "test 979 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 980
char41 += 48042;
size = char41.Size();
cout << "test 980 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 981
char14 += 55024;
size = char14.Size();
cout << "test 981 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 982
char3 -= 34670;
size = char3.Size();
cout << "test 982 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 983
status = char105[55428];
cout << "test 983 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 984
char148 += 21778;
size = char148.Size();
cout << "test 984 - out: " << size << " - ref: 4 - match: " << (size == 4) << endl;
 
//test 985
status = char15[44408];
cout << "test 985 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 986
char151 -= 5526;
size = char151.Size();
cout << "test 986 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 987
char51 += 47820;
size = char51.Size();
cout << "test 987 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 988
char12 -= 12794;
size = char12.Size();
cout << "test 988 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 989
CDegChar char190 = char157;
status = char190 == char157;
cout << "test 989 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 990
char45 -= 26236;
size = char45.Size();
cout << "test 990 - out: " << size << " - ref: 0 - match: " << (size == 0) << endl;
 
//test 991
status = char151 == char159;
cout << "test 991 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 992
char103 -= 2992;
size = char103.Size();
cout << "test 992 - out: " << size << " - ref: 3 - match: " << (size == 3) << endl;
 
//test 993
status = char186[54062];
cout << "test 993 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 994
char58 -= 26436;
size = char58.Size();
cout << "test 994 - out: " << size << " - ref: 1 - match: " << (size == 1) << endl;
 
//test 995
char12 += 17106;
size = char12.Size();
cout << "test 995 - out: " << size << " - ref: 2 - match: " << (size == 2) << endl;
 
//test 996
status = char155[50744];
cout << "test 996 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
 
//test 997
char159 = char111;
status = char159 == char111;
cout << "test 997 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 998
char31 = char10;
status = char31 == char10;
cout << "test 998 - out: " << status << " - ref: 1 - match: " << status << endl;
 
//test 999
status = char152[46010];
cout << "test 999 - out: " << status << " - ref: 0 - match: " << (status == false) << endl;
  return 0;
 }
#endif /* __PROGTEST__ */

