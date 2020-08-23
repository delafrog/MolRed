#ifndef _ROLLING_H
#define _ROLLING_H

#include "volume.h"
#include "mlstrct.h"
#include "Trimesh.h"

#define ADD_TRS_NMBR	500	
#define ADD_TWS_NMBR	500	

#define ADD_SCTRS_NMBR	10
#define ADD_SCSTS_NMBR	10
#define ADD_SCTWS_NMBR	10


#define ADD_GRP_NMBR	100



#define IND_TR_ATOM		1		// ���� ������� ������������. ���
#define IND_NONTR_ATOM	0		// ���� ���������
#define IND_NTRSF_ATOM	2		// ���� ������� ���� ����������. ���
#define IND_SURF_ATOM	3		// ���� ������� ���� ����������. ���

#define MY_INFINITY		1e20
#define SQ_ERR_ALW		1e-14
#define ERR_ALW			2e-12

extern bool nondelete;

class AtPnt
{public:

	Vec3db	xyz;		// ����� ���
	double	r_wdw;		// ��� ���

	p_ms1Dint n_tr;		// ��� ����� �. ���
	p_ms1Dint n_tw;		// ��� ����� ��

	p_ms1Dint n_trs;	// ����� �. ���
	p_ms1Dint n_tws;	// ����� �� ����

	p_ms1Dint n_un;		// ����� ���������
	p_ms1Dint n_ge;		// ������ ��� ���������

	p_ms1Dint c_un;		// ��� �������������� ��������������

	p_ms1Dint n_pnt;	// ��� ����������������

	ms1D<Vec3db> csf;	// �������� ���� � ���
	ms1D<double>mx;		// ���� ���� �������� � ������������.

	ms1DVec3db csf_c;	// ��� (� ����� ��� ������ ��� �������� ���� � ���
	ms1Ddb	mx_c;		// ��� (� ����� ��� ������ ��� ���� ���� ����� �� � ������ ������

	ms1D<int>		nfs;	// ��� �������.
	ms1D<ms1Dint>	set_ntw;// �������� ���� ��� ��

	int				cfs;	// указатель на номер текущей группы связности

	bool Pnt2Surf(Vec3db &p_in, Vec3db &p_out, Vec3db &nrm,  double &sq_dst, double &p_rol, int &infs);	// ���� ���'p_in' � �� -> 'p_out', ��� - 'nrm'



	friend void CopyObject(AtPnt &a,AtPnt &b);
	friend void InitObject(AtPnt &a);
	friend void ClearObject(AtPnt &a);
//n_ge = new ms1Dint [1];n_un = new ms1Dint [1];n_tr = new ms1Dint [1];n_tw = new ms1Dint [1];n_tws = new ms1Dint [1];n_trs = new ms1Dint [1];n_pnt = new ms1Dint [1];
//delete [] n_ge; delete [] n_un; delete [] n_tr;  delete [] n_tw;delete [] n_tws;delete [] n_trs;delete [] n_pnt;

	AtPnt(){n_ge = 0x0;n_un = 0x0;c_un = 0x0;n_tr = 0x0;n_tw = 0x0;n_tws = 0x0;n_trs = 0x0;n_pnt = 0x0;}
	~AtPnt(){if (!nondelete){ClearObject(*this);}}

};

class TwPnt
{public:
	Vec3db	rp;			// ����� ��� ��
	Vec3db	x;			// 'x' ��� ����� ���
	Vec3db	y;			// 'y' ��� ����� ���
	Vec3db	z;			// 'z' ��� ����� ���

	ms1DVec3db	*dpc;	// ���� ��� ��
	ms1DVec3db	*dz;	// ���� ����� ��
	ms1Ddb		*dh;	// ���� ��������


	Vec2db	mx;			// ��������� ����� ����
	Vec2int	n_at;		// ��� ���-��

	p_ms1Dint n_pnt;	// ��� ������������ ��

	Vec3db	hab;		// ��� ������� �������������� � 'rp' � ��� - ��.
	Vec2int	n_tr;		// ��� ������ �����. ���

	//---����������� � ���� ���� ����� ����� ��(��� 'rp' ��������� 'hab' ���)
	Vec3db		nc2;	// ���� ����� ������ ������ ���� ��� �-�����������������������
	double		cs2;	// ������������ � ����� 'nc2' � ���������� ����� �����

