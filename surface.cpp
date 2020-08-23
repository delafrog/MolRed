#ifndef SURFACE_CPP
#define SURFACE_CPP


#include "init.h"

#include "surface.h"

#include "massivcpp.h"
#include "rdflscpp.h"
#include "volumecpp.h"
#include "Trimeshcpp.h"
//#include "rolling.h"
#include "rollingcpp.h"
#include "MeshCreatorcpp.h"
#include "globals.h"
#include "mlstrct.h"


//#include "rdwrfls.h"

void Surface::BuildSurface(int m_id) // строить поверхность молекулы с номером m_id
{
	//isSur	= true;

	InitObject(DDD);

	ms1D<Vec3db> xyz;
	ms1Ddb r_wdw;
	ms1D<Vec3db> clr;

	xyz.init(WF->Mls.x[m_id]->Atoms.N);
	r_wdw.init(WF->Mls.x[m_id]->Atoms.N);
	clr.init(WF->Mls.x[m_id]->Atoms.N);

	int jj;
	for(int ii=0;ii<xyz.N;ii++)
	{
		xyz.x[ii].x[0]	= WF->Mls.x[m_id]->Atoms.x[ii].r.x[0];
		xyz.x[ii].x[1]	= WF->Mls.x[m_id]->Atoms.x[ii].r.x[1];
		xyz.x[ii].x[2]	= WF->Mls.x[m_id]->Atoms.x[ii].r.x[2];
		jj	= WF->Mls.x[m_id]->Atoms.x[ii].id_Tpz;
		r_wdw.x[ii]	= WF->TableZR.Lines.x[jj].vdwrad;
		r_wdw.x[ii] = r_wdw.x[ii]==-0.01 ? 2 : r_wdw.x[ii]/100;
		clr.x[ii].x[0]	= (double)(WF->TableZR.Lines.x[jj].color.x[0])/256.0;
		clr.x[ii].x[1]	= (double)(WF->TableZR.Lines.x[jj].color.x[1])/256.0;
		clr.x[ii].x[2]	= (double)(WF->TableZR.Lines.x[jj].color.x[2])/256.0;
	}

	DDD.SetDataMol(xyz,r_wdw,clr);

	DDD.SetEigBasis();
	DDD.Get2EigBasis();	
	DDD.SetCubDiv();
	DDD.SetRolling();
	InitObject(Surf);
	Msh.InitMolData(DDD);
	Msh.InitSurface(Surf);
	Msh.SetPar();
	Msh.TrInit();
	Msh.Build();
	//Msh.RefineMesh();
	//Msh.Surf2vrml();
	Msh.JuggleMesh(1,0,Msh.Point.N);
	Msh.Ret2InitBas();
	Msh.DoAtomClr();	// задание параметров раскраски повехности
	Msh.FreeMolData(DDD);
	Msh.FreeSurface(Surf);
}

