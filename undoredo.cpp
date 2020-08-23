#ifndef UNDOREDO_CPP
#define UNDOREDO_CPP


#include <QAction>
#include <QLabel>
#include <QString>
#include <QVBoxLayout>
#include <QSplitter>

#include "undoredo.h"
#include "linalg.h"
//#include "linalg.cpp"
#include "datatypes.h"
#include "rdwrfls.h"
#include "GLframe.h"

//---------------------
CommandItem::CommandItem(const QList<QVariant> &data, CommandItem *parent)
{
	itemData	= data;
	parentItem	= parent;
}
//---------------------
CommandItem::~CommandItem()
{
    qDeleteAll(childItems);
}
//---------------------
void CommandItem::appendChild(CommandItem *child)
{
	childItems.append(child);	// добавление производиться с помощью метода класса QList
}
//---------------------
//---------------------
CommandItem *CommandItem::child(int row) // возвращает указатель на дочерний элемент с номером 'row' в списке текущего элемента
{
    return childItems.value(row);
}
//---------------------
int CommandItem::childCount() const // возвращает количество дочерних элементов
{
    return childItems.count();
}
//---------------------
int CommandItem::columnCount() const // возвращает количество столбцов
{
    return itemData.count();
}
//---------------------
QVariant CommandItem::data(int column) const // возвращает данные для столбца с номером 'column'
{
    return itemData.value(column);
}
//---------------------
CommandItem *CommandItem::parent()  // возвращает указатель на родительский элемент
{
    return parentItem;
}
//---------------------
int CommandItem::row() const  // возвращает номер текущего элемента в списке родительского
{
    if (parentItem)
        return parentItem->childItems.indexOf(const_cast<CommandItem*>(this));

    return 0;
}
//-------------------------------------------------

//---------------------
CmdTrModel::CmdTrModel(const QString &data, QObject * parent) : QAbstractItemModel(parent)
{
	QList<QVariant> rootData;
	rootData<<tr("Command")<<tr("Data")<<tr("|");
	rootItem	= new CommandItem(rootData);
	setupModelData(data.split(QString("\n")), rootItem);
}
CmdTrModel::CmdTrModel(QObject * parent) : QAbstractItemModel(parent)
{
	QList<QVariant> rootData;
	rootData<<tr("Command")<<tr("Data")<<tr("|");
	rootItem	= new CommandItem(rootData);
	//setupModelData();//data.split(QString("\n")), rootItem);
}
CmdTrModel::~CmdTrModel()
{
	delete rootItem;
}
QVariant CmdTrModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    CommandItem *item = static_cast<CommandItem*>(index.internalPointer());

    return item->data(index.column());
}
Qt::ItemFlags CmdTrModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

	return Qt::ItemIsEnabled | Qt::ItemIsSelectable ;
}

//---------------------
void CmdTrModel::setupModelData(const QStringList &lines, CommandItem *parent)
{
    QList<CommandItem*> parents;
    QList<int> indentations;
    parents << parent;
    indentations << 0;

    int number = 0;

	beginResetModel();

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
            parents.last()->appendChild(new CommandItem(columnData, parents.last()));
        }

        number++;
    }
	endResetModel();
}


QVariant CmdTrModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

QModelIndex CmdTrModel::index(int row, int column, const QModelIndex &parent)
            const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    CommandItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<CommandItem*>(parent.internalPointer());

    CommandItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex CmdTrModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    CommandItem *childItem = static_cast<CommandItem*>(index.internalPointer());
    CommandItem *parentItem = childItem->parent();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int CmdTrModel::rowCount(const QModelIndex &parent) const
{
    CommandItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<CommandItem*>(parent.internalPointer());

    return parentItem->childCount();
}

int CmdTrModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<CommandItem*>(parent.internalPointer())->columnCount();
    else
        return rootItem->columnCount();
}
//---------------------

void CmdTrModel::updateModel()//const Molecule &mol,SmplTpzlTable &tbl)	// обновить данные
{
	delete rootItem;

	QList<QVariant> rootData;
	rootData<<tr("Command")<<tr("Data")<<tr("|");

	rootItem = new CommandItem(rootData);

	setUpModelData();//mol,tbl);
}

void CmdTrModel::clearAllModelData()
{
	//parents
}/**/

