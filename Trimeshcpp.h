#ifndef _TRIMESH_CPP
#define _TRIMESH_CPP

#include "Trimesh.h"
#include <fstream>
using namespace std;

//--------����� ����SPoint----------
//____________________________________
void SPoint::Swap(SPoint &a)
{
	n_edg->swp(*a.n_edg);
	n_fc->swp(*a.n_fc);
	n_cbs->swp(*a.n_cbs);
	Vec3db x;
	x	= crd; crd = a.crd; a.crd = x;
	x	= nor; nor = a.nor; a.nor = x;
	Vec3int y;
	y = stp; stp = a.stp; a.stp = y;
	int i;
	i = cbn; cbn = a.cbn; a.cbn = i;
	i = edg1;edg1= a.edg1;a.edg1= i;
	i = edg2;edg2= a.edg2;a.edg2= i;	
	bool ch;
	ch = cmb; cmb = a.cmb; a.cmb = ch;
}
//____________________________________
ostream &	operator <<(ostream &stream, SPoint &a)
{
	stream.width(17);
	stream << a.crd;
	stream << a.nor;
	stream << a.stp;
	stream << a.n_edg->N<<endl<<*a.n_edg;
	stream << a.n_fc->N<<endl<<*a.n_fc;
	stream << a.n_cbs->N<<endl<<*a.n_cbs;
	stream << a.edg1<<"  "<<a.edg2<<"  "<<a.cbn<<"  "<<a.cmb<<endl<<endl;	
	return stream;
}
//____________________________________
istream &	operator >>(istream &stream, SPoint &a)
{
	int i;
	stream >> a.crd;
	stream >> a.nor;
	stream >> a.stp;
	stream >> a.n_edg->N;
	if (a.n_edg->mN>a.n_edg->N) a.n_edg->sm(a.n_edg->N);
	stream >> *a.n_edg;
	stream >> a.n_fc->N;
	if (a.n_fc->mN>a.n_fc->N) a.n_fc->sm(a.n_fc->N);
	stream >> *a.n_fc;
	stream >> a.n_cbs->N;
	if (a.n_cbs->mN>a.n_cbs->N) a.n_cbs->sm(a.n_cbs->N);
	stream >> *a.n_cbs;

	stream >> a.edg1;
	stream >> a.edg2;
	stream >> a.cbn;
	stream >> i;
	a.cmb	= i==0 ? false :true;
	return stream;
}
//____________________________________
void SPoint::SetPoint(Vec3db &p1, Vec3db &n1, Vec3int &type, const int &e1, const int &e2, const int &f)	// ����� �������
{
	crd		= p1;
	nor		= n1;

	stp		= type;

	n_edg->one(2);
	n_fc->one(1);
	n_edg->x[0]	= e1;
	n_edg->x[1]	= e2;
	n_fc->x[0]	= f;
	edg1	= e1;
	edg2	= e2;
	cmb		= true;
}
//____________________________________
void SPoint::SetPoint(Vec3db &p1, Vec3db &n1, Vec3int &type, const int &e1, const int &e2, const int &e3, const int &f1, const int &f2)	// �����
{
	crd	= p1;
	nor	= n1;

	stp		= type;

	n_edg->one(3);
	n_fc->one(2);
	n_edg->x[0]	= e1;
	n_edg->x[1]	= e2;
	n_edg->x[2]	= e3;
	n_fc->x[0]	= f1;
	n_fc->x[1]	= f2;
	edg1	= e1;
	edg2	= e3;
	cmb		= true;
}
//____________________________________
void CopyObject(SPoint &a,SPoint &b)
{
	ms1Dint *an_edg,*an_fc;
	an_edg	= a.n_edg;
	an_fc	= a.n_fc;
	memcpy(&a,&b,sizeof(SPoint));
	a.n_edg	= an_edg;
	a.n_fc	= an_fc;
	a.n_edg->pst(*b.n_edg);
	a.n_fc->pst(*b.n_fc);
	a.n_cbs->pst(*b.n_cbs);
}
//____________________________________
void InitObject(SPoint &a)
{
	memset(&a,0,sizeof(SPoint));
	a.n_edg		= new ms1Dint [1];
	a.n_fc		= new ms1Dint [1];	
	a.n_cbs		= new ms1Dint [1];	
	InitObject(a.n_edg[0]);
	InitObject(a.n_fc[0]);
	InitObject(a.n_cbs[0]);
	a.sfr		= true;
}
//____________________________________
void ClearObject(SPoint &a)
{
//	ClearObject(*a.n_edg);
//	ClearObject(*a.n_fc);
//	ClearObject(*a.n_cbs);
	delete [] a.n_edg;
	delete [] a.n_fc;
	delete [] a.n_cbs;
	memset(&a,0,sizeof(SPoint));
}	
//____________________________________

