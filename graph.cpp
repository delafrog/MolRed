/*
graph.cpp 
реализация методов класса описывающего взвешенный граф.
--------------
MolRed.
Copyright @ Zhabin S.N.
ver. 2.0.0
09.2010
*/

#ifndef GRAPH_CPP
#define GRAPH_CPP

#include "linalg.h"
//#include "linalg.cpp"
#include "graph.h"

void  Primes(unsigned int N,vecT<unsigned int> &a)// возвращает массив первых N простых чисел. (решето Сундарама)
{
	if(N==1){a.N=0;a.add(2);}else{
	if(N>200000000) N	= 200000000;
	vecboolx8 A;unsigned int ii,jj,i1;unsigned int N1 =(unsigned int) (N)*(1.0879*log( (double)(N))+0.5659);N1--;N1/=2;N1=N1<10? 10:N1;A.setsize(N1+1);A.setalltrue();
	for(ii=1;ii<=(unsigned int) (N1-1)/3;ii++){for(jj=ii;jj<=(unsigned int)(N1-ii)/(2*ii+1);jj++){(++(i1=jj<<1)*=ii)+=jj;A.setfalse(i1);}}
	i1	= N1+1;	a.setmem(N);vecT<unsigned int> b(8);
	for(ii=0;ii<A.ch.N;ii++){b.N	= 0;i1	= ii*8;	A.ch.x[ii].extrtrue(i1,b);if(a.N+b.N<a.mN){a.add(b);}else{b.N	= a.mN-a.N;a.add(b);break;}}a.x[0]	= 2;}
};

void  Primes_(unsigned int N,vecT<unsigned int> &a)// возвращает массив первых N простых чисел. (решето Сундарама)
{
	if(N>20000000) N	= 20000000;
	unsigned int ii,jj,i1;vecT<bool> ch;unsigned int N1 =(unsigned int) (N)*(1.0879*log( (double)(N))+0.5659);N1--;N1/=2;ch.setlen((N1+1));ch	= true;
	for(ii=1;ii<=(unsigned int) (N1-1)/3;ii++){for(jj=ii;jj<=(unsigned int)(N1-ii)/(2*ii+1);jj++){(++(i1=jj<<1)*=ii)+=jj;ch.x[i1]=false;}}
	i1	= N1+1;	a.setmem(N);for(ii=0;(ii<i1)&&(a.N<N);ii++){if(ch.x[i1]){++(jj=ii<<1);a.add(jj);}}a.x[0]	= 2;
};

void Primes1(unsigned int N,vecT<unsigned int> &a) // алгоритм из интернета [ автор der_waldgeist (жж)]
{
	bool isPrime;
	unsigned int num,level;
	num		= 0;
	level	=1;
	a.setmem(N);
	vecT<unsigned int> maxes;
	num	= (unsigned int) 2*sqrt((double) N );
	maxes.setmem(num);
	num	= 0;
	a.add(2);
	for(unsigned int ii=0;ii<N;ii++)
	{
		isPrime = false;
		while (!isPrime)
		{
			num++;
			if (2 * level * (level + 1) == num)
			{
				maxes.add(2 * level * (level + 1));
				level++;
			}
			isPrime = true;
			for (int i = 0; i < maxes.N; i++)
			{
				if (num == maxes.x[i])
					isPrime = false;
				else if (num > maxes.x[i])
					maxes.x[i] += i * 2 + 3;
			}
		}
		a.add(2*num+1);
	}
}

void Graph::setVertexes(vecT<int> &types)
{
	vecT<int> tp,id,idt;
	tp.setmem(types.N);
	id.setmem(types.N);
	idt.setlen(types.N);
	id.var1D(0,1,types.N-1);
	types.sort(tp,id);
	int ii,jj,kk;
	kk	= tp.x[0];
	jj	= 0;
	idt.x[id.x[0]] = jj;
	for(ii=1;ii<tp.N;ii++)
	{
		if(tp.x[ii]!=kk)
		{
			kk	= tp.x[ii];
			jj++;
		}
		idt.x[id.x[ii]]=jj;
	}
	jj++;
	// в jj количество различных типов вершин
	vecT<unsigned int> prms;
	Primes(jj,prms);
	VertexId.setmem(types.N);
	for(ii=0;ii<types.N;ii++)
	{
		VertexId.add(prms.x[idt.x[ii]]);
	}
}

void Graph::setAdjacency(SparseMatr<int> &CMatr)	// установить матрицу связности по маске матрицы CMatr, но у ччётом весов вершин
{
	AdjacMatr=CMatr;
	int ii,jj,kk;
	vecT<int> * ptS, * ptI;
	showfull_infile(AdjacMatr,"bef.txt");
	for(ii=0;ii<AdjacMatr.S.N;ii++)
	{
		kk	= VertexId.x[ii];
		ptS	= &AdjacMatr.S.x[ii];
		ptI	= &AdjacMatr.I.x[ii];
		for(jj=0;jj<ptS->N;jj++)
		{
			ptS->x[jj]	= kk*VertexId.x[ptI->x[jj]];
		}
	}
	for(ii=0;ii<AdjacMatr.nx;ii++)
	{
		AdjacMatr.set(ii,ii)	= VertexId.x[ii]*VertexId.x[ii];
	}
	showfull_infile(AdjacMatr,"aft.txt");

	SparseMatr<double> A;
	A.setCopyW(AdjacMatr);
	FullMatrix<double> B,Q;
	//vecT< vecT<double> > Q;
	B.setCopy(A);
	B.showfull_infile("B.txt");
	B.HessenbergForm(Q);

	B.showfull_infile("B_hsbrg.txt");
	Q.showfull_infile("Q_hsbrg.txt");

	TriDiag<double> Tri,Tr2,Tr1;

	Tri.setCopy(B);
	Tri.showfull_infile("TrB.txt");

	Tri.separation(Tr1,Tr2,6);

	Tr1.showfull_infile("TrB1.txt");
	Tr2.showfull_infile("TrB2.txt");

	Tri.setCopy(A);
	Tri.showfull_infile("TrA.txt");

}

#endif
