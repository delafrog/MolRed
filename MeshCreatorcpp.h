#ifndef _MESHCREATOR_CPP
#define _MESHCREATOR_CPP


#include "MeshCreator.h"
#include "globals.h"
#include "rolling.h"
#include "Trimesh.h"
#include <fstream>
#include <math.h>

#define EXT 10

#define AtomSphere 0
#define TwosTorus  1
#define TrisSphere 2
#define ScStblSph1 3 
#define ScStblSph2 4
#define ScTrisSphr 5
#define ScTwosTor  6


#define	AddQuantPnt	10000
#define	AddQuantEdg	30000
#define	AddQuantTri	20000


MeshConstructor::MeshConstructor()
{
	//TrSurface();
	//MolData();
}

void MeshConstructor::InitSurface(TrSurface	&A)
{
	
	//delete [] Point.x;
	Point.x	= A.Point.x;
	Point.N	= A.Point.N;
	Point.mN= A.Point.mN;

	//delete [] Edge.x;
	Edge.x	= A.Edge.x;
	Edge.N	= A.Edge.N;
	Edge.mN	= A.Edge.mN;

	//delete [] Trngl.x;
	Trngl.x	= A.Trngl.x;
	Trngl.N	= A.Trngl.N;
	Trngl.mN= A.Trngl.mN;

	//delete [] BndEd.x;
	BndEd.x	= A.BndEd.x;
	BndEd.N	= A.BndEd.N;
	BndEd.mN= A.BndEd.mN;
	
}

void MeshConstructor::FreeSurface(TrSurface	&A)
{
	A.Point.x	= Point.x;
	A.Point.N	= Point.N;
	A.Point.mN	= Point.mN;

	A.Edge.x	= Edge.x;
	A.Edge.N	= Edge.N;
	A.Edge.mN	= Edge.mN;

	A.Trngl.x	= Trngl.x;
	A.Trngl.N	= Trngl.N;
	A.Trngl.mN	= Trngl.mN;

	A.BndEd.x	= BndEd.x;
	A.BndEd.N	= BndEd.N;

	Point.x	= 0x0;
	Edge.x	= 0x0;
	Trngl.x	= 0x0;
	BndEd.x	= 0x0;

}

void MeshConstructor::InitMolData(MolData	&M)
{

	AtTp.x	= M.AtTp.x;
	AtTp.N	= M.AtTp.N;
	AtTp.mN	= M.AtTp.mN;

	AtClr.x	= M.AtClr.x;
	AtClr.N	= M.AtClr.N;
	AtClr.mN= M.AtClr.mN;

	eig		= M.eig;
	pc		= M.pc;
	p_rol	= M.p_rol;
	s_rol	= M.s_rol;
	d_min	= M.d_min;
	InEig	= M.InEig;


	cbs.equal(M.cbs);

	//delete [] Q.x;
	Q.x		= M.Q.x;
	Q.N		= M.Q.N;
	Q.mN	= M.Q.mN;

	//delete [] Atom.x;
	Atom.x	= M.Atom.x;
	Atom.N	= M.Atom.N;
	Atom.mN	= M.Atom.mN;

	//delete [] sro.x;
	sro.x	= M.sro.x;
	sro.N	= M.sro.N;
	sro.mN	= M.sro.mN;

	//delete [] Nc.x;
	Nc.x	= M.Nc.x;
	Nc.N	= M.Nc.N;
	Nc.mN	= M.Nc.mN;

	//delete [] S_At.x;
	S_At.x	= M.S_At.x;
	S_At.N	= M.S_At.N;
	S_At.mN	= M.S_At.mN;

	Tris		= M.Tris;

	Twos		= M.Twos;

	SRol		= M.SRol;

	//delete [] TrsCnnNmb.x;
	TrsCnnNmb.x	= M.TrsCnnNmb.x;
	TrsCnnNmb.N	= M.TrsCnnNmb.N;
	TrsCnnNmb.mN= M.TrsCnnNmb.mN;

	AtmCnnNmb.x	= M.AtmCnnNmb.x;
	AtmCnnNmb.N	= M.AtmCnnNmb.N;
	AtmCnnNmb.mN= M.AtmCnnNmb.mN;

	//delete [] TrsCnfGrp.x;
	TrsCnfGrp.x	= M.TrsCnfGrp.x;	
	TrsCnfGrp.N	= M.TrsCnfGrp.N;
	TrsCnfGrp.mN= M.TrsCnfGrp.mN;	
}

void MeshConstructor::FreeMolData(MolData	&M)
{
	M.AtTp.x	= AtTp.x;
	M.AtTp.N	= AtTp.N;
	M.AtTp.mN	= AtTp.mN;

	M.AtClr.x	= AtClr.x;
	M.AtClr.N	= AtClr.N;
	M.AtClr.mN	= AtClr.mN;

	M.eig	= eig;
	M.pc	= pc;
	M.p_rol	= p_rol;
	M.s_rol	= s_rol;
	M.d_min	= d_min;
	M.InEig	= InEig;
	
	cbs.free(M.cbs);

	M.Q.x		= Q.x;
	M.Q.N		= Q.N;
	M.Q.mN		= Q.mN;

	M.Atom.x	= Atom.x;
	M.Atom.N	= Atom.N;
	M.Atom.mN	= Atom.mN;

	M.sro.x	= sro.x;
	M.sro.N	= sro.N;
	M.sro.mN= sro.mN;

	M.Nc.x	= Nc.x;
	M.Nc.N	= Nc.N;
	M.Nc.mN	= Nc.mN;

	M.S_At.x	= S_At.x;
	M.S_At.N	= S_At.N;
	M.S_At.mN	= S_At.mN;

	M.Tris		= Tris;

	M.Twos		= Twos;

	M.SRol		= SRol;

	M.TrsCnnNmb.x	= TrsCnnNmb.x;
	M.TrsCnnNmb.N	= TrsCnnNmb.N;
	M.TrsCnnNmb.mN	= TrsCnnNmb.mN;

	M.AtmCnnNmb.x	= AtmCnnNmb.x;
	M.AtmCnnNmb.N	= AtmCnnNmb.N;
	M.AtmCnnNmb.mN	= AtmCnnNmb.mN;

	M.TrsCnfGrp.x	= TrsCnfGrp.x;	
	M.TrsCnfGrp.N	= TrsCnfGrp.N;
	M.TrsCnfGrp.mN	= TrsCnfGrp.mN;	


	AtClr.x		= 0x0; AtClr.N		= 0; AtClr.mN		= 0;
	AtTp.x		= 0x0; AtTp.N		= 0; AtTp.mN		= 0;
	Q.x			= 0x0; Q.N			= 0; Q.mN			= 0;
	sro.x		= 0x0; sro.N		= 0; sro.mN			= 0;
	Nc.x		= 0x0; Nc.N			= 0; Nc.mN			= 0;
	S_At.x		= 0x0; S_At.N		= 0; S_At.mN		= 0;
	Atom.x		= 0x0; Atom.N		= 0; Atom.mN		= 0;
	Tris		= 0x0;
	Twos		= 0x0;
	SRol		= 0x0;
	TrsCnfGrp.x	= 0x0; TrsCnfGrp.N	= 0; TrsCnfGrp.mN	= 0;
	TrsCnnNmb.x	= 0x0; TrsCnnNmb.N	= 0; TrsCnnNmb.mN	= 0;
	AtmCnnNmb.x	= 0x0; AtmCnnNmb.N	= 0; AtmCnnNmb.mN	= 0;

}



void MeshConstructor::SetConfig(configpar &ConfPr)	//
{
	int ii;
	ms1D<int> tpind_in;
	ms1D<Vec3db> xyz_in;
	ms1D<double> Qin;

	smschar Prot("Prot",5);
	smschar Lig("Lig",4);
	smschar Compl("Compl",5);

	/*if(ConfPr.fnms.isoutfl=='Y')
	{
		outstm.open(ConfPr.fnms.outname.x,ios::out);
		//cout.sync_with_stdio();
		//outstm<<cout;
	
		cout_buffer = cout.rdbuf();
		cout.rdbuf (outstm.rdbuf());
	}/**/

	ii	= sizeof(char)*Prot.N;
	if (memcmp(ConfPr.surfpar.protlig.x,Prot.x,ii)==0)
	{
		str2data(ConfPr.fnms.protname,ConfPr.atomparam.AtNm,tpind_in,xyz_in,Qin);
	}else
	{
		ii	= sizeof(char)*Lig.N;
		if (memcmp(ConfPr.surfpar.protlig.x,Lig.x,ii)==0)
		{
			str2data(ConfPr.fnms.ligname,ConfPr.atomparam.AtNm,tpind_in,xyz_in,Qin);
		}else
		{
			ii	= sizeof(char)*Compl.N;
			if (memcmp(ConfPr.surfpar.protlig.x,Compl.x,ii)==0)
			{
				str2data(ConfPr.fnms.protname,ConfPr.fnms.ligname,ConfPr.atomparam.AtNm,tpind_in,xyz_in,Qin);
			}
			else
			{
				cout<<"Error in PROTLIG parametr. Only \"Prot\" \"Lig\" and \"Compl\" are allowed as keywords. "<<endl;
				cout<<"Prot - for construction the surface of protien only. "<<endl;
				cout<<"Lig - for construction the surface of lagend only. "<<endl;
				cout<<"Compl - for construction the surface of complex of protien ang ligand. "<<endl;
				cout<<"Try again with correct paramert. Programm is stoped. \n"<<endl;
				my_exit(0);
			}
		}
	}	


	MolData::tpind.pst(tpind_in);
	MolData::Q.pst(Qin);
	MolData::Atom.init(Qin.N);
	MolData::AtTp.init(Qin.N);
	MolData::AtClr.init(Qin.N);
	for(ii=0;ii<xyz_in.N;ii++)
	{
		MolData::Atom.x[ii].xyz		= xyz_in.x[ii];
		MolData::Atom.x[ii].r_wdw	= ConfPr.atomparam.r_wdw.x[tpind_in.x[ii]];
		MolData::AtTp.x[ii].pst(ConfPr.atomparam.AtNm.x[tpind_in.x[ii]]);
		MolData::AtClr.x[ii]		= ConfPr.atomparam.AtColor.x[tpind_in.x[ii]];
	}
	MolData::p_rol	= ConfPr.surfpar.rolradius;
	MolData::s_rol	= ConfPr.surfpar.secrolrad;
	MolData::d_min	= ConfPr.surfpar.minradcrv;

	MolData::S_At.init(Qin.N);
	MolData::S_At = -1;

	R_crcl	= ConfPr.surfpar.trsize;
	R_maxx	= ConfPr.surfpar.maxtrsize;
	alf_c	= ConfPr.surfpar.adptmesh2;
	Theta	= ConfPr.surfpar.in_thet;
	Phi		= ConfPr.surfpar.in_phi;
	
	N_rfn	= ConfPr.surfpar.refine;
}

void MeshConstructor::SetPar(grdpar &Gpar)
{
	R_crcl	= Gpar.R_tr;
	R_maxx	= Gpar.R_mx;
	alf_c	= Gpar.alfa;
	Theta	= Gpar.Thet;
	Phi		= Gpar.Phi;
}

void MeshConstructor::SetPar()
{
	R_crcl	= 0.3;
	R_maxx	= 0.7;
	alf_c	= 0;
	Theta	= 0;
	Phi		= 0;
}

int MeshConstructor::Pnt2Atom()
{
	int i,j,k;
	Vec3db dp,p1,dp1;
	double csa,csx,csy,csf,cba,cmn,csc;
	p_ms1Dint x;
	TwPnt	*Tw;
	//bool ch;

	dp	= p_in-Atom.x[n_At].xyz;
	dp.nrml(dst);
	dst	-= Atom.x[n_At].r_wdw;
	
	// ���� � ���� ���������
	cmn	= -1.01;
	k	= Atom.x[n_At].cfs;
	x	= &(Atom.x[n_At].set_ntw.x[k]);
	if (Atom.x[n_At].csf_c.N==0)
	{
		p_out	= Atom.x[n_At].xyz+dp*Atom.x[n_At].r_wdw;
		n_out	= dp;
				
		type.x[0]	= AtomSphere;
		type.x[1]	= n_At;
		type.x[2]	= -1;
		return 0;
	}
	for(i=0;i<Atom.x[n_At].csf_c.N;i++)
	{
		csa	= Atom.x[n_At].csf_c.x[i].scpr(dp);
		csc	= Atom.x[n_At].mx_c.x[i];
		if (csa>csc)
		{
			return 1;
		}
		cba	= csa*csc+sqrt((1-csa*csa)*(1-csc*csc));
		if(float(cba)>float(cmn))
		{
			indtw.N=0;
			j	= x->x[i];
			indtw.add(j);
			cmn	= cba;
		}else
		{
			if (float(cba)==float(cmn))
			{
				j	= x->x[i];
				indtw.add(j);
			}
		}
		//*/
	}
	// ���� � ���� �������������� ��
	p1	= Atom.x[n_At].xyz+dp*Atom.x[n_At].r_wdw;
	x	= &indtw;
	//x	= &(Atom.x[n_At].set_ntw.x[n_un_srf]);
	//i	= j;
	for(i=0;i<x->N;i++)
	{
		j	= Atom.x[n_At].n_tw->x[x->x[i]];
		Tw	= &(Twos->x[j]);
		dp1	= p1 - Tw->rp;
		csa	= Tw->z.scpr(dp1);
		dp1	-=Tw->z*csa;
		dp1.nrml();
		csx	= Tw->x.scpr(dp1);
		csy	= Tw->y.scpr(dp1);
		csf	= csy>0 ? csx+1 : -csx-1;
		if ((Tw->mx.x[1]>=csf)&&(csf>=Tw->mx.x[0]))
		{
			/*y	= &(Atom.x[n_At].set_ntw.x[n_un_srf]);
			ch	= true;
			for(j=0;(j<y->N)&&(ch);j++)
			{
				ch	= Tris->x[x->x[j]].isTris(p1);
			}
			if (ch)//*/
			{
				p_out	= p1;
				n_out	= dp;
				
				type.x[0]	= AtomSphere;
				type.x[1]	= n_At;
				type.x[2]	= -1;
				return 0;
			}
		}
	}//*/
	return 2;
}
int MeshConstructor::Pnt2Tws1()
{
	int i,j;
	Vec3db dp,p1,dp1,dp2;
	double csa,csx,csy,csf;
	p_ms1Dint x;
	TwPnt	*Tw;

	dst1	= MY_INFINITY;
	x	= &(Atom.x[n_At].set_ntw.x[n_un_srf]);
	for(i=0;i<x->N;i++)
	{
		j	= Atom.x[n_At].n_tw->x[x->x[i]];
		Tw	= &(Twos->x[j]);
		dp1	= p_in - Tw->rp;
		csa	= Tw->z.scpr(dp1);
		dp1	-=Tw->z*csa;
		dp1.nrml();
		csx	= Tw->x.scpr(dp1);
		csy	= Tw->y.scpr(dp1);
		csf	= csy>0 ? csx+1 : -csx-1;
		if((Tw->mx.x[1]>=csf)&&(csf>=Tw->mx.x[0]))
		{
			p1	= Tw->rp+dp1*Tw->hab.x[0];	// ����������
			dp	= p_in-p1;
			dp.nrml(dst1);
			dp2	= Tw->nc2-p1;
			dp2.nrml();
			csa	= dp2.scpr(dp);
			if(Tw->cs2<csa)
			{
				csa	= -dp1.scpr(dp);
				if(Tw->cs1>csa)
				{
					dst1	= p_rol- dst1;
					n_out	= -dp;
					p_out	= p1+dp*p_rol;
					n_Tw	= j;
					
					type.x[0]	= TwosTorus;
					type.x[1]	= n_Tw;
					type.x[2]	= -1;
					return 0;
				}
				else
				{
					n_ScGr	= Tw->igr;
					return 11;
				}
			}
		}
	}

	return 1;
}

int MeshConstructor::Pnt2Trs1()
{
	int i,j,k;
	Vec3db dp,p1;
	bool ch;
	double dr;
	p_ms1Dint x;
	TrPnt	*Tr;

	dst1= MY_INFINITY;
	x	= Atom.x[n_At].n_tr;
	k	= 1;
	for(i=0;i<x->N;i++)
	{
		Tr	= &(Tris->x[x->x[i]]);
		ch	= true;
		if (Tr->nfs==n_un_srf)
		{
			dp	= p_in-Tr->pc;
			dp.nrml(dr);
			if(dr<p_rol+0.5)
			{
				if(Tr->mx->x[0].scpr(dp)<0) {ch = false;}
				if(Tr->mx->x[1].scpr(dp)<0) {ch = false;}
				if(Tr->mx->x[2].scpr(dp)<0) {ch = false;}
				
				for(j=3;j<Tr->mx->N;j++)
				{
					if (Tr->mx->x[j].scpr(dp)<0) {ch = false;}
				}
				if ((ch)&&(dst1>dr))
				{
					
					for(j=0;j<Tr->s_mx->N;j++)
					{
						if((Tr->s_tr->x[j].scpr(dp))>Tr->s_mx->x[j]) {ch	= false;}
					}
					
					if (ch)
					{
						dst1	= dr;
						n_out	= -dp;
						p_out	= Tr->pc+dp*p_rol;
						n_Tr	= x->x[i];
						k		= 0;
						
						type.x[0]	= TrisSphere;
						type.x[1]	= n_Tr;
						type.x[2]	= -1;
					}
					else
					{
						dst1	= dr;
						n_ScGr	= Tr->igr;
						k	= 11;
					}
				}
			}
		}
	}
	return k;
}

int MeshConstructor::Pnt2Tws2()
{
	int i,j;
	Vec3db dp,p1,dp1,dp2;
	double csa,csx,csy,csf,dr;
	p_ms1Dint x;
	TwPnt	*Tw;

	dst1	= MY_INFINITY;
	x	= Atom.x[n_At].n_tws;
	for(i=0;i<x->N;i++)
	{
		j	= x->x[i];
		Tw	= &(Twos->x[j]);
		if(Tw->nfs==n_un_srf)
		{
			dp1	= p_in - Tw->rp;
			csa	= Tw->z.scpr(dp1);
			dp1	-=Tw->z*csa;
			dp1.nrml();
			csx	= Tw->x.scpr(dp1);
			csy	= Tw->y.scpr(dp1);
			csf	= csy>0 ? csx+1 : -csx-1;
			if((Tw->mx.x[1]>=csf)&&(csf>=Tw->mx.x[0]))
			{
				p1	= Tw->rp+dp1*Tw->hab.x[0];
				dp	= p_in-p1;
				dp.nrml(dr);
				dp2	= Tw->nc2-p1;
				dp2.nrml();
				csa	= dp2.scpr(dp);
				if(Tw->cs2<csa)
				{
					csa	= -dp1.scpr(dp);
					if(Tw->cs1>csa)
					{
						dr	=	p_rol-dr;
						dst1	= dr;
						n_out	= -dp;
						p_out	= p1+dp*p_rol;
						n_Tw	= j;
						
						type.x[0]	= TwosTorus;
						type.x[1]	= n_Tw;
						type.x[2]	= -1;
						return 0;
					}
					else
					{
						n_ScGr	= Tw->igr;
						return 11;
					}
				}
			}
		}
	}

	return 1;
}

int MeshConstructor::Pnt2Trs2()
{
	int i,j,k;
	Vec3db dp,p1;
	bool ch;
	double dr;
	p_ms1Dint x;
	TrPnt	*Tr;

	dst1= MY_INFINITY;
	x	= Atom.x[n_At].n_trs;
	k	= 1;
	for(i=0;i<x->N;i++)
	{
		Tr	= &(Tris->x[x->x[i]]);
		ch	= true;
		if (Tr->nfs==n_un_srf)
		{
			dp	= p_in-Tr->pc;
			dp.nrml(dr);
			if (dr<p_rol+0.5)
			{

			if(Tr->mx->x[0].scpr(dp)<0) ch = false;
			if(Tr->mx->x[1].scpr(dp)<0) ch = false;
			if(Tr->mx->x[2].scpr(dp)<0) ch = false;

			for(j=3;j<Tr->mx->N;j++)
			{
				if (Tr->mx->x[j].scpr(dp)<0) ch = false;
			}
			if ((ch)&&(dst1>dr))
			{
				for(j=0;j<Tr->s_mx->N;j++)
				{
					if((Tr->s_tr->x[j].scpr(dp))>Tr->s_mx->x[j]) {ch	= false;}
				}

				if (ch)
				{
					dst1	= dr;
					n_out	= -dp;
					p_out	= Tr->pc+dp*p_rol;
					n_Tr	= x->x[i];
					k		= 0;
					
					type.x[0]	= TrisSphere;
					type.x[1]	= n_Tr;
					type.x[2]	= -1;
				}
				else
				{
					dst1	= dr;
					n_ScGr	= Tr->igr;
					k	= 11;
				}
			}
			}
		}		
	}
	return k;
}

int MeshConstructor::Pnt2Srf1()
{
	int n_Rslt;

	DefCubNmb(p_in);	// ������������ �����������p_in

	n_At	= DefNearAt(p_in);	// ���� �� 	

	n_Rslt	= Pnt2Atom();		// ���� � ���� ��

	switch (n_Rslt)				// ��� ����� ������
	{
	case 0:		// �����������- ������ � ������
		{
			return 0;}
	/*case 1:		// ������������- ������������������� ��
		{
			n_Rslt = Pnt2Tws1();	// ��������� � ����� ��
			if (n_Rslt==1)			// ���� ����
			{
				n_Rslt = Pnt2Trs1();	// ���������� � ����� �. ���
			}
			break;			
		}
	case 2:
		{	// ������������- ������ ��� � ��� ������������� ��
			n_Rslt = Pnt2Trs1();	// ���������� � ����� �. ���
			break;
		}//*/
	}
	
	//if (n_Rslt==1)	// ���� ��������������� � ����� ����. ���
	{
		n_Rslt = Pnt2Tws2();	// ���������� � ����� ��
		if (n_Rslt==1)	
		{
			n_Rslt = Pnt2Trs2();	// ��� ����� �. ���
		}
	}

		return n_Rslt;
}


int MeshConstructor::Pnt2ScSt()
{
	int i,k;
	Vec3db dp,p1;
	double dr;
	ms1D<ScStPnt> *x;
	ScStPnt	*SSt;

	dst1= MY_INFINITY;
	x	= SRol->x[n_ScGr].Stbl;
	k	= 1;
	for(i=0;i<x->N;i++)
	{
		SSt	= &x->x[i];

		dp	= p_in-SSt->pc1;
		if(SSt->nst.scpr(dp)<SSt->d)
		{
			dp.nrml(dr);
			if(SSt->nst.scpr(dp)>SSt->csa)
			{
				if((SSt->n_tr.x[0]==-1)||(SSt->nc1.scpr(dp)>0))
				{
					dst1	-=sec_r;
					n_out	= dp;
					p_out	= SSt->pc1+dp*sec_r;
					k		= 0;

					type.x[0]	= ScStblSph1;
					type.x[1]	= i;
					type.x[2]	= n_ScGr;
				}
			}
		}else
		{
			dp	= p_in-SSt->pc2;
			dp.nrml(dr);
			if(-SSt->nst.scpr(dp)>SSt->csa)
			{
				if((SSt->n_tr.x[0]==-1)||(SSt->nc2.scpr(dp)>0))
				{
					dst1	-=sec_r;
					n_out	= dp;
					p_out	= SSt->pc2+dp*sec_r;
					k		= 0;

					type.x[0]	= ScStblSph2;
					type.x[1]	= i;
					type.x[2]	= n_ScGr;
				}
			}
		}
	}
	return k;
}

int MeshConstructor::Pnt2ScTr()
{
	int i,j,k;
	Vec3db dp,p1;
	bool ch;
	double dr;
	ms1D<ScTrPnt> *x;
	ScTrPnt	*STr;

	dst1= MY_INFINITY;
	x	= SRol->x[n_ScGr].Tris;
	k	= 1;
	for(i=0;i<x->N;i++)
	{
		STr	= &x->x[i];
		dp	= p_in-STr->pc;
		if(dp.scpr(STr->nr)<STr->nr.ssqr())
		{
			dp.nrml(dr);
			ch	= true;
			for(j=0;j<STr->mx->N;j++)
			{
				if (STr->mx->x[j].scpr(dp)<0) {ch = false; break;}
			}
			if((ch)&&(dst1>dr))
			{
				dst1	= dr;
				n_out	= dp;
				p_out	= STr->pc+dp*sec_r;
				k	= 0;
				
				type.x[0]	= ScTrisSphr;
				type.x[1]	= i;
				type.x[2]	= n_ScGr;
			}
		}
	}
	return k;
}


int MeshConstructor::Pnt2ScTw()
{
	int i;
	Vec3db dp,p1,dp1;
	double csa,csx,csy,csf;
	ms1D<ScTwPnt> *x;
	ScTwPnt	*STw;

	dst1= MY_INFINITY;
	x	= SRol->x[n_ScGr].Twos;
	for(i=0;i<x->N;i++)
	{
		STw	= &x->x[i];
		dp1	= p_in-STw->rp;
		csa	= STw->z.scpr(dp1);
		dp1	-=STw->z*csa;
		dp1.nrml();
		csx	= STw->x.scpr(dp1);
		csy	= STw->y.scpr(dp1);
		csf	= csy>0 ? csx+1 : -csx-1;
		if((STw->mx.x[1]>=csf)&&(csf>=STw->mx.x[0]))
		{
			p1	= STw->rp+dp1*STw->r_sc;
			dp	= p_in-p1;
			dp.nrml(dst1);
			csa	= -dp1.scpr(dp);
			if(STw->cs2<csa)
			{
				dst1	-=sec_r;
				n_out	= dp;
				p_out	= p1+dp*sec_r;

				type.x[0]	= ScTwosTor;
				type.x[1]	= i;
				type.x[2]	= n_ScGr;

				return 0;
			}
		}
	}
	return 1;
}

int MeshConstructor::Pnt2Srf2()
{
	int n_Rslt;
	sec_r	= sro.x[n_ScGr];
	n_Rslt	= Pnt2ScTw();
	if (n_Rslt!=0)
	{
		n_Rslt	= Pnt2ScSt();
		if (n_Rslt!=0)
		{
			n_Rslt	= Pnt2ScTr();
		}
	}
	return n_Rslt;
}

int MeshConstructor::Pnt2Surf()
{
	n_Rslt = Pnt2Srf1();		// �������� ���� ����
	if (n_Rslt==11)				// �� �������� ���� ���������
	{
		n_Rslt	= Pnt2Srf2();	// �������� ���� ����
	}	
	return n_Rslt;
}

int MeshConstructor::Pnt2Surf(Vec3db &p1,Vec3db &p2,Vec3db &n2,Vec3int &t)
{
	p_in	= p1;
	n_Rslt	= Pnt2Srf1();		// �������� ���� ����
	if (n_Rslt==11)				// �� �������� ���� ���������
	{
		n_Rslt	= Pnt2Srf2();	// �������� ���� ����
	}
	p2	= p_out;
	n2	= n_out;
	t	= type;
	return n_Rslt;
}

int MeshConstructor::Pnt2Surf(Vec3db &p1,Vec3db &p2,Vec3db &n2)
{
	p_in	= p1;
	n_Rslt	= Pnt2Srf1();		// �������� ���� ����
	if (n_Rslt==11)				// �� �������� ���� ���������
	{
		n_Rslt	= Pnt2Srf2();	// �������� ���� ����
	}

/*	if((p_in-p_out).norm()>0.1)
	{
		n_Rslt = Pnt2Srf1();		// �������� ���� ����
		if (n_Rslt==11)				// �� �������� ���� ���������
		{
			n_Rslt	= Pnt2Srf2();	// �������� ���� ����
		}
	}//*/

	p2	= p_out;
	n2	= n_out;
	return n_Rslt;
}


bool MeshConstructor::Pnt2Atom(Vec3db &p_in, Vec3db &p_out, Vec3db &nrm, double &sq_dst, int &infs, int &n_At)	// ���� ���'p_in' � �� 'n_At'
{
	int i,j;
	Vec3db dp,dpw;
	double csa,dr,dR,z,x,y;	
	bool ch;

	dp	= p_in-Atom.x[n_At].xyz;
	dp.nrml(dr);
	dR	= Atom.x[n_At].r_wdw+p_rol;
	
	ch	= true;
	
	for(i=0;i<Atom.x[n_At].csf.N;i++)
	{
		//if(infs==Atom.x[n_At].nfs.x[i])
		//{
		csa	= Atom.x[n_At].csf.x[i].scpr(dp);
		if (csa>Atom.x[n_At].mx.x[i]) return false;
		/*}else
		{
		csa	= Atom.x[n_At].csf.x[i].scpr(dp);
		if (csa>Atom.x[n_At].mx.x[i]) ch1.x[Atom.x[n_At].nfs.x[i]]	= false;
	}*/
	}
	ch = true;
	for(i=0;i<Atom.x[n_At].csf.N;i++)
	{
		j	= Atom.x[n_At].n_tw->x[i];
		dpw	= p_in-Twos->x[j].rp;
		z	= dpw.scpr(Twos->x[j].z);
		dpw	-=Twos->x[j].z*z;
		dpw.nrml();
		x	= dpw.scpr(Twos->x[j].x);
		y	= dpw.scpr(Twos->x[j].y);
		z	= y>0 ? x+1 : -x-1;		
		if(infs==Atom.x[n_At].nfs.x[i])
		{			
			if ((z<Twos->x[j].mx.x[0])||(z>Twos->x[j].mx.x[1]))
			{
				//ch	 = true;
				return false;
			}
		}
		/*if(infs!=Atom.x[n_At].nfs.x[i])
		{
			if ((z>Twos->x[j].mx.x[0])&&(z<Twos->x[j].mx.x[1]))
			{
				return false;
			}
		}*/
	}
	
	if (ch)
	{
		sq_dst	= dr-Atom.x[n_At].r_wdw;
		nrm		= dp;
		p_out	= Atom.x[n_At].xyz+dp*Atom.x[n_At].r_wdw;
		return true;
	}
	return false;

}

bool MeshConstructor::Pnt2Tris(Vec3db &p_in, double &sq_dst, int &n_Tr)	// ���� ���'p_in' � �. ���'n_Tr' �sq_dst ��� ������ �������. ���
{
	Vec3db dp;

	dp	= p_in-Tris->x[n_Tr].pc;
	dp.nrml(sq_dst);
	sq_dst	-= p_rol;

	if(Tris->x[n_Tr].mx->x[0].scpr(dp)<0) return false;
	if(Tris->x[n_Tr].mx->x[1].scpr(dp)<0) return false;
	if(Tris->x[n_Tr].mx->x[2].scpr(dp)<0) return false;

	for(int i=3;i<Tris->x[n_Tr].mx->N;i++)
	{
		if (Tris->x[n_Tr].mx->x[i].scpr(dp)<0) return false;
	}	
	return true;
}

bool MeshConstructor::Pnt2Twos(Vec3db &p_in, double &sq_dst, int &n_Tw)	// ���� ���� ��������� ��'n_Tw' �'sq_dst' ��� ������ �������� ��
{
	Vec3db dp,pc;
	double x,y,z,f,dr;

	dp	= p_in-Twos->x[n_Tw].rp;
	dp.nrml();

	x	= Twos->x[n_Tw].x.scpr(dp);
	y	= Twos->x[n_Tw].y.scpr(dp);
	z	= Twos->x[n_Tw].z.scpr(dp);

	if ((z<Twos->x[n_Tw].hab.x[1])||(z>Twos->x[n_Tw].hab.x[2])) return false;
	f	= y>0 ? x+1 : -x-1;
	if ((f<Twos->x[n_Tw].mx.x[0])||(f>Twos->x[n_Tw].mx.x[1])) return false;
	
	pc	= Twos->x[n_Tw].rp+Twos->x[n_Tw].x*Twos->x[n_Tw].hab.x[0]*x+Twos->x[n_Tw].y*Twos->x[n_Tw].hab.x[0]*y;
	dp	= p_in-pc;
	dp.nrml(dr);
	f = Twos->x[n_Tw].nc2.scpr(dp);
	if (f<Twos->x[n_Tw].cs2) return false;

	dr	-= p_rol;
	return true;
}


bool MeshConstructor::Pnt2ScTr(Vec3db &p_in, double &sq_dst, int & icg, int &n_Tr)	// ���� ���� ��������� �. �����. ����'n_Tw' �'sq_dst' ��� ������ �������� �. ���
{
	Vec3db dp;

	dp	= p_in-SRol->x[icg].Tris->x[n_Tr].pc;
	dp.nrml(sq_dst);
	sq_dst	-= p_rol;

	if(SRol->x[icg].Tris->x[n_Tr].mx->x[0].scpr(dp)<0) return false;
	if(SRol->x[icg].Tris->x[n_Tr].mx->x[1].scpr(dp)<0) return false;
	if(SRol->x[icg].Tris->x[n_Tr].mx->x[2].scpr(dp)<0) return false;

	for(int i=3;i<SRol->x[icg].Tris->x[n_Tr].mx->N;i++)
	{
		if (SRol->x[icg].Tris->x[n_Tr].mx->x[i].scpr(dp)<0) return false;
	}	
	return true;
}

void MeshConstructor::DefCubNmb(Vec3db &p)	// ����� ����������� ���'p'
{
	ix	= (int)((p.x[0]-cbs.cnrMin.x[0])/cbs.cubsz);
	iy	= (int)((p.x[1]-cbs.cnrMin.x[1])/cbs.cubsz);
	iz	= (int)((p.x[2]-cbs.cnrMin.x[2])/cbs.cubsz);

	ix	= (ix<=0) ? 0 : (ix>=cbs.nx) ? cbs.nx-1 : ix;
	iy	= (iy<=0) ? 0 : (iy>=cbs.ny) ? cbs.ny-1 : iy;
	iz	= (iz<=0) ? 0 : (iz>=cbs.nz) ? cbs.nz-1 : iz;

	ii	= ix+cbs.nx*(iy+cbs.ny*iz);
}

void MeshConstructor::SetNC_At()			// ����� ��������� �����������������
{
	int i,j;
	NC_At.init(Atom.N);
	NC_At	= 0;
	for(i=0;i<AtmCnnNmb.N;i++)
	{
		for(j=0;j<AtmCnnNmb.x[i].N;j++)
		{
			NC_At.x[AtmCnnNmb.x[i].x[j]]++;
		}
	}
}

void MeshConstructor::SetC_At(int &infs)	// ����� �������������� �������
{
	int j,k;
	C_At.init(Atom.N);
	C_At	= IND_NONTR_ATOM;
	for(j=0;j<Atom.N;j++)
	{
		if(S_At.x[j]!=IND_NONTR_ATOM)
		{
			if (Atom.x[j].nfs.N>0)
			{
				for(k=0;k<Atom.x[j].nfs.N;k++)
				{
					if(Atom.x[j].nfs.x[k]==infs)
					{
						C_At.x[j] = IND_SURF_ATOM;
						break;
					}
				}
			}
		}
	}
}

