#ifndef __PROGTEST__
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <algorithm>
 
 
using namespace std;
   
class CTimeStamp
 {
   public:
      CTimeStamp ( int       year,
                   int       month,
                   int       day,
                   int       hour,
                   int       minute,
                   double    sec );
 
    int Compare ( const CTimeStamp & x ) const;
    friend ostream & operator << ( ostream     & os, const CTimeStamp & x );
 
 
   private:
 
    int year;
    int month;
    int day;
    int hour;
    int minute;
    double sec;
 
 };
 
CTimeStamp::CTimeStamp(int year, int month, int day, int hour, int minute, double sec )
: year(year), month(month), day(day), hour(hour), minute(minute), sec(sec) {}
 
int CTimeStamp::Compare ( const CTimeStamp & x ) const
 {
    if(year < x.year){
        return -1;
    }else if (year > x.year){
        return 1;
    }else{
        if(month < x.month){
            return -1;
        }else if (month > x.month){
            return 1;
        }else{
            if(day < x.day){
                return -1;
            }else if (day > x.day){
                return 1;
            }else{
                if(hour < x.hour){
                    return -1;
                }else if (hour > x.hour){
                    return 1;
                }else{
                    if(minute < x.minute){
                        return -1;
                    }else if (minute > x.minute){
                        return 1;
                    }else{
                        if(month < x.month){
                            return -1;
                        }else if (month > x.month){
                            return 1;
                        }else{
                            return 0;
                        }
                    }
                }          
            }
        }
    }
 }
 
ostream & operator << ( ostream & os, const CTimeStamp & x )
{
  //YYYY-MM-DD HH24:MI:SS.UUU
  os << x.year << "-" << x.month << "-" << x.day << " " << x.hour << ":" << x.minute << ":" << x.sec << " ";
  return os;
}
 
class CMail
 {
   public:
         CMail  ( const CTimeStamp & timeStamp,
                  const string & from,
                  const string & to );
    int CompareTimeStamp ( const CTimeStamp & x ) const;
    int CompareByTimeStamp ( const CMail & x ) const;
    const string & From ( void ) const;
    const string & To ( void ) const;
    const CTimeStamp & TimeStamp ( void ) const;
    friend ostream & operator << ( ostream & os, const CMail & x );
   
   private:
    CTimeStamp timeStamp;
    string from;
    string to;
 };
 
CMail::CMail  ( const CTimeStamp & timeStamp, const string & from, const string & to )
: timeStamp(timeStamp), from(from), to(to) {}
 
 
int CMail::CompareTimeStamp ( const CTimeStamp & x ) const
{
    return timeStamp.Compare(x);
}
 
int CMail::CompareByTimeStamp ( const CMail & x ) const
{
  return timeStamp.Compare(x.timeStamp);
}
 
const string & CMail::From ( void ) const
{
    return from;
}
 
const string & CMail::To ( void ) const
{
    return to;
}
 
const CTimeStamp & CMail::TimeStamp ( void ) const
{
    return timeStamp;
}
 
ostream & operator << ( ostream & os, const CMail & x )
{
    os << x.timeStamp << x.from << " -> " << x.to << endl;
    return os;
 
}
 
 
#endif /* __PROGTEST__ */  
 
class CMailLog      
 {
   public:
    // default constructor
    CMailLog();
    // destructor
    ~CMailLog();
    int ParseLog( istream & in );
    list<CMail> ListMail( const CTimeStamp & from, const CTimeStamp & to ) const;
    set<string> ActiveUsers ( const CTimeStamp & from, const CTimeStamp & to ) const;
   
   private:
    vector<CMail*> EMails;
    int countOfEMails;
 
 
 };
 
bool Compare( const CMail * x, const CMail * y )
{
    if((*x) . CompareByTimeStamp(*y) < 0)
    {
        return true;
    }
 
    return false;
}
 
