#ifndef RDWRFLS_H
#define RDWRFLS_H
// ������ � ������ ������ �� ������

#include "linalg.h"
#include "datatypes.h"

class QString;
class Surface;

//int hinparser(vecT<Molecule> &Mls);	// ������ ������ �� hin-����� � ���������� ������ � ���������
//template <class T>
class WorkFrame
{
public:
	SmplTpzlTable	TableZR;	// ������� ����� ������ � �� ����������
	vecT<Molecule*>	Mls;
	vecT<Protein*>  Prot;

	//vecT<vec2int> id_select;	// ������ ��������� ������ � ���������

	vecT<Surface*>		Srfcs;	// �����������

	WorkFrame(void);
	~WorkFrame(void);

	void MolSwap(const int &id1,const int &id2);

	void InitMolSurf(ConnectedAtoms *mol);	// ������������� ����������� ��������� � ��������� 
	void DelMolSurf(ConnectedAtoms *mol);// �������� ����������� ��� �������� mol
	void DelMolSurf(Surface *srf);// �������� ����������� ��� �������� mol
	void DelMolSurf();

	int hinparser(vecT<char> &fname);	// ������ ������ �� hin-����� � ���������� ������ � ���������
	int mrkparser(vecT<char> &fname);	// ������ ������ �� mrk-����� � ���������� ������ � ���������
	int pdbparser0(vecT<char> &fname);	// ������ ������ �� pbd-����� � ���������� ������ � ��������� (����� ������ �������)
	int pdbparser1(vecT<char> &fname);	// ������ ������ �� pbd-����� 
	int molparser(vecT<char> &fname);	// ������ ������ �� mol-�����
	int xyzparser(vecT<char> &fname);	// ������ ������ �� xyz-�����
	int checkxyztype(vecT <vecT <char> > &txtdata); // ����������� ���� xyz - �����. ������������ �����-��� ����. ����������� 0 �������� ������������� �� ������ �� �����.
	// ������� ��������� ����� xyz - ������
	int xyzpars_1(vecT <vecT <char> > &txtdata,Molecule *cMlc);
	int xyzpars_2(vecT <vecT <char> > &txtdata,Molecule *cMlc);
	int xyzpars_3(vecT <vecT <char> > &txtdata,Molecule *cMlc);
	int xyzpars_4(vecT <vecT <char> > &txtdata,Molecule *cMlc);
	int xyzpars_5(vecT <vecT <char> > &txtdata,Molecule *cMlc);
	int xyzpars_6(vecT <vecT <char> > &txtdata,Molecule *cMlc);
	int xyzpars_7(vecT <vecT <char> > &txtdata,Molecule *cMlc);
	//--
	void setdistanceconnect(Molecule * cMlc);
	bool readFile(const QString &fileName);
	void hinscript(int id_ml,vecT<vecT <char> > &hinstr);	// ��������� ����� ����� � hin- ��������� �������� � ������� 'id-ml'
	void hinscript(vecT<vecT <char> > &hinstr);	// ��������� ����� ����� � hin - ��������� �������
	void mrkscript(vecT<vecT <char> > &mrkstr); // ��������� ����� ����� � mrk - ��������� ��������
	void mrkscript(int id_ml,vecT<vecT <char> > &mrkstr); // ��������� ����� ����� � mrk - ��������� �������� � ������� 'id-ml'
	void pdbscript(vecT<vecT <char> > &pdbstr); // ��������� ����� ����� � pdb - ��������� ��������
	void xyzscript(int id_ml, vecT<vecT <char> > &xyzstr);
	void xyzscript(vecT<vecT <char> > &xyzstr);
	bool writeFile(const QString &fileName,int id_ml);
	bool writeFile(const QString &fileName);


};

#endif