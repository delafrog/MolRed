
#ifndef _MESHCREATOR_H
#define _MESHCREATOR_H

#include "Trimesh.h"
#include "rolling.h"
#include "mlstrct.h"
//#include <iostream>

class Surface;

//using namespace std;

class MeshConstructor : public TrSurface , public MolData
{public:

	Surface * SRF;

	// �����������������
	// � ��� ����
	int ix,iy,iz,ii;	// ����� ��� ������. ii - �������������
	int i_x,i_y,i_z,ix_,iy_,iz_,iix,iiy,iiz,ii_;
	double sp;	// ���� ������ �� - � �� ���� �������
	//sp	= subcub::sz+2*R_expd;
	Vec3db cb_crd;		// ����� ��������� ��
	Vec3db p_in;		// ����� ������ ���
	Vec3db p_out,n_out;	// ����� ���� ������������ �����
	//-----
	// ������ ������ ���� ����
	int NPnt;
	int NEdg;
	int NTri;
	//------
	// ������ ������ ��������� ������ ���������
	ms1D<int> B1;
	ms1D<int> B2;
	//------
	// ������ �������� �����. (������ ������� ����
	double dst,dst1;
	//------
	// ����� � ����� �� ���� �����������
	Vec3int type;
	//-----
	// ����� � ����� ��� ������ ������
	int n_un_srf;

	//- � ����������-
	int time,time1;
	//-----

	double Gtot;

	ms1Dint indtw;

	int NumberOfCycle;

	// ����������� � �����:
	int n_At;			// ������
	int n_Tw;			// ����� 
	int n_Tr;			// ����. ���
	int n_ScGr;			// ������ ���������
	int n_ScSt;			// �������� ���� ���������
	int n_ScTr;			// ����. ������������
	int n_Rslt;			// �������������������



	ms1D<int>		C_At;	// ��� ������������� ������ ��������� ���� ��� (���� ����
	ms1D<int>		NC_At;	// ���������-�������������������
	
	double Theta;		// �� 
	double Phi;

	// ��������� ��������� �������������
	double R_crcl;	// ������� ����� ��������������
	double R_high;	// ��� ��� ������
	double R_expd;	// ��� ������������ - � ���������

	double R_Tr;	// ����� ������.

	double R_maxx;	// ��������� ����� ��������������

	double alf_c;	// ����� ���� ����� ����������

	int		N_rfn;	// количество вызовов процедуры двоичного дробления секти


	//fstream outstm;
	//streambuf* cout_buffer;
	
	//------------
	// ������ �����

	ms1D<ms1Ddb>	I;	// ���� � ����� ����� ����. (n,i)-(��� ����� ������
	ms1D<ms1DDdb>	dI;	// ������ ����� � ����� ����� ����. (n,i,j)-(��� ����� ������ �����. �����)

	ms1Ddb			BR;	// ����� ��� ���
	ms1D<ms1Ddb>	dBR;// ������ ����� ����

	double			GB;	// ��� ��������� �������
	ms1Ddb			dGB;// ������ GB

//	ms1D<ms1DDint>	Nmdf;	// ��� ��� ����� ��������������� ��������
//	ms1D<ms1DVec3db> Diff;	// ���� ������� �����dx dy dz ������� ��� ����� � Nmdf

	//ms1D<ms1DVec3db>	TrDf;	// ������. ���
	//ms1D<TwsDfPr>	TwDf;	// 
	//ms1D<ms1DVec3db>	sTrDf;
	//ms1D<ms1DVec3db>	sTwDf;
	//ms1D<ms1DVec3db>	sStDf;

	// ���
	MeshConstructor();
	void InitSurface(TrSurface	&A);
	void InitMolData(MolData	&M);

	void FreeSurface(TrSurface	&A);
	void FreeMolData(MolData	&M);
	
	// ��������������
	void SetPar(grdpar &Gpar);
	void SetPar();

