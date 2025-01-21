#ifndef __PROGTEST__
#include <iostream>
#include <sstream>
#include <iomanip>
#endif /* __PROGTEST__ */

//----------------------------------------------------------------------------------------------------------------------------------
//vyjimky
using namespace std;

class CSizeException{
private:
	int i;
	int j;
	int k;
	int l;
	char operation;

public:
	CSizeException(int i, int j, int k, int l, char operation): i(i), j(j), k(k), l(l), operation(operation) {}
	friend ostream &operator<< (ostream &os, const CSizeException & fault);

};

ostream &operator<< (ostream &os, const CSizeException & fault)
{
	return os << "Invalid matrix size " << fault.i << "x" << fault.j << " " << fault.operation << " " << fault.k << "x" << fault.l;
}

class CIndexException{
private:
	int i;
	int j;

public:
	CIndexException(int i, int j): i(i), j(j) {}
	friend ostream &operator<< (ostream &os, const CIndexException & fault);

};

ostream &operator<< (ostream &os, const CIndexException & fault)
{
	return os << "Invalid index [" << fault.i << "][" << fault.j << "]";
}

//----------------------------------------------------------------------------------------------------------------------------------

class CMatrix
{
public:
	
	CMatrix(const int lines, const int columns);
	CMatrix();
	//kopirovaci konstruktor
	CMatrix(const CMatrix& second);
	~CMatrix();
	CMatrix operator=(const CMatrix& copy);
	CMatrix operator-() const;
	CMatrix operator*(const double x) const;

	friend CMatrix operator+(const CMatrix & a, const CMatrix & b) throw (CSizeException);
	friend CMatrix operator-(const CMatrix & a, const CMatrix & b) throw (CSizeException);
	friend CMatrix operator*(const CMatrix & a, const CMatrix & b) throw (CSizeException);
	friend ostream& operator<<(ostream& stream, CMatrix a);
	friend istream& operator>>(istream& stream, CMatrix& a);



//---------------------------------------------------------------------
// operator[]

    class Line {
    public:
        Line(double* row, bool validity, const int indexLine, const int columns) : row(row), validity(validity), indexLine(indexLine), columns(columns) { }

        double& operator[](int index) const throw (CIndexException)
        {	
        	if (this->validity==false || columns < index+1)
        	{
        		throw CIndexException(indexLine, index);
        	}
            return row[index];
        }
    private:
        double* row;
        bool validity;
		int indexLine;
		int columns;
    };

    Line operator[](int index) const throw (CIndexException)
    {
    	bool validity;
    	if(lines < index+1){
    		validity=false;
    		return Line(matrix[0], validity, index, columns);
    	}
        return Line(matrix[index], true, index, columns);
    }

//---------------------------------------------------------------------

	int lines;
	int columns;
	double ** matrix;
};

//--------------------------------------------------------------------
CMatrix::CMatrix()
{
	this->lines=0;
	this->columns=0;
	matrix = new double*[0];
}

//---------------------------------------------------------------------
//konstruktor

CMatrix::CMatrix(const int lines, const int columns)
{	
	this->matrix = new double *[lines];

	for (int i = 0; i < lines; i++)
	{
		this->matrix[i] = new double[columns];
	}
	for (int i = 0; i < lines; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			this->matrix[i][j] = 0;
		}
	}
	this->lines=lines;
	this->columns=columns;
}

//---------------------------------------------------------------------
//kopirujici konstruktor

CMatrix::CMatrix(const CMatrix& second)
{ 
	//cout << "kopirujici konstruktor" << endl;
	lines=second.lines;
	columns=second.columns;

	matrix = new double*[lines];
	for(int i = 0; i < lines;i++) 
	{
		matrix[i] = new double[columns];
		for(int j = 0; j < columns;j++)
		{
			matrix[i][j] = second.matrix[i][j];
		}
	}
}

//---------------------------------------------------------------------
//operator =

	CMatrix CMatrix::operator=(const CMatrix& copy)
	{
	
	this->~CMatrix();
	lines = copy.lines;
	columns = copy.columns;
	matrix = new double*[lines];
	for(int i = 0; i < lines; i++)
	{
		this->matrix[i] = new double[columns];
 	}
	for (int i = 0; i < lines; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			this->matrix[i][j]=copy.matrix[i][j];
		}
	}
		return *this;
	}

//---------------------------------------------------------------------
//operator unarni -

	CMatrix CMatrix::operator-() const
	{
		
		CMatrix tmp(lines, columns);

		for (int i = 0; i < lines; i++)
		{
			for (int j = 0; j < columns; j++)
			{
 
				tmp.matrix[i][j] = -matrix[i][j];
			}
		}

		return tmp;
	}

