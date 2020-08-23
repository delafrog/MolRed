#ifndef DATATYPES_CPP
#define DATATYPES_CPP

//#include <fstream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "linalg.h"
//#include "linalg.cpp"
#include "datatypes.h"
#include "surface.h"


//___________________________________________________
p_AD::p_AD(p_AD &r)
{
	if(r.dat!=0x0)
	{
		if(dat==0x0) initdat();
		dat->q	= r.dat->q;
		dat->id_mmff	= r.dat->id_mmff;
	}else
	{
		if(dat!=0x0)
		{
			delete dat;
			dat	= 0x0;
		}
	}
}
//___________________________________________________
p_AD & p_AD::operator =(const p_AD &r)
{
	if(r.dat!=0x0)
	{
		if(dat==0x0) initdat();
		*dat	= *r.dat;
		//dat->q	= r.dat->q;
		//dat->id_mmff	= r.dat->id_mmff;
	}else
	{
		if(dat!=0x0)
		{
			delete dat;
			dat	= 0x0;
		}
	}
	return *this;
}

//___________________________________________________
Atom::Atom()
{
	r			= 0.0;
//	id_MndTbl = 0;
//	id_TpzTbl	= -1;	// номер таблицы типизирования
	id_Tpz		= -1;		// номер типа текущего атома в установленной таблице типизирования (с номером id_TpzTbl)
	id_Tot		= -1;		
};
//___________________________________________________
Atom::Atom(vec3db r_in,int id_in)
{
	r	= r_in;
//	id_TpzTbl	= -1;		// номер таблицы типизирования
	id_Tpz		= -1;		// номер типа текущего атома в установленной таблице типизирования (с номером id_TpzTbl)
	id_Tot		= id_in;	
};
Atom::Atom(const Atom &ra)
{
	r	= ra.r;
	id_Tot	= ra.id_Tot;
	id_Tpz	= ra.id_Tpz;
	dat		= ra.dat;
}
//___________________________________________________
//___________________________________________________
Bond::Bond()
{
	oder	= -1;
	id_Atoms.x[0]	= -1;
	id_Atoms.x[1]	= -1;
}
//___________________________________________________
Bond::Bond(int in_od,int in_at1, int in_at2)
{
	oder	= in_od;
	id_Atoms.x[0]	= in_at1;
	id_Atoms.x[1]	= in_at2;

}


//___________________________________________________
ConnectedAtoms::ConnectedAtoms(int Na)	// инициализация для молекулы из N атомов
{
	id_TpzTbl	= 0;	// номер таблицы типизирования
	Atoms.setmem(Na);
	//b_at.setmem(Na);
	Connect.setSize(Na,Na);
	surf	= 0x0;
}
//___________________________________________________
ConnectedAtoms::ConnectedAtoms(ConnectedAtoms  &r)
{
	Name.pst(r.Name);
	Atoms.pst(r.Atoms);
	Bonds.pst(r.Bonds);
	Connect	= r.Connect;
	id_TpzTbl=r.id_TpzTbl;
	surf	= r.surf;
}
//___________________________________________________
void ConnectedAtoms::InitSurface(SmplTpzlTable &Tbl)
{
	surf	= new MolSurf;
	InitObject(surf->DDD);

	ms1D<Vec3db> xyz;
	ms1Ddb r_wdw;
	ms1D<Vec3db> clr;

	xyz.init(Atoms.N);
	r_wdw.init(Atoms.N);
	clr.init(Atoms.N);

	int jj,ii;
	for(ii=0;ii<xyz.N;ii++)
	{
		xyz.x[ii].x[0]	= Atoms.x[ii].r.x[0];
		xyz.x[ii].x[1]	= Atoms.x[ii].r.x[1];
		xyz.x[ii].x[2]	= Atoms.x[ii].r.x[2];
		jj	= Atoms.x[ii].id_Tpz;
		r_wdw.x[ii]	= Tbl.Lines.x[jj].vdwrad;
		r_wdw.x[ii] = r_wdw.x[ii]==-0.01 ? 2 : r_wdw.x[ii]/100;
		clr.x[ii].x[0]	= (double)(Tbl.Lines.x[jj].color.x[0])/256.0;
		clr.x[ii].x[1]	= (double)(Tbl.Lines.x[jj].color.x[1])/256.0;
		clr.x[ii].x[2]	= (double)(Tbl.Lines.x[jj].color.x[2])/256.0;
	}

	surf->DDD.SetDataMol(xyz,r_wdw,clr);

}
//___________________________________________________
ConnectedAtoms::~ConnectedAtoms()
{
	if (surf!=0x0) delete surf;
}
//___________________________________________________
//___________________________________________________

