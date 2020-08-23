#ifndef DATATYPES_H
#define DATATYPES_H



#include <QMainWindow>

#include "linalg.h"
//#include "graph.h

#define UNDEFINED 0
#define AMINOACID 1
#define PROTEINE  2
#define LIGAND    3

class atom_node;
class protein_node;

class AminoAcid
{
public:
	//vecT<Atom *> Atoms;
	vecT<int > Atoms_id; // ��������� ������ ���������� ������������
	vecT<char> amin_ch; // ��������� ����������� ������������
	int id;	// ����� ������������ � ������� ���������� ����

	AminoAcid &	operator = (const AminoAcid &a) {Atoms_id	= a.Atoms_id; amin_ch	= a.amin_ch; id	= a.id; return *this;}
};

/*
typedef AminoAcid * p_AminoAcid;

class ChAminPtr
{
public :
	atom_node * p_atm;	// ��������� �� ����-���� � �������-���������
	//p_AminoAcid ptr_amin; // ��������� �� ����������� � ������� ������ ���� - ��� ����������� ����������.
	int id_at;	// ��������� ����� ����� � ������� ������������
	int id_ch;	// ����� ���� � ������� ������ ������������ ptr_amin; ���� � ������� �������� ��������
	ChAminPtr(){ id_ch = -1;p_atm = 0x0;}
	ChAminPtr(ChAminPtr &r){ id_ch = r.id_ch; id_at = r.id_at; p_atm = r.p_atm;}
	inline ChAminPtr & operator = (const ChAminPtr &r){id_ch = r.id_ch; id_at = r.id_at;	p_atm = r.p_atm; return *this;}
};
*/

class AtomData
{
public:
	atom_node* amin;	// ������ � ��������� � �������� � ����� ������ ����������� ���������.
	double	q;			// �����
	int		id_mmff;	// ��� MMFF 
	AtomData(){q = 0; id_mmff=-1; amin =0x0;}
	AtomData(AtomData &r) {q=r.q;id_mmff=r.id_mmff; amin=r.amin;}
	inline AtomData & operator = (const AtomData &r){q	= r.q; id_mmff=r.id_mmff; amin=r.amin; return *this;}
};

class p_AD
{
public:
	AtomData * dat;
	p_AD(){dat = 0x0;}
	inline void initdat()
	{
		dat = new AtomData;
	}
	inline void setq(double &q_){if (dat== 0x0) {initdat();} dat->q = q_;}
	inline void qsetq(double &q_){dat->q = q_;}
	inline void setid(int id_){if (dat== 0x0) {initdat();} dat->id_mmff = id_;}
	inline void qsetid(int id_){dat->id_mmff = id_;}
	inline p_AD(p_AD &r);//{dat = r.dat;}//{if(r.dat!=0x0){ if (dat== 0x0) {initdat();}; *dat = *r.dat;} else{if(dat!=0x0){delete dat;} } }
	~p_AD(){if(dat!=0x0){delete dat;dat = 0x0;}}
	inline p_AD & operator = (const p_AD &r);//{ dat = r.dat;	return *this;}//{/*if(r.dat!=0x0){if (dat== 0x0){	initdat();}*dat = *r.dat;} else{	if(dat!=0x0){delete dat;}}*/ dat = r.dat;	return *this;}
};

//class vecT;

class Atom // �������� �����
{
public:
	vec3db	 r;		// ���������� �����
//	int id_MndTbl;	// ����� � ������� ����������
	int id_Tpz;		// ����� ���� �������� ����� � ������������� ������� ������������� (� ������� id_TpzTbl)
	int id_Tot;		// ����� �������� ����� � ����� ������� ������
	p_AD dat;	// �������������� ������ ��� �����.
//	int id_Tot;		// ����� 
	Atom();
	Atom(const Atom &ra);
	Atom(vec3db r_in,int id_in);

	inline Atom & operator = (const Atom &rm) {r=rm.r;id_Tpz=rm.id_Tpz;id_Tot=rm.id_Tot; dat=rm.dat;  return *this;}
};

class Bond // �������� �����
{
public:
	int oder;			// ������� �����
	vec2int id_Atoms;	// ������ ������ �� ������ ������� �� ������ �����
	Bond();
	Bond(int in_od,int in_at1, int in_at2);

	inline Bond & operator = (const Bond & r){oder=r.oder;id_Atoms.x[0]=r.id_Atoms.x[0];id_Atoms.x[1]=r.id_Atoms.x[1]; return *this; }
};

class MolSurf;
class SmplTpzlTable;