void MeshConstructor::SetAtCmx(int &infs)	// ����� �������������� �������
{
	int i,j,k,j1,i1;

	for(i=0;i<AtmCnnNmb.x[infs].N;i++)
	{
		j	= AtmCnnNmb.x[infs].x[i];
		Atom.x[j].c_un->N	= 0;
		k	= Atom.x[j].nfs.fnd(infs);
		Atom.x[j].cfs	= k;
		if (k!=-1)
		{
			Atom.x[j].mx.ind(Atom.x[j].set_ntw.x[k],Atom.x[j].mx_c);
			Atom.x[j].csf.ind(Atom.x[j].set_ntw.x[k],Atom.x[j].csf_c);

			for(i1=0;i1<Atom.x[j].n_un->N;i1++)
			{
				j1	= Atom.x[j].n_un->x[i1];
				k	= Atom.x[j1].nfs.fnd(infs);
				if (k!=-1)
				{
					Atom.x[j].c_un->add(j1);
				}
			}
		}else{cout<<"Error in \"SetAtCmx\" incorrect data in field \"nfs\" of \"Atom\" class. \n Programm stoped."<<endl;}
	}

	for(i=0;i<cbs.n_at.N;i++)
	{
		for(j=0;j<cbs.n_at.x[i].N;j++)
		{
			j1	= cbs.n_at.x[i].x[j];
			k	= Atom.x[j1].nfs.fnd(infs);
			if(k!=-1)
			{
				cbs.c_at.x[i].add(j1);
			}
		}
	}
}

int MeshConstructor::DefNearAt(Vec3db &p)	// ����� ������������ ���'p' (�� � ������ 'ii')
{
	int i,j,k;
	double drc,drm;
	ms1Dint *x;
	j	= -1;
	drm	= MY_INFINITY;

	if (cbs.c_at.x[ii].N!=0)
	{
		x	= &cbs.c_at.x[ii];
		for(i=0;i<x->N;i++)
		{
			drc	= (p-Atom.x[x->x[i]].xyz).norm()-Atom.x[x->x[i]].r_wdw;
			if (drm>drc) {drm = drc; j = x->x[i];}
		}
		x	= Atom.x[j].c_un;
		k	= j;
		for(i=0;i<x->N;i++)
		{
			drc	= (p-Atom.x[x->x[i]].xyz).norm()-Atom.x[x->x[i]].r_wdw;
			if (drm>drc) {drm = drc; j = x->x[i];}
		}
		if (k!=j)
		{
			k	= j;
			x	= Atom.x[j].c_un;
			for(i=0;i<x->N;i++)
			{
				drc	= (p-Atom.x[x->x[i]].xyz).norm()-Atom.x[x->x[i]].r_wdw;
				if (drm>drc) {drm = drc; j = x->x[i];}
			}
			if (k!=j)
			{
				k	= j;
				x	= Atom.x[j].c_un;
				for(i=0;i<x->N;i++)
				{
					drc	= (p-Atom.x[x->x[i]].xyz).norm()-Atom.x[x->x[i]].r_wdw;
					if (drm>drc) {drm = drc; j = x->x[i];}
				}
				if (k!=j)
				{
					k	= j;
					x	= Atom.x[j].c_un;
					for(i=0;i<x->N;i++)
					{
						drc	= (p-Atom.x[x->x[i]].xyz).norm()-Atom.x[x->x[i]].r_wdw;
						if (drm>drc) {drm = drc; j = x->x[i];}
					}
					if (k!=j)
					{
						j	= GlobDefAt(p);
					}
				}
				cbs.c_at.x[ii].add(j);
				cbs.c_at.x[ii].sort();
			}
		}

		if(drm>2*p_rol)
		{
			i	= GlobDefAt(p);
			if (i!=k)
			{
				Atom.x[k].c_un->add(i);
				Atom.x[i].c_un->add(k);
				Atom.x[k].c_un->sort();
				Atom.x[i].c_un->sort();
				Atom.x[k].n_un->add(i);
				Atom.x[i].n_un->add(k);
				Atom.x[k].n_un->sort();
				Atom.x[i].n_un->sort();
				if (i<k) 
				{
					Atom.x[i].n_ge->add(k);
					Atom.x[i].n_ge->sort();
				}else
				{
					Atom.x[k].n_ge->add(i);
					Atom.x[k].n_ge->sort();
				}
			}
			j	= i;
		}//*/
	}
	else
	{
		j	= GlobDefAt(p);
		cbs.c_at.x[ii].add(j);
		cbs.c_at.x[ii].sort();
	}


	return j;

	/*x	= &cbs.n_at.x[ii];
	for(i=0;i<x->N;i++)
	{
		if(C_At.x[x->x[i]]!=IND_NONTR_ATOM)
		{
			drc	= (p-Atom.x[x->x[i]].xyz).norm()-Atom.x[x->x[i]].r_wdw;
			if (drm>drc) {drm = drc; j = x->x[i];}
		}
	}
	if (j==-1) return DefExpdAt(p);
	x	= Atom.x[j].n_un;
	for(i=0;i<x->N;i++)
	{
		if(C_At.x[x->x[i]]!=IND_NONTR_ATOM)
		{
			drc	= (p-Atom.x[x->x[i]].xyz).norm()-Atom.x[x->x[i]].r_wdw;
			if (drm>drc) {drm = drc; j = x->x[i];}
		}
	}
	
	return j;*/
	//return drm<0.2*p_rol ? j : DefExpdAt(p);
}
int MeshConstructor::DefExpdAt(Vec3db &p)
{
	int iiz,iiy,iix,iii;
	ms1Dint n_NearAt;
	int i,j;
	double drc,drm;

	for (iiz=iz-1;iiz<=iz+1;iiz++)
			if ((iiz>=0)&&(iiz<cbs.nz))
			for (iiy=iy-1;iiy<=iy+1;iiy++)
				if ((iiy>=0)&&(iiy<cbs.ny))
				for (iix=ix-1;iix<=ix+1;iix++)
					if ((iix>=0)&&(iix<cbs.nx))
					{
						iii	= iix+cbs.nx*(iiy+cbs.ny*iiz);
						n_NearAt.add(cbs.n_at.x[iii]);		// ����� ������� � ���� ��������
					}	
	j	= -1;
	drm	= MY_INFINITY;
	for(i=0;i<n_NearAt.N;i++)
	{
		iii = n_NearAt.x[i];
		if(C_At.x[iii]!=IND_NONTR_ATOM)
		{
			drc	= (p-Atom.x[iii].xyz).norm()-Atom.x[iii].r_wdw;
			if (drm>drc) {drm = drc; j = iii;}
		}
	}
	if (j==-1) return GlobDefAt(p);
	return j;
}
int MeshConstructor::GlobDefAt(Vec3db &p)	// ����� ������������ ���'p' (����� �������)
{
	int i,j,k;
	double drc,drm;
	j	= -1;
	drm	= MY_INFINITY;
	for(i=0;i<AtmCnnNmb.x[n_un_srf].N;i++)
	{
		k	= AtmCnnNmb.x[n_un_srf].x[i];
		drc	= (p-Atom.x[k].xyz).norm()-Atom.x[k].r_wdw;
		if (drm>drc) {drm = drc; j = k;}
	}
	return j;
}

/*bool MeshConstructor::Pnt2TrNm(Vec3db &p_in,Vec3db &n_in,Vec3db &p_out,Vec3db &n_out,Vec3int &type)	// ��� ���� ������ ���� ����� ��������� 
{
	int i,j,k;
	double min;
	bool ch;

	ch	= Tris->x[x->x[i]].Pnt2Surf(p_in,p_out,n_out,dst,p_rol,type.x[2]);
}*/


bool MeshConstructor::Pnt2AtNm(Vec3db &p_in,Vec3db &n_in,Vec3db &p_out,Vec3db &n_out,Vec3int &type)	// ��� ���� ������ ���� ����� ��������� 
{
	int i,k;
	double min;
	bool ch;
	ms1Dint *x;
	Vec3db p_cr,n_cr;

	ch	= Atom.x[type.x[1]].Pnt2Surf(p_in,p_out,n_out,dst,p_rol,type.x[2]);	// ���� ���� ��������� ��.
	min	= dst;
	if (!ch)
	{
		x	= Atom.x[n_At].n_tw;	// ���� � ��� ����������
		for(i=0;i<x->N;i++)
		{
			ch	= Twos->x[x->x[i]].Pnt2Surf(p_in,p_out,n_out,dst,p_rol,type.x[2]);
			if (ch)
			{
				// ���� �����
				type.x[0]	= 2; //���� � �������������������������� ��
				type.x[1]	= x->x[i];	// �����
				//type.x[2]	= 0; // ??? �� ����� ������� ���������� (�� igr)			
				return true;
			}
		}
		x	= Atom.x[n_At].n_tr;
		
		//min	= -INFINITY;
		k	=-1;
		for(i=0;i<x->N;i++)	// ����� �����. ���
		{		
			ch	= Tris->x[x->x[i]].Pnt2Surf(p_in,p_out,n_out,dst,p_rol,type.x[2]);
			if (ch)
			{
			/*if(dst>=-s_rol)	- ����������� ��� � �������. ���
			{
			// ���� �����
			type.x[0]	= 1; //���� � ����. ���
			type.x[1]	= x->x[i];	// �����
			return true;
			}*/
				if(dst>min)
				{
					k	= x->x[i];
					min	= dst;
				}
			}
		}
		ch	= false;
		if (k!=-1)
		{
			ch	= Tris->x[k].Pnt2Surf(p_in,p_out,n_out,dst,p_rol,type.x[2]);
			type.x[0]	= 1; //���� � ����. ���
			type.x[1]	= k;	// ���;
			return true;
		}/*else
		{
			ch	= Pnt2PrRl_(p_in,n_in,p_out,n_out,type);
			if (!ch)
			{
				ch	= Pnt2PrRl(p_in,n_in,p_out,n_out,type);
			}
		}*/

	}
	return ch;
}

bool MeshConstructor::Pnt2TrNm(Vec3db &p_in,Vec3db &n_in,Vec3db &p_out,Vec3db &n_out,Vec3int &type)	// ��� ���� ������ ���� ����� ��������� 
{
	/*int i,k;
	double min;
	bool ch;
	ms1Dint *x;
	Vec3db p_cr,n_cr;/**/

	return false;
}

bool MeshConstructor::Pnt2PrRl_(Vec3db &p_in,Vec3db &n_in,Vec3db &p_out,Vec3db &n_out,Vec3int &type)	// ��� ���� ������ ���� ����� ��������� 
{
	int i,j,k;
	double min;
	bool ch;
	ms1Dint *x;
	Vec3db p_cr,n_cr;
	
	n_At	= type.x[1]; 
	x	= Atom.x[n_At].n_tws;	// ���� � ��� �������� ����������
	for(i=0;i<x->N;i++)
	{
		ch	= Twos->x[x->x[i]].Pnt2Surf(p_in,p_out,n_out,dst,p_rol,type.x[2]);
		if (ch)
		{
			// ���� �����
			type.x[0]	= 2; //���� � �������������������������� ��
			type.x[1]	= x->x[i];	// �����
			//type.x[2]	= 0; // ??? �� ����� ������� ���������� (�� igr)			
			return true;
		}
	}
	
	// � ����� ������� � �.
	

	min	= MY_INFINITY;
	j	= -1;
	ch	= Atom.x[n_At].Pnt2Surf(p_in,p_out,n_out,dst,p_rol,type.x[2]);	// ���� ���� ��������� ��.
	if (ch)
	{
		/*if (dst<=p_rol)
		{
			// ���� �����
			type.x[0]	= 0; //���� � ��
			type.x[1]	= n_At;	// ������
			//type.x[2]	= 0; // ??? �� ����� ������o����������� (�� igr)
			return true;
		}else*/
		{
			min	= dst;
			j	= n_At;
		}
	}
	// ���� ����� ��

	x	= Atom.x[n_At].n_un;	
	for(i=0;i<x->N;i++)	// �� � �� ���� ���
	{
		k	= x->x[i];
		if (C_At.x[k]!=IND_NONTR_ATOM)
		{
			ch = Atom.x[k].Pnt2Surf(p_in,p_out,n_out,dst,p_rol,type.x[2]);
			if (ch)
			{
				/*if (dst<=p_rol)
				{
					// ���� �����
					type.x[0]	= 0; //���� � ��
					type.x[1]	= k;	// ������
					return true;
				}*/
				if(dst<min)
				{
					min = dst;
					j	= k;
				}
			}
		}
	}	

	/*if (j!=-1)
	{
		Atom.x[j].Pnt2Surf(p_in,p_out,n_out,dst,p_rol,type.x[2]);
		type.x[0]	= 0; //���� � ��
		type.x[1]	= j;	// ������
		return true;
	}*/	

	x	= Atom.x[n_At].n_trs;
	//min	= -INFINITY;
	min = -min;
	k	=-1;
	for(i=0;i<x->N;i++)	// ����� ���. ���
	{		
		ch	= Tris->x[x->x[i]].Pnt2Surf(p_in,p_out,n_out,dst,p_rol,type.x[2]);
		if (ch)
		{
			/*if(dst>=-s_rol)	- ����������� ��� � �������. ���
			{
				// ���� �����
				type.x[0]	= 1; //���� � ����. ���
				type.x[1]	= x->x[i];	// �����
				return true;
			}*/
			if(dst>min)
			{
				k	= x->x[i];
				min	= dst;
			}
		}
	}

	//�� � �������� � ������ ���� ��������(������ ��������?? - ���� �������� ��������  - ������������ � ���� ����. ���� �����
	if (k==-1)
	{
		if(j!=-1)
		{	
			Atom.x[j].Pnt2Surf(p_in,p_out,n_out,dst,p_rol,type.x[2]);
			type.x[0]	= 0; //���� � ��
			type.x[1]	= j;	// ������	
			return true;
		}
	}else
	{
		ch	= Tris->x[k].Pnt2Surf(p_in,p_out,n_out,dst,p_rol,type.x[2]);
		type.x[0]	= 1; //���� � ����. ���
		type.x[1]	= k;	// ���;
		return true;
	}	
	return false;
}


bool MeshConstructor::Pnt2PrRl(Vec3db &p_in,Vec3db &n_in,Vec3db &p_out,Vec3db &n_out,Vec3int &type)	// ��� ���� ������ ���� ����� ��������� 
{
	int i,j,k;
	double min;
	bool ch;
	ms1Dint *x;
	Vec3db p_cr,n_cr;
	
	/*if (n_in.x[0]==1e10)
	{
		cout<<p_in;
	}*/
	DefCubNmb(p_in);	// ������������ �����������p_in
	/*n_At	= DefNearAt(p_in);	// ���� �� 	

	this->p_in	= p_in;
	n_Rslt	= Pnt2Surf();//*/

	n_At	= DefExpdAt(p_in);	// ���� �� 	
	/*if (n_in.x[0]==1e10)
	{
		cout<<ii<<endl;
		cout<<n_At<<endl;
		time	= clock();
		time	= clock()- time;
		time1	+= time;
	}*/





	if (n_At==-1){n_At	= GlobDefAt(p_in);}		// ����������������.
	//n_At	= GlobDefAt(p_in);		
	x	= Atom.x[n_At].n_tws;	// ���� � ��� �������� ����������
	for(i=0;i<x->N;i++)
	{
		ch	= Twos->x[x->x[i]].Pnt2Surf(p_in,p_out,n_out,dst,p_rol,type.x[2]);
		if (ch)
		{
			// ���� �����
			type.x[0]	= 2; //���� � �������������������������� ��
			type.x[1]	= x->x[i];	// �����
			//type.x[2]	= 0; // ??? �� ����� ������� ���������� (�� igr)			
			return true;
		}
	}
	
	// � ����� ������� � �.
	

	min	= MY_INFINITY;
	j	= -1;
	ch	= Atom.x[n_At].Pnt2Surf(p_in,p_out,n_out,dst,p_rol,type.x[2]);	// ���� ���� ��������� ��.
	if (ch)
	{
		/*if (dst<=p_rol)
		{
			// ���� �����
			type.x[0]	= 0; //���� � ��
			type.x[1]	= n_At;	// ������
			//type.x[2]	= 0; // ??? �� ����� ������o����������� (�� igr)
			return true;
		}else*/
		{
			min	= dst;
			j	= n_At;
		}
	}
	// ���� ����� ��

	x	= Atom.x[n_At].n_un;	
	for(i=0;i<x->N;i++)	// �� � �� ���� ���
	{
		k	= x->x[i];
		if (C_At.x[k]!=IND_NONTR_ATOM)
		{
			ch = Atom.x[k].Pnt2Surf(p_in,p_out,n_out,dst,p_rol,type.x[2]);
			if (ch)
			{
				/*if (dst<=p_rol)
				{
					// ���� �����
					type.x[0]	= 0; //���� � ��
					type.x[1]	= k;	// ������
					return true;
				}*/
				if(dst<min)
				{
					min = dst;
					j	= k;
				}
			}
		}
	}	

	/*if (j!=-1)
	{
		Atom.x[j].Pnt2Surf(p_in,p_out,n_out,dst,p_rol,type.x[2]);
		type.x[0]	= 0; //���� � ��
		type.x[1]	= j;	// ������
		return true;
	}*/	

	x	= Atom.x[n_At].n_trs;
	//min	= -INFINITY;
	min = -min;
	k	=-1;
	for(i=0;i<x->N;i++)	// ����� ���. ���
	{		
		ch	= Tris->x[x->x[i]].Pnt2Surf(p_in,p_out,n_out,dst,p_rol,type.x[2]);
		if (ch)
		{
			/*if(dst>=-s_rol)	- ����������� ��� � �������. ���
			{
				// ���� �����
				type.x[0]	= 1; //���� � ����. ���
				type.x[1]	= x->x[i];	// �����
				return true;
			}*/
			if(dst>min)
			{
				k	= x->x[i];
				min	= dst;
			}
		}
	}

	//�� � �������� � ������ ���� ��������(������ ��������?? - ���� �������� ��������  - ������������ � ���� ����. ���� �����
	if (k==-1)
	{
		if(j!=-1)
		{	
			Atom.x[j].Pnt2Surf(p_in,p_out,n_out,dst,p_rol,type.x[2]);
			type.x[0]	= 0; //���� � ��
			type.x[1]	= j;	// ������	
			return true;
		}
	}else
	{
		ch	= Tris->x[k].Pnt2Surf(p_in,p_out,n_out,dst,p_rol,type.x[2]);
		type.x[0]	= 1; //���� � ����. ���
		type.x[1]	= k;	// ���;
		return true;
	}	
	return false;
}

bool MeshConstructor::Pnt2Surf(Vec3db &p_in,Vec3db &n_in,Vec3db &p_out,Vec3db &n_out,Vec3int &type)	// ��� ���� ������ ���� �����. 
{
	double dst;
	Vec3db _p_out,_n_out;
	int tp1,tp0; 
	bool ch;

	ch	= Pnt2PrRl(p_in,n_in,p_out,n_out,type);
 	if(ch)
	{
		switch (type.x[0])
		{
		case	0:	//���� � ��
			if (NC_At.x[type.x[1]]!=1)
			{
				if ((p_out-p_in).norm()>0.5) return false;
				//��� ���� � ����� ���� � �� ��������� ���������������
				//Pnt2Atom(p_in,p_out,n_out,dst,type.x[2],type.x[1])
			}
			return true;
		case	1:	//���� � �. ���
			if(Tris->x[type.x[1]].igr!=-1)
			{
				// �������� ���� ����
				dst	= s_rol;
				if(SRol->x[Tris->x[type.x[1]].igr].Pnt2Surf(p_in,_p_out,_n_out,dst,tp0,tp1)) //
				{
//					SRol->x[Tris->x[type.x[1]].igr].Pnt2Surf(p_in,_p_out,_n_out,dst,tp0,tp1);
					p_out	= _p_out;
					n_out	= _n_out;
					type.x[1]=tp1;
					type.x[0]=tp0;
				}
			}
			return true;
		case	2:	//���� � �
			if(Twos->x[type.x[1]].igr!=-1)
			{
				// �������� ���� ����
				dst	= s_rol;
				if(SRol->x[Twos->x[type.x[1]].igr].Pnt2Surf(p_in,_p_out,_n_out,dst,tp0,tp1))
				{
					p_out	= _p_out;
					n_out	= _n_out;
					type.x[1]= tp1;
					type.x[0]= tp0;
				}
			}
			return true;			
		}
	}else
	{
		ch	= Pnt2PrRl(p_in,n_in,p_out,n_out,type);
	}
	return ch;
}

bool MeshConstructor::Pnt2Surf_(Vec3db &p_in,Vec3db &n_in,Vec3db &p_out,Vec3db &n_out,Vec3int &type)	// ��� ���� ������ ���� �����. 
{
	bool ch;
	switch (type.x[0])
	{
		case	0:	//���� � ��
			ch	= Pnt2AtNm(p_in,n_in,p_out,n_out,type);
			break;
		/*case	1:	//���� � �. ���
			ch	= Pnt2TrNm(p_in,n_in,p_out,n_out,type);
			break;
		case	2:	//���� � �
			break;
		case	3:
			break;
		case	4:
			break;
		case	5:
			break;
		case	6:
			break;*/
		default :
			return Pnt2Surf(p_in,n_in,p_out,n_out,type);
	}
	if ((ch)&&type.x[0]!=0)
		return Pnt2Surf(p_in,n_in,p_out,n_out,type);
	else return true;
	return false;
}


void MeshConstructor::AddPntCbs(Vec3db &p_in,const int &n_pnt) // ��� ����� ��� �� ����� ������������������� ���� �����
{	
	ix	= (int)((p_in.x[0]-cbs.cnrMin.x[0])/cbs.cubsz);
	iy	= (int)((p_in.x[1]-cbs.cnrMin.x[1])/cbs.cubsz);
	iz	= (int)((p_in.x[2]-cbs.cnrMin.x[2])/cbs.cubsz);

	ix	= (ix<=0) ? 0 : (ix>=cbs.nx) ? cbs.nx-1 : ix;
	iy	= (iy<=0) ? 0 : (iy>=cbs.ny) ? cbs.ny-1 : iy;
	iz	= (iz<=0) ? 0 : (iz>=cbs.nz) ? cbs.nz-1 : iz;

	ii	= ix+cbs.nx*(iy+cbs.ny*iz);

	cbs.n_sp.x[ii].add(n_pnt);
	if (Point.N>=Point.mN) Point.adm_(AddQuantPnt);
	Point.x[n_pnt].cbn	= ii;
	Point.x[n_pnt].n_cbs->add(ii);
	
	ix_	= ix>=(cbs.nx-1)?cbs.nx:ix+2;
	iy_	= iy>=(cbs.ny-1)?cbs.ny:iy+2;
	iz_	= iz>=(cbs.nz-1)?cbs.nz:iz+2;
	i_x	= ix<=0?0:ix-1;
	i_y	= iy<=0?0:iy-1;
	i_z	= iz<=0?0:iz-1;	
	for (iiz=i_z;iiz<iz_;iiz++)
	{
		cb_crd.x[2]	= p_in.x[2]-(cbs.cnrMin.x[2]+iiz*cbs.cubsz);
		cb_crd.x[2]	+=R_expd;
		for(iiy=i_y;iiy<iy_;iiy++)
		{
			cb_crd.x[1]	= p_in.x[1]-(cbs.cnrMin.x[1]+iiy*cbs.cubsz);
			cb_crd.x[1]	+=R_expd;
			for(iix=i_x;iix<ix_;iix++)
			{
				ii_	= iix+cbs.nx*(iiy+cbs.ny*iiz);
				cb_crd.x[0]	= p_in.x[0]-(cbs.cnrMin.x[0]+iix*cbs.cubsz);
				cb_crd.x[0]	+=R_expd;

				if ((cb_crd.x[0]>=0)&&(cb_crd.x[1]>=0)&&(cb_crd.x[2]>=0)&&(cb_crd.x[0]<=sp)&&(cb_crd.x[1]<=sp)&&(cb_crd.x[2]<=sp)&&(ii!=ii_))
				{	
					cbs.n_sp.x[ii_].add(n_pnt);
					Point.x[n_pnt].n_cbs->add(ii_);
				}else
				{
					if ( ((iix==0)&&(cb_crd.x[0]<0)) || ((iix==cbs.nx-1)&&(cb_crd.x[0]>sp)) || ((iiy==0)&&(cb_crd.x[1]<0)) || ((iiy==cbs.ny-1)&&(cb_crd.x[1]>sp)) || ((iiz==0)&&(cb_crd.x[2]<0)) || ((iiz==cbs.nz-1)&&(cb_crd.x[2]>sp)) )
					{
						cbs.n_sp.x[ii_].add(n_pnt);
						Point.x[n_pnt].n_cbs->add(ii_);
					}
				}
			}
		}
	}
}



void MeshConstructor::TrInit(int n_srf)	// ����������� �����
{
	double ampl,dr,drm;	
	const double cs	= cos(2*pi/3);	// ����120 ����. ������ ������� ��� ���� � ����� �������������.
	const double sn	= sin(2*pi/3);	
	Mtr3db Sr;
	Vec3db r,r1,r2,r3,n,n1,n2,n3,p1,p2,p3;
	Vec3int t1,t2,t3;

	int i,im;

	type		= 0;
	n_un_srf	= n_srf;

	SetAtCmx(n_un_srf);
	SetNC_At();
	SetC_At(n_un_srf);

	R_high	= 1.5*R_crcl; 	// ��� ��� ������
	R_expd	= 2*R_crcl;	// ��� ������������ - � ���������
	
	/*Theta	= -1.0;
	Phi		= 1.5;/*/

	Theta	= 0.0;
	Phi		= 0.0;


	sp		= cbs.cubsz+2*R_expd;

	B1.sm(1);
	B2.sm(1);
	//-----------------

	t1	= t2 = t3 = type;

	ampl	= 2*cbs.cnrMin.norm();

	r.x[0]	= ampl*cos(Theta)*cos(Phi);
	r.x[1]	= ampl*cos(Theta)*sin(Phi);
	r.x[2]	= ampl*sin(Theta);

	drm	= 10*ampl;
	if(TrsCnnNmb.x[n_un_srf].N!=0)
	{
		for(i=0;i<TrsCnnNmb.x[n_un_srf].N;i++)
		{
			r1	= r-Tris->x[TrsCnnNmb.x[n_un_srf].x[i]].pc;
			r1.nrml(dr);
			if(dr<drm)
			{
				drm	= dr;
				im	= i;
			}
		}
		r1	= r-Tris->x[TrsCnnNmb.x[n_un_srf].x[im]].pc;
		r1.nrml(dr);
		r	= Tris->x[TrsCnnNmb.x[n_un_srf].x[im]].pc+p_rol*r1;
	}else
	{
		for(i=0;i<AtmCnnNmb.x[n_un_srf].N;i++)
		{
			r1	= r-Atom.x[AtmCnnNmb.x[n_un_srf].x[i]].xyz;
			r1.nrml(dr);
			if(dr<drm)
			{
				drm	= dr;
				im	= i;
			}
		}
		r1	= r-Atom.x[AtmCnnNmb.x[n_un_srf].x[im]].xyz;
		r1.nrml(dr);
		r	= Atom.x[AtmCnnNmb.x[n_un_srf].x[im]].xyz+Atom.x[AtmCnnNmb.x[n_un_srf].x[im]].r_wdw;
	}
		
	Pnt2Surf(r,r1,n3,t1);
	r	= r1;

	if (n3.x[0]!=0)
	{
		n1.x[2]	= 0;
		n1.x[1]	= 1/sqrt(1+n3.x[1]*n3.x[1]/(n3.x[0]*n3.x[0]));
		n1.x[0]	= -n1.x[1]*n3.x[1]/n3.x[0];
	}else
	{		
		n1.x[0]	= 1.0;
		n1.x[1]	= 0.0;
		n1.x[2]	= 0.0;
	}

	n2.crss(n3,n1);
	Sr	= Mtr3db(cs,-sn,0,sn,cs,0,0,0,1);	// �������� � 120 ����

	p1	= 0;
	p1.x[0]	= R_crcl; // ��������������������� �������� �����������'r0'.

	Sr.pmv(p2,p1);
	Sr.pmv(p3,p2);

	// ��������� ���� � ����� ��� ���������, �������� ���������
	Sr.x[0]=n1.x[0];Sr.x[1]=n2.x[0];Sr.x[2]=n3.x[0];
	Sr.x[3]=n1.x[1];Sr.x[4]=n2.x[1];Sr.x[5]=n3.x[1];
	Sr.x[6]=n1.x[2];Sr.x[7]=n2.x[2];Sr.x[8]=n3.x[2];
	//����� ����
	n	= n3;
	// ��������� ���������� ����� ���.
	Sr.pmv(r1,p1)+=r;
	Sr.pmv(r2,p2)+=r;
	Sr.pmv(r3,p3)+=r;
	// ������������ �����.
	Pnt2Surf(r1,p1,n1,t1);
	Pnt2Surf(r2,p2,n2,t2);
	Pnt2Surf(r3,p3,n3,t3);	
	// ������ ��� 'surf' - �����, ��� ���� ��, ��� � ��� ������.
	TrSurface::init(p1,p2,p3,n1,n2,n3,t1,t2,t3);

	AddPntCbs(p1,0);
	AddPntCbs(p2,1);
	AddPntCbs(p3,2);
}



void MeshConstructor::TrInit()	// ����������� �����
{
	double ampl,dr,drm;	
	const double cs	= cos(2*pi/3);	// ����120 ����. ������ ������� ��� ���� � ����� �������������.
	const double sn	= sin(2*pi/3);	
	Mtr3db Sr;
	Vec3db r,r1,r2,r3,n,n1,n2,n3,p1,p2,p3;
	Vec3int t1,t2,t3;

	int i,im;

	// ���� ��� ��������
	time1	= 0;

	type		= 0;
	n_un_srf	= 0;

	SetAtCmx(n_un_srf);

	SetNC_At();
	SetC_At(n_un_srf);

//	Cube2File(133);
	

	//R_crcl	= 0.5;
	R_high	= 1.5*R_crcl; 	// ��� ��� ������
	R_expd	= 2*R_crcl;	// ��� ������������ - � ���������
	
	Theta	= -1.0;
	Phi		= 1.5;
	sp		= cbs.cubsz+2*R_expd;

	B1.sm(1);
	B2.sm(1);
	//-----------------

	t1	= t2 = t3 = type;

	ampl	= 2*cbs.cnrMin.norm();

	r.x[0]	= ampl*cos(Theta)*cos(Phi);
	r.x[1]	= ampl*cos(Theta)*sin(Phi);
	r.x[2]	= ampl*sin(Theta);

	drm	= 10*ampl;
	if(TrsCnnNmb.x[n_un_srf].N!=0)
	{
		for(i=0;i<TrsCnnNmb.x[n_un_srf].N;i++)
		{
			r1	= r-Tris->x[TrsCnnNmb.x[n_un_srf].x[i]].pc;
			r1.nrml(dr);
			if(dr<drm)
			{
				drm	= dr;
				im	= i;
			}
		}
		r1	= r-Tris->x[TrsCnnNmb.x[n_un_srf].x[im]].pc;
		r1.nrml(dr);
		r	= Tris->x[TrsCnnNmb.x[n_un_srf].x[im]].pc+p_rol*r1;
	}else
	{
		for(i=0;i<AtmCnnNmb.x[n_un_srf].N;i++)
		{
			r1	= r-Atom.x[AtmCnnNmb.x[n_un_srf].x[i]].xyz;
			r1.nrml(dr);
			if(dr<drm)
			{
				drm	= dr;
				im	= i;
			}
		}
		r1	= r-Atom.x[AtmCnnNmb.x[n_un_srf].x[im]].xyz;
		r1.nrml(dr);
		r	= Atom.x[AtmCnnNmb.x[n_un_srf].x[im]].xyz+Atom.x[AtmCnnNmb.x[n_un_srf].x[im]].r_wdw;
	}

//	DefCubNmb(r);


//	r.x[0]	= -22.0;
//	r.x[1]	= 13.2;
//	r.x[2]	= -22.2;

		
	Pnt2Surf(r,r1,n3,t1);
	r	= r1;

	// ���� ���� ���� ��������� ��� �� ���� �� ���. (� ���� ����� ������)
	// ����������� ���
	if (n3.x[0]!=0)
	{
		n1.x[2]	= 0;
		n1.x[1]	= 1/sqrt(1+n3.x[1]*n3.x[1]/(n3.x[0]*n3.x[0]));
		n1.x[0]	= -n1.x[1]*n3.x[1]/n3.x[0];
	}else
	{		
		n1.x[0]	= 1.0;
		n1.x[1]	= 0.0;
		n1.x[2]	= 0.0;
	}

	n2.crss(n3,n1);
	//crs(n3,n1,n2);
	//----
	//R	= trsize(r);
	
	Sr	= Mtr3db(cs,-sn,0,sn,cs,0,0,0,1);	// �������� � 120 ����

	p1	= 0;
	p1.x[0]	= R_crcl; // ��������������������� �������� �����������'r0'.

	Sr.pmv(p2,p1);
	Sr.pmv(p3,p2);

	// ��������� ���� � ����� ��� ���������, �������� ���������
	Sr.x[0]=n1.x[0];Sr.x[1]=n2.x[0];Sr.x[2]=n3.x[0];
	Sr.x[3]=n1.x[1];Sr.x[4]=n2.x[1];Sr.x[5]=n3.x[1];
	Sr.x[6]=n1.x[2];Sr.x[7]=n2.x[2];Sr.x[8]=n3.x[2];
	//����� ����
	n	= n3;
	// ��������� ���������� ����� ���.
	Sr.pmv(r1,p1)+=r;
	Sr.pmv(r2,p2)+=r;
	Sr.pmv(r3,p3)+=r;
	// ������������ �����.
	Pnt2Surf(r1,p1,n1,t1);
	Pnt2Surf(r2,p2,n2,t2);
	Pnt2Surf(r3,p3,n3,t3);	
	// ������ ��� 'surf' - �����, ��� ���� ��, ��� � ��� ������.
	TrSurface::init(p1,p2,p3,n1,n2,n3,t1,t2,t3);

	AddPntCbs(p1,0);
	AddPntCbs(p2,1);
	AddPntCbs(p3,2);
}


