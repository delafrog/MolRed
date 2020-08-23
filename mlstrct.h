// ************************************************
//  ��������� ������-TAGSS-  (��� 2.0.0)
//  Triangulated Adaptive Grid of Smotoh Surface
//	28 �� 2006�
//  ��������
//  (C) DIMONTA Lab
// ************************************************

#ifndef _MLSTRCT_H
#define _MLSTRCT_H

#include "massiv.h"
using namespace std;

struct solpar
{
	double R_rol;
	double s_rol;
	double r_min;
};

struct grdpar
{
	double R_tr;	// ������� ������ (� ��������������)
	double R_mx;	// ��������� ������ (� ��������������)
	double alfa;	// ����� ����� ����������
	double Thet;	// ������ ������������� ������
	double Phi;		// �������� ������������� ������
	int		Nc;		
	int		Np;
};

struct cntlpar
{
	char isExS;
	char isOut;
	char TpSur;
	char TpBld;
};

struct cappar
{
	smschar ProtName;
	smschar LigName;
	double x;
	double y;
	double z;
	double R;

	cappar(){}
	~cappar(){}
};

struct filenames
{
	smschar protname;
	smschar ligname;
	smschar outname;
	char	isoutfl;	// Y - сохранять, N - не сохранять

	filenames()
	{
		protname.sm(1);
		ligname.sm(1);
		outname.sm(1);
	}
	~filenames(){}
};
struct surfconstr
{
	double trsize;
	double maxtrsize;
	int	   refine;
	double rolradius;
	double secrolrad;
	double minradcrv;
	double in_thet;
	double in_phi;
	double adptmesh1;
	double adptmesh2;
	smschar protlig;
	double cavenmbr;

	surfconstr()
	{
		refine	= 0;
		protlig.sm(1);
	}
	~surfconstr(){}
};

struct vslztn
{
	char isvrml;
	char viziner;
	ms1D<Vec3db> surfclr;
	ms1D<Vec3db> caveclr;
	char isatsrc;
	char isatcvc;

	vslztn()
	{
		caveclr.sm(1);
	}
	~vslztn(){}
};

struct slvntn
{
	double eps_in;
	double eps_cv;
	double eps_out;
	double c;
	double sgb1;
	double sgb2;
	slvntn(){}
	~slvntn(){}
};
struct atmprmtr
{
	ms1D<smschar>	AtNm;
	ms1D<double>	r_wdw;
	ms1D<Vec3db>	AtColor;

	atmprmtr()
	{
		AtNm.sm(1);
		r_wdw.sm(1);
		AtColor.sm(1);
	}
	~atmprmtr(){}
};


struct configpar
{
	filenames	fnms;
	surfconstr	surfpar;
	vslztn		viz;
	slvntn		solvtn;
	atmprmtr	atomparam;

	configpar(){}
	~configpar(){}

	friend ostream &	operator <<(ostream &stream, const configpar &a)
	{
		stream<<"VISUALIZATION"<<endl;
		stream<<"PROTNAME		"<<a.fnms.protname.x<<endl;
		stream<<"LIGNAME		"<<a.fnms.ligname.x<<endl;
		stream<<"OUTNAME		"<<a.fnms.outname.x<<endl;
		stream<<"ISOUTFL		"<<a.fnms.isoutfl<<endl;
		stream<<"END"<<endl<<endl;

		stream<<"SURFACE_CONSTRUCTION"<<endl;
		stream<<"TRSIZE 		"<<a.surfpar.trsize<<endl;
		stream<<"MAXTRSIZE	"<<a.surfpar.maxtrsize<<endl;
		stream<<"REFINE		"<<a.surfpar.refine<<endl;
		stream<<"ROLRADIUS	"<<a.surfpar.rolradius<<endl;
		stream<<"SECROLRAD	"<<a.surfpar.secrolrad<<endl;
		stream<<"MINRADCRV	"<<a.surfpar.minradcrv<<endl;
		stream<<"INITVEC		"<<a.surfpar.in_thet<<"	"<<a.surfpar.in_phi<<endl;
		stream<<"ADAPTMESH	"<<a.surfpar.adptmesh1<<"	"<<a.surfpar.adptmesh2<<endl;
		stream<<"PROTLIG		"<<a.surfpar.protlig.x<<endl;
		stream<<"CAVENMBR		"<<a.surfpar.cavenmbr<<endl;
		stream<<"END"<<endl<<endl;
		stream<<"VISUALIZATION"<<endl;
		stream<<"ISVIZ		"<<a.viz.isvrml<<endl;
		stream<<"SURFCLR		"<<a.viz.surfclr;
		stream<<"CAVECLR		"<<a.viz.caveclr;
		stream<<"ISATSRC		"<<a.viz.isatsrc<<endl;
		stream<<"ISATCVC		"<<a.viz.isatcvc<<endl;
		stream<<"END"<<endl<<endl;

		stream<<"SOLVENTION"<<endl;
		stream<<"INRDIEL		"<<a.solvtn.eps_in<<endl;
		stream<<"CAVDIEL		"<<a.solvtn.eps_cv<<endl;
		stream<<"OUTDIEL		"<<a.solvtn.eps_out<<endl;
		stream<<"GBPARC		"<<a.solvtn.c<<endl;
		stream<<"SGBPAR1		"<<a.solvtn.sgb1<<endl;
		stream<<"SGBPAR2		"<<a.solvtn.sgb2<<endl;
		stream<<"END"<<endl<<endl;

		stream<<"ATOMS_TIPIZATION"<<endl;
		int i;
		for(i=0;i<a.atomparam.AtNm.N;i++)
		{
			stream<<a.atomparam.AtNm.x[i].x<<"		"<<a.atomparam.r_wdw.x[i]<<"		"<<a.atomparam.AtColor.x[i];
		}
		stream<<"END"<<endl<<endl;

		return stream;
	}


};

struct aminotip
{
	//smschar acidname;
	smpl_ms<smschar>	TpNm;
	ms1D<int>			mmff_tp;
};




#endif
