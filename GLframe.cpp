/*
GLframe.cpp 
реализация методов 3D рендеринга
--------------
MolRed.
Copyright @ Zhabin S.N.
ver. 0.0.1
07.2008
*/

#ifndef GLFRAME_CPP
#define GLFRAME_CPP

#include <QOpenGLWidget>//<QtOpenGL>
#include <QMouseEvent>
#include <QPainter>
#include <QGLWidget>
//#include <QOpenGLFunctions>
#include "GLframe.h"
#include "linalg.h"
//#include "linalg.cpp"
#include <math.h>
#include "rdwrfls.h"
#include "surface.h"
#include "rotat.h"
#include "datatypes.h"
#include "ActualSpace.h"

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE 0x809D
#endif

OpenGLWidget::OpenGLWidget(QWidget *parent) : QGLWidget(parent)
{
	double q;

//	QGLFormat	qlgf(QGL::DoubleBuffer|QGL::DepthBuffer);

	//qlgf.setStereo(true);

//	setFormat(qlgf);
	//setFormat(QGLFormat());
	//setFormat(QGLFormat(QGL::SampleBuffers));


	rotationX	= -21.0;
	rotationY	= -57.0;
	rotationZ	= -0.0;
	faceColors[0]= Qt::red;
	faceColors[1]= Qt::green;
	faceColors[2]= Qt::blue;
	faceColors[3]= Qt::yellow;
	//camPos[0]	= 8.0;
	//camPos[1]	= 7.0;
	//camPos[2]	= 15.0;
	camPos[0]	= 0;
	camPos[1]	= 0;
	camPos[2]	= 50;

	focPos[0]	= 0.0;
	focPos[1]	= 0.0;
	focPos[2]	= 0.0;

	camOZ[0]	= focPos[0]-camPos[0];
	camOZ[1]	= focPos[1]-camPos[1];
	camOZ[2]	= focPos[2]-camPos[2];

	q	= sqrt(camOZ[0]*camOZ[0]+camOZ[1]*camOZ[1]+camOZ[2]*camOZ[2]);
	camOZ[0]	/= q;
	camOZ[1]	/= q;
	camOZ[2]	/= q;

	camOX[0]	= -1.0;
	camOX[1]	= 0.0;
	camOX[2]	= 0.0;

	q	= sqrt(camOX[0]*camOX[0]+camOX[1]*camOX[1]+camOX[2]*camOX[2]);
	camOX[0]	/= q;
	camOX[1]	/= q;
	camOX[2]	/= q;

	camOY[0]	= camOZ[1]*camOX[2]-camOZ[2]*camOX[1];
	camOY[1]	= camOZ[2]*camOX[0]-camOZ[0]*camOX[2];
	camOY[2]	= camOZ[0]*camOX[1]-camOZ[1]*camOX[0];
/**/

	/** /camOX[0]	= 1.0;
	camOX[1]	= 0.0;
	camOX[2]	= 0.0;

	camOY[0]	= 0.0;
	camOY[1]	= 1.0;
	camOY[2]	= 0.0;

	camOZ[0]	= 0.0;
	camOZ[1]	= 0.0;
	camOZ[2]	= 1.0;*/

	VCMPos[0]	= 0.0;
	VCMPos[1]	= 0.0;
	VCMPos[2]	= 0.0;/**/

	
	qobj	= gluNewQuadric(); 
	qobj1	 = gluNewQuadric(); 
	qobj2	 = gluNewQuadric();
	qobj3	 = gluNewQuadric();
	
	isDblRight	= false;

	theMol	= 0;
	theSph	= 0;
	theCyl	= 0;
	the2Cyl	= 0;
	the3Cyl	= 0;
	theSph_		= 0;
	theCyl_		= 0;
	the2Cyl_	= 0;
	the3Cyl_	= 0;
	theSurf		= 0;
	theInvSurf	= 0;
	theAtoms	= 0;
	theBonds	= 0;
	theWires	= 0;
	theMols		= 0;
	theScene	= 0;
	s_id.setmem();
	isShift = false;
	isCtrl	= false;
	isSurf	= false;
	isOrtho	= false;
	isFrameSel	= false;
	isMolSel	= false;
	isRenChAt	= false;

	isRotat		= false;
	isActSpcShow= false;
	isMovQc		= false;// флаг перемещения оси вращения

	isBondLen	= false;
	isValAngl	= false;
	isTorAngl	= false;

	isSelParShow= false;

	isSurfModify= false;

	alf	= 0.0;
	pnr	= 0.0;
	axs	= 0.0;
	


	dis_koeff	= 1.0;

	rc	= 0.0;
	
	isFrgBrw	= false;
	isAtomBrw	= false;

	drawFrame	= false;

	rucon	= ldcon	= 0.0;
	ruc		= ldc	= 0.0;

	id_at	= -1;
	id_ml	= -1;
	addatomtype	= 0;

	z_near	= 2.0;	// расстояние до ближней грани
	z_far	= 1000.0;	// расстояние до дальней грани 
	p_alf	= 60.0;	// угол перспективы
	mgnf	= 2;	// коэффцициент увеличения для отрогональной проекции


	//s_ids	= 0x0;

	colcod	= 0;

	pi	= 3.1415926535897932384626433832795;
	//setCursor(Qt::CrossCursor);
	//setCursor(Qt::BlankCursor);
	connect(this,SIGNAL(closeAtomBwrw()),this,SLOT(AtomBrwOff()));
}

void OpenGLWidget::initializeGL()
{
	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 0.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_position[] = { 1.0, 1.0, 2.0, 0.0 };
	GLfloat light_position_[] = { -0.5, 0.5, 2.0, 0.0 };
	GLfloat light_spot_cutoff = 0.1;

	GLfloat spot_direction[] = { 0.5, -0.50, -2.0 };
	

   // устанавливаем параметры источника света 
	glLightfv (GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv (GL_LIGHT0, GL_DIFFUSE, light_diffuse);
   // glLightfv (GL_LIGHT0, GL_SPECULAR, light_specular);
   glLightfv (GL_LIGHT0, GL_POSITION, light_position);

   glLightfv (GL_LIGHT1, GL_SPECULAR, light_specular);
   glLightfv (GL_LIGHT1, GL_POSITION, light_position_);
   glLightf (GL_LIGHT1, GL_SPOT_CUTOFF, light_spot_cutoff);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);

   // включаем освещение и источник света 
	glEnable (GL_LIGHTING);
	glEnable (GL_LIGHT0);
//	glEnable (GL_LIGHT1);
	

   // включаем z-буфер 
	glEnable(GL_DEPTH_TEST);

	// включение использования альфа-параметра
	glEnable(GL_ALPHA_TEST);

	// включение уствновки свойств материала по glColor
	//glEnable(GL_COLOR_MATERIAL);


	if (colcod == 0)	glClearColor(0.0,0.0,0.0,1.0);// Qt::black);
	else glClearColor(1.0,1.0,1.0,1.0);// Qt::white);
	glShadeModel(GL_SMOOTH);
	//glShadeModel(GL_FLAT);
	//glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	//glEnable(GL_LINE_SMOOTH);


	//glEnable (GL_LINE_SMOOTH);
	//glEnable (GL_BLEND);
	//glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
	//glLineWidth (0.3);

//	glPixelStorei (GL_UNPACK_ALIGNMENT, 1);

	createFontBits();
}

void OpenGLWidget::resizeGL(int width, int height)
{
	glViewport(0,0,width,height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat x	= GLfloat(width)/height;
	//glFrustum(-x,x,-1,1,2,1000.0);
	if (!isOrtho)
		gluPerspective(p_alf, x, z_near, z_far );
	else
		glOrtho(-x*mgnf,x*mgnf,-mgnf,mgnf,z_near,z_far);

	glMatrixMode(GL_MODELVIEW);
}

void OpenGLWidget::reprojGL()
{
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT,viewport);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat x	= GLfloat(viewport[2])/GLfloat(viewport[3]);
	//glFrustum(-x,x,-1,1,2,1000.0);
	if (!isOrtho)
		gluPerspective(p_alf, x, z_near, z_far );
	else
		glOrtho(-x*mgnf,x*mgnf,-mgnf,mgnf,z_near,z_far);
	glMatrixMode(GL_MODELVIEW);}

void OpenGLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	draw();
}
void OpenGLWidget::frameSel()
{
	setCursor(Qt::CrossCursor);
	isFrameSel	= true;
	isMolSel	= false;
}

void OpenGLWidget::narrowSel()
{
	setCursor(Qt::ArrowCursor);
	isFrameSel	= false;
	isMolSel	= false;
}

void OpenGLWidget::moleculeSel()
{
	setCursor(Qt::PointingHandCursor);
	isFrameSel	= false;
	isMolSel	= true;
}

void OpenGLWidget::draw()
{
/*	glDisable(GL_LIGHT0);

	//GLfloat lmodel_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

	//GLfloat light_ambient[] = {0.0, 0.0, 0.0, 0};
	GLfloat light_diffuse[] = {0.5, 0.5, 0.5, 1};

	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_diffuse);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);*/

	//GLfloat light_diffuse[] = {0.3, 0.3, 0.3, 0};

	//glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	//glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);

	GLfloat param[4];

	//glLineWidth(2.0);
	//glColor3d(1,0,0);


	//GLfloat lmodel_ambient[] = {1, 1, 1, 1 };
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	

	param[0]	= 0;param[1]	= 0;param[2]	= 0;param[3]	= 0;
	glMaterialfv(GL_FRONT, GL_AMBIENT,param);
	glMaterialfv(GL_FRONT, GL_DIFFUSE,param);
	param[0]	= 1;param[1]	= 0;param[2]	= 0;param[3]	= 0;
	glMaterialfv(GL_FRONT, GL_EMISSION,param);

	//glEnable(GL_COLOR_MATERIAL);

	glBegin(GL_LINES);
	  //glColor3d(1,0,0);
      glVertex3f(0,0,0);
	  glVertex3f(1,0,0);
	glEnd();

	//glColor3d(0,1,0);
	param[0]	= 0;param[1]	= 0;param[2]	= 0;param[3]	= 0;
	glMaterialfv(GL_FRONT, GL_AMBIENT,param);
	glMaterialfv(GL_FRONT, GL_DIFFUSE,param);
	param[0]	= 0;param[1]	= 1;param[2]	= 0;param[3]	= 0;
	glMaterialfv(GL_FRONT, GL_EMISSION,param);


	glBegin(GL_LINES);
	//  glColor3d(0,1,0);
	  glVertex3f(0,0,0);
	  glVertex3f(0,1,0);
	glEnd();


	//glColor3d(0,0,1);
	param[0]	= 0;param[1]	= 0;param[2]	= 0;param[3]	= 0;
	glMaterialfv(GL_FRONT, GL_AMBIENT,param);
	glMaterialfv(GL_FRONT, GL_DIFFUSE,param);
	param[0]	= 0;param[1]	= 0;param[2]	= 1;param[3]	= 0;
	glMaterialfv(GL_FRONT, GL_EMISSION,param);
	glBegin(GL_LINES);	
	 // glColor3d(0,0,1);
	  glVertex3f(0,0,0);
	  glVertex3f(0,0,1);
	glEnd();


	if(isRotat)
	{
		vec3db rr,ax;

		rr	= RW->GetDis();

		ax	= rr+RW->GetAxis();

		param[0]	= 0;param[1]	= 0;param[2]	= 0;param[3]	= 0;
		glMaterialfv(GL_FRONT, GL_AMBIENT,param);
		glMaterialfv(GL_FRONT, GL_DIFFUSE,param);
		param[0]	= 1;param[1]	= 0;param[2]	= 0;param[3]	= 0;
		glMaterialfv(GL_FRONT, GL_EMISSION,param);

		glBegin(GL_LINES);
		glVertex3f(rr.x[0],rr.x[1],rr.x[2]);
		glVertex3f(1.0+rr.x[0],rr.x[1],rr.x[2]);
		glEnd();

		param[0]	= 0;param[1]	= 0;param[2]	= 0;param[3]	= 0;
		glMaterialfv(GL_FRONT, GL_AMBIENT,param);
		glMaterialfv(GL_FRONT, GL_DIFFUSE,param);
		param[0]	= 0;param[1]	= 1;param[2]	= 0;param[3]	= 0;
		glMaterialfv(GL_FRONT, GL_EMISSION,param);

		glBegin(GL_LINES);
		glVertex3f(rr.x[0],rr.x[1],rr.x[2]);
		glVertex3f(rr.x[0],1.0+rr.x[1],rr.x[2]);
		glEnd();

		param[0]	= 0;param[1]	= 0;param[2]	= 0;param[3]	= 0;
		glMaterialfv(GL_FRONT, GL_AMBIENT,param);
		glMaterialfv(GL_FRONT, GL_DIFFUSE,param);
		param[0]	= 0;param[1]	= 0;param[2]	= 1;param[3]	= 0;
		glMaterialfv(GL_FRONT, GL_EMISSION,param);

		glBegin(GL_LINES);
		glVertex3f(rr.x[0],rr.x[1],rr.x[2]);
		glVertex3f(rr.x[0],rr.x[1],1.0+rr.x[2]);
		glEnd();

		param[0]	= 0;param[1]	= 0;param[2]	= 0;param[3]	= 0;
		glMaterialfv(GL_FRONT, GL_AMBIENT,param);
		glMaterialfv(GL_FRONT, GL_DIFFUSE,param);
		param[0]	= 1;param[1]	= 1;param[2]	= 1;param[3]	= 0;
		glMaterialfv(GL_FRONT, GL_EMISSION,param);

		glBegin(GL_LINES);
		glVertex3f(rr.x[0],rr.x[1],rr.x[2]);
		glVertex3f(ax.x[0],ax.x[1],ax.x[2]);
		glEnd();

		param[0]	= 1.0;param[1]	= 1.0;param[2]	= 1.0;param[3]	= 1.0;
		glLightfv (GL_LIGHT0, GL_DIFFUSE, param);

		param[0]	= 0;param[1]	= 0;param[2]	= 0;param[3]	= 0;
		glMaterialfv(GL_FRONT, GL_EMISSION,param);

		param[0]	= 0.9;param[1]	= 0.9;param[2]	= 0.9;param[3]	= 1.0;
		glMaterialfv(GL_FRONT, GL_DIFFUSE,param);
		param[0]	= 0.0;param[1]	= 0.0;param[2]	= 0.0;param[3]	= 1.0;
		glMaterialfv(GL_FRONT, GL_AMBIENT,param);
		
		glTranslatef(rr.x[0],rr.x[1],rr.x[2]);

		gluQuadricDrawStyle(qobj, GLU_FILL); 
		gluSphere(qobj,0.1,30,21);

		glTranslatef(-rr.x[0],-rr.x[1],-rr.x[2]);

	}

//	param[0]	= 0;param[1]	= 0;param[2]	= 0;param[3]	= 0;
//	glMaterialfv(GL_FRONT, GL_EMISSION,param);
	//glDisable(GL_COLOR_MATERIAL);
//	lmodel_ambient[0]	= 0;
//	lmodel_ambient[1]	= 0;
//	lmodel_ambient[2]	= 0;
//	lmodel_ambient[3]	= 0;
//	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);


	//glPushAttrib(GL_ALL_ATTRIB_BITS);

	//setFont(QFont("Times",12));
	//renderText(1.1,0.0,0.0,QString("x"));
	//renderText(0.0,1.1,0.0,QString("y"));
	//renderText(0.0,0.0,1.1,QString("z"));



	//glPopAttrib();
	if(drawFrame)
	{
		vec3db dx,dy;
		double al;

		param[0]	= 0.5;param[1]	= 0.5;param[2]	= 0.5;param[3]	= 0;
		glMaterialfv(GL_FRONT, GL_EMISSION,param);

		//qglColor(QColor(250,250,250));
		//param[0]	= 1;param[1]	= 1;param[2]	= 1;param[3]	= 1;
		//glMaterialfv(GL_FRONT, GL_AMBIENT,param);
		dx	=  ldcon-rucon;
		al	= dx.x[0]*camOY[0]+dx.x[1]*camOY[1]+dx.x[2]*camOY[2];
		dy.x[0]	= camOY[0]*al; dy.x[1]	= camOY[1]*al; dy.x[2]	= camOY[2]*al;
		al	= dx.x[0]*camOX[0]+dx.x[1]*camOX[1]+dx.x[2]*camOX[2];
		dx.x[0]	= camOX[0]*al; dx.x[1]	= camOX[1]*al; dx.x[2]	= camOX[2]*al;
		glBegin(GL_LINE_LOOP);
		glVertex3d(rucon.x[0],rucon.x[1],rucon.x[2]);
		glVertex3d(rucon.x[0]+dx.x[0],rucon.x[1]+dx.x[1],rucon.x[2]+dx.x[2]);
		glVertex3d(ldcon.x[0],ldcon.x[1],ldcon.x[2]);
		glVertex3d(rucon.x[0]+dy.x[0],rucon.x[1]+dy.x[1],rucon.x[2]+dy.x[2]);
		glEnd();
	}


	param[0]	= 1.0;param[1]	= 1.0;param[2]	= 1.0;param[3]	= 1.0;
	glLightfv (GL_LIGHT0, GL_DIFFUSE, param);

	param[0]	= 0;param[1]	= 0;param[2]	= 0;param[3]	= 0;
	glMaterialfv(GL_FRONT, GL_EMISSION,param);

	glMatrixMode(GL_MODELVIEW);
	
	glLoadIdentity();


	//gluLookAt (40,40,40,0,0,0,0,0,1);
	gluLookAt (camPos[0],camPos[1],camPos[2],focPos[0],focPos[1],focPos[2],camOY[0],camOY[1],camOY[2]);
	//glTranslatef(VCMPos[0],VCMPos[1],VCMPos[2]);

	glTranslatef(VCMPos[0],VCMPos[1],VCMPos[2]);
	//glTranslatef(camPos[0],camPos[1],camPos[2]);

	//glColor3d(1,1,1);

	param[0]	= 0.3;param[1]	= 0.3;param[2]	= 0.3;param[3]	= 1.0;
	glMaterialfv(GL_FRONT, GL_DIFFUSE,param);
	param[0]	= 0.0;param[1]	= 0.0;param[2]	= 0.0;param[3]	= 1.0;
	glMaterialfv(GL_FRONT, GL_AMBIENT,param);

	//glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE,param);

	gluQuadricDrawStyle(qobj, GLU_FILL); 
	gluSphere(qobj,0.1,30,21);

	glTranslatef(-VCMPos[0],-VCMPos[1],-VCMPos[2]);



	/*if (isRenChAt)
	{
		glTranslatef(-0.5*camOZ[0],-0.5*camOZ[1],-0.5*camOZ[2]);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glCallList(theAtCh);
		glDisable(GL_BLEND);
		glTranslatef(+0.5*camOZ[0],+0.5*camOZ[1],+0.5*camOZ[2]);
	}*/


//	GLfloat light_diffuse1[] = {0.2, 0.2, 0.2, 1};

	//glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse1);
	//glLightfv(GL_LIGHT0, GL_AMBIENT, light_diffuse1);

/*	if(theMol!=0)
	{
		glCallList(theMol);
		if (isRenChAt)
		{
			rendAtCh();
		}

	}/**/
	if(theScene!=0)
	{
		glCallList(theScene);
	//	glCallList(theAtoms.x[0].x[0]);
		if (isRenChAt)
		{
			rendAtCh();
			/*glTranslatef(-0.35*camOZ[0],-0.35*camOZ[1],-0.35*camOZ[2]);
			glCallList(theAtCh_);
			glTranslatef(0.35*camOZ[0],0.35*camOZ[1],0.35*camOZ[2]);
			*/
		}
		if(isSelParShow)
		{
			//glCallList(theSelecteds);
			param[0]	= 0.5;param[1]	= 0.5;param[2]	= 0.5;param[3]	= 0;
			glMaterialfv(GL_FRONT, GL_EMISSION,param);
			param[0]	= 0.0;param[1]	= 0.0;param[2]	= 0.0;param[3]	= 1.0;
			glMaterialfv(GL_FRONT, GL_AMBIENT,param);
			glMaterialfv(GL_FRONT, GL_DIFFUSE,param);
			rendSelPar();
			//param[0]	= 0;param[1]	= 0;param[2]	= 0;param[3]	= 0;
			//glMaterialfv(GL_FRONT, GL_EMISSION,param);
		}
	}

/*	if(theBonds!=0)
	{
		glCallList(theBonds);
	}

	if(theWires!=0)
	{
		glCallList(theWires);
	}
*/

	if (isSurf)
	{
		glCallList(theSurf);
		//glCallList(theInvSurf);		
	}
	if(isActSpcShow)
	{
		glCallList(theActSpc);
	}

//	RenderText( this, 1.0, 1.0, 1.0, QString("text"),Qt::white, QFont("Times",14));
	//rendAtCh();
}

void OpenGLWidget::rcAS_set()
{
	vec3db rr;
	rr.x[0]	= focPos[0];
	rr.x[1]	= focPos[1];
	rr.x[2]	= focPos[2];
	AS->set_rc(rr);
}


int OpenGLWidget::add_Selectd_ids(vecT<ConnectedAtoms * > &ptr_ml, vecT<int> &id_atoms)	// добавить массивы о выделенных атомах
{
	int ii;
	ii	= check_Selected_ids(ptr_ml, id_atoms);
	if(ii==-1)
	{
		his_ptrs_ml.add(ptr_ml);
		his_id_sels.add(id_atoms);
	}
	return(ii);
}


int OpenGLWidget::check_Selected_ids(vecT<ConnectedAtoms * > &ptr_ml, vecT<int> &id_atoms)
{
	int ii,jj,ji,k1;

	k1	= -1;
	jj	= ptr_ml.N*sizeof( ConnectedAtoms * );
	ji	= id_atoms.N*sizeof(int);
	for(ii=0;ii<his_ptrs_ml.N;ii++)
	{
		if(ptr_ml.N==his_ptrs_ml.x[ii].N)
		{
			switch (ptr_ml.N)
			{
			case 2:
				{
					if(((ptr_ml.x[0]==his_ptrs_ml.x[ii].x[0])&&(id_atoms.x[0]==his_id_sels.x[ii].x[0]))&&((ptr_ml.x[1]==his_ptrs_ml.x[ii].x[1])&&(id_atoms.x[1]==his_id_sels.x[ii].x[1])))
					{
						k1	= ii;
						return k1;
					}else
					{
						if(((ptr_ml.x[0]==his_ptrs_ml.x[ii].x[1])&&(id_atoms.x[0]==his_id_sels.x[ii].x[1]))&&((ptr_ml.x[1]==his_ptrs_ml.x[ii].x[0])&&(id_atoms.x[1]==his_id_sels.x[ii].x[0])))
						{
							k1	= ii;
							return k1;
						}
					}
					break;
				}
			case 3:
				{
					if((ptr_ml.x[1]==his_ptrs_ml.x[ii].x[1])&&(id_atoms.x[1]==his_id_sels.x[ii].x[1]))
					{
						if(((ptr_ml.x[0]==his_ptrs_ml.x[ii].x[0])&&(id_atoms.x[0]==his_id_sels.x[ii].x[0]))&&((ptr_ml.x[2]==his_ptrs_ml.x[ii].x[2])&&(id_atoms.x[2]==his_id_sels.x[ii].x[2])))
						{
							k1	= ii;
							return k1;
						}else
						{
							if(((ptr_ml.x[0]==his_ptrs_ml.x[ii].x[2])&&(id_atoms.x[0]==his_id_sels.x[ii].x[2]))&&((ptr_ml.x[2]==his_ptrs_ml.x[ii].x[0])&&(id_atoms.x[2]==his_id_sels.x[ii].x[0])))
							{
								k1	= ii;
								return k1;
							}
						}
					}
					break;
				}
			case 4:
				{
					if ( ((ptr_ml.x[0]==his_ptrs_ml.x[ii].x[0])&&(ptr_ml.x[3]==his_ptrs_ml.x[ii].x[3])) || ((ptr_ml.x[0]==his_ptrs_ml.x[ii].x[3])&&(ptr_ml.x[3]==his_ptrs_ml.x[ii].x[0])) )
					{
						if( ( (ptr_ml.x[1]==his_ptrs_ml.x[ii].x[1])&&(ptr_ml.x[2]==his_ptrs_ml.x[ii].x[2]) ) || ((ptr_ml.x[1]==his_ptrs_ml.x[ii].x[2])&&(ptr_ml.x[2]==his_ptrs_ml.x[ii].x[1])) )
						{
							k1	= ii;
							return k1;
						}
					}
					break;
				}
			default :
				{
					if(memcmp(ptr_ml.x,his_ptrs_ml.x[ii].x,jj)==0)
					{
						if(memcmp(id_atoms.x,his_id_sels.x[ii].x,ji)==0)
						{
							k1	= ii;
							return k1;
						}
					}
					break;
				}
			}
		}
	}
	return k1;
}