	Vec3db		nc1;	// ������� ���rp � ���� �� ����� ��� �-���

	double		cs1;	// ������������������� ��.
	//---


	int			nfs;	// ������ ����.
	int			igr;	// ������������

	bool		iss;
	bool		ism;	// ������� ��������� ��� �������� �� ��.

	bool Pnt2Surf(Vec3db &p_in, Vec3db &p_out, Vec3db &nrm, double &sq_dst,  double &p_rol, int &infs);	// ���� ���� ��������� �� �'sq_dst' ��� ������ �������� ��

	friend void CopyObject(TwPnt &a,TwPnt &b);
	friend void InitObject(TwPnt &a);
	friend void ClearObject(TwPnt &a);	

	TwPnt(){n_pnt = 0x0;}
	~TwPnt(){if (!nondelete){ClearObject(*this);}}
};

class TrPnt
{public:
	Vec3db	pc;			// ����� ����. ���
	Vec3db	nr;			// ��� ����� 'pc' � ���� ��� - ��

	ms1DVec3db	*dpc;	// ���� �������� � ���� ��������- ��
	//Mtr3db	mx;		// �������� ��������
	ms1DVec3db	*mx;	// ������� ��� ����'mx' � �������. ���(����� ������ �����
	//bool		_xm;	// ����������� 'xm'
 
	p_ms1Dint	n_at;		// ��� ��� - ��.

	p_ms1Dint	n_tr;		// ��� ���� �. ���(���������)
	p_ms1Dint	n_tw;		// ��� ���� ��
	p_ms1Dint	tr_n;		// ��� ���� �. ���(�������� ���

	ms1DVec3db	*s_tr;		// ��� ������� ���� ���������.
	ms1Ddb		*s_mx;		// ��� �����������������

	//ms1DVec3db	s_dr;		// ��� ������� ���� �. ���
	//ms1Ddb		s_ds;		// ��� �����

	p_ms1Dint	c_tr;		// ��� �������. ���
	p_ms1Dint	c_tw;		//

	p_ms1Dint n_pnt;		// ��� ������������ �. ���

	int			nfs;		// ������ ����.
	int			igr;		// ������������

	bool isTris(Vec3db & a);// ����, ������ � ���'a' � ��������� �. ���

	bool Pnt2Surf(Vec3db &p_in, Vec3db &p_out, Vec3db &nrm, double &sq_dst, double &p_rol,int &infs);	// ���� ���'p_in' � �. ���(��� �'sq_dst' ��� ������ �������� �. ���

	friend void CopyObject(TrPnt &a,TrPnt &b);
	friend void InitObject(TrPnt &a);
	friend void ClearObject(TrPnt &a);

	TrPnt(){n_pnt=0x0;mx=0x0;n_at=0x0;n_tr=0x0;n_tw=0x0;tr_n=0x0;c_tr=0x0;c_tw=0x0;s_tr=0x0;s_mx=0x0;dpc=0x0;}
	~TrPnt(){if (!nondelete){ClearObject(*this);}}
};

class ScTrPnt	// ���� �. ������������ (���� ���. ������������
{public:

	Vec3db	pc;			// ����� ��� �. ���
	Vec3db	nr;			// ��� ����� 'pc' � ���� ������. ���- �� 
	//Mtr3db	mx;			// �������� ��������
	ms1DVec3db	*mx;	// ������� ���� � ��� ���� ��.

	ms1DVec3db	*dpc;	// ���� �������� �. ����� ����� �������� -�� ���� �� ��� ��. ����
	p_ms1Dint	n_at;	// ��� ���- �� �����. ������������


	p_ms1Dint	n_tr;		// ��� �. ���- ��.
	p_ms1Dint	n_tw;		// ��� �� ���������(������ ���� ���� (?)

	p_ms1Dint	n_str;		// ��� ���� �. ���(���������) (?)
	p_ms1Dint	n_stw;		// ��� ���� ��
	//p_ms1Dint	tr_n;		// ��� ���� �. ���(�������� ���

	//p_ms1Dint	c_tr;		// ��� �������. ���
	//p_ms1Dint	c_tw;		//

