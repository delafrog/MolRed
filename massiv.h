
#ifndef _MASSIV_H
#define _MASSIV_H

#include <iostream>
#include <memory.h>
#include <string.h>
#include "init.h"

using namespace std;


template <class T>
inline T abs(T &a){ return a>0 ? a :-a;}

template <class T>
class Vec2		// 2-������
{public: 
	T x[2];

	Vec2() {}
	Vec2(T x1,T x2) {x[0] = x1;x[1] = x2;}
	Vec2(Vec2 <T> &a){x[0] = a.x[0];x[1] = a.x[1];}// ���������
	~Vec2(){}

	T		summ();		// �������;
	T		ssqr();		// ������������;
	void	nrml();		// ����� ���� sqrt(sqs());
	void	nrml(T &a);	// ����� ������������� �� �'a';
	T		norm();		// �������(���)

	T			scpr(Vec2<T> &a);				// ���� �������������������'a'
	T			crss(Vec2<T> &a);				// ��� ����� ������.


	// ����� �����
	Vec2<T> &	operator =(Vec2<T> &a);
	Vec2<T> &	operator =(T a);

	Vec2<T>		operator +(Vec2<T> &a);
	Vec2<T>		operator -(Vec2<T> &a);
	Vec2<T>		operator *(Vec2<T> &a);
	Vec2<T>		operator /(Vec2<T> &a);

	Vec2<T>		operator +(T a);
	Vec2<T>		operator -(T a);
	Vec2<T>		operator *(T a);
	Vec2<T>		operator /(T a);

	Vec2<T> &	operator +=(Vec2<T> &a);
	Vec2<T> &	operator -=(Vec2<T> &a);
	Vec2<T> &	operator *=(Vec2<T> &a);
	Vec2<T> &	operator /=(Vec2<T> &a);

	Vec2<T> &	operator +=(T a);
	Vec2<T> &	operator -=(T a);
	Vec2<T> &	operator *=(T a);
	Vec2<T> &	operator /=(T a);

template <class W>
	friend Vec2<W> operator +(W a,Vec2<W> &b);
template <class W>
	friend Vec2<W> operator -(W a,Vec2<W> &b);
template <class W>
	friend Vec2<W> operator *(W a,Vec2<W> &b);
template <class W>
	friend Vec2<W> operator /(W a,Vec2<W> &b);


template <class W>
	friend Vec2<W> operator -(Vec2<W> &a);	

	int	find(T &a)		{return (x[0]==a)?0:(x[1]==a)?1:-1;}

	// ����� ����� ������.
template <class W>
	friend ostream &	operator <<(ostream &stream, Vec2<W> &a);
template <class W>
	friend istream &	operator >>(istream &stream, Vec2<W> &a);	
	
template <class W>
	friend void CopyObject(Vec2<W> &a,Vec2<W> &b);
template <class W>
	friend void InitObject(Vec2<W> &a);
template <class W>
	friend void ClearObject(Vec2<W> &a);	
};
typedef Vec2<double>	Vec2db;
typedef Vec2<int>		Vec2int;



template <class T>
class Vec3		// 3-������
{public: 
	T x[3];

	Vec3(){}
	Vec3(const T x1, const T x2, const T x3) {x[0] = x1;x[1] = x2;x[2] = x3;}
	Vec3(const Vec3 <T> &a){x[0] = a.x[0];x[1] = a.x[1];x[2] = a.x[2];}// ���������
	~Vec3(){}

	inline T		summ();		// �������;
	inline T		ssqr();		// ������������;
	inline void		nrml();			// ����� ���� sqrt(sqs());
	inline void		nrml(T &a);		// ����� ������������� �� �'a';
	inline T		norm();		// �������(���)

	inline T			scpr(Vec3<T> &a);				// ���� �������������������'a'
	inline Vec3<T>&	crss(Vec3<T> &a,Vec3<T>	&b);	// �����������. ��������� ���.

	//int			fnd(T &a,T&b);	// ����� ��������������� ���'a' �� ���'b'.

	// ����� �����
	//inline Vec3<T> &	operator =(Vec3<T> &a);
	/*inline*/ Vec3<T> &	operator =(const Vec3<T> &a);
	inline Vec3<T> &	operator =(const T &a);

	inline Vec3<T>		operator +(const Vec3<T> &a);
	inline Vec3<T>		operator -(const Vec3<T> &a);
	inline Vec3<T>		operator *(const Vec3<T> &a);
	inline Vec3<T>		operator /(const Vec3<T> &a);

