#ifndef SURFACE_H
#define SURFACE_H

#include <QObject>
#include "rolling.h"
#include "Trimesh.h"
#include "MeshCreator.h"
#include "rdwrfls.h"
#include "rdfls.h"

#include "GLframe.h"
//class QObject;
//class WorkFrame;

class Surface: public QObject
{
	WorkFrame *WF;
	OpenGLWidget *glWidg;

	ConnectedAtoms * smol;

	//bool isSur;

	int viztype; // 1 - сплошна€, 2 - решЄтка
	double transp;	// 1 - непрозрачна€, [0,1) - прозрачна€
	
	// тип визуализации молеклы. 0 - гладка€ поверхность, цвета по атомам, 1 - решЄтка, цвета по атомам, 
					// 2 - гладка€ + (инв) решЄтка, цвета по атомам, 3 - гладка€, двусторонн€€, цвета по атомам, 
					// 4 - решЄтка, двусторон€€, цвета по атомам, 5 - гладка€ монохромна€, цвет пользовател€, 
					// 6 - решЄтка монохромна€, цвет пользовател€...
	vec3int color;


public:

	MolData DDD;
	TrSurface Surf;
	MeshConstructor Msh;

	Surface(){ viztype = -1; color.x[0] = -1;color.x[1] = -1;color.x[2] = -1;transp = 1.0;}
	~Surface(){ delSurface();}

	void SetWorkframe(WorkFrame *wf){WF=wf;}
	void SetGL(OpenGLWidget *wf){glWidg=wf;}
	void SetMolecule(ConnectedAtoms * lmol){smol	= lmol;}
	void BuildSurface(int m_id); // строить поверхность молекулы с номером m_id
	void BuildSurface(); // строить поверхность молекулы
	void delSurface();
	inline ConnectedAtoms * GetMolecule(){return smol;}

	int getviztype() {return viztype;}
	void setviztype(int tp){viztype	= tp;}
	int gettransp() {return transp;}
	void settransp(double tp){transp	= tp;}
	vec3int & getcolor(){return color;}
	void setcolor(vec3int &c){color = c;}
	bool getismoth() {return (viztype==0)||(viztype==2)||(viztype==3)||(viztype==5);}
	//BuildSurface(vecT<int> &m_id, vecT<int> &a_id); // строить поверхность атомов из

	void clearWF(){WF=0x0;}
	void clearMol(){smol	= 0x0;}

	void RCS();
//signals:
//	void RdrCrSrf();

};

class MolSurf
{
public:

	MolData DDD;
	TrSurface Surf;
	MeshConstructor Msh;

	MolSurf(){}
	~MolSurf(){}//if(isSur) delSurface();}

	void BuildSurface(); // строить поверхность молекулы 
//	void delSurface();

	//int getviztype() {return viztype;}
	//bool getismoth() {return (viztype==0)||(viztype==2)||(viztype==3)||(viztype==5);}
	//BuildSurface(vecT<int> &m_id, vecT<int> &a_id); // строить поверхность атомов из
};

#endif 