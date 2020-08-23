#ifndef MOLBROWSE_H
#define MOLBROWSE_H


/*class QString;
class QVariant;
class QAbstractItemModel;
class QModelIndex;
class QList;*/

#include <QString>
#include <QtAlgorithms>
#include <QVariant>
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QList>
#include <QTreeView>
#include "linalg.h"

class WorkFrame;
class Molecule;
class SmplTpzlTable;
class QMenu;
class QAction;

class QKeyEvent;

class TreeItem // узел дерева представления данных
{
public:

	enum Type {Root,Surface,Area,Bound,Supra,Complex,Protein,Ligand,Molecule,Fragment,Atom,Chain,AminoAcid}; // типы возможных элементов

    TreeItem(const QList<QVariant> &data, TreeItem *parent = 0); // конструктор без определения типа узла
	TreeItem(const Type &typ, TreeItem *parent = 0);	// конструктор с определением типа узла, но без определения данных в узлах
	TreeItem(const Type &typ,const QList<QVariant> &data, TreeItem *parent = 0);// конструктор с определением типа узла и данных в узлах
    ~TreeItem();

    void appendChild(TreeItem *child);	// добавить дочерний узел
	//void clearChild();

	Type type;	// тип узла
    TreeItem *child(int row); //  возвращет указатель на дочерний узел с номером row
    int childCount() const;		// возвращает количество дочерних узлов
    int columnCount() const;   // возвращает количество данных в текущем узле
    QVariant data(int column) const; // возвращет данные узла
    int row() const;  // возвращает номер строки
    TreeItem *parent(); // возвращает указатель на вышний уровень (родительский уровень)

private:
    QList<TreeItem*> childItems; // список указателей на дочерний узлы
    QList<QVariant> itemData;	// список данных узлов
    TreeItem *parentItem;	// указатель на вышний уровень (родительский)
};


//class TreeItem;

class TreeModel : public QAbstractItemModel // модель представления данных в виде дерева
{
    Q_OBJECT

public:
    TreeModel(const QString &data, QObject *parent = 0);
	TreeModel(QObject *parent = 0);
    ~TreeModel();

    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

	//void setupModelData(const Molecule &mol);
	void setUpModelData();//const Molecule &mol,SmplTpzlTable &tbl);
	void updateModel();//const Molecule &mol,SmplTpzlTable &tbl);	// обновить данные
	void clearAllModelData();
	void setWF(WorkFrame *in_wf);

private:
    void setupModelData(const QStringList &lines, TreeItem *parent); 

	WorkFrame *WF;

    TreeItem *rootItem; // указатель на самый верхний уровень
};


class TreeView : public QTreeView
{
	Q_OBJECT
public: 
	TreeView(QWidget *parent = 0);
	~TreeView(){}

	void mouseDoubleClickEvent( QMouseEvent *event);
	void contextMenuEvent ( QContextMenuEvent *e);
	vecT<vec2int> & getselatoms(){return ida;}
	vecT<int> & getselsurfaces(){return ids;}
	int	get_s_type(){return s_type;}
	//double get_s_tsp(){return s_tsp;}

	vec3int & getcolor(){return col;}

public slots:
	void markAnalize();	// анализ помеченных пунктов меню
	void markAnalize4();	// анализ помеченных пунктов меню
	void markAnalize5();	// анализ помеченных пунктов меню
	//void selectionChanged ( const QItemSelection & selected, const QItemSelection & deselected );
	//void markMolAnalize();
	void hideSurf();
	void solidSurf();
	void wireframeSurf();
	void deleteSurf();
	void singleColor();
	void atomsColor();
	void typeColor();
	void transparenceSurf();

signals:
	void selready();
	void selChready();
	void selAmnready();
	void selectMol();
	void changeMol();
	void changeSurf();
	void changecolorSurf();



private:

	void markSurfAnalize();

	QMenu *contextMenu1;
	QMenu *contextMenu2;
	QMenu *contextMenu3;
	QMenu *contextMenu4;
	QMenu *contextMenu5;
	QMenu *colorMenu;
	QAction *contextselectAction1;
	QAction *contextselectAction2_1;
	QAction *contextselectAction2_2;
	QAction *contextselectAction3_1;
	QAction *contextselectAction3_2;
	QAction *contextselectAction3_3;
	QAction *contextselectAction3_4;
	QAction *contextselectAction3_5;
	QAction *contextselectAction4;
	QAction *contextselectAction5;
	QAction *colorAction1;
	QAction *colorAction2;
	QAction *colorAction3;
	QModelIndexList indexlist;

	vecT<vec2int> ida;	// отмеченые атомы в молекулах
	vecT<vec3int> idam; // отмеченные аминокислоты
	vecT<int> ids;	// отмеченные повехности
	int s_type;		// тип действия над отмеченными поверхностями
	//double 
	vec3int col;
	//QModelIndex loc_item;
};


#endif