// ************************************************
//  ��������� ������-TAGSS-  (��� 1.0.0)
//  Triangulated Adaptive Grid of Smooth Surface
//	21 ��� 2005�
//  ��������
//  (C) DIMONTA Lab
// ************************************************

#ifndef _RDFLS_CPP
#define _RDFLS_CPP

#include <fstream>
#include "rdfls.h"
#include "globals.h"
using namespace std;


void read2words(smschar &str, smschar &wrd1, smschar &wrd2)
{
	int i,j;//k;

	for(i=0;((str.x[i]==' ')||(str.x[i]=='\t')||(str.x[i]=='\0'));i++);
	j	= i;
	for(;((str.x[i]!=' ')&&(str.x[i]!='\t')&&(str.x[i]!='\0'));i++);
	wrd1.pst(j,i,str);
	for(;((str.x[i]==' ')||(str.x[i]=='\t')||(str.x[i]=='\0'));i++);
	j	= i;
	for(;((str.x[i]!=' ')&&(str.x[i]!='\t')&&(str.x[i]!='\0'));i++);
	wrd2.pst(j,i,str);
}

void read2words(smschar &str, smpl_ms<smschar> &wrds)
{
	int i;//,j,k;
	bool ch;
	smschar wrd;
	wrd.sm(1);


	ch	= true;

	for(i=0;i<wrds.N;wrds.x[i++].N=0)
	wrds.N=0;
	i	= 0;

	wrd.N	= 0;
	for(i=0;i<str.N;i++)
	{
		ch	= ((str.x[i]!=' ')&&(str.x[i]!='\t')&&(str.x[i]!='\0'));
		if(ch)
		{
			wrd.add(str.x[i]);
		}
		else
		{
			if(wrd.N!=0)
			{
				wrd.add('\0');
				wrds.adc(wrd);
				wrd.N	= 0;
			}
		}
	}
}

bool ConfigRead(configpar &cnfpr)
{
	smpl_ms<smschar> KW;

	KW.init(33);

	KW.x[0].add("TITLE\0",6);
	KW.x[1].add("FILENAMES\0",10);
	KW.x[2].add("PROTNAME\0",9);
	KW.x[3].add("LIGNAME\0",8);
	KW.x[4].add("OUTNAME\0",8);
	KW.x[5].add("ISOUTFL\0",8);
	KW.x[6].add("SURFACE_CONSTRUCTION\0",21);
	KW.x[7].add("TRSIZE\0",7);
	KW.x[8].add("MAXTRSIZE\0",10);
	KW.x[9].add("ROLRADIUS\0",10);
	KW.x[10].add("SECROLRAD\0",11);
	KW.x[11].add("MINRADCRV\0",11);
	KW.x[12].add("INITVEC\0",9);
	KW.x[13].add("ADAPTMESH\0",11);
	KW.x[14].add("PROTLIG\0",9);
	KW.x[15].add("CAVENMBR\0",10);
	KW.x[16].add("VISUALIZATION\0",14);
	KW.x[17].add("ISVIZ\0",6);
	KW.x[18].add("SURFCLR\0",8);
	KW.x[19].add("CAVECLR\0",8);
	KW.x[20].add("ISATSRC\0",8);
	KW.x[21].add("ISATCVC\0",8);
	KW.x[22].add("SOLVENTION\0",11);
	KW.x[23].add("INRDIEL\0",8);
	KW.x[24].add("CAVDIEL\0",8);
	KW.x[25].add("OUTDIEL\0",8);
	KW.x[26].add("GBPARC\0",7);
	KW.x[27].add("SGBPAR1\0",8);
	KW.x[28].add("SGBPAR2\0",8);
	KW.x[29].add("ATOMS_TIPIZATION\0",17);
	KW.x[30].add("END\0",4);
	KW.x[31].add("REFINE\0",7);
	KW.x[32].add("VIZINER\0",8);

	int i,j,k,sz,m;
	bool ch,chj;
	Vec3db	atcl;

	sz	= sizeof(char);

	smpl_ms<smschar> str;
	smpl_ms<smschar> wrds;
	//smschar	wrd1(80);
	//smschar	wrd2(80);
	wrds.init(5);

	
	fil2str(ConfigFileName,str); // ������

	ms1Dint group;
	group.init(6);
	group.x[0]	= 0;
	group.x[1]	= 1;
	group.x[2]	= 6;
	group.x[3]	= 16;
	group.x[4]	= 22;
	group.x[5]	= 29;
	
	ms1Dint group0;
	group0.ad1(2,5,1);
	ms1Dint group1;
	group1.ad1(7,15,1);
	group1.add(31);
	ms1Dint group2;
	group2.ad1(17,21,1);
	group2.add(32);
	ms1Dint group3;
	group3.ad1(23,28,1);

	for(i=0;i<str.N;i++)
	{
		ch	= true;
		for(j=0;(j<group.N)&&(ch);j++)
		{
			ch	= !(memcmp(KW.x[group.x[j]].x,str.x[i].x,(KW.x[group.x[j]].N-1)*sz)==0);
		}
		j--;
		if (!ch)
		{
			i++;
			ch	=!(memcmp(KW.x[30].x,str.x[i].x,(KW.x[30].N-1)*sz)==0);
			if (ch)
			{	
				if (j==0)
				{
			//		i++;
			//		ch	=!(memcmp(KW.x[30].x,str.x[i].x,(KW.x[30].N-1)*sz)==0);
					for(;ch;i++)
					{
						ch	=!(memcmp(KW.x[30].x,str.x[i].x,(KW.x[30].N-1)*sz)==0);
					}
					i--;
				}else
				{

					for(;(ch&&i<str.N);i++)
					{
						read2words(str.x[i],wrds);
						if (wrds.N!=0)
						{
							ch	=!(memcmp(KW.x[30].x,wrds.x[0].x,(KW.x[30].N-1)*sz)==0);

							if(ch)
							{
								switch (j)
								{
								case 1:
									chj	= true;
									for(k=0;k<group0.N&&chj;k++)
									{
										chj	=!(memcmp(KW.x[group0.x[k]].x,wrds.x[0].x,(KW.x[group0.x[k]].N-1)*sz)==0);
									}
									k--;
									if(!chj)
									{
										switch (group0.x[k])
										{
										case 2:
											cnfpr.fnms.protname.pst(wrds.x[1]);
											break;
										case 3:
											cnfpr.fnms.ligname.pst(wrds.x[1]);
											break;
										case 4:
											cnfpr.fnms.outname.pst(wrds.x[1]);
											break;
										case 5:
											cnfpr.fnms.isoutfl=wrds.x[1].x[0];
											break;
										}
									}
									break;
								case 2:
									chj	= true;
									for(k=0;k<group1.N&&chj;k++)
									{
										chj	=!(memcmp(KW.x[group1.x[k]].x,wrds.x[0].x,(KW.x[group1.x[k]].N-1)*sz)==0);
									}
									k--;
									if(!chj)
									{
										switch (group1.x[k])
										{
										case 7:
											cnfpr.surfpar.trsize=atof(wrds.x[1].x);
											break;
										case 8:
											cnfpr.surfpar.maxtrsize=atof(wrds.x[1].x);
											break;
										case 9:
											cnfpr.surfpar.rolradius=atof(wrds.x[1].x);
											break;
										case 10:
											cnfpr.surfpar.secrolrad=atof(wrds.x[1].x);
											break;
										case 11:
											cnfpr.surfpar.minradcrv=atof(wrds.x[1].x);
											break;
										case 12:
											cnfpr.surfpar.in_thet=atof(wrds.x[1].x);
											cnfpr.surfpar.in_phi=atof(wrds.x[2].x);
											break;
										case 13:
											cnfpr.surfpar.adptmesh1=atof(wrds.x[1].x);
											cnfpr.surfpar.adptmesh2=atof(wrds.x[2].x);
											break;
										case 14:
											cnfpr.surfpar.protlig.pst(wrds.x[1]);
											break;
										case 15:
											cnfpr.surfpar.cavenmbr=atof(wrds.x[1].x);
											break;
										case 31:
											cnfpr.surfpar.refine=atoi(wrds.x[1].x);
											break;
										}
									}
									break;
								case 3:
									chj	= true;
									for(k=0;k<group2.N&&chj;k++)
									{
										chj	=!(memcmp(KW.x[group2.x[k]].x,wrds.x[0].x,(KW.x[group2.x[k]].N-1)*sz)==0);
									}
									k--;
									if(!chj)
									{
										switch (group2.x[k])
										{
										case 17:
											cnfpr.viz.isvrml	= wrds.x[1].x[0];
											break;
										case 18:
											m	= wrds.N-1;
											if ((3*(int(m/3)))!= m ) 
											{
												cout<<"WRONG INPUT DATA!"<<endl;
												cout<<"Please check the SURFCLR fiedls. Quantity of numbers must be multiple by 3. In accordance with RBG pallete."<<endl;
												cout<<"Programm is stoped."<<endl;
												exit(0);
											}
											m/=3;
											cnfpr.viz.surfclr.init(m);
											for(k=0;k<m;k++)
											{
												atcl.x[0]	= atof(wrds.x[3*k+1].x);
												atcl.x[1]	= atof(wrds.x[3*k+2].x);
												atcl.x[2]	= atof(wrds.x[3*k+3].x);
												cnfpr.viz.surfclr.x[k]	= atcl;
											}
											break;
										case 19:
											m	= wrds.N-1;
											if ((3*(int(m/3)))!= m ) 
											{
												cout<<"WRONG INPUT DATA!"<<endl;
												cout<<"Please check the CAVECLR fiedls. Quantity of numbers must be multiple by 3. In accordance with RBG pallete."<<endl;
												cout<<"Programm is stoped."<<endl;
												exit(0);
											}
											m/=3;
											cnfpr.viz.caveclr.init(m);
											for(k=0;k<m;k++)
											{
												atcl.x[0]	= atof(wrds.x[3*k+1].x);
												atcl.x[1]	= atof(wrds.x[3*k+2].x);
												atcl.x[2]	= atof(wrds.x[3*k+3].x);
												cnfpr.viz.caveclr.x[k]	= atcl;
											}
											break;
										case 20:
											cnfpr.viz.isatsrc=wrds.x[1].x[0];
											break;
										case 21:
											cnfpr.viz.isatcvc=wrds.x[1].x[0];
											break;
										case 32:
											cnfpr.viz.viziner	= wrds.x[1].x[0];
											break;
										}
									}
									break;
								case 4:
									chj	= true;
									for(k=0;k<group3.N&&chj;k++)
									{
										chj	=!(memcmp(KW.x[group3.x[k]].x,wrds.x[0].x,(KW.x[group3.x[k]].N-1)*sz)==0);
									}
									k--;
									if(!chj)
									{
										switch (group3.x[k])
										{
										case 23:
											cnfpr.solvtn.eps_in	= atof(wrds.x[1].x);										
											break;
										case 24:
											cnfpr.solvtn.eps_cv	= atof(wrds.x[1].x);										
											break;
										case 25:
											cnfpr.solvtn.eps_out= atof(wrds.x[1].x);										
											break;
										case 26:
											cnfpr.solvtn.c	= atof(wrds.x[1].x);										
											break;
										case 27:
											cnfpr.solvtn.sgb1= atof(wrds.x[1].x);										
											break;
										case 28:
											cnfpr.solvtn.sgb2= atof(wrds.x[1].x);										
											break;
										}
									}
									break;
								case 5:
									cnfpr.atomparam.AtNm.adc(wrds.x[0]);
									atcl.x[0]	= atof(wrds.x[1].x);
									cnfpr.atomparam.r_wdw.add(atcl.x[0]);
									atcl.x[0]	= atof(wrds.x[2].x);
									atcl.x[1]	= atof(wrds.x[3].x);
									atcl.x[2]	= atof(wrds.x[4].x);
									cnfpr.atomparam.AtColor.add(atcl);
									break;
								}
							}
						}

					}
					i--;

					
				}				
			}
		}
		
	}
	
	return true;
}