	// ��� ����� ����� ��������������
	void AddPnt1(Vec3db &p3,Vec3db &n3,ms1D<int> &b, int &En, int &Pn1, int &Pn2, int &s);	// �������� ����� ������ ����'En' ��� 'p3'.
	void AddPnt2(Vec3db &p3,Vec3db &n3,ms1D<int> &b, int &ib, int &E_n, int &P_n, int &Pn1, int &Pn2, int &s, int &lsb);	// �������� ������ ������ �� 'E_n' �'En'.
	void AddPnt3(Vec3db &p3,Vec3db &n3,ms1D<int> &b, int &ib, int &En_, int &Pn_, int &Pn1, int &Pn2, int &s);	// �������� ������ ������ �� 'En_' �'En'.
	void AddPnt4(Vec3db &p3,Vec3db &n3,ms1D<int> &b, int &ib, int &P_ , int &Pn1, int &Pn2, int &s  , int &lsb);	// ������ (�����) ��� ���� ������
	void AddPnt7(int &ib,int &Pn1,int &Pn2, int &Pn_,int &E_n, int &En , int &En_, int &s  , int &lsb);	// ������� ��� ������� �� ������� ����.
	void AddPnt9(Vec3db &p3,Vec3db &n3,ms1D<int> &b, int &ib, int &P_n, int &Pn1, int &Pn2, int &E_n, int &lsb); // �������� �� �������, �� ������� ���������
	void AddPnt10(Vec3db&p3,Vec3db &n3,ms1D<int> &b, int &ib, int &Pn1, int &Pn2, int &Pn_, int &En_, int &lsb); // �������� �� �������, �� ������� ���������
	void RmvBnd(int &s);	// ���� ����� ����������'s'.
	void RmvPnt(int &Pn);	// ���� ��������'Pn' � ���� ������
	void RmvEdg(int &En,ms1D<int> &b);	// ���� ��������'En' � ���� ������

	void AddPntCbs(Vec3db &p_in,const int &n_pnt); // ��� ����� ��� �� ����� ������������������� ���� �����

	void TrInit();  // ������ ���- ����� ����������.
	void TrInit(int n_srf);  // ������ ���- ����� ����������.
	void Build ();		// ���� ��������� �� ����� �����������
	//void Jiggle(int n, int N0, int N1);	// �������

	void FragmPntCorl();
	void FragmPntClear();

	
	double TrSize(Vec3db &p);	// ��� ����� ��������������

	void JuggleMesh(int iJ=1, int N0=0, int N1=0);// ������� iJ - ����� ���.  ����� � ������ ���� N0 � N1

	void RefineMesh();	// "двоичное" улучшение сетки триангуляции. Каждое ребро разделяется попалам, треулоьник - соответсвенно на 4 треугольника. Количество узлов возрастает в 4 раза.

	void TagssView();	// сценарий построения поверхности для целей просмотра, без дополнительных вычислений

	// ��� ����� �����������

	inline void DefCubNmb(Vec3db &p);	// ����� ����������� ���'p'

	void SetC_At(int &infs);	// ����� �������������� �������
	void SetNC_At();			// ����� ��������� �����������������

	void SetAtCmx(int &infs);	// ����� ���� mx_c � csf_c � ���� �����������infs

	int DefNearAt(Vec3db &p);	// ����� ������������ ���'p' (�� � ������ 'ii')
	int DefExpdAt(Vec3db &p);	// ����� ������������ ���'p' (������ � ��������� ���)
	int GlobDefAt(Vec3db &p);	// ����� ������������ ���'p' (����� �������)

	// --------
	int Pnt2Atom();
	int Pnt2Tws1();
	int Pnt2Trs1();
	int Pnt2Tws2();
	int Pnt2Trs2();
	int Pnt2ScTw();
	int Pnt2ScTr();
	int Pnt2ScSt();
	int Pnt2Srf1();
	int Pnt2Srf2();
	int Pnt2Surf();
	int Pnt2Surf(Vec3db &p1,Vec3db &p2,Vec3db &n2);
	int Pnt2Surf(Vec3db &p1,Vec3db &p2,Vec3db &n2, Vec3int &t);
	// --------

	bool Pnt2Surf_(Vec3db &p_in,Vec3db &n_in,Vec3db &p_out,Vec3db &n_out,Vec3int &type);	// ��� ���� ������ ���� �����.

	bool Pnt2Surf(Vec3db &p_in,Vec3db &n_in,Vec3db &p_out,Vec3db &n_out,Vec3int &type);	// ��� ���� ������ ���� �����. 
	bool Pnt2PrRl(Vec3db &p_in,Vec3db &n_in,Vec3db &p_out,Vec3db &n_out,Vec3int &type);	// ��� ���� ������ ���� ����� ��������� 
	bool Pnt2PrRl_(Vec3db &p_in,Vec3db &n_in,Vec3db &p_out,Vec3db &n_out,Vec3int &type);	// ��� ���� ������ ���� ����� ��������� 

	bool Pnt2Atom(Vec3db &p_in, Vec3db &p_out, Vec3db &nrm, double &sq_dst, int &infs, int &n_At);	// ���� ���'p_in' � �� 'n_At' �'sq_dst' ��� ������ ���������

	bool Pnt2AtNm(Vec3db &p_in,Vec3db &n_in,Vec3db &p_out,Vec3db &n_out,Vec3int &type);	// ��� ���� ������ ���� ����� ��������� 
	bool Pnt2TrNm(Vec3db &p_in,Vec3db &n_in,Vec3db &p_out,Vec3db &n_out,Vec3int &type);	// ��� ���� ������ ���� ����� ��������� 