void MeshConstructor::Build ()	// ���� ��������� �� ����� �����������
{
	// �����
	int i,j,k;		// - �������������� ���� ��������

	int i_main;		// - ����� ��������
	int i_setb;		// - ��� ��������� �������.
	int i_bndr;		// - ��� ��������� ���
	int len_sb;		// - ������������ �������.
	int method;		// - ����������������� ���

	int iEdgCr;		// - ��� ��������� ���
	int iEdgPr;		// - ��� ���������� ���
	int iEdgNx;		// - ��� ����������� ���

	int iTriCr;		// - ��� ��������� ������.
	int iTriPr;		// - ��� ���������� ������.
	int iTriNx;		// - ��� ����������� ������.
	int iTriMx;		// - ��� �����������

	int iPntTr;		// - ��� ������� ���� ������
	int iPntPr;		// - ��� ����������������� ���	(0)
	int iPnt_1;		// - ��� ��� ��� ������������ ���(1)
	int iPnt_2;		// - ��� ��� ��� ������������ ���(2)
	int iPntNx;		// - ��� ������������������ ���	(4)

	int mnn,mn1,mn2;// - ��� ���� ���
	
	Vec3db p0,p1,p2,p3,p4,p5,pm;	// ����� ��� ���� ����- ���� ����� ��������� 
	Vec3db n0,n1,n2,n3,n4,nm,n5;	// ��������
	Vec3db r_01,r_12,r_24,r_04;		// ������������
	Vec3db r_13,r_23;
	Vec3db d1,d2,d3;				// ���������������� ��� ���

	ms1Dint NwBndS(1);	// ��� � ���� ��������������
	ms1Dint LcBndS(1);	// ��� � ����� ���� ����������

	ms1Ddb  rcm(10);	// ��� � ������ ��� ������� ���� ������������	
	ms1Dint np(10);		// ���� ���������� ��������� � ����������Rch � ������
	ms1Ddb rc1(10);		// ��� � ������ ���iPnt_1 � ���� ������������	
	ms1Ddb rc2(10);		// ��� � ������ ���iPnt_2 � ���� ������������	

	double loc_cs;		// ����� ����� ��� - ����� � ���� ���� ����������������

	double cs_012,cs_124,cs_013,cs_324;	// ���� ��������������.
	double cs_123,cs_213,cs_132;		// ���� ������ ������.
	double cs_240,cs_401;				// ���� ���������.
	double csn;							// ������ �������.

	double sr01,sr12,sr23,sr24,sr13,sr04;	// ��� �� ������ ����.
	double r01,r12,r23,r24,r13,r04;			// �� ������ ����.

	double Rch,rch;		// 
	Vec3db r_ch;		//
	double Rcn;			// ���������� ���� � ������� ���� ��� ������� ������ ����(�����) ���.

	double h1,h2;
	Vec3db r_cp;		//

	bool prj_rs;		// �������� ��������������� �����.
	bool alwcpy;		// ����� ����� ����� ���������� �������� ��������� ����� (����� ����� ���������� ��)
	bool hp1,hp2;		// ������������������ ����
	bool ch_cmb;		// ���������� �������������� ��������������. (������������ ���

	bool stp_glb;		// ���������� � �������� ������
	bool surfchg;		// ������������ ���� ����������� ���

	int nf,ne,_np;

	// ����������

	const double dpm	= 0.018;		// ~(1-cos(pi/3))^2; ���� � ���� ���� �������������������� ��� ������
	const double cstrch = cos(pi/6);	// ������ �� � ��������������� ������� ���������� ������4 ���
	const double cs0	= cos(pi/9);	// ����� ������� �����������. (20 ����)
	const double cs1	= cos(pi/3);	// �������� ������� �������� ��� ��� ��� ������ ���� ����.
	const double cs2	= cos(pi/6);	// ����� ������� ������ ��� ������ ������� ���.
	const double cs3	= cos(2*pi/9);	// ��� � �� ������ ��� ��������� - � ����� ������
	const double cs4	= cos(2*pi/4);	// �������� ����������� ��� ��������� ��� (�������) ��������� ��.
	const double cs5	= cos(pi/9);	// ����� ������� �����������  �������4-���. (20 ����)
	const double cmx	= cos(15*pi/36);// ����� �� ��� ������. (75 ����)
	const double cmn	= cos(5*pi/18); // �������� ��� ������. (50 ����)
	const double cs6	= cos(pi/2);	// ����� ������� ������ ��������������� ������

	// �����������
	//double locmin;
	int total;
	ms1Dint Nicd;
	Nicd.init(12);
	
	NumberOfCycle	= 400;

	total	= -1;
	i_main	= -1;
	do				// ���� ��. 
	{
		surfchg	= false;
		i_main++;
		/*cout<<i_main<<" NP:"<<Point.N<<" NF:"<<Trngl.N<<" NE:"<<Edge.N<<" NbE:";//"Main cycle: "<<
		for (i=0;i<BndEd.N;i++)
		{
			cout<<BndEd.x[i].bn.N<<"  ";
		}
		cout<<endl;//<<A.P.N<<endl;//*/
		i_setb	= 0;	// ��������������������.
		do			// �� � �� ����� �������.
		{
			i_bndr	= 0;					// ������������������ �
			NwBndS.N	= 0;				// ��������������.
			len_sb	= BndEd.x[i_setb].bn.N-1;	// �������� ����� �������� ����������
			i_bndr	= 0;			
			do		// �� � �� �������� ���������
			{	
				/*if(total>8160)
				{
					cout<<1;
				}
				total++;*/

				//if(Edge.N>=99182) {cout<<total<<" <- "<<Edge.x[99182].n_pnt<<endl;}
				/*if(total>=2936)//(total==67296)
				{
//					SrfT2vrml();
					//cout<<total<<endl;
				}/**/

				alwcpy	= true;
				prj_rs	= true;

				method	= 0;

				iEdgCr	= BndEd.x[i_setb].bn.x[i_bndr];	// ���������������
				iEdgNx	= i_bndr==len_sb	? NwBndS.x[0] : BndEd.x[i_setb].bn.x[i_bndr+1];	// ������������������
				iEdgPr	= i_bndr==0	? BndEd.x[i_setb].bn.x[len_sb] : NwBndS.x[NwBndS.N-1];	// ����������������			

				if (iEdgPr==iEdgNx)
				{
					method	= 11;
					iPnt_1	= Edge.x[iEdgCr].n_pnt.x[0];
					iPnt_2	= Edge.x[iEdgCr].n_pnt.x[1];
				}else
				{
					// �����������������
					iTriCr	= Edge.x[iEdgCr].n_fc.x[0];	// ���,
					iTriNx	= Edge.x[iEdgNx].n_fc.x[0];	// �����,
					iTriPr	= Edge.x[iEdgPr].n_fc.x[0];	// ����.
					// �������������
					iPntPr	= Edge.x[iEdgPr].n_pnt.x[0];
					iPnt_1	= Edge.x[iEdgCr].n_pnt.x[0];
					iPnt_2	= Edge.x[iEdgCr].n_pnt.x[1];
					iPntNx	= Edge.x[iEdgNx].n_pnt.x[1];

					/*if (i_main>200)
					{
						if (Edge.x[iEdgCr].n_pnt.x[1]!=Edge.x[iEdgNx].n_pnt.x[0])
						{
							cout<<iEdgNx<<" "<<iPnt_2<<" => "<<*Point.x[iPnt_2].n_edg;
						}
					}*/
					
					//points2vrml(iPntPr,iPnt_1,iPnt_2,iPntNx,p3);

					//cout<<total<<" : "<<iPntPr<<", "<<iPnt_1<<", "<<iPnt_2<<", "<<iPntNx<<", "<<iPntTr<<endl;
					
					if (BndEd.x[i_setb].bn.N-i_bndr+NwBndS.N==4)
					{
						LcBndS.pst(NwBndS);
						LcBndS.add((BndEd.x[i_setb].bn.x+i_bndr),(BndEd.x[i_setb].bn.N-i_bndr));
						j	= 0;
						for(i=0;i<4;i++) // �� � �� ��������
						{// ��������� ��� ���������� � � ���
							if (Point.x[Edge.x[LcBndS.x[i]].n_pnt.x[0]].n_edg->N==2)
							{
								j++;
								
								k	= i;
							}
						}
						if (j==1)
						{// ���� ��� ��������� ���
							NwBndS.N	= 0;
							NwBndS.add(LcBndS.x+k,LcBndS.N-k);
							NwBndS.add(LcBndS.x,i);
							iPnt_1	= Edge.x[NwBndS.x[0]].n_pnt.x[0];
							iPnt_2	= Edge.x[NwBndS.x[1]].n_pnt.x[0];
							iPntNx	= Edge.x[NwBndS.x[2]].n_pnt.x[0];
							iPntPr	= Edge.x[NwBndS.x[3]].n_pnt.x[0];
							// ���� ������� ������ ����� �����(��� �����)
							//points2vrml(iPntPr,iPnt_1,iPnt_2,iPntNx,p3);							
							
							
							p0	= Point.x[iPntPr].crd;	// ����������������� ����
							p1	= Point.x[iPnt_1].crd;
							p2	= Point.x[iPnt_2].crd;
							p4	= Point.x[iPntNx].crd;
							
							r_01= p1-p0;		// ���������� �� ��� ����
							r_12= p2-p1;
							r_24= p4-p2;
							r_04= p0-p4;
							
							//crs(r_01,r_12,n1);
							//crs(r_24,r_04,n2);
							n1.crss(r_01,r_12);
							n2.crss(r_24,r_04);
							
							n1.nrml();
							n2.nrml();
							
							loc_cs	= -n1.scpr(n2);
							
							method	= (loc_cs<cstrch) ? 12:14; // cstr -> loc_cs
							
						}else
						{
							if (j==0)
							{
								p0	= Point.x[iPntPr].crd;	// ����������������� ����
								p1	= Point.x[iPnt_1].crd;
								p2	= Point.x[iPnt_2].crd;
								p4	= Point.x[iPntNx].crd;
								
								r_01= p1-p0;		// ���������� �� ��� ����
								r_12= p2-p1;
								r_24= p4-p2;
								r_04= p0-p4;
								
								sr01= r_01.ssqr();	// ���� ��
								sr12= r_12.ssqr();
								sr24= r_24.ssqr();
								sr04= r_04.ssqr();
								
								
								r01	= sqrt(sr01);	// ��
								r12	= sqrt(sr12);
								r24	= sqrt(sr24);
								r04	= sqrt(sr04);
								
								cs_012	= -r_01.scpr(r_12)/(r01*r12);
								cs_124	= -r_12.scpr(r_24)/(r12*r24);
								cs_240	= -r_24.scpr(r_04)/(r24*r04);
								cs_401	= -r_04.scpr(r_01)/(r04*r01);
								
								if ((cs_012<cs5)&&(cs_124<cs5)&&(cs_240<cs5)&&(cs_401<cs5))
								{
									k	= NwBndS.N;
									NwBndS.N	= 0;
									NwBndS.add(LcBndS.x+k,LcBndS.N-k);
									NwBndS.add(LcBndS.x,k);
									
									method	= cs_012>cs_124 ? 13 : cs_012<cs_124 ? 12 : method;
								}
							}
						}
					}
					if (method==0)
					{

						if (iPntNx==iPntPr)
						{
							if ((iTriPr==iTriNx)&&(iTriCr==iTriNx)&&(iTriPr==iTriCr))
							{
								method = 1;
							}else
							{
								if ((iTriPr!=iTriNx)&&(iTriCr!=iTriNx)&&(iTriPr!=iTriCr))
								{
									method = 7;
								}
								else
								{
									method = 0;
								}
							}
						}else
						{
							method = 1;
						}

						
						if (method!=1) //((iPntNx==iPntPr)&&(iTriPr!=iTriNx)&&(iTriCr!=iTriNx)&&(iTriPr!=iTriCr)) // ���� ����-� �������������������
						{
							//method	= 7;
							//A.cp2wrl(name);
						}else
						{
							method	= 0;
							p0	= Point.x[iPntPr].crd;	// ������������������ ����
							p1	= Point.x[iPnt_1].crd;
							p2	= Point.x[iPnt_2].crd;
							p4	= Point.x[iPntNx].crd;
							
							r_01= p1-p0;		// ���������� �� ��� ����
							r_12= p2-p1;
							r_24= p4-p2;
							
							sr01= r_01.ssqr();	// ���� ��
							sr12= r_12.ssqr();
							sr24= r_24.ssqr();
							
							r01	= sqrt(sr01);	// ��
							r12	= sqrt(sr12);
							r24	= sqrt(sr24);
							
							if (false)//((r01>em*r12)|(r24>em*r12)|(r12>em*r01)|(r12>em*r24)) // ���� �� ���� ��.
							{
								// ���� ������� ��� ���� ���� ��. ������ ��
							}else
							{
								cs_012	= -r_01.scpr(r_12)/(r01*r12);
								cs_124	= -r_12.scpr(r_24)/(r12*r24);
								hp1	= ((cs_012>cs0)&&(iTriCr!=iTriPr));
								hp2	= ((cs_124>cs0)&&(iTriCr!=iTriNx));
								if (hp2||hp1) // ���� ��������������.
								{
									// ��� � ������ ��.
									if (hp1&&(!hp2))
									{
										method	= 9;

										int itoc1,itoc2;
										for(int oldob=0;oldob<Point.x[iPntPr].n_edg->N;oldob++)
										{
											itoc1=Edge.x[Point.x[iPntPr].n_edg->x[oldob]].n_pnt.x[1];
											if (itoc1==iPntPr) itoc1=Edge.x[Point.x[iPntPr].n_edg->x[oldob]].n_pnt.x[0];

											for(int oldob1=0;oldob1<Point.x[itoc1].n_edg->N;oldob1++)
											{

												itoc2=Edge.x[Point.x[itoc1].n_edg->x[oldob1]].n_pnt.x[1];
												if (itoc2==itoc1) itoc2=Edge.x[Point.x[itoc1].n_edg->x[oldob1]].n_pnt.x[0];
												if(itoc2==iPnt_2&&itoc1!=iPnt_1) 
												{
													p3.x[0]	= Point.x[iPntPr].crd.x[0];
													p3.x[1]	= Point.x[iPntPr].crd.x[1];
													p3.x[2]	= Point.x[iPntPr].crd.x[2];
						
													n3.x[0]	= Point.x[iPntPr].nor.x[0];
													n3.x[1]	= Point.x[iPntPr].nor.x[1];
													n3.x[2]	= Point.x[iPntPr].nor.x[2];
						
													method=2;
												}												
											}
										}


									}else
									{
										if (hp2&&(!hp1))
										{
											method	= 10;
											int itoc1,itoc2;
											for(int oldob=0;oldob<Point.x[iPnt_1].n_edg->N;oldob++)
											{
												itoc1=Edge.x[Point.x[iPnt_1].n_edg->x[oldob]].n_pnt.x[1];
												if (itoc1==iPnt_1) itoc1=Edge.x[Point.x[iPnt_1].n_edg->x[oldob]].n_pnt.x[0];

												for(int oldob1=0;oldob1<Point.x[itoc1].n_edg->N;oldob1++)
												{

													itoc2=Edge.x[Point.x[itoc1].n_edg->x[oldob1]].n_pnt.x[1];
													if (itoc2==itoc1) itoc2=Edge.x[Point.x[itoc1].n_edg->x[oldob1]].n_pnt.x[0];
													if(itoc2==iPntNx&&itoc1!=iPnt_2) 
													{
														p3.x[0]	= Point.x[iPntNx].crd.x[0];
														p3.x[1]	= Point.x[iPntNx].crd.x[1];
														p3.x[2]	= Point.x[iPntNx].crd.x[2];

														n3.x[0]	= Point.x[iPntNx].nor.x[0];
														n3.x[1]	= Point.x[iPntNx].nor.x[1];
														n3.x[2]	= Point.x[iPntNx].nor.x[2];

                                                        method=3;
													}
												}
											}
										}
									}
								}
								else
								{
									r_04	= p4-p0;
									r04		= r_04.ssqr();
									/*if (false)//((r04<=cr04)&(iPntPr!=iPntNx)) // ���� ���� ��� 'p0' �'p4'. �� ������� ��� , � 
									{
									// ��� � ������ �� �������� ����� ������.
									method	= 8;							
									}
									else*/
									{									
										
										// ���������� ����� ������
										//n1	= A.P.x[iPnt_1].nor;
										n1.x[0]	= Point.x[iPnt_1].nor.x[0];
										n1.x[1]	= Point.x[iPnt_1].nor.x[1];
										n1.x[2]	= Point.x[iPnt_1].nor.x[2];
										
										//n2	= A.P.x[iPnt_2].nor;
										n2.x[0]	= Point.x[iPnt_2].nor.x[0];
										n2.x[1]	= Point.x[iPnt_2].nor.x[1];
										n2.x[2]	= Point.x[iPnt_2].nor.x[2];
										//double two =2;
										//pm	= p1+p2;
										pm.x[0]	= p1.x[0]+p2.x[0];
										pm.x[1]	= p1.x[1]+p2.x[1];
										pm.x[2]	= p1.x[2]+p2.x[2];
										//pm	/=two;	// ���� �������
										pm.x[0]	/=2;
										pm.x[1]	/=2;
										pm.x[2]	/=2;
										//nm	= n1+n2;
										nm.x[0]= n1.x[0]+n2.x[0];
										nm.x[1]= n1.x[1]+n2.x[1];
										nm.x[2]= n1.x[2]+n2.x[2];
										nm.nrml();	// ����� ��� ����� ���

										DefCubNmb(pm);

										prj_rs	= true;

										/*  !!!!!!!!!!!!!!!!!!
										n3	= nm;
										prj_rs	= fpnts(pm,p3,nm,ii);
										  !!!!!!!!!!!!!!!!!!!!! */

										/*if(total==243073)
										{
											cout<<2<<endl;
											//Surf2vrml();
											DefCubNmb(pm);
											cout<<ii<<endl;
											cout<<3<<endl;
											//points2vrml(ii,iPntPr,iPnt_1,iPnt_2,iPntNx,pm,pm);
											//nm.x[0] = 1e10;
											//cout<<nm<<endl;
										}*/

										prj_rs	= (Pnt2Surf(pm,p3,n3)==0);

										//points2vrml(ii,iPntPr,iPnt_1,iPnt_2,iPntNx,pm,p3);

										/*if ((p3-pm).norm()>0.5)
										{
											points2vrml(ii,iPntPr,iPnt_1,iPnt_2,iPntNx,pm,p3);
											prj_rs	= Pnt2Surf(pm,nm,p3,nm,type);
										}*/

										
										if (prj_rs)
										{	
											d1.crss(r_12,n3); 	// ���������� � �� ���
											d1.nrml();
											// ���� ����������.										
											R_Tr= TrSize(p3);
											/*R_	= 1.5*R;
											Rv	= 2*R;*/
											Rch	= 1.5*R_Tr*R_Tr;
											Rcn	= 1.5*R_Tr*R_Tr;
											// ����������
											
											d2	= p3	+= d1*R_high;	// ����� �����������
											nm	= n3;

											/*  !!!!!!!!!!!!!!!!!!
											prj_rs	= fpnts(d2,p3,n3,ii);

											n3	= nm;

											prj_rs	= fpnts(d2,p3,n3,ii);
											!!!!!!!!!!!!!!!!!!!!! */												
											prj_rs	= (Pnt2Surf(d2,p3,n3)==0);
											//prj_rs	= Pnt2Surf_(d2,nm,p3,n3,type);

											/*if ((p3-d2).norm()>0.5)
											{
												points2vrml(ii,iPntPr,iPnt_1,iPnt_2,iPntNx,d2,p3);
												prj_rs	= Pnt2Surf(d2,nm,p3,n3,type);
											}*/

											//points2vrml(ii,iPntPr,iPnt_1,iPnt_2,iPntNx,d2,p3);

											//cout<<(p3-d2).norm()<<endl;

											if (prj_rs)
											{
												
												r_13	= p3-p1;
												r_23	= p3-p2;
												sr13	= r_13.ssqr();
												sr23	= r_23.ssqr();
												r13		= sqrt(sr13);
												r23		= sqrt(sr23);
												
												cs_123	= -r_12.scpr(r_23)/(r12*r23);
												cs_213	= r_12.scpr(r_13)/(r12*r13);
												cs_132	= r_13.scpr(r_23)/(r13*r23);
												
												cs_013	= (cs_213<cs_012)&&(Point.x[iPnt_1].n_fc->N>3) ? 1 :-r_01.scpr(r_13)/(r13*r01);	// �� ��������� ������� ������
												cs_324	= (cs_123<cs_124)&&(Point.x[iPnt_2].n_fc->N>3) ? 1 : r_24.scpr(r_23)/(r24*r23);	// �� ��������� ������� �����
												//	  /|\
												// ����� ���� ����'cs_324' �'cs_013'. �� ���� �������� ��� ��� ������, � ���� �� 2-� �� 3- � ���.
												//if ((cs_123<cs_124)&&(A.P.x[iPnt_2].n_fc.N>3)){cs_324	= 1;}
												//if ((cs_213<cs_012)&&(A.P.x[iPnt_1].n_fc.N>3)){cs_013	= 1;}											
												if ((cs_013<cs2)&&((cs_012<cs3)||(iTriPr==iTriCr))&&(cs_324<cs2)&&((cs_124<cs3)||(iTriNx==iTriCr))) // ���� ������ ���� ���.
												{										
													// ��� ���� ���������������� ���� � ��� �������� ����.
													//cout<<ix<<' '<<iy<<' '<<iz<<':'<<endl<<cbs.x[ii].n_pnt<<endl;
													iPntTr	= Trngl.x[iTriCr].n_pnt.x[Trngl.x[iTriCr].n_pnt.find(iPnt_1,iPnt_2)];
													method	= 1; // ���� ��������� ������ ���.													
													rcm.N	= np.N	= 0;
													//p5	= p3;
													//p5	+= (p1+p2+p3);
													//p5	/= four;

///////////////////////////////////////////////////////////////////////////////dobavka////////////////////////////////////
													csn	= nm.scpr(n3);		// ugol mezhdu normaljami (normal' v novoj tochke i normal' na proekcii serediny tekuwego rebra)
													method	= csn<cs6 ? 0 : 1; 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


													p5.x[0]	= (p1.x[0]+p2.x[0]+p3.x[0]+p3.x[0])/4;
													p5.x[1]	= (p1.x[1]+p2.x[1]+p3.x[1]+p3.x[1])/4;
													p5.x[2]	= (p1.x[2]+p2.x[2]+p3.x[2]+p3.x[2])/4;													
													ch_cmb	= true;
													for (i=0;i<cbs.n_sp.x[ii].N;i++) // �������� ���������. (���� ��� ���� ��.)
													{
														if ((cbs.n_sp.x[ii].x[i]!=iPntPr)&&(cbs.n_sp.x[ii].x[i]!=iPnt_1)&&(cbs.n_sp.x[ii].x[i]!=iPnt_2)&&(cbs.n_sp.x[ii].x[i]!=iPntNx)&&((cbs.n_sp.x[ii].x[i]!=iPntTr))) // � ���� ��������'iPntNx','iPnt_1','iPnt_2,'iPntPr'.
														{
															//r_ch	= Point.x[cbs.x[ii].n_pnt.x[i]].crd-p5;// ����� ���� ���������
															r_ch.x[0]	= Point.x[cbs.n_sp.x[ii].x[i]].crd.x[0]-p5.x[0];
															r_ch.x[1]	= Point.x[cbs.n_sp.x[ii].x[i]].crd.x[1]-p5.x[1];
															r_ch.x[2]	= Point.x[cbs.n_sp.x[ii].x[i]].crd.x[2]-p5.x[2];
															
															//rch		= r_ch.sqs();	// ������ �����
															rch		= r_ch.x[0]*r_ch.x[0]+r_ch.x[1]*r_ch.x[1]+r_ch.x[2]*r_ch.x[2];
															if (rch<Rch) // �� ��������������, �
															{
																if ((Point.x[cbs.n_sp.x[ii].x[i]].edg1!=-1)&&(Point.x[cbs.n_sp.x[ii].x[i]].cmb)) // ����� ��� � ��� ������ �����������.
																{
																	np.add(cbs.n_sp.x[ii].x[i]);	// ���������
																	rcm.add(rch);		// ����������.
																	//method	= 0;
																}else if(!Point.x[cbs.n_sp.x[ii].x[i]].cmb) ch_cmb = false;
																method	= 0;			// ��� ����� ��� '1' � ����� ��� ������.
															}
														}
													}
																										
													if (ch_cmb)
													{
														if ((np.N!=0)&&(cs_012<=cs4)&&(cs_124<=cs4))// �� �� ����� ���� �������� �
														{
															rc1.N= rc2.N= 0;
															for (i=0;i<np.N;i++)	// ����� ������ ���'p1' �'p2' � ���������
															{
																//r_ch= Point.x[np.x[i]].crd-p1;
																r_ch.x[0]= Point.x[np.x[i]].crd.x[0]-p1.x[0];
																r_ch.x[1]= Point.x[np.x[i]].crd.x[1]-p1.x[1];
																r_ch.x[2]= Point.x[np.x[i]].crd.x[2]-p1.x[2];
																
																//rch	= r_ch.sqs();
																rch	= r_ch.x[0]*r_ch.x[0]+r_ch.x[1]*r_ch.x[1]+r_ch.x[2]*r_ch.x[2];
																
																rc1.add(rch);
																//r_ch= Point.x[np.x[i]].crd-p2;
																r_ch.x[0]= Point.x[np.x[i]].crd.x[0]-p2.x[0];
																r_ch.x[1]= Point.x[np.x[i]].crd.x[1]-p2.x[1];
																r_ch.x[2]= Point.x[np.x[i]].crd.x[2]-p2.x[2];
																
																//rch	= r_ch.sqs();
																rch	= r_ch.x[0]*r_ch.x[0]+r_ch.x[1]*r_ch.x[1]+r_ch.x[2]*r_ch.x[2];
																
																rc2.add(rch);
															}
															mnn	= rcm.mmin();	// ��������'np' ������� �������'p3'
															mn1	= rc1.mmin();	// ��������'np' ������� ����'p1'
															mn2	= rc2.mmin();	// ��������'np' ������� ����'p2'
															sr12	/=4;
															if ((rc1.x[mn1]<sr12)&&(rc2.x[mn2]>rc1.x[mn1]))
															{
																//A.out(name);
																method = 0;
															}else
															{
																if ((rc2.x[mn2]<sr12)&&(rc1.x[mn1]>rc2.x[mn2])){
																	//A.out(name);
																	method = 0;
																}else
																{
																	
																	if (rcm.x[mnn]<Rcn)
																	{
																		csn	= nm.scpr(n3);		// �� �������.(�� ������ ��������n1,n2,n3)
																		method	= csn<cs6 ? 0 : 4; 
																	}
																}
															}
														}
													}/*else
													{
														if (!((cs_013<cs2)&&((cs_012<cs3)||(iTriPr==iTriCr))&&(cs_324<cs2)&&((cs_124<cs3)||(iTriNx!=iTriPr)))) // ���� ������ ���� ���.
														{
															if ( ((cs_013>=cs2)||(cs_012>=cs3))&&((cs_324<cs2)&&(cs_124<cs3))&&(iTriCr!=iTriPr) )
															{
																method	= 2;
															}else 
																if ( ((cs_324>=cs2)||(cs_124>=cs3))&&((cs_013<cs2)&&(cs_012<cs3))&&(iTriCr!=iTriNx) )
																{
																	method	= 3;
																}else
																	if ( (cs_324>=cs2)&&(cs_013>=cs2) )
																	{
																		method	= cs_013>=cs_324 ? 2 : 3;
																	}
														}
													}*/
												}
												else
												{
													if ( ((cs_013>=cs2)||(cs_012>=cs3))&&((cs_324<cs2)&&(cs_124<cs3))&&(iTriCr!=iTriPr) )
													{
														method	= 2;
													}else 
														if ( ((cs_324>=cs2)||(cs_124>=cs3))&&((cs_013<cs2)&&(cs_012<cs3))&&(iTriCr!=iTriNx) )
														{
															method	= 3;
														}else
															if ( (cs_324>=cs2)&&(cs_013>=cs2) )
															{
																method	= cs_013>=cs_324 ? 2 : 3;
															}
												}/**/
										}										
									}										
								}								
							}
						}
					}
					}
					}

					if (!prj_rs) method	= 0;										
					//SrfT2vrml();
					//cp2wrl(name);
					switch (method)
					{
					case 0:		// � ����� ��������� ��� �������������
						Nicd.x[0]++;
						NwBndS.add(iEdgCr);break;
					case 1:		// ��� ����������� (�� ��� �� �� ���- ���)
						Nicd.x[1]++;
						AddPntCbs(p3,Point.N);
						AddPnt1(p3,n3,NwBndS,iEdgCr,iPnt_1,iPnt_2,i_setb);
						surfchg	= true;
						//A.cp2wrl(name);x
						break;
					case 2:		// ��� ��������� �������� 
						Nicd.x[2]++;
						h1	= (double)Point.x[iPntPr].n_edg->N;
						//p3	*= two;
						p3.x[0]	*= 2;
						p3.x[1]	*= 2;
						p3.x[2]	*= 2;
						
						//p3	+= p0*h1;
						p3.x[0]	+= p0.x[0]*h1;
						p3.x[1]	+= p0.x[1]*h1;
						p3.x[2]	+= p0.x[2]*h1;
						
						h1+=2;
						//p3	/= h1;
						p3.x[0]	/= h1;
						p3.x[1]	/= h1;
						p3.x[2]	/= h1;
						
						//						p3	= sr2(p3,P,r_wdw);
						//r_cp	= p3;
						r_cp.x[0]	= p3.x[0];
						r_cp.x[1]	= p3.x[1];
						r_cp.x[2]	= p3.x[2];
						
						nm	= n3;
						//if(fndpnt_(r_cp,p3,n3,ii,id1,id2))
						if(Pnt2Surf(r_cp,p3,n3)==0)
						{
							//A.cp2wrl(name);
							AddPnt2(p3,n3,NwBndS,i_bndr,iEdgPr,iPntPr,iPnt_1,iPnt_2,i_setb,len_sb);						
							surfchg	= true;
						}
						else
							NwBndS.add(iEdgCr);
						//A.cp2wrl(name);
						//A.cp2wrl_(name);						
						break;
					case 3:		// ��� ��������� ��������
						Nicd.x[3]++;
						h1	= (double)Point.x[iPntNx].n_edg->N;
						//p3	*= two;
						p3.x[0]	*= 2;
						p3.x[1]	*= 2;
						p3.x[2]	*= 2;
						
						//p3	+= p4*h1;
						p3.x[0]	+= p4.x[0]*h1;
						p3.x[1]	+= p4.x[1]*h1;
						p3.x[2]	+= p4.x[2]*h1;
						
						h1+=2;
						
						//p3	/= h1;
						p3.x[0]	/= h1;
						p3.x[1]	/= h1;
						p3.x[2]	/= h1;
						
						//						p3	= sr2(p3,P,r_wdw);
						//r_cp	= p3;
						r_cp.x[0]	= p3.x[0];
						r_cp.x[1]	= p3.x[1];
						r_cp.x[2]	= p3.x[2];
						
						nm	= n3;
						//if (fndpnt_(r_cp,p3,n3,ii,id1,id2)) 
						if(Pnt2Surf(r_cp,p3,n3)==0)
						{
							//A.cp2wrl(name);
							AddPnt3(p3,n3,NwBndS,i_bndr,iEdgNx,iPntNx,iPnt_1,iPnt_2,i_setb);
							surfchg	= true;
						}
						else
							NwBndS.add(iEdgCr);						
						//A.cp2wrl(name);
						break;
					case 4:		// ��� ������ ��������� ��������������������
						Nicd.x[4]++;
						h1	= (double)Point.x[np.x[mnn]].n_edg->N;
						p3.x[0]	*= 2;p3.x[1]	*= 2;p3.x[2]	*= 2;
						p3	+= Point.x[np.x[mnn]].crd*h1;h1+=2;
						p3.x[0]	/= h1;p3.x[1]	/= h1;p3.x[2]	/= h1;
						//						p3	= sr2(p3,P,r_wdw);
						r_cp	= p3;
						//if (fndpnt_(r_cp,p3,n3,ii,id1,id2))						
						nm	= n3;
						if(Pnt2Surf(r_cp,p3,n3)==0)
						{
							//A.cp2wrl(name);
						//	points2vrml(ii,iPntPr,iPnt_1,iPnt_2,iPntNx,r_cp,p3);
							AddPnt4(p3,n3,NwBndS,i_bndr,np.x[mnn],iPnt_1,iPnt_2,i_setb,len_sb);	
							surfchg	= true;
						}
						//A.cp2wrl(name);
						else
							NwBndS.add(iEdgCr);						
						break;
					case 7:		// ��� ���������� ������������� �����
						Nicd.x[5]++;
						AddPnt7(i_bndr,iPnt_1,iPnt_2,iPntNx,iEdgPr,iEdgCr,iEdgNx,i_setb,len_sb);
						alwcpy	= false;
						surfchg	= true;
						break;
						/*case 8:
						h1	= (double)A.P.x[iPntPr].n_edg.N;
						n2	= (double)A.P.x[iPntNx].n_edg.N;
						p3	= p0*h1+p4*h2;h1+=h2;
						p3	/= h1;
						A.ad8();*/
					case 9:		// ����������� ���� �� �����
						Nicd.x[6]++;
						h1	= (double)Point.x[iPntPr].n_edg->N;
						h2	= (double)Point.x[iPnt_2].n_edg->N;
						p3	= p0*h1+p2*h2;h1+=h2;
						p3.x[0]	/= h1;p3.x[1]	/= h1;p3.x[2]	/= h1;
						
						//DefCubNmb(p3);
						//points2vrml(ii,iPntPr,iPnt_1,iPnt_2,iPntNx,p3,p3);
						
						r_cp	= p3;
						nm	= (Point.x[iPntPr].nor+Point.x[iPnt_2].nor);nm.nrml();
						//if (fndpnt_(r_cp,p3,n3,ii,id1,id2))							
						if(Pnt2Surf(r_cp,p3,n3)==0)
						{
							AddPnt9(p3,n3,NwBndS,i_bndr,iPntPr,iPnt_1,iPnt_2,iEdgPr,len_sb);
							surfchg	= true;
						}
						else
							NwBndS.add(iEdgCr);						
						break;
					case 10:	// ����������� ���� �� �����
						Nicd.x[7]++;
						h1	= (double)Point.x[iPnt_1].n_edg->N;
						h2	= (double)Point.x[iPntNx].n_edg->N;
						p3	= p1*h1+p4*h2;h1+=h2;
						p3.x[0]	/= h1;p3.x[1]	/= h1;p3.x[2]	/= h1;												
						
						DefCubNmb(p3);						
						
						r_cp	= p3;
						nm	= (Point.x[iPntNx].nor+Point.x[iPnt_1].nor);nm.nrml();
						//if (fndpnt_(r_cp,p3,n3,ii,id1,id2))						
						if(Pnt2Surf(r_cp,p3,n3)==0)
						{
							AddPnt10(p3,n3,NwBndS,i_bndr,iPnt_1,iPnt_2,iPntNx,iEdgNx,len_sb);
							surfchg	= true;
						}
						else
							NwBndS.add(iEdgCr);
						break;
					case 11:	// ���� ��� � �� ������������. (��. ���������� �� �. ��.)
						Nicd.x[8]++;
						i	= Edge.x[iEdgCr].n_fc.x[1]=Edge.x[iEdgNx].n_fc.x[0];
						Trngl.x[i].n_edg.x[Trngl.x[i].n_edg.find(iEdgNx)]	= iEdgCr;
						i	= Point.x[Edge.x[iEdgCr].n_pnt.x[0]].n_edg->fnd(iEdgNx);
						Point.x[Edge.x[iEdgCr].n_pnt.x[0]].n_edg->rem(1,i);
						i	= Point.x[Edge.x[iEdgCr].n_pnt.x[1]].n_edg->fnd(iEdgNx);
						Point.x[Edge.x[iEdgCr].n_pnt.x[1]].n_edg->rem(1,i);
						Point.x[iPnt_1].edg1 = Point.x[iPnt_1].edg2 = Point.x[iPnt_2].edg1 = Point.x[iPnt_2].edg2 = -1;
						Edge.x[iEdgCr].bnd	= false;
						RmvEdg(iEdgNx,NwBndS);
						RmvBnd(i_setb);
						i_bndr	= len_sb;
						alwcpy	= false;
						surfchg	= true;
						break;
					case 12:	//	��������� ����������� 4-��� (/)
						Nicd.x[9]++;
						// ����� �� ����������� ���
						iTriMx	= Trngl.N+1;
											
						Point.x[iPnt_1].n_edg->add(Edge.N);
						Point.x[iPntNx].n_edg->add(Edge.N);
						Point.x[iPnt_1].n_fc->adt(Trngl.N,iTriMx);
						Point.x[iPntNx].n_fc->adt(Trngl.N,iTriMx);
						Point.x[iPnt_2].n_fc->add(Trngl.N);
						Point.x[iPntPr].n_fc->add(iTriMx);
						
						Edge.x[NwBndS.x[0]].bnd	= Edge.x[NwBndS.x[1]].bnd	= Edge.x[NwBndS.x[2]].bnd	= Edge.x[NwBndS.x[3]].bnd	= false;
						Edge.x[NwBndS.x[0]].n_fc.x[1] = Edge.x[NwBndS.x[1]].n_fc.x[1] = Trngl.N;
						Edge.x[NwBndS.x[2]].n_fc.x[1] = Edge.x[NwBndS.x[3]].n_fc.x[1] = iTriMx;
						Point.x[iPntPr].edg1	= Point.x[iPntPr].edg2	= Point.x[iPnt_1].edg1	= Point.x[iPnt_1].edg2	= -1;
						Point.x[iPnt_2].edg1	= Point.x[iPnt_2].edg2	= Point.x[iPntNx].edg1	= Point.x[iPntNx].edg2	= -1;
						
						// ���� ���� �� ���� �� ��������
						if(Edge.N+EXT>=Edge.mN) Edge.adm_(AddQuantEdg);
						if(Trngl.N+EXT>=Trngl.mN) Trngl.adm_(AddQuantTri);
						Edge.x[Edge.N].SetEdge(iPnt_1,iPntNx,Trngl.N,iTriMx,i_setb);
						Trngl.x[Trngl.N].SetTriangle(iPnt_1,iPntNx,iPnt_2,Edge.N,NwBndS.x[1],NwBndS.x[0]);
						Trngl.x[iTriMx].SetTriangle(iPnt_1,iPntPr,iPntNx,NwBndS.x[3],NwBndS.x[2],Edge.N);
						
						Edge.N++;
						Trngl.N+=2;
						RmvBnd(i_setb);
						i_bndr	= len_sb;
						alwcpy	= false;
						surfchg	= true;
						break;
					case 13:	//	��������� ����������� 4-��� (����� � ��� 12) (\)
						Nicd.x[10]++;
						iTriMx	= Trngl.N+1;
						
						Point.x[iPntPr].n_edg->add(Edge.N);
						Point.x[iPnt_2].n_edg->add(Edge.N);
						Point.x[iPntPr].n_fc->adt(Trngl.N,iTriMx);
						Point.x[iPnt_2].n_fc->adt(Trngl.N,iTriMx);
						Point.x[iPnt_1].n_fc->add(Trngl.N);
						Point.x[iPntNx].n_fc->add(iTriMx);
						
						Edge.x[NwBndS.x[0]].bnd	= Edge.x[NwBndS.x[1]].bnd	= Edge.x[NwBndS.x[2]].bnd	= Edge.x[NwBndS.x[3]].bnd	= false;
						Edge.x[NwBndS.x[1]].n_fc.x[1] = Edge.x[NwBndS.x[2]].n_fc.x[1] = iTriMx;
						Edge.x[NwBndS.x[3]].n_fc.x[1] = Edge.x[NwBndS.x[0]].n_fc.x[1] = Trngl.N;
						Point.x[iPntPr].edg1	= Point.x[iPntPr].edg2	= Point.x[iPnt_1].edg1	= Point.x[iPnt_1].edg2	= -1;
						Point.x[iPnt_2].edg1	= Point.x[iPnt_2].edg2	= Point.x[iPntNx].edg1	= Point.x[iPntNx].edg2	= -1;
						
						// ���� ���� �� ���� �� ��������
						if(Edge.N+EXT>=Edge.mN) Edge.adm_(AddQuantEdg);
						if(Trngl.N+EXT>=Trngl.mN) Trngl.adm_(AddQuantTri);
						Edge.x[Edge.N].SetEdge(iPntPr,iPnt_2,Trngl.N,iTriMx,i_setb);
						Trngl.x[Trngl.N].SetTriangle(iPntPr,iPnt_2,iPnt_1,Edge.N,NwBndS.x[0],NwBndS.x[3]);
						Trngl.x[iTriMx].SetTriangle(iPnt_2,iPntPr,iPntNx,Edge.N,NwBndS.x[2],NwBndS.x[1]);
						
						Edge.N++;
						Trngl.N+=2;
						RmvBnd(i_setb);
						i_bndr	= len_sb;
						alwcpy	= false;
						surfchg	= true;
						break;
					case 14: //	��������� ����������� 4-��� (����� � ����12 �13) (\)
						Nicd.x[11]++;
						// ����������������A.P.x[iPnt_1].n_fc.x[0];						
						// ��� ��� ���
						nf	= Point.x[iPnt_1].n_fc->x[0];
						_np	= Trngl.x[nf].n_pnt.find(iPnt_1);
						Trngl.x[nf].n_pnt.x[_np]=iPntNx;
						// ��� ������
						_np	= Trngl.x[nf].n_edg.find(NwBndS.x[0]);
						Trngl.x[nf].n_edg.x[_np]=NwBndS.x[1];
						_np	= Trngl.x[nf].n_edg.find(NwBndS.x[3]);
						Trngl.x[nf].n_edg.x[_np]=NwBndS.x[2];
						// ����� ����� ��������������
						Point.x[iPntNx].n_fc->add(nf);
						// ����� ����� ������ �������
						Edge.x[NwBndS.x[1]].n_fc.x[1]	= nf;
						Edge.x[NwBndS.x[2]].n_fc.x[1]	= nf;
						Edge.x[NwBndS.x[1]].bnd	= false;
						Edge.x[NwBndS.x[2]].bnd	= false;						
						// ���� ����� ����������� iPnt_2 �iPntPr
						ne	= Point.x[iPnt_2].n_edg->fnd(NwBndS.x[0]);
						if (ne==-1){ cout<<"Error in metod 14! (1)"<<endl; my_exit(1);}
						Point.x[iPnt_2].n_edg->rem(1,ne);
						ne	= Point.x[iPntPr].n_edg->fnd(NwBndS.x[3]);
						if (ne==-1){ cout<<"Error in metod 14! (2)"<<endl; my_exit(1);}
						Point.x[iPntPr].n_edg->rem(1,ne);
						// ���� ��������iPnt_1
						RmvPnt(iPnt_1);
						// ���� �� ����� NwBndS.x[0] �NwBndS.x[3].
						if ((NwBndS.x[0]!=(Edge.N-1))&&(NwBndS.x[3]!=(Edge.N-1)))
						{
							RmvEdg(NwBndS.x[0],NwBndS);
							RmvEdg(NwBndS.x[3],NwBndS);
						}else
						{
							if (NwBndS.x[0]==(Edge.N-1))
							{
								RmvEdg(NwBndS.x[0],NwBndS);
								RmvEdg(NwBndS.x[3],NwBndS);
							}else
							{
								RmvEdg(NwBndS.x[3],NwBndS);
								RmvEdg(NwBndS.x[0],NwBndS);
							}
						}
						/*RmvEdg(NwBndS.x[0],NwBndS);
						RmvEdg(NwBndS.x[3],NwBndS);*/
						i_bndr	+= 3;
						RmvBnd(i_setb);						
						//len_sb	= 0;
						//cout<< "method number 14"<<endl;
						alwcpy	=false;
						surfchg	= true;
						break;
					}
					i_bndr++;

					/*for(int lii=0;lii<BndEd.N;lii++)// поиск среди граничных рёбер ребра с нулевой длинной в силу одинаковых точек на концах
						for(int kii=0;kii<BndEd.x[lii].bn.N;kii++)
						{
							int egii;
							egii	= BndEd.x[lii].bn.x[kii];
							if(Edge.x[egii].n_pnt.x[0]==Edge.x[egii].n_pnt.x[1])
							{
								int jii;
								jii=0;
							}
						}*/
					/*cout<<i_bndr<<"  "<<len_sb<<endl;
					cout<<BndEd.x[i_setb].bn;
					cout<<NwBndS;
					cout<<alwcpy<<endl;*/
				}while(i_bndr<=len_sb);	// ����� �� � ���� ����.				&&(ttt<tt_)
				if (alwcpy) {BndEd.x[i_setb].bn.pst(NwBndS);i_setb++;}else
				{
					alwcpy=true;
				}
			}while(i_setb<BndEd.N);	// &&(ttt<tt_)
			/*if(!surfchg)
			{
				cout<<1;
			}/**/
		stp_glb	= ((BndEd.N!=0)&&(surfchg));
		/*if (i_main>=120)//259 ncyclm  (ttt>=tt_)
			{
				stp_glb	= false;
			}/**/
		//SRF->RCS();
	}while(stp_glb);

	/*for(i=0;i<Point.N;i++)
	{
		j	= Point.x[i].stp.x[1];
		switch (Point.x[i].stp.x[0])
		{
			case	AtomSphere:
			{
				Atom.x[j].n_pnt->add(i);
				break;
			}
			case	TwosTorus:
			{
				Twos->x[j].n_pnt->add(i);
				break;
			}
			case	TrisSphere:
			{
				Tris->x[j].n_pnt->add(i);
				break;
			}
			case	ScStblSph1:
			{
				k	= Point.x[i].stp.x[2];
				SRol->x[k].Stbl->x[j].n_pnt1->add(i);
				break;
			}
			case	ScStblSph2:
			{
				k	= Point.x[i].stp.x[2];
				SRol->x[k].Stbl->x[j].n_pnt2->add(i);
				break;
			}
			case	ScTrisSphr:
			{
				k	= Point.x[i].stp.x[2];
				SRol->x[k].Tris->x[j].n_pnt->add(i);
				break;
			}
			case	ScTwosTor:
			{
				k	= Point.x[i].stp.x[2];
				SRol->x[k].Twos->x[j].n_pnt->add(i);
				break;
			}
		}
	}/**/

	FragmPntCorl();
}

