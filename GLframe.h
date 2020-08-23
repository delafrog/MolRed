/*
GLframe.h 
���������� ������� 3D ����������
--------------
MolRed.
Copyright @ Zhabin S.N.
ver. 0.0.1
07.2008
*/

#ifndef GLFRAME_H
#define GLFRAME_H


//#include <QWhellEvent>
#include <Windows.h>
#include <GL\GLU.h>
//#include <GL\GL.h>
//#include <GL\GL.h>

#include <QGLWidget>
//#include <QOpenGLFunctions_2_1>

#include "linalg.h"
//#include "linalg.cpp"
#include "rdwrfls.h"




class Surface;
class RotatWin;
class ConnectedAtoms;
class ActualSpace;


#define SPHERE 11
#define CYLINDER1 12
#define CYLINDER2 13
#define CYLINDER3 14
#define SCENE     15
//#define ATOMSCHARS  16



class GrphType
{
public:
	int colortype; // ��� �������� ��������� (���� ������������, ���� �� ������)
	int structype; //  ��� ��������� ���������� ()
};

/*class UserSpace:: public QWidget
{
public:
	vec3db rc; // ���������� ������ ��������������
	vec3db abc; // ������� ��������������
//	Quaternion<double> q; // ���������� �������� ��������������.
}*/


class OpenGLWidget : public QGLWidget//, protected QOpenGLFunctions_2_1
{
	Q_OBJECT
public:
	OpenGLWidget(QWidget *parent = 0);
	~OpenGLWidget(){gluDeleteQuadric(qobj);gluDeleteQuadric(qobj1);gluDeleteQuadric(qobj2);gluDeleteQuadric(qobj3);}

	//void genScene(WorkFrame &wFr);	// ������������� ����� � ���������
//	void genScene();	// ������������� ����� � ���������
//	void genScene1();	// ������������� ����� � ���������
	//void genWrScene(WorkFrame &wFr);	// ������������� ����� � ��������� � ���� �������
//	void genWrScene();	// ������������� ����� � ��������� � ���� �������
	void genAtCh();
	void initmol(WorkFrame *wFr);
	void setrotwin(RotatWin *rw){RW=rw;}
	void setActSpc(ActualSpace *as){AS=as;}
	void genSurfScene(Surface *surface);
	void setBL(bool ch){isBondLen = ch;}
	void setVA(bool ch){isValAngl = ch;}
	void setTA(bool ch){isTorAngl = ch;}
	void setidmlbl(){id_ml_bl	= select_id.x[0].x[0]; id_at_bl1=select_id.x[0].x[1];id_at_bl2=select_id.x[1].x[1];}
	void setidmlbl(int id,int ia1,int ia2){id_ml_bl	= id; id_at_bl1=ia1;id_at_bl2=ia2;}
	void setidmlva(){id_ml_va	= select_id.x[0].x[0]; id_at_va1=select_id.x[0].x[1];id_at_va2=select_id.x[1].x[1];id_at_va3=select_id.x[2].x[1];}
	void setidmlva(int id,int ia1,int ia2,int ia3){id_ml_va	= id; id_at_va1=ia1;id_at_va2=ia2;id_at_va3=ia3;}
	void setidmlta(){id_ml_va	= select_id.x[0].x[0]; id_at_va1=select_id.x[0].x[1];id_at_va2=select_id.x[1].x[1];id_at_va3=select_id.x[2].x[1];id_at_va4=select_id.x[3].x[1];}
	void setidmlta(int id,int ia1,int ia2,int ia3,int ia4){id_ml_va	= id; id_at_va1=ia1;id_at_va2=ia2;id_at_va3=ia3;id_at_va4=ia4;}
	void setAlf(double a){alf = a;}
	vecT<int> s_id;
	//vecT<vec2int> *s_ids;
	vecT<vec2int> select_id;
	vecT<int>	sel_idm;
	vecT<vec3db> sel_xyz;
	vecT<vec3db> init_xyz; // ������ � ����������� ������ �� ��������� ����� ����� ��� ��������� � ���������� �����
	vecT<int> ids_bl;
	vec3db	getrc(){return rc;}
	vec3db	getFocPos(){return vec3db(focPos[0],focPos[1],focPos[2]);}
	vec3db  gettv(){return tv;}
 	bool	getMolSel(){return isMolSel;}
	void	setIsSurf(bool ch){isSurf	= ch;}
	int		getAtId(){return id_at;}
	int		getMlId(){return id_ml;}
	void	clrIds(){id_at	= -1;id_ml	= -1;addatomtype = 0;}
	int		getAddTp(){return addatomtype;}
	double	getAlf(){return alf;}
	vec3db  getPnr(){return pnr;}
	vec3db  getAxs(){return axs;}
	int		getIdMlBl(){return id_ml_bl;}
	int		getIdAtBl(){return id_at_bl2;}

