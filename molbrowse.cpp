#ifndef MOLBROWSE_CPP
#define MOLBROWSE_CPP


//#include <QString>
//#include <QtAlgorithms>
//#include <QVariant>
//#include <QAbstractItemModel>
//#include <QModelIndex>
//#include <QList>
#include <QKeyEvent>
#include <QAction>
#include <QMenu>
#include <QColorDialog>

#include "molbrowse.h"
#include "datatypes.h"
#include "rdwrfls.h"

/*Node::Node()
{
	parent = 0;
}

Node::Node(Type type, const QString &str)
{
	this->type = type;
	this->str  = str;
	parent = 0;
}

Node::~Node()
{
	qDeleteAll(children);
}

BrowseModel::BrowseModel(QObject *parent) : QAbstractItemModel(parent)
{
	rootNode = 0;
}

BrowseModel::~BrowseModel()
{
	delete rootNode;
}

void BrowseModel::setRootNode(Node *node)
{
	delete rootNode;
	rootNode = node;
	reset(); // вызывается для уведомления всех представлений о необходимости обновления отображаемых данных всеми видимыми элементами
	// reset() - фукция-член класса QAbstractItemModel ( void QAbstractItemModel::reset ()   [protected] )
}

QModelIndex BrowseModel::index(int row, int column, const QModelIndex &parent) const
{
	if(rootNode || row<0 || column < 0 ) return QModelIndex(); // вернуть недействительный индекс  QModelIndex
	Node *parentNode = nodeFromIndex(parent);
	Node *childNode = parentNode->children.value(row);
	if (!childNode) return QModelIndex();
	return createIndex(row,column,childNode);
}

Node * BrowseModel::nodeFromIndex(const QModelIndex &index) const
{
	if (index.isValid())
	{
		return static_cast<Node *> (index.internalPointer());
	}else
	{
		return rootNode;
	}
}

int BrowseModel::rowCount(const QModelIndex &parent) const
{
	if(parent.column()>0) return 0;
	Node *parentNode = nodeFromIndex(parent);
	if(!parentNode) return 0;
	return parentNode->children.count();
}

int BrowseModel::columnCount(const QModelIndex &parent) const
{
	return 2;
}

QModelIndex BrowseModel::parent(const QModelIndex &child) const
{
	Node *node = nodeFromIndex(child);
	if (!node) return QModelIndex();
	Node *parentNode = node->parent;
	if(!parentNode) return QModelIndex();
	Node *grandparentNode = parentNode->parent;
	if(!grandparentNode) return QModelIndex();

	int row = grandparentNode->children.indexOf(parentNode);
	return createIndex(row, 0,parentNode);
}

QVariant BrowseModel::data(const QModelIndex &index, int role) const
{
	if(role != Qt::DisplayRole) return QVariant();

	Node* node = nodeFromIndex(index);
	if(!node) return QVariant();

	if (index.column()==0)
	{
		switch (node->type)
		{
		case Node::Root :
			return tr("Root");
		case Node::Surface :
			return tr("Surface");
		case Node::Area :
			return tr("Area");
		case Node::Supra :
			return tr("Supra");
		case Node::Complex :
			return tr("Complex");
		case Node::Protein :
			return tr("Protein");
		case Node::Ligand :
			return tr("Ligand");
		case Node::Molecule :
			return tr("Molecule");
		case Node::Bound :
			return tr("Boundary");
		case Node::Atom :
			return tr("Atom");
		}
	}else if (index.column()==1) return node->str;
	return QVariant();
}

QVariant BrowseModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
	{
		if (section == 0) return tr("Molecula`s objects");
		else if (section == 1) return tr("Content");
	}
	return QVariant();
}*/

#include <QStringList>

//#include "treeitem.h"

TreeItem::TreeItem(const QList<QVariant> &data, TreeItem *parent)
{
    parentItem = parent;
    itemData = data;
}

TreeItem::TreeItem(const Type &typ, TreeItem *parent)
{
    parentItem = parent;
    type = typ;
	switch (type)
	{
		case TreeItem::Root :
			itemData	<< QObject::tr("Structure")<<QObject::tr("Content")<<QObject::tr("Data");//<<QObject::tr("Data");
			break;
		case TreeItem::Surface :
			itemData	<< QObject::tr("Surface");
			break;
		case TreeItem::Area :
			itemData	<< QObject::tr("Area");
			break;
		case TreeItem::Supra :
			itemData	<< QObject::tr("Supra");
			break;
		case TreeItem::Complex :
			itemData	<< QObject::tr("Complex");
			break;
		case TreeItem::Protein :
			itemData	<< QObject::tr("Protein");
			break;
		case TreeItem::Ligand :
			itemData	<< QObject::tr("Ligand");
			break;
		case TreeItem::Molecule :
			itemData	<< QObject::tr("Molecule");
			break;
		case TreeItem::Bound :
			itemData	<< QObject::tr("Boundary");
			break;
		case TreeItem::Atom :
			itemData	<< QObject::tr("Atom");
			break;
		case TreeItem::Chain :
			itemData	<< QObject::tr("Chain");
			break;
		case TreeItem::AminoAcid :
			itemData	<< QObject::tr("AminoAcid");
			break;
	}
}