void OpenGLWidget::del_Selected_ids(int id_mlat)	// удалить массивы о выделеных атомах
{
	his_ptrs_ml.N--;
	his_ptrs_ml.x[id_mlat].N	= 0;
	if(id_mlat!=his_ptrs_ml.N)
	{
		his_ptrs_ml.x[id_mlat].pad(his_ptrs_ml.x[his_ptrs_ml.N]);
	}
	his_id_sels.N--;
	his_id_sels.x[id_mlat].N	= 0;
	if(id_mlat!=his_id_sels.N)
	{
		his_id_sels.x[id_mlat].pad(his_id_sels.x[his_id_sels.N]);
	}
}

void OpenGLWidget::del_Selected_ids(vecT<int> &ids_mlat)	// удалить массивы о выделеных атомах
{
	int ii;
	for(ii=ids_mlat.N-1;ii>=0;ii--)
	{
		del_Selected_ids(ids_mlat.x[ii]);
	}
}

void OpenGLWidget::check_Selected_ids(vecT<int> &ids_mlat)
{
	int ii,jj,kk;
	vecT<int> ids1;
	bool ch;
	//vec3int tx;
	ids_mlat.N=0;
	ids1.N	= 0;
	for(ii=0;ii<his_ptrs_ml.N;ii++)
	{
		for(jj=0;jj<his_ptrs_ml.x[ii].N;jj++)
		{
			ch	= true;
			for(kk=0;kk<select_id.N;kk++)
			{
				if(select_id.x[kk].x[1]==his_id_sels.x[ii].x[jj])
				{
					if(mols.x[select_id.x[kk].x[0]]==his_ptrs_ml.x[ii].x[jj])
					{
						ids1.add(ii);
						ch	= false;
						break;
					}
				}
			}
			if(!ch) 
			{
				break;
			}
		}
	}
	ids1.sort();
	ids_mlat.pst(ids1);
}
void OpenGLWidget::doSelShow()
{
	vecT<ConnectedAtoms * > ptr_ml;
	vecT<int> id_atoms;
	if(select_id.N>0)
	{
		int ii;
		ptr_ml.setlen(select_id.N);
		id_atoms.setlen(select_id.N);

		for(ii=0;ii<select_id.N;ii++)
		{
			ptr_ml.x[ii]	= mols.x[select_id.x[ii].x[0]];
			id_atoms.x[ii]	= select_id.x[ii].x[1];
		}
		ii	= add_Selectd_ids(ptr_ml,id_atoms);
		if(ii!=-1)
		{
			del_Selected_ids(ii);
		}
		showSelPar();
		updateSelPar();
	}
	if(his_ptrs_ml.N==0)
	{
		clearSelPar();
	}else
	{
		showSelPar();
	}
}

void OpenGLWidget::jump2sel()
{
	// поместить центр вращения в геом. центр выделенных молекул и прибилить камеру на расстояние приблизително равное размеру области выделенных атомов
	vec3db p0,p1;
	double ds;

	if(select_id.N>0)
	{
		p0	= 0;
		for (int ii=0;ii<select_id.N;ii++)
		{
			p0	+= WF->Mls.x[select_id.x[ii].x[0]]->Atoms.x[select_id.x[ii].x[1]].r;
		}
		p0	/= select_id.N;
		ds	= 0;
		for (int ii=0;ii<select_id.N;ii++)
		{
			p1	= WF->Mls.x[select_id.x[ii].x[0]]->Atoms.x[select_id.x[ii].x[1]].r-p0;
			ds	+= p1.sqnr();
		}
		ds	= 2*sqrt(ds/select_id.N)+4;
		focPos[0] = VCMPos[0]	= p0.x[0];
		focPos[1] = VCMPos[1]	= p0.x[1];
		focPos[2] = VCMPos[2]	= p0.x[2];

		camPos[0]	= p0.x[0] - ds*camOZ[0];
		camPos[1]	= p0.x[1] - ds*camOZ[1];
		camPos[2]	= p0.x[2] - ds*camOZ[2];

		update();
	}
}

void OpenGLWidget::swp_Selected_ids(int id_ml,int id_at1, int id_at2)	// свап номеров
{
	int ii,jj;
	ConnectedAtoms * ptr;
	ptr	= mols.x[id_ml];
	vecT<vec2int> id1,id2;
	for(ii=0;ii<his_ptrs_ml.N;ii++)
	{
		for(jj=0;jj<his_ptrs_ml.x[ii].N;jj++)
		{
			if(ptr==his_ptrs_ml.x[ii].x[jj])
			{
				if(id_at1==his_id_sels.x[ii].x[jj])
				{
					id1.add(vec2int(ii,jj));	// собираем указания на первый атом
					//his_id_sels.x[ii].x[jj]	= id_at2;
				}else
				{
					if(id_at2==his_id_sels.x[ii].x[jj])
					{
						id2.add(vec2int(ii,jj));	// собираем указания на второй атом
						//his_id_sels.x[ii].x[jj]	= id_at1;
					}
				}
			}
		}
	}
	for(ii=0;ii<id1.N;ii++)
	{
		his_id_sels.x[id1.x[ii].x[0]].x[id1.x[ii].x[1]]	= id_at2;
	}
	for(ii=0;ii<id2.N;ii++)
	{
		his_id_sels.x[id2.x[ii].x[0]].x[id2.x[ii].x[1]]	= id_at1;
	}
}

void OpenGLWidget::mousePressEvent(QMouseEvent *event)
{
	lastPos	= event->pos();
	if(isFrameSel)
	{
		if (event->buttons()&Qt::LeftButton)
		{
			ruc.x[0]	= lastPos.x();
			ruc.x[1]	= lastPos.y();
			drawFrame	= true;
			setrucon();
		}else
		{
			ldc.x[0]	= 0.0;
			ldc.x[1]	= 0.0;
			isFrameSel	= false;
			drawFrame	= false;
			rucon	= 0.0;
			ldcon	= 0.0;
			narrowSel();
		}
	}else
	{
		if(isRotat)
		{
			if((event->buttons()&Qt::LeftButton)&&isShift)
			{
				selectAtom(event->pos());
				if (id_at!=-1)//s_id.N	== 1)
				{
					vec3db p;
					if(id_ml==id_ml_)
					{
						if (((!RW->isZeroSpin())||(!RW->isZeroDisp())))
						{
							int ii;
							for(ii=0;ii<mols.x[id_ml_]->Atoms.N;ii++)
							{
								mols.x[id_ml_]->Atoms.x[ii].r	= sel_xyz.x[ii];
							}
							emit rotatDo();
							for(ii=0;ii<mols.x[id_ml_]->Atoms.N;ii++)
							{
								sel_xyz.x[ii]	= mols.x[id_ml_]->Atoms.x[ii].r;
							}
						}
						/*	p	= sel_xyz.x[id_at]-RW->GetDis();
						p.nrml();
						RW->SetAxis(p);
						//RW->SetDis();//WF->Mls.x[id_ml]->Atoms.x[id_at].r);
						id_at	= -1;
						id_ml	= -1;*/
					}//else
					
						//RW->SetDis(WF->Mls.x[id_ml]->Atoms.x[id_at].r);
						p	= mols.x[id_ml]->Atoms.x[id_at].r-RW->GetDis();
						p.nrml();
						RW->SetAxis(p);
						id_at	= -1;
						id_ml	= -1;
					
					rotatproc();
					//update();
				}

			}else
			{
				if((event->buttons()&Qt::RightButton)&&isShift)
				{
					selectAtom(event->pos());
					if (id_at!=-1)
					{
						if(id_ml==id_ml_)
						{
							if (((!RW->isZeroSpin())||(!RW->isZeroDisp())))
							{
								int ii;
								for(ii=0;ii<mols.x[id_ml_]->Atoms.N;ii++)
								{
									mols.x[id_ml_]->Atoms.x[ii].r	= sel_xyz.x[ii];
								}
								emit rotatDo();
								for(ii=0;ii<mols.x[id_ml_]->Atoms.N;ii++)
								{
									sel_xyz.x[ii]	= mols.x[id_ml_]->Atoms.x[ii].r;
								}
							}
						}
							/*RW->SetDis(sel_xyz.x[id_at]);//WF->Mls.x[id_ml]->Atoms.x[id_at].r);
							id_at	= -1;
							id_ml	= -1;
						}else
						{*/
						RW->SetDis(mols.x[id_ml]->Atoms.x[id_at].r);
						id_at	= -1;
						id_ml	= -1;
						//}
						rotatproc();
					}else
					{
						isMovQc	= true;
					}
				}
			}
		}else
		{
			if(event->buttons()&Qt::RightButton)
			{
				if(isFrgBrw)
				{
					isFrgBrw	= false;
					emit closeFrgBrw();
				}
				if(isAtomBrw)
				{
					isAtomBrw	= false;
					emit closeAtomBrw();
				}
				if(isMolSel)
				{
					//isMolSel	= false;
					narrowSel();
				}
				if(!isDblRight)
				{
					setCursor(Qt::ClosedHandCursor);
				}
			}else
			{
				if (event->buttons()&Qt::LeftButton)
				{
					if(isAtomBrw)
					{
						if(addatomtype==0)
						{
							lastPos	= event->pos();
							//selectAction(event->pos());
							selectAtom(event->pos());
							if (id_at!=-1)//s_id.N	== 1)
							{
								addatomtype	= 1;
								rendScene();
								update();
							}
						}else
						{
							//get3Dfrom2D();
							emit addatomDo();
						}

					}
					if(!isDblRight)
					{
						if(isShift)
						{
							Molecule *lmol;
							if(isBondLen)
							{
								selectAtom(event->pos());
								ids_bl.N	= 0;
								init_xyz.N	= 0;
								if((id_ml==id_ml_bl)&&(id_ml!=-1))
								{
									if(id_at_bl1==id_at)
									{
										id_at_bl1	= id_at_bl2;
										id_at_bl2	= id_at;
										lmol	= reinterpret_cast<Molecule *> (mols.x[id_ml]);
										lmol->GetSubMol(id_at_bl1,id_at_bl2,ids_bl);
										init_xyz.setlen(ids_bl.N);
										for(int ii=0;ii<ids_bl.N;ii++)
										{
											init_xyz.x[ii]	= lmol->Atoms.x[ids_bl.x[ii]].r; // запомнить начальную конфигурацию атомов
										}
										pnr	= lmol->Atoms.x[id_at_bl2].r-lmol->Atoms.x[id_at_bl1].r;
										pnr.nrml();
										inversel	= true;
									}else
									{
										if((id_at_bl2==id_at))
										{
											lmol	= reinterpret_cast<Molecule *> (mols.x[id_ml]);
											lmol->GetSubMol(id_at_bl1,id_at_bl2,ids_bl);
											init_xyz.setlen(ids_bl.N);
											for(int ii=0;ii<ids_bl.N;ii++)
											{
												init_xyz.x[ii]	= lmol->Atoms.x[ids_bl.x[ii]].r; // запомнить начальную конфигурацию атомов
											}
											pnr	= lmol->Atoms.x[id_at_bl2].r-lmol->Atoms.x[id_at_bl1].r;
											pnr.nrml();
											inversel	= false;
										}
									}
								}
								id_at	= -1;
								id_ml	= -1;
							}else
							{
								if(isValAngl)
								{
									selectAtom(event->pos());
									ids_bl.N	= 0;
									if((id_ml==id_ml_va)&&(id_ml!=-1))
									{
										vec3db p1,p2;
										if(id_at_va1==id_at)
										{
											id_at_va1	= id_at_va3;
											id_at_va3	= id_at;
											lmol	= reinterpret_cast<Molecule *> (mols.x[id_ml]);
											lmol->GetSubMol(id_at_va2,id_at_va3,ids_bl);
											if (ids_bl.fnd(id_at_va1)!=-1) ids_bl.N = 1;
											init_xyz.setlen(ids_bl.N);
											for(int ii=0;ii<ids_bl.N;ii++)
											{
												init_xyz.x[ii]	= lmol->Atoms.x[ids_bl.x[ii]].r; // запомнить начальную конфигурацию атомов
											}
											p1	= lmol->Atoms.x[id_at_va3].r-lmol->Atoms.x[id_at_va2].r;
											p2	= lmol->Atoms.x[id_at_va1].r-lmol->Atoms.x[id_at_va2].r;
											axs.crss(p1,p2);
											if(axs.norm()<1e-10) axs.x[0] = 1.0;
											axs.nrml();
											inversel	= true;
										}else
										{
											if((id_at_va3==id_at))
											{
												lmol	= reinterpret_cast<Molecule *> (mols.x[id_ml]);
												lmol->GetSubMol(id_at_va2,id_at_va3,ids_bl);
												if (ids_bl.fnd(id_at_va1)!=-1) ids_bl.N = 1;
												init_xyz.setlen(ids_bl.N);
												for(int ii=0;ii<ids_bl.N;ii++)
												{
													init_xyz.x[ii]	= lmol->Atoms.x[ids_bl.x[ii]].r; // запомнить начальную конфигурацию атомов
												}
												p1	= lmol->Atoms.x[id_at_va3].r-lmol->Atoms.x[id_at_va2].r;
												p2	= lmol->Atoms.x[id_at_va1].r-lmol->Atoms.x[id_at_va2].r;
												axs.crss(p1,p2);
												if(axs.norm()<1e-10) axs.x[0] = 1.0;
												axs.nrml();
												inversel	= false;
											}
										}
									}
									id_at	= -1;
									id_ml	= -1;
								}
								if(isTorAngl)
								{
									selectAtom(event->pos());
									ids_bl.N	= 0;
									if((id_ml==id_ml_va)&&(id_ml!=-1))
									{
										lmol	= reinterpret_cast<Molecule *> (mols.x[id_ml]);
										if(id_at_va1==id_at)
										{
											id_at_va1	= id_at_va4;
											id_at_va4	= id_at;
											id_at		= id_at_va3;
											id_at_va3	= id_at_va2;
											id_at_va2	= id_at;
											lmol->GetSubMol(id_at_va2,id_at_va3,ids_bl);
											if (ids_bl.fnd(id_at_va1)!=-1) ids_bl.N = 0;
											init_xyz.setlen(ids_bl.N);
											for(int ii=0;ii<ids_bl.N;ii++)
											{
												init_xyz.x[ii]	= lmol->Atoms.x[ids_bl.x[ii]].r; // запомнить начальную конфигурацию атомов
											}
											axs	= lmol->Atoms.x[id_at_va3].r-lmol->Atoms.x[id_at_va2].r;
											axs.nrml();
											inversel	= true;
										}else
										{
											if((id_at_va4==id_at))
											{
												lmol->GetSubMol(id_at_va2,id_at_va3,ids_bl);
												if (ids_bl.fnd(id_at_va1)!=-1) ids_bl.N = 0;
												init_xyz.setlen(ids_bl.N);
												for(int ii=0;ii<ids_bl.N;ii++)
												{
													init_xyz.x[ii]	= lmol->Atoms.x[ids_bl.x[ii]].r; // запомнить начальную конфигурацию атомов
												}
												axs	= lmol->Atoms.x[id_at_va3].r-lmol->Atoms.x[id_at_va2].r;
												axs.nrml();
												inversel	= false;
											}
										}
									}
									id_at	= -1;
									id_ml	= -1;
								}
							}
						}else
						{
							if(!isMolSel)
							{
								setCursor(Qt::ArrowCursor);
							}
						}
					}else
					{
						setCursor(Qt::ClosedHandCursor);
					}
				}
			}
		}
	}
}

void OpenGLWidget::mouseReleaseEvent(QMouseEvent *event)
{
	lastPos	= event->pos();
	if(isFrameSel)
	{
		ldc.x[0]	= lastPos.x();
		ldc.x[1]	= lastPos.y();
		drawFrame	= false;
		rucon	= 0.0;
		ldcon	= 0.0;
		selectFrameAction();
	}else
	{
		if(event->button()==Qt::RightButton)
		{
			if(!isDblRight)
			{
				setCursor(Qt::OpenHandCursor);
			}
		}else
		{
			if (event->button()==Qt::LeftButton)
			{
				if(isRotat)
				{
					isMovQc	= false;
				}
				if(!isDblRight)
				{
					if(isShift)
					{
						if((isBondLen)&&(init_xyz.N>0))
						{
							
							pnr	= mols.x[id_ml_bl]->Atoms.x[ids_bl.x[0]].r-init_xyz.x[0]; // итоговое смещение фрагмента
							if (pnr.norm()>1e-13)
							{
								for(int ii=0;ii<ids_bl.N;ii++)
								{
									mols.x[id_ml_bl]->Atoms.x[ids_bl.x[ii]].r	-= pnr;//init_xyz.x[ii]; // вспомнить начальную конфигурацию атомов
								}
								alf	= 0.0;
								axs	= 0.0;
								emit movefrgDo();
							}
							//genScene();
							//update();
						}
						if((isValAngl)&&(init_xyz.N>0))
						{
							
							//pnr	= WF->Mls.x[id_ml_bl]->Atoms.x[ids_bl.x[0]].r-init_xyz.x[0]; // итоговое смещение фрагмента

							if (fabs(alf)>1e-13)
							{
								for(int ii=0;ii<ids_bl.N;ii++)
								{
									mols.x[id_ml_va]->Atoms.x[ids_bl.x[ii]].r	= init_xyz.x[ii]; // вспомнить начальную конфигурацию атомов
								}
								id_ml_bl	= id_ml_va;
								id_at_bl2	= id_at_va2;
								pnr	= 0.0;
								emit movefrgDo();
							}
							//genScene();
							//update();
						}
						if((isTorAngl)&&(init_xyz.N>0))
						{
							if (fabs(alf)>1e-13)
							{
								for(int ii=0;ii<ids_bl.N;ii++)
								{
									mols.x[id_ml_va]->Atoms.x[ids_bl.x[ii]].r	= init_xyz.x[ii]; // вспомнить начальную конфигурацию атомов
								}
								id_ml_bl	= id_ml_va;
								id_at_bl2	= id_at_va3;
								pnr	= 0.0;
								emit movefrgDo();
							}
						}
					}else
					{
						if(!isMolSel)
						{
							setCursor(Qt::ArrowCursor);
						}
					}
				}else
				{
					setCursor(Qt::OpenHandCursor);
				}
			}
		}
	}
	/*if (isDblRight)
	{
	// вычислить смещения выделенных атомов
	int ii;
	for(ii=0;ii<s_id.N;ii++)
	{
	sel_xyz.x[ii]	-= xyz.x[s_id.x[ii]];
	}
	// инициировать и запомнить операцию смещения атомов
	moveDo();
	}*/
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{

	GLfloat dx	= GLfloat(event->x()-lastPos.x())/width();
	GLfloat dy	= GLfloat(event->y()-lastPos.y())/height();
	
	if (!isFrameSel)
	{
		if((isRotat)&&(isShift))
		{
			if (event->buttons()&Qt::LeftButton)
			{
				/*if(isMovQc)
				{
					vec3db p;
					p	= get3Dfrom2D(RW->GetDis(),event->x(),event->y());
					RW->SetDis(p);
					rotatproc();
					//update();
				}
				else
				{*/
					vec3db p0,pq,p;
					pq	= RW->GetAxis();
					p	= RW->GetDis()+pq;
					p0	= get3Dfrom2D(p,lastPos.x(),lastPos.y());
					p	= get3Dfrom2D(p,event->x(),event->y());
					p	-= p0;
					p	+= pq;
					p.nrml();
					RW->SetAxis(p);
					rotatproc();
					//update();
				//}
			}else
			{
				if (event->buttons()&Qt::RightButton)
				{
					if(isMovQc)
					{
						vec3db p;
						get3Dfrom2D(RW->GetDis());
						p	= get3Dfrom2D(RW->GetDis(),event->x(),event->y());
						p	= RW->GetDis()+p-tv;
						RW->SetDis(p);
						rotatproc();
						//update();
					}
				}
			}
			lastPos	= event->pos();
		}else
		{
			if (!isDblRight)
			{
				if(isShift&&isBondLen)
				{

					if(inversel) 
					{
						int kk;
						kk	= id_at_bl2;
						id_at_bl2	= id_at_bl1;
						id_at_bl1	= kk;
					}
					//vec3db dp;
					//p	= WF->Mls.x[id_ml_bl]->Atoms.x[id_at_bl2].r-WF->Mls.x[id_ml_bl]->Atoms.x[id_at_bl1].r;
					//p.nrml();
					get3Dfrom2D(mols.x[id_ml_bl]->Atoms.x[id_at_bl2].r);
					tv	= get3Dfrom2D(mols.x[id_ml_bl]->Atoms.x[id_at_bl2].r,event->x(),event->y())-tv;				
					tv	= pnr*(pnr.scpr(tv));

					for(int ii=0;ii<ids_bl.N;ii++)
					{
						mols.x[id_ml_bl]->Atoms.x[ids_bl.x[ii]].r	+= tv;
					}

					rendScene();
					update();
					emit updatestate();
				}else
				{
					if(isShift&&isValAngl) 
					{
						//vec3db p,dp;

						if(inversel) 
						{
							int kk;
							kk	= id_at_va3;
							id_at_va3	= id_at_va1;
							id_at_va1	= kk;
						}
						
						get3Dfrom2D(mols.x[id_ml_va]->Atoms.x[id_at_va3].r);
						pnr	= get3Dfrom2D(mols.x[id_ml_va]->Atoms.x[id_at_va3].r,event->x(),event->y())-tv;				
						pnr	= pnr-axs*(axs.scpr(pnr));
						rc	= mols.x[id_ml_va]->Atoms.x[id_at_va3].r-mols.x[id_ml_va]->Atoms.x[id_at_va2].r;
						pnr+=rc;
						pnr.nrml();
						rc.nrml();
						tv.crss(rc,pnr);
						sna	= tv.scpr(axs);
						alf	+= sna;

						Quat.x[0]	= cos(sna/2);
						sna			= sin(sna/2);
						Quat.x[1]	= sna*axs.x[0];
						Quat.x[2]	= sna*axs.x[1];
						Quat.x[3]	= sna*axs.x[2];

						Arot	= Quat.qua2matrR();
						for(int ii=0;ii<ids_bl.N;ii++)
						{
							pnr	= mols.x[id_ml_va]->Atoms.x[ids_bl.x[ii]].r - mols.x[id_ml_va]->Atoms.x[id_at_va2].r;
							pnr	= Arot*pnr;
							mols.x[id_ml_va]->Atoms.x[ids_bl.x[ii]].r	= pnr + mols.x[id_ml_va]->Atoms.x[id_at_va2].r;
						}

						rendScene();
						update();
						emit updatestate();/**/
					}
					else
					{
						if((isShift&&isTorAngl))
						{

							//vec3db p,dp;

							if(inversel) 
							{
								int kk;
								kk	= id_at_va4;
								id_at_va4	= id_at_va1;
								id_at_va1	= kk;
								kk	= id_at_va2;
								id_at_va2	= id_at_va3;
								id_at_va3	= kk;
							}

							get3Dfrom2D(mols.x[id_ml_va]->Atoms.x[id_at_va4].r);
							pnr	= get3Dfrom2D(mols.x[id_ml_va]->Atoms.x[id_at_va4].r,event->x(),event->y())-tv;				
							pnr	= pnr-axs*(axs.scpr(pnr));
							rc	= mols.x[id_ml_va]->Atoms.x[id_at_va4].r-mols.x[id_ml_va]->Atoms.x[id_at_va3].r;
							rc	= rc-axs*(axs.scpr(rc));
							pnr	+=rc;
							pnr.nrml();
							rc.nrml();
							tv.crss(rc,pnr);
							sna	= tv.scpr(axs);
							alf	+= sna;

							Quat.x[0]	= cos(sna/2);
							sna			= sin(sna/2);
							Quat.x[1]	= sna*axs.x[0];
							Quat.x[2]	= sna*axs.x[1];
							Quat.x[3]	= sna*axs.x[2];

							Arot	= Quat.qua2matrR();
							for(int ii=0;ii<ids_bl.N;ii++)
							{
								pnr	= mols.x[id_ml_va]->Atoms.x[ids_bl.x[ii]].r - mols.x[id_ml_va]->Atoms.x[id_at_va3].r;
								pnr	= Arot*pnr;
								mols.x[id_ml_va]->Atoms.x[ids_bl.x[ii]].r	= pnr + mols.x[id_ml_va]->Atoms.x[id_at_va3].r;
							}

							rendScene();
							update();
							emit updatestate();/**/
						}else
						{

							if (event->buttons()&Qt::LeftButton)
							{
								double q,alf,bet,cs1,sn1,cs2,sn2;
								GLfloat x,y,z,x1,y1,z1,x2,y2,z2,x3,y3,z3;


								x	= focPos[0]-camPos[0]; // вектор в точку наблюдения из центра камеры
								y	= focPos[1]-camPos[1];
								z	= focPos[2]-camPos[2];

								q	= sqrt(x*x+y*y+z*z); // расстояние до точки наблюдения

								alf	= 10*dx;	// угол поворота вокруг вертикальной (относительно экрана) оси
								bet	= 10*dy;	// угол поворота вокруг горизонтальной (относительно экрана) оси
								cs2	= cos(alf);
								sn2	= sin(alf);
								cs1	= cos(bet);
								sn1	= sin(bet);


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

								/*x1	= (cs1*cs2*camOX[0]+sn1*camOX[1]+cs1*sn2*camOX[2]);
								y1	= (-sn1*cs2*camOX[0]+cs1*camOX[1]-sn1*sn2*camOX[2]);
								z1	= (cs2*camOX[2]-sn2*camOZ[2]);

								x2	= (cs1*cs2*camOY[0]+sn1*camOY[1]+cs1*sn2*camOY[2]);
								y2	= (-sn1*cs2*camOY[0]+cs1*camOY[1]-sn1*sn2*camOY[2]);
								z2	= (cs2*camOY[2]-sn2*camOY[2]);

								x3	= (cs1*cs2*camOZ[0]+sn1*camOZ[1]+cs1*sn2*camOZ[2]);
								y3	= (-sn1*cs2*camOZ[0]+cs1*camOZ[1]-sn1*sn2*camOZ[2]);
								z3	= (cs2*camOZ[2]-sn2*camOZ[2]);/**/

								x	= -q*camOZ[0];
								y	= -q*camOZ[1];
								z	= -q*camOZ[2];

								// новое положение камеры
								camPos[0]	= x+focPos[0];
								camPos[1]	= y+focPos[1];
								camPos[2]	= z+focPos[2];

								/*camOX[0]	= x1;
								camOX[1]	= y1;
								camOX[2]	= z1;

								camOY[0]	= x2;
								camOY[1]	= y2;
								camOY[2]	= z2;

								camOZ[0]	= x3;
								camOZ[1]	= y3;
								camOZ[2]	= z3;/**/

								//rotationX	+= 180*dy;
								//rotationY	+= 180*dx;

								//camPos[0]	+= 10*dx;
								//camPos[1]	+= 10*dy;

								update();
							}else if (event->buttons()&Qt::RightButton)
							{

								GLfloat x,y,z,x1,y1,z1;
								//rotationX	+= 180*dy;
								//rotationZ	+= 180*dx;
								//camPos[0]	+= 10*dx;
								//camPos[1]	+= 10*dy;



								/*			x	= 100*dx;
								z	= 0.0;
								y	= 100*dy; */
								vec3db p;
								get3Dfrom2D();
								p	= get3Dfrom2D(event->x(),event->y());

								x1	= tv.x[0]-p.x[0];
								y1	= tv.x[1]-p.x[1];
								z1	= tv.x[2]-p.x[2];

								VCMPos[0]	+= x1;
								VCMPos[1]	+= y1;
								VCMPos[2]	+= z1;

								camPos[0]	+= x1;
								camPos[1]	+= y1;
								camPos[2]	+= z1;


								/*x1	= x*(camOX[0]);
								y1	= x*(camOX[1]);
								z1	= x*(camOX[2]);

								VCMPos[0]	+= x1;
								VCMPos[1]	+= y1;
								VCMPos[2]	+= z1;

								camPos[0]	+= x1;
								camPos[1]	+= y1;
								camPos[2]	+= z1;

								x1	= y*(camOY[0]);
								y1	= y*(camOY[1]);
								z1	= y*(camOY[2]);

								VCMPos[0]	+= x1;
								VCMPos[1]	+= y1;
								VCMPos[2]	+= z1;

								camPos[0]	+= x1;
								camPos[1]	+= y1;
								camPos[2]	+= z1;*/


								focPos[0]	= VCMPos[0];
								focPos[1]	= VCMPos[1];
								focPos[2]	= VCMPos[2];

								update();
							}
						}
					}
				}
			}else
			{
				if (event->buttons()&Qt::LeftButton)
				{
					if(select_id.N!=0)
					{
						GLfloat x,y,z,x1,y1,z1;
						vec3db p,rc1;
						rc	= 0.0;
						for(int ii=0;ii<select_id.N;ii++)
						{
							rc	+= mols.x[select_id.x[ii].x[0]]->Atoms.x[select_id.x[ii].x[1]].r;
						}
						rc	/= double(select_id.N);
						get3Dfrom2D(rc);
						p	= get3Dfrom2D(rc,event->x(),event->y());

						p	-= tv;
						for(int ii=0;ii<select_id.N;ii++)
						{
							mols.x[select_id.x[ii].x[0]]->Atoms.x[select_id.x[ii].x[1]].r	+= p;
						}
						rendScene();
						update();
						emit updatestate();
					}
				}
			}
			lastPos	= event->pos();
		}
	}else
	{
		lastPos	= event->pos();
		setldcon();
		update();
	}
}

void OpenGLWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
	if (event->buttons()&Qt::LeftButton)
	{
		if(isFrgBrw) // если включён выбор фрагмента  и фрагмент вырбран
		{
			lastPos	= event->pos();
			get3Dfrom2D(); // определить полoжение центра фрагмента по положению курсора
			emit addfrgDo(); // эммитировать сигнал о добавлении фрагмента
			//WF->Mls.x[0]->Atoms.x[0].r	= tv;
			//genScene();
			//update();
		}else
		{
			if(isRotat)
			{
				isRotat	= false;
				RW->setVisible(false);

				if (!RW->isZeroSpin())
				{
					int ii;
					for(ii=0;ii<mols.x[id_ml_]->Atoms.N;ii++)
					{
						mols.x[id_ml_]->Atoms.x[ii].r	= sel_xyz.x[ii];
					}
					emit rotatDo();
				}
				//update();
			}else
			{
				if((isAtomBrw)&&(!isMolSel))
				{
					lastPos	= event->pos();
					get3Dfrom2D();
					selectAtom(event->pos());
					addatomtype	= 0;
					emit addatomDo();
				}else
				{
					if(isDblRight)
					{
						int ii;
						for(ii=0;ii<select_id.N;ii++)
						{
							sel_xyz.x[ii]	-= mols.x[select_id.x[ii].x[0]]->Atoms.x[select_id.x[ii].x[1]].r;//xyz.x[s_id.x[ii]];
						}
						// инициировать и запомнить операцию смещения атомов
						moveDo();
					}
					isDblRight	= false;
					selectAction(event->pos());

					ids_bl.N	= 0;
					init_xyz.N	= 0;
				}				
			}
		}
	}else if (event->buttons()&Qt::RightButton)
	{
		if(isRotat)
		{
			isRotat	= false;
			RW->setVisible(false);
			
			if (!RW->isZeroSpin())
			{
				int ii;
				for(ii=0;ii<mols.x[id_ml_]->Atoms.N;ii++)
				{
					mols.x[id_ml_]->Atoms.x[ii].r	= sel_xyz.x[ii];
				}
				emit rotatDo();
			}
			//update();
		}else
		{
			int ii;
			isDblRight	= !isDblRight;
			if (isDblRight)
			{
				// сохранить координаты выделенных атомов
				sel_xyz.N	= 0;
				if(sel_xyz.mN<s_id.N) sel_xyz.setmem(s_id.N);
				for(ii=0;ii<select_id.N;ii++)
				{
					sel_xyz.x[ii]	= mols.x[select_id.x[ii].x[0]]->Atoms.x[select_id.x[ii].x[1]].r;//xyz.x[s_id.x[ii]];
				}
				sel_xyz.N	= ii;
			}else
			{
				for(ii=0;ii<select_id.N;ii++)
				{
					sel_xyz.x[ii]	-= mols.x[select_id.x[ii].x[0]]->Atoms.x[select_id.x[ii].x[1]].r;//xyz.x[s_id.x[ii]];
				}
				// инициировать и запомнить операцию смещения атомов
				moveDo();
				update();
			}
		}
	}
}

