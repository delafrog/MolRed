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
	vecT<int > Atoms_id; // указатели атомов образующих аминокислоту
	vecT<char> amin_ch; // буквенное обозначение аминокислоты
	int id;	// номер аминокислоты в составе полимерной цепи

	AminoAcid &	operator = (const AminoAcid &a) {Atoms_id	= a.Atoms_id; amin_ch	= a.amin_ch; id	= a.id; return *this;}
};

/*
typedef AminoAcid * p_AminoAcid;

class ChAminPtr
{
public :
	atom_node * p_atm;	// указатель на атом-узел в протеин-структуре
	//p_AminoAcid ptr_amin; // указатель на аминокслоту в которую входит атом - для протеиновых соединений.
	int id_at;	// локальный номер атома в составе аминокислоты
	int id_ch;	// номер цепи в которую входит аминокислота ptr_amin; цепи в составе исходной молекулы
	ChAminPtr(){ id_ch = -1;p_atm = 0x0;}
	ChAminPtr(ChAminPtr &r){ id_ch = r.id_ch; id_at = r.id_at; p_atm = r.p_atm;}
	inline ChAminPtr & operator = (const ChAminPtr &r){id_ch = r.id_ch; id_at = r.id_at;	p_atm = r.p_atm; return *this;}
};
*/

class AtomData
{
public:
	atom_node* amin;	// данные о вхождении в молекулу с точки зрения протеиновой структуры.
	double	q;			// заряд
	int		id_mmff;	// тип MMFF 
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

class Atom // описание атома
{
public:
	vec3db	 r;		// координаты атома
//	int id_MndTbl;	// номер в таблице Менделеева
	int id_Tpz;		// номер типа текущего атома в установленной таблице типизирования (с номером id_TpzTbl)
	int id_Tot;		// номер текущего атома в общем массиве атомов
	p_AD dat;	// дополнительные данные для атома.
//	int id_Tot;		// номер 
	Atom();
	Atom(const Atom &ra);
	Atom(vec3db r_in,int id_in);

	inline Atom & operator = (const Atom &rm) {r=rm.r;id_Tpz=rm.id_Tpz;id_Tot=rm.id_Tot; dat=rm.dat;  return *this;}
};

class Bond // описание связи
{
public:
	int oder;			// порядок связи
	vec2int id_Atoms;	// номера атомов из общего массива на концах связи
	Bond();
	Bond(int in_od,int in_at1, int in_at2);

	inline Bond & operator = (const Bond & r){oder=r.oder;id_Atoms.x[0]=r.id_Atoms.x[0];id_Atoms.x[1]=r.id_Atoms.x[1]; return *this; }
};

class MolSurf;
class SmplTpzlTable;

class ConnectedAtoms // набор связанных атомов
{
public:
	vecT<char> Name;	// название молекулы
	vecT<Atom> Atoms;	// атомы молекулы
	vecT<Bond> Bonds;	// связи молекулы
	SparseMatr<int> Connect; // матрица связности молекулы
	int id_TpzTbl;	// номер таблицы типизирования

	MolSurf *surf;	//указатель на поверхность ассоциированную с молекулой

	ConnectedAtoms(){surf	= 0x0; id_TpzTbl	= -1;}	// номер таблицы типизирования
	ConnectedAtoms(int Na);	// инициализация для молекулы из N атомов

	ConnectedAtoms(ConnectedAtoms  &r	);

	~ConnectedAtoms();//{}


	void InitSurface(SmplTpzlTable &Tbl);	// инициализация данных для дальнейшей возможности построения поверхности
};



class Molecule : public ConnectedAtoms //, public Protein  // описание молекулы - набора связанных атомов
{
public:
	/*vecT<char> Name;	// название молекулы
	vecT<Atom> Atoms;	// атомы молекулы
	vecT<Bond> Bonds;	// связи молекулы
	SparseMatr<int> Connect; // матрица связности молекулы
	int id_TpzTbl;	// номер таблицы типизирования

	Molecule(){	id_TpzTbl	= -1;}	// номер таблицы типизирования
	Molecule(int Na);	// инициализация для молекулы из N атомов

	Molecule(Molecule  &r);

	~Molecule();//{}*/