//___________________________________________________
Molecule::Molecule(int Na)	// инициализация для молекулы из N атомов
{
	id_TpzTbl	= 0;	// номер таблицы типизирования
	Atoms.setmem(Na);
	b_at.setmem(Na);
	Connect.setSize(Na,Na);
}
//___________________________________________________
Molecule::Molecule(Molecule  &r)
{
	Name.pst(r.Name);
	//Atoms.pst(r.Atoms);
	Atoms.N=0;
	Atoms.pad(r.Atoms);
	Bonds.pst(r.Bonds);
	Connect	= r.Connect;
	id_TpzTbl=r.id_TpzTbl;
	b_at.pst(r.b_at);
	id_mov.pst(r.id_mov);
	lx=r.lx;
	ly=r.ly;
	lz=r.lz;
	pc=r.pc;
	mol_type	= r.mol_type;
	//chains		= r.chains;
	//ch_Leter	= r.ch_Leter;
	if(mol_type == PROTEINE)
	{
		*p_prt		= *r.p_prt;
		chain_node * p_chs;
		amino_node * p_amn;
		atom_node  * p_atm;
		for(int ii=0;ii<p_prt->childs.N;ii++)
		{
			p_chs	= p_prt->getChild(ii);
			for(int jj=0;jj<p_chs->childs.N;jj++)
			{
				p_amn	= p_chs->getChild(jj);
				for(int kk=0;jj<p_amn->childs.N;jj++)
				{
					p_atm	= p_amn->getChild(kk);
					p_atm->atom	= &Atoms.x[p_atm->atom->id_Tot];
				}
			}
		}
	}
}
//___________________________________________________
Molecule::~Molecule()
{
	if(mol_type == PROTEINE)
	{
		delete p_prt;
	}
}
//___________________________________________________
Molecule & Molecule::operator =( Molecule  &r)
{
	Name.pst(r.Name);
	//Atoms.pst(r.Atoms);
	Atoms.N=0;
	Atoms.pad(r.Atoms);
	Bonds.pst(r.Bonds);
	Connect.setCopy(r.Connect);
	id_TpzTbl=r.id_TpzTbl;
	b_at.pst(r.b_at);
	id_mov.pst(r.id_mov);
	lx=r.lx;
	ly=r.ly;
	lz=r.lz;
	pc=r.pc;
	mol_type	= r.mol_type;
	//chains		= r.chains;
	//ch_Leter	= r.ch_Leter;
	if(mol_type == PROTEINE)
	{
		p_prt	= new protein_node(*r.p_prt);
		//*p_prt		= *r.p_prt;
		chain_node * p_chs;
		amino_node * p_amn;
		atom_node  * p_atm;
		for(int ii=0;ii<p_prt->childs.N;ii++)
		{
			p_chs	= p_prt->getChild(ii);
			for(int jj=0;jj<p_chs->childs.N;jj++)
			{
				p_amn	= p_chs->getChild(jj);
				for(int kk=0;kk<p_amn->childs.N;kk++)
				{
					p_atm	= p_amn->getChild(kk);
					p_atm->atom	= &Atoms.x[p_atm->atom->id_Tot];
				}
			}
		}
	}
	return *this;
}
//___________________________________________________
void Molecule::ReInit(int Na)	// инициализация для молекулы из N атомов
{
	ClearAll();
	id_TpzTbl	= 0;	// номер таблицы типизирования
	Atoms.setmem(Na);
	b_at.setmem(Na);
	Connect.setSize(Na,Na);
}
//___________________________________________________
void Molecule::ReSize(int Na) // изменение размеров молелкулы на Na атомов с сохранением данных
{
	//if(Na>)
}
//___________________________________________________
int Molecule::AddBond(int oder,int in1,int in2)
{
	if (Connect.get(in1,in2)==0)
	{
		if(Bonds.N+1>Bonds.mN) Bonds.addmem();
		Bonds.x[Bonds.N].oder	= oder;
		Bonds.x[Bonds.N].id_Atoms.x[0]	= in1;
		Bonds.x[Bonds.N].id_Atoms.x[1]	= in2;
		Bonds.N++;
		Connect.set(in1,in2)	= Bonds.N;
		Connect.set(in2,in1)	= Bonds.N;
	}
	return (Bonds.N-1);
}/**/
void Molecule::AtomIns(int M_ID) // добавить атом с номером 'M_ID' из таблицы менделеева
{
	Atom cAt;

	cAt.id_Tpz	= M_ID;
	cAt.id_Tot	= Atoms.N;
	Atoms.pad(cAt);
	b_at.setmem(Atoms.N);
	Connect.reSize(Atoms.N,Atoms.N);
}
//___________________________________________________
void Molecule::AtomDel(int id)	// удалить атом с номером id
{
	if(Connect.I.x[id].N==0)
	{
		int ii,jj,kk;
		ii	= Atoms.N-1;
		if (id!=ii)
		{
			for(jj=0;jj<Connect.I.x[ii].N;jj++) // перебор связей последнего атома
			{
				kk	= Connect.S.x[ii].x[jj]-1;
				if(Bonds.x[kk].id_Atoms.x[0]==ii)Bonds.x[kk].id_Atoms.x[0]	= id;
				if(Bonds.x[kk].id_Atoms.x[1]==ii)Bonds.x[kk].id_Atoms.x[1]	= id;
			}
		}
		//showfull_infile(Connect,"CB.txt");
		Connect.delsym(id);
		//showfull_infile(Connect,"CA.txt");
		//AtomData *ptr;
		//ptr	= Atoms.x[id].dat.dat;
		// id == ii - здесь должно быть всегда
		// ! Atoms.x[id]	= Atoms.x[ii];
		// ! Atoms.x[id].id_Tot	= id;
		//Atoms.x[ii].dat.dat	= ptr;

		if(mol_type==PROTEINE)
		{
			/*protein_node * p_prt;
			atom_node * p_atm;

			p_atm	= Atoms.x[id].dat.dat->amin.p_atm;
			p_prt	= static_cast<protein_node * > ( p_atm->parent->parent->parent );

			p_prt->delAtomNode(p_atm);*/
/*
			p_AminoAcid ptr;
			jj	= Atoms.x[id].dat.dat->amin.id_at;
			ptr	= Atoms.x[id].dat.dat->amin.ptr_amin;
			if (jj!=ptr->Atoms_id.N)
			{ // своп для записей в массиве
				ptr->Atoms_id.x[jj]	= ptr->Atoms_id.x[ptr->Atoms_id.N-1]; // перестановка последнего номера наместо удаляемого номера
				kk	= ptr->Atoms_id.x[jj]; // глоб. номер атома запись о котором изменилась в массиве аминокислоты
				Atoms.x[kk].dat.dat->amin.id_at	= jj;	// записать новый локальный номер
			}
			// далее jj== ptr->Atoms_id.N
			ptr->Atoms_id.N--;
			if(ptr->Atoms_id.N==0)// удалены все атомы аминокислоты
			{
				
			}*/
		}

		Atoms.N--;
		//Atoms.x[Atoms.N].dat.dat	= 0x0;
	}
	else
	{
		// связи у удаляемого атома должны быть удалены заранее!
		exit(1);
	}
}
//___________________________________________________
void Molecule::endswap(int id)	// поменять местами атом с номером с последним атомом в массиве  Atoms
{
	int ii,jj,ib,id_at;
	ii	= Atoms.N-1;


	//showfull_infile ( Connect,"CB.txt");

	Connect.symswp(id);	// поменять местами строки и столбцы в матрице связности

	//showfull_infile ( Connect,"CA.txt");

	for(jj=0;jj<Connect.I.x[id].N;jj++)
	{
		ib	= Connect.S.x[id].x[jj]-1; // номер связи
		id_at	= Connect.I.x[id].x[jj]; // номер второго атома
		Bonds.x[ib].id_Atoms.x[0]	= id;
		Bonds.x[ib].id_Atoms.x[1]	= id_at;
	}

	for(jj=0;jj<Connect.I.x[ii].N;jj++)
	{
		ib	= Connect.S.x[ii].x[jj]-1; // номер связи
		id_at	= Connect.I.x[ii].x[jj]; // номер второго атома
		Bonds.x[ib].id_Atoms.x[0]	= ii;
		Bonds.x[ib].id_Atoms.x[1]	= id_at;
	}

	Atom	cAt;
	cAt	=Atoms.x[ii];
	Atoms.x[ii]	= Atoms.x[id];
	Atoms.x[id]	= cAt;
}
//___________________________________________________
void Molecule::AtomSwap(const int &id1,  const int &id2)
{
	//showfull_infile(Connect,"CB.txt");

	Connect.RowSwap(id1,id2);
	//showfull_infile(Connect,"CAr.txt");
	Connect.ColumnSwap(id1,id2);
	//showfull_infile(Connect,"CA.txt");

	int jj,ib,id_at;
	for(jj=0;jj<Connect.I.x[id1].N;jj++)
	{
		ib	= Connect.S.x[id1].x[jj]-1; // номер связи
		id_at	= Connect.I.x[id1].x[jj]; // номер второго атома
		Bonds.x[ib].id_Atoms.x[0]	= id1;
		Bonds.x[ib].id_Atoms.x[1]	= id_at;
	}

	for(jj=0;jj<Connect.I.x[id2].N;jj++)
	{
		ib	= Connect.S.x[id2].x[jj]-1; // номер связи
		id_at	= Connect.I.x[id2].x[jj]; // номер второго атома
		Bonds.x[ib].id_Atoms.x[0]	= id2;
		Bonds.x[ib].id_Atoms.x[1]	= id_at;
	}

	//Atom	cAt(Atoms.x[id1]);
	AtomData* ptr;
	vec3db r(Atoms.x[id1].r);
	jj	= Atoms.x[id1].id_Tpz;
	ptr	= Atoms.x[id1].dat.dat;

	Atoms.x[id1].r	= Atoms.x[id2].r;
	Atoms.x[id1].id_Tpz	= Atoms.x[id2].id_Tpz;
	Atoms.x[id1].dat.dat	= Atoms.x[id2].dat.dat;

	Atoms.x[id2].r	= r;
	Atoms.x[id2].id_Tpz	= jj;
	Atoms.x[id2].dat.dat= ptr;

	Atoms.x[id1].id_Tot	= id1;
	Atoms.x[id2].id_Tot	= id2;

	if(mol_type==PROTEINE)
	{
		/*jj	= Atoms.x[id1].dat.dat->amin.id_at;
		Atoms.x[id1].dat.dat->amin.ptr_amin->Atoms_id.x[jj]	= id1;

		jj	= Atoms.x[id2].dat.dat->amin.id_at;
		Atoms.x[id2].dat.dat->amin.ptr_amin->Atoms_id.x[jj]	= id2;*/


		Atoms.x[id1].dat.dat->amin->atom	= &Atoms.x[id1];
		Atoms.x[id2].dat.dat->amin->atom	= &Atoms.x[id2];
	}

	ptr	= 0x0;
	/*if(mol_type == PROTEINE)
	{
		for(int ii=0;ii<chains.N;ii++)
		{
			jj	= chains.x[ii].fnd(id1);
		}
	}*/
}
//___________________________________________________
void Molecule::BondDel(int id)	// удалить связь с номером id
{
	int id1,id2;

	id1	= Bonds.x[id].id_Atoms.x[0];
	id2	= Bonds.x[id].id_Atoms.x[1];
	//showfull_infile(Connect,"C0.txt");
	Connect.del(id2,id1);
	//showfull_infile(Connect,"C1.txt");
	Connect.del(id1,id2);
	//showfull_infile(Connect,"C2.txt");
	if (id!=Bonds.N-1)
	{
		Bonds.x[id]	= Bonds.x[Bonds.N-1];
		id1	= Bonds.x[id].id_Atoms.x[0];
		id2	= Bonds.x[id].id_Atoms.x[1];
		Connect.set(id2,id1)	=	Connect.set(id1,id2)	= id+1;
	}
	Bonds.N--;
}
//___________________________________________________
void Molecule::ClearAll()// очистить все поля объекта
{
	Name.N	= 0;
	for(int ii=0;ii<Atoms.N;ii++)
	{
		Atoms.x[ii].dat.~p_AD();
	}
	Atoms.N	= 0;
	Bonds.N	= 0;
	Connect.I.N	= 0;
	Connect.S.N = 0;
	Connect.nx	= 0;
	Connect.ny	= 0;
	id_TpzTbl	= 0;
	b_at.N		= 0;
	id_mov.N	= 0;
	pc	= 0;
	lx	= 0;
	ly	= 0;
	lz	= 0;
}
//___________________________________________________
void Molecule::UniMol(Molecule  *r)//,vecT<int> &id1)	// объединить текущую молекулу с другой в текущей молекуле
{
	int n,m;
	n	= Atoms.N;
	//id1	= -1;
	Atoms.pad(r->Atoms);
	//id1.setlen(Atoms.N);
	//id1	= -1;
	for(int ii=n;ii<Atoms.N;ii++)
	{
	//	id1.x[ii]	= Atoms.x[ii].id_Tot;
		Atoms.x[ii].id_Tot	+=n;	// коррекция данных о номере тек. атома в общем массиве атомов
	}
	m	= Bonds.N;
	Bonds.add(r->Bonds);
	for(int ii=m;ii<Bonds.N;ii++)Bonds.x[ii].id_Atoms	+=n;
	//showfull_infile(Connect,"Un1.txt");
	//showfull_infile(r.Connect,"r.txt");
	Connect.UniMatr(r->Connect);
	//showfull_infile(Connect,"Un2.txt");
	for(int ii=n;ii<Connect.ny;ii++)
	{
		Connect.S.x[ii]	+= m;
	}
}
//___________________________________________________
void Molecule::SubMol(vecT<int> &id,int at,int bn) // выделяет часть молекулы по одну сторону от атома at в напрвлении связи bn
{
	vec2int idb12;

	b_at.setlen(Atoms.N);
	b_at	= false;
	id.setmem(Atoms.N);

	idb12	= Bonds.x[bn].id_Atoms;

	b_at.x[idb12.x[0]]	= true;
	b_at.x[idb12.x[1]]	= true;

//	b_at.x[at]			= true; // ???
	AtNieb(id,at);
}
//___________________________________________________
void Molecule::AtNieb(vecT<int> &id_nieb,int at) // определяет номера id_nieb соседних по связям атомов с атомом id
{
	int ii,jj;
	for (ii=0;ii<Connect.I.x[at].N;ii++)
	{
		jj	= Connect.I.x[at].x[ii];	// номер атома-соседа по связи
		if (!b_at.x[jj])	// ещё не обрабатывался
		{
			b_at.x[jj]	= true;	// метка обработки
			id_nieb.add(jj);	// добавить себя в массив.
			AtNieb(id_nieb, jj);	// опросить соседей
		}
	}
}
//___________________________________________________
bool Molecule::ComTest(int &id_at1,int id_at2) // тест на принадлежность односвязной области двух атомов.
{
	vecT<int> id_neib;
	b_at.setlen(Atoms.N);
	b_at	= false;

	id_neib.add(id_at1);
	b_at.x[id_at1]= true;
	AtNieb(id_neib,id_at1); // в id_neib выделены номера атомов косвенно связанных с первым атомом.

	return (id_neib.fnd(id_at2)!=-1); // если второго атома не найдено, то возвращается ложь.
}
//___________________________________________________
void Molecule::SepMol(vecT<Molecule>  &r,vecT< vecT<int> > &ids) // разъеденить молекулу на две. (признак разделения - незвязанные связями группы атомов) 
{
	int ii,jj,kk,iy,iyn,ix,ixn,ib;
	vecT<int> id;
	r.setmem(ids.N);
	Molecule mol;
	id.setmem(Atoms.N);
	for(ii=0;ii<ids.N;ii++)
	{
		mol.ReInit(ids.x[ii].N);
		id.N	= ids.x[ii].N;
		id		= -1;
		for(jj=0;jj<ids.x[ii].N;jj++)
		{
			kk	= ids.x[ii].x[jj];
			mol.Atoms.x[jj]	= Atoms.x[kk];
			mol.Atoms.x[jj].id_Tot	= jj;
			id.x[kk]	= jj;
		}
		mol.Atoms.N	= ids.x[ii].N;
		for(iyn=0;iyn<ids.x[ii].N;iyn++)
		{
			iy	= ids.x[ii].x[iyn];
			for(jj=0;jj<Connect.I.x[iy].N;jj++)
			{
				ix	= Connect.I.x[iy].x[jj];
				ixn	= id.x[ix];
				ib	= Connect.S.x[iy].x[jj]-1;
				mol.AddBond(Bonds.x[ib].oder,iyn,ixn);
			}
		}
		r.pad(mol);
	}
}
//___________________________________________________
void Molecule::SepMol(Molecule *r, int &Nmx) // разъеденить молекулу по рубежу задаваемым номером Nmx
{
	int jj,ii,io,kk;
	r->ReInit(Atoms.N-Nmx);
	//r->Atoms.pad()
	jj	= 0;
	for(ii=Nmx;ii<Atoms.N;ii++)
	{
		r->Atoms.x[jj]	= Atoms.x[ii];
		r->Atoms.x[jj].id_Tot	= jj;
		jj++;
	}
	r->Atoms.N	= jj;
	r->Connect.setSize(jj,jj);
	for(ii=Nmx;ii<Atoms.N;ii++)
	{
		for(jj=0;jj<Connect.I.x[ii].N;jj++)
		{
			kk	= Connect.I.x[ii].x[jj]; // номер атома на связи в исходной молекуле
			if(kk>ii)	// исключение двойного выбора связи
			{
				io	= Connect.S.x[ii].x[jj]-1;
				io	= Bonds.x[io].oder;
				r->AddBond(io,(ii-Nmx),(kk-Nmx));
			}
		}
	}

	Molecule mol;
	mol.Atoms.swp(Atoms);
	mol.Atoms.N	= Nmx;
	mol.Connect.setSize(Nmx,Nmx);
	for(ii=0;ii<Nmx;ii++)
	{
		for(jj=0;jj<Connect.I.x[ii].N;jj++)
		{
			kk	= Connect.I.x[ii].x[jj]; // номер атома на связи в исходной молекуле
			if(kk>ii)	// исключение двойного выбора связи
			{
				io	= Connect.S.x[ii].x[jj]-1;
				io	= Bonds.x[io].oder;
				mol.AddBond(io,ii,kk);
			}
		}
	}

	mol.Atoms.swp(Atoms);
	mol.Bonds.swp(Bonds);
	mol.Connect.swp(Connect);
}
//___________________________________________________
void Molecule::SepMolInd(vecT<vecT<int> >&ids)// определение номеров атомов связных связями
{
	vecT<int> id_neib;
	vecT<int> n_ats,id_n;
	//vecT<vecT<int> > l_ids;
	int jj;
	b_at.setlen(Atoms.N);
	b_at	= false;
	jj		= b_at.fnd(false);
	ids.N	= 0;
	while(jj!=-1)
	{
		id_neib.N	= 0;
		id_neib.add(jj);
		b_at.x[jj]= true;
		AtNieb(id_neib,jj); // в id_neib выделены номера атомов косвенно связанных с первым атомом.
		ids.pad(id_neib);
		//n_ats.add(id_neib.N);
		jj	= b_at.fnd(false);
	}
	for(jj=0;jj<ids.N;jj++) ids.x[jj].sort();
	/*ids.setlen(l_ids.N);
	if(l_ids.N>1)
	{
		jj	= l_ids.N-1;
		id_n.var1D(0,1,jj);
		for(jj=0;jj<l_ids.N;jj++) 
		{
			n_ats.add(l_ids.x[jj].idscheck());
		}
		n_ats.sort_(id_n);
		int ii,kk;
		kk	= id_n.N;
		for(jj=0;jj<id_n.N;jj++)
		{
			kk--;
			ii	= id_n.x[jj];
			ids.x[kk].swp(l_ids.x[ii]);
		}
	}else
	{
		ids.x[0].swp(l_ids.x[0]);
	}*/

}
//___________________________________________________
void Molecule::GetSubMol(int &id_at1,int &id_at2, vecT<int> &id_ats) // выдать фрагмент молеклы, по одну сторону от связи id_at1-id_at2, со стороны id_at2
{
	int ii,jj;
	b_at.setlen(Atoms.N);
	b_at	= false;
	//b_at.x[id_at1]	= true;
	b_at.x[id_at2]	= true;
	id_ats.N= 0;
	id_ats.add(id_at2);
	//AtNieb(id_ats, id_at2);	// опросить соседей

	for (ii=0;ii<Connect.I.x[id_at2].N;ii++)
	{
		jj	= Connect.I.x[id_at2].x[ii];	// номер атома-соседа по связи
		if ((jj!=id_at1)&&(!b_at.x[jj]))	// ещё не обрабатывался
		{
			b_at.x[jj]	= true;	// метка обработки
			id_ats.add(jj);	// добавить себя в массив.
			AtNieb(id_ats, jj);	// опросить соседей
		}
	}
	jj	= id_ats.fnd(id_at1);
	if(jj!=-1) id_ats.N = 1;
}
//___________________________________________________
void Molecule::SetLocBas1(int at0,int at,int bn) // установка лоакльного базиса 1 типа. (для изменения вал. угла)
{
	int ida1,ida2,idpc;

	ida1	= Bonds.x[bn].id_Atoms.x[0];
	ida2	= Bonds.x[bn].id_Atoms.x[1];

	idpc		= ida1==at ? ida2 : ida1; 

	pc	= Atoms.x[idpc].r;
	lx	= Atoms.x[at].r-pc;
	lx.nrml();
	ly	= Atoms.x[at0].r-pc;
	lz.crss(lx,ly);
	lz.nrml();
	ly.crss(lz,lx);

	SubMol(id_mov,at,bn); // выделяет часть молеулы по одну сторону от атома at в напрвлении связи bn
}
//___________________________________________________
void Molecule::GeoModify1(double fi)
{
	int ii,jj;
	vec3db r0,r1;
	double x,y,csf,snf;
	csf	= cos(fi);
	snf	= sin(fi);
	 for(ii=0;ii,id_mov.N;ii++)
	 {
		 jj	= id_mov.x[ii];
		 r0	= Atoms.x[jj].r-pc;
		 x	= r0.scpr(lx);
		 y	= r0.scpr(ly);
		 r1.x[2] = r0.scpr(lz);
		 r1.x[0] = x*csf+y*snf;
		 r1.x[1] = -x*snf+y*csf;
	 }
}
//___________________________________________________
void Molecule::setGCM(const vec3db & r0) // установить центр масс молекулы в значение r0
{
	int ii;
	vec3db p;
	p	= 0.0;
	for(ii=0;ii<Atoms.N;ii++)
	{
		p	+= Atoms.x[ii].r;
	}
	p	/= double(Atoms.N);

	p -= r0;
	p *= -1.0;

	for(ii=0;ii<Atoms.N;ii++)
	{
		Atoms.x[ii].r	+= p;
	}
}
//___________________________________________________
vec3db Molecule::getGCM()	// вернуть значение коорлинат геометрического центра молекулы.
{
	int ii;
	vec3db p;
	p	= 0.0;
	for(ii=0;ii<Atoms.N;ii++)
	{
		p	+= Atoms.x[ii].r;
	}
	p	/= double(Atoms.N);
	return p;
}
//___________________________________________________
double Molecule::getMSz()	// вернуть размер молекулы
{
	int ii;
	vec3db p,p0;
	double r;
	p0	= 0.0;
	for(ii=0;ii<Atoms.N;ii++)
	{
		p0	+= Atoms.x[ii].r;
	}
	p0	/= double(Atoms.N);
	r	= 0.0;
	for(ii=0;ii<Atoms.N;ii++)
	{
		p	= Atoms.x[ii].r-p0;
		r	+= p.sqnr(); 
	}
	r	/= (double)(Atoms.N);
	r	= sqrt(r);
	r	+= r<3.0 ? 3 : 0;
	return r;
}
//___________________________________________________
void Molecule::setAtoms2Amin()
{
	/*int id_at;
	ChAminPtr amn;
	for(int ic=0;ic<chains.N;ic++)// перебор цепей
	{
		for(int ia = 0; ia<chains.x[ic].N;ia++)	// перебор аминок слот
		{
			amn.id_ch		= ic;
			amn.ptr_amin	= chains.x[ic].x+ia;
			for(int it = 0;it<amn.ptr_amin->Atoms_id.N;it++)	// перебор аминокислот
			{
				amn.id_at	= it;
				id_at		= amn.ptr_amin->Atoms_id.x[it];	// номер атома в глоб. массиве.
				amn.p_atm	= Atoms.x[id_at].dat.dat->amin.p_atm;
				Atoms.x[id_at].dat.setamin(amn);
			}		
		}
	}*/
}
//___________________________________________________
void base_node::addChild(base_node *chld)
{
	chld->id	= childs.N;
	chld->parent	= this;
	childs.add(chld);
}
void base_node::addChild(base_node *chld, int ii)
{
	chld->parent	= this;
	childs.add(chld,ii);
	for(;ii<childs.N;ii++) // цикл коррекции индексов
	{
		childs.x[ii]->id	= ii;
	}
}
base_node * base_node::getChild(int ii)
{
	return childs.x[ii];
}
void base_node::delChild()
{
	int ii	= --childs.N;
	delete childs.x[ii];
	childs.x[ii] = 0x0;
}
void base_node::delChild(int ii)
{
	delete  childs.x[ii];	// удаление узла
	childs.rem(1,ii);
	childs.x[childs.N] = 0x0;
	for(;ii<childs.N;ii++) // цикл коррекции индексов
	{
		childs.x[ii]->id	= ii;
	}
}
void base_node::swap(int ii)
{
	int jj = childs.N-1;
	if(jj>ii)
	{
		base_node * p = childs.x[ii];
		childs.x[ii]	= childs.x[jj];
		childs.x[jj]	= p;
	}
}
void base_node::updateparents()
{
	for(int ii=0;ii<childs.N;ii++)
	{
		childs.x[ii]->parent	= this;
	}
}
base_node::~base_node()
{
	parent = 0x0;
	id		= -1;
	for(int ii=0;ii<childs.N;ii++)
	{
		delete childs.x[ii];
	}
}
base_node::base_node( base_node &bs)
{
	parent	= bs.parent;
	id	= bs.id;
	childs.setlen(bs.childs.N);
	for(int ii=0;ii<childs.N;ii++)
	{
		childs.x[ii]	= new base_node(*bs.childs.x[ii]);
		childs.x[ii]->parent	= this;
	}
	//updateparents();
}
base_node & base_node::operator =( base_node &bs)
{
	parent	= bs.parent;
	id	= bs.id;
	childs.setlen(bs.childs.N);
	for(int ii=0;ii<childs.N;ii++)
	{
		childs.x[ii]	= new base_node(*bs.childs.x[ii]);
		childs.x[ii]->parent	= this;
	}
	//updateparents();
	return * this;
}
//___________________________________________________
chain_node::chain_node( chain_node &bs)
{
	parent	= bs.parent;
	ch	= bs.ch;
	id	= bs.id;
	childs.setlen(bs.childs.N);
	for(int ii=0;ii<childs.N;ii++)
	{
		childs.x[ii]	= new amino_node(*bs.getChild(ii));
		childs.x[ii]->parent	= this;
	}
}
chain_node & chain_node::operator =( chain_node &bs)
{
	parent	= bs.parent;
	ch	= bs.ch;
	id	= bs.id;
	childs.setlen(bs.childs.N);
	for(int ii=0;ii<childs.N;ii++)
	{
		childs.x[ii]	= new amino_node(*bs.getChild(ii));
		childs.x[ii]->parent	= this;
	}
	return *this;
}
/*void chain_node::delChild()
{
	int ii	= --childs.N;
	delete childs.x[ii];
	childs.x[ii] = 0x0;
}
void chain_node::delChild(int ii)
{
	swap(ii);
	ii	= --childs.N;
	delete childs.x[ii];
	childs.x[ii] = 0x0;
}*/
//___________________________________________________
atom_node::~atom_node()
{
	atom	= 0x0;
}
atom_node::atom_node( atom_node &bs)
{
	parent	= bs.parent;
	atom	= bs.atom;
	id	= bs.id;
}
atom_node & atom_node::operator =( atom_node &bs)
{
	parent	= bs.parent;
	atom	= bs.atom;
	id	= bs.id;
	name.pst(bs.name);
	return *this;
}
//___________________________________________________
/*void amino_node ::addChild(atom_node *chld)
{
	chld->id	= childs.N;
	chld->parent	= this;
	childs.add(chld);
}*/
atom_node * amino_node::getChild(int ii) const
{
	return static_cast<atom_node *> (childs.x[ii]);
}
amino_node::amino_node( amino_node &bs)
{
	parent	= bs.parent;
	id_ch	=bs.id_ch;
	id		= bs.id;
	name.pst(bs.name);
	childs.setlen(bs.childs.N);
	for(int ii=0;ii<childs.N;ii++)
	{
		childs.x[ii]	= new atom_node(*bs.getChild(ii));
		childs.x[ii]->parent	= this;
	}
}
amino_node & amino_node::operator =(amino_node &bs)
{
	parent	= bs.parent;
	id_ch	= bs.id_ch;
	id		= bs.id;
	name.pst(bs.name);
	childs.setlen(bs.childs.N);
	for(int ii=0;ii<childs.N;ii++)
	{
		childs.x[ii]	= new atom_node(*bs.getChild(ii));
		childs.x[ii]->parent	= this;
	}
	return *this;
}
/*
void amino_node::delChild()
{
	int ii	= --childs.N;
	delete childs.x[ii];
	childs.x[ii] = 0x0;
}
void amino_node::delChild(int ii)
{
	swap(ii);
	ii	= --childs.N;
	delete childs.x[ii];
	childs.x[ii] = 0x0;
}
//___________________________________________________
void chain_node ::addChild(amino_node *chld)
{
	chld->id	= childs.N;
	chld->parent	= this;
	childs.add(chld);
}*/
amino_node * chain_node::getChild(int ii) const
{
	return static_cast<amino_node *> (childs.x[ii]);
}
//___________________________________________________
/*void protein_node ::addChild(chain_node *chld)
{
	chld->id	= childs.N;
	chld->parent	= this;
	childs.add(chld);
}*/
chain_node * protein_node::getChild(int ii) const
{
	return static_cast<chain_node *> (childs.x[ii]);
}
//___________________________________________________
void protein_node::setProt(vecT< vecT< AminoAcid > >	&chains, vecT<char>	&ch_Leter,Molecule &M) // генерирование структуры дерева по данным chains и ch_Leter
{
	chain_node * p_chs;
//	base_node * p_bs;
	for(int ii=0;ii<ch_Leter.N;ii++)
	{
		p_chs	= new chain_node;
		p_chs->ch	= ch_Leter.x[ii];
		this->addChild(p_chs);
	}
	amino_node * p_amn;
	atom_node  * p_atm;
	for(int ii=0;ii<childs.N;ii++)
	{
		p_chs	= this->getChild(ii);//static_cast<chain_node *> (childs.x[ii]); // цепь 
		for(int jj=0;jj<chains.x[ii].N;jj++)
		{
			p_amn	= new amino_node; //  новый амино-узел
			//p_amn->id	= jj;
			p_amn->id_ch	= chains.x[ii].x[jj].id; // номер аминокислоты по pdb записи
			p_amn->name		= chains.x[ii].x[jj].amin_ch; // имя аммнокислоты
			p_chs->addChild(p_amn);// добавить к цепи амино-узел
			for(int kk=0;kk<chains.x[ii].x[jj].Atoms_id.N;kk++)
			{
				p_atm	= new atom_node; // новый атом-узел
				//p_atm->id	= kk;
				p_atm->atom	= M.Atoms.x+chains.x[ii].x[jj].Atoms_id.x[kk]; // связь с атомом
				//p_bs	= static_cast<base_node *> (p_atm);  // базовый узел от атом-узла
				//p_amn->addChild(p_bs); // добавить атом-узел по его базовому узлу
				p_amn->addChild(p_atm);
			}
		}
		
	}

	for(int ii=0;ii<childs.N;ii++)	// перебор цепей
	{
		p_chs	= this->getChild(ii);
		for(int jj=0;jj<childs.x[ii]->childs.N;jj++)	// перебор аминокислот
		{
			p_amn	= p_chs->getChild(jj);
			for(int kk=0;kk<childs.x[ii]->childs.x[jj]->childs.N;kk++)
			{
				p_atm	= p_amn->getChild(kk);//static_cast<atom_node *> (childs.x[ii]->childs.x[jj]->childs.x[kk]);
				if(p_atm->atom->dat.dat== 0x0)
				{
					p_atm->atom->dat.initdat();
				}
				p_atm->atom->dat.dat->amin	= p_atm;
			}
		}
	}
	M.p_prt	= this;
}
/*void protein_node::delChild()
{
	int ii	= --childs.N;
	delete childs.x[ii];
	childs.x[ii] = 0x0;
}
void protein_node::delChild(int ii)
{
	swap(ii);
	ii	= --childs.N;
	delete childs.x[ii];
	childs.x[ii] = 0x0;
}*/
//___________________________________________________
/*void protein_node::delAtomNode(atom_node *p_atm) // удалить узел по указателю p_atm
{
	amino_node *p_amn;
	int id;
	p_amn	= static_cast< amino_node * > (p_atm->parent); // аминокислота содержащая удаляемый атом
	id	= p_atm->id; // номер удаляемого атом-узла
	p_amn->childs.N--;
	p_amn->childs.x[id]	= p_amn->childs.x[p_amn->childs.N]; // удаление атом-узла путём замены его последним атом-узлом из массива дочерних узлов
	//p_amn->childs.x[p_amn->childs.N]	= 0x0;
	p_atm = static_cast<atom_node *> (p_amn->childs.x[id]); // указатель на перемещённый узел
	p_atm->atom->dat.dat->amin.p_atm	= p_atm; // обновление записи в данных атома об указателе на его атом-узел в структуре протениа.
}*/
//___________________________________________________
atom_node * protein_node::addAtomNode(int id_ch,int id_am,int id_at)
{
	atom_node * p_atm= 0x0;
	if(id_ch<childs.N)
	{
		chain_node * p_chs	= getChild(id_ch);
		if(id_am<p_chs->childs.N)
		{
			//p_amn	= p_chs->getChild(id_am);//static_cast<amino_node * > (childs.x[id_ch]->childs.x[id_am]);
			p_atm	= new atom_node;
			//p_chs->getChild(id_am)->addChild(p_atm);
			p_chs->childs.x[id_am]->addChild(p_atm,id_at);
		}
	}
	return p_atm;
}
protein_node::protein_node(protein_node &bs)
{
	parent	= bs.parent;
	id	= bs.id;
	id_ml	= bs.id_ml;
	protname.pst(bs.protname);
	childs.setlen(bs.childs.N);
	for(int ii=0;ii<childs.N;ii++)
	{
		childs.x[ii]	= new chain_node(*bs.getChild(ii));
		childs.x[ii]->parent	= this;
	}
}
protein_node & protein_node::operator =(protein_node &bs)
{
	parent	= bs.parent;
	id	= bs.id;
	id_ml	= bs.id_ml;
	protname.pst(bs.protname);
	childs.setlen(bs.childs.N);
	for(int ii=0;ii<childs.N;ii++)
	{
		childs.x[ii]	= new chain_node(*bs.getChild(ii));
		childs.x[ii]->parent	= this;
	}
	return *this;
}
//___________________________________________________
//void protein_node::clearAll()
//{
	//base_node::~base_node();
	/*atom_node  *p_atm;
	amino_node *p_amn;
	chain_node *p_chs;
	for(int ii=0;ii<childs.mN;ii++) // перебор цепей-узлов
	{
		p_chs	= static_cast<chain_node * > (childs.x[ii]);
		for(int jj =0;jj<p_chs->childs.mN;jj++) // перебор амино-узлов
		{
			p_amn	= static_cast<amino_node *> (p_chs->childs.x[jj]);
			for(int kk=0;kk<p_amn->childs.mN;kk++) // перебор атом-узлов
			{
				p_atm	= static_cast<atom_node * > (p_amn->childs.x[kk]);
				p_atm->atom	= 0x0;
				p_atm->parent	= 0x0;
				delete p_atm;
			}
			p_amn->parent	= 0x0;
			//p_amn->childs.~vecT();
			//p_amn->name.~vecT();
			delete p_amn;
		}
		p_chs->parent	= 0x0;
		//p_chs->childs.~vecT();
		delete p_chs;
	}*/