void CmdTrModel::setUpModelData()
{
	QList<CommandItem*> parents;
    parents << rootItem;
	QString nstr,nstr1;

	QList<QVariant> sdt;
	QList<QString> comnms;
	QList<QString> datas;

	int i_beg,i_end,di;

	beginResetModel();

	if(!unrd)
	{
		i_beg	= UR->id_cr_op-1;
		i_end	= 0;
		di	= -1;
	}else
	{
		i_beg	= UR->id_cr_op;
		i_end	= UR->operations.N;
		di	= 1;
	}

	for(int ii=i_beg;(unrd ? ii<i_end : ii>=i_end);ii+=di)
	{
		sdt.clear();
		comnms.clear();
		datas.clear();
		switch (UR->operations.x[ii].x[0])
		{
			case   ADD_MOL :
			{
				nstr	= QString(tr("Add Molecule"));
//				comnms.append(tr("Type of molecule :"));
			//	comnms.append(tr("Molecule`s nubmer :"));
			//	datas.append(QString("%1").arg(UR->WF->Mls.N));
				//comnms.append(tr("Amoount of atoms : "));

				break;
			}
		case   DEL_MOL :
			{
				nstr	= QString(tr("Delete Molecule"));
//				comnms.append(tr("Type of molecule :"));
				comnms.append(tr("Molecule`s nubmer :"));
				datas.append(QString("%1").arg(UR->id_ml_dl_op.x[UR->operations.x[ii].x[1]]+1));
				//comnms.append(tr("Amoount of atoms : "));

				break;
			}
		case   ADD_ATM :
			{
				nstr	= QString(tr("Add Atom"));
				comnms.append(tr("Molecule`s nubmer :"));
				//comnms.append(tr("Atoms`s nubmer : "));

				datas.append(QString("%1").arg(UR->id_at_br_op.x[UR->operations.x[ii].x[1]]+1));
				//datas.append(QString("%1").arg(UR->WF->Mls.x[UR->id_at_br_op.x[UR->operations.x[ii].x[1]]]->Atoms.N));

				break;
			}
		case   DEL_ATM :
			{
				nstr	= QString(tr("Delete Atom"));
				comnms.append(tr("Molecule`s nubmer :"));
				comnms.append(tr("Atoms`s nubmer : "));

				datas.append(QString("%1").arg(UR->id_at_dl_op.x[UR->operations.x[ii].x[1]].x[0]+1));
				datas.append(QString("%1").arg(UR->id_at_dl_op.x[UR->operations.x[ii].x[1]].x[1]+1));

				break;
			}
		case   ADD_BND :
			{
				nstr	= QString(tr("Add Bond"));
				comnms.append(tr("Molecule`s nubmer :"));
				comnms.append(tr("Nubmers of atoms :"));
				
				datas.append(QString("%1").arg(UR->id_bn_br_op.x[UR->operations.x[ii].x[1]].x[0]+1));
				datas.append(QString("%1").arg(UR->id_bn_br_op.x[UR->operations.x[ii].x[1]].x[1]+1));
				datas.last().append(QString(", %1").arg(UR->id_bn_br_op.x[UR->operations.x[ii].x[1]].x[2]+1));
				//comnms.append(tr("Nubmer of bond :"));
				break;
			}
		case   DEL_BND :
			{
				nstr	= QString(tr("Delete Bond"));
				comnms.append(tr("Molecule`s nubmer :"));
				comnms.append(tr("Nubmers of atoms :"));
				
				datas.append(QString("%1").arg(UR->id_bn_dl_op.x[UR->operations.x[ii].x[1]].x[0]+1));
				datas.append(QString("%1").arg(UR->id_bn_dl_op.x[UR->operations.x[ii].x[1]].x[1]+1));
				datas.last().append(QString(", %1").arg(UR->id_bn_dl_op.x[UR->operations.x[ii].x[1]].x[2]+1));

				break;
			}
		case   UNI_MOL :
			{
				nstr	= QString(tr("Unite Molecules"));
				comnms.append(tr("Nubmers of molecules :"));
				
				datas.append(QString("%1").arg(UR->id_ml_un_op.x[UR->operations.x[ii].x[1]].x[0]+1));
				datas.last().append(QString(", %1").arg(UR->id_ml_un_op.x[UR->operations.x[ii].x[1]].x[1]+1));
				break;
			}
		case   SEP_MOL :
			{
				nstr	= QString(tr("Split Molecule"));
				comnms.append(tr("Nubmer of molecule :"));
				comnms.append(tr("Separation atom :"));
				datas.append(QString("%1").arg(UR->id_ml_un_op.x[UR->operations.x[ii].x[1]].x[0]+1));
				datas.append(QString("%1").arg(UR->id_ml_sp_op.x[UR->operations.x[ii].x[1]]+1));
				break;
			}

		case   CHG_TYP :
			{
				nstr	= QString(tr("Change Atom Type"));
				comnms.append(tr("Nubmer of molecule :"));
				comnms.append(tr("Nubmer of atom :"));
				comnms.append(tr("Type of atom :"));
				//comnms.append(tr("Additional data"));
				datas.append(QString("%1").arg(UR->id_at_tp_op.x[UR->operations.x[ii].x[1]].x[0]+1));
				datas.append(QString("%1").arg(UR->id_at_tp_op.x[UR->operations.x[ii].x[1]].x[1]+1));
				vecT<char> ch(UR->WF->TableZR.Lines.x[ UR->id_at_tp_op.x[UR->operations.x[ii].x[1]].x[2] ].Ch.x,2);
				ch.add('\0');
				datas.append(QString(ch.x));

				break;
			}
		case   CHG_BND :
			{
				nstr	= QString(tr("Change Bond Order"));
				comnms.append(tr("Nubmer of molecule :"));
				comnms.append(tr("Nubmers of atoms :"));
				comnms.append(tr("Bond order:"));
				datas.append(QString("%1").arg(UR->id_bn_tp_op.x[UR->operations.x[ii].x[1]].x[0]+1));
				datas.append(QString("%1").arg(UR->id_bn_tp_op.x[UR->operations.x[ii].x[1]].x[1]+1));
				datas.last().append(QString(", %1").arg(UR->id_bn_tp_op.x[UR->operations.x[ii].x[1]].x[2]+1));
				datas.append(QString("%1").arg(UR->id_bn_tp_op.x[UR->operations.x[ii].x[1]].x[3]+1));
				break;
			}
		case   MOV_ATM :
			{
				nstr	= QString(tr("Move Atom"));
				comnms.append(tr("Nubmer of molecule :"));
				comnms.append(tr("Nubmer of atom :"));
				comnms.append(tr("Displacement vector :"));
				datas.append(QString("%1").arg(UR->at_mv_op.x[UR->operations.x[ii].x[1]].id_at_mv_op.x[0]+1));
				datas.append(QString("%1").arg(UR->at_mv_op.x[UR->operations.x[ii].x[1]].id_at_mv_op.x[1]+1));
				datas.append(QString("x: %1, ").arg(UR->at_mv_op.x[UR->operations.x[ii].x[1]].dr_at_mv_op.x[0],0,'g',8));
				datas.last().append(QString("y: %1, ").arg(UR->at_mv_op.x[UR->operations.x[ii].x[1]].dr_at_mv_op.x[1],0,'g',8));
				datas.last().append(QString("z: %1.").arg(UR->at_mv_op.x[UR->operations.x[ii].x[1]].dr_at_mv_op.x[2],0,'g',8));
				break;
			}
		case  MOV_MOL :
			{
				nstr	= QString(tr("Move Molecule"));
				comnms.append(tr("Nubmer of molecule :"));
				comnms.append(tr("Displacement vector :"));
				comnms.append(tr("Center vector :"));
				comnms.append(tr("Rotation quaternion :"));
				datas.append(QString("%1").arg(UR->ml_mv_op.x[UR->operations.x[ii].x[1]].id_ml_mv_op+1));
				datas.append(QString("x: %1, ").arg(UR->ml_mv_op.x[UR->operations.x[ii].x[1]].dr_ml_mv_op.x[0],0,'g',8));
				datas.last().append(QString("y: %1, ").arg(UR->ml_mv_op.x[UR->operations.x[ii].x[1]].dr_ml_mv_op.x[1],0,'g',8));
				datas.last().append(QString("z: %1. ").arg(UR->ml_mv_op.x[UR->operations.x[ii].x[1]].dr_ml_mv_op.x[2],0,'g',8));
				datas.append(QString("x: %1, ").arg(UR->ml_mv_op.x[UR->operations.x[ii].x[1]].cq_ml_mv_op.x[0],0,'g',8));
				datas.last().append(QString("y: %1, ").arg(UR->ml_mv_op.x[UR->operations.x[ii].x[1]].cq_ml_mv_op.x[1],0,'g',8));
				datas.last().append(QString("z: %1. ").arg(UR->ml_mv_op.x[UR->operations.x[ii].x[1]].cq_ml_mv_op.x[2],0,'g',8));
				datas.append(QString("cos(a/2): %1, ").arg(UR->ml_mv_op.x[UR->operations.x[ii].x[1]].qa_ml_mv_op.x[0],0,'g',8));
				datas.last().append(QString("x: %1, ").arg(UR->ml_mv_op.x[UR->operations.x[ii].x[1]].qa_ml_mv_op.x[1],0,'g',8));
				datas.last().append(QString("y: %1, ").arg(UR->ml_mv_op.x[UR->operations.x[ii].x[1]].qa_ml_mv_op.x[2],0,'g',8));
				datas.last().append(QString("z: %1. ").arg(UR->ml_mv_op.x[UR->operations.x[ii].x[1]].qa_ml_mv_op.x[3],0,'g',8));
				break;
			}
		case  MOV_FRG :
			{
				nstr	= QString(tr("Move Fragment"));
				comnms.append(tr("Nubmer of molecule :"));
				comnms.append(tr("Nubmers of atoms :"));
				comnms.append(tr("Displacement vector :"));
				comnms.append(tr("Center vector :"));
				comnms.append(tr("Rotation quaternion :"));
				datas.append(QString("%1").arg(UR->fr_mv_op.x[UR->operations.x[ii].x[1]].id_ml+1));
				datas.append(QString("%1").arg(UR->fr_mv_op.x[UR->operations.x[ii].x[1]].id_fr_mv_op.x[0]+1));
				for(int ij=1;ij<UR->fr_mv_op.x[UR->operations.x[ii].x[1]].id_fr_mv_op.N;ij++)
				{
					datas.last().append(QString(", %1").arg(UR->fr_mv_op.x[UR->operations.x[ii].x[1]].id_fr_mv_op.x[ij]+1));
				}
				datas.append(QString("x: %1, ").arg(UR->fr_mv_op.x[UR->operations.x[ii].x[1]].dr_fr_mv_op.x[0],0,'g',8));
				datas.last().append(QString("y: %1, ").arg(UR->fr_mv_op.x[UR->operations.x[ii].x[1]].dr_fr_mv_op.x[1],0,'g',8));
				datas.last().append(QString("z: %1. ").arg(UR->fr_mv_op.x[UR->operations.x[ii].x[1]].dr_fr_mv_op.x[2],0,'g',8));
				datas.append(QString("x: %1, ").arg(UR->fr_mv_op.x[UR->operations.x[ii].x[1]].cq_fr_mv_op.x[0],0,'g',8));
				datas.last().append(QString("y: %1, ").arg(UR->fr_mv_op.x[UR->operations.x[ii].x[1]].cq_fr_mv_op.x[1],0,'g',8));
				datas.last().append(QString("z: %1. ").arg(UR->fr_mv_op.x[UR->operations.x[ii].x[1]].cq_fr_mv_op.x[2],0,'g',8));
				datas.append(QString("cos(a/2): %1, ").arg(UR->fr_mv_op.x[UR->operations.x[ii].x[1]].qa_fr_mv_op.x[0],0,'g',8));
				datas.last().append(QString("x: %1, ").arg(UR->fr_mv_op.x[UR->operations.x[ii].x[1]].qa_fr_mv_op.x[1],0,'g',8));
				datas.last().append(QString("y: %1, ").arg(UR->fr_mv_op.x[UR->operations.x[ii].x[1]].qa_fr_mv_op.x[2],0,'g',8));
				datas.last().append(QString("z: %1. ").arg(UR->fr_mv_op.x[UR->operations.x[ii].x[1]].qa_fr_mv_op.x[3],0,'g',8));

				break;
			}

		case SWP_ATM :
			{
				nstr	= QString(tr("Swap Atoms"));
				comnms.append(tr("Nubmer of molecule :"));
				comnms.append(tr("Nubmers of atoms :"));
				datas.append(QString("%1").arg(UR->id_at_sw_op.x[UR->operations.x[ii].x[1]].x[0]+1));
				datas.append(QString("%1, ").arg(UR->id_at_sw_op.x[UR->operations.x[ii].x[1]].x[1]+1));
				datas.last().append(QString("%1").arg(UR->id_at_sw_op.x[UR->operations.x[ii].x[1]].x[2]+1));
				break;
			}
		case SWP_MOL :
			{
				nstr	= QString(tr("Swap Molecules"));
				comnms.append(tr("Nubmers of molecules :"));
				datas.append(QString("%1").arg(UR->id_ml_sw_op.x[UR->operations.x[ii].x[1]].x[0]+1));
				datas.last().append(QString(", %1").arg(UR->id_ml_sw_op.x[UR->operations.x[ii].x[1]].x[1]+1));
				break;
			}
		case ADD_PAA :
			{
				nstr	= QString(tr("Add Atom Node"));
				comnms.append(tr("Number of molecule :"));
				comnms.append(tr("Number of chain :"));
				comnms.append(tr("Number of aminoacid :"));
				comnms.append(tr("Number of atom (in amin) :"));
				comnms.append(tr("AminoName of atom : "));
				datas.append(QString("%1").arg(UR->id_pr_at_op.x[UR->operations.x[ii].x[1]].id_s.x[0]+1));
				datas.append(QString("%1").arg(UR->id_pr_at_op.x[UR->operations.x[ii].x[1]].id_s.x[1]+1));
				datas.append(QString("%1").arg(UR->id_pr_at_op.x[UR->operations.x[ii].x[1]].id_s.x[2]+1));
				datas.append(QString("%1").arg(UR->id_pr_at_op.x[UR->operations.x[ii].x[1]].id_s.x[3]+1));
				datas.append(QString(UR->id_pr_at_op.x[UR->operations.x[ii].x[1]].name.x));
				break;
			}
		case DEL_PAA :
			{
				nstr	= QString(tr("Delete Atom Node"));
				comnms.append(tr("Number of molecule :"));
				comnms.append(tr("Number of chain :"));
				comnms.append(tr("Number of aminoacid :"));
				comnms.append(tr("Number of atom (in amin) :"));
				//comnms.append(tr("Name of atom in amin :"));

				datas.append(QString("%1").arg(UR->id_pr_at_op.x[UR->operations.x[ii].x[1]].id_s.x[0]+1));
				datas.append(QString("%1").arg(UR->id_pr_at_op.x[UR->operations.x[ii].x[1]].id_s.x[1]+1));
				datas.append(QString("%1").arg(UR->id_pr_at_op.x[UR->operations.x[ii].x[1]].id_s.x[2]+1));
				datas.append(QString("%1").arg(UR->id_pr_at_op.x[UR->operations.x[ii].x[1]].id_s.x[3]+1));
				//datas.append(QString("%1").arg(UR->id_pr_dl_op.x[UR->operations.x[ii].x[1]].x[3]+1));

				break;
			}

		case DEL_AMN :
			{
				nstr	= QString(tr("Delete AminoAcid Node"));
				comnms.append(tr("Number of molecule :"));
				comnms.append(tr("Number of chain :"));
				comnms.append(tr("Aminoacid :"));
				
				datas.append(QString("%1").arg(UR->id_pr_am_op.x[UR->operations.x[ii].x[1]].id_s.x[0]+1));
				datas.append(QString("%1").arg(UR->id_pr_am_op.x[UR->operations.x[ii].x[1]].id_s.x[1]+1));
				datas.append(QString("%1  ( ").arg(UR->id_pr_am_op.x[UR->operations.x[ii].x[1]].id_s.x[2]+1));
				datas.last().append(QString(UR->id_pr_am_op.x[UR->operations.x[ii].x[1]].name.x));
				datas.last().append(QString(" %1 )").arg(UR->id_pr_am_op.x[UR->operations.x[ii].x[1]].id_ch));
				
				break;
			}
		case ADD_AMN :
			{
				nstr	= QString(tr("Add AminoAcid Node"));
				comnms.append(tr("Number of molecule :"));
				comnms.append(tr("Number of chain :"));
				comnms.append(tr("Number of aminoacid :"));
				
				datas.append(QString("%1").arg(UR->id_pr_am_op.x[UR->operations.x[ii].x[1]].id_s.x[0]+1));
				datas.append(QString("%1").arg(UR->id_pr_am_op.x[UR->operations.x[ii].x[1]].id_s.x[1]+1));
				datas.append(QString("%1  ( ").arg(UR->id_pr_am_op.x[UR->operations.x[ii].x[1]].id_s.x[2]+1));
				datas.last().append(QString(UR->id_pr_am_op.x[UR->operations.x[ii].x[1]].name.x));
				datas.last().append(QString(" %1 )").arg(UR->id_pr_am_op.x[UR->operations.x[ii].x[1]].id_ch));
				break;
			}
		case DEL_CHN :
			{
				nstr	= QString(tr("Delete Chain Node"));
				comnms.append(tr("Number of molecule :"));
				comnms.append(tr("Number of chain :"));

				datas.append(QString("%1").arg(UR->id_pr_ch_op.x[UR->operations.x[ii].x[1]].id_s.x[0]+1));
				datas.append(QString("%1 (").arg(UR->id_pr_ch_op.x[UR->operations.x[ii].x[1]].id_s.x[1]+1));
				datas.last().append(QChar(UR->id_pr_ch_op.x[UR->operations.x[ii].x[1]].ch));
				datas.last().append(QString(")"));				
				break;
			}
		case ADD_CHN :
			{
				nstr	= QString(tr("Add Chain Node"));
				comnms.append(tr("Number of molecule :"));
				comnms.append(tr("Number of chain :"));

				datas.append(QString("%1").arg(UR->id_pr_ch_op.x[UR->operations.x[ii].x[1]].id_s.x[0]+1));
				datas.append(QString("%1 (").arg(UR->id_pr_ch_op.x[UR->operations.x[ii].x[1]].id_s.x[1]+1));
				datas.last().append(QChar(UR->id_pr_ch_op.x[UR->operations.x[ii].x[1]].ch));
				datas.last().append(QString(")"));			
				break;
			}
		case DEL_PRT :
			{
				nstr	= QString(tr("Delete Protein Node"));
				comnms.append(tr("Number of molecule :"));
				datas.append(QString("%1").arg(UR->id_pr_pr_op.x[UR->operations.x[ii].x[1]].id_s+1));
				break;
			}
		case ADD_PRT :
			{
				nstr	= QString(tr("Add Protein Node"));
				comnms.append(tr("Number of molecule :"));
				datas.append(QString("%1").arg(UR->id_pr_pr_op.x[UR->operations.x[ii].x[1]].id_s+1));
				break;
			}

		case   STOP_OP :
			{
				nstr	= QString(tr("Stop"));
				break;
			}
		}
		sdt<<nstr;
		nstr	= QString("%1").arg(ii);
		nstr.append(QString("	%1").arg(UR->operations.x[ii].x[1]));
		sdt<<nstr;

		parents.last()->appendChild(new CommandItem(sdt,parents.last()));

		parents<<parents.last()->child(parents.last()->childCount()-1);
		for(int jj=0;jj<comnms.length();jj++)
		{
			sdt.clear();
			sdt<<comnms.value(jj);
			sdt<<datas.value(jj);
			parents.last()->appendChild(new CommandItem(sdt,parents.last()));
		}

		parents<<parents.last()->parent();
		

	}
	endResetModel();
}


