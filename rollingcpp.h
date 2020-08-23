#ifndef _ROLLING_CPP
#define _ROLLING_CPP

#include "rolling.h"
#include "time.h"
#include "massiv.h"
#include <fstream>
#include <math.h>
using namespace std;



int AtPntCount	= 0;
//____________________________________
void CopyObject(AtPnt &a,AtPnt &b)
{
	a.xyz	= b.xyz;
	a.r_wdw	= b.r_wdw;
	a.nfs	= b.nfs;
	a.cfs	= b.cfs;
	a.csf.pst(b.csf);
	a.mx.pst(b.mx);
	a.nfs.pst(b.nfs);
	a.n_ge->pst(*b.n_ge);
	a.n_un->pst(*b.n_un);
	a.c_un->pst(*b.c_un);
	a.n_tr->pst(*b.n_tr);
	a.n_tw->pst(*b.n_tw);
	a.n_trs->pst(*b.n_trs);
	a.n_tws->pst(*b.n_tws);
	a.n_pnt->pst(*b.n_pnt);
	CopyObject(a.csf_c,b.csf_c);
	CopyObject(a.mx_c,b.mx_c);
	CopyObject(a.set_ntw,b.set_ntw);
}
void InitObject(AtPnt &a)
{
	a.n_ge = new ms1Dint [1];a.n_un = new ms1Dint [1];a.c_un = new ms1Dint [1];a.n_tr = new ms1Dint [1];
	a.n_tw = new ms1Dint [1];a.n_tws = new ms1Dint [1];a.n_trs = new ms1Dint [1];a.n_pnt = new ms1Dint [1];

	/*cout<<"AtPnt_Init: n_pnt: "<<a.n_pnt<<" n_tr: "<<a.n_tr<<" n_tw: "<<a.n_tw<<" n_un: "<<a.n_un<<" n_ge: "<<a.n_ge<<endl;

	AtPntCount++;
	cout<<"Init: AtPntCount "<<AtPntCount<<endl;*/

	a.xyz	= 0.0;
	a.r_wdw	= 0.0;
	a.nfs	= -1;
	InitObject(*a.n_ge);
	InitObject(*a.n_un);
	InitObject(*a.c_un);
	InitObject(*a.n_tr);
	InitObject(*a.n_tw);
	InitObject(*a.n_trs);
	InitObject(*a.n_tws);
	InitObject(*a.n_pnt);
	InitObject(a.csf);
	InitObject(a.mx);
	InitObject(a.nfs);
	InitObject(a.csf_c);
	InitObject(a.mx_c);
	InitObject(a.set_ntw);
	a.cfs	= -1;
}
void ClearObject(AtPnt &a)
{
	delete [] a.n_ge; delete [] a.n_un; delete [] a.c_un; delete [] a.n_tr;
	delete [] a.n_tw; delete [] a.n_tws;delete [] a.n_trs;delete [] a.n_pnt;

	/*cout<<"AtPnt_Clear: n_pnt: "<<a.n_pnt<<" n_tr: "<<a.n_tr<<" n_tw: "<<a.n_tw<<" n_un: "<<a.n_un<<" n_ge: "<<a.n_ge<<endl;

	AtPntCount--;
	cout<<"Clear: AtPntCount "<<AtPntCount<<endl;*/

	a.n_ge = 0x0;a.n_un = 0x0;a.c_un = 0x0;a.n_tr = 0x0;
	a.n_tw = 0x0;a.n_tws = 0x0;a.n_trs = 0x0;a.n_pnt = 0x0;
	ClearObject(a.csf);
	ClearObject(a.mx);
	ClearObject(a.nfs);
	ClearObject(a.csf_c);
	ClearObject(a.mx_c);
	ClearObject(a.set_ntw);
}
//____________________________________
void CopyObject(TwPnt &a,TwPnt &b)
{
	p_ms1Dint n_pnt;
	n_pnt	= a.n_pnt;
	memcpy(&a,&b,sizeof(TwPnt));
	a.n_pnt	= n_pnt;
	a.n_pnt->pst(*b.n_pnt);
	a.dpc->pst(*b.dpc);
	a.dz->pst(*b.dz);
	a.dh->pst(*b.dh);
}
void InitObject(TwPnt &a)
{
	p_ms1Dint n_pnt;
	n_pnt	= a.n_pnt;
	memset(&a,0,sizeof(TwPnt));
	a.n_pnt	= n_pnt;
	a.n_pnt	= new ms1Dint [1];
	a.dpc= new ms1DVec3db [1];
	a.dz= new ms1DVec3db [1];
	a.dh= new ms1Ddb [1];

	//cout<<"TwPnt_Init: n_pnt: "<<a.n_pnt<<endl;

	InitObject(*a.n_pnt);
}
void ClearObject(TwPnt &a)
{
	//cout<<"TwPnt_Clear: n_pnt: "<<a.n_pnt<<endl;
	delete [] a.n_pnt; delete [] a.dpc; delete [] a.dz; delete [] a.dh;
	a.n_pnt	= 0x0;a.dpc	= 0x0;a.dz	= 0x0;a.dh	= 0x0;
}	
//____________________________________
void CopyObject(TrPnt &a,TrPnt &b)
{
	a.pc	= b.pc;
	a.nr	= a.nr;
	a.nfs	= b.nfs;
	a.igr	= b.igr;
	a.dpc->pst(*b.dpc);
	a.mx->pst(*b.mx);
	a.n_at->pst(*b.n_at);
	a.tr_n->pst(*b.tr_n);
	a.n_tr->pst(*b.n_tr);
	a.n_tw->pst(*b.n_tw);
	a.c_tr->pst(*b.c_tr);
	a.c_tw->pst(*b.c_tw);
	a.n_pnt->pst(*b.n_pnt);
	a.s_tr->pst(*b.s_tr);
	a.s_mx->pst(*b.s_mx);
}
void InitObject(TrPnt &a)
{
	a.n_pnt=new ms1Dint [1];a.mx=new ms1DVec3db [1];a.n_at=new ms1Dint [1];a.n_tr=new ms1Dint [1];
	a.n_tw=new ms1Dint [1];a.tr_n=new ms1Dint [1];a.c_tr=new ms1Dint [1];a.c_tw=new ms1Dint [1];
	a.s_tr=new ms1DVec3db [1]; a.s_mx= new ms1Ddb [1];a.dpc= new ms1DVec3db [1];

	//cout<<"TrPnt_Init: n_pnt: "<<a.n_pnt<<"  mx: "<<a.mx<<" n_at : "<<a.n_at<<" n_tr : "<<a.n_tr<<" n_tw : "<<a.n_tw<<" n_tr : "<<a.tr_n<<" c_tr : "<<a.c_tw<<" c_tr : "<<a.c_tw<<endl;

	a.pc	= 0.0;
	a.nr	= 0.0;
	a.nfs	= -1;
	a.igr	= -1;
	InitObject(*a.n_pnt);
	a.dpc->one(3);
	a.mx->one(3);
	a.n_at->one(3);
	InitObject(*a.tr_n);
	InitObject(*a.n_tr);
	InitObject(*a.n_tw);
	InitObject(*a.c_tr);
	InitObject(*a.c_tw);
}
void ClearObject(TrPnt &a)
{
	//cout<<"TrPnt_Clear: n_pnt: "<<a.n_pnt<<"  mx: "<<a.mx<<" n_at : "<<a.n_at<<" n_tr : "<<a.n_tr<<" n_tw : "<<a.n_tw<<" n_tr : "<<a.tr_n<<" c_tr : "<<a.c_tw<<" c_tr : "<<a.c_tw<<endl;

	delete [] a.n_pnt; delete [] a.mx; delete [] a.n_at;delete [] a.n_tr;
	delete [] a.n_tw; delete [] a.tr_n; delete[] a.c_tr; delete [] a.c_tw;
	delete [] a.s_tr; delete [] a.s_mx; delete [] a.dpc;
	a.n_pnt=0x0;a.mx=0x0;a.n_at=0x0;a.n_tr=0x0;
	a.n_tw=0x0;a.tr_n=0x0;a.c_tr=0x0;a.c_tw=0x0;
	a.s_tr=0x0; a.s_mx=0x0;a.dpc=0x0;
}
void Swap(TrPnt &a,TrPnt &b)
{
	int x;
	x	= a.nfs; a.nfs= b.nfs;b.nfs = x; 
	x	= a.igr; a.igr= b.igr;b.igr = x;
	Vec3db c;
	c	= a.pc; a.pc =b.pc; b.pc = c;
	c	= a.nr; a.nr =b.nr; b.nr = c;
	ms1DVec3db *p1;
	p1	= a.dpc;	a.dpc	= b.dpc;	b.dpc	= p1;
	p1	= a.mx;		a.mx	= b.mx;		b.mx	= p1;
	p1	= a.s_tr;	a.s_tr	= b.s_tr;	b.s_tr	= p1;
	ms1Ddb *p2;
	p2	= a.s_mx;	a.s_mx = b.s_mx;	b.s_mx = p2;
	ms1Dint *p;
	p	= a.n_at;	a.n_at = b.n_at;	b.n_at = p;
	p	= a.n_pnt;	a.n_pnt = b.n_pnt;	b.n_pnt = p;
	p	= a.n_tr;	a.n_tr = b.n_tr;	b.n_tr = p;
	p	= a.tr_n;	a.tr_n = b.tr_n;	b.tr_n = p;
	p	= a.n_tw;	a.n_tw = b.n_tw;	b.n_tw = p;
	p	= a.c_tr;	a.c_tr = b.c_tr;	b.c_tr = p;
	p	= a.c_tw;	a.c_tw = b.c_tw;	b.c_tw = p;
}
//____________________________________
void CopyObject(ScTrPnt &a,ScTrPnt &b)
{
	a.pc	= b.pc;
	a.nr	= b.nr;
	a.csa	= b.csa;
	a.dpc->pst(*b.dpc);
	a.n_at->pst(*b.n_at);
	a.mx->pst(*b.mx);
	a.n_tr->pst(*b.n_tr);
	a.n_tw->pst(*b.n_tw);
	a.n_str->pst(*b.n_str);
	a.n_stw->pst(*b.n_stw);
	a.n_pnt->pst(*b.n_pnt);
}
void InitObject(ScTrPnt &a)
{
	a.n_pnt=new ms1Dint [1];a.mx=new ms1DVec3db [1];a.n_tr=new ms1Dint [1];a.n_at=new ms1Dint [1];
	a.n_tw=new ms1Dint [1];a.n_str=new ms1Dint [1];a.n_stw=new ms1Dint [1];a.dpc=new ms1DVec3db [1];
	a.pc	= 0.0;
	a.nr	= 0.0;
	a.csa	= 0.0;
	InitObject(*a.n_pnt);
	InitObject(*a.n_at);
	InitObject(*a.dpc);
	a.mx->one(3);
	a.n_tr->one(3);
	InitObject(*a.n_tw);
	InitObject(*a.n_str);
	InitObject(*a.n_stw);
}
void ClearObject(ScTrPnt &a)
{
	delete [] a.n_pnt; delete [] a.mx;delete [] a.n_tr;delete [] a.n_at;
	delete [] a.n_tw; delete[] a.n_str; delete [] a.n_stw; delete [] a.dpc;
	a.n_pnt=0x0;a.mx=0x0;a.n_tr=0x0;a.dpc=0x0;
	a.n_tw=0x0;a.n_str=0x0;a.n_stw=0x0;a.n_at=0x0;
}
void Swap(ScTrPnt &a,ScTrPnt &b)
{
	double x;
	x	= a.csa; a.csa = b.csa;b.csa = x;
	Vec3db c;
	c	= a.pc; a.pc =b.pc; b.pc = c;
	c	= a.nr; a.nr =b.nr; b.nr = c;
	ms1DVec3db *p1;
	p1	= a.mx;a.mx = b.mx; b.mx = p1;
	p1	= a.dpc;a.dpc = b.dpc; b.dpc = p1;
	ms1Dint *p;
	p	= a.n_at;	a.n_at	= b.n_at;	b.n_at	= p;
	p	= a.n_pnt;	a.n_pnt = b.n_pnt;	b.n_pnt	= p;
	p	= a.n_tr;	a.n_tr	= b.n_tr;	b.n_tr	= p;
	p	= a.n_tw;	a.n_tw	= b.n_tw;	b.n_tw	= p;
	p	= a.n_str;	a.n_str	= b.n_str;	b.n_str	= p;
	p	= a.n_stw;	a.n_stw	= b.n_stw;	b.n_stw	= p;
}
//____________________________________
void CopyObject(ScStPnt &a,ScStPnt &b)
{
	p_ms1Dint n_pnt1;
	p_ms1Dint n_pnt2;

	p_ms1Dint n_at1;
	p_ms1Dint n_at2;

	ms1DVec3db *dpc1;
	ms1DVec3db *dpc2;

	n_pnt1	= a.n_pnt1;
	n_pnt2	= a.n_pnt2;

	n_at1	= a.n_at1;
	n_at2	= a.n_at2;

	dpc1	= a.dpc1;
	dpc2	= a.dpc2;

	memcpy(&a,&b,sizeof(ScStPnt));
	a.n_pnt1	= n_pnt1;
	a.n_pnt2	= n_pnt2;

	a.n_at1	= n_at1;
	a.n_at2	= n_at2;


	a.dpc1	= dpc1;
	a.dpc2	= dpc2;

	a.n_pnt1->pst(*b.n_pnt1);
	a.n_pnt2->pst(*b.n_pnt2);

	a.n_at1->pst(*b.n_at1);
	a.n_at2->pst(*b.n_at2);

	a.dpc1->pst(*b.dpc1);
	a.dpc2->pst(*b.dpc2);
}
void InitObject(ScStPnt &a)
{
	memset(&a,0,sizeof(ScStPnt));
	a.n_pnt1 = new ms1Dint [1];
	a.n_pnt2 = new ms1Dint [1];

	a.n_at1 = new ms1Dint [1];
	a.n_at2 = new ms1Dint [1];

	a.dpc1 = new ms1DVec3db [1];
	a.dpc2 = new ms1DVec3db [1];

	InitObject(*a.n_pnt1);
	InitObject(*a.n_pnt2);

	InitObject(*a.n_at1);
	InitObject(*a.n_at2);

	InitObject(*a.dpc1);
	InitObject(*a.dpc2);
}
void ClearObject(ScStPnt &a)
{
	delete [] a.n_pnt1;
	delete [] a.n_pnt2;

	delete [] a.n_at1;
	delete [] a.n_at2;

	delete [] a.dpc1;
	delete [] a.dpc2;

	a.n_pnt1 = 0x0;
	a.n_pnt2 = 0x0;

	a.n_at1 = 0x0;
	a.n_at2 = 0x0;

	a.dpc1 = 0x0;
	a.dpc2 = 0x0;
}
//____________________________________
void CopyObject(ScTwPnt &a,ScTwPnt &b)
{
	p_ms1Dint	n_pnt;
	p_ms1Dint	n_at;
	ms1Ddb		*dh;
	ms1DVec3db	*dz;
	ms1DVec3db	*dpc;
	n_at	= a.n_at;
	n_pnt	= a.n_pnt;
	dh		= a.dh;
	dz		= a.dz;
	dpc		= a.dpc;
	memcpy(&a,&b,sizeof(ScTwPnt));
	a.n_at	= n_at;
	a.n_pnt	= n_pnt;
	a.dh	= dh;
	a.dz	= dz;
	a.dpc	= dpc;
	a.n_pnt->pst(*b.n_pnt);
	a.n_pnt->pst(*b.n_pnt);
	a.dz->pst(*b.dz);
	a.dpc->pst(*b.dpc);
	a.dh->pst(*b.dh);
}
void InitObject(ScTwPnt &a)
{
	memset(&a,0,sizeof(ScTwPnt));
	a.n_pnt	= new ms1Dint [1];
	a.dh	= new ms1Ddb [1];
	a.dz	= new ms1DVec3db [1];
	a.dpc	= new ms1DVec3db [1];
	a.n_at	= new ms1Dint [1];

	InitObject(*a.n_pnt);
	InitObject(*a.dh);
	InitObject(*a.dz);
	InitObject(*a.dpc);
	InitObject(*a.n_at);
}
void ClearObject(ScTwPnt &a)
{	
	delete [] a.n_pnt;
	delete [] a.dh;
	delete [] a.dz;
	delete [] a.dpc;
	a.n_pnt	= 0x0;a.dh	= 0x0;a.dz	= 0x0;a.dpc	= 0x0;
}	
//____________________________________
void CopyObject(ScRll &a,ScRll &b)
{
	a.s_rol	= b.s_rol;
	a.igr	= b.igr;
	a.ifl.pst(b.ifl);
	CopyObject(*a.Tris,*b.Tris);
	CopyObject(*a.Twos,*b.Twos);
	CopyObject(*a.Stbl,*b.Stbl);
}
void InitObject(ScRll &a)
{
	a.Tris=new ms1D<ScTrPnt> [1];a.Stbl=new ms1D<ScStPnt> [1]; a.Twos=new ms1D<ScTwPnt> [1];

	//cout<<"ScRll_Init: Tris: "<<a.Tris<<"  Twos: "<<a.Twos<<" SRol : "<<a.Stbl<<endl;

	a.s_rol	= 0;
	a.igr	= -1;
	InitObject(a.ifl);
	InitObject(*a.Tris);
	InitObject(*a.Twos);
	InitObject(*a.Stbl);
}
void ClearObject(ScRll &a)
{
	//cout<<"ScRll_Clear: Tris: "<<a.Tris<<"  Twos: "<<a.Twos<<" SRol : "<<a.Stbl<<endl;
	delete [] a.Tris;delete [] a.Twos;delete [] a.Stbl;
	ClearObject(a.ifl);
	a.Tris = 0x0;a.Twos = 0x0;a.Stbl = 0x0;
}
//____________________________________
void CopyObject(MolData &a,MolData &b)
{
	a.eig	= b.eig;
	a.pc	= b.pc;

	a.p_rol	= b.p_rol;
	a.s_rol	= b.s_rol;
	a.d_min	= b.d_min;

	a.Q.pst(b.Q);
	a.sro.pst(a.sro);
	a.Nc.pst(b.Nc);
	a.S_At.pst(a.S_At);

	CopyObject(a.AtTp,b.AtTp);
	CopyObject(a.AtClr,b.AtClr);

	CopyObject(a.cbs,b.cbs);
	CopyObject(a.Atom,b.Atom);
	CopyObject(*a.Tris,*b.Tris);
	CopyObject(*a.Twos,*b.Twos);
	CopyObject(*a.SRol,*b.SRol);
	CopyObject(a.TrsCnfGrp,b.TrsCnfGrp);
	CopyObject(a.AtmCnnNmb,b.AtmCnnNmb);
	CopyObject(a.TwsCnnNmb,b.TwsCnnNmb);
	CopyObject(a.TrsCnnNmb,b.TrsCnnNmb);
}
void InitObject(MolData &a)
{
	a.Tris=new ms1D<TrPnt> [1];a.Twos=new ms1D<TwPnt> [1];a.SRol=new ms1D<ScRll> [1]; 

	//cout<<"MolData_Init: Tris: "<<a.Tris<<"  Twos: "<<a.Twos<<" SRol : "<<a.SRol<<endl;

	//memset(&a.eig.x,0,9*sizeof(double));
	//a.pc	= 0;

	InitObject(a.eig);
	InitObject(a.pc);

	a.p_rol	= 0;
	a.s_rol	= 0;
	a.d_min	= 0;
	a.sec_r	= 0;

	InitObject(a.AtTp);
	InitObject(a.AtClr);

	InitObject(a.Q);
	InitObject(a.sro);
	InitObject(a.Nc);
	InitObject(a.S_At);
	InitObject(a.cbs);
	InitObject(a.Atom);
	InitObject(*a.Tris);
	InitObject(*a.Twos);
	InitObject(*a.SRol);
	InitObject(a.TrsCnfGrp);
	InitObject(a.AtmCnnNmb);
	InitObject(a.TwsCnnNmb);
	InitObject(a.TrsCnnNmb);
}
void ClearObject(MolData &a)
{
	//cout<<"MolData_Clear: Tris: "<<a.Tris<<"  Twos: "<<a.Twos<<" SRol : "<<a.SRol<<endl;

	delete [] a.Tris;
	delete [] a.Twos;
	delete [] a.SRol;
	a.Tris = 0x0;
	a.Twos = 0x0;
	a.SRol = 0x0;
	/*ClearObject(a.Q);
	ClearObject(a.sro);
	ClearObject(a.Nc);
	ClearObject(a.S_At);
	ClearObject(a.cbs);
	ClearObject(a.Atom);
	ClearObject(a.TrsCnfGrp);
	ClearObject(a.AtmCnnNmb);
	ClearObject(a.TwsCnnNmb);
	ClearObject(a.TrsCnnNmb);*/
}
//____________________________________
//____________________________________
/*bool AtPnt::Pnt2Surf(Vec3db &p_in, Vec3db &p_out, Vec3db &nrm, double &sq_dst, double &p_rol, int &infs)	// ���� ���'p_in' � �� 'n_At'
{
	int i;	
	Vec3db dp;
	double csa,dr,dR;
	bool ch;

	dp	= p_in-xyz;
	dp.nrml(dr);
	dR	= r_wdw+p_rol;

	ch	 = false;

	for(i=0;i<csf.N;i++)
	{
		//if(infs==nfs.x[i])
		//{
			ch	 = true;
			csa	= csf.x[i].scpr(dp);
			if (csa>mx.x[i]) return false;
			//if (dr*csa>dR*mx.x[i]) return false;			
		//}
	}
	sq_dst	= dr-r_wdw;
	nrm		= dp;
	p_out	= xyz+dp*r_wdw;
	return ch;
}/**/
//____________________________________
bool AtPnt::Pnt2Surf(Vec3db &p_in, Vec3db &p_out, Vec3db &nrm, double &sq_dst, double &p_rol, int &infs)	// ���� ���'p_in' � �� 'n_At'
{
	int i;	
	Vec3db dp;
	double csa,dr,dR;
	bool ch;

	dp	= p_in-xyz;
	dp.nrml(dr);
	dR	= r_wdw+p_rol;

	ch	 = false;

	for(i=0;i<csf.N;i++)
	{
		//if(infs==nfs.x[i])
		//{
			ch	 = true;
			csa	= csf.x[i].scpr(dp);
			if (csa>mx.x[i]) return false;
			//if (dr*csa>dR*mx.x[i]) return false;			
		//}
	}
	sq_dst	= dr-r_wdw;
	nrm		= dp;
	p_out	= xyz+dp*r_wdw;
	return ch;
}
//____________________________________
bool TrPnt::Pnt2Surf(Vec3db &p_in, Vec3db &p_out, Vec3db &nrm, double &sq_dst, double &p_rol, int &infs)	// ���� ���'p_in' � �. ���(��� �'sq_dst' ��� ������ �������� �. ���
{
	if (infs!=nfs) return false;
	Vec3db dp;

	dp	= p_in-pc;
	dp.nrml(sq_dst);	

	if(mx->x[0].scpr(dp)<0) return false;
	if(mx->x[1].scpr(dp)<0) return false;
	if(mx->x[2].scpr(dp)<0) return false;

	for(int i=3;i<mx->N;i++)
	{
		if (mx->x[i].scpr(dp)<0) return false;
	}
	sq_dst	= p_rol-sq_dst;
	nrm		= -dp;
	p_out	= pc+dp*p_rol;
	return true;
}
//____________________________________
bool TwPnt::Pnt2Surf(Vec3db &p_in, Vec3db &p_out, Vec3db &nrm, double &sq_dst, double &p_rol, int &infs)	// ���� ���� ��������� �� �'sq_dst' ��� ������ �������� ��
{
	if (infs!=nfs) return false;
	Vec3db dp,pc,nc;
	double x_,y_,z_,f,dr;

	dp	= p_in-rp;
	z_	= z.scpr(dp);
	//if ((z_<hab.x[1])||(z_>hab.x[2])) return false;
	dp	-= z*z_;
	dp.nrml(dr);
	if(dr>hab.x[0]) return false;
	x_	= x.scpr(dp);
	y_	= y.scpr(dp);
	f	= y_>0 ? x_+1 : -x_-1;
	if ((f<mx.x[0])||(f>mx.x[1])) return false;
	pc	= x*x_+y*y_;
	pc	*=hab.x[0];
	pc	+=rp;
	dp	= p_in - pc;
	dp.nrml(dr);
	nc	= nc2 - pc;
	nc.nrml();
	f = nc.scpr(dp);
	if (f<cs2) return false;
	dr	-= p_rol;
	nrm	= -dp;
	p_out	= pc+dp*p_rol;
	return true;
}
//____________________________________
bool ScTrPnt::Pnt2Surf(Vec3db &p_in, Vec3db &p_out, Vec3db &nrm, double &sq_dst, double &s_rol)	// ���� ���� ��������� �� �'sq_dst' ��� ������ �������� ��
{
	Vec3db dp;

	dp	= p_in-pc;

	if(dp.scpr(nr)>nr.ssqr()) return false;

	dp.nrml(sq_dst);

	
	if(dp.scpr(nr)<csa) return false;
		
	/*if (mx->x[0].scpr(dp)<0) return false;
	if (mx->x[1].scpr(dp)<0) return false;
	if (mx->x[2].scpr(dp)<0) return false;*/

	for(int i=0;i<mx->N;i++)
	{
		if (mx->x[i].scpr(dp)<0) return false;
	}

	sq_dst -= s_rol;
	nrm		= dp;
	p_out	= pc+dp*s_rol;
	return true;
}
//____________________________________
bool ScStPnt::Pnt2Surf1(Vec3db &p_in, Vec3db &p_out, Vec3db &nrm, double &sq_dst, double &s_rol)	// ���� ���� ��������� �� �'sq_dst' ��� ������ �������� ��
{
	Vec3db dp;

	dp	= p_in-pc1;
	if(nst.scpr(dp)>d) return false;	// ���� � �� 'pc1-pc2' ��������� ���� 'pc1-pc2'
	dp.nrml(sq_dst);
	if(nst.scpr(dp)<csa) return false;	// �� �� ����������
	if(n_tr.x[0]!=-1)
	{
		if (nc1.scpr(dp)<0) return false;	// �� ���� ����� ����������90 ����
	}

	sq_dst -= s_rol;
	nrm		= dp;
	p_out	= pc1+dp*s_rol;
	return true;
}
//____________________________________
bool ScStPnt::Pnt2Surf2(Vec3db &p_in, Vec3db &p_out, Vec3db &nrm, double &sq_dst, double &s_rol)	// ���� ���� ��������� �� �'sq_dst' ��� ������ �������� ��
{
	Vec3db dp;

	dp	= p_in-pc2;
	if(nst.scpr(dp)<-d) return false;	// ���� � �� 'pc1-pc2' ��������� ���� 'pc1-pc2'
	dp.nrml(sq_dst);
	if(nst.scpr(dp)>-csa) return false;	// �� �� ����������
	if(n_tr.x[0]!=-1)
	{
		if (nc2.scpr(dp)<0) return false;	// �� ���� ����� ����������90 ����
	}
	sq_dst -= s_rol;
	nrm		= dp;
	p_out	= pc2+dp*s_rol;
	return true;
}
//____________________________________
bool ScTwPnt::Pnt2Surf(Vec3db &p_in, Vec3db &p_out, Vec3db &nrm, double &sq_dst, double &s_rol)	// ���� ���� ��������� �� �'sq_dst' ��� ������ �������� ��
{
	Vec3db dp,pc;
	double x_,y_,z_,f,dr;

	dp	= p_in-rp;
	z_	= z.scpr(dp);
	if ((z_<-d)||(z_>d)) return false;

	dp	-=z*z_;
	dp.nrml();

	x_	= x.scpr(dp);
	y_	= y.scpr(dp);		
	f	= y_>0 ? x_+1 : -x_-1;
	if ((f<mx.x[0])||(f>mx.x[1])) return false;
	
	pc	= (x*x_+y*y_)*r_sc;
	dp	= p_in-(rp+pc);
	dp.nrml(dr);
	f = -pc.scpr(dp)/r_sc;
	if (f<cs2) return false;
	dr	-= s_rol;
	nrm	= dp;
	p_out	= pc+rp+dp*s_rol;
	return true;
}
//____________________________________
bool ScRll::Pnt2Surf(Vec3db &p_in, Vec3db &p_out, Vec3db &nrm, double &sq_dst,int &type, int &id)	// ���� ���'p_in' � ��� ��������� �'sq_dst' ��� ������ ��������. ����
{
	int i,j;
	char ch;
	double min;	

	j	= -1;
	min	= sq_dst;	// ���� ��� ���� ������ ����.

	for(i=0;i<Twos->N;i++)
	{
		ch	 = Twos->x[i].Pnt2Surf(p_in,p_out,nrm,sq_dst,s_rol);
		if (ch)
		{
			type= 3;
			id	= i;
			return true;
		}
	}
	for(i=0;i<Stbl->N;i++)
	{
		ch	= Stbl->x[i].Pnt2Surf1(p_in,p_out,nrm,sq_dst,s_rol);
		if (ch)
		{
			type= 4;
			id	= i;
			return true;
		}
		ch	= Stbl->x[i].Pnt2Surf2(p_in,p_out,nrm,sq_dst,s_rol);
		if (ch)
		{
			type= 5;
			id	= i;
			return true;
		}
	}	
	for(i=0;i<Tris->N;i++)
	{
		ch	= Tris->x[i].Pnt2Surf(p_in,p_out,nrm,sq_dst,s_rol);
		if (ch)
		{
			if(sq_dst<min)
			{
				j	= i;
				min	= sq_dst;
			}
		}
	}
	if (j!=-1)
	{ 
		Tris->x[j].Pnt2Surf(p_in,p_out,nrm,sq_dst,s_rol);
		type= 6;
		id	= i;
		return true;
	}
	return false;
}
//____________________________________
void MolData::SetDataMol(ms1D<Vec3db> &xyz, ms1Ddb &r_wdw, ms1Ddb &Q_in, solpar &slp, smpl_ms<smschar> &AtType,ms1D<int> &tpind)
{
	int ii;
	Atom.init(0,xyz.N);
	Q.init(0,Q_in.N);
	AtTp.sm(xyz.N);
	for(ii=0;ii<xyz.N;ii++)
	{
		if(r_wdw.x[ii]>0)
		{
			Atom.x[Q.N].xyz		= xyz.x[ii];
			Atom.x[Q.N].r_wdw	= r_wdw.x[ii];
			Q.x[Q.N]			= Q_in.x[ii];
			AtTp.x[ii].pst(AtType.x[tpind.x[ii]]);
			Q.N++;
		}
	}
	Atom.N	= Q.N;
	AtTp.N	= Q.N;

	p_rol	= slp.R_rol;
	s_rol	= slp.s_rol;
	d_min	= slp.r_min;

	S_At.init(Atom.N);
	S_At = -1;
}
//____________________________________
void MolData::SetDataMol(ms1D<Vec3db> &xyz, ms1Ddb &r_wdw, ms1D<Vec3db> &clr)
{
	int ii;
	Atom.init(0,xyz.N);
	AtClr.init(0,xyz.N);
	Q.init(0,xyz.N);
	AtTp.sm(xyz.N);
	for(ii=0;ii<xyz.N;ii++)
	{
		/*if(r_wdw.x[ii]>0)
		{*/
			Atom.x[Q.N].xyz		= xyz.x[ii];
			Atom.x[Q.N].r_wdw	= r_wdw.x[ii];
			//Q.x[Q.N]			= Q_in.x[ii];
			//AtTp.x[ii].pst(AtType.x[tpind.x[ii]]);
			AtClr.x[Q.N]	= clr.x[ii];
			Q.N++;
		//}
	}
	Atom.N	= Q.N;
	AtTp.N	= Q.N;
	AtClr.N	= Q.N;

	p_rol	= 1.5;//slp.R_rol;
	s_rol	= 0.4;//0.4;//slp.s_rol;
	d_min	= 0.15;//0.15;//slp.r_min;

	S_At.init(Atom.N);
	S_At = -1;
}
//____________________________________
void MolData::SetAtColor()
{
	int ii;
	AtClr.init(AtTp.N);
	for(ii=0;ii<AtTp.N;ii++)
	{
		// �� ������� � �� ��� �� �� - ���
		AtClr.x[ii]	= 0.5;
		//m_B[ii] =m_G[ii] =m_R[ii] = 0.5;
		if (AtTp.x[ii].x[0]=='C')
		{
			AtClr.x[ii]	= 0.6;
			//m_B[ii] = m_G[ii] =m_R[ii] = (float)0.5;
		}
		if (AtTp.x[ii].x[0]=='O')
		{
			AtClr.x[ii].x[1] = AtClr.x[ii].x[2] = 0;
			AtClr.x[ii].x[0] = 1;
		}
		if (AtTp.x[ii].x[0]=='N')
		{
			AtClr.x[ii].x[0] = AtClr.x[ii].x[1] = 0;
			AtClr.x[ii].x[2] = 1;
		}
		if (AtTp.x[ii].x[0]=='S')
		{
			AtClr.x[ii].x[0] = AtClr.x[ii].x[1] = 1;
			AtClr.x[ii].x[2] = 0;
		}
		if (AtTp.x[ii].x[0]=='H')
		{
			AtClr.x[ii]	= 0.9;
		}
	}
}
//____________________________________
void MolData::SetCubDiv()	// ���� � ��
{
	int iu;
	ms1D<Vec3db> P(Atom.N);
	ms1Ddb		 r_wdw(Atom.N);
	for (iu=0;iu<Atom.N;iu++)
	{
		P.x[iu]=Atom.x[iu].xyz;
		r_wdw.x[iu]=Atom.x[iu].r_wdw;
	}
	r_wdw.N	= P.N	= Atom.N;
	cbs.cubsz	= 2*(p_rol+r_wdw.x[r_wdw.mmax()]);
	cbs.at_in_cubs(P,r_wdw);
}
//____________________________________
void MolData::SetEigBasis()	// ��������������� ������������ ����
{
	ms1D<Vec3db> P_0;
	ms1D<Vec3db> P_1;
	Vec3db dia, nod, vec;
	Mtr3db tnr,res,res1;


	P_0.init(Atom.N);
	P_1.init(Atom.N);

	int ii;
	pc	= 0;
	for(ii=0;ii<Atom.N;ii++){P_0.x[ii] = Atom.x[ii].xyz;}
	pc	= P_0.sum();
	pc	/= (double)Atom.N;

	P_0	-= pc;
	P_1.N = P_0.N;

	for(ii=0;ii<P_0.N;ii++)
	{
		P_1.x[ii].x[0] = P_0.x[ii].x[1];
		P_1.x[ii].x[1] = P_0.x[ii].x[2];
		P_1.x[ii].x[2] = P_0.x[ii].x[0];
	}
	
	P_1	*= P_0;

	dia		= P_0.sqs()/P_0.N;
	nod		= P_1.sum()/P_1.N;


	tnr.x[0]=dia.x[0];tnr.x[1]=tnr.x[3]=nod.x[0];tnr.x[2]=tnr.x[6]=nod.x[2]; // ��� ���� ����
	tnr.x[5]=tnr.x[7]=nod.x[1];tnr.x[4]=dia.x[1];tnr.x[8]=dia.x[2]; //  �����	

	tnr.egn(eig,vec);

	eig.tns();

	InEig	= false;

  /*memcpy(tnr.x,eig.x,9*8);
	eig.tns();
	tnr.pmm(res,eig);
	eig.tns();
	//eig.pmm(res1,res);


	/*for(ii=0;ii<P_0.N;ii++)
	{
		dia	+= P_0.x[ii]*P_0.x[ii];
		nod += P_1.x[ii]*P_1.x[ii];
	}*/	
}
//____________________________________
void MolData::Get2EigBasis()// �������������
{
	Vec3db vec;
	int ii;

	if (!InEig)
	{
		for(ii=0;ii<Atom.N;ii++){Atom.x[ii].xyz	-= pc;}
		for(ii=0;ii<Atom.N;ii++){eig.pmv(vec, Atom.x[ii].xyz); Atom.x[ii].xyz = vec;}
		InEig	= true;
	}
}
//____________________________________
void MolData::Ret2InitBas()	// ������������
{
	Vec3db vec;
	int ii;

	if (InEig)
	{
		eig.tns();
		
		for(ii=0;ii<Atom.N;ii++)
		{
			eig.pmv(vec, Atom.x[ii].xyz); 
			Atom.x[ii].xyz = vec;
		}
		for(ii=0;ii<Atom.N;ii++){Atom.x[ii].xyz	+= pc;}
		
		eig.tns();
		
		InEig	= false;
	}

}
//____________________________________