	p_ms1Dint n_pnt;		// ��� ������������ �. ���

	double	csa;			// ������

	//int			nfs;		// ������ ����.
	//int			igr;		// ������������

	bool Pnt2Surf(Vec3db &p_in, Vec3db &p_out, Vec3db &nrm, double &sq_dst, double &s_rol);	// ���� ���'p_in' � �. ���(��� �'sq_dst' ��� ������ �������� �. ���

	bool isTris(Vec3db & a);// ����, ������ � ���'a' � ��������� �. ���

	friend void CopyObject(ScTrPnt &a,ScTrPnt &b);
	friend void InitObject(ScTrPnt &a);
	friend void ClearObject(ScTrPnt &a);

	friend void Swap(ScTrPnt &a,ScTrPnt &b);

	ScTrPnt(){n_pnt=0x0;mx=0x0;n_tr=0x0;n_tw=0x0;n_str=0x0;n_stw=0x0;dpc=0x0;n_at=0x0;}
	~ScTrPnt(){if (!nondelete){ClearObject(*this);}}
};

class ScStPnt		// ���� �� ����������������������
{public:			// ����� � ����������������
	Vec3db pc1;		// ����� ��� ���
	Vec3db pc2;		// ����� ��� ���
	Vec2int n_tr;	// ��� � ������������
	Vec3db	nst;	// �������� � 'pc1' �'pc2'
	Vec3db  nc1;	// ��� � ��������� ���'pc1'
	Vec3db  nc2;	// ��� � ��������� ���'pc2'

	ms1DVec3db *dpc1;	// ���� �������� ���pc1 � ��������- ��
	ms1DVec3db *dpc2;	// ���� �������� ���pc2 � ��������- ��

	p_ms1Dint n_pnt1;	// ��� ������������ �� ���'pc1'
	p_ms1Dint n_pnt2;	// ��� ������������ �� ���'pc2'

	p_ms1Dint n_at1;	// ��� ��� ��� � �������� �� ���'pc1'
	p_ms1Dint n_at2;	// ��� ��� ��� � �������� �� ���'pc2'

	int		nTw;	// ���������� ��������� "�����
	double	d;		// ���� ���� ���'pc1' �'pc2'
	double	csa;	// ������������ ��������� ��� ����� 'ns'
	bool	isf;	// ����������������� ��� ��� ��

	bool Pnt2Surf1(Vec3db &p_in, Vec3db &p_out, Vec3db &nrm, double &sq_dst, double &s_rol);	// ���� ���'p_in' � �. ���(��� �'sq_dst' ��� ������ �������� �. ���
	bool Pnt2Surf2(Vec3db &p_in, Vec3db &p_out, Vec3db &nrm, double &sq_dst, double &s_rol);	// ���� ���'p_in' � �. ���(��� �'sq_dst' ��� ������ �������� �. ���

	bool isSt1(Vec3db &a);	// ������������'a' � �����'pc1'	
	bool isSt2(Vec3db &a);	// ������������'a' � �����'pc2'
	bool isSt1(Vec3db &a, double &dz);	// ������������'a' � �����'pc1'
	bool isSt2(Vec3db &a, double &dz);	// ������������'a' � �����'pc2'
	
	friend void CopyObject(ScStPnt &a,ScStPnt &b);
	friend void InitObject(ScStPnt &a);
	friend void ClearObject(ScStPnt &a);

	ScStPnt(){n_pnt1 = 0x0;n_pnt2 = 0x0;dpc2=0x0;dpc1=0x0;n_at1=0x0;n_at2=0x0;}
	~ScStPnt(){if (!nondelete){ClearObject(*this);}}
};


class ScTwPnt	// ���� � ����������������� �. ������������
{public:
	Vec3db	x,y,z;	// ���� ����� ���
	Vec3db	rp;		// ������� ����� ���������
	Vec2db	mx;		// "��" ����� �� ����� �� ��.

	ms1DVec3db	*dpc;	// ���� ��� ��
	ms1DVec3db	*dz;	// ���� ����� ��
	ms1Ddb		*dh;	// ���� ��������

	ms1Dint		*n_at;	// ���� ��������

	Vec2int n_tr;	// ��� �. �����. ������� ���������� ��. �
	Vec2int n_stb;	// ��� ���. ���. �����. ���� ������������. ��� ��� ��
	Vec2int type_;	// ����� ������. ����� ���� � ��� ��� (0 - �. ��� 1 ��2- ��� ���� ����

	p_ms1Dint n_pnt;// ��� ������������ ��

	bool ismorpi;	// ���� � � ���� ���������180 ����
	double	r_sc;	// ��� ���������
	double	d;		// ������ ��� ����� �����. �����. ����

	//Vec3db		nc2;	// ���� ����� ������ ������ ���� ��� �-�����������������������
	double		cs2;	// ������������ � ����� 'nc2' � ���������� ����� �����

	bool Pnt2Surf(Vec3db &p_in, Vec3db &p_out, Vec3db &nrm, double &sq_dst, double &s_rol);	// ���� ���'p_in' � �. ���(��� �'sq_dst' ��� ������ �������� �. ���

	friend void CopyObject(ScTwPnt &a,ScTwPnt &b);
	friend void InitObject(ScTwPnt &a);
	friend void ClearObject(ScTwPnt &a);

	ScTwPnt(){n_pnt =0x0;dpc=0x0;dz=0x0;dh=0x0;n_at=0x0;}
	~ScTwPnt(){if (!nondelete){ClearObject(*this);}}
};

class ScRll
{public:
    ms1D<bool>		ifl;		// ���������� ����� � ����� ����
	ms1D<ScTrPnt>	*Tris;		// �. ����� ����
	ms1D<ScStPnt>	*Stbl;		// ��� ��������������
	ms1D<ScTwPnt>	*Twos;		// ��� �� ���������
	double			s_rol;		// ����t ����������������� ��� ���.
	int				igr;		// ������ ������������ � ����� ����

	bool Pnt2Surf(Vec3db &p_in, Vec3db &p_out, Vec3db &nrm, double &sq_dst,int &type, int &id);	// ���� ���'p_in' � ��� ��������� �'sq_dst' ��� ������ ��������. ����

	friend void CopyObject(ScRll &a,ScRll &b);
	friend void InitObject(ScRll &a);
	friend void ClearObject(ScRll &a);

	ScRll(){Tris=0x0;Stbl=0x0;Twos=0x0;}
	~ScRll(){if (!nondelete){ClearObject(*this);}}
};

class MolData
{public:

	smpl_ms<smschar> AtTp;	// �����������������. 
	ms1D<Vec3db>	AtClr;	// ������
	
	Mtr3db		eig;	// �������� ����������
	Vec3db		pc;		// ������� ���� ���.

	ms1Ddb		Q;		// ���� ���;

	ms1D<AtPnt> Atom;	// �������.
	ms1D<TrPnt> *Tris;	// �����. ���
	ms1D<TwPnt> *Twos;	// ������

	ms1D<ScRll> *SRol;	// �������������

	msDDint	TrsCnnNmb;	// ������� �����. ��������� ���������
	msDDint	TwsCnnNmb;	// ������� ������ ������ ���������
	msDDint	AtmCnnNmb;	// ������� ������� ������ ���������

	msDDint TrsCnfGrp;	// ������� �����-�����. ���

	ms1D<double>	sro;	// ��� ���� ���������
	ms1D<int>		Nc;		// ��� ������������������ ��.
	ms1D<int>		S_At;	// ��� ����������.	
	ms1D<int>		SAlw;	// ��� ���� ��� �������� ������� ���	


	ms1D<int>		tpind;	// номера идентификаторов типов атомов

	cubdev		cbs;	// �������� � ��.

	double		p_rol;	// ��� �������
	double		s_rol;	// ��� ������������
	double		d_min;	// ��� ����������.
	double		sec_r;	// ��� ��� ������������

	int At_ntr_mx;
	int At_nun_mx;
	int Tr_nat_mx;

	bool		InEig;	// ������� ���������������

	void SetEigBasis();	// ��������������� ������������ ����
	void Get2EigBasis();// �������������
	void Ret2InitBas();	// ������������

	void SetAtNeib(int &j);	// �������������

	void Tr_in_cbs();	// ��������. ���� ���
	void Tw_in_cbs();	// ��������� � ���

	// �������������

	void SetDataMol(ms1D<Vec3db> &xyz, ms1Ddb &r_wdw, ms1Ddb &Q_in, solpar &slp, smpl_ms<smschar> &AtType, ms1D<int> &tpind);
	void SetDataMol(ms1D<Vec3db> &xyz, ms1Ddb &r_wdw, ms1D<Vec3db> &clr);
	void SetAtColor();	// �������� ��� ���� � ��
	//void SetAtColor(ms1D<Vec3db> &clr;);	// �������� ��� ���� � ��

	void SetCubDiv();	// ���� � ��

	// ��� ����-------------

	
	void SetRolling();	// ����������� ����	

	// ���� ����

	void SetTris();		// �����������(������ 3 ��� ����������������� ����.
	void CorTris();		// ������������. ���.

	void SetTwos();		// �������� ������� �� ���.
	void CorTwos();		// ����������� ������ 

	void SetConect();	// ����������� �. ��� ���������. ������������ ������
	void CorTrisTw();	// ������������. ��� ������������� ������

	void SetTrNeib();	// �������. ���� ���	
	void SetTwNeib();	// �������� ���� ���
	void SetTrNbTr();	// �������. ���� �. ���

	void SetTrsCnf();	// �������������. ����� � ���
	void SetCnfGrp();	// ����������������. ���

	void SetTwsCnf();	// �������������


	// ���� ����
	void SetSecRol();	// ����������� ���������

	void SetScTris(ms1D<ms1Dint> &nScTrPr);	// �������. ������������
	void SetScTris(ms1D<int> &n_icg, ms1D<ms1Dint> &nScTrPr);	// �������. ������������

	void SetScStbl(ms1D<ms1Dint> &nScStPr);	// �������������������������
	void SetScStbl(ms1D<int> &n_icg, ms1D<ms1Dint> &nScStPr);	// �������������������������

	void SetScTwos(ms1D<ms1Dint> &nScTrPr, ms1D<ms1Dint> &nScStPr);	// �������� ���������
	void SetScTwos(ms1D<int> &n_icg, ms1D<ms1Dint> &nScTrPr, ms1D<ms1Dint> &nScStPr);	// �������� ���������

	void CorScTris(ms1D<ms1Dint> &nScTrPr);		// ������������. ��� ���������
	void CorScTris(ms1D<int> &n_icg, ms1D<ms1Dint> &nScTrPr);	// ������������. ��� ���������

	void CorScStTr(ms1D<ms1Dint> &nScTrPr);		// ������������. ��� ���������

	void CorScTwTr();							// ������������. ��� ���������
	void CorScTwTr(ms1D<int> &n_icg);			// ������������. ��� ���������

	void SetAtomCn();							// �������� ���������� �������

	void SetScForb();							// ���������� �����������������

	//void CorScTwos();							// ��������� d	

	void ScRlAnlze(ms1D<int> &SecCnfGrp);	// ��� ����� ��������� ����������������.
	void ConflFree(ms1D<int> &n_icg, ms1D<ms1Dint> &nScTrPr, ms1D<ms1Dint> &nScStPr); //��� � �������� ��� � ���������

	// ���������������vrml-���
	void Atom2File();	// ��� �vrml �� ����������. ��� ���������
	void Atom2File(int k);	// ��� �vrml �� �������������� ��� 'k'
	void Atom2File(ms1Dint &ind);
	void CnTr2File(int k=-1);	// ��� �vrml �� ����������. ��� ���������
	void Tris2File(int k=0);	// ��� �vrml �� �����. ��� ���������
	void ScTr2File(int k=-1);	// ��� �vrml �� �����. ��� ���������
	void ScSt2File(int k=-1);	// ��� �vrml �� ������������ ���������

	void Cube2File(int k);		// ��� �vrml �� ���������� ������ �� �����'k'
	//--------------------
	
	void ClearMoldata();	// ���������

	friend void CopyObject(MolData &a,MolData &b);
	friend void InitObject(MolData &a);
	friend void ClearObject(MolData &a);


	MolData(){Tris = 0x0;Twos = 0x0; SRol = 0x0; InEig=false;}
	~MolData()
	{
		if (!nondelete)
		{
			ClearObject(*this);
		}
	}

	//	surf 		*Srf;	// ���� � ���������������������� ����.
};

#endif