HstrView::HstrView(QWidget *parent) : QTreeView(parent)
{
//	setSelectionMode(QAbstractItemView::ExtendedSelection);
//	setSelectionBehavior(QAbstractItemView::SelectRows);
	setHorizontalScrollMode ( QAbstractItemView::ScrollPerPixel );
}

//---------------------
undoredo::undoredo(QWidget *parent ) : QWidget(parent)
{

	setWindowIcon(QIcon(":/images/undoredo.png"));
	setWindowTitle(tr("Undo/Redo Viewer"));

	unmodel	= new CmdTrModel;
	unhistory		= new HstrView;

	unhistory->setModel(unmodel);

	unmodel->setUR(this);
	unmodel->setundo();

	rdmodel	= new CmdTrModel;
	rdhistory		= new HstrView;

	rdhistory->setModel(rdmodel);

	rdmodel->setUR(this);
	rdmodel->setredo();

	//QTextBrowser *textBrowser = new QTextBrowser;

	//textBrowser->setText(tr("Some text."));

	//QVBoxLayout *mainLayout	= new QVBoxLayout;

	

	QLabel *lb = new QLabel(tr("Undo Operations"));
	QVBoxLayout *leftLayout	= new QVBoxLayout;
	leftLayout->addWidget(lb);
	leftLayout->addWidget(unhistory);

	QLabel *rb = new QLabel(tr("Redo Operations"));
	QVBoxLayout *rigthLayout	= new QVBoxLayout;
	rigthLayout->addWidget(rb);
	rigthLayout->addWidget(rdhistory);

	QHBoxLayout *mainLayout	= new QHBoxLayout;

	QWidget * hWidget1, *hWidget2;

	hWidget1	= new QWidget;
	hWidget2	= new QWidget;

	hWidget1->setLayout(leftLayout);
	hWidget2->setLayout(rigthLayout);

	QSplitter * splitterWidget;
	splitterWidget	= new QSplitter;
	splitterWidget->addWidget(hWidget1);
	splitterWidget->addWidget(hWidget2);

	mainLayout->addWidget(splitterWidget);

	setLayout(mainLayout);

	//setWindowFlags(Qt::WindowStaysOnTopHint);


	id_cr_op	= 0;
	op_count	= 0;

	WF			= 0x0;
	GW			= 0x0;
	undoAction	= 0x0;
	redoAction	= 0x0;
}