//----------����� ����SEdge---------
//_____________________________________
void SEdge::Swap(SEdge &a)
{
	Vec2int x;
	x = n_pnt; n_pnt = a.n_pnt; a.n_pnt = x;
	x = n_fc; n_fc = a.n_fc; a.n_fc = x;	
	bool i;
	i = bnd; bnd = a.bnd; a.bnd = i;
	int j;
	j = sb; sb = a.sb; a.sb = j;
}
//_____________________________________
ostream &	operator <<(ostream &stream, SEdge &a) // ���� ��� �� ������
{
	stream << a.n_pnt;
	stream << a.n_fc;
	stream << a.bnd<<"  "<<a.sb<<endl<<endl;
	return stream;
}//_____________________________________
istream &	operator >>(istream &stream, SEdge &a) // ���� ��� �� ������
{
	int	i;
	stream >> a.n_pnt;
	stream >> a.n_fc;
	stream >> i;a.bnd= i==0 ? false : true;
	stream >> a.sb;
	return stream;
}
//_____________________________________
void SEdge::SetEdge(const int &p1, const int &p2, const int &f1, const int &f2, const int &s)	// �������������
{
	n_pnt.x[0]	= p1;
	n_pnt.x[1]	= p2;
	n_fc.x[0]	= f1;
	n_fc.x[1]	= f2;
	sb			= s;
	bnd			= (f2==-1);
}
//____________________________________
void CopyObject(SEdge &a,SEdge &b)
{
	memcpy(&a,&b,sizeof(SEdge));
}
//____________________________________
void InitObject(SEdge &a)
{
	memset(&a,0,sizeof(SEdge));
}
//____________________________________
void ClearObject(SEdge &a)
{
	memset(&a,0,sizeof(SEdge));
}
//_____________________________________


//----------����� ����STriangle--------
//_____________________________________
ostream &	operator <<(ostream &stream, STriangle &a)
{
	stream	<< a.n_pnt;
	stream	<< a.n_edg<<endl;
	return stream;
}
//_____________________________________
istream &	operator >>(istream &stream, STriangle &a)
{
	stream	>> a.n_pnt;
	stream	>> a.n_edg;
	return stream;
}
//_____________________________________
void STriangle::SetTriangle(const int &p1, const int &p2, const int &p3, const int &e1, const int &e2, const int &e3)
{
	n_pnt.x[0]	= p1;
	n_pnt.x[1]	= p2;
	n_pnt.x[2]	= p3;
	n_edg.x[0]	= e1;
	n_edg.x[1]	= e2;
	n_edg.x[2]	= e3;
}
//____________________________________
void CopyObject(STriangle &a,STriangle &b)
{
	memcpy(&a,&b,sizeof(STriangle));
}
//____________________________________
void InitObject(STriangle &a)
{
	memset(&a,0,sizeof(STriangle));
}
//____________________________________
void ClearObject(STriangle &a)
{
	memset(&a,0,sizeof(STriangle));
}
//------------����� ����BndrEdg----------
//_____________________________________
void CopyObject(BndrEdg &a,BndrEdg &b)
{
	a.bn.pst(b.bn);
}
//_____________________________________
void InitObject(BndrEdg &a)
{
	InitObject(a.bn);	
}
//_____________________________________
void ClearObject(BndrEdg &a)
{
	ClearObject(a.bn);
}
//_____________________________________