void OpenGLWidget::wheelEvent(QWheelEvent *event)
{
	if(isCtrl)
	{
		if(isRotat)
		{
			event->delta()>0 ? RW->incdis() : RW->decdis();
		}else
		{
			if(isOrtho)
			{
				if((mgnf<=100)&&(mgnf>=0.5))
				{
					mgnf	+= GLfloat(event->delta())/100;
				}
				else
				{
					if(mgnf<0.5) mgnf	= 0.5; else mgnf	= 100.0;
				}
			}else
			{
				if((p_alf<=160.0)&&(p_alf>=1.0))
				{
					p_alf	+= GLfloat(event->delta())/100;
				}
				else
				{
					if(p_alf<1.0) p_alf	= 1.0; else p_alf	= 160.0;
				}
			}
			reprojGL();
			update();
		}
	}else
	{
		if(!drawFrame)
		{
			if(isRotat&&isShift)
			{
				event->delta()>0 ? RW->inc() : RW->dec();
			}else
			{
				if (event->buttons()&Qt::RightButton)
				{

					if (!isDblRight)
					{

						GLfloat dq,x1,y1,z1,a;

						dq	= -GLfloat(event->delta())/100;

						x1	= (VCMPos[0]-camPos[0]);
						y1	= (VCMPos[1]-camPos[1]);
						z1	= (VCMPos[2]-camPos[2]);

						a	= sqrt(x1*x1+y1*y1+z1*z1);

						x1	/= a;
						y1	/= a;
						z1	/= a;

						dq	= a>10 ? dq : (a>5 ? 0.5*dq : a>1 ? 0.1*dq : 0.05*abs(dq) );

						a	+= dq;

						VCMPos[0]	= camPos[0]+x1*a;
						VCMPos[1]	= camPos[1]+y1*a;
						VCMPos[2]	= camPos[2]+z1*a;

						focPos[0]	= VCMPos[0];
						focPos[1]	= VCMPos[1];
						focPos[2]	= VCMPos[2];

						camPos[0]	+= dq*x1;
						camPos[1]	+= dq*y1;
						camPos[2]	+= dq*z1;

						update();
					}else
					{
						int dq;
						dq	= event->delta();
						dis_koeff	*= dq >0 ? 2.0 : 0.5;
					}
				}else
				{
					if (!isDblRight)
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
						update();
					}
					else
					{
						double q,dq;
						GLfloat x,y,z;

						/*for(int ii=0;ii<s_id.N;ii++)
						{
							x	= WF->Mls.x[0]->Atoms.x[s_id.x[ii]].r.x[0]-rc.x[0]-camPos[0];
							y	= WF->Mls.x[0]->Atoms.x[s_id.x[ii]].r.x[1]-rc.x[1]-camPos[1];
							z	= WF->Mls.x[0]->Atoms.x[s_id.x[ii]].r.x[2]-rc.x[2]-camPos[2];

							q	= sqrt(x*x+y*y+z*z);

							x	/= q;
							y	/= q;
							z	/= q;

							dq	= GLfloat(event->delta())/500;

							dq	= q>10 ? dq : (q>5 ? 0.5*dq : q>1 ? 0.1*dq : 0.05*abs(dq) );

							q	+= dq;// *= dis_koeff;

							x	*= q;
							y	*= q;
							z	*= q;

							WF->Mls.x[0]->Atoms.x[s_id.x[ii]].r.x[0]	= camPos[0]+rc.x[0]+x;
							WF->Mls.x[0]->Atoms.x[s_id.x[ii]].r.x[1]	= camPos[1]+rc.x[1]+y;
							WF->Mls.x[0]->Atoms.x[s_id.x[ii]].r.x[2]	= camPos[2]+rc.x[2]+z;
						}*/

						//rendScene();
						update();
					}	
				}
			}
		}
	}
}

void OpenGLWidget::keyPressEvent(QKeyEvent *event)
{
	switch (event->key())
	{
	case Qt::Key_Control :
		{
			isCtrl	= true;
			break;
		}
	case Qt::Key_Shift :
		{
			isShift = true;
			break;
		}
	case Qt::Key_Delete :
		{
			deleteDo();
			break;
		}
	case Qt::Key_B :
		{
			addbndDo();
			break;
		}
	case Qt::Key_R :
		{
		/*	//активировать выбор рамкой
			isFrameSel	= true;
			frameSel();*/
			break;
		}
	case Qt::Key_T :
		{
			//деактивировать выбор рамкой
			/*isFrameSel	= false;
			drawFrame	= false;
			narrowSel();*/
			break;
		}
	case Qt::Key_S :
		{
			emit genCrSurf();
			//деактивировать выбор рамкой
			/*isFrameSel	= false;
			drawFrame	= false;
			narrowSel();*/
			break;
		}


/*	default :
		QGLWidget::keyPressEvent(event);*/
	}
}

void OpenGLWidget::keyReleaseEvent(QKeyEvent *event)
{
	int k;
	k	= event->key();
	switch (event->key())
	{
	case Qt::Key_Control :
	{
		isCtrl	= false;
		break;
	}
	case Qt::Key_Shift :
		{
			isShift = false;
			if((isBondLen)&&(init_xyz.N>0))
			{

				pnr	= mols.x[id_ml_bl]->Atoms.x[ids_bl.x[0]].r-init_xyz.x[0]; // итоговое смещение фрагмента
				for(int ii=0;ii<ids_bl.N;ii++)
				{
					mols.x[id_ml_bl]->Atoms.x[ids_bl.x[ii]].r	-= pnr;//init_xyz.x[ii]; // вспомнить начальную конфигурацию атомов
				}
				//emit movefrgDo();
				rendScene();
				update();
			}/**/
			break;
		}
	case Qt::Key_Return :
		{
			if((isRotat)&&((!RW->isZeroSpin())||(!RW->isZeroDisp())))
			{
				int ii;
				for(ii=0;ii<mols.x[id_ml_]->Atoms.N;ii++)
				{
					mols.x[id_ml_]->Atoms.x[ii].r	= sel_xyz.x[ii];
				}
				emit rotatDo();
				for(ii=0;ii<mols.x[id_ml_]->Atoms.N;ii++)
				{
					sel_xyz.x[ii]	= mols.x[id_ml_]->Atoms.x[ii].r;
				}
			}
			break;
		}
	/*default :
		QGLWidget::keyReleaseEvent(event);*/
	}
}

void OpenGLWidget::enterEvent(QEvent *event)
{
	QGLWidget::enterEvent(event);
}
void OpenGLWidget::leaveEvent(QEvent *event)
{
	QGLWidget::leaveEvent(event);
}


int OpenGLWidget::selectAction(const QPoint &pos)
{
	int MaxSize,im,issel;
	GLuint *buffer,*ptr,ih;
	GLint viewport[4];
	GLdouble px,py,width,height;
	GLint hits;
	double x,y,z,rd;
	int theSph,is,jm;
	GLfloat param[4];
	GLfloat xx;
	is	=0;
	for (jm=0;jm<mols.N;jm++)
	{
		is	+= mols.x[jm]->Atoms.N;
	}	
	MaxSize	= 4*is;
	buffer	= new GLuint [MaxSize];

	px	= pos.x();
	py	= pos.y();
	width	= 2;
	height	= 2;

	glGetIntegerv(GL_VIEWPORT,viewport);

	glSelectBuffer(MaxSize,buffer);
	glRenderMode(GL_SELECT);
	
	glInitNames();
	glPushName(0);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	xx	= GLfloat(viewport[2])/GLfloat(viewport[3]);
	gluPickMatrix (px, (GLdouble)(viewport[3]-py), width, height, viewport );
	if (!isOrtho)
		gluPerspective(p_alf, xx, z_near, z_far );
	else
		glOrtho(-xx*mgnf,xx*mgnf,-mgnf,mgnf,z_near,z_far);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPopMatrix();
	is	= 0;
	for (jm=0;jm<mols.N;jm++)
	{
		for(int i=0;i<mols.x[jm]->Atoms.N;i++)
		{
			x	= mols.x[jm]->Atoms.x[i].r.x[0];
			y	= mols.x[jm]->Atoms.x[i].r.x[1];
			z	= mols.x[jm]->Atoms.x[i].r.x[2];

			rd	= WF->TableZR.Lines.x[mols.x[jm]->Atoms.x[i].id_Tpz].vdwrad/500;//radius.x[i];

			glTranslated(x,y,z);
			glScaled(rd,rd,rd);
			param[0]	= 0.5;param[1]	= 0.5;param[2]	= 0.5;param[3]	= 1;
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE,param);
			is++;
			glLoadName(is);
			glCallList(theSph_);
			//gluSphere(qobj,rd,30,21);
			glScaled(1/rd,1/rd,1/rd);
			glTranslated(-x,-y,-z);
		}
	}
	hits = glRenderMode(GL_RENDER);
	ptr	 = (GLuint*)buffer;
	resizeGL(viewport[2],viewport[3]);
	if (!isShift) s_id.N=0;
	if (hits>0)
	{
		is	= ptr[3]-1;
		ih=0xffffffff;
		for(im = 0;im<hits;im++)
		{
			if (ih > ptr[4*im+1])
			{
				ih	= ptr[4*im+1];
				is	= ptr[4*im+3]-1;
			}
		}
		issel	= s_id.fnd(is);
		if(issel==-1)
		{
			s_id.add(is);
		}else
		{
			s_id.rem(1,issel);
		}
	}
	selAnalize();
	if(getMolSel())
	{
		selectMols();
	}else
	{
		sel_idm.N	= 0;
	}
	rendScene();
	update();
	selectDo();
	delete [] buffer;
	return 0;
}

void OpenGLWidget::selectMols()
{
	int ii,jj,jk,is;
	Molecule *lmol;
	vecT<int> idms(select_id.N);
	vecT<int> idat;
	vecT<int> r_id;
	s_id.N	= 0;
	jk	= -1;
	is	= 0;
	idat.setmem(idms.N);
	for(ii=0;ii<select_id.N;ii++)
	{
		idms.add(select_id.x[ii].x[0]);
		idat.add(select_id.x[ii].x[1]);
	}
	idms.sort_(idat);
	for(ii=0;ii<select_id.N;ii++)
	{
		select_id.x[ii].x[0]	= idms.x[ii];
		select_id.x[ii].x[1]	= idat.x[ii];
	}
	idat.N=0;
	for(ii=0;ii<select_id.N;ii++)
	{
		if(idat.N==0)
		{
			idat.add(select_id.x[ii].x[0]);
		}else
		{
			if(idat.x[idat.N-1]!=select_id.x[ii].x[0])
			{
				idat.add(select_id.x[ii].x[0]);
			}
		}
	}
	s_id.N	= 0;
	jk	= 0;
	sel_idm.pst(idat);
	r_id.setlen(mols.N);
	for(jj=0;jj<r_id.N;jj++)
	{
		r_id.x[jj]	= jk;
		jk	+= mols.x[jj]->Atoms.N;
	}
	jk	= 0;
	for(ii=0;ii<idat.N;ii++)
	{
		lmol	= reinterpret_cast< Molecule * >(mols.x[idat.x[ii]]);
		lmol->ids.N	= 0;
		jk	= r_id.x[idat.x[ii]];
		for(jj=0;jj<lmol->Atoms.N;jj++)
		{
			lmol->ids.add(jj);
			s_id.add(jk+jj);
		}
	}
	selAnalize();
}

void OpenGLWidget::selAnalize()
{
	Molecule *lmol;
	int jm;
	for(jm=0;jm<mols.N;jm++)
	{
		lmol	= reinterpret_cast< Molecule * > (mols.x[jm]);
		lmol->ids.N	= 0;
	}
	if(s_id.N>0)
	{
		vec2int loc;
		int id_c,jj;
		vecT<int> r_id;
		select_id.N	= 0;

		r_id.setlen(mols.N);
		if (select_id.mN < mols.N) select_id.setmem(mols.N);
		jm	= 0;
		for(jj=0;jj<r_id.N;jj++)
		{
			jm	+= mols.x[jj]->Atoms.N;
			r_id.x[jj]	= jm;
		}

		for(jm=0;jm<s_id.N;jm++)
		{
			id_c	= s_id.x[jm];
			for(jj=0;(jj<mols.N)&(id_c>=r_id.x[jj]);jj++);
			if(jj!=mols.N)
			{
				loc.x[0]	= jj; // номер молекулы
				loc.x[1]	= jj>0 ? id_c-r_id.x[jj-1]: id_c ; // номер атома в тек. молекуле
				select_id.add(loc);
			}
		}
		for(jm=0;jm<select_id.N;jm++)
		{
			lmol	= reinterpret_cast< Molecule * > (mols.x[select_id.x[jm].x[0]]);
			lmol->ids.add(select_id.x[jm].x[1]);
		}
	}else
	{
		select_id.N	= 0;
	}
}

void OpenGLWidget::sel2atom()
{
	Molecule *lmol;
	for(int jm=0;jm<select_id.N;jm++)
	{
		lmol	= reinterpret_cast< Molecule * > (mols.x[select_id.x[jm].x[0]]);
		lmol->ids.add(select_id.x[jm].x[1]);
	}
}

void OpenGLWidget::unselprod()
{
	if(select_id.N!=0)
	{
		int ii,jj;
		vecT<int> r_id;	// массив с номерами начала новых молекул при сплошной нумерации всех атомов сцены

		r_id.setlen(mols.N);

		ii	= 0;
		for(jj=1;jj<r_id.N;jj++)
		{
			ii	+= mols.x[jj-1]->Atoms.N;
			r_id.x[jj]	= ii;
		}
		if(s_id.mN<select_id.N) s_id.setmem(select_id.N);
		s_id.N	= select_id.N;
		for(ii=0;ii<select_id.N;ii++)
		{
			jj	= select_id.x[ii].x[0];
			s_id.x[ii]	= r_id.x[jj]+select_id.x[ii].x[1];
		}
	}
}

void OpenGLWidget::unselprod(vecT<vec2int> &s)
{
	if(s.N!=0)
	{
		int ii,jj;
		vecT<int> r_id;	// массив с номерами начала новых молекул при сплошной нумерации всех атомов сцены

		r_id.setlen(mols.N);

		ii	= 0;
		for(jj=1;jj<r_id.N;jj++)
		{
			ii	+= mols.x[jj-1]->Atoms.N;
			r_id.x[jj]	= ii;
		}
		if(s_id.mN<s.N) s_id.setmem(s.N);
		s_id.N	= s.N;
		for(ii=0;ii<s.N;ii++)
		{
			jj	= s.x[ii].x[0];
			s_id.x[ii]	= r_id.x[jj]+s.x[ii].x[1];
		}
	}
}

void OpenGLWidget::invertSel()
{
	//uselDo();
//	s_ids->N	= 0;
	int j	= 0;
	for (int im=0;im<mols.N;im++)
	{
		j	+= mols.x[im]->Atoms.N;
	}
	if (s_id.N!=0)
	{
		vecT<int> ids(j);
		int jj,ii;
		jj	= 0;
		s_id.sort();
		for(ii=0;(ii<j)&(jj<s_id.N);ii++)
		{
			if ((ii!=s_id.x[jj])&&(jj<s_id.N))
			{
				ids.add(ii);
			}else
			{
				jj++;
			}
		}
		for(;ii<j;ii++)
		{
			ids.add(ii);
		}
		s_id.pst(ids);


	}else
	{
		s_id.setlen(j);
		for(int ii=0;ii<j;ii++)
		{
			s_id.x[ii]=ii;
		}
	}
	selAnalize();
	if(getMolSel())
	{
		selectMols();
	}else
	{
		sel_idm.N	= 0;
	}
	rendScene();
	update();
	selectDo();
}

int OpenGLWidget::selectAtom(const QPoint &pos)
{
	int MaxSize,im,j,ik;
	GLuint *buffer,*ptr,ih;
	GLint viewport[4];
	GLdouble px,py,width,height;
	GLint hits;
	vecT<vec2int> nn; 
	double x,y,z,rd;
	int theSph,is;
	GLfloat param[4];
	GLfloat xx;

	j	= 0;
	for (im=0;im<mols.N;im++)
	{
		j	+= mols.x[im]->Atoms.N;
	}	
	MaxSize	= 4*j;
	buffer	= new GLuint [MaxSize];

	nn.setmem(j);

	/*if(theSph != 0) {glDeleteLists(theSph, 1);}
	theSph=glGenLists(1);
	glNewList(theSph,GL_COMPILE);
	gluQuadricDrawStyle(qobj, GLU_FILL); 
	gluSphere(qobj,1,30,21);
	glEndList();*/

	px	= pos.x();
	py	= pos.y();
	width	= 2;
	height	= 2;
	
	glGetIntegerv(GL_VIEWPORT,viewport);

	glSelectBuffer(MaxSize,buffer);
	glRenderMode(GL_SELECT);
	
	glInitNames();
	glPushName(0);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	xx	= GLfloat(viewport[2])/GLfloat(viewport[3]);
	//gluPerspective ( 60.0, xx, 1.0, 1000.0 );
	gluPickMatrix (px, (GLdouble)(viewport[3]-py), width, height, viewport );
	//glFrustum(-xx,xx,-1,1,2,1000.0);
	if (!isOrtho)
		gluPerspective(p_alf, xx, z_near, z_far );
	else
		glOrtho(-xx*mgnf,xx*mgnf,-mgnf,mgnf,z_near,z_far);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPopMatrix();
	

	rd	= 0.2;
	for (ik=0;ik<mols.N;ik++)
	{
	for(int i=0;i<mols.x[ik]->Atoms.N;i++)
		{

			j	= nn.N;
			nn.x[j].x[0]	= ik;
			nn.x[j].x[1]	= i;
			nn.N++;
			x	= mols.x[ik]->Atoms.x[i].r.x[0];
			y	= mols.x[ik]->Atoms.x[i].r.x[1];
			z	= mols.x[ik]->Atoms.x[i].r.x[2];

			j	= mols.x[ik]->Atoms.x[i].id_Tpz;
			rd	= WF->TableZR.Lines.x[j].vdwrad/500;//radius.x[i];
			glTranslated(x,y,z);
			glScaled(rd,rd,rd);
			//glPushName(i);
			glLoadName(nn.N);
			param[0]	= 0.5;param[1]	= 0.5;param[2]	= 0.5;param[3]	= 1;
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE,param);
			glCallList(theSph_);
			//gluSphere(qobj,rd,30,21);
			glScaled(1/rd,1/rd,1/rd);
			glTranslated(-x,-y,-z);
		}/**/
	}
	
	hits = glRenderMode(GL_RENDER);
	ptr	 = (GLuint*)buffer;
	resizeGL(viewport[2],viewport[3]);
	//if (!isShift) s_id.N=0;
	if (hits>0)
	{
		is	= ptr[3]-1;
		ih=0xffffffff;
		for(im = 0;im<hits;im++)
		{
			if (ih > ptr[4*im+1])
			{
				ih	= ptr[4*im+1];
				is	= ptr[4*im+3]-1;
			}
		}
		id_ml	= nn.x[is].x[0];
		id_at	= nn.x[is].x[1];
	}
	return 0;

}

