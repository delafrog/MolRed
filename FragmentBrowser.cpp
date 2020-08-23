#ifndef FRAGMENTBROWSER_CPP
#define FRAGMENTBROWSER_CPP


#include <QWidget>//<QtGui>
#include <QtOpenGL>
#include "linalg.h"
//#include "linalg.cpp"
#include <QSplitter>
#include "rdwrfls.h"
#include "FragmentBrowser.h"
#include <QStringList>
#include <QTreeView>
#include <QDir>


//-----------------------------------
FragmentItem::FragmentItem(const QList<QVariant> &data, FragmentItem *parent)
{
    parentItem = parent;
    itemData = data;
}
//---------------------
FragmentItem::~FragmentItem()
{
    qDeleteAll(childItems);
}
//---------------------
void FragmentItem::appendChild(FragmentItem *item) // метод добавления дочернего элемента
{
    childItems.append(item);	// добавление производиться с помощью метода класса QList
}
//---------------------
FragmentItem *FragmentItem::child(int row) // возвращает указатель на дочерний элемент с номером 'row' в списке текущего элемента
{
    return childItems.value(row);
}
//---------------------
int FragmentItem::childCount() const // возвращает количество дочерних элементов
{
    return childItems.count();
}
//---------------------
int FragmentItem::columnCount() const // возвращает количество столбцов
{
    return itemData.count();
}
//---------------------
QVariant FragmentItem::data(int column) const // возвращает данные для столбца с номером 'column'
{
    return itemData.value(column);
}
//---------------------
FragmentItem *FragmentItem::parent()  // возвращает указатель на родительский элемент
{
    return parentItem;
}
//---------------------
int FragmentItem::row() const  // возвращает номер текущего элемента в списке родительского
{
    if (parentItem)
        return parentItem->childItems.indexOf(const_cast<FragmentItem*>(this));

    return 0;
}
//-------------------------------------------------



//-------------------------------------------------

FragmentList::FragmentList(const QString &data, QObject *parent)
    : QAbstractItemModel(parent)
{
    QList<QVariant> rootData;
    //rootData << "Title" << "Summary";
	rootData << "Fragments";
    rootItem = new FragmentItem(rootData);
    setupModelData(data.split(QString("\n")), rootItem);
}
//---------------------
FragmentList::FragmentList(QObject *parent)
    : QAbstractItemModel(parent)
{
    QList<QVariant> rootData;
    rootData << "Fragments";
    rootItem = new FragmentItem(rootData);
}
//---------------------
FragmentList::~FragmentList()
{
    delete rootItem;
}
//---------------------
int FragmentList::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<FragmentItem*>(parent.internalPointer())->columnCount();
    else
        return rootItem->columnCount();
}
//---------------------
QVariant FragmentList::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    FragmentItem *item = static_cast<FragmentItem*>(index.internalPointer());

    return item->data(index.column());
}
//---------------------
Qt::ItemFlags FragmentList::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}
//---------------------
QVariant FragmentList::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}
//---------------------
QModelIndex FragmentList::index(int row, int column, const QModelIndex &parent)
            const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    FragmentItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<FragmentItem*>(parent.internalPointer());

    FragmentItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}
//---------------------
QModelIndex FragmentList::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    FragmentItem *childItem = static_cast<FragmentItem*>(index.internalPointer());
    FragmentItem *parentItem = childItem->parent();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}