// методы инициализации

void undoredo::AddMol_init(Molecule *r)
{
	vec2int opr;
	id_ml_dl_op.add(WF->Mls.N); // запись об инверсной оперции
	ml_br_dl_op.add(r);
	opr.x[0]	= ADD_MOL;
	opr.x[1]	= id_ml_dl_op.N-1;
	operations.add(opr);	// запись о прямой операции
	
}
void undoredo::DelMol_init(int id_ml)
{
	vec2int opr;
	id_ml_dl_op.add(id_ml);
	ml_br_dl_op.pad(WF->Mls.x[id_ml]);
	opr.x[0]	= DEL_MOL;
	opr.x[1]	= id_ml_dl_op.N-1;
	operations.add(opr); // запись о прямой оперции
	// инверсная операция не имеет параметром - для неё нет записи
}
/*void undoredo::AddProt_init(Protein *r)
{
	vec2int opr;
	id_ml_dl_op.add(WF->Prot.N); // запись об инверсной оперции
	ml_br_dl_op.add(r);
	opr.x[0]	= ADD_MOL;
	opr.x[1]	= id_ml_dl_op.N-1;
	operations.add(opr);	// запись о прямой операции
	
}*/
void undoredo::AddAtm_init(int id_ml)
{
	vec2int opr;
	//AtomData * ptr = 0x0;
	opr.x[0]	= id_ml;
	opr.x[1]	= WF->Mls.x[id_ml]->Atoms.N;
	id_at_br_op.add(id_ml);
	id_at_dl_op.add(opr); // инверсия оперции
	//ptr_dat_op.add(ptr);
	opr.x[0]	= ADD_ATM;
	opr.x[1]	= id_at_br_op.N-1;
	operations.add(opr);
}
void undoredo::SwpAtm_init(int id_ml,int &id_at1,int &id_at2)	// swap атомов id_at1 и id_at2
{
	vec2int opr;
	vec3int data(id_ml,id_at1,id_at2);
	id_at_sw_op.add(data);
	opr.x[0]	= SWP_ATM;
	opr.x[1]	= id_at_sw_op.N-1;
	operations.add(opr);
}
void undoredo::SwpMol_init(int id_ml1,int &id_ml2)	// swap атомов id_at1 и id_at2
{
	vec2int opr(id_ml1,id_ml2);
	id_ml_sw_op.add(opr);
	opr.x[0]	= SWP_MOL;
	opr.x[1]	= id_ml_sw_op.N-1;
	operations.add(opr);
}
void undoredo::DelAtm_init(int id_ml,int &id_at)
{
	vec2int opr;
	opr.x[0]	= id_ml;
	opr.x[1]	= id_at;
	//ptr_dat_op.add(WF->Mls.x[id_ml]->Atoms.x[id_at].dat.dat);
	id_at_dl_op.add(opr);
	id_at_br_op.add(id_ml);// инверсия операции
	opr.x[0]	= DEL_ATM;
	opr.x[1]	= id_at_dl_op.N-1;
	operations.add(opr);
}

void undoredo::AddPaa_init(int id_ml, int id_ch, int id_am, int id_at, vecT<char> &name)
{
	vec2int opr;
	data_op12 dat;
	dat.id_s.x[0]	= id_ml;
	dat.id_s.x[1]	= id_ch;
	dat.id_s.x[2]	= id_am;
	dat.id_s.x[3]	= id_at;
	dat.name.pst(name);
	id_pr_at_op.pad(dat);
	//id_pr_aa_op.add(dat);
	//id_pr_dl_op.add(dat);	// для инверсной операции
	opr.x[0]	= ADD_PAA;
	opr.x[1]	= id_pr_at_op.N-1;
	operations.add(opr);
}
void undoredo::DelPaa_init(int id_ml, int id_ch, int id_am, int id_at )
{
	vec2int opr;
	data_op12 dat;
	dat.id_s.x[0]	= id_ml;
	dat.id_s.x[1]	= id_ch;
	dat.id_s.x[2]	= id_am;
	dat.id_s.x[3]	= id_at;
	dat.name.pst(WF->Mls.x[id_ml]->p_prt->getChild(id_ch)->getChild(id_am)->getChild(id_at)->name);
	//vec4int dat(id_ml,id_ch,id_am,id_at);
	opr.x[0]	= DEL_PAA;
	opr.x[1]	= id_pr_at_op.N;
	id_pr_at_op.pad(dat);
	//id_pr_dl_op.add(dat);
	//id_pr_aa_op.add(dat); // инверсная операция
	operations.add(opr);
}

void undoredo::DelAmn_init(int id_ml, int id_ch, int id_am )
{
	vec2int opr;
	data_op13 dat;
	dat.id_s	= vec3int(id_ml,id_ch,id_am);
	dat.name.pst(WF->Mls.x[id_ml]->p_prt->getChild(id_ch)->getChild(id_am)->name);
	dat.id_ch	= WF->Mls.x[id_ml]->p_prt->getChild(id_ch)->getChild(id_am)->id_ch;
	opr.x[0]	= DEL_AMN;
	opr.x[1]	= id_pr_am_op.N;
	id_pr_am_op.pad(dat);
	operations.add(opr);
}
void undoredo::AddAmn_init(int id_ml, int id_ch, int id_am, vecT<char> &name, int id_a)
{
	vec2int opr;
	data_op13 dat;
	dat.id_s	= vec3int(id_ml,id_ch,id_am);
	dat.name.pst(name);
	dat.id_ch	= id_a;
	opr.x[0]	= ADD_AMN;
	opr.x[1]	= id_pr_am_op.N;
	id_pr_am_op.pad(dat);
	operations.add(opr);
}