TreeItem::TreeItem(const Type &typ, const QList<QVariant> &data, TreeItem *parent)
{
	parentItem = parent;
	type = typ;
	switch (type)
	{
		case TreeItem::Surface :
			itemData	<< QObject::tr("Surface") << data;
			break;
		case TreeItem::Area :
			itemData	<< QObject::tr("Area")  << data;
			break;
		case TreeItem::Supra :
			itemData	<< QObject::tr("Supra") << data;
			break;
		case TreeItem::Complex :
			itemData	<< QObject::tr("Complex") << data;
			break;
		case TreeItem::Protein :
			itemData	<< QObject::tr("Protein") << data;
			break;
		case TreeItem::Ligand :
			itemData	<< QObject::tr("Ligand") << data;
			break;
		case TreeItem::Molecule :
			itemData	<< QObject::tr("Molecule") << data;
			break;
		case TreeItem::Bound :
			itemData	<< QObject::tr("Boundary") << data;
			break;
		case TreeItem::Atom :
			itemData	<< QObject::tr("Atom") << data;
			break;
		case TreeItem::Chain :
			itemData	<< QObject::tr("Chain") << data;
			break;
		case TreeItem::AminoAcid :
			itemData	<< QObject::tr("AminoAcid") << data;
			break;
	}    
}

TreeItem::~TreeItem()
{
    qDeleteAll(childItems);
}

void TreeItem::appendChild(TreeItem *item)
{
    childItems.append(item);	// в список указателей дочерних узлов добавляется ещё один указатель
}

/*void TreeItem::clearChild()
{
	qDeleteAll(childItems);
}/**/
TreeItem *TreeItem::child(int row) // возвращет указательна дочерний узел с номером row
{
    return childItems.value(row);
}

int TreeItem::childCount() const // возвращает количество дочерних узлов
{
    return childItems.count();
}

int TreeItem::columnCount() const // возвращает количество данных в текущем узле
{
    return itemData.count();
}

QVariant TreeItem::data(int column) const // возвращет данные с номером column в текущем узле 
{
    return itemData.value(column);
}

TreeItem *TreeItem::parent() // возвращет указатель на вышний уровень (родительский)
{
    return parentItem;
}

int TreeItem::row() const // возвращет номер текущего узла в массиве дочерних узлов родительского уровня
{
    if (parentItem)
        return parentItem->childItems.indexOf(const_cast<TreeItem*>(this));

    return 0;
}



TreeModel::TreeModel(const QString &data, QObject *parent)
    : QAbstractItemModel(parent)
{
    QList<QVariant> rootData;
    rootData << tr("Title") << tr("Summary");
    rootItem = new TreeItem(rootData);
    setupModelData(data.split(QString("\n")), rootItem);
}

TreeModel::TreeModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    QList<QVariant> rootData;
    //rootData << "Molecule`s Structure" << "Content";
	rootItem = new TreeItem(TreeItem::Root);
	//rootItem->type = TreeItem::Root;
    //setupModelData(data.split(QString("\n")), rootItem);
}


TreeModel::~TreeModel()
{
    delete rootItem;
}

void TreeModel::setWF(WorkFrame *in_wf)
{
	WF=in_wf;
}
int TreeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
    else
        return rootItem->columnCount();
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());

    return item->data(index.column());
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent)
            const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    TreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem *parentItem = childItem->parent();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
    TreeItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    return parentItem->childCount();
}

