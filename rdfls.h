// ************************************************
//  ��������� ������-TAGSS-  (��� 1.0.0)
//  Triangulated Adaptive Grid of Smooth Surface
//	21 ��� 2005�
//  ��������
//  (C) DIMONTA Lab
// ************************************************

#ifndef _RDFLS_H
#define _RDFLS_H

#include "massiv.h"
#include "mlstrct.h"


void read2words(smschar &str, smschar &wrd1, smschar &wrd2);
void read2words(smschar &str, smpl_ms<smschar> &wrds);

bool ConfigRead(configpar &cnfpr);

bool fil2str(smschar &name,smpl_ms<smschar> &str); // ������ ��� ������� ���

bool s2dh(smpl_ms<smschar> &a, smpl_ms<smschar> &AtTp, ms1D<int> &tpind, ms1D<Vec3db> &xyz, ms1D<double> &Q);	//��� ������� ���������������������hin - ����

//bool s2dx(ms<mschar> &a, ms<mschar> &AtTp, ms<int> &tpind, ms<double> &xyz, ms<double> &Q);	//��� ������� ���������������������xyz - ����

bool str2data(smschar &name , smpl_ms<smschar> &AtTp, ms1D<int> &tpind, ms1D<Vec3db> &xyz, ms1D<double> &Q);	//��� ������� ���������������������mrk - ����

bool s2dm(smpl_ms<smschar> &a, smpl_ms<smschar> &AtTp, ms1D<int> &tpind, ms1D<Vec3db> &xyz, ms1D<double> &Q);	//��� ������� ���������������������mrk - ����

//bool s2dx(smpl_ms<smschar> &a, smpl_ms<smschar> &AtTp, ms1D<int> &tpind, ms1D<double> &xyz, ms1D<double> &Q);	//��� ������� ���������������������xyz - ����
bool s2dx(smpl_ms<smschar> &a, smpl_ms<smschar> &AtTp, ms1D<int> &tpind, ms1D<Vec3db> &xyz, ms1D<double> &Q);	//��� ������� ���������������������xyz - ����

bool s2d_pdb(smpl_ms<smschar> &a, smpl_ms<smschar> &AtTp, ms1D<int> &tpind, ms1D<Vec3db> &xyz, ms1D<double> &Q);	//��� ������� ���������������������pdb - ����
bool s2d_pdb2(smpl_ms<smschar> &a, smpl_ms<smschar> &AtTp, ms1D<int> &tpind, ms1D<Vec3db> &xyz, ms1D<double> &Q);	//��� ������� ���������������������pdb - ����

bool libread(smschar &name,smpl_ms<smschar> &AtTp,ms1D<double> &wdr);	// ������ ����� ���� ���.

bool GetCntlDt(smpl_ms<smschar> &str, solpar &A, grdpar &B,cntlpar &C, cappar &D);


void AmAcFill(aminotip &Acid, ms1D<double> &MMFF_RWDV);
#endif