bool fil2str(smschar &name,smpl_ms<smschar> &str) // ������
{		// ��� ���� �� ������ �'name'  ���� ���'str'
		// ��������, �� ��� ������������ ���, ��� , �� �� � ��� ���.
	char ch;	// �������������

	smschar s_;
	s_.sm(80);
	//str.dN	= 500;	// ������������, � ������������� ����� � �� �� ��������
	str.N=0;		// ������������� � 'dN' ����
	// ��� � ��������� str.
	ifstream io;			// ������������ 
	io.open(name.x,ios::in);// ����� ���� 'name'
	if (!io.is_open())		// ��� ��
	{
		cout<<"File "<<name.x<<" is not open!"<<endl;	
		return false;
	}else
	{
		io.unsetf(ios::skipws);	// �� �� ����� ��������� (�� ���� '\0')
		while (io.eof()!=1)		// ���� �� � �����������
		{
			s_.N=0;
			io>>ch;			// ���� ��� � ��� �'ch'
			if (io.eof()!=1)
			{
				while ((ch!='\n')&&(io.eof()!=1)) // ���� �� � ������� �����������
				{
					s_.add(ch);	// ��� �������� 's_'
					io>>ch;		// ���� �������� � ��� �'ch'
				}
				s_.add('\0');
				ch	='M';		// ���� ���� 'ch' �� �� ������.				
				if (s_.N!=0)
				{
					if (str.mN<str.N+2) str.adm_(1000);
					str.adc(s_);	// ���� ��� 's_' ���� ���'str'
				}
			}
		}
		io.close();		// ��� ��		
		// ������.
	}
	return true;
}


bool libread(smschar &name,smpl_ms<smschar> &AtTp,ms1D<double> &wdr)	// ������ ����� ���� ���.
{
	double a;
	smschar tp(80);
	smpl_ms<smschar> str;
	smpl_ms<smschar> KW;
	int N_KW=6;
	KW.sm(N_KW);
	KW.N	= N_KW;

	KW.x[0].add("TITLE\0",6);
	KW.x[1].add("TOPPHYSCON\0",11);
	KW.x[2].add("TOPVERSION\0",11);
	KW.x[3].add("ATOMTYPENAME\0",13);
	KW.x[4].add("END\0",4);
	KW.x[5].add("#\0",2);  //�����
	
	fil2str(name,str); // ��� ����� ������� ���(��� ���� ����.)

	int i,j,k,sz;
	char ch	= true;
	sz	= sizeof(char);
	
	for(i=0;(i<str.N)&&(ch);i++)
	{
		ch	= !(memcmp(KW.x[3].x,str.x[i].x,(KW.x[3].N-1)*sz)==0);//||(KW.x[3].N!=str.x[i].N);
	}
	
	i+=3;
	
	ch	= !(memcmp(KW.x[4].x,str.x[i].x,(KW.x[4].N-1)*sz)==0);//||(KW.x[4].N!=str.x[i].N);

	for(;(i<str.N)&&(ch);i++)
	{
		ch	= !(memcmp(KW.x[4].x,str.x[i].x,(KW.x[4].N-1)*sz)==0);//||(KW.x[4].N!=str.x[i].N);
		if (ch)
		{
			j	= 0;
			for (j=0;(str.x[i].x[j]==' ')||(str.x[i].x[j]=='\t')||(str.x[i].x[j]=='\0');j++); // �������� ������
			k	= j;
			for (;(str.x[i].x[j]!=' ')&&(str.x[i].x[j]!='\t')&&(str.x[i].x[j]!='\0');j++); // ������������
			j	-=k;
			tp.add(str.x[i].x+k,j);
			tp.add("\0",1);
			j	+=k;

			
			AtTp.adc(tp); // ���� ��������

			tp.N= 0;

			for (;(str.x[i].x[j]==' ')||(str.x[i].x[j]=='\t')||(str.x[i].x[j]=='\0');j++); // �������� ������
			k	= j;
			for (;(str.x[i].x[j]!=' ')&&(str.x[i].x[j]!='\t')&&(str.x[i].x[j]!='\0');j++); // ������������
			j	-=k;
			tp.add(str.x[i].x+k,j);
			tp.add("\0",1);
			j	+=k;

			a	= atof(tp.x);
			wdr.add(a); // ���� ���� ��

			tp.N= 0;
		}
	}
	return true;
}

