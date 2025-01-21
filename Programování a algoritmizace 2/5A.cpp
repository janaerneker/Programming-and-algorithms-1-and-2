#ifndef __PROGTEST__
#include <cctype>
#include <iostream>
#include <iomanip>
#include <set>
#include <list>
#include <map>
#include <vector>
#include <queue>
#include <string>
using namespace std;
#endif /* __PROGTEST__ */

template <typename _Type, typename _Comparator = std::equal_to<typename _Type::value_type> >
class CSearch
 {

public:

    // default constructor
    CSearch ( void ) : cmp ( _Comparator () ) {}

    // constructor with comparator parameter
    CSearch ( const _Comparator & cmp) : cmp ( cmp ) {}
    
    //Metoda prida dalsi sekvenci (needle) -> identifikace pomoci id.
    void Add ( int id, const _Type & needle );

    //Metoda vrati mnozinu vsech drive zadanych sekvenci, ktere byly v prohledavane sekvenci hayHeap nalezene. 
    set<int> Search ( const _Type & hayHeap ) const;


private:

    // empty copy constructor
    CSearch ( const CSearch <_Type, _Comparator> & a ){}

    // empty operator =
    CSearch <_Type, _Comparator> operator = ( const CSearch <_Type, _Comparator> & a ) {}

    map<int, _Type> data;
    _Comparator cmp;
 };

template <typename _Type, typename _Comparator>
void CSearch<_Type, _Comparator>::Add ( int id, const _Type & needle )
{
    data[id]=needle;
}

template <typename _Type, typename _Comparator>
set <int> CSearch<_Type, _Comparator>::Search ( const _Type & hayHeap ) const
{
    set<int> foundSequence;
    

    for(typename map<int, _Type>::const_iterator it=data.begin(); it!=data.end(); it++)
    {   
        for(typename _Type::const_iterator hayIt=hayHeap.begin(); hayIt!=hayHeap.end(); hayIt++)
        {       
            typename _Type::const_iterator dataIt=it->second.begin();

            if(cmp(*dataIt, *hayIt))
            {   
                typename _Type::const_iterator newHayIt=hayIt;
                while(dataIt!=it->second.end())
                {
                    if(!cmp(*dataIt, *newHayIt))
                    {
                        break;
                    }
                    dataIt++;
                    newHayIt++;
                }                    
                if(dataIt==it->second.end())
                {
                    foundSequence.insert(it->first);
                }
            }  
        }
    }
    
    return foundSequence;
}



#ifndef __PROGTEST__

class CharComparator
 {
   public:
               CharComparator ( bool caseSensitive = true ) 
                : m_CaseSensitive ( caseSensitive ) { }
    bool       operator () ( const char & a, const char & b ) const 
                { return m_CaseSensitive ? a == b : toupper (a) == toupper (b); }
   private:
    bool       m_CaseSensitive;  
 };

bool upperCaseCompare ( const char & a, const char & b )
 {
   return toupper ( a ) == toupper ( b );
 }

void printSet ( const set<int> & s )
 {
   for ( set<int>::const_iterator it = s . begin (); it != s . end (); ++it )
    cout << ( it == s . begin () ? "" : ", " ) << *it;
   cout << endl; 
 }

template <typename _T, int _CNT>
vector<_T> makeVector ( const _T (&data)[_CNT] )
 {
   return vector<_T> ( data, data + _CNT );
 } 

 int main ( int argc, char * argv [] )
 {
   
    return 0;
 }
#endif /* __PROGTEST__ */