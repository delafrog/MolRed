// ************************************************
//  ��������� ������-TAGSS-  (��� 1.0.0)
//  Triangulated Adaptive Grid of Smooth Surface
//	21 ��� 2005�
//  ��������
//  (C) DIMONTA Lab
// ************************************************


#ifndef _VOLUME_H
#define _VOLUME_H

#include "massiv.h"


void setrwdw(ms1D<int> &tpind, ms1D<double> &wdr, ms1D<double> &r_wdw);

class cubdev		// ������� ����������� � ��.
{
public:
	double	cubsz;	// ��� ��� ��.

	Vec3db	cnrMin;	// ����� ��, ��� ���� ���� � �� ���� ����������� (����'sz').
					// (����x),���y),���(z) ��, ���� ��������)
	Vec3db	cnrMax;
	ms1D<ms1Dint> n_at;	// ����� ���;	
	ms1D<ms1Dint> c_at;	// ����� ���;	
	ms1D<ms1Dint> n_tr; // ����� �. ���
	ms1D<ms1Dint> n_tw; // ����� �� ����

	ms1D<ms1Dint> n_sp;	// ����� ���������
	//ms1D<ms1Dint> n_cb;	// ����� ���

	int N, nx,ny,nz;	// �� �������� �������� ����� �� �����

	cubdev(double cubsz_){cubsz = cubsz_;}

	void RemovePoint(int &n_pnt,int &ii);

	void equal(cubdev &cbs)
	{
		cubsz	= cbs.cubsz;
		cnrMin	= cbs.cnrMin;
		cnrMax	= cbs.cnrMax;
		N=cbs.N;nx=cbs.nx;ny=cbs.ny;nz=cbs.nz;
		c_at.x	= cbs.c_at.x;c_at.N	= cbs.c_at.N;c_at.mN	= cbs.c_at.mN;
		n_at.x	= cbs.n_at.x;n_at.N	= cbs.n_at.N;n_at.mN	= cbs.n_at.mN;
		n_sp.x	= cbs.n_sp.x;n_sp.N	= cbs.n_sp.N;n_sp.mN	= cbs.n_sp.mN;
		n_tr.x	= cbs.n_tr.x;n_tr.N	= cbs.n_tr.N;n_tr.mN	= cbs.n_tr.mN;
		n_tw.x	= cbs.n_tw.x;n_tw.N	= cbs.n_tw.N;n_tw.mN	= cbs.n_tw.mN;
	}
	void free(cubdev &cbs)
	{
		/*cbs.n_at.x	= n_at.x;
		cbs.c_at.x	= c_at.x;
		cbs.n_sp.x	= n_sp.x;
		cbs.n_tr.x	= n_tr.x;
		cbs.n_tw.x	= n_tw.x;//*/
		cbs.c_at.x	= c_at.x;cbs.c_at.N	= c_at.N;cbs.c_at.mN	= c_at.mN;
		cbs.n_at.x	= n_at.x;cbs.n_at.N	= n_at.N;cbs.n_at.mN	= n_at.mN;
		cbs.n_sp.x	= n_sp.x;cbs.n_sp.N	= n_sp.N;cbs.n_sp.mN	= n_sp.mN;
		cbs.n_tr.x	= n_tr.x;cbs.n_tr.N	= n_tr.N;cbs.n_tr.mN	= n_tr.mN;
		cbs.n_tw.x	= n_tw.x;cbs.n_tw.N	= n_tw.N;cbs.n_tw.mN	= n_tw.mN;
		cbs.cubsz	= cubsz;
		cbs.cnrMin	= cnrMin;
		cbs.cnrMax	= cnrMax;
		cbs.N=N;cbs.nx=nx;cbs.ny=ny;cbs.nz=nz;
		c_at.x	= 0x0;c_at.N	= 0;c_at.mN	= 0;
		n_at.x	= 0x0;n_at.N	= 0;n_at.mN	= 0;
		n_sp.x	= 0x0;n_sp.N	= 0;n_sp.mN	= 0;
		n_tr.x	= 0x0;n_tr.N	= 0;n_tr.mN	= 0;
		n_tw.x	= 0x0;n_tw.N	= 0;n_tw.mN	= 0;
	}