void undoredo::DelChn_init(int id_ml, int id_ch )
{
	vec2int opr;
	data_op14 dat;
	dat.id_s	= vec2int(id_ml,id_ch);
	dat.ch		= WF->Mls.x[id_ml]->p_prt->getChild(id_ch)->ch;
	opr.x[0]	= DEL_CHN;
	opr.x[1]	= id_pr_ch_op.N;
	id_pr_ch_op.pad(dat);
	operations.add(opr);
}
void undoredo::AddChn_init(int id_ml, int id_ch , char ch)
{
	vec2int opr;
	data_op14 dat;
	dat.id_s	= vec2int(id_ml,id_ch);
	dat.ch		= ch;
	opr.x[0]	= ADD_CHN;
	opr.x[1]	= id_pr_ch_op.N;
	id_pr_ch_op.pad(dat);
	operations.add(opr);
}
void undoredo::DelPrt_init(int id_ml )
{
	vec2int opr;
	opr.x[0]	= DEL_PRT;
	opr.x[1]	= id_pr_pr_op.N;
	data_op15 dat;
	dat.id_s	= id_ml;
	dat.protname.pst(WF->Mls.x[id_ml]->p_prt->protname);
	id_pr_pr_op.pad(dat);
	operations.add(opr);
}
void undoredo::AddPrt_init(int id_ml , vecT<char> &name)
{
	vec2int opr;
	opr.x[0]	= ADD_PRT;
	opr.x[1]	= id_pr_pr_op.N;
	data_op15 dat;
	dat.id_s	= id_ml;
	dat.protname.pst(name);
	id_pr_pr_op.pad(dat);
	operations.add(opr);
}
//-------
void undoredo::AddBnd_init(int id_ml,int &id_at1,int &id_at2)	// добавить связь
{
	vec2int opr;
	vec3int data(id_ml,id_at1,id_at2);
	id_bn_br_op.add(data);

	//opr.x[0]	= id_ml;
	//opr.x[1]	= WF->Mls.x[id_ml]->Bonds.N;
	id_bn_dl_op.add(data);	// инверсия

	opr.x[0]	= ADD_BND;
	opr.x[1]	= id_bn_br_op.N-1;
	operations.add(opr);


}
void undoredo::DelBnd_init(int id_ml,int &id_at1,int &id_at2)	// удалить связь
{
	//int id_bn;
	vec3int data(id_ml,id_at1,id_at2);
	id_bn_dl_op.add(data);
	
	//id_at1	= WF->Mls.x[id_ml]->Bonds.x[id_bn].id_Atoms.x[0];
	//id_at2	= WF->Mls.x[id_ml]->Bonds.x[id_bn].id_Atoms.x[1];
	
	id_bn_br_op.add(data); // инверсия

	vec2int opr;
	opr.x[0]	= DEL_BND;
	opr.x[1]	= id_bn_dl_op.N-1;
	operations.add(opr);
}
void undoredo::UniMol_init(int &id_ml1,int &id_ml2)	// объединть две молекулы
{
	vec2int opr(id_ml1,id_ml2);
	id_ml_un_op.add(opr);
	opr.x[0]	= UNI_MOL;
	opr.x[1]	= id_ml_un_op.N-1;
	operations.add(opr);
	id_ml_sp_op.add(WF->Mls.x[id_ml1]->Atoms.N);
	// инверсия операци
	/*vecT<int> data;
	data.var1D(0,1,WF->Mls.x[id_ml2]->Atoms.N);
	data	+= WF->Mls.x[id_ml1]->Atoms.N;*/
	//int id = id_ml1>id_ml2 ? id_ml2 : id_ml1;
	//id_ml_sp_op.add(id_ml1);
}
void undoredo::SepMol_init(int &id_ml1,int &id_ml2)//,vecT<int> &id_bn)
{
	id_ml_sp_op.add(id_ml2);
	vec2int opr(id_ml1,WF->Mls.N-1);
	id_ml_un_op.add(opr);
	opr.x[0]	= SEP_MOL;
	opr.x[1]	= id_ml_un_op.N-1;
	operations.add(opr);
	// запись для инверсной операции
	//opr.x[0]	= id_ml;
	//opr.x[1]	= WF->Mls.N;
	//id_ml_un_op.add(opr);
}
void undoredo::ChgTyp_init(int id_ml,int id_at,int id_tp, AtomData *ptr)	// изменить тип атома
{
	vec2int opr;
	vec3int data(id_ml,id_at,id_tp);
	id_at_tp_op.add(data);
	/*if(ptr==0x0) // 0х0 означает что атом будет удаляться
	{
		ptr	= WF->Mls.x[id_ml]->Atoms.x[id_at].dat.dat;//WF->Mls.x[id_ml].Atoms.x[id_at]
	}*/
	ptr_dat_op.add(ptr);
	opr.x[0]	= CHG_TYP;
	opr.x[1]	= id_at_tp_op.N-1;
	operations.add(opr);
}
void undoredo::ChgBnd_init(int id_ml,int &id_at1,int &id_at2,int &id_tp)	// изменить тип связи
{
	vec2int opr;
	vec4int data(id_ml,id_at1,id_at2,id_tp);
	id_bn_tp_op.add(data);
	opr.x[0]	= CHG_BND;
	opr.x[1]	= id_bn_tp_op.N-1;
	operations.add(opr);
}
void undoredo::MovAtm_init(int id_ml,int &id_at,vec3db &dr)	// поступательное смещение атома
{
	data_op5 op_data;
	vec2int opr;
	opr.x[0]	= MOV_ATM;
	opr.x[1]	= at_mv_op.N;
	operations.add(opr);
	op_data.id_at_mv_op.x[0]	= id_ml;
	op_data.id_at_mv_op.x[1]	= id_at;
	op_data.dr_at_mv_op	=	dr;
	at_mv_op.add(op_data);
}
void undoredo::MovMol_init(int id_ml,vec3db &dr,vec3db &cq,Quaternion<double> &qa)	// смещение и поворот молекулы
{
	data_op6 op_data;
	vec2int opr;
	opr.x[0]	= MOV_MOL;
	opr.x[1]	= ml_mv_op.N;
	operations.add(opr);
	op_data.id_ml_mv_op	= id_ml;
	op_data.dr_ml_mv_op	= dr;
	op_data.cq_ml_mv_op	= cq;
	op_data.qa_ml_mv_op	= qa;
	ml_mv_op.add(op_data);
	//id_ml_mv_op.add(id_ml);
	//dr_ml_mv_op.add(dr);
	//cq_ml_mv_op.add(cq);
	//qa_ml_mv_op.add(qa);

}
void undoredo::MovFrg_init(int id_ml,vecT<int> &id_at,vec3db &dr,vec3db &cq,Quaternion<double> &qa)	// смещение и поворот фрагмента
{
	data_op7 op_data;
	vec2int opr;
	opr.x[0]	= MOV_FRG;
	opr.x[1]	= fr_mv_op.N;
	operations.add(opr);

	op_data.id_ml	= id_ml;
	op_data.id_fr_mv_op.pst(id_at);
	op_data.dr_fr_mv_op	= dr;
	op_data.cq_fr_mv_op	= cq;
	op_data.qa_fr_mv_op	= qa;

	fr_mv_op.add(op_data);
;
}
void undoredo::Stop_init()
{
	vec2int opr;
	opr.x[0]	= STOP_OP;
	opr.x[1]	= 0;
	operations.add(opr);
	id_cr_op	= operations.N;

	unmodel->updateModel();
	rdmodel->updateModel();
}
// ------------------------