bool str2data(smschar &name, smpl_ms<smschar> &AtTp, ms1D<int> &tpind, ms1D<Vec3db> &xyz, ms1D<double> &Q)	//��� ������� ���������������������mrk - ����
{
	smpl_ms<smschar> str;
	//smpl_ms<smschar> res;
	bool ch;
	char *pch;
	//int sz;

	//sz	= sizeof(char);

	/*res.init(6);
	res.x[0].add("xyz",4);
	res.x[1].add("mrk",4);
	res.x[2].add("pdb",4);*/

	fil2str(name,str);

	//ch	= !(memcmp(res.x[0].x,name.x+(name.N-4),4*sz)==0);

	pch	= name.x+(name.N-4);
	ch	= ((pch[0]=='x')||(pch[0]=='X'))&&((pch[1]=='y')||(pch[1]=='Y'))&&((pch[2]=='z')||(pch[2]=='Z'));

	if(!ch)
	{
		//ch	= !(memcmp(res.x[1].x,name.x+(name.N-4),4*sz)==0);
		
		ch	= ((pch[0]=='m')||(pch[0]=='M'))&&((pch[1]=='r')||(pch[1]=='R'))&&((pch[2]=='k')||(pch[2]=='K'));
		if(!ch)
		{
			//ch	= !(memcmp(res.x[2].x,name.x+(name.N-4),4*sz)==0);
			ch	= ((pch[0]=='p')||(pch[0]=='P'))&&((pch[1]=='d')||(pch[1]=='D'))&&((pch[2]=='b')||(pch[2]=='B'));
			if(!ch)
			{
				return false;
			}
			s2d_pdb2(str,AtTp,tpind,xyz,Q);
			return true;
		}
		s2dm(str,AtTp,tpind,xyz,Q);
		return true;
	}

	s2dx(str,AtTp,tpind,xyz,Q);
	//s2dm(str,AtTp,_tpind,_xyz,_Q);

	return true;
}

bool str2data(smschar &pname,smschar &lname, smpl_ms<smschar> &AtTp, ms1D<int> &tpind, ms1D<Vec3db> &xyz, ms1D<double> &Q)	//��� ������� ���������������������mrk - ����
{
	
	ms1D<int> tpind_L;
	ms1D<Vec3db> xyz_L;
	ms1D<double> Q_L;


	str2data(pname,AtTp,tpind,xyz,Q);
	str2data(lname,AtTp,tpind_L,xyz_L,Q_L);

	tpind.add(tpind_L);
	xyz.add(xyz_L);
	Q.add(Q_L);

	return true;
}

/*
bool s2dh(ms<mschar> &a, ms<mschar> &AtTp, ms1D<int> &tpind, ms1D<double> &xyz, ms1D<double> &Q)	//��� ������� ���������������������hin - ����
{
	ms<char> tp(100);
	ms<char> q(100);
	bool cycl,cycl2;
	int i,j,k,ia,jo;
	xyz.sm(3*a.N);
	Q.sm(a.N);
	double r;
	i	= -1;
	jo	= 0;
	cycl2	= true;
	tpind.N= 0;
	for(ia=0;(ia<a.N)&&(cycl2);ia++)
	{		
		for(j=0;((a.x[ia].x[j]==' ')||(a.x[ia].x[j]=='\t')||(a.x[ia].x[j]=='\0'));j++);// ����� �������� �������������
		k	= j;
		for( ; ((a.x[ia].x[j]!=' ')&&(a.x[ia].x[j]!='\t')&&(a.x[ia].x[j]!='\0')) ; j++);	// ���� � �����������������������
		j	-= k;
		memcpy(tp.x,a.x[ia].x+k,j*tp.sz);	// ����� ���� ��� ��������
		tp.N= j;
		tp.x[tp.N++]='\0';
		j	+= k;

		cycl	= (memcmp(tp.x,"mol",4*tp.sz)!=0)||(tp.N!=4);//  ����������

		if (!cycl)
		{
			
			for(;(ia<a.N)&&(cycl2);ia++)
			{		
				for(j=0;((a.x[ia].x[j]==' ')||(a.x[ia].x[j]=='\t')||(a.x[ia].x[j]=='\0'));j++);// ����� �������� �������������
				k	= j;
				for( ; ((a.x[ia].x[j]!=' ')&&(a.x[ia].x[j]!='\t')&&(a.x[ia].x[j]!='\0')) ; j++);	// ���� � �����������������������
				j	-= k;
				memcpy(tp.x,a.x[ia].x+k,j*tp.sz);	// ����� ���� ��� ��������
				tp.N= j;
				tp.x[tp.N++]='\0';
				j	+= k;

				cycl	= true;

				cycl	= (memcmp(tp.x,"atom",5*tp.sz)!=0)||(tp.N!=5);//  ����������
				
				if (!cycl)
				{
					for(;((a.x[ia].x[j]==' ')||(a.x[ia].x[j]=='\t')||(a.x[ia].x[j]=='\0'));j++);// ����� �������� �������������
					for(;((a.x[ia].x[j]!=' ')&&(a.x[ia].x[j]!='\t')&&(a.x[ia].x[j]!='\0')) ; j++);	// ���� � �����������������������
					for(;((a.x[ia].x[j]==' ')||(a.x[ia].x[j]=='\t')||(a.x[ia].x[j]=='\0'));j++);// ����� �������� �������������
					for(; ((a.x[ia].x[j]!=' ')&&(a.x[ia].x[j]!='\t')&&(a.x[ia].x[j]!='\0')) ; j++);	// ���� � �����������������������
					for(;((a.x[ia].x[j]==' ')||(a.x[ia].x[j]=='\t')||(a.x[ia].x[j]=='\0'));j++);// ����� �������� �������������
					k	= j;
					for(;((a.x[ia].x[j]!=' ')&&(a.x[ia].x[j]!='\t')&&(a.x[ia].x[j]!='\0')) ; j++);	// ���� � �����������������������
					j	-= k;
					memcpy(tp.x,a.x[ia].x+k,j*tp.sz);	// ����� ���� ��� ��������
					tp.N= j;
					tp.x[tp.N++]='\0';
					j	+= k;
					cycl	= true;
					for(k=0;(k<AtTp.N)&&(cycl);k++)	// ���� � �����
					{
						cycl	= (memcmp(tp.x,AtTp.x[k].x,AtTp.x[k].N*tp.sz)!=0)||(tp.N!=AtTp.x[k].N);//  ����������
					}
					if (!cycl) // �� ����� ���� �
					{
						for(;((a.x[ia].x[j]==' ')||(a.x[ia].x[j]=='\t')||(a.x[ia].x[j]=='\0'));j++);// ����� �������� �������������
						for(;((a.x[ia].x[j]!=' ')&&(a.x[ia].x[j]!='\t')&&(a.x[ia].x[j]!='\0')) ; j++);	// ���� � �����������������������
						for(;((a.x[ia].x[j]==' ')||(a.x[ia].x[j]=='\t')||(a.x[ia].x[j]=='\0'));j++);// ����� �������� �������������
						for(;((a.x[ia].x[j]!=' ')&&(a.x[ia].x[j]!='\t')&&(a.x[ia].x[j]!='\0')) ; j++);	// ���� � �����������������������
						
						i++;
						k--;
						tpind.add(k);	// ��� ��� �� ���

						for(;((a.x[ia].x[j]==' ')||(a.x[ia].x[j]=='\t')||(a.x[ia].x[j]=='\0'));j++);// ����� �������� �������������
						k	= j;			
						for(;((a.x[ia].x[j]!=' ')&&(a.x[ia].x[j]!='\t')&&(a.x[ia].x[j]!='\0'));j++);	// ���� � �����������������������
						j	-= k;
						memcpy(q.x,a.x[ia].x+k,j*q.sz);	// ����� ���� ��� ��������
						q.N	= j;
						q.x[q.N++]	= '\0';
						r	= atof(q.x);
						Q.add(r);
						j	+= k;
						
						for(;((a.x[ia].x[j]==' ')||(a.x[ia].x[j]=='\t')||(a.x[ia].x[j]=='\0'));j++);// ����� �������� �������������
						k	= j;			
						for(;((a.x[ia].x[j]!=' ')&&(a.x[ia].x[j]!='\t')&&(a.x[ia].x[j]!='\0'));j++);	// ���� � �����������������������
						j	-= k;
						memcpy(q.x,a.x[ia].x+k,j*q.sz);	// ����� ���� ��� ��������
						q.N	= j;
						q.x[q.N++]	= '\0';
						r	= atof(q.x);
						xyz.add(r);
						j	+= k;
						
						for(;((a.x[ia].x[j]==' ')||(a.x[ia].x[j]=='\t')||(a.x[ia].x[j]=='\0'));j++);// ����� �������� �������������
						k	= j;			
						for(;((a.x[ia].x[j]!=' ')&&(a.x[ia].x[j]!='\t')&&(a.x[ia].x[j]!='\0'));j++);	// ���� � �����������������������
						j	-= k;
						memcpy(q.x,a.x[ia].x+k,j*q.sz);	// ����� ���� ��� ��������
						q.N	= j;
						q.x[q.N++]	= '\0';
						r	= atof(q.x);
						xyz.add(r);
						j	+= k;
						
						for(;((a.x[ia].x[j]==' ')||(a.x[ia].x[j]=='\t')||(a.x[ia].x[j]=='\0'));j++);// ����� �������� �������������
						k	= j;			
						for(;((a.x[ia].x[j]!=' ')&&(a.x[ia].x[j]!='\t')&&(a.x[ia].x[j]!='\0'));j++);	// ���� � �����������������������
						j	-= k;
						memcpy(q.x,a.x[ia].x+k,j*q.sz);	// ����� ���� ��� ��������
						q.N	= j;
						q.x[q.N++]	= '\0';
						r	= atof(q.x);
						xyz.add(r);
						j	+= k;
					}					
				}else
				{
					cycl2	= (memcmp(tp.x,"endmol",9*tp.sz)!=0);//  ����������
				}
			}
		}

	}

//	xyz.two(3,tpind.N);
	return true;
}
*/
/*
bool s2dx(ms<mschar> &a, ms<mschar> &AtTp, ms<int> &tpind, ms<double> &xyz, ms<double> &Q)	//��� ������� ���������������������xyz - ����
{
	ms<char> tp(80);
	ms<char> q(30);
	double r;
	bool cycl;
	int i,j,k,ia,jo;
	xyz.two(a.N,3);
	Q.one(a.N);
	Q.N		= xyz.N = 0;
	i	= -1;
	jo	= 0;
	tpind.N	= 0;
	for(ia=0;ia<a.N;ia++)
	{		
		for(j=0;((a.x[ia].x[j]==' ')||(a.x[ia].x[j]=='\t')||(a.x[ia].x[j]=='\0'));j++);// ����� �������� �������������
		k	= j;
		for( ; ((a.x[ia].x[j]!=' ')&&(a.x[ia].x[j]!='\t')&&(a.x[ia].x[j]!='\0')) ; j++);	// ���� � �����������������������
		j	-= k;
		memcpy(tp.x,a.x[ia].x+k,j*tp.sz);	// ����� ���� ��� ��������
		tp.N= j;
		tp.x[tp.N++]='\0';
		j	+= k;
		cycl	= true;
		for(k=0;(k<AtTp.N)&&(cycl);k++)	// ���� � �����
		{
			cycl	= (memcmp(tp.x,AtTp.x[k].x,AtTp.x[k].N*tp.sz)!=0)||(tp.N!=AtTp.x[k].N);//  ����������
		}
		if (!cycl) // �� ����� ���� �
		{
			i++;
			k--;
			tpind.add(k);	// ��� ��� �� ���

			for(;((a.x[ia].x[j]==' ')||(a.x[ia].x[j]=='\t')||(a.x[ia].x[j]=='\0'));j++);// ����� �������� �������������
			k	= j;			
			for(;((a.x[ia].x[j]!=' ')&&(a.x[ia].x[j]!='\t')&&(a.x[ia].x[j]!='\0'));j++);	// ���� � �����������������������
			j	-= k;
			memcpy(q.x,a.x[ia].x+k,j*q.sz);	// ����� ���� ��� ��������
			q.N	= j;
			q.x[q.N++]	= '\0';
			r	= atof(q.x);
			xyz.add(r);
			j	+= k;

			for(;((a.x[ia].x[j]==' ')||(a.x[ia].x[j]=='\t')||(a.x[ia].x[j]=='\0'));j++);// ����� �������� �������������
			k	= j;			
			for(;((a.x[ia].x[j]!=' ')&&(a.x[ia].x[j]!='\t')&&(a.x[ia].x[j]!='\0'));j++);	// ���� � �����������������������
			j	-= k;
			memcpy(q.x,a.x[ia].x+k,j*q.sz);	// ����� ���� ��� ��������
			q.N	= j;
			q.x[q.N++]	= '\0';
			r	= atof(q.x);
			xyz.add(r);
			j	+= k;

			for(;((a.x[ia].x[j]==' ')||(a.x[ia].x[j]=='\t')||(a.x[ia].x[j]=='\0'));j++);// ����� �������� �������������
			k	= j;			
			for(;((a.x[ia].x[j]!=' ')&&(a.x[ia].x[j]!='\t')&&(a.x[ia].x[j]!='\0'));j++);	// ���� � �����������������������
			j	-= k;
			memcpy(q.x,a.x[ia].x+k,j*q.sz);	// ����� ���� ��� ��������
			q.N	= j;
			q.x[q.N++]	= '\0';
			r	= atof(q.x);
			xyz.add(r);
			j	+= k;

			for(;((a.x[ia].x[j]==' ')||(a.x[ia].x[j]=='\t')||(a.x[ia].x[j]=='\0'));j++);// ����� �������� �������������
			k	= j;			
			for(;((a.x[ia].x[j]!=' ')&&(a.x[ia].x[j]!='\t')&&(a.x[ia].x[j]!='\0'));j++);	// ���� � �����������������������
			j	-= k;
			memcpy(q.x,a.x[ia].x+k,j*q.sz);	// ����� ���� ��� ��������
			q.N	= j;
			q.x[q.N++]	= '\0';
			r	= atof(q.x);
			Q.add(r);
			j	+= k;
		}

	}
	xyz.two(tpind.N,3);
	xyz.tns();	// ��������;
	Q.one(tpind.N);
	return true;
}
*/

