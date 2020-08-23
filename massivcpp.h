#ifndef _MASSIV_CPP
#define _MASSIV_CPP

//#include "vm/vecmath.h"
//#include <memory.h>
#include <stdlib.h> 
#include <math.h>
#include "massiv.h"
#include <fstream>

using namespace std;


// Implementation of the class Vec2<>
//____________________________________
template <class T>
T Vec2<T>::summ(){return x[0]+x[1];}
//____________________________________
template <class T>
T Vec2<T>::ssqr(){return x[0]*x[0]+x[1]*x[1];}
//____________________________________
template <class T>
void Vec2<T>::nrml() {T a;a	= sqrt(x[0]*x[0]+x[1]*x[1]);x[0]/=a;x[1]/=a;}
//____________________________________
template <class T>
void Vec2<T>::nrml(T &a) {a	= sqrt(x[0]*x[0]+x[1]*x[1]);x[0]/=a;x[1]/=a;}
//____________________________________
template <class T>
T Vec2<T>::norm()	{return sqrt(x[0]*x[0]+x[1]*x[1]);}
//____________________________________
template <class T>
T Vec2<T>::scpr(Vec2<T> &a){return a.x[0]*x[0]+a.x[1]*x[1];}
//____________________________________
template <class T>
T Vec2<T>::crss(Vec2<T>&a){return x[0]*a.x[1]-x[1]*a.x[0];}
//____________________________________
template <class T>
Vec2<T> & Vec2<T>::operator =(Vec2<T> &a) {x[0]=a.x[0];x[1]=a.x[1]; return *this;}
//____________________________________
template <class T>
Vec2<T> & Vec2<T>::operator =(T a) {x[0] = x[1] = a; return *this;}

//____________________________________
template <class T>
Vec2<T> Vec2<T>::operator +(Vec2<T> &a) {return Vec2<T>(x[0]+a.x[0],x[1]+a.x[1]);}
//____________________________________
template <class T>
Vec2<T> Vec2<T>::operator -(Vec2<T> &a) {return Vec2<T>(x[0]-a.x[0],x[1]-a.x[1]);}
//____________________________________
template <class T>
Vec2<T> Vec2<T>::operator *(Vec2<T> &a) {return Vec2<T>(x[0]*a.x[0],x[1]*a.x[1]);}
//____________________________________
template <class T>
Vec2<T> Vec2<T>::operator /(Vec2<T> &a) {return Vec2<T>(x[0]/a.x[0],x[1]/a.x[1]);}

//____________________________________
template <class T>
Vec2<T> Vec2<T>::operator +(T a) {return Vec2<T>(x[0]+a,x[1]+a);}
//____________________________________
template <class T>
Vec2<T> Vec2<T>::operator -(T a) {return Vec2<T>(x[0]-a,x[1]-a);}
//____________________________________
template <class T>
Vec2<T> Vec2<T>::operator *(T a) {return Vec2<T>(x[0]*a,x[1]*a);}
//____________________________________
template <class T>
Vec2<T> Vec2<T>::operator /(T a) {return Vec2<T>(x[0]/a,x[1]/a);}

//____________________________________
template <class T>
Vec2<T> & Vec2<T>::operator +=(Vec2<T> &a) {x[0]+=a.x[0];x[1]+=a.x[1];return *this;}
//____________________________________
template <class T>
Vec2<T> & Vec2<T>::operator -=(Vec2<T> &a) {x[0]-=a.x[0];x[1]-=a.x[1];return *this;}
//____________________________________
template <class T>
Vec2<T> & Vec2<T>::operator *=(Vec2<T> &a) {x[0]*=a.x[0];x[1]*=a.x[1];return *this;}
//____________________________________
template <class T>
Vec2<T> & Vec2<T>::operator /=(Vec2<T> &a) {x[0]/=a.x[0];x[1]/=a.x[1];return *this;}

//____________________________________
template <class T>
Vec2<T> & Vec2<T>::operator +=(T a) {x[0]+=a;x[1]+=a;return *this;}
//____________________________________
template <class T>
Vec2<T> & Vec2<T>::operator -=(T a) {x[0]-=a;x[1]-=a;return *this;}
//____________________________________
template <class T>
Vec2<T> & Vec2<T>::operator *=(T a) {x[0]*=a;x[1]*=a;return *this;}
//____________________________________
template <class T>
Vec2<T> & Vec2<T>::operator /=(T a) {x[0]/=a;x[1]/=a;return *this;}


//____________________________________
template <class T>
Vec2<T> operator + (T a,Vec2<T> &b) {return Vec2<T>(a+b.x[0],a+b.x[1]);}
//____________________________________
template <class T>
Vec2<T> operator - (T a,Vec2<T> &b) {return Vec2<T>(a-b.x[0],a-b.x[1]);}
//____________________________________
template <class T>
Vec2<T> operator * (T a,Vec2<T> &b) {return Vec2<T>(a*b.x[0],a*b.x[1]);}
//____________________________________
template <class T>
Vec2<T> operator / (T a,Vec2<T> &b) {return Vec2<T>(a/b.x[0],a/b.x[1]);}

//____________________________________
template <class T>
Vec2<T> operator -(Vec2<T> &a) {return Vec2<T>(-a.x[0],-a.x[1]);}

//____________________________________
template <class T>
ostream &	operator <<(ostream &stream, Vec2<T> &a) {stream<< a.x[0]<<" "<<a.x[1]<<'\n'; return stream;}
//____________________________________
template <class T>
istream &	operator >>(istream &stream, Vec2<T> &a) {stream>> a.x[0];stream>> a.x[1]; return stream;}
//____________________________________
template <class T>
void InitObject(Vec2<T> &a){InitObject(a.x[0]);InitObject(a.x[1]);}
//____________________________________
template <class T>
void ClearObject(Vec2<T> &a){ClearObject(a.x[0]);ClearObject(a.x[1]);}
//____________________________________
template <class T>
void CopyObject(Vec2<T> &a,Vec2<T> &b){CopyObject(a.x[0],b.x[0]);CopyObject(a.x[1],b.x[1]);}






// Implementation of the class Vec3<>
//____________________________________
template <class T>
inline T Vec3<T>::summ(){return x[0]+x[1]+x[2];}
//____________________________________
template <class T>
inline T Vec3<T>::ssqr(){return x[0]*x[0]+x[1]*x[1]+x[2]*x[2];}
//____________________________________
template <class T>
inline void Vec3<T>::nrml() {T a;a	= sqrt(x[0]*x[0]+x[1]*x[1]+x[2]*x[2]);x[0]/=a;x[1]/=a;x[2]/=a;}
//____________________________________
template <class T>
inline void Vec3<T>::nrml(T &a) {a	= sqrt(x[0]*x[0]+x[1]*x[1]+x[2]*x[2]);x[0]/=a;x[1]/=a;x[2]/=a;}
//____________________________________
template <class T>
inline T Vec3<T>::norm()	{return sqrt(x[0]*x[0]+x[1]*x[1]+x[2]*x[2]);}
//____________________________________
template <class T>
inline T Vec3<T>::scpr(Vec3<T> &a){	return a.x[0]*x[0]+a.x[1]*x[1]+a.x[2]*x[2];}
//____________________________________
template <class T>
inline Vec3<T> & Vec3<T>::crss(Vec3<T>&a,Vec3<T>&b)
{
	x[0]	= a.x[1]*b.x[2]-a.x[2]*b.x[1];
	x[1]	= a.x[2]*b.x[0]-a.x[0]*b.x[2];
	x[2]	= a.x[0]*b.x[1]-a.x[1]*b.x[0];
	return *this;
}

//____________________________________
/*template <class T>
int	Vec3<T>::fnd(T &a,T&b)	// ����� ��������������� ���'a' �� ���'b'.
{
	if ((x[0]!=a)&&(x[0]!=b)) return 0;
	if ((x[1]!=a)&&(x[1]!=b)) return 1;
	if ((x[2]!=a)&&(x[2]!=b)) return 2;
	return -1;
}*/

//____________________________________
//template <class T>
//inline Vec3<T> & Vec3<T>::operator =(Vec3<T> &a) {x[0]=a.x[0];x[1]=a.x[1];x[2]=a.x[2]; return *this;}
//____________________________________
template <class T>
inline Vec3<T> & Vec3<T>::operator =(const Vec3<T> &a) {x[0]=a.x[0];x[1]=a.x[1];x[2]=a.x[2]; return *this;}
//____________________________________
template <class T>
		inline Vec3<T> & Vec3<T>::operator =(const T &a) {x[0] = x[1] = x[2] =a; return *this;}

//____________________________________
template <class T>
		inline Vec3<T> Vec3<T>::operator +(const Vec3<T> &a) {return Vec3<T>(x[0]+a.x[0],x[1]+a.x[1],x[2]+a.x[2]);}