//}
//___________________________________________________
//___________________________________________________
//___________________________________________________
//___________________________________________________
//___________________________________________________
int SmplTpzlTable::indret(vec2T<char> &ch)
{
	int i;
	for(i=0;(i<Lines.N)&(Lines.x[i].Ch!=ch);i++);
	return i==Lines.N ? -1 : i;
}
//___________________________________________________
SmplTpzlTable::SmplTpzlTable()// конструктор загружает таблицу из файла
{
	char fname[]	= "SmplTable.txt";
	int Ns;
	char *token;
	char seps[]   = " ,\t\n";
	vecT<char> str;
	str.setlen(200);


	FILE *fio;
	fio	= fopen(fname,"r");
	fgets( str.x,str.N, fio );
	Ns	= 0;
	do
	{
		fgets( str.x,str.N,fio);
		Ns++;
	}while(!feof(fio));
	fclose(fio);

	Lines.setmem(Ns);
	fio	= fopen(fname,"r");
	fgets( str.x,str.N, fio );
	for(int i=0;i<Ns;i++)
	{
		fgets(str.x,str.N,fio);
		token = strtok( str.x,seps);
		if (token != NULL)
		{
			Lines.x[i].id_MndTbl	= atoi(token);
			token = strtok( NULL, seps );
			Lines.x[i].Ch.x[0]	= token[0];
			Lines.x[i].Ch.x[1]	= token[1];
			token = strtok( NULL, seps );
			Lines.x[i].Name.add(token,(int)strlen(token)+1);
			token = strtok( NULL, seps );
			token = strtok( NULL, seps );
			Lines.x[i].mass	= atof(token);
			token = strtok( NULL, seps );
			Lines.x[i].emprad	= atof(token);
			token = strtok( NULL, seps );
			Lines.x[i].calrad	= atof(token);
			token = strtok( NULL, seps );
			Lines.x[i].vdwrad	= atof(token);
			Lines.x[i].vdwrad	= Lines.x[i].vdwrad==-1 ? 185 : Lines.x[i].vdwrad;
			token = strtok( NULL, seps );
			Lines.x[i].cvlrad	= atof(token);
			token = strtok( NULL, seps );
			token = strtok( NULL, seps );
			Lines.x[i].metrad	= atof(token);
			token = strtok( NULL, seps );
			Lines.x[i].color.x[0]	= atoi(token);
			token = strtok( NULL, seps );
			Lines.x[i].color.x[1]	= atoi(token);
			token = strtok( NULL, seps );
			Lines.x[i].color.x[2]	= atoi(token);
			token = strtok( NULL, seps );
			while( token != NULL )
			{
				Lines.x[i].oxd.add(atoi(token));
				token = strtok( NULL, seps );
			}
			Lines.N++;
		}
	}
	fclose(fio);
	brad    = 0.05;	// радиус цилинрда связи
	krad	= 0.3;	// коэффициент радиуса атома (krad*___rad - значение радиуса рисуемого шара )
};

/*void my_gcvt(double x,int n, vecT<char> &s)	// преобразовать число в строку
{
	if(x==0.0)
	{
		s.N	= 0;
		s.add("0.");
		for(int ii=0;ii<n;ii++)s.add('0');
		s.add('\0');
	}else
	{
		int ix;
		//ix	= int(x>0 ? )
	}
}*/
//___________________________________________________
//___________________________________________________
#endif