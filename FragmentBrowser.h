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
    FragmentItem(const QList<QVariant> &data, FragmentItem *parent = 0);// конструктор с заполнением
    ~FragmentItem();

    void appendChild(FragmentItem *item);	// метод добавления дочернего элемента

    FragmentItem *child(int row);	// возвращает указатель на дочерний элемент с номером 'row' в списке текущего элемента
    int childCount() const;			// возвращает количество дочерних элементов
    int columnCount() const;		// возвращает количество столбцов 
    QVariant data(int column) const;// возвращает данные для столбца с номером 'column'
    int row() const;				// возвращает номер текущего элемента в списке родительского
    FragmentItem *parent();			// возвращает указатель на родительский элемент

private:
    QList<FragmentItem*> childItems;	// список указателей на дочерние элементы
    QList<QVariant> itemData;			// список данных для текущего элемента
    FragmentItem *parentItem;			// указатель на родительский элемент
};

class FragmentList : public QAbstractItemModel
{
	Q_OBJECT

public:
    FragmentList(const QString &data, QObject *parent = 0);
	FragmentList(QObject *parent = 0);
    ~FragmentList();

    QVariant data(const QModelIndex &index, int role) const;			// возвращает данные по индексу 'index' 
    Qt::ItemFlags flags(const QModelIndex &index) const;				// флаг-функция для указания что модель только для чтения
    QVariant headerData(int section, Qt::Orientation orientation,int role = Qt::DisplayRole) const;	// возвращает данные для заголовка
    QModelIndex index(int row, int column,const QModelIndex &parent = QModelIndex()) const;			// возвращает индеск элемента по его строке и столбцу
    QModelIndex parent(const QModelIndex &index) const;					// возвращает индекс родителя для элемента с индексом 'index'
    int rowCount(const QModelIndex &parent = QModelIndex()) const;		// возвращает число дочерних элеметов для элемента с заданным индексом
    int columnCount(const QModelIndex &parent = QModelIndex()) const;	// возвращает число столбцов

	void setUpModelData();	// установить данные для модели
private:
    void setupModelData(const QStringList &lines, FragmentItem *parent);// устанавливает данные в модель
    FragmentItem *rootItem;												// указатель на корневой элемент
};


class ViewScene : public QGLWidget
{
	Q_OBJECT
public:
	ViewScene(QWidget *parent = 0);
	~ViewScene(){gluDeleteQuadric(qobj);}

	void setMol(WorkFrame *in_mol){wrkFrm = in_mol;}	// установка координат атомов и их радиусов для отображения
	void genScene();	// сгенерировать сцену с молекулой
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

	GLfloat	camPos[3];	// положение камеры	(в глобальной системе координат)
	GLfloat	camOX[3];	// ориентация камеры (в глобальной системе координат)
	GLfloat	camOY[3];	// ориентация камеры (в глобальной системе координат)
	GLfloat	camOZ[3];	// ориентация камеры (в глобальной системе координат)
	GLfloat focPos[3];	// точка фокуса камеры (вокруг которой происходит вращение) (в глобальной системе координат)

	GLUquadricObj *qobj;

	int theMol,theSph,theCyl,the2Cyl,the3Cyl;


	WorkFrame		*wrkFrm;
	//SmplTpzlTable	TZR;	// таблица типов атомов и их параметров
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

	WorkFrame *		getwrkFrm();// вернуть значение указателя workFrame

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