//____________________________________
template <class T>
		inline Vec3<T> Vec3<T>::operator -(const Vec3<T> &a) {return Vec3<T>(x[0]-a.x[0],x[1]-a.x[1],x[2]-a.x[2]);}
//____________________________________
template <class T>
		inline Vec3<T> Vec3<T>::operator *(const Vec3<T> &a) {return Vec3<T>(x[0]*a.x[0],x[1]*a.x[1],x[2]*a.x[2]);}
//____________________________________
template <class T>
		inline Vec3<T> Vec3<T>::operator /(const Vec3<T> &a) {return Vec3<T>(x[0]/a.x[0],x[1]/a.x[1],x[2]/a.x[2]);}

//____________________________________
template <class T>
		inline Vec3<T> Vec3<T>::operator +(const T a) {return Vec3<T>(x[0]+a,x[1]+a,x[2]+a);}
//____________________________________
template <class T>
		inline Vec3<T> Vec3<T>::operator -(const T a) {return Vec3<T>(x[0]-a,x[1]-a,x[2]-a);}
//____________________________________
template <class T>
		inline Vec3<T> Vec3<T>::operator *(const T a) {return Vec3<T>(x[0]*a,x[1]*a,x[2]*a);}
//____________________________________
template <class T>
		inline Vec3<T> Vec3<T>::operator /(const T a) {return Vec3<T>(x[0]/a,x[1]/a,x[2]/a);}

//____________________________________
template <class T>
		inline Vec3<T> & Vec3<T>::operator +=(const Vec3<T> &a) {x[0]+=a.x[0];x[1]+=a.x[1];x[2]+=a.x[2];return *this;}
//____________________________________
template <class T>
		inline Vec3<T> & Vec3<T>::operator -=(const Vec3<T> &a) {x[0]-=a.x[0];x[1]-=a.x[1];x[2]-=a.x[2];return *this;}
//____________________________________
template <class T>
		inline Vec3<T> & Vec3<T>::operator *=(const Vec3<T> &a) {x[0]*=a.x[0];x[1]*=a.x[1];x[2]*=a.x[2];return *this;}
//____________________________________
template <class T>
		inline Vec3<T> & Vec3<T>::operator /=(const Vec3<T> &a) {x[0]/=a.x[0];x[1]/=a.x[1];x[2]/=a.x[2];return *this;}

//____________________________________
template <class T>
inline Vec3<T> & Vec3<T>::operator +=(T a) {x[0]+=a;x[1]+=a;x[2]+=a;return *this;}
//____________________________________
template <class T>
inline Vec3<T> & Vec3<T>::operator -=(T a) {x[0]-=a;x[1]-=a;x[2]-=a;return *this;}
//____________________________________
template <class T>
inline Vec3<T> & Vec3<T>::operator *=(T a) {x[0]*=a;x[1]*=a;x[2]*=a;return *this;}
//____________________________________
template <class T>
inline Vec3<T> & Vec3<T>::operator /=(T a) {x[0]/=a;x[1]/=a;x[2]/=a;return *this;}


//____________________________________
template <class T>
		inline Vec3<T> operator + (const T a,const Vec3<T> &b) {return Vec3<T>(a+b.x[0],a+b.x[1],a+b.x[2]);}
//____________________________________
template <class T>
		inline Vec3<T> operator - (const T a,const Vec3<T> &b) {return Vec3<T>(a-b.x[0],a-b.x[1],a-b.x[2]);}
//____________________________________
template <class T>
inline Vec3<T> operator * (const T a,const Vec3<T> &b) {return Vec3<T>(a*b.x[0],a*b.x[1],a*b.x[2]);}
//____________________________________
template <class T>
		inline Vec3<T> operator / (const T a,const Vec3<T> &b) {return Vec3<T>(a/b.x[0],a/b.x[1],a/b.x[2]);}

//____________________________________
template <class T>
inline Vec3<T> operator -(Vec3<T> &a) {return Vec3<T>(-a.x[0],-a.x[1],-a.x[2]);}

//____________________________________
template <class T>
ostream &	operator <<(ostream &stream, const Vec3<T> &a) {stream<< a.x[0]<<" "<<a.x[1]<<" "<<a.x[2]<<'\n'; return stream;}
//____________________________________
template <class T>
istream &	operator >>(istream &stream, Vec3<T> &a) {stream>> a.x[0];stream>> a.x[1];stream>> a.x[2]; return stream;}
//____________________________________
template <class T>
void InitObject(Vec3<T> &a){InitObject(a.x[0]);InitObject(a.x[1]);InitObject(a.x[2]);}
//____________________________________
template <class T>
void ClearObject(Vec3<T> &a){ClearObject(a.x[0]);ClearObject(a.x[1]);ClearObject(a.x[2]);}
//____________________________________
template <class T>
void CopyObject(Vec3<T> &a,Vec3<T> &b){CopyObject(a.x[0],b.x[0]);CopyObject(a.x[1],b.x[1]);CopyObject(a.x[2],b.x[2]);}











//____________________________________
template <class T>
Vec3<T> & Matr3x3<T>::pmv(Vec3<T> &a, const Vec3<T> &b) // �������� ��� � ��� 'b', ��������� ���� 'a'. 
{
	a.x[0]	= x[0]*b.x[0]+x[1]*b.x[1]+x[2]*b.x[2];
	a.x[1]	= x[3]*b.x[0]+x[4]*b.x[1]+x[5]*b.x[2];
	a.x[2]	= x[6]*b.x[0]+x[7]*b.x[1]+x[8]*b.x[2];
	return a;
}

//____________________________________
template <class T>
Matr3x3<T>	&	 Matr3x3<T>::pmm(Matr3x3<T> &a, const Matr3x3<T> &b)// �������� ��� � ����'b', ��������� �����'a'. 
{
	a.x[0]	= x[0]*b.x[0]+x[1]*b.x[3]+x[2]*b.x[6];
	a.x[1]	= x[0]*b.x[1]+x[1]*b.x[4]+x[2]*b.x[7];
	a.x[2]	= x[0]*b.x[2]+x[1]*b.x[5]+x[2]*b.x[8];

	a.x[3]	= x[3]*b.x[0]+x[4]*b.x[3]+x[5]*b.x[6];
	a.x[4]	= x[3]*b.x[1]+x[4]*b.x[4]+x[5]*b.x[7];
	a.x[5]	= x[3]*b.x[2]+x[4]*b.x[5]+x[5]*b.x[8];

	a.x[6]	= x[6]*b.x[0]+x[7]*b.x[3]+x[8]*b.x[6];
	a.x[7]	= x[6]*b.x[1]+x[7]*b.x[4]+x[8]*b.x[7];
	a.x[8]	= x[6]*b.x[2]+x[7]*b.x[5]+x[8]*b.x[8];

	return a;
}

