#ifndef FRAGMENTBROWSER_H
#define FRAGMENTBROWSER_H

#include <Windows.h>
#include <GL\GLU.h>
//#include <GL\GL.h>


#include<QWidget>
#include <QGLWidget>
#include "linalg.h"
//#include "linalg.cpp"
#include "datatypes.h"
#include <QAbstractItemModel>
//class WorkFrame;
#include "rdwrfls.h"
class QSplitter;
class QTreeView;
class QDir;
//class QWidget;

class FragmentItem
{
public:
    FragmentItem(const QList<QVariant> &data, FragmentItem *parent = 0);// ����������� � �����������
    ~FragmentItem();

    void appendChild(FragmentItem *item);	// ����� ���������� ��������� ��������

    FragmentItem *child(int row);	// ���������� ��������� �� �������� ������� � ������� 'row' � ������ �������� ��������
    int childCount() const;			// ���������� ���������� �������� ���������
    int columnCount() const;		// ���������� ���������� �������� 
    QVariant data(int column) const;// ���������� ������ ��� ������� � ������� 'column'
    int row() const;				// ���������� ����� �������� �������� � ������ �������������
    FragmentItem *parent();			// ���������� ��������� �� ������������ �������

private:
    QList<FragmentItem*> childItems;	// ������ ���������� �� �������� ��������
    QList<QVariant> itemData;			// ������ ������ ��� �������� ��������
    FragmentItem *parentItem;			// ��������� �� ������������ �������
};

class FragmentList : public QAbstractItemModel
{
	Q_OBJECT

public:
    FragmentList(const QString &data, QObject *parent = 0);
	FragmentList(QObject *parent = 0);
    ~FragmentList();

    QVariant data(const QModelIndex &index, int role) const;			// ���������� ������ �� ������� 'index' 
    Qt::ItemFlags flags(const QModelIndex &index) const;				// ����-������� ��� �������� ��� ������ ������ ��� ������
    QVariant headerData(int section, Qt::Orientation orientation,int role = Qt::DisplayRole) const;	// ���������� ������ ��� ���������
    QModelIndex index(int row, int column,const QModelIndex &parent = QModelIndex()) const;			// ���������� ������ �������� �� ��� ������ � �������
    QModelIndex parent(const QModelIndex &index) const;					// ���������� ������ �������� ��� �������� � �������� 'index'
    int rowCount(const QModelIndex &parent = QModelIndex()) const;		// ���������� ����� �������� �������� ��� �������� � �������� ��������
    int columnCount(const QModelIndex &parent = QModelIndex()) const;	// ���������� ����� ��������

	void setUpModelData();	// ���������� ������ ��� ������
private:
    void setupModelData(const QStringList &lines, FragmentItem *parent);// ������������� ������ � ������
    FragmentItem *rootItem;												// ��������� �� �������� �������
};


class ViewScene : public QGLWidget
{
	Q_OBJECT
public:
	ViewScene(QWidget *parent = 0);
	~ViewScene(){gluDeleteQuadric(qobj);}

	void setMol(WorkFrame *in_mol){wrkFrm = in_mol;}	// ��������� ��������� ������ � �� �������� ��� �����������
	void genScene();	// ������������� ����� � ���������
protected:
	void initializeGL();
	void resizeGL(int width,int height);
	void paintGL();

	void mousePressEvent(QMouseEvent *event);
	//void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	//void mouseDoubleClickEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);
	/*void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);
	void enterEvent(QEvent *event);
	void leaveEvent(QEvent *event);
*/

private:
	void draw();

	QPoint	lastPos;

	GLfloat	camPos[3];	// ��������� ������	(� ���������� ������� ���������)
	GLfloat	camOX[3];	// ���������� ������ (� ���������� ������� ���������)
	GLfloat	camOY[3];	// ���������� ������ (� ���������� ������� ���������)
	GLfloat	camOZ[3];	// ���������� ������ (� ���������� ������� ���������)
	GLfloat focPos[3];	// ����� ������ ������ (������ ������� ���������� ��������) (� ���������� ������� ���������)

	GLUquadricObj *qobj;

	int theMol,theSph,theCyl,the2Cyl,the3Cyl;


	WorkFrame		*wrkFrm;
	//SmplTpzlTable	TZR;	// ������� ����� ������ � �� ����������
	//Molecule *mol;
	//vec3db	rc;
	//vecT<vec3db> xyz;
	//vecT<vec3int> color;
	//vecT<double> radius;
};

class FragmentBrowser : public QWidget
{
	Q_OBJECT

public:
	FragmentBrowser(QWidget *parent =0);

	WorkFrame *		getwrkFrm();// ������� �������� ��������� workFrame

public slots:
	void getfilename(const QModelIndex & index);
protected:
	void closeEvent(QCloseEvent* event);
signals:
	void detfrg();
	void desfrg();
	
private:

	QString			filename;
	QTreeView		*treeView;
	FragmentList	*fragmentList;
	ViewScene		*viewScene;

	QSplitter		*splitterWidget;

	WorkFrame		workFrame;
	

};

#endif