bool OpenGLWidget::selectQuaC(const QPoint &pos)
{
	int MaxSize;
	GLuint *buffer,*ptr,ih;
	GLint viewport[4];
	GLdouble px,py,width,height;
	GLint hits;
	GLfloat param[4];
	GLfloat xx;
	vec3db qc;


	qc	= RW->GetDis();
	MaxSize	= 4;
	buffer	= new GLuint [MaxSize];

	px	= pos.x();
	py	= pos.y();
	width	= 2;
	height	= 2;
	
	glGetIntegerv(GL_VIEWPORT,viewport);

	glSelectBuffer(MaxSize,buffer);
	glRenderMode(GL_SELECT);
	
	glInitNames();
	glPushName(0);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	xx	= GLfloat(viewport[2])/GLfloat(viewport[3]);
	gluPickMatrix (px, (GLdouble)(viewport[3]-py), width, height, viewport );
	if (!isOrtho)
		gluPerspective(p_alf, xx, z_near, z_far );
	else
		glOrtho(-xx*mgnf,xx*mgnf,-mgnf,mgnf,z_near,z_far);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPopMatrix();
	
	glTranslated(qc.x[0],qc.x[1],qc.x[2]);
	gluSphere(qobj,0.1,30,21);
	glTranslated(-qc.x[0],-qc.x[1],-qc.x[2]);
	
	hits = glRenderMode(GL_RENDER);
	resizeGL(viewport[2],viewport[3]);
	return (hits>0);
}

int OpenGLWidget::selectFrameAction()
{
	int MaxSize,im,issel;
	GLuint *buffer,*ptr,ih;
	GLint viewport[4];
	GLdouble px,py,width,height;
	GLint hits;
	double x,y,z,rd;
	int theSph,is,j,jm;
	GLfloat param[4];
	GLfloat xx;

	j	= 0;
	for (im=0;im<mols.N;im++)
	{
		j	+= mols.x[im]->Atoms.N;
	}	
	MaxSize	= 4*j;
	buffer	= new GLuint [MaxSize];

	//rendPrmtv();

	px	= (ruc.x[0]+ldc.x[0])/2;
	py	= (ruc.x[1]+ldc.x[1])/2;
	width	= abs(ldc.x[0]-ruc.x[0]);
	height	= abs(ldc.x[1]-ruc.x[1]);

	glGetIntegerv(GL_VIEWPORT,viewport);

	glSelectBuffer(MaxSize,buffer);
	glRenderMode(GL_SELECT);
	
	glInitNames();
	glPushName(0);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	xx	= GLfloat(viewport[2])/GLfloat(viewport[3]);
	gluPickMatrix (px, (GLdouble)(viewport[3]-py), width, height, viewport );
	if (!isOrtho)
		gluPerspective(p_alf, xx, z_near, z_far );
	else
		glOrtho(-xx*mgnf,xx*mgnf,-mgnf,mgnf,z_near,z_far);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPopMatrix();
	

	is	= 0;
	for (jm=0;jm<mols.N;jm++)
	{
		for(int i=0;i<mols.x[jm]->Atoms.N;i++)
		{
			x	= mols.x[jm]->Atoms.x[i].r.x[0];
			y	= mols.x[jm]->Atoms.x[i].r.x[1];
			z	= mols.x[jm]->Atoms.x[i].r.x[2];

			rd	= WF->TableZR.Lines.x[mols.x[jm]->Atoms.x[i].id_Tpz].vdwrad/500;//radius.x[i];

			glTranslated(x,y,z);
			glScaled(rd,rd,rd);
			param[0]	= 0.5;param[1]	= 0.5;param[2]	= 0.5;param[3]	= 1;
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE,param);
			is++;
			glLoadName(is);
			glCallList(theSph_);
			//gluSphere(qobj,rd,30,21);
			glScaled(1/rd,1/rd,1/rd);
			glTranslated(-x,-y,-z);
		}
	}
	
	hits = glRenderMode(GL_RENDER);
	ptr	 = (GLuint*)buffer;
	resizeGL(viewport[2],viewport[3]);
	if (!isShift) s_id.N=0;
	if (hits>0)
	{
		is	= ptr[3]-1;
		ih=0xffffffff;
		for(im = 0;im<hits;im++)
		{
			is	= ptr[4*im+3]-1;
			issel	= s_id.fnd(is);
			if(issel==-1)
			{
				s_id.add(is);
			}else
			{
				s_id.rem(1,issel);
			}
		}
	}
	selAnalize();
	rendScene();
	update();
	selectDo();
	delete [] buffer;
	return 0;
}


void OpenGLWidget::selsort()
{
	if(select_id.N>0)
	{
		vecT<vecT<int> > xx;
		xx.setmem(select_id.N);
		vecT<int> id_mls;
		int ii,jj,kk,mm;
		kk	= -2;
		xx.setlen(mols.N);
		for(ii=0;ii<select_id.N;ii++)
		{
			jj	= select_id.x[ii].x[0]; // номер молекулы
			xx.x[jj].add(select_id.x[ii].x[1]);
			if(jj!=kk)	// если номер не совпадает с номером на предыдущей операции
			{
				mm	= id_mls.fnd(jj); // найти номер в массиве ранее найденых номеров
				if(mm==-1)	// если это новый номер
				{
					id_mls.add(jj);	// добавить новый номер в массив
				}
				kk	= jj;	// сохранить номер молекулы 
			}
		}
		id_mls.sort();
		for(ii=0;ii<id_mls.N;ii++)
		{
			jj	= id_mls.x[ii];
			xx.x[jj].sort();
		}
		mm	= 0;
		for(ii=id_mls.N-1;ii>=0;ii--)
		{
			jj	= id_mls.x[ii];
			for(kk=xx.x[jj].N-1;kk>=0;kk--)
			{
				select_id.x[mm].x[0]	= jj;
				select_id.x[mm].x[1]	= xx.x[jj].x[kk];
				mm++;
			}
		}
	}
}

int OpenGLWidget::faceAtPosition(const QPoint &pos)
{
	const int MaxSize	= 512;
	GLuint buffer[MaxSize];
	GLint viewport[4];

	glGetIntegerv(GL_VIEWPORT,viewport);
	glSelectBuffer(MaxSize,buffer);
	glRenderMode(GL_SELECT);

	glInitNames();
	glPushName(0);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluPickMatrix(GLdouble(pos.x()),GLdouble(viewport[3]-pos.y()),5.0,5.0,viewport);
	GLfloat x	= GLfloat (width())/ height();
	if (!isOrtho)
		gluPerspective(p_alf, x, z_near, z_far );
	else
		glOrtho(-x*mgnf,x*mgnf,-mgnf,mgnf,z_near,z_far);
	draw();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	if(!glRenderMode(GL_RENDER)) return -1;
	return buffer[3];
}
void OpenGLWidget::initmol(WorkFrame *wFr)
{
	WF	= wFr;
	createFontBits_Atoms();
}

void OpenGLWidget::setmolcrd(int id_mol)
{
	int ii;
	id_ml_	= id_mol;
	sel_xyz.setlen(mols.x[id_mol]->Atoms.N);
	for(ii=0;ii<sel_xyz.N;ii++)
	{
		sel_xyz.x[ii]	= mols.x[id_mol]->Atoms.x[ii].r;
	}
}

void OpenGLWidget::rotatproc()
{
	Quaternion<double> qa;
	FullMatrix<double> A;
	double sn;
	int ii;
	vec3db rr,p0(RW->GetDis()),p(RW->GetAxis()),drl;
	sn		= RW->GetAlfa()/2.0;
	drl		= p*(RW->GetDsp());
	qa.x[0]	= cos(sn);
	sn		= sin(sn);
	qa.x[1]	= sn*p.x[0];
	qa.x[2]	= sn*p.x[1];
	qa.x[3]	= sn*p.x[2];

	//Quat	= qa*Quat;

	A	= qa.qua2matrR();
	for(ii=0;ii<mols.x[id_ml_]->Atoms.N;ii++)
	{
		rr	= sel_xyz.x[ii]-p0;
		rr	= A*rr;
		mols.x[id_ml_]->Atoms.x[ii].r	=	rr+p0+drl;
	}
	rendScene();
	update();
}

void OpenGLWidget::clearAllthes()
{
	int ii;
	
	for(ii=0;ii<theAtoms.N;ii++)
	{
		glDeleteLists(theAtoms.x[ii],1);
		theAtoms.x[ii]	= 0;
	}
	theAtoms.N	= 0;
	for(ii=0;ii<theBonds.N;ii++)
	{
		glDeleteLists(theBonds.x[ii],1);
		theBonds.x[ii]	= 0;
	}
	theBonds.N	= 0;
	for(ii=0;ii<theWires.N;ii++)
	{
		glDeleteLists(theWires.x[ii],1);
		theWires.x[ii]	= 0;
	}
	theWires.N	= 0;
	for(ii=0;ii<theMols.N;ii++)
	{
		glDeleteLists(theMols.x[ii],1);
		theMols.x[ii]	= 0;
	}
	theMols.N=0;
	for(ii=0;ii<theAtomsChars.N;ii++)
	{
		glDeleteLists(theAtomsChars.x[ii],1);
		theAtomsChars.x[ii]	= 0;
	}
	theAtomsChars.N	= 0;

	/*for(ii=0;ii<theSurfaces.N;ii++)
	{
		glDeleteLists(theSurfaces.x[ii],1);
		theSurfaces.x[ii]	= 0;
	}
	theSurfaces.N	= 0;*/
}

void OpenGLWidget::initAllthes()
{
	int ii;
	ii	= WF->Mls.N+WF->Prot.N;
	if(theMols.mN<ii)
	{
		theMols.setlen(ii);
	}
	theMols.N	= ii;
	if(theAtoms.mN<ii)
	{
		theAtoms.setlen(ii);
	}
	theAtoms.N	= ii;
	if(theBonds.mN<ii)
	{
		theBonds.setlen(ii);
	}
	theBonds.N	= ii;
	if(theWires.mN<ii)
	{
		theWires.setlen(ii);
	}
	theWires.N	= ii;
	if(theAtomsChars.mN<ii)
	{
		theAtomsChars.setlen(ii);
	}
	theAtomsChars.N	= ii;

	/*ii	= WF->Srfcs.N;
	if(theSurfaces.mN<ii)
	{
		theSurfaces.setlen(ii);
	}
	theSurfaces.N	= ii;*/
}

void OpenGLWidget::setmols(vecT<ConnectedAtoms * > &in_mols)
{
	if(mols.mN<in_mols.N) mols.setlen(in_mols.N);
	for(int ii=0;ii<in_mols.N;ii++)
	{
		mols.x[ii]	= in_mols.x[ii];
	}
}

void OpenGLWidget::rendScene()
{
	clearAllthes();
	initAllthes();
	rendPrmtv();
	int ii,jj;
	ii	= WF->Mls.N+WF->Prot.N;
	if(mols.mN<ii) 
	{
		mols.setmem(ii);
	}
	mols.N	= ii;
	jj	= 0;
	for(ii=0;ii<WF->Mls.N;ii++)
	{
		mols.x[jj]	= WF->Mls.x[ii];
		jj++;
	}
	for(ii=0;ii<WF->Prot.N;ii++)
	{
		mols.x[jj]	= WF->Prot.x[ii];
		jj++;
	}
	for(ii=0;ii<mols.N;ii++)
	{
		rendMol(mols.x[ii],ii);
	}

	for(ii=0;ii<mols.N;ii++)
	{
		rendAtomsChar(mols.x[ii],ii);
	}

	if (theAtCh_!=0)
	{
		glDeleteLists(theAtCh_,1);
	}

	if(isActSpcShow)
	{
		rendActSpc();
	}

	if(isSurfModify)
	{
		int tp;
		double tsp;
		isSurf	= true; 
		for(ii=0;ii<theSurfaces.N;ii++)
		{
			glDeleteLists(theSurfaces.x[ii],1);
			theSurfaces.x[ii]	= 0;
		}
		theSurfaces.N	= 0;

		ii	= WF->Srfcs.N;
		if(theSurfaces.mN<ii)
		{
			theSurfaces.setlen(ii);
		}
		theSurfaces.N	= ii;

		for(ii=0;ii<WF->Srfcs.N;ii++)
		{
			tp	= WF->Srfcs.x[ii]->getviztype();
			tp	= tp==-1 ? 1 : tp;
			tsp	= WF->Srfcs.x[ii]->gettransp();
			rendSurface(WF->Srfcs.x[ii],ii,tp,tsp);
		}

	/*	if(theSurf!=0)
		{
			glDeleteLists(theSurf,1);
		}
		theSurf	= glGenLists(1);
		glNewList(theSurf,GL_COMPILE);
		for(ii=0;ii<theSurfaces.N;ii++)
		{
			glCallList(theSurfaces.x[ii]);
		}
		glEndList();*/
	}

	if(theSurf!=0)
	{
		glDeleteLists(theSurf,1);
	}
	theSurf	= glGenLists(1);
	glNewList(theSurf,GL_COMPILE);
	for(ii=0;ii<theSurfaces.N;ii++)
	{
		glCallList(theSurfaces.x[ii]);
	}
	glEndList();

	theAtCh_=glGenLists(1);
	glNewList(theAtCh_,GL_COMPILE);
	for(ii=0;ii<mols.N;ii++)
	{
		glCallList(theAtomsChars.x[ii]);
	}

	glEndList();

	if (theScene!=0)
	{
		glDeleteLists(theScene,SCENE);
	}
	theScene=glGenLists(SCENE);
	glNewList(theScene,GL_COMPILE);
	
	glDisable(GL_LIGHT0);

	GLfloat light_ambient[] = {.0, .0, .0, 1};

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);

	GLfloat light_diffuse[] = {0.0, 0.0, 0.0, 1};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

	GLfloat light_shine[] = {0., 0., 0., 1};
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_shine);

	GLfloat mat_shininess[] = { 5.0 };
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	//GLfloat mat_shine[] = {0.1, 0.1, 0.1, 1};
	//glMaterialfv(GL_FRONT, GL_SPECULAR,mat_shine);

	//glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	//glMaterialfv(GL_FRONT, GL_SPECULAR,param);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	for(ii=0;ii<mols.N;ii++)
	{
		glCallList(theMols.x[ii]);
	}

	glEndList();

	if(isSelParShow)
	{
		updateSelPar();
	}


}

void OpenGLWidget::rendActSpc()
{
	vec3db rc;
	vec3db abc;

	rc	= AS->getrc();
	abc	= AS->getabc();
	abc	/= 2.0;

	GLfloat param[4];

	GLfloat vertices[24];
	GLuint	indices[24];
	GLuint	edgeind[24];
	//GLuint	normals[24];
	GLfloat colors[24];
	
	edgeind[0]	= 0;
	edgeind[1]	= 1;
	edgeind[2]	= 0;
	edgeind[3]	= 4;
	edgeind[4]	= 0;
	edgeind[5]	= 3;

	edgeind[6]	= 6;
	edgeind[7]	= 7;
	edgeind[8]	= 6;
	edgeind[9]	= 5;
	edgeind[10]	= 6;
	edgeind[11]	= 2;

	edgeind[12]	= 5;
	edgeind[13]	= 4;
	edgeind[14]	= 4;
	edgeind[15]	= 7;
	edgeind[16]	= 7;
	edgeind[17]	= 3;
	edgeind[18]	= 3;
	edgeind[19]	= 2;
	edgeind[20]	= 2;
	edgeind[21]	= 1;
	edgeind[22]	= 1;
	edgeind[23]	= 5;

	


	indices[0]	= 0;
	indices[1]	= 4;
	indices[2]	= 7;
	indices[3]	= 3;

	indices[4]	= 4;
	indices[5]	= 5;
	indices[6]	= 6;
	indices[7]	= 7;

	indices[8]	= 5;
	indices[9]	= 1;
	indices[10]	= 2;
	indices[11]	= 6;

	indices[12]	= 1;
	indices[13]	= 0;
	indices[14]	= 3;
	indices[15]	= 2;

	indices[16]	= 4;
	indices[17]	= 0;
	indices[18]	= 1;
	indices[19]	= 5;

	indices[20]	= 3;
	indices[21]	= 7;
	indices[22]	= 6;
	indices[23]	= 2;

	vertices[0]	= rc.x[0]-abc.x[0];
	vertices[1]	= rc.x[1]-abc.x[1];
	vertices[2]	= rc.x[2]-abc.x[2];

	vertices[3]	= rc.x[0]+abc.x[0];
	vertices[4]	= rc.x[1]-abc.x[1];
	vertices[5]	= rc.x[2]-abc.x[2];

	vertices[6]	= rc.x[0]+abc.x[0];
	vertices[7]	= rc.x[1]-abc.x[1];
	vertices[8]	= rc.x[2]+abc.x[2];

	vertices[9]	= rc.x[0]-abc.x[0];
	vertices[10]= rc.x[1]-abc.x[1];
	vertices[11]= rc.x[2]+abc.x[2];

	vertices[12]= rc.x[0]-abc.x[0];
	vertices[13]= rc.x[1]+abc.x[1];
	vertices[14]= rc.x[2]-abc.x[2];

	vertices[15]= rc.x[0]+abc.x[0];
	vertices[16]= rc.x[1]+abc.x[1];
	vertices[17]= rc.x[2]-abc.x[2];

	vertices[18]= rc.x[0]+abc.x[0];
	vertices[19]= rc.x[1]+abc.x[1];
	vertices[20]= rc.x[2]+abc.x[2];

	vertices[21]= rc.x[0]-abc.x[0];
	vertices[22]= rc.x[1]+abc.x[1];
	vertices[23]= rc.x[2]+abc.x[2];

	for(int ii=0;ii<24;ii++)
	{
		colors[ii]	= 0.5;
	}


	//glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	//glColorPointer(3, GL_FLOAT, 0, colors);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	//glEdgeFlagPointer(0 ,edgeflags);


	if(theActSpc!=0)
	{
		glDeleteLists(theActSpc,1);
	}
	theActSpc=glGenLists(1);
	glNewList(theActSpc,GL_COMPILE);

	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);

	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);

	/*param[0]	= 0.0;param[1]	= 0.0;param[2]	= 0.0;param[3]	= 0.0;
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,param);

	GLfloat light_diffuse[] = {1, 1, 1, 1};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS,0.0);

	param[0]	= 0.0;param[1]	= 0.0;param[2]	= 0.0;param[3]	= 0.0;
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,param);

	param[0]	= 0.0;param[1]	= 0.0;param[2]	= 0.0;param[3]	= 0;
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,param);

	//GLfloat light_specular[] = {1, 1, 1, 1};
	//glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);	

	param[0]	= 0.5;param[1]	= 0.5;param[2]	= 0.5;param[3]	= 0.5;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,param);

	GLfloat light_ambient[] = {1.0, 1.0, 1.0, 1.0};
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
*/

	
	param[0]	= 0.25;param[1]	= 0.25;param[2]	= 0.25;param[3]	= 0.5;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,param);
	glColor3fv(param);
	//glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 30);	


	/**/
	//glShadeModel(GL_FLAT);
	glPolygonMode(GL_BACK, GL_FILL);
	glPolygonMode(GL_FRONT, GL_FILL);
	glDisable(GL_CULL_FACE);
	//glHint(GL_FOG_HINT,GL_NICEST);
	//glDisable(GL_POLYGON_SMOOTH);



	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT);
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, indices);
	//glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, edgeind);

	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);

	glDisable(GL_COLOR_MATERIAL);
	//glShadeModel(GL_SMOOTH);
	glEnable(GL_CULL_FACE);
	//glEnable(GL_POLYGON_SMOOTH);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEndList();

	//isSurf	= true;

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void OpenGLWidget::rendAtomsChar(ConnectedAtoms *mol,int jm)
{
	int ii,jj;
	Molecule * lmol;
	lmol	= reinterpret_cast< Molecule* > (mol);

	if (theAtomsChars.x[jm]!=0) 
	{
		glDeleteLists(theAtomsChars.x[jm], 1);
	}

	theAtomsChars.x[jm]=glGenLists(1);
	glNewList(theAtomsChars.x[jm],GL_COMPILE);


	rendAtCh();

	/*double x,y,z;
	QString str;
	QFont font("Times",10);
	for(ii=0;ii<lmol->Atoms.N;ii++)
	{

		x	= mol->Atoms.x[ii].r.x[0];
		y	= mol->Atoms.x[ii].r.x[1];
		z	= mol->Atoms.x[ii].r.x[2];

		jj	= lmol->Atoms.x[ii].id_Tpz;
		//str.fromLocal8Bit(WF->TableZR.Lines.x[jj].Ch.x,2);
		str.clear();
		str.append(QChar(WF->TableZR.Lines.x[jj].Ch.x[0]));
		if(WF->TableZR.Lines.x[jj].Ch.x[1]!='\0') str.append(QChar(WF->TableZR.Lines.x[jj].Ch.x[1]));
//		glTranslated(x,y,z);
		renderText(x,y,z,str,font);//, const QFont & font = QFont(), int listBase = 2000 );
//		glTranslated(-x,-y,-z);
	}*/

	glEndList();
}

/*void OpenGLWidget::rendCub(int id_cub)
{
	if (theCubs.x[id_cub]!=0) 
	{
		glDeleteLists(theMols.x[id_cub],1);
	}
	theCubs.x[id_cub]=glGenLists(1);
	glNewList(theCubs.x[id_cub],GL_COMPILE);

}/**/

void OpenGLWidget::rendMol(ConnectedAtoms *mol,int jm)
{
	Molecule * lmol;
	lmol	= reinterpret_cast< Molecule* > (mol);
	if (lmol->drawtype==0)
	{
		rendAtoms(mol,jm);
		if(mol->Bonds.N!=0) rendBonds(mol,jm);
	}else
	{
		rendWire(mol,jm);
	}

	if (theMols.x[jm]!=0) 
	{
		glDeleteLists(theMols.x[jm],1);
	}
	theMols.x[jm]=glGenLists(1);
	glNewList(theMols.x[jm],GL_COMPILE);

	if (lmol->drawtype==0)
	{
		glCallList(theAtoms.x[jm]);
		if(mol->Bonds.N!=0) glCallList(theBonds.x[jm]);
	}else
	{
		glCallList(theWires.x[jm]);
	}
	
	glEndList();
}
void OpenGLWidget::rendAtoms(ConnectedAtoms *mol,int jm)
{
	if (theAtoms.x[jm]!=0) 
	{
		glDeleteLists(theAtoms.x[jm], 1);
	}
	theAtoms.x[jm]=glGenLists(1);
	glNewList(theAtoms.x[jm],GL_COMPILE);

	int ii,ia;
	double x,y,z,rd;
	double r,g,b;
	GLfloat param[4];
	int isl;

	Molecule * lmol;

	lmol	= reinterpret_cast< Molecule* > (mol);

	for (ii=0;ii<mol->Atoms.N;ii++)
	{
		x	= mol->Atoms.x[ii].r.x[0];
		y	= mol->Atoms.x[ii].r.x[1];
		z	= mol->Atoms.x[ii].r.x[2];

		ia	= mol->Atoms.x[ii].id_Tpz;

		r	= double(WF->TableZR.Lines.x[ia].color.x[0])/256;
		g	= double(WF->TableZR.Lines.x[ia].color.x[1])/256;
		b	= double(WF->TableZR.Lines.x[ia].color.x[2])/256;

		rd	= WF->TableZR.Lines.x[ia].vdwrad/500;

		if(lmol->ids.fnd(ii)!=-1)
		{
			r	= 1;
			g	= 0;
			b	= 1;
		}

		glTranslated(x,y,z);
		glScaled(rd,rd,rd);

		param[0]	= 0.3*rd;param[1]	= 0.3*rd;param[2]	= 0.3*rd;param[3]	= 1.0;
		glLightfv (GL_LIGHT0, GL_AMBIENT, param);

		param[0]	= rd;param[1]	= rd;param[2]	= rd;param[3]	= 1.0;
		glLightfv (GL_LIGHT0, GL_DIFFUSE, param);

		param[0]	= 0.01*rd;param[1]	= 0.01*rd;param[2]	= 0.01*rd;param[3]	= 1.0;
		glLightfv (GL_LIGHT1, GL_SPECULAR, param);

		param[0]	= r;param[1]	= g;param[2]	= b;param[3]	= 1.0;
		glMaterialfv(GL_FRONT, GL_DIFFUSE,param);
		glMaterialfv(GL_FRONT, GL_AMBIENT,param);
		//param[0]	= 0.1;param[1]	= 0.1;param[2]	= 0.1;param[3]	= 1.0;
		glMaterialfv(GL_FRONT, GL_SPECULAR,param);

		GLfloat mat_shininess[] = { 16*rd };
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

		//gluSphere(qobj,rd,30,21);
		glCallList(theSph_);
		glScaled(1/rd,1/rd,1/rd);
		glTranslated(-x,-y,-z);
	}
	glEndList();
}