	inline Vec3<T>		operator +(const T a);
	inline Vec3<T>		operator -(const T a);
	inline Vec3<T>		operator *(const T a);
	inline Vec3<T>		operator /(const T a);

	inline Vec3<T> &	operator +=(const Vec3<T> &a);
	inline Vec3<T> &	operator -=(const Vec3<T> &a);
	inline Vec3<T> &	operator *=(const Vec3<T> &a);
	inline Vec3<T> &	operator /=(const Vec3<T> &a);

	inline Vec3<T> &	operator +=(T a);
	inline Vec3<T> &	operator -=(T a);
	inline Vec3<T> &	operator *=(T a);
	inline Vec3<T> &	operator /=(T a);

template <class W>
	/*inline*/ friend Vec3<W> operator +(const W a,const Vec3<W> &b);
template <class W>
	/*inline*/ friend Vec3<W> operator -(const W a,const Vec3<W> &b);
template <class W>
	/*inline*/ friend Vec3<W> operator *(const W a,const Vec3<W> &b);
template <class W>
	/*inline*/ friend Vec3<W> operator /(const W a,const Vec3<W> &b);


template <class W>
	/*inline*/ friend Vec3<W> operator -(Vec3<W> &a);	


	// ����� ����� ������.
template <class W>
	friend ostream &	operator <<(ostream &stream, const Vec3<W> &a);
template <class W>
	friend istream &	operator >>(istream &stream, Vec3<W> &a);	

	int	find(T &a, T &b){return (x[0]!=a)&&(x[0]!=b)?0:(x[1]!=a)&&(x[1]!=b)?1:(x[2]!=a)&&(x[2]!=b)?2:-1;}
	int	find(T &a)		{return (x[0]==a)?0:(x[1]==a)?1:(x[2]==a)?2:-1;}

template <class W>
	friend void CopyObject(Vec3<W> &a,Vec3<W> &b);
template <class W>
	friend void InitObject(Vec3<W> &a);
template <class W>
	friend void ClearObject(Vec3<W> &a);		
};
typedef Vec3<double> Vec3db;
typedef Vec3<int> Vec3int;


template <class T>
class Matr3x3		// ����3�
{public:
	T x[9];

	Matr3x3() {}
	Matr3x3(const T x11,const T x12,const T x13, 
		    const T x21,const T x22,const T x23, 
			const T x31,const T x32,const T x33 ){x[0]=x11;x[1]=x12;x[2]=x13; x[3]=x21;x[4]=x22;x[5]=x23; x[6]=x31;x[7]=x32;x[8]=x33;} 

	Vec3<T>	&	pmv(Vec3<T> &a, const Vec3<T> &b);// �������� ��� � ��� 'b', ��������� ���� 'a'. 
	Matr3x3<T>	&	pmm(Matr3x3<T> &a, const  Matr3x3<T> &b);// �������� ��� � ����'b', ��������� �����'a'. 

	void tns(){T a; a=x[1];x[1]=x[3];x[3]=a; a=x[2];x[2]=x[6];x[6]=a; a=x[5];x[5]=x[7];x[7]=a;}

	Matr3x3<T>	egn(Matr3x3<T> &m, Vec3<T> &v); // ����� ������������ ������ ���, �������� �'m'.
					// ��� ���������� ���� ���� 'v'. �������� ����'m' ����������
					// ������������� ���. ����� ��������� ���� ����

	inline Matr3x3<T> &	operator =(const T &a){x[0]=x[1]=x[2]=x[3]=x[4]=x[5]=x[6]=x[7]=x[8]=a;return *this;}

template <class W>
	friend void CopyObject(Matr3x3<W> &a,Matr3x3<W> &b);
template <class W>
	friend void InitObject(Matr3x3<W> &a);
template <class W>
	friend void ClearObject(Matr3x3<W> &a);	
};

typedef Matr3x3<double> Mtr3db;

const	int cnstdN	= 10;	// ��� ����� �������������� ����.
const	int cnstN	= 0;	// ��� ���������� ����.
const	int cnstmN	= 1;	// ��� ��� � �������������� ����.