//------����� ����TrSurface------------
//_____________________________________
ostream &	operator <<(ostream &stream, TrSurface &a)
{
	int i;
	stream <<endl<<a.Point.N<<endl;
	stream.precision(15);
	for (i=0;i<a.Point.N;i++) stream<<a.Point.x[i];
	stream <<endl<<a.Edge.N<<endl;
	for (i=0;i<a.Edge.N;i++) stream<<a.Edge.x[i];
	stream <<endl<<a.Trngl.N<<endl;
	for (i=0;i<a.Trngl.N;i++) stream<<a.Trngl.x[i];
	stream <<endl<<a.BndEd.N<<endl;
	for (i=0;i<a.BndEd.N;i++) stream<<a.BndEd.x[i];
	return stream;
}
//_____________________________________
istream &	operator >>(istream &stream, TrSurface &a)
{
	int i;
	stream >> i;
	a.Point.one(i);
	stream.precision(15);
	for (i=0;i<a.Point.N;i++) stream>>a.Point.x[i]; 
	stream >> i;
	a.Edge.one(i);
	for (i=0;i<a.Edge.N;i++) stream>>a.Edge.x[i];
	stream >> i;
	a.Trngl.one(i);
	for (i=0;i<a.Trngl.N;i++) stream>>a.Trngl.x[i];
	stream >> i;
	a.BndEd.one(i);
	for (i=0;i<a.BndEd.N;i++) stream>>a.BndEd.x[i];
	return stream;
}
//_____________________________________
TrSurface::TrSurface()
{
}
//_____________________________________
TrSurface::TrSurface(const int &NPoint)
{
	Point.sm(NPoint);
	Trngl.sm(2*NPoint);
	Edge.sm(3*NPoint);
	BndEd.sm(10);
}
//_____________________________________
void TrSurface::init(Vec3db &p1,Vec3db &p2, Vec3db &p3, Vec3db &n1, Vec3db &n2, Vec3db &n3, Vec3int &t1,  Vec3int &t2,  Vec3int &t3) // ������, ���� ������ ����������'p1,p2,p3'.
{
	const int nnf	= -1;
	const int a0=0,a1=1,a2=2;


	Point.init(3);
	Edge.init(3);
	Trngl.init(1);
	BndEd.init(1);
	BndEd.x[a0].bn.one(3);
	
	Point.x[a0].SetPoint(p1,n1,t1,a2,a0,a0);
	Point.x[a1].SetPoint(p2,n2,t2,a0,a1,a0);
	Point.x[a2].SetPoint(p3,n3,t3,a1,a2,a0);
	
	Edge.x[a0].SetEdge(a0,a1,a0,nnf,a0);
	Edge.x[a1].SetEdge(a1,a2,a0,nnf,a0);
	Edge.x[a2].SetEdge(a2,a0,a0,nnf,a0);

	Trngl.x[a0].SetTriangle(a0,a1,a2,a0,a1,a2);

	BndEd.x[a0].bn.x[a0]	= a0;
	BndEd.x[a0].bn.x[a1]	= a1;
	BndEd.x[a0].bn.x[a2]	= a2;
}
//_____________________________________
void TrSurface::ClearSurface()		// ���������
{
	int i;
	for(i=0;i<Point.mN;i++)
	{
		delete [] Point.x[i].n_edg;
		delete [] Point.x[i].n_fc;
	}	
}
//_____________________________________
void CopyObject(TrSurface &a,TrSurface &b)
{
	CopyObject(a.Point,b.Point);
	CopyObject(a.Edge,b.Edge);
	CopyObject(a.Trngl,b.Trngl);
	CopyObject(a.BndEd,b.BndEd);
}
//_____________________________________
void InitObject(TrSurface &a)
{
	int NPoint	= 1;

	a.Point.sm(NPoint);
	a.Trngl.sm(2*NPoint);
	a.Edge.sm(3*NPoint);
	a.BndEd.sm(10);

	InitObject(a.Point);
	InitObject(a.Edge);
	InitObject(a.Trngl);
	InitObject(a.BndEd);
}
//_____________________________________
void ClearObject(TrSurface &a)
{
	ClearObject(a.Point);
	ClearObject(a.Edge);
	ClearObject(a.Trngl);
	ClearObject(a.BndEd);
}
//_____________________________________
double TrSurface::GetVolume()	// определяет объём полости ограниченный поверхностью. Если возвращаемое значение отрицательно, то ориентация поверхности внутрь полости, иначе - наружу.
{

	Vec3db c1,c0;
	double dv,V,rn;
	
	int i;

	V	= 0;

	c0	= 0.0;
	for(i=0;i<Point.N;i++)
	{
		c0	+= Point.x[i].crd;
	}
	c0	/= double(Point.N);

	for(i=0;i<Point.N;i++)
	{
		c1	= Point.x[i].crd-c0;
		rn	= c1.scpr(Point.x[i].nor)/3;
		dv	= rn*Point.x[i].area;
		V	+= dv;
	}

	return V;
	/*
	Vec3db a,b,da,db,c1,c2,c3,c0,cr,cr1,cr2;
	int* n_pnt;
	double ds,s,S,dS,r;
	
	int i;

	S	= dS	= 0;

	c0	= 0.0;
	for(i=0;i<Point.N;i++)
	{
		c0	+= Point.x[i].crd;
	}
	c0	/= double(Point.N);

	for(i=0;i<Trngl.N;i++)
	{
		n_pnt	= Trngl.x[i].n_pnt.x;

		c1	= Point.x[n_pnt[0]].crd-c0;
		c2	= Point.x[n_pnt[1]].crd-c0;
		c3	= Point.x[n_pnt[2]].crd-c0;
		r	= c1.scpr(Point.x[n_pnt[0]].nor)+c2.scpr(Point.x[n_pnt[1]].nor)+c3.scpr(Point.x[n_pnt[2]].nor);
		r	/= 3;
		a	= c2-c1;
		b	= c3-c1;
		da	= Point.x[n_pnt[1]].nor-Point.x[n_pnt[0]].nor;
		db	= Point.x[n_pnt[2]].nor-Point.x[n_pnt[0]].nor;
		s	= 2.0*((cr.crss(a,b)).norm());
		S	+= s;
		cr1.crss(da,b)	+=cr2.crss(a,db);
		ds	= cr1.scpr(cr)/s;
		dS	+= r*ds;
	}
	dS	+= S;
	dS	/= 3;

	return (dS>0);
	*/
}
//_____________________________________
void TrSurface::Surf2vrml() // ������ ������ ����� ���� VRML- ����.
{
	int i,j;
	
	fstream sss;
	sss.open("TrSurface.vrml",ios::out);
	sss.precision(17);
	sss<<"#VRML V2.0 utf8"<<'\n';
	sss<<"WorldInfo { info  [\"Surface\"]}"<<'\n';
	sss<<"Background{ skyColor 0 0 0}"<<'\n';
	sss<<"Group{children["<<'\n';
	sss<<"Shape	{appearance Appearance	{material Material {diffuseColor 0 1 1	}}	geometry IndexedFaceSet{"<<'\n';//emissiveColor 	material Material {diffuseColor 0 1 1}	
	sss<<"solid FALSE"<<'\n';
	sss<<"coord Coordinate {point ["<<'\n';
	for (i=0;i<Point.N;i++)
	{
		sss.width(15);
		sss<<Point.x[i].crd;
	}
	sss<<"]	}coordIndex ["<<'\n';
	for (i=0;i<Trngl.N;i++)
	{
		sss.width(7);
		sss<<Trngl.x[i].n_pnt.x[0]<<' '<<Trngl.x[i].n_pnt.x[1]<<' '<<Trngl.x[i].n_pnt.x[2]<<' '<<-1<<' ';
	}
	sss<<'\n'<<"	]"<<'\n';
	sss<<"} }"<<'\n';

	for (j=0;j<BndEd.N;j++)
	{
		sss<<"Shape	{appearance Appearance{}geometry IndexedLineSet{"<<'\n'; //	material Material {diffuseColor 1 0 0 \n emissiveColor 1 0 0}
		sss<<"coord Coordinate 	{point ["<<'\n';
		for (i=0;i<BndEd.x[j].bn.N;i++)
		{
			sss.width(15);
			sss<<Point.x[Edge.x[BndEd.x[j].bn.x[i]].n_pnt.x[0]].crd;
		}
		sss<<"]	}coordIndex ["<<'\n';
		for (i=0;i<BndEd.x[j].bn.N-1;i++)
		{
			sss.width(7);
			sss<<i<<' '<<i+1<<' '<<-1<<' ';
		}
		sss<<BndEd.x[j].bn.N-1<<' '<<0<<' '<<-1<<' ';
		sss<<'\n'<<"]"<<'\n';
		
		sss<<"color Color	{color ["<<'\n';
		sss.width(7);
		sss<<0<<' '<<0<<' '<<1<<' '<<'\n';
		sss.width(7);
		sss<<0<<' '<<1<<' '<<1<<' '<<'\n';
		sss.width(7);
		sss<<1<<' '<<1<<' '<<0<<' '<<'\n';
		for (i=0;i<BndEd.x[j].bn.N-3;i++)
		{
			sss.width(7);
			sss<<1<<' '<<0<<' '<<0<<' '<<'\n';
		}
		sss<<"] } }}"<<'\n';	
	}
	sss<<" ]}"<<'\n';
	sss.close();
}
//_____________________________________
void TrSurface::Surf2vrml(double &ro) // ������ ������ ����� ���� VRML- ����.
{
	int i,j;
	Vec3db pp,a1,a2;
	
	fstream sss;
	sss.open("ShTrSurf.vrml",ios::out);
	sss.precision(17);
	sss<<"#VRML V2.0 utf8"<<'\n';
	sss<<"WorldInfo { info  [\"Surface\"]}"<<'\n';
	sss<<"Background{ skyColor 0 0 0}"<<'\n';
	sss<<"Group{children["<<'\n';
	sss<<"Shape	{appearance Appearance	{material Material {diffuseColor 0 1 1	}}	geometry IndexedFaceSet{"<<'\n';//emissiveColor 	material Material {diffuseColor 0 1 1}	
	sss<<"solid FALSE"<<'\n';
	sss<<"coord Coordinate {point ["<<'\n';
	for (i=0;i<Point.N;i++)
	{
		sss.width(15);
//		a1=Point.x[i].crd;
//		a2=Point.x[i].nor*ro;
		pp	= Point.x[i].crd;
		
		a1 = Point.x[i].nor*ro;
		pp += a1;
		//		pp	= a1+a2;
		sss<<pp;
	}
	sss<<"]	}coordIndex ["<<'\n';
	for (i=0;i<Trngl.N;i++)
	{
		sss.width(7);
		sss<<Trngl.x[i].n_pnt.x[0]<<' '<<Trngl.x[i].n_pnt.x[1]<<' '<<Trngl.x[i].n_pnt.x[2]<<' '<<-1<<' ';
	}
	sss<<'\n'<<"	]"<<'\n';
	sss<<"} }"<<'\n';

	for (j=0;j<BndEd.N;j++)
	{
		sss<<"Shape	{appearance Appearance{}geometry IndexedLineSet{"<<'\n'; //	material Material {diffuseColor 1 0 0 \n emissiveColor 1 0 0}
		sss<<"coord Coordinate 	{point ["<<'\n';
		for (i=0;i<BndEd.x[j].bn.N;i++)
		{
			sss.width(15);
			sss<<Point.x[Edge.x[BndEd.x[j].bn.x[i]].n_pnt.x[0]].crd;
		}
		sss<<"]	}coordIndex ["<<'\n';
		for (i=0;i<BndEd.x[j].bn.N-1;i++)
		{
			sss.width(7);
			sss<<i<<' '<<i+1<<' '<<-1<<' ';
		}
		sss<<BndEd.x[j].bn.N-1<<' '<<0<<' '<<-1<<' ';
		sss<<'\n'<<"]"<<'\n';
		
		sss<<"color Color	{color ["<<'\n';
		sss.width(7);
		sss<<0<<' '<<0<<' '<<1<<' '<<'\n';
		sss.width(7);
		sss<<0<<' '<<1<<' '<<1<<' '<<'\n';
		sss.width(7);
		sss<<1<<' '<<1<<' '<<0<<' '<<'\n';
		for (i=0;i<BndEd.x[j].bn.N-3;i++)
		{
			sss.width(7);
			sss<<1<<' '<<0<<' '<<0<<' '<<'\n';
		}
		sss<<"] } }}"<<'\n';	
	}
	sss<<" ]}"<<'\n';
	sss.close();
}
//_____________________________________
void TrSurface::SrfT2vrml() // ������ ������ ����� ���� VRML- ����.
{
	int i,j;
	double r,g,b;
	
	fstream sss;
	sss.open("TrSurfaceT.vrml",ios::out);
	sss.precision(17);
	sss<<"#VRML V2.0 utf8"<<'\n';
	sss<<"WorldInfo { info  [\"Surface\"]}"<<'\n';
	sss<<"Background{ skyColor 0 0 0}"<<'\n';
	sss<<"Group{children["<<'\n';
	sss<<"Shape	{appearance Appearance	{material Material {}}	geometry IndexedFaceSet{"<<'\n';//emissiveColor 	material Material {diffuseColor 0 1 1}	
	sss<<"solid FALSE"<<'\n';
	sss<<"coord Coordinate {point ["<<'\n';
	for (i=0;i<Point.N;i++)
	{
		sss.width(15);
		sss<<Point.x[i].crd;
	}
	sss<<"]	}coordIndex ["<<'\n';
	for (i=0;i<Trngl.N;i++)
	{
		sss.width(7);
		sss<<Trngl.x[i].n_pnt.x[0]<<' '<<Trngl.x[i].n_pnt.x[1]<<' '<<Trngl.x[i].n_pnt.x[2]<<' '<<-1<<' ';
	}
	sss<<'\n'<<"	]"<<'\n';

	sss<<"color Color	{color ["<<'\n';
	for (i=0;i<Point.N;i++)
	{
		sss.width(7);		

		switch (Point.x[i].stp.x[0])
		{
		case 0:	// ���� � ��
			r = 0.0; g = 1.0; b = 1.0;
			break;
		case 1:	// ���� � �. ���
			r = 0.0; g = 0.0; b = 1.0;
			break;
		case 2:	// ���� � �����������. ����
			r = 0.0; g = 1.0; b = 0.0;
			break;
		case 3:	// ���� � �����������. ����
			r = 1.0; g = 0.0; b = 1.0;
			break;
		case 4:	// ���� � �� �� ���(��� ��. ����
			r = 0.7; g = 0.3; b = 0.0;
			break;
		case 5:	// ���� � ��� �� ���(��� ��. ����
			r = 0.7; g = 0.0; b = 0.3;
			break;
		case 6:	// ���� � �. ����� ����
			r = 1.0; g = 1.0; b = 0.0;
			break;
		}
		
		sss<<r<<' '<<g<<' '<<b<<' '<<'\n';
		//sss<<a<<' '<<0<<' '<<1-alfa*(D.x[i]-vn)<<' '<<'\n';
	}
	/*for (i=0;i<(int)P.N/2;i++)
	{
		sss.width(7);
		sss<<0<<' '<<1-(double)i/(P.N/2-1)<<' '<<(double)i/(P.N/2-1)<<' '<<'\n';
	}//*/
	sss<<"] } } }"<<'\n';	//*/
	//sss<<"} }"<<'\n';

	//sss<<"} }"<<'\n';

	for (j=0;j<BndEd.N;j++)
	{
		sss<<"Shape	{appearance Appearance{}geometry IndexedLineSet{"<<'\n'; //	material Material {diffuseColor 1 0 0 \n emissiveColor 1 0 0}
		sss<<"coord Coordinate 	{point ["<<'\n';
		for (i=0;i<BndEd.x[j].bn.N;i++)
		{
			sss.width(15);
			sss<<Point.x[Edge.x[BndEd.x[j].bn.x[i]].n_pnt.x[0]].crd;
		}
		sss<<"]	}coordIndex ["<<'\n';
		for (i=0;i<BndEd.x[j].bn.N-1;i++)
		{
			sss.width(7);
			sss<<i<<' '<<i+1<<' '<<-1<<' ';
		}
		sss<<BndEd.x[j].bn.N-1<<' '<<0<<' '<<-1<<' ';
		sss<<'\n'<<"]"<<'\n';
		
		sss<<"color Color	{color ["<<'\n';
		sss.width(7);
		sss<<0<<' '<<0<<' '<<1<<' '<<'\n';
		sss.width(7);
		sss<<0<<' '<<1<<' '<<1<<' '<<'\n';
		sss.width(7);
		sss<<1<<' '<<1<<' '<<0<<' '<<'\n';
		for (i=0;i<BndEd.x[j].bn.N-3;i++)
		{
			sss.width(7);
			sss<<1<<' '<<0<<' '<<0<<' '<<'\n';
		}
		sss<<"] } }}"<<'\n';	
	}
	sss<<" ]}"<<'\n';
	sss.close();
}
//_____________________________________
//_____________________________________
void TrSurface::SrfA2vrml() // ������ ������ ����� ���� VRML- ����.
{
	int i,j;
	double r,g,b;
	
	fstream sss;
	sss.open("TrSurfaceA.vrml",ios::out);
	sss.precision(17);
	sss<<"#VRML V2.0 utf8"<<'\n';
	sss<<"WorldInfo { info  [\"Surface\"]}"<<'\n';
	sss<<"Background{ skyColor 0 0 0}"<<'\n';
	sss<<"Group{children["<<'\n';
	sss<<"Shape	{appearance Appearance	{material Material {}}	geometry IndexedFaceSet{"<<'\n';//emissiveColor 	material Material {diffuseColor 0 1 1}	
	sss<<"solid FALSE"<<'\n';
	sss<<"coord Coordinate {point ["<<'\n';
	for (i=0;i<Point.N;i++)
	{
		sss.width(15);
		sss<<Point.x[i].crd;
	}
	sss<<"]	}coordIndex ["<<'\n';
	for (i=0;i<Trngl.N;i++)
	{
		sss.width(7);
		sss<<Trngl.x[i].n_pnt.x[0]<<' '<<Trngl.x[i].n_pnt.x[1]<<' '<<Trngl.x[i].n_pnt.x[2]<<' '<<-1<<' ';
	}
	sss<<'\n'<<"	]"<<'\n';

	sss<<"color Color	{color ["<<'\n';
	for (i=0;i<Point.N;i++)
	{
		sss.width(7);		

		r	= Point.x[i].clr.x[0];
		g	= Point.x[i].clr.x[1];
		b	= Point.x[i].clr.x[2];
				
		sss<<r<<' '<<g<<' '<<b<<' '<<'\n';
		//sss<<a<<' '<<0<<' '<<1-alfa*(D.x[i]-vn)<<' '<<'\n';
	}
	/*for (i=0;i<(int)P.N/2;i++)
	{
		sss.width(7);
		sss<<0<<' '<<1-(double)i/(P.N/2-1)<<' '<<(double)i/(P.N/2-1)<<' '<<'\n';
	}//*/
	sss<<"] } } }"<<'\n';	//*/
	//sss<<"} }"<<'\n';

	//sss<<"} }"<<'\n';

	for (j=0;j<BndEd.N;j++)
	{
		sss<<"Shape	{appearance Appearance{}geometry IndexedLineSet{"<<'\n'; //	material Material {diffuseColor 1 0 0 \n emissiveColor 1 0 0}
		sss<<"coord Coordinate 	{point ["<<'\n';
		for (i=0;i<BndEd.x[j].bn.N;i++)
		{
			sss.width(15);
			sss<<Point.x[Edge.x[BndEd.x[j].bn.x[i]].n_pnt.x[0]].crd;
		}
		sss<<"]	}coordIndex ["<<'\n';
		for (i=0;i<BndEd.x[j].bn.N-1;i++)
		{
			sss.width(7);
			sss<<i<<' '<<i+1<<' '<<-1<<' ';
		}
		sss<<BndEd.x[j].bn.N-1<<' '<<0<<' '<<-1<<' ';
		sss<<'\n'<<"]"<<'\n';
		
		sss<<"color Color	{color ["<<'\n';
		sss.width(7);
		sss<<0<<' '<<0<<' '<<1<<' '<<'\n';
		sss.width(7);
		sss<<0<<' '<<1<<' '<<1<<' '<<'\n';
		sss.width(7);
		sss<<1<<' '<<1<<' '<<0<<' '<<'\n';
		for (i=0;i<BndEd.x[j].bn.N-3;i++)
		{
			sss.width(7);
			sss<<1<<' '<<0<<' '<<0<<' '<<'\n';
		}
		sss<<"] } }}"<<'\n';	
	}
	sss<<" ]}"<<'\n';
	sss.close();
}