void TreeModel::setupModelData(const QStringList &lines, TreeItem *parent)
{
    QList<TreeItem*> parents;
    QList<int> indentations;
    parents << parent;
    indentations << 0;

    int number = 0;

    while (number < lines.count()) {
        int position = 0;
        while (position < lines[number].length()) {
            if (lines[number].mid(position, 1) != " ")
                break;
            position++;
        }

        QString lineData = lines[number].mid(position).trimmed();

        if (!lineData.isEmpty()) {
            // Read the column data from the rest of the line.
            QStringList columnStrings = lineData.split("\t", QString::SkipEmptyParts);
            QList<QVariant> columnData;
            for (int column = 0; column < columnStrings.count(); ++column)
                columnData << columnStrings[column];

            if (position > indentations.last()) {
                // The last child of the current parent is now the new parent
                // unless the current parent has no children.

                if (parents.last()->childCount() > 0) {
                    parents << parents.last()->child(parents.last()->childCount()-1);
                    indentations << position;
                }
            } else {
                while (position < indentations.last() && parents.count() > 0) {
                    parents.pop_back();
                    indentations.pop_back();
                }
            }

            // Append a new item to the current parent's list of children.
            parents.last()->appendChild(new TreeItem(columnData, parents.last()));
        }

        number++;
    }
}