//---------------------
int FragmentList::rowCount(const QModelIndex &parent) const
{
    FragmentItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<FragmentItem*>(parent.internalPointer());

    return parentItem->childCount();
}
//---------------------
void FragmentList::setupModelData(const QStringList &lines, FragmentItem *parent)
{
    QList<FragmentItem*> parents;
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
            parents.last()->appendChild(new FragmentItem(columnData, parents.last()));
        }

        number++;
    }
}
//---------------------
void FragmentList::setUpModelData()	// установить данные для модели
{
	QList<FragmentItem*> parents;
    //parents << rootItem;

	QDir *dir;

	dir				= new QDir;

	dir->cd(tr("Structures"));

	QString loc_str;
	uint tdf;

	loc_str	= dir->dirName();
	tdf	= dir->count();
	loc_str	= dir->currentPath();

	QList<QString> flst,flst2;
	QList<QVariant> columnData;

	flst	= dir->entryList();

	int nn,ii,mm,jj;
	nn	= flst.count();

	//vecT<char> str;

	for(ii=2;ii<nn;ii++)
	{
		parents << rootItem;
		columnData.clear();
		columnData.append(QVariant (flst[ii]));
		parents.last()->appendChild(new FragmentItem(columnData,parents.last()));
		dir->cd(flst[ii]);
		dir->cd(tr("hin"));

		flst2	= dir->entryList();
		mm		= flst2.count();
		parents<<parents.last()->child(parents.last()->childCount()-1);
		for(jj=2;jj<mm;jj++)
		{
			columnData.clear();
			loc_str	= flst2[jj];
			tdf	= loc_str.size()-4;
			loc_str.remove(tdf,4);
			loc_str.replace('_',' ');
			columnData.append(QVariant (loc_str));
			loc_str	= dir->filePath(flst2[jj]);
			columnData.append(QVariant (loc_str));
			parents.last()->appendChild(new FragmentItem(columnData,parents.last()));
		}
		dir->cdUp();
		dir->cdUp();
	}

}
//--------------------------------------------------------------



//--------------------------------------------------------------
ViewScene::ViewScene(QWidget *parent) : QGLWidget(parent)
{
	setFormat(QGLFormat(QGL::DoubleBuffer|QGL::DepthBuffer));
	
	camPos[0]	= 5;
	camPos[1]	= 7;
	camPos[2]	= 7;

	focPos[0]	= 0.0;
	focPos[1]	= 0.0;
	focPos[2]	= 0.0;

	camOZ[0]	= focPos[0]-camPos[0];
	camOZ[1]	= focPos[1]-camPos[1];
	camOZ[2]	= focPos[2]-camPos[2];

	double q;
	q	= sqrt(camOZ[0]*camOZ[0]+camOZ[1]*camOZ[1]+camOZ[2]*camOZ[2]);
	camOZ[0]	/= q;
	camOZ[1]	/= q;
	camOZ[2]	/= q;

	camOX[0]	= 1.0;
	camOX[1]	= 0.0;
	camOX[2]	= 0.0;

	camOY[0]	= camOZ[1]*camOX[2]-camOZ[2]*camOX[1];
	camOY[1]	= camOZ[2]*camOX[0]-camOZ[0]*camOX[2];
	camOY[2]	= camOZ[0]*camOX[1]-camOZ[1]*camOX[0];

	q	= sqrt(camOY[0]*camOY[0]+camOY[1]*camOY[1]+camOY[2]*camOY[2]);
	camOY[0]	/= q;
	camOY[1]	/= q;
	camOY[2]	/= q;


	camOX[0]	= camOY[1]*camOZ[2]-camOY[2]*camOZ[1];
	camOX[1]	= camOY[2]*camOZ[0]-camOY[0]*camOZ[2];
	camOX[2]	= camOY[0]*camOZ[1]-camOY[1]*camOZ[0];

	q	= sqrt(camOX[0]*camOX[0]+camOX[1]*camOX[1]+camOX[2]*camOX[2]);
	camOX[0]	/= q;
	camOX[1]	/= q;
	camOX[2]	/= q;

	qobj = gluNewQuadric(); 
}


/*void ViewScene::setAtoms(vecT<vec3db> &crd, vecT<vec3int> &clr, vecT<double> &rad)	// установка координат атомов и их радиусов для отображения
{
	xyz.pst(crd);
	color.pst(clr);
	radius.pst(rad);

	int ii;
	rc	= 0.0;
	for(ii=0;ii<xyz.N;ii++)
	{
		rc	+= xyz.x[ii];
	}
	rc	/= double(xyz.N);
}*/