template <class T>
class smpl_ms	// ��� ���� �� 'T' (���
{
public:
	T	*x;	// ���� � ���.
	int N;	// ������� !!! ����� ��� �������� ��� 'N'!!!
	int mN;	// ��� ����� ����� n�� � ����(����� ���� ����
//____________________________________
	// ������
	smpl_ms();						// � ����
	smpl_ms(int n);					// ��� �������� � 'n' ����.
	smpl_ms(const T *a,int n);			// ���������������
	smpl_ms(const T *a,int n,int m);		// ���������������� ���
	smpl_ms(smpl_ms <T> &cpms);		// ���������

	~smpl_ms();

	void init(int n);
	void init(const int &n, const int &m);
	void adm__(int n);
	void adm_(int n=cnstdN);
	// ��� ���� ���
	void adm(int n=cnstdN);		// ���� ������ ��� � 'n' ����. ���� ������� (�������� ���
	void _adm(int n=cnstdN);	// ���� ������ ��� � 'n' ����. ���� ������� (������������
	void sm(int n=cnstdN);		// ���� ��� � 'n' ����. ���� �������
	inline void fill() {N=mN;}	// ����� ��������� ������������������ ���� ���

	 // ��� ����
	void add(const T &y);			// ���� �� ��� ��������
	void add(T &y,const int &pos);// ���� �� ��� ���� � ��� 'pos'
	void add(smpl_ms<T> &y);			// ���� ��� ��� ������������
	void add(smpl_ms<T> &y,const int &pos);	// ���� ��� ��� ������� �����'pos'
	void add(const T* y, const int &n);	// ���� ������� � 'n' ���� � ���� 'y'.
	void adc(T &a);						// ���� �� ��� ��������( �������� � ������� ���
	void adc(smpl_ms<T> &a);			// ���� �� ��� ��������( �������� � ������� ���
	void adt(const T &a,const T &b);				// ���� ����������
	void pst(smpl_ms<T> &y);			// ���� ��� ��� � ��� 'y' (����������
	void pst(const int &n1, const int &n2, smpl_ms<T> &y);			// ���� ��� ��� � ��������'y' � ����n1 � n2
	void pad(T &y);						// ���� ��� ��� ���������������� �� ��� ��������� ����

	void swp(smpl_ms<T> &y);	// ���� ��� ��� � ��� 'y' �'y' � ���

	void rem();				// ��� ��������.
	void rem(const int &y);		// ��� 'y' ���������.
	void rem(const int &y, const int &pos);	// ��� 'y' ���� ��� �����'pos'.

	smpl_ms<T>	&	ind(smpl_ms<int> &in, smpl_ms<T> &a);	// ��� ���� 'a' ���� ������������� � ����'in'.
	smpl_ms<T>	&	ind(const int & i1,const int & i2,smpl_ms<T> &a);	// ��� ���� 'a' ���� �������������i1 � i2.
	smpl_ms<T>	&	its(smpl_ms<T> & a,smpl_ms<T> & b);		// ������������������������'a'.
	smpl_ms<T>	&	uni(smpl_ms<T> & a,smpl_ms<T> & b);		// ������b ����� �������������'a'.
	smpl_ms<int> &	fnd(smpl_ms<int> &in,T a);				// ������� ���� �������'a'.
	smpl_ms<int> &	fnd(smpl_ms<bool> &in,smpl_ms<int> &a);// ������� �������� ����'in' ������ �'a'.
	smpl_ms<int> &	fnd(smpl_ms<bool> &in,smpl_ms<int> &a,smpl_ms<int> &b);// ������� �������� ����'in' ������ �'a'
														// , ���� ���- �'b'.

	int			fnd(const T &a,const T&b);	// ����� ��������������� ���'a' �� ���'b'.
	int			fnd(const T &a);		// ������� ������������ ���� �������'a'


	// ��� ����
	inline T & operator [](int &i) {return x[i];}	// ����� ����������

template <class W>
	friend ostream & operator << (ostream & stream,const smpl_ms<W> &a);
template <class W>
	friend istream & operator >> (const istream & stream,smpl_ms<W> &a);// ����� ��� ���

template <class W>
	friend void CopyObject(smpl_ms<W> &a,smpl_ms<W> &b);
template <class W>
	friend void InitObject(smpl_ms<W> &a);
template <class W>
	friend void ClearObject(smpl_ms<W> &a);	

	void	data2file(char ch=' ');
	void	data2file(const char *ch);
};

typedef smpl_ms<int> smsint;