void TreeModel::setUpModelData()//const Molecule &mol,SmplTpzlTable &tbl)
{
	QList<TreeItem*> parents;
    parents << rootItem;
	QString nstr,nstr1;

	//TreeItem* pxx;

	QList<QVariant> sdt,sdt1;
	char xx[3];

	xx[2] = '\0';
	//pxx	= parents.last();

	beginResetModel();

	for(int j=0;j<WF->Mls.N;j++) // проход по всем молекулам
	{
		if(WF->Mls.x[j]->mol_type==UNDEFINED)
		{
			sdt.clear();
			nstr	= QString("%1").arg(j+1);
			sdt<<nstr;
			//nstr.append(QString().setNum(WF->Mls.x[j]->Atoms.N,10));
			//nstr.append(") ");
			//sdt<<WF->Mls.x[j]->Atoms.N;//nstr;
			nstr	= QString("%1").arg(WF->Mls.x[j]->Atoms.N);
			nstr.append(QString(" ("));
			nstr.append(QString(tr(WF->Mls.x[j]->Name.x)));
			nstr.append(QString(")"));
			sdt<<nstr;
			//nstr.append(" (");
			//sdt<<QObject::tr(" ");
			//sdt<<QObject::tr(WF->Mls.x[j]->Name.x);


			parents.last()->appendChild(new TreeItem(TreeItem::Molecule,sdt,parents.last()));
			parents<<parents.last()->child(parents.last()->childCount()-1);

			for(int i=0;i<WF->Mls.x[j]->Atoms.N;i++)
			{
				sdt.clear();
				xx[0] = WF->TableZR.Lines.x[WF->Mls.x[j]->Atoms.x[i].id_Tpz].Ch.x[0];
				xx[1] = WF->TableZR.Lines.x[WF->Mls.x[j]->Atoms.x[i].id_Tpz].Ch.x[1];	
				//nstr1.clear();
				nstr1=QObject::tr(xx);
				sdt<<nstr1;
				//nstr1.append(' ');
				//nstr1.append(QString().setNum(i+1,10));
				sdt<<(i+1);//nstr1;
				parents.last()->appendChild(new TreeItem(TreeItem::Atom,sdt,parents.last()));
			}
			parents<<parents.last()->parent();
		}
		if (WF->Mls.x[j]->mol_type==PROTEINE)
		{
			sdt.clear();
			nstr	= QString("%1").arg(j+1);
			//nstr.append(" (");
			sdt<<nstr;
			//nstr.append(QString().setNum(WF->Mls.x[j]->Atoms.N,10));
			//nstr.append(") ");
			//sdt<<WF->Mls.x[j]->Atoms.N;//nstr;
			//sdt<<WF->Mls.x[j]->Atoms.N;
			nstr	= QString("%1").arg(WF->Mls.x[j]->Atoms.N);
			nstr.append(QString(" ("));
			nstr.append(QString(tr(WF->Mls.x[j]->Name.x)));
			nstr.append(QString(")"));
			sdt<<nstr;
			//sdt<<WF->Mls.x[j]->chains.N;
			//sdt<<QObject::tr(" ");
			//sdt<<QObject::tr(WF->Mls.x[j]->Name.x);


			parents.last()->appendChild(new TreeItem(TreeItem::Protein,sdt,parents.last()));
			parents<<parents.last()->child(parents.last()->childCount()-1);
			protein_node * p_prt = WF->Mls.x[j]->p_prt;
			chain_node* p_chs;
			amino_node* p_amn;
			atom_node * p_atm;
			for(int i=0;i<p_prt->childs.N;i++)
			{
				sdt.clear();
				//nstr	= QString("chain ");
				p_chs	= p_prt->getChild(i);
				nstr1	= QString(p_chs->ch);
				nstr1.append(QString("  %1").arg(p_chs->id+1));
				//nstr<<nstr1;
				//xx[0] = WF->TableZR.Lines.x[WF->Mls.x[j]->Atoms.x[i].id_Tpz].Ch.x[0];
				//xx[1] = WF->TableZR.Lines.x[WF->Mls.x[j]->Atoms.x[i].id_Tpz].Ch.x[1];	
				//nstr1.clear();
				//nstr1=QObject::tr(xx);
				sdt<<nstr1;
				//nstr1.append(' ');
				//nstr1.append(QString().setNum(i+1,10));
				//sdt<<(i+1);//nstr1;
				if(p_chs->childs.N>0)
				{
					sdt<<p_chs->childs.N;// WF->Mls.x[j]->chains.x[i].N;
					parents.last()->appendChild(new TreeItem(TreeItem::Chain,sdt,parents.last()));
					parents<<parents.last()->child(parents.last()->childCount()-1);

					for(int k=0;k<p_chs->childs.N;k++)
					{
						p_amn	= p_chs->getChild(k);
						if(p_amn->childs.N>0)//WF->Mls.x[j]->chains.x[i].x[k].Atoms_id.N>0)
						{
							sdt.clear();
							nstr1	= QString::fromLatin1(p_amn->name.x,3);//WF->Mls.x[j]->chains.x[i].x[k].amin_ch.x,3);
							nstr1.append(" ");
							nstr1.append(QString("%1").arg((p_amn->id_ch)));//WF->Mls.x[j]->chains.x[i].x[k].id)));
							sdt<<nstr1;
							sdt<<(k+1);//WF->Mls.x[j]->chains.x[i].x[k].Atoms_id.N;//nstr1;
							parents.last()->appendChild(new TreeItem(TreeItem::AminoAcid,sdt,parents.last()));
							parents<<parents.last()->child(parents.last()->childCount()-1);
							for(int q=0;q<p_amn->childs.N;q++)//WF->Mls.x[j]->chains.x[i].x[k].Atoms_id.N;q++)
							{
								int p;
								sdt.clear();
								p_atm	= p_amn->getChild(q);
								p	= p_atm->atom->id_Tot;//WF->Mls.x[j]->chains.x[i].x[k].Atoms_id.x[q];
								xx[0] = WF->TableZR.Lines.x[p_atm->atom->id_Tpz].Ch.x[0];
								xx[1] = WF->TableZR.Lines.x[p_atm->atom->id_Tpz].Ch.x[1];	
								//nstr1.clear();
								nstr1=QObject::tr(xx);
								nstr1.append(" (");
								nstr1.append(p_atm->name.x);
								nstr1.append(")");
								sdt<<nstr1;
								//nstr1.append(' ');
								//nstr1.append(QString().setNum(i+1,10));
								sdt<<(p+1);//nstr1;
								parents.last()->appendChild(new TreeItem(TreeItem::Atom,sdt,parents.last()));
							}
						}

						parents<<parents.last()->parent();
					}

					parents<<parents.last()->parent();
				}
			}
			parents<<parents.last()->parent();
		}
		if (WF->Mls.x[j]->mol_type==LIGAND)
		{
			sdt.clear();
			nstr	= QString("%1").arg(j+1);
			//nstr.append(" (");
			sdt<<nstr;
			//nstr.append(QString().setNum(WF->Mls.x[j]->Atoms.N,10));
			//nstr.append(") ");
			//sdt<<WF->Mls.x[j]->Atoms.N;//nstr;
			nstr	= QString("%1").arg(WF->Mls.x[j]->Atoms.N);
			nstr.append(QString(" ("));
			nstr.append(QString(tr(WF->Mls.x[j]->Name.x)));
			nstr.append(QString(")"));
			sdt<<nstr;
			//sdt<<QObject::tr(" ");
			//sdt<<QObject::tr(WF->Mls.x[j]->Name.x);


			parents.last()->appendChild(new TreeItem(TreeItem::Ligand,sdt,parents.last()));
			parents<<parents.last()->child(parents.last()->childCount()-1);

			for(int i=0;i<WF->Mls.x[j]->Atoms.N;i++)
			{
				sdt.clear();
				xx[0] = WF->TableZR.Lines.x[WF->Mls.x[j]->Atoms.x[i].id_Tpz].Ch.x[0];
				xx[1] = WF->TableZR.Lines.x[WF->Mls.x[j]->Atoms.x[i].id_Tpz].Ch.x[1];	
				//nstr1.clear();
				nstr1=QObject::tr(xx);
				sdt<<nstr1;
				//nstr1.append(' ');
				//nstr1.append(QString().setNum(i+1,10));
				sdt<<(i+1);//nstr1;
				parents.last()->appendChild(new TreeItem(TreeItem::Atom,sdt,parents.last()));
			}
			parents<<parents.last()->parent();
		}
	}
	for(int j=0;j<WF->Srfcs.N;j++) // проход по всем поеверхностям
	{
		sdt.clear();
		nstr	= QString("%1").arg(j+1);
		sdt<<nstr;
		//sdt<<WF->Mls.x[j]->Atoms.N;//nstr;
		//sdt<<QObject::tr(" ");
		//sdt<<QObject::tr(WF->Mls.x[j]->Name.x);


		parents.last()->appendChild(new TreeItem(TreeItem::Surface,sdt,parents.last()));
		//parents<<parents.last()->child(parents.last()->childCount()-1);
	
		/*for(int i=0;i<WF->Mls.x[j]->Atoms.N;i++)
		{
			sdt.clear();
			xx[0] = WF->TableZR.Lines.x[WF->Mls.x[j]->Atoms.x[i].id_Tpz].Ch.x[0];
			xx[1] = WF->TableZR.Lines.x[WF->Mls.x[j]->Atoms.x[i].id_Tpz].Ch.x[1];	
			//nstr1.clear();
			nstr1=QObject::tr(xx);
			sdt<<nstr1;
			//nstr1.append(' ');
			//nstr1.append(QString().setNum(i+1,10));
			sdt<<(i+1);//nstr1;
			parents.last()->appendChild(new TreeItem(TreeItem::Atom,sdt,parents.last()));
		}*/
		//parents<<parents.last()->parent();
	}
	endResetModel();
	//reset();
    //int number = 0;
}