//____________________________________
template <class T>
Matr3x3<T> Matr3x3<T>::egn(Matr3x3<T> &m, Vec3<T> &v)
{

	// ����� ����'m' ������. 
	Matr3x3<T> a;
	memset(m.x,0,9*sizeof(T));	// ����� ��� �� ����
	int dm,j;
	m.x[0] = m.x[4] = m.x[8] =1;
	dm	= 4;

	a.x[0] = x[0];a.x[1] = x[1];a.x[2] = x[2];
	a.x[3] = x[3];a.x[4] = x[4];a.x[5] = x[5];
	a.x[6] = x[6];a.x[7] = x[7];a.x[8] = x[8];
	
	double prc	= 1e-15;// ����� � ����� ����� ����������� ����
	double amx;			// ����� � ���� ������ � ��� �������� ����
	bool cycl	= true; // ����� ��� �� ������ �� 'cycl' ���.
	int i_,i;				// � �������� ������ ����
	int ri,rj,rix,rjx;		// � ���� ���������� ����
	double p,q,c,s,cq,sq;	// ������ ����� ������. 'c' �'s' -������� ���� ������'(ri,rj)'
	double aii,ajj,aij;		// � ����� ����  ���,
	Vec3db bmj;
	Vec3db bmi;
	const double sq2	= sqrt(2.0)/2.0;	// ���������� 45 ����.
	while (cycl)	// ������. �� ��������.
	{
		cycl= false;
		i_	= 3;
		amx	= prc;
		for(i=1;i<3;i++)
		{	
			for(j=0;j<i;j++)
			{
				if (amx<=abs(a.x[i_]))
				{
					amx	= abs(a.x[i_]);
					ri	= j;rj	= i;
					cycl	= true;
				}
				i_++;
			}
			i_	+= 3; i_-=i;
		}
		if (cycl)
		{
			rjx	= rj*3;
			rix	= ri*3;
			// ���������� ���� ���
			aii	= a.x[ri*dm];	
			ajj	= a.x[rj*dm];
			aij	= a.x[ri+rjx];
			// ���������� ��� ���� ����
			p	= ajj-aii;
			if (p==0) {c	= s	= sq2;}	
			else
			{
				q	= aij/p;
				cq	= sqrt(p/((p*=p)+4*aij*aij))+1;
				c	= sqrt(cq/2);
				s	= q*(1-cq)/c;
			}
			cq	/= 2;
			sq	*= sq	= s;
			// ������������� ��� ����� ������� ��.
			for (i=0;i<3;i++)
			{
				bmi.x[i]	= c*a.x[i+rix]+s*a.x[i+rjx];
				bmj.x[i]	= c*a.x[i+rjx]-s*a.x[i+rix];
			}
			for (i=0;i<3;i++)
			{
				a.x[i+rix]	= a.x[ri+i*3]	= bmi.x[i];
				a.x[i+rjx]	= a.x[rj+i*3]	= bmj.x[i];
			}
			a.x[ri*dm]	= cq*aii+sq*ajj+2*c*s*aij;
			a.x[rj*dm]	= sq*aii+cq*ajj-2*c*s*aij;
			a.x[rj+rix] = a.x[ri+rjx]	= 0;
			// �������������� ��� �����.
			for (i=0;i<3;i++)
			{
				bmi.x[i]	= c*m.x[i+rix]+s*m.x[i+rjx];
				bmj.x[i]	= c*m.x[i+rjx]-s*m.x[i+rix];
			}
			for (i=0;i<3;i++)
			{
				m.x[i+rix]	= bmi.x[i];
				m.x[i+rjx]	= bmj.x[i];
			}
		}
	}
	for (i=0;i<3;i++)
	{
		v.x[i]	= a.x[i*dm];
	}
	m.tns();
	return a;
}
//____________________________________
template <class T>
void InitObject(Matr3x3<T> &a)
{
	InitObject(a.x[0]);	InitObject(a.x[1]);	InitObject(a.x[2]);
	InitObject(a.x[3]);	InitObject(a.x[4]);	InitObject(a.x[5]);
	InitObject(a.x[6]);	InitObject(a.x[7]);	InitObject(a.x[8]);
}
//____________________________________
template <class T>
void ClearObject(Matr3x3<T> &a)
{
	ClearObject(a.x[0]); ClearObject(a.x[1]); ClearObject(a.x[2]);
	ClearObject(a.x[3]); ClearObject(a.x[4]); ClearObject(a.x[5]);
	ClearObject(a.x[6]); ClearObject(a.x[7]); ClearObject(a.x[8]);
}
//____________________________________
template <class T>
void CopyObject(Matr3x3<T> &a,Matr3x3<T> &b)
{
	ClearObject(a.x[0],b.x[0]); ClearObject(a.x[1],b.x[1]); ClearObject(a.x[2],b.x[2]);
	ClearObject(a.x[3],b.x[3]); ClearObject(a.x[4],b.x[4]); ClearObject(a.x[5],b.x[3]);
	ClearObject(a.x[6],b.x[6]); ClearObject(a.x[7],b.x[7]); ClearObject(a.x[8],b.x[8]);
}
//____________________________________



// Implementation of the class smpl_ms<>
//____________________________________
template <class T>
smpl_ms<T>::smpl_ms()
{
	x	= 0x00000000;
	mN	= 0;
	N	= 0;
}
bool	nondelete	= false;
template <class T>
smpl_ms<T>::~smpl_ms()
{
	if (!nondelete)
	{
		ClearObject(*this);
	}
}		// �����


//____________________________________
template <class T>
smpl_ms<T>::smpl_ms(int n){N=0;mN=n;x	= new T [n];InitObject(*this);}
//____________________________________
template <class T>
smpl_ms<T>::smpl_ms(const T *a,int n)
{
	mN	= N = n;
	x = new T [mN];
	InitObject(*this);
	for(int i=0;i<N;i++)x[i] = a[i];
}
//____________________________________
template <class T>
smpl_ms<T>::smpl_ms(const T *a,int n,int m)
{
	N	= n;
	mN	= m;
	x	= new T [mN];
	InitObject(*this);
	for(int i=0;i<N;i++)x[i] = a[i];
}
//____________________________________
template <class T>
smpl_ms<T>::smpl_ms(smpl_ms <T> &cpms)
{
	N	= cpms.N;mN	= cpms.mN;	
	x	= new T [mN];
	for(int i=0;i<N;i++)x[i]=cpms.x[i];
}
//____________________________________
template <class T>
void smpl_ms<T>::init(int n)
{
	if (mN<n)
	{
		if(mN==0)
		{
			mN = n;
			if (x!=0x0) {cout<<"Memory Error!"<<endl;exit(1);}
			x	= new T [mN];
			InitObject(*this);
		}
		else adm_(n-mN);
	}else InitObject(*this);
	N	= n;
}
//____________________________________
template <class T>
void smpl_ms<T>::init(const int &n, const int &m)
{	
	if (mN<m)
	{
		if(mN==0)
		{
			mN = m;
			if (x!=0x0) {cout<<"Memory Error!"<<endl;exit(1);}
			x	= new T [mN];
			InitObject(*this);
		}
		else adm_(m-mN);
	}else InitObject(*this);
	N	= n;
}
//____________________________________
template <class T>
void smpl_ms<T>::_adm(int n)
{	
	T *x_,*y;
	x_	= new T [mN+n];	
	y	= x;
	x	= x_;
	x_	= y;
	//for(i=0;i<mN;i++){ClearObject(x[i]);} (������������ � ����)
	memcpy(x,x_,mN*sizeof(T));
	mN	+= n;
	nondelete	= true;
	delete [] x_;
	nondelete	= false;
}
//____________________________________
template <class T>
void smpl_ms<T>::adm_(int n)
{
	int i;
	T *x_;
	x_	= new T [mN+n];	
	//for(i=0;i<mN;i++)ClearObject(x_[i]);
	memcpy(x_,x,mN*sizeof(T));
	for(i=mN;i<mN+n;i++)InitObject(x_[i]);
	mN	+= n;
	nondelete	= true;
	delete [] x;
	nondelete	= false;
	x	= x_;
	/*T *x_;
	mN+=n;
	x_	= new T [mN];
	memcpy(x_,x,N*sizeof(T));
	delete [] x;
	x	= x_;*/
	/*x_	= (T*)malloc((mN+n)*sizeof(T));//new T [mN+n];
	memset(x_,0,(mN+n)*sizeof(T));/**/
}
//____________________________________
template <class T>
void smpl_ms<T>::adm(int n)
{
	T *x_;
	mN+=n;
	x_	= new T [mN];
	memcpy(x_,x,N*sizeof(T));
	delete [] x;
	x	= x_;
}
//____________________________________
template <class T>
void smpl_ms<T>::adm__(int n)
{
	/*T *x_;
	int *y;
	mN+=n;
	x_	= new T [mN];
	memcpy(x_,x,N*sizeof(T));
	delete [] x;
	x	= x_;/**/

		T *x_;
		int i,j,sz;
		sz	= sizeof(T);
		j	= mN;
		mN	+= n;
		x_	= new T [mN];
		for(i=0;i<j;i++)
		{
			ClearObject(x_[i]);
		}
		/*y	= x_;
		x_ = (T*)malloc(mN*sizeof(T));
		for(int i=0;i<mN;i++)
		{
			x_[i] = T();
		}*/
		//x_ = (T*)malloc(mN*sizeof(T));
		memcpy(x_,x,j*sz);
		for(i=j;i<mN;i++)
		{
			InitObject(x_[i]);
		}
		nondelete	= true;
		delete [] x;
		nondelete	= false;
		x	= x_;
/**/
}
//____________________________________
//template <class T>
//void smpl_ms<T>::adm(){}
//____________________________________
template <class T>
void smpl_ms<T>::sm(int n)
{
	mN	= n;
	delete [] x;
	x	= new T [mN];
}
//____________________________________
//template <class T>
//void smpl_ms<T>::sm(){mN	= cnstdN;delete [] x;x	= new T [mN];}
//____________________________________
template <class T>
void smpl_ms<T>::add(const T &y)
{
	if (N>=mN)
	{
		T *x_;
		mN	+= cnstdN;
		x_	= new T [mN];
		memcpy(x_,x,N*sizeof(T));
		delete [] x;
		x	= x_;	
	}
	x[N]	= y;
	N++;	
}
//____________________________________
template <class T>
void smpl_ms<T>::add(T &y,const int &pos)
{
	if (N>=mN)
	{
		T *x_;
		mN	+= cnstdN;
		x_	= new T [mN];
		memcpy(x_,x,pos*sizeof(T));
		x_[pos]	= y;
		memcpy(x_+pos+1,x+pos,(N-pos)*sizeof(T));
		delete [] x;
		x	= x_;	
	}
	else
	{
		memmove(x+pos+1,x+pos,(N-pos)*sizeof(T));
		x[pos]	= y;
	}
	N++;
}
//____________________________________
template <class T>
void smpl_ms<T>::add(smpl_ms<T> &y)
{
	if ((N+y.N)>=mN)
	{
		T *x_;
		mN	+= y.N;
		x_	= new T [mN];
		memcpy(x_,x,N*sizeof(T));
		delete [] x;
		memcpy(x_+N,y.x,y.N*sizeof(T));
		x	= x_;

	}
	else
	{
		memcpy(x+N,y.x,y.N*sizeof(T));
	}
	N	+= y.N;
}
//____________________________________
template <class T>
void smpl_ms<T>::add(smpl_ms<T> &y,const int &pos)
{
	if (N+y.N>=mN)
	{
		T *x_;
		mN	+= y.N;
		x_	= new T [mN];
		memcpy(x_,x,pos*sizeof(T));
		memcpy(x_+pos,y.x,y.N*sizeof(T));
		memcpy(x_+pos+y.N,x+pos,(N-pos)*sizeof(T));
		delete [] x;
		x	= x_;	
	}
	else
	{
		memmove(x+pos+y.N,x+pos,(N-pos)*sizeof(T));
		memcpy(x+pos,y.x,y.N*sizeof(T));
	}
	N	+= y.N;
}
//____________________________________
template <class T>
void smpl_ms<T>::add(const T* y, const int &n)	// ���� ������� � 'n' ���� � ���� 'y'.
{
	if ((N+n)>=mN)
	{
		T *x_;
		mN	+= n;
		x_	= new T [mN];
		memcpy(x_,x,N*sizeof(T));
		delete [] x;
		memcpy(x_+N,y,n*sizeof(T));
		x	= x_;	
	}
	else
	{
		memcpy(x+N,y,n*sizeof(T));
	}
	N	+= n;
}
//____________________________________
template <class T>
void smpl_ms<T>::adc(T &a)	// ���� ��� ����(��������
{
	if (N>=mN)
	{
		this->adm_(cnstdN);
	}
	CopyObject(x[N],a);
	N++;	
}
//____________________________________
template <class T>
void smpl_ms<T>::adc(smpl_ms<T> &a)	// ���� ��� ����(��������
{
	if (a.N>mN)
	{
		this->adm(a.N-mN);
	}
	for(int i=0;i<a.N;i++)CopyObject(x[i+N],a[i]);
	N++;
}
//____________________________________
template <class T>
void smpl_ms<T>::adt(const T &a,const T &b)	// ���� ����������
{
	if (N>=mN-1)
	{
		T *x_;
		mN	+= cnstdN;
		x_	= new T [mN];
		memcpy(x_,x,N*sizeof(T));
		delete [] x;
		x	= x_;	
	}
	x[N]	= a;
	N++;
	x[N]	= b;
	N++;
}
//____________________________________
template <class T>
void smpl_ms<T>::pst(const int &n1, const int &n2, smpl_ms<T> &y)			// ���� ��� ��� � ��������'y' � ����n1 � n2
{
	N	= n2-n1;
	if (N>mN)
	{
		mN	= N+cnstdN;
		delete [] x;
		x	= new T [mN];
	}
	memcpy(x,y.x+n1,N*sizeof(T));
}
//____________________________________
template <class T>
void smpl_ms<T>::pst(smpl_ms<T> &y)		// ���� ��� ��� � ��� 'y' (����������
{
	if (y.N>mN)
	{
		mN	= y.N+cnstdN;
		delete [] x;
		x	= new T [mN];
	}
	memcpy(x,y.x,y.N*sizeof(T));
	N	= y.N;
}
//____________________________________
template <class T>
void smpl_ms<T>::pad(T &y)
{
	if (N>=mN)
	{
		T *x_;
		mN	+= cnstdN;
		x_	= new T [mN];
		//memcpy(x_,x,N*sz);
		for(int i=0;i<N;i++){x_[i]=x[i];}
		delete [] x;
		x	= x_;	
	}
	x[N]	= y;
	N++;
}
//____________________________________
template <class T>
void smpl_ms<T>::swp(smpl_ms<T> &y)	// ���� ��� ��� � ��� 'y' �'y' � ���
{
	T *z;
	int i;
	i	= y.N;y.N	= N;N	= i;
	i	= y.mN;y.mN	= mN;mN	= i;
	z	= y.x;y.x	= x;x	=z;
}
//____________________________________
template <class T>
void smpl_ms<T>::rem()
{
	N--;
}
//____________________________________
template <class T>
void smpl_ms<T>::rem(const int &y)
{
	N	-= y;
}
//____________________________________
template <class T>
void smpl_ms<T>::rem(const int &y,const int &pos)
{
	if (pos>=N-y)
	{
		N	= pos;
	}
	else
	{
		memmove(x+pos,x+pos+y,(N-pos-y)*sizeof(T));
		N	-= y;
	}
}
//____________________________________
template <class T>
smpl_ms<T>&	smpl_ms<T>::ind(smpl_ms<int> &in, smpl_ms<T> &a)	// ��� ���� 'a' ���� ��������� � ����'in';
{
	a.N	= in.N;
	for(int i=0;i<a.N;i++){a.x[i]	= x[in.x[i]];}
	return a;
}
//____________________________________
template <class T>
smpl_ms<T>	&	smpl_ms<T>::ind(const int & i1,const int & i2,smpl_ms<T> &a)	// ��� ���� 'a' ���� �������������i1 � i2.
{
	a.N	= i2-i1;
	for(int i=0;i<a.N;i++){a.x[i]	= x[i+i1];}
	return a;
}
//____________________________________
template <class T>
smpl_ms<T> &	smpl_ms<T>::its(smpl_ms<T> & a,smpl_ms<T> & b)		// ������������������������'a'.
{
	b.N	= 0;
	int k;
	for(int i=0;i<N;i++)
	{
		k	= 0;
		for(int j=0;j<b.N;j++){if (x[i]==b.x[j]) {k	= 1; break;}}
		if (k==0)
		{
			for(int j=0;j<a.N;j++){if (x[i]==a.x[j]) {k	= 1; break;}}
			if (k==1) {b.x[b.N++] = x[i];}
		}
	}
	return b;
}
//____________________________________
template <class T>
inline smpl_ms<T> &	smpl_ms<T>::uni(smpl_ms<T> & a,smpl_ms<T> & b)		// ������b ����� �������������'a'.
{
	static T r;
	static int i,j;
	int sz = sizeof(T);
	if (b.mN<N+a.N) b.sm(N+a.N);
	memcpy(b.x,x,N*sz);b.N	= N;	// ���� ��� ��� ���� ����b
	for(i=0;i<a.N;i++)	// ������ ���� ��������- a
	{		
		r	= a.x[i];
		for(j=0;(j<b.N)&&(b.x[j]!=r);j++);	// ����: ��- � ��� ��� ������� ����b
		if (j==b.N) b.x[b.N++] = r;		// �� �� � ���� ������ b
	}
	return b;
}
//____________________________________
template <class T>
smpl_ms<int> &	smpl_ms<T>::fnd(smpl_ms<int> &in,T a)		// ������� ���� �������'a'.
{
	in.N	= 0;
	for(int i=0;i<N;i++){if (x[i]==a){in.x[in.N++]	= i;}}
	return in;
}
//____________________________________
template <class T>
smpl_ms<int> &	smpl_ms<T>::fnd(smpl_ms<bool> &in,smpl_ms<int> &a)	// ������� �������� ����'in' ������ �'a'.
{
	a.N	= 0;
	for(int i=0;i<in.N;i++){if (in.x[i]==1){a.x[a.N++]	=i;}}
	return a;
}
//____________________________________
template <class W>
ostream & operator << (ostream & stream,const smpl_ms<W> &a)// ����� ��� ���
	{
		for (int i=0;i<a.N;i++)	stream<<a.x[i]<<'\n';
		//stream<<endl;
		return stream;
	}
template <class W>
istream & operator >> (const istream & stream,smpl_ms<W> &a)// ����� ��� ���
	{
		for (int i=0;i<a.N;i++)	stream>>a.x[i];
		return stream;
	}