void MolData::SetAtNeib(int &j)
{
	int ia,ix,iy,iz,ii,iix,iiy,iiz;
	int *iA,NA,*iA_,NA_;
	Vec3db	pAt,pCn,pDr;
	double	R,a,b,c,e,f,csa,z_,d1,d2,b1,b2,r;
	bool ch;

	ms1D<int> itss;

	ms1D<int> n_NearAt;
	ms1D<ms1Dint> n_msNrAt;

	n_msNrAt.init(Atom.N);
	Nc.init(Atom.N);

	for(ia=0;ia<Atom.N;ia++) // �� � �� ��� ����.
	{
		// ����� ��� �� �������������.
		pAt	= Atom.x[ia].xyz-cbs.cnrMin;

		ix	= (int) (pAt.x[0]/cbs.cubsz);
		iy	= (int) (pAt.x[1]/cbs.cubsz);
		iz	= (int) (pAt.x[2]/cbs.cubsz);
		ii	= ix+cbs.nx*(iy+cbs.ny*iz);

		Nc.x[ia]	= ii;

		n_NearAt.N =0;

		for (iiz=iz-1;iiz<=iz+1;iiz++)
			if ((iiz>=0)&&(iiz<cbs.nz))
			for (iiy=iy-1;iiy<=iy+1;iiy++)
				if ((iiy>=0)&&(iiy<cbs.ny))
				for (iix=ix-1;iix<=ix+1;iix++)
					if ((iix>=0)&&(iix<cbs.nx))
					{
						ii	= iix+cbs.nx*(iiy+cbs.ny*iiz);
						n_NearAt.add(cbs.n_at.x[ii]);		// ����� ������� � ���� ��������
					}
		n_msNrAt.x[ia].pst(n_NearAt);		// ���� ��� ��� � ���� ���
	}

	SAlw.init(Atom.N);
	SAlw	= true;

	j	= 0;
	for(ia=0;ia<n_msNrAt.N;ia++)
	{
		NA	= n_msNrAt.x[ia].N;
		Atom.x[ia].n_ge->sm(NA);
		Atom.x[ia].n_un->sm(NA);
		Atom.x[ia].n_un->N = Atom.x[ia].n_ge->N	=0;
		j	= j>NA? j :NA;
	}
	itss.init(0,j);

	for(ia=0;ia<n_msNrAt.N;ia++)	// �� � �� ���.
	{
		if (SAlw.x[ia])
		{
			iA	= n_msNrAt.x[ia].x;
			NA	= n_msNrAt.x[ia].N;
			for (ii=0;ii<NA;ii++)		// �������� ���
			{
				ix	= iA[ii];
				if ((ix>ia)&&(SAlw.x[ix]))
				{
					pAt.x[0]	= Atom.x[ia].xyz.x[0]-Atom.x[ix].xyz.x[0];
					pAt.x[1]	= Atom.x[ia].xyz.x[1]-Atom.x[ix].xyz.x[1];
					pAt.x[2]	= Atom.x[ia].xyz.x[2]-Atom.x[ix].xyz.x[2];
					
					r	*=r = Atom.x[ia].r_wdw - Atom.x[ix].r_wdw;
					a	= pAt.x[0]*pAt.x[0]+pAt.x[1]*pAt.x[1]+pAt.x[2]*pAt.x[2];
					
					if (a < r )
					{
						if (Atom.x[ia].r_wdw>Atom.x[ix].r_wdw) SAlw.x[ix] = false;
						if (Atom.x[ix].r_wdw>Atom.x[ia].r_wdw) SAlw.x[ia] = false;
					}
				}
			}
		}
	}

	for(ia=0;ia<n_msNrAt.N;ia++)	// �� � �� ���.
	{
		if (SAlw.x[ia])
		{
			iA	= n_msNrAt.x[ia].x;
			NA	= n_msNrAt.x[ia].N;
			for (ii=0;ii<NA;ii++)		// �������� ���
			{
				ix	= iA[ii];
				if ((ix>ia)&&(SAlw.x[ix]))
				{
					pAt.x[0]	= Atom.x[ia].xyz.x[0]-Atom.x[ix].xyz.x[0];
					pAt.x[1]	= Atom.x[ia].xyz.x[1]-Atom.x[ix].xyz.x[1];
					pAt.x[2]	= Atom.x[ia].xyz.x[2]-Atom.x[ix].xyz.x[2];
					
					R	*=R = Atom.x[ia].r_wdw + Atom.x[ix].r_wdw + 2*p_rol;
					a	= pAt.x[0]*pAt.x[0]+pAt.x[1]*pAt.x[1]+pAt.x[2]*pAt.x[2];
					
					if (a < R )
					{
						Atom.x[ia].n_ge->x[Atom.x[ia].n_ge->N++]=ix;
						Atom.x[ia].n_un->x[Atom.x[ia].n_un->N++]=ix;
						Atom.x[ix].n_un->x[Atom.x[ix].n_un->N++]=ia;
						/*Atom.x[ia].n_ge->add(ix);
						Atom.x[ia].n_un->add(ix);
						Atom.x[ix].n_un->add(ia);*/						
					}
				}
			}
		}
	}
	for(ia=0;ia<Atom.N;ia++) {Atom.x[ia].n_un->sort();Atom.x[ia].n_ge->sort();}


	for(ia=0;ia<Atom.N;ia++)
	{	
		iA	= Atom.x[ia].n_ge->x;
		NA	= Atom.x[ia].n_ge->N;		

		a	= p_rol+Atom.x[ia].r_wdw;
		n_NearAt.N	= 0;
		for(ii=0;ii<NA;ii++)
		{
			ix	= iA[ii];

			//pAt	= Atom.x[ia].xyz-Atom.x[ix].xyz;
			pAt.x[0]	= Atom.x[ix].xyz.x[0]-Atom.x[ia].xyz.x[0];
			pAt.x[1]	= Atom.x[ix].xyz.x[1]-Atom.x[ia].xyz.x[1];
			pAt.x[2]	= Atom.x[ix].xyz.x[2]-Atom.x[ia].xyz.x[2];

			pAt.nrml(c);
			b	*= b = p_rol+Atom.x[ix].r_wdw;
			csa	= (a*a+c*c-b)/(2*a*c);
			f	= a*csa;
			e	= a*sqrt(1-csa*csa);

			//pCn	= Atom.x[ia].xyz + pAt*f;
			pCn.x[0]	= Atom.x[ia].xyz.x[0] + pAt.x[0]*f;
			pCn.x[1]	= Atom.x[ia].xyz.x[1] + pAt.x[1]*f;
			pCn.x[2]	= Atom.x[ia].xyz.x[2] + pAt.x[2]*f;

			Atom.x[ia].n_un->itss(*Atom.x[ix].n_un,itss);
			iA_	= itss.x;
			NA_	= itss.N;
			//iA_	= Atom.x[ia].n_un->x;
			//NA_	= Atom.x[ia].n_un->N;

			ch	= true;
			for(iy=0;(iy<NA_)&&(ch);iy++)
			{
				iz	= iA_[iy];
				if (iz!=ix)
				{
					//pDr	= Atom.x[iz].xyz - pCn;
					pDr.x[0]	= Atom.x[iz].xyz.x[0] - pCn.x[0];
					pDr.x[1]	= Atom.x[iz].xyz.x[1] - pCn.x[1];
					pDr.x[2]	= Atom.x[iz].xyz.x[2] - pCn.x[2];

					//z_	*= z_ = pDr.scpr(pAt);
					z_	*= z_ = pDr.x[0]*pAt.x[0]+pDr.x[1]*pAt.x[1]+pDr.x[2]*pAt.x[2];

					d2	*= d2= (p_rol+Atom.x[iz].r_wdw);

					d1	= d2-z_;

					b2	= pDr.x[0]*pDr.x[0]+pDr.x[1]*pDr.x[1]+pDr.x[2]*pDr.x[2]-z_;
					if (b2<1e-14)
					{
						ch	= e*e > d1;
					}else
					{
						/*d2	*= d2 = d1-=(b2+e);
						b1	= 4*e*b2;
						ch	= ((b1>d2)||(d1<0));*/

						//e	= sqrt(e);
						b2	= sqrt(b2);
						b1	*=b1 = e+b2;
						b2	*=b2 = e-b2;
						b1	-=d1;
						b2	-=d1;
						ch	= (b1>0)||(b2>0);
					}
					/**/

					/*b2	= pDr.x[0]*pDr.x[0]+pDr.x[1]*pDr.x[1]+pDr.x[2]*pDr.x[2]-z_;
					d1 = d2-z_-b2-e*e;
					b1	= 4*b2*e*e;

					ch	= d1<0 ? true : b1 > d1*d1 ;/**/

					//cout<<ch1<<"  "<<ch<<endl;
				}
			}
			if (ch) n_NearAt.add(ix);
		}
		Atom.x[ia].n_ge->pst(n_NearAt);
	}
	j	= 0;
	for(ia=0;ia<Atom.N;ia++){j=Atom.x[ia].n_un->N>j ? Atom.x[ia].n_un->N : j;}
}

void MolData::SetRolling()	// ����������� ���������
{
	SetTris();		// ����������� �. ������������
	CorTris();		// ���� �. ���- ���� �����
	SetTwos();		// �������� ���������
	CorTrisTw();	// ���� �����. ��� ������.
	SetTrNeib();	// �����������. ������� �����
	//cout<<*Tris->x[8815].tr_n;
/**/SetTrNbTr();//??// �������. ������� ��� �. ���(?? ��� ������CorTris()!! ���� ����� ��...)
	//cout<<*Tris->x[8815].tr_n;	
	SetTwNeib();	// �������� ���� ���
	SetConect();	// ������ ���� ����������� �. ���
/**/CorTwos();//??	// ���� ���� �����������������(�� ���� ���������� ����������� � � ��� � ���
	SetTrsCnf();	// ����� ���������������. ���� ��� �. ���
	//cout<<*Tris->x[8815].c_tr;
	//exit(0);
	SetCnfGrp();	// ������ ��� ���������-�����. ���
	SetSecRol();	// ����� ���� ���������(������������������)
	SetAtomCn();	// �������� ���������� ����������� ���
	SetScForb();	// ����������� ���� ������������������
}

void MolData::SetTris()	// �����������(������ 3 ��� ����������������� ����.
{
	int NA,NA_;
	ms1D<int> *iA,*iA_,*i_A,*i_A_;
	int i,j,i0,i1,i2,j0,j1,j2;
	ms1D<int> itsat,comat;
	Vec3db	P0,P1,P2,P3;
	Vec3db	dP1,dP2,dP3;
	Vec3db	nx,ny,nz,pc;
	Vec3db	nrH;
	double a,b,c,d,e,f,g,csa,csb,csg,sng;
	double rd0,rd1,rd2,rd,crd,det,H;
	bool   ccl,cca;

	SetAtNeib(i0);
	itsat.init(0,i0);
	comat.init(0,i0);
	//Tris	= new ms1D<TrPnt> [1];
	i		= 2*(int) pow((double) 11*Atom.N,0.6666666666);
	i+=100;
	Tris->init(0,i);
	j	= -1;
	for(i0=0;i0<Atom.N-2;i0++)	// ������ ��� � � ���������
	{
		NA	= Atom.x[i0].n_ge->N;
		iA	= Atom.x[i0].n_ge;
		i_A	= Atom.x[i0].n_un;
		P1	= Atom.x[i0].xyz;
		a	= Atom.x[i0].r_wdw+p_rol;
		for (j0=0;j0<NA;j0++)
		{
			i1	= iA->x[j0];
			NA_	= Atom.x[i1].n_ge->N;
			iA_	= Atom.x[i1].n_ge;
			i_A_= Atom.x[i1].n_un;
			P2	= Atom.x[i1].xyz;
			b	= Atom.x[i1].r_wdw+p_rol;
			dP1	= P2-P1;
			dP1.nrml(e);
			iA->itss(*iA_,itsat);
			i_A->itss(*i_A_,comat);
			for(j1 =0; j1<itsat.N;j1++)
			{
				i2	= itsat.x[j1];
				P3.x[0]	= Atom.x[i2].xyz.x[0];
				P3.x[1]	= Atom.x[i2].xyz.x[1];
				P3.x[2]	= Atom.x[i2].xyz.x[2];
				dP2.x[0]= P3.x[0]-P2.x[0];
				dP2.x[1]= P3.x[1]-P2.x[1];
				dP2.x[2]= P3.x[2]-P2.x[2];
				dP3.x[0]= P1.x[0]-P3.x[0];
				dP3.x[1]= P1.x[1]-P3.x[1];
				dP3.x[2]= P1.x[2]-P3.x[2];
				c	= Atom.x[i2].r_wdw+p_rol;
				dP3.nrml(f);
				dP2.nrml(g);
				csa	= (a*a+f*f-c*c)/(2*a*f);	// ������ (P3,P1,����
				csb	= (a*a+e*e-b*b)/(2*a*e);	// ������ (P2,P1,����
				csg	= (f*f+e*e-g*g)/(2*f*e);	// ������ (P3,P1,P2)
				nx.x[0]	= -dP3.x[0];
				nx.x[1]	= -dP3.x[1];
				nx.x[2]	= -dP3.x[2];
				ny.x[0]	= dP1.x[0]-nx.x[0]*csg;
				ny.x[1]	= dP1.x[1]-nx.x[1]*csg;
				ny.x[2]	= dP1.x[2]-nx.x[2]*csg;
				ny.nrml(sng);
				nz.crss(nx,ny);
				// ���������� ���������� ���� ���� ��������� (nx,ny).
				d	= (csb-csg*csa)/sng;		// d*a -> ������ ����dP3 � ���� ��� � ���� (nx,ny).
				H	*= H	= (csa-csg*csb)/sng;// H*a*a -> �������� � ����dP1 � ���� ��� � ���� (nx,ny).
				if ((d*d<=(1-csa*csa))&&(H<=(1-csb*csb))) // ����� ������ �������. 
				{						// ����������d*a �sqrt(H)*a ������ � ���� dP3 �dP1 � ���.
										// ���������� ��� � ���� (nx,ny)
					P0.x[0]	= nx.x[0]*csa+ny.x[0]*d;
					P0.x[1]	= nx.x[1]*csa+ny.x[1]*d;	
					P0.x[2]	= nx.x[2]*csa+ny.x[2]*d;	
					P0.x[0]	*=a;			// P0 ��� ���� � ���� ��� ������(nx,ny) � ���P1
					P0.x[1]	*=a;
					P0.x[2]	*=a;
					// ��������� ����������� �����
					d	*=d;
					d	+=csa*csa;		// �������� �� (P0,P1.����
					H	= a*sqrt(1-d);	// ���
					nrH.x[0]	= nz.x[0]*H;			// ���-��� (P0,���� (���������������
					nrH.x[1]	= nz.x[1]*H;
					nrH.x[2]	= nz.x[2]*H;
					P0.x[0]	+=P1.x[0];			// ���-��� ���� ��� ���������������
					P0.x[1]	+=P1.x[1];
					P0.x[2]	+=P1.x[2];
					pc.x[0]	= P0.x[0]+nrH.x[0];			// ���-��� ��� ���������������-> ������ ���
					pc.x[1]	= P0.x[1]+nrH.x[1];
					pc.x[2]	= P0.x[2]+nrH.x[2];
					ccl	= false;
					cca	= true;
					for(i=0;(i<comat.N)&&(cca);i++)	// �� ���� �� ��� �����comat
					{
						j2	= comat.x[i];		// ��������
						rd0	= pc.x[0]-Atom.x[j2].xyz.x[0];
						rd1	= pc.x[1]-Atom.x[j2].xyz.x[1];
						rd2	= pc.x[2]-Atom.x[j2].xyz.x[2];
						rd	= rd0*rd0+rd1*rd1+rd2*rd2+1e-14;// �������� � ��� � ���������
						crd	*=crd = p_rol+Atom.x[j2].r_wdw;	// ��������� ����� ���� ������� ���������
						cca	= !((rd<crd)&&(j2!=i0)&&(j2!=i1)&&(j2!=i2));
					}
					if (cca)
					{
						j++;  //!!! �� �� ���� �������������� ��� � ���� ��� 'B' !!!
						if (j>=Tris->mN)
						{
							Tris->adm_(ADD_TRS_NMBR);
						}
						/*Tris->x[j].mx	= new ms1DVec3db [1];
						Tris->x[j].mx->one(3);
						Tris->x[j].n_tw = new ms1Dint [1];
						Tris->x[j].n_tr = new ms1Dint [1];
						Tris->x[j].c_tr = new ms1Dint [1];
						Tris->x[j].c_tw = new ms1Dint [1];
						Tris->x[j].n_pnt= new ms1Dint [1];
						Tris->x[j].n_at	= new ms1Dint [1];
						Tris->x[j].n_at->one(3);*/
						Tris->x[j].n_at->x[0]	= i0;
						Tris->x[j].n_at->x[1]	= i1;
						Tris->x[j].n_at->x[2]	= i2;
						//Tris->x[j].n_at->N		= 3;
						Tris->x[j].n_at->sort();
						Tris->x[j].pc	= pc;
						Tris->x[j].nr	= -nrH;
						Atom.x[i0].n_tr->add(j);
						Atom.x[i1].n_tr->add(j);
						Atom.x[i2].n_tr->add(j);

						nx	= P1-pc;
						nx.nrml();
						ny	= P2-pc; 
						ny.nrml();
						nz	= P3-pc; 
						nz.nrml();
						Tris->x[j].mx->x[0].crss(nx,ny);
						Tris->x[j].mx->x[1].crss(ny,nz);
						Tris->x[j].mx->x[2].crss(nz,nx);

						det	= nx.x[0]*(ny.x[1]*nz.x[2]-ny.x[2]*nz.x[1])-nx.x[1]*(ny.x[0]*nz.x[2]-ny.x[2]*nz.x[0])+nx.x[2]*(ny.x[0]*nz.x[1]-ny.x[1]*nz.x[0]);
						Tris->x[j].mx->x[0]	/= det;
						Tris->x[j].mx->x[1]	/= det;
						Tris->x[j].mx->x[2]	/= det;
						Tris->x[j].mx->x[0].nrml();
						Tris->x[j].mx->x[1].nrml();
						Tris->x[j].mx->x[2].nrml();

						Tris->x[j].nfs		= -1;
						Tris->x[j].igr		= -1;
						Tris->N++;
						S_At.x[i0]	= IND_TR_ATOM;
						S_At.x[i1]	= IND_TR_ATOM;
						S_At.x[i2]	= IND_TR_ATOM;
						ccl	= true;
					}
					pc	= P0-nrH; // ������
					cca	= true;
					for(i=0;(i<comat.N)&&(cca);i++)	// �� ���� �� ��� �����comat
					{
						j2	= comat.x[i];		// ��������
						rd0	= pc.x[0]-Atom.x[j2].xyz.x[0];
						rd1	= pc.x[1]-Atom.x[j2].xyz.x[1];
						rd2	= pc.x[2]-Atom.x[j2].xyz.x[2];
						rd	= rd0*rd0+rd1*rd1+rd2*rd2+1e-14;	// �������� � ��� � ���������
						crd	*=crd = p_rol+Atom.x[j2].r_wdw;	// ��������� ����� ���� ������� ���������
						cca	= !((rd<crd)&&(j2!=i0)&&(j2!=i1)&&(j2!=i2));
					}
					if (cca)
					{						
						j++;  //!!! �� �� ���� �������������� ��� � ���� ��� 'B' !!!
						if (j>=Tris->mN)
						{
							Tris->adm_(ADD_TRS_NMBR);
						}
						/*Tris->x[j].mx	= new ms1DVec3db [1];
						Tris->x[j].mx->one(3);
						Tris->x[j].n_tw = new ms1Dint [1];
						Tris->x[j].n_tr = new ms1Dint [1];
						Tris->x[j].c_tr = new ms1Dint [1];
						Tris->x[j].c_tw = new ms1Dint [1];
						Tris->x[j].n_pnt= new ms1Dint [1];
						Tris->x[j].n_at	= new ms1Dint [1];
						Tris->x[j].n_at->x	= new int [3];
						Tris->x[j].n_at->mN		= 3;*/
						Tris->x[j].n_at->x[0]	= i0;
						Tris->x[j].n_at->x[1]	= i1;
						Tris->x[j].n_at->x[2]	= i2;
						//Tris->x[j].n_at->N		= 3;
						Tris->x[j].n_at->sort();
						Tris->x[j].pc	= pc;
						Tris->x[j].nr	= nrH;
						Atom.x[i0].n_tr->add(j);
						Atom.x[i1].n_tr->add(j);
						Atom.x[i2].n_tr->add(j);
						
						nx	= P1-pc;
						nx.nrml();
						ny	= P2-pc; 
						ny.nrml();
						nz	= P3-pc; 
						nz.nrml();
						Tris->x[j].mx->x[0].crss(nx,ny);
						Tris->x[j].mx->x[1].crss(ny,nz);
						Tris->x[j].mx->x[2].crss(nz,nx);

						det	= nx.x[0]*(ny.x[1]*nz.x[2]-ny.x[2]*nz.x[1])-nx.x[1]*(ny.x[0]*nz.x[2]-ny.x[2]*nz.x[0])+nx.x[2]*(ny.x[0]*nz.x[1]-ny.x[1]*nz.x[0]);
						Tris->x[j].mx->x[0]	/= det;
						Tris->x[j].mx->x[1]	/= det;
						Tris->x[j].mx->x[2]	/= det;
						Tris->x[j].mx->x[0].nrml();
						Tris->x[j].mx->x[1].nrml();
						Tris->x[j].mx->x[2].nrml();
						
						Tris->x[j].nfs		= -1;
						Tris->x[j].igr		= -1;
						Tris->N++;
						S_At.x[i0]	= IND_TR_ATOM;
						S_At.x[i1]	= IND_TR_ATOM;
						S_At.x[i2]	= IND_TR_ATOM;
						ccl	= true;
					}else
					{
						if (!ccl)
						{
							if (S_At.x[i0]==-1) S_At.x[i0] = IND_NONTR_ATOM;
							if (S_At.x[i1]==-1) S_At.x[i1] = IND_NONTR_ATOM;
							if (S_At.x[i2]==-1) S_At.x[i2] = IND_NONTR_ATOM;
						}
					}
				}
			}
		}
	}
}