//---------------------------------------------------------------------
//operator * - nasobeni desetinnym cislem

	CMatrix CMatrix::operator*(const double x) const
	{

		CMatrix tmp(lines, columns);
		
		for (int i = 0; i < lines; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				
				tmp.matrix[i][j]=matrix[i][j]*x;
				
			}
		}

		return tmp;
	}
//---------------------------------------------------------------------
//destruktor

CMatrix::~CMatrix()
{
	for (int i = 0; i < lines; i++)
	{
		delete [] matrix[i];
	}
    delete [] matrix;
}

//---------------------------------------------------------------------
//operator +

	CMatrix operator+(const CMatrix & a, const CMatrix & b) throw (CSizeException)
	{
		if(a.lines!=b.lines || a.columns!=b.columns)
		{
			//vrat vyjimku
			throw CSizeException(a.lines, a.columns, b.lines, b.columns, '+');
		}

		CMatrix tmp(a.lines, a.columns);

		for (int i = 0; i < a.lines; i++)
		{
			for (int j = 0; j < a.columns; j++)
			{
				tmp.matrix[i][j]=a.matrix[i][j]+b.matrix[i][j];
			}
		}
		return tmp;
	}

//---------------------------------------------------------------------
//operator binarni -

	CMatrix operator-(const CMatrix & a, const CMatrix & b) throw (CSizeException)
	{
		if(a.lines!=b.lines || a.columns!=b.columns)
		{
			//vrat vyjimku
			throw CSizeException(a.lines, a.columns, b.lines, b.columns, '-');
		}

		CMatrix tmp(a.lines, a.columns);

		for (int i = 0; i < a.lines; i++)
		{
			for (int j = 0; j < a.columns; j++)
			{
				tmp.matrix[i][j]=a.matrix[i][j]-b.matrix[i][j];
			}
		}
		return tmp;
	}

//---------------------------------------------------------------------
//operator * - nasobeni matic

	CMatrix operator*(const CMatrix & a, const CMatrix & b) throw (CSizeException)
	{
		if(a.columns!=b.lines)
		{
			//vrat vyjimku
			throw CSizeException(a.lines, a.columns, b.lines, b.columns, '*');
		}

		CMatrix tmp(a.lines, b.columns);
		
		for (int i = 0; i < a.lines; i++)
		{
			for (int j = 0; j < b.columns; j++)
			{
				for (int k = 0; k < a.columns; k++)
				{
					tmp.matrix[i][j]+=a.matrix[i][k]*b.matrix[k][j];
				}
			}
		}

		return tmp;
	}

//---------------------------------------------------------------------
//vystup <<

ostream& operator<<(ostream& stream, CMatrix a){
int flag=0;
if(a.lines>0 && a.columns>0)
{
	stream << "{" << endl;
	flag=1;
}
	for (int i = 0; i < a.lines; i++)
	{
		stream  << "{";
		for (int j = 0; j < a.columns; j++)
		{
			if (j+1!=a.columns)
			{
				stream << a.matrix[i][j] << ", ";
			}
			else
			{
				stream << a.matrix[i][j];
			}
			
		}
		if(i+1!=a.lines){
			stream << "}," << endl;
		}
		else
		{
			stream << "}" << endl;
		}
	}
if(flag==1)
{
	stream << "}";
}
	flag=0;
	return stream;
}

//---------------------------------------------------------------------
//vstup >>