	Molecule(){	id_TpzTbl	= -1;drawtype=0;colortype=0; mol_type = UNDEFINED;/* f_ptr_swp = 0x0;f_ptr_upd = 0x0;/**/}	// номер таблицы типизирования
	Molecule(int Na);	// инициализация для молекулы из N атомов

	Molecule(Molecule  &r);

	~Molecule();//{}*/

	void ReInit(int Na); // инициализация для молекулы из Na атомов

	void ReSize(int Na); // изменение размеров молелкулы на Na атомов с сохранением данных

	void setGCM(const vec3db & r0); // установить геометрический центр молекулы в значение r0

	vec3db getGCM();	// вернуть значение координат геометрического центра молекулы.
	double getMSz();	// вернуть размер молекулы


	int AddBond(int oder,int in1,int in2);	
	void AtomIns(int M_ID); // добавить атом с номером 'M_ID' из таблицы менделеева
	void AtomDel(int id);	// удалить атом с номеров id
	void BondDel(int id);	// удалить связь с номером id
	void SubMol(vecT<int> &id,int at,int bn); // выделяет часть молеулы по одну сторону от атома at в напрвлении связи bn
	void AtNieb(vecT<int> &id_nieb,int at); // определяет номера id_nieb соседних по связям атомов с атомом id
	void SetLocBas1(int at0,int at,int bn); // установка лоакльного базиса 1 типа. (для изменения вал. угла)
	void GeoModify1(double fi);
	void ClearAll();// очистить все поля объекта
	void UniMol(Molecule  *r);//,vecT<int> &id1);	// объединть текущую молекулу с другой в текущей молекуле
	void SepMol(vecT<Molecule>  &r,vecT< vecT<int> > &ids); // разъеденить молекулу  в соответсвии с номерами из ids
	void SepMol(Molecule *r, int &Nmx); // разъеденить молекулу  в соответсвии с номерами из ids
	bool ComTest(int &id_at1,int id_at2); // тест на принадлежность односвязной области двух атомов.

	void GetSubMol(int &id_at1,int &id_at2, vecT<int> &id_ats); // выдать фрагмент молеклы, по одну сторону от связи id_at1-id_at2, со стороны id_at2

	void SepMolInd(vecT<vecT<int> >&ids);// определение номеров атомов связных связями

	void endswap(int id);	// поменять местами атом с номером с последним атомом в массиве  Atoms

	void AtomSwap(const int &id1,  const int &id2);// поменять местами два атома в массиве атомов

	Molecule & operator = ( Molecule &r);

	void setAtoms2Amin();	// установка соответсвия атома аминокислоте в которую он входит. Для протеинов.

	//private:
	vecT<bool> b_at; // метки обработанных атомов
	vec3db lx,ly,lz;	// локальный базис для изменения геометрии
	vec3db pc; // вектор смещения в начало лоального базиса
	vecT<int> id_mov;	// номера двигаемых атомов

	vecT<int> ids;

	int drawtype;	// идентификатор типа визуализации молекулы. 0 - шарики + цилиндры, 1 - решётка ...
	int colortype;	// шифр цветового решения для раскраски атомов молекулы

	//void (*f_ptr_swp)(const int &,  const int &);   // указатель на функцию - сингализация свопа номеров атомов
	//void (*f_ptr_upd)(void *);	// сигнализация пересчёта всех номеров атомов

	int mol_type;	// тип молекулы. 0- нетипизированная молекула, 1 - аминокислота, 2 - протеин, 3 - лиганд

//	vecT< vecT< AminoAcid > >	chains;// идентификаторы цепей - массивы с указателями на аминоксилоты
//	vecT<char>	ch_Leter;	// буквы цепей

	protein_node *p_prt;