class ConnectedAtoms // ����� ��������� ������
{
public:
	vecT<char> Name;	// �������� ��������
	vecT<Atom> Atoms;	// ����� ��������
	vecT<Bond> Bonds;	// ����� ��������
	SparseMatr<int> Connect; // ������� ��������� ��������
	int id_TpzTbl;	// ����� ������� �������������

	MolSurf *surf;	//��������� �� ����������� ��������������� � ���������

	ConnectedAtoms(){surf	= 0x0; id_TpzTbl	= -1;}	// ����� ������� �������������
	ConnectedAtoms(int Na);	// ������������� ��� �������� �� N ������

	ConnectedAtoms(ConnectedAtoms  &r	);

	~ConnectedAtoms();//{}


	void InitSurface(SmplTpzlTable &Tbl);	// ������������� ������ ��� ���������� ����������� ���������� �����������
};



class Molecule : public ConnectedAtoms //, public Protein  // �������� �������� - ������ ��������� ������
{
public:
	/*vecT<char> Name;	// �������� ��������
	vecT<Atom> Atoms;	// ����� ��������
	vecT<Bond> Bonds;	// ����� ��������
	SparseMatr<int> Connect; // ������� ��������� ��������
	int id_TpzTbl;	// ����� ������� �������������

	Molecule(){	id_TpzTbl	= -1;}	// ����� ������� �������������
	Molecule(int Na);	// ������������� ��� �������� �� N ������

	Molecule(Molecule  &r);

	~Molecule();//{}*/

	Molecule(){	id_TpzTbl	= -1;drawtype=0;colortype=0; mol_type = UNDEFINED;/* f_ptr_swp = 0x0;f_ptr_upd = 0x0;/**/}	// ����� ������� �������������
	Molecule(int Na);	// ������������� ��� �������� �� N ������

	Molecule(Molecule  &r);

	~Molecule();//{}*/

	void ReInit(int Na); // ������������� ��� �������� �� Na ������

	void ReSize(int Na); // ��������� �������� ��������� �� Na ������ � ����������� ������

	void setGCM(const vec3db & r0); // ���������� �������������� ����� �������� � �������� r0

	vec3db getGCM();	// ������� �������� ��������� ��������������� ������ ��������.
	double getMSz();	// ������� ������ ��������


	int AddBond(int oder,int in1,int in2);	
	void AtomIns(int M_ID); // �������� ���� � ������� 'M_ID' �� ������� ����������
	void AtomDel(int id);	// ������� ���� � ������� id
	void BondDel(int id);	// ������� ����� � ������� id
	void SubMol(vecT<int> &id,int at,int bn); // �������� ����� ������� �� ���� ������� �� ����� at � ���������� ����� bn
	void AtNieb(vecT<int> &id_nieb,int at); // ���������� ������ id_nieb �������� �� ������ ������ � ������ id
	void SetLocBas1(int at0,int at,int bn); // ��������� ���������� ������ 1 ����. (��� ��������� ���. ����)
	void GeoModify1(double fi);
	void ClearAll();// �������� ��� ���� �������
	void UniMol(Molecule  *r);//,vecT<int> &id1);	// ��������� ������� �������� � ������ � ������� ��������
	void SepMol(vecT<Molecule>  &r,vecT< vecT<int> > &ids); // ����������� ��������  � ����������� � �������� �� ids
	void SepMol(Molecule *r, int &Nmx); // ����������� ��������  � ����������� � �������� �� ids
	bool ComTest(int &id_at1,int id_at2); // ���� �� �������������� ����������� ������� ���� ������.

	void GetSubMol(int &id_at1,int &id_at2, vecT<int> &id_ats); // ������ �������� �������, �� ���� ������� �� ����� id_at1-id_at2, �� ������� id_at2

	void SepMolInd(vecT<vecT<int> >&ids);// ����������� ������� ������ ������� �������

	void endswap(int id);	// �������� ������� ���� � ������� � ��������� ������ � �������  Atoms

	void AtomSwap(const int &id1,  const int &id2);// �������� ������� ��� ����� � ������� ������

	Molecule & operator = ( Molecule &r);

	void setAtoms2Amin();	// ��������� ����������� ����� ������������ � ������� �� ������. ��� ���������.

	//private:
	vecT<bool> b_at; // ����� ������������ ������
	vec3db lx,ly,lz;	// ��������� ����� ��� ��������� ���������
	vec3db pc; // ������ �������� � ������ ��������� ������
	vecT<int> id_mov;	// ������ ��������� ������

	vecT<int> ids;

	int drawtype;	// ������������� ���� ������������ ��������. 0 - ������ + ��������, 1 - ������� ...
	int colortype;	// ���� ��������� ������� ��� ��������� ������ ��������

	//void (*f_ptr_swp)(const int &,  const int &);   // ��������� �� ������� - ������������ ����� ������� ������
	//void (*f_ptr_upd)(void *);	// ������������ ��������� ���� ������� ������

	int mol_type;	// ��� ��������. 0- ���������������� ��������, 1 - ������������, 2 - �������, 3 - ������

//	vecT< vecT< AminoAcid > >	chains;// �������������� ����� - ������� � ����������� �� ������������
//	vecT<char>	ch_Leter;	// ����� �����

	protein_node *p_prt;

	//enum amino_names {ALA,ARG,ASN,ASP,CYS,GLN,GLU,GLY,HIS,ILE,LEU,LYS,MET,PHE,PRO,SER,THR,TRP,TYR,VAL}; // �������� �����������

//	Molecule(vecT<Atom> &in_Atoms,)

};


class base_node // ����� �������� ���� ����������� ������
{
public:
	//void *ptr;
	base_node * parent;
	vecT<base_node *> childs;
	int id;	// ����� ��������� ���� � ������������ ������.
	base_node(){ parent = 0x0; id = -1; }
	void addChild(base_node *chld); // �������� ���� � �����
	void addChild(base_node *chld, int ii); // �������� ��������� ii
	base_node * getparent(){return parent;}
    base_node * getChild(int ii);
	void delChild(); // ������� ��������� �������� ����;
	void delChild(int ii); // ������� �������� ���� �� ������� ii;
	//void swap(int ii, int jj); // ���� �������� ����� � �������� ii � jj;
	void swap(int ii); // ���� �������� ����� � �������� ii � ����������
	void updateparents();	// �������� ��������� parent � �������� �����
	base_node( base_node &bs);	// ����������� �����
	virtual ~base_node();
	//node(node* prnt = 0x0){}
	//void clear();
	base_node & operator = ( base_node & bs);
};

class amino_node;
class chain_node;
class protein_node;


class protein_node : public base_node
{
public:
	vecT<char> protname;
	int id_ml;  // ����� �������� ������� �������� �������
	protein_node(){}
//	void addChild(chain_node *chld);
	void setProt(vecT< vecT< AminoAcid > >	&chains, vecT<char>	&ch_Leter,Molecule &M); // ������������� ��������� ������ �� ������ chains � ch_Leter
	//void delAtomNode(atom_node *p_atm);
	atom_node * addAtomNode(int id_ch,int id_am,int id_at);
	chain_node * getChild(int ii) const;
	protein_node( protein_node &bs);	// ����������� �����
	~protein_node(){id_ml =-1;}
	protein_node & operator = ( protein_node & bs);
//	void delChild(); // ������� ��������� �������� ����;
//	void delChild(int ii);
	//void clearAll();	// �������� ��� ���������
};

class chain_node : public base_node	// ����� ����-���� ����
{
public :
	char ch;	// ��������� ������������� ����.
	chain_node(){ch = '\0';}
//	void addChild(amino_node *chld);
	protein_node * getparent(){return static_cast<protein_node *> (parent);}
	amino_node * getChild(int ii) const;
	chain_node( chain_node &bs);	// ����������� �����
	~chain_node(){}
	chain_node & operator = ( chain_node & bs);
//	void delChild(); // ������� ��������� �������� ����;
//	void delChild(int ii);
};

class amino_node : public base_node	// ����� ����-���� ����
{
public :
	vecT<char> name; // �������� ������������
	int id_ch;		// ����� ������������ � ���������� ����. (�� ����  ����� ���� � ������� ���������!)
	amino_node(){id_ch = -1;}
//	void addChild(atom_node *chld);
	chain_node * getparent(){return static_cast<chain_node *> (parent);}
	atom_node * getChild(int ii) const;
	amino_node( amino_node &bs);
	~amino_node(){}
	amino_node & operator = (amino_node & bs);
//	void delChild(); // ������� ��������� �������� ����;
//	void delChild(int ii);
};

class atom_node : public base_node
{
public :
	Atom * atom;	// ��������� �� ����.
	vecT<char> name; // ��� ����� � ������������ 
	atom_node(){atom = 0x0;}
	amino_node * getparent(){return static_cast<amino_node *> (parent);}
//	void addChild(base_node *chld ){}
	base_node * getChild(int ii){return 0x0;}
	atom_node( atom_node &bs);
	//virtual base_node * getChild(int ii) {return 0x0;}
	~atom_node();
	atom_node & operator = ( atom_node &bs);
};






class base_tree // ����� �������� ������
{
public :
	base_node * top; // ��������� �� ������ ������.
	base_tree(){top = 0x0;}
};