	int		add_Selectd_ids(vecT<ConnectedAtoms * > &ptr_ml, vecT<int> &id_atoms);	// �������� ������� � ���������� ������
	int		check_Selected_ids(vecT<ConnectedAtoms * > &ptr_ml, vecT<int> &id_atoms);	// ��������� ������� � ��������� ������
	void	check_Selected_ids(vecT<int> &ids_mlat);	// ��������� ������� � ��������� ������
	void	del_Selected_ids(int id_mlat);	// ������� ������� � ��������� ������
	void	del_Selected_ids(vecT<int> &ids_mlat);	// ������� ������� � ��������� ������
	void	swp_Selected_ids(int id_ml,int id_at1, int id_at2);	// ���� �������

	vecT<ConnectedAtoms * > mols;

	void setmols(vecT<ConnectedAtoms * > &in_mols);

	bool	getproj(){return isOrtho;}
	void	setproj(bool ch){isOrtho	= ch;}
	void	setrwr(bool ch){isRotat = ch;}
	void	clearQuat(){Quat.zerospin();}

	void	setmolcrd(int id_mol);
	void    sel2atom();
	void	unselprod();
	void	unselprod(vecT<vec2int> &s);

	void setCamera(vec3db &r0, vec3db &r1); // ���������� ������ � ��������� r1 � ������� � r0.
	//vecT<int> getsel();

	void get3Dfrom2D(); // �������� 3D ���������� �� 2D ����������� ������� ����
	void get3Dfrom2D(const vec3db &upc); // �������� 3D ���������� �� 2D ����������� ������� ����
	vec3db get3Dfrom2D(int x, int y); // �������� 3D ���������� �� 2D ����������� ������� ����
	vec3db get3Dfrom2D(const vec3db &upc,int x, int y); // �������� 3D ���������� �� 2D ����������� ������� ����

	void reprojGL();

	void selsort();
	void selAnalize();	// ������ ���������� ������ - ��������� ������ � ������� ������� � ������� ������ � ���
	void selectMols();	// ��������� ������� �� ���������� ������

	void rendScene();	// ������ �����
	void rendPrmtv();	// ������ ���������� - ����� � ���������

public slots:
	void FrgBrwOn(){isFrgBrw = true;}
	void FrgBrwOff(){isFrgBrw = false;}
	void AtomBrwOn(){isAtomBrw = true;}
	void AtomBrwOff(){isAtomBrw = false;id_ml	= -1;id_at	= -1;addatomtype	= 0;rendScene();update();}
	void narrowSel();
	void frameSel();
	void moleculeSel(); // �������� ����� ������ �������
	void invertSel(); // ������������� ���������

	void renderAtCh_on(){isRenChAt	= true;update();}
	void renderAtCh_off(){isRenChAt	= false;update();}

	void renAS_onoff(){isActSpcShow	= !isActSpcShow;rendScene();update();}
	void rcAS_set();
	//void renAS_off(){isActSpc	= false;updateGL();}

	void rendSurface(Surface *srf,int jm,int tp = 1,double tsp = 1.);

	void SurfModifyOn(){isSurfModify	= true;}
	void SurfModifyOff(){isSurfModify	= false;}

	void rotatproc();	// ���������� ��������� �������� 

	void showSelPar(){isSelParShow = true;}	// �������� ��������� ��������� ������ � ����������� �����
	void clearSelPar(){isSelParShow = false; his_ptrs_ml.N=0;his_id_sels.N=0;his_strs.N=0;}

	void doSelShow();
	void jump2sel();

	void updtAS(){rendScene();update();}
//	void genCrSurf();

//	void nonmolSel();

	void changefoncolor();// �������� ���� ����

protected:
	void initializeGL();
	void resizeGL(int width,int height);

	void paintGL();

	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseDoubleClickEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);
	void enterEvent(QEvent *event);
	void leaveEvent(QEvent *event);

signals:
	void selectDo();
	void uselDo();
	void deleteDo();
	void addbndDo();
	void moveDo();
	void addfrgDo();
	void addatomDo();
	void closeFrgBrw();
	void closeAtomBrw();
	void rotatDo();
	void movefrgDo();
	void updatestate();

	void genCrSurf();