void OpenGLWidget::rendSurface(Surface *srf,int jm,int tp,double tsp)
{
	srf->setviztype(tp);
	srf->settransp(tsp);
	if ((tp==1)||(tp==2))
	{

		int i1;

		//vecT<int> tr_flg;

		//GLfloat xc,yc,zc;

		GLfloat param[4];

		GLfloat *vertices;
		GLfloat *normals;
		GLfloat *colors;
		GLuint	*indices;
		GLuint  *edgeind;

		colors		= new GLfloat [3*srf->Surf.Point.N];
		vertices	= new GLfloat [3*srf->Surf.Point.N];
		normals		= new GLfloat [3*srf->Surf.Point.N];
		indices		= new GLuint  [3*srf->Surf.Trngl.N];
		edgeind		= new GLuint  [2*srf->Surf.Edge.N];

		for(int ii=0;ii<srf->Surf.Edge.N;ii++)	
		{
			edgeind[2*ii]=srf->Surf.Edge.x[ii].n_pnt.x[0];
			edgeind[2*ii+1]=srf->Surf.Edge.x[ii].n_pnt.x[1];
		}

		for(int ii=0;ii<srf->Surf.Trngl.N;ii++)
		{
			indices[3*ii]	= srf->Surf.Trngl.x[ii].n_pnt.x[0];
			indices[3*ii+1]	= srf->Surf.Trngl.x[ii].n_pnt.x[1];
			indices[3*ii+2]	= srf->Surf.Trngl.x[ii].n_pnt.x[2];
		}


		vec3int col = srf->getcolor();

		if(col.x[0]==-1)
		{
			for(int ii=0;ii<srf->Surf.Point.N;ii++)
			{
				colors[3*ii]	= srf->Surf.Point.x[ii].clr.x[0];
				colors[3*ii+1]	= srf->Surf.Point.x[ii].clr.x[1];
				colors[3*ii+2]	= srf->Surf.Point.x[ii].clr.x[2];
			}
		}else
		{

			if(col.x[0]==-2)
			{
				for(int ii=0;ii<srf->Surf.Point.N;ii++)
				{
					switch (srf->Surf.Point.x[ii].stp.x[0])
					{
					case 	0 :
							{
								colors[3*ii]	= 0;
								colors[3*ii+1]	= 1;
								colors[3*ii+2]	= 1;
								break;
							}
					case 	1 :
							{
								colors[3*ii]	= 0;
								colors[3*ii+1]	= 1;
								colors[3*ii+2]	= 0;
								break;
							}
					case 	2 :
							{
								colors[3*ii]	= 1;
								colors[3*ii+1]	= 0.3;
								colors[3*ii+2]	= 0;
								break;
							}
					case 	3 :
							{
								colors[3*ii]	= 1;
								colors[3*ii+1]	= 1;
								colors[3*ii+2]	= 0;
								break;
							}
					case 	4 :
							{
								colors[3*ii]	= 1;
								colors[3*ii+1]	= 1;
								colors[3*ii+2]	= 0;
								break;
							}
					case 	5 :
							{
								colors[3*ii]	= 0.8;
								colors[3*ii+1]	= 0;
								colors[3*ii+2]	= 0.8;
								break;
							}
					case 	6 :
							{
								colors[3*ii]	= 0;
								colors[3*ii+1]	= 0;
								colors[3*ii+2]	= 1;
								break;
							}					
					}
				}
			}else
			{
				vec3db dcl;
				dcl.x[0]	= col.x[0];dcl.x[1]	= col.x[1];dcl.x[2]	= col.x[2];
				dcl	/= 255.0;
				for(int ii=0;ii<srf->Surf.Point.N;ii++)
				{
					colors[3*ii]	= dcl.x[0];
					colors[3*ii+1]	= dcl.x[1];
					colors[3*ii+2]	= dcl.x[2];
				}
			}
		}

		for(int ii=0;ii<srf->Surf.Point.N;ii++)
		{
			vertices[3*ii]		= srf->Surf.Point.x[ii].crd.x[0];//-xc;
			vertices[3*ii+1]	= srf->Surf.Point.x[ii].crd.x[1];//-yc;
			vertices[3*ii+2]	= srf->Surf.Point.x[ii].crd.x[2];//-zc;

			normals[3*ii]		= srf->Surf.Point.x[ii].nor.x[0];
			normals[3*ii+1]		= srf->Surf.Point.x[ii].nor.x[1];
			normals[3*ii+2]		= srf->Surf.Point.x[ii].nor.x[2];
		}

		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		//glEnableClientState(GL_EDGE_FLAG_ARRAY);

		glColorPointer(3, GL_FLOAT, 0, colors);
		glVertexPointer(3, GL_FLOAT, 0, vertices);
		glNormalPointer(GL_FLOAT,0, normals);
		//glEdgeFlagPointer(0 ,edgeflags);

		i1	= 3*srf->Surf.Trngl.N;



		if(theSurfaces.x[jm]!=0)
		{
			glDeleteLists(theSurfaces.x[jm],1);
		}
		theSurfaces.x[jm]=glGenLists(1);
		glNewList(theSurfaces.x[jm],GL_COMPILE);

		/**/glDisable(GL_LIGHT0);
		glDisable(GL_LIGHTING);

		if(tsp!=1.0)
		{
			glEnable(GL_BLEND);
			glDepthMask(GL_FALSE);
			glBlendFunc(GL_SRC_ALPHA,GL_ONE);
		}

		param[0]	= 0.0;param[1]	= 0.0;param[2]	= 0.0;param[3]	= tsp;
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,param);

		GLfloat light_diffuse[] = {1, 1, 1, 1};
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS,0.0);

		param[0]	= 0.0;param[1]	= 0.0;param[2]	= 0.0;param[3]	= tsp;
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,param);

		param[0]	= 0.0;param[1]	= 0.0;param[2]	= 0.0;param[3]	= 0;
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,param);

		//GLfloat light_specular[] = {1, 1, 1, 1};
		//glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);	

		param[0]	= 0;param[1]	= 0;param[2]	= 0;param[3]	= 0;
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,param);

		GLfloat light_ambient[] = {0.0, 0.0, 0.0, 0};
		glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);


		//glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 30);	

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		/**/
		//glShadeModel(GL_FLAT);
		glPolygonMode(GL_BACK, GL_LINE);
		glPolygonMode(GL_FRONT, GL_FILL);
		glDisable(GL_CULL_FACE);
		glHint(GL_FOG_HINT,GL_NICEST);
		//glDisable(GL_POLYGON_SMOOTH);



		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
		//  ? glColorMaterial(GL_FRONT, GL_SPECULAR);
		switch (tp)
		{
		case 1:
			{
				glDrawElements(GL_TRIANGLES, i1, GL_UNSIGNED_INT, indices);
				break;
			}
		case 2:
			{
				glDrawElements(GL_LINES, i1, GL_UNSIGNED_INT, edgeind);
			}
		}

		if(tsp!=1.0)
		{
			glDepthMask(GL_TRUE);
			glDisable(GL_BLEND);
		}
		
		glDisable(GL_COLOR_MATERIAL);
		//glShadeModel(GL_SMOOTH);
		glEnable(GL_CULL_FACE);
		//glEnable(GL_POLYGON_SMOOTH);
		glEndList();



		//isSurf	= true;

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		//glDisableClientState(GL_EDGE_FLAG_ARRAY);



		delete [] vertices;
		delete [] colors;
		delete [] normals;
		delete [] indices;
		delete [] edgeind;
	}else
	{
		if(theSurfaces.x[jm]!=0)
		{
			glDeleteLists(theSurfaces.x[jm],1);
		}
		theSurfaces.x[jm]	= 0;
	}
}

void OpenGLWidget::rendBonds(ConnectedAtoms *mol,int jm)
{
	if (theBonds.x[jm]!=0) 
	{
		glDeleteLists(theBonds.x[jm],1);
	}
	theBonds.x[jm]=glGenLists(1);
	glNewList(theBonds.x[jm],GL_COMPILE);

	int ii,ia;
	double x,y,z,rd;
	double dx,dy,dz;
	double r,g,b,r1,g1,b1;
	double lb,th,fi;
	GLfloat param[4];
	int isl;

	for (ii=0;ii<mol->Bonds.N;ii++)
	{
		ia	= mol->Bonds.x[ii].id_Atoms.x[0];
		x	= mol->Atoms.x[ia].r.x[0];
		y	= mol->Atoms.x[ia].r.x[1];
		z	= mol->Atoms.x[ia].r.x[2];

		ia	= mol->Atoms.x[ia].id_Tpz;

		r	= double(WF->TableZR.Lines.x[ia].color.x[0])/256;
		g	= double(WF->TableZR.Lines.x[ia].color.x[1])/256;
		b	= double(WF->TableZR.Lines.x[ia].color.x[2])/256;

		ia	= mol->Bonds.x[ii].id_Atoms.x[1];
		dx	= (mol->Atoms.x[ia].r.x[0])-x;
		dy	= (mol->Atoms.x[ia].r.x[1])-y;
		dz	= (mol->Atoms.x[ia].r.x[2])-z;

		ia	= mol->Atoms.x[ia].id_Tpz;

		r1	= double(WF->TableZR.Lines.x[ia].color.x[0])/256;
		g1	= double(WF->TableZR.Lines.x[ia].color.x[1])/256;
		b1	= double(WF->TableZR.Lines.x[ia].color.x[2])/256;

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

		glTranslated (x,y,z); 
		glRotated ( 180*fi/pi, 0, 0, 1);
		glRotated ( 180*th/pi, 0, 1, 0);

		glScaled (0.07, 0.07, 0.5*lb); 

		param[0]	= 0.3*0.07;param[1]	= 0.3*0.07;param[2]	= 0.3*0.07;param[3]	= 1.0;
		glLightfv (GL_LIGHT0, GL_AMBIENT, param);

		param[0]	= 0.05;param[1]	= 0.05;param[2]	= 0.05;param[3]	= 1.0;
		glLightfv (GL_LIGHT0, GL_DIFFUSE, param);

		param[0]	= 0.1*0.07;param[1]	= 0.1*0.07;param[2]	= 0.1*0.07;param[3]	= 1.0;
		glLightfv (GL_LIGHT1, GL_SPECULAR, param);

		param[0]	= r;param[1]	= g;param[2]	= b;param[3]	= 1.0;
		glMaterialfv(GL_FRONT, GL_DIFFUSE,param);
		glMaterialfv(GL_FRONT, GL_AMBIENT,param);
		glMaterialfv(GL_FRONT, GL_SPECULAR,param);
		GLfloat mat_shininess[] = { 1.5 };
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
		if(mol->Bonds.x[ii].oder==1)
		{
			glCallList(theCyl_);			
		}
		else
		{
			if(mol->Bonds.x[ii].oder==2)
			{
				glCallList(the2Cyl_);
			}
			else 
			{
				glCallList(the3Cyl_);
			}
		}
		glTranslated ( 0, 0, 1); 
		param[0]	= r1;param[1]	= g1;param[2]	= b1;param[3]	= 1.0;
		glMaterialfv(GL_FRONT, GL_DIFFUSE,param);
		glMaterialfv(GL_FRONT, GL_AMBIENT,param);
		glMaterialfv(GL_FRONT, GL_SPECULAR,param);
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
		if(mol->Bonds.x[ii].oder==1)
		{
			glCallList(theCyl_);			
		}
		else
		{
			if(mol->Bonds.x[ii].oder==2)
			{
				glCallList(the2Cyl_);
			}
			else 
			{
				glCallList(the3Cyl_);
			}
		}
		glPopMatrix();

	}

	glEndList();
}

void OpenGLWidget::rendWire(ConnectedAtoms *mol,int jm)
{
	double x,y,z,x1,y1,z1;
	int it,ia;
	double r,g,b;

	GLfloat param[4];

	if (theWires.x[jm]!=0) 
	{
		glDeleteLists(theWires.x[jm],1);
	}
	theWires.x[jm]=glGenLists(1);

	glNewList(theWires.x[jm],GL_COMPILE);

	param[0]	= 1;param[1]	= 1;param[2]	= 1;param[3]	= 1.0;
	glLightfv (GL_LIGHT0, GL_AMBIENT, param);

	glBegin(GL_LINES);

	for(int i=0;i<mol->Bonds.N;i++)
	{
		ia	= mol->Bonds.x[i].id_Atoms.x[0];
		x	= mol->Atoms.x[ia].r.x[0];
		y	= mol->Atoms.x[ia].r.x[1];
		z	= mol->Atoms.x[ia].r.x[2];

		it	= mol->Atoms.x[ia].id_Tpz;
		r	= double(WF->TableZR.Lines.x[it].color.x[0])/256;
		g	= double(WF->TableZR.Lines.x[it].color.x[1])/256;
		b	= double(WF->TableZR.Lines.x[it].color.x[2])/256;

		param[0]	= r;param[1]	= g;param[2]	= b;param[3]	= 0;
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,param);
		glVertex3f(x,y,z);
		ia	= mol->Bonds.x[i].id_Atoms.x[1];
		x1	= mol->Atoms.x[ia].r.x[0];
		y1	= mol->Atoms.x[ia].r.x[1];
		z1	= mol->Atoms.x[ia].r.x[2];
		glVertex3f((x+x1)/2,(y+y1)/2,(z+z1)/2);


		if(mol->Bonds.x[i].oder>1)
		{
			for(int j=1;j<mol->Bonds.x[i].oder;j++)
			{
				glVertex3f(x+0.05*j,y,z);
				glVertex3f(0.5*(x+x1)+0.05*j,(y+y1)/2,(z+z1)/2);
			}
		}

		it	= mol->Atoms.x[ia].id_Tpz;
		r	= double(WF->TableZR.Lines.x[it].color.x[0])/256;
		g	= double(WF->TableZR.Lines.x[it].color.x[1])/256;
		b	= double(WF->TableZR.Lines.x[it].color.x[2])/256;

		param[0]	= r;param[1]	= g;param[2]	= b;param[3]	= 0;
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,param);

		glVertex3f((x+x1)/2,(y+y1)/2,(z+z1)/2);
		glVertex3f(x1,y1,z1);
		if(mol->Bonds.x[i].oder>1)
		{
			for(int j=1;j<mol->Bonds.x[i].oder;j++)
			{
				glVertex3f((x+x1)/2+0.05,(y+y1)/2,(z+z1)/2);
				glVertex3f(x1+0.05,y1,z1);
			}
		}
	}

	glEnd();
	glEndList();

	/*	if (theWire!=0) 
	{
	glDeleteLists(theWire, 12);
	}
	theWire=glGenLists(12);
	glNewList(theWire,GL_COMPILE);

	glDisable(GL_LIGHT0);

	GLfloat light_ambient[] = {1, 1, 1, 1};

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);

	GLfloat light_diffuse[] = {0.0, 0.0, 0.0, 1};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	//glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glCallList(twr);

	glEndList();*/

	//glDeleteLists(twr, 11);
}

void OpenGLWidget::rendPrmtv()
{
	if (theSph_!=0) 
	{
		glDeleteLists(theSph_, 1);//SPHERE);
	}

	theSph_=glGenLists(1);//SPHERE);
	glNewList(theSph_,GL_COMPILE);
	gluQuadricDrawStyle(qobj, GLU_FILL); 
	gluSphere(qobj,1.0,30,21);
	glEndList();

	GLdouble base,top,height;
	GLint slices,stacks;

	height	= base	= top	= 1.0;
	slices	= 20;
	stacks	= 2;

	if (theCyl_!=0) 
	{
		glDeleteLists(theCyl_, 1);//CYLINDER1);
	}
	theCyl_=glGenLists(1);//CYLINDER1);
	glNewList(theCyl_,GL_COMPILE);
	gluQuadricDrawStyle(qobj1, GLU_FILL); 	
	gluCylinder(qobj1,  base,  top,  height,  slices, stacks); 
	glEndList();

	if (the2Cyl_!=0) 
	{
		glDeleteLists(the2Cyl_, 1);// CYLINDER2);
	}
	the2Cyl_=glGenLists( 1);//CYLINDER2);
	glNewList(the2Cyl_,GL_COMPILE);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslated(-1,0,0);
	gluQuadricDrawStyle(qobj2, GLU_FILL); 	
	gluCylinder(qobj2,  base,  top,  height,  slices, stacks); 
	glTranslated(2.0,0,0);
	gluQuadricDrawStyle(qobj3, GLU_FILL); 	
	gluCylinder(qobj3,  base,  top,  height,  slices, stacks); 
	glPopMatrix();
	glEndList();

	if (the3Cyl_!=0) 
	{
		glDeleteLists(the3Cyl_, 1);//CYLINDER3);
	}
	the3Cyl_=glGenLists( 1);//CYLINDER3);
	glNewList(the3Cyl_,GL_COMPILE);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslated(0,1,0);
	gluQuadricDrawStyle(qobj1, GLU_FILL); 	
	gluCylinder(qobj1,  base,  top,  height,  slices, stacks); 
	glTranslated(-0.866,-1.5,0);
	gluQuadricDrawStyle(qobj2, GLU_FILL); 	
	gluCylinder(qobj2,  base,  top,  height,  slices, stacks); 
	glTranslated(1.732,0,0);
	gluQuadricDrawStyle(qobj3, GLU_FILL); 	
	gluCylinder(qobj3,  base,  top,  height,  slices, stacks); 
	glPopMatrix();
	glEndList();

}
/*void OpenGLWidget::genScene1()	// сгенерировать сцену с молекулой
{}

void OpenGLWidget::genScene()	// сгенерировать сцену с молекулой
{
	if(WF->Mls.N>0)
	{

		//makeCurrent();

		double x,y,z,x0,y0,z0,rd;
		int ia;//theSph,theCyl,the2Cyl,the3Cyl;
		double r,g,b,r1,g1,b1;

		GLfloat param[4];

		vec3db pnt;

		scenetype	= 1;

		//WF	= &wFr;

		/*glDisable(GL_LIGHT0);

		GLfloat light_diffuse[] = {0.2, 0.2, 0.2, 0};

		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

		GLfloat light_ambient[] = {0.0, 0.0, 0.0, 1};
		glLightfv(GL_LIGHT0, GL_AMBIENT, light_diffuse);

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);*/
/*
		x0	= y0	= z0	= 0.0;
		/*for(int i=0;i<WF->Mls.x[0]->Atoms.N;i++)
		{
		x0	+= WF->Mls.x[0]->Atoms.x[i].r.x[0];
		y0	+= WF->Mls.x[0]->Atoms.x[i].r.x[1];
		z0	+= WF->Mls.x[0]->Atoms.x[i].r.x[2];
		}
		x0	/= WF->Mls.x[0]->Atoms.N;
		y0	/= WF->Mls.x[0]->Atoms.N;
		z0	/= WF->Mls.x[0]->Atoms.N;

		rc.x[0]	= x0;	rc.x[1]	= y0;	rc.x[2]	= z0;*/

/*

		if (theSph!=0) 
		{
			glDeleteLists(theSph, 1);
		}

		theSph=glGenLists(1);
		glNewList(theSph,GL_COMPILE);
		gluQuadricDrawStyle(qobj, GLU_FILL); 
		gluSphere(qobj,1.0,30,21);
		glEndList();

		GLdouble base,top,height;
		GLint slices,stacks;

		height	= base	= top	= 1.0;
		slices	= 20;
		stacks	= 2;

		if (theCyl!=0) 
		{
			glDeleteLists(theCyl, 2);
		}
		theCyl=glGenLists(2);
		glNewList(theCyl,GL_COMPILE);
		gluQuadricDrawStyle(qobj1, GLU_FILL); 	
		gluCylinder(qobj1,  base,  top,  height,  slices, stacks); 
		glEndList();

		if (the2Cyl!=0) 
		{
			glDeleteLists(the2Cyl, 3);
		}
		the2Cyl=glGenLists(3);
		glNewList(the2Cyl,GL_COMPILE);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslated(-1,0,0);
		gluQuadricDrawStyle(qobj2, GLU_FILL); 	
		gluCylinder(qobj2,  base,  top,  height,  slices, stacks); 
		glTranslated(2.0,0,0);
		gluQuadricDrawStyle(qobj3, GLU_FILL); 	
		gluCylinder(qobj3,  base,  top,  height,  slices, stacks); 
		glPopMatrix();
		glEndList();

		if (the3Cyl!=0) 
		{
			glDeleteLists(the3Cyl, 4);
		}
		the3Cyl=glGenLists(4);
		glNewList(the3Cyl,GL_COMPILE);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslated(0,1,0);
		gluQuadricDrawStyle(qobj1, GLU_FILL); 	
		gluCylinder(qobj1,  base,  top,  height,  slices, stacks); 
		glTranslated(-0.866,-1.5,0);
		gluQuadricDrawStyle(qobj2, GLU_FILL); 	
		gluCylinder(qobj2,  base,  top,  height,  slices, stacks); 
		glTranslated(1.732,0,0);
		gluQuadricDrawStyle(qobj3, GLU_FILL); 	
		gluCylinder(qobj3,  base,  top,  height,  slices, stacks); 
		glPopMatrix();
		glEndList();


		if (theMol!=0) 
		{
			glDeleteLists(theMol, 5);
		}
		theMol=glGenLists(5);
		glNewList(theMol,GL_COMPILE);


		xyz.setmem(WF->Mls.x[0]->Atoms.N);
		radius.setmem(WF->Mls.x[0]->Atoms.N);

		int jk = 0;

//		param[0]	= 0;param[1]	= 0;param[2]	= 0;param[3]	= 0.0;
//		glMaterialfv(GL_FRONT, GL_AMBIENT,param);

		id_at_sB.N	= 0;

		for (int im=0;im<WF->Mls.N;im++)
		{
			for(int i=0;i<WF->Mls.x[im]->Atoms.N;i++)
			{
				x	= WF->Mls.x[im]->Atoms.x[i].r.x[0]-x0;
				y	= WF->Mls.x[im]->Atoms.x[i].r.x[1]-y0;
				z	= WF->Mls.x[im]->Atoms.x[i].r.x[2]-z0;

				ia	= WF->Mls.x[im]->Atoms.x[i].id_Tpz;

				id_at_sB.add(ia);

				r	= double(WF->TableZR.Lines.x[ia].color.x[0])/256;
				g	= double(WF->TableZR.Lines.x[ia].color.x[1])/256;
				b	= double(WF->TableZR.Lines.x[ia].color.x[2])/256;

				rd	= WF->TableZR.Lines.x[ia].vdwrad/500;

				if(s_id.N!=0)
				{
					if (s_id.fnd(jk)!=-1) 
					{
						r	= 1;
						g	= 0;
						b	= 1;
					}
				}

				jk++;
				//	glLoadIdentity();
				glTranslated(x,y,z);
				glScaled(rd,rd,rd);
				//glColor3d(r,g,b);
				//glPushName(i);

				param[0]	= 0.3*rd;param[1]	= 0.3*rd;param[2]	= 0.3*rd;param[3]	= 1.0;
				glLightfv (GL_LIGHT0, GL_AMBIENT, param);

				param[0]	= rd;param[1]	= rd;param[2]	= rd;param[3]	= 1.0;
				glLightfv (GL_LIGHT0, GL_DIFFUSE, param);

				param[0]	= r;param[1]	= g;param[2]	= b;param[3]	= 1.0;
				glMaterialfv(GL_FRONT, GL_DIFFUSE,param);
				glMaterialfv(GL_FRONT, GL_AMBIENT,param);
				//gluQuadricDrawStyle(qobj, GLU_FILL); 
				//gluSphere(qobj,rd,30,21);

				glCallList(theSph);
				glScaled(1/rd,1/rd,1/rd);
				glTranslated(-x,-y,-z);
				//gluQuadricDrawStyle(qobj, GLU_FILL); 
				//gluSphere(qobj,rd,10,7);

				pnt.x[0]	= x;
				pnt.x[1]	= y;
				pnt.x[2]	= z;

				xyz.add(pnt);
				radius.add(rd);
				//xyz.N++;
				/**/