class Protein  : public Molecule
{
public:
	//vecT< vecT< AminoAcid > >	chains;// �������������� ����� - ������� � ����������� �� ������������
	//vecT<char>	ch_Leter;	// ����� �����
// ������������� �������� ��������: ����� ����� - chains. ������ ���� ������������ ����� ������ ������� ������
	// ������������ ������������
	//void AtomSwap(const int &id1,  const int &id2);// �������� ������� ��� ����� � ������� ������
};
/**/
class SmplTpzlTableLine	// ������ ������� ������� ���������
{
public:
	int id_MndTbl;	// ����� � ������� ����������
	vecT<char> Name;// �������� �����;
	vec2T<char> Ch; // ���������� ������������� �������� � ������� ����������
	double mass;	// ����� ��������� ������� [a.e.]
	double vdwrad;	// ���-���-���������� ����� ����� [A] (��������)
	double emprad;	// ���������� ����� ����� [A] (��������)
	double calrad;	// ����������� ����� ����� [A] (��������)
	double cvlrad;	// ����������� ������ [A] (��������)
	double metrad;	// ������ ��������������� ������� [A] (��������)
	vecT<int> oxd;	// ��������� ������� ���������
	vec3int color;	// ���� ����� (rgb - �������, �������� ��� ������� ������: 0-255)
};

class SmplTpzlTable	// ������� ������� ���������
{
public:
	vecT<SmplTpzlTableLine> Lines;
	double	brad;   // ������ �������� �����
	double	krad;	// ����������� ������� ����� (krad*___rad - �������� ������� ��������� ���� )
	int indret(vec2T<char> &ch);
	SmplTpzlTable();
};

/*class VizTable	// ������� ������
{
	vecT<vec3int> colors;	// ���� ����� (rgb - �������, �������� ��� ������� ������: 0-255)
	double	brad;   // ������ �������� �����
	double	krad;	// ����������� ������� ����� (krad*___rad - �������� ������� ��������� ���� )

};*/

/*namespace glb
{
	SmplTpzlTable TableZR;
}/**/

//#include <memory.h>
//template <class T> class QVector;
/*
template <class T>
class Node	// ����� Node - ��������� ���� � �����. ����� � ����� �����
{
public:
	T *NodeObject;	// ��������� �� ������ ��������� � �����
	int self_id;	// ����� �������� ����
	QVector<int> edgs_id;	// ������ ���� ��������� �� ����

	Node(){NodeObject	= 0x0;self_id	= -1;}
	//Node(Node &r);
	void AddObject(T &nodeObject){NodeObject	= &nodeObject;}
};

template <class T>
class Edge	// ����� Edge - ��������� ����� �����. ����� � ����� ��������
{
public:
	T *EdgeObject;	// ��������� �� ������ ��������� � ������
	int self_id;	// ����� �������� �����
	vec2int  nods_id;	// ������ ����� �� ������ �����

	Edge();
	Edge(Edge &r);
};

template<class N,class E>
class Graph	// ����� Graph - ��������� ����. (������ ��������� ������ �����)
{
public:
	QVector<Node<N> > Nodes;	// ������ ����� �����
	QVector<Edge<E> > Edges;	// ������ ���� �����
	Graph(){}	// ����������� �� ��������� - ������ ����
	void AddNode(Node<N> & node); // �������� ����������� ����
	void InitNodes(int k = 10);	// ������������� 'k' ����������� �����, ��� �������� �� ������ ����
	//QVector<int> AddNode(Node<N> & new_node,QVector<int> & old_nodes);	// �������� ���� � ��������� �����, ���������� ������ �������������� �����, ���� ������� ������� � old_nodes
	//AddEdge(Egde<E> & edge);
};


template <class T>
class SparseMatrix	// ����� SparseMatrix - ��������� ���������� ������� 
{
	int M,N;		// M - ����� ������, ����� ��������
	QVector<T> elements;	// ��������� �������� �������
	QVector<Qvector<int> > id;		// ������� ������ ��������� � ��������� ������ ���� ������ j �����,�� id[j].empty()=true
	//Qvector<int> rows;		// ����� ��������� ������

	SparseMatrix(){M = N = 0;}
	SparseMatrix(const int n,const int m);
	SparseMatrix(SparseMatrix &r);
	SparseMatrix(const int n,const int m, /*const Qvector<int> rows_in,* /const QVector<QVector<int> > id_in,const QVector<T> elements_in);
	T & getElement(const int m,const int n,const T &r);
	T & setElement(const int m,const int n,T &r);
	SparseMatrix & getSubMatrix(const int m_beg,const int m_end,const int n_beg,const int n_end,const  SparseMatrix &r);
	SparseMatrix & setSubMatrix(const int m_beg,const int m_end,const int n_beg,const int n_end,SparseMatrix &r);
}/**/

	//void my_gcvt(double x,int n, vecT<char> &s);	// ������������� ����� � ������


#endif