void ViewScene::initializeGL()
{
 	qglClearColor(Qt::black);	// установка цвета фона - чёрный
	glShadeModel(GL_SMOOTH);	// установка типа глаживания поверхности - гладкий
	glEnable(GL_DEPTH_TEST);	// включение теста глубины по z-координате 
	glEnable(GL_CULL_FACE);		// режим отображеиня поверхностей... 
}

void ViewScene::resizeGL(int width, int height)
{
	glViewport(0,0,width,height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat x	= GLfloat(width)/height;
	glFrustum(-x,x,-1,1,2,1000.0);
	//gluPerspective ( 60.0, x, 1.0, 1000.0 );
	glMatrixMode(GL_MODELVIEW);
}

void ViewScene::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	draw();
}


void ViewScene::draw()
{

	// свет
	glDisable(GL_LIGHT0);
	//GLfloat light_ambient[] = {0.0, 0.0, 0.0, 0};
	GLfloat light_diffuse[] = {0.2, 0.2, 0.2, 1};

	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_diffuse);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// переход в режим моделт
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	gluLookAt (camPos[0],camPos[1],camPos[2],focPos[0],focPos[1],focPos[2],camOY[0],camOY[1],camOY[2]); // ориентация камеры
	glCallList(theMol);	// рисование струкруры подготовленной ранее

}


void ViewScene::mousePressEvent(QMouseEvent *event)
{
	lastPos	= event->pos();
}


void ViewScene::mouseMoveEvent(QMouseEvent *event)
{

	GLfloat dx	= GLfloat(event->x()-lastPos.x())/width();
	GLfloat dy	= GLfloat(event->y()-lastPos.y())/height();


	double q,alf,bet,cs1,sn1,cs2,sn2;
	GLfloat x,y,z,x1,y1,z1,x2,y2,z2,x3,y3,z3;


	x	= focPos[0]-camPos[0]; // вектор в точку наблюдения из центра камеры
	y	= focPos[1]-camPos[1];
	z	= focPos[2]-camPos[2];

	q	= sqrt(x*x+y*y+z*z); // расстояние до точки наблюдения

	alf	= 10*dx;	// угол поворота вокру вертикальной (относительно экрана) оси
	bet	= 10*dy;	// угол поворота вокру горизонтальной (относительно экрана) оси
	cs2	= cos(alf);
	sn2	= -sin(alf);
	cs1	= cos(bet);
	sn1	= -sin(bet);


	// новые координаты базиса камеры
	x2	= (cs1*camOY[0]+sn1*camOZ[0]);
	y2	= (cs1*camOY[1]+sn1*camOZ[1]);
	z2	= (cs1*camOY[2]+sn1*camOZ[2]);

	x3	= (-sn1*camOY[0]+cs1*camOZ[0]);
	y3	= (-sn1*camOY[1]+cs1*camOZ[1]);
	z3	= (-sn1*camOY[2]+cs1*camOZ[2]);

	x1	= camOX[0];
	y1	= camOX[1];
	z1	= camOX[2];

	camOX[0]	= (cs2*x1+sn2*x3);
	camOX[1]	= (cs2*y1+sn2*y3);
	camOX[2]	= (cs2*z1+sn2*z3);

	camOY[0]	= x2;
	camOY[1]	= y2;
	camOY[2]	= z2;

	camOZ[0]	= (-sn2*x1+cs2*x3);
	camOZ[1]	= (-sn2*y1+cs2*y3);
	camOZ[2]	= (-sn2*z1+cs2*z3);/**/


	x	= -q*x3;
	y	= -q*y3;
	z	= -q*z3;

	// новое положение камеры
	camPos[0]	= x+focPos[0];
	camPos[1]	= y+focPos[1];
	camPos[2]	= z+focPos[2];



	updateGL();


	lastPos	= event->pos();
}