//   методы операци	
void undoredo::SwpAtm_op()
{
	int ii,id_ml,id_at1,id_at2;
	ii	= operations.x[id_cr_op].x[1];
	id_ml	= id_at_sw_op.x[ii].x[0];
	id_at1	= id_at_sw_op.x[ii].x[1];
	id_at2	= id_at_sw_op.x[ii].x[2];
	GW->swp_Selected_ids(id_ml,id_at1,id_at2);
	WF->Mls.x[id_ml]->AtomSwap(id_at1,id_at2);

}
void undoredo::SwpMol_op()
{
	int ii,id_ml1,id_ml2;
	ii	= operations.x[id_cr_op].x[1];
	id_ml1	= id_ml_sw_op.x[ii].x[0];
	id_ml2	= id_ml_sw_op.x[ii].x[1];
	WF->MolSwap(id_ml1,id_ml2);

}
void undoredo::AddMol_op()	// добавить пустую молекулу
{
	int ii;
	ii		= operations.x[id_cr_op].x[1];
	WF->Mls.add(ml_br_dl_op.x[ii]);
	// инверсия текущей оперции:
	operations.x[id_cr_op].x[0]	= DEL_MOL;

}
void undoredo::DelMol_op()	// удалить молекулу
{
	int	ii,id_ml;//,m;
	ii	= operations.x[id_cr_op].x[1]; // номер элемента из массива с входными данными
	id_ml	= id_ml_dl_op.x[ii];	//  номер удаляемой молекулы;
	--WF->Mls.N;
	// инверсия текущей оперции:
	operations.x[id_cr_op].x[0]	= ADD_MOL;

}
/*void undoredo::AddPrt_op()	// добавить пустую молекулу
{
	int ii;
	ii		= operations.x[id_cr_op].x[1];
	WF->Prot.add(pr_br_dl_op.x[ii]);
	// инверсия текущей оперции:
	operations.x[id_cr_op].x[0]	= DEL_PRT;
}*/
void undoredo::AddAtm_op()
{
	int	id_ml,ii;
	ii	= operations.x[id_cr_op].x[1]; // номер элемента из массива структур входных данных
	id_ml	= id_at_br_op.x[ii];	// номер молекулы для которой происходит рождене атома
	WF->Mls.x[id_ml]->AtomIns(0);
	// инверсия текущей оперции:
	operations.x[id_cr_op].x[0]	= DEL_ATM;

}
void undoredo::DelAtm_op()
{
	int id_ml,id_at,ii;
	ii	= operations.x[id_cr_op].x[1];
	id_ml	= id_at_dl_op.x[ii].x[0];
	id_at	= id_at_dl_op.x[ii].x[1];
	WF->Mls.x[id_ml]->AtomDel(id_at);

	// инверсия текущей оперции:
	operations.x[id_cr_op].x[0]	= ADD_ATM;

}
void undoredo::AddBnd_op()	// добавить связь
{
	int ii,id_ml,id_at1,id_at2;
	ii	= operations.x[id_cr_op].x[1];
	id_ml	= id_bn_br_op.x[ii].x[0];
	id_at1	= id_bn_br_op.x[ii].x[1];
	id_at2	= id_bn_br_op.x[ii].x[2];
	WF->Mls.x[id_ml]->AddBond(1,id_at1,id_at2);
	// инверсия текущей оперции:
	operations.x[id_cr_op].x[0]	= DEL_BND;

}
void undoredo::DelBnd_op()	// удалить связь
{
	int ii,id_ml,id_at1,id_at2,id_bn;
	ii	= operations.x[id_cr_op].x[1];
	id_ml	= id_bn_dl_op.x[ii].x[0];
	id_at1	= id_bn_dl_op.x[ii].x[1];
	id_at2	= id_bn_dl_op.x[ii].x[2];
	id_bn	= WF->Mls.x[id_ml]->Connect.get(id_at1,id_at2)-1;
	WF->Mls.x[id_ml]->BondDel(id_bn);
	// инверсия текущей оперции:
	operations.x[id_cr_op].x[0]	= ADD_BND;

}
void undoredo::UniMol_op()
{
	int ii,id_ml1,id_ml2;
	vecT<int> id1;
	ii	= operations.x[id_cr_op].x[1];
	id_ml1	= id_ml_un_op.x[ii].x[0];
	id_ml2	= id_ml_un_op.x[ii].x[1];
	WF->Mls.x[id_ml1]->UniMol(WF->Mls.x[id_ml2]);
	//WF->Mls.N--;
	//delete WF->Mls.x[WF->Mls.N];
	// инверсия текущей оперции:
	operations.x[id_cr_op].x[0]	= SEP_MOL;

}
void undoredo::SepMol_op()	//	разъединить молекулу на две
{
	int ii,jj,id_ml1,id_ml2;
	vecT<int> id1,id2;
	ii		= operations.x[id_cr_op].x[1];
	id_ml1	= id_ml_un_op.x[ii].x[0];
	id_ml2	= id_ml_un_op.x[ii].x[1];
	jj		= id_ml_sp_op.x[ii];
	WF->Mls.x[id_ml1]->SepMol(WF->Mls.x[id_ml2],jj);
	//WF->Mls.x[id_ml1];
	//Molecule *m;
	//WF->Mls.x[id_ml]->SepMol(*m,id1,id2);
	//WF->Mls.add(m);
	//m	= 0x0;
	// коррекция данных о номерах атомов в новообразованных молекулах

	/*	idmcns(id1);
		//n_k	= id_ml;
		if(idn.N>0)
		{
			swp3_(id_at_tp_op,0,id_ml,1);
			swp2_(id_at_dl_op,0,id_ml,1);
			swp3_(id_bn_br_op,0,id_ml,1);
			swp3_(id_bn_br_op,0,id_ml,2);
			swp3_(id_bn_dl_op,0,id_ml,1);
			swp3_(id_bn_dl_op,0,id_ml,2);
			swp2_(id_at_mv_op,0,id_ml,1);
			swp4_(id_bn_tp_op,0,id_ml,1);
			swp4_(id_bn_tp_op,0,id_ml,2);
		}

		idmcns(id2);
		//n_k	= jj;
		if(idn.N>0)
		{
			swp_3(id_at_tp_op,0,id_ml,jj,1);
			swp_2(id_at_dl_op,0,id_ml,jj,1);
			swp3_(id_bn_br_op,0,id_ml,1);
			swp_3(id_bn_br_op,0,id_ml,jj,2);
			swp3_(id_bn_dl_op,0,id_ml,1);
			swp_3(id_bn_dl_op,0,id_ml,jj,2);
			swp_2(id_at_mv_op,0,id_ml,jj,1);
			swp4_(id_bn_tp_op,0,id_ml,1);
			swp_4(id_bn_tp_op,0,id_ml,jj,2);
		}*/

//	swp2(id_at_dl_op,0,id_ml2,WF->Mls.N);
	// инверсия текущей оперции:
	operations.x[id_cr_op].x[0]	= UNI_MOL;

}
void undoredo::ChgTyp_op()	// изменить тип атома
{
	int ii,id_ml,id_at,id_tp;
	AtomData * ptr;
	ii	= operations.x[id_cr_op].x[1];
	id_ml	= id_at_tp_op.x[ii].x[0];
	id_at	= id_at_tp_op.x[ii].x[1];
	id_tp	= WF->Mls.x[id_ml]->Atoms.x[id_at].id_Tpz;
	ptr		= WF->Mls.x[id_ml]->Atoms.x[id_at].dat.dat;
	WF->Mls.x[id_ml]->Atoms.x[id_at].id_Tpz	= id_at_tp_op.x[ii].x[2];
	WF->Mls.x[id_ml]->Atoms.x[id_at].dat.dat	= ptr_dat_op.x[ii];
	// инверсия оперции
	id_at_tp_op.x[ii].x[2]	= id_tp;
	ptr_dat_op.x[ii]		= ptr;

}
void undoredo::ChgBnd_op()	// изменить тип связи
{
	int ii,id_ml,id_bn,id_tp,id_at1,id_at2;
	ii	= operations.x[id_cr_op].x[1];
	id_ml	= id_bn_tp_op.x[ii].x[0];
	id_at1	= id_bn_tp_op.x[ii].x[1];
	id_at2	= id_bn_tp_op.x[ii].x[2];
	id_bn	= WF->Mls.x[id_ml]->Connect.get(id_at1,id_at2)-1;
	id_tp	= WF->Mls.x[id_ml]->Bonds.x[id_bn].oder;
	WF->Mls.x[id_ml]->Bonds.x[id_bn].oder	= id_bn_tp_op.x[ii].x[3];
	// инверсия оперции
	id_bn_tp_op.x[ii].x[3]	= id_tp;
}
void undoredo::MovAtm_op()	// поступательное смещение атома
{
	int  ii,id_ml,id_at;
	vec3db dr;
	ii	= operations.x[id_cr_op].x[1];
	id_ml	= at_mv_op.x[ii].id_at_mv_op.x[0];
	id_at	= at_mv_op.x[ii].id_at_mv_op.x[1];
	dr		= at_mv_op.x[ii].dr_at_mv_op;
	WF->Mls.x[id_ml]->Atoms.x[id_at].r	+= dr;
	// инверсия оперции
	at_mv_op.x[ii].dr_at_mv_op	*= -1.0;

}

void undoredo::MovMol_op()	// смещение и поворот молекулы
{
	int  jj,ii,id_ml;
	vec3db dr,cq,rr;
	FullMatrix<double> A;
	ii	= operations.x[id_cr_op].x[1];

	id_ml	= ml_mv_op.x[ii].id_ml_mv_op;
	dr		= ml_mv_op.x[ii].dr_ml_mv_op;
	cq		= ml_mv_op.x[ii].cq_ml_mv_op;

	A		= ml_mv_op.x[ii].qa_ml_mv_op.qua2matrR();
	for(jj=0;jj<WF->Mls.x[id_ml]->Atoms.N;jj++)
	{
		rr	= WF->Mls.x[id_ml]->Atoms.x[jj].r - cq;
		rr	= A*rr;
		WF->Mls.x[id_ml]->Atoms.x[jj].r	= rr + cq + dr;
	}
	// инверсия
	ml_mv_op.x[ii].qa_ml_mv_op.conjugate();
	ml_mv_op.x[ii].dr_ml_mv_op	*= -1.0; 
}