void MeshConstructor::FragmPntClear()
{
	int i,j;
	for(i=0;i<Atom.N;++i)Atom.x[i].n_pnt->N	= 0;
	for(i=0;i<Twos->N;++i)Twos->x[i].n_pnt->N	= 0;
	for(i=0;i<Tris->N;++i)Tris->x[i].n_pnt->N	= 0;
	for(j=0;j<SRol->N;++j)
	{
		for(i=0;i<SRol->x[j].Stbl->N;++i)
		{
			SRol->x[j].Stbl->x[i].n_pnt1->N	= 0;
			SRol->x[j].Stbl->x[i].n_pnt2->N	= 0;
		}
		for(i=0;i<SRol->x[j].Tris->N;++i)SRol->x[j].Tris->x[i].n_pnt->N	= 0;
		for(i=0;i<SRol->x[j].Twos->N;++i)SRol->x[j].Twos->x[i].n_pnt->N	= 0;
	}
}

void MeshConstructor::FragmPntCorl()
{
	int i,j,k;
	for(i=0;i<Point.N;i++)
	{
		j	= Point.x[i].stp.x[1];
		switch (Point.x[i].stp.x[0])
		{
			case	AtomSphere:
			{
				Atom.x[j].n_pnt->add(i);
				break;
			}
			case	TwosTorus:
			{
				Twos->x[j].n_pnt->add(i);
				break;
			}
			case	TrisSphere:
			{
				Tris->x[j].n_pnt->add(i);
				break;
			}
			case	ScStblSph1:
			{
				k	= Point.x[i].stp.x[2];
				SRol->x[k].Stbl->x[j].n_pnt1->add(i);
				break;
			}
			case	ScStblSph2:
			{
				k	= Point.x[i].stp.x[2];
				SRol->x[k].Stbl->x[j].n_pnt2->add(i);
				break;
			}
			case	ScTrisSphr:
			{
				k	= Point.x[i].stp.x[2];
				SRol->x[k].Tris->x[j].n_pnt->add(i);
				break;
			}
			case	ScTwosTor:
			{
				k	= Point.x[i].stp.x[2];
				SRol->x[k].Twos->x[j].n_pnt->add(i);
				break;
			}
		}
	}
}

double MeshConstructor::TrSize(Vec3db &p)
{
	R_high	= 1.5*R_crcl; 	// ��� ��� ������
	R_expd	= 2*R_crcl;	// ��� ������������ - � ���������



	return R_crcl;

}


void MeshConstructor::AddPnt1(Vec3db &p3, Vec3db &n3, ms1D<int> &b, int &En, int &Pn1, int &Pn2, int &s)
{	
	NEdg	= Edge.N+1;
	Point.x[Pn1].n_edg->add(Edge.N);
	Point.x[Pn2].n_edg->add(NEdg);

	Point.x[Pn1].n_fc->add(Trngl.N);
	Point.x[Pn2].n_fc->add(Trngl.N);

	Edge.x[En].bnd	= false;
	Edge.x[En].n_fc.x[1]	= Trngl.N;

	Point.x[Pn1].edg2=Edge.N;
	Point.x[Pn2].edg1=NEdg;

	if (EXT+Point.N >= Point.mN)Point.adm_(AddQuantPnt);
	if (EXT+Edge.N  >= Edge.mN) Edge.adm_(AddQuantEdg);
	if (EXT+Trngl.N >= Trngl.mN)Trngl.adm_(AddQuantTri);
	
	Point.x[Point.N].SetPoint(p3,n3,type,Edge.N,NEdg,Trngl.N);

	Edge.x[Edge.N].SetEdge(Pn1,Point.N,Trngl.N,-1,s);
	Edge.x[NEdg].SetEdge(Point.N,Pn2,Trngl.N,-1,s);

	Trngl.x[Trngl.N].SetTriangle(Pn1,Point.N,Pn2,Edge.N,NEdg,En);

	b.adt(Edge.N,NEdg);

	Point.N++;
	Edge.N+=2;
	Trngl.N++;
}

void MeshConstructor::AddPnt2(Vec3db &p3, Vec3db &n3, ms1D<int> &b, int &ib, int &E_n, int &P_n, int &Pn1, int &Pn2, int &s, int &lsb)
{
	
	Point.x[P_n].crd	= p3;
	Point.x[P_n].nor	= n3;

	Point.x[P_n].n_edg->add(Edge.N);
	Point.x[Pn2].n_edg->add(Edge.N);

	Point.x[P_n].n_fc->add(Trngl.N);
	Point.x[Pn1].n_fc->add(Trngl.N);
	Point.x[Pn2].n_fc->add(Trngl.N);

	Point.x[Pn2].edg1	= Point.x[P_n].edg2	= Edge.N; 
	Point.x[Pn1].edg1	= Point.x[Pn1].edg2	= -1;


	Edge.x[BndEd.x[s].bn[ib]].n_fc.x[1]	= Trngl.N;
	Edge.x[E_n].n_fc.x[1]				= Trngl.N;
	Edge.x[BndEd.x[s].bn[ib]].bnd		= false;
	Edge.x[E_n].bnd= false;
	if (Edge.N+EXT>=Edge.mN)	Edge.adm_(AddQuantEdg);
	if (Trngl.N+EXT>=Trngl.mN)Trngl.adm_(AddQuantTri);

	Edge.x[Edge.N].SetEdge(P_n,Pn2,Trngl.N,-1,s);
	Trngl.x[Trngl.N].SetTriangle(P_n,Pn2,Pn1,Edge.N,BndEd.x[s].bn[ib],E_n);

	BndEd.x[s].bn.x[ib]	= Edge.N;
	if (ib==0)
	{
		BndEd.x[s].bn.N--;
		lsb--;
	}
	else
	{
		b.N--;
		if (b.N==0)
		{
			//BndEd.x[s].bn.x[0]	= BndEd.x[s].bn.x[lsb];
			memmove(BndEd.x[s].bn.x,BndEd.x[s].bn.x+ib,(lsb-ib+1)*sizeof(int)); // �� ���
			//memcpy(BndEd.x[s].bn.x,BndEd.x[s].bn.x+lsb-ib+1,ib*BndEd.x[s].bn.sz); - ������ ����.
			BndEd.x[s].bn.N	-= ib;
			lsb	-=	ib;			
			ib	= 0;
		}
	}
	ib--;
	Edge.N++;
	Trngl.N++;
} 

void MeshConstructor::AddPnt3(Vec3db &p3, Vec3db &n3, ms1D<int> &b, int &ib, int &En_, int &Pn_, int &Pn1, int &Pn2, int &s)
{	
	Point.x[Pn_].crd	= p3;
	Point.x[Pn_].nor	= n3;

	Point.x[Pn_].n_edg->add(Edge.N);
	Point.x[Pn1].n_edg->add(Edge.N);

	Point.x[Pn_].n_fc->add(Trngl.N);
	Point.x[Pn1].n_fc->add(Trngl.N);
	Point.x[Pn2].n_fc->add(Trngl.N);

	Point.x[Pn_].edg1	= Point.x[Pn1].edg2	= Edge.N;
	Point.x[Pn2].edg1	= Point.x[Pn2].edg2	= -1;

	Edge.x[BndEd.x[s].bn[ib]].n_fc.x[1]	= Trngl.N;
	Edge.x[En_].n_fc.x[1]	= Trngl.N;
	Edge.x[BndEd.x[s].bn[ib]].bnd	= false;
	Edge.x[En_].bnd= false;
	if (Edge.N+EXT>=Edge.mN)	Edge.adm_(AddQuantEdg);
	if (Trngl.N+EXT>=Trngl.mN)Trngl.adm_(AddQuantTri);

	Edge.x[Edge.N].SetEdge(Pn1,Pn_,Trngl.N,-1,s);
	Trngl.x[Trngl.N].SetTriangle(Pn1,Pn_,Pn2,Edge.N,En_,BndEd.x[s].bn[ib]);

	if (ib==BndEd.x[s].bn.N-1)
	{
		*b.x	= Edge.N;
	}
	else
	{
		b.add(Edge.N);
	}
	Edge.N++;
	Trngl.N++;
	ib++;
}

void MeshConstructor::AddPnt4(Vec3db &p3, Vec3db &n3, ms1D<int> &b, int &ib, int &P_, int &Pn1, int &Pn2, int &s, int &lsb)
{
	int En1,En2;
	int inb,in1,in2,ins;

	NEdg	= Edge.N+1;

	Point.x[P_].crd	= p3;
	Point.x[P_].nor	= n3;

	Point.x[P_].n_edg->adt(Edge.N,NEdg);
	Point.x[Pn1].n_edg->add(Edge.N);
	Point.x[Pn2].n_edg->add(NEdg);

	Point.x[P_].n_fc->add(Trngl.N);
	Point.x[Pn1].n_fc->add(Trngl.N);
	Point.x[Pn2].n_fc->add(Trngl.N);

	Edge.x[BndEd.x[s].bn[ib]].n_fc.x[1]	= Trngl.N;
	Edge.x[BndEd.x[s].bn[ib]].bnd	= false;

	Point.x[Pn1].edg2	= Edge.N;
	Point.x[Pn2].edg1	= NEdg;
	
	// �� �� ���� ���� ��������������� ������� ���� ��� ���������
	if(Edge.N+EXT>=Edge.mN) Edge.adm_(AddQuantEdg);

	Edge.x[Edge.N].SetEdge(Pn1,P_,Trngl.N,-1,s);	// s-??
	Edge.x[NEdg].SetEdge(P_,Pn2,Trngl.N,-1,s);		// s-??
	
	if(Trngl.N+EXT>=Trngl.mN) Trngl.adm_(AddQuantTri);
	Trngl.x[Trngl.N].SetTriangle(Pn1,P_,Pn2,Edge.N,NEdg,BndEd.x[s].bn[ib]);	

	En1	= Point.x[P_].edg1;
	En2	= Point.x[P_].edg2;

	if (Edge.x[En2].sb==s) // �� �������'p3' ���� ��������� �
	{	// ����� �������� ���
		inb	= b.fnd(En2); // �����������'En1' ���������������. ���� �� �������� ��, ����� �������, ������ -1.
		if (inb==-1) // �� ���� ������������ � ����� ���� ������� � ��� ���
		{
			in1	= BndEd.x[s].bn.fnd(En1);
			in2	= BndEd.x[s].bn.fnd(En2);
			if(in1	==-1)
			{
				in1	= -1;
			}
			B1.pst(b);
			B1.add(Edge.N);
			if ((B1.mN-B1.N)<=(BndEd.x[s].bn.N-in2)){B1.adm(BndEd.x[s].bn.N-in2+10);}
			memcpy(B1.x+B1.N,BndEd.x[s].bn.x+in2,(BndEd.x[s].bn.N-in2)*sizeof(int));
			B1.N	+= BndEd.x[s].bn.N-in2;
			// ���� ���� ��� ����'BndEd.x'
			if (BndEd.N+EXT>=BndEd.mN) BndEd.adm_(50);
			BndEd.x[BndEd.N].bn.N=0;
			BndEd.x[BndEd.N].bn.adt(En1,NEdg);
			if (BndEd.x[BndEd.N].bn.mN<=(in1-ib+10)){BndEd.x[BndEd.N].bn.adm(in1-ib+10);}
			memcpy(BndEd.x[BndEd.N].bn.x+BndEd.x[BndEd.N].bn.N,BndEd.x[s].bn.x+ib+1,(in1-ib-1)*sizeof(int));
			BndEd.x[BndEd.N].bn.N	+= in1-ib-1;
			ib	= b.N-1;			
		}else
		{
			// ���� ���� ��� ����'BndEd.x'
			if (BndEd.N+EXT>=BndEd.mN) BndEd.adm_(50);
			BndEd.x[BndEd.N].bn.N	= 0;
			BndEd.x[BndEd.N].bn.adt(Edge.N,En2);
			if ((b.N-inb+10)>=(BndEd.x[BndEd.N].bn.mN)){BndEd.x[BndEd.N].bn.adm(b.N-inb+10);}
			memcpy(BndEd.x[BndEd.N].bn.x+BndEd.x[BndEd.N].bn.N,b.x+inb+1,(b.N-inb-1)*sizeof(int));
			BndEd.x[BndEd.N].bn.N+=	b.N-inb-1;

			B1.N	= 0;
			if (B1.mN<=(lsb-ib+inb+10)){B1.adm(BndEd.x[s].bn.N-ib+inb+10);}
			if (inb>0)
			{
				memcpy(B1.x,b.x,inb*sizeof(int));
				B1.N	= inb;
				B1.add(NEdg);
				memcpy(B1.x+B1.N,BndEd.x[s].bn.x+ib+1,(lsb-ib)*sizeof(int));
				B1.N+= lsb-ib;
				ib	= inb-2;
				b.N	= ib+1;
			}
			else
			{
				B1.adt(En1,NEdg);
				memcpy(B1.x+B1.N,BndEd.x[s].bn.x+ib+1,(lsb-ib-1)*sizeof(int));
				B1.N+= lsb-ib-1;
				ib	= -1;
				b.N	= 0;
			}
		}
		for (inb=0;inb<BndEd.x[BndEd.N].bn.N;inb++){Edge.x[BndEd.x[BndEd.N].bn.x[inb]].sb	= BndEd.N;}
		BndEd.N++;

		BndEd.x[s].bn.pst(B1);
		lsb	= BndEd.x[s].bn.N-1;
	}
	else
	{	// �� ��� ��� � ����� ������ �� ��� ���.
		/*char *nam="1qbr.pdb";		// ������������
		int l_n; l_n=80;
		ms<char> name(nam,l_n);
		ms<int> nstr(l_n);
		name.fnd(nstr,'\0');
		nstr.mmin(l_n);
		name.N=++l_n;

		out(name);*/

		ins	= Edge.x[En1].sb;
		for (inb=0;inb<BndEd.x[ins].bn.N;inb++){Edge.x[BndEd.x[ins].bn.x[inb]].sb	= s;}
		inb	= BndEd.x[ins].bn.fnd(En2);
		if (B1.mN<=(lsb+BndEd.x[ins].bn.N-ib+b.N+10)){B1.adm(lsb+BndEd.x[ins].bn.N-ib+b.N+10);}
		B1.N= 0;
		B1.pst(b);
		B1.add(Edge.N);
		memcpy(B1.x+B1.N,BndEd.x[ins].bn.x+inb,(BndEd.x[ins].bn.N-inb)*sizeof(int));
		B1.N+=BndEd.x[ins].bn.N-inb;
		memcpy(B1.x+B1.N,BndEd.x[ins].bn.x,inb*sizeof(int));
		B1.N+=inb;
		B1.add(NEdg);
		memcpy(B1.x+B1.N,BndEd.x[s].bn.x+ib+1,(lsb-ib)*sizeof(int));
		B1.N+=lsb-ib;

		BndEd.x[s].bn.pst(B1);
		lsb	= BndEd.x[s].bn.N-1;

		RmvBnd(ins);
		s	= s==BndEd.N ? ins : s;
		ib	= b.N-1;
	}
	Point.x[P_].edg2	= NEdg;
	Point.x[P_].cmb	= false;
	Edge.N	+=2;
	Trngl.N++;
}

void MeshConstructor::AddPnt7(int &ib, int &Pn1,int &Pn2,int &Pn_,int &E_n,int &En,int &En_,int &s,int &lsb)
{
	Point.x[Pn1].n_fc->add(Trngl.N);
	Point.x[Pn2].n_fc->add(Trngl.N);
	Point.x[Pn_].n_fc->add(Trngl.N);

	Point.x[Pn1].edg1 = Point.x[Pn1].edg2 = Point.x[Pn2].edg1 = Point.x[Pn2].edg2 = Point.x[Pn_].edg1 = Point.x[Pn_].edg2 = -1;

	Edge.x[En].n_fc.x[1]	= Trngl.N;
	Edge.x[En_].n_fc.x[1]	= Trngl.N;
	Edge.x[E_n].n_fc.x[1]	= Trngl.N;

	Edge.x[En].bnd	= false;
	Edge.x[En_].bnd= false;
	Edge.x[E_n].bnd= false;

	// ���� �� ����'Trngl.x'!
	if(Trngl.N+EXT>=Trngl.mN) Trngl.adm_(AddQuantTri);
	Trngl.x[Trngl.N].SetTriangle(Pn2,Pn1,Pn_,En,E_n,En_);
	Trngl.N++;
	RmvBnd(s);
	ib	= lsb;
}

void MeshConstructor::AddPnt9(Vec3db &p3, Vec3db &n3, ms1D<int> &b, int &ib, int &P_n, int &Pn1, int &Pn2, int &E_n, int &lsb)
{
	int En,s,ii,jj,a;
	s	= Edge.x[E_n].sb;
	En	= BndEd.x[s].bn.x[ib];

	ii	= Edge.x[En].n_fc.x[1]	= Edge.x[E_n].n_fc.x[0]; //  ��� ��� ������.
	Edge.x[En].bnd	= false;	// ��� ��� ���� ��� �����

	Trngl.x[ii].n_edg.x[Trngl.x[ii].n_edg.find(E_n)]	= En; // ��� ���� ��������������������.
	
	ii	= Point.x[Pn1].n_edg->fnd(E_n);		//
	Point.x[Pn1].n_edg->rem(1,ii);			// ��� ���� ������������
	Point.x[Pn1].edg1	= Point.x[Pn1].edg2	= -1;// ���� ��� ��������

	a	= Point.x[P_n].n_edg->N;
	for (jj=0;jj<a;jj++)
	{
		ii	= Edge.x[Point.x[P_n].n_edg->x[jj]].n_pnt.find(P_n);
		Edge.x[Point.x[P_n].n_edg->x[jj]].n_pnt.x[ii]	= Pn2;
	}
	a	= Point.x[P_n].n_fc->N;
	for (jj=0;jj<a;jj++)
	{
		ii	= Trngl.x[Point.x[P_n].n_fc->x[jj]].n_pnt.find(P_n);
		Trngl.x[Point.x[P_n].n_fc->x[jj]].n_pnt.x[ii]	= Pn2;
	}
	
	ii	= Point.x[P_n].n_edg->fnd(E_n);		//
	Point.x[P_n].n_edg->rem(1,ii);			// ��� � ���'P_n' ���� ����'E_n'

	Point.x[Pn2].n_edg->add(*Point.x[P_n].n_edg); // ���� �����������'Pn2' '����� ������'P_n'.
	Point.x[Pn2].n_fc->add(*Point.x[P_n].n_fc);	// ����� �����������

	Point.x[Pn2].edg1	= Point.x[P_n].edg1;	// ���� ���� ���������

	Point.x[Pn2].crd	= p3;
	Point.x[Pn2].nor	= n3;

	RmvPnt(P_n);	// ���� ���
	RmvEdg(E_n,b);	// ���� ���  (������� ����� �����������.)

	if (ib==lsb){b.N--;}
	else
	{
		if (ib==0)
		{
			BndEd.x[s].bn.N--;
			BndEd.x[s].bn.rem(1,0);
			lsb	-=2;
			ib--;
		}else
		{
			b.N--;
			a	= ib+1;
			BndEd.x[s].bn.rem(a,0);
			BndEd.x[s].bn.add(b,0);
			lsb	= BndEd.x[s].bn.N-1;
			ib	= b.N-1;
		}
	}

	// !!!
	// !!! ����� ���� ���� - � ���� � ������ ����� ����� ���. ��� ��������
	// !!! �� ���� � ����� ��� � ���������� ��, ����������� ���������� ����������.
	// !!!
	/*if (lsb==0)
	{
		if (Edge.x[BndEd.x[s].bn.x[0]].n_pnt.x[0]==Edge.x[BndEd.x[s].bn.x[0]].n_pnt.x[1])
		{
			ii	= Edge.x[BndEd.x[s].bn.x[0]].n_pnt.x[0];	// ��������� ���
			jj	= Edge.x[BndEd.x[s].bn.x[0]].n_fc.x[0];	// ��������� ������
			RmvEdg(BndEd.x[s].bn.x[0],b);	// ���� ���
			RmvPnt(cbs,ii);
			rm
		}
	}*/
}

void MeshConstructor::AddPnt10(Vec3db&p3,Vec3db &n3,ms1D<int> &b, int &ib, int &Pn1, int &Pn2, int &Pn_, int &En_, int &lsb) // �������� �� �������, �� ������� ���������
{
	int En,s,ii,jj,a;	
	s	= Edge.x[En_].sb;
	En	= BndEd.x[s].bn.x[ib];

	ii	= Edge.x[En].n_fc.x[1]	= Edge.x[En_].n_fc.x[0]; //  ��� ��� ������.
	Edge.x[En].bnd	= false;	// ��� ��� ���� ��� �����

	Trngl.x[ii].n_edg.x[Trngl.x[ii].n_edg.find(En_)]	= En; // ��� ���� ��������������������.
	
	ii	= Point.x[Pn2].n_edg->fnd(En_);		//
	if (ii == -1) 
	{
		cout<<"Error 1 in method 10"<<endl;
		cout<<"n_Point	: "<<Pn2<<endl;
		cout<<"n_En		: "<<En_<<endl;
		cout<<"n_Edges	: "<<*Point.x[Pn2].n_edg<<endl;
		cout<<"n_Edges	: "<<*Point.x[Pn1].n_edg<<endl;
		cout<<"n_Edges	: "<<*Point.x[Pn_].n_edg<<endl;
		my_exit(0);}
	Point.x[Pn2].n_edg->rem(1,ii);			// ��� ���� ������������
	Point.x[Pn2].edg1	= Point.x[Pn2].edg2	= -1;// ���� ��� ��������

	a	= Point.x[Pn_].n_edg->N;
	for (jj=0;jj<a;jj++)
	{
		ii	= Edge.x[Point.x[Pn_].n_edg->x[jj]].n_pnt.find(Pn_);
		if (ii == -1) {cout<<"Error 2 in method 10"<<endl;my_exit(0);}
		Edge.x[Point.x[Pn_].n_edg->x[jj]].n_pnt.x[ii]	= Pn1;
	}
	a	= Point.x[Pn_].n_fc->N;
	for (jj=0;jj<a;jj++)
	{
		ii	= Trngl.x[Point.x[Pn_].n_fc->x[jj]].n_pnt.find(Pn_);
		if (ii == -1) {cout<<"Error 3 in method 10"<<endl;my_exit(0);}
		Trngl.x[Point.x[Pn_].n_fc->x[jj]].n_pnt.x[ii]	= Pn1;
	}
	
	ii	= Point.x[Pn_].n_edg->fnd(En_);		//
	if (ii == -1) {cout<<"Error 4 in method 10"<<endl;my_exit(0);}
	Point.x[Pn_].n_edg->rem(1,ii);			// ��� � ���'Pn_' ���� ����'En_'

	Point.x[Pn1].n_edg->add(*Point.x[Pn_].n_edg); // ���� �����������'Pn2' '����� ������'P_n'.
	Point.x[Pn1].n_fc->add(*Point.x[Pn_].n_fc);	// ����� �����������

	Point.x[Pn1].edg2	= Point.x[Pn_].edg2;	// ���� ���� ���������

	Point.x[Pn1].crd	= p3;
	Point.x[Pn1].nor	= n3;

	RmvPnt(Pn_);	// ���� ���
	RmvEdg(En_,b);	// ���� ��� (������� ����� �����������.)

	if (ib==lsb){b.rem(1,0);}
	else
	{
		if (ib==0)
		{
			BndEd.x[s].bn.rem(2,0);
			lsb	-=2;
			ib--;
		}else
		{
			a	= ib+2;
			BndEd.x[s].bn.rem(a,0);
			BndEd.x[s].bn.add(b,0);
			lsb	= BndEd.x[s].bn.N-1;
			ib	= b.N-1;
		}
	}
	// !!!
	// !!! ����� ���� ���� - � ���� � ������ ����� ����� ���. ��� ��������
	// !!! �� ���� � ����� ��� � ���������� ��, ����������� ���������� ����������.
	// !!!
}