	bool Pnt2Tris(Vec3db &p_in, double &sq_dst, int &n_Tr);	// ���� ���'p_in' � �. ���(��� 'n_Tr' �'sq_dst' ��� ������ �������� �. ���
	bool Pnt2Twos(Vec3db &p_in, double &sq_dst, int &n_Tw);	// ���� ���� ��������� ��'n_Tw' �'sq_dst' ��� ������ �������� ��

	bool Pnt2ScTr(Vec3db &p_in, double &sq_dst, int & icg, int &n_Tt);	// ���� ���� ��������� �. �����. ����'n_Tw' �'sq_dst' ��� ������ �������� �. ���
	bool Pnt2ScSt(Vec3db &p_in, double &sq_dst, int & icg, int &n_Tt);	// ���� ���� ��������� �� �����. ����'n_St' �'sq_dst' ��� ������ �������� �� ���


	// �����������
	void DoAtomClr();	// ������ ��� ���.
	// ��� ����vrml - �� (������������
	void dat2wrl(ms1D<double> &D);

	void points2vrml(int &i);	// ����vrml ��� ������� � �� �����'i'
	void points2vrml(int &i,int &ip0,int &ip1,int &ip2,int &ip4, Vec3db &p5, Vec3db &p3);	// ����vrml ��� ������� � �� �����'i'
	void points2vrml(int &ip0,int &ip1,int &ip2,int &ip4,Vec3db &p3);	// ����vrml ��� ������� � �� �����'i'

	//------------
	double CavDatFile(ms1D<Vec3db> &pnt, ms1D<Vec3db> &nrm, ms1Ddb &sqr);


	void Ret2InitBas();	// ������������
	void Ret2InitBas(ms1DVec3db &pnt, ms1DVec3db &nrm);	// ������������
	void RetSrf2InitBas();	// ������������

	// ��� ��� ��������������
	void CreateTess(ms1DVec3db &pnt, ms1DVec3db &nrm, ms1D<Vec3int> &tp, ms1Ddb &sqr); // ���� ���� ����������.
	void SetSrfArea(); // определение площади поверхностных элементов
	void SetTriArea(); // определение площадей треуголников триангуляции.
	void SetPntArea(); // определение площади поверхностных элементов (метод отличный от SetSrfArea() )

	double GetArea();	// полная площадь SES  поверхности

	void TplgStruct();	// ������������� �� ���������������������� ���� ������
	void HLTplgBndr();	// �����"����� ��� ��� ������ �������������

	void ReProecMsh(ms1DVec3db &pnt, ms1DVec3db &nrm, ms1D<Vec3int> &tp, ms1Ddb &sqr, Vec3db &Crd, double &Rpr,ms1Dint &CnfPnt,ms1Dint &NCnfPnt,ms1DVec3db &p, ms1DVec3db &n, ms1Ddb &sq); // ���������������������� ���� ������ 'Crd' �����'Rpr'
	void ReProecMsh(); // progon precedury proecirovanija dlja vseh tochek provyerhnosti

	void SetProbePr(ms1Dint &CnfPnt,ms1DVec3db &p, ms1DVec3db &n); // ���� ������������������� ���(����� - ����� � ���������)

	void S_GB_Radii(ms1DVec3db &pnt, ms1DVec3db &nrm, ms1Ddb &sqr,ms1Ddb &AG); // ����� ��������� (� ������ ������
	void S_GB_Radii(ms1DVec3db &pnt, ms1DVec3db &nrm, ms1Ddb &sqr,ms1Ddb &AtBrnRd,ms1Ddb &AG); // ����� ��������� (� ������ ������
	void S_GB_Radii(ms1DVec3db &pnt, ms1DVec3db &nrm, ms1Ddb &sqr,ms1Ddb &AtBrnRd,ms1Ddb &AG,Vec3db &Crd, double &Rpr,double &Rbr); // ����� ��������� (� ����� ������
	void S_GB_Radii(ms1DVec3db &pnt, ms1DVec3db &nrm, ms1Ddb &sqr,ms1D<ms1Ddb> &AtBrnRd,ms1Ddb &AG,ms1DVec3db &Crd, ms1Ddb &Rpr,ms1Ddb &Rbr); // ����� ��������� (� ����� ������


	void SetTwosDiff();	// ����������������� �������� � ����� ��������(��).
	void SetTrisDiff();	// ����������������� �������� � ����� �. ���
	void SetScStDiff();	// ����������������� �� ���
	void SetScTrDiff();	// ����������������� �. �����. ����
	void SetScTwDiff();	// ����������������� ����������. ����

	void SetPntDiff();	// ����������������� �������� � ���������

	void SetSGBDiff();	// ��������� s_gb �������

	void SetConfig(configpar &ConfPr);	//

	void my_exit(int exitcode);
};


#endif