void MolData::Tr_in_cbs()	// ��������. ���� ���
{
/*	int i,j,j0,*x;
	ms1D<int> ntr;
	for(i=0;i<Tris->N;i++)
	{
		for(j=0;j<Tris->x[i].n_at->N;j++)
		{
			j0	= Nc.x[Tris->x[i].n_at->x[j]];
			cbs.n_tr.x[j0].add(i);
		}
	}
	cbs.n_tr.N	= cbs.N;
	for(i=0;i<cbs.n_tr.N;i++)
	{
		cbs.n_tr.x[i].sort();
		x	= cbs.n_tr.x[i].x;
		ntr.N	= 0;
		for(j=1;j<cbs.n_tr.x[i].N;j++)
		{
			if (x[j]!=x[j-1]) ntr.add(x[j-1]);
		}
		cbs.n_tr.x[j0].pst(ntr);
	}
	//for(i=0;i<cbs.N;i++) cout<<i<<" : "<<cbs.n_tr.x[i].N<<" :: "<<cbs.n_tr.x[i];//cbs.n_tr.x[i].sort();
*/
}

void MolData::Tw_in_cbs()	// ��������. ���� ���
{
/*	int i,j,j0,*x;
	ms1D<int> ntw;
	for(i=0;i<Twos->N;i++)
	{		
		j0	= Nc.x[Twos->x[i].n_at.x[0]];
		cbs.n_tw.x[j0].add(i);
		j0	= Nc.x[Twos->x[i].n_at.x[1]];
		cbs.n_tw.x[j0].add(i);
	}
	cbs.n_tw.N	= cbs.N;
	for(i=0;i<cbs.n_tw.N;i++)
	{
		cbs.n_tw.x[i].sort();
		x	= cbs.n_tw.x[i].x;
		ntw.N	= 0;
		for(j=1;j<cbs.n_tw.x[i].N;j++)
		{
			if (x[j]!=x[j-1]) ntw.add(x[j-1]);
		}
		cbs.n_tw.x[j0].pst(ntw);
	}
	//for(i=0;i<cbs.N;i++) cout<<i<<" : "<<cbs.n_tr.x[i].N<<" :: "<<cbs.n_tr.x[i];//cbs.n_tr.x[i].sort();
*/
}


void MolData::CorTris()		// ������������. ���.
{
	int i,j,N,i0,i1,i2,j0,j1;
	ms1D<int> trs0(Tris->N),trs1(Tris->N),atm0(Atom.N),atm1(Atom.N);
	ms1D<bool> alw(Tris->N);
	ms1D<int> cnf(Tris->N);
	ms1D<ms1Dint> tr_n(Tris->N);
	ms1D<ms1Dint> tr_c(Tris->N);
	int *x;
	Vec3db p0,dr;

	tr_n.N	= Tris->N;
	tr_c.N	= Tris->N;
	cnf.N	= alw.N = Tris->N;
	alw		= true;
	cnf		= -1;

	//for(i=0;i<Tris->N;i++)
	//{
		//Tris->x[i].tr_n	= new ms1Dint [1];		� � ���������������� 
		//tr_n.x[i].N=tr_c.x[i].N=0;  - � tr_n �tr_c �� ���- �SetTris � Tris
	//}	

	for(i=0;i<Tris->N;i++)
	{
		if (alw.x[i])	// ���� - ����-� �. ���� ����� ������. ����
		{
			i0	= Tris->x[i].n_at->x[0];	// ��� ��� �� �. ���
			i1	= Tris->x[i].n_at->x[1];
			i2	= Tris->x[i].n_at->x[2];

			Atom.x[i0].n_un->itss(*Atom.x[i1].n_un,atm0);	// �������� ������������������
			Atom.x[i2].n_un->itss(atm0,atm1);
			
			
			trs0.N	= trs1.N = 0;			
			for(j=0;j<atm1.N;j++)	// �� � �� ��� ����
			{				
				i0	= atm1.x[j];	//������
				// �trs0 ���� ��� �� �. ������������� �� � �� � ��� ���.
				trs0.unis(*Atom.x[i0].n_tr,trs1);
				x		= trs1.x;
				trs1.x	= trs0.x;
				trs0.x	= x;
				
				N	= trs1.N;
				trs1.N	= trs0.N;
				trs0.N	= N;
			}
			// trs0 - ��� ����� ��� ���� �'i'-���. ���.

			// ���� ���������'i'
			i0	= trs0.fnd(i); 
			//if (i0==-1) {cout<<"Error in 'CorTris'!!!"<<endl; exit(1);}
			if (i0!=-1) trs0.rem(1,i0);

			// ���� ������ ��� �. ���� ����.
			p0		= Tris->x[i].pc;
			for(j=0;j<trs0.N;j++)
			{				
				i0	= trs0.x[j];
				if(alw.x[i0]) // ���� ������ ���� ���
				{
					dr	= p0-Tris->x[i0].pc;
					if (dr.ssqr()<SQ_ERR_ALW)// ���������
					{
						alw.x[i0]	= false;	// ������� �� �����
						cnf.x[i0]	= i;		// ������ ������ �. ���('i') � ��� ������('i0')
						tr_c.x[i].add(i0);		// 
					}
				}
			}
			tr_n.x[i].pst(trs0);			// ���� ������� �. ���
		}		
	}

	// ���� ����� ������ ���� � ������.
	for(i=0;i<Tris->N;i++) // �� � �� �. ���
	{
		for(j=0;j<tr_c.x[i].N;j++)	// �� � �� �������� ����. ���
		{
			i0	= tr_c.x[i].x[j];	// �������� �. ���
			// ���������� ������ �������
			x	= Tris->x[i0].n_at->x;	// ���� � ��� ������� �� ����� �. ���
			for(j0=0;j0<Tris->x[i0].n_at->N;j0++)	// ������ ��� � ������a�� ����. �. ���
			{
				i1	= x[j0];						// ������
				i2	= Atom.x[i1].n_tr->fnd(i);		// ����-� � �� �. ��������'i'
				if (i2==-1)							// �� ��
				{
					j1	= Atom.x[i1].n_tr->fnd(i0);	// ����� ������. ���i0
					if (j1!=-1) Atom.x[i1].n_tr->x[j1] = i;	// ���� ����� ���'i'
					Tris->x[i].n_at->add(i1);		// ���� ���� ��� �� �. ���'i' ������'i1'
				}else
				{
					j1	= Atom.x[i1].n_tr->fnd(i0);	// ����� ������. ���i0
					if (j1!=-1) Atom.x[i1].n_tr->x[j1] = Atom.x[i1].n_tr->x[--Atom.x[i1].n_tr->N]; //��� ��� ���� � ����� �. ���
				}
			}
		}
	}	// ��� ���� ��� ��� � ������. ���
	//-----

	trs0.N	= Tris->N;
	trs0	= -1;
	j1		= 0;
	for(i=0;i<Tris->N;i++) // �� � �� �. ���
	{
		if(alw.x[i])	trs0.x[i]	= j1++;
	}
	for(i=0;i<Atom.N;i++)
	{
		for(i1=0;i1<Atom.x[i].n_tr->N;i1++)
		{
			j	= trs0.x[Atom.x[i].n_tr->x[i1]];			
			if(j!=-1) Atom.x[i].n_tr->x[i1]	= j;
			else {
				cout<<"Error! Atom relates to unexist tr. point."<<endl;
				exit(1);
			}
		}
		Atom.x[i].n_tr->sort();
	}

	for(i=0;i<Tris->N;i++)
	{
		trs1.N	= 0;
		for(i1=0;i1<tr_n.x[i].N;i1++)
		{
			j	= trs0.x[tr_n.x[i].x[i1]];
			if(j!=-1) trs1.add(j);			
		}
		Tris->x[i].tr_n->pst(trs1);
	}

	for(i=0;(i<Tris->N)&&(i==trs0.x[i]);i++);
	for(;i<Tris->N;i++)
	{
		if(trs0.x[i]!=-1) Swap(Tris->x[trs0.x[i]],Tris->x[i]);
	}
	
	Tris->N	= j1;
}

void MolData::CorTrisTw()	// ������������. ��� ������������� ������
{
	int i,j,i0,i1,k;
	Vec3db		pc,p0,p1;
	Vec3db		vv,v0;

	for(i=0;i<Tris->N;i++)
	{
		if (Tris->x[i].n_tw->N>3)
		{
			Tris->x[i].mx->sm(Tris->x[i].n_tw->N);
			Tris->x[i].mx->N	= 0;
			pc	= Tris->x[i].pc;
			v0	= 0.0;
			for(j=0;j<Tris->x[i].n_at->N;j++)v0+=(Atom.x[Tris->x[i].n_at->x[j]].xyz-pc);
			v0.nrml();
			for(j=0;j<Tris->x[i].n_tw->N;j++)
			{
				k	= Tris->x[i].n_tw->x[j];
				i0	= Twos->x[k].n_at.x[0];
				i1	= Twos->x[k].n_at.x[1];
				p0	= Atom.x[i0].xyz-pc;
				p1	= Atom.x[i1].xyz-pc;
				vv.crss(p0,p1);
				vv.nrml();
				vv	= vv.scpr(v0)>0 ? vv :-vv;
				Tris->x[i].mx->add(vv);
			}
		}
	}
}


void MolData::CorTwos()		// ����������� ������ 
{
	int i,j,k,n,l;
	int i0,i1,j0,j1;
	ms1D<int> itss(At_ntr_mx);
	ms1D<int> idgr(At_ntr_mx);
	ms1D<int> idtw(Twos->N);

	for(i=0;i<Twos->N;i++)
	{
		if(!Twos->x[i].ism)
		{
			j0	= Twos->x[i].n_at.x[0];
			j1	= Twos->x[i].n_at.x[1];
			Atom.x[j0].n_tr->itss(*Atom.x[j1].n_tr,itss);
			for(j=0;j<itss.N;j++)idgr.x[j]	= Tris->x[itss.x[j]].nfs;
			idgr.N	= itss.N;
			idgr.sort_(itss);
			k	= idgr.x[0];
			n	= 0;
			for(j=1;j<idgr.N;j++)
			{
				if(k!=idgr.x[j])
				{
 					if(n<2)
					{
						i0	= itss.x[j-2];
						i1	= itss.x[j-1];
						Tris->x[i0].n_tw->itss(*Tris->x[i1].n_tw,idtw);
						for(l=0;l<idtw.N;l++)
						{
							if((Twos->x[idtw.x[l]].n_at.x[0]==j0)&&(Twos->x[idtw.x[l]].n_at.x[1]==j1)||(Twos->x[idtw.x[l]].n_at.x[0]==j1)&&(Twos->x[idtw.x[l]].n_at.x[1]==j0))
							{
								Twos->x[idtw.x[l]].ism = true;
							}
						}
					}
					n	= 0;
					k	= idgr.x[j];
				}else n++;
			}
			if(n==1)
			{
				i0	= itss.x[j-2];
				i1	= itss.x[j-1];
				Tris->x[i0].n_tw->itss(*Tris->x[i1].n_tw,idtw);
				for(l=0;l<idtw.N;l++)
				{
					if((Twos->x[idtw.x[l]].n_at.x[0]==j0)&&(Twos->x[idtw.x[l]].n_at.x[1]==j1)||(Twos->x[idtw.x[l]].n_at.x[0]==j1)&&(Twos->x[idtw.x[l]].n_at.x[1]==j0))
					{
						Twos->x[idtw.x[l]].ism = true;
					}
				}
			}
		}
	}
}


void MolData::SetTrNeib()	// �������. ���� ���
{
	int i,j;//k;
	ms1D<int> itsat(Tris->N);
	ms1D<int> itsst(Tris->N);
	Vec3db	dtr;
	int *x,N,*y;
	double Rr,r;
	//TrPnt	*Tr;
	//bool ch;

	r	= 2*p_rol;

	for (i=0;i<Atom.N;i++)
	{
		x	= Atom.x[i].n_un->x;
		N	= Atom.x[i].n_un->N;
		itsst.pst(*Atom.x[i].n_tr);
		for (j =0;j<N;j++)
		{
			itsst.unis(*Atom.x[x[j]].n_tr,itsat);
			y		= itsst.x;
			itsst.x	= itsat.x;
			itsat.x	= y;
			itsst.N	= itsat.N;
			itsat.N = 0;/**/
		}
		Atom.x[i].n_trs->init(0,itsst.N);
		//  ����������. ���� ���� �������������. ���
		/*for (j =0;j<itsst.N;j++)
		{
			Tr	= &Tris->x[itsst.x[j]];
			dtr	= Atom.x[i].xyz-Tr->pc;
			cout<<dtr.norm()<<endl;
			ch	= true;
			for(k=0;(k<Tr->mx->N)&&(ch);k++)
			{
				ch	= (dtr.scpr(Tr->mx->x[k])>-Atom.x[i].r_wdw);
			}
			if (ch) itsat.add(itsst.x[j]);
		}//*/


		Rr	*= Rr = Atom.x[i].r_wdw+r;	// ??? ������� ��� ����� ������������� �. ���?
		for (j =0;j<itsst.N;j++)
		{
			if ((Atom.x[i].xyz-Tris->x[itsst.x[j]].pc).ssqr()<Rr) Atom.x[i].n_trs->add(itsst.x[j]);
		}
	}
}

void MolData::SetTwNeib()	// �������� ���� ���
{
	int i,j;
	ms1D<int> itsat(Twos->N);
	ms1D<int> itsst(Twos->N);
	int *x,N,*y;
	double Rr,r,ro;

	r	= p_rol;
 //����� ��� ��� ���� �� ����� ���  SetTrNeib() ???
	for (i=0;i<Atom.N;i++)
	{
		x	= Atom.x[i].n_un->x;
		N	= Atom.x[i].n_un->N;
		itsst.pst(*Atom.x[i].n_tw);
		for (j =0;j<N;j++)
		{
			itsst.unis(*Atom.x[x[j]].n_tw,itsat);
			y		= itsst.x;
			itsst.x	= itsat.x;
			itsat.x	= y;
			itsst.N	= itsat.N;
			itsat.N = 0;/**/
		}
		//Atom.x[i].n_tws	= new ms1D<int> [1];
		Atom.x[i].n_tws->init(0,itsst.N);
		Rr	*= Rr = Atom.x[i].r_wdw+r;	// ??? ������� ��� ����� ������������� �. ���?
		//Atom.x[i].n_tws->N = 0;
		for (j =0;j<itsst.N;j++) 
		{
			ro	= (Atom.x[i].xyz-Twos->x[itsst.x[j]].rp).ssqr();
			if (ro<Rr) Atom.x[i].n_tws->add(itsst.x[j]);
		}
	}
}

void MolData::SetTrNbTr()	// �������. ���� �. ���
{
	int i,j,k;
	ms1D<int> itsat(Tris->N);
	ms1D<int> itsst(Tris->N);
	int *y;
	double r,ro;

	r	*= r = 2*(p_rol+s_rol);

	for(i=0;i<Tris->N;i++)
	{
		itsat.N	= itsst.N	=0;
		for(j=0;j<Tris->x[i].n_at->N;j++)
		{
			k	= Tris->x[i].n_at->x[j];
			itsst.unis(*Atom.x[k].n_trs,itsat);
			y	= itsst.x;
			itsst.x	= itsat.x;
			itsat.x	= y;
			itsst.N	= itsat.N;
			itsat.N = 0;/**/
		}
		//Tris->x[i].tr_n	= new ms1D<int> [1];
		Tris->x[i].tr_n->init(0,itsst.N);
		for(j=0;j<itsst.N;j++)
		{
			ro	= (Tris->x[i].pc-Tris->x[itsst.x[j]].pc).ssqr();
			if(ro<r) Tris->x[i].tr_n->add(itsst.x[j]);
		}
		j	= Tris->x[i].tr_n->fnd(i);
		Tris->x[i].tr_n->rem(1,j);
	}

}

void MolData::SetConect() // ����������� ���, ����������� ����������������
{
	int i,j,k,NTG;
	int iw,jw,kw;
	ms1D<int> *p_i;	
	double rmin;

	int infs= 0; // ��� ��� �����.

	ms1D<int> N1(Tris->N);	// ������
	ms1D<int> N2(Tris->N);	// ��� ���
	ms1D<int> N3(Tris->N);	// ���� ���
	ms1D<int> Nt(Tris->N);	// �� ��� �����. ���
	
	//ms1D<ms1Dint> tr_connect(Tris->N);
	TrsCnnNmb.sm();	// �������� � �������������. 


	rmin	= 0;
	for(j=0;j<Tris->N;j++)
	{
		if(Tris->x[j].pc.ssqr()>rmin) 
		{
			rmin = Tris->x[j].pc.ssqr();
			i=j;
		}
	}


	if (Tris->N!=0)
	{
		do{
			Nt.N= N1.N= N2.N= N3.N= 0;
			N2.add(i);
			do
			{
				for(i=0;i<N2.N;i++)
				{
					p_i	= Tris->x[N2.x[i]].n_tr;
					for (k=0;k<p_i->N;k++)
					{
						j	= p_i->x[k];
						if ((N1.fnd(j)==-1)&&(N2.fnd(j)==-1)&&(N3.fnd(j)==-1)) N1.add(j);
					}
					Tris->x[N2.x[i]].nfs	= infs;
				}
				Nt.add(N2);
				N3.pst(N2);	// ��� ��� ������ ���� ���.
				N2.pst(N1);	// ������ ������ ��� ���.
				N1.N=0;		// ���� ������.			
			}
			while(N2.N>0);
			Nt.sort();
			TrsCnnNmb.adc(Nt);
			infs++;
			i	= -1;
			for(k=0;(k<Tris->N)&&(i==-1);k++)
			{
				i	= Tris->x[k].nfs==-1 ? k : i;
			}
		}while(i!=-1);
	}

	// ����� ������������ � ����������
	// ��� �'Nt' ���� ��� ���� ����� ���

	ms1Dint n2g(Twos->N);
	ms1Dint nTr(1);
	nTr.N	= 1;
	n2g.N	= Twos->N;
	NTG	= Nt.N = Tris->N;
	for(i=0;i<Tris->N;i++) Nt.x[i] = Tris->x[i].nfs;
	for(i=0;i<Twos->N;i++)
	{
		k	= Twos->x[i].n_tr.x[0];
		if(k==-1)
		{
			n2g.x[i] = nTr.x[0] = Nt.N; // ���� ������ �. ���
			Nt.add(TrsCnnNmb.N);	// ������ - ��� �. ����������� ���� � ���������������					
			TrsCnnNmb.adc(nTr);
		}else n2g.x[i] = k;
	}
	
	// ������������� ���� ���
	//ms1D<ms1Dint> attwgr(Atom.N);
	//attwgr.N	= Atom.N;
	ms1Dint		twgr(20);	// ��� ������
	ms1Dint		gr_0(20);
	ms1Dint		Ntgr(20);	// 
	ms1D<ms1Dint> ngrp(20); // �������. Ntgr[i]-���� ���� ��� � ����twgr ������� ���'i'
	double csa,csb;
	int igr,Ngr,ii;

	bool ch,ch1;

	InitObject(ngrp);

	Ngr	= 0;

	for(i=0;i<Atom.N;i++)
	{
		if(S_At.x[i]!=IND_NONTR_ATOM)
		{
			if(Atom.x[i].n_tw->N!=0)
			{
				twgr.N	= 0;
				Ntgr.N	= 0;
				ngrp.N	= 0;
				for(j=0;j<Atom.x[i].n_tw->N;j++)
				{
					k	= Atom.x[i].n_tw->x[j];
					igr	= Nt.x[n2g.x[k]];	// ������������� ������ ������...
					/*if (Twos->x[k].n_tr.x[0]!=-1)
					{
						iw	= Twos->x[k].n_tr.x[0];	// ����. �������� �������������
						igr	= Tris->x[iw].nfs;		// �������������;
					}
					else
					{
						//igr	= -1;
						igr	= Nt.x[n2g.x[k]];	// ������������� ������ ������...
					}*/
					twgr.add(igr);	// � ����������� ��� �� ��������� ���
				}
				ch	= true;
				igr	= twgr.x[0];
				for(j=1;(j<twgr.N)&&ch;j++) ch	= twgr.x[j]==igr;	// ������ ���������������
				if(!ch)	// �� ��� �� ���
				{
					gr_0.N	= 0;
					j--;
					gr_0.one(j);
					for(k=0;k<j;gr_0.x[k++]=k);
					//Atom.x[i].n_tw->ind(0,j,gr_0);
					j--;
					Ntgr.add(twgr.x[j]);	// ��� ���������
					ngrp.adc(gr_0);			// ����� �����������
					for(j++;j<twgr.N;j++)	// ����� ���������������
					{
						jw	= Ntgr.fnd(twgr.x[j]);	// �������� �������� ��������
						if(jw==-1)		// �� � ������
						{
							gr_0.N=0;	
							gr_0.add(j);	
							ngrp.adc(gr_0);	// �������� ����� ������ ����
							Ntgr.add(twgr.x[j]);	// ����� ��� ��� ���� �������
						}else
						{
							if(twgr.x[j]==-1)	// �� ��� �����������
							{
								gr_0.N=0;	
								gr_0.add(j);
								ngrp.adc(gr_0);
							}
							else
							{
								ngrp.x[jw].add(j);	// ���� ��������...
							}							
						}

					}
					// ��� �Ntgr ��� ��� ���� ������� ��ngrp - ��� ���������� ���� � ���������� ��� ��� � Ntgr
					
					if(Ntgr.N>1)
					{
						for(j=0;j<Ntgr.N-1;j++)
						{
							if(Ntgr.x[j]!=-1)
							{
								ch1	= true;
								for(k=j+1;k<Ntgr.N;k++)
								{
									if(Ntgr.x[k]!=-1)
									{
										ch	= true;
										for(ii=0;(ii<ngrp.x[j].N)&&ch;ii++)
										{
											kw	= ngrp.x[j].x[ii];
											for(iw=0;(iw<ngrp.x[k].N)&&ch;iw++)
											{
												jw	= ngrp.x[k].x[iw];
												csa	= Atom.x[i].mx.x[kw];
												csb	= Atom.x[i].mx.x[jw];
												csb	= csa*csb-sqrt((1-csa*csa)*(1-csb*csb));
												csa	= Atom.x[i].csf.x[kw].scpr(Atom.x[i].csf.x[jw]);
												ch	= csa<=csb;
											}
										}
										if(ch)
										{
											if	(Ntgr.x[k]>Ntgr.x[j])
											{
												ii	= Ntgr.x[k];	// ��� �����
												iw	= Ntgr.x[j];	// ��� �����
												ngrp.x[j].add(ngrp.x[k]); // ���� ������ � ��� ���� �������� ��� ����� ��� ���� ����
												ngrp.N--;
												if(k!=ngrp.N)
												{
													ngrp.x[k].pst(ngrp.x[ngrp.N]);	// �k-���� ���� �������� (���� k-������
												}
												
												Ntgr.N--;
												Ntgr.x[k]	= Ntgr.x[Ntgr.N];	// � ���k-���������� �����																									
												//ch1	= k>j;	//?
												k--;
											}else
											{
												ii	= Ntgr.x[j];
												iw	= Ntgr.x[k];
												ngrp.x[k].add(ngrp.x[j]);
												ngrp.N--;
												if(j!=ngrp.N)
												{
													ngrp.x[j].pst(ngrp.x[ngrp.N]);	// �k-���� ���� �������� (���� k-������
												}
												
												Ntgr.N--;
												Ntgr.x[j]	= Ntgr.x[Ntgr.N];
												k--;		//?
												//ch1	= false;//?
											}
											TrsCnnNmb.x[iw].add(TrsCnnNmb.x[ii]);
											//for(jw=0;jw<TrsCnnNmb.x[ii].N;jw++) Tris->x[TrsCnnNmb.x[ii].x[jw]].nfs = iw;
											for(jw=0;jw<TrsCnnNmb.x[ii].N;jw++) Nt.x[TrsCnnNmb.x[ii].x[jw]] = iw;
											TrsCnnNmb.N--;
											if(Ntgr.x[Ntgr.mmax()]==TrsCnnNmb.N) Ntgr.x[Ntgr.mmax()]--;
											if (ii<TrsCnnNmb.N)
											{
												TrsCnnNmb.x[ii].pst(TrsCnnNmb.x[TrsCnnNmb.N]);
												//for(jw=0;jw<TrsCnnNmb.x[ii].N;jw++) Tris->x[TrsCnnNmb.x[ii].x[jw]].nfs = ii;
												for(jw=0;jw<TrsCnnNmb.x[ii].N;jw++) Nt.x[TrsCnnNmb.x[ii].x[jw]] = ii;
											}
										}										
									}
								}
							}
						}
					}
				}
			}
		}
	}

	// ����� ����� ������������ ��� �������� ��� ������ (Atom , Tris, Twos)
	
	if(Nt.N!=0) Nt.mmax(j);else j = -1;	// �'j' - ����������� ����������������. ������� ���������
//	AtmCnnNmb.init(++j);	// ������ 
	TwsCnnNmb.init(++j);	// ������ 

	// ������ ����� �������� ����������� � �. ���
	for(i=0;i<Tris->N;i++)Tris->x[i].nfs	= Nt.x[i];

	// ������ ����� �������� ����������� � ��
	for(i=0;i<Twos->N;i++)
	{
		j	= Twos->x[i].n_tr.x[0];
		if(j!=-1)	iw	= Nt.x[j];
		else		iw	= Nt.x[n2g.x[i]];
		Twos->x[i].nfs	= iw;
		TwsCnnNmb.x[iw].add(i);
	}

	// ����������� ���������������.
	for(i=0;i<TwsCnnNmb.N;i++)
	{	
		for(j=0;j<TwsCnnNmb.x[i].N;j++)
		{
			iw	= TwsCnnNmb.x[i].x[j];
			jw	= Twos->x[iw].n_at.x[0];
			kw	= Atom.x[jw].nfs.fnd(i);
			if (kw==-1) Atom.x[jw].nfs.add(i);
			//kw	= Atom.x[jw].n_tw.fnd(iw);
			jw	= Twos->x[iw].n_at.x[1];
			kw	= Atom.x[jw].nfs.fnd(i);
			if (kw==-1) Atom.x[jw].nfs.add(i);
		}
	}
	// ������ ����� ������������������� � ���
	for(i=0;i<Atom.N;i++)
	{
		if (Atom.x[i].nfs.N>0)
		{
			Atom.x[i].set_ntw.one(Atom.x[i].nfs.N);
			for(iw=0;iw<Atom.x[i].n_tw->N;iw++)
			{
				kw	= Twos->x[Atom.x[i].n_tw->x[iw]].nfs;
				jw	= Atom.x[i].nfs.fnd(kw);
				Atom.x[i].set_ntw.x[jw].add(iw);
			}
		}
	}
	// �������� �����������, ������ � ��������� ����
	j	= TwsCnnNmb.N;
	for(i=0;i<Atom.N;i++)
	{
		if(Atom.x[i].n_un->N==0)
		{
			Atom.x[i].nfs.add(j);
			j++;
		}
	}
	// ����� ���� 'AtmCnnNmb'
	AtmCnnNmb.init(j);	// ������ 
	for(i=0;i<Atom.N;i++)
	{
		for(j=0;j<Atom.x[i].nfs.N;j++)
		{
			AtmCnnNmb.x[Atom.x[i].nfs.x[j]].add(i);
		}
	}

	if (AtmCnnNmb.N>TrsCnnNmb.N)
	{
		TrsCnnNmb.adm_(AtmCnnNmb.N-TrsCnnNmb.N);
		for(i=TrsCnnNmb.N;i<TrsCnnNmb.mN;i++)
		{
			TrsCnnNmb.x[i].N=0;
		}
	}
	if (AtmCnnNmb.N>TwsCnnNmb.N)
	{
		TwsCnnNmb.adm_(AtmCnnNmb.N-TwsCnnNmb.N);
		for(i=TwsCnnNmb.N;i<TwsCnnNmb.mN;i++)
		{
			TwsCnnNmb.x[i].N=0;
		}
	}

	/*for(i=0;i<Atom.N;i++)
	{		
		if(Atom.x[i].n_tw->N>0)
		{
			for(j=0;j<Atom.x[i].n_tw->N;j++)
			{
				k	= Twos->x[Atom.x[i].n_tw->x[j]].nfs;
				Atom.x[i].nfs.add(k);
				iw	= AtmCnnNmb.x[k].fnd(i);
				if (iw==-1) AtmCnnNmb.x[k].add(i);
			}
		}else
		{
			if ((Atom.x[i].n_un->N==0)&&(SAlw.x[i]))
			{
				S_At.x[i]	= IND_SURF_ATOM;
				gr_0.N		= 1;
				gr_0.x[0]	= i;			
				Atom.x[i].nfs.N	 =0;
				Atom.x[i].nfs.add(AtmCnnNmb.N);
				Atom.x[i].csf.init(1);
				Atom.x[i].mx.init(1);
				Atom.x[i].csf.x[0]	= 0;
				Atom.x[i].mx.x[0]	= 1.01;
				AtmCnnNmb.adc(gr_0);
			}
		}
	}//*/
	
}