void MeshConstructor::RmvPnt(int &Pn)
{
	int i,j,k;
	/*i	= Point.x[Pn].cbn;
	j	= cbs.n_sp.x[i].fnd(Pn);
	if (j!=-1) cbs.n_sp.x[i].rem(1,j);
	else {
		cout<<"Error! in  'void MeshConstructor::RmvPnt(int &Pn)' "<<endl;exit (1);
	}*/
	for (i=0;i<Point.x[Pn].n_cbs->N;i++)
	{
		k	= Point.x[Pn].n_cbs->x[i];
		j	= cbs.n_sp.x[k].fnd(Pn);
		if (j!=-1) cbs.n_sp.x[k].rem(1,j);
		else {
			cout<<"Error! in  'void MeshConstructor::RmvPnt(int &Pn)' "<<endl;exit (1);
		}
	}
	NPnt	= Point.N-1;
	if (Pn!=NPnt)
	{
		for (i=0;i<Point.x[NPnt].n_edg->N;i++)
		{
			k	= Point.x[NPnt].n_edg->x[i];
			j	= Edge.x[k].n_pnt.find(NPnt);
			Edge.x[k].n_pnt.x[j]	= Pn;
		}
		for (i=0;i<Point.x[NPnt].n_fc->N;i++)
		{
			k	= Point.x[NPnt].n_fc->x[i];
			j	= Trngl.x[k].n_pnt.find(NPnt);
			Trngl.x[k].n_pnt.x[j]	= Pn;
		}
		for (i=0;i<Point.x[NPnt].n_cbs->N;i++)
		{
			k	= Point.x[NPnt].n_cbs->x[i];
			j	= cbs.n_sp.x[k].fnd(NPnt);
			cbs.n_sp.x[k].x[j]	= Pn;
		}

		Point.x[Pn]= Point.x[NPnt];
	}
	Point.x[NPnt].n_cbs->N =0;
	Point.x[NPnt].n_edg->N =0;
	Point.x[NPnt].n_fc->N =0;
	Point.N--;
}

void MeshConstructor::RmvEdg(int &En, ms1D<int> &b)
{
	int i,j;
	NEdg	= Edge.N-1;	
	if (En!=NEdg)
	{
		if (Edge.x[NEdg].bnd)
		{
			j	= Edge.x[NEdg].sb;
			i	= b.fnd(NEdg);  // ? �� b.N==0, � �����??
			if (i!=-1){b.x[i]	= En;}
			else
			{
				i	= BndEd.x[j].bn.fnd(NEdg);
				if (i!=-1){BndEd.x[j].bn.x[i]	= En;}else{	cout<<"error!!! Bound edge is not consist in bound set"<<endl;}
			}
			Point.x[Edge.x[NEdg].n_pnt.x[0]].edg2	= Point.x[Edge.x[NEdg].n_pnt.x[1]].edg1	= En;
		}

		j	= Edge.x[NEdg].n_pnt.x[0];
		i	= Point.x[j].n_edg->fnd(NEdg);
		Point.x[j].n_edg->x[i]	= En;
		j	= Edge.x[NEdg].n_pnt.x[1];
		i	= Point.x[j].n_edg->fnd(NEdg);
		Point.x[j].n_edg->x[i]	= En;

		j	= Edge.x[NEdg].n_fc.x[0];
		i	= Trngl.x[j].n_edg.find(NEdg);
		Trngl.x[j].n_edg.x[i]	= En;
		if (!Edge.x[NEdg].bnd)	//��� ���: �������� ������� � � ������ ����������.
		{
			j	= Edge.x[NEdg].n_fc.x[1];
			i	= Trngl.x[j].n_edg.find(NEdg);
			Trngl.x[j].n_edg.x[i]	= En;
		}
		Edge.x[En]	= Edge.x[NEdg];
	}
	Edge.N--;
}

void MeshConstructor::RmvBnd(int &s)
{
	BndEd.N--;
	if (s!=(BndEd.N))
	{
		BndEd.x[s].bn.pst(BndEd.x[BndEd.N].bn);
		for(int i=0;i<BndEd.x[s].bn.N;i++){Edge.x[BndEd.x[s].bn.x[i]].sb	= s;}
	}
}


void MeshConstructor::JuggleMesh(int iJ, int N0, int N1)// ������� imsh - ����� ���.
{
	Vec3db pm,p3;
	Vec3db nw;
	int i,j,k,niE,niT,iiE,iiP;

	N0	= N0<0?0:N0<Point.N?N0:Point.N;
	N1	= N1>Point.N?Point.N:N1>N0?N1:N0;
	for (i=0;i<iJ;i++)
	{			
		for (j=N0;j<N1;j++)
		{
			niE	= Point.x[j].n_edg->N;
			niT	= Point.x[j].n_fc->N;
			pm	= 0;
			nw	= 0;
			if (niE==niT)
			{
				for (k=0;k<niE;k++)
				{
					iiE	= Point.x[j].n_edg->x[k];
					iiP	= Edge.x[iiE].n_pnt.find(j);
					iiP	= iiP==0 ? Edge.x[iiE].n_pnt.x[1] : Edge.x[iiE].n_pnt.x[0];
					pm	+=Point.x[iiP].crd;
				}
				pm	/= (double)niE;
				if (Pnt2Surf(pm,p3,nw)==0)
				{
					if((p3-pm).norm()>0.1)
					{
						Pnt2Surf(pm,p3,nw);
					}
					Point.x[j].crd	= p3;
					Point.x[j].nor	= nw;
					Point.x[j].stp	= type;
				}
			}
		}
	}
	FragmPntClear();
	FragmPntCorl();
}

void MeshConstructor::ReProecMsh()
{	
	Vec3db pm,p3;
	Vec3db nw;
	int i;
	
	for (i=0;i<Point.N;i++)
	{			
		pm	= Point.x[i].crd;
		nw	= Point.x[i].nor;
		Pnt2Surf(pm,p3,nw);
		Point.x[i].crd	= p3;
		Point.x[i].nor	= nw;
		Point.x[i].stp	= type;
	}
}
/*
void MeshConstructor::ReProecMsh(ms1DVec3db &pnt, ms1DVec3db &nrm, ms1D<Vec3int> &tp, ms1Ddb &sqr, Vec3db &Crd, double &Rpr,ms1Dint &CnfPnt,ms1Dint &NCnfPnt,ms1DVec3db &p, ms1DVec3db &n, ms1Ddb &sq) // lokal'noe izmenenie setki svjazanoe s nalichiem probnogo zodna vtochke 'Crd' i radiusa 'Rpr'
{
 // tochek poverhnosti kotorye konfliktuju s tekuwim polozheniem proby
	Vec3db dp,n1;

	int i,j;
	double sqR,dp1,cs;
	sqR	*= sqR = Rpr;
	// opredelenie nomerov tochek poverhnosti kotorye konfliktuju s tekuwim polozheniem proby
	CnfPnt.N= 0;
	NCnfPnt.N= 0;
	for(i=0;i<Point.N;i++)
	{
		(Crd-Point.x[i].crd).ssqr()<sqR ? CnfPnt.add(i) : NCnfPnt.add(i);
	}
	p.init(CnfPnt.N);
	n.init(CnfPnt.N);
	sq.init(CnfPnt.N);
	for(i=0;i<CnfPnt.N;i++)
	{
		j	= CnfPnt.x[i];

		dp	= Point.x[j].crd-Crd;
		dp1	= dp.ssqr();
		n1	= dp/sqrt(dp1);

		p.x[i]	= Crd+n1*Rpr;	// proekcija tochki na sferu proby
		cs		= Point.x[j].nor.scpr(n1);
		n.x[i]	= cs > 0 ? n1 : -n1; // nomal' proekcii na sferu

		sq.x[i]	= 2*pi*sqR*(1-1/sqrt(1+abs(cs)*sqr.x[j]/(pi*dp1)));	// priblizhjonnoe znachenie plowadi jelementa proecirovannogo na sferu
	}
}
*/

void MeshConstructor::RefineMesh()	// "двоичное" улучшение сетки триангуляции. Каждое ребро разделяется попалам, треугольник - соответсвенно на 4 треугольника. Количество узлов возрастает примерно в 4 раза.
{

	Point.adm_(Edge.N);
	Edge.adm_(Edge.N+3*Trngl.N);
	Trngl.adm_(3*Trngl.N);

	int i,j,k,j1,k1;
	int ip1e2,ip1e3,ip2e3,ip2e1,ip3e1,ip3e2;	// номера новых и старых рёбер опирающиехся на старые точки
	int ie1,ie2,ie3,ip1,ip2,ip3,ipn1,ipn2,ipn3;
	Vec3db pn1,p1,n1,pn2,p2,n2,pn3,p3,n3;
	Vec3int netr;


	for(i=0;i<Trngl.N;i++)	// цикл перестановки номеров рёбер в массивах треугольниках - в соответствии с ориентацией треуголника
	{
		ie3	= Trngl.x[i].n_edg.x[0];
		ie1	= Edge.x[ie3].n_pnt.x[0];
		ie2	= Edge.x[ie3].n_pnt.x[1];
		ip1	= Trngl.x[i].n_pnt.find(ie1,ie2);
		netr.x[ip1]	= ie3;

		ie3	= Trngl.x[i].n_edg.x[1];
		ie1	= Edge.x[ie3].n_pnt.x[0];
		ie2	= Edge.x[ie3].n_pnt.x[1];
		ip1	= Trngl.x[i].n_pnt.find(ie1,ie2);
		netr.x[ip1]	= ie3;

		ie3	= Trngl.x[i].n_edg.x[2];
		ie1	= Edge.x[ie3].n_pnt.x[0];
		ie2	= Edge.x[ie3].n_pnt.x[1];
		ip1	= Trngl.x[i].n_pnt.find(ie1,ie2);
		netr.x[ip1]	= ie3;

		Trngl.x[i].n_edg	= netr;
	}

	j	= Point.N-1;
	k	= Edge.N-1;
	for(i=0;i<Edge.N;i++)	// обход по рёбрам - постоение новых точек и частичные изменения в записях структур.
	{
		j++;	// номер новой точки
		k++;	// номер нового ребра
		ip1	= Edge.x[i].n_pnt.x[0];	// номер точки начала ребра
		ip2	= Edge.x[i].n_pnt.x[1]; // номер точки конца ребра

		pn1	= 0.5*(Point.x[ip1].crd+Point.x[ip2].crd);	// середина ребра
		Pnt2Surf(pn1,p1,n1);	// точка проецируется на повверхность.

		Point.x[j].crd	= p1;
		Point.x[j].nor	= n1;
		Point.x[j].stp	= type;

		Point.x[j].n_edg->sm(6);	// все новые точки имеют ровно 6 исходящих рёбер
		Point.x[j].n_fc->sm(6);	// и 6 опирающихся треугольников
		Point.x[j].n_edg->x[0]	= i;	// новая точка запоминает номера первых двух исходящих рёбер : сначала номер старого
		Point.x[j].n_edg->x[1]	= k;	// а затем номер нового рёбер
		Point.x[j].n_edg->N	= 2;

		Edge.x[i].n_pnt.x[1]	= j;	// старое ребро меняет номер точки на своём конце
		Edge.x[k].n_pnt.x[0]	= j;	// новое ребро запоминает номера точек совего начала 
		Edge.x[k].n_pnt.x[1]	= ip2;	// и конца

		ie1	= Point.x[ip2].n_edg->fnd(i);	// точка конца старого ребра находит расположение в своём массиве номера старого ребра
		Point.x[ip2].n_edg->x[ie1]	= k;	// и меняет  его на номер нового
	}

	j	= Point.N;
	k1	= Trngl.N;
	k++;	// k=2*Edge.N;
	for(i=0;i<Trngl.N;i++)	// обход по треугольникам
	{
		//  номера старых точек образующих треугольник
		ip1	= Trngl.x[i].n_pnt.x[0];
		ip2	= Trngl.x[i].n_pnt.x[1];
		ip3	= Trngl.x[i].n_pnt.x[2];

		// номера старых рёбер треугольника
		ie1	= Trngl.x[i].n_edg.x[0];
		ie2	= Trngl.x[i].n_edg.x[1];
		ie3	= Trngl.x[i].n_edg.x[2];

		// номера новых точек образованых из середин рёбер
		ipn1	= ie1 + j;
		ipn2	= ie2 + j;
		ipn3	= ie3 + j;

		// Корректная связь вершинных точек новых треугольников и новых рёбер
		j1	= Edge.x[ie1].n_fc.x[0]==i ? 0 :1;
		if (Edge.x[ie1].n_pnt.x[0]==ip2)
		{
			ip2e1	= ie1;
			ip3e1	= ie1+Edge.N;
			Edge.x[ie1].n_fc.x[j1]			= k1+1;
			Edge.x[ie1+Edge.N].n_fc.x[j1]	= k1+2;
		}
		else
		{
			ip2e1	= ie1+Edge.N;
			ip3e1	= ie1;
			Edge.x[ie1].n_fc.x[j1]			= k1+2;
			Edge.x[ie1+Edge.N].n_fc.x[j1]	= k1+1;
		}
		j1	= Edge.x[ie2].n_fc.x[0]==i ? 0 :1;
		if (Edge.x[ie2].n_pnt.x[0]==ip3)
		{
			ip3e2	= ie2;
			ip1e2	= ie2+Edge.N;
			Edge.x[ie2].n_fc.x[j1]			= k1+2;
			Edge.x[ie2+Edge.N].n_fc.x[j1]	= k1;
		}
		else
		{
			ip3e2	= ie2+Edge.N;
			ip1e2	= ie2;
			Edge.x[ie2].n_fc.x[j1]			= k1;
			Edge.x[ie2+Edge.N].n_fc.x[j1]	= k1+2;
		}
		j1	= Edge.x[ie3].n_fc.x[0]==i ? 0 :1;
		if (Edge.x[ie3].n_pnt.x[0]==ip1)
		{
			ip1e3	= ie3;
			ip2e3	= ie3+Edge.N;
			Edge.x[ie3].n_fc.x[j1]			= k1;
			Edge.x[ie3+Edge.N].n_fc.x[j1]	= k1+1;
		}
		else
		{
			ip1e3	= ie3+Edge.N;
			ip2e3	= ie3;
			Edge.x[ie3].n_fc.x[j1]			= k1+1;
			Edge.x[ie3+Edge.N].n_fc.x[j1]	= k1;
		}

		// Новые рёбра построенные в предыдущем цикле и старые рёбра изменяют свои записи о своих треугольниках
		//j1	= Edge.x[ie1].n_fc.x[0]==i ? 0 :1
		//Edge.x[ie1].n_fc.x[j1]	= 
		


		// формирование трёх новых внутренних рёбер
		Edge.x[k].n_pnt.x[0]	= ipn2;
		Edge.x[k].n_pnt.x[1]	= ipn3;
		Edge.x[k].n_fc.x[0]		= i;
		Edge.x[k].n_fc.x[1]		= k1;

		Edge.x[k+1].n_pnt.x[0]	= ipn3;
		Edge.x[k+1].n_pnt.x[1]	= ipn1;
		Edge.x[k+1].n_fc.x[0]	= i;
		Edge.x[k+1].n_fc.x[1]	= k1+1;

		Edge.x[k+2].n_pnt.x[0]	= ipn1;
		Edge.x[k+2].n_pnt.x[1]	= ipn2;
		Edge.x[k+2].n_fc.x[0]	= i;
		Edge.x[k+2].n_fc.x[1]	= k1+2;

		// изменение данных старого треугольника - перенос его в центральный меньший
		Trngl.x[i].n_pnt.x[0]	= ipn1;
		Trngl.x[i].n_pnt.x[1]	= ipn2;
		Trngl.x[i].n_pnt.x[2]	= ipn3;

		Trngl.x[i].n_edg.x[0]	= k;
		Trngl.x[i].n_edg.x[1]	= k+1;
		Trngl.x[i].n_edg.x[2]	= k+2;

		// формирование новых угловых треуголников
		Trngl.x[k1].n_pnt.x[0]	= ip1;
		Trngl.x[k1].n_pnt.x[1]	= ipn3;
		Trngl.x[k1].n_pnt.x[2]	= ipn2;

		Trngl.x[k1].n_edg.x[0]	= k;
		Trngl.x[k1].n_edg.x[1]	= ip1e2;
		Trngl.x[k1].n_edg.x[2]	= ip1e3;

		Trngl.x[k1+1].n_pnt.x[0]	= ip2;
		Trngl.x[k1+1].n_pnt.x[1]	= ipn1;
		Trngl.x[k1+1].n_pnt.x[2]	= ipn3;

		Trngl.x[k1+1].n_edg.x[0]	= k+1;
		Trngl.x[k1+1].n_edg.x[1]	= ip2e3;
		Trngl.x[k1+1].n_edg.x[2]	= ip2e1;

		Trngl.x[k1+2].n_pnt.x[0]	= ip3;
		Trngl.x[k1+2].n_pnt.x[1]	= ipn2;
		Trngl.x[k1+2].n_pnt.x[2]	= ipn1;

		Trngl.x[k1+2].n_edg.x[0]	= k+2;
		Trngl.x[k1+2].n_edg.x[1]	= ip3e1;
		Trngl.x[k1+2].n_edg.x[2]	= ip3e2;

		// Коррекция записей в полях точек
		Point.x[ipn1].n_edg->adt(k+1,k+2);
		Point.x[ipn2].n_edg->adt(k+2,k);
		Point.x[ipn3].n_edg->adt(k,k+1);

		Point.x[ipn1].n_fc->adt(k1+1,i);
		Point.x[ipn1].n_fc->add(k1+2);
		Point.x[ipn2].n_fc->adt(k1+2,i);
		Point.x[ipn2].n_fc->add(k1);
		Point.x[ipn3].n_fc->adt(k1,i);
		Point.x[ipn3].n_fc->add(k1+1);

		j1	= Point.x[ip1].n_fc->fnd(i);
		Point.x[ip1].n_fc->x[j1]	= k1;
		j1	= Point.x[ip2].n_fc->fnd(i);
		Point.x[ip2].n_fc->x[j1]	= k1+1;
		j1	= Point.x[ip3].n_fc->fnd(i);
		Point.x[ip3].n_fc->x[j1]	= k1+2;

		k	+= 3;
		k1	+= 3;

	}

	i	= Edge.N;
	j	= 3*Trngl.N;
	Point.N	+= i;
	Edge.N	+= i+j;
	Trngl.N	+= j;

	FragmPntClear();
	FragmPntCorl();

}
//_________________________________
void MeshConstructor::TagssView()
{
	
}
//_________________________________
void MeshConstructor::RetSrf2InitBas()	// ������������
{
	Vec3db vec;
	int ii;

	eig.tns();

	if (InEig)
	{	
		for(ii=0;ii<Point.N;ii++){eig.pmv(vec,Point.x[ii].nor);Point.x[ii].nor=vec;}
		for(ii=0;ii<Point.N;ii++){eig.pmv(vec,Point.x[ii].crd);Point.x[ii].crd=vec;}
		for(ii=0;ii<Point.N;ii++){Point.x[ii].crd += pc;}
	}

	eig.tns();
}

//_________________________________
void MeshConstructor::Ret2InitBas()	// ������������
{
	Vec3db vec;
	int ii;

	eig.tns();

	if (InEig)
	{	
		for(ii=0;ii<Atom.N;ii++){eig.pmv(vec, Atom.x[ii].xyz); Atom.x[ii].xyz = vec;}
		for(ii=0;ii<Atom.N;ii++){Atom.x[ii].xyz	+= pc;}

		for(ii=0;ii<Point.N;ii++){eig.pmv(vec,Point.x[ii].nor);Point.x[ii].nor=vec;}
		for(ii=0;ii<Point.N;ii++){eig.pmv(vec,Point.x[ii].crd);Point.x[ii].crd=vec;}
		for(ii=0;ii<Point.N;ii++){Point.x[ii].crd += pc;}

		InEig	= false;
	}

	eig.tns();
}
//_________________________________
void MeshConstructor::Ret2InitBas(ms1DVec3db &pnt, ms1DVec3db &nrm)	// ������������
{
	Vec3db vec;
	int ii;

	eig.tns();

	if (InEig)
	{	
		for(ii=0;ii<Atom.N;ii++){eig.pmv(vec, Atom.x[ii].xyz); Atom.x[ii].xyz = vec;}
		for(ii=0;ii<Atom.N;ii++){Atom.x[ii].xyz	+= pc;}

		for(ii=0;ii<Point.N;ii++){eig.pmv(vec,Point.x[ii].nor);nrm.x[ii]=Point.x[ii].nor=vec;}
		for(ii=0;ii<Point.N;ii++){eig.pmv(vec,Point.x[ii].crd);Point.x[ii].crd=vec;}
		for(ii=0;ii<Point.N;ii++){pnt.x[ii]=Point.x[ii].crd += pc;}

		InEig	= false;
	}

	eig.tns();
}
//_________________________________


void MeshConstructor::CreateTess(ms1DVec3db &pnt, ms1DVec3db &nrm, ms1D<Vec3int> &tp, ms1Ddb &sqr) // ���� ���� ����������.
{
	int i,j1,j2,j3;
	ms1DVec3db m_tr(Trngl.N), m_ed(Edge.N);
	Vec3db p1,p2,n1,n2,pm,p3;
	double sq;

	pnt.init(Point.N);
	nrm.init(Point.N);
	tp.init(Point.N);
	sqr.init(Point.N);

	for(i=0;i<Point.N;i++)
	{
		pnt.x[i]	= Point.x[i].crd;
		nrm.x[i]	= Point.x[i].nor;
		tp.x[i]		= Point.x[i].stp;
	}
	for(i=0;i<Edge.N;i++)
	{
		j1	= Edge.x[i].n_pnt.x[0];
		j2	= Edge.x[i].n_pnt.x[1];
		p1	= 0.5*(Point.x[j1].crd+Point.x[j2].crd);
		n1	= Point.x[j1].nor;
		type= Point.x[j1].stp;
		if(Pnt2Surf(p1,p2,n2)==0)
		{
			m_ed.x[i]	= p2;
		}else
		{
			m_ed.x[i]	= p1;
		}
	}
	for(i=0;i<Trngl.N;i++)
	{
		j1	= Trngl.x[i].n_pnt.x[0];
		j2	= Trngl.x[i].n_pnt.x[1];
		j3	= Trngl.x[i].n_pnt.x[2];
		p1	= 0.333333333333333333333333*(Point.x[j1].crd+Point.x[j2].crd+Point.x[j3].crd);
		n1	= Point.x[j1].nor;
		type= Point.x[j1].stp;
		if(Pnt2Surf(p1,p2,n2)==0)
		{
			m_tr.x[i]	= p2;
		}else
		{
			m_tr.x[i]	= p1;
		}
	}

	for(i=0;i<Point.N;i++)
	{
		if(Point.x[i].n_fc->N==Point.x[i].n_edg->N)
		{
			sq	= 0;
			for(j1=0;j1<Point.x[i].n_edg->N;j1++)
			{
				j2	= Point.x[i].n_edg->x[j1];
				pm	= m_ed.x[j2];
				p1	= m_tr.x[Edge.x[j2].n_fc.x[0]];
				p2	= m_tr.x[Edge.x[j2].n_fc.x[1]];
				pm	-=Point.x[i].crd;
				p1	-=Point.x[i].crd;
				p2	-=Point.x[i].crd;

				p3.crss(pm,p1);
				sq	+= p3.norm();
				p3.crss(p2,pm);
				sq	+= p3.norm();
			}
			sqr.x[i] = sq;
		}
	}
	sqr	/=2;
}

double MeshConstructor::GetArea()	// полная площадь SES  поверхности
{
	int i;
	double sq;

	sq	= 0;
	for(i=0;i<Point.N;i++)
	{
		sq	+= Point.x[i].area;
	}
	return sq;
}

void MeshConstructor::SetPntArea() // определение площади поверхностных элементов
{
	int i,j1,j2;
	double sq;

	for(i=0;i<Point.N;i++)
	{
		sq	= 0;
		for(j1=0;j1<Point.x[i].n_fc->N;j1++)
		{
			j2	= Point.x[i].n_fc->x[j1];
			sq	+= Trngl.x[j2].area;
		}
		Point.x[i].area	= sq/3;
	}

}

void MeshConstructor::SetSrfArea() // ���������������������
{
	int i,j1,j2,j3;
	ms1DVec3db m_tr(Trngl.N), m_ed(Edge.N);
	Vec3db p1,p2,n1,n2,pm,p3;
	double sq;

	for(i=0;i<Edge.N;i++)
	{
		j1	= Edge.x[i].n_pnt.x[0];
		j2	= Edge.x[i].n_pnt.x[1];
		p1	= 0.5*(Point.x[j1].crd+Point.x[j2].crd);
		n1	= Point.x[j1].nor;
		type= Point.x[j1].stp;
		if(Pnt2Surf(p1,p2,n2)==0)
		{
			m_ed.x[i]	= p2;
		}else
		{
			m_ed.x[i]	= p1;
		}
	}
	for(i=0;i<Trngl.N;i++)
	{
		j1	= Trngl.x[i].n_pnt.x[0];
		j2	= Trngl.x[i].n_pnt.x[1];
		j3	= Trngl.x[i].n_pnt.x[2];
		p1	= 0.333333333333333333333333*(Point.x[j1].crd+Point.x[j2].crd+Point.x[j3].crd);
		n1	= Point.x[j1].nor;
		type= Point.x[j1].stp;
		if(Pnt2Surf(p1,p2,n2)==0)
		{
			m_tr.x[i]	= p2;
		}else
		{
			m_tr.x[i]	= p1;
		}
	}

	for(i=0;i<Point.N;i++)
	{
		if(Point.x[i].n_fc->N==Point.x[i].n_edg->N)
		{
			sq	= 0;
			for(j1=0;j1<Point.x[i].n_edg->N;j1++)
			{
				j2	= Point.x[i].n_edg->x[j1];
				pm	= m_ed.x[j2];
				p1	= m_tr.x[Edge.x[j2].n_fc.x[0]];
				p2	= m_tr.x[Edge.x[j2].n_fc.x[1]];
				pm	-=Point.x[i].crd;
				p1	-=Point.x[i].crd;
				p2	-=Point.x[i].crd;

				p3.crss(pm,p1);
				sq	+= p3.norm();
				p3.crss(p2,pm);
				sq	+= p3.norm();
			}
			Point.x[i].area = 0.5*sq;
		}
	}
}

void MeshConstructor::SetTriArea() // ���������� ������ ������
{
	int i,j,ind,ind1,ind2;

	ms1Dint *n_tr;
	Vec3db r12,r13,nrm,r0;

	double alf,bet,gam,twopi,R2;
	double aa,bb,ab,an,bn,csa,sma;

	ms1Ddb	sa_tor,alf_tor,bet_tor;
	ms1DVec3db a_sph;

	sa_tor.init(Point.N);
	alf_tor.init(Point.N);
	bet_tor.init(Point.N);
	a_sph.init(Trngl.N);

	twopi	= 2*pi;

	for(i=0;i<Point.N;i++)
	{
		switch (Point.x[i].stp.x[0])
		{
		case TwosTorus :
			sa_tor.x[i]		= -Point.x[i].nor.scpr(Twos->x[Point.x[i].stp.x[1]].z);
			alf_tor.x[i]	= asin(sa_tor.x[i]);
			gam				= sqrt(1-sa_tor.x[i]*sa_tor.x[i]);
			alf	= Point.x[i].nor.scpr(Twos->x[Point.x[i].stp.x[1]].x)/gam;
			bet	= Point.x[i].nor.scpr(Twos->x[Point.x[i].stp.x[1]].y);
			bet_tor.x[i]	= bet > 0 ? acos(alf) : twopi-acos(alf); 
			break;
			
		case ScTwosTor :
			sa_tor.x[i]		= -Point.x[i].nor.scpr(SRol->x[Point.x[i].stp.x[2]].Twos->x[Point.x[i].stp.x[1]].z);
			alf_tor.x[i]	= asin(sa_tor.x[i]);
			gam				= sqrt(1-sa_tor.x[i]*sa_tor.x[i]);
			alf	= Point.x[i].nor.scpr(SRol->x[Point.x[i].stp.x[2]].Twos->x[Point.x[i].stp.x[1]].x)/gam;
			bet	= Point.x[i].nor.scpr(SRol->x[Point.x[i].stp.x[2]].Twos->x[Point.x[i].stp.x[1]].y);
			bet_tor.x[i]	= bet > 0 ? acos(alf) : twopi-acos(alf); 
			break;

		default:
			n_tr	= Point.x[i].n_fc;
			nrm		= Point.x[i].nor;
			r0		= Point.x[i].crd;
			sma		= 0.0;
			for(j=0;j<n_tr->N-1;j++)
			{				
				ind		= Trngl.x[n_tr->x[j]].n_pnt.find(i);
				ind1	= ind+1;
				ind1	= ind1>2 ? 0 :ind1;
				ind2	= ind1 +1;
				ind2	= ind2>2 ? 0 :ind2;
				ind1	= Trngl.x[n_tr->x[j]].n_pnt.x[ind1];
				ind2	= Trngl.x[n_tr->x[j]].n_pnt.x[ind2];

				r12		= Point.x[ind1].crd-r0;
				r13		= Point.x[ind2].crd-r0;
				aa		= r12.ssqr();
				bb		= r13.ssqr();
				ab		= r12.scpr(r13);
				an		= r12.scpr(nrm);
				bn		= r12.scpr(nrm);
				csa		= (ab-an*bn)/sqrt((aa-an*an)*(bb-bn*bn));
				sma		+= a_sph.x[n_tr->x[j]].x[ind] = acos(csa);
				//r12	= Point.x[]
			}
			ind		= Trngl.x[n_tr->x[j]].n_pnt.find(i);
			a_sph.x[n_tr->x[j]].x[ind]	= twopi-sma;
			break;
		}
	}

	for(i=0;i<Trngl.N;i++)
	{
		if(Trngl.x[i].sfr)
		{
			j	= Trngl.x[i].n_pnt.x[0];
			switch (Point.x[j].stp.x[0])
			{
			case  AtomSphere:
				R2	*= R2 = Atom.x[Point.x[j].stp.x[1]].r_wdw;
				Trngl.x[i].area	= R2*(a_sph.x[i].summ()-pi);
				break;
			case  TrisSphere:
				R2	*= R2 = p_rol;
				Trngl.x[i].area	= R2*(a_sph.x[i].summ()-pi);
				break;
			case  ScStblSph1:
				R2	*= R2 = SRol->x[Point.x[j].stp.x[2]].s_rol;
				Trngl.x[i].area	= R2*(a_sph.x[i].summ()-pi);
				break;
			case  ScStblSph2:
				R2	*= R2 = SRol->x[Point.x[j].stp.x[2]].s_rol;
				Trngl.x[i].area	= R2*(a_sph.x[i].summ()-pi);
				break;
			case  ScTrisSphr:
				R2	*= R2 = SRol->x[Point.x[j].stp.x[2]].s_rol;
				Trngl.x[i].area	= R2*(a_sph.x[i].summ()-pi);
				break;
			case  TwosTorus:
			//	Trngl.x[i].area	= 0.5*();
				break;
			case  ScTwosTor:
				break;
			}
		}else
		{
		}
	}

	for(i=0;i<Trngl.N;i++)
	{
		if (Trngl.x[i].sfr)
		{}else
		{
		}
	}
}


void MeshConstructor::TplgStruct()	// ������������� �� ���������������������� ���� ������
{
	int i,j,isz;
	Vec2int ip;
	Vec3int ist1,ist2,iedg;

	isz	= 3*sizeof(int);

	// ������������ ��� �� ���� �����������
	for(i=0;i<Edge.N;i++)
	{
		ip		= Edge.x[i].n_pnt;
		ist1	= Point.x[ip.x[0]].stp;
		ist2	= Point.x[ip.x[1]].stp;
		j		= memcmp(ist1.x,ist2.x,isz);
		Edge.x[i].sfr = (j==0);
		Point.x[ip.x[0]].sfr = Point.x[ip.x[0]].sfr ? Edge.x[i].sfr : false;
		Point.x[ip.x[1]].sfr = Point.x[ip.x[1]].sfr ? Edge.x[i].sfr : false;
	}
	// ������������ ��� ������ ���� �����������
	for(i=0;i<Trngl.N;i++)
	{
		iedg			= Trngl.x[i].n_edg;
		Trngl.x[i].sfr	= (Edge.x[iedg.x[0]].sfr)&&(Edge.x[iedg.x[1]].sfr)&&(Edge.x[iedg.x[2]].sfr);
	}

}

void MeshConstructor::HLTplgBndr()	// �����"����� ��� ��� ������ �������������
{
	int i;

	for(i=0;i<Point.N;i++)
	{
		if (!Point.x[i].sfr)
		{
			Point.x[i].clr.x[0]	= 0;
			Point.x[i].clr.x[1]	= 1;
			Point.x[i].clr.x[2]	= 0;
			//Point.x[i].clr	= 1.0-Point.x[i].clr;
		}
	}
}

void MeshConstructor::dat2wrl(ms1D<double> &D)
{
	int i,j;
	smschar p(10);

	double vn,vm, alfa,mn;

	D.mmin(vn);
	D.mmax(vm);

	mn	= D.sum()/D.N;

	alfa	= 1/(vm-vn);
	
	//p.pst(name);
	p.x[p.N-10]	= 'D';
	p.x[p.N-9]	= 'A';
	p.x[p.N-8]	= 'T';
	p.x[p.N-7]	= 'A';
	p.x[p.N-6]	= '.';
	p.x[p.N-5]	= 'v';
	p.x[p.N-4]	= 'r';
	p.x[p.N-3]	= 'm';
	p.x[p.N-2]	= 'l';
	p.x[p.N-1]	= '\0';
	//p.N++;

	fstream sss;
	sss.open(p.x,ios::out);
	sss.precision(17);
	sss<<"#VRML V2.0 utf8"<<'\n';
	sss<<"WorldInfo { info  [\"Surface\"]}"<<'\n';
	sss<<"Background{ skyColor 0 0 0}"<<'\n';
	sss<<"Group{children["<<'\n';


	/*sss<<"Shape {"<<endl;
	sss<<"geometry IndexedLineSet {"<<endl;
	sss<<"colorPerVertex FALSE"<<endl;
	sss<<"coord Coordinate {"<<endl;
	sss<<"point [ "<<endl;
	sss<< rmn;
	sss<< 1+rmn.x[0]<<" "<<rmn.x[1]<<" "<<rmn.x[2]<<" "<<endl;
	sss<< rmn.x[0]<<" "<<1+rmn.x[1]<<" "<<rmn.x[2]<<" "<<endl;
	sss<< rmn.x[0]<<" "<<rmn.x[1]<<" "<<1+rmn.x[2]<<" "<<endl;
	sss<<"] }"<<endl;			
	sss<<"coordIndex [ 0 1 -1 0 2 -1 0 3 ]"<<endl;
	sss<<"color Color {"<<endl;
	sss<<"color [ 1 0 0, 0 1 0,  0 0 1]}"<<endl;
	sss<<"	}	}"<<endl;//*/


	sss<<"Shape	{appearance Appearance	{material Material {}}	geometry IndexedFaceSet{"<<'\n';//emissiveColor 	material Material {diffuseColor 0 1 1}	  diffuseColor 0 1 1	
	sss<<"solid FALSE"<<'\n';
	sss<<"coord Coordinate {point ["<<'\n';
	for (i=0;i<Point.N;i++)
	{
		sss.width(15);
		sss<<Point.x[i].crd;
	}
	sss<<"]	}coordIndex ["<<'\n';
	for (i=0;i<<Trngl.N;i++)
	{
		sss.width(7);
		sss<<Trngl.x[i].n_pnt.x[0]<<' '<<Trngl.x[i].n_pnt.x[1]<<' '<<Trngl.x[i].n_pnt.x[2]<<' '<<-1<<' ';		
	}
	sss<<'\n'<<"	]"<<'\n';

	sss<<"color Color	{color ["<<'\n';
	for (i=0;i<Point.N;i++)
	{
		sss.width(7);
		sss<<alfa*(D.x[i]-vn)<<' '<<0<<' '<<1-alfa*(D.x[i]-vn)<<' '<<'\n';
	}
	/*for (i=0;i<(int)P.N/2;i++)
	{
		sss.width(7);
		sss<<0<<' '<<1-(double)i/(P.N/2-1)<<' '<<(double)i/(P.N/2-1)<<' '<<'\n';
	}//*/
	sss<<"] } } }"<<'\n';	//*/
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
	/*sss<<"Inline {url[\"1.vrml\"]}"<<endl;
	sss<<"Inline {url[\"2.vrml\"]}"<<endl;*/
	sss.close();
}