void undoredo::MovFrg_op()	// смещение и поворот молекулы
{
	int  jj,ii,id_ml;
	vec3db dr,cq,rr;
	vecT<int> ids_at;
	FullMatrix<double> A;
	ii	= operations.x[id_cr_op].x[1];

	id_ml	= fr_mv_op.x[ii].id_ml;
	dr		= fr_mv_op.x[ii].dr_fr_mv_op;
	cq		= fr_mv_op.x[ii].cq_fr_mv_op;
	ids_at.N	= 0;
	ids_at.add(fr_mv_op.x[ii].id_fr_mv_op.x,fr_mv_op.x[ii].id_fr_mv_op.N);

	A		= fr_mv_op.x[ii].qa_fr_mv_op.qua2matrR();
	for(jj=0;jj<ids_at.N;jj++)
	{
		rr	= WF->Mls.x[id_ml]->Atoms.x[ids_at.x[jj]].r - cq;
		rr	= A*rr;
		rr	+= dr;
		WF->Mls.x[id_ml]->Atoms.x[ids_at.x[jj]].r	= rr + cq;
	}
	// инверсия
	fr_mv_op.x[ii].qa_fr_mv_op.conjugate();
	fr_mv_op.x[ii].dr_fr_mv_op	*= -1.0; 
}

void undoredo::AddPaa_op()
{
	int ii;
	ii	= operations.x[id_cr_op].x[1];
	data_op12 dat;
	dat	= id_pr_at_op.x[ii];
	atom_node * p_atm = WF->Mls.x[dat.id_s.x[0]]->p_prt->addAtomNode(dat.id_s.x[1],dat.id_s.x[2],dat.id_s.x[3]);//)->atom=&WF->Mls.x[data.x[0]]->Atoms.x[data.x[3]];
	p_atm->atom	= &WF->Mls.x[dat.id_s.x[0]]->Atoms.x[WF->Mls.x[dat.id_s.x[0]]->Atoms.N-1];// связь атом-узла с !!!ПОСЛЕДНИМ!!! атомом
	p_atm->atom->dat.dat->amin	= p_atm; // связь атома с атом-узлом
	p_atm->name.pst(dat.name);
	operations.x[id_cr_op].x[0]	= DEL_PAA; // инверсия операции
}

void undoredo::DelPaa_op()
{
	int ii,id_at;
	data_op12 dat;
	ii	= operations.x[id_cr_op].x[1];
	//protein_node * p_prt;
	dat		= id_pr_at_op.x[ii];
	//p_prt	= WF->Mls.x[dat.x[0]]->p_prt;
	id_at	= dat.id_s.x[3]; //WF->Mls.x[dat.x[0]]->Atoms.x[dat.x[3]].dat.dat->amin->id;
	//p_prt->getChild(dat.x[1])->getChild(dat.x[2])->delChild(id_at);//->getChild(data.x[2])
	WF->Mls.x[dat.id_s.x[0]]->p_prt->childs.x[dat.id_s.x[1]]->childs.x[dat.id_s.x[2]]->delChild(id_at);//->getChild(data.x[2])
	operations.x[id_cr_op].x[0]	= ADD_PAA; // инверсия операции
}

void undoredo::AddAmn_op()
{
	int ii;
	ii	= operations.x[id_cr_op].x[1];
	data_op13 dat;
	dat	= id_pr_am_op.x[ii];
	amino_node * p_atm = new amino_node;//WF->Mls.x[dat.x[0]]->p_prt->addAtomNode(dat.x[1],dat.x[2]);//)->atom=&WF->Mls.x[data.x[0]]->Atoms.x[data.x[3]];
	p_atm->id_ch	= dat.id_ch;
	p_atm->name.pst(dat.name);
	WF->Mls.x[dat.id_s.x[0]]->p_prt->childs.x[dat.id_s.x[1]]->addChild(p_atm,dat.id_s.x[2]);
	operations.x[id_cr_op].x[0]	= DEL_AMN; // инверсия операции
}

void undoredo::DelAmn_op()
{
	int ii;
	ii	= operations.x[id_cr_op].x[1];
	data_op13 dat;
	dat	= id_pr_am_op.x[ii];
	WF->Mls.x[dat.id_s.x[0]]->p_prt->childs.x[dat.id_s.x[1]]->delChild(dat.id_s.x[2]);
	operations.x[id_cr_op].x[0]	= ADD_AMN; // инверсия операции
}

void undoredo::AddChn_op()
{
	int ii;
	ii	= operations.x[id_cr_op].x[1];
	data_op14 dat;
	dat	= id_pr_ch_op.x[ii];
	chain_node * p_chs = new chain_node;//WF->Mls.x[dat.x[0]]->p_prt->addAtomNode(dat.x[1],dat.x[2]);//)->atom=&WF->Mls.x[data.x[0]]->Atoms.x[data.x[3]];
	p_chs->ch	= dat.ch;
	WF->Mls.x[dat.id_s.x[0]]->p_prt->addChild(p_chs,dat.id_s.x[1]);
	operations.x[id_cr_op].x[0]	= DEL_CHN; // инверсия операции
}

void undoredo::DelChn_op()
{
	int ii;
	ii	= operations.x[id_cr_op].x[1];
	data_op14 dat;
	dat	= id_pr_ch_op.x[ii];
	WF->Mls.x[dat.id_s.x[0]]->p_prt->delChild(dat.id_s.x[1]);
	operations.x[id_cr_op].x[0]	= ADD_CHN; // инверсия операции
}

void undoredo::AddPrt_op()
{
	int ii;
	ii	= operations.x[id_cr_op].x[1];
	data_op15 dat;
	dat	= id_pr_pr_op.x[ii];
	protein_node * p_prt = new protein_node;//WF->Mls.x[dat.x[0]]->p_prt->addAtomNode(dat.x[1],dat.x[2]);//)->atom=&WF->Mls.x[data.x[0]]->Atoms.x[data.x[3]];
	p_prt->protname.pst(dat.protname);
	WF->Mls.x[dat.id_s]->p_prt = p_prt;
	operations.x[id_cr_op].x[0]	= DEL_PRT; // инверсия операции
}

void undoredo::DelPrt_op()
{
	int ii;
	ii	= operations.x[id_cr_op].x[1];
	data_op15 dat;
	dat	= id_pr_pr_op.x[ii];
	delete WF->Mls.x[dat.id_s]->p_prt;
	WF->Mls.x[dat.id_s]->p_prt	= 0x0;
	operations.x[id_cr_op].x[0]	= ADD_PRT; // инверсия операции
}