void MolData::SetTrsCnf()	// �������������. ����� �. ���
{
	int jc,i1,j1;
	int i,j,igr,jgr;
	double a0,a1,a2,b,c;
	bool ch;

	Vec3db	r0,r1,r2,r3;
	Vec3db	dr0,dr1,dr2,dr3;

	a1	*= a1 = p_rol+s_rol;
	a2	*= a2 = p_rol+d_min;

	for(i=0;i<Tris->N;i++)
	{
		igr	= Tris->x[i].nfs;
		for(j=0;j<Tris->x[i].tr_n->N;j++)
		{			
			jc	= Tris->x[i].tr_n->x[j];
			jgr	= Tris->x[jc].nfs;
			if((jc>j)&&(igr==jgr))
			{
				r0	= Tris->x[jc].pc-Tris->x[i].pc;
				a0	= 0.25*r0.ssqr();		
				if(a0<a1)
				{				
					b	= -sqrt(1-a0/a1);
					r0.nrml();
					ch	= true;
					for(j1=0;(j1<Tris->x[i].mx->N)&&ch;j1++)					
					{
						ch	= r0.scpr(Tris->x[i].mx->x[j1])>b;
					}
					if(ch)
					{
						r0	*=-1.0;
						for(j1=0;(j1<Tris->x[jc].mx->N)&&ch;j1++)					
						{
							ch	= r0.scpr(Tris->x[jc].mx->x[j1])>b;
						}
						if(ch)
						{
							if(a0<a2)
							{
								j1	= Tris->x[i].c_tr->fnd(jc);
								if(j1==-1)
								{
									Tris->x[i].c_tr->add(jc);
								}
								i1	= Tris->x[jc].c_tr->fnd(i);
								if(i1==-1)
								{
									Tris->x[jc].c_tr->add(i);
								}
							}else
							{
								c	= sqrt(a1-a0)-s_rol;
								if(c>d_min)
								{
									j1	= Tris->x[i].c_tr->fnd(jc);
									if(j1==-1)
									{
										Tris->x[i].c_tr->add(jc);
									}
									i1	= Tris->x[jc].c_tr->fnd(i);
									if(i1==-1)
									{
										Tris->x[jc].c_tr->add(i);
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

void MolData::SetCnfGrp()	// ����������������. ���
{
	int i,j,i0,j0,i1,j1;

	ms1D<int> cnf_id(Tris->N>>1);	// ��� ����� �. ���
	ms1D<int> curLev(1);	// ��� ���
	ms1D<int> newLev(1);	// ������
	ms1D<int> prvLev(1);	// ���� ���

	ms1D<bool> alw;	// �������
	alw.one(Tris->N);
	alw	= true;

	for(i=0;i<Tris->N;i++) if(Tris->x[i].c_tr->N!=0) cnf_id.add(i);

	for(i=0;i<cnf_id.N;i++) Tris->x[cnf_id.x[i]].c_tr->sort();

	for(i=0;i<cnf_id.N;i++)
	{
		j	= cnf_id.x[i];
		if(alw.x[j])
		{
			curLev.add(j);
			alw.x[j]	= false;
			do
			{
				for(i0=0;i0<curLev.N;i0++)
				{
					j0	= curLev.x[i0];
					for(i1	=0;i1<Tris->x[j0].c_tr->N;i1++)
					{
						j1	= Tris->x[j0].c_tr->x[i1];
						if(alw.x[j1])
						{
							newLev.add(j1);
							alw.x[j1]	= false;
						}
					}
				}
				prvLev.add(curLev);
				curLev.pst(newLev);
				newLev.N	= 0;
			}
			while(curLev.N!=0);
			TrsCnfGrp.adc(prvLev);
			for(i0=0;i0<prvLev.N;i0++)Tris->x[prvLev.x[i0]].igr	= TrsCnfGrp.N-1;
			prvLev.N	= 0;
		}
	}
	for(i=0;i<TrsCnfGrp.N;i++)TrsCnfGrp.x[i].sort();
	for(i=0;i<TrsCnfGrp.N;i++)
	{
		for(j=0;j<TrsCnfGrp.x[i].N;j++) Tris->x[TrsCnfGrp.x[i].x[j]].igr= i;
	}
}

void MolData::SetSecRol()	// ����������� ���������
{
	ms1D<int> SecCnfGrp(1);
	ms1D<ms1Dint> nScTrPr;	// ��� �����.����������������� � �� �. ������������
	ms1D<ms1Dint> nScStPr;	// ��� �������������������������� � �� �. ������������
	//ms1D<ms1Dint> nScTwPr(Tris->N);	// ��� ������ �������������� � �� �. ������������

	//SRol	= new ms1D<ScRll> [1];
	SRol->init(TrsCnfGrp.N,TrsCnfGrp.N+10);

	for(int i=0;i<SRol->N;SRol->x[i++].s_rol=s_rol);	// ����������� ���������������������

	nScTrPr.init(Tris->N);
	nScStPr.init(Tris->N);	

	SetScTris(nScTrPr);			// �������. ������������
	CorScTris(nScTrPr);			// ���� �. ������������(���� �����)
 	SetScStbl(nScStPr);			// ����� �����������������
	SetScTwos(nScTrPr,nScStPr);	// �������� ���������
	CorScTwTr();				// ���� �����. ��� ������ ���������

	ScRlAnlze(SecCnfGrp);		// ��� ����� ���������(���� ����� �������������� ��. ����
	ConflFree(SecCnfGrp,nScTrPr,nScStPr); // �������� ��������� ���������

	SetScTris(SecCnfGrp,nScTrPr);	// �������. �����. ����� ��� ����������� ����
	CorScTris(SecCnfGrp,nScTrPr);	// ���� �. ���- ���� �����
	SetScStbl(SecCnfGrp,nScStPr);	// ����������������. ����(� ��� ���
	SetScTwos(SecCnfGrp,nScTrPr,nScStPr);	//����� �� (� ��� ���
	CorScTwTr(SecCnfGrp);			// ���� �����. ��� ������ ��. ����(� ��� ���

	SetTwsCnf();
	//CorScTwos();					// ��������� 'd'
}

void MolData::SetScTris(ms1D<ms1Dint> &nScTrPr)	// �������. ������������
{
	int i,j,k;
	int icg;
	int i0,i1,i2,j0,j1,j2;

	double a,b,d,e,f,g,h;
	double csa,csb,csg,sng;
	double det;

	double mxds;
	
	bool cca,ccl;

	Vec3db P0,P1,P2,P3;
	Vec3db dP01,dP12,dP20,dH;
	Vec3db nx,ny,nz,pc,dr,mr;

	ms1D<int> its_un,its_ge;

	ms1D<ms1Dint> nTr_un;
	ms1D<ms1Dint> nTr_ge;

	j	=0;
	for(icg	=0;icg<TrsCnfGrp.N;icg++) j	= TrsCnfGrp.x[icg].N>j ? TrsCnfGrp.x[icg].N : j;

	j+=5;
	nTr_un.init(0,j);
	nTr_ge.init(0,j);
	its_un.init(0,j);
	its_ge.init(0,j);

	
	b	*= b = a = p_rol+s_rol;

	mxds	= 2*a;
	mxds	*=mxds;
	
	for(icg	=0;icg<TrsCnfGrp.N;icg++)
	{
		SRol->x[icg].igr	= icg;
		
		//SRol->x[icg].Tris	= new ms1D<ScTrPnt> [1];
		for(i=0;i<nTr_un.N;nTr_un.x[i++].N=0);
		for(i=0;i<nTr_ge.N;nTr_ge.x[i++].N=0);
		nTr_un.N	= nTr_ge.N = 0;//TrsCnfGrp.x[icg].N;
		for(i=0;i<TrsCnfGrp.x[icg].N;i++)
		{
			j	= TrsCnfGrp.x[icg].x[i];
			/*P0	= Tris->x[j].pc;
			for(i1=0;i1<i;i1++)
			{
				j1	= TrsCnfGrp.x[icg].x[i1];
				P1	= Tris->x[j1].pc;
				dP01= P1-P0;
				e	= dP01.ssqr();
				if(e<=mxds)
				{
					nTr_ge.x[i].add(j1);
					nTr_un.x[i].add(j1);
					nTr_un.x[i1].add(j);
				}
			}*/

		/**/	nTr_un.x[i].pst(TrsCnfGrp.x[icg]);
			k	= nTr_un.x[i].fnd(j);
			if(k!=-1)
			{
				nTr_un.x[i].rem(1,k);
				nTr_ge.x[i].pst(0,k,nTr_un.x[i]);
			}
			else
			{
				cout<<"Error 1 in 'MolData::SetScTris(ms1D<ms1Dint> &nScTrPr)' "<<endl;
				exit(1);
			}/**/
		}
		
		if(TrsCnfGrp.x[icg].N>2)
		{
			k	 = -1;
			for(i0=0;i0<TrsCnfGrp.x[icg].N;i0++)
			{
				j0	= TrsCnfGrp.x[icg].x[i0];
				P0	= Tris->x[j0].pc;
				for(i1=0;i1<nTr_ge.x[i0].N;i1++)
				{
					j1	= nTr_ge.x[i0].x[i1];
					P1	= Tris->x[j1].pc;
					dP01= P1-P0;
					dP01.nrml(e);
					its_ge.N	= 0;
					its_un.N	= 0;
					nTr_ge.x[i1].itss(nTr_ge.x[i0],its_ge);
					nTr_un.x[i1].itss(nTr_un.x[i0],its_un);
					
					for(i2=0;i2<its_ge.N;i2++)
					{
						j2	= its_ge.x[i2];
						P2	= Tris->x[j2].pc;
						dP12= P2-P1;
						dP20= P0-P2;
						dP12.nrml(g);
						dP20.nrml(f);
						
						// �� ����� ��� (���������P1, ���������)
						csa	= f/(2*a);	// ������ (P2,P0,����
						csb	= e/(2*a);	// ������ (P1,P0,����
						csg	= (f*f+e*e-g*g)/(2*f*e);	// ������ (P2,P0,P1)
						
						// ����������� ���. (���������P0 ��� nx,ny,nz)
						nx	= -dP20;
						ny	= dP01	- nx*csg;
						ny.nrml(sng);
						
						nz.crss(nx,ny);
						
						// ���������� ���������� ���� ���� ��������� (nx,ny).
						d	= (csb-csg*csa)/sng;		// d*a -> ������ ����dP20 � ���� ��� � ���� (nx,ny).
						h	*= h	= (csa-csg*csb)/sng;// h*a*a -> �������� � ����dP01 � ���� ��� � ���� (nx,ny).
						if ((d*d<=(1-csa*csa))&&(h<=(1-csb*csb))) // ����� ������ �������. 
						{						// ����������d*a �sqrt(H)*a ������ � ���� dP3 �dP1 � ���.
							// ���������� ��� � ���� (nx,ny)
							P3	= nx*csa+ny*d;
							P3	*=a;
							
							// ��������� ����������� �����							
							d	*=d;
							d	+=csa*csa;		// �������� �� (P0,P1.����
							h	= a*sqrt(1-d);	// ���
							
							dH	= nz*h;			// ���-��� (P0,���� (���������������
							P3	+=P0;			// ���-��� ���� ��� ���������������
							pc	= P3+dH;		// ���-��� ��� ���������������-> ������ ���
							
							// ���� ��� ���� 
							//dr	= pc-P0;							
							//Tris->x[j0].mx.pmv(mr,dr);
							//if ((mr.x[0]>-ERR_ALW)&&(mr.x[1]>-ERR_ALW)&&(mr.x[2]>-ERR_ALW))
							if(Tris->x[j0].isTris(pc))
							{
								if(Tris->x[j1].isTris(pc))
								{
									if(Tris->x[j2].isTris(pc))
									{
										ccl	= false;
										cca	= true;
										for(i=0;i<its_un.N&&cca;i++)
										{
											j	= its_un.x[i];
											dr	= pc - Tris->x[j].pc;											
											cca	= !(((dr.ssqr()+1e-13<b))&&(j!=j2));
										}
										if	(cca)
										{
											k++;
											if (k>=SRol->x[icg].Tris->mN)
											{
												SRol->x[icg].Tris->adm_(ADD_SCTRS_NMBR);
											}
											//SRol->x[icg].Tris->x[k].mx		= new ms1DVec3db [1];
											//SRol->x[icg].Tris->x[k].mx->one(3);
											/*SRol->x[icg].Tris->x[k].n_tr	= new ms1Dint [1];
											SRol->x[icg].Tris->x[k].n_tw	= new ms1Dint [1];
											SRol->x[icg].Tris->x[k].n_str	= new ms1Dint [1];
											SRol->x[icg].Tris->x[k].n_stw	= new ms1Dint [1];
											SRol->x[icg].Tris->x[k].n_pnt	= new ms1Dint [1];*/
											//SRol->x[icg].Tris->x[k].n_tr->one(3);
											SRol->x[icg].Tris->x[k].n_tr->x[0]	= j0;
											SRol->x[icg].Tris->x[k].n_tr->x[1]	= j1;
											SRol->x[icg].Tris->x[k].n_tr->x[2]	= j2;
											SRol->x[icg].Tris->x[k].n_tr->sort();
											
											SRol->x[icg].Tris->x[k].pc			= pc; 
											SRol->x[icg].Tris->x[k].nr			= -dH;											
											
											nScTrPr.x[j0].add(k);
											nScTrPr.x[j1].add(k);
											nScTrPr.x[j2].add(k);
											
											// ������ ��. ��� ���������'pc' ������� � ��� �������
											nx	=P0-pc;
											ny	=P1-pc;
											nz	=P2-pc;
											nx.nrml();
											ny.nrml();
											nz.nrml();

											SRol->x[icg].Tris->x[k].csa			= -nx.scpr(dH);

											SRol->x[icg].Tris->x[k].mx->x[0].crss(nx,ny);
											SRol->x[icg].Tris->x[k].mx->x[1].crss(ny,nz);
											SRol->x[icg].Tris->x[k].mx->x[2].crss(nz,nx);
											
											//����� ������ ��� ���� ���� ���
											det	= nx.x[0]*(ny.x[1]*nz.x[2]-ny.x[2]*nz.x[1])-nx.x[1]*(ny.x[0]*nz.x[2]-ny.x[2]*nz.x[0])+nx.x[2]*(ny.x[0]*nz.x[1]-ny.x[1]*nz.x[0]);
											SRol->x[icg].Tris->x[k].mx->x[0]	/= det;
											SRol->x[icg].Tris->x[k].mx->x[1]	/= det;
											SRol->x[icg].Tris->x[k].mx->x[2]	/= det;
											SRol->x[icg].Tris->x[k].mx->x[0].nrml();
											SRol->x[icg].Tris->x[k].mx->x[1].nrml();
											SRol->x[icg].Tris->x[k].mx->x[2].nrml();

											// ����� ���� ��� ���� �������
											/*SRol->x[icg].Tris->x[k].mx.x[0]	= ny.x[1]*nz.x[2]-ny.x[2]*nz.x[1];
											SRol->x[icg].Tris->x[k].mx.x[1]	= ny.x[2]*nz.x[0]-ny.x[0]*nz.x[2];
											SRol->x[icg].Tris->x[k].mx.x[2]	= ny.x[0]*nz.x[1]-ny.x[1]*nz.x[0];
											SRol->x[icg].Tris->x[k].mx.x[3]	= nx.x[2]*nz.x[1]-nx.x[1]*nz.x[2];
											SRol->x[icg].Tris->x[k].mx.x[4]	= nx.x[0]*nz.x[2]-nx.x[2]*nz.x[0];
											SRol->x[icg].Tris->x[k].mx.x[5]	= nx.x[1]*nz.x[0]-nx.x[0]*nz.x[1];
											SRol->x[icg].Tris->x[k].mx.x[6]	= nx.x[1]*ny.x[2]-nx.x[2]*ny.x[1];
											SRol->x[icg].Tris->x[k].mx.x[7]	= nx.x[2]*ny.x[0]-nx.x[0]*ny.x[2];
											SRol->x[icg].Tris->x[k].mx.x[8]	= nx.x[0]*ny.x[1]-nx.x[1]*ny.x[0];

											//SRol->x[icg].Tris->x[k].mx	/= det;
											SRol->x[icg].Tris->x[k].mx.x[0]	/= det;
											SRol->x[icg].Tris->x[k].mx.x[1]	/= det;
											SRol->x[icg].Tris->x[k].mx.x[2]	/= det;
											SRol->x[icg].Tris->x[k].mx.x[3]	/= det;
											SRol->x[icg].Tris->x[k].mx.x[4]	/= det;
											SRol->x[icg].Tris->x[k].mx.x[5]	/= det;
											SRol->x[icg].Tris->x[k].mx.x[6]	/= det;
											SRol->x[icg].Tris->x[k].mx.x[7]	/= det;
											SRol->x[icg].Tris->x[k].mx.x[8]	/= det;*/

											SRol->x[icg].Tris->N++;
										}
									}
								}
							}
							// ������ 
							pc	= P3-dH;
							
							// ���� ��� ���� 
							/*dr	= pc-P0;
							Tris->x[j0].mx.pmv(mr,dr);
							if ((mr.x[0]>-ERR_ALW)&&(mr.x[1]>-ERR_ALW)&&(mr.x[2]>-ERR_ALW))
							{*/
							if(Tris->x[j0].isTris(pc))
							{
								if(Tris->x[j1].isTris(pc))
								{
									if(Tris->x[j2].isTris(pc))
									{
							
										ccl	= false;
										cca	= true;
										for(i=0;i<its_un.N&&cca;i++)
										{
											j	= its_un.x[i];
											dr	= pc - Tris->x[j].pc;
											cca	= !(((dr.ssqr()+1e-13)<b)&&(j!=j2));
										}
										if	(cca)
										{
											k++;
											if (k>=SRol->x[icg].Tris->mN)
											{
												SRol->x[icg].Tris->adm_(ADD_SCTRS_NMBR);
											}
											//SRol->x[icg].Tris->x[k].mx		= new ms1DVec3db [1];
											//SRol->x[icg].Tris->x[k].mx->one(3);
											/*SRol->x[icg].Tris->x[k].n_tr	= new ms1Dint [1];
											SRol->x[icg].Tris->x[k].n_tw	= new ms1Dint [1];
											SRol->x[icg].Tris->x[k].n_str	= new ms1Dint [1];
											SRol->x[icg].Tris->x[k].n_stw	= new ms1Dint [1];
											SRol->x[icg].Tris->x[k].n_pnt	= new ms1Dint [1];*/
											//SRol->x[icg].Tris->x[k].n_tr->one(3);
											SRol->x[icg].Tris->x[k].n_tr->x[0]	= j0;
											SRol->x[icg].Tris->x[k].n_tr->x[1]	= j1;
											SRol->x[icg].Tris->x[k].n_tr->x[2]	= j2;
											SRol->x[icg].Tris->x[k].n_tr->sort();
											
											SRol->x[icg].Tris->x[k].pc			= pc; 
											SRol->x[icg].Tris->x[k].nr			= dH;
											
											nScTrPr.x[j0].add(k);
											nScTrPr.x[j1].add(k);
											nScTrPr.x[j2].add(k);
											
											// ������ ��. ��� ���������'pc' ������� � ��� �������
											nx	=P0-pc;
											ny	=P1-pc;
											nz	=P2-pc;
											nx.nrml();
											ny.nrml();
											nz.nrml();

											SRol->x[icg].Tris->x[k].csa			= nx.scpr(dH);

											SRol->x[icg].Tris->x[k].mx->x[0].crss(nx,ny);
											SRol->x[icg].Tris->x[k].mx->x[1].crss(ny,nz);
											SRol->x[icg].Tris->x[k].mx->x[2].crss(nz,nx);
											
											//����� ������ ��� ���� ���� ���
											det	= nx.x[0]*(ny.x[1]*nz.x[2]-ny.x[2]*nz.x[1])-nx.x[1]*(ny.x[0]*nz.x[2]-ny.x[2]*nz.x[0])+nx.x[2]*(ny.x[0]*nz.x[1]-ny.x[1]*nz.x[0]);

											SRol->x[icg].Tris->x[k].mx->x[0]	/= det;
											SRol->x[icg].Tris->x[k].mx->x[1]	/= det;
											SRol->x[icg].Tris->x[k].mx->x[2]	/= det;
											SRol->x[icg].Tris->x[k].mx->x[0].nrml();
											SRol->x[icg].Tris->x[k].mx->x[1].nrml();
											SRol->x[icg].Tris->x[k].mx->x[2].nrml();

											// ����� ���� ��� ���� �������
											/*SRol->x[icg].Tris->x[k].mx.x[0]	= ny.x[1]*nz.x[2]-ny.x[2]*nz.x[1];
											SRol->x[icg].Tris->x[k].mx.x[1]	= ny.x[2]*nz.x[0]-ny.x[0]*nz.x[2];
											SRol->x[icg].Tris->x[k].mx.x[2]	= ny.x[0]*nz.x[1]-ny.x[1]*nz.x[0];
											SRol->x[icg].Tris->x[k].mx.x[3]	= nx.x[2]*nz.x[1]-nx.x[1]*nz.x[2];
											SRol->x[icg].Tris->x[k].mx.x[4]	= nx.x[0]*nz.x[2]-nx.x[2]*nz.x[0];
											SRol->x[icg].Tris->x[k].mx.x[5]	= nx.x[1]*nz.x[0]-nx.x[0]*nz.x[1];
											SRol->x[icg].Tris->x[k].mx.x[6]	= nx.x[1]*ny.x[2]-nx.x[2]*ny.x[1];
											SRol->x[icg].Tris->x[k].mx.x[7]	= nx.x[2]*ny.x[0]-nx.x[0]*ny.x[2];
											SRol->x[icg].Tris->x[k].mx.x[8]	= nx.x[0]*ny.x[1]-nx.x[1]*ny.x[0];
											
											//SRol->x[icg].Tris->x[k].mx	/= det;
											SRol->x[icg].Tris->x[k].mx.x[0]	/= det;
											SRol->x[icg].Tris->x[k].mx.x[1]	/= det;
											SRol->x[icg].Tris->x[k].mx.x[2]	/= det;
											SRol->x[icg].Tris->x[k].mx.x[3]	/= det;
											SRol->x[icg].Tris->x[k].mx.x[4]	/= det;
											SRol->x[icg].Tris->x[k].mx.x[5]	/= det;
											SRol->x[icg].Tris->x[k].mx.x[6]	/= det;
											SRol->x[icg].Tris->x[k].mx.x[7]	/= det;
											SRol->x[icg].Tris->x[k].mx.x[8]	/= det;*/
											
											SRol->x[icg].Tris->N++;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}
void MolData::SetScTris(ms1D<int> &n_icg, ms1D<ms1Dint> &nScTrPr)	// �������. ������������
{
	int i,j,k;
	int i0,i1,i2,j0,j1,j2;
	int icg,ic;

	double a,b,d,e,f,g,h;
	double csa,csb,csg,sng;
	double det,s_rol;
	
	bool cca,ccl;

	double mxds;

	Vec3db P0,P1,P2,P3;
	Vec3db dP01,dP12,dP20,dH;
	Vec3db nx,ny,nz,pc,dr,mr;

	ms1D<int> its_un,its_ge;

	ms1D<ms1Dint> nTr_un;
	ms1D<ms1Dint> nTr_ge;

	j	=0;
	j	=0;
	for(icg	=0;icg<TrsCnfGrp.N;icg++) j	= TrsCnfGrp.x[icg].N>j ? TrsCnfGrp.x[icg].N : j;

	nTr_un.sm(j+5);
	nTr_ge.sm(j+5);
	its_un.sm(j+5);
	its_ge.sm(j+5);
	InitObject(nTr_un);
	InitObject(nTr_ge);

	
	for(ic=0;ic<n_icg.N;ic++)
	{
		icg	= n_icg.x[ic];

		s_rol	=  sro.x[icg];
		b	*= b = a = p_rol+s_rol;
		mxds	*= mxds = 2*a;
		
		for(i=0;i<SRol->x[icg].Tris->N;i++)
		{
			SRol->x[icg].Tris->x[i].mx->N		= 0;
			SRol->x[icg].Tris->x[i].n_pnt->N	= 0;
			SRol->x[icg].Tris->x[i].n_str->N	= 0;
			SRol->x[icg].Tris->x[i].n_stw->N	= 0;
			SRol->x[icg].Tris->x[i].n_tr->N		= 0;
			SRol->x[icg].Tris->x[i].n_tw->N		= 0;
			SRol->x[icg].Tris->x[i].nr			= 0.0;
			SRol->x[icg].Tris->x[i].pc			= 0.0;
			SRol->x[icg].Tris->x[i].csa			= 0.0;
		}
		SRol->x[icg].Tris->N =0;
		
		//nTr_un.N	= nTr_ge.N = 0;
		for(i=0;i<nTr_un.N;nTr_un.x[i++].N=0);
		for(i=0;i<nTr_ge.N;nTr_ge.x[i++].N=0);
		nTr_un.N	= nTr_ge.N = 0;//TrsCnfGrp.x[icg].N;
		if(icg<TrsCnfGrp.N)
		{
			for(i=0;i<TrsCnfGrp.x[icg].N;i++)
			{
				j	= TrsCnfGrp.x[icg].x[i];

				/*P0	= Tris->x[j].pc;
				for(i1=0;i1<i;i1++)
				{
					j1	= TrsCnfGrp.x[icg].x[i1];
					P1	= Tris->x[j1].pc;
					dP01= P1-P0;
					e	= dP01.ssqr();
					if(e<=mxds)
					{
						nTr_ge.x[i].add(j1);
						nTr_un.x[i].add(j1);
						nTr_un.x[i1].add(j);
					}
				}*/

				/**/	nTr_un.x[i].pst(TrsCnfGrp.x[icg]);
				k	= nTr_un.x[i].fnd(j);
				if(k!=-1)
				{
				nTr_un.x[i].rem(1,k);
				nTr_ge.x[i].pst(0,k,nTr_un.x[i]);
				}
				else
				{
				cout<<"Error 1 in 'MolData::SetScTris(ms1D<int> &n_icg, ms1D<ms1Dint> &nScTrPr)' "<<endl;				
				exit(1);
				}/**/
			}
			
			if(TrsCnfGrp.x[icg].N>2)
			{
				k	 = -1;
				for(i0=0;i0<TrsCnfGrp.x[icg].N;i0++)
				{
					j0	= TrsCnfGrp.x[icg].x[i0];
					P0	= Tris->x[j0].pc;
					for(i1=0;i1<nTr_ge.x[i0].N;i1++)
					{
						j1	= nTr_ge.x[i0].x[i1];
						P1	= Tris->x[j1].pc;
						dP01= P1-P0;
						dP01.nrml(e);
						its_ge.N	= 0;
						its_un.N	= 0;
						nTr_ge.x[i1].itss(nTr_ge.x[i0],its_ge);
						nTr_un.x[i1].itss(nTr_un.x[i0],its_un);
						
						for(i2=0;i2<its_ge.N;i2++)
						{
							j2	= its_ge.x[i2];
							P2	= Tris->x[j2].pc;
							dP12= P2-P1;
							dP20= P0-P2;
							dP12.nrml(g);
							dP20.nrml(f);
							
							// �� ����� ��� (���������P1, ���������)
							csa	= f/(2*a);	// ������ (P2,P0,����
							csb	= e/(2*a);	// ������ (P1,P0,����
							csg	= (f*f+e*e-g*g)/(2*f*e);	// ������ (P2,P0,P1)
							
							// ����������� ���. (���������P0 ��� nx,ny,nz)
							nx	= -dP20;
							ny	= dP01	- nx*csg;
							ny.nrml(sng);
							
							nz.crss(nx,ny);
							
							// ���������� ���������� ���� ���� ��������� (nx,ny).
							d	= (csb-csg*csa)/sng;		// d*a -> ������ ����dP20 � ���� ��� � ���� (nx,ny).
							h	*= h	= (csa-csg*csb)/sng;// h*a*a -> �������� � ����dP01 � ���� ��� � ���� (nx,ny).
							if ((d*d<=(1-csa*csa))&&(h<=(1-csb*csb))) // ����� ������ �������. 
							{						// ����������d*a �sqrt(H)*a ������ � ���� dP3 �dP1 � ���.
								// ���������� ��� � ���� (nx,ny)
								P3	= nx*csa+ny*d;
								P3	*=a;
								
								// ��������� ����������� �����							
								d	*=d;
								d	+=csa*csa;		// �������� �� (P0,P1.����
								h	= a*sqrt(1-d);	// ���
								
								dH	= nz*h;			// ���-��� (P0,���� (���������������
								P3	+=P0;			// ���-��� ���� ��� ���������������
								pc	= P3+dH;		// ���-��� ��� ���������������-> ������ ���
								
								// ���� ��� ���� 
								//dr	= pc-P0;							
								//Tris->x[j0].mx.pmv(mr,dr);
								//if ((mr.x[0]>-ERR_ALW)&&(mr.x[1]>-ERR_ALW)&&(mr.x[2]>-ERR_ALW))
								if(Tris->x[j0].isTris(pc))
								{
									if(Tris->x[j1].isTris(pc))
									{
										if(Tris->x[j2].isTris(pc))
										{
											ccl	= false;
											cca	= true;
											for(i=0;i<its_un.N&&cca;i++)
											{
												j	= its_un.x[i];
												dr	= pc - Tris->x[j].pc;
												cca	= !(((dr.ssqr()+1e-13<b))&&(j!=j2));
											}
											if	(cca)
											{
												k++;
												if (k>=SRol->x[icg].Tris->mN)SRol->x[icg].Tris->adm_(ADD_SCTRS_NMBR);
												//SRol->x[icg].Tris->x[k].mx		= new ms1DVec3db [1];
												SRol->x[icg].Tris->x[k].mx->one(3);
												/*SRol->x[icg].Tris->x[k].n_tr	= new ms1Dint [1];
												SRol->x[icg].Tris->x[k].n_tw	= new ms1Dint [1];
												SRol->x[icg].Tris->x[k].n_str	= new ms1Dint [1];
												SRol->x[icg].Tris->x[k].n_stw	= new ms1Dint [1];
												SRol->x[icg].Tris->x[k].n_pnt	= new ms1Dint [1];*/
												SRol->x[icg].Tris->x[k].n_tr->one(3);
												SRol->x[icg].Tris->x[k].n_tr->x[0]	= j0;
												SRol->x[icg].Tris->x[k].n_tr->x[1]	= j1;
												SRol->x[icg].Tris->x[k].n_tr->x[2]	= j2;
												SRol->x[icg].Tris->x[k].n_tr->sort();
												
												SRol->x[icg].Tris->x[k].pc			= pc; 
												SRol->x[icg].Tris->x[k].nr			= -dH;											
												
												nScTrPr.x[j0].add(k);
												nScTrPr.x[j1].add(k);
												nScTrPr.x[j2].add(k);
												
												// ������ ��. ��� ���������'pc' ������� � ��� �������
												nx	=P0-pc;
												ny	=P1-pc;
												nz	=P2-pc;
												nx.nrml();
												ny.nrml();
												nz.nrml();
												
												SRol->x[icg].Tris->x[k].csa			= -nx.scpr(dH);
												
												SRol->x[icg].Tris->x[k].mx->x[0].crss(nx,ny);
												SRol->x[icg].Tris->x[k].mx->x[1].crss(ny,nz);
												SRol->x[icg].Tris->x[k].mx->x[2].crss(nz,nx);
												
												//����� ������ ��� ���� ���� ���
												det	= nx.x[0]*(ny.x[1]*nz.x[2]-ny.x[2]*nz.x[1])-nx.x[1]*(ny.x[0]*nz.x[2]-ny.x[2]*nz.x[0])+nx.x[2]*(ny.x[0]*nz.x[1]-ny.x[1]*nz.x[0]);
												SRol->x[icg].Tris->x[k].mx->x[0]	/= det;
												SRol->x[icg].Tris->x[k].mx->x[1]	/= det;
												SRol->x[icg].Tris->x[k].mx->x[2]	/= det;
												SRol->x[icg].Tris->x[k].mx->x[0].nrml();
												SRol->x[icg].Tris->x[k].mx->x[1].nrml();
												SRol->x[icg].Tris->x[k].mx->x[2].nrml();
												
												SRol->x[icg].Tris->N++;
											}
										}
									}
								}
								// ������ 
								pc	= P3-dH;
								
								if(Tris->x[j0].isTris(pc))
								{
									if(Tris->x[j1].isTris(pc))
									{
										if(Tris->x[j2].isTris(pc))
										{
											
											ccl	= false;
											cca	= true;
											for(i=0;i<its_un.N&&cca;i++)
											{
												j	= its_un.x[i];
												dr	= pc - Tris->x[j].pc;
												cca	= !(((dr.ssqr()+1e-13)<b)&&(j!=j2));
											}
											if	(cca)
											{
												k++;
												if (k>=SRol->x[icg].Tris->mN)SRol->x[icg].Tris->adm_(ADD_SCTRS_NMBR);
												//SRol->x[icg].Tris->x[k].mx		= new ms1DVec3db [1];
												SRol->x[icg].Tris->x[k].mx->one(3);
												/*SRol->x[icg].Tris->x[k].n_tr	= new ms1Dint [1];
												SRol->x[icg].Tris->x[k].n_tw	= new ms1Dint [1];
												SRol->x[icg].Tris->x[k].n_str	= new ms1Dint [1];
												SRol->x[icg].Tris->x[k].n_stw	= new ms1Dint [1];
												SRol->x[icg].Tris->x[k].n_pnt	= new ms1Dint [1];*/
												SRol->x[icg].Tris->x[k].n_tr->one(3);
												SRol->x[icg].Tris->x[k].n_tr->x[0]	= j0;
												SRol->x[icg].Tris->x[k].n_tr->x[1]	= j1;
												SRol->x[icg].Tris->x[k].n_tr->x[2]	= j2;
												SRol->x[icg].Tris->x[k].n_tr->sort();
												
												SRol->x[icg].Tris->x[k].pc			= pc; 
												SRol->x[icg].Tris->x[k].nr			= dH;
												
												nScTrPr.x[j0].add(k);
												nScTrPr.x[j1].add(k);
												nScTrPr.x[j2].add(k);
												
												// ������ ��. ��� ���������'pc' ������� � ��� �������
												nx	=P0-pc;
												ny	=P1-pc;
												nz	=P2-pc;
												nx.nrml();
												ny.nrml();
												nz.nrml();
												
												SRol->x[icg].Tris->x[k].csa			= nx.scpr(dH);
												
												SRol->x[icg].Tris->x[k].mx->x[0].crss(nx,ny);
												SRol->x[icg].Tris->x[k].mx->x[1].crss(ny,nz);
												SRol->x[icg].Tris->x[k].mx->x[2].crss(nz,nx);
												
												//����� ������ ��� ���� ���� ���
												det	= nx.x[0]*(ny.x[1]*nz.x[2]-ny.x[2]*nz.x[1])-nx.x[1]*(ny.x[0]*nz.x[2]-ny.x[2]*nz.x[0])+nx.x[2]*(ny.x[0]*nz.x[1]-ny.x[1]*nz.x[0]);
												
												SRol->x[icg].Tris->x[k].mx->x[0]	/= det;
												SRol->x[icg].Tris->x[k].mx->x[1]	/= det;
												SRol->x[icg].Tris->x[k].mx->x[2]	/= det;
												SRol->x[icg].Tris->x[k].mx->x[0].nrml();
												SRol->x[icg].Tris->x[k].mx->x[1].nrml();
												SRol->x[icg].Tris->x[k].mx->x[2].nrml();
												
												SRol->x[icg].Tris->N++;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

void MolData::CorScTris(ms1D<ms1Dint> &nScTrPr)		// ������������. ��� ���������
{
	int i,j,i0,i1,i2,j0,j1;
	int icg,*x;

	j=0;
	for(icg=0;icg<SRol->N;icg++)j = j>SRol->x[icg].Tris->N ? j : SRol->x[icg].Tris->N;

	ms1D<bool> alw(j);
	ms1D<int> trs(j),trs1(j);
	ms1D<ms1Dint> tr_c(j);
	Vec3db p0,dr;
	
	InitObject(tr_c);

	for(icg=0;icg<TrsCnfGrp.N;icg++)
	{
		if(SRol->x[icg].Tris->N!=0)
		{
			tr_c.N = alw.N = SRol->x[icg].Tris->N;
			alw	= true;
			for(i0=0;i0<SRol->x[icg].Tris->N;i0++)
			{
				tr_c.x[i0].N= 0;
				if(alw.x[i0])
				{
					p0	= SRol->x[icg].Tris->x[i0].pc;
					for(i1=i0+1;i1<SRol->x[icg].Tris->N;i1++)
					{
						if(alw.x[i1])
						{
							dr	= SRol->x[icg].Tris->x[i1].pc-p0;
							if(dr.ssqr()<SQ_ERR_ALW)		// ���� ����� ����. ������. ����
							{
								alw.x[i1]	= false;		// �����������������. ���
								tr_c.x[i0].add(i1);			// ����� ��� ����� ������� ��� �. ���
							}
						}
					}
				}
			}
			// ���� ����� ������ ���� � ���� nScTrPr
			for(i=0;i<SRol->x[icg].Tris->N;i++)// перебор всех сфер вторичной обкатки
			{
				for(j=0;j<tr_c.x[i].N;j++)	// перебор всех претендентов на удаление по факту совпадения с текущей сферой втор обкатки
				{
					i0	= tr_c.x[i].x[j]; // номер сферы которую необходимо удалить
					
					x	= SRol->x[icg].Tris->x[i0].n_tr->x; // копирование указателя на массив сфер первичной обкати на которые опирается удаляемая сфера втор обкатки
					for(j0=0;j0<SRol->x[icg].Tris->x[i0].n_tr->N;j0++) // перебор всех сфер первичной обкатки на которые опирается удаляемая сфера втор обкатки
					{
						i1	= x[j0]; // номер сферы-опоры первичной обкатки
						i2	= nScTrPr.x[i1].fnd(i);	// поиск номера 'i' сферы втор обкатки среди номеров сфер втор обкатки опирающихся на текущ. сферу первичной обкатки
						if(i2==-1) // если номер не найден, то
						{	// 
							j1	= nScTrPr.x[i1].fnd(i0);	// поиск номера 'i0' сферы втор обкатки среди номеров сфер втор обкатки опирающихся на текущ. сферы первичной обкатки
							if(j1!=-1) 
							{
								nScTrPr.x[i1].x[j1]	= i; // если номер найден, то запись о номере i0 заменяется на запись о номере 'i'
							}else
							{
								nScTrPr.x[i1].add(i); // если номера нет то добавляется новый номер 'i'
							}
							SRol->x[icg].Tris->x[i].n_tr->add(i1); // в массив о номерах первичной обкатки добавляется номер i1 сферы вторичной обкатки
						}else // если номер найден , то
						{
							j1	= nScTrPr.x[i1].fnd(i0); // поиск номера 'i0' сферы втор обкатки среди номеров сфер втор обкатки опирающихся на текущ. сферы первичной обкатки
							if(j1!=-1) // номер найден
							{
								nScTrPr.x[i1].x[j1]	= nScTrPr.x[i1].x[--nScTrPr.x[i1].N]; // удаление записи о номере i0
							}
						}
					}
				}
			}
			
			// удаление самих сфер вторичной обкатки
			
			trs.fill();
			trs	= -1;
			j1	= 0;
			for(i=0;i<alw.N;i++) trs.x[i]	= alw.x[i] ? j1++ : trs.x[i];
			for(i=0;i<nScTrPr.N;i++)
			{
				if(Tris->x[i].igr==icg)
				{
					for(i1=0;i1<nScTrPr.x[i].N;i1++)
					{
						j	= trs.x[nScTrPr.x[i].x[i1]];
						if(j!=-1) nScTrPr.x[i].x[i1]	= j;
						else{
							cout<<"Error! Tr. point relates to unexist seс. tr. point."<<endl;
							exit(5);
						}
					}
					nScTrPr.x[i].sort();
				}
			}
			
			for(i=0;(i<SRol->x[icg].Tris->N)&&(i==trs.x[i]);i++);
			for(;i<SRol->x[icg].Tris->N;i++)
			{
				if(trs.x[i]!=-1)
				{
					Swap(SRol->x[icg].Tris->x[trs.x[i]],SRol->x[icg].Tris->x[i]);
				}
			}
			SRol->x[icg].Tris->N	= j1;
		}
	}

	/*for(icg=0;icg<TrsCnfGrp.N;icg++)
	{
		for(i0=0;i0<SRol->x[icg].Tris->N;i0++)
		{
			for(j0=0;j0<TrsCnfGrp.x[icg].N;j0++)
			{
				j1	= TrsCnfGrp.x[icg].x[j0]
				ii	= SRol->x[icg].Tris->x[i0].n_tr->fnd(j1);
				if (ii==-1)
				{
					dp	= Tris->x[j1].pc-SRol->x[icg].Tris->x[i0].pc;
					if(dp.)
				}
			}
		}
	}//*/
}

void MolData::CorScTris(ms1D<int> &n_icg, ms1D<ms1Dint> &nScTrPr)		// ������������. ��� ���������
{
	int i,j,i0,i1,i2,j0,j1;
	int icg,ic,*x;	

	j=0;
	for(icg=0;icg<SRol->N;icg++)j = j>SRol->x[icg].Tris->N ? j : SRol->x[icg].Tris->N;

	ms1D<bool> alw(j);
	ms1D<int> trs(j),trs1(j);
	ms1D<ms1Dint> tr_c(j);
	Vec3db p0,dr;

	InitObject(tr_c);
	

	for(ic=0;ic<n_icg.N;ic++)
	{
		icg	= n_icg.x[ic];
		if(SRol->x[icg].Tris->N!=0)
		{
			tr_c.N = alw.N = SRol->x[icg].Tris->N;
			alw	= true;
			for(i0=0;i0<SRol->x[icg].Tris->N;i0++)
			{
				tr_c.x[i0].N= 0;
				if(alw.x[i0])
				{
					p0	= SRol->x[icg].Tris->x[i0].pc;
					for(i1=i0+1;i1<SRol->x[icg].Tris->N;i1++)
					{
						if(alw.x[i1])
						{
							dr	= SRol->x[icg].Tris->x[i1].pc-p0;
							if(dr.ssqr()<SQ_ERR_ALW)		// ���� ����� ����. ������. ����
							{
								alw.x[i1]	= false;		// �����������������. ���
								tr_c.x[i0].add(i1);			// ����� ��� ����� ������� ��� �. ���
							}
						}
					}
				}
			}
			// ���� ����� ������ ���� � ���� nScTrPr
			for(i=0;i<SRol->x[icg].Tris->N;i++)
			{
				for(j=0;j<tr_c.x[i].N;j++)
				{
					i0	= tr_c.x[i].x[j];
					
					x	= SRol->x[icg].Tris->x[i0].n_tr->x;
					for(j0=0;j0<SRol->x[icg].Tris->x[i0].n_tr->N;j0++)
					{
						i1	= x[j0];
						i2	= nScTrPr.x[i1].fnd(i);
						if(i2==-1)
						{
							j1	= nScTrPr.x[i1].fnd(i0);
							if(j1!=-1) 
							{
								nScTrPr.x[i1].x[j1]	= i;
							}else
							{
								nScTrPr.x[i1].add(i);
							}
							SRol->x[icg].Tris->x[i].n_tr->add(i1);
						}else
						{
							j1	= nScTrPr.x[i1].fnd(i0);
							if(j1!=-1) 
							{
								nScTrPr.x[i1].x[j1]	= nScTrPr.x[i1].x[--nScTrPr.x[i1].N];
							}
						}
					}
				}
			}
			
			// ���� ����������. ������������
			
			trs.fill();
			trs	= -1;
			j1	= 0;
			for(i=0;i<alw.N;i++) trs.x[i]	= alw.x[i] ? j1++ : trs.x[i];
			for(i=0;i<nScTrPr.N;i++)
			{
				if(Tris->x[i].igr==icg)
				{
					for(i1=0;i1<nScTrPr.x[i].N;i1++)
					{
						j	= trs.x[nScTrPr.x[i].x[i1]];
						if(j!=-1) nScTrPr.x[i].x[i1]	= j;
						else{
							cout<<"Error! Tr. point relates to unexist ses. tr. point."<<endl;
							exit(5);
						}
					}
					nScTrPr.x[i].sort();
				}
			}
			
			for(i=0;(i<SRol->x[icg].Tris->N)&&(i==trs.x[i]);i++);
			for(;i<SRol->x[icg].Tris->N;i++)
			{
				if(trs.x[i]!=-1) Swap(SRol->x[icg].Tris->x[trs.x[i]],SRol->x[icg].Tris->x[i]);
			}
			SRol->x[icg].Tris->N	= j1;
		}
	}
}

void MolData::CorScTwTr()	// ������������. ��� ���������
{
	int i,j,k,i0,i1,icg;
	Vec3db		pc,p0,p1;
	Vec3db		vv,v0;

	for(icg	=0;icg<SRol->N;icg++)
	{
		for(i=0;i<SRol->x[icg].Tris->N;i++)
		{
			if(SRol->x[icg].Tris->x[i].n_tr->N>3)
			{
				SRol->x[icg].Tris->x[i].mx->one(SRol->x[icg].Tris->x[i].n_stw->N);
				SRol->x[icg].Tris->x[i].mx->N	= 0;
				pc	= SRol->x[icg].Tris->x[i].pc;
				v0	= 0.0;
				for(j=0;j<SRol->x[icg].Tris->x[i].n_tr->N;j++)
				{
					v0+=Tris->x[SRol->x[icg].Tris->x[i].n_tr->x[j]].pc-pc;
				}
				v0.nrml();
				for(j=0;j<SRol->x[icg].Tris->x[i].n_stw->N;j++)
				{
					k	= SRol->x[icg].Tris->x[i].n_stw->x[j];
					i0	= SRol->x[icg].Twos->x[k].n_tr.x[0];
					i1	= SRol->x[icg].Twos->x[k].n_tr.x[1];
					p0	= Tris->x[i0].pc-pc;
					p1	= Tris->x[i1].pc-pc;
					vv.crss(p0,p1);
					vv.nrml();
					vv	= vv.scpr(v0) >0 ? vv : -vv;
					SRol->x[icg].Tris->x[i].mx->add(vv);
				}
			}
		}
	}
}

void MolData::CorScTwTr(ms1D<int> &n_icg)	// ������������. ��� ���������
{
	int i,j,k,i0,i1,icg,ic;
	Vec3db		pc,p0,p1;
	Vec3db		vv,v0;

	for(ic=0;ic<n_icg.N;ic++)
	{
		icg	= n_icg.x[ic];
		for(i=0;i<SRol->x[icg].Tris->N;i++)
		{
			if(SRol->x[icg].Tris->x[i].n_tr->N>3)
			{
				SRol->x[icg].Tris->x[i].mx->one(SRol->x[icg].Tris->x[i].n_stw->N);
				SRol->x[icg].Tris->x[i].mx->N	= 0;
				pc	= SRol->x[icg].Tris->x[i].pc;
				v0	= 0.0;
				for(j=0;j<SRol->x[icg].Tris->x[i].n_tr->N;j++)
				{
					v0+=Tris->x[SRol->x[icg].Tris->x[i].n_tr->x[j]].pc-pc;
				}
				v0.nrml();
				for(j=0;j<SRol->x[icg].Tris->x[i].n_stw->N;j++)
				{
					k	= SRol->x[icg].Tris->x[i].n_stw->x[j];
					i0	= SRol->x[icg].Twos->x[k].n_tr.x[0];
					i1	= SRol->x[icg].Twos->x[k].n_tr.x[1];
					p0	= Tris->x[i0].pc-pc;
					p1	= Tris->x[i1].pc-pc;
					vv.crss(p0,p1);
					vv.nrml();
					vv	= vv.scpr(v0) >0 ? vv : -vv;
					SRol->x[icg].Tris->x[i].mx->add(vv);
				}
			}
		}
	}
}

void MolData::CorScStTr(ms1D<ms1Dint> &nScTrPr)	// ������������. ��� ���������
{
	int /*i,j,*/icg;

	for(icg=0;icg<SRol->N;icg++)
	{
		if(SRol->x[icg].Tris->N==1)
		{
			cout<<"Error in Secondary rolling!"<<endl;
			exit(7);
			/*for(i=0;i<SRol->x[icg].Tris->x[0].n_tr->N;i++)
			{
				j	= SRol->x[icg].Tris->x[0].n_tr->x[i];
				nScTrPr.x[j].N=0;
			}
			SRol->x[icg].Tris->N	= 0;
			*/
		}
	}
}

void MolData::SetScStbl(ms1D<ms1Dint> &nScStPr)	// �������������������������
{
	int i,j,k,i0,i1;
	//int icg;
	double b,d;
	Vec3db p1,p2;

	ms1D<int> nst;

	b	*=b = p_rol+s_rol;

	/*for(icg=0;icg<SRol->N;icg++)
	{
		SRol->x[icg].Stbl	= new ms1D<ScStPnt> [1];
	}*/

	nst.one(SRol->N);
	nst	= 0;

	for(i=0;i<Twos->N;i++)
	{
		if((Twos->x[i].ism)&&(Twos->x[i].hab.x[0]-p_rol<=s_rol))
		{
			if (Twos->x[i].hab.x[1]*Twos->x[i].hab.x[2]<0)
			{
				d		= sqrt(b-Twos->x[i].hab.x[0]*Twos->x[i].hab.x[0]);
				
				i0		= Twos->x[i].n_tr.x[0];
				i1		= Twos->x[i].n_tr.x[1];
				if (i0!=-1)
				{				
					if ((Tris->x[i0].igr!=-1)&&(Tris->x[i1].igr!=-1)&&(Tris->x[i0].igr==Tris->x[i1].igr))
					{
						j	= Tris->x[i0].igr;//
					}else
					{
						if((Tris->x[i0].igr==-1)&&(Tris->x[i1].igr==-1))
						{
							j	= SRol->N;
							if(SRol->N>=SRol->mN)SRol->adm_(ADD_GRP_NMBR);
							if(nst.N>=nst.mN) nst.adm(ADD_GRP_NMBR);
							SRol->N++;
							nst.x[nst.N]= 0;
							nst.N++;
						}else
						{
							cout<<"Error 2 in 'MolData::SetScStbl(ms1D<ms1Dint> &nScStPr)'"<<endl;
							exit(2);
						}
					}
					
					// j - ������������
					k	= nst.x[j];
					if(SRol->x[j].Stbl->N>=SRol->x[j].Stbl->mN) SRol->x[j].Stbl->adm_(ADD_SCTRS_NMBR);
					
					
					//SRol->x[j].Stbl->x[k].n_pnt1	= new ms1Dint [1];
					//SRol->x[j].Stbl->x[k].n_pnt2	= new ms1Dint [1];
					SRol->x[j].Stbl->x[k].d			= d;
					
					SRol->x[j].Stbl->x[k].nTw		= i;	// �������� �����������
					SRol->x[j].Stbl->x[k].n_tr.x[0]	= i0;	// ����������. ���
					SRol->x[j].Stbl->x[k].n_tr.x[1]	= i1;	// ����������. ���
					
					nScStPr.x[i0].add(k);
					nScStPr.x[i1].add(k);
					
					SRol->x[j].Stbl->x[k].isf	= true;
					
					// ����� ������������������
					SRol->x[j].Stbl->x[k].pc1	= Twos->x[i].rp-Twos->x[i].z*d;
					SRol->x[j].Stbl->x[k].pc2	= Twos->x[i].rp+Twos->x[i].z*d;
					SRol->x[j].Stbl->x[k].csa	= d/(p_rol+s_rol);
					SRol->x[j].Stbl->x[k].nst	= Twos->x[i].z;
					
					p1	= Tris->x[i0].pc-SRol->x[j].Stbl->x[k].pc1;
					p2	= Tris->x[i1].pc-SRol->x[j].Stbl->x[k].pc1;				
					SRol->x[j].Stbl->x[k].nc1.crss(p1,p2);
					SRol->x[j].Stbl->x[k].nc1.nrml();
					
					p1	= Tris->x[i0].pc-SRol->x[j].Stbl->x[k].pc2;
					p2	= Tris->x[i1].pc-SRol->x[j].Stbl->x[k].pc2;
					SRol->x[j].Stbl->x[k].nc2.crss(p2,p1);
					SRol->x[j].Stbl->x[k].nc2.nrml();
					
					SRol->x[j].Stbl->N			= ++nst.x[j];
				}else
				{
					j	= SRol->N;
					if(SRol->N>=SRol->mN)SRol->adm_(ADD_GRP_NMBR);
					if(nst.N>=nst.mN) nst.adm(ADD_GRP_NMBR);			
					SRol->N++;
					nst.x[nst.N]= 0;
					nst.N++;
					
					k	= nst.x[j];
					
					//SRol->x[j].Stbl->x[k].n_pnt1	= new ms1Dint [1];
					//SRol->x[j].Stbl->x[k].n_pnt2	= new ms1Dint [1];
					
					SRol->x[j].Stbl->x[k].d		= d;
					SRol->x[j].Stbl->x[k].nTw	= i;
					
					SRol->x[j].Stbl->x[k].isf	= true;
					
					SRol->x[j].Stbl->x[k].n_tr.x[0]	= -1;
					SRol->x[j].Stbl->x[k].n_tr.x[1]	= -1;
					SRol->x[j].Stbl->x[k].nc1		= 0.0;
					SRol->x[j].Stbl->x[k].nc2		= 0.0;
					SRol->x[j].Stbl->x[k].csa		= d/(p_rol+s_rol);
					
					// ����� ������������������
					SRol->x[j].Stbl->x[k].pc1	= Twos->x[i].rp-Twos->x[i].z*d;
					SRol->x[j].Stbl->x[k].pc2	= Twos->x[i].rp+Twos->x[i].z*d;
					SRol->x[j].Stbl->x[k].nst	= Twos->x[i].z;
					
					SRol->x[j].Stbl->N			= ++nst.x[j];
					
				}
			}
		}
	}
	for(i=0;i<nScStPr.N;i++) {nScStPr.x[i].sort();}
}

void MolData::SetScStbl(ms1D<int> &n_icg, ms1D<ms1Dint> &nScStPr)	// �������������������������
{
	int i,j,k,i0,i1,j0,j1;
	double b,d,s_rol;
	Vec3db p1,p2;
	int icg;

	ms1D<int> nst(n_icg.N);
	ms1D<int> its(n_icg.N);
	ms1D<int> itw(n_icg.N);
	ms1D<double> sr(n_icg.N);

	nst.one(n_icg.N);
	nst = 0;
	its	= -1;	

	for (j=0;j<n_icg.N;j++)
	{
		for(i=0;i<SRol->x[n_icg.x[j]].Stbl->N;i++)
		{
			itw.add(SRol->x[n_icg.x[j]].Stbl->x[i].nTw);
			sr.add(sro.x[n_icg.x[j]]);
		}
	}

	for (j=0;j<n_icg.N;j++)
	{
		icg	= n_icg.x[j];
		if (SRol->x[icg].Stbl->x[0].n_tr.x[0]==-1)
		{
			its.x[j]	= SRol->x[icg].Stbl->x[0].nTw;
		}
		for(i=0;i<SRol->x[icg].Stbl->N;i++)
		{
			SRol->x[icg].Stbl->x[i].csa			= 0;
			SRol->x[icg].Stbl->x[i].d			= 0;
			SRol->x[icg].Stbl->x[i].isf			= 0;
			SRol->x[icg].Stbl->x[i].n_pnt1->N	= 0;
			SRol->x[icg].Stbl->x[i].n_pnt2->N	= 0;
			SRol->x[icg].Stbl->x[i].n_tr		= -1;
			SRol->x[icg].Stbl->x[i].nc1			= 0;
			SRol->x[icg].Stbl->x[i].nc2			= 0;
			SRol->x[icg].Stbl->x[i].nst			= 0;
			SRol->x[icg].Stbl->x[i].nTw			= -1;
			SRol->x[icg].Stbl->x[i].pc1			= 0;
			SRol->x[icg].Stbl->x[i].pc2			= 0;
		}
		SRol->x[icg].Stbl->N	= 0;
	}	

	for(j0=0;j0<itw.N;j0++)
	{
		i	= itw.x[j0];
		if((Twos->x[i].ism)&&(Twos->x[i].hab.x[0]-p_rol<=sr.x[j0]))
		{
			//nst.N	= 0;			

			i0		= Twos->x[i].n_tr.x[0];
			i1		= Twos->x[i].n_tr.x[1];
			if (i0!=-1)
			{				
				if ((Tris->x[i0].igr!=-1)&&(Tris->x[i1].igr!=-1)&&(Tris->x[i0].igr==Tris->x[i1].igr))
				{
					j	= Tris->x[i0].igr;//
				}else
				{
					cout<<"Error 2 in 'MolData::SetScStbl(ms1D<int> &n_icg, ms1D<ms1Dint> &nScStPr)'"<<endl;
					exit(2);
				}
				
				// j - ������������
				j1	= n_icg.fnd(j);
				if(j1!=-1)
				{
					k	= nst.x[j1];

					s_rol	= sro.x[j];
					b	*=b = p_rol+s_rol;
					d		= sqrt(b-Twos->x[i].hab.x[0]*Twos->x[i].hab.x[0]);

					if(SRol->x[j].Stbl->N>=SRol->x[j].Stbl->mN) SRol->x[j].Stbl->adm_(ADD_SCTRS_NMBR);
					
					SRol->x[j].Stbl->x[k].d			= d;
					
					SRol->x[j].Stbl->x[k].nTw		= i;	// �������� �����������
					SRol->x[j].Stbl->x[k].n_tr.x[0]	= i0;	// ����������. ���
					SRol->x[j].Stbl->x[k].n_tr.x[1]	= i1;	// ����������. ���
					
					nScStPr.x[i0].add(k);
					nScStPr.x[i1].add(k);
					
					SRol->x[j].Stbl->x[k].isf	= true;
					
					// ����� ������������������
					SRol->x[j].Stbl->x[k].pc1	= Twos->x[i].rp-Twos->x[i].z*d;
					SRol->x[j].Stbl->x[k].pc2	= Twos->x[i].rp+Twos->x[i].z*d;
					SRol->x[j].Stbl->x[k].csa	= d/(p_rol+s_rol);
					SRol->x[j].Stbl->x[k].nst	= Twos->x[i].z;
					
					p1	= Tris->x[i0].pc-SRol->x[j].Stbl->x[k].pc1;
					p2	= Tris->x[i1].pc-SRol->x[j].Stbl->x[k].pc1;				
					SRol->x[j].Stbl->x[k].nc1.crss(p1,p2);
					SRol->x[j].Stbl->x[k].nc1.nrml();
					
					p1	= Tris->x[i0].pc-SRol->x[j].Stbl->x[k].pc2;
					p2	= Tris->x[i1].pc-SRol->x[j].Stbl->x[k].pc2;
					SRol->x[j].Stbl->x[k].nc2.crss(p2,p1);
					SRol->x[j].Stbl->x[k].nc2.nrml();
					
					SRol->x[j].Stbl->N			= ++nst.x[j1];
				}
			}else
			{
				k	= its.fnd(i);
				j	= n_icg.x[k];

				s_rol	= sro.x[j];
				b	*=b = p_rol+s_rol;

				SRol->x[j].Stbl->x[0].d		= d;
				SRol->x[j].Stbl->x[0].nTw	= i;

				SRol->x[j].Stbl->x[0].isf	= true;

				SRol->x[j].Stbl->x[0].n_tr.x[0]	= -1;
				SRol->x[j].Stbl->x[0].n_tr.x[1]	= -1;
				SRol->x[j].Stbl->x[0].nc1		= 0.0;
				SRol->x[j].Stbl->x[0].nc2		= 0.0;
				SRol->x[j].Stbl->x[0].csa		= d/(p_rol+s_rol);

				// ����� ������������������
				SRol->x[j].Stbl->x[0].pc1	= Twos->x[i].rp-Twos->x[i].z*d;
				SRol->x[j].Stbl->x[0].pc2	= Twos->x[i].rp+Twos->x[i].z*d;
				SRol->x[j].Stbl->x[0].nst	= Twos->x[i].z;

				SRol->x[j].Stbl->N			= 1;

			}

		}
	}
	for(i=0;i<nScStPr.N;i++) {nScStPr.x[i].sort();}
}

void MolData::SetScTwos(ms1D<ms1Dint> &nScTrPr, ms1D<ms1Dint> &nScStPr)	// определение тров вторичной обкатки
{
	int i,j,k,i0,i1,j0,j1,k0;
	int icg,itw;//,itr;
	
	bool ch;
	
	double a,b,c,d;
	double x_,y_,z_;
	
	Vec3db pm,p0,p1,p2,p3;
	Vec3db x,y,z;
	Vec3db dr;

	Vec3db ds1,ds2;
	
	ms1D<double> f_(6);

	ms1D<bool> alw;
	
	ms1D<int> ind(6),tind(6),type(6);
	
	ms1D<int> its_tr,its_st,its_tw,its_wt;
	
	ms1D<ms1Dint> nTr_un;
	ms1D<ms1Dint> nTr_ge;
	
	j=0;
	for(i=0;i<nScTrPr.N;i++)j	= j>nScTrPr.x[i].N ? j : nScTrPr.x[i].N;
	for(i=0;i<nScStPr.N;i++)j	= j>nScStPr.x[i].N ? j : nScStPr.x[i].N;
	
	its_tr.sm(j+5);
	its_st.sm(j+5);
	its_tw.sm(j+5);
	its_wt.sm(j+5);
	alw.sm(j+5);
	
	j	=0;
	for(icg	=0;icg<TrsCnfGrp.N;icg++) j	= TrsCnfGrp.x[icg].N>j ? TrsCnfGrp.x[icg].N : j;
	
	nTr_un.sm(j+5);
	nTr_ge.sm(j+5);

	InitObject(nTr_un);
	InitObject(nTr_ge);
	
	//for(i=0;i<SRol->N;i++) SRol->x[i].Twos	= new ms1D<ScTwPnt> [1];
	
	a	*= a	= p_rol+s_rol;
	
	for(icg	=0 ;icg<TrsCnfGrp.N;icg++)	// перебор всех конфликтных групп сфер. треугольников первичной обкатки
	{
		// оперделение соседей для каждого сфер. треугольника из текущей группы, а также соседей с превосходящими номерами.
		//nTr_un.N	= nTr_ge.N = 0;
		nTr_un.N	= nTr_ge.N = TrsCnfGrp.x[icg].N; // число конфликных сфер в текущей группе
		for(i=0;i<TrsCnfGrp.x[icg].N;i++)
		{
			j	= TrsCnfGrp.x[icg].x[i];	// номер текущей конфл. группы
			nTr_un.x[i].pst(TrsCnfGrp.x[icg]);	// в nTr_un - копируются текущие конфликнтые номера 
			k	= nTr_un.x[i].fnd(j);	// поиск позиции с текущим номером (j) кофликтного сферического треугольника
			if(k!=-1)	// был найден
			{
				nTr_un.x[i].rem(1,k);	// удалить текущий номер из списка конфликтных номеров
				nTr_ge.x[i].pst(0,k,nTr_un.x[i]);// в nTr_ge - вставить часть массива nTr_un от нулевой позиции до k-ой
			}	
			else	// не был найден -  ошибка 
			{
				cout<<"Error 1 in 'MolData::SetScTris(ms1D<ms1Dint> &nScTrPr)' "<<endl;
				exit(1);
			}
		}
		
		k	= 0;
		for(i0=0;i0<TrsCnfGrp.x[icg].N;i0++)	// перебор конфликнтых сфер текущей группы
		{
			j0	= TrsCnfGrp.x[icg].x[i0];		// номер текущего конфликтного сфер. треуголника
			for(i1=0;i1<nTr_ge.x[i0].N;i1++)	// перебор всех конфликных сфер с превосходящими номерами
			{
				j1	= nTr_ge.x[i0].x[i1];		// номер соседней конфликнтой сферы
				
				its_tr.N= its_st.N = 0;
				nScTrPr.x[j0].itss(nScTrPr.x[j1],its_tr);	// выделение общих сфер вторичной обкатки
				nScStPr.x[j0].itss(nScStPr.x[j1],its_st);	// выделение общих устойчивых свер вторичной обкатки 
				
				/*if(2*(its_tr.N>>1)!=its_tr.N)// число общих сфер вторичной обкатки должно быть чётным. 
				{
					cout<<"Error 6 in 'MolData::SetScTris(ms1D<ms1Dint> &nScTrPr)'  "<<endl;
					exit(6);
				}*/
				if(2*(its_tr.N>>1)==its_tr.N)// число общих сфер вторичной обкатки должно быть чётным. 
				{
					pm	= (Tris->x[j0].pc+Tris->x[j1].pc);	// середина отрезка соединяющего две текущеи сферы первичной обкатки
					pm	*=0.5;
					if(its_st.N!=0)		// �� �� ��� �� ��������
					{
						z	= Tris->x[j1].pc-pm;	// ��� ���� ���� 'pm' ���� � �. ���
						z.nrml(d);					// ����� ���� � �. ���� ���� 'pm'

						itw	= SRol->x[icg].Stbl->x[its_st.x[0]].nTw;	// ���� ��������������� ��� �� ��
						dr	= pm-Twos->x[itw].rp;						// ��� � ���� ���������������� 'pm'

						dr.nrml(c);
						b	*= b = Twos->x[itw].hab.x[0];
						c	= sqrt(a-b+c*c);				// ��� ����� ������������ ��� �� �. ���


						x_	= dr.scpr(Twos->x[itw].x);
						y_	= dr.scpr(Twos->x[itw].y);

						z_	= y_>0 ? x_+1: -x_-1;			// ������� ����dr ������ �����������

						x	= (Twos->x[itw].mx.x[0]>z_)||(Twos->x[itw].mx.x[1]<z_) ? -dr : dr; // � ������� 'x' ����� ����� ������ ��� �������

						y.crss(z,x);	// ���� ����� ����� ���

						f_.N	= 0;
						ind.N	= 0;
						tind.N	= 0;
						type.N	= 0;

						for(i=0;i<its_st.N;i++) // �� � �� �� ��� ��. ����
						{
							SRol->x[icg].Stbl->x[its_st.x[i]].isf	= false;	// 

							p0	= SRol->x[icg].Stbl->x[its_st.x[i]].pc1 - pm;	// ��� � ���� pm ����pc1 ��� �� �� ���
							p0.nrml();

							x_	= p0.scpr(x);
							y_	= p0.scpr(y);

							z_	= y_>0 ? x_+1 :-x_-1;		// ������.

							f_.add(z_);						// ���� ���� �������
							ind.add(its_st.x[i]);			// ���� ����� ���
							type.add(1);					// ���� ���� �������� ���.

							p0	= SRol->x[icg].Stbl->x[its_st.x[i]].pc2 - pm;// ��� � ���� pm ����pc2 ��� �� �� ���
							p0.nrml();

							x_	= p0.scpr(x);
							y_	= p0.scpr(y);

							z_	= y_>0 ? x_+1 :-x_-1;		// ������.

							f_.add(z_);						// ���� ���� �������
							ind.add(its_st.x[i]);			// ���� ����� ���
							type.add(2);					// ���� ���� �������� ���.
						}

						for(i=0;i<its_tr.N;i++)				//�� � �� �. ��� 
						{
							p0	= SRol->x[icg].Tris->x[its_tr.x[i]].pc-pm;
							p0.nrml();

							x_	= p0.scpr(x);
							y_	= p0.scpr(y);

							z_	= y_>0 ? x_+1 :-x_-1;	// ���������������� ����. ��������� ����� �� ��

							f_.add(z_);
							ind.add(its_tr.x[i]);
							type.add(0);
						}

						tind.one(f_.N);
						for(i=0;i<f_.N;tind.x[i++]=i);
						f_.sort_(tind);	//����� � �����. ��� ������ ������ �'tind'

						for(j=0;j<tind.N;j++)		// ������ �� �� ����������
						{
							i	= tind.x[j];	// ����� ���. ���

							if(SRol->x[icg].Twos->N>=SRol->x[icg].Twos->mN) SRol->x[icg].Twos->adm_(ADD_SCTWS_NMBR);

							// ����� ������ ��
							//SRol->x[icg].Twos->x[k].n_pnt	= new ms1Dint [1];

							SRol->x[icg].Twos->x[k].mx.x[0]	= f_.x[j];
							SRol->x[icg].Twos->x[k].mx.x[1]	= f_.x[j+1];

							SRol->x[icg].Twos->x[k].x		= x;
							SRol->x[icg].Twos->x[k].y		= y;
							SRol->x[icg].Twos->x[k].z		= z;

							SRol->x[icg].Twos->x[k].rp		= pm;

							SRol->x[icg].Twos->x[k].ismorpi	= ((f_.x[j+1]-f_.x[j])>2);

							SRol->x[icg].Twos->x[k].n_tr.x[0]	= j0;
							SRol->x[icg].Twos->x[k].n_tr.x[1]	= j1;

							SRol->x[icg].Twos->x[k].n_stb.x[0]	= ind.x[i];
							SRol->x[icg].Twos->x[k].type_.x[0]	= type.x[i];


							//---						
							SRol->x[icg].Twos->x[k].cs2	= c/(s_rol+p_rol);
							//---

							if(type.x[i]==0) SRol->x[icg].Tris->x[ind.x[i]].n_stw->add(k);

							j++;
							i	= tind.x[j];

							SRol->x[icg].Twos->x[k].n_stb.x[1]	= ind.x[i];
							SRol->x[icg].Twos->x[k].type_.x[1]	= type.x[i];

							SRol->x[icg].Twos->x[k].r_sc		= c;

							if(type.x[i]==0) SRol->x[icg].Tris->x[ind.x[i]].n_stw->add(k);

							SRol->x[icg].Twos->x[k].d			= d;

							k++;
							SRol->x[icg].Twos->N++;
						}
					}else
					{
						z	= Tris->x[j1].pc-pm;
						z.nrml(d);
						c	= d*d;
						if(a>c)
						{
							b	= sqrt(a-c);

							ch	= true;
							for(i=0;(i<TrsCnfGrp.x[icg].N&&ch);i++)
							{
								j	= TrsCnfGrp.x[icg].x[i];
								if((j!=j0)&&(j!=j1))
								{
									dr	= Tris->x[j].pc-pm;
									z_	= dr.scpr(z);
									x	= dr-z*z_;
									x.nrml();
									p0	= dr-x*b;

									ch	= p0.ssqr()>a;
								}
							}
							if(its_tr.N!=0)
							{
								if(ch)
								{
									cout<<"Error 3 in MolData::SetScTwos(ms1D<ms1Dint> &nScTrPr, ms1D<ms1Dint> &nScStPr) {secondary rolling}"<<endl;
									exit(3);
								}


								j	= SRol->x[icg].Tris->x[its_tr.x[0]].n_tr->fnd(j0,j1);
								j	= SRol->x[icg].Tris->x[its_tr.x[0]].n_tr->x[j];
								x	= Tris->x[j].pc-pm;
								z_	= x.scpr(z);
								x	-= z*z_;
								x.nrml();
								y.crss(z,x);

								f_.N	= 0;

								for(i=0;i<its_tr.N;i++)
								{
									p0	= SRol->x[icg].Tris->x[its_tr.x[i]].pc-pm;
									p0.nrml();

									x_	= p0.scpr(x);
									y_	= p0.scpr(y);

									z_	= y_>0 ? x_+1 : -x_-1;

									f_.add(z_);
								}
								tind.one(f_.N);
								for(i=0;i<f_.N;tind.x[i++]=i);
								f_.sort_(tind);	//����� � �����. ��� ������ ������ �'tind'

								j	= its_tr.x[tind.x[0]];
								its_tw.pst(*SRol->x[icg].Tris->x[j].n_tr);
								for(i=0;i<its_tr.N;i++)
								{
									j		= its_tr.x[tind.x[i]];
									its_tw.unis(*SRol->x[icg].Tris->x[j].n_tr,its_wt);
									its_tw	= its_wt;
								}
								j	= its_tw.fnd(j0);
								its_tw.rem(1,j);
								j	= its_tw.fnd(j1);
								its_tw.rem(1,j);
								its_wt.N	= 0;

								alw.N	= tind.N;
								alw		= true;
								for(i=0;i<its_tw.N;i++)
								{
									j	= its_tw.x[i];
									p0	= Tris->x[j].pc-pm;
									z_	= p0.scpr(z);
									p0	-= z*z_;
									p0.nrml();
									x_	= p0.scpr(x);
									y_	= p0.scpr(y);
									z_	= y_>=0 ? x_+1:-x_-1;
									for(k0=0;(k0<f_.N)&&(f_.x[k0]<z_);k0++);
									k0	= k0==f_.N ? 0 : k0;
									alw.x[k0]	= false;
								}


								for(i=0;i<tind.N;i++)
								{
									if (alw.x[i])
									{
										z_	= 0.5*(f_.x[i]+f_.x[i-1]);
										x_	= z_<0 ? -z_-1 : z_-1;
										y_	= z_<0 ? -sqrt(1-x_*x_) : sqrt(1-x_*x_);

										p0	= pm+(x*x_+y*y_)*b;

										if(Tris->x[j0].isTris(p0))
										{
											if(Tris->x[j1].isTris(p0))
											{
												if(SRol->x[icg].Twos->N>=SRol->x[icg].Twos->mN) SRol->x[icg].Twos->adm_(ADD_SCTWS_NMBR);

												j	= tind.x[i-1];

												//SRol->x[icg].Twos->x[k].n_pnt		= new ms1Dint [1];

												SRol->x[icg].Twos->x[k].mx.x[0]		= f_.x[i-1];
												SRol->x[icg].Twos->x[k].mx.x[1]		= f_.x[i];

												SRol->x[icg].Twos->x[k].x			= x;
												SRol->x[icg].Twos->x[k].y			= y;
												SRol->x[icg].Twos->x[k].z			= z;

												SRol->x[icg].Twos->x[k].rp			= pm;

												SRol->x[icg].Twos->x[k].ismorpi		= ((f_.x[i]-f_.x[i-1])>2);

												SRol->x[icg].Twos->x[k].n_tr.x[0]	= j0;
												SRol->x[icg].Twos->x[k].n_tr.x[1]	= j1;

												SRol->x[icg].Twos->x[k].n_stb.x[0]	= its_tr.x[j];
												SRol->x[icg].Twos->x[k].type_.x[0]	= 0;

												//---
												SRol->x[icg].Twos->x[k].cs2	= b/(s_rol+p_rol);
												//---


												SRol->x[icg].Tris->x[its_tr.x[j]].n_stw->add(k);

												j	= tind.x[i];

												SRol->x[icg].Twos->x[k].n_stb.x[1]	= its_tr.x[j];
												SRol->x[icg].Twos->x[k].type_.x[1]	= 0;

												SRol->x[icg].Tris->x[its_tr.x[j]].n_stw->add(k);

												SRol->x[icg].Twos->x[k].r_sc		= b;
												SRol->x[icg].Twos->x[k].d			= d;

												SRol->x[icg].Twos->N++;
												k++;
											}
										}
									}
								}
							}
							else
							{
								if((ch)&&(b>s_rol+d_min))
								{
									p1	= Tris->x[j0].pc;
									p2	= Tris->x[j1].pc;

									if(Tris->x[j0].isTris(p2))
									{
										if(Tris->x[j1].isTris(p1))
										{
											if(SRol->x[icg].Twos->N>=SRol->x[icg].Twos->mN) SRol->x[icg].Twos->adm_(ADD_SCTWS_NMBR);

											//SRol->x[icg].Twos->x[k].n_pnt		= new ms1Dint [1];

											SRol->x[icg].Twos->x[k].ismorpi		= true;

											SRol->x[icg].Twos->x[k].n_tr.x[0]	= j0;
											SRol->x[icg].Twos->x[k].n_tr.x[1]	= j1;

											SRol->x[icg].Twos->x[k].n_stb		= -1;
											SRol->x[icg].Twos->x[k].type_		= -1;

											SRol->x[icg].Twos->x[k].r_sc		= b;
											SRol->x[icg].Twos->x[k].d			= d;

											SRol->x[icg].Twos->x[k].mx.x[0]		= -2.01;
											SRol->x[icg].Twos->x[k].mx.x[1]		= 2.01;

											SRol->x[icg].Twos->x[k].rp			= pm;

											x		= 0.0;
											x.x[0]	= 1.0;

											b	= x.scpr(z);
											if ((b>0 ? b : -b)<0.9999)
											{
												x	-= z*b;
												x.nrml();
											}else
											{
												x		= 0.0;
												x.x[0]	= 1.0;
												b		= x.scpr(z);
												x		-= x*b;
												x.nrml();
											}
											y.crss(z,x);

											SRol->x[icg].Twos->x[k].x	= x;
											SRol->x[icg].Twos->x[k].y	= y;
											SRol->x[icg].Twos->x[k].z	= z;


											//---
											SRol->x[icg].Twos->x[k].cs2	= SRol->x[icg].Twos->x[k].r_sc/(p_rol+s_rol);
											//---


											SRol->x[icg].Twos->N++;
											k++;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
};

void MolData::SetScTwos(ms1D<int>&n_icg, ms1D<ms1Dint> &nScTrPr, ms1D<ms1Dint> &nScStPr)	// �������� ���������
{
	int i,j,k,i0,i1,j0,j1,k0;
	int icg,itw,ic;//,itr;
	
	bool ch;
	
	double a,b,c,d;
	double x_,y_,z_;
	double s_rol;
	
	Vec3db pm,p0,p1,p2,p3;
	Vec3db x,y,z;
	Vec3db dr;

	Vec3db ds1,ds2;
	
	ms1D<double> f_(6);

	ms1D<bool> alw;
	
	ms1D<int> ind(6),tind(6),type(6);
	
	ms1D<int> its_tr,its_st,its_tw,its_wt;
	
	ms1D<ms1Dint> nTr_un;
	ms1D<ms1Dint> nTr_ge;
	
	j=0;
	for(i=0;i<nScTrPr.N;i++)j	= j>nScTrPr.x[i].N ? j : nScTrPr.x[i].N;
	for(i=0;i<nScStPr.N;i++)j	= j>nScStPr.x[i].N ? j : nScStPr.x[i].N;
	
	its_tr.sm(j+5);
	its_st.sm(j+5);
	its_tw.sm(j+5);
	its_wt.sm(j+5);
	alw.sm(j+5);
	
	j	=0;
	for(icg	=0;icg<TrsCnfGrp.N;icg++) j	= TrsCnfGrp.x[icg].N>j ? TrsCnfGrp.x[icg].N : j;
	
	nTr_un.sm(j+5);
	nTr_ge.sm(j+5);

	InitObject(nTr_un);
	InitObject(nTr_ge);
	
	
	for(ic=0;ic<n_icg.N;ic++)
	{		
		icg	= n_icg.x[ic];
		s_rol		= sro.x[icg];
		a	*= a	= p_rol+s_rol;

		for(i=0;i<SRol->x[icg].Twos->N;i++)
		{
			SRol->x[icg].Twos->x[i].d		= 0;
			SRol->x[icg].Twos->x[i].ismorpi	= 0;
			SRol->x[icg].Twos->x[i].mx		= 0;
			SRol->x[icg].Twos->x[i].n_pnt->N= 0;
			SRol->x[icg].Twos->x[i].n_stb	= -1;
			SRol->x[icg].Twos->x[i].n_tr	= -1;
			SRol->x[icg].Twos->x[i].r_sc	= 0;
			SRol->x[icg].Twos->x[i].rp		= 0;
			SRol->x[icg].Twos->x[i].type_	= -1;
			SRol->x[icg].Twos->x[i].x		= 0;
			SRol->x[icg].Twos->x[i].y		= 0;
			SRol->x[icg].Twos->x[i].z		= 0;
		}
		SRol->x[icg].Twos->N	= 0;

		// ����������� ��� �. ���� ��� ���, ��������������������.
		nTr_un.N	= nTr_ge.N = 0;
		if (icg<TrsCnfGrp.N)
		{
			nTr_un.N	= nTr_ge.N = TrsCnfGrp.x[icg].N;
			for(i=0;i<TrsCnfGrp.x[icg].N;i++)
			{
				
				j	= TrsCnfGrp.x[icg].x[i];
				nTr_un.x[i].pst(TrsCnfGrp.x[icg]);
				k	= nTr_un.x[i].fnd(j);
				if(k!=-1)
				{
					nTr_un.x[i].rem(1,k);
					nTr_ge.x[i].pst(0,k,nTr_un.x[i]);
				}
				else
				{
					cout<<"Error 1 in 'MolData::SetScTris(ms1D<ms1Dint> &nScTrPr)' "<<endl;
					exit(1);
				}
			}
			
			k	= 0;
			for(i0=0;i0<TrsCnfGrp.x[icg].N;i0++)	// �����. ���� ������������
			{
				j0	= TrsCnfGrp.x[icg].x[i0];		// �������. ���
				for(i1=0;i1<nTr_ge.x[i0].N;i1++)	// ������ ���� � ���������� ����
				{
					j1	= nTr_ge.x[i0].x[i1];		// ������� �. ���
					
					its_tr.N= its_st.N = 0;
					nScTrPr.x[j0].itss(nScTrPr.x[j1],its_tr);	// ������� �. �����. ����
					nScStPr.x[j0].itss(nScStPr.x[j1],its_st);	// ������� �� �����. ����
					
					/*if(2*(its_tr.N>>1)!=its_tr.N) 
					{					
						cout<<"Error 6 in 'MolData::SetScTris(ms1D<ms1Dint> &nScTrPr)'  "<<endl;
						exit(6);
					}*/
					
					if(2*(its_tr.N>>1)==its_tr.N)
					{
						pm	= (Tris->x[j0].pc+Tris->x[j1].pc);	// ���������� �������������� �. ���
						pm	*=0.5;
						if(its_st.N!=0)		// �� �� ��� �� ��������
						{
							z	= Tris->x[j1].pc-pm;	// ��� ���� ���� 'pm' ���� � �. ���
							z.nrml(d);					// ����� ���� � �. ���� ���� 'pm'

							itw	= SRol->x[icg].Stbl->x[its_st.x[0]].nTw;	// ���� ��������������� ��� �� ��
							dr	= pm-Twos->x[itw].rp;						// ��� � ���� ���������������� 'pm'

							dr.nrml(c);
							b	*= b = Twos->x[itw].hab.x[0];
							c	= sqrt(a-b+c*c);				// ��� ����� ������������ ��� �� �. ���


							x_	= dr.scpr(Twos->x[itw].x);
							y_	= dr.scpr(Twos->x[itw].y);

							z_	= y_>0 ? x_+1: -x_-1;			// ������� ����dr ������ �����������

							x	= (Twos->x[itw].mx.x[0]>z_)||(Twos->x[itw].mx.x[1]<z_) ? -dr : dr; // � ������� 'x' ����� ����� ������ ��� �������

							y.crss(z,x);	// ���� ����� ����� ���

							f_.N	= 0;
							ind.N	= 0;
							tind.N	= 0;
							type.N	= 0;

							for(i=0;i<its_st.N;i++) // �� � �� �� ��� ��. ����
							{
								SRol->x[icg].Stbl->x[its_st.x[i]].isf	= false;	// 

								p0	= SRol->x[icg].Stbl->x[its_st.x[i]].pc1 - pm;	// ��� � ���� pm ����pc1 ��� �� �� ���
								p0.nrml();

								x_	= p0.scpr(x);
								y_	= p0.scpr(y);

								z_	= y_>0 ? x_+1 :-x_-1;		// ������.

								f_.add(z_);						// ���� ���� �������
								ind.add(its_st.x[i]);			// ���� ����� ���
								type.add(1);					// ���� ���� �������� ���.

								p0	= SRol->x[icg].Stbl->x[its_st.x[i]].pc2 - pm;// ��� � ���� pm ����pc2 ��� �� �� ���
								p0.nrml();

								x_	= p0.scpr(x);
								y_	= p0.scpr(y);

								z_	= y_>0 ? x_+1 :-x_-1;		// ������.

								f_.add(z_);						// ���� ���� �������
								ind.add(its_st.x[i]);			// ���� ����� ���
								type.add(2);					// ���� ���� �������� ���.
							}

							for(i=0;i<its_tr.N;i++)				//�� � �� �. ��� 
							{
								p0	= SRol->x[icg].Tris->x[its_tr.x[i]].pc-pm;
								p0.nrml();

								x_	= p0.scpr(x);
								y_	= p0.scpr(y);

								z_	= y_>0 ? x_+1 :-x_-1;	// ���������������� ����. ��������� ����� �� ��

								f_.add(z_);
								ind.add(its_tr.x[i]);
								type.add(0);
							}

							tind.one(f_.N);
							for(i=0;i<f_.N;tind.x[i++]=i);
							f_.sort_(tind);	//����� � �����. ��� ������ ������ �'tind'

							for(j=0;j<tind.N;j++)		// ������ �� �� ����������
							{
								i	= tind.x[j];	// ����� ���. ���

								if(SRol->x[icg].Twos->N>=SRol->x[icg].Twos->mN) SRol->x[icg].Twos->adm_(ADD_SCTWS_NMBR);

								// ����� ������ ��
								SRol->x[icg].Twos->x[k].mx.x[0]	= f_.x[j];
								SRol->x[icg].Twos->x[k].mx.x[1]	= f_.x[j+1];

								SRol->x[icg].Twos->x[k].x		= x;
								SRol->x[icg].Twos->x[k].y		= y;
								SRol->x[icg].Twos->x[k].z		= z;

								SRol->x[icg].Twos->x[k].rp		= pm;

								SRol->x[icg].Twos->x[k].ismorpi	= ((f_.x[j+1]-f_.x[j])>2);

								SRol->x[icg].Twos->x[k].n_tr.x[0]	= j0;
								SRol->x[icg].Twos->x[k].n_tr.x[1]	= j1;

								SRol->x[icg].Twos->x[k].n_stb.x[0]	= ind.x[i];
								SRol->x[icg].Twos->x[k].type_.x[0]	= type.x[i];

								//---
								SRol->x[icg].Twos->x[k].cs2	= c/(p_rol+s_rol);
								//---

								if(type.x[i]==0) SRol->x[icg].Tris->x[ind.x[i]].n_stw->add(k);

								j++;
								i	= tind.x[j];

								SRol->x[icg].Twos->x[k].n_stb.x[1]	= ind.x[i];
								SRol->x[icg].Twos->x[k].type_.x[1]	= type.x[i];

								SRol->x[icg].Twos->x[k].r_sc		= c;

								if(type.x[i]==0) SRol->x[icg].Tris->x[ind.x[i]].n_stw->add(k);

								SRol->x[icg].Twos->x[k].d			= d;

								k++;
								SRol->x[icg].Twos->N++;
							}
						}else
						{
							z	= Tris->x[j1].pc-pm;
							z.nrml(d);
							c	= d*d;
							if(a>c)
							{
								b	= sqrt(a-c);

								ch	= true;
								for(i=0;(i<TrsCnfGrp.x[icg].N&&ch);i++)
								{
									j	= TrsCnfGrp.x[icg].x[i];
									if((j!=j0)&&(j!=j1))
									{
										dr	= Tris->x[j].pc-pm;
										z_	= dr.scpr(z);
										x	= dr-z*z_;
										x.nrml();
										p0	= dr-x*b;

										ch	= p0.ssqr()>a;
									}
								}
								if(its_tr.N!=0)
								{
									if(ch)
									{
										cout<<"Error 3 in MolData::SetScTwos(ms1D<ms1Dint> &nScTrPr, ms1D<ms1Dint> &nScStPr) {secondary rolling}"<<endl;
										exit(3);
									}


									j	= SRol->x[icg].Tris->x[its_tr.x[0]].n_tr->fnd(j0,j1);
									j	= SRol->x[icg].Tris->x[its_tr.x[0]].n_tr->x[j];
									x	= Tris->x[j].pc-pm;
									z_	= x.scpr(z);
									x	-= z*z_;
									x.nrml();
									y.crss(z,x);

									f_.N	= 0;

									for(i=0;i<its_tr.N;i++)
									{
										p0	= SRol->x[icg].Tris->x[its_tr.x[i]].pc-pm;
										p0.nrml();

										x_	= p0.scpr(x);
										y_	= p0.scpr(y);

										z_	= y_>0 ? x_+1 : -x_-1;

										f_.add(z_);
									}
									tind.one(f_.N);
									for(i=0;i<f_.N;tind.x[i++]=i);
									f_.sort_(tind);	//����� � �����. ��� ������ ������ �'tind'

									j	= its_tr.x[tind.x[0]];
									its_tw.pst(*SRol->x[icg].Tris->x[j].n_tr);
									for(i=0;i<its_tr.N;i++)
									{
										j		= its_tr.x[tind.x[i]];
										its_tw.unis(*SRol->x[icg].Tris->x[j].n_tr,its_wt);
										its_tw	= its_wt;
									}
									j	= its_tw.fnd(j0);
									its_tw.rem(1,j);
									j	= its_tw.fnd(j1);
									its_tw.rem(1,j);
									its_wt.N	= 0;

									alw.N	= tind.N;
									alw		= true;
									for(i=0;i<its_tw.N;i++)
									{
										j	= its_tw.x[i];
										p0	= Tris->x[j].pc-pm;
										z_	= p0.scpr(z);
										p0	-= z*z_;
										p0.nrml();
										x_	= p0.scpr(x);
										y_	= p0.scpr(y);
										z_	= y_>=0 ? x_+1:-x_-1;
										for(k0=0;(k0<f_.N)&&(f_.x[k0]<z_);k0++);
										k0	= k0==f_.N ? 0 : k0;
										alw.x[k0]	= false;
									}


									for(i=0;i<tind.N;i++)
									{
										if (alw.x[i])
										{
											z_	= 0.5*(f_.x[i]+f_.x[i-1]);
											x_	= z_<0 ? -z_-1 : z_-1;
											y_	= z_<0 ? -sqrt(1-x_*x_) : sqrt(1-x_*x_);

											p0	= pm+(x*x_+y*y_)*b;

											if(Tris->x[j0].isTris(p0))
											{
												if(Tris->x[j1].isTris(p0))
												{
													if(SRol->x[icg].Twos->N>=SRol->x[icg].Twos->mN) SRol->x[icg].Twos->adm_(ADD_SCTWS_NMBR);

													j	= tind.x[i-1];

													SRol->x[icg].Twos->x[k].mx.x[0]		= f_.x[i-1];
													SRol->x[icg].Twos->x[k].mx.x[1]		= f_.x[i];

													SRol->x[icg].Twos->x[k].x			= x;
													SRol->x[icg].Twos->x[k].y			= y;
													SRol->x[icg].Twos->x[k].z			= z;

													SRol->x[icg].Twos->x[k].rp			= pm;

													SRol->x[icg].Twos->x[k].ismorpi		= ((f_.x[i]-f_.x[i-1])>2);

													SRol->x[icg].Twos->x[k].n_tr.x[0]	= j0;
													SRol->x[icg].Twos->x[k].n_tr.x[1]	= j1;

													SRol->x[icg].Twos->x[k].n_stb.x[0]	= its_tr.x[j];
													SRol->x[icg].Twos->x[k].type_.x[0]	= 0;

													//---
													SRol->x[icg].Twos->x[k].cs2	= b/(p_rol+s_rol);
													//---


													SRol->x[icg].Tris->x[its_tr.x[j]].n_stw->add(k);

													j	= tind.x[i];

													SRol->x[icg].Twos->x[k].n_stb.x[1]	= its_tr.x[j];
													SRol->x[icg].Twos->x[k].type_.x[1]	= 0;

													SRol->x[icg].Tris->x[its_tr.x[j]].n_stw->add(k);

													SRol->x[icg].Twos->x[k].r_sc		= b;
													SRol->x[icg].Twos->x[k].d			= d;

													SRol->x[icg].Twos->N++;
													k++;
												}
											}
										}
									}
								}
								else
								{
									if((ch)&&(b>s_rol+d_min))
									{
										p1	= Tris->x[j0].pc;
										p2	= Tris->x[j1].pc;

										if(Tris->x[j0].isTris(p2))
										{
											if(Tris->x[j1].isTris(p1))
											{
												if(SRol->x[icg].Twos->N>=SRol->x[icg].Twos->mN) SRol->x[icg].Twos->adm_(ADD_SCTWS_NMBR);

												SRol->x[icg].Twos->x[k].ismorpi		= true;

												SRol->x[icg].Twos->x[k].n_tr.x[0]	= j0;
												SRol->x[icg].Twos->x[k].n_tr.x[1]	= j1;

												SRol->x[icg].Twos->x[k].n_stb		= -1;
												SRol->x[icg].Twos->x[k].type_		= -1;

												SRol->x[icg].Twos->x[k].r_sc		= b;
												SRol->x[icg].Twos->x[k].d			= d;

												SRol->x[icg].Twos->x[k].mx.x[0]		= -2.01;
												SRol->x[icg].Twos->x[k].mx.x[1]		= 2.01;

												SRol->x[icg].Twos->x[k].rp			= pm;

												x		= 0.0;
												x.x[0]	= 1.0;

												b	= x.scpr(z);
												if ((b>0 ? b : -b)<0.9999)
												{
													x	-= z*b;
													x.nrml();
												}else
												{
													x		= 0.0;
													x.x[0]	= 1.0;
													b		= x.scpr(z);
													x		-= x*b;
													x.nrml();
												}
												y.crss(z,x);

												SRol->x[icg].Twos->x[k].x	= x;
												SRol->x[icg].Twos->x[k].y	= y;
												SRol->x[icg].Twos->x[k].z	= z;

												//---
												SRol->x[icg].Twos->x[k].cs2	= SRol->x[icg].Twos->x[k].r_sc/(p_rol+s_rol);
												//---

												SRol->x[icg].Twos->N++;
												k++;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
};


void MolData::ScRlAnlze(ms1D<int> &SecCnfGrp)	// ��� ����� ��������� ����������������.
{
	int i,j,k;
	int icg,c_icg;

	double a,b,c,d;

	bool ch,ch1;

	Vec3db dp;

	
	ms1D<double> cnfdst(SRol->N);
	ms1D<double> sq_dst(SRol->N);

	b	*= b = a = s_rol+d_min;

	sro.one(SRol->N);
	sro	= s_rol;

	SecCnfGrp.N =0;
	for(icg=0;icg<SRol->N;icg++)
	{
		ch	 = true;
		for(i=0;(i<SRol->x[icg].Stbl->N)&&ch;i++)
		{
			if (SRol->x[icg].Stbl->x[i].d<a)
			{
				if(SRol->x[icg].Stbl->x[i].n_tr.x[0]==-1)
				{
					SecCnfGrp.add(icg);
					ch	 = false;
				}else
				{
					c	= SRol->x[icg].Stbl->x[i].nc1.scpr(SRol->x[icg].Stbl->x[i].nst);
					if(c>0)
					{
						SecCnfGrp.add(icg);
						ch	 = false;
					}
				}
				
			}
		}
		if (ch)
		{
			for(i=0;(i<SRol->x[icg].Twos->N)&&ch;i++)
			{
				if(SRol->x[icg].Twos->x[i].r_sc<a)
				{
					SecCnfGrp.add(icg);
					ch	 = false;
				}
			}
		}
		if(ch)
		{
			for(i=0;i<SRol->x[icg].Tris->N-1&&ch;i++)
			{
				for(j=i+1;j<SRol->x[icg].Tris->N&&ch;j++)
				{
					dp	= SRol->x[icg].Tris->x[j].pc-SRol->x[icg].Tris->x[i].pc;
					c	= 0.25*dp.ssqr();
					if(c<b)
					{
						d	= sqrt(1-c/b);
						dp.nrml();
						ch1	= true;
						for(k=0;k<SRol->x[icg].Tris->x[i].mx->N&&ch1;k++)
						{
							ch1	= dp.scpr(SRol->x[icg].Tris->x[i].mx->x[k])>d;
						}
						if(ch1)
						{
							dp	*= -1.0;
							for(k=0;k<SRol->x[icg].Tris->x[j].mx->N&&ch1;k++)
							{
								ch1	= dp.scpr(SRol->x[icg].Tris->x[j].mx->x[k])>d;
							}
							if(ch1)
							{
								SecCnfGrp.add(icg);
								ch	 = false;
							}
						}
					}
				}
			}
		}
	}

	for(c_icg=0;c_icg<SecCnfGrp.N;c_icg++)
	{
		icg	= SecCnfGrp.x[c_icg];
		cnfdst.N	= 0;
		for(i=0;i<SRol->x[icg].Twos->N;i++)
		{
			if(SRol->x[icg].Twos->x[i].d>p_rol)
			{
				cnfdst.add(SRol->x[icg].Twos->x[i].d);
			}
		}
		for(i=0;i<SRol->x[icg].Stbl->N;i++)
		{
			d	= Twos->x[SRol->x[icg].Stbl->x[i].nTw].hab.x[0];
			if(d>p_rol)
			{
				cnfdst.add(d);
			}
		}
		for(i=0;i<SRol->x[icg].Tris->N;i++)
		{
			d	= SRol->x[icg].Tris->x[i].nr.ssqr();
			d	= (p_rol+s_rol)*(p_rol+s_rol)-d;
			if(d>p_rol*p_rol)
			{
				cnfdst.add(sqrt(d));
			}
		}

		cnfdst.sort();
		sq_dst.N	= 0;
		sq_dst.add(cnfdst.x[0]);
		for(i=1;i<cnfdst.N;i++)
		{
			if(cnfdst.x[i]!=cnfdst.x[i-1]) sq_dst.add(cnfdst.x[i]);
		}
		cnfdst.pst(sq_dst);
		sq_dst	*= sq_dst;

		a	*= a =p_rol+d_min;
		c	= p_rol-d_min;

		for(i=cnfdst.N-1;i>0;i--)		//  �� � �� �������������� ���� ����
		{
			b	= c*(2*cnfdst.x[i]-c);	// � �� ��. �� ��. ��� �������������. ������� �� ��. ���p_rol
			if(b>sq_dst.x[i-1])			// ������������������������ ��� � 
			{
				sro.x[icg]	= cnfdst.x[i]-p_rol-1e-14;	// ����� ������ ����� ��� ���������
				break;
			}
		}
		if((i==0)||(sro.x[icg]<d_min))	// �� ������ ������� � ��
		{
			b	= c*(2*cnfdst.x[0]-c);	// ���� ��. ������ s_rol ����. ���� cnfdst.x[0]
			if(b>a)						// �� �������������������������, �
			{
				sro.x[icg]	= cnfdst.x[i]-p_rol-1e-14;	// ����� ������ ��. ����� �� ��� ���
			}else
			{
				b	= c*(3*d_min+p_rol);	// ���� ��. ������ s_rol==d_min
				for(i=0;(i<cnfdst.N)&&(sq_dst.x[i]<b);i++);		// ���� ��� b - ��-� ��� ���������?
				if((cnfdst.x[i]>(p_rol+d_min))||(i==cnfdst.N))	// �� ��� ���� ��� ��b �� ���� ���������
				{
					sro.x[icg]	= d_min-1e-14;	// ����� ������ ��. ����� �� ��� ��� ���d_min
				}else
				{
					cout<<"Can`t find the nonconflict value for the radius of the secondary rolling over "<<endl;
					cout<<"the "<< icg <<"`s  conflict group of the primary rolling!"<<endl;
					k	= cnfdst.N;
					d	= (p_rol+s_rol)*(p_rol+s_rol)-sq_dst.x[k-1];	// ��� ��� �� ������������. ���� ��� ���������
					for(i=cnfdst.N-1;i>0;i--)
					{
						if(sq_dst.x[i]>a)
						{
							b	= sq_dst.x[i]-sq_dst.x[i-1];	// ����� ������� �� ������s_rol = cnfdst.x[i] ������ ����� sq_dst.x[i-1]
							if(d<b)	// �������������
							{
								d	= b;
								k	= i;
							}
						}
					}
					b	= k==cnfdst.N ? s_rol : cnfdst.x[k]-p_rol;	// ���� ��������
					d	= sqrt(d)-b;	//	��� ����� ����������. ������� ���� ��. 
					cout<<"The new value of secondary rolling radius : "<<b<<endl;
					cout<<"Distortioned trajectory radius is : "<<d <<" instead given "<<d_min<<endl;
					sro.x[icg]	= b-1e-4;
					SRol->x[icg].s_rol = sro.x[icg];
					//CnTr2File(icg);
					//ScTr2File(icg);
					//ScSt2File(icg);
				}
			}
		}
	}
	for(i=0;i<SRol->N;i++)SRol->x[i].s_rol	= sro.x[i];
}

void MolData::SetTwsCnf()	// �������������
{
	int i,j1,j2;
	for(i=0;i<Twos->N;i++)
	{
		j1	= Twos->x[i].n_tr.x[0];
		j2	= Twos->x[i].n_tr.x[1];
		if((j1!=-1)&&(j2!=-1))
		{
			j1	= Tris->x[j1].igr;
			j2	= Tris->x[j2].igr;
			if((j1!=-1)&&(j2!=-1)&&(j1==j2)) Twos->x[i].igr	= j1;
		}
	}
	for(i=0;i<SRol->N;i++)
	{
		if ((SRol->x[i].Stbl->N==1)&&(SRol->x[i].Tris->N==0)&&(SRol->x[i].Twos->N==0))
		{
			j1	= SRol->x[i].Stbl->x[0].nTw;
			Twos->x[j1].igr	= i;
		}
	}
}

void MolData::ConflFree(ms1D<int> &n_icg, ms1D<ms1Dint> &nScTrPr, ms1D<ms1Dint> &nScStPr) //��� � �������� ��� � ���������
{
	int i,j;
	int icg,ic;

	for(ic=0;ic<n_icg.N;ic++)
	{
		icg	= n_icg.x[ic];
		if (icg<TrsCnfGrp.N)
		{
			for(i=0;i<TrsCnfGrp.x[icg].N;i++)
			{
				j	= TrsCnfGrp.x[icg].x[i];
				nScTrPr.x[j].N	= 0;
				nScStPr.x[j].N	= 0;
			}
		}
	}
}

void MolData::Atom2File()
{
	int j;

	fstream sss;

	sss.open("Atoms.vrml",ios::out);
	sss.precision(17);
	sss<<"#VRML V2.0 utf8"<<'\n';
	sss<<"WorldInfo { info  [\"Surface\"]}"<<'\n';
	sss<<"Background{ skyColor 0 0 0}"<<'\n';

	for(j=0;j<Atom.N;j++)
	{
		
		sss<<"Transform {translation "<<Atom.x[j].xyz;
		//sss<<"children[ Sphere {radius  "<< Atom.x[j].r_wdw<<" }]}"<<endl;

		sss<<"scale "<<Atom.x[j].r_wdw<<" "<<Atom.x[j].r_wdw<<" "<<Atom.x[j].r_wdw<<endl;
		//sss<<"children[Sphere ]}"<<endl;				

		sss<<"children[Inline {url[\"sphere.vrml\"]}]}"<<endl;				
	}
	sss.close();
}

void MolData::Atom2File(int k)
{
	int j,j1;

	fstream sss;

	sss.open("Atoms.vrml",ios::out);
	sss.precision(17);
	sss<<"#VRML V2.0 utf8"<<'\n';
	sss<<"WorldInfo { info  [\"Surface\"]}"<<'\n';
	sss<<"Background{ skyColor 0 0 0}"<<'\n';

	for(j1=0;j1<AtmCnnNmb.x[k].N;j1++)
	{		
		j	= AtmCnnNmb.x[k].x[j1];	
		sss<<"Transform {translation "<<Atom.x[j].xyz;
		//sss<<"children[ Sphere {radius  "<< Atom.x[j].r_wdw<<" }]}"<<endl;

		sss<<"scale "<<Atom.x[j].r_wdw<<" "<<Atom.x[j].r_wdw<<" "<<Atom.x[j].r_wdw<<endl;
		//sss<<"children[Sphere ]}"<<endl;				

		sss<<"children[Inline {url[\"sphere.vrml\"]}]}"<<endl;				
	}
	sss.close();
}

void MolData::Atom2File(ms1Dint &ind)
{
	int j,j1;

	fstream sss;

	sss.open("Atoms.vrml",ios::out);
	sss.precision(17);
	sss<<"#VRML V2.0 utf8"<<'\n';
	sss<<"WorldInfo { info  [\"Surface\"]}"<<'\n';
	sss<<"Background{ skyColor 0 0 0}"<<'\n';

	for(j1=0;j1<ind.N;j1++)
	{		
		j	= ind.x[j1];	
		sss<<"Transform {translation "<<Atom.x[j].xyz;
		//sss<<"children[ Sphere {radius  "<< Atom.x[j].r_wdw<<" }]}"<<endl;

		sss<<"scale "<<Atom.x[j].r_wdw<<" "<<Atom.x[j].r_wdw<<" "<<Atom.x[j].r_wdw<<endl;
		//sss<<"children[Sphere ]}"<<endl;				

		sss<<"children[Inline {url[\"sphere_b.vrml\"]}]}"<<endl;				
	}
	sss.close();
}

void MolData::CnTr2File(int k)	// ��� �vrml �� ����������. ��� ���������
{
	int j;

	fstream sss;

	sss.open("Tris.vrml",ios::out);
	sss.precision(17);
	sss<<"#VRML V2.0 utf8"<<'\n';
	sss<<"WorldInfo { info  [\"Surface\"]}"<<'\n';
	sss<<"Background{ skyColor 0 0 0}"<<'\n';

	for(j=0;j<Tris->N;j++)
	{
		if(Tris->x[j].igr==k)
		{
			sss<<"Transform {translation "<<Tris->x[j].pc;
			sss<<"scale "<<p_rol<<" "<<p_rol<<" "<<p_rol<<endl;
			sss<<"children[Inline {url[\"sphere.vrml\"]}]}"<<endl;				
		}
	}
	sss.close();

}


void MolData::Tris2File(int k)			// ��� �vrml �� �����. ��� ���������
{
	int j;

	fstream sss;

	sss.open("Tris.vrml",ios::out);
	sss.precision(17);
	sss<<"#VRML V2.0 utf8"<<'\n';
	sss<<"WorldInfo { info  [\"Surface\"]}"<<'\n';
	sss<<"Background{ skyColor 0 0 0}"<<'\n';

	for(j=0;j<Tris->N;j++)
	{
		if(Tris->x[j].igr==k)
		{
			sss<<"Transform {translation "<<Tris->x[j].pc;
			sss<<"scale "<<p_rol<<" "<<p_rol<<" "<<p_rol<<endl;
			sss<<"children[Inline {url[\"sphere.vrml\"]}]}"<<endl;				
		}
	}
	sss.close();


}

void MolData::ScTr2File(int k)	// ��� �vrml �� ����� ��� ���������
{
	int i,j,i1;	

	fstream sss;

	sss.open("SecTris.vrml",ios::out);
	sss.precision(17);
	sss<<"#VRML V2.0 utf8"<<'\n';
	sss<<"WorldInfo { info  [\"Surface\"]}"<<'\n';
	sss<<"Background{ skyColor 0 0 0}"<<'\n';
	
	if (k==-1)
	{
		for(i=0;i<SRol->N;i++)
		{
			for(j=0;j<SRol->x[i].Tris->N;j++)
			{
				sss<<"Transform {translation "<<SRol->x[i].Tris->x[j].pc;
				sss<<"scale "<<SRol->x[i].s_rol<<" "<<SRol->x[i].s_rol<<" "<<SRol->x[i].s_rol<<endl;
				sss<<"children[Inline {url[\"sphere_r.vrml\"]}]}"<<endl;				


				for(i1=0;i1<SRol->x[i].Tris->x[j].mx->N;i1++)
				{
					sss<<"Transform {translation "<<SRol->x[i].Tris->x[j].pc;
					sss<<"scale "<<SRol->x[i].Tris->x[j].mx->x[i1];
					sss<<"children[Inline {url[\"line.vrml\"]}]}";
				}

				/*
					Group{children[
					Shape	{appearance Appearance	{material Material {diffuseColor 0 1 1	}}	geometry IndexedFaceSet{
					solid FALSE
					coord Coordinate {point [
					0.391366150008174 -0.140986708622242 -7.09884112605941

					]	}coordIndex [                                         
					0 1 2 -1       0 3 1 -1       1 4 2 -1       2 5 0 -1   
					]                                                     
					} }                                                           
					]}                                                           


				*/
			}
			sss<<endl;
		}
	}else
	{
		k	= k<SRol->N? k : 0;
		for(j=0;j<SRol->x[k].Tris->N;j++)
		{
			sss<<"Transform {translation "<<SRol->x[k].Tris->x[j].pc;
			sss<<"scale "<<SRol->x[k].s_rol<<" "<<SRol->x[k].s_rol<<" "<<SRol->x[k].s_rol<<endl;
			sss<<"children[Inline {url[\"sphere_r.vrml\"]}]}"<<endl;
			for(i=0;i<SRol->x[k].Tris->x[j].mx->N;i++)
			{
				sss<<"Transform {translation "<<SRol->x[k].Tris->x[j].pc;
				sss<<"scale "<<SRol->x[k].Tris->x[j].mx->x[i];
				sss<<"children[Inline {url[\"line.vrml\"]}]}";
			}
		}
		sss<<endl;
	}

	sss.close();
}

void MolData::ScSt2File(int k)	// ��� �vrml �� ����� ��� ���������
{
	int i,j;
	double s_rol;

	fstream sss;

	sss.open("SecStbl.vrml",ios::out);
	sss.precision(17);
	sss<<"#VRML V2.0 utf8"<<'\n';
	sss<<"WorldInfo { info  [\"Surface\"]}"<<'\n';
	sss<<"Background{ skyColor 0 0 0}"<<'\n';
	
	if (k ==-1)
	{
		for(i=0;i<SRol->N;i++)
		{
			s_rol	= sro.x[i];
			for(j=0;j<SRol->x[i].Stbl->N;j++)
			{
				sss<<"Transform {translation "<<SRol->x[i].Stbl->x[j].pc1;
				sss<<"scale "<<SRol->x[i].s_rol<<" "<<SRol->x[i].s_rol<<" "<<SRol->x[i].s_rol<<endl;
				sss<<"children[Inline {url[\"sphere_g.vrml\"]}]}";
				sss<<"Transform {translation "<<SRol->x[i].Stbl->x[j].pc2;
				sss<<"scale "<<SRol->x[i].s_rol<<" "<<SRol->x[i].s_rol<<" "<<SRol->x[i].s_rol<<endl;
				sss<<"children[Inline {url[\"sphere_b.vrml\"]}]}"<<endl;
				
				sss<<"Transform {translation "<<SRol->x[i].Stbl->x[j].pc1;
				sss<<"scale "<<SRol->x[i].Stbl->x[j].nst;
				sss<<"children[Inline {url[\"line.vrml\"]}]}";
				sss<<"Transform {translation "<<SRol->x[i].Stbl->x[j].pc1;
				sss<<"scale "<<SRol->x[i].Stbl->x[j].nc1;
				sss<<"children[Inline {url[\"line_g.vrml\"]}]}";
				sss<<"Transform {translation "<<SRol->x[i].Stbl->x[j].pc2;
				sss<<"scale "<<SRol->x[i].s_rol<<" "<<SRol->x[i].s_rol<<" "<<SRol->x[i].s_rol<<endl;
				sss<<"children[Inline {url[\"sphere_b.vrml\"]}]}"<<endl;
				sss<<"Transform {translation "<<SRol->x[i].Stbl->x[j].pc2;
				sss<<"scale "<<(-SRol->x[i].Stbl->x[j].nst);
				sss<<"children[Inline {url[\"line.vrml\"]}]}";
				sss<<"Transform {translation "<<SRol->x[i].Stbl->x[j].pc2;
				sss<<"scale "<<SRol->x[i].Stbl->x[j].nc2;
				sss<<"children[Inline {url[\"line_b.vrml\"]}]}";

			}
			sss<<endl;
		}
	}else
	{
		i	= k<SRol->N? k : 0;
		s_rol	= sro.x[i];
		for(j=0;j<SRol->x[i].Stbl->N;j++)
		{
			sss<<"Transform {translation "<<SRol->x[i].Stbl->x[j].pc1;
			sss<<"scale "<<SRol->x[i].s_rol<<" "<<SRol->x[i].s_rol<<" "<<SRol->x[i].s_rol<<endl;
			sss<<"children[Inline {url[\"sphere_g.vrml\"]}]}";
			sss<<"Transform {translation "<<SRol->x[i].Stbl->x[j].pc1;
			sss<<"scale "<<SRol->x[i].Stbl->x[j].nst;
			sss<<"children[Inline {url[\"line.vrml\"]}]}";
			sss<<"Transform {translation "<<SRol->x[i].Stbl->x[j].pc1;
			sss<<"scale "<<SRol->x[i].Stbl->x[j].nc1;
			sss<<"children[Inline {url[\"line_g.vrml\"]}]}";
			sss<<"Transform {translation "<<SRol->x[i].Stbl->x[j].pc2;
			sss<<"scale "<<SRol->x[i].s_rol<<" "<<SRol->x[i].s_rol<<" "<<SRol->x[i].s_rol<<endl;
			sss<<"children[Inline {url[\"sphere_b.vrml\"]}]}"<<endl;
			sss<<"Transform {translation "<<SRol->x[i].Stbl->x[j].pc2;
			sss<<"scale "<<(-SRol->x[i].Stbl->x[j].nst);
			sss<<"children[Inline {url[\"line.vrml\"]}]}";
			sss<<"Transform {translation "<<SRol->x[i].Stbl->x[j].pc2;
			sss<<"scale "<<SRol->x[i].Stbl->x[j].nc2;
			sss<<"children[Inline {url[\"line_b.vrml\"]}]}";
		}
		sss<<endl;
	}
	
	sss.close();
}


void MolData::Cube2File(int k)		// ��� �vrml �� ���������� ������ �� �����'k'
{

	int i_x,i_y,i_z;
	double pcx,pcy,pcz;

	i_z	= (int)(k/(cbs.nx*cbs.ny));
	i_y	= (int)((k -i_z*cbs.nx*cbs.ny)/cbs.nx);
	i_x	= (int)(k -i_z*cbs.nx*cbs.ny-i_y*cbs.nx);

	pcx	= cbs.cnrMin.x[0]+i_x*cbs.cubsz+0.5*cbs.cubsz;
	pcy	= cbs.cnrMin.x[1]+i_y*cbs.cubsz+0.5*cbs.cubsz;
	pcz	= cbs.cnrMin.x[2]+i_z*cbs.cubsz+0.5*cbs.cubsz;

	fstream sss;

	sss.open("Cube.vrml",ios::out);
	sss.precision(17);
	sss<<"#VRML V2.0 utf8"<<'\n';
	sss<<"WorldInfo { info  [\"Surface\"]}"<<'\n';
	sss<<"Background{ skyColor 0 0 0}"<<'\n';


	sss<<"Transform {	translation " <<  pcx <<"  "<< pcy <<"  " << pcz <<'\n';
	sss<<"children [	Shape {	appearance Appearance {	material Material {"<<'\n';
	sss<<"diffuseColor 1 1 1	transparency 0.6	emissiveColor 0.2 0.2 0.2	} }"<<'\n';
	sss<<"geometry Box { size "<< cbs.cubsz <<"  "<< cbs.cubsz <<"  " << cbs.cubsz <<'\n';
	sss<<"}} ] }"<<'\n';

	sss.close();
}

bool TrPnt::isTris(Vec3db & a)
{
	Vec3db dr;
	double d;

	dr	= a-pc;
	d	= -ERR_ALW*dr.ssqr();
	
	if (mx->x[0].scpr(dr)<d) return false;
	if (mx->x[1].scpr(dr)<d) return false;
	if (mx->x[2].scpr(dr)<d) return false;

	for(int i=3;i<mx->N;i++)
	{
		if (mx->x[i].scpr(dr)<d) return false;
	}
	return true;
}
bool ScTrPnt::isTris(Vec3db & a)
{
	Vec3db dr;
	double d;

	dr	= a-pc;
	d	= -ERR_ALW*dr.ssqr();

		
	if (mx->x[0].scpr(dr)<d) return false;
	if (mx->x[1].scpr(dr)<d) return false;
	if (mx->x[2].scpr(dr)<d) return false;

	for(int i=3;i<mx->N;i++)
	{
		if (mx->x[i].scpr(dr)<d) return false;
	}
	return true;
}


bool ScStPnt::isSt1(Vec3db &a)
{
	Vec3db dr;	

	dr	= a-pc1;
	if(nst.scpr(dr)>d) return false;	// ���� � �� 'pc1-pc2' ��������� ���� 'pc1-pc2'
	dr.nrml();
	if(nst.scpr(dr)<csa) return false;	// �� �� ����������
	if(n_tr.x[0]!=-1)
	{
		if (nc1.scpr(dr)<0) return false;	// �� ���� ����� ����������90 ����
	}
	return true;
}

bool ScStPnt::isSt1(Vec3db &a, double &dz)
{
	Vec3db dr;

	dr	= a-pc1;
	if(nst.scpr(dr)>d) return false;	// ���� � �� 'pc1-pc2' ��������� ���� 'pc1-pc2'
	dr.nrml(dz);
	if(nst.scpr(dr)<csa) return false;	// �� �� ����������
	if(n_tr.x[0]!=-1)
	{
		if (nc1.scpr(dr)<0) return false;	// �� ���� ����� ����������90 ����
	}
	return true;
}

bool ScStPnt::isSt2(Vec3db &a)
{
	Vec3db dr;	

	dr	= a-pc1;
	if(nst.scpr(dr)<-d) return false;	// ���� � �� 'pc1-pc2' ��������� ���� 'pc1-pc2'
	dr.nrml();
	if(nst.scpr(dr)>-csa) return false;	// �� �� ����������
	if(n_tr.x[0]!=-1)
	{
		if (nc2.scpr(dr)<0) return false;	// �� ���� ����� ����������90 ����
	}
	return true;
}

bool ScStPnt::isSt2(Vec3db &a, double &dz)
{
	Vec3db dr;	

	dr	= a-pc1;
	if(nst.scpr(dr)<-d) return false;	// ���� � �� 'pc1-pc2' ��������� ���� 'pc1-pc2'
	dr.nrml(dz);
	if(nst.scpr(dr)>-csa) return false;	// �� �� ����������
	if(n_tr.x[0]!=-1)
	{
		if (nc2.scpr(dr)<0) return false;	// �� ���� ����� ����������90 ����
	}
	return true;
}


void MolData::ClearMoldata()	// ���������
{
	int i,j;
	
	for(i=0;i<Twos->mN;i++)
	{
		delete [] Twos->x[i].n_pnt;
	}
	for(i=0;i<Tris->mN;i++)
	{
		delete [] Tris->x[i].n_at;
		delete [] Tris->x[i].n_tr;
		delete [] Tris->x[i].n_tw;
		delete [] Tris->x[i].tr_n;
		delete [] Tris->x[i].c_tr;
		delete [] Tris->x[i].c_tw;
		delete [] Tris->x[i].n_pnt;
		delete [] Tris->x[i].mx;
	}
	for(i=0;i<SRol->mN;i++)
	{
		for(j=0;j<SRol->x[i].Tris->mN;j++)
		{
			delete [] SRol->x[i].Tris->x[j].mx;
			delete [] SRol->x[i].Tris->x[j].n_pnt;
			delete [] SRol->x[i].Tris->x[j].n_tr;
			delete [] SRol->x[i].Tris->x[j].n_tw;
			delete [] SRol->x[i].Tris->x[j].n_str;
			delete [] SRol->x[i].Tris->x[j].n_stw;
		}
		for(j=0;j<SRol->x[i].Twos->mN;j++)
		{
			delete [] SRol->x[i].Twos->x[j].n_pnt;
		}
		for(j=0;j<SRol->x[i].Stbl->mN;j++)
		{
			delete [] SRol->x[i].Stbl->x[j].n_pnt1;
			delete [] SRol->x[i].Stbl->x[j].n_pnt2;
		}
		delete [] SRol->x[i].Tris; 
		delete [] SRol->x[i].Stbl; 
		delete [] SRol->x[i].Twos;
	}	
	delete [] Tris;
	delete [] Twos; 
	delete [] SRol;
}

void MolData::SetTwos()	// �������� ������� �� ���.
{
	ms1D<int> niner(Atom.N);
	ms1D<bool> isa(Atom.N);
	ms1D<bool> alw(20);

	ms1D<int> itsat;
	ms1D<int> itsat1(Atom.N);
	ms1D<int> ntrp;	

	ms1D<int> *iA;

	Vec3db P0,P1,dP0,dP1;
	Vec3db x,y,z,pm,dh,csf;

	//---
	Vec3db ds1,ds2,ns1,ns2;
	//---

	ms1D<double> fi(20);
	ms1D<double> fi_(20);

	int i,j,i0,i1,j0,j1,k,k1;
	int jmin;
	int n_at3;

	//double Rc,dRw;
	double Rmin	= MY_INFINITY;

	double a,b,c,d,b1,c1;
	double csa,csb,cr1;
	double x_,y_,z_,csfmx;

	bool ch,ch1;

	j	= 0;
	for(i=0;i<Atom.N;i++){	j	= Atom.x[i].n_tr->N>j ? Atom.x[i].n_tr->N : j;}
	j	+= 20;
	At_ntr_mx	= j;
	ntrp.sm(j);
	j	= 0;
	for(i=0;i<Atom.N;i++){	j	= Atom.x[i].n_un->N>j ? Atom.x[i].n_un->N : j;}
	j	+= 20;
	At_nun_mx	= j;
	itsat.sm(j);
	j	= 0;
	for(i=0;i<Tris->N;i++){	j	= Tris->x[i].n_at->N>j ? Tris->x[i].n_at->N : j;}
	j	+= 20;
	Tr_nat_mx	= j;
	itsat1.sm(j);


	Twos->init(0,(int)(1.5*Tris->N+100));

	isa	= (IND_TR_ATOM != S_At);
	S_At.fnd(isa,niner);	//  �niner ��� ��� � ��� �. ���

	for (i=0;i<niner.N;i++)	// �� � ��� � ��� ���������
	{

		i0	= niner.x[i];	// ������
		P0	= Atom.x[i0].xyz;
		a	= p_rol+Atom.x[i0].r_wdw;
		ch1	= true;
		for (j=0;j<Atom.x[i0].n_un->N&&ch1;j++)
		{
			jmin	= Atom.x[i0].n_un->x[j];
			b	= Atom.x[jmin].r_wdw+p_rol;
			P1	= Atom.x[jmin].xyz;
			dP0	= P1-P0;
			c	= dP0.ssqr();
			d	*=d = a-b; 
			if(c>d)
			{	
				c	= sqrt(c);
				dP0	/=c;
				csa	= (a*a+c*c-b*b)/(2*a*c);
				d	= a*sqrt(1-csa*csa);
				if (dP0.x[1]!=0)
				{
					dh.x[2]	= 0;
					dh.x[0]	= d*dP0.x[1]/sqrt(dP0.x[0]*dP0.x[0]+dP0.x[1]*dP0.x[1]);
					dh.x[1]	= -dh.x[0]*dP0.x[0]/dP0.x[1];
				}
				else
				{
					dh.x[2]	= 0;
					dh.x[0]	= 0;
					dh.x[1]	= d;
				}
				pm	= P0+dP0*a*csa;
				dh	+= pm;
				
				Atom.x[i0].n_un->itss(*Atom.x[jmin].n_un,itsat);
				
				ch	= true;
				for(k=0;(k<itsat.N)&&(ch);k++)
				{
					j0	= itsat.x[k];
					P1	= Atom.x[j0].xyz;
					dP1	= P1-dh;
					
					b*= b = Atom.x[j0].r_wdw+p_rol;
					ch	 = dP1.ssqr()>=b;
				}
				if (ch)
				{
					S_At.x[i0]	= IND_NTRSF_ATOM; // ��������� � ��� ������ ���
					//S_At.x[jmin]= IND_NTRSF_ATOM; // ��������� � ��� ������ ���
					break;
				}
			}else
			{
				if (b>a) ch1	= false;
			}
		}
		if (ch1) S_At.x[i0]	= IND_NTRSF_ATOM; // ��������� � ��������� ��� ����� �� ����
	}

		/*i0	= niner.x[i];	// ������
		P0	= Atom.x[i0].xyz;
		a	= Atom.x[i0].r_wdw;
		jmin	= -1;
		Rmin	= MY_INFINITY;
		for (j=0;j<Atom.x[i0].n_un->N;j++)
		{
			i1	= Atom.x[i0].n_un->x[j];
			P1	= Atom.x[i1].xyz;
			dP0	= P1-P0;
			Rc	= dP0.ssqr();
			dRw	*= dRw = a-Atom.x[i1].r_wdw;
			if((Rc>dRw)&&(Rc<Rmin))
			{
				jmin	= i1;
				Rmin	= Rc;
			}
		}
		Rmin	= sqrt(Rmin);
		c	= a+Atom.x[jmin].r_wdw+2*p_rol;
		if ((jmin!=-1)&&(Rmin<c))
		{
			a	+= p_rol;
			b	= Atom.x[jmin].r_wdw+p_rol;
			P1	= Atom.x[jmin].xyz;
			dP0	= P1-P0;
			dP0.nrml(c);
			csa	= (a*a+c*c-b*b)/(2*a*c);
			d	= a*sqrt(1-csa*csa);
			if (dP0.x[1]!=0)
			{
				dh.x[2]	= 0;
				dh.x[0]	= d*dP0.x[1]/sqrt(dP0.x[0]*dP0.x[0]+dP0.x[1]*dP0.x[1]);
				dh.x[1]	= -dh.x[0]*dP0.x[0]/dP0.x[1];
			}
			else
			{
				dh.x[2]	= 0;
				dh.x[0]	= 0;
				dh.x[1]	= 1;
				/*if (dP0.x[0]==0)
				{
					dh.x[2]	= 0;
					dh.x[0]	= 1;
					dh.x[1]	= 0;
				}else
				{
					if (dP0.x[2]==0)
					{
						dh.x[2]	= 1;
						dh.x[0]	= 0;
						dh.x[1]	= 0;
					}
				}* /
			}

			dh	*= d;
			pm	= P0+dP0*a*csa;
			dh	+= pm;

			Atom.x[i0].n_un->itss(*Atom.x[jmin].n_un,itsat);

			ch	= true;
			for(j=0;(j<itsat.N)&&(ch);j++)
			{
				j0	= itsat.x[j];
				P1	= Atom.x[j0].xyz;
				dP1	= P1-dh;

				b*= b = Atom.x[j0].r_wdw+p_rol;
				ch	 = dP1.ssqr()>=b;
			}
			if (ch)
			{
				S_At.x[i0]	= IND_NTRSF_ATOM; // ��������� � ��� ������ ���
				//S_At.x[jmin]= IND_NTRSF_ATOM; // ��������� � ��� ������ ���
			}
		}
	}*/

	k	= 0;
	niner.N=0;
	for (i=0;i<S_At.N;i++)
	{		
		if((S_At.x[i]==IND_TR_ATOM)||(S_At.x[i]==IND_NTRSF_ATOM))
		{
			isa.x[i] = true;
			niner.x[niner.N++]=i;
		}else
			isa.x[i] = false;
	}

	for (i=0;i<niner.N;i++)
	{		
		i0	= niner.x[i];
		P0	= Atom.x[i0].xyz;
		a	= Atom.x[i0].r_wdw+p_rol;

		iA	= Atom.x[i0].n_ge;
		
		for(j=0;j<iA->N;j++)
		{			
			j0	= iA->x[j];
			if(isa.x[j0])
			{
				P1	= Atom.x[j0].xyz;
				b	= Atom.x[j0].r_wdw+p_rol;
				dP0	= P1-P0;
				cr1	*= cr1= a+b;
				c	= dP0.ssqr();
				if(c<cr1)
				{
					c	= sqrt(c);
					dP0/= c;
					csa	= (a*a+c*c-b*b)/(2*a*c);// ������: (��� ��, �����, ��)
					csfmx	= (b*b+c*c-a*a)/(2*b*c);
					pm	= P0+dP0*a*csa;	// ��������� ���� ������ ��� ���.

					Atom.x[i0].n_tr->itss(*Atom.x[j0].n_tr,ntrp); // ����� ��� ��c������� �� � ��� ���.

					if (ntrp.N!=0)
					{
						n_at3	= Tris->x[ntrp.x[0]].n_at->fnd(i0,j0);
						n_at3	= Tris->x[ntrp.x[0]].n_at->x[n_at3];// ��������� �������� (������ �������� ����'ntrp')
						x		= Atom.x[n_at3].xyz;
						x		-=pm;
						z		= dP0;
						csb		= z.scpr(x);
						x		-=z*csb;
						x.nrml();
						y.crss(z,x);

						fi.N		= 0;

						for(j1=0;j1<ntrp.N;j1++)
						{
							dh	= Tris->x[ntrp.x[j1]].pc-pm;
							dh.nrml();
							x_	= dh.scpr(x);
							y_	= dh.scpr(y);
							z_	= y_>=0 ? x_+1:-x_-1;
							fi.add(z_);
						}

						fi.sort(fi_,ntrp);

						itsat.pst(*Tris->x[ntrp.x[0]].n_at);						
						for(j1=1;j1<ntrp.N;j1++)
						{
							itsat.unis(*Tris->x[ntrp.x[j1]].n_at,itsat1);
							itsat=itsat1;
						}
						j1	= itsat.fnd(i0);
						itsat.rem(1,j1);
						j1	= itsat.fnd(j0);
						itsat.rem(1,j1);
						itsat1.N= 0;

						if (ntrp.N>alw.mN) alw.sm(ntrp.N);
						alw.N	= ntrp.N;
						alw		= true;
						for(j1=0;j1<itsat.N;j1++)
						{
							dh	= Atom.x[itsat.x[j1]].xyz-pm;
							z_	= dh.scpr(z);
							dh	-= z*z_;
							dh.nrml();
							x_	= dh.scpr(x);
							y_	= dh.scpr(y);
							z_	= y_>=0 ? x_+1:-x_-1;
							for(i1=0;(i1<fi_.N)&&(fi_.x[i1]<z_);i1++);
							i1	= i1==fi_.N ? 0 : i1;
							alw.x[i1]	= false;
						}
						itsat1.N= alw.N;
						itsat1	= 0;
						for(j1=0;j1<alw.N;j1++)if(alw.x[j1]){itsat.x[j1]++;}

						k1	=0;
						for(j1=1;j1<alw.N;j1++)
						{
							if(alw.x[j1])
							{
								if (k>=Twos->mN)Twos->adm_(ADD_TWS_NMBR);

								Twos->x[k].hab.x[0]	= a*sqrt(1-csa*csa);
								Twos->x[k].hab.x[1]	= -a*csa;
								Twos->x[k].hab.x[2]	= c-a*csa;
								
								Twos->x[k].rp		= pm;
								Twos->x[k].x		= x;
								Twos->x[k].y		= y;
								Twos->x[k].z		= z;
								
								Twos->x[k].mx.x[0]	= fi_.x[j1-1];
								Twos->x[k].mx.x[1]	= fi_.x[j1];

								//--- ������������������ ����� ���� � ���. ����� ��
								ds1	= Atom.x[i0].xyz-(pm+x*Twos->x[k].hab.x[0]);
								ds2	= Atom.x[j0].xyz-(pm+x*Twos->x[k].hab.x[0]);
								ds1	/= a;
								ds2	/= b;
								ds2	+= ds1;
								ds2.nrml();
								Twos->x[k].cs2	= ds2.scpr(ds1);
								Twos->x[k].nc2	= pm-z*z.scpr(ds2)*Twos->x[k].hab.x[0]/x.scpr(ds2);
								Twos->x[k].cs1	= 1.01;	// ���� ������ �������
								//---

								
								Twos->x[k].n_tr.x[0]= ntrp.x[j1-1];
								Twos->x[k].n_tr.x[1]= ntrp.x[j1];
								
								Twos->x[k].n_at.x[0]= i0;
								Twos->x[k].n_at.x[1]= j0;
								
								Twos->x[k].ism		= false;
								Twos->x[k].igr		= -1;
								
								if(Twos->x[k].hab.x[0]-p_rol<= s_rol)
								{
									//здесь надо добавить дополнительные условия
									//- пример: обкатка воргуг атомов с сильно отличающимися радиусами 
									// при этом маленький атом расположен на расстоянии немного меньше 
									// чем радиус большого атома - при этом расзрешённая часть тора не будет 
									// включать в себя перетяжку ...
									Tris->x[ntrp.x[j1-1]].c_tr->add(ntrp.x[j1]);
									Tris->x[ntrp.x[j1]].c_tr->add(ntrp.x[j1-1]);
								}

								Tris->x[ntrp.x[j1-1]].n_tr->add(ntrp.x[j1]);
								Tris->x[ntrp.x[j1]].n_tr->add(ntrp.x[j1-1]);

								//Tris->x[ntrp.x[j1-1]].n_tw->add(ntrp.x[j1]);
								//Tris->x[ntrp.x[j1]].n_tw->add(ntrp.x[j1-1]);
								Tris->x[ntrp.x[j1-1]].n_tw->add(k);
								Tris->x[ntrp.x[j1]].n_tw->add(k);
								Atom.x[i0].n_tw->add(k);
								Atom.x[j0].n_tw->add(k);

								Atom.x[i0].mx.add(csa);
								Atom.x[i0].csf.add(dP0);		
								Atom.x[j0].mx.add(csfmx);
								Atom.x[j0].csf.add(-dP0);

								Twos->N++;
								k++;
								k1++;
							}
						}
						if (k1==1) Twos->x[k-1].ism	= true;
					}else
					{
						d	= a*sqrt(1-csa*csa);	// ��� ����
						ch	= true;
						itsat.N=0;
						Atom.x[i0].n_un->itss(*Atom.x[j0].n_un,itsat);
						for(j1=0;(j1<itsat.N)&&(ch);j1++)
						{
							i1	= itsat.x[j1];
							if(isa.x[i1])
							{
								y	= Atom.x[i1].xyz;
								y	-=pm; 
								b1	= y.ssqr();
								c1	*= c1 =y.scpr(dP0);
								y_	= b1+d*d-2*d*sqrt(b1-c1);//-c1);
								b1	*= b1 = Atom.x[i1].r_wdw+p_rol;
								ch	= y_>=b1;
							}
						}
						if(ch)
						{
							if (dP0.x[1]!=0)
							{
								dh.x[2]	= 0.0;
								dh.x[0]	= d*dP0.x[1]/sqrt(dP0.x[0]*dP0.x[0]+dP0.x[1]*dP0.x[1]);
								dh.x[1]	= -dh.x[0]*dP0.x[0]/dP0.x[1];
							}else
							{
								dh.x[0]	= 0.0;
								dh.x[1]	= d;
								dh.x[2]	= 0.0;
							}

							if (k>=Twos->mN) {Twos->adm_(ADD_TWS_NMBR);}
							
							Twos->x[k].hab.x[0]	= d;
							Twos->x[k].hab.x[1]	= -a*csa;
							Twos->x[k].hab.x[2]	= c-a*csa;
							
							Twos->x[k].rp		= pm;
							Twos->x[k].x		= dh/d;
							Twos->x[k].z		= dP0;
							Twos->x[k].y.crss(Twos->x[k].z,Twos->x[k].x);
							
							Twos->x[k].mx.x[0]	= -2.0;
							Twos->x[k].mx.x[1]	= 2.0;
							
							Twos->x[k].n_tr.x[0]= -1;
							Twos->x[k].n_tr.x[1]= -1;
							
							Twos->x[k].n_at.x[0]= i0;
							Twos->x[k].n_at.x[1]= j0;
							
							Twos->x[k].ism		= true;
							Twos->x[k].igr		= -1;


							//--- ������������������ ����� ���� � ���. ����� ��
							ds1	= Atom.x[i0].xyz-(pm+dh);
							ds2	= Atom.x[j0].xyz-(pm+dh);
							ds1	/= a;ds2	/= b;ds2	+= ds1;
							ds2.nrml();
							Twos->x[k].cs2	= ds2.scpr(ds1);
							Twos->x[k].nc2	= pm-dP0*dP0.scpr(ds2)*d*d/dh.scpr(ds2);
							Twos->x[k].cs1	= 1.01;	// ���� ������ �������
							//---


							// ������� � ������ ???
							
							Atom.x[i0].n_tw->add(k);
							Atom.x[j0].n_tw->add(k);

							Atom.x[i0].mx.add(csa);
							Atom.x[i0].csf.add(dP0);							
							Atom.x[j0].mx.add(csfmx);
							Atom.x[j0].csf.add(-dP0);
							
							Twos->N++;
							k++;

						}
					}
				}
			}
		}
	}
	for(i=0;i<Twos->N;i++) Twos->x[i].igr = -1;	
}

void MolData::SetAtomCn()							// �������� ���������� �������
{
	int i,j,i0,j0;
	double a,b;
	Vec3db P0,dP0,P1;
	/*ms1D<int> niner(Atom.N);
	ms1D<int> *iA;*/

	for(i=0;i<Atom.N;i++)
	{
		a	= Atom.x[i].r_wdw+p_rol;
		P0	= Atom.x[i].xyz;
		Atom.x[i].csf.one(Atom.x[i].n_tw->N);
		Atom.x[i].mx.one(Atom.x[i].n_tw->N);
		Atom.x[i].mx_c.sm(Atom.x[i].n_tw->N);
		Atom.x[i].csf_c.sm(Atom.x[i].n_tw->N);
		for(j=0;j<Atom.x[i].n_tw->N;j++)
		{
			i0	= Atom.x[i].n_tw->x[j];
			j0	= Twos->x[i0].n_at.x[0]==i ? Twos->x[i0].n_at.x[1] : Twos->x[i0].n_at.x[0];
			P1	= Twos->x[i0].rp-P0;
			dP0	= Atom.x[j0].xyz-P0;
			P1.nrml(b);
			dP0.nrml();
			Atom.x[i].csf.x[j]	= dP0;
			Atom.x[i].mx.x[j]	= P1.scpr(dP0)>0 ? b/a : -b/a ;
		}
	}
	/*niner.N=0;
	for (i=0;i<S_At.N;i++) 	if((S_At.x[i]==IND_TR_ATOM)||(S_At.x[i]==IND_NTRSF_ATOM))	niner.x[niner.N++]=i;

	for (i=0;i<niner.N;i++) Atom.x[niner.x[i]].mx.N = Atom.x[niner.x[i]].csf.N = 0;

	for (i=0;i<niner.N;i++)
	{		
		i0	= niner.x[i];
		P0	= Atom.x[i0].xyz;
		a	= Atom.x[i0].r_wdw+p_rol;

		iA	= Atom.x[i0].n_un;
		for(j=0;j<iA->N;j++)
		{
			j0	= iA->x[j];
			P1	= Atom.x[j0].xyz;
			b	= Atom.x[j0].r_wdw+p_rol;

			dP0	= P1-P0;
			cr1	*= cr1= a+b;
			c	= dP0.ssqr();
			if(c<cr1)
			{
				c	= sqrt(c);
				dP0/= c;
				csa	= (a*a+c*c-b*b)/(2*a*c);// ������: (��� ��, �����, ��)
				//csb	= (b*b+c*c-a*a)/(2*b*c);

				Atom.x[i0].mx.add(csa);
				Atom.x[i0].csf.add(dP0);
				//Atom.x[j0].mx.add(csb);
				//Atom.x[j0].csf.add(-dP0);
			}
		}
	}*/
}

void MolData::SetScForb()
{
	int i,j;
	int itw;
	double rol,dd;
	//ScStPnt	*SSt;
	ScTwPnt	*STw;
	Vec3db	p1;

	for(i=0;i<SRol->N;i++)
	{
		rol	= p_rol+sro.x[i];
		/*for(j=0;j<SRol->x[i].Stbl->N;j++)
		{
			SSt	= &SRol->x[i].Stbl->x[j];
			itw	= SSt->nTw;
			Twos->x[itw].cs1	= Twos->x[itw].hab.x[0]/rol;
		}//*/
		for(j=0;j<SRol->x[i].Twos->N;j++)
		{
			STw	= &SRol->x[i].Twos->x[j];

			itw	= STw->n_tr.x[0];
			p1	= STw->rp-Tris->x[itw].pc;
			p1	/=STw->d;
			dd	= STw->d/rol;
			Tris->x[itw].s_tr->add(p1);
			Tris->x[itw].s_mx->add(dd);

			itw	= STw->n_tr.x[1];
			p1	= STw->rp-Tris->x[itw].pc;
			p1	/=STw->d;
			Tris->x[itw].s_tr->add(p1);
			Tris->x[itw].s_mx->add(dd);
		}
	}
	for(i=0;i<Twos->N;i++)
	{
		j	= Twos->x[i].igr;
		if(j!=-1)
		{
			Twos->x[i].cs1	= Twos->x[i].hab.x[0]/(p_rol+sro.x[j]);
		}
	}
}

#endif
