// ************************************************
//  ��������� ������-TAGSS-  (��� 1.0.0)
//  Triangulated Adaptive Grid of Smooth Surface
//	21 ��� 2005�
//  ��������
//  (C) DIMONTA Lab
// ************************************************

#ifndef _GLOBALS_H
#define _GLOBALS_H
#include "massiv.h"
#include "massivcpp.h"

	double pi	= 3.1415926535897932384626433832795;

	smschar InitFileName("surfPr.txt",11);

	smschar F_libName( "f.lib",6);

	smschar ConfigFileName( "surfpr.udf",11);

	double koeff, E_in,E_out;

	smpl_ms<smschar> AtTp;

	solpar Pr1;
	cappar Pr2;
	grdpar Pr3;
	cntlpar Pr4;

	ms1D<int> tpind;

	configpar	ConfPr;

	aminotip Acid;

	ms1D<double> MMFF_RWDV;

	/*smpl_ms<smschar> pdbamino;
	smpl_ms<smschar> pdbatom;
	smpl_ms<int> pdbmmff;
	/**/


#endif
