#include "datatypes.h"
#include <QtAlgorithms>

/*template<class N,class E>
void Graph<N,E>::AddNode(Node<N> & node)
{
	int ii;
	ii	= Nodes.size();
	Nodes.append(node);
	Nodes.back().self_id	= ii;
}

template<class N,class E>
void Graph<N,E>::InitNodes(int k)
{
	int jj	=  Nodes.size();
	k		+= jj;
	Nodes.resize(k);
	for(;jj<k;++jj)
	{
		Nodes[jj].self_id	= jj;
		Nodes[jj].NodeObject	= 0x0;
	}
}
/*
template<class N,class E>
QVector<int> Graph<N,E>::AddNode(Node<N> & new_node,QVector<int> & old_nodes)	// добавить узел к указанным узлам, возвращает массив несуществующих узлов, если таковые указаны в old_nodes
{
	qSort(old_nodes);
}*/
template<class T>
SparseMatrix::SparseMatrix(const int n,const int m)
{
	M = m;
	N = n;
	id.resize(M);
	for(int jj = 0;jj<M;++jj) id[jj]	= -1;
}

template<class T>
SparseMatrix::SparseMatrix(SparseMatrix &r)
{
	elements	= r.elements;
	id			= r.id;
	//rows		= r.rows;
	N			= r.N;
	M			= r.M;
}

template<class T>
SparseMatrix::SparceMatrix(const int n/*,const Qvector<int> rows_in*/,const QVector<QVector<int> > id_in,const QVector<T> elements_in)
{
	N	= n;
	M	= m;
	//rows	= rows_in;
	id		= id_in;
	elements= elements_in;
}

template<class T>
T & SparseMatrix::getElement(const int m,const int n,const T &r)
{
	if(id[m]isEmpty())
	{
		return r = 0;
	}
	else
	{
		int ii,jj,kk;
		jj	= id[m].size();
		kk	= id[m][0];
		for(ii=1;(ii<jj)&&(id[m][ii]<n);++ii);
		if (id[m][ii]==n)
		{
			--kk	+= ii;
			return r	= elements[kk];
		}
	}
}
template<class T>
T & SparseMatrix::setElement(const int m,const int n,const T &r)
{

}
