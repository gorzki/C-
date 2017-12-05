#ifndef __CMATIRX_H__
#define __CMATRIX_H__
#include <math.h>
#include <fstream>
using namespace std;

class OutOfMem{};
class IndexOutOfRange{};
class WrongDim{};

class CMatrix{
private:

	struct rcmatrix;
	rcmatrix* block;

public:
	class Cref;

	CMatrix();
	CMatrix(const CMatrix& cm);
	CMatrix(fstream& fs);
	CMatrix(unsigned int nrows, unsigned int ncols, double var);
	CMatrix(unsigned int nrows, unsigned int ncols, double var1, double var2);
	void write(unsigned int i, double* c);
	double* read(unsigned int i) const;
	double* operator[](unsigned int i )const;
	CMatrix& operator=(const CMatrix& asOp);
	CMatrix& operator=(double** co);
	~CMatrix();
	friend ostream & operator << (ostream & s, const CMatrix & matrix);
	friend ostream & operator << (ostream & s, const CMatrix::Cref& s1);
	friend CMatrix operator* (const CMatrix&, const CMatrix&);

	Cref operator[](unsigned int i);

};


struct CMatrix::rcmatrix
{
	double** data;
	unsigned int rows;
	unsigned int cols;
	unsigned int n;

	rcmatrix(){
		this->data=NULL;
		this->cols=0;
		this->rows=0;
		this->n=0;
	}

	rcmatrix(fstream& fs){
		fs >> this->rows;
		fs >> this->cols;

		try
		{
			this->data = new double*[this->rows];
			for(unsigned int i=0;i<this->rows;i++)
			this->data[i]=new double[this->cols];
		}
		catch(...)
		{
			throw OutOfMem();
		}

		for(unsigned int i=0;i<this->rows;i++)
		for(unsigned int j=0;j<this->cols;j++){
			fs >> this->data[i][j];
		}
		this->n=1;
	}

	rcmatrix(unsigned int nrows, unsigned int ncols, double var){
		try
		{
			this->data = new double*[nrows];
			for(unsigned int i=0;i<nrows;i++)
			this->data[i]=new double[ncols];
		}
		catch(...){
			throw OutOfMem();
		}

		for(unsigned int i=0;i<nrows;i++)
		for(unsigned int j=0;j<ncols;j++)
		if(i==j)this->data[i][j]=var;
		else this->data[i][j]=0.0;

		this->rows=nrows;
		this->cols=ncols;
		this->n=1;
	}

	rcmatrix(unsigned int nrows, unsigned int ncols, double var1, double var2){
		try
		{
			this->data = new double*[nrows];
			for(unsigned int i=0;i<nrows;i++)
			this->data[i]=new double[ncols];
		}
		catch(...){
			throw OutOfMem();
		}

		for(unsigned int i=0;i<nrows;i++)
		for(unsigned int j=0;j<ncols;j++)
		if(i==j)this->data[i][j]=var1;
		else this->data[i][j]=var2;

		this->rows=nrows;
		this->cols=ncols;
		this->n=1;
	};

	rcmatrix(unsigned int nrows, unsigned int ncols,double** lol){
		this->rows=nrows;
		this->cols=ncols;
		this->n=1;
		this->data = lol;
	}
	rcmatrix(const rcmatrix& lol){

		try
		{
			this->data = new double*[lol.rows];
			for(unsigned int i=0;i<lol.rows;i++)
			this->data[i]=new double[lol.cols];
		}
		catch(...){
			throw OutOfMem();
		}

		for(unsigned int i=0;i<lol.rows;i++)
		for(unsigned int j=0;j<lol.cols;j++)
		this->data[i][j]=lol.data[i][j];


		this->rows=lol.rows;
		this->cols=lol.cols;
		this->n=1;

	}

	~rcmatrix(){
		for(unsigned int i=0;i<this->rows;i++)
		delete[] data[i];
		delete[] data;
	}

	rcmatrix* detach(){
		if(n==1)
		return this;
		rcmatrix* t=new rcmatrix(*this);
		n--;
		return t;
	}

	void assign(double** p){
		data = p;
	}
};