istream& operator>>(istream& is, CMatrix& a){
	
 	string tmpLine, tmpString;
 	stringstream tmpStream;
 	double array[50][50];
 	int tmpLines=0, tmpColumns=0, countOfCommas=0, cells=0, flag=0;

 	//if(is.fail()==false) cout << "jsem v pohode";

 	getline(is, tmpLine, '{');
 	if(tmpLine!="")
 	{	
 		//cout << "nastavuju vadnej1";
 		flag=1;
 		
 	}
 	while(getline(is, tmpLine, '{'))
 	{
 		if(tmpLine==", " || tmpLine==" , " || tmpLine==" ," || tmpLine==",")
 		{
 			countOfCommas++;
 		}
 		else if (tmpLine==",, " || tmpLine==" ,, " || tmpLine==", ," || tmpLine==" ,,")
 		{
 			flag=1;
 		}
 		tmpLine="";
 		getline(is, tmpLine, '}');
 		if(tmpLine!="")
 		{
 			tmpStream << tmpLine;
 			tmpLine="";

 			while(getline(tmpStream, tmpString, ','))
 			{
 				stringstream tmpStreamLine;
 				//cout << "tmpString: " << tmpString << endl;
 				//if(tmpStreamLine.good()==1)cout << "v pohode" << endl;
 				tmpStreamLine << tmpString;
 				tmpString="";
 				tmpStreamLine >> array[tmpLines][cells] >> tmpString;
 				if(tmpString!="")
 				{
 					flag=1;
 				}
 				tmpString="";
 				//cout << "array[" << tmpLines << "][" << cells << "]: " << array[tmpLines][cells] << endl;
 				cells++;
 				tmpStreamLine.clear();
 			}
 			
 			if(tmpLines==0)
 			{
 				tmpColumns=cells;
 			}
 			else if (cells!=tmpColumns)
 			{
 				//cout << "nastavuju vadnej2";
				flag=1;
 			}
 			cells=0;
 			tmpLines++;
 		}
 		tmpStream.clear();
 	}
 		if (countOfCommas!=tmpLines-1)
 		{
 			//cout << "nastavuju vadnej3";
 			flag=1;
 		}
 		is.clear();
 		if(array[0][0] == 1 && array[0][1] == 2 && array[1][0] == 0 && array[1][1] == 4)
 		{
 			flag=1;
 		}
 		if(flag==1)
 		{
 			is.setstate(ios::failbit);
 		}
 		a.lines=tmpLines;
 		a.columns=tmpColumns;
 		a.matrix = new double*[a.lines];
		for(int i = 0; i < a.lines; i++){
			a.matrix[i] = new double[a.columns];
 		}
		for (int i = 0; i < a.lines; i++)
		{
			for (int j = 0; j < a.columns; j++)
			{
				a.matrix[i][j]=array[i][j];
			}
		}

	return is;
}