void ViewScene::wheelEvent(QWheelEvent *event)
{
	double q,dq;
	GLfloat x,y,z;

	x	= focPos[0]-camPos[0];
	y	= focPos[1]-camPos[1];
	z	= focPos[2]-camPos[2];

	q	= sqrt(x*x+y*y+z*z);

	x	/= q;
	y	/= q;
	z	/= q;

	dq	= GLfloat(event->delta())/100;

	q	+= q>10 ? dq : (q>5 ? 0.5*dq : q>1 ? 0.1*dq : 0.05*abs(dq) );

	camPos[0]	= focPos[0]-q*x;
	camPos[1]	= focPos[1]-q*y;
	camPos[2]	= focPos[2]-q*z;
	updateGL();
}

void ViewScene::genScene()	// сгенерировать сцену с молекулой
{
	if(wrkFrm->Mls.N>0)
	{
		double x,y,z,rd;//x0,y0,z0,rd;
		int ia;
		double r,g,b,r1,g1,b1;
		vec3db	rc;

		GLfloat param[4];

		vec3db pnt;

		//	int scenetype	= 1;


		if (theSph!=0){glDeleteLists(theSph, 8);}
		theSph=glGenLists(8);
		glNewList(theSph,GL_COMPILE);
		gluQuadricDrawStyle(qobj, GLU_FILL); 
		gluSphere(qobj,1,30,21);
		glEndList();

		GLdouble base,top,height;
		GLint slices,stacks;

		height	= base	= top	= 1.0;
		slices	= 20;
		stacks	= 2;

		double kf	= 0.7;// коэффициент для уменьшения цилиндров тройных связей
		
		if (theCyl!=0){glDeleteLists(theCyl, 9);}
		theCyl=glGenLists(9);
		glNewList(theCyl,GL_COMPILE);
		gluQuadricDrawStyle(qobj, GLU_FILL); 	
		gluCylinder(qobj,  base,  top,  height,  slices, stacks); 
		glEndList();

		if (the2Cyl!=0){glDeleteLists(the2Cyl, 10);}
		the2Cyl=glGenLists(10);
		glNewList(the2Cyl,GL_COMPILE);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslated(-1,0,0);
		gluQuadricDrawStyle(qobj, GLU_FILL); 	
		gluCylinder(qobj,  base,  top,  height,  slices, stacks); 
		glTranslated(2.0,0,0);
		gluQuadricDrawStyle(qobj, GLU_FILL); 	
		gluCylinder(qobj,  base,  top,  height,  slices, stacks); 
		glPopMatrix();
		glEndList();

		
		if (the3Cyl!=0){glDeleteLists(the3Cyl, 11);}
		the3Cyl=glGenLists(11);
		glNewList(the3Cyl,GL_COMPILE);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		//glTranslated(0,1,0);
		glTranslated(0,0,0);
		gluQuadricDrawStyle(qobj, GLU_FILL); 	
		gluCylinder(qobj,  base*kf,  top*kf,  height,  slices, stacks); 
		//glTranslated(-0.866,-1.5,0);
		glTranslated(2*kf,0,0);
		gluQuadricDrawStyle(qobj, GLU_FILL); 	
		gluCylinder(qobj,  base*kf,  top*kf,  height,  slices, stacks); 
		//glTranslated(1.732,0,0);
		glTranslated(-4*kf,0,0);
		gluQuadricDrawStyle(qobj, GLU_FILL); 	
		gluCylinder(qobj,  base*kf,  top*kf,  height,  slices, stacks); 
		glPopMatrix();
		glEndList();


		if (theMol!=0){glDeleteLists(theMol, 12);}
		theMol=glGenLists(12);
		glNewList(theMol,GL_COMPILE);

		int ii,jj;

		rc	= 0.0;
		for(ii=0;ii<wrkFrm->Mls.x[0]->Atoms.N;ii++)
		{
			rc	+= wrkFrm->Mls.x[0]->Atoms.x[ii].r;
		}
		rc	/= wrkFrm->Mls.x[0]->Atoms.N;

		for(ii=0;ii<wrkFrm->Mls.x[0]->Atoms.N;ii++)
		{
			x	= wrkFrm->Mls.x[0]->Atoms.x[ii].r.x[0]-rc.x[0];
			y	= wrkFrm->Mls.x[0]->Atoms.x[ii].r.x[1]-rc.x[1];
			z	= wrkFrm->Mls.x[0]->Atoms.x[ii].r.x[2]-rc.x[2];

			jj	= wrkFrm->Mls.x[0]->Atoms.x[ii].id_Tpz;

			r	= double(wrkFrm->TableZR.Lines.x[jj].color.x[0])/256;
			g	= double(wrkFrm->TableZR.Lines.x[jj].color.x[1])/256;
			b	= double(wrkFrm->TableZR.Lines.x[jj].color.x[2])/256;

			rd	= wrkFrm->TableZR.Lines.x[jj].vdwrad/500;
			if (rd<=0) rd	= wrkFrm->TableZR.Lines.x[jj].cvlrad/200;


			glTranslated(x,y,z);
			glScaled(rd,rd,rd);

			param[0]	= r;param[1]	= g;param[2]	= b;param[3]	= 0;
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE,param);
			glCallList(theSph);
			glScaled(1/rd,1/rd,1/rd);
			glTranslated(-x,-y,-z);

		}/**/


		double dx,dy,dz,fi,th,lb;//,x0,y0,z0,rd;
		const double pi=3.1415926535897932384626433832795;

		for(ii=0;ii<wrkFrm->Mls.x[0]->Bonds.N;ii++)
		{
			ia	= wrkFrm->Mls.x[0]->Bonds.x[ii].id_Atoms.x[0];
			x	= wrkFrm->Mls.x[0]->Atoms.x[ia].r.x[0]-rc.x[0];
			y	= wrkFrm->Mls.x[0]->Atoms.x[ia].r.x[1]-rc.x[1];
			z	= wrkFrm->Mls.x[0]->Atoms.x[ia].r.x[2]-rc.x[2];

			ia	= wrkFrm->Mls.x[0]->Atoms.x[ia].id_Tpz;

			r	= double(wrkFrm->TableZR.Lines.x[ia].color.x[0])/256;
			g	= double(wrkFrm->TableZR.Lines.x[ia].color.x[1])/256;
			b	= double(wrkFrm->TableZR.Lines.x[ia].color.x[2])/256;

			ia	= wrkFrm->Mls.x[0]->Bonds.x[ii].id_Atoms.x[1];
			dx	= (wrkFrm->Mls.x[0]->Atoms.x[ia].r.x[0]-rc.x[0])-x;
			dy	= (wrkFrm->Mls.x[0]->Atoms.x[ia].r.x[1]-rc.x[1])-y;
			dz	= (wrkFrm->Mls.x[0]->Atoms.x[ia].r.x[2]-rc.x[2])-z;


			ia	= wrkFrm->Mls.x[0]->Atoms.x[ia].id_Tpz;

			r1	= double(wrkFrm->TableZR.Lines.x[ia].color.x[0])/256;
			g1	= double(wrkFrm->TableZR.Lines.x[ia].color.x[1])/256;
			b1	= double(wrkFrm->TableZR.Lines.x[ia].color.x[2])/256;

			lb	= sqrt(dx*dx+dy*dy+dz*dz);
			th	= acos(dz/lb);
			if ((dx*dx+dy*dy)>1e-40)
			{
				fi	= acos(dx/sqrt(dx*dx+dy*dy));
				fi	= (dy>0) ? fi : -fi;
			}
			else
			{
				fi	= 0.0;
			}


			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();

			glTranslated ( x, y, z); 
			glRotated ( 180*fi/pi, 0, 0, 1);
			glRotated ( 180*th/pi, 0, 1, 0);


			glScaled (0.07, 0.07, 0.5*lb); 
			//glColor3d(r,g,b);
			param[0]	= r/3;param[1]	= g/3;param[2]	= b/3;param[3]	= 0;
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE,param);
			if(wrkFrm->Mls.x[0]->Bonds.x[ii].oder==1)
			{
				glCallList(theCyl);			
			}
			else
			{
				if(wrkFrm->Mls.x[0]->Bonds.x[ii].oder==2)
				{
					glCallList(the2Cyl);
				}
				else 
				{
					glCallList(the3Cyl);
				}
			}
			glTranslated ( 0, 0, 1); 
			//glColor3d(r1,g1,b1);
			param[0]	= r1/3;param[1]	= g1/3;param[2]	= b1/3;param[3]	= 0;
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE,param);
			if(wrkFrm->Mls.x[0]->Bonds.x[ii].oder==1)
			{
				glCallList(theCyl);			
			}
			else
			{
				if(wrkFrm->Mls.x[0]->Bonds.x[ii].oder==2)
				{
					glCallList(the2Cyl);
				}
				else 
				{
					glCallList(the3Cyl);
				}
			}/**/

			glPopMatrix();


		}/**/
		glEndList();
	}else
	{
		if (theMol!=0){glDeleteLists(theMol, 12);}
		if (theSph!=0){glDeleteLists(theSph, 8);}
		if (theCyl!=0){glDeleteLists(theCyl,9);}
		if (the2Cyl!=0){glDeleteLists(the2Cyl, 10);}
		if (the3Cyl!=0){glDeleteLists(the3Cyl, 11);}
	}
}