bool s2dm(smpl_ms<smschar> &a, smpl_ms<smschar> &AtTp, ms1D<int> &tpind, ms1D<Vec3db> &xyz, ms1D<double> &Q)	//��� ������� ���������������������xyz - ����
{
	smschar tp(80);
	smschar q(30);
	double r;
	bool cycl;
	int i,j,k,ia,jo,sz;
	sz	= sizeof(char);
	Vec3db rv;

	i	= -1;
	jo	= 0;
	tpind.N	= 0;

	int N_str;

	ia=2;

	for(j=0;((a.x[ia].x[j]==' ')||(a.x[ia].x[j]=='\t')||(a.x[ia].x[j]=='\0'));j++);// ����� �������� �������������
	k	= j;
	for( ; ((a.x[ia].x[j]!=' ')&&(a.x[ia].x[j]!='\t')&&(a.x[ia].x[j]!='\0')) ; j++);	// ���� � �����������������������
	j	-= k;
	if(tp.mN<=j)tp.adm(j);
	memcpy(tp.x,a.x[ia].x+k,j*sz);	// ����� ���� ��� ��������
	tp.N= j;
	tp.x[tp.N++]='\0';
	N_str	= atoi(tp.x);

	xyz.sm(N_str);
	Q.sm(N_str);
	Q.N		= xyz.N = 0;



		
	for(ia=3;ia<N_str+3;ia++)
	{	
	
		for(j=0;((a.x[ia].x[j]==' ')||(a.x[ia].x[j]=='\t')||(a.x[ia].x[j]=='\0'));j++);// ����� �������� �������������
		k	= j;
		for( ; ((a.x[ia].x[j]!=' ')&&(a.x[ia].x[j]!='\t')&&(a.x[ia].x[j]!='\0')) ; j++);	// ���� � �����������������������
		j	-= k;
		if(q.mN<=j)q.adm(j);
		memcpy(q.x,a.x[ia].x+k,j*sz);	// ����� ���� ��� ��������
		q.N	= j;
		q.x[q.N++]	= '\0';
		rv.x[0]	= atof(q.x);
		j	+= k;

		for(;((a.x[ia].x[j]==' ')||(a.x[ia].x[j]=='\t')||(a.x[ia].x[j]=='\0'));j++);// ����� �������� �������������
		k	= j;			
		for(;((a.x[ia].x[j]!=' ')&&(a.x[ia].x[j]!='\t')&&(a.x[ia].x[j]!='\0'));j++);	// ���� � �����������������������
		j	-= k;
		if(q.mN<=j)q.adm(j);
		memcpy(q.x,a.x[ia].x+k,j*sz);	// ����� ���� ��� ��������
		q.N	= j;
		q.x[q.N++]	= '\0';
		rv.x[1]	= atof(q.x);
		j	+= k;
		
		for(;((a.x[ia].x[j]==' ')||(a.x[ia].x[j]=='\t')||(a.x[ia].x[j]=='\0'));j++);// ����� �������� �������������
		k	= j;			
		for(;((a.x[ia].x[j]!=' ')&&(a.x[ia].x[j]!='\t')&&(a.x[ia].x[j]!='\0'));j++);	// ���� � �����������������������
		j	-= k;
		if(q.mN<=j)q.adm(j);
		memcpy(q.x,a.x[ia].x+k,j*sz);	// ����� ���� ��� ��������
		q.N	= j;
		q.x[q.N++]	= '\0';
		rv.x[2]	= atof(q.x);
		j	+= k;

		
		for( ;((a.x[ia].x[j]==' ')||(a.x[ia].x[j]=='\t')||(a.x[ia].x[j]=='\0'));j++);// ����� ����� �������������
		for( ; ((a.x[ia].x[j]!=' ')&&(a.x[ia].x[j]!='\t')&&(a.x[ia].x[j]!='\0')) ; j++);	// ���� � �����������������������

		for( ;((a.x[ia].x[j]==' ')||(a.x[ia].x[j]=='\t')||(a.x[ia].x[j]=='\0'));j++);// ����� ����� �������������
		for( ; ((a.x[ia].x[j]!=' ')&&(a.x[ia].x[j]!='\t')&&(a.x[ia].x[j]!='\0')) ; j++);	// ���� � �����������������������

		for( ;((a.x[ia].x[j]==' ')||(a.x[ia].x[j]=='\t')||(a.x[ia].x[j]=='\0'));j++);// ����� ����� �������������
		for( ; ((a.x[ia].x[j]!=' ')&&(a.x[ia].x[j]!='\t')&&(a.x[ia].x[j]!='\0')) ; j++);	// ���� � �����������������������

		for( ;((a.x[ia].x[j]==' ')||(a.x[ia].x[j]=='\t')||(a.x[ia].x[j]=='\0'));j++);// ����� ����� �������������
		for( ; ((a.x[ia].x[j]!=' ')&&(a.x[ia].x[j]!='\t')&&(a.x[ia].x[j]!='\0')) ; j++);	// ���� � �����������������������

		for( ;((a.x[ia].x[j]==' ')||(a.x[ia].x[j]=='\t')||(a.x[ia].x[j]=='\0'));j++);// ����� ����� �������������
		k	= j;
		for( ; ((a.x[ia].x[j]!=' ')&&(a.x[ia].x[j]!='\t')&&(a.x[ia].x[j]!='\0')) ; j++);	// ���� � �����������������������
		j	-= k;
		if(tp.mN<=j)tp.adm(j);
		memcpy(tp.x,a.x[ia].x+k,j*sz);	// ����� ���� ��� ��������
		/*!!!tp.N= j;*/
		tp.N= 1;
		tp.x[tp.N++]='\0';
		j	+= k;

		cycl	= true;
		for(k=0;(k<AtTp.N)&&(cycl);k++)	// ���� � �����
		{
			cycl	= (memcmp(tp.x,AtTp.x[k].x,AtTp.x[k].N*sz)!=0)||(tp.N!=AtTp.x[k].N);//  ����������
		}
		if (!cycl) // �� ����� ���� �
		{
			i++;
			k--;
			tpind.add(k);	// ��� ��� �� ���

			xyz.add(rv);

			for( ;((a.x[ia].x[j]==' ')||(a.x[ia].x[j]=='\t')||(a.x[ia].x[j]=='\0'));j++);// ����� ����� �������������
			for( ; ((a.x[ia].x[j]!=' ')&&(a.x[ia].x[j]!='\t')&&(a.x[ia].x[j]!='\0')) ; j++);	// ���� � �����������������������

			for(;((a.x[ia].x[j]==' ')||(a.x[ia].x[j]=='\t')||(a.x[ia].x[j]=='\0'));j++);// ����� �������� �������������
			k	= j;			
			for(;((a.x[ia].x[j]!=' ')&&(a.x[ia].x[j]!='\t')&&(a.x[ia].x[j]!='\0'));j++);	// ���� � �����������������������
			j	-= k;
			if(q.mN<=j)q.adm(j);
			memcpy(q.x,a.x[ia].x+k,j*sz);	// ����� ���� ��� ��������
			q.N	= j;
			q.x[q.N++]	= '\0';
			r	= atof(q.x);
			Q.add(r);
			j	+= k;

		}
	}
	return true;
}