template <class T>
smpl_ms<int> &	smpl_ms<T>::fnd(smpl_ms<bool> &in,smpl_ms<int> &a,smpl_ms<int> &b)	// ������� �������� ����'in' ������ �'a', ����- �'b'.
{
	a.N	= 0;b.N	= 0;
	for(int i=0;i<in.N;i++){if (in.x[i]==1){a.x[a.N++]	=i;}else{b.x[b.N++]	=i;}}
	return a;
}
//____________________________________
template <class T>
int	smpl_ms<T>::fnd(const T &a)					// ������� ������������ ���� �������'a'
{
	
	for(int i=0;i<N;i++){if (x[i]==a){return i;}}
	return -1;
}
//____________________________________
template <class T>
int	smpl_ms<T>::fnd(const T &a,const T &b)// ����� ��������������� ���'a' �� ���'b'.
{
	for(int i=0;i<N;i++){if ((x[i]!=a)&&(x[i]!=b)) return i;}
	return -1;
}
//____________________________________
template <class T>
void CopyObject(smpl_ms<T> &a,smpl_ms<T> &b)
{
	if (b.mN>a.mN){a.sm(b.mN);}
	a.N	= b.N;
	a.mN= b.mN;
	for(int i=0;i<a.mN;i++)
	{
		CopyObject(a.x[i],b.x[i]);
	}
}
//____________________________________
void CopyObject(smpl_ms<char> &a,smpl_ms<char> &b)
{
	if (b.mN>a.mN){a.sm(b.mN);}
	a.N	= b.N;
	a.mN= b.mN;
	memcpy(a.x,b.x,a.N*sizeof(char));
	/*for(int i=0;i<a.mN;i++)
	{
		CopyObject(a.x[i],b.x[i]);
	}*/
}
//____________________________________
template <class T>
void InitObject(smpl_ms<T> &a)
{
	if (a.mN==0)
	{
		a.x	= new T [1];
		a.mN= 1;
	}
	for(int i=0;i<a.mN;i++)
	{
		InitObject(a.x[i]);
	}
	a.N	= 0;
}
//____________________________________
template <class T>
void ClearObject(smpl_ms<T> &a)
{
	/*if (a.mN!=0)
	{
		for(int i=0;i<a.mN;i++)
		{
			ClearObject(a.x[i]);
		}		
	}*/
	delete [] a.x;
	a.x	= 0x00000000;
	a.N	= 0;
	a.mN= 0;
}
//____________________________________
template <class T>
void	smpl_ms<T>::data2file(char ch)
{
	fstream sss;

	if (ch==' ')
	{
		sss.open("data.txt",ios::out);
	}else
	{
		smpl_ms<char> name("data.txt",10);
		name.add(ch,4);
		sss.open(name.x,ios::out);
	}
	sss.precision(12);
	sss.setf(ios::left);
	sss.setf(ios::scientific);

	sss<<*this;
	sss.close();
}
//____________________________________
template <class T>
void	smpl_ms<T>::data2file(const char *ch)
{
	fstream sss;

	sss.open(ch,ios::out);

	sss.precision(12);
	sss.setf(ios::left);
	sss.setf(ios::scientific);

	sss<<*this;
	sss.close();
}
//____________________________________
//____________________________________


/*
//____________________________________
template <class T>
smpl_ms<T>::smpl_ms(){x	= new T [1]; mN=1;N=0;}//x = (T*)malloc(mN*sizeof(T)); mN=1;N=0;}
//	x	= new T [1]; mN=1;N=0;}
//____________________________________
template <class T>
smpl_ms<T>::smpl_ms(int n){mN=n;N=0;x	= new T [n];}
//____________________________________
template <class T>
void smpl_ms<T>::addm(int n){mN+=n;x = (T*)realloc((void*)x,mN*sizeof(T));}
*/


//____________________________class	smpl_ms______________________________________________________________________________
//_______________________________�������� ����__________________________________________________________






/*
//____________________________class	strng____________________________________________________________________________
//________________________________����� ����_______________________________________________________________
strng::strng()
{
	i	= 0;
	this->N		= 1;
	this->x[0]	= '\0';
}
//____________________________________
strng::strng(const char *a)
{
	i	= strlen(a);
	this->add(a,++i);
	i	= 0;
}
//____________________________________
strng &	strng::operator = (strng	&rhs)
{
	i	= rhs.i;
	if (rhs.N>mN)
	{
		delete [] x;
		mN	= rhs.mN;
		N	= rhs.N;
		x	= new char [mN];
	}
	memcpy(x,rhs.x,sizeof(char)*N);
	return *this;
}
//____________________________________
strng::strng(strng &cpms)	// ���������
{
	i	= cpms.i;
	N	= cpms.N;
	mN	= cpms.mN;
	x	= new char [mN];	
	memcpy(x,cpms.x,N*sizeof(char));
}
//____________________________________

//____________________________class	strng____________________________________________________________________________
//_______________________________�������� ����__________________________________________________________

*/




//____________________________class	ms1D____________________________________________________________________________
//________________________________����� ����_______________________________________________________________
//____________________________________
template <class T>
ms1D<T>::ms1D(int n)				// ��� �������� � 'n' ����.
{
	N	= 0;
	mN	= n;
	x	= new T [mN];
	InitObject(*this);
}
//____________________________________
template <class T>
ms1D<T>::ms1D(T *a,int n)			// ���������������
{	
	mN	= N = n;
	x = new T [mN];	
	//InitObject(*this);
	for(int i=0;i<N;i++)
	{
		CopyObject(x[i],a[i]);
	}
}
//____________________________________
template <class T>
ms1D<T>::ms1D(T *a,int n,int m)		// ���������������� ���
{
	N = n;
	mN= m;
	x = new T [mN];
	for(int i=0;i<N;i++){CopyObject(x[i],a[i]);}
	for(int i=N;i<mN;i++)InitObject(x[i]);
}
//____________________________________
template <class T>
ms1D<T>::ms1D(const ms1D <T> &cpms)		// ���������
{
	/*N	= cpms.N;
	mN	= cpms.mN;
	delete [] x;
	x	= new T [mN];
	memcpy(x,cpms.x,N*sizeof(T));*/
	CopyObject(*this,cpms);
}
// ����
//____________________________________
template <class T>
ms1D<T> &	ms1D<T>::operator =(const ms1D<T> &a)
{
	N	= a.N;
	memcpy(x,a.x,N*sizeof(T));
	return *this;
}
//____________________________________
template <class T>
ms1D<T> &	ms1D<T>::operator =(const T a)
{
	int i;
	for(i=0;i<N;x[i++]=a);
	return *this;
}
//____________________________________
template <class T>
ms1D<T>	ms1D<T>::operator +(const ms1D<T> &a)
{
	static ms1D<T>	b(N);
	if (b.N<N) {b.sm(N);}
	memcpy(b.x,x,N*sizeof(T));
	for(int i=0;i<N;i++){b.x[i]+=a.x[i];}
	b.N	= N;
	return b;
}
//____________________________________
template <class T>
ms1D<T>	ms1D<T>::operator -(ms1D<T> &a)
{
	static ms1D<T>	b(N);
	if (b.N<N) {b.sm(N);}
	memcpy(b.x,x,N*sizeof(T));
	for(int i=0;i<N;i++){b.x[i]-=a.x[i];}
	b.N	= N;
	return b;
}
//____________________________________
template <class T>
ms1D<T>	ms1D<T>::operator *(ms1D<T> &a)
{
	static ms1D<T>	b(N);
	if (b.N<N) {b.sm(N);}
	memcpy(b.x,x,N*sizeof(T));
	for(int i=0;i<N;i++){b.x[i]*=a.x[i];}
	b.N	= N;
	return b;
}
//____________________________________
template <class T>
ms1D<T>	ms1D<T>::operator /(ms1D<T> &a)
{
	static ms1D<T>	b(N);
	if (b.N<N) {b.sm(N);}
	memcpy(b.x,x,N*sizeof(T));
	for(int i=0;i<N;i++){b.x[i]/=a.x[i];}
	b.N	= N;
	return b;
}
//____________________________________
template <class T>
ms1D<T>  ms1D<T>::operator +(T a)
{
	static ms1D<T>	b(N);
	if (b.N<N) {b.sm(N);}
	memcpy(b.x,x,N*sizeof(T));
	for(int i=0;i<N;i++){b.x[i]+=a;}
	b.N	= N;
	return b;
}
//____________________________________
template <class T>
ms1D<T>  ms1D<T>::operator -(T a)
{
	static ms1D<T>	b(N);
	if (b.N<N) {b.sm(N);}
	memcpy(b.x,x,N*sizeof(T));
	for(int i=0;i<N;i++){b.x[i]-=a;}
	b.N	= N;
	return b;
}
//____________________________________
template <class T>
ms1D<T>  ms1D<T>::operator *(T a)
{
	static ms1D<T>	b(N);
	if (b.N<N) {b.sm(N);}
	memcpy(b.x,x,N*sizeof(T));
	for(int i=0;i<N;i++){b.x[i]*=a;}
	b.N	= N;
	return b;
}
//____________________________________
template <class T>
ms1D<T>  ms1D<T>::operator /(T a)
{
	static ms1D<T>	b(N);
	if (b.N<N) {b.sm(N);}
	memcpy(b.x,x,N*sizeof(T));
	for(int i=0;i<N;i++){b.x[i]/=a;}
	b.N	= N;
	return b;
}
//____________________________________
template <class T>
ms1D<T> & ms1D<T>::operator +=(ms1D<T> &a)
{
	for(int i=0;i<N;i++){x[i]+=a.x[i];}
	return *this;
}
//____________________________________
template <class T>
ms1D<T> & ms1D<T>::operator -=(ms1D<T> &a)
{
	for(int i=0;i<N;i++){x[i]-=a.x[i];}
	return *this;
}
//____________________________________
template <class T>
ms1D<T> & ms1D<T>::operator *=(ms1D<T> &a)
{
	for(int i=0;i<N;i++){x[i]*=a.x[i];}
	return *this;
}
//____________________________________
template <class T>
ms1D<T> & ms1D<T>::operator /=(ms1D<T> &a)
{
	for(int i=0;i<N;i++){x[i]/=a.x[i];}
	return *this;
}
//____________________________________
template <class T>
ms1D<T> & ms1D<T>::operator +=(T a)
{
	for(int i=0;i<N;i++){x[i]+=a;}
	return *this;
}
//____________________________________
template <class T>
ms1D<T> & ms1D<T>::operator -=(T a)
{
	for(int i=0;i<N;i++){x[i]-=a;}
	return *this;
}
//____________________________________
template <class T>
ms1D<T> & ms1D<T>::operator *=(T a)
{
	for(int i=0;i<N;i++){x[i]*=a;}
	return *this;
}