private:
	void draw();
	int faceAtPosition(const QPoint &pos);
	int selectAction(const QPoint &pos);
	int selectAtom(const QPoint &pos);
	int selectFrameAction();
	bool selectQuaC(const QPoint &pos);

	void createFontBits_Atoms();// �������� ������� ������� ���� ������ ��� ������

	void createFontBits();	// �������� ������� ������� ���� ������ ��� ������

	void createFontBits(vecT<char > &s_dt,  vecT <GLubyte>  &Bits, QRect &rects);	// �������� ������� ������� ���� ������ ��� ������


	void rendAtCh();

	void rendMol(ConnectedAtoms *mol,int jm);
	void rendAtoms(ConnectedAtoms *mol,int jm);
	void rendBonds(ConnectedAtoms *mol,int jm);
	void rendWire(ConnectedAtoms *mol,int jm);

	void rendAtomsChar(ConnectedAtoms *mol,int jm);

	void rendActSpc(); // ���������� ����
	

	void rendSelPar();	// ��������� ���������� ���������� ������
	void updateSelPar();	// ���������� ���������� ���������� ������

	void clearAllthes();
	void initAllthes();

	void setrucon(); // �������� 3D ���������� �� 2D ����������� ������� ����
	void setldcon(); // �������� 3D ���������� �� 2D ����������� ������� ����

	int theMol,theSph,theCyl,the2Cyl,the3Cyl,theAtCh;
	int theSurf;
	int theInvSurf;
	
	int theAtCh_;

	int theSelected;
	vecT<int> theSelecteds;

	int theL;

	int theSph_,theCyl_,the2Cyl_,the3Cyl_;

	vecT<int> theAtoms;
	vecT<int> theBonds;
	vecT<int> theWires;
	vecT<int> theMols;
	vecT<int> theAtomsChars;
	vecT<int> theSurfaces;
	int theActSpc;
	int theScene;

	vecT< vecT<int> > his_id_sels;	// ������� ������� ��������� ������, ��������� ������ �������� � ����������� �����
	vecT< vecT<ConnectedAtoms * > > his_ptrs_ml;	// ��������� �� �������� � ������� ��������� ����� ������
	vecT< vecT<char> > his_strs;

	//vecT<int> idthes;

	WorkFrame *WF;
	RotatWin *RW;
	ActualSpace *AS;


	
	/*vecT<vec3T<double> > rA;
	vecT<vec3T<int> > cA;
	vecT<double> rd;*/

	GLfloat	rotationX;
	GLfloat	rotationY;
	GLfloat	rotationZ;
	QColor	faceColors[4];
	QPoint	lastPos;
	GLfloat	camPos[3];	// ��������� ������	(� ���������� ������� ���������)
	GLfloat	camOX[3];	// ���������� ������ (� ���������� ������� ���������)
	GLfloat	camOY[3];	// ���������� ������ (� ���������� ������� ���������)
	GLfloat	camOZ[3];	// ���������� ������ (� ���������� ������� ���������)
	GLfloat focPos[3];	// ����� ������ ������ (������ ������� ���������� ��������) (� ���������� ������� ���������)
	GLfloat VCMPos[3];	// ��������� ������������ ������������
	GLUquadricObj *qobj;
	GLUquadricObj *qobj1;
	GLUquadricObj *qobj2,*qobj3;

	vec3db	rc;
	vec3db  tv;	// ������ ��� �������� ���������� ������ ��������� get3Dfrom2D();
	vec3db	pnr;	// ������ ��� �������� ���������� ������� ����������� �������� ��� ��������� ����� �����, ���������� ��� ����������� �����

	double alf;	// ���� ��������
	vec3db axs;	// ��� ��������
	double sna;

	bool inversel;

	//vecT<vecint> selected_ids;
//	vecT<vec3db> xyz;
//	vecT<double> radius;
	//vecT<vec2int> atom_ids;
	
	int scenetype;
	bool isDblRight;
	bool isShift;
	bool isCtrl;
	bool isSurf;
	bool isFrgBrw;
	bool isAtomBrw;
	bool isFrameSel;
	bool isMolSel;
	bool isOrtho;
	bool isRenChAt;// ���� ���������� ����� ������ 
	bool isRotat;// ���� ��������� ������ �������� ������� ��� ��������������
	bool isMovQc;// ���� ����������� ��� ��������
	bool isBondLen;// ���� ����������� ������������� ����� �����
	bool isValAngl;// ���� ����������� ������������� ��������� ����
	bool isTorAngl;// ���� ����������� ������������� ���������� ����
	bool isSelParShow; // ���� ��������� ���������� ��������� ������ � ����������� �����
	bool isActSpcShow;	// ���� ��������� ����

	bool isSurfModify;	// ���� ����������� ������������
	
	bool drawFrame;
	double dis_koeff; 
	vec3db rucon,ldcon;
	vec2int ruc,ldc;
	int id_at,id_ml,id_ml_,id_ml_bl,id_ml_va;
	int id_at_bl1,id_at_bl2;
	int id_at_va1,id_at_va2,id_at_va3,id_at_va4;
	int addatomtype;
	double atom_visual_size;
//	vecT<int> ids_bl;

	int colcod; // ���� ����� ���� 0 - ������, 1 - �����

	double z_near;	// ���������� �� ������� �����
	double z_far;	// ���������� �� ������� ����� 
	double p_alf;	// ���� �����������
	double mgnf;	// ������������ ���������� ��� ������������� ��������

	double pi;//=3.1415926535897932384626433832795;

	vecT< vecT <GLubyte> > sBits_text;	// ������ ������ � ������������� ������� ����� ��� ������
	vecT< QRect > sBits_txt_rects;	// ������� ���������������

	vecT< vecT <GLubyte> > sBits_atom;	// ������ ������ � ������������� ������� ����� ��� ������
	vecT< QRect >	sB_at_rects;
	vecT<int> id_at_sB;	// ������

	vecT< vecT <GLubyte> > sBits;	// ������ ������ � ������������� ������� ����� ��� ������
	vecT< QRect > srects;	// ������� ���������������

	//vec3db cub_rc;// ����� ����
	//double cub_a; // ������� ����


	Quaternion<double> Quat;
	FullMatrix<double> Arot;
};


void RenderText( QGLWidget* w, double x, double y, double z, const QString& text, const QColor& col , const QFont& font);

#endif