bool s2d_pdb(smpl_ms<smschar> &a, smpl_ms<smschar> &AtTp, ms1D<int> &tpind, ms1D<Vec3db> &xyz, ms1D<double> &Q)	//��� ������� ���������������������pdb - ����
{
	smschar tp(80);
	smschar q(30);
	smschar atom(5);
	//double r;
	bool cycla,cycl;
	int i,j,k,ia,jo,sz;
	sz	= sizeof(char);
	Vec3db rv;


	i	= -1;
	jo	= 0;
	tpind.N	= 0;

	atom.add("ATOM\0",5);
	for(ia=0;ia<a.N;ia++)
	{
		for(j=0;((a.x[ia].x[j]==' ')||(a.x[ia].x[j]=='\t')||(a.x[ia].x[j]=='\0'));j++);// ����� �������� �������������
		k	= j;
		for( ; ((a.x[ia].x[j]!=' ')&&(a.x[ia].x[j]!='\t')&&(a.x[ia].x[j]!='\0')) ; j++);	// ���� � �����������������������
		j	-= k;
		if(tp.mN<=j)tp.adm(j);
		memcpy(tp.x,a.x[ia].x+k,j*sz);	// ����� ���� ��� ��������
		tp.N= j;
		tp.x[tp.N++]='\0';
		j	+= k;

		cycla	= (memcmp(tp.x,atom.x,5*sz)!=0)||(tp.N!=5);//  ����������
		if (!cycla) // �� ����� ���� �
		{
			for( ;((a.x[ia].x[j]==' ')||(a.x[ia].x[j]=='\t')||(a.x[ia].x[j]=='\0'));j++);// ����� ����� �������������
			for( ; ((a.x[ia].x[j]!=' ')&&(a.x[ia].x[j]!='\t')&&(a.x[ia].x[j]!='\0')) ; j++);	// ���� � �����������������������

			for( ;((a.x[ia].x[j]==' ')||(a.x[ia].x[j]=='\t')||(a.x[ia].x[j]=='\0'));j++);// ����� �������� �������������
			k	= j;
			for( ; ((a.x[ia].x[j]!=' ')&&(a.x[ia].x[j]!='\t')&&(a.x[ia].x[j]!='\0')) ; j++);	// ���� � �����������������������
			j	-= k;
			if(tp.mN<=j)tp.adm(j);
			memcpy(tp.x,a.x[ia].x+k,j*sz);	// ����� ���� ��� ��������
			/*!!!tp.N= j;*/
			tp.N= 1;
			tp.x[tp.N++]='\0';
			j	+= k;
			cycl	= true;
			for(k=0;(k<AtTp.N)&&(cycl);k++)	// ���� � �����
			{
				cycl	= (memcmp(tp.x,AtTp.x[k].x,AtTp.x[k].N*sz)!=0)||(tp.N!=AtTp.x[k].N);//  ����������
			}

			if (!cycl) // �� ����� ���� �
			{
				i++;
				k--;
				tpind.add(k);	// ��� ��� �� ���

				for( ;((a.x[ia].x[j]==' ')||(a.x[ia].x[j]=='\t')||(a.x[ia].x[j]=='\0'));j++);// ����� ����� �������������
				for( ; ((a.x[ia].x[j]!=' ')&&(a.x[ia].x[j]!='\t')&&(a.x[ia].x[j]!='\0')) ; j++);	// ���� � �����������������������

				for( ;((a.x[ia].x[j]==' ')||(a.x[ia].x[j]=='\t')||(a.x[ia].x[j]=='\0'));j++);// ����� ����� �������������
				for( ; ((a.x[ia].x[j]!=' ')&&(a.x[ia].x[j]!='\t')&&(a.x[ia].x[j]!='\0')) ; j++);	// ���� � �����������������������

				for(;((a.x[ia].x[j]==' ')||(a.x[ia].x[j]=='\t')||(a.x[ia].x[j]=='\0'));j++);// ����� �������� �������������
				k	= j;
				for( ; ((a.x[ia].x[j]!=' ')&&(a.x[ia].x[j]!='\t')&&(a.x[ia].x[j]!='\0')) ; j++);	// ���� � �����������������������
				j	-= k;
				if(q.mN<=j)q.adm(j);
				memcpy(q.x,a.x[ia].x+k,j*sz);	// ����� ���� ��� ��������
				q.N	= j;
				q.x[q.N++]	= '\0';
				rv.x[0]	= atof(q.x);
				j	+= k;

				for(;((a.x[ia].x[j]==' ')||(a.x[ia].x[j]=='\t')||(a.x[ia].x[j]=='\0'));j++);// ����� �������� �������������
				k	= j;			
				for(;((a.x[ia].x[j]!=' ')&&(a.x[ia].x[j]!='\t')&&(a.x[ia].x[j]!='\0'));j++);	// ���� � �����������������������
				j	-= k;
				if(q.mN<=j)q.adm(j);
				memcpy(q.x,a.x[ia].x+k,j*sz);	// ����� ���� ��� ��������
				q.N	= j;
				q.x[q.N++]	= '\0';
				rv.x[1]	= atof(q.x);
				j	+= k;
				
				for(;((a.x[ia].x[j]==' ')||(a.x[ia].x[j]=='\t')||(a.x[ia].x[j]=='\0'));j++);// ����� �������� �������������
				k	= j;			
				for(;((a.x[ia].x[j]!=' ')&&(a.x[ia].x[j]!='\t')&&(a.x[ia].x[j]!='\0'));j++);	// ���� � �����������������������
				j	-= k;
				if(q.mN<=j)q.adm(j);
				memcpy(q.x,a.x[ia].x+k,j*sz);	// ����� ���� ��� ��������
				q.N	= j;
				q.x[q.N++]	= '\0';
				rv.x[2]	= atof(q.x);
				j	+= k;

				xyz.add(rv);
			}
		}
	}

	Q.init(0,xyz.N);
	Q.N	= xyz.N;

	return true;
}

