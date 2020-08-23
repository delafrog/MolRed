#ifndef _TRIMESH_H
#define _TRIMESH_H

#include "volume.h"
#include "init.h"
#include "massiv.h"

extern bool nondelete;
//------ �������� ���� ���������������--------------------------------
class SPoint	// ���������
{public:
	Vec3db		crd;	// �����
	Vec3db		nor;	// ���
	double		area;	// ��� ������������������� ����
	p_ms1Dint	n_edg;	// �� ����� � ���
	p_ms1Dint	n_fc;	// ������ ����� � ���
	p_ms1Dint	n_cbs;	// ��� �������� ���
	Vec3int		stp;	// ����� ������� ����������(����� �������)
	Vec3db		clr;	// �� ���

	bool		sfr;	// ���������� ���� ���� ������� �����

	int			cbn;	// ����� �����������
	int			edg1;	// ����. �����������
	int			edg2;	// �������� ��������� ���
	bool		cmb;	// ���� � � �������� �� � �� ��� ������

	void SetPoint(Vec3db &p1, Vec3db &n1, Vec3int &type, const int &e1, const int &e2, const int &f);	// ����� �������
	void SetPoint(Vec3db &p1, Vec3db &n1, Vec3int &type, const int &e1, const int &e2, const int &e3, const int &f1, const int &f2);	// �����

	SPoint & operator = (SPoint &a)	// ����� �����������
	{
		n_edg->pst(*a.n_edg);
		n_fc->pst(*a.n_fc);
		n_cbs->pst(*a.n_cbs);
		crd	= a.crd;
		nor	= a.nor;
		stp	= a.stp;
		clr	= a.clr;
		sfr	= a.sfr;

		cbn	= a.cbn;
		edg1= a.edg1;
		edg2= a.edg2;
		cmb	= a.cmb;
		return *this;
	}
	void Swap(SPoint &a);

	friend ostream &	operator << (ostream &stream, SPoint &a); // ���� ��� �� ������
	friend istream &	operator >> (istream &stream, SPoint &a); // ���� ����� ������

	friend void CopyObject(SPoint &a,SPoint &b);
	friend void InitObject(SPoint &a);
	friend void ClearObject(SPoint &a);	

	SPoint()
	{
		n_cbs = n_fc = n_edg = 0x00000000;
		sfr	= true;
	}
	~SPoint(){if(!nondelete) ClearObject(*this);}
};

class SEdge			// ������� ������ ���������
{public:
	Vec2int n_pnt;	// ��� ���� ��� ���
	Vec2int	n_fc;	// ��� ������� � ���������� ����
	bool	sfr;	// ������������ ��� ������� ������� �����- ������ ��������
	bool	bnd;	// ���������� ��� �� �������� � 'bnd = true'.
	int		sb;		// �������� �����
	void SetEdge(const int &p1,const int &p2,const int &f1,const int &f2,const int &s);	// �������������
	SEdge & operator = (SEdge &a)
	{
		n_pnt	= a.n_pnt;
		n_fc	= a.n_fc;
		sfr		= a.sfr;
		bnd		= a.bnd;
		sb		= a.sb;
		return *this;
	}

	void Swap(SEdge &a);

	friend ostream &	operator <<(ostream &stream, SEdge &a); // ���� ��� �� ������
	friend istream &	operator >>(istream &stream, SEdge &a); // ���� ����� ������

	friend void CopyObject(SEdge &a,SEdge &b);
	friend void InitObject(SEdge &a);
	friend void ClearObject(SEdge &a);

	SEdge(){}
	~SEdge(){}
};

class STriangle		// ����� ������� ���� 
{public:
	Vec3int n_pnt;
	Vec3int n_edg;
	double	area;	// ��� ������
	bool	sfr;	// ������������ ��� �� ���������� ������� �����- ������ ��������

	void SetTriangle(const int &p1,const int &p2,const int &p3,const int &e1,const int &e2,const int &e3);	// ����� ���������
	STriangle &	operator =(STriangle &a)
	{
		n_pnt	= a.n_pnt;
		n_edg	= a.n_edg;
		sfr		= a.sfr;	
		return *this;
	}