void TreeModel::updateModel()//const Molecule &mol,SmplTpzlTable &tbl)	// обновить данные
{
	delete rootItem;

	rootItem = new TreeItem(TreeItem::Root);

	setUpModelData();//mol,tbl);
}

void TreeModel::clearAllModelData()
{
	//parents
}/**/

TreeView::TreeView(QWidget *parent) : QTreeView(parent)
{
	setSelectionMode(QAbstractItemView::ExtendedSelection);
	setSelectionBehavior(QAbstractItemView::SelectRows);


	contextMenu1	= new QMenu(this);

	contextselectAction1	= new QAction(tr("&Select on 3D scene"),this);
	connect(contextselectAction1,SIGNAL(triggered()),this,SLOT(markAnalize()));
	
	contextMenu1->addAction(contextselectAction1);

	contextMenu2	= new QMenu(this);

	contextselectAction2_1	= new QAction(tr("&Select on 3D scene"),this);
	connect(contextselectAction2_1,SIGNAL(triggered()),this,SIGNAL(selectMol()));

	contextselectAction2_2	= new QAction(tr("&Change drawing type"),this);
	connect(contextselectAction2_2,SIGNAL(triggered()),this,SIGNAL(changeMol()));

	contextMenu2->addAction(contextselectAction2_1);
	contextMenu2->addAction(contextselectAction2_2);

	contextMenu3	= new QMenu(this);

	contextselectAction3_1	= new QAction(tr("&Hide Surface"),this);
	connect(contextselectAction3_1,SIGNAL(triggered()),this,SLOT(hideSurf()));
	
	contextselectAction3_2	= new QAction(tr("&Solid Surface"),this);
	connect(contextselectAction3_2,SIGNAL(triggered()),this,SLOT(solidSurf()));

	contextselectAction3_3	= new QAction(tr("&Wireframe Surface"),this);
	connect(contextselectAction3_3,SIGNAL(triggered()),this,SLOT(wireframeSurf()));

	contextselectAction3_4	= new QAction(tr("&Delete Surface"),this);
	connect(contextselectAction3_4,SIGNAL(triggered()),this,SLOT(deleteSurf()));

	contextselectAction3_5	= new QAction(tr("&Transparence Surface"),this);
	connect(contextselectAction3_5,SIGNAL(triggered()),this,SLOT(transparenceSurf()));

	colorAction1	= new QAction(tr("&Select Surface Color"),this);
	connect(colorAction1,SIGNAL(triggered()),this,SLOT(singleColor()));
	colorAction2	= new QAction(tr("&By Atoms "),this);
	connect(colorAction2,SIGNAL(triggered()),this,SLOT(atomsColor()));
	colorAction3	= new QAction(tr("By Topologic &Fragments"),this);
	connect(colorAction3,SIGNAL(triggered()),this,SLOT(typeColor()));



	contextMenu3->addAction(contextselectAction3_1);
	contextMenu3->addAction(contextselectAction3_2);
	contextMenu3->addAction(contextselectAction3_3);
	contextMenu3->addAction(contextselectAction3_5);
	contextMenu3->addAction(contextselectAction3_4);
	contextMenu3->addSeparator();

	colorMenu	= contextMenu3->addMenu(tr("&Color Setting"));
	colorMenu->addAction(colorAction1);
	colorMenu->addAction(colorAction2);
	colorMenu->addAction(colorAction3);


	contextMenu4	= new QMenu(this);

	contextselectAction4	= new QAction(tr("&Select on 3D scene"),this);
	connect(contextselectAction4,SIGNAL(triggered()),this,SLOT(markAnalize4()));
	contextMenu4->addAction(contextselectAction4);
	
	contextMenu5	= new QMenu(this);

	contextselectAction5	= new QAction(tr("&Select on 3D scene"),this);
	connect(contextselectAction5,SIGNAL(triggered()),this,SLOT(markAnalize5()));
	contextMenu5->addAction(contextselectAction5);


	s_type	= -1;
	ida.N	= 0;
	ids.N	= 0;
}