CMailLog::CMailLog()
{
    countOfEMails=0;
}
 
 
int CMailLog::ParseLog( istream & in )
{
    int countOfMails=0;
    string tmpLine;
    map<string, string> Mfrom;
 
    string tmpMonth, tmpString;
    char c;
 
    string mailID;
    int month;
    int day;
    int year;
    int hour;
    int minute;
    double sec;
    string relayName;
    string to;
    string from;
 
    while(getline(in, tmpLine))
    {
 
          stringstream tmpStream;
 
 
        //cout << "tmpLine: " << tmpLine << endl;
        tmpStream << tmpLine;
 
        //mesic
        getline(tmpStream, tmpMonth, ' ');  
        //cout << "tmpMonth: " << tmpMonth << endl;
        stringstream tmpMonthStream;
        tmpMonthStream << tmpMonth;
        c = tmpMonthStream.get();
        //prevadim mesic na int...
        switch(c)
          {
              case 'J':
                  //cout << "jsem J." <<  endl;
                  c = tmpMonthStream.get();
                  if(c=='a')
                  {
                    month=1;
                    break;
                  }
                  else
                  {
                    c = tmpMonthStream.get();
                    if (c=='n')
                    {
                      month=6;
                    }
                    else
                    {
                      month=7;
                    }
                  }
                  break;
              case 'F':
                    month=2;
                  break;
              case 'M':
                    c = tmpMonthStream.get();
                    //cout << "c: " << c << endl;
                    c = tmpMonthStream.get();
                    //cout << "c: " << c << endl;
                    if (c=='r')
                    {
                      month=3;
                    }
                    else
                    {
                      month=5;
                    }
                  break;
              case 'A':
                    c = tmpMonthStream.get();
                    if (c=='p')
                    {
                      month=4;
                    }
                    else
                    {
                      month=8;
                    }
                  break;
              case 'S':
                    month=9;
                  break;
              case 'O':
                    month=10;
                  break;
              case 'N':
                    month=11;
                  break;
              case 'D':
                    month=12;
                  break;
          }
        //cout << "month: " << month << endl;
 
        //den
        getline(tmpStream, tmpString, ' ');  
        day = atoi(tmpString.c_str());
        //cout << "day: " << day << endl;
 
        //rok
        getline(tmpStream, tmpString, ' ');
        year = atoi(tmpString.c_str());
        //cout << "year: " << year << endl;
 
        //cas
        getline(tmpStream, tmpString, ' ');
        stringstream tmpTime;
        tmpTime  << tmpString;
          //hodina
          getline(tmpTime, tmpString, ':');
          hour = atoi(tmpString.c_str());
          //cout << "hour: " << hour << endl;
          //minuty
          getline(tmpTime, tmpString, ':');
          minute = atoi(tmpString.c_str());
          //cout << "minute: " << minute << endl;
          //sec
          getline(tmpTime, tmpString, ':');
          sec = atof(tmpString.c_str());
          //cout << "sec: " << sec << endl;
        tmpTime.clear();
 
        CTimeStamp tmpStamp(year, month, day, hour, minute, sec);
       
        //relay
        getline(tmpStream, relayName, ' ');
        //cout << "relayName: " << relayName << endl;
 
        //mailID
        getline(tmpStream, tmpString, ' ');
        stringstream tmpID;
        tmpID << tmpString;
          getline(tmpID, mailID, ':');
          //cout << "mailID: " << mailID << endl;
        tmpID.clear();
 
        //message
        getline(tmpStream, tmpString, ' ');
        //cout << "tmpString: " << tmpString << endl;
        stringstream tmpMessage;
        tmpMessage << tmpString;
          c = tmpMessage.get();
          map<string, string>::iterator it;
          switch(c)
          {
              case 'f':
                  //cout << "jsem f." <<  endl;
                  getline(tmpMessage, tmpString, '=');
                  getline(tmpMessage, from);
                  //cout << "from: " << from << endl;
 
                  //ukladam do from
                  Mfrom[mailID] = from;
                 
 
                  break;
              case 't':
                  //cout << "jsem t." <<  endl;
                  getline(tmpMessage, tmpString, '=');
                  getline(tmpMessage, to);
                  //cout << "to: " << to << endl;
 
                  //ukladam do CMail
 
                 
                  it = Mfrom.find(mailID);
 
                  if(it != Mfrom.end())
                  {
                    CMail * tmp = new CMail ( tmpStamp, it -> second, to );
                    EMails.push_back ( tmp );
 
                    countOfMails++;
                    countOfEMails++;
                  }
                 
                  break;
              case 'm':
                  break;
          }
 
    }
 
  /*map<string,string>::iterator it = Mfrom.begin();
  cout << "mymap contains:\n";
  for (it=Mfrom.begin(); it!=Mfrom.end(); it++)
    cout << it->first << " => " << it->second << '\n';*/
 
  /*for (int i = 0; i < countOfEMails; i++)
  {
      cout << "timeStamp: " << EMails[i]->TimeStamp();
      cout << "from: " << EMails[i]->From() << endl;
      cout << "to: " << EMails[i]->To() << endl;
      cout << endl;
  }*/
 
    sort(EMails.begin(), EMails.end(), Compare);
   
    return countOfMails;
}
 
list<CMail> CMailLog::ListMail( const CTimeStamp & from, const CTimeStamp & to ) const
{
    list<CMail> mails;
 
    for (int i = 0; i < countOfEMails; i++)
    {
        if(from.Compare(EMails[i]->TimeStamp())<=0 && to.Compare(EMails[i]->TimeStamp())>=0)
        {
            mails.push_back(CMail(EMails[i]->TimeStamp(), EMails[i]->From(), EMails[i]->To()));
        }
    }
 
 
    return mails;
}
 
set<string> CMailLog::ActiveUsers ( const CTimeStamp & from, const CTimeStamp & to ) const
{
  set<string> users;
    for (int i = 0; i < countOfEMails; i++)
    {
        if(from.Compare(EMails[i]->TimeStamp())<=0 && to.Compare(EMails[i]->TimeStamp())>=0)
        {
            users.insert(EMails[i]->From());
            users.insert(EMails[i]->To());
        }
    }
 
  return users;
}
 
 
CMailLog::~CMailLog()
{
    for (vector<CMail*>::iterator it = EMails.begin() ; it != EMails.end(); it++)
    {
        delete *it;
    }
}
#ifndef __PROGTEST__
 
 void showMail ( const list<CMail> & l )
 {
   for ( list<CMail>::const_iterator it = l . begin (); it != l . end (); ++it )
    cout << *it;
 }
void showUsers ( const set<string> & s )
 {
   for ( set<string>::const_iterator it = s . begin (); it != s . end (); ++it )
    cout << *it << endl;
 }
 
int main ( int argc, char * argv [] )
 {
    
 
    return 0;
 }
#endif /* __PROGTEST__ */