void undoredo::Frwd_op()// реализация операции вперёд по списку операций
{
	if(id_cr_op<(operations.N-1))
	{
		//id_cr_op++;
		if(!undoAction->isEnabled()) undoAction->setEnabled(true);
		for(;(operations.x[id_cr_op].x[0]!=STOP_OP);id_cr_op++)
		{

			switch (operations.x[id_cr_op].x[0])
			{
			case   ADD_MOL :
				   {
					   AddMol_op();
					   break;
				   }
			case   DEL_MOL : 
				   {
					   DelMol_op();	// удалить молекулу
					   break;
				   }
			/*case   ADD_PRT :
				   {
					   AddPrt_op();
					   break;
				   }*/
			case   ADD_ATM :
				   {
					   AddAtm_op();	// добавить нетипизированный атом
					   break;
				   }
			case   DEL_ATM :
				   {
					   DelAtm_op();	// удалить атом
					   break;
				   }
			case   ADD_BND :
				   {
					   AddBnd_op();	// добавить связь
					   break;
				   }
			case   DEL_BND :
				   {
					   DelBnd_op();	// удалить связь
					   break;
				   }
			case   UNI_MOL :
				   {
					   UniMol_op();	// объединть две молекулы
					   break;
				   }
			case   SEP_MOL :
				   {
					   SepMol_op();	// разъединить молекулу на две
					   break;
				   }

			case   CHG_TYP :
				   {
					   ChgTyp_op();	// изменить тип атома
					   break;
				   }
			case   CHG_BND :
				   {
					   ChgBnd_op();	// изменить тип связи
					   break;
				   }
			case   MOV_ATM :	
				   {
					   MovAtm_op();	// поступательное смещение атома
					   break;
				   }
			case   MOV_MOL :
				   {
						MovMol_op(); // вращение молекулы
						break;
				   }
			case  MOV_FRG :
				   {
					   MovFrg_op();
					   break;
				   }
			case SWP_ATM :
					{
						SwpAtm_op();
						break;
					}
			case SWP_MOL :
					{
						SwpMol_op();
						break;
					}
			case ADD_PAA :
					{
						AddPaa_op();
						break;
					}
			case DEL_PAA :
					{
						DelPaa_op();
						break;
					}
			case DEL_AMN :
					{
						DelAmn_op();
						break;
					}
			case ADD_AMN :
					{
						AddAmn_op();
						break;
					}
			case DEL_CHN :
					{
						DelChn_op();
						break;
					}
			case ADD_CHN :
					{
						AddChn_op();
						break;
					}
			case DEL_PRT :
					{
						DelPrt_op();
						break;
					}
			case ADD_PRT :
					{
						AddPrt_op();
						break;
					}
			case   STOP_OP :
				   {
					   break;
				   }
			}
		}
		id_cr_op++;
	}
	if(id_cr_op>=(operations.N-1))
	{
		redoAction->setEnabled(false);
	}

	unmodel->updateModel();
	rdmodel->updateModel();
}
void undoredo::Back_op()// реализация операции назад по списку опеаций
{
	if(id_cr_op>1)
	{
		if(!redoAction->isEnabled()) redoAction->setEnabled(true);
		id_cr_op--;
		id_cr_op--;
		for(;(operations.x[id_cr_op].x[0]!=STOP_OP);id_cr_op--)
		{
			switch (operations.x[id_cr_op].x[0])
			{
			case   ADD_MOL :
				   {
					   AddMol_op();
					   break;
				   }
			case   DEL_MOL :
				   {
					   DelMol_op();	// удалить молекулу
					   break;
				   }
			/*case   ADD_PRT :
				   {
					   AddPrt_op();
					   break;
				   }*/
			case   ADD_ATM :
				   {
					   AddAtm_op();	// добавить нетипизированный атом
					   break;
				   }
			case   DEL_ATM :
				   {
					   DelAtm_op();	// удалить атом
					   break;
				   }
			case   ADD_BND :
				   {
					   AddBnd_op();	// добавить связь
					   break;
				   }
			case   DEL_BND :
				   {
					   DelBnd_op();	// удалить связь
					   break;
				   }
			case   UNI_MOL :
				   {
					   UniMol_op();	// объединть две молекулы
					   break;
				   }
			case   SEP_MOL :
				   {
					   SepMol_op();	// разъединить молекулу на две
					   break;
				   }

			case   CHG_TYP :
				   {
					   ChgTyp_op();	// изменить тип атома
					   break;
				   }
			case   CHG_BND :
				{
					ChgBnd_op();	// изменить тип связи
					break;
				}
			case   MOV_ATM :
				   {
					   MovAtm_op();	// поступательное смещение атома
					   break;
				   }
			case  MOV_MOL :
				   {
						MovMol_op();
						break;
				   }
			case  MOV_FRG :
				   {
						MovFrg_op();
						break;
				   }
			case SWP_ATM :
					{
						SwpAtm_op();
						break;
					}
			case SWP_MOL :
					{
						SwpMol_op();
						break;
					}
			case ADD_PAA :
					{
						AddPaa_op();
						break;
					}
			case DEL_PAA :
					{
						DelPaa_op();
						break;
					}
			case DEL_AMN :
					{
						DelAmn_op();
						break;
					}
			case ADD_AMN :
					{
						AddAmn_op();
						break;
					}
			case DEL_CHN :
					{
						DelChn_op();
						break;
					}
			case ADD_CHN :
					{
						AddChn_op();
						break;
					}
			case DEL_PRT :
					{
						DelPrt_op();
						break;
					}
			case ADD_PRT :
					{
						AddPrt_op();
						break;
					}
			case   STOP_OP :
				   {

					   break;
				   }
			}
		}
		id_cr_op++;
	}
	if(id_cr_op<=1)
	{
		undoAction->setEnabled(false);
	}

	unmodel->updateModel();
	rdmodel->updateModel();
}
void undoredo::reset_op()	// сброс операций описанных впереди от текущего положения индикатора операций
{
	int ii;
	ii	= operations.N;
	ii--;
	for(;ii>=id_cr_op;ii--)
	{
		switch (operations.x[ii].x[0])
		{
		case   ADD_MOL :
			{
				id_ml_dl_op.N--;
				ml_br_dl_op.N--;
				Molecule *mol	= ml_br_dl_op.x[ml_br_dl_op.N];
				if (ml_br_dl_op.fnd(mol)==-1)// найти ниаменьший номер ячейки с указателем совпадаюсщим с текущим указателем
				{	// если дугих таких таких указателей нет, то  данные по текущему указателю можно удалять
					delete ml_br_dl_op.x[ml_br_dl_op.N];
				}
				ml_br_dl_op.x[ml_br_dl_op.N]	= 0x0;
				break;
			}
		case   DEL_MOL :
			{
				id_ml_dl_op.N--;	// удалить молекулу
				ml_br_dl_op.N--;
				Molecule *mol	= ml_br_dl_op.x[ml_br_dl_op.N];
				if (ml_br_dl_op.fnd(mol)==-1)// найти ниаменьший номер ячейки с указателем совпадаюсщим с текущим указателем
				{	// если дугих таких таких указателей нет, то  данные по текущему указателю можно удалять
					delete ml_br_dl_op.x[ml_br_dl_op.N];
					
				}
				ml_br_dl_op.x[ml_br_dl_op.N]	= 0x0;
				break;
			}
		case   ADD_ATM :
			{
				id_at_br_op.N--;	// добавить нетипизированный атом
				id_at_dl_op.N--;
				break;
			}
		case   DEL_ATM :
			{
				
				id_at_br_op.N--;	// удалить нетипизированный атом
				id_at_dl_op.N--;
				break;
			}
		case   ADD_BND :
			{
				id_bn_br_op.N--;
				id_bn_dl_op.N--;
				break;
			}
		case   DEL_BND :
			{
				id_bn_br_op.N--;
				id_bn_dl_op.N--;
				break;
			}
		case   UNI_MOL :
			{
				id_ml_un_op.N--;
				id_ml_sp_op.N--;
				break;
			}
		case   SEP_MOL :
			{
				id_ml_un_op.N--;
				id_ml_sp_op.N--;
				break;
			}

		case   CHG_TYP :
			{
				id_at_tp_op.N--;
				if(ptr_dat_op.x[id_at_tp_op.N]!=0x0)
				{
					delete ptr_dat_op.x[id_at_tp_op.N];
					ptr_dat_op.x[id_at_tp_op.N]	= 0x0;
				}
				ptr_dat_op.N--;
				break;
			}
		case   CHG_BND :
			{
				id_bn_tp_op.N--;
				break;
			}
		case   MOV_ATM :
			{
				at_mv_op.N--;
				break;
			}
		case  MOV_MOL :
			{
				ml_mv_op.N--;
				break;
			}
		case  MOV_FRG :
			{
				fr_mv_op.N--;
				break;
			}

		case SWP_ATM :
			{
				id_at_sw_op.N--;
				break;
			}
		case SWP_MOL :
			{
				id_ml_sw_op.N--;
				break;
			}
		case ADD_PAA :
			{
				id_pr_at_op.N--;
				//id_pr_dl_op.N--;
				break;
			}
		case DEL_PAA :
			{
				id_pr_at_op.N--;
				//id_pr_dl_op.N--;
				break;
			}
		case DEL_AMN :
			{
				id_pr_am_op.N--;
				break;
			}
		case ADD_AMN :
			{
				id_pr_am_op.N--;
				break;
			}
		case DEL_CHN :
			{
				id_pr_ch_op.N--;
				break;
			}
		case ADD_CHN :
			{
				id_pr_ch_op.N--;
				break;
			}
		case DEL_PRT :
			{
				id_pr_pr_op.N--;
				break;
			}
		case ADD_PRT :
			{
				id_pr_pr_op.N--;
				break;
			}
		case   STOP_OP :
			{
				break;
			}
		}
	}
	operations.N	= id_cr_op;
	redoAction->setEnabled(false);
}

void undoredo::reset_all()	// сброс всех операций
{
	id_cr_op	= 1;
	reset_op();
}

void undoredo::chesk_reset()
{
	if(operations.N!=id_cr_op) reset_op();
}
// ----------------------------

#endif