void TreeView::hideSurf()
{
	markSurfAnalize();
	s_type	= 0;
	emit changeSurf();
}

void TreeView::solidSurf()
{
	markSurfAnalize();
	s_type	= 1;
	emit changeSurf();
}

void TreeView::wireframeSurf()
{
	markSurfAnalize();
	s_type	= 2;
	emit changeSurf();
}

void TreeView::deleteSurf()
{
	markSurfAnalize();
	s_type	= 3;
	emit changeSurf();
}
void TreeView::transparenceSurf()
{
	markSurfAnalize();
	s_type	= 4;
	emit changeSurf();
}

void TreeView::singleColor()
{
	markSurfAnalize();
	QColor color	= QColorDialog::getColor();
	if(color.isValid())
	{
		col.x[0]	= color.red();
		col.x[1]	= color.green();
		col.x[2]	= color.blue();
		emit changecolorSurf();
	}
}

void TreeView::atomsColor()
{
	markSurfAnalize();
	col	= -1;
	emit changecolorSurf();
}

void TreeView::typeColor()
{
	markSurfAnalize();
	col	= -2;
	emit changecolorSurf();
}

//void TreeView::mouseReleaseEvent( QMouseEvent *event
void TreeView::mouseDoubleClickEvent( QMouseEvent *event)
{
	if (event->buttons()&Qt::LeftButton)
	{
		clearSelection();
		update();
		resize(width()+1,height());
		resize(width()-1,height());
	}
}

//void TreeView::selectionChanged ( const QItemSelection & selected, const QItemSelection & deselected )
//{
	// анализ выбрираемых пунтов меню. Цель - выбираться должны только однотипные пункты (либо только атомы, либо только молекулы, либо только поверхности и т.д.)
	// приоритет выбора - по первому выбранному элементу. Если первый выбраный атом - то в дальнейшем выбирать только атомы, если молекула - то отмечать молекулы, и т.д.
/*	if((deselected.isEmpty())&&(selected.length()==1)) // анализ при первом выборе
	{
		// при первом выборе элемента нужно замопнить его тип.
		loc_item		= selected.indexes().at(0);
	}else
	{
		/*int ii;
		QString str;
		str	= loc_item.data().toString();
		QModelIndex mindx;
		for(ii=selected.indexes().length();ii>=0;ii++)
		{
			if(selected.indexes().at(ii).data().toString()!=str)
			{
				mindx	= selected.indexes().at(ii);
				//deselected.select(mindx,mindx);
			}
		}*/
//	}
//}