void MeshConstructor::ReProecMsh(ms1DVec3db &pnt, ms1DVec3db &nrm, ms1D<Vec3int> &tp, ms1Ddb &sqr, Vec3db &Crd, double &Rpr,ms1Dint &CnfPnt,ms1Dint &NCnfPnt,ms1DVec3db &p, ms1DVec3db &n, ms1Ddb &sq) // ���������������������� ���� ������ 'Crd' �����'Rpr'
{
//	ms1Dint CnfPnt(1); // ������������������ ���� ����� ��
	Vec3db dp,n1;
//	ms1DVec3db p,n;
//	ms1Ddb	sq;
	int i,j;
	double sqR,dp1,cs;
	sqR	*= sqR = Rpr;
	// ���������������������������� ���� ����� ��
	CnfPnt.N= 0;
	NCnfPnt.N= 0;
	for(i=0;i<Point.N;i++)
	{
		(Crd-Point.x[i].crd).ssqr()<sqR ? CnfPnt.add(i) : NCnfPnt.add(i);
	}
	p.init(CnfPnt.N);
	n.init(CnfPnt.N);
	sq.init(CnfPnt.N);
	for(i=0;i<CnfPnt.N;i++)
	{
		j	= CnfPnt.x[i];

		dp	= Point.x[j].crd-Crd;
		dp1	= dp.ssqr();
		n1	= dp/sqrt(dp1);

		p.x[i]	= Crd+n1*Rpr;	// ���� ���� �����
		cs		= Point.x[j].nor.scpr(n1);
		n.x[i]	= cs > 0 ? n1 : -n1; // ��� ���� � ���

		sq.x[i]	= 2*pi*sqR*(1-1/sqrt(1+abs(cs)*sqr.x[j]/(pi*dp1)));	// ���������� ����������������� ���
	}
}

void MeshConstructor::SetProbePr(ms1Dint &CnfPnt,ms1DVec3db &p, ms1DVec3db &n) // ���� ������������������� ���(����� - ����� � ���������)
{
	int i,j;
	for(i=0;i<CnfPnt.N;i++)
	{
		j	= CnfPnt.x[i];
		Point.x[j].crd	= p.x[i];
		Point.x[j].nor	= n.x[i];
	}
}


void MeshConstructor::S_GB_Radii(ms1DVec3db &pnt, ms1DVec3db &nrm, ms1Ddb &sqr,ms1Ddb &AtBrnRd,ms1Ddb &AG) // ����� ��������� (� ������ ������
{
	int i,j;
	Vec3db p0,p1,p2,n0,n1,n2;
	Vec3db dp;
	double a,h1,h2,h3,hf;
	ms1Ddb it1,it2,it3,it4;

	double Kk	= 332.0716;	// ��������� ���/��

	it1.init(Atom.N);
	it2.init(Atom.N);
	it3.init(Atom.N);
	it4.init(Atom.N);
	for(i=0;i<Atom.N;i++)
	{
		p0	= Atom.x[i].xyz;
		for(j=0;j<pnt.N;j++)
		{
			dp	= pnt.x[i]-p0;
			a	= dp.scpr(nrm.x[i])*sqr.x[j];
			h2	*= h2 = h3 = 1/dp.ssqr();
			hf	= a*h2;
			h1	= sqrt(h3);

			it1.x[i]	+= hf;
			hf*=h1;

			it2.x[i]	+= hf;
			hf*=h1;

			it3.x[i]	+= hf;
			hf*=h1;

			it4.x[i]	+= hf;
		}
		it1.x[i]	= it1.x[i]>0 ? it1.x[i] : 0; 
		it2.x[i]	= it2.x[i]>0 ? it2.x[i] : 0; 
		it3.x[i]	= it3.x[i]>0 ? it3.x[i] : 0; 
		it4.x[i]	= it4.x[i]>0 ? it4.x[i] : 0; 

	}

	AtBrnRd.init(Atom.N);
	for(i=0;i<Atom.N;i++)
	{
		AtBrnRd.x[i]=AG.x[4]-(AG.x[0]*it1.x[i]+AG.x[1]*sqrt(it2.x[i])+AG.x[2]*pow(it3.x[i],0.333333333333333333)+AG.x[3]*pow(it4.x[i],0.25));
	}
	for(i=0;i<Atom.N;i++)
	{
		AtBrnRd.x[i]	= -0.5*Kk/AtBrnRd.x[i];
	}

}

void MeshConstructor::S_GB_Radii(ms1DVec3db &pnt, ms1DVec3db &nrm, ms1Ddb &sqr,ms1Ddb &AG) // ����� ��������� (� ������ ������
{
	int i,j;
	Vec3db p0,p1,p2,n0,n1,n2;
	Vec3db dp;
	double a,h1,h2,h3,hf;
	ms1Ddb it1,it2,it3,it4;
	ms1Ddb jt1,jt2,jt3,jt4;
	ms1Ddb AtBrnRd;

	double Kk	= 332.0716;	// ��������� ���/��

	it1.init(Atom.N);
	it2.init(Atom.N);
	it3.init(Atom.N);
	it4.init(Atom.N);

	jt1.init(pnt.N);
	jt2.init(pnt.N);
	jt3.init(pnt.N);
	jt4.init(pnt.N);

	for(i=0;i<Atom.N;i++)
	{
		p0	= Atom.x[i].xyz;
		for(j=0;j<pnt.N;j++)
		{
			dp	= pnt.x[j]-p0;
			a	= dp.scpr(nrm.x[j])*sqr.x[j];
			h2	*= h2 = h3 = 1/dp.ssqr();
			hf	= a*h2;
			h1	= sqrt(h3);

			it1.x[i]	+= jt1.x[j] = hf;
			hf*=h1;

			it2.x[i]	+= jt2.x[j] = hf;
			hf*=h1;

			it3.x[i]	+= jt3.x[j] = hf;
			hf*=h1;

			it4.x[i]	+= jt4.x[j] = hf;

		}
/*		it1.x[i]	= it1.x[i]>0 ? it1.x[i] : 0; 
		it2.x[i]	= it2.x[i]>0 ? it2.x[i] : 0; 
		it3.x[i]	= it3.x[i]>0 ? it3.x[i] : 0; 
		it4.x[i]	= it4.x[i]>0 ? it4.x[i] : 0; /**/

	}

	/*it1.data2file("it1.txt");
	it2.data2file("it2.txt");
	it3.data2file("it3.txt");
	it4.data2file("it4.txt");*/



/*	// ����� � ������ � ���

	double Ee	= (1-1/80);
	Ee	= (1/E_in-1/E_out);
	AtBrnRd.init(Atom.N);
	for(i=0;i<Atom.N;i++)
	{
		AtBrnRd.x[i]= (AG.x[4]+AG.x[0]*it1.x[i]+AG.x[1]*sqrt(it2.x[i])+AG.x[2]*pow(it3.x[i],0.333333333333333333)+AG.x[3]*pow(it4.x[i],0.25));
	}
	double Gself,Ginter;

	Gself	= -Kk*Ee*(Q*Q).spr(AtBrnRd);

	for(i=0;i<Atom.N;i++)
	{
		AtBrnRd.x[i]	= -0.5/AtBrnRd.x[i];
	}

	Ginter=0.0;
	double Rr;
	for(i=0;i<AtBrnRd.N;i++)
	{
		for(j=0;j<i;j++)
		{
			Rr		=  (Atom.x[i].xyz-Atom.x[j].xyz).ssqr();
			a		=  AtBrnRd.x[i]*AtBrnRd.x[j];
			h1		=  Rr+a*exp(-Rr/(koeff*a));
			//if (h1<0 ) cout<<i<<"  "<<j<<"  "<<a<<"  "<<h1<<endl;
			Ginter	+= Q.x[i]*Q.x[j]/sqrt(h1);
		}			
	}

	Ginter *= -Kk*Ee;
	Gtot	= Gself+Ginter;
	cout.precision(17);
	cout<<"Total GB: " <<Gtot<<endl;
/**/

	double Ee	= (1-1/80);
	Ee	= (1/E_in-1/E_out);

	AtBrnRd.init(Atom.N);
	for(i=0;i<Atom.N;i++)
	{
		AtBrnRd.x[i]=AG.x[4]-(AG.x[0]*it1.x[i]+AG.x[1]*sqrt(it2.x[i])+AG.x[2]*pow(it3.x[i],0.333333333333333333)+AG.x[3]*pow(it4.x[i],0.25));
	}


	double Gself,Ginter;
	Gself	= (Q*Q).spr(AtBrnRd);
		
	for(i=0;i<Atom.N;i++)
	{
		AtBrnRd.x[i]	= -0.5*Kk*Ee/AtBrnRd.x[i];
	}

	BR.pst(AtBrnRd);
//	AtBrnRd.data2file("Born.txt");

	Ginter=0.0;
	double Rr;
	for(i=0;i<AtBrnRd.N;i++)
	{
		for(j=0;j<i;j++)
		{
			Rr		=  (Atom.x[i].xyz-Atom.x[j].xyz).ssqr();
			a		=  AtBrnRd.x[i]*AtBrnRd.x[j];
			h1		=  Rr+a*exp(-Rr/(koeff*a));
			//if (h1<0 ) cout<<i<<"  "<<j<<"  "<<a<<"  "<<h1<<endl;
			Ginter	+= Q.x[i]*Q.x[j]/sqrt(h1);
		}			
	}

	Ginter *= -Kk*Ee;
	Gtot	= Gself+Ginter;
	/*cout.precision(17);
	cout<<"Total GB: " <<Gtot<<endl;
/*	*/
}

void MeshConstructor::S_GB_Radii(ms1DVec3db &pnt, ms1DVec3db &nrm, ms1Ddb &sqr,ms1Ddb &AtBrnRd,ms1Ddb &AG,Vec3db &Crd, double &Rpr, double &Rbr) // ����� ��������� (� ����� ������
{
	ms1DVec3db pp,nn;
	ms1Dint CnfPnt,NCnfPnt;
	ms1D<Vec3int> tp;
	ms1Ddb ssq;

	int i,j,k;
	Vec3db p0,p1,p2,n0,n1,n2;
	Vec3db dp;
	double a,h1,h2,h3,hf;
	ms1Ddb it1,it2,it3,it4;

	double Kk	= 332.0716;	// ��������� ���/��

	bool ch;

	ReProecMsh(pnt,nrm,tp,sqr,Crd,Rpr,CnfPnt,NCnfPnt,pp,nn,ssq);	// ����� ���� �����

	a	= MY_INFINITY;
	for(i=0;i<pnt.N;i++)
	{
		if((pnt.x[i]-Crd).ssqr()<a){j=i;a=(pnt.x[i]-Crd).ssqr();}
	}
	ch	= (pnt.x[j]-Crd).scpr(nrm.x[j])<0;	// true - �� �����������������false - ��� ������

	// ��������� ��������������������

	it1.init(Atom.N);
	it2.init(Atom.N);
	it3.init(Atom.N);
	it4.init(Atom.N);

	for(i=0;i<Atom.N;i++)	// ������� � ������ ���
	{
		p0	= Atom.x[i].xyz;
		for(k=0;k<NCnfPnt.N;k++)
		{
			j	= NCnfPnt.x[k];
			dp	= pnt.x[j]-p0;
			a	= dp.scpr(nrm.x[j])*sqr.x[j];
			h2	*= h2 = h3 = 1/dp.ssqr();
			hf	= a*h2;
			h1	= sqrt(h3);

			it1.x[i]	+= hf;
			hf*=h1;

			it2.x[i]	+= hf;
			hf*=h1;

			it3.x[i]	+= hf;
			hf*=h1;

			it4.x[i]	+= hf;
		}
	}	
	for(i=0;i<Atom.N;i++)	// ������� � ����� ���
	{
		p0	= Atom.x[i].xyz;
		for(j=0;j<CnfPnt.N;j++)
		{
			dp	= pp.x[j]-p0;
			a	= dp.scpr(nn.x[j])*ssq.x[j];
			h2	*= h2 = h3 = 1/dp.ssqr();
			hf	= a*h2;
			h1	= sqrt(h3);

			it1.x[i]	+= hf;
			hf*=h1;

			it2.x[i]	+= hf;
			hf*=h1;

			it3.x[i]	+= hf;
			hf*=h1;

			it4.x[i]	+= hf;
		}
	}

	if (ch)	// �� �������������� � ���� ���� � ��������������
	{
		for(i=0;i<Atom.N;i++)	// ������� � ����� ���
		{
			dp	= Atom.x[i].xyz-Crd;
			h1	= dp.norm();
			h2	= h1*h1-Rpr*Rpr;
			it1.x[i]	+= pi*(2*h1*Rpr/h2+log((h1-Rpr)/(h1+Rpr)))/h1;
			it2.x[i]	+= 8*pi*(Rpr*Rpr*Rpr/(h2*h2))/(3*h1);
			it3.x[i]	+= 4*pi*(Rpr*Rpr*Rpr)/(h2*h2*h2);
			it4.x[i]	+= 16*pi*(Rpr*Rpr*Rpr*(5*h1*h1+Rpr*Rpr)/(h2*h2*h2*h2))/(15*h1);
		}
	}
	
	for(i=0;i<Atom.N;i++)
	{
		it1.x[i]	= it1.x[i]>0 ? it1.x[i] : 0;
		it2.x[i]	= it2.x[i]>0 ? it2.x[i] : 0; 
		it3.x[i]	= it3.x[i]>0 ? it3.x[i] : 0; 
		it4.x[i]	= it4.x[i]>0 ? it4.x[i] : 0; 
	}

	AtBrnRd.init(Atom.N);
	for(i=0;i<Atom.N;i++)
	{
		AtBrnRd.x[i]=AG.x[4]-(AG.x[0]*it1.x[i]+AG.x[1]*sqrt(it2.x[i])+AG.x[2]*pow(it3.x[i],0.333333333333333333)+AG.x[3]*pow(it4.x[i],0.25));
	}
	for(i=0;i<Atom.N;i++)
	{
		AtBrnRd.x[i]	= -0.5*Kk/AtBrnRd.x[i];
	}

	// ����� ���������� ��
	it1.x[0] = it2.x[0] = it3.x[0] = it4.x[0] = 0;
	for(k=0;k<NCnfPnt.N;k++)
	{
		j	= NCnfPnt.x[k];
		dp	= pnt.x[i]-Crd;
		a	= dp.scpr(nrm.x[i])*sqr.x[j];
		h2	*= h2 = h3 = 1/dp.ssqr();
		hf	= a*h2;
		h1	= sqrt(h3);
		
		it1.x[0]	+= hf;
		hf*=h1;
		
		it2.x[0]	+= hf;
		hf*=h1;
		
		it3.x[0]	+= hf;
		hf*=h1;
		
		it4.x[0]	+= hf;
	}
	for(j=0;j<CnfPnt.N;j++)
	{
		dp	= pp.x[j]-Crd;
		a	= dp.scpr(nn.x[j])*ssq.x[j];
		h2	*= h2 = h3 = 1/dp.ssqr();
		hf	= a*h2;
		h1	= sqrt(h3);
		
		it1.x[0]	+= hf;
		hf*=h1;
		
		it2.x[0]	+= hf;
		hf*=h1;
		
		it3.x[0]	+= hf;
		hf*=h1;
		
		it4.x[0]	+= hf;
	}
	if (ch)
	{
		it1.x[0]	+= 4*pi/Rpr;
		it2.x[0]	+= 4*pi/(Rpr*Rpr);
		it3.x[0]	+= 4*pi/(Rpr*Rpr*Rpr);
		it4.x[0]	+= 4*pi/(Rpr*Rpr*Rpr*Rpr);
	}
	it1.x[0]	= it1.x[0]>0 ? it1.x[0] : 0;
	it2.x[0]	= it2.x[0]>0 ? it2.x[0] : 0; 
	it3.x[0]	= it3.x[0]>0 ? it3.x[0] : 0;
	it4.x[0]	= it4.x[0]>0 ? it4.x[0] : 0;

	Rbr	= AG.x[4]-(AG.x[0]*it1.x[0]+AG.x[1]*sqrt(it2.x[0])+AG.x[2]*pow(it3.x[0],0.333333333333333333)+AG.x[3]*pow(it4.x[0],0.25));
	Rbr	= -0.5*Kk/Rbr;
}

void MeshConstructor::S_GB_Radii(ms1DVec3db &pnt, ms1DVec3db &nrm, ms1Ddb &sqr,ms1D<ms1Ddb> &AtBrnRd,ms1Ddb &AG,ms1DVec3db &Crd, ms1Ddb &Rpr,ms1Ddb &Rbr) // ����� ��������� (� ����� ������
{
	ms1DVec3db pp,nn;
	ms1Dint CnfPnt,NCnfPnt;
	ms1D<Vec3int> tp;
	ms1Ddb ssq;

	int i,j,k,ipr;
	Vec3db p0,p1,p2,n0,n1,n2;
	Vec3db dp;
	double a,h1,h2,h3,hf,it10,it20,it30,it40,RR;
	ms1Ddb it1,it2,it3,it4,it1_,it2_,it3_,it4_;

	double Kk	= 332.0716;	// ��������� ���/��

	bool ch;

	it1.init(Atom.N);
	it2.init(Atom.N);
	it3.init(Atom.N);
	it4.init(Atom.N);
	it1_.init(Atom.N);
	it2_.init(Atom.N);
	it3_.init(Atom.N);
	it4_.init(Atom.N);

	for(i=0;i<Atom.N;i++)	// ������� � �� ������
	{
		p0	= Atom.x[i].xyz;
		for(j=0;j<pnt.N;j++)
		{
			dp	= pnt.x[j]-p0;
			a	= dp.scpr(nrm.x[j])*sqr.x[j];
			h2	*= h2 = h3 = 1/dp.ssqr();
			hf	= a*h2;
			h1	= sqrt(h3);

			it1_.x[i]	+= hf;
			hf*=h1;

			it2_.x[i]	+= hf;
			hf*=h1;

			it3_.x[i]	+= hf;
			hf*=h1;

			it4_.x[i]	+= hf;
		}
	}



	for(ipr=0;ipr<Crd.N;ipr++)
	{
		RR	= Rpr.x[ipr];
		a	= MY_INFINITY;
		for(i=0;i<pnt.N;i++)
		{
			if((pnt.x[i]-Crd.x[ipr]).ssqr()<a){j=i;a=(pnt.x[i]-Crd.x[ipr]).ssqr();}
		}
		ch	= (pnt.x[j]-Crd.x[ipr]).scpr(nrm.x[j])<0;	// true - �� �����������������false - ��� ������


		ReProecMsh(pnt,nrm,tp,sqr,Crd.x[ipr],Rpr.x[ipr],CnfPnt,NCnfPnt,pp,nn,ssq);	// ����� ���� �����
		it1	= 0;
		it2	= 0;
		it3	= 0;
		it4	= 0;

		if (CnfPnt.N!=0)
		{
			for(i=0;i<Atom.N;i++)	// ������� � ����� ���(�������� � �����)
			{
				p0	= Atom.x[i].xyz;
				for(j=0;j<CnfPnt.N;j++)
				{
					k	= CnfPnt.x[j];
					dp	= pnt.x[k]-p0;
					a	= dp.scpr(nrm.x[k])*sqr.x[k];
					h2	*= h2 = h3 = 1/dp.ssqr();
					hf	= a*h2;
					h1	= sqrt(h3);
					
					it1.x[i]	-= hf;
					hf*=h1;
					
					it2.x[i]	-= hf;
					hf*=h1;
					
					it3.x[i]	-= hf;
					hf*=h1;
					
					it4.x[i]	-= hf;
				}
			}
			for(i=0;i<Atom.N;i++)	// ������� � ����� ���(����� ��� ��������)
			{
				p0	= Atom.x[i].xyz;
				for(j=0;j<CnfPnt.N;j++)
				{
					dp	= pp.x[j]-p0;
					a	= dp.scpr(nn.x[j])*ssq.x[j];
					h2	*= h2 = h3 = 1/dp.ssqr();
					hf	= a*h2;
					h1	= sqrt(h3);
					
					it1.x[i]	+= hf;
					hf*=h1;
					
					it2.x[i]	+= hf;
					hf*=h1;
					
					it3.x[i]	+= hf;
					hf*=h1;
					
					it4.x[i]	+= hf;
				}
			}
		}

		it1	+= it1_;
		it2	+= it2_;
		it3	+= it3_;
		it4	+= it4_;

		if (ch)
		{
			for(i=0;i<Atom.N;i++)	// ������� � ����� ���
			{
				dp	= Atom.x[i].xyz-Crd.x[ipr];
				h1	= dp.norm();
				h2	= h1*h1-RR*RR;
				it1.x[i]	+= pi*(2*h1*RR/h2+log((h1-RR)/(h1+RR)))/h1;
				it2.x[i]	+= 8*pi*(RR*RR*RR/(h2*h2))/(3*h1);
				it3.x[i]	+= 4*pi*(RR*RR*RR)/(h2*h2*h2);
				it4.x[i]	+= 16*pi*(RR*RR*RR*(5*h1*h1+RR*RR)/(h2*h2*h2*h2))/(15*h1);
			}
		}
		for(i=0;i<Atom.N;i++)
		{
			it1.x[i]	= it1.x[i]>0 ? it1.x[i] : 0;
			it2.x[i]	= it2.x[i]>0 ? it2.x[i] : 0; 
			it3.x[i]	= it3.x[i]>0 ? it3.x[i] : 0; 
			it4.x[i]	= it4.x[i]>0 ? it4.x[i] : 0; 
		}

		AtBrnRd.x[ipr].init(Atom.N);
		for(i=0;i<Atom.N;i++)
		{
			AtBrnRd.x[ipr].x[i]=AG.x[4]-(AG.x[0]*it1.x[i]+AG.x[1]*sqrt(it2.x[i])+AG.x[2]*pow(it3.x[i],0.333333333333333333)+AG.x[3]*pow(it4.x[i],0.25));
		}
		for(i=0;i<Atom.N;i++)
		{
			AtBrnRd.x[ipr].x[i]	= -0.5*Kk/AtBrnRd.x[ipr].x[i];
		}

		// ����� ���������� ��
		it10 = it10 = it1.x[2] = it1.x[3] = 0;
		for(k=0;k<NCnfPnt.N;k++)
		{
			j	= NCnfPnt.x[k];
			dp	= pnt.x[i]-Crd.x[ipr];
			a	= dp.scpr(nrm.x[i])*sqr.x[j];
			h2	*= h2 = h3 = 1/dp.ssqr();
			hf	= a*h2;
			h1	= sqrt(h3);
			
			it10	+= hf;
			hf*=h1;
			
			it20	+= hf;
			hf*=h1;
			
			it30	+= hf;
			hf*=h1;
			
			it40	+= hf;
		}
		for(j=0;j<CnfPnt.N;j++)
		{
			dp	= pp.x[j]-Crd.x[ipr];
			a	= dp.scpr(nn.x[j])*ssq.x[j];
			h2	*= h2 = h3 = 1/dp.ssqr();
			hf	= a*h2;
			h1	= sqrt(h3);
			
			it10	+= hf;
			hf*=h1;
			
			it20	+= hf;
			hf*=h1;
			
			it30	+= hf;
			hf*=h1;
			
			it40	+= hf;
		}
		if (ch)
		{
			it10	+= 4*pi/RR;
			it20	+= 4*pi/(RR*RR);
			it30	+= 4*pi/(RR*RR*RR);
			it40	+= 4*pi/(RR*RR*RR*RR);
		}
		it10	= it10>0 ? it10 : 0;
		it20	= it20>0 ? it20 : 0; 
		it30	= it30>0 ? it30 : 0;
		it40	= it40>0 ? it40 : 0;
		
		Rbr.x[ipr]	= AG.x[4]-(AG.x[0]*it10+AG.x[1]*sqrt(it20)+AG.x[2]*pow(it30,0.333333333333333333)+AG.x[3]*pow(it40,0.25));
		Rbr.x[ipr]	= -0.5*Kk/Rbr.x[ipr];
	}
}

void MeshConstructor::SetTwosDiff()// ����������������� �������� � ����� ��������(��).
{
	double a,b,c,dc,h,h1,h2,sqc;
	Vec3db r12,dr12;

	int i,j1,j2;
	for(i=0;i<Twos->N;i++)
	{
		Twos->x[i].dpc->init(6);
		Twos->x[i].dz->init(6);
		Twos->x[i].dh->init(6);

		j1	= Twos->x[i].n_at.x[0];
		j2	= Twos->x[i].n_at.x[1];

		a*= a = Atom.x[j1].r_wdw+p_rol;
		b*= b = Atom.x[j2].r_wdw+p_rol;
		r12	= Atom.x[j2].xyz-Atom.x[j1].xyz;

		c*=	c = sqc	= Twos->x[i].z.scpr(r12);
		h	= Twos->x[i].hab.x[0];
		h1	= (a-b)/c;
		h2	= (0.5*(a+b-c)/h-h);
		sqc	= 1/sqc;
		//h*=	h = (a+c-b);
		//h	= 0.5*sqrt(4*a*c-h)/sqc;

		// dr1=|dx 0 0|, dr2=|0 0 0|.
		dc	= -r12.x[0]/c;
//! ���� ���
		Twos->x[i].dh->x[0]			= dc*h2;

		Twos->x[i].dpc->x[0]		= -r12*h1*dc;
		Twos->x[i].dpc->x[0].x[0]	+= 0.5*(1-h1);

		Twos->x[i].dz->x[0]			= -Twos->x[i].z*dc;
		Twos->x[i].dz->x[0].x[0]	-= sqc;

		// dr1=|0 dy 0|, dr2=|0 0 0|.
		dc	= -r12.x[1]/c;

		Twos->x[i].dh->x[1]			= dc*h2;

		Twos->x[i].dpc->x[1]		= -r12*h1*dc;
		Twos->x[i].dpc->x[1].x[1]	+= 0.5*(1-h1);
		
		Twos->x[i].dz->x[1]			= -Twos->x[i].z*dc;
		Twos->x[i].dz->x[1].x[1]	-= sqc;

		// dr1=|0 0 dz|, dr2=|0 0 0|.
		dc	= -r12.x[2]/c;

		Twos->x[i].dh->x[2]			= dc*h2;

		Twos->x[i].dpc->x[2]		= -r12*h1*dc;
		Twos->x[i].dpc->x[2].x[2]	+= 0.5*(1-h1);

		Twos->x[i].dz->x[2]			= -Twos->x[i].z*dc;
		Twos->x[i].dz->x[2].x[2]	-= sqc;


		// dr1=|0 0 0|, dr2=|dx 0 0|.

		Twos->x[i].dpc->x[3]		= -Twos->x[i].dpc->x[0];
		Twos->x[i].dpc->x[3].x[0]	+= 1;
		Twos->x[i].dz->x[3]			= -Twos->x[i].dz->x[0];
		Twos->x[i].dh->x[3]			= -Twos->x[i].dh->x[0];

		// dr1=|0 0 0|, dr2=|0 dy 0|.

		Twos->x[i].dpc->x[4]		= -Twos->x[i].dpc->x[1];
		Twos->x[i].dpc->x[4].x[1]	+= 1;
		Twos->x[i].dz->x[4]			= -Twos->x[i].dz->x[1];
		Twos->x[i].dh->x[4]			= -Twos->x[i].dh->x[1];

		// dr1=|0 0 0|, dr2=|0 0 dz|.

		Twos->x[i].dpc->x[5]		= -Twos->x[i].dpc->x[2];
		Twos->x[i].dpc->x[5].x[2]	+= 1;
		Twos->x[i].dz->x[5]			= -Twos->x[i].dz->x[2];
		Twos->x[i].dh->x[5]			= -Twos->x[i].dh->x[2];


		/** /cout<<"i : "<<i<<endl;
		cout<<"dpc : \n"<<*Twos->x[i].dpc<<endl;
		cout<<"dz : \n"<<*Twos->x[i].dz<<endl;
		cout<<"dh : \n"<<*Twos->x[i].dh<<endl;//*/
	}
}