/*
			}/**/
/*		}

		if(id_ml!=-1)
		{
				x	= WF->Mls.x[id_ml]->Atoms.x[id_at].r.x[0]-x0;
				y	= WF->Mls.x[id_ml]->Atoms.x[id_at].r.x[1]-y0;
				z	= WF->Mls.x[id_ml]->Atoms.x[id_at].r.x[2]-z0;

				ia	= WF->Mls.x[id_ml]->Atoms.x[id_at].id_Tpz;

				r	= double(WF->TableZR.Lines.x[ia].color.x[0])/256;
				g	= double(WF->TableZR.Lines.x[ia].color.x[1])/256;
				b	= double(WF->TableZR.Lines.x[ia].color.x[2])/256;

				rd	= WF->TableZR.Lines.x[ia].vdwrad/490;

				r	= 0.9;
				g	= 0.2;
				b	= 0.9;
				
				//	glLoadIdentity();
				glTranslated(x,y,z);
				glScaled(rd,rd,rd);
				//glColor3d(r,g,b);
				//glPushName(i);

				param[0]	= 0.3*rd;param[1]	= 0.3*rd;param[2]	= 0.3*rd;param[3]	= 1.0;
				glLightfv (GL_LIGHT0, GL_AMBIENT, param);

				param[0]	= rd;param[1]	= rd;param[2]	= rd;param[3]	= 1.0;
				glLightfv (GL_LIGHT0, GL_DIFFUSE, param);

				param[0]	= r;param[1]	= g;param[2]	= b;param[3]	= 1.0;
				glMaterialfv(GL_FRONT, GL_DIFFUSE,param);
				glMaterialfv(GL_FRONT, GL_AMBIENT,param);
				glCallList(theSph);
				glScaled(1/rd,1/rd,1/rd);
				glTranslated(-x,-y,-z);
		}

		double dx,dy,dz,fi,th,lb;//,x0,y0,z0,rd;
		//const double pi=3.1415926535897932384626433832795;

		for (int im=0;im<WF->Mls.N;im++)
		{
			for(int i=0;i<WF->Mls.x[im]->Bonds.N;i++)
			{
				ia	= WF->Mls.x[im]->Bonds.x[i].id_Atoms.x[0];
				x	= WF->Mls.x[im]->Atoms.x[ia].r.x[0]-x0;
				y	= WF->Mls.x[im]->Atoms.x[ia].r.x[1]-y0;
				z	= WF->Mls.x[im]->Atoms.x[ia].r.x[2]-z0;

				ia	= WF->Mls.x[im]->Atoms.x[ia].id_Tpz;

				r	= double(WF->TableZR.Lines.x[ia].color.x[0])/256;
				g	= double(WF->TableZR.Lines.x[ia].color.x[1])/256;
				b	= double(WF->TableZR.Lines.x[ia].color.x[2])/256;

				ia	= WF->Mls.x[im]->Bonds.x[i].id_Atoms.x[1];
				dx	= (WF->Mls.x[im]->Atoms.x[ia].r.x[0]-x0)-x;
				dy	= (WF->Mls.x[im]->Atoms.x[ia].r.x[1]-y0)-y;
				dz	= (WF->Mls.x[im]->Atoms.x[ia].r.x[2]-z0)-z;


				ia	= WF->Mls.x[im]->Atoms.x[ia].id_Tpz;

				r1	= double(WF->TableZR.Lines.x[ia].color.x[0])/256;
				g1	= double(WF->TableZR.Lines.x[ia].color.x[1])/256;
				b1	= double(WF->TableZR.Lines.x[ia].color.x[2])/256;

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
				//fi	= acos(dx/sqrt(dx*dx+dy*dy));
				//fi	= (dy>0) ? fi : -fi;

				glMatrixMode(GL_MODELVIEW);
				glPushMatrix();

				glTranslated ( x, y, z); 
				glRotated ( 180*fi/pi, 0, 0, 1);
				glRotated ( 180*th/pi, 0, 1, 0);


				glScaled (0.07, 0.07, 0.5*lb); 
				//glColor3d(r,g,b);

				param[0]	= 0.3*0.07;param[1]	= 0.3*0.07;param[2]	= 0.3*0.07;param[3]	= 1.0;
				glLightfv (GL_LIGHT0, GL_AMBIENT, param);

				param[0]	= 0.07;param[1]	= 0.07;param[2]	= 0.07;param[3]	= 1.0;
				glLightfv (GL_LIGHT0, GL_DIFFUSE, param);

				param[0]	= r;param[1]	= g;param[2]	= b;param[3]	= 1.0;
				glMaterialfv(GL_FRONT, GL_DIFFUSE,param);
				glMaterialfv(GL_FRONT, GL_AMBIENT,param);
				if(WF->Mls.x[im]->Bonds.x[i].oder==1)
				{
					glCallList(theCyl);			
				}
				else
				{
					if(WF->Mls.x[im]->Bonds.x[i].oder==2)
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
				param[0]	= r1;param[1]	= g1;param[2]	= b1;param[3]	= 1.0;
				glMaterialfv(GL_FRONT, GL_DIFFUSE,param);
				glMaterialfv(GL_FRONT, GL_AMBIENT,param);
				if(WF->Mls.x[im]->Bonds.x[i].oder==1)
				{
					glCallList(theCyl);			
				}
				else
				{
					if(WF->Mls.x[im]->Bonds.x[i].oder==2)
					{
						glCallList(the2Cyl);
					}
					else 
					{
						glCallList(the3Cyl);
					}
				}/**/
/*
				glPopMatrix();


			}/**/
/*		}
		glEndList();

	/*	glDeleteLists(theSph,1);
		glDeleteLists(theCyl,2);
		glDeleteLists(the2Cyl,3);
		glDeleteLists(the3Cyl,4);*/
/*	}else
	{
		xyz.N		= 0;
		radius.N	= 0;
		if (theMol!=0){glDeleteLists(theMol, 5);theMol	= 0;}
		if (theSph!=0){glDeleteLists(theSph, 1);theSph	= 0;}
		if (theCyl!=0){glDeleteLists(theCyl, 2);theCyl	= 0;}
		if (the2Cyl!=0){glDeleteLists(the2Cyl, 3);the2Cyl	= 0;}
		if (the3Cyl!=0){glDeleteLists(the3Cyl, 4);the3Cyl	= 0;}
	}

	genAtCh();
}


void OpenGLWidget::genWrScene()	// сгенерировать сцену с молекулой
{
	if(WF->Mls.N>0)
	{
		double x,y,z,x1,y1,z1,x0,y0,z0,rd;
		int it,ia;//,theSph,theWires;//,theCyl,the2Cyl,the3Cyl;
		double r,g,b;//,r1,g1,b1;

		vec3db pnt;

		int jk = 0;

		//WF	= &wFr;
		scenetype	= 0;
		GLfloat param[4];
		/*glDisable(GL_LIGHT0);
		//GLfloat param[4];

		//	int i,j,k;
		//   double s,t,x,y,z,twopi;

		/*G

		GLfloat light_ambient[] = {1, 1, 1, 1};

		glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);

		GLfloat light_diffuse[] = {0.0, 0.0, 0.0, 1};
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
		//glLightfv(GL_LIGHT0, GL_POSITION, light_position);

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);*/

/*		x0	= y0	= z0	= 0.0;
		/*for(int i=0;i<WF->Mls.x[0]->Atoms.N;i++)
		{
		x0	+= WF->Mls.x[0]->Atoms.x[i].r.x[0];
		y0	+= WF->Mls.x[0]->Atoms.x[i].r.x[1];
		z0	+= WF->Mls.x[0]->Atoms.x[i].r.x[2];
		}
		x0	/= WF->Mls.x[0]->Atoms.N;
		y0	/= WF->Mls.x[0]->Atoms.N;
		z0	/= WF->Mls.x[0]->Atoms.N;

		rc.x[0]	= x0;	rc.x[1]	= y0;	rc.x[2]	= z0;*/

/*		if (theSph!=0) 
		{
			glDeleteLists(theSph, 1);
		}
		theSph=glGenLists(1);
		glNewList(theSph,GL_COMPILE);
		gluQuadricDrawStyle(qobj, GLU_FILL); 
		gluSphere(qobj,1,10,15);
		glEndList();

		if (theCyl!=0) 
		{
			glDeleteLists(theCyl, 2);
		}
		theCyl=glGenLists(2);

		glNewList(theCyl,GL_COMPILE);
		//glColor3d(0.7,0.7,0.7);
		//param[0]	= 0.7;param[1]	= 0.7;param[2]	= 0.7;param[3]	= 0;
		//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,param);

		glBegin(GL_LINES);

		for (int im=0;im<WF->Mls.N;im++)
		{
			for(int i=0;i<WF->Mls.x[im]->Bonds.N;i++)
			{
				ia	= WF->Mls.x[im]->Bonds.x[i].id_Atoms.x[0];
				x	= WF->Mls.x[im]->Atoms.x[ia].r.x[0]-x0;
				y	= WF->Mls.x[im]->Atoms.x[ia].r.x[1]-y0;
				z	= WF->Mls.x[im]->Atoms.x[ia].r.x[2]-z0;

				it	= WF->Mls.x[im]->Atoms.x[ia].id_Tpz;
				r	= double(WF->TableZR.Lines.x[it].color.x[0])/256;
				g	= double(WF->TableZR.Lines.x[it].color.x[1])/256;
				b	= double(WF->TableZR.Lines.x[it].color.x[2])/256;

				param[0]	= r;param[1]	= g;param[2]	= b;param[3]	= 0;
				glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,param);
				glVertex3f(x,y,z);
				ia	= WF->Mls.x[im]->Bonds.x[i].id_Atoms.x[1];
				x1	= WF->Mls.x[im]->Atoms.x[ia].r.x[0]-x0;
				y1	= WF->Mls.x[im]->Atoms.x[ia].r.x[1]-y0;
				z1	= WF->Mls.x[im]->Atoms.x[ia].r.x[2]-z0;
				glVertex3f((x+x1)/2,(y+y1)/2,(z+z1)/2);


				if(WF->Mls.x[im]->Bonds.x[i].oder>1)
				{
					for(int j=1;j<WF->Mls.x[im]->Bonds.x[i].oder;j++)
					{
						glVertex3f(x+0.05*j,y,z);
						glVertex3f(0.5*(x+x1)+0.05*j,(y+y1)/2,(z+z1)/2);
					}
				}

				it	= WF->Mls.x[im]->Atoms.x[ia].id_Tpz;
				r	= double(WF->TableZR.Lines.x[it].color.x[0])/256;
				g	= double(WF->TableZR.Lines.x[it].color.x[1])/256;
				b	= double(WF->TableZR.Lines.x[it].color.x[2])/256;

				param[0]	= r;param[1]	= g;param[2]	= b;param[3]	= 0;
				glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,param);

				glVertex3f((x+x1)/2,(y+y1)/2,(z+z1)/2);
				glVertex3f(x1,y1,z1);
				if(WF->Mls.x[im]->Bonds.x[i].oder>1)
				{
					for(int j=1;j<WF->Mls.x[im]->Bonds.x[i].oder;j++)
					{
						glVertex3f((x+x1)/2+0.05,(y+y1)/2,(z+z1)/2);
						glVertex3f(x1+0.05,y1,z1);
					}
				}
			}/**/
/*		}
		glEnd();
		glEndList();/**/

/*		if (theMol!=0) 
		{
			glDeleteLists(theMol, 5);
		}
		theMol=glGenLists(5);
		glNewList(theMol,GL_COMPILE);
		//glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);


		glDisable(GL_LIGHT0);

		GLfloat light_ambient[] = {1, 1, 1, 1};

		glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);

		GLfloat light_diffuse[] = {0.0, 0.0, 0.0, 1};
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
		//glLightfv(GL_LIGHT0, GL_POSITION, light_position);

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);

		/*xyz.setmem(WF->Mls.x[0]->Atoms.N);
		radius.setmem(WF->Mls.x[0]->Atoms.N);
		for (int im=0;im<WF->Mls.N;im++)
		{
			for(int i=0;i<WF->Mls.x[im]->Atoms.N;i++)
			{
				x	= WF->Mls.x[im]->Atoms.x[i].r.x[0]-x0;
				y	= WF->Mls.x[im]->Atoms.x[i].r.x[1]-y0;
				z	= WF->Mls.x[im]->Atoms.x[i].r.x[2]-z0;

				ia	= WF->Mls.x[im]->Atoms.x[i].id_Tpz;

				r	= double(WF->TableZR.Lines.x[ia].color.x[0])/256;
				g	= double(WF->TableZR.Lines.x[ia].color.x[1])/256;
				b	= double(WF->TableZR.Lines.x[ia].color.x[2])/256;

				rd	= WF->TableZR.Lines.x[ia].vdwrad/2000;

				if(s_id.N!=0)
				{
					if (s_id.fnd(jk)!=-1) 
					{
						r	= 1;
						g	= 0;
						b	= 1;
					}
				}

				jk++;

				//	glLoadIdentity();
				glTranslated(x,y,z);
				glScaled(rd,rd,rd);
				glColor3d(r,g,b);
				param[0]	= r;param[1]	= g;param[2]	= b;param[3]	= 0;
				glMaterialfv(GL_FRONT, GL_AMBIENT,param);
				glCallList(theSph);
				glScaled(1/rd,1/rd,1/rd);
				glTranslated(-x,-y,-z);
				//gluQuadricDrawStyle(qobj, GLU_FILL); 
				//gluSphere(qobj,rd,10,7);

				pnt.x[0]	= x;
				pnt.x[1]	= y;
				pnt.x[2]	= z;

				xyz.add(pnt);
				radius.add(rd);

			}
		}*/
		//torus(8,25);

/*		glCallList(theCyl);

		glEndList();

	}else
	{
		if (theMol!=0){glDeleteLists(theMol, 5);}
		if (theSph!=0){glDeleteLists(theSph, 1);}
		if (theCyl!=0){glDeleteLists(theCyl, 2);}
		if (the2Cyl!=0){glDeleteLists(the2Cyl, 3);}
		if (the3Cyl!=0){glDeleteLists(the3Cyl, 4);}
	}

		genAtCh();
}
*/

void OpenGLWidget::setCamera(vec3db &r0, vec3db &r1) // установить камеру в начальное положение.
{
	vec3db z0,y0,x0;

	focPos[0] = r0.x[0];focPos[1] = r0.x[1];focPos[2] = r0.x[2];
	VCMPos[0] = r0.x[0];VCMPos[1] = r0.x[1];VCMPos[2] = r0.x[2];
	camPos[0] = r1.x[0];camPos[1] = r1.x[1];camPos[2] = r1.x[2];

	z0	= r0-r1;
	z0.nrml();
	camOZ[0]	= z0.x[0];camOZ[1]	= z0.x[1];camOZ[2]	= z0.x[2];
	y0	=  0.0;
	y0.x[1]	= 1.0;
	x0.crss(y0,z0);
	y0.crss(z0,x0);
	camOY[0]	= y0.x[0];camOY[1]	= y0.x[1];camOY[2]	= y0.x[2];
	camOX[0]	= x0.x[0];camOX[1]	= x0.x[1];camOX[2]	= x0.x[2];
}

//void OpenGLWidget::genCrSurf();

void OpenGLWidget::genSurfScene(Surface *surface)	// сгенерировать сцену 
{

	vecT<int> tr_flg;
	int i1;//,i2,i3;
	//double c1,c2,c3;
	GLfloat xc,yc,zc;
	//GLfloat x,y,z;


	GLfloat param[4];
		

	//GLfloat mat_specular[] = { 0.1, 0.1, 0.1, 0.0 };
//	GLfloat mat_shininess[] = { 50.0 };

	
	
	tr_flg.setlen(surface->Surf.Trngl.N);

	//surface->Surf.SrfA2vrml();

	/*glDisable(GL_LIGHT0);

	GLfloat light_diffuse[] = {0.2, 0.2, 0.2, 0};

	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

	GLfloat light_ambient[] = {0.0, 0.0, 0.0, 1};
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_diffuse);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);*/

//	glClearColor (0.0, 0.0, 0.0, 0.0);
	
	//glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
//	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	xc	= yc	= zc	= 0.0;
	/*for(int i=0;i<WF->Mls.x[0]->Atoms.N;i++)
	{
		xc	+= WF->Mls.x[0]->Atoms.x[i].r.x[0];
		yc	+= WF->Mls.x[0]->Atoms.x[i].r.x[1];
		zc	+= WF->Mls.x[0]->Atoms.x[i].r.x[2];
	}
	xc	/= WF->Mls.x[0]->Atoms.N;
	yc	/= WF->Mls.x[0]->Atoms.N;
	zc	/= WF->Mls.x[0]->Atoms.N;*/

	GLfloat *vertices;
	GLfloat *normals;
	GLfloat *colors;
	GLuint	*indices;
	GLuint  *edgeind;

	colors		= new GLfloat [3*surface->Surf.Point.N];
	vertices	= new GLfloat [3*surface->Surf.Point.N];
	normals		= new GLfloat [3*surface->Surf.Point.N];
	indices		= new GLuint  [3*surface->Surf.Trngl.N];
	edgeind		= new GLuint  [2*surface->Surf.Edge.N];
	//edgeflags	= new bool  [surface->Surf.Edge.N];
	
	for(int ii=0;ii<surface->Surf.Edge.N;ii++)
	{
		edgeind[2*ii]=surface->Surf.Edge.x[ii].n_pnt.x[0];
		edgeind[2*ii+1]=surface->Surf.Edge.x[ii].n_pnt.x[1];
	}

	for(int ii=0;ii<surface->Surf.Trngl.N;ii++)
	{
		indices[3*ii]	= surface->Surf.Trngl.x[ii].n_pnt.x[0];
		indices[3*ii+1]	= surface->Surf.Trngl.x[ii].n_pnt.x[1];
		indices[3*ii+2]	= surface->Surf.Trngl.x[ii].n_pnt.x[2];
	}
	

	if ((surface->getviztype()>=0)&&(surface->getviztype()<=4))
	{
		for(int ii=0;ii<surface->Surf.Point.N;ii++)
		{
			colors[3*ii]	= surface->Surf.Point.x[ii].clr.x[0];
			colors[3*ii+1]	= surface->Surf.Point.x[ii].clr.x[1];
			colors[3*ii+2]	= surface->Surf.Point.x[ii].clr.x[2];
		}
	}
	
	for(int ii=0;ii<surface->Surf.Point.N;ii++)
	{
		vertices[3*ii]		= surface->Surf.Point.x[ii].crd.x[0];//-xc;
		vertices[3*ii+1]	= surface->Surf.Point.x[ii].crd.x[1];//-yc;
		vertices[3*ii+2]	= surface->Surf.Point.x[ii].crd.x[2];//-zc;

		normals[3*ii]		= surface->Surf.Point.x[ii].nor.x[0];
		normals[3*ii+1]		= surface->Surf.Point.x[ii].nor.x[1];
		normals[3*ii+2]		= surface->Surf.Point.x[ii].nor.x[2];
	}

	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	//glEnableClientState(GL_EDGE_FLAG_ARRAY);

	glColorPointer(3, GL_FLOAT, 0, colors);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glNormalPointer(GL_FLOAT,0, normals);
	//glEdgeFlagPointer(0 ,edgeflags);

	i1	= 3*surface->Surf.Trngl.N;

    if(theSurf!=0)
	{
		glDeleteLists(theSurf, 1);
	}

	theSurf	= glGenLists(1);
	glNewList(theSurf,GL_COMPILE);

	
	/**/glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	param[0]	= 0.0;param[1]	= 0.0;param[2]	= 0.0;param[3]	= 0;
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,param);

	GLfloat light_diffuse[] = {1, 1, 1, 1};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS,0.0);

	param[0]	= 0.0;param[1]	= 0.0;param[2]	= 0.0;param[3]	= 0;
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,param);

	param[0]	= 0.0;param[1]	= 0.0;param[2]	= 0.0;param[3]	= 0;
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,param);

	//GLfloat light_specular[] = {1, 1, 1, 1};
	//glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);	

	param[0]	= 0;param[1]	= 0;param[2]	= 0;param[3]	= 0;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,param);

	GLfloat light_ambient[] = {0.0, 0.0, 0.0, 0};
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);


	//glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 30);	

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	/**/
	//glShadeModel(GL_FLAT);
	glPolygonMode(GL_BACK, GL_LINE);
	glPolygonMode(GL_FRONT, GL_FILL);
	glDisable(GL_CULL_FACE);
	glHint(GL_FOG_HINT,GL_NICEST);
	//glDisable(GL_POLYGON_SMOOTH);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	//  ? glColorMaterial(GL_FRONT, GL_SPECULAR);
	if (surface->getismoth())
	{
		glDrawElements(GL_TRIANGLES, i1, GL_UNSIGNED_INT, indices);
	}else
	{
		glDrawElements(GL_LINES, i1, GL_UNSIGNED_INT, edgeind);
	}
	glDisable(GL_COLOR_MATERIAL);
	//glShadeModel(GL_SMOOTH);
	glEnable(GL_CULL_FACE);
	//glEnable(GL_POLYGON_SMOOTH);
	glEndList();

	if (surface->getviztype()==2)
	{

		glDisableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);

		for(int ii=0;ii<surface->Surf.Point.N;ii++)
		{
			vertices[3*ii]		= vertices[3*ii]-0.03*normals[3*ii];
			vertices[3*ii+1]	= vertices[3*ii+1]-0.03*normals[3*ii+1];
			vertices[3*ii+2]	= vertices[3*ii+2]-0.03*normals[3*ii+2];

			normals[3*ii]		= -normals[3*ii];
			normals[3*ii+1]		= -normals[3*ii+1];
			normals[3*ii+2]		= -normals[3*ii+2];
		}
		glNormalPointer(GL_FLOAT,0, normals);

		if(theInvSurf!=0)
		{
			glDeleteLists(theInvSurf, 1);
		}
		theInvSurf	= glGenLists(1);
		glNewList(theInvSurf,GL_COMPILE);

		//glEnable(GL_CULL_FACE);
		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
		glFrontFace(GL_CW);
		//glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
		//glDrawElements(GL_TRIANGLES, i1, GL_UNSIGNED_INT, indices);
		glDrawElements(GL_LINES, i1, GL_UNSIGNED_INT, edgeind);
		glFrontFace(GL_CCW);
		glDisable(GL_COLOR_MATERIAL);

		
	//glShadeModel(GL_FLAT);
//glEnable(GL_CULL_FACE);

		glEndList();

	}

	isSurf	= true;

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	//glDisableClientState(GL_EDGE_FLAG_ARRAY);

	delete [] vertices;
	delete [] colors;
	delete [] normals;
	delete [] indices;
	delete [] edgeind;
	//delete [] edgeflags;
}
void OpenGLWidget::get3Dfrom2D() // получить 3D координаты по 2D координатам курсора мыши
{
	// вычисляются координаты точки находящиеся "под" мышью на удалении от экрана равному удалению от экрана до центральной точки вокруг производится вращение
	vec3db r1,r2,r3;
	double dz,tga,tgt,tgb;
	GLint viewport[4];
	
	glGetIntegerv(GL_VIEWPORT,viewport);
	
	// вектор смещения из середины экрана в центральную точку
	r2.x[0]	= focPos[0]-camPos[0];
	r2.x[1]	= focPos[1]-camPos[1];
	r2.x[2]	= focPos[2]-camPos[2];

	dz		= r2.norm();	

	if(!isOrtho)
	{

		//wh		= double(viewport[2])/double(viewport[3]); // отношение сторон видимой части 3D окна
		tgt		= tan(p_alf*pi/360.0);

		tga		= tgt*(1.0-double(2*lastPos.x())/double(viewport[2]))*double(viewport[2])/double(viewport[3]);
		tgb		= tgt*(1.0-double(2*lastPos.y())/double(viewport[3]));

		// координаты в базисе связанном с экраном, но в единицах 3D сцены
		r1.x[0]	= tga*dz;
		r1.x[1]	= tgb*dz;
		r1.x[2]	= dz;

	}else
	{
		r1.x[0]	= (1.0-double(2*lastPos.x())/double(viewport[2]))*mgnf*double(viewport[2])/double(viewport[3]);
		r1.x[1]	= (1.0-double(2*lastPos.y())/double(viewport[3]))*mgnf;
		r1.x[2]	= dz;
	}

	// переход в систему координат сцены
	r3.x[0]	= camOX[0]*r1.x[0]+camOY[0]*r1.x[1]+camOZ[0]*r1.x[2]+camPos[0];
	r3.x[1]	= camOX[1]*r1.x[0]+camOY[1]*r1.x[1]+camOZ[1]*r1.x[2]+camPos[1];
	r3.x[2]	= camOX[2]*r1.x[0]+camOY[2]*r1.x[1]+camOZ[2]*r1.x[2]+camPos[2];

	tv	= r3;	// 3D координаты целевой точки 
}