bool s2d_pdb2(smpl_ms<smschar> &a, smpl_ms<smschar> &AtTp, ms1D<int> &tpind, ms1D<Vec3db> &xyz, ms1D<double> &Q)	//��� ������� ���������������������pdb - ����
{
	smschar tp(80);
	smschar q(30);
	smschar atom(5);
	//double r;
	bool cycla,cycl;
	int i,j,k,ia,jo,sz;
	sz	= sizeof(char);
	Vec3db rv;


	i	= -1;
	jo	= 0;
	tpind.N	= 0;

	atom.add("ATOM\0",5);
	for(ia=0;ia<a.N;ia++)
	{
		for(j=0;((a.x[ia].x[j]==' ')||(a.x[ia].x[j]=='\t')||(a.x[ia].x[j]=='\0'));j++);// ����� �������� �������������
		k	= j;
		for( ; ((a.x[ia].x[j]!=' ')&&(a.x[ia].x[j]!='\t')&&(a.x[ia].x[j]!='\0')) ; j++);	// ���� � �����������������������
		j	-= k;
		if(tp.mN<=j)tp.adm(j);
		memcpy(tp.x,a.x[ia].x+k,j*sz);	// ����� ���� ��� ��������
		tp.N= j;
		tp.x[tp.N++]='\0';
		j	+= k;

		cycla	= (memcmp(tp.x,atom.x,5*sz)!=0)||(tp.N!=5);//  ����������
		if (!cycla) // �� ����� ���� �
		{
			/*for( ;((a.x[ia].x[j]==' ')||(a.x[ia].x[j]=='\t')||(a.x[ia].x[j]=='\0'));j++);// ����� ����� �������������
			for( ; ((a.x[ia].x[j]!=' ')&&(a.x[ia].x[j]!='\t')&&(a.x[ia].x[j]!='\0')) ; j++);	// ���� � �����������������������

			//*/
			j	= 11;
			for( ;((a.x[ia].x[j]==' ')||(a.x[ia].x[j]=='\t')||(a.x[ia].x[j]=='\0'));j++);// ����� �������� �������������			
			
			k	= j;
			for( ; ((a.x[ia].x[j]!=' ')&&(a.x[ia].x[j]!='\t')&&(a.x[ia].x[j]!='\0')) ; j++);	// ���� � �����������������������
			j	-= k;
			if(tp.mN<=j)tp.adm(j);
			memcpy(tp.x,a.x[ia].x+k,j*sz);	// ����� ���� ��� ��������
			/*!!!tp.N= j;*/
/*!!! -> */ tp.N= 1;
			tp.x[tp.N++]='\0';
			//cout<<tp.x<<endl;
			j	+= k;
			cycl	= true;
			for(k=0;(k<AtTp.N)&&(cycl);k++)	// ���� � �����
			{
				cycl	= (memcmp(tp.x,AtTp.x[k].x,AtTp.x[k].N*sz)!=0)||(tp.N!=AtTp.x[k].N);//  ����������
			}

			if (!cycl) // �� ����� ���� �
			{
				i++;
				k--;
				tpind.add(k);	// ��� ��� �� ���

				/*for( ;((a.x[ia].x[j]==' ')||(a.x[ia].x[j]=='\t')||(a.x[ia].x[j]=='\0'));j++);// ����� ����� �������������
				for( ; ((a.x[ia].x[j]!=' ')&&(a.x[ia].x[j]!='\t')&&(a.x[ia].x[j]!='\0')) ; j++);	// ���� � �����������������������

				for( ;((a.x[ia].x[j]==' ')||(a.x[ia].x[j]=='\t')||(a.x[ia].x[j]=='\0'));j++);// ����� ����� �������������
				for( ; ((a.x[ia].x[j]!=' ')&&(a.x[ia].x[j]!='\t')&&(a.x[ia].x[j]!='\0')) ; j++);	// ���� � �����������������������
				*/
				j	= 27;

				for(;((a.x[ia].x[j]==' ')||(a.x[ia].x[j]=='\t')||(a.x[ia].x[j]=='\0'));j++);// ����� �������� �������������
				k	= j;
				for( ; ((a.x[ia].x[j]!=' ')&&(a.x[ia].x[j]!='\t')&&(a.x[ia].x[j]!='\0')) ; j++);	// ���� � �����������������������
				j	-= k;
				if(q.mN<=j)q.adm(j);
				memcpy(q.x,a.x[ia].x+k,j*sz);	// ����� ���� ��� ��������
				q.N	= j;
				q.x[q.N++]	= '\0';
				rv.x[0]	= atof(q.x);
				j	+= k;

				for(;((a.x[ia].x[j]==' ')||(a.x[ia].x[j]=='\t')||(a.x[ia].x[j]=='\0'));j++);// ����� �������� �������������
				k	= j;			
				for(;((a.x[ia].x[j]!=' ')&&(a.x[ia].x[j]!='\t')&&(a.x[ia].x[j]!='\0'));j++);	// ���� � �����������������������
				j	-= k;
				if(q.mN<=j)q.adm(j);
				memcpy(q.x,a.x[ia].x+k,j*sz);	// ����� ���� ��� ��������
				q.N	= j;
				q.x[q.N++]	= '\0';
				rv.x[1]	= atof(q.x);
				j	+= k;
				
				for(;((a.x[ia].x[j]==' ')||(a.x[ia].x[j]=='\t')||(a.x[ia].x[j]=='\0'));j++);// ����� �������� �������������
				k	= j;			
				for(;((a.x[ia].x[j]!=' ')&&(a.x[ia].x[j]!='\t')&&(a.x[ia].x[j]!='\0'));j++);	// ���� � �����������������������
				j	-= k;
				if(q.mN<=j)q.adm(j);
				memcpy(q.x,a.x[ia].x+k,j*sz);	// ����� ���� ��� ��������
				q.N	= j;
				q.x[q.N++]	= '\0';
				rv.x[2]	= atof(q.x);
				j	+= k;

				xyz.add(rv);
			}
		}
	}

	Q.init(0,xyz.N);
	Q.N	= xyz.N;

	return true;
}