	cubdev(cubdev &cbs)
	{
		cubsz	= cbs.cubsz;
		cnrMin	= cbs.cnrMin;
		cnrMax	= cbs.cnrMax;
		N=cbs.N;nx=cbs.nx;ny=cbs.ny;nz=cbs.nz;
		c_at.sm(cbs.c_at.N);
		n_at.sm(cbs.n_at.N);
		n_sp.sm(cbs.n_sp.N);
		n_tr.sm(cbs.n_tr.N);
		n_tw.sm(cbs.n_tw.N);
		c_at.N	= cbs.c_at.N;
		n_at.N	= cbs.n_at.N;
		n_sp.N	= cbs.n_sp.N;
		n_tr.N	= cbs.n_tr.N;
		n_tw.N	= cbs.n_tw.N;
		int i;
		for(i=0;i<c_at.N;i++) {c_at.x[i].pst(cbs.c_at.x[i]);}
		for(i=0;i<n_at.N;i++) {n_at.x[i].pst(cbs.n_at.x[i]);}
		for(i=0;i<n_sp.N;i++) {n_sp.x[i].pst(cbs.n_sp.x[i]);}
		for(i=0;i<n_tr.N;i++) {n_tr.x[i].pst(cbs.n_tr.x[i]);}
		for(i=0;i<n_tw.N;i++) {n_tw.x[i].pst(cbs.n_tw.x[i]);}
	}

	cubdev &	operator = (const cubdev &cbs)
	{
		cubsz	= cbs.cubsz;
		cnrMin	= cbs.cnrMin;
		cnrMax	= cbs.cnrMax;
		N=cbs.N;nx=cbs.nx;ny=cbs.ny;nz=cbs.nz;
		c_at.sm(cbs.c_at.N);
		n_at.sm(cbs.n_at.N);
		n_sp.sm(cbs.n_sp.N);
		n_tr.sm(cbs.n_tr.N);
		n_tw.sm(cbs.n_tw.N);
		c_at.N	= cbs.c_at.N;
		n_at.N	= cbs.n_at.N;
		n_sp.N	= cbs.n_sp.N;
		n_tr.N	= cbs.n_tr.N;
		n_tw.N	= cbs.n_tw.N;
		int i;
		for(i=0;i<c_at.N;i++) {c_at.x[i].pst(cbs.c_at.x[i]);}
		for(i=0;i<n_at.N;i++) {n_at.x[i].pst(cbs.n_at.x[i]);}
		for(i=0;i<n_sp.N;i++) {n_sp.x[i].pst(cbs.n_sp.x[i]);}
		for(i=0;i<n_tr.N;i++) {n_tr.x[i].pst(cbs.n_tr.x[i]);}
		for(i=0;i<n_tw.N;i++) {n_tw.x[i].pst(cbs.n_tw.x[i]);}

		return *this;
	}

	void at_in_cubs(ms1D<Vec3db> &xyz, ms1D<double> &r_wdw);	// ���� ��� � ���

	friend void CopyObject(cubdev &a,cubdev &b);
	friend void InitObject(cubdev &a);
	friend void ClearObject(cubdev &a);



	cubdev(){}
	~cubdev(){}
	
/*	friend ostream & operator << (ostream & stream,subcub &a)	// ����� ��� ���
	{
		stream<<a.n_pnt.N<<endl;
		stream<<a.n_pnt<<endl;
		return stream;
	}
	friend istream & operator >> (istream & stream,subcub &a)	// ����� ��� ���
	{
		stream>>a.n_pnt.N;
		if (a.n_pnt.N>a.n_pnt.mN) a.n_pnt.sm(a.n_pnt.N);
		stream>>a.n_pnt;
		return stream;
	}*/
};

#endif
