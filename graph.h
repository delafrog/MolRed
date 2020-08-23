/*
graph.h 
определеине класса описывающего взвешенный граф.
--------------
MolRed.
Copyright @ Zhabin S.N.
ver. 2.0.0
09.2010
*/

#ifndef GRAPH_H
#define GRAPH_H

#include "linalg.h"
//#include "linalg.cpp"
#include <math.h>

struct mybool8
{
	bool a : 1;
	bool b : 1;
	bool c : 1;
	bool d : 1;
	bool e : 1;
	bool f : 1;
	bool g : 1;
	bool h : 1;
	void setalltrue(){a	= 1;b	= 1;c	= 1;d	= 1;e	= 1;f	= 1;g	= 1;h	= 1;}
	bool getvalue(unsigned int jj)
	{
		switch (jj)
		{
		case 0:{return a;}
		case 1:{return b;}
		case 2:{return c;}
		case 3:{return d;}
		case 4:{return e;}
		case 5:{return f;}
		case 6:{return g;}
		case 7:{return h;}
		}
		return false;
	}
	void extrtrue(unsigned int &i1,vecT<unsigned int> &p)
	{
		unsigned int jj;
		if(a){++(jj=i1<<1);p.x[p.N]=jj;p.N++;}
		i1++;
		if(b){++(jj=i1<<1);p.x[p.N]=jj;p.N++;}
		i1++;
		if(c){++(jj=i1<<1);p.x[p.N]=jj;p.N++;}
		i1++;
		if(d){++(jj=i1<<1);p.x[p.N]=jj;p.N++;}
		i1++;
		if(e){++(jj=i1<<1);p.x[p.N]=jj;p.N++;}
		i1++;
		if(f){++(jj=i1<<1);p.x[p.N]=jj;p.N++;}
		i1++;
		if(g){++(jj=i1<<1);p.x[p.N]=jj;p.N++;}
		i1++;
		if(h){++(jj=i1<<1);p.x[p.N]=jj;p.N++;}
	}
};

class vecboolx8
{
public:
	vecT<mybool8> ch; 
	//int getchsize(){return ch.N;}
	void setsize(unsigned int N) {int ii=N/8; ii++; ch.setlen(ii);}
	inline void settrue(unsigned int &id)
	{
		int ii,jj; ii=id/8; jj= id%8;
		switch (jj)
		{
			case 0:{ch.x[ii].a	= 1;break;}
			case 1:{ch.x[ii].b	= 1;break;}
			case 2:{ch.x[ii].c	= 1;break;}
			case 3:{ch.x[ii].d	= 1;break;}
			case 4:{ch.x[ii].e	= 1;break;}
			case 5:{ch.x[ii].f	= 1;break;}
			case 6:{ch.x[ii].g	= 1;break;}
			case 7:{ch.x[ii].h	= 1;break;}
		}
	}
	inline void setfalse(unsigned int &id)
	{
		int ii,jj; ii=id/8; jj= id%8;
		switch (jj)
		{
			case 0:{ch.x[ii].a	= 0;break;}
			case 1:{ch.x[ii].b	= 0;break;}
			case 2:{ch.x[ii].c	= 0;break;}
			case 3:{ch.x[ii].d	= 0;break;}
			case 4:{ch.x[ii].e	= 0;break;}
			case 5:{ch.x[ii].f	= 0;break;}
			case 6:{ch.x[ii].g	= 0;break;}
			case 7:{ch.x[ii].h	= 0;break;}
		}
	}
	void setalltrue()
	{
		mybool8 lg;
		lg.setalltrue();
		for (unsigned int ii=0;ii<ch.N;ii++) 
		{
			ch.x[ii]	= lg;
			/*ch.x[ii].a	= 1;
			ch.x[ii].b	= 1;
			ch.x[ii].c	= 1;
			ch.x[ii].d	= 1;
			ch.x[ii].e	= 1;
			ch.x[ii].f	= 1;
			ch.x[ii].g	= 1;
			ch.x[ii].h	= 1;*/
		}
	}
	bool getvalue(unsigned int id)
	{
		int ii,jj; ii=id/8; jj= id%8;
		switch (jj)
		{
			case 0:{return (ch.x[ii].a	== 1);}
			case 1:{return (ch.x[ii].b	== 1);}
			case 2:{return (ch.x[ii].c	== 1);}
			case 3:{return (ch.x[ii].d	== 1);}
			case 4:{return (ch.x[ii].e	== 1);}
			case 5:{return (ch.x[ii].f	== 1);}
			case 6:{return (ch.x[ii].g	== 1);}
			case 7:{return (ch.x[ii].h	== 1);}
		}
		return false;
	}
};

void  Primes(unsigned int N,vecT<unsigned int> &a);// возвращает массив первых N простых чисел. (решето Сундарама)
void  Primes_(unsigned int N,vecT<unsigned int> &a);// возвращает массив первых N простых чисел. (решето Сундарама)
void Primes1(unsigned int N,vecT<unsigned int> &a);

class Graph
{
public:
	vecT<int> VertexId; // список вершин. Вершины разных типов задаются разными простыми числами. 
	SparseMatr <int> AdjacMatr; // матрица связности графа - значения элементов матрицы- произведеия типов смежных вершин из VertexId

	Graph(){}
	Graph(Graph & a){VertexId = a.VertexId;AdjacMatr = a.AdjacMatr;}
	void setVertexes(vecT<int> &types);	// установка типов вершин. в types номера типов соответсвующей вершины
	void setVertexes(int N){VertexId.setlen(N);VertexId	= 1;}	// установка N вершин одинакового типа;
	void setAdjacency(SparseMatr<int> &CMatr);	// установить матрицу связности по маске матрицы CMatr, но у ччётом весов вершин


};


#endif 