bool s2dx(smpl_ms<smschar> &a, smpl_ms<smschar> &AtTp, ms1D<int> &tpind, ms1D<Vec3db> &xyz, ms1D<double> &Q)	//��� ������� ���������������������xyz - ����
{
	smschar tp(80);
	smschar q(30);
	double r;
	bool cycl;
	int i,j,k,ia,jo,sz;
	sz	= sizeof(char);
	Vec3db rv;
//	xyz.two(a.N,3);
	Q.one(a.N);
	Q.N		= xyz.N = 0;
	i	= -1;
	jo	= 0;
	tpind.N	= 0;
	for(ia=0;ia<a.N;ia++)
	{	
		for(j=0;((a.x[ia].x[j]==' ')||(a.x[ia].x[j]=='\t')||(a.x[ia].x[j]=='\0'));j++);// ����� �������� �������������
		k	= j;
		for( ; ((a.x[ia].x[j]!=' ')&&(a.x[ia].x[j]!='\t')&&(a.x[ia].x[j]!='\0')) ; j++);	// ���� � �����������������������
		j	-= k;
		if(tp.mN<=j)tp.adm(j);
		memcpy(tp.x,a.x[ia].x+k,j*sz);	// ����� ���� ��� ��������
		tp.N= j;
		tp.x[tp.N++]='\0';
		j	+= k;
		cycl	= true;
		for(k=0;(k<AtTp.N)&&(cycl);k++)	// ���� � �����
		{
			cycl	= (memcmp(tp.x,AtTp.x[k].x,AtTp.x[k].N*sz)!=0)||(tp.N!=AtTp.x[k].N);//  ����������
		}
		if (!cycl) // �� ����� ���� �
		{
			i++;
			k--;
			tpind.add(k);	// ��� ��� �� ���

			for(;((a.x[ia].x[j]==' ')||(a.x[ia].x[j]=='\t')||(a.x[ia].x[j]=='\0'));j++);// ����� �������� �������������
			k	= j;			
			for(;((a.x[ia].x[j]!=' ')&&(a.x[ia].x[j]!='\t')&&(a.x[ia].x[j]!='\0'));j++);	// ���� � �����������������������
			j	-= k;
			memcpy(q.x,a.x[ia].x+k,j*sz);	// ����� ���� ��� ��������
			if(q.mN<=j)q.adm(j);
			q.N	= j;
			q.x[q.N++]	= '\0';
			rv.x[0]	= atof(q.x);
			j	+= k;

			for(;((a.x[ia].x[j]==' ')||(a.x[ia].x[j]=='\t')||(a.x[ia].x[j]=='\0'));j++);// ����� �������� �������������
			k	= j;			
			for(;((a.x[ia].x[j]!=' ')&&(a.x[ia].x[j]!='\t')&&(a.x[ia].x[j]!='\0'));j++);	// ���� � �����������������������
			j	-= k;
			memcpy(q.x,a.x[ia].x+k,j*sz);	// ����� ���� ��� ��������
			if(q.mN<=j)q.adm(j);
			q.N	= j;
			q.x[q.N++]	= '\0';
			rv.x[1]	= atof(q.x);
			j	+= k;

			for(;((a.x[ia].x[j]==' ')||(a.x[ia].x[j]=='\t')||(a.x[ia].x[j]=='\0'));j++);// ����� �������� �������������
			k	= j;			
			for(;((a.x[ia].x[j]!=' ')&&(a.x[ia].x[j]!='\t')&&(a.x[ia].x[j]!='\0'));j++);	// ���� � �����������������������
			j	-= k;
			memcpy(q.x,a.x[ia].x+k,j*sz);	// ����� ���� ��� ��������
			if(q.mN<=j)q.adm(j);
			q.N	= j;
			q.x[q.N++]	= '\0';
			rv.x[2]	= atof(q.x);
			j	+= k;

			xyz.add(rv);

			for(;((a.x[ia].x[j]==' ')||(a.x[ia].x[j]=='\t')||(a.x[ia].x[j]=='\0'));j++);// ����� �������� �������������
			k	= j;			
			for(;((a.x[ia].x[j]!=' ')&&(a.x[ia].x[j]!='\t')&&(a.x[ia].x[j]!='\0'));j++);	// ���� � �����������������������
			j	-= k;
			memcpy(q.x,a.x[ia].x+k,j*sz);	// ����� ���� ��� ��������
			if(q.mN<=j)q.adm(j);
			q.N	= j;
			q.x[q.N++]	= '\0';
			r	= atof(q.x);
			Q.add(r);
			j	+= k;
		}

	}
//	xyz.two(tpind.N,3);
//	xyz.tns();	// ��������;
	Q.one(tpind.N);
	return true;
}