template <class T>
ms1D<T> & ms1D<T>::operator /=(T a)
{
	for(int i=0;i<N;i++){x[i]/=a;}
	return *this;
}
//____________________________________
template <class T>
void ms1D<T>::ad1(const T &a,const T &b,const T &d)
{
	int n,i;
	if (b>a)
	{
		n	= (b-a)/d ;
		n++;
		this->init(n);
		for(i=0;i<n;i++)
		{
			x[i] = a+i*d;
		}
	}else
	{
		n	= (a-b)/d ;
		n++;
		this->init(n);
		for(i=0;i<n;i++)
		{
			x[i] = a-i*d;
		}
	}
}
//____________________________________
template <class T>
ms1D<T>	 operator -(ms1D<T> &a)
{
	static ms1D<T> b(a.N);
	if(b.N<a.N){b.sm(a.N);}
	for(int i=0;i<a.N;i++){b.x[i]=-a.x[i];}
	return b;
}
//____________________________________
template <class T>
ms1D<T> operator +(T &a,ms1D<T> &b)
{
	static ms1D<T> c(b.N);
	if (c.N<b.N) {c.sm(b.N);}
	for(int i=0;i<b.N;i++){c.x[i] = a+b.x[i];}
	c.N	= b.N;
	return c;
}
//____________________________________
template <class T>
ms1D<T> operator -(T &a,ms1D<T> &b)
{
	static ms1D<T> c(b.N);
	if (c.N<b.N) {c.sm(b.N);}
	for(int i=0;i<b.N;i++){c.x[i] = a-b.x[i];}
	c.N	= b.N;
	return c;
}
//____________________________________
template <class T>
ms1D<T> operator *(T &a,ms1D<T> &b)
{
	static ms1D<T> c(b.N);
	if (c.N<b.N) {
		c.sm(b.N);
	}
	memcpy(c.x,b.x,b.N*sizeof(T));
	for(int i=0;i<b.N;i++){c.x[i] = a*b.x[i];}
	c.N	= b.N;
	return c;
}
//____________________________________
template <class T>
ms1D<T> operator /(T &a,ms1D<T> &b)
{
	static ms1D<T> c(b.N);
	if (c.N<b.N) {c.sm(b.N);}
	memcpy(c.x,b.x,b.N*sizeof(T));
	for(int i=0;i<b.N;i++){c.x[i] = a/b.x[i];}
	c.N	= b.N;
	return c;
}
//____________________________________
template <class T>
ms1D<bool> ms1D<T>::operator >(ms1D<T> &a)
{
	static ms1D<bool>	b(N);
	if (b.N<N) {b.sm(N);}
	for(int i=0;i<N;i++){b.x[i]=x[i]>a.x[i];}
	b.N	= N;
	return b;
}
//____________________________________
template <class T>
ms1D<bool> ms1D<T>::operator >(T &a)
{
	static ms1D<bool>	b(N);
	if (b.N<N) {b.sm(N);}
	for(int i=0;i<N;i++){b.x[i]=x[i]>a;}
	b.N	= N;
	return b;
}
//____________________________________
template <class T>
void ms1D<T>::one(int n){
	if (mN<n){
		if(mN==0){
			this->sm(n);
			InitObject(*this);
		}else{
			this->adm(n-mN);
		}
	}
	N=n;
}
template <class T>
ms1D<bool> ms1D<T>::operator <(ms1D<T> &a)
{
	static ms1D<bool>	b(N);
	if (b.N<N) {b.sm(N);}
	for(int i=0;i<N;i++){b.x[i]=x[i]<a.x[i];}
	b.N	= N;
	return b;
}
//____________________________________
template <class T>
ms1D<bool> ms1D<T>::operator <(T &a)
{
	static ms1D<bool>	b(N);
	if (b.N<N) {b.sm(N);}
	for(int i=0;i<N;i++){b.x[i]=x[i]<a;}
	b.N	= N;
	return b;
}
//____________________________________
template <class T>
ms1D<bool> ms1D<T>::operator >=(ms1D<T> &a)
{
	static ms1D<bool>	b(N);
	if (b.N<N) {b.sm(N);}
	for(int i=0;i<N;i++){b.x[i]=x[i]>=a.x[i];}
	b.N	= N;
	return b;
}
//____________________________________
template <class T>
ms1D<bool> ms1D<T>::operator >=(T &a)
{
	static ms1D<bool>	b(N);
	if (b.N<N) {b.sm(N);}
	for(int i=0;i<N;i++){b.x[i]=x[i]>=a;}
	b.N	= N;
	return b;
}
//____________________________________
template <class T>
ms1D<bool> ms1D<T>::operator <=(ms1D<T> &a)
{
	static ms1D<bool>	b(N);
	if (b.N<N) {b.sm(N);}
	for(int i=0;i<N;i++){b.x[i]=x[i]<=a.x[i];}
	b.N	= N;
	return b;
}
//____________________________________
template <class T>
ms1D<bool> ms1D<T>::operator <=(T &a)
{
	static ms1D<bool>	b(N);
	if (b.N<N) {b.sm(N);}
	for(int i=0;i<N;i++){b.x[i]=x[i]<=a;}
	b.N	= N;
	return b;
}
//____________________________________
template <class T>
ms1D<bool> ms1D<T>::operator ==(ms1D<T> &a)
{
	static ms1D<bool>	b(N);
	if (b.N<N) {b.sm(N);}
	for(int i=0;i<N;i++){b.x[i]=x[i]==a.x[i];}
	b.N	= N;
	return b;
}
//____________________________________
template <class T>
ms1D<bool> ms1D<T>::operator ==(T &a)
{
	static ms1D<bool>	b(N);
	if (b.N<N) {b.sm(N);}
	for(int i=0;i<N;i++){b.x[i]=x[i]==a;}
	b.N	= N;
	return b;
}
//____________________________________
template <class T>
ms1D<bool> ms1D<T>::operator !=(ms1D<T> &a)
{
	static ms1D<bool>	b(N);
	if (b.N<N) {b.sm(N);}
	for(int i=0;i<N;i++){b.x[i]=x[i]!=a.x[i];}
	b.N	= N;
	return b;
}
//____________________________________
template <class T>
ms1D<bool> ms1D<T>::operator !=(T &a)
{
	static ms1D<bool>	b(N);
	if (b.N<N) {b.sm(N);}
	for(int i=0;i<N;i++){b.x[i]=x[i]!=a;}
	b.N	= N;
	return b;
}
//____________________________________
template <class T>
ms1D<bool> operator >(T a,ms1D<T>	&b)
{
	static ms1D<bool>	c(b.N);
	if (c.N<b.N) {c.sm(b.N);}
	for(int i=0;i<b.N;i++){c.x[i]=a>b.x[i];}
	c.N	= b.N;
	return c;
}
//____________________________________
template <class T>
ms1D<bool> operator <(T a,ms1D<T>	&b)
{
	static ms1D<bool>	c(b.N);
	if (c.N<b.N) {c.sm(b.N);}
	for(int i=0;i<b.N;i++){c.x[i]= a<b.x[i];}
	c.N	= b.N;
	return c;
}
//____________________________________
template <class T>
ms1D<bool> operator >=(T a,ms1D<T>	&b)
{
	static ms1D<bool>	c(b.N);
	if (c.N<b.N) {c.sm(b.N);}
	for(int i=0;i<b.N;i++){c.x[i]= a>=b.x[i];}
	c.N	= b.N;
	return c;
}
//____________________________________
template <class T>
ms1D<bool> operator <=(T a,ms1D<T>	&b)
{
	static ms1D<bool>	c(b.N);
	if (c.N<b.N) {c.sm(b.N);}
	for(int i=0;i<b.N;i++){c.x[i]= a<=b.x[i];}
	c.N	= b.N;
	return c;
}
//____________________________________
template <class T>
ms1D<bool> operator ==(T a,ms1D<T>	&b)
{
	static ms1D<bool>	c(b.N);
	if (c.N<b.N) {c.sm(b.N);}
	for(int i=0;i<b.N;i++){c.x[i]= a==b.x[i];}
	c.N	= b.N;
	return c;
}
//____________________________________
template <class T>
ms1D<bool> operator !=(T a,ms1D<T>	&b)
{
	static ms1D<bool>	c(b.N);
	if (c.N<b.N) {c.sm(b.N);}
	for(int i=0;i<b.N;i++){c.x[i]= a!=b.x[i];}
	c.N	= b.N;
	return c;
}
//____________________________________
template <class T>
ostream &	operator <<(ostream &stream, ms1D<T> &a)
{
	for(int i=0;i<a.N;i++)
	{
		stream<<a.x[i]<<"  ";
	}
	stream<<endl;
	return stream;
}
//____________________________________
template <class T>
istream &	operator >>(istream &stream, ms1D<T> &a)
{
	for(int i=0;i<a.N;i++)	stream>>a.x[i];	
	return stream;
}
//____________________________________
template <class T>
int ms1D<T>::mmin()
{
	T m;
	m	= *x;
	int j,i;
	j	= 0;
	for (i	= 1;i<N;i++){if (m>x[i]){m	= x[i]; j	= i;}}
	return j;
}
//____________________________________
template <class T>
int ms1D<T>::mmin(T &m)
{
	m	= *x;
	int j,i;
	j	= 0;
	for (i	= 1;i<N;i++){if (m>x[i]){m	= x[i]; j	= i;}}
	return j;
}
//____________________________________
template <class T>
int ms1D<T>::mmax()
{
	T m;
	m	= *x;
	int j,i;
	j	= 0;
	for (i	= 1;i<N;i++){if (m<x[i]){m	= x[i]; j	= i;}}
	return j;
}
//____________________________________
template <class T>
int ms1D<T>::mmax(T &m)
{
	m	= *x;
	int j,i;
	j	= 0;
	for (i	= 1;i<N;i++){if (m<x[i]){m	= x[i]; j	= i;}}
	return j;
}
//____________________________________
template <class T>
void ms1D<T>::sort()	// ����� ����� �����. (���:-) 
{					// ���� ��� ���� ����������� ��� 
	static int i;
	static T b;
	static bool ch;
	do
	{
		ch	= false;
		for (i=0;i<N-1;i++)
		if(x[i]>x[i+1])
			{
			b		= x[i];
			x[i]	= x[i+1];
			x[i+1]= b; 
			ch	= true;
		}
	}while(ch);
}
//____________________________________
template <class T>
void ms1D<T>::sort(ms1D<T> &a)	// ����� ����� �����. (���:-) 
{							// ���� 'a' ���� ����������� ���
	if (a.N<N) a.sm(N);
	memcpy(a.x,x,sizeof(T)*N);
	a.N	= N;
	static int i;
	static T b;
	static bool ch;
	do
	{
		ch	= false;
		for (i=0;i<N-1;i++)
		if(a.x[i]>a.x[i+1])
			{
			b		= a.x[i];
			a.x[i]	= a.x[i+1];
			a.x[i+1]= b; 
			ch	= true;
		}
	}while(ch);
}
//____________________________________
template <class T>
void ms1D<T>::sort(ms1D<T> &a, ms1D<int> &j)	// ����� ����� �����. (���:-)
{					// ���� 'a' ���� ����������� ���, ��'j' ��� ������
	if (a.N<N) a.sm(N);
	memcpy(a.x,x,sizeof(T)*N);
	a.N	= N;
	static int i,k;
	static T b;
	static bool ch;	
	do
	{
		ch	= false;
		for (i=0;i<N-1;i++)
		if(a.x[i]>a.x[i+1])
		{
			b		= a.x[i];
			a.x[i]	= a.x[i+1];
			a.x[i+1]= b; 
			k		= j.x[i];
			j.x[i]	= j.x[i+1];
			j.x[i+1]= k;
			ch	= true;
		}
	}while(ch);
}
void sort_(ms1D<int> &j);	// ����� ���;  �'j' - ��� ����� 'a'.
//____________________________________
template <class T>
void ms1D<T>::sort_(ms1D<int> &j)	// ����� ���;  �'j' - ��� ����� 'a'.
{
	int i,k;
	T b;
	bool ch;
	do
	{
		ch	= false;
		for (i=0;i<N-1;i++)
		if(x[i]>x[i+1])
		{
			b		= x[i];
			x[i]	= x[i+1];
			x[i+1]= b;
			k		= j.x[i];
			j.x[i]	= j.x[i+1];
			j.x[i+1]= k;
			ch	= true;
		}
	}while(ch);
}