void OpenGLWidget::get3Dfrom2D(const vec3db &upc) // получить 3D координаты по 2D координатам курсора мыши
{
	// вычисляются координаты точки находящиеся "под" мышью на удалении от экрана равному удалению от экрана до точки upc
	vec3db r1,r2,r3;
	double dz,tga,tgt,tgb;
	GLint viewport[4];
	
	glGetIntegerv(GL_VIEWPORT,viewport);

/*	// координаты в базисе связанном с экраном, но в единицах 3D сцены
	r1.x[0]	= -(double(2*lastPos.x())/double(viewport[2]) - 1.0)*wh;
	r1.x[1]	= 1.0-double(2*lastPos.y())/double(viewport[3]);
	r1.x[2]	= 0.0;
	
	// вектор смещения из середины экрана в центральную точку
	r2.x[0]	= upc.x[0]-camPos[0];
	r2.x[1]	= upc.x[1]-camPos[1];
	r2.x[2]	= upc.x[2]-camPos[2];

	dz		= r2.x[0]*camOZ[0]+r2.x[1]*camOZ[1]+r2.x[2]*camOZ[2];
	r1.x[0]	*= dz/2;
	r1.x[1]	*= dz/2;
	r1.x[2]	+= dz;*/

	// вектор смещения из середины экрана в центральную точку
	r2.x[0]	= upc.x[0]-camPos[0];
	r2.x[1]	= upc.x[1]-camPos[1];
	r2.x[2]	= upc.x[2]-camPos[2];

	dz		= r2.x[0]*camOZ[0]+r2.x[1]*camOZ[1]+r2.x[2]*camOZ[2];	

	if(!isOrtho)
	{

		//wh		= double(viewport[2])/double(viewport[3]); // отношение сторон видимой части 3D окна
		tgt		= tan(p_alf*pi/360.0);

		tga		= tgt*(1.0-double(2*lastPos.x())/double(viewport[2]))*double(viewport[2])/double(viewport[3]);
		tgb		= tgt*(1.0-double(2*lastPos.y())/double(viewport[3]));

		// координаты в базисе связанном с экраном, но в единицах 3D сцены
		r1.x[0]	= tga*dz;
		r1.x[1]	= tgb*dz;
		r1.x[2]	= dz;

	}else
	{
		r1.x[0]	= (1.0-double(2*lastPos.x())/double(viewport[2]))*mgnf*double(viewport[2])/double(viewport[3]);
		r1.x[1]	= (1.0-double(2*lastPos.y())/double(viewport[3]))*mgnf;
		r1.x[2]	= dz;
	}

	// переход в систему координат сцены
	r3.x[0]	= camOX[0]*r1.x[0]+camOY[0]*r1.x[1]+camOZ[0]*r1.x[2]+camPos[0];
	r3.x[1]	= camOX[1]*r1.x[0]+camOY[1]*r1.x[1]+camOZ[1]*r1.x[2]+camPos[1];
	r3.x[2]	= camOX[2]*r1.x[0]+camOY[2]*r1.x[1]+camOZ[2]*r1.x[2]+camPos[2];

	tv	= r3;	// 3D координаты целевой точки 
}


vec3db OpenGLWidget::get3Dfrom2D(int x, int y) // получить 3D координаты по 2D координатам курсора мыши
{
	// вычисляются координаты точки находящиеся "под" мышью на удалении от экрана равному удалению от экрана до центральной точки вокруг производится вращение
	vec3db r1,r2,r3;
	double dz,tga,tgt,tgb;
	GLint viewport[4];
	
	glGetIntegerv(GL_VIEWPORT,viewport);
	
	// вектор смещения из середины экрана в центральную точку
	r2.x[0]	= focPos[0]-camPos[0];
	r2.x[1]	= focPos[1]-camPos[1];
	r2.x[2]	= focPos[2]-camPos[2];

	dz		= r2.norm();	

	if(!isOrtho)
	{

		//wh		= double(viewport[2])/double(viewport[3]); // отношение сторон видимой части 3D окна
		tgt		= tan(p_alf*pi/360.0);

		tga		= tgt*(1.0-double(2*x)/double(viewport[2]))*double(viewport[2])/double(viewport[3]);
		tgb		= tgt*(1.0-double(2*y)/double(viewport[3]));

		// координаты в базисе связанном с экраном, но в единицах 3D сцены
		r1.x[0]	= tga*dz;
		r1.x[1]	= tgb*dz;
		r1.x[2]	= dz;

	}else
	{
		r1.x[0]	= (1.0-double(2*x)/double(viewport[2]))*mgnf*double(viewport[2])/double(viewport[3]);
		r1.x[1]	= (1.0-double(2*y)/double(viewport[3]))*mgnf;
		r1.x[2]	= dz;
	}


	// переход в систему координат сцены
	r3.x[0]	= camOX[0]*r1.x[0]+camOY[0]*r1.x[1]+camOZ[0]*r1.x[2]+camPos[0];
	r3.x[1]	= camOX[1]*r1.x[0]+camOY[1]*r1.x[1]+camOZ[1]*r1.x[2]+camPos[1];
	r3.x[2]	= camOX[2]*r1.x[0]+camOY[2]*r1.x[1]+camOZ[2]*r1.x[2]+camPos[2];

	return r3;	// 3D координаты целевой точки 
}


vec3db OpenGLWidget::get3Dfrom2D(const vec3db &upc, int x, int y) // получить 3D координаты по 2D координатам курсора мыши
{
	// вычисляются координаты точки находящиеся "под" мышью на удалении от экрана равному удалению от экрана до точки upc
	vec3db r1,r2,r3;
	double dz,tga,tgt,tgb;
	GLint viewport[4];
	
	glGetIntegerv(GL_VIEWPORT,viewport);
	
	// вектор смещения из середины экрана в центральную точку
	r2.x[0]	= upc.x[0]-camPos[0];
	r2.x[1]	= upc.x[1]-camPos[1];
	r2.x[2]	= upc.x[2]-camPos[2];

	dz		= r2.x[0]*camOZ[0]+r2.x[1]*camOZ[1]+r2.x[2]*camOZ[2];	

	if(!isOrtho)
	{

		//wh		= double(viewport[2])/double(viewport[3]); // отношение сторон видимой части 3D окна
		tgt		= tan(p_alf*pi/360.0);

		tga		= tgt*(1.0-double(2*x)/double(viewport[2]))*double(viewport[2])/double(viewport[3]);
		tgb		= tgt*(1.0-double(2*y)/double(viewport[3]));

		// координаты в базисе связанном с экраном, но в единицах 3D сцены
		r1.x[0]	= tga*dz;
		r1.x[1]	= tgb*dz;
		r1.x[2]	= dz;

	}else
	{
		r1.x[0]	= (1.0-double(2*x)/double(viewport[2]))*mgnf*double(viewport[2])/double(viewport[3]);
		r1.x[1]	= (1.0-double(2*y)/double(viewport[3]))*mgnf;
		r1.x[2]	= dz;
	}

	// переход в систему координат сцены
	r3.x[0]	= camOX[0]*r1.x[0]+camOY[0]*r1.x[1]+camOZ[0]*r1.x[2]+camPos[0];
	r3.x[1]	= camOX[1]*r1.x[0]+camOY[1]*r1.x[1]+camOZ[1]*r1.x[2]+camPos[1];
	r3.x[2]	= camOX[2]*r1.x[0]+camOY[2]*r1.x[1]+camOZ[2]*r1.x[2]+camPos[2];

	return r3;	// 3D координаты целевой точки 
}

void OpenGLWidget::setrucon() // получить 3D координаты по 2D координатам курсора мыши
{
	// вычисляются координаты точки находящиеся "под" мышью на удалении от экрана равному удалению от экрана до центральной точки вокруг производится вращение
	vec3db r1,r2,r3;
	double dz,tga,tgt,tgb;
	GLint viewport[4];
	
	glGetIntegerv(GL_VIEWPORT,viewport);
	
	// вектор смещения из середины экрана в центральную точку
	r2.x[0]	= focPos[0]-camPos[0];
	r2.x[1]	= focPos[1]-camPos[1];
	r2.x[2]	= focPos[2]-camPos[2];

	dz		= r2.norm();	
	dz		= z_near+0.01;

	if(!isOrtho)
	{

		//wh		= double(viewport[2])/double(viewport[3]); // отношение сторон видимой части 3D окна
		tgt		= tan(p_alf*pi/360.0);

		tga		= tgt*(1.0-double(2*lastPos.x())/double(viewport[2]))*double(viewport[2])/double(viewport[3]);
		tgb		= tgt*(1.0-double(2*lastPos.y())/double(viewport[3]));

		// координаты в базисе связанном с экраном, но в единицах 3D сцены
		r1.x[0]	= tga*dz;
		r1.x[1]	= tgb*dz;
		r1.x[2]	= dz;

	}else
	{
		r1.x[0]	= (1.0-double(2*lastPos.x())/double(viewport[2]))*mgnf*double(viewport[2])/double(viewport[3]);
		r1.x[1]	= (1.0-double(2*lastPos.y())/double(viewport[3]))*mgnf;
		r1.x[2]	= dz;
	}

	// переход в систему координат сцены
	r3.x[0]	= camOX[0]*r1.x[0]+camOY[0]*r1.x[1]+camOZ[0]*r1.x[2]+camPos[0];
	r3.x[1]	= camOX[1]*r1.x[0]+camOY[1]*r1.x[1]+camOZ[1]*r1.x[2]+camPos[1];
	r3.x[2]	= camOX[2]*r1.x[0]+camOY[2]*r1.x[1]+camOZ[2]*r1.x[2]+camPos[2];

	rucon	= r3;	// 3D координаты целевой точки 
}


void OpenGLWidget::setldcon() // получить 3D координаты по 2D координатам курсора мыши
{
	// вычисляются координаты точки находящиеся "под" мышью на удалении от экрана равному удалению от экрана до центральной точки вокруг производится вращение
	vec3db r1,r2,r3;
	double dz,tga,tgt,tgb;
	GLint viewport[4];
	
	glGetIntegerv(GL_VIEWPORT,viewport);

	// вектор смещения из середины экрана в центральную точку
	r2.x[0]	= focPos[0]-camPos[0];
	r2.x[1]	= focPos[1]-camPos[1];
	r2.x[2]	= focPos[2]-camPos[2];

	dz		= r2.norm();
	dz		= z_near+0.01;

	if(!isOrtho)
	{

		//wh		= double(viewport[2])/double(viewport[3]); // отношение сторон видимой части 3D окна
		tgt		= tan(p_alf*pi/360.0);

		tga		= tgt*(1.0-double(2*lastPos.x())/double(viewport[2]))*double(viewport[2])/double(viewport[3]);
		tgb		= tgt*(1.0-double(2*lastPos.y())/double(viewport[3]));

		// координаты в базисе связанном с экраном, но в единицах 3D сцены
		r1.x[0]	= tga*dz;
		r1.x[1]	= tgb*dz;
		r1.x[2]	= dz;

	}else
	{
		r1.x[0]	= (1.0-double(2*lastPos.x())/double(viewport[2]))*mgnf*double(viewport[2])/double(viewport[3]);
		r1.x[1]	= (1.0-double(2*lastPos.y())/double(viewport[3]))*mgnf;
		r1.x[2]	= dz;
	}

	// переход в систему координат сцены
	r3.x[0]	= camOX[0]*r1.x[0]+camOY[0]*r1.x[1]+camOZ[0]*r1.x[2]+camPos[0];
	r3.x[1]	= camOX[1]*r1.x[0]+camOY[1]*r1.x[1]+camOZ[1]*r1.x[2]+camPos[1];
	r3.x[2]	= camOX[2]*r1.x[0]+camOY[2]*r1.x[1]+camOZ[2]*r1.x[2]+camPos[2];

	ldcon	= r3;	// 3D координаты целевой точки 
}

#endif


	//glBegin(GL_TRIANGLES);
	//glDrawElements(GL_TRIANGLES, i1, GL_UNSIGNED_INT, indices);
	/*for(int ii=0;ii<surface->Surf.Trngl.N;ii++)
	{
		i1	= surface->Surf.Trngl.x[ii].n_pnt.x[0];
		i2	= surface->Surf.Trngl.x[ii].n_pnt.x[1];
		i3	= surface->Surf.Trngl.x[ii].n_pnt.x[2];

		glArrayElement(i1);
		glArrayElement(i2);
		glArrayElement(i3);

		/*glColor3fv(&colors[i1*3]);
		glVertex3fv(&vertices[i1*3]);
		glNormal3fv(&normals[i1*3]);

		glColor3fv(&colors[i2*3]);
		glVertex3fv(&vertices[i2*3]);
		glNormal3fv(&normals[i2*3]);

		glColor3fv(&colors[i3*3]);
		glVertex3fv(&vertices[i3*3]);
		glNormal3fv(&normals[i3*3]);
	}*/
	//glEnd();

	/*glBegin(GL_TRIANGLES);
	for(int ii=0;ii<surface->Surf.Trngl.N;ii++)
	{
		i1	= surface->Surf.Trngl.x[ii].n_pnt.x[0];
		i2	= surface->Surf.Trngl.x[ii].n_pnt.x[1];
		i3	= surface->Surf.Trngl.x[ii].n_pnt.x[2];

		c1	= (GLfloat)(surface->Surf.Point.x[i1].clr.x[0]);
		c2	= (GLfloat)(surface->Surf.Point.x[i1].clr.x[1]);
		c3	= (GLfloat)(surface->Surf.Point.x[i1].clr.x[2]);
		glColor3f(c1,c2,c3);
		x	= (GLfloat)(surface->Surf.Point.x[i1].nor.x[0]);
		y	= (GLfloat)(surface->Surf.Point.x[i1].nor.x[1]);
		z	= (GLfloat)(surface->Surf.Point.x[i1].nor.x[2]);
		glNormal3f(x,y,z);
		x	= (GLfloat)(surface->Surf.Point.x[i1].crd.x[0])-xc;
		y	= (GLfloat)(surface->Surf.Point.x[i1].crd.x[1])-yc;
		z	= (GLfloat)(surface->Surf.Point.x[i1].crd.x[2])-zc;
		glVertex3f(x,y,z);

		c1	= (GLfloat)(surface->Surf.Point.x[i2].clr.x[0]);
		c2	= (GLfloat)(surface->Surf.Point.x[i2].clr.x[1]);
		c3	= (GLfloat)(surface->Surf.Point.x[i2].clr.x[2]);
		glColor3f(c1,c2,c3);
		x	= (GLfloat)(surface->Surf.Point.x[i2].nor.x[0]);
		y	= (GLfloat)(surface->Surf.Point.x[i2].nor.x[1]);
		z	= (GLfloat)(surface->Surf.Point.x[i2].nor.x[2]);
		glNormal3f(x,y,z);
		x	= (GLfloat)(surface->Surf.Point.x[i2].crd.x[0])-xc;
		y	= (GLfloat)(surface->Surf.Point.x[i2].crd.x[1])-yc;
		z	= (GLfloat)(surface->Surf.Point.x[i2].crd.x[2])-zc;
		glVertex3f(x,y,z);

		c1	= (GLfloat)(surface->Surf.Point.x[i3].clr.x[0]);
		c2	= (GLfloat)(surface->Surf.Point.x[i3].clr.x[1]);
		c3	= (GLfloat)(surface->Surf.Point.x[i3].clr.x[2]);
		glColor3f(c1,c2,c3);
		x	= (GLfloat)(surface->Surf.Point.x[i3].nor.x[0]);
		y	= (GLfloat)(surface->Surf.Point.x[i3].nor.x[1]);
		z	= (GLfloat)(surface->Surf.Point.x[i3].nor.x[2]);
		glNormal3f(x,y,z);
		x	= (GLfloat)(surface->Surf.Point.x[i3].crd.x[0])-xc;
		y	= (GLfloat)(surface->Surf.Point.x[i3].crd.x[1])-yc;
		z	= (GLfloat)(surface->Surf.Point.x[i3].crd.x[2])-zc;
		glVertex3f(x,y,z);
	}
	glEnd();/**/




/*void OpenGLWidget::genScene(WorkFrame &wFr)	// сгенерировать сцену с молекулой
{
	double x,y,z,x0,y0,z0,rd;
	int ia,theSph,theCyl,the2Cyl,the3Cyl;
	double r,g,b,r1,g1,b1;

	GLfloat param[4];

	vec3db pnt;

	WF	= &wFr;


	scenetype	= 1;


	x0	= y0	= z0	= 0.0;
	for(int i=0;i<wFr.Mls.x[0]->Atoms.N;i++)
	{
		x0	+= wFr.Mls.x[0]->Atoms.x[i].r.x[0];
		y0	+= wFr.Mls.x[0]->Atoms.x[i].r.x[1];
		z0	+= wFr.Mls.x[0]->Atoms.x[i].r.x[2];
	}
	x0	/= wFr.Mls.x[0]->Atoms.N;
	y0	/= wFr.Mls.x[0]->Atoms.N;
	z0	/= wFr.Mls.x[0]->Atoms.N;

	rc.x[0]	= x0;	rc.x[1]	= y0;	rc.x[2]	= z0;

	theSph=glGenLists(1);
	glNewList(theSph,GL_COMPILE);
	gluQuadricDrawStyle(qobj, GLU_FILL); 
	gluSphere(qobj,1,30,21);
	glEndList();

	GLdouble base,top,height;
	GLint slices,stacks;

	height	= base	= top	= 1.0;
	slices	= 20;
	stacks	= 2;

	theCyl=glGenLists(2);
	glNewList(theCyl,GL_COMPILE);
	gluQuadricDrawStyle(qobj1, GLU_FILL); 	
	gluCylinder(qobj1,  base,  top,  height,  slices, stacks); 
	glEndList();

	the2Cyl=glGenLists(3);
	glNewList(the2Cyl,GL_COMPILE);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslated(-1,0,0);
	gluQuadricDrawStyle(qobj2, GLU_FILL); 	
	gluCylinder(qobj2,  base,  top,  height,  slices, stacks); 
	glTranslated(2.0,0,0);
	gluQuadricDrawStyle(qobj3, GLU_FILL); 	
	gluCylinder(qobj3,  base,  top,  height,  slices, stacks); 
	glPopMatrix();
	glEndList();

	the3Cyl=glGenLists(4);
	glNewList(the3Cyl,GL_COMPILE);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslated(0,1,0);
	gluQuadricDrawStyle(qobj1, GLU_FILL); 	
	gluCylinder(qobj1,  base,  top,  height,  slices, stacks); 
	glTranslated(-0.866,-1.5,0);
	gluQuadricDrawStyle(qobj2, GLU_FILL); 	
	gluCylinder(qobj2,  base,  top,  height,  slices, stacks); 
	glTranslated(1.732,0,0);
	gluQuadricDrawStyle(qobj3, GLU_FILL); 	
	gluCylinder(qobj3,  base,  top,  height,  slices, stacks); 
	glPopMatrix();
	glEndList();


	if (theMol!=0) 
		{
			glDeleteLists(theMol, 5);
		}

	theMol=glGenLists(5);
	glNewList(theMol,GL_COMPILE);

	xyz.setmem(wFr.Mls.x[0]->Atoms.N);
	radius.setmem(wFr.Mls.x[0]->Atoms.N);
	for (int im=0;im<wFr.Mls.N;im++)
	{
		for(int i=0;i<wFr.Mls.x[im]->Atoms.N;i++)
		{
			x	= wFr.Mls.x[im]->Atoms.x[i].r.x[0]-x0;
			y	= wFr.Mls.x[im]->Atoms.x[i].r.x[1]-y0;
			z	= wFr.Mls.x[im]->Atoms.x[i].r.x[2]-z0;

			ia	= wFr.Mls.x[im]->Atoms.x[i].id_Tpz;

			r	= double(wFr.TableZR.Lines.x[ia].color.x[0])/256;
			g	= double(wFr.TableZR.Lines.x[ia].color.x[1])/256;
			b	= double(wFr.TableZR.Lines.x[ia].color.x[2])/256;

			rd	= wFr.TableZR.Lines.x[ia].vdwrad/500;

			//	glLoadIdentity();
			glTranslated(x,y,z);
			glScaled(rd,rd,rd);
			//glColor3d(r,g,b);
			//glPushName(i);
			param[0]	= r;param[1]	= g;param[2]	= b;param[3]	= 0;
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE,param);
			glCallList(theSph);
			glScaled(1/rd,1/rd,1/rd);
			glTranslated(-x,-y,-z);
			//gluQuadricDrawStyle(qobj, GLU_FILL); 
			//gluSphere(qobj,rd,10,7);


			pnt.x[0]	= x;
			pnt.x[1]	= y;
			pnt.x[2]	= z;

			xyz.add(pnt);
			radius.add(rd);

		}
	}

	double dx,dy,dz,fi,th,lb;//,x0,y0,z0,rd;
	const double pi=3.1415926535897932384626433832795;

	for (int im=0;im<wFr.Mls.N;im++)
	{
	for(int i=0;i<wFr.Mls.x[im]->Bonds.N;i++)
	{
		ia	= wFr.Mls.x[im]->Bonds.x[i].id_Atoms.x[0];
		x	= wFr.Mls.x[im]->Atoms.x[ia].r.x[0]-x0;
		y	= wFr.Mls.x[im]->Atoms.x[ia].r.x[1]-y0;
		z	= wFr.Mls.x[im]->Atoms.x[ia].r.x[2]-z0;

		ia	= wFr.Mls.x[im]->Atoms.x[ia].id_Tpz;

		r	= double(wFr.TableZR.Lines.x[ia].color.x[0])/256;
		g	= double(wFr.TableZR.Lines.x[ia].color.x[1])/256;
		b	= double(wFr.TableZR.Lines.x[ia].color.x[2])/256;
	
		ia	= wFr.Mls.x[im]->Bonds.x[i].id_Atoms.x[1];
		dx	= (wFr.Mls.x[im]->Atoms.x[ia].r.x[0]-x0)-x;
		dy	= (wFr.Mls.x[im]->Atoms.x[ia].r.x[1]-y0)-y;
		dz	= (wFr.Mls.x[im]->Atoms.x[ia].r.x[2]-z0)-z;


		ia	= wFr.Mls.x[im]->Atoms.x[ia].id_Tpz;

		r1	= double(wFr.TableZR.Lines.x[ia].color.x[0])/256;
		g1	= double(wFr.TableZR.Lines.x[ia].color.x[1])/256;
		b1	= double(wFr.TableZR.Lines.x[ia].color.x[2])/256;

		lb	= sqrt(dx*dx+dy*dy+dz*dz);
		th	= acos(dz/lb);
		fi	= acos(dx/sqrt(dx*dx+dy*dy));
		fi	= (dy>0) ? fi : -fi;

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();

		glTranslated ( x, y, z); 
		glRotated ( 180*fi/pi, 0, 0, 1);
		glRotated ( 180*th/pi, 0, 1, 0);
		

		glScaled (0.07, 0.07, 0.5*lb); 
		//glColor3d(r,g,b);
		param[0]	= r/3;param[1]	= g/3;param[2]	= b/3;param[3]	= 0;
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE,param);
		if(wFr.Mls.x[im]->Bonds.x[i].oder==1)
		{
			glCallList(theCyl);			
		}
		else
		{
			if(wFr.Mls.x[im]->Bonds.x[i].oder==2)
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
		if(wFr.Mls.x[im]->Bonds.x[i].oder==1)
		{
			glCallList(theCyl);			
		}
		else
		{
			if(wFr.Mls.x[im]->Bonds.x[i].oder==2)
			{
				glCallList(the2Cyl);
			}
			else 
			{
				glCallList(the3Cyl);
			}
		}

		glPopMatrix();
	}
	}
	glEndList();

		glDeleteLists(theSph,1);
		glDeleteLists(theCyl,2);
		glDeleteLists(the2Cyl,3);
		glDeleteLists(the3Cyl,4);
}

void OpenGLWidget::genWrScene(WorkFrame &wFr)	// сгенерировать сцену с молекулой
{
	double x,y,z,x0,y0,z0,rd;
	int ia,theSph,theWires;//,theCyl,the2Cyl,the3Cyl;
	double r,g,b;//,r1,g1,b1;

	vec3db pnt;

	WF	= &wFr;
	scenetype	= 0;

	GLfloat param[4];



	x0	= y0	= z0	= 0.0;
	for(int i=0;i<wFr.Mls.x[0]->Atoms.N;i++)
	{
		x0	+= wFr.Mls.x[0]->Atoms.x[i].r.x[0];
		y0	+= wFr.Mls.x[0]->Atoms.x[i].r.x[1];
		z0	+= wFr.Mls.x[0]->Atoms.x[i].r.x[2];
	}
	x0	/= wFr.Mls.x[0]->Atoms.N;
	y0	/= wFr.Mls.x[0]->Atoms.N;
	z0	/= wFr.Mls.x[0]->Atoms.N;

	rc.x[0]	= x0;	rc.x[1]	= y0;	rc.x[2]	= z0;

	theSph=glGenLists(1);
	glNewList(theSph,GL_COMPILE);
	gluQuadricDrawStyle(qobj, GLU_FILL); 
	gluSphere(qobj,1,10,15);
	glEndList();

	theWires=glGenLists(2);

	glNewList(theWires,GL_COMPILE);
	//glColor3d(0.7,0.7,0.7);
	//param[0]	= 0.7;param[1]	= 0.7;param[2]	= 0.7;param[3]	= 0;
	//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,param);

	glBegin(GL_LINES);

	for (int im=0;im<wFr.Mls.N;im++)
	{
	for(int i=0;i<wFr.Mls.x[im]->Bonds.N;i++)
	{
		ia	= wFr.Mls.x[im]->Bonds.x[i].id_Atoms.x[0];
		x	= wFr.Mls.x[im]->Atoms.x[ia].r.x[0]-x0;
		y	= wFr.Mls.x[im]->Atoms.x[ia].r.x[1]-y0;
		z	= wFr.Mls.x[im]->Atoms.x[ia].r.x[2]-z0;
		glVertex3f(x,y,z);
		ia	= wFr.Mls.x[im]->Bonds.x[i].id_Atoms.x[1];
		x	= wFr.Mls.x[im]->Atoms.x[ia].r.x[0]-x0;
		y	= wFr.Mls.x[im]->Atoms.x[ia].r.x[1]-y0;
		z	= wFr.Mls.x[im]->Atoms.x[ia].r.x[2]-z0;
		glVertex3f(x,y,z);
		if(wFr.Mls.x[im]->Bonds.x[i].oder>1)
		{
			for(int j=1;j<wFr.Mls.x[im]->Bonds.x[i].oder;j++)
			{
				ia	= wFr.Mls.x[im]->Bonds.x[i].id_Atoms.x[0];
				x	= wFr.Mls.x[im]->Atoms.x[ia].r.x[0]-x0+0.05*j;
				y	= wFr.Mls.x[im]->Atoms.x[ia].r.x[1]-y0;
				z	= wFr.Mls.x[im]->Atoms.x[ia].r.x[2]-z0;
				glVertex3f(x,y,z);
				ia	= wFr.Mls.x[im]->Bonds.x[i].id_Atoms.x[1];
				x	= wFr.Mls.x[im]->Atoms.x[ia].r.x[0]-x0+0.05*j;
				y	= wFr.Mls.x[im]->Atoms.x[ia].r.x[1]-y0;
				z	= wFr.Mls.x[im]->Atoms.x[ia].r.x[2]-z0;
				glVertex3f(x,y,z);
			}
		}
	}
	}
	glEnd();
	glEndList();

	
	theMol=glGenLists(3);
	glNewList(theMol,GL_COMPILE);
	//glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);


	glDisable(GL_LIGHT0);

	GLfloat light_ambient[] = {1, 1, 1, 1};

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);

	GLfloat light_diffuse[] = {0.0, 0.0, 0.0, 1};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	//glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	xyz.setmem(WF->Mls.x[0]->Atoms.N);
	radius.setmem(WF->Mls.x[0]->Atoms.N);
	for (int im=0;im<wFr.Mls.N;im++)
	{
		for(int i=0;i<wFr.Mls.x[im]->Atoms.N;i++)
		{
			x	= wFr.Mls.x[im]->Atoms.x[i].r.x[0]-x0;
			y	= wFr.Mls.x[im]->Atoms.x[i].r.x[1]-y0;
			z	= wFr.Mls.x[im]->Atoms.x[i].r.x[2]-z0;

			ia	= wFr.Mls.x[im]->Atoms.x[i].id_Tpz;

			r	= double(wFr.TableZR.Lines.x[ia].color.x[0])/256;
			g	= double(wFr.TableZR.Lines.x[ia].color.x[1])/256;
			b	= double(wFr.TableZR.Lines.x[ia].color.x[2])/256;

			rd	= wFr.TableZR.Lines.x[ia].vdwrad/2000;

			//	glLoadIdentity();
			glTranslated(x,y,z);
			glScaled(rd,rd,rd);
			glColor3d(r,g,b);
			param[0]	= r;param[1]	= g;param[2]	= b;param[3]	= 0;
			glMaterialfv(GL_FRONT, GL_AMBIENT,param);
			glCallList(theSph);
			glScaled(1/rd,1/rd,1/rd);
			glTranslated(-x,-y,-z);
			//gluQuadricDrawStyle(qobj, GLU_FILL); 
			//gluSphere(qobj,rd,10,7);

			pnt.x[0]	= x;
			pnt.x[1]	= y;
			pnt.x[2]	= z;

			xyz.add(pnt);
			radius.add(rd);

		}
	}
      //torus(8,25);

	glCallList(theWires);

	glEndList();

}*/