void TreeView::contextMenuEvent(QContextMenuEvent *e)
{	
	indexlist	= selectedIndexes();
	// в зависимости от того какие выбраны пункты выдаётся тот или иной тип контекстного меню
	// типы контектных меню: 1 меню для атомов, 2 меню для аминокислот, 3 меню для молекул, 4 меню для поверхностей
	//
	if (!indexlist.isEmpty())
	{
		if(indexlist.length()==3)
		{
			//contextMenu2->exec(QCursor::pos());
			if(indexlist.at(0).data().toString()==QString("Chain"))
			{
				contextMenu4->exec(QCursor::pos());
			}
			if(indexlist.at(0).data().toString()==QString("AminoAcid"))
			{
				contextMenu5->exec(QCursor::pos());
			}
			if(indexlist.at(0).data().toString()==QString("Atom"))
			{
				contextMenu1->exec(QCursor::pos());
			}else
			{
				if((indexlist.at(0).data().toString()==QString("Molecule"))||(indexlist.at(0).data().toString()==QString("Ligand"))||(indexlist.at(0).data().toString()==QString("Protein")))
				{
					vec2int id;
					//int tt=1;
					ida.N	=0;
					id.x[0]	= indexlist.at(0).row();
					id.x[1] = 0;
					ida.add(id);
					contextMenu2->exec(QCursor::pos());
				}
				else
				{
					if(indexlist.at(0).data().toString()==QString("Surface"))
					{
						contextMenu3->exec(QCursor::pos());
					}
				}
			}
		}else
		{
			if(indexlist.at(0).data().toString()==QString("Chain"))
			{
				contextMenu4->exec(QCursor::pos());
			}
			if(indexlist.at(0).data().toString()==QString("AminoAcid"))
			{
				contextMenu5->exec(QCursor::pos());
			}
			if(indexlist.at(0).data().toString()==QString("Surface"))
			{
					contextMenu3->exec(QCursor::pos());
			}else
			{
				if(indexlist.at(0).data().toString()==QString("Atom"))
				{
					contextMenu1->exec(QCursor::pos());
				}
			}
		}
	}
}

/*void TreeView::selready()
{
	int i;
	i=0;
}*/

void TreeView::markAnalize()
{
	// определить типы отмеченых пунктов
	// идентификатор типа пункта - имя; 

	QModelIndexList selindexlist;

	selindexlist	= selectedIndexes();

	int i1,j1,j2,k1;
	QString str,strA("Atom"),strAmn("AminoAcid"),strCh("Chain"),strPr("Protein"),strLig("Ligand"),strMol("Molecule");
	QVariant data;
	QModelIndex parent,child;
	vec2int id;

	int ny,rw;

	//nx	= 3;
	ny	= selindexlist.length();///nx;

	ida.N	= 0;
	for(i1=0;i1<ny;i1++)
	{
		//j2	= indexlist.at(i1).row();
		//if(j2==0)
		//{
			data	= indexlist.at(i1).data();
			str	= data.toString();
			if(str == strA)
			{	
				rw		= indexlist.at(i1).row();
				child	= indexlist.at(i1).sibling(rw,2);
				id.x[1]	= child.data().toInt()-1;
				parent	= indexlist.at(i1).parent();
				data	= parent.data();
				str		= data.toString();
				if((str	== strMol)||(str == strLig))
				{
					id.x[0]	= parent.row();
					ida.add(id);
				}else
				{
					if(str	== strAmn)
					{
						parent	= parent.parent();
						data	= parent.data();
						str		= data.toString();
						if(str	== strCh)
						{
							parent	= parent.parent();
							data	= parent.data();
							str		= data.toString();
							if(str	== strPr)
							{
								rw	= parent.row();
								child	= parent.sibling(rw,1);
								id.x[0]	= child.data().toInt()-1;
								ida.add(id);
							}
						}
					}
				}

			}
		//}
		//k1	= data.toInt();
	}


	clearSelection();
	update();
	resize(width()+1,height());
	resize(width()-1,height());

	/*QModelIndex parent;
	
	indexlist	= getselitems();
	int i1,j1,j2,k1;
	
	vecT<vec2int> br_sel;
	vec2int loc;

	vecT<void *> ptr;
	vecT<int>	id_p;

	void * h_p;

	k1	= indexlist.length();
	for(i1=0;i1<k1;i1++)
	{
		ptr.add(indexlist.at(i1).parent().internalPointer());
	}
	i1--;
	id_p.var1D(0,1,i1);
	ptr.sort_(id_p);

	h_p	= ptr.x[0];
	for(i1=0;i1<id_p.N;i1++)
	{
		k1	= id_p.x[i1];
		parent	= indexlist.at(k1).parent();
		j1	= indexlist.at(i1).column();
		j2	= indexlist.at(i1).row();
		data	= indexlist.at(i1).data();
		//k1	= data.toInt();
		str	= data.toString();
	}*/
	emit selready();
}