//____________________________________
/*template <class T>
ms1D<T>& ms1D<T>::ind(ms1D<int> &in, ms1D<T> &a)	// ��� ���� 'a' ���� ��������� � ����'in';
{
	a.N	= in.N;
	for(int i=0;i<a.N;i++){a.x[i]	= x[in.x[i]];}
	return a;
}
//____________________________________
template <class T>
ms1D<T>	&	ms1D<T>::ind(const int & i1,const int & i2,ms1D<T> &a)	// ��� ���� 'a' ���� �������������i1 � i2.
{
	a.N	= i2-i1;
	for(int i=0;i<a.N;i++){a.x[i]	= x[i+i1];}
	return a;
}*/
//____________________________________
template <class T>
inline ms1D<T> &	ms1D<T>::its(ms1D<T> & a,ms1D<T> & b)		// ������'b' �������������������'a'.
{

	b.N	= 0;
	int i,j;
	for(i=0;i<N;i++)
	{
		for(j=0;(j<b.N)&&(x[i]!=b.x[j]);j++);	// ����: ��- � ��� ��� �����������
		if (j==b.N)
		{										// �� �� � ���� ����� ��������
			for(j=0;(j<a.N)&&(x[i]!=a.x[j]);j++); // ����������'a'.
			if (j<a.N) {b.x[b.N++] = x[i];}
		}
	}
	return b;
}
//____________________________________
template <class T>
inline ms1D<T> &	ms1D<T>::uni(ms1D<T> & a,ms1D<T> & b)		// ������b ����� �������������'a'.
{
	T r;
	int i,j;
	if (b.mN<N+a.N) b.sm(N+a.N);
	memcpy(b.x,x,N*sizeof(T));b.N	= N;	// ���� ��� ��� ���� ����b
	for(i=0;i<a.N;i++)	// ������ ���� ��������- a
	{		
		r	= a.x[i];
		for(j=0;(j<b.N)&&(b.x[j]!=r);j++);	// ����: ��- � ��� ��� ������� ����b
		if (j==b.N) b.x[b.N++] = r;		// �� �� � ���� ������ b
	}
	return b;
}
//____________________________________
template <class T>
inline ms1D<T> &	ms1D<T>::itss(ms1D<T> & a,ms1D<T> & b)		// ������'b' �������������������'a'.
{
	b.N	= 0;
	if ((smpl_ms<T>::N==0)||(a.N==0)) // если хоть один массив пустой - возвратить пустой массив, пересечение - нулевое
	{	
		return b;
	}
	
	T c;
	int i,j;
	j	= 0;
	if ((a.x[0]>smpl_ms<T>::x[smpl_ms<T>::N-1])||(smpl_ms<T>::x[0]>a.x[a.N-1])) return b;
	c	= smpl_ms<T>::x[0];
	for(i=0;(i<smpl_ms<T>::N)&&(j<a.N);i++)
	{
		if ((smpl_ms<T>::x[i]==a.x[j])&&((smpl_ms<T>::x[i]!=c)||(b.N==0))) {c = b.x[b.N++]=smpl_ms<T>::x[i];j++;}
		else
		{
			while((smpl_ms<T>::x[i]>a.x[j])&&(j<a.N-1)){j++;}
			if ((smpl_ms<T>::x[i]==a.x[j])&&((smpl_ms<T>::x[i]!=c)||(b.N==0))) {c = b.x[b.N++]=smpl_ms<T>::x[i];j++;}
		}
	}
	
	return b;
}
/*	T c;
	b.N	= 0;
	int i,j;
	j	= 0;
	if ((a.x[0]>x[N-1])||(x[0]>a.x[a.N-1])) return b;
	c	= x[0];
	for(i=0;(i<N)&&(j<a.N);i++)
	{
		if ((x[i]==a.x[j])&&((x[i]!=c)||(b.N==0))) {c = b.x[b.N++]=x[i];j++;}
		else
		{
			while((x[i]>a.x[j])&&(j<a.N-1)){j++;}
			if ((x[i]==a.x[j])&&((x[i]!=c)||(b.N==0))) {c = b.x[b.N++]=x[i];j++;}
		}
	}
	
	return b;
}/**/
//____________________________________
template <class T>
inline ms1D<T> &	ms1D<T>::unis(ms1D<T> & a,ms1D<T> & b)		// ������b ����� �������������'a'.
{
	b.N	= 0;
	if ((smpl_ms<T>::N>0)&&(a.N>0))
	{
		if (a.x[0]>smpl_ms<T>::x[smpl_ms<T>::N-1])
		{
			memcpy(b.x,smpl_ms<T>::x,smpl_ms<T>::N*sizeof(T));
			memcpy(b.smpl_ms<T>::x+smpl_ms<T>::N,a.x,a.N*sizeof(T));
			b.N=smpl_ms<T>::N+a.N;
			return b;
		}
		if (smpl_ms<T>::x[0]>a.x[a.N-1])
		{
			memcpy(b.x,a.x,a.N*sizeof(T));
			memcpy(b.x+a.N,smpl_ms<T>::x,smpl_ms<T>::N*sizeof(T));
			b.N=smpl_ms<T>::N+a.N;
			return b;
		}
		T c;
		int j;
		j	= 0;
		c	= smpl_ms<T>::x[0];
		for(int i=0;i<smpl_ms<T>::N;i++)
		{
			if ((j<a.N)&&(smpl_ms<T>::x[i]==a.x[j])&&((smpl_ms<T>::x[i]!=c)||(b.N==0))) {c = b.x[b.N++]=smpl_ms<T>::x[i];j++;}			
			else
			{
				while((j<a.N)&&(smpl_ms<T>::x[i]>=a.x[j]))
				{
					if ((a.x[j]!=c)||(b.N==0)) c = b.x[b.N++]=a.x[j++];
				}
				if ((smpl_ms<T>::x[i]!=c)||(b.N==0)) {c = b.x[b.N++]=smpl_ms<T>::x[i];}
			}
		}
		while((j<a.N)&&(smpl_ms<T>::x[smpl_ms<T>::N-1]<a.x[j]))
		{
			if ((a.x[j]!=c)||(b.N==0)) c = b.x[b.N++]=a.x[j++];
		}
	}else
	{
		if (smpl_ms<T>::N==0) // если текщий массив пустой - вернуть массив 'a'
		{	
			memcpy(b.x,a.x,a.N*sizeof(T));
			b.N	= a.N;
			return b;
		}else  // иначе - вернуть текущий массив
		{ 
			memcpy(b.x,smpl_ms<T>::x,smpl_ms<T>::N*sizeof(T));
			b.N	= smpl_ms<T>::N;
			return b;
		}
	}

	return b;
}
/*	T c;
	b.N	= 0;
	int i,j,sz;
	j	= 0;
	sz	= sizeof(T);
	if (N>0)
	{
		if (a.x[0]>x[N-1])
		{
			memcpy(b.x,x,N*sz);
			memcpy(b.x+N,a.x,a.N*sz);
			b.N=N+a.N;
			return b;
		}
		if (x[0]>a.x[a.N-1])
		{
			memcpy(b.x,a.x,a.N*sz);
			memcpy(b.x+a.N,x,N*sz);
			b.N=N+a.N;
			return b;
		}
		c	= x[0];
		for(i=0;i<N;i++)
		{
			if ((x[i]==a.x[j])&&((x[i]!=c)||(b.N==0))) {c = b.x[b.N++]=x[i];j++;}
			else
			{
				while((x[i]>=a.x[j])&&(j<a.N))
				{
					if ((a.x[j]!=c)||(b.N==0)) c = b.x[b.N++]=a.x[j++];
				}
				if ((x[i]!=c)||(b.N==0)) {c = b.x[b.N++]=x[i];}
			}
		}
		while((x[N-1]<a.x[j])&&(j<a.N))
		{
			if ((a.x[j]!=c)||(b.N==0)) c = b.x[b.N++]=a.x[j++];
		}
	}
	else
	{
		memcpy(b.x,a.x,a.N*sz);
		b.N	= a.N;
	}
	return b;
}/**/
//____________________________________
template <class T>
ms1D<int> &	ms1D<T>::fnd(ms1D<int> &in,T a)		// ������� ���� �������'a'.
{
	in.N	= 0;
	for(int i=0;i<N;i++){if (x[i]==a){in.x[in.N++]	= i;}}
	return in;
}
//____________________________________
template <class T>
ms1D<int> &	ms1D<T>::fnd(ms1D<bool> &in,ms1D<int> &a)	// ������� �������� ����'in' ������ �'a'.
{
	a.N	= 0;
	for(int i=0;i<in.N;i++){if (in.x[i]==1){a.x[a.N++]	=i;}}
	return a;
}
//____________________________________
template <class T>
ms1D<int> &	ms1D<T>::fnd(ms1D<bool> &in,ms1D<int> &a,ms1D<int> &b)	// ������� �������� ����'in' ������ �'a', ����- �'b'.
{
	a.N	= 0;b.N	= 0;
	for(int i=0;i<in.N;i++){if (in.x[i]==1){a.x[a.N++]	=i;}else{b.x[b.N++]	=i;}}
	return a;
}
//____________________________________
template <class T>
int	ms1D<T>::fnd(T &a)					// ������� ������������ ���� �������'a'
{
	for(int i=0;i<N;i++){if (x[i]==a){return i;}}
	return -1;
}
//____________________________________
template <class T>
int	ms1D<T>::fnd(T &a,T &b)// ����� ��������������� ���'a' �� ���'b'.
{
	for(int i=0;i<N;i++){if ((x[i]!=a)&&(x[i]!=b)) return i;}
	return -1;
}
//____________________________________
template <class T>
T	ms1D<T>::sum()
{
	T S;
	S	= *x;
	for (int i=1;i<N;i++){S	+= x[i];}
	return S;
}
//____________________________________
template <class T>
T	ms1D<T>::sqs()
{
	T S,s_;
	S	*= S	= *x;
	for (int i=1;i<N;i++){S	+= s_	*=	s_	= x[i];}
	return S;
}
//____________________________________
template <class T>
T	ms1D<T>::nrm()
{
	T S,s_;
	S	*= S	= *x;
	for (int i=1;i<N;i++){S	+= s_	*=	s_	= x[i];}
	return sqrt(S);
}
//____________________________________
template <class T>
void ms1D<T>::Nrm()
{
	T S,s_;
	int	i;
	S	*= S	= *x;
	for (i=1;i<N;i++){S	+= s_	*=	s_	= x[i];}
	S	= sqrt(S);
	for (i=0;i<N;i++){x[i]	/= S;}
}
//____________________________________
template <class T>
void ms1D<T>::Nrm(T &a)
{
	T S,s_;
	int i;
	S	*= S	= *x;
	for (i=1;i<N;i++){S	+= s_	*=	s_	= x[i];}
	S	= sqrt(S);
	for (i=0;i<N;i++){x[i]	/= S;}
	a=S;
}