/*class msl : public ms<bool>
{public:
	msl(){};
	msl(int n){this->sm(n);};
	msl(msl &cpms){N	= cpms.N;mN	= cpms.mN;x	= new bool [mN];memcpy(x,cpms.x,N*sizeof(char));};
	msl &	operator =(msl &rhs)
	{
		if (rhs.N>mN)
		{
			delete [] x;
			mN	= rhs.mN;
			N	= rhs.N;
			x	= new bool [mN];
		}
		memcpy(x,rhs.x,N*sizeof(char));
		return *this;
	};
	friend ostream & operator << (ostream & stream,msl &a)// ����� ��� ���
	{
		for (int i=0;i<a.N;i++)	stream<<a.x[i];
		stream<<endl;
		return stream;
	}
	friend void InitObject(msl &a)
	{
		if (a.x	==0x00000000)
		{
			a.x	= new bool [1];
			a.N	= 0;
			a.mN= 1;
		}
		for(int i=0;i<a.mN;i++)
		{
			InitObject(a.x[i]);
		}
	}
};
*/
typedef smpl_ms<char> smschar;
/*
class strng :public smschar
{
public:
	int i;			// ����������������
	strng();			// ������� ����
	strng(const char *a);	// ��������������
	strng(strng &cpms);// ���������
	~strng(){}		// �����

	strng &	operator =(strng &a);

	friend ostream & operator << (ostream & stream,strng &a){stream<<a.x<<endl;return stream;}	// ����� ��� ���
	friend istream & operator >> (istream & stream,strng &a){stream>>a.x;return stream;}			// ����� ��� ���
	friend void InitObject(strng &a)
	{
		if (a.x	==0x00000000)
		{
			a.x	= new char [1];
			a.N	= 0;
			a.mN= 1;
		}
		for(int i=0;i<a.mN;i++)
		{
			InitObject(a.x[i]);
		}
		a.i	= 0;
	}
};
*/

template <class T>
class ms1D : public smpl_ms<T>{
public:
	/*T	*x;	// ���� � ���.
	int N;	// ������� !!! ����� ��� �������� ��� 'N'!!!
	int mN;	// ��� ����� ����� n�� � ����(����� ���� ����*/
	//������
	ms1D(){}				// ������� ����
	ms1D(int n);				// ��� �������� � 'n' ����.
	ms1D(T *a,int n);			// ���������������
	ms1D(T *a,int n,int m);		// ���������������� ���
	ms1D(const ms1D <T> &cpms);		// ���������
	~ms1D(){}
	//if (!nondelete) delete [] x;
	// ����� �����
	ms1D<T> &	operator = (const ms1D<T> &a);
	ms1D<T> &	operator = (const T a);
	ms1D<T>		operator + (const ms1D<T> &a);
	ms1D<T>		operator - (ms1D<T> &a);
	ms1D<T>		operator * (ms1D<T> &a);
	ms1D<T>		operator / (ms1D<T> &a);
	ms1D<T>		operator + (T a);
	ms1D<T>		operator - (T a);
	ms1D<T>		operator * (T a);
	ms1D<T>		operator / (T a);
	ms1D<T> &	operator +=(ms1D<T> &a);
	ms1D<T> &	operator -=(ms1D<T> &a);
	ms1D<T> &	operator *=(ms1D<T> &a);
	ms1D<T> &	operator /=(ms1D<T> &a);
	ms1D<T> &	operator +=(T a);
	ms1D<T> &	operator -=(T a);
	ms1D<T> &	operator *=(T a);
	ms1D<T> &	operator /=(T a);

	void ad1(const T &a,const  T &b,const  T &d);
	
template <class W>
	friend ms1D<W> operator -(ms1D<W> &a);

template <class W>
	friend ms1D<W> operator +(W &a,ms1D<W> &b);
template <class W>
	friend ms1D<W> operator -(W &a,ms1D<W> &b);
template <class W>
	friend ms1D<W> operator *(W &a,ms1D<W> &b);
template <class W>
	friend ms1D<W> operator /(W &a,ms1D<W> &b);