CMatrix::CMatrix(fstream& fs){
	block = new rcmatrix(fs);
}

CMatrix::CMatrix(const CMatrix& cm){
	cm.block->n++;
	block = cm.block;
}

CMatrix::~CMatrix(){
	if(--block->n==0)
	delete block;
}

CMatrix::CMatrix(){
	block = new rcmatrix();
}

CMatrix::CMatrix(unsigned int nrows, unsigned int ncols, double var){
	block = new rcmatrix(nrows,ncols,var);
}

CMatrix::CMatrix(unsigned int nrows, unsigned int ncols, double var1, double var2){
	block = new rcmatrix(nrows,ncols,var1,var2);
}

CMatrix& CMatrix::operator = (const CMatrix& asOp){

	asOp.block->n++;
	if(--block->n == 0)
	delete block;

	block=asOp.block;
	return *this;
}

CMatrix & CMatrix::operator=(double** co){
	if(block->n==1){
		block->assign(co);
	}
	else
	{
		rcmatrix* t= new rcmatrix(1,1,co);
		this->block->n--;
		this->block = t;
	}
	return *this;
}

ostream & operator << (ostream & s, const CMatrix & matrix){
	//cout << \"matrix.cols=\" << matrix.block->cols <<endl;
	s << "[";
	for(unsigned int i=0;i<matrix.block->rows;i++)
	for(unsigned int j=0;j<matrix.block->cols;j++){

		s << matrix.block->data[i][j];

		if(((j+1) % matrix.block->cols) == 0 && j!=0 && i!=matrix.block->rows-1)
		s << endl ; // Tu trzeba cos wykombibnowac xd

		if(!(i==matrix.block->rows-1 && j==matrix.block->cols-1) && j!=matrix.block->cols-1)
		s << "\", \"";
	}
	s << "]";
	return s;
}

inline CMatrix operator * (const CMatrix& m1, const CMatrix& m2)
{

	if(m1.block->cols != m2.block->rows)throw WrongDim();

	CMatrix newMatrix(m1.block->rows, m2.block->cols,0.0);

	for(unsigned int i=0;i<newMatrix.block->rows;i++)
	for(unsigned int j=0;j<newMatrix.block->cols;j++)
	{
		double var=0.0;

		for(unsigned int lol=0;lol<m1.block->cols;lol++)
		var += m1.block->data[i][lol]*m2.block->data[lol][j];

		newMatrix.block->data[i][j] = var;
	}

	return newMatrix;
}

double* CMatrix::read(unsigned int i) const{
	try{
		return block->data[i];
	}
	catch(...){
		throw IndexOutOfRange();
	}
}

void CMatrix::write(unsigned int i, double* c){
	block = block->detach();
	try{
		block->data[i] = c;
	}
	catch(...){
		throw IndexOutOfRange();
	}
}

class CMatrix::Cref
{
	friend class CMatrix;
	CMatrix& s;
	unsigned int i;

	Cref (CMatrix& ss, unsigned int ii): s(ss), i(ii){
		cout << "\"cref contructor CALLED\""<<endl;
	};

public:

	operator double*() const{
		cout << "\"operator double* CALLED\""<<endl;
		return s.read(i);
	};

	CMatrix::Cref& operator = (double* c){
		cout << "\"operator = (double* c) CALLED\"" << endl;
		s.write(i,c);
		return *this;
	};

	CMatrix::Cref& operator = (const Cref& ref){
		cout << "\"operator = (const Cref& ref) CALLED\"" << endl;
		return operator = ((double*)ref);
	};


	friend ostream& operator<<(ostream&, const CMatrix::Cref&);
};

CMatrix::Cref CMatrix::operator[](unsigned int i)
{
	cout << "\"Cref rcstring::operator[](unsigned int i) CALLED\""<<endl;
	return Cref(*this,i);
}

ostream& operator<<(ostream& o, const CMatrix::Cref& s1){
	cout << "\"operator<<(ostream& o, const CMatrix::Cref& s1)\""<<endl;
	o << s1.s.block->data[s1.i][s1.i];
	return o;
}
#endif