void Surface::BuildSurface() // строить поверхность молекулы 
{
	//isSur	= true;

	InitObject(DDD);

	ms1D<Vec3db> xyz;
	ms1Ddb r_wdw;
	ms1D<Vec3db> clr;

	xyz.init(smol->Atoms.N);
	r_wdw.init(smol->Atoms.N);
	clr.init(smol->Atoms.N);

	int jj;
	for(int ii=0;ii<xyz.N;ii++)
	{
		xyz.x[ii].x[0]	= smol->Atoms.x[ii].r.x[0];
		xyz.x[ii].x[0]	= smol->Atoms.x[ii].r.x[0];
		xyz.x[ii].x[1]	= smol->Atoms.x[ii].r.x[1];
		xyz.x[ii].x[2]	= smol->Atoms.x[ii].r.x[2];
		xyz.x[ii].x[0]	= smol->Atoms.x[ii].r.x[0];
		jj	= smol->Atoms.x[ii].id_Tpz;
		r_wdw.x[ii]	= WF->TableZR.Lines.x[jj].vdwrad;
		r_wdw.x[ii] = r_wdw.x[ii]==-0.01 ? 2 : r_wdw.x[ii]/100;
		clr.x[ii].x[0]	= (double)(WF->TableZR.Lines.x[jj].color.x[0])/256.0;
		clr.x[ii].x[1]	= (double)(WF->TableZR.Lines.x[jj].color.x[1])/256.0;
		clr.x[ii].x[2]	= (double)(WF->TableZR.Lines.x[jj].color.x[2])/256.0;
	}

	DDD.SetDataMol(xyz,r_wdw,clr);

	DDD.SetEigBasis();
	DDD.Get2EigBasis();	
	DDD.SetCubDiv();
	DDD.SetRolling();
	InitObject(Surf);
	Msh.InitMolData(DDD);
	Msh.InitSurface(Surf);
	Msh.SRF	= this;
	Msh.SetPar();
	Msh.TrInit();
	Msh.Build();
	//Msh.RefineMesh();
	//Msh.RefineMesh();
	//Msh.Surf2vrml();
	//Msh.Surf2vrml(Msh.p_rol);
	/*Msh.RefineMesh();
	Msh.JuggleMesh(1,0,Msh.Point.N);
	Msh.RefineMesh();*/
	Msh.JuggleMesh(1,0,Msh.Point.N);
	Msh.Ret2InitBas();
	Msh.DoAtomClr();	// задание параметров раскраски повехности
	Msh.FreeMolData(DDD);
	Msh.FreeSurface(Surf);
}
void Surface::RCS()
{

	Surf.Point.x	= Msh.Point.x;
	Surf.Point.N	= Msh.Point.N;
	Surf.Point.mN	= Msh.Point.mN;

	Surf.Edge.x	= Msh.Edge.x;
	Surf.Edge.N	= Msh.Edge.N;
	Surf.Edge.mN	= Msh.Edge.mN;

	Surf.Trngl.x	= Msh.Trngl.x;
	Surf.Trngl.N	= Msh.Trngl.N;
	Surf.Trngl.mN	= Msh.Trngl.mN;

	Surf.BndEd.x	= Msh.BndEd.x;
	Surf.BndEd.N	= Msh.BndEd.N;
	

	Vec3db vec;
	Msh.eig.tns();

	

		for(int ii=0;ii<Surf.Point.N;ii++){Msh.eig.pmv(vec,Surf.Point.x[ii].nor);Surf.Point.x[ii].nor=vec;}
		for(int ii=0;ii<Surf.Point.N;ii++){Msh.eig.pmv(vec,Surf.Point.x[ii].crd);Surf.Point.x[ii].crd=vec;}
		for(int ii=0;ii<Surf.Point.N;ii++){Surf.Point.x[ii].crd += Msh.pc;}

	Msh.eig.tns();

	glWidg->SurfModifyOn();
	glWidg->rendScene();
	glWidg->update();
	glWidg->SurfModifyOff();


	for(int ii=0;ii<Surf.Point.N;ii++){Surf.Point.x[ii].crd -= Msh.pc;}
	for(int ii=0;ii<Surf.Point.N;ii++){Msh.eig.pmv(vec,Surf.Point.x[ii].nor);Surf.Point.x[ii].nor=vec;}
	for(int ii=0;ii<Surf.Point.N;ii++){Msh.eig.pmv(vec,Surf.Point.x[ii].crd);Surf.Point.x[ii].crd=vec;}
}
//void Surface::RdrCrSrf()
//{
//}
void Surface::delSurface()
{
	WF	= 0x0;
	smol= 0x0;
	//DDD.ClearMoldata();
	//Surf.ClearSurface();
}

//___________________________________
void MolSurf::BuildSurface()
{
	DDD.SetEigBasis();
	DDD.Get2EigBasis();	
	DDD.SetCubDiv();
	DDD.SetRolling();
	InitObject(Surf);
	Msh.InitMolData(DDD);
	Msh.InitSurface(Surf);
	Msh.SetPar();
	Msh.TrInit();
	Msh.Build();
	Msh.RefineMesh();
//	Msh.RefineMesh();
//	Msh.RefineMesh();
	Msh.JuggleMesh(1,0,Msh.Point.N);
	Msh.Ret2InitBas();
	Msh.DoAtomClr();	// задание параметров раскраски повехности

	Msh.FreeMolData(DDD);

	Msh.FreeSurface(Surf);
}

#endif