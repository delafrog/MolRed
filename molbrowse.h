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

class TreeItem // ���� ������ ������������� ������
{
public:

	enum Type {Root,Surface,Area,Bound,Supra,Complex,Protein,Ligand,Molecule,Fragment,Atom,Chain,AminoAcid}; // ���� ��������� ���������

    TreeItem(const QList<QVariant> &data, TreeItem *parent = 0); // ����������� ��� ����������� ���� ����
	TreeItem(const Type &typ, TreeItem *parent = 0);	// ����������� � ������������ ���� ����, �� ��� ����������� ������ � �����
	TreeItem(const Type &typ,const QList<QVariant> &data, TreeItem *parent = 0);// ����������� � ������������ ���� ���� � ������ � �����
    ~TreeItem();

    void appendChild(TreeItem *child);	// �������� �������� ����
	//void clearChild();

	Type type;	// ��� ����
    TreeItem *child(int row); //  ��������� ��������� �� �������� ���� � ������� row
    int childCount() const;		// ���������� ���������� �������� �����
    int columnCount() const;   // ���������� ���������� ������ � ������� ����
    QVariant data(int column) const; // ��������� ������ ����
    int row() const;  // ���������� ����� ������
    TreeItem *parent(); // ���������� ��������� �� ������ ������� (������������ �������)

private:
    QList<TreeItem*> childItems; // ������ ���������� �� �������� ����
    QList<QVariant> itemData;	// ������ ������ �����
    TreeItem *parentItem;	// ��������� �� ������ ������� (������������)
};


//class TreeItem;

class TreeModel : public QAbstractItemModel // ������ ������������� ������ � ���� ������
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
	void updateModel();//const Molecule &mol,SmplTpzlTable &tbl);	// �������� ������
	void clearAllModelData();
	void setWF(WorkFrame *in_wf);

private:
    void setupModelData(const QStringList &lines, TreeItem *parent); 

	WorkFrame *WF;

    TreeItem *rootItem; // ��������� �� ����� ������� �������
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
	void markAnalize();	// ������ ���������� ������� ����
	void markAnalize4();	// ������ ���������� ������� ����
	void markAnalize5();	// ������ ���������� ������� ����
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

	vecT<vec2int> ida;	// ��������� ����� � ���������
	vecT<vec3int> idam; // ���������� ������������
	vecT<int> ids;	// ���������� ����������
	int s_type;		// ��� �������� ��� ����������� �������������
	//double 
	vec3int col;
	//QModelIndex loc_item;
};


#endif