void MeshConstructor::SetTrisDiff()// ����������������� �������� � ����� �. ���
{
	double a,b,c,f,g,e,CA,CB,CG,SG,h,xf,yg,dh,df,dg,de,dxf,dyg,dSG,dCA,dCB,dCG;
	Vec3db	x,y,z,z0,dz1,dz2,dz,pc,dpc,r12,r13,r23,dr1,dr2,dr3,dr12,dr13,dr23;

	int i,j1,j2,j3;
	for(i=0;i<Tris->N;i++)
	{
		Tris->x[i].dpc->init(9);
		j1	= Tris->x[i].n_at->x[0];
		j2	= Tris->x[i].n_at->x[1];
		j3	= Tris->x[i].n_at->x[2];

		a	*= a	= Atom.x[j1].r_wdw+p_rol;
		b	*= b	= Atom.x[j2].r_wdw+p_rol;
		c	*= c	= Atom.x[j3].r_wdw+p_rol;

		r12	= Atom.x[j2].xyz-Atom.x[j1].xyz;
		r13	= Atom.x[j3].xyz-Atom.x[j1].xyz;
		r23	= r13-r12;

		f	= r12.ssqr();
		g	= r13.ssqr();
		e	= r23.ssqr();

		CA	= a+f-b;
		CB	= a+g-c;
		CG	= f+g-e;
		SG	= 4*f*g-CG*CG;//((f+g)*(f+g)-e*e)*(e*e-(f-g)*(f-g));

		xf	= (2*g*CA-CB*CG)/SG;
		yg	= (2*f*CB-CA*CG)/SG;

		z0	= z.crss(r12,r13);
		z.nrml();

		/*
		// dr1	=[dx 0 0]; dr2	=[0 0 0];dr3	=[0 0 0];

		dr3		= dr2 = dr1	= 0;
		dr1.x[0]= 1;

		dr12	= dr2-dr1;
		dr13	= dr3-dr1;
		dr23	= dr3-dr2;

		dz1.crss(dr12,r13);
		dz2.crss(r12,dr13);

		df		= dr12.scpr(r12);
		dg		= dr13.scpr(r13);
		de		= dr23.scpr(r23);


		dCA		= 2*df;
		dCB		= 2*dg;
		dCG		= 2*(df+dg-de);

		dSG		= 4*(dCA+dCG)-2*CG*dCG;

		dxf		= (dCB*(2*CA-CG)+2*g*g*dCA-dCG*CB-xf*dSG)/SG;
		dyg		= (dCA*(2*CB-CG)+2*f*f*dCB-dCG*CA-yg*dSG)/SG;

		dz		= 2.0*( dz1+dz2-0.5*z*dSG/SG )/sqrt(SG);

		z.nrml();

		h	= Tris->x[i].nr.scpr(z);

		dh		= -0.5*(CA*dxf+CB*dyg+dCA*xf*xf+dCB*yg*yg+xf*yg*dCG)/h;		

		dpc		= dr1+dxf*(r12)+dyg*(r13)+xf*(dr12)+yg*(dr13);

		Tris->x[i].dpc->x[0]	= dpc+dh*z+h*dz;//*/
		
		// dr1	=[dx 0 0]; dr2	=[0 0 0];dr3	=[0 0 0];

		dr3		= dr2 = dr1	= 0;
		dr1.x[0]= 1;

		dr12	= dr2-dr1;
		dr13	= dr3-dr1;
		dr23	= dr3-dr2;

		dz1.crss(dr12,r13);
		dz2.crss(r12,dr13);

		df		= dr12.scpr(r12);
		dg		= dr13.scpr(r13);
		de		= dr23.scpr(r23);


		dCA		= 2*df;
		dCB		= 2*dg;
		dCG		= 2*(df+dg-de);

		dSG		= 4*(dCA*g+dCB*f)-2*CG*dCG;

		dxf		= (dCB*(2*CA-CG)+2*g*dCA-dCG*CB-xf*dSG)/SG;
		dyg		= (dCA*(2*CB-CG)+2*f*dCB-dCG*CA-yg*dSG)/SG;

		dz		= 2.0*( dz1+dz2-0.5*z0*dSG/SG )/sqrt(SG);

		h	= Tris->x[i].nr.scpr(z);

		dh		= -0.5*(CA*dxf+CB*dyg+dCA*xf*xf+dCB*yg*yg+xf*yg*dCG)/h;		

		dpc		= dr1+dxf*(r12)+dyg*(r13)+xf*(dr12)+yg*(dr13);

		Tris->x[i].dpc->x[0]	= dpc+dh*z+h*dz;

		// dr1	=[0 dy 0]; dr2	=[0 0 0];dr3	=[0 0 0];

		dr3		= dr2 = dr1	= 0;
		dr1.x[1]= 1;

		dr12	= dr2-dr1;
		dr13	= dr3-dr1;
		dr23	= dr3-dr2;

		dz1.crss(dr12,r13);
		dz2.crss(r12,dr13);

		df		= dr12.scpr(r12);
		dg		= dr13.scpr(r13);
		de		= dr23.scpr(r23);


		dCA		= 2*df;
		dCB		= 2*dg;
		dCG		= 2*(df+dg-de);

		dSG		= 4*(dCA*g+dCB*f)-2*CG*dCG;
		
		dxf		= (dCB*(2*CA-CG)+2*g*dCA-dCG*CB-xf*dSG)/SG;
		dyg		= (dCA*(2*CB-CG)+2*f*dCB-dCG*CA-yg*dSG)/SG;

		dz		= 2.0*( dz1+dz2-0.5*z0*dSG/SG )/sqrt(SG);

		h	= Tris->x[i].nr.scpr(z);

		dh		= -0.5*(CA*dxf+CB*dyg+dCA*xf*xf+dCB*yg*yg+xf*yg*dCG)/h;		

		dpc		= dr1+dxf*(r12)+dyg*(r13)+xf*(dr12)+yg*(dr13);

		Tris->x[i].dpc->x[1]	= dpc+dh*z+h*dz;

		// dr1	=[0 0 1]; dr2	=[0 0 0];dr3	=[0 0 0];

		dr3		= dr2 = dr1	= 0;
		dr1.x[2]= 1;

		dr12	= dr2-dr1;
		dr13	= dr3-dr1;
		dr23	= dr3-dr2;

		dz1.crss(dr12,r13);
		dz2.crss(r12,dr13);

		df		= dr12.scpr(r12);
		dg		= dr13.scpr(r13);
		de		= dr23.scpr(r23);


		dCA		= 2*df;
		dCB		= 2*dg;
		dCG		= 2*(df+dg-de);

		dSG		= 4*(dCA*g+dCB*f)-2*CG*dCG;
		
		dxf		= (dCB*(2*CA-CG)+2*g*dCA-dCG*CB-xf*dSG)/SG;
		dyg		= (dCA*(2*CB-CG)+2*f*dCB-dCG*CA-yg*dSG)/SG;

		dz		= 2.0*( dz1+dz2-0.5*z0*dSG/SG )/sqrt(SG);

		h	= Tris->x[i].nr.scpr(z);

		dh		= -0.5*(CA*dxf+CB*dyg+dCA*xf*xf+dCB*yg*yg+xf*yg*dCG)/h;		

		dpc		= dr1+dxf*(r12)+dyg*(r13)+xf*(dr12)+yg*(dr13);

		Tris->x[i].dpc->x[2]	= dpc+dh*z+h*dz;


		// dr1	=[0 0 0]; dr2	=[1 0 0];dr3	=[0 0 0];

		dr3		= dr2 = dr1	= 0;
		dr2.x[0]= 1;

		dr12	= dr2-dr1;
		dr13	= dr3-dr1;
		dr23	= dr3-dr2;

		dz1.crss(dr12,r13);
		dz2.crss(r12,dr13);

		df		= dr12.scpr(r12);
		dg		= dr13.scpr(r13);
		de		= dr23.scpr(r23);


		dCA		= 2*df;
		dCB		= 2*dg;
		dCG		= 2*(df+dg-de);

		dSG		= 4*(dCA*g+dCB*f)-2*CG*dCG;

		dxf		= (dCB*(2*CA-CG)+2*g*dCA-dCG*CB-xf*dSG)/SG;
		dyg		= (dCA*(2*CB-CG)+2*f*dCB-dCG*CA-yg*dSG)/SG;

		dz		= 2.0*( dz1+dz2-0.5*z0*dSG/SG )/sqrt(SG);


		h	= Tris->x[i].nr.scpr(z);

		dh		= -0.5*(CA*dxf+CB*dyg+dCA*xf*xf+dCB*yg*yg+xf*yg*dCG)/h;		

		dpc		= dr1+dxf*(r12)+dyg*(r13)+xf*(dr12)+yg*(dr13);

		Tris->x[i].dpc->x[3]	= dpc+dh*z+h*dz;


		// dr1	=[0 0 0]; dr2	=[0 1 0];dr3	=[0 0 0];

		dr3		= dr2 = dr1	= 0;
		dr2.x[1]= 1;

		dr12	= dr2-dr1;
		dr13	= dr3-dr1;
		dr23	= dr3-dr2;

		dz1.crss(dr12,r13);
		dz2.crss(r12,dr13);

		df		= dr12.scpr(r12);
		dg		= dr13.scpr(r13);
		de		= dr23.scpr(r23);


		dCA		= 2*df;
		dCB		= 2*dg;
		dCG		= 2*(df+dg-de);

		dSG		= 4*(dCA*g+dCB*f)-2*CG*dCG;

		dxf		= (dCB*(2*CA-CG)+2*g*dCA-dCG*CB-xf*dSG)/SG;
		dyg		= (dCA*(2*CB-CG)+2*f*dCB-dCG*CA-yg*dSG)/SG;

		dz		= 2.0*( dz1+dz2-0.5*z0*dSG/SG )/sqrt(SG);

		h	= Tris->x[i].nr.scpr(z);

		dh		= -0.5*(CA*dxf+CB*dyg+dCA*xf*xf+dCB*yg*yg+xf*yg*dCG)/h;		

		dpc		= dr1+dxf*(r12)+dyg*(r13)+xf*(dr12)+yg*(dr13);

		Tris->x[i].dpc->x[4]	= dpc+dh*z+h*dz;


		// dr1	=[0 0 0]; dr2	=[0 0 1];dr3	=[0 0 0];

		dr3		= dr2 = dr1	= 0;
		dr2.x[2]= 1;

		dr12	= dr2-dr1;
		dr13	= dr3-dr1;
		dr23	= dr3-dr2;

		dz1.crss(dr12,r13);
		dz2.crss(r12,dr13);

		df		= dr12.scpr(r12);
		dg		= dr13.scpr(r13);
		de		= dr23.scpr(r23);


		dCA		= 2*df;
		dCB		= 2*dg;
		dCG		= 2*(df+dg-de);

		dSG		= 4*(dCA*g+dCB*f)-2*CG*dCG;

		dxf		= (dCB*(2*CA-CG)+2*g*dCA-dCG*CB-xf*dSG)/SG;
		dyg		= (dCA*(2*CB-CG)+2*f*dCB-dCG*CA-yg*dSG)/SG;

		dz		= 2.0*( dz1+dz2-0.5*z0*dSG/SG )/sqrt(SG);

		h	= Tris->x[i].nr.scpr(z);

		dh		= -0.5*(CA*dxf+CB*dyg+dCA*xf*xf+dCB*yg*yg+xf*yg*dCG)/h;		

		dpc		= dr1+dxf*(r12)+dyg*(r13)+xf*(dr12)+yg*(dr13);

		Tris->x[i].dpc->x[5]	= dpc+dh*z+h*dz;

		// dr1	=[0 0 0]; dr2	=[0 0 0];dr3	=[1 0 0];

		dr3		= dr2 = dr1	= 0;
		dr3.x[0]= 1;

		dr12	= dr2-dr1;
		dr13	= dr3-dr1;
		dr23	= dr3-dr2;

		dz1.crss(dr12,r13);
		dz2.crss(r12,dr13);

		df		= dr12.scpr(r12);
		dg		= dr13.scpr(r13);
		de		= dr23.scpr(r23);


		dCA		= 2*df;
		dCB		= 2*dg;
		dCG		= 2*(df+dg-de);

		dSG		= 4*(dCA*g+dCB*f)-2*CG*dCG;

		dxf		= (dCB*(2*CA-CG)+2*g*dCA-dCG*CB-xf*dSG)/SG;
		dyg		= (dCA*(2*CB-CG)+2*f*dCB-dCG*CA-yg*dSG)/SG;

		dz		= 2.0*( dz1+dz2-0.5*z0*dSG/SG )/sqrt(SG);

		h	= Tris->x[i].nr.scpr(z);

		dh		= -0.5*(CA*dxf+CB*dyg+dCA*xf*xf+dCB*yg*yg+xf*yg*dCG)/h;		

		dpc		= dr1+dxf*(r12)+dyg*(r13)+xf*(dr12)+yg*(dr13);

		Tris->x[i].dpc->x[6]	= dpc+dh*z+h*dz;
		

		// dr1	=[0 0 0]; dr2	=[0 0 0];dr3	=[0 1 0];

		dr3		= dr2 = dr1	= 0;
		dr3.x[1]= 1;

		dr12	= dr2-dr1;
		dr13	= dr3-dr1;
		dr23	= dr3-dr2;

		dz1.crss(dr12,r13);
		dz2.crss(r12,dr13);

		df		= dr12.scpr(r12);
		dg		= dr13.scpr(r13);
		de		= dr23.scpr(r23);


		dCA		= 2*df;
		dCB		= 2*dg;
		dCG		= 2*(df+dg-de);

		dSG		= 4*(dCA*g+dCB*f)-2*CG*dCG;

		dxf		= (dCB*(2*CA-CG)+2*g*dCA-dCG*CB-xf*dSG)/SG;
		dyg		= (dCA*(2*CB-CG)+2*f*dCB-dCG*CA-yg*dSG)/SG;

		dz		= 2.0*( dz1+dz2-0.5*z0*dSG/SG )/sqrt(SG);

		h	= Tris->x[i].nr.scpr(z);

		dh		= -0.5*(CA*dxf+CB*dyg+dCA*xf*xf+dCB*yg*yg+xf*yg*dCG)/h;		

		dpc		= dr1+dxf*(r12)+dyg*(r13)+xf*(dr12)+yg*(dr13);

		Tris->x[i].dpc->x[7]	= dpc+dh*z+h*dz;

		// dr1	=[0 0 0]; dr2	=[0 0 0];dr3	=[0 0 1];

		dr3		= dr2 = dr1	= 0;
		dr3.x[2]= 1;

		dr12	= dr2-dr1;
		dr13	= dr3-dr1;
		dr23	= dr3-dr2;

		dz1.crss(dr12,r13);
		dz2.crss(r12,dr13);

		df		= dr12.scpr(r12);
		dg		= dr13.scpr(r13);
		de		= dr23.scpr(r23);


		dCA		= 2*df;
		dCB		= 2*dg;
		dCG		= 2*(df+dg-de);

		dSG		= 4*(dCA*g+dCB*f)-2*CG*dCG;

		dxf		= (dCB*(2*CA-CG)+2*g*dCA-dCG*CB-xf*dSG)/SG;
		dyg		= (dCA*(2*CB-CG)+2*f*dCB-dCG*CA-yg*dSG)/SG;

		dz		= 2.0*( dz1+dz2-0.5*z0*dSG/SG )/sqrt(SG);

		h	= Tris->x[i].nr.scpr(z);

		dh		= -0.5*(CA*dxf+CB*dyg+dCA*xf*xf+dCB*yg*yg+xf*yg*dCG)/h;		

		dpc		= dr1+dxf*(r12)+dyg*(r13)+xf*(dr12)+yg*(dr13);

		Tris->x[i].dpc->x[8]	= dpc+dh*z+h*dz;

		/** /cout<<"i : "<<i<<endl;
		cout<<"dpc : \n"<<*Tris->x[i].dpc<<endl;
		//*/

	}
}

void MeshConstructor::SetScStDiff()// ����������������� �� ���
{
	double dd,d;
	//Vec3db r12,dr12;

	int i,i1,i2,j;//j1,j2;
	for(i=0;i<SRol->N;i++)
	{
		for(i1=0;i1<SRol->x[i].Stbl->N;i1++)
		{
			i2	= 	SRol->x[i].Stbl->x[i1].nTw;
	//		j1	=	Twos->x[i2].n_at.x[0];
	//		j2	=	Twos->x[i2].n_at.x[1];

			SRol->x[i].Stbl->x[i1].dpc1->init(6);
			SRol->x[i].Stbl->x[i1].dpc2->init(6);

			d	= SRol->x[i].Stbl->x[i1].d;

			for(j=0;j<6;j++)
			{
				dd	= - Twos->x[i2].dh->x[j]*Twos->x[i2].hab.x[0]/d;
				SRol->x[i].Stbl->x[i1].dpc1->x[j]	= Twos->x[i2].dpc->x[j] - dd*Twos->x[i2].z - d*Twos->x[i2].dz->x[j];
			}
			
			for(j=0;j<6;j++)
			{
				dd	= - Twos->x[i2].dh->x[j]*Twos->x[i2].hab.x[0]/d;
				SRol->x[i].Stbl->x[i1].dpc2->x[j]	= Twos->x[i2].dpc->x[j] + dd*Twos->x[i2].z + d*Twos->x[i2].dz->x[j];
			}
			/** /cout<<"i : "<<i<<endl;
			cout<<"i1 : "<<i1<<endl;
			cout<<"dpc1 : \n"<<*SRol->x[i].Stbl->x[i1].dpc1<<endl;
			cout<<"dpc2 : \n"<<*SRol->x[i].Stbl->x[i1].dpc2<<endl;
			//*/
		}
	}
}

void MeshConstructor::SetScTrDiff()// ����������������� �. �����. ����
{

	double a,f,g,e,CA,CB,CG,SG,h,xf,yg,dh,df,dg,de,dxf,dyg,dSG,dCA,dCB,dCG;

	ms1D<int> itsst(10);
	ms1D<int> itstt(10);

	Vec3db	x,y,z,z0,dz1,dz2,dz,pc,dpc,r12,r13,r23,dr1,dr2,dr3,dr12,dr13,dr23;
	
	int i,i1,i2,i3,j,j1,j2,j3,k,k1;

	a	*= a	= s_rol+p_rol;;
	for(i=0;i<SRol->N;i++)
	{
		for(j=0;j<SRol->x[i].Tris->N;j++)
		{

			i1	= SRol->x[i].Tris->x[j].n_tr->x[0];
			i2	= SRol->x[i].Tris->x[j].n_tr->x[1];
			i3	= SRol->x[i].Tris->x[j].n_tr->x[2];

			r12	= Tris->x[i2].pc-Tris->x[i1].pc;
			r13	= Tris->x[i3].pc-Tris->x[i1].pc;
			r23	= r13-r12;

			f	= r12.ssqr();
			g	= r13.ssqr();
			e	= r23.ssqr();

			CA	= f;
			CB	= g;
			CG	= f+g-e;
			SG	= 4*f*g-CG*CG;//((f+g)*(f+g)-e*e)*(e*e-(f-g)*(f-g));

			xf	= (2*g*CA-CB*CG)/SG;
			yg	= (2*f*CB-CA*CG)/SG;

			z0	= z.crss(r12,r13);
			z.nrml();

			Tris->x[i1].n_at->unis(*Tris->x[i2].n_at,itstt);
			Tris->x[i2].n_at->unis(itstt,itsst);

			SRol->x[i].Tris->x[j].n_at->init(itsst.N);
			SRol->x[i].Tris->x[j].dpc->init(3*itsst.N);
			SRol->x[i].Tris->x[j].n_at->pst(itsst);

			for(k=0;k<itsst.N;k++)
			{
				dr1	= dr2 = dr3	= 0;
				k1	= itsst.x[k];
				j1	= Tris->x[i1].n_at->fnd(k1);
				j2	= Tris->x[i2].n_at->fnd(k1);
				j3	= Tris->x[i3].n_at->fnd(k1);

				if((j1!=-1)&&(j1<3))	dr1	=	Tris->x[i1].dpc->x[3*j1];
				if((j2!=-1)&&(j2<3))	dr2	=	Tris->x[i2].dpc->x[3*j2];
				if((j3!=-1)&&(j3<3))	dr3	=	Tris->x[i3].dpc->x[3*j3];

				dr12	= dr2-dr1;
				dr13	= dr3-dr1;
				dr23	= dr3-dr2;
				
				dz1.crss(dr12,r13);
				dz2.crss(r12,dr13);
				
				df		= dr12.scpr(r12);
				dg		= dr13.scpr(r13);
				de		= dr23.scpr(r23);
				
				
				dCA		= 2*df;
				dCB		= 2*dg;
				dCG		= 2*(df+dg-de);
				
				dSG		= 4*(dCA*g+dCB*f)-2*CG*dCG;
				
				dxf		= (dCB*(2*CA-CG)+2*g*dCA-dCG*CB-xf*dSG)/SG;
				dyg		= (dCA*(2*CB-CG)+2*f*dCB-dCG*CA-yg*dSG)/SG;
				
				dz		= 2.0*( dz1+dz2-0.5*z0*dSG/SG )/sqrt(SG);
				
				
				h	= SRol->x[i].Tris->x[j].nr.scpr(z);
				
				dh		= -0.5*(CA*dxf+CB*dyg+dCA*xf*xf+dCB*yg*yg+xf*yg*dCG)/h;		
				
				dpc		= dr1+dxf*(r12)+dyg*(r13)+xf*(dr12)+yg*(dr13);
				
				SRol->x[i].Tris->x[j].dpc->x[3*k]	= dpc+dh*z+h*dz;


				dr1	= dr2 = dr3	= 0;

				if((j1!=-1)&&(j1<3))	dr1	=	Tris->x[i1].dpc->x[3*j1+1];
				if((j2!=-1)&&(j2<3))	dr2	=	Tris->x[i2].dpc->x[3*j2+1];
				if((j3!=-1)&&(j3<3))	dr3	=	Tris->x[i3].dpc->x[3*j3+1];

				dr12	= dr2-dr1;
				dr13	= dr3-dr1;
				dr23	= dr3-dr2;
				
				dz1.crss(dr12,r13);
				dz2.crss(r12,dr13);
				
				df		= dr12.scpr(r12);
				dg		= dr13.scpr(r13);
				de		= dr23.scpr(r23);
				
				
				dCA		= 2*df;
				dCB		= 2*dg;
				dCG		= 2*(df+dg-de);
				
				dSG		= 4*(dCA*g+dCB*f)-2*CG*dCG;
				
				dxf		= (dCB*(2*CA-CG)+2*g*dCA-dCG*CB-xf*dSG)/SG;
				dyg		= (dCA*(2*CB-CG)+2*f*dCB-dCG*CA-yg*dSG)/SG;
				
				dz		= 2.0*( dz1+dz2-0.5*z0*dSG/SG )/sqrt(SG);
				
				
				h	= SRol->x[i].Tris->x[j].nr.scpr(z);
				
				dh		= -0.5*(CA*dxf+CB*dyg+dCA*xf*xf+dCB*yg*yg+xf*yg*dCG)/h;		
				
				dpc		= dr1+dxf*(r12)+dyg*(r13)+xf*(dr12)+yg*(dr13);
				
				SRol->x[i].Tris->x[j].dpc->x[3*k+1]	= dpc+dh*z+h*dz;

				dr1	= dr2 = dr3	= 0;

				if((j1!=-1)&&(j1<3))	dr1	=	Tris->x[i1].dpc->x[3*j1+2];
				if((j2!=-1)&&(j2<3))	dr2	=	Tris->x[i2].dpc->x[3*j2+2];
				if((j3!=-1)&&(j3<3))	dr3	=	Tris->x[i3].dpc->x[3*j3+2];

				dr12	= dr2-dr1;
				dr13	= dr3-dr1;
				dr23	= dr3-dr2;
				
				dz1.crss(dr12,r13);
				dz2.crss(r12,dr13);
				
				df		= dr12.scpr(r12);
				dg		= dr13.scpr(r13);
				de		= dr23.scpr(r23);
				
				
				dCA		= 2*df;
				dCB		= 2*dg;
				dCG		= 2*(df+dg-de);
				
				dSG		= 4*(dCA*g+dCB*f)-2*CG*dCG;
				
				dxf		= (dCB*(2*CA-CG)+2*g*dCA-dCG*CB-xf*dSG)/SG;
				dyg		= (dCA*(2*CB-CG)+2*f*dCB-dCG*CA-yg*dSG)/SG;
				
				dz		= 2.0*( dz1+dz2-0.5*z0*dSG/SG )/sqrt(SG);
				
				
				h	= SRol->x[i].Tris->x[j].nr.scpr(z);
				
				dh		= -0.5*(CA*dxf+CB*dyg+dCA*xf*xf+dCB*yg*yg+xf*yg*dCG)/h;		
				
				dpc		= dr1+dxf*(r12)+dyg*(r13)+xf*(dr12)+yg*(dr13);
				
				SRol->x[i].Tris->x[j].dpc->x[3*k+2]	= dpc+dh*z+h*dz;

			}
			/** /cout<<"i : "<<i<<endl;
			cout<<"j : "<<j<<endl;
			cout<<"dpc : \n"<<*SRol->x[i].Tris->x[j].dpc<<endl;
			//*/
		}
	}
}

void MeshConstructor::SetScTwDiff()// ����������������� ����������. ����
{
	ms1D<int> itsst(10);

	double a,c,dc,h,h2,sqc;
	Vec3db r12,dr12,z,dr1,dr2;

	int i,i1,i2,j,j1,j2,k,k1;

	a	*= a = p_rol+s_rol;
	for(i=0;i<SRol->N;i++)
	{
		for(j=0;j<SRol->x[i].Twos->N;j++)
		{
			i1	= SRol->x[i].Twos->x[j].n_tr.x[0];
			i2	= SRol->x[i].Twos->x[j].n_tr.x[1];

			r12	= Tris->x[i2].pc-Tris->x[i1].pc;

			z	= SRol->x[i].Twos->x[j].z;

			c*=	c = sqc	= z.scpr(r12);
			h	= SRol->x[i].Twos->x[j].r_sc;
			h2	= -0.25*c/h;
			sqc	= 1/sqc;			


			Tris->x[i1].n_at->unis(*Tris->x[i2].n_at,itsst);

			SRol->x[i].Twos->x[j].n_at->init(itsst.N);
			SRol->x[i].Twos->x[j].dpc->init(3*itsst.N);
			SRol->x[i].Twos->x[j].dz->init(3*itsst.N);
			SRol->x[i].Twos->x[j].dh->init(3*itsst.N);
			SRol->x[i].Twos->x[j].n_at->pst(itsst);
			
			for(k=0;k<itsst.N;k++)
			{				
				k1	= itsst.x[k];

				j1	= Tris->x[i1].n_at->fnd(k1);
				j2	= Tris->x[i2].n_at->fnd(k1);

				dr1	= dr2= 0;
				if((j1!=-1)&&(j1<3))	dr1	=	Tris->x[i1].dpc->x[3*j1];
				if((j2!=-1)&&(j2<3))	dr2	=	Tris->x[i2].dpc->x[3*j2];
				
				dr12	= dr2-dr1;				
				dc		= dr12.scpr(z)/c;
				SRol->x[i].Twos->x[j].dh->x[3*k]		= dc*h2*sqc;
				SRol->x[i].Twos->x[j].dpc->x[3*k]		= 0.5*(dr1+dr2);
				SRol->x[i].Twos->x[j].dz->x[3*k]		= (dr12-r12*dc)*sqc;

				dr1	= dr2= 0;
				if((j1!=-1)&&(j1<3))	dr1	=	Tris->x[i1].dpc->x[3*j1+1];
				if((j2!=-1)&&(j2<3))	dr2	=	Tris->x[i2].dpc->x[3*j2+1];
				
				dr12	= dr2-dr1;				
				dc		= dr12.scpr(z)/c;
				SRol->x[i].Twos->x[j].dh->x[3*k+1]		= dc*h2*sqc;
				SRol->x[i].Twos->x[j].dpc->x[3*k+1]		= 0.5*(dr1+dr2);
				SRol->x[i].Twos->x[j].dz->x[3*k+1]		= (dr12-r12*dc)*sqc;

				dr1	= dr2= 0;
				if((j1!=-1)&&(j1<3))	dr1	=	Tris->x[i1].dpc->x[3*j1+2];
				if((j2!=-1)&&(j2<3))	dr2	=	Tris->x[i2].dpc->x[3*j2+2];
				
				dr12	= dr2-dr1;				
				dc		= dr12.scpr(z)/c;
				SRol->x[i].Twos->x[j].dh->x[3*k+2]		= dc*h2*sqc;
				SRol->x[i].Twos->x[j].dpc->x[3*k+2]		= 0.5*(dr1+dr2);
				SRol->x[i].Twos->x[j].dz->x[3*k+2]		= (dr12-r12*dc)*sqc;

			}
			/** /cout<<"i : "<<i<<endl;
			cout<<"j : "<<j<<endl;
			cout<<"N : "<<SRol->x[i].Twos->x[j].dpc->N<<endl;
			cout<<"dpc : \n"<<*SRol->x[i].Twos->x[j].dpc<<endl;
			cout<<"dz : \n"<<*SRol->x[i].Twos->x[j].dz<<endl;
			cout<<"dh : \n"<<*SRol->x[i].Twos->x[j].dh<<endl;//*/
		}
	}


}