void TreeView::markAnalize4()
{
	// определить типы отмеченых пунктов
	// идентификатор типа пункта - имя; 

	int i1,j1;
	QString str,strAmn("AminoAcid"),strCh("Chain"),strPr("Protein");
	QVariant data;
	QModelIndex parent,child;
	vec2int id;

	int ny,rw;

	ny	= indexlist.length();///nx;

	ida.N	= 0;
	for(i1=0;i1<ny;i1++)
	{
		data	= indexlist.at(i1).data();
		str	= data.toString();

		if(str	== strCh)
		{
			//id.x[2]	= parent.row();
			parent	= indexlist.at(i1).parent();
			data	= parent.data();
			str		= data.toString();
			if(str	== strPr)
			{
				rw	= parent.row();
				child	= parent.sibling(rw,1);
				id.x[0]	= child.data().toInt()-1;
				//rw	= indexlist.at(i1).row();
				//for(int jj=0;jj<rw;jj++)
				rw	= 0;
				while(indexlist.at(i1).child(rw,0).isValid())
				{
					child	= indexlist.at(i1).child(rw,0);
					str		= child.data().toString();
					j1	=0;
					while(child.child(j1,2).isValid())
					{
						id.x[1] = child.child(j1,2).data().toInt()-1;
						ida.add(id);
						j1++;
					}
					rw++;
				}
			}
		}

		/*data	= indexlist.at(i1).data();
		str	= data.toString();
		if(str == strCh)
		{	
			id.x[1]	= indexlist.at(i1).row();
			parent	= indexlist.at(i1).parent();
			data	= parent.data();
			str		= data.toString();
			if(str	== strPr)
			{
				rw	= parent.row();
				child	= parent.sibling(rw,1);
				id.x[0]	= child.data().toInt()-1;
				ida.add(id);
			}
		}*/
	}


	clearSelection();
	update();
	resize(width()+1,height());
	resize(width()-1,height());


	emit selready();
}

void TreeView::markAnalize5()
{
		// определить типы отмеченых пунктов
	// идентификатор типа пункта - имя; 

	int i1;
	QString str,strAmn("AminoAcid"),strCh("Chain"),strPr("Protein");
	QVariant data;
	QModelIndex parent,child;
	//vec3int id;
	vec2int id;

	int ny,rw;

	ny	= indexlist.length();///nx;

	ida.N	= 0;
	for(i1=0;i1<ny;i1++)
	{
		data	= indexlist.at(i1).data();
		str	= data.toString();
		if(str == strAmn)
		{	
			//id.x[1]	= indexlist.at(i1).row();
			parent	= indexlist.at(i1).parent();
			data	= parent.data();
			str		= data.toString();

			if(str	== strCh)
			{
				//id.x[2]	= parent.row();
				parent	= parent.parent();
				data	= parent.data();
				str		= data.toString();
				if(str	== strPr)
				{
					rw	= parent.row();
					child	= parent.sibling(rw,1);
					id.x[0]	= child.data().toInt()-1;
					//rw	= indexlist.at(i1).row();
					//for(int jj=0;jj<rw;jj++)
					rw	= 0;
					while(indexlist.at(i1).child(rw,2).isValid())
					{
						id.x[1] = indexlist.at(i1).child(rw,2).data().toInt()-1;
						ida.add(id);
						rw++;
					}
				}
			}
		}
/*		data	= indexlist.at(i1).data();
		str	= data.toString();
		if(str == strAmn)
		{	
			id.x[2]	= indexlist.at(i1).row();
			parent	= indexlist.at(i1).parent();
			data	= parent.data();
			str		= data.toString();

			if(str	== strCh)
			{
				id.x[2]	= parent.row();
				parent	= parent.parent();
				data	= parent.data();
				str		= data.toString();
				if(str	== strPr)
				{
					rw	= parent.row();
					child	= parent.sibling(rw,1);
					id.x[0]	= child.data().toInt()-1;
					idam.add(id);
				}
			}

			if(str	== strPr)
			{
				rw	= parent.row();
				child	= parent.sibling(rw,1);
				id.x[0]	= child.data().toInt()-1;
				ida.add(id);
			}
		}
		*/
	}

	clearSelection();
	update();
	resize(width()+1,height());
	resize(width()-1,height());

	emit selready();
}

void TreeView::markSurfAnalize()
{
	QModelIndexList selindexlist;

	selindexlist	= selectedIndexes();

	int i1,j1,j2,k1;
	QString str,strS("Surface");
	QVariant data;
	QModelIndex parent;
	int id;

	ids.N	= 0;
	j1		= selindexlist.length();
	k1		= j1/3;

	for(i1=0;i1<k1;i1++)
	{
		data	= indexlist.at(i1).data();
		str	= data.toString();
		if(str == strS)
		{
			j2	= i1 + k1;
			data	= indexlist.at(j2).data();
			id	= data.toInt();
			ids.add(--id);
		}
	}
	
	clearSelection();
	update();
	resize(width()+1,height());
	resize(width()-1,height());
}


#endif