	void Swap(STriangle &a);

	friend ostream &	operator <<(ostream &stream, STriangle &a); // ���� ��� �� ���������
	friend istream &	operator >> (istream & stream,STriangle &a); // ���� ����� ���������

	friend void CopyObject(STriangle &a,STriangle &b);
	friend void InitObject(STriangle &a);
	friend void ClearObject(STriangle &a);	

	STriangle(){}
	~STriangle(){}
};

class BndrEdg	// �������������
{public:
	ms1Dint bn;	// ���� � ��� �������
	BndrEdg &	operator =(BndrEdg &a)
	{
		bn.pst(a.bn);
		return *this;
	}
	friend ostream &	operator <<(ostream &stream, BndrEdg &a) // ���� ��� �� ���������
	{
		stream << a.bn.N<<endl;
		stream << a.bn;
		return stream;
	}
	friend istream &	operator >> (istream & stream,BndrEdg &a) // ���� ����� ���������
	{
			stream >> a.bn.N;
			if (a.bn.N>a.bn.mN) a.bn.sm(a.bn.N);
			stream >> a.bn;
			return stream;
	}

	void Swap(BndrEdg &a);

	friend void CopyObject(BndrEdg &a,BndrEdg &b);
	friend void InitObject(BndrEdg &a);
	friend void ClearObject(BndrEdg &a);	

	BndrEdg(){}
	BndrEdg(int i){bn.sm(i);}
	~BndrEdg(){}
};

typedef SPoint*		p_SPoint;
typedef SEdge*		p_SEdge;
typedef STriangle*	p_STriangle;
typedef BndrEdg*	p_BndrEdg;

class TrSurface	// �������� �����
{public:
	ms1D<SPoint>	Point;	// � ��� �������������
	ms1D<SEdge>		Edge;	// � ��� ������
	ms1D<STriangle>	Trngl;	// � ��� �����������
	ms1D<BndrEdg>	BndEd;	// � ��� �����������

	TrSurface &	operator =(TrSurface &a)
	{
		Point	= a.Point;
		Edge	= a.Edge;
		Trngl	= a.Trngl;
		BndEd	= a.BndEd;
		return *this;
	}

	//bool GetOrient();	// определяет интегральную ориентацию поверхности - внутрь (fslse) или наружу (true).
	double GetVolume();	// определяет объём полости ограниченный поверхностью. Если возвращаемое значение отрицательно, то ориентация поверхности внутрь полости, иначе - наружу.

	void Swap(TrSurface &a);

	void init(Vec3db &p1,Vec3db &p2, Vec3db &p3, Vec3db &n1, Vec3db &n2, Vec3db &n3, Vec3int &t1, Vec3int &t2,  Vec3int &t3); // ������, ���� ������ ����������'p1,p2,p3'.

	friend ostream &	operator <<(ostream &stream, TrSurface &a); // ���� ��� �� ���������
	friend istream &	operator >>(istream &stream, TrSurface &a); // ���� ��� �� ���������

	void Surf2vrml(); // ������ ������ ����� ���� VRML- ����.
	void SrfT2vrml(); // ������ ������ ����� ���� VRML- ����.
	void SrfA2vrml(); // ������ ������ ����� ���� VRML- ����.
	void Surf2vrml(double &ro); // ������ ������ ����� ���� VRML- ����.

	void SrfA2vrml(smschar &fname,bool f); // ������ ������ ����� ���� VRML- ����.
	void Surf2vrml(smschar &fname, Vec3db &clr, bool f); // ������ ������ ����� ���� VRML- ����.

	void Surf2msms();

	void ClearSurface();		// ���������

	friend void CopyObject(TrSurface &a,TrSurface &b);
	friend void InitObject(TrSurface &a);
	friend void ClearObject(TrSurface &a);	

	TrSurface();
	TrSurface(const int &Npoint);
	~TrSurface(){}
};

//-------------------------------------------------------------------------------------------------
#endif