void MeshConstructor::SetSGBDiff()	// ��������� s_gb �������
{
	int i,i1,i2,j,j1,k,k1,itr,itw,iat,iat3;
	ms1Dint		j_sph,j_tor;
	ms1DVec3db	dr_sph,dr_tor,dn_tor,r_sph,n_sph,r_tor,n_tor,ds_tor;
	ms1Ddb		s_sph,s_tor;

	Vec3db	dx,dy,dz,dx_,dy_,dz_,dnx,dny,dnz,drp,e,de,ds;
	ms1DVec3db	dxyz(3),dxyz_(3),spnt;

	double	alfa,beta,gamma,alfa1,beta1,sg;//,*dst;
	double	dst,dst2,dst4,dst5,dst6,dst7,drns,drns1,drns0;
	Vec3db	rps,rat; 

	ms1D<ms1Dint> tr_str(Tris->N);	// ��. �. �������� � ��. �. ���
	ms1D<ms1Dint> tr_stw(Tris->N);	// �� ��� ��. � ���
	ms1D<ms1Dint> tw_sst(Twos->N);	// ��. �� ���� ��. ��

	/*tw_sst.init(Twos->N);
	tr_str.init(Tris->N);
	tr_stw.init(Tris->N);//*/

	ms1Ddb AG;	

	AG.init(5);

/*	AG.x[0]	= 8.1908681906;
	AG.x[1]	= -152.660991555;
	AG.x[2]	= 238.55481746;
	AG.x[3]	= -151.700438246;
	AG.x[4]	= -1.0743470369;*/


	AG.x[0]	= -0.056090914150351;
	AG.x[1]	= 1.0454196517588;
	AG.x[2]	= -1.6336189857942;
	AG.x[3]	= 1.0388418004324;
	AG.x[4]	= 0.0073571086742183;
	

	//ms1D<ms1Ddb>	ASdst;

	ms1D<ms1Ddb>	dJ;	//������ �����

	ms1D<ms1Ddb>	J;

	dGB.init(3*Atom.N);

	J.one(4);
	J.x[0].init(Atom.N);
	J.x[1].init(Atom.N);
	J.x[2].init(Atom.N);
	J.x[3].init(Atom.N);
	dJ.one(4);
	dJ.x[0].init(3*Atom.N);
	dJ.x[1].init(3*Atom.N);
	dJ.x[2].init(3*Atom.N);
	dJ.x[3].init(3*Atom.N);

	I.one(4);			// 4 ���f ����� � �������
	I.x[0].init(Atom.N);
	I.x[1].init(Atom.N);
	I.x[2].init(Atom.N);
	I.x[3].init(Atom.N);
	dI.one(4);			// 4 ��������� ����� � �������
	dI.x[0].init(Atom.N);
	dI.x[1].init(Atom.N);
	dI.x[2].init(Atom.N);
	dI.x[3].init(Atom.N);

	BR.init(Atom.N);	//	��� ����� ���� � �������
	dBR.one(Atom.N);	//  ��� ����� ����� ���� � �������
	

	dr_sph.init(Point.N);
	dr_tor.init(Point.N);
	dn_tor.init(Point.N);
	r_sph.init(Point.N);
	n_sph.init(Point.N);
	r_tor.init(Point.N);
	n_tor.init(Point.N);
	s_sph.init(Point.N);
	s_tor.init(Point.N);
	ds_tor.init(Point.N);


	/*ASdst.one(Atom.N);
	spnt.one(Point.N);
	for(i=0;i<Atom.N;i++)
	{
		ASdst.x[i].one(Point.N);
	}
	for(j=0;j<Point.N;j++){spnt.x[j]=Point.x[j].crd;}

	for(i=0;i<Atom.N;i++)
	{
		e	= Atom.x[i].xyz;
		dst	= ASdst.x[i].x;
		for(j=0;j<Point.N;j++)
		{
			dst[j]= (spnt.x[j]-e).norm();
		}
	}*/	

	Vec3db r_ch_1,r_ch_2,r_ch_3;


	for(i=0;i<SRol->N;i++)
	{
		for(j=0;j<SRol->x[i].Tris->N;j++)
		{
			i1	= SRol->x[i].Tris->x[j].n_tr->x[0];
			tr_str.x[i1].add(j);
			i1	= SRol->x[i].Tris->x[j].n_tr->x[1];
			tr_str.x[i1].add(j);
			i1	= SRol->x[i].Tris->x[j].n_tr->x[2];
			tr_str.x[i1].add(j);
		}
		for(j=0;j<SRol->x[i].Twos->N;j++)
		{
			i1	= SRol->x[i].Twos->x[j].n_tr.x[0];
			tr_stw.x[i1].add(j);
			i1	= SRol->x[i].Twos->x[j].n_tr.x[1];
			tr_stw.x[i1].add(j);
		}
		for(j=0;j<SRol->x[i].Stbl->N;j++)
		{
			i1	= SRol->x[i].Stbl->x[j].nTw;
			tw_sst.x[i1].add(j);
		}
	}



	//tr_stw.data2file('s');

	dx	= dy = dz = 0;
	dx.x[0]	= dy.x[1] = dz.x[2] =1;

	dxyz.add(dx);
	dxyz.add(dy);
	dxyz.add(dz);

//	double it1,it2,it3,bri;

	for(i=0;i<Atom.N;i++)	// ����� ����� ���� ������
	{

		dI.x[0].x[i].init(3*Atom.N);
		dI.x[1].x[i].init(3*Atom.N);
		dI.x[2].x[i].init(3*Atom.N);
		dI.x[3].x[i].init(3*Atom.N);
		dBR.x[i].init(3*Atom.N);

		rat	= Atom.x[i].xyz;
		for(k=0;k<Point.N;k++)
		{
			rps		= Point.x[k].crd-rat;
			dst2	= rps.ssqr(); 
			dst		= sqrt(dst2);
			dst4	= dst2*dst2;
			dst5	= dst4*dst;
			dst6	= dst4*dst2;
			dst7	= dst6*dst;

			drns0	= Point.x[k].area*(Point.x[k].nor.scpr(rps));

			I.x[0].x[i]	+= drns0/dst4;
			I.x[1].x[i]	+= drns0/dst5;
			I.x[2].x[i]	+= drns0/dst6;
			I.x[3].x[i]	+= drns0/dst7;
		}
		I.x[1].x[i]			= sqrt(I.x[1].x[i]);
		I.x[2].x[i]			= pow(I.x[2].x[i],0.33333333333333333333333333);
		I.x[3].x[i]			= pow(I.x[3].x[i],0.25);

		BR.x[i]				= 0.5/(AG.x[4]+AG.x[0]*I.x[0].x[i]+AG.x[1]*I.x[1].x[i]+AG.x[2]*I.x[2].x[i]+AG.x[3]*I.x[3].x[i]);
	}

	for(i=0;i<Atom.N;i++)	// ������ ��� � �������������� ������
	{

		// ������������ ����������� � �������
		r_sph.N	= n_sph.N = s_sph.N = 0;
		r_tor.N	= n_tor.N = s_tor.N = 0;
		dr_sph.N= 0;
		dr_tor.N= dn_tor.N = ds_tor.N = 0;

		j_sph.pst(*Atom.x[i].n_pnt);
		for(j=0;j<j_sph.N;j++)
		{
			dr_sph.add(dxyz);
			r_sph.add(Point.x[j_sph.x[j]].crd);
			n_sph.add(Point.x[j_sph.x[j]].nor);
			s_sph.add(Point.x[j_sph.x[j]].area);
		}

		for(i1=0;i1<Atom.x[i].n_tr->N;i1++)
		{
			itr	= Atom.x[i].n_tr->x[i1];
			iat	= Tris->x[itr].n_at->fnd(i);
			iat3= 3*iat;			
			
			dx_	= Tris->x[itr].dpc->x[iat3];
			dy_	= Tris->x[itr].dpc->x[iat3+1];
			dz_	= Tris->x[itr].dpc->x[iat3+2];
			
			dxyz_.N	= 0;
			dxyz_.add(dx_);
			dxyz_.add(dy_);
			dxyz_.add(dz_);
			
			j_sph.pst(*Tris->x[itr].n_pnt);
			for(j=0;j<j_sph.N;j++)
			{
				dr_sph.add(dxyz_);
				r_sph.add(Point.x[j_sph.x[j]].crd);
				n_sph.add(Point.x[j_sph.x[j]].nor);
				s_sph.add(Point.x[j_sph.x[j]].area);
			}
			k	= Tris->x[itr].igr;
			if (k!=-1)
			{
				for(i2=0;i2<tr_str.x[itr].N;i2++)
				{
					k1	= tr_str.x[itr].x[i2];
					iat = SRol->x[k].Tris->x[k1].n_at->fnd(i);
					iat3= 3*iat;					
					
					dx_	= SRol->x[k].Tris->x[k1].dpc->x[iat3];
					dy_	= SRol->x[k].Tris->x[k1].dpc->x[iat3+1];
					dz_	= SRol->x[k].Tris->x[k1].dpc->x[iat3+2];
					
					dxyz_.N	= 0;
					dxyz_.add(dx_);
					dxyz_.add(dy_);
					dxyz_.add(dz_);
					
					j_sph.pst(*SRol->x[k].Tris->x[k1].n_pnt);
					for(j=0;j<j_sph.N;j++)
					{
						dr_sph.add(dxyz_);
						r_sph.add(Point.x[j_sph.x[j]].crd);
						n_sph.add(Point.x[j_sph.x[j]].nor);
						s_sph.add(Point.x[j_sph.x[j]].area);
					}
				}
				for(i2=0;i2<tr_stw.x[itr].N;i2++)
				{
					k1	= tr_stw.x[itr].x[i2];
					iat = SRol->x[k].Twos->x[k1].n_at->fnd(i);
					iat3= 3*iat;					
					
					j_sph.pst(*SRol->x[k].Twos->x[k1].n_pnt);
					for(j=0;j<j_sph.N;j++)
					{
						j1		= j_sph.x[j];
						alfa	= Point.x[j1].nor.scpr(SRol->x[k].Twos->x[k1].x);
						beta	= Point.x[j1].nor.scpr(SRol->x[k].Twos->x[k1].y);
						gamma	= Point.x[j1].nor.scpr(SRol->x[k].Twos->x[k1].z);
						
						sg		= 1/sqrt(1-gamma*gamma);
						
						alfa1	= alfa*sg;
						beta1	= beta*sg;
						
						e		= SRol->x[k].Twos->x[k1].x*alfa1+SRol->x[k].Twos->x[k1].y*beta1;
						
						de		= -SRol->x[k].Twos->x[k1].z*(alfa*SRol->x[k].Twos->x[k1].x.scpr(SRol->x[k].Twos->x[k1].dz->x[iat3])+beta*SRol->x[k].Twos->x[k1].y.scpr(SRol->x[k].Twos->x[k1].dz->x[iat3]));
						dnx		= de+SRol->x[k].Twos->x[k1].dz->x[iat3]*gamma;			
						de		*=sg;
						dx_		= SRol->x[k].Twos->x[k1].dpc->x[iat3]+e*SRol->x[k].Twos->x[k1].dh->x[iat3]+de*SRol->x[k].Twos->x[k1].r_sc-dnx*p_rol;
						ds.x[0]	= Point.x[j1].area*SRol->x[k].Twos->x[k1].dh->x[iat3]/(SRol->x[k].Twos->x[k1].r_sc+SRol->x[k].s_rol);
						
						de		= -SRol->x[k].Twos->x[k1].z*(alfa*SRol->x[k].Twos->x[k1].x.scpr(SRol->x[k].Twos->x[k1].dz->x[iat3+1])+beta*SRol->x[k].Twos->x[k1].y.scpr(SRol->x[k].Twos->x[k1].dz->x[iat3+1]));
						dny		= de+SRol->x[k].Twos->x[k1].dz->x[iat3+1]*gamma;			
						de		*=sg;
						dy_		= SRol->x[k].Twos->x[k1].dpc->x[iat3+1]+e*SRol->x[k].Twos->x[k1].dh->x[iat3+1]+de*SRol->x[k].Twos->x[k1].r_sc-dny*p_rol;
						ds.x[1]	= Point.x[j1].area*SRol->x[k].Twos->x[k1].dh->x[iat3+1]/(SRol->x[k].Twos->x[k1].r_sc+SRol->x[k].s_rol);
						
						de		= -SRol->x[k].Twos->x[k1].z*(alfa*SRol->x[k].Twos->x[k1].x.scpr(SRol->x[k].Twos->x[k1].dz->x[iat3+2])+beta*SRol->x[k].Twos->x[k1].y.scpr(SRol->x[k].Twos->x[k1].dz->x[iat3+2]));
						dnz		= de+SRol->x[k].Twos->x[k1].dz->x[iat3+2]*gamma;			
						de		*=sg;
						dz_		= SRol->x[k].Twos->x[k1].dpc->x[iat3+2]+e*SRol->x[k].Twos->x[k1].dh->x[iat3+2]+de*SRol->x[k].Twos->x[k1].r_sc-dnz*p_rol;
						ds.x[2]	= Point.x[j1].area*SRol->x[k].Twos->x[k1].dh->x[iat3+2]/(SRol->x[k].Twos->x[k1].r_sc+SRol->x[k].s_rol);
						
						dr_tor.add(dx_);
						dr_tor.add(dy_);
						dr_tor.add(dz_);
						
						dn_tor.add(dnx);
						dn_tor.add(dny);
						dn_tor.add(dnz);
						
						ds_tor.add(ds);
						
						r_tor.add(Point.x[j1].crd);
						n_tor.add(Point.x[j1].nor);
						s_tor.add(Point.x[j1].area);
						
						
					}
				}
			}
		}
		for(i1=0;i1<Atom.x[i].n_tw->N;i1++)
		{
			itw	= Atom.x[i].n_tw->x[i1];
			iat3= Twos->x[itw].n_at.x[0]==i ? 0 : 3;

			j_sph.pst(*Twos->x[itw].n_pnt);
			for(j=0;j<j_sph.N;j++)
			{
				j1		= j_sph.x[j];
				alfa	= Point.x[j1].nor.scpr(Twos->x[itw].x);
				beta	= Point.x[j1].nor.scpr(Twos->x[itw].y);
				gamma	= Point.x[j1].nor.scpr(Twos->x[itw].z);
				
				sg		= sqrt(1-gamma*gamma);
				
				alfa1	= alfa/sg;
				beta1	= beta/sg;
				
				e		= Twos->x[itw].x*alfa1+Twos->x[itw].y*beta1;
				
				de		= -Twos->x[itw].z*(alfa1*Twos->x[itw].x.scpr(Twos->x[itw].dz->x[iat3])+beta1*Twos->x[itw].y.scpr(Twos->x[itw].dz->x[iat3]));
				dnx		= de*sg+Twos->x[itw].dz->x[iat3]*gamma;
				dx_		= Twos->x[itw].dpc->x[iat3]+e*Twos->x[itw].dh->x[iat3]+de*Twos->x[itw].hab.x[0]-dnx*p_rol;
				ds.x[0]	= Point.x[j1].area*Twos->x[itw].dh->x[iat3]/(Twos->x[itw].hab.x[0]+p_rol*sg);

				de		= -Twos->x[itw].z*(alfa1*Twos->x[itw].x.scpr(Twos->x[itw].dz->x[iat3+1])+beta1*Twos->x[itw].y.scpr(Twos->x[itw].dz->x[iat3+1]));
				dny		= de*sg+Twos->x[itw].dz->x[iat3+1]*gamma;
				dy_		= Twos->x[itw].dpc->x[iat3+1]+e*Twos->x[itw].dh->x[iat3+1]+de*Twos->x[itw].hab.x[0]-dny*p_rol;
				ds.x[1]	= Point.x[j1].area*Twos->x[itw].dh->x[iat3+1]/(Twos->x[itw].hab.x[0]+p_rol*sg);

				de		= -Twos->x[itw].z*(alfa1*Twos->x[itw].x.scpr(Twos->x[itw].dz->x[iat3+2])+beta1*Twos->x[itw].y.scpr(Twos->x[itw].dz->x[iat3+2]));
				dnz		= de*sg+Twos->x[itw].dz->x[iat3+2]*gamma;
				dz_		= Twos->x[itw].dpc->x[iat3+2]+e*Twos->x[itw].dh->x[iat3+2]+de*Twos->x[itw].hab.x[0]-dnz*p_rol;
				ds.x[2]	= Point.x[j1].area*Twos->x[itw].dh->x[iat3+2]/(Twos->x[itw].hab.x[0]+p_rol*sg);

				dr_tor.add(dx_);
				dr_tor.add(dy_);
				dr_tor.add(dz_);
				
				dn_tor.add(dnx);
				dn_tor.add(dny);
				dn_tor.add(dnz);
				
				ds_tor.add(ds);
				
				r_tor.add(Point.x[j1].crd);
				n_tor.add(Point.x[j1].nor);
				s_tor.add(Point.x[j1].area);
			}

			k	= Twos->x[itw].igr;
			if(k!=-1)
			{
				k1	= tw_sst.x[itw].x[0];

				dx_	= SRol->x[k].Stbl->x[k1].dpc1->x[iat3];
				dy_	= SRol->x[k].Stbl->x[k1].dpc1->x[iat3+1];
				dz_	= SRol->x[k].Stbl->x[k1].dpc1->x[iat3+2];

				dxyz_.N	= 0;
				dxyz_.add(dx_);
				dxyz_.add(dy_);
				dxyz_.add(dz_);

				j_sph.pst(*SRol->x[k].Stbl->x[k1].n_pnt1);
				for(j=0;j<j_sph.N;j++)
				{
					dr_sph.add(dxyz_);
					
					r_sph.add(Point.x[j_sph.x[j]].crd);
					n_sph.add(Point.x[j_sph.x[j]].nor);
					s_sph.add(Point.x[j_sph.x[j]].area);
				}

				dx_	= SRol->x[k].Stbl->x[k1].dpc2->x[iat3];
				dy_	= SRol->x[k].Stbl->x[k1].dpc2->x[iat3+1];
				dz_	= SRol->x[k].Stbl->x[k1].dpc2->x[iat3+2];

				dxyz_.N	= 0;
				dxyz_.add(dx_);
				dxyz_.add(dy_);
				dxyz_.add(dz_);

				j_sph.pst(*SRol->x[k].Stbl->x[k1].n_pnt2);
				for(j=0;j<j_sph.N;j++)
				{
					dr_sph.add(dxyz_);
					
					r_sph.add(Point.x[j_sph.x[j]].crd);
					n_sph.add(Point.x[j_sph.x[j]].nor);
					s_sph.add(Point.x[j_sph.x[j]].area);
				}
			}
		}
		//���������������
/**/	dr_sph.data2file("dr_sph.txt");
		dn_tor.data2file("dn_tor.txt");
		dr_tor.data2file("dr_tor.txt");
		ds_tor.data2file("ds_tor.txt");
		s_tor.data2file("s_tor.txt");
		r_tor.data2file("r_tor.txt");//*/

		cout<<s_tor.sum()<<endl;

		cout<<ds_tor.sum()<<endl;

		//����������dh ������ �� ��.......

		dJ.x[0]	= 0;
		dJ.x[1]	= 0;
		dJ.x[2]	= 0;
		dJ.x[3]	= 0;

		// �������
		for(j=0;j<Atom.N;j++) // ������� � ����� �������� ��. ��� �������
		{
			rat	= Atom.x[j].xyz;
/**/ 		for(k=0;k<r_sph.N;k++)
			{
				rps		= r_sph.x[k]-rat;
				dst2	= rps.ssqr(); 
				dst		= sqrt(dst2);
				dst4	= dst2*dst2;
				dst5	= dst4*dst;
				dst6	= dst4*dst2;
				dst7	= dst6*dst;

				drns	= s_sph.x[k]*((n_sph.x[k].scpr(dr_sph.x[3*k])));
				drns1	= s_sph.x[k]*(n_sph.x[k].scpr(rps))*(dr_sph.x[3*k].scpr(rps))/dst2;

				dJ.x[0].x[3*j]	+= (drns-4*drns1)/dst4;
				dJ.x[1].x[3*j]	+= (drns-5*drns1)/dst5;
				dJ.x[2].x[3*j]	+= (drns-6*drns1)/dst6;
				dJ.x[3].x[3*j]	+= (drns-7*drns1)/dst7;

				drns	= s_sph.x[k]*((n_sph.x[k].scpr(dr_sph.x[3*k+1])));
				drns1	= s_sph.x[k]*(n_sph.x[k].scpr(rps))*(dr_sph.x[3*k+1].scpr(rps))/dst2;

				dJ.x[0].x[3*j+1]	+= (drns-4*drns1)/dst4;
				dJ.x[1].x[3*j+1]	+= (drns-5*drns1)/dst5;
				dJ.x[2].x[3*j+1]	+= (drns-6*drns1)/dst6;
				dJ.x[3].x[3*j+1]	+= (drns-7*drns1)/dst7;

				drns	= s_sph.x[k]*((n_sph.x[k].scpr(dr_sph.x[3*k+2])));
				drns1	= s_sph.x[k]*(n_sph.x[k].scpr(rps))*(dr_sph.x[3*k+2].scpr(rps))/dst2;

				dJ.x[0].x[3*j+2]	+= (drns-4*drns1)/dst4;
				dJ.x[1].x[3*j+2]	+= (drns-5*drns1)/dst5;
				dJ.x[2].x[3*j+2]	+= (drns-6*drns1)/dst6;
				dJ.x[3].x[3*j+2]	+= (drns-7*drns1)/dst7;
			}/**/
			r_ch_1	= r_ch_2 = r_ch_3 = 0;
			for(k=0;k<r_tor.N;k++)
			{

/*				r_ch_1	+= dr_tor.x[3*k];
				r_ch_2	+= dr_tor.x[3*k+1];
				r_ch_3	+= dr_tor.x[3*k+2];*/

				rps		= r_tor.x[k]-rat;
				dst2	= rps.ssqr(); 
				dst		= sqrt(dst2);
				dst4	= dst2*dst2;
				dst5	= dst4*dst;
				dst6	= dst4*dst2;
				dst7	= dst6*dst;

				drns	= s_tor.x[k]*((n_tor.x[k].scpr(dr_tor.x[3*k]))+(dn_tor.x[3*k].scpr(rps)));
				drns	+=n_tor.x[k].scpr(rps)*ds_tor.x[k].x[0];
				drns1	= s_tor.x[k]*(n_tor.x[k].scpr(rps))*(dr_tor.x[3*k].scpr(rps))/dst2;

				dJ.x[0].x[3*j]	+= (drns-4*drns1)/dst4;
				dJ.x[1].x[3*j]	+= (drns-5*drns1)/dst5;
				dJ.x[2].x[3*j]	+= (drns-6*drns1)/dst6;
				dJ.x[3].x[3*j]	+= (drns-7*drns1)/dst7;

				drns	= s_tor.x[k]*((n_tor.x[k].scpr(dr_tor.x[3*k+1]))+(dn_tor.x[3*k+1].scpr(rps)));
				drns	+=n_tor.x[k].scpr(rps)*ds_tor.x[k].x[1];
				drns1	= s_tor.x[k]*(n_tor.x[k].scpr(rps))*(dr_tor.x[3*k+1].scpr(rps))/dst2;

				dJ.x[0].x[3*j+1]	+= (drns-4*drns1)/dst4;
				dJ.x[1].x[3*j+1]	+= (drns-5*drns1)/dst5;
				dJ.x[2].x[3*j+1]	+= (drns-6*drns1)/dst6;
				dJ.x[3].x[3*j+1]	+= (drns-7*drns1)/dst7;

				drns	= s_tor.x[k]*((n_tor.x[k].scpr(dr_tor.x[3*k+2]))+(dn_tor.x[3*k+2].scpr(rps)));
				drns	+=n_tor.x[k].scpr(rps)*ds_tor.x[k].x[2];
				drns1	= s_tor.x[k]*(n_tor.x[k].scpr(rps))*(dr_tor.x[3*k+2].scpr(rps))/dst2;

				dJ.x[0].x[3*j+2]	+= (drns-4*drns1)/dst4;
				dJ.x[1].x[3*j+2]	+= (drns-5*drns1)/dst5;
				dJ.x[2].x[3*j+2]	+= (drns-6*drns1)/dst6;
				dJ.x[3].x[3*j+2]	+= (drns-7*drns1)/dst7;
			}
		}

//		dJ.data2file("dJ1.txt");
//		cout<<"i : "<<i<<" : \n"<<dJ<<endl;

/**/	rat	= Atom.x[i].xyz;
		for(k=0;k<Point.N;k++)
		{
			rps		= Point.x[k].crd-rat;
			dst2	= rps.ssqr(); 
			dst		= sqrt(dst2);
			dst4	= dst2*dst2;
			dst5	= dst4*dst;
			dst6	= dst4*dst2;
			dst7	= dst6*dst;

			drns0	= Point.x[k].area*(Point.x[k].nor.scpr(rps));

			drns0	/= dst2;

			drns	= Point.x[k].area*Point.x[k].nor.x[0];
			drns1	= drns0*rps.x[0];

			dJ.x[0].x[3*i]	+= (4*drns1-drns)/dst4;
			dJ.x[1].x[3*i]	+= (5*drns1-drns)/dst5;
			dJ.x[2].x[3*i]	+= (6*drns1-drns)/dst6;
			dJ.x[3].x[3*i]	+= (7*drns1-drns)/dst7;


			drns	= Point.x[k].area*Point.x[k].nor.x[1];
			drns1	= drns0*rps.x[1];

			dJ.x[0].x[3*i+1]	+= (4*drns1-drns)/dst4;
			dJ.x[1].x[3*i+1]	+= (5*drns1-drns)/dst5;
			dJ.x[2].x[3*i+1]	+= (6*drns1-drns)/dst6;
			dJ.x[3].x[3*i+1]	+= (7*drns1-drns)/dst7;

			drns	= Point.x[k].area*Point.x[k].nor.x[2];
			drns1	= drns0*rps.x[2];

			dJ.x[0].x[3*i+2]	+= (4*drns1-drns)/dst4;
			dJ.x[1].x[3*i+2]	+= (5*drns1-drns)/dst5;
			dJ.x[2].x[3*i+2]	+= (6*drns1-drns)/dst6;
			dJ.x[3].x[3*i+2]	+= (7*drns1-drns)/dst7;

		}/**/


/** /	dJ.x[0].data2file("dJ0.txt");
		dJ.x[1].data2file("dJ1.txt");
		dJ.x[2].data2file("dJ2.txt");
		dJ.x[3].data2file("dJ3.txt");/**/


/*		it1		= I.x[1].x[i];
		it2		= I.x[2].x[i]*I.x[2].x[i];
		it3		= I.x[3].x[i]*I.x[3].x[i]*I.x[3].x[i];

		bri		= BR.x[i]*BR.x[i];*/

		for(j=0;j<Atom.N;j++)
		{
			dI.x[0].x[j].x[3*i]	= dJ.x[0].x[3*j];
			dI.x[1].x[j].x[3*i]	= 0.5*dJ.x[1].x[3*j]/I.x[1].x[j];
			dI.x[2].x[j].x[3*i]	= 0.3333333333333333333333333*dJ.x[3].x[3*j]/(I.x[2].x[j]*I.x[2].x[j]);
			dI.x[3].x[j].x[3*i]	= 0.25*dJ.x[3].x[3*j]/(I.x[3].x[j]*I.x[3].x[j]*I.x[3].x[j]);

			dBR.x[j].x[3*i]		= -2*BR.x[j]*BR.x[j]*(AG.x[0]*dI.x[0].x[j].x[3*i]+AG.x[1]*dI.x[1].x[j].x[3*i]+AG.x[2]*dI.x[2].x[j].x[3*i]+AG.x[3]*dI.x[3].x[j].x[3*i]);

			dI.x[0].x[j].x[3*i+1]	= dJ.x[0].x[3*j+1];
			dI.x[1].x[j].x[3*i+1]	= 0.5*dJ.x[1].x[3*j+1]/I.x[1].x[j];
			dI.x[2].x[j].x[3*i+1]	= 0.3333333333333333333333333*dJ.x[3].x[3*j+1]/(I.x[2].x[j]*I.x[2].x[j]);
			dI.x[3].x[j].x[3*i+1]	= 0.25*dJ.x[3].x[3*j+1]/(I.x[3].x[j]*I.x[3].x[j]*I.x[3].x[j]);

			dBR.x[j].x[3*i+1]		= -2*BR.x[j]*BR.x[j]*(AG.x[0]*dI.x[0].x[j].x[3*i+1]+AG.x[1]*dI.x[1].x[j].x[3*i+1]+AG.x[2]*dI.x[2].x[j].x[3*i+1]+AG.x[3]*dI.x[3].x[j].x[3*i+1]);

			dI.x[0].x[j].x[3*i+2]	= dJ.x[0].x[3*j+2];
			dI.x[1].x[j].x[3*i+2]	= 0.5*dJ.x[1].x[3*j+2]/I.x[1].x[j];
			dI.x[2].x[j].x[3*i+2]	= 0.3333333333333333333333333*dJ.x[3].x[3*j+2]/(I.x[2].x[j]*I.x[2].x[j]);
			dI.x[3].x[j].x[3*i+2]	= 0.25*dJ.x[3].x[3*j+2]/(I.x[3].x[j]*I.x[3].x[j]*I.x[3].x[j]);

			dBR.x[j].x[3*i+2]		= -2*BR.x[j]*BR.x[j]*(AG.x[0]*dI.x[0].x[j].x[3*i+2]+AG.x[1]*dI.x[1].x[j].x[3*i+2]+AG.x[2]*dI.x[2].x[j].x[3*i+2]+AG.x[3]*dI.x[3].x[j].x[3*i+2]);
		}
	}
	

	dI.x[0].data2file("dI0.txt");
	dI.x[1].data2file("dI1.txt");
	dI.x[2].data2file("dI2.txt");
	dI.x[3].data2file("dI3.txt");

	dBR.data2file("dBr.txt");
	BR.data2file("Br.txt");

	double Kk	= 332.0716;	// ��������� ���/��
	double Ee	= (1-1/80);
	Ee	= (1/E_in-1/E_out);

	double sqgij,gij,dgij,qi,qj,qq;
	double ai,aj,rij,exp_ra,ra,exp_1;
	double G_self,G_inter;

	dGB	= 0;
	GB	= 0;
	G_self	= G_inter	= 0;

	for(i=0;i<Atom.N;i++)
	{		
		ai	= BR.x[i];
		qi	= Q.x[i];
		for(j=0;j<i;j++)
		{
			aj		= BR.x[j];
			qj		= Q.x[j];
			qq		= qi*qj;
			rij		= (Atom.x[i].xyz-Atom.x[j].xyz).ssqr();
			ra		= rij/(koeff*ai*aj);
			exp_ra	= exp(-ra);
			exp_1	= (1+ra)*exp_ra;
			sqgij	= 1/(rij+ai*aj*exp_ra);
			gij		= sqrt(sqgij);
			sqgij	*= -gij;
			G_inter	+= qq*gij;

			for(k=0;k<i;k++)
			{
				dgij		= sqgij*(aj*dBR.x[i].x[3*k]+ai*dBR.x[j].x[3*k])*exp_1;
				dGB.x[3*k]	+= qq*dgij;

				dgij		= sqgij*(aj*dBR.x[i].x[3*k+1]+ai*dBR.x[j].x[3*k+1])*exp_1;
				dGB.x[3*k+1]+= qq*dgij;

				dgij		= sqgij*(aj*dBR.x[i].x[3*k+2]+ai*dBR.x[j].x[3*k+2])*exp_1;
				dGB.x[3*k+2]+= qq*dgij;
			}

			for(k=i+1;k<j;k++)
			{
				dgij		= sqgij*(aj*dBR.x[i].x[3*k]+ai*dBR.x[j].x[3*k])*exp_1;
				dGB.x[3*k]	+= qq*dgij;

				dgij		= sqgij*(aj*dBR.x[i].x[3*k+1]+ai*dBR.x[j].x[3*k+1])*exp_1;
				dGB.x[3*k+1]+= qq*dgij;

				dgij		= sqgij*(aj*dBR.x[i].x[3*k+2]+ai*dBR.x[j].x[3*k+2])*exp_1;
				dGB.x[3*k+2]+= qq*dgij;
			}

			for(k=j+1;k<Atom.N;k++)
			{
				dgij		= sqgij*(aj*dBR.x[i].x[3*k]+ai*dBR.x[j].x[3*k])*exp_1;
				dGB.x[3*k]	+= qq*dgij;

				dgij		= sqgij*(aj*dBR.x[i].x[3*k+1]+ai*dBR.x[j].x[3*k+1])*exp_1;
				dGB.x[3*k+1]+= qq*dgij;

				dgij		= sqgij*(aj*dBR.x[i].x[3*k+2]+ai*dBR.x[j].x[3*k+2])*exp_1;
				dGB.x[3*k+2]+= qq*dgij;
			}
		}

		qq	= qi*qi;
		gij	= 1/ai;
		G_self	+= 0.5*qq*gij;
		gij	*= -gij;		
		for(k=0;k<3*Atom.N;k++)
		{
			dGB.x[k]+= qq*dBR.x[i].x[k]*gij;
		}
	}
	G_self	*= -Kk*Ee;
	G_inter	*= -Kk*Ee;
	GB		= G_self+G_inter;

	dGB		*= -Kk*Ee;

	dGB.data2file("dGB.txt");
	cout.precision(17);
	cout<<"2 Total GB: " <<GB<<endl;
}

void MeshConstructor::SetPntDiff()	// ����������������� �������� � ���������
{
	/*Nmdf.init(Point.N);
	Diff.init(Point.N);

	int i,jt,jn,k;
	for(i=0;i<Nmdf.N;i++)
	{
		jt	= Point.x[i].stp.x[0];
		jn	= Point.x[i].stp.x[1];

		switch  (jt)
		{}

	}*/
}

void MeshConstructor::DoAtomClr()
{
	int i,ia1,ia2,ia3,itw;
	SPoint *P;
	double d1,d2,d3;
	ms1Dint itss(5);

	for(i=0;i<Point.N;i++)
	{
		P	= &Point.x[i];
		switch  (P->stp.x[0])
		{
 			case AtomSphere:
			{
				P->clr	= AtClr.x[P->stp.x[1]];
				break;
			}
			case TwosTorus:
			{
				itw	= P->stp.x[1];
				ia1	= Twos->x[itw].n_at.x[0];
				ia2	= Twos->x[itw].n_at.x[1];
				d1	= (Atom.x[ia1].xyz-P->crd).norm()-Atom.x[ia1].r_wdw;
				d2	= (Atom.x[ia2].xyz-P->crd).norm()-Atom.x[ia2].r_wdw;
				P->clr	= (AtClr.x[ia1]*d2+AtClr.x[ia2]*d1)/(d1+d2);
				break;
			}
			case TrisSphere:
			{
				itw	= P->stp.x[1];
				ia1	= Tris->x[itw].n_at->x[0];
				ia2	= Tris->x[itw].n_at->x[1];
				ia3	= Tris->x[itw].n_at->x[2];
				d1	= (Atom.x[ia1].xyz-P->crd).norm()-Atom.x[ia1].r_wdw;
				d2	= (Atom.x[ia2].xyz-P->crd).norm()-Atom.x[ia2].r_wdw;
				d3	= (Atom.x[ia3].xyz-P->crd).norm()-Atom.x[ia3].r_wdw;
				P->clr	= (AtClr.x[ia1]*(d2*d3)+AtClr.x[ia2]*(d1*d3)+AtClr.x[ia3]*(d1*d2))/(d1*d2+d2*d3+d1*d3);
				break;
			}
			case ScStblSph1:
			{
				itw	= P->stp.x[1];
				ia1	= P->stp.x[2];
				itw	= SRol->x[ia1].Stbl->x[itw].nTw;
				ia1	= Twos->x[itw].n_at.x[0];
				ia2	= Twos->x[itw].n_at.x[1];
				d1	= (Atom.x[ia1].xyz-P->crd).norm()-Atom.x[ia1].r_wdw;
				d2	= (Atom.x[ia2].xyz-P->crd).norm()-Atom.x[ia2].r_wdw;
				P->clr	= (AtClr.x[ia1]*d2+AtClr.x[ia2]*d1)/(d1+d2);
				break;
			}
			case ScStblSph2:
			{
				itw	= P->stp.x[1];
				ia1	= P->stp.x[2];
				itw	= SRol->x[ia1].Stbl->x[itw].nTw;
				ia1	= Twos->x[itw].n_at.x[0];
				ia2	= Twos->x[itw].n_at.x[1];
				d1	= (Atom.x[ia1].xyz-P->crd).norm()-Atom.x[ia1].r_wdw;
				d2	= (Atom.x[ia2].xyz-P->crd).norm()-Atom.x[ia2].r_wdw;
				P->clr	= (AtClr.x[ia1]*d2+AtClr.x[ia2]*d1)/(d1+d2);
				break;
			}
			case ScTrisSphr:
			{
				itw	= P->stp.x[1];
				ia3	= P->stp.x[2];
				ia1	= SRol->x[ia3].Tris->x[itw].n_tr->x[0];
				ia2	= SRol->x[ia3].Tris->x[itw].n_tr->x[1];
				Tris->x[ia1].n_at->itss(*Tris->x[ia2].n_at,itss);
				ia1	= itss.x[0];
				ia2	= itss.x[1];
				d1	= (Atom.x[ia1].xyz-P->crd).norm()-Atom.x[ia1].r_wdw;
				d2	= (Atom.x[ia2].xyz-P->crd).norm()-Atom.x[ia2].r_wdw;
				P->clr	= (AtClr.x[ia1]*d2+AtClr.x[ia2]*d1)/(d1+d2);
				break;
			}
			case ScTwosTor:
			{
				itw	= P->stp.x[1];
				ia3	= P->stp.x[2];
				ia1	= SRol->x[ia3].Twos->x[itw].n_tr.x[0];
				ia2	= SRol->x[ia3].Twos->x[itw].n_tr.x[1];
				Tris->x[ia1].n_at->itss(*Tris->x[ia2].n_at,itss);
				if (itss.N==1)
				{
					P->clr	= AtClr.x[itss.x[0]];
				}
				if (itss.N==2)
				{
					ia1	= itss.x[0];
					ia2	= itss.x[1];
					d1	= (Atom.x[ia1].xyz-P->crd).norm()-Atom.x[ia1].r_wdw;
					d2	= (Atom.x[ia2].xyz-P->crd).norm()-Atom.x[ia2].r_wdw;
					P->clr	= (AtClr.x[ia1]*d2+AtClr.x[ia2]*d1)/(d1+d2);
				}
				if (itss.N==3)
				{
					ia1	= itss.x[0];
					ia2	= itss.x[1];
					ia3	= itss.x[2];
					d1	= (Atom.x[ia1].xyz-P->crd).norm()-Atom.x[ia1].r_wdw;
					d2	= (Atom.x[ia2].xyz-P->crd).norm()-Atom.x[ia2].r_wdw;
					d3	= (Atom.x[ia3].xyz-P->crd).norm()-Atom.x[ia3].r_wdw;
					P->clr	= (AtClr.x[ia1]*(d2*d3)+AtClr.x[ia2]*(d1*d3)+AtClr.x[ia3]*(d1*d2))/(d1*d2+d2*d3+d1*d3);
				}
				break;
			}
		}
	}
}


void MeshConstructor::points2vrml(int &ip0,int &ip1,int &ip2,int &ip4,Vec3db &p3)	// ����vrml ��� ������� � �� �����'i'
{
	int i;
	DefCubNmb(Point.x[ip0].crd);
	fstream sss;
	sss.open("cbsPoints.vrml",ios::out);
	sss.precision(17);
	sss<<"#VRML V2.0 utf8"<<'\n';
	sss<<"WorldInfo { info  [\"Surface\"]}"<<'\n';
	sss<<"Background{ skyColor 0 0 0}"<<'\n';

	i	= ii;
	for(int j=0; j<cbs.n_sp.x[i].N;j++)
	{
		if((cbs.n_sp.x[i].x[j]!=ip0)&&(cbs.n_sp.x[i].x[j]!=ip1)&&(cbs.n_sp.x[i].x[j]!=ip2)&&(cbs.n_sp.x[i].x[j]!=ip4))
		{
			sss<<"Transform {translation "<<Point.x[cbs.n_sp.x[i].x[j]].crd;
			sss<<"scale 0.02 0.02 0.02 "<<endl;
			sss<<"children[Inline {url[\"pnt_y.vrml\"]}]}"<<endl;
		}
	}

	sss<<"Transform {translation "<<Point.x[ip0].crd;
	sss<<"scale 0.02 0.02 0.02 "<<endl;
	sss<<"children[Inline {url[\"pnt_mt.vrml\"]}]}"<<endl;

	sss<<"Transform {translation "<<Point.x[ip1].crd;
	sss<<"scale 0.02 0.02 0.02 "<<endl;
	sss<<"children[Inline {url[\"pnt_g.vrml\"]}]}"<<endl;

	sss<<"Transform {translation "<<Point.x[ip2].crd;
	sss<<"scale 0.02 0.02 0.02 "<<endl;
	sss<<"children[Inline {url[\"pnt_b.vrml\"]}]}"<<endl;

	sss<<"Transform {translation "<<Point.x[ip4].crd;
	sss<<"scale 0.02 0.02 0.02 "<<endl;
	sss<<"children[Inline {url[\"pnt_c.vrml\"]}]}"<<endl;

	sss<<"Transform {translation "<<p3;
	sss<<"scale 0.02 0.02 0.02 "<<endl;
	sss<<"children[Inline {url[\"pnt_m.vrml\"]}]}"<<endl;


	sss.close();
}


void MeshConstructor::points2vrml(int &i,int &ip0,int &ip1,int &ip2,int &ip4, Vec3db &p5, Vec3db &p3)	// ����vrml ��� ������� � �� �����'i'
{
	fstream sss;
	sss.open("cbsPoints.vrml",ios::out);
	sss.precision(17);
	sss<<"#VRML V2.0 utf8"<<'\n';
	sss<<"WorldInfo { info  [\"Surface\"]}"<<'\n';
	sss<<"Background{ skyColor 0 0 0}"<<'\n';

	for(int j=0; j<cbs.n_sp.x[i].N;j++)
	{
		if((cbs.n_sp.x[i].x[j]!=ip0)&&(cbs.n_sp.x[i].x[j]!=ip1)&&(cbs.n_sp.x[i].x[j]!=ip2)&&(cbs.n_sp.x[i].x[j]!=ip4))
		{
			sss<<"Transform {translation "<<Point.x[cbs.n_sp.x[i].x[j]].crd;
			sss<<"scale 0.02 0.02 0.02 "<<endl;
			sss<<"children[Inline {url[\"pnt_y.vrml\"]}]}"<<endl;
		}
	}

	sss<<"Transform {translation "<<Point.x[ip0].crd;
	sss<<"scale 0.02 0.02 0.02 "<<endl;
	sss<<"children[Inline {url[\"pnt_mt.vrml\"]}]}"<<endl;

	sss<<"Transform {translation "<<Point.x[ip1].crd;
	sss<<"scale 0.02 0.02 0.02 "<<endl;
	sss<<"children[Inline {url[\"pnt_g.vrml\"]}]}"<<endl;

	sss<<"Transform {translation "<<Point.x[ip2].crd;
	sss<<"scale 0.02 0.02 0.02 "<<endl;
	sss<<"children[Inline {url[\"pnt_b.vrml\"]}]}"<<endl;

	sss<<"Transform {translation "<<Point.x[ip4].crd;
	sss<<"scale 0.02 0.02 0.02 "<<endl;
	sss<<"children[Inline {url[\"pnt_c.vrml\"]}]}"<<endl;

	sss<<"Transform {translation "<<p5;
	sss<<"scale 0.02 0.02 0.02 "<<endl;
	sss<<"children[Inline {url[\"pnt_r.vrml\"]}]}"<<endl;

	sss<<"Transform {translation "<<p3;
	sss<<"scale 0.02 0.02 0.02 "<<endl;
	sss<<"children[Inline {url[\"pnt_m.vrml\"]}]}"<<endl;


	sss.close();
}

void MeshConstructor::points2vrml(int &i)	// ����vrml ��� ������� � �� �����'i'
{
	fstream sss;
	sss.open("cbsPoints.vrml",ios::out);
	sss.precision(17);
	sss<<"#VRML V2.0 utf8"<<'\n';
	sss<<"WorldInfo { info  [\"Surface\"]}"<<'\n';
	sss<<"Background{ skyColor 0 0 0}"<<'\n';

	for(int j=0; j<cbs.n_sp.x[i].N;j++)
	{	
		sss<<"Transform {translation "<<Point.x[cbs.n_sp.x[i].x[j]].crd;
		sss<<"scale 0.02 0.02 0.02 "<<endl;
		sss<<"children[Inline {url[\"pnt_y.vrml\"]}]}"<<endl;
	}
	sss.close();
}


double MeshConstructor::CavDatFile(ms1D<Vec3db> &pnt, ms1D<Vec3db> &nrm, ms1Ddb &sqr)
{
	fstream sss;
	double Vv;
	Vec3db p0;
	int i;
	Vv	= 0;
	p0	= pnt.sum()/((double)pnt.N);
	for(i=0;i<pnt.N;i++)
	{
		Vv	+= 0.33333333333333333333333333333*((pnt.x[i]-p0).scpr(nrm.x[i]))*sqr.x[i];
	}

	sss.open("cavdata.txt",ios::out);
	sss.precision(12);
	sss.setf(ios::left);
	sss.setf(ios::scientific);
	sss<<"TITLE"<<endl;
	sss<<" Square of surface : S = "<<sqr.sum()<<" (Angst)^2."<<endl;
	sss<<" Volume of cavity  : V = "<<Vv<<" (Angst)^3."<<endl;
	sss<<" Number of elements: N = "<<pnt.N<<" units."<<endl;
	sss<<" Topology factor : Nf+Np-Ne = "<<Point.N+Trngl.N-Edge.N<<" (Eiler)."<<endl;
	/*sss<<" Center of mass : "<<pc;
	sss<<" Diagonal : "<<evg;
	sss<<" Eigenvector of matrix transfer : "<<endl<<egm;//*/
	
	sss<<"END"<<endl;
	sss<<endl;
	sss<<"TESSER"<<endl;
	sss<<pnt.N<<endl;
	for (i=0;i<pnt.N;i++)
	{						
		sss<<i+1<<"	"<<pnt.x[i].x[0]<<"	"<<pnt.x[i].x[1]<<"	"<<pnt.x[i].x[2]<<"	"<<sqr.x[i]<<endl;
	}		
	sss<<"END"<<endl;
	sss<<endl;
	sss<<"NORMALS"<<endl;
	for (i=0;i<pnt.N;i++)
	{						
		sss<<i+1<<"	"<<nrm.x[i].x[0]<<"	"<<nrm.x[i].x[1]<<"	"<<nrm.x[i].x[2]<<"	"<< (sqr.x[i]!=0 ? sqrt(pi/sqr.x[i])/p_rol : 0) <<endl;
	}
	sss<<"END"<<endl;
	sss.close();

	return Vv;
}
void MeshConstructor::my_exit(int exitcode)
{
	exit(exitcode);
}

//-------------------------------------------------------------------------------------------------

#endif