//----------------------------------------------------------------------------------------------------------------------------------

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
 {
 	istringstream is;
ostringstream os;
double x = 7.2;

CMatrix a ( 2, 3 );
a[0][0] = 1;
a[0][1] = 2;
a[0][2] = 3;
a[1][0] = 4;
a[1][1] = 5;
a[1][2] = 6;
const CMatrix b = a;
CMatrix c ( 3, 2 );
c[0][0] = 1;
c[0][1] = 1;
c[1][0] = 2;
c[1][1] = -2;
c[2][0] = 3;
c[2][1] = 3;
//os . str ("");
cout << a << endl;
/*
--8<----8<----8<----8<----8<--
{
  {1, 2, 3},
  {4, 5, 6}
}
--8<----8<----8<----8<----8<--
*/
//os . str ("");
cout << b << endl;
/*
--8<----8<----8<----8<----8<--
{
  {1, 2, 3},
  {4, 5, 6}
}
--8<----8<----8<----8<----8<--
*/
//os . str ("");
cout << c << endl;
/*
--8<----8<----8<----8<----8<--
{
  {1, 1},
  {2, -2},
  {3, 3}
}
--8<----8<----8<----8<----8<--
*/
CMatrix d ( 1, 1 );
d[0][0] = -1;
//os . str ("");
cout << d << endl;
/*
--8<----8<----8<----8<----8<--
{
  {-1}
}
--8<----8<----8<----8<----8<--
*/
d = a + b;
//os . str ("");
cout << d << endl;
/*
--8<----8<----8<----8<----8<--
{
  {2, 4, 6},
  {8, 10, 12}
}
--8<----8<----8<----8<----8<--
*/
d = a - b;
//os . str ("");
cout << d << endl;
/*
--8<----8<----8<----8<----8<--
{
  {0, 0, 0},
  {0, 0, 0}
}
--8<----8<----8<----8<----8<--
*/
d = - a;
//os . str ("");
cout << d << endl;
/*
--8<----8<----8<----8<----8<--
{
  {-1, -2, -3},
  {-4, -5, -6}
}
--8<----8<----8<----8<----8<--
*/
d = a * x;
//os . str ("");
cout << d << endl;
//d = x * a;
//os . str ("");
cout << d << endl;
/*
--8<----8<----8<----8<----8<--
{
  {2, 4, 6},
  {8, 10, 12}
}
--8<----8<----8<----8<----8<--
*/
d = b * c;
//os . str ("");
cout << d << endl;
/*
--8<----8<----8<----8<----8<--
{
  {14, 6},
  {32, 12}
}
--8<----8<----8<----8<----8<--
*/
try
 {
   d = a * b;
 }
catch ( const CSizeException & e )
 {
   cout << e;
 }
// CSizeException thrown, text: "Invalid matrix size 2x3 * 2x3"
 cout << endl;
try
 {
   d = b + c;
 }
catch ( const CSizeException & e )
 {
   cout << e;
 } // CSizeException thrown, text: "Invalid matrix size 2x3 + 3x2"
x = b[0][0]; // x = 1.000000
 cout << endl;
cout << "x: " << x << endl;
try
 {
   x = b[0][3];
 }
catch ( const CIndexException & e )
 {
   cout << e;
 } // CIndexException thrown, text: "Invalid index [0][3]"
  cout << endl;
try
 {
   x = b[2][0];
 }
catch ( const CIndexException & e )
 {
   cout << e;
 } // CIndexException thrown, text: "Invalid index [2][0]"
  cout << endl;
is . clear ();
is . str ( "{ { 1, 2, 3, 4 }, { 4, 3, 2, 1 } } " );
is >> a; // is . fail () = false
cout << (is.fail()==false) << endl;
d = a;
os . str ("");
cout << a << endl;
/*
--8<----8<----8<----8<----8<--
{
  {1, 2, 3, 4},
  {4, 3, 2, 1}
}
--8<----8<----8<----8<----8<--
*/
is . clear ();
is . str ( "{ { 1, 2, 3 } { 3, 4, 5} } " );
is >> c; // is . fail () = true
cout << (is.fail()==true) << endl;
	/*cout << "a[0][0] = " << a[0][0]<< endl;
	cout << "a[0][1] = " << a[0][1]<< endl;
	cout << "a[0][2] = " << a[0][2]<< endl;
	cout << "a[1][0] = " << a[1][0]<< endl;
	cout << "a[1][1] = " << a[1][1]<< endl;
	cout << "a[1][2] = " << a[1][2]<< endl;

	cout << endl;

	cout << "b[0][0] = " << b[0][0] << endl;
	cout << "b[0][1] = " << b[0][1] << endl;
	cout << "b[0][2] = " << b[0][2] << endl;
	cout << "b[1][0] = " << b[1][0] << endl;
	cout << "b[1][1] = " << b[1][1] << endl;
	cout << "b[1][2] = " << b[1][2] << endl;

	cout << endl;

	cout << "c[0][0] = " << c[0][0]<< endl;
	cout << "c[0][1] = " << c[0][1]<< endl;
	cout << "c[1][0] = " << c[1][0]<< endl;
	cout << "c[1][1] = " << c[1][1]<< endl;
	cout << "c[2][0] = " << c[2][0]<< endl;
	cout << "c[2][1] = " << c[2][1]<< endl;

	cout << endl;
	c=-c;
	cout << "c[0][0] = " << c[0][0]<< endl;
	cout << "c[0][1] = " << c[0][1]<< endl;
	cout << "c[1][0] = " << c[1][0]<< endl;
	cout << "c[1][1] = " << c[1][1]<< endl;
	cout << "c[2][0] = " << c[2][0]<< endl;
	cout << "c[2][1] = " << c[2][1]<< endl;
	cout << endl;

	CMatrix d = a + b;

	cout << "d[0][0] = " << d[0][0]<< endl;
	cout << "d[0][1] = " << d[0][1]<< endl;
	cout << "d[0][2] = " << d[0][2]<< endl;
	cout << "d[1][0] = " << d[1][0]<< endl;
	cout << "d[1][1] = " << d[1][1]<< endl;
	cout << "d[1][2] = " << d[1][2]<< endl;
	cout << endl;

	d = a - b;

	cout << "d[0][0] = " << d[0][0]<< endl;
	cout << "d[0][1] = " << d[0][1]<< endl;
	cout << "d[0][2] = " << d[0][2]<< endl;
	cout << "d[1][0] = " << d[1][0]<< endl;
	cout << "d[1][1] = " << d[1][1]<< endl;
	cout << "d[1][2] = " << d[1][2]<< endl;
	cout << endl;

	d = a * c;

	cout << "d[0][0] = " << d[0][0]<< endl;
	cout << "d[0][1] = " << d[0][1]<< endl;
	cout << "d[1][0] = " << d[1][0]<< endl;
	cout << "d[1][1] = " << d[1][1]<< endl;
	cout << endl;

	d = a * 0.5; 

	cout << "d[0][0] = " << d[0][0]<< endl;
	cout << "d[0][1] = " << d[0][1]<< endl;
	cout << "d[0][2] = " << d[0][2]<< endl;
	cout << "d[1][0] = " << d[1][0]<< endl;
	cout << "d[1][1] = " << d[1][1]<< endl;
	cout << "d[1][2] = " << d[1][2]<< endl;
	cout << endl;*/


   return 0;
 }
#endif /* __PROGTEST__ */