	//enum amino_names {ALA,ARG,ASN,ASP,CYS,GLN,GLU,GLY,HIS,ILE,LEU,LYS,MET,PHE,PRO,SER,THR,TRP,TYR,VAL}; // названия аминокислот

//	Molecule(vecT<Atom> &in_Atoms,)

};


class base_node // класс базового узла абстактного дерева
{
public:
	//void *ptr;
	base_node * parent;
	vecT<base_node *> childs;
	int id;	// номер указалеля узла в родительском списке.
	base_node(){ parent = 0x0; id = -1; }
	void addChild(base_node *chld); // добавить узел в конец
	void addChild(base_node *chld, int ii); // добавить напозицию ii
	base_node * getparent(){return parent;}
    base_node * getChild(int ii);
	void delChild(); // удалить последний дочерний узел;
	void delChild(int ii); // удалить дочерний узел на позиции ii;
	//void swap(int ii, int jj); // своп дочерних узлов с номерами ii и jj;
	void swap(int ii); // своп дочерних узлов с номерами ii и последнего
	void updateparents();	// обновить указатель parent в дочерних узлах
	base_node( base_node &bs);	// конструктор копий
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
	int id_ml;  // номер молекулы которой является протеин
	protein_node(){}
//	void addChild(chain_node *chld);
	void setProt(vecT< vecT< AminoAcid > >	&chains, vecT<char>	&ch_Leter,Molecule &M); // генерирование структуры дерева по данным chains и ch_Leter
	//void delAtomNode(atom_node *p_atm);
	atom_node * addAtomNode(int id_ch,int id_am,int id_at);
	chain_node * getChild(int ii) const;
	protein_node( protein_node &bs);	// конструктор копий
	~protein_node(){id_ml =-1;}
	protein_node & operator = ( protein_node & bs);
//	void delChild(); // удалить последний дочерний узел;
//	void delChild(int ii);
	//void clearAll();	// очистить всю структуру
};

class chain_node : public base_node	// класс узла-типа цепь
{
public :
	char ch;	// буквенный идентификотор цепи.
	chain_node(){ch = '\0';}
//	void addChild(amino_node *chld);
	protein_node * getparent(){return static_cast<protein_node *> (parent);}
	amino_node * getChild(int ii) const;
	chain_node( chain_node &bs);	// конструктор копий
	~chain_node(){}
	chain_node & operator = ( chain_node & bs);
//	void delChild(); // удалить последний дочерний узел;
//	void delChild(int ii);
};

class amino_node : public base_node	// класс узла-типа цепь
{
public :
	vecT<char> name; // название аминокислоты
	int id_ch;		// номер аминокислоты в полимерной цепи. (не есть  номер узла в массиве роддителя!)
	amino_node(){id_ch = -1;}
//	void addChild(atom_node *chld);
	chain_node * getparent(){return static_cast<chain_node *> (parent);}
	atom_node * getChild(int ii) const;
	amino_node( amino_node &bs);
	~amino_node(){}
	amino_node & operator = (amino_node & bs);
//	void delChild(); // удалить последний дочерний узел;
//	void delChild(int ii);
};

class atom_node : public base_node
{
public :
	Atom * atom;	// указатель на атом.
	vecT<char> name; // имя атома в аминокислоте 
	atom_node(){atom = 0x0;}
	amino_node * getparent(){return static_cast<amino_node *> (parent);}
//	void addChild(base_node *chld ){}
	base_node * getChild(int ii){return 0x0;}
	atom_node( atom_node &bs);
	//virtual base_node * getChild(int ii) {return 0x0;}
	~atom_node();
	atom_node & operator = ( atom_node &bs);
};






class base_tree // класс базового дерева
{
public :
	base_node * top; // указатель на корень дерева.
	base_tree(){top = 0x0;}
};

class Protein  : public Molecule
{
public:
	//vecT< vecT< AminoAcid > >	chains;// идентификаторы цепей - массивы с указателями на аминоксилоты
	//vecT<char>	ch_Leter;	// буквы цепей
// представление белковой молекулы: набор цепей - chains. каждая цепь представляет собой массив номеров атомов
	// составляющих амонокислоту
	//void AtomSwap(const int &id1,  const int &id2);// поменять местами два атома в массиве атомов
};
/**/
class SmplTpzlTableLine	// строка простой таблицы типизации
{
public:
	int id_MndTbl;	// номер в таблице Менделеева
	vecT<char> Name;// название атома;
	vec2T<char> Ch; // символьное представление элемента в таблице Менделеева
	double mass;	// масса основного изотопа [a.e.]
	double vdwrad;	// ван-дер-ваальсовый радис атома [A] (ангстрем)
	double emprad;	// измеренный радис атома [A] (ангстрем)
	double calrad;	// вычисленный радис атома [A] (ангстрем)
	double cvlrad;	// ковалентный радиус [A] (ангстрем)
	double metrad;	// радиус кристаллической решётки [A] (ангстрем)
	vecT<int> oxd;	// возможные степени окисления
	vec3int color;	// цвет атома (rgb - палитра, значения для каждого канала: 0-255)
};

class SmplTpzlTable	// простая таблица типизации
{
public:
	vecT<SmplTpzlTableLine> Lines;
	double	brad;   // радиус цилинрда связи
	double	krad;	// коэффициент радиуса атома (krad*___rad - значение радиуса рисуемого шара )
	int indret(vec2T<char> &ch);
	SmplTpzlTable();
};

/*class VizTable	// таблица цветов
{
	vecT<vec3int> colors;	// цвет атома (rgb - палитра, значения для каждого канала: 0-255)
	double	brad;   // радиус цилинрда связи
	double	krad;	// коэффициент радиуса атома (krad*___rad - значение радиуса рисуемого шара )

};*/

/*namespace glb
{
	SmplTpzlTable TableZR;
}/**/

//#include <memory.h>
//template <class T> class QVector;
/*
template <class T>
class Node	// класс Node - описывает узел в графе. Знает о своих рёбрах
{
public:
	T *NodeObject;	// указатель на объект связанный с узлом
	int self_id;	// номер текущего узла
	QVector<int> edgs_id;	// номера рёбер исходящих из узла

	Node(){NodeObject	= 0x0;self_id	= -1;}
	//Node(Node &r);
	void AddObject(T &nodeObject){NodeObject	= &nodeObject;}
};

template <class T>
class Edge	// класс Edge - описывает ребро графа. Знает о своих вершинах
{
public:
	T *EdgeObject;	// указатель на объект связанный с ребром
	int self_id;	// номер текущего ребра
	vec2int  nods_id;	// номера узлов на концах ребра

	Edge();
	Edge(Edge &r);
};

template<class N,class E>
class Graph	// класс Graph - описывает граф. (только топология связей графа)
{
public:
	QVector<Node<N> > Nodes;	// массив узлов графа
	QVector<Edge<E> > Edges;	// массив рёбер графа
	Graph(){}	// конструктор по умолчанию - пустой граф
	void AddNode(Node<N> & node); // добавить незвязанный узел
	void InitNodes(int k = 10);	// инициализация 'k' несвязанных узлов, без указания на объект узла
	//QVector<int> AddNode(Node<N> & new_node,QVector<int> & old_nodes);	// добавить узел к указанным узлам, возвращает массив несуществующих узлов, если таковые указаны в old_nodes
	//AddEdge(Egde<E> & edge);
};


template <class T>
class SparseMatrix	// класс SparseMatrix - описывает разрежённую матрицу 
{
	int M,N;		// M - число сктрок, число столбцов
	QVector<T> elements;	// ненулевые элементы матрицы
	QVector<Qvector<int> > id;		// индексы первых элементов в очередной строке если строка j пуста,то id[j].empty()=true
	//Qvector<int> rows;		// номер очередной строки

	SparseMatrix(){M = N = 0;}
	SparseMatrix(const int n,const int m);
	SparseMatrix(SparseMatrix &r);
	SparseMatrix(const int n,const int m, /*const Qvector<int> rows_in,* /const QVector<QVector<int> > id_in,const QVector<T> elements_in);
	T & getElement(const int m,const int n,const T &r);
	T & setElement(const int m,const int n,T &r);
	SparseMatrix & getSubMatrix(const int m_beg,const int m_end,const int n_beg,const int n_end,const  SparseMatrix &r);
	SparseMatrix & setSubMatrix(const int m_beg,const int m_end,const int n_beg,const int n_end,SparseMatrix &r);
}/**/

	//void my_gcvt(double x,int n, vecT<char> &s);	// преобразовать число в строку


#endif