void OpenGLWidget::createFontBits(vecT<char > &s_dt,  vecT <GLubyte> &Bits, QRect &rects)	// создание массива битовых карт фонтов для текста
{
	int ii;
	QString str;
	QColor  col,col1;
	GLubyte *ch;
	int nn,ir,ig,ib;

	QFont font0("Times",12);
	QFont font1("Times",12);

	//QSize qsz;

	QFontMetrics fm(font0);
	QRect rect;
	QPixmap pixmap(100,100);
	pixmap.fill( Qt::transparent);
	QPixmap *pixmaps;
	
	QPainter painter;//(&pixmap);

	QImage img;//,img1;

	
		str.clear();
		str=QString().fromLatin1(s_dt.x,s_dt.N);
		ir=ig=ib=255;
		col.setRgb(ir,ig,ib,255);
		col1.setRgb(0,0,0,255);
		//col.setRgb(120,120,120,255);
		rect	= fm.boundingRect(str);
		pixmaps	= new QPixmap;
		pixmaps[0]	= pixmap.copy(rect);
		//pixmaps->fill( Qt::transparent);
		painter.begin(pixmaps);
		painter.setFont(font0);
		painter.setPen(col);
		painter.drawText(-rect.left(), -rect.top(),str);//rect,Qt::AlignCenter,str);
		painter.setFont(font1);
		painter.setPen(col1);
	 	painter.drawText(-rect.left()+1, -rect.top()+1,str);//rect,Qt::AlignCenter,str);

		
		img = pixmaps->toImage();
		img.convertToFormat(QImage::Format_ARGB32,Qt::ColorOnly);
		img = QGLWidget::convertToGLFormat(img);

		ch	= img.bits();
		nn	= img.byteCount();

		Bits.add(ch,nn);
		rects	= rect;

		painter.end();
		delete pixmaps;
}

void OpenGLWidget::createFontBits()
{
	int ii;
	QString str;
	QColor  col,col1;
	GLubyte *ch;
	int nn,ir,ig,ib;

	QFont font0("Times",13);
	QFont font1("Times",11);

	//QSize qsz;

	QFontMetrics fm(font0);
	QRect rect;
	QPixmap pixmap(100,100);
	pixmap.fill( Qt::transparent);
	QPixmap *pixmaps;
	
	QPainter painter;//(&pixmap);

	QImage img;//,img1;

	sBits_text.setlen(256);
	sBits_txt_rects.setlen(256);

	for(ii=0;ii<256;ii++)
	{
		str.clear();
		str.append(QChar(ii));
		ir=ig=ib=225;
		col.setRgb(ir,ig,ib,255);
		col1.setRgb(0,0,0,255);
		//col.setRgb(120,120,120,255);
		rect	= fm.boundingRect(str);
		pixmaps	= new QPixmap;
		pixmaps[0]	= pixmap.copy(rect);
		//pixmaps->fill( Qt::transparent);
		painter.begin(pixmaps);
		painter.setFont(font0);
		painter.setPen(col);
		painter.drawText(-rect.left(), -rect.top(),str);//rect,Qt::AlignCenter,str);
		painter.setFont(font1);
		painter.setPen(col1);
	 	painter.drawText(-rect.left()+1, -rect.top()+1,str);//rect,Qt::AlignCenter,str);

		
		img = pixmaps->toImage();
		img.convertToFormat(QImage::Format_ARGB32,Qt::ColorOnly);
		img = QGLWidget::convertToGLFormat(img);

		ch	= img.bits();
		nn	= img.byteCount();

		sBits_text.x[ii].add(ch,nn);
		sBits_txt_rects.x[ii]	= rect;

		painter.end();
		delete pixmaps;
	}
}

void OpenGLWidget::createFontBits_Atoms()
{
	int ii;
	QString str;
	QColor  col,col1;
	GLubyte *ch;
	int nn,ir,ig,ib;

	QFont font0("Times",13);
	QFont font1("Times",11);

	//QSize qsz;

	QFontMetrics fm(font0);
	QRect rect;
	QPixmap pixmap(100,100);
	pixmap.fill( Qt::transparent);
	QPixmap *pixmaps;
	
	QPainter painter;//(&pixmap);

	QImage img;//,img1;

	sBits_atom.setlen(WF->TableZR.Lines.N);
	sB_at_rects.setlen(WF->TableZR.Lines.N);

	for(ii=0;ii<WF->TableZR.Lines.N;ii++)
	{
		str.clear();
		str.append(QChar(WF->TableZR.Lines.x[ii].Ch.x[0]));
		if(WF->TableZR.Lines.x[ii].Ch.x[1]!='\0') str.append(QChar(WF->TableZR.Lines.x[ii].Ch.x[1]));
		ir=ig=ib=225;
		col.setRgb(ir,ig,ib,255);
		col1.setRgb(0,0,0,255);
		//col.setRgb(120,120,120,255);
		rect	= fm.boundingRect(str);
		pixmaps	= new QPixmap;
		pixmaps[0]	= pixmap.copy(rect);
		//pixmaps->fill( Qt::transparent);
		painter.begin(pixmaps);
		//pixmap.//..fill( Qt::transparent);
//		painter->setBackgroundMode(Qt::TransparentMode);
		painter.setFont(font0);
		painter.setPen(col);
		//painter.setViewport(0,0,rect.left(), rect.top());
		painter.drawText(-rect.left(), -rect.top(),str);//rect,Qt::AlignCenter,str);
		painter.setFont(font1);
		painter.setPen(col1);
	 	//painter.drawText(rect,Qt::AlignCenter,str);
		painter.drawText(-rect.left()+1, -rect.top()+1,str);//rect,Qt::AlignCenter,str);

		
		img = pixmaps->toImage();
		img.convertToFormat(QImage::Format_ARGB32,Qt::ColorOnly);
		img = QGLWidget::convertToGLFormat(img);

		ch	= img.bits();
		nn	= img.byteCount();

		sBits_atom.x[ii].add(ch,nn);
		sB_at_rects.x[ii]	= rect;

		painter.end();
		delete pixmaps;
	}
}

void OpenGLWidget::rendAtCh()
{
	int ii,jj,kk;
	vec3db rch;
	double rd;

	if(mols.N>0)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		for (kk=0;kk<mols.N;kk++)
		{
			for (ii=0;ii<mols.x[kk]->Atoms.N;ii++)
			{
				rch.x[0]	= camPos[0];
				rch.x[1]	= camPos[1];
				rch.x[2]	= camPos[2];

				rch	-= mols.x[kk]->Atoms.x[ii].r;

				if(rch.sqnr()<196)
				{
					rch	= mols.x[kk]->Atoms.x[ii].r;
					jj	= mols.x[kk]->Atoms.x[ii].id_Tpz;
					rd	= WF->TableZR.Lines.x[jj].vdwrad/500;
					rch.x[0]	-= rd*camOZ[0]*1.05;
					rch.x[1]	-= rd*camOZ[1]*1.05;
					rch.x[2]	-= rd*camOZ[2]*1.05;

					rch.x[0]	+= rd*camOX[0]*0.3;
					rch.x[1]	+= rd*camOX[1]*0.3;
					rch.x[2]	+= rd*camOX[2]*0.3;

					rch.x[0]	-= rd*camOY[0]*0.3;
					rch.x[1]	-= rd*camOY[1]*0.3;
					rch.x[2]	-= rd*camOY[2]*0.3;/**/

					glRasterPos3d( rch.x[0], rch.x[1], rch.x[2]);
					glDrawPixels( sB_at_rects.x[jj].width(), sB_at_rects.x[jj].height(), GL_RGBA, GL_UNSIGNED_BYTE, sBits_atom.x[jj].x );
				}
			}
		}
		glDisable(GL_BLEND);
	}
}
/*
void OpenGLWidget::genAtCh()
{
	int ii,jj;
	vec3db rch;


	if(theAtCh!=0)
	{
		glDeleteLists(theAtCh, 8);
	}

	theAtCh	= glGenLists(8);
	glNewList(theAtCh,GL_COMPILE);

	if(xyz.N>0)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		for (ii=0;ii<xyz.N;ii++)
		{
			rch	= xyz.x[ii];
/*			rch.x[0]	-= radius.x[ii]*camOZ[0]*1.05;
			rch.x[1]	-= radius.x[ii]*camOZ[1]*1.05;
			rch.x[2]	-= radius.x[ii]*camOZ[2]*1.05;

			rch.x[0]	+= radius.x[ii]*camOX[0]*0.3;
			rch.x[1]	+= radius.x[ii]*camOX[1]*0.3;
			rch.x[2]	+= radius.x[ii]*camOX[2]*0.3;

			rch.x[0]	-= radius.x[ii]*camOY[0]*0.3;
			rch.x[1]	-= radius.x[ii]*camOY[1]*0.3;
			rch.x[2]	-= radius.x[ii]*camOY[2]*0.3;*/

/*			jj	= id_at_sB.x[ii];


			glRasterPos3d( rch.x[0], rch.x[1], rch.x[2]);
			glDrawPixels( sB_at_rects.x[jj].width(), sB_at_rects.x[jj].height(), GL_RGBA, GL_UNSIGNED_BYTE, sBits_atom.x[jj].x );
		}
		glDisable(GL_BLEND);
	}
	glEndList();
}
*/

void OpenGLWidget::updateSelPar()
{
	int ii;
	his_strs.setlen(his_ptrs_ml.N);
	vec3db r1,r2,r3,r4,n1,n2;
	QString str;
	double par,d1,d2,d3;

	sBits.setlen(his_ptrs_ml.N);
	srects.setlen(his_ptrs_ml.N);

	for(ii=0;ii<his_ptrs_ml.N;ii++)
	{
		switch (his_ptrs_ml.x[ii].N)
		{
		case 2:
			{
				r1	= his_ptrs_ml.x[ii].x[0]->Atoms.x[his_id_sels.x[ii].x[0]].r;
				r2	= his_ptrs_ml.x[ii].x[1]->Atoms.x[his_id_sels.x[ii].x[1]].r;
				r2	-=r1;
				par	= r2.norm();
				str	= QString("%1").arg(par,0,'g',5);
				his_strs.x[ii].add((str.toLatin1()).data(),str.length());

				createFontBits(his_strs.x[ii], sBits.x[ii], srects.x[ii]);

				break;
			}
		case 3:
			{
				r1	= his_ptrs_ml.x[ii].x[0]->Atoms.x[his_id_sels.x[ii].x[0]].r;
				r2	= his_ptrs_ml.x[ii].x[1]->Atoms.x[his_id_sels.x[ii].x[1]].r;
				r3	= his_ptrs_ml.x[ii].x[2]->Atoms.x[his_id_sels.x[ii].x[2]].r;
				
				r3	-=r2;
				d3	= r3.norm();
				r2	-=r1;
				d2	= r2.norm();
				par	= 180*acos(-r3.scpr(r2)/(d2*d3))/3.1415926535897932384626433832795;
				str	= QString("%1").arg(par,0,'g',5);
				his_strs.x[ii].add((str.toLatin1()).data(),str.length());

				createFontBits(his_strs.x[ii], sBits.x[ii], srects.x[ii]);

				break;
			}
		case 4:
			{
				r1	= his_ptrs_ml.x[ii].x[0]->Atoms.x[his_id_sels.x[ii].x[0]].r;
				r2	= his_ptrs_ml.x[ii].x[1]->Atoms.x[his_id_sels.x[ii].x[1]].r;
				r3	= his_ptrs_ml.x[ii].x[2]->Atoms.x[his_id_sels.x[ii].x[2]].r;
				r4	= his_ptrs_ml.x[ii].x[3]->Atoms.x[his_id_sels.x[ii].x[3]].r;

				r4 -= r3;
				r3 -= r2;
				r2 -= r1;

				n1.crss(r4,r3);
				n2.crss(r3,r2);

				d1 =  n1.norm();
				d2 =  n2.norm();

				par	= 180*acos(n1.scpr(n2)/(d1*d2))/3.1415926535897932384626433832795;
				str	= QString("%1").arg(par,0,'g',5);
				his_strs.x[ii].add((str.toLatin1()).data(),str.length());

				createFontBits(his_strs.x[ii], sBits.x[ii], srects.x[ii]);

				break;
			}
		}
	}
	update();
}

void OpenGLWidget::rendSelPar()
{
	int ii;

	vec3db r1,r2,r3,r4,n1,n2,n3,rr,r0,nn;
	//vecT<vec3db> crd;
	double a,sn,cs,b;
	//crd.setlen(10);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_LINE_STIPPLE);
	glLineStipple(4, 0xAAAA);
	for(ii=0;ii<his_ptrs_ml.N;ii++)
	{
		switch (his_ptrs_ml.x[ii].N)
		{
		case 2:
			{
				r1	= his_ptrs_ml.x[ii].x[0]->Atoms.x[his_id_sels.x[ii].x[0]].r;
				r2	= his_ptrs_ml.x[ii].x[1]->Atoms.x[his_id_sels.x[ii].x[1]].r;

				glBegin(GL_LINES);
				glVertex3f(r1.x[0],r1.x[1],r1.x[2]);
				glVertex3f(r2.x[0],r2.x[1],r2.x[2]);
				glEnd();

				r2	+= r1;

				r2	/= 2.0;

				r2.x[0]	-= 0.3*camOZ[0];
				r2.x[1]	-= 0.3*camOZ[1];
				r2.x[2]	-= 0.3*camOZ[2];
		
				glRasterPos3d( r2.x[0], r2.x[1], r2.x[2]);
				glDrawPixels( srects.x[ii].width(), srects.x[ii].height(), GL_RGBA, GL_UNSIGNED_BYTE, sBits.x[ii].x );
					
				break;
			}
		case 3:
			{
				r1	= his_ptrs_ml.x[ii].x[0]->Atoms.x[his_id_sels.x[ii].x[0]].r;
				r2	= his_ptrs_ml.x[ii].x[1]->Atoms.x[his_id_sels.x[ii].x[1]].r;
				r3	= his_ptrs_ml.x[ii].x[2]->Atoms.x[his_id_sels.x[ii].x[2]].r;


				n1	= r1-r2;
				n1.nrml();
				n2	= r3-r2;
				n2.nrml();

				b	= n1.scpr(n2);
				n3.crss(n1,n2);
				n3.nrml();
				a	= acos(b)/9;
				n2.crss(n3,n1);

				glBegin(GL_LINES);
				glVertex3f(r1.x[0],r1.x[1],r1.x[2]);
				glVertex3f(r2.x[0],r2.x[1],r2.x[2]);
				glVertex3f(r3.x[0],r3.x[1],r3.x[2]);
				glVertex3f(r2.x[0],r2.x[1],r2.x[2]);
				glEnd();

				glBegin(GL_LINE_STRIP);
				for(int jj=0;jj<10;jj++)
				{
					sn	= sin(a*jj);
					cs	= cos(a*jj);
					rr	= n1*cs+n2*sn;
					rr	+= r2;
					glVertex3f(rr.x[0],rr.x[1],rr.x[2]);
					if(jj==4) n3 = rr;
				}
				glEnd();

				n3.x[0]	-= 0.3*camOZ[0];
				n3.x[1]	-= 0.3*camOZ[1];
				n3.x[2]	-= 0.3*camOZ[2];
		
				glRasterPos3d( n3.x[0], n3.x[1], n3.x[2]);
				glDrawPixels( srects.x[ii].width(), srects.x[ii].height(), GL_RGBA, GL_UNSIGNED_BYTE, sBits.x[ii].x );

				break;

			}
		case 4:
			{
				r1	= his_ptrs_ml.x[ii].x[0]->Atoms.x[his_id_sels.x[ii].x[0]].r;
				r2	= his_ptrs_ml.x[ii].x[1]->Atoms.x[his_id_sels.x[ii].x[1]].r;
				r3	= his_ptrs_ml.x[ii].x[2]->Atoms.x[his_id_sels.x[ii].x[2]].r;
				r4	= his_ptrs_ml.x[ii].x[3]->Atoms.x[his_id_sels.x[ii].x[3]].r;

				n3	= r3-r2;
				n3.nrml();
				n1	= r1-r2;
				n1	= n1-n3*(n1.scpr(n3));
				n1.nrml();
				n2	= r4-r3;
				n2	= n2-n3*(n2.scpr(n3));
				n2.nrml();

				nn	= n2;

				b	= n1.scpr(n2);
				n3.crss(n1,n2);
				n3.nrml();
				a	= acos(b)/9;
				n2.crss(n3,n1);

				r0	= (r2+r3)/2.0;
				


				glBegin(GL_LINES);
				glVertex3f(r2.x[0],r2.x[1],r2.x[2]);
				glVertex3f(r3.x[0],r3.x[1],r3.x[2]);

				glVertex3f(r0.x[0],r0.x[1],r0.x[2]);
				glVertex3f(r1.x[0],r1.x[1],r1.x[2]);

				glVertex3f(r4.x[0],r4.x[1],r4.x[2]);
				glVertex3f(r0.x[0],r0.x[1],r0.x[2]);



				r1	= r0+n1;
				r4	= r0+nn;

				glVertex3f(r1.x[0],r1.x[1],r1.x[2]);
				glVertex3f(r0.x[0],r0.x[1],r0.x[2]);
				glVertex3f(r4.x[0],r4.x[1],r4.x[2]);
				glVertex3f(r0.x[0],r0.x[1],r0.x[2]);
				glEnd();

				glBegin(GL_LINE_STRIP);
				for(int jj=0;jj<10;jj++)
				{
					sn	= sin(a*jj);
					cs	= cos(a*jj);
					rr	= n1*cs+n2*sn;
					rr	+= r0;
					glVertex3f(rr.x[0],rr.x[1],rr.x[2]);
					if(jj==4) n3 = rr;
				}
				glEnd();

				n3.x[0]	-= 0.3*camOZ[0];
				n3.x[1]	-= 0.3*camOZ[1];
				n3.x[2]	-= 0.3*camOZ[2];
		
				glRasterPos3d( n3.x[0], n3.x[1], n3.x[2]);
				glDrawPixels( srects.x[ii].width(), srects.x[ii].height(), GL_RGBA, GL_UNSIGNED_BYTE, sBits.x[ii].x );
			}
		}
	}
	
	glDisable(GL_LINE_STIPPLE);
	glDisable(GL_BLEND);
}

void RenderText( QGLWidget* w, double x, double y, double z, const QString& text, const QColor& col = Qt::white, const QFont& font = QFont() )
{
   /* glMatrixMode( GL_PROJECTION );
    glPushMatrix();              
    glLoadIdentity();              
    glOrtho( 0, w->width(), w->height(), 0, 0, 1 );
    glMatrixMode( GL_MODELVIEW );
    glPushMatrix();              
    glLoadIdentity();              
*/
	QFontMetrics fm(font);
	QRect rect = fm.boundingRect( text);

	QPixmap pixmap( rect.size() );
	pixmap.fill( Qt::transparent);
	QPainter painter(&pixmap);
	painter.setPen( col );
	painter.setFont( font );
	painter.drawText( -rect.left(), -rect.top(), text );

	QImage img = pixmap.toImage();
	img.convertToFormat(QImage::Format_ARGB32,Qt::ColorOnly);
	//img.setAlphaBuffer( true );
	/*for ( int i = 0; i < img.height(); i++ ) {
		QRgb* rgb = (QRgb*) img.scanLine(i);
		for ( int j = 0; j < img.width(); j++ ) {
			rgb[j] = qRgba( col.red(), col.green(), col.blue(), qRed(rgb[j]) );
		}   
	}*/
	img = QGLWidget::convertToGLFormat(img);

	GLubyte * ch;
	int nn;

	ch	= img.bits();
	nn	= img.byteCount();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glRasterPos3d( x, y, z );
	glDrawPixels( rect.width(), rect.height(), GL_RGBA, GL_UNSIGNED_BYTE, img.bits() );
	glDisable(GL_BLEND);
	/*glMatrixMode( GL_PROJECTION );
    glPopMatrix();              
    glMatrixMode( GL_MODELVIEW );
    glPopMatrix();
	*/
}

void OpenGLWidget::changefoncolor()
{
	colcod	= colcod==0 ? 1 : 0;

	if (colcod == 0)	glClearColor(0,0,0,1);// Qt::black);
	else glClearColor(1,1,1,1);// Qt::white);

	//genScene();
	update();
}