bool GetCntlDt(smpl_ms<smschar> &str, solpar &A, grdpar &B,cntlpar &C, cappar &D)
{

	char nam;
	double kappa;
	fstream sss;


	/*sss.open("file.txt",ios::in);
	sss<<"file"<<endl;
	sss.close();*/


	sss.open(InitFileName.x,ios::in);


	sss.unsetf(ios::skipws);	// �� �� ����� ��������� (�� ���� '\0')
	do
	{
		sss>>nam;
		D.ProtName	.add(nam);
	}while(nam!='.');	
	sss>>nam;
	D.ProtName.add(nam);
	sss>>nam;
	D.ProtName.add(nam);
	sss>>nam;
	D.ProtName.add(nam);
	nam	='\0';
	D.ProtName.add(nam);
	

	
	do
	{
		sss>>nam;
	}while(nam!='\n');	
	do
	{
		sss>>nam;
		D.LigName.add(nam);
	}while(nam!='.');	
	sss>>nam;
	D.LigName.add(nam);
	sss>>nam;
	D.LigName.add(nam);
	sss>>nam;
	D.LigName.add(nam);
	nam	='\0';
	D.LigName.add(nam);
	sss.setf(ios::skipws);	// ����� �� ����� ��������� (�� ���� '\0')

	
	sss>>B.R_tr;
	sss>>B.R_mx;

	sss>>A.R_rol;
	sss>>A.s_rol;
	sss>>A.r_min;

	sss>>B.Thet;
	sss>>B.Phi;

	sss>>C.isExS;
	sss>>D.x;
	sss>>D.y;
	sss>>D.z;
	sss>>D.R;

	sss>>kappa;
	sss>>B.alfa;

	sss>>C.TpBld;

	sss>>C.TpSur;

	sss>>C.isOut;

	sss>>B.Nc;
	sss>>B.Np;

	sss>>E_out;
	sss>>E_in;

	sss>>koeff;
	sss>>koeff;

	sss.close();	

	return true;
}

  void AmAcFill(aminotip &Acid,ms1D<double> &MMFF_RWDV)
 {

	MMFF_RWDV.sm(99);
	MMFF_RWDV.N=99;



	MMFF_RWDV.x[0]	=	1.96886950 ;
	MMFF_RWDV.x[1]	=	2.09653949 ;
	MMFF_RWDV.x[2]	=	1.99190113 ;
	MMFF_RWDV.x[3]	=	2.07685150 ;
	MMFF_RWDV.x[4]	=	1.48492424 ;
	MMFF_RWDV.x[5]	=	1.77907442 ;
	MMFF_RWDV.x[6]	=	1.74641698 ;
	MMFF_RWDV.x[7]	=	2.01416046 ;
	MMFF_RWDV.x[8]	=	1.89443729 ;
	MMFF_RWDV.x[9]	=	1.94500000 ;
	MMFF_RWDV.x[10]	=	1.49601730 ;
	MMFF_RWDV.x[11]	=	2.04427843 ;
	MMFF_RWDV.x[12]	=	2.16586018 ;
	MMFF_RWDV.x[13]	=	2.35836702 ;
	MMFF_RWDV.x[14]	=	2.18468286 ;
	MMFF_RWDV.x[15]	=	2.33278245 ;
	MMFF_RWDV.x[16]	=	2.12788929 ;
	MMFF_RWDV.x[17]	=	1.99831023 ;
	MMFF_RWDV.x[18]	=	2.41774902 ;
	MMFF_RWDV.x[19]	=	1.96886950 ;
	MMFF_RWDV.x[20]	=	1.30689925 ;
	MMFF_RWDV.x[21]	=	1.99190113 ;
	MMFF_RWDV.x[22]	=	1.30689925 ;
	MMFF_RWDV.x[23]	=	1.30689925 ;
	MMFF_RWDV.x[24]	=	1.86697320 ;
	MMFF_RWDV.x[25]	=	2.28656585 ;
	MMFF_RWDV.x[26]	=	1.30689925 ;
	MMFF_RWDV.x[27]	=	1.30689925 ;
	MMFF_RWDV.x[28]	=	1.30689925 ;
	MMFF_RWDV.x[29]	=	2.09653949 ;
	MMFF_RWDV.x[30]	=	1.30689925 ;
	MMFF_RWDV.x[31]	=	1.81002645 ;
	MMFF_RWDV.x[32]	=	1.30689925 ;
	MMFF_RWDV.x[33]	=	1.94500000 ;
	MMFF_RWDV.x[34]	=	2.15249633 ;
	MMFF_RWDV.x[35]	=	1.30689925 ;
	MMFF_RWDV.x[36]	=	2.09653949 ;
	MMFF_RWDV.x[37]	=	1.86755903 ;
	MMFF_RWDV.x[38]	=	1.99190113 ;
	MMFF_RWDV.x[39]	=	1.94500000 ;
	MMFF_RWDV.x[40]	=	1.99190113 ;
	MMFF_RWDV.x[41]	=	1.94500000 ;
	MMFF_RWDV.x[42]	=	1.94500000 ;
	MMFF_RWDV.x[43]	=	2.18468286 ;
	MMFF_RWDV.x[44]	=	2.01416046 ;
	MMFF_RWDV.x[45]	=	2.07685150 ;
	MMFF_RWDV.x[46]	=	1.94500000 ;
	MMFF_RWDV.x[47]	=	2.03570535 ;
	MMFF_RWDV.x[48]	=	1.94500000 ;
	MMFF_RWDV.x[49]	=	1.30689925 ;
	MMFF_RWDV.x[50]	=	1.54680157 ;
	MMFF_RWDV.x[51]	=	1.30689925 ;
	MMFF_RWDV.x[52]	=	1.94500000 ;
	MMFF_RWDV.x[53]	=	2.07685150 ;
	MMFF_RWDV.x[54]	=	1.83946743 ;
	MMFF_RWDV.x[55]	=	1.83946743 ;
	MMFF_RWDV.x[56]	=	1.94500000 ;
	MMFF_RWDV.x[57]	=	1.83946743 ;
	MMFF_RWDV.x[58]	=	1.74641698 ;
	MMFF_RWDV.x[59]	=	2.25287830 ;
	MMFF_RWDV.x[60]	=	1.83946743 ;
	MMFF_RWDV.x[61]	=	2.07685150 ;
	MMFF_RWDV.x[62]	=	2.09653949 ;
	MMFF_RWDV.x[63]	=	2.09653949 ;
	MMFF_RWDV.x[64]	=	1.94500000 ;
	MMFF_RWDV.x[65]	=	1.81002645 ;
	MMFF_RWDV.x[66]	=	1.92021787 ;
	MMFF_RWDV.x[67]	=	1.89443729 ;
	MMFF_RWDV.x[68]	=	1.92021787 ;
	MMFF_RWDV.x[69]	=	1.87844904 ;
	MMFF_RWDV.x[70]	=	1.30689925 ;
	MMFF_RWDV.x[71]	=	2.34759451 ;
	MMFF_RWDV.x[72]	=	2.18468286 ;
	MMFF_RWDV.x[73]	=	2.18468286 ;
	MMFF_RWDV.x[74]	=	2.34759451 ;
	MMFF_RWDV.x[75]	=	2.03570535 ;
	MMFF_RWDV.x[76]	=	1.83709199 ;
	MMFF_RWDV.x[77]	=	2.09653949 ;
	MMFF_RWDV.x[78]	=	1.94500000 ;
	MMFF_RWDV.x[79]	=	1.94500000 ;
	MMFF_RWDV.x[80]	=	1.83946743 ;
	MMFF_RWDV.x[81]	=	1.92021787 ;

	MMFF_RWDV.x[82]	=	2.0 ;
	MMFF_RWDV.x[83]	=	2.0 ;
	MMFF_RWDV.x[84]	=	2.0 ;
	MMFF_RWDV.x[85]	=	2.0 ;

	MMFF_RWDV.x[86]	=	1.63807252 ;
	MMFF_RWDV.x[87]	=	1.72234706 ;
	MMFF_RWDV.x[88]	=	2.11568796 ;
	MMFF_RWDV.x[89]	=	2.41774902 ;
	MMFF_RWDV.x[90]	=	2.49630991 ;
	MMFF_RWDV.x[91]	=	1.24466595 ;
	MMFF_RWDV.x[92]	=	1.59054146 ;
	MMFF_RWDV.x[93]	=	2.00000000 ;
	MMFF_RWDV.x[94]	=	1.61956025 ;
	MMFF_RWDV.x[95]	=	1.94800749 ;
	MMFF_RWDV.x[96]	=	1.53832113 ;
	MMFF_RWDV.x[97]	=	1.59054146 ;
	MMFF_RWDV.x[98]	=	1.53832113 ;







	 //Acid.sm(23);
	 //Acid.N	= 23;
	 //Acid.x[0].acidname.sm(4);

	 /*Acid.x[0].acidname.add("ALA",4);
	 Acid.x[0].TpNm.sm(10);Acid.x[0].TpNm.N=10;
	 Acid.x[0].mmff_tp.sm(10);Acid.x[0].mmff_tp.N=10;
	 
	 Acid.x[0].TpNm.x[0].add("N",2);
	 Acid.x[0].TpNm.x[1].add("HN",3);
	 Acid.x[0].TpNm.x[2].add("CA",3);
	 Acid.x[0].TpNm.x[3].add("HA",3);
	 Acid.x[0].TpNm.x[4].add("CB",3);
	 Acid.x[0].TpNm.x[5].add("HB1",4);
	 Acid.x[0].TpNm.x[6].add("HB2",4);
	 Acid.x[0].TpNm.x[7].add("HB3",4);
	 Acid.x[0].TpNm.x[8].add("C",2);
	 Acid.x[0].TpNm.x[9].add("O",2);

	 Acid.x[0].mmff_tp.x[0]	= 10;
	 Acid.x[0].mmff_tp.x[1]	= 28;
	 Acid.x[0].mmff_tp.x[2]	= 1;
	 Acid.x[0].mmff_tp.x[3]	= 5;
	 Acid.x[0].mmff_tp.x[4]	= 1;
	 Acid.x[0].mmff_tp.x[5]	= 5;
	 Acid.x[0].mmff_tp.x[6]	= 5;
	 Acid.x[0].mmff_tp.x[7]	= 5;
	 Acid.x[0].mmff_tp.x[8]	= 3;
	 Acid.x[0].mmff_tp.x[9]	= 7;


	 Acid.x[1].acidname.add("ARG",4);
	 Acid.x[1].TpNm.sm(24);Acid.x[0].TpNm.N=24;
	 Acid.x[1].mmff_tp.sm(24);Acid.x[0].mmff_tp.N=24;

	 Acid.x[1].TpNm.x[0].add("N",2);
	 Acid.x[1].TpNm.x[1].add("HN",3);
	 Acid.x[1].TpNm.x[2].add("CA",3);
	 Acid.x[1].TpNm.x[3].add("HA",3);
	 Acid.x[1].TpNm.x[4].add("CB",3);
	 Acid.x[1].TpNm.x[5].add("HB1",4);
	 Acid.x[1].TpNm.x[6].add("HB2",4);
	 Acid.x[1].TpNm.x[7].add("C",2);
	 Acid.x[1].TpNm.x[8].add("O",2);
	 Acid.x[1].TpNm.x[9].add("CG",2);
	 Acid.x[1].TpNm.x[10].add("HG1",2);
	 Acid.x[1].TpNm.x[11].add("HG2",2);
	 Acid.x[1].TpNm.x[12].add("CD",2);
	 Acid.x[1].TpNm.x[13].add("HD1",2);
	 Acid.x[1].TpNm.x[14].add("HD2",2);
	 Acid.x[1].TpNm.x[15].add("NE",2);
	 Acid.x[1].TpNm.x[16].add("HE",2);
	 Acid.x[1].TpNm.x[17].add("CZ",2);
	 Acid.x[1].TpNm.x[18].add("NH1",2);
	 Acid.x[1].TpNm.x[19].add("HH11",2);
	 Acid.x[1].TpNm.x[20].add("HH12",2);
	 Acid.x[1].TpNm.x[21].add("NH2",2);
	 Acid.x[1].TpNm.x[22].add("HH21",2);
	 Acid.x[1].TpNm.x[23].add("HH22",2);
	 

	 Acid.x[1].mmff_tp.x[0]	= 10;
	 Acid.x[1].mmff_tp.x[1]	= 28;
	 Acid.x[1].mmff_tp.x[2]	= 1;
	 Acid.x[1].mmff_tp.x[3]	= 5;
	 Acid.x[1].mmff_tp.x[4]	= 1;
	 Acid.x[1].mmff_tp.x[5]	= 5;
	 Acid.x[1].mmff_tp.x[6]	= 5;
	 Acid.x[1].mmff_tp.x[7]	= 3;
	 Acid.x[1].mmff_tp.x[8]	= 7;
	 Acid.x[1].mmff_tp.x[9]	= 1;
	 Acid.x[1].mmff_tp.x[10]	= 5;
	 Acid.x[1].mmff_tp.x[11]	= 5;
	 Acid.x[1].mmff_tp.x[12]	= 1;
	 Acid.x[1].mmff_tp.x[13]	= 5;
	 Acid.x[1].mmff_tp.x[14]	= 5;
	 Acid.x[1].mmff_tp.x[15]	= 56;
	 Acid.x[1].mmff_tp.x[16]	= 36;
	 Acid.x[1].mmff_tp.x[17]	= 57;
	 Acid.x[1].mmff_tp.x[18]	= 56;
	 Acid.x[1].mmff_tp.x[19]	= 36;
	 Acid.x[1].mmff_tp.x[20]	= 36;
	 Acid.x[1].mmff_tp.x[21]	= 56;
	 Acid.x[1].mmff_tp.x[22]	= 36;
	 Acid.x[1].mmff_tp.x[23]	= 36;
	 /**/







}

void double2char(double x, char * sx, int pres);

#endif
