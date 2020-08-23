// ************************************************
//  ��������� ������-TAGSS-  (��� 1.0.0)
//  Triangulated Adaptive Grid of Smooth Surface
//	21 ��� 2005�
//  ��������
//  (C) DIMONTA Lab
// ************************************************


#ifndef _VOLUME_CPP
#define _VOLUME_CPP


#include "volume.h"


//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
void setrwdw(ms1D<int> &tpind, ms1D<double> &wdr, ms1D<double> &r_wdw)
{
	r_wdw.one(tpind.N);
	for(int i=0;i<tpind.N;i++) r_wdw.x[i] =wdr.x[tpind.x[i]];
}


void cubdev::RemovePoint(int &n_pnt,int &ii)
{
	int ix,iy,iz,i_x,i_y,i_z,ix_,iy_,iz_,iix,iiy,iiz,ii_,j;

	iz	= (int)(ii/(nx*ny));
	iy	= (int)(ii-nx*ny*iz)/(nx);
	ix	= ii-nx*(iy+ny*iz);

	ix_	= ix>=(nx-1)?nx:ix+2;
	iy_	= iy>=(ny-1)?ny:iy+2;
	iz_	= iz>=(nz-1)?nz:iz+2;
	i_x	= ix<=0?0:ix-1;
	i_y	= iy<=0?0:iy-1;
	i_z	= iz<=0?0:iz-1;
	for (iiz=i_z;iiz<iz_;iiz++)
	{
		for(iiy=i_y;iiy<iy_;iiy++)
		{
			for(iix=i_x;iix<ix_;iix++)
			{
				ii_	= iix+nx*(iiy+ny*iiz);
				j	= n_sp.x[ii_].fnd(n_pnt);
				if(j!=-1)
				{
					n_sp.x[ii_].rem(1,j);
				}
			}
		}
	}
}


void cubdev::at_in_cubs(ms1D<Vec3db> &xyz, ms1D<double> &r_wdw)
{
	int ix,iy,iz,ii,i;

	double R_max;

	cnrMin=cnrMax=0.0;

	r_wdw.mmax(R_max);	

	for (i=0;i<xyz.N;i++)
	{
		cnrMin.x[0]	= xyz.x[i].x[0] < cnrMin.x[0] ? xyz.x[i].x[0] : cnrMin.x[0];
		cnrMin.x[1]	= xyz.x[i].x[1] < cnrMin.x[1] ? xyz.x[i].x[1] : cnrMin.x[1];
		cnrMin.x[2]	= xyz.x[i].x[2] < cnrMin.x[2] ? xyz.x[i].x[2] : cnrMin.x[2];

		cnrMax.x[0]	= xyz.x[i].x[0] > cnrMax.x[0] ? xyz.x[i].x[0] : cnrMax.x[0];
		cnrMax.x[1]	= xyz.x[i].x[1] > cnrMax.x[1] ? xyz.x[i].x[1] : cnrMax.x[1];
		cnrMax.x[2]	= xyz.x[i].x[2] > cnrMax.x[2] ? xyz.x[i].x[2] : cnrMax.x[2];
	}

	cnrMax	+= R_max;
	cnrMin	-= R_max;

	nx	= (int)((cnrMax.x[0]-cnrMin.x[0])/cubsz);nx++;
	ny	= (int)((cnrMax.x[1]-cnrMin.x[1])/cubsz);ny++;
	nz	= (int)((cnrMax.x[2]-cnrMin.x[2])/cubsz);nz++;

	N	= nx*ny*nz;
	
	n_at.init(N);
	c_at.init(N);
	n_tr.sm(N);
	n_tw.sm(N);
	n_sp.init(N);

	for (i=0;i<xyz.N;i++)
	{
		ix	= (int)((xyz.x[i].x[0]-cnrMin.x[0])/cubsz);
		iy	= (int)((xyz.x[i].x[1]-cnrMin.x[1])/cubsz);
		iz	= (int)((xyz.x[i].x[2]-cnrMin.x[2])/cubsz);

		ii	= ix+nx*(iy+ny*iz);

		n_at.x[ii].add(i);
	}
	for (ii=0;ii<n_at.N;ii++) n_at.x[ii].sort();
}

void CopyObject(cubdev &a,cubdev &b)
{
	a.cubsz	= b.cubsz;
	a.cnrMax= b.cnrMax;
	a.cnrMin= b.cnrMin;
	a.N		= b.N;
	a.nx	= b.nx;
	a.ny	= b.ny;
	a.nz	= b.nz;
	a.n_at.pst(b.n_at);
	a.n_tr.pst(b.n_tr);
	a.n_tw.pst(b.n_tw);
	a.n_sp.pst(b.n_sp);
}
void InitObject(cubdev &a)
{
	a.cubsz	= 0;
	a.cnrMax= 0;
	a.cnrMin= 0;
	a.N		= 0;
	a.nx	= 0;
	a.ny	= 0;
	a.nz	= 0;
	InitObject(a.n_at);
	InitObject(a.n_tr);
	InitObject(a.n_tw);
	InitObject(a.n_sp);
}
void ClearObject(cubdev &a)
{
	ClearObject(a.n_at);
	ClearObject(a.n_tr);
	ClearObject(a.n_tw);
	ClearObject(a.n_sp);
}
//---------------------------------------------------------------------------------

#endif