void TrSurface::SrfA2vrml(smschar &fname,bool f) // ������ ������ ����� ���� VRML- ����.
{
	int i,j;
	double r,g,b;
	
	fstream sss;
	if (f)
	{
		sss.open(fname.x,ios::out);		
		sss<<"#VRML V2.0 utf8"<<'\n';
		sss<<"WorldInfo { info  [\"Surface\"]}"<<'\n';
		sss<<"Background{ skyColor 0 0 0}"<<'\n';
	}else
	{
		sss.open(fname.x,ios::app);
	}
	sss.precision(17);
	sss<<"Group{children["<<'\n';
	sss<<"Shape	{appearance Appearance	{material Material {}}	geometry IndexedFaceSet{"<<'\n';//emissiveColor 	material Material {diffuseColor 0 1 1}	
	sss<<"solid FALSE"<<'\n';
	sss<<"coord Coordinate {point ["<<'\n';
	for (i=0;i<Point.N;i++)
	{
		sss.width(15);
		sss<<Point.x[i].crd;
	}
	sss<<"]	}coordIndex ["<<'\n';
	for (i=0;i<Trngl.N;i++)
	{
		sss.width(7);
		sss<<Trngl.x[i].n_pnt.x[0]<<' '<<Trngl.x[i].n_pnt.x[1]<<' '<<Trngl.x[i].n_pnt.x[2]<<' '<<-1<<' ';
	}
	sss<<'\n'<<"	]"<<'\n';

	sss<<"color Color	{color ["<<'\n';
	for (i=0;i<Point.N;i++)
	{
		sss.width(7);		

		r	= Point.x[i].clr.x[0];
		g	= Point.x[i].clr.x[1];
		b	= Point.x[i].clr.x[2];
				
		sss<<r<<' '<<g<<' '<<b<<' '<<'\n';
		//sss<<a<<' '<<0<<' '<<1-alfa*(D.x[i]-vn)<<' '<<'\n';
	}
	/*for (i=0;i<(int)P.N/2;i++)
	{
		sss.width(7);
		sss<<0<<' '<<1-(double)i/(P.N/2-1)<<' '<<(double)i/(P.N/2-1)<<' '<<'\n';
	}//*/
	sss<<"] } } }"<<'\n';	//*/
	//sss<<"} }"<<'\n';

	//sss<<"} }"<<'\n';

	for (j=0;j<BndEd.N;j++)
	{
		sss<<"Shape	{appearance Appearance{}geometry IndexedLineSet{"<<'\n'; //	material Material {diffuseColor 1 0 0 \n emissiveColor 1 0 0}
		sss<<"coord Coordinate 	{point ["<<'\n';
		for (i=0;i<BndEd.x[j].bn.N;i++)
		{
			sss.width(15);
			sss<<Point.x[Edge.x[BndEd.x[j].bn.x[i]].n_pnt.x[0]].crd;
		}
		sss<<"]	}coordIndex ["<<'\n';
		for (i=0;i<BndEd.x[j].bn.N-1;i++)
		{
			sss.width(7);
			sss<<i<<' '<<i+1<<' '<<-1<<' ';
		}
		sss<<BndEd.x[j].bn.N-1<<' '<<0<<' '<<-1<<' ';
		sss<<'\n'<<"]"<<'\n';
		
		sss<<"color Color	{color ["<<'\n';
		sss.width(7);
		sss<<0<<' '<<0<<' '<<1<<' '<<'\n';
		sss.width(7);
		sss<<0<<' '<<1<<' '<<1<<' '<<'\n';
		sss.width(7);
		sss<<1<<' '<<1<<' '<<0<<' '<<'\n';
		for (i=0;i<BndEd.x[j].bn.N-3;i++)
		{
			sss.width(7);
			sss<<1<<' '<<0<<' '<<0<<' '<<'\n';
		}
		sss<<"] } }}"<<'\n';	
	}
	sss<<" ]}"<<'\n';
	sss.close();
}