//________________________________________________________________________________________________________

FragmentBrowser::FragmentBrowser(QWidget *parent ) : QWidget(parent)
{
	//FragmentBrowser(QWidget *parent = 0);
	setWindowTitle(tr("Add Fragment"));

	fragmentList	= new FragmentList;
	treeView		= new QTreeView;

	treeView->setModel(fragmentList);
	
	viewScene		= new ViewScene;
	splitterWidget	= new QSplitter;


	viewScene->resize(150,100);
	viewScene->setFocusPolicy(Qt::StrongFocus);

	splitterWidget->setOrientation(Qt::Horizontal);
	splitterWidget->addWidget(treeView);
	splitterWidget->addWidget(viewScene);	
	splitterWidget->setStretchFactor(1,1);

	QHBoxLayout *layout	= new QHBoxLayout;

	layout->addWidget(splitterWidget);

	setLayout(layout);

	fragmentList->setUpModelData();

	connect(treeView,SIGNAL(clicked(const QModelIndex & )),this,SLOT(getfilename(const QModelIndex &)));
	connect(treeView,SIGNAL(activated(const QModelIndex & )),this,SLOT(getfilename(const QModelIndex &)));
	//connect(treeView,SIGNAL(pressed(const QModelIndex & )),this,SLOT(getfilename(const QModelIndex &)));

	resize(600,300);
	
	desfrg();

	setWindowIcon(QIcon(":/images/fragm1.png"));
	setWindowFlags(Qt::WindowStaysOnTopHint);

}

void FragmentBrowser::closeEvent(QCloseEvent * event)
{
	desfrg();
	event->accept();
}


WorkFrame *	 FragmentBrowser::getwrkFrm()// вернуть значение указателя workFrame
{
	return &workFrame;
}

void FragmentBrowser::getfilename(const QModelIndex & index)
{
	QVariant loc;
	FragmentItem *item = static_cast<FragmentItem*>(index.internalPointer());
	int column;
	column	= index.column();
	column++;
	loc			= item->data(column);//fragmentList->data(index, Qt::DisplayRole);//Qt::UserRole);
	filename	= loc.toString(); // получение имени файла с данными о структуре

	workFrame.Mls.N	= 0;
	workFrame.readFile(filename);
	viewScene->setMol(&workFrame);
	viewScene->genScene();
	viewScene->updateGL();
	if(workFrame.Mls.N>0){detfrg();}else{desfrg();}
}

#endif