	// ���� ����
	ms1D<bool>	operator >(ms1D<T>	&a);
	ms1D<bool>	operator >(		T	&a);
	ms1D<bool>	operator <(ms1D<T>	&a);
	ms1D<bool>	operator <(		T	&a);
	ms1D<bool>	operator >=(ms1D<T>	&a);
	ms1D<bool>	operator >=(	T	&a);
	ms1D<bool>	operator <=(ms1D<T>	&a);
	ms1D<bool>	operator <=(	T	&a);
	ms1D<bool>	operator ==(ms1D<T>	&a);
	ms1D<bool>	operator ==(	T	&a);
	ms1D<bool>	operator !=(	T	&a);
	ms1D<bool>	operator !=(ms1D<T>	&a);

template <class W>
	friend ms1D<bool>	operator >( W a,ms1D<W>	&b);
template <class W>
	friend ms1D<bool>	operator <( W a,ms1D<W>	&b);
template <class W>
	friend ms1D<bool>	operator >=(W a,ms1D<W>	&b);
template <class W>
	friend ms1D<bool>	operator <=(W a,ms1D<W>	&b);
template <class W>
	friend ms1D<bool>	operator ==(W a,ms1D<W>	&b);
template <class W>
	friend ms1D<bool>	operator !=(W a,ms1D<W>	&b);


	// ����� ����� ����������.
template <class W>
	friend ostream &	operator <<(ostream &stream, ms1D<W> &a);
template <class W>
	friend istream &	operator >>(istream &stream, ms1D<W> &a);

	int mmin();		// ������� ������ ����
	int mmin(T &m);	// ������� ������ �������� �����'m'.
	int mmax();		// ������� ������ ����
	int mmax(T &m);	// ������� ������ �������� �����'m'.

	void sort();					// ����� ����
	void sort(ms1D<T> &a);			// ����� ����������'a'.
	void sort(ms1D<T> &a, ms1D<int> &j);// ����� ����������'a', �'j' - ��� ����� 'a'.
	void sort_(ms1D<int> &j);	// ����� ���;  �'j' - ��� ����� 'a'.

	void one(int n);	

	// ��� ��� ����� ������ ����
//	ms1D<T>	&	ind(ms1D<int>&in,ms1D<T> &a);	// ��� ���� 'a' ���� ������������� � ����'in'.
//	ms1D<T>	&	ind(const int & i1,const int & i2,ms1D<T> &a);	// ��� ���� 'a' ���� �������������i1 � i2.
	ms1D<T>	&	its(ms1D<T> & a,ms1D<T> & b);	// ������������������������'a'.
	ms1D<T>	&	itss(ms1D<T> & a,ms1D<T> & b);	// ������������������������'a' (� ������������).
	ms1D<T>	&	uni(ms1D<T> & a,ms1D<T> & b);	// ������b ����� �������������'a'.
	ms1D<T>	&	unis(ms1D<T> & a,ms1D<T> & b);	// ������b ����� �������������'a'(� ������������).
	ms1D<int> &	fnd(ms1D<int> &in,T a);		// ������� ���� �������'a'.
	ms1D<int> &	fnd(ms1D<bool> &in,ms1D<int> &a);// ������� �������� ����'in' ������ �'a'.
	ms1D<int> &	fnd(ms1D<bool> &in,ms1D<int> &a,ms1D<int> &b);// ������� �������� ����'in' ������ �'a'
														// , ���� ���- �'b'.
	int			fnd(T &a,T&b);	// ����� ��������������� ���'a' �� ���'b'.
	int			fnd(T &a);		// ������� ������������ ���� �������'a'


	T	sum();		// �������;

	T	sqs();		// ����������������;
	T	nrm();		// ������� sqrt(sqs());
	void Nrm();		// ����� ����� ����
	void Nrm(T &a);	// ����� ����� ����
	T	spr(ms1D<T>	&a);	// ���� �������c���'a' �'b'. �� ���� ��� �� �����!

	template <class W>	/*inline*/ friend void CopyObject(ms1D<W> &a,const ms1D<W> &b);
	template <class W>	/*inline*/ friend void InitObject(ms1D<W> &a);
	template <class W>	/*inline*/ friend void ClearObject(ms1D<W> &a);	
	/*template <class W>	/*inline*/ friend void CopyObject(ms1D<int> &a,const ms1D<int> &b);

};


typedef ms1D<int> ms1Dint;
typedef ms1D<double> ms1Ddb;
typedef ms1D<ms1Ddb> ms1DDdb;
typedef ms1D<ms1DDdb> ms1DDDdb;
typedef ms1D<int> * p_ms1Dint;
typedef ms1D<ms1Dint> msDDint;

typedef ms1D<Vec3db> ms1DVec3db;

#endif