//____________________________________
template <class T>
T	ms1D<T>::spr(ms1D<T>	&a)	// ���� ���������� 'a' �'b'
{
	T S;
	S	= a.x[0]*x[0];
	for(int i=1;i<N;i++){S	+= a.x[i]*x[i];}
	return S;
}
//____________________________________
template <class T>
void CopyObject(ms1D<T> &a,const ms1D<T> &b)
{
	if(a.mN != 0) delete [] a.x;
	a.x	= new T [b.mN];
	a.N	= b.N;
	a.mN= b.mN;
	for(int i=0;i<a.mN;i++)
	{
		CopyObject(a.x[i],b.x[i]);
	}
}
//____________________________________
void CopyObject(ms1D<int> &a,const ms1D<int> &b)
{
	if(a.mN < b.mN) a.adm_(b.mN-a.mN);
	a.N	= b.N;
	a.mN= b.mN;
	memcpy(a.x,b.x,a.N*sizeof(int));
	/*for(int i=0;i<a.mN;i++)
	{
		CopyObject(a.x[i],b.x[i]);
	}*/
}
//____________________________________
/**/template <class T>
void InitObject(ms1D<T> &a)
{
	if (a.mN==0)
	{
		a.x	= new T [1];
		//a.N	= 0;
		a.mN= 1;
	}
	for(int i=0;i<a.mN;i++)
	{
		InitObject(a.x[i]);
	}
	a.N	= 0;
}/**/
//____________________________________
template <class T>
void ClearObject(ms1D<T> &a)
{
	if (a.mN!=0)
	{
		for(int i=0;i<a.mN;i++)
		{
			ClearObject(a.x[i]);
		}
		delete [] a.x;
		a.x	= 0x00000000;
	}
	a.N	= 0;
	a.mN= 0;
}
//____________________________________



//____________________________class	ms1D____________________________________________________________________________
//_______________________________�������� ����__________________________________________________________


#endif

//____________________________________