void TrSurface::Surf2vrml(smschar &fname, Vec3db &clr, bool f) // ������ ������ ����� ���� VRML- ����.
{
	int i,j;
	
	fstream sss;
	if (f)
	{
		sss.open(fname.x,ios::out);		
		sss<<"#VRML V2.0 utf8"<<'\n';
		sss<<"WorldInfo { info  [\"Surface\"]}"<<'\n';
		sss<<"Background{ skyColor 0 0 0}"<<'\n';
	}else
	{
		sss.open(fname.x,ios::app);
	}
	sss.precision(17);
	sss<<"Group{children["<<'\n';
	sss<<"Shape	{appearance Appearance	{material Material { diffuseColor "<<clr.x[0]<<" "<<clr.x[1]<<" "<<clr.x[2]<<" }}	geometry IndexedFaceSet{"<<'\n';//emissiveColor 	material Material {diffuseColor 0 1 1}	
	sss<<"solid FALSE"<<'\n';
	sss<<"coord Coordinate {point ["<<'\n';
	for (i=0;i<Point.N;i++)
	{
		sss.width(15);
		sss<<Point.x[i].crd;
	}
	sss<<"]	}coordIndex ["<<'\n';
	for (i=0;i<Trngl.N;i++)
	{
		sss.width(7);
		sss<<Trngl.x[i].n_pnt.x[0]<<' '<<Trngl.x[i].n_pnt.x[1]<<' '<<Trngl.x[i].n_pnt.x[2]<<' '<<-1<<' ';
	}
	sss<<'\n'<<"	]"<<'\n';

	sss<<" } }"<<'\n';	//*/
	//sss<<"} }"<<'\n';

	//sss<<"} }"<<'\n';

	for (j=0;j<BndEd.N;j++)
	{
		sss<<"Shape	{appearance Appearance{}geometry IndexedLineSet{"<<'\n'; //	material Material {diffuseColor 1 0 0 \n emissiveColor 1 0 0}
		sss<<"coord Coordinate 	{point ["<<'\n';
		for (i=0;i<BndEd.x[j].bn.N;i++)
		{
			sss.width(15);
			sss<<Point.x[Edge.x[BndEd.x[j].bn.x[i]].n_pnt.x[0]].crd;
		}
		sss<<"]	}coordIndex ["<<'\n';
		for (i=0;i<BndEd.x[j].bn.N-1;i++)
		{
			sss.width(7);
			sss<<i<<' '<<i+1<<' '<<-1<<' ';
		}
		sss<<BndEd.x[j].bn.N-1<<' '<<0<<' '<<-1<<' ';
		sss<<'\n'<<"]"<<'\n';
		
		sss<<"color Color	{color ["<<'\n';
		sss.width(7);
		sss<<0<<' '<<0<<' '<<1<<' '<<'\n';
		sss.width(7);
		sss<<0<<' '<<1<<' '<<1<<' '<<'\n';
		sss.width(7);
		sss<<1<<' '<<1<<' '<<0<<' '<<'\n';
		for (i=0;i<BndEd.x[j].bn.N-3;i++)
		{
			sss.width(7);
			sss<<1<<' '<<0<<' '<<0<<' '<<'\n';
		}
		sss<<"] } }}"<<'\n';	
	}
	sss<<" ]}"<<'\n';
	sss.close();
}


void TrSurface::Surf2msms()
{
	int i;
	fstream sss;
	sss.open("TrSurface.vert",ios::out);
	sss.precision(17);
	for (i=0;i<Point.N;i++)
	{
		sss.width(15);
		sss<<Point.x[i].crd.x[0]<<"	"<<Point.x[i].crd.x[1]<<"	"<<Point.x[i].crd.x[2]<<"	"<<Point.x[i].nor.x[0]<<"	"<<Point.x[i].nor.x[1]<<"	"<<Point.x[i].nor.x[2]<<"	"<<endl;
	}
	sss.close();
	sss.open("TrSurface.face",ios::out);
	sss.precision(17);
	for (i=0;i<Trngl.N;i++)
	{
		sss.width(15);
		sss<<(Trngl.x[i].n_pnt+1);
	}
	sss.close();
}
//_____________________________________


//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

#endif

