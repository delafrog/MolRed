#ifndef RDWRFLS_CPP
#define RDWRFLS_CPP


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <QString>
#include <QByteArray>
#include "linalg.h"
//#include "linalg.cpp"
#include "datatypes.h"
#include "rdwrfls.h"
#include "surface.h"

//_____________________________________________________________________________________________
//_____________________________________________________________________________________________
WorkFrame::WorkFrame()
{
}
//_____________________________________________________________________________________________
WorkFrame::~WorkFrame()
{
}
//_____________________________________________________________________________________________
void WorkFrame::MolSwap(const int &id1,const int &id2)
{
	Molecule *m;

	m	= Mls.x[id1];
	Mls.x[id1]	= Mls.x[id2];
	Mls.x[id2]	= m;
}
//_____________________________________________________________________________________________
void WorkFrame::InitMolSurf(ConnectedAtoms *mol)
{
	//ConnectedAtoms *mol;
	//mol	= reinterpret_cast<ConnectedAtoms *> (glWidg->mols.x[id_ml]);
	Surface * l_srf;

	l_srf	= new (Surface);

	l_srf->SetMolecule(mol);
	l_srf->SetWorkframe(this);

	Srfcs.add(l_srf);
}
//_____________________________________________________________________________________________
void WorkFrame::DelMolSurf(ConnectedAtoms * mol)
{
	int ii;
	//ii	= Srfcs.fnd(mol);
	ii = -1;
	for(ii=0;ii<Srfcs.N;ii++)
	{
		if(Srfcs.x[ii]->GetMolecule()==mol)
		{
		//	jj=ii;
			break;
		}
	}
	if ((ii!=-1)&&(ii<Srfcs.N))
	{
		delete Srfcs.x[ii];
		Srfcs.x[ii]	= 0x0;
		Srfcs.rem(1,ii);
	}
}
//_____________________________________________________________________________________________
void WorkFrame::DelMolSurf(Surface *srf)
{
	int ii;
	ii	= Srfcs.fnd(srf);
	if(ii!=-1)
	{
		Srfcs.x[ii]->clearWF();
		Srfcs.x[ii]->clearMol();
		delete Srfcs.x[ii];
		Srfcs.x[ii]	= 0x0;
		Srfcs.rem(1,ii);
	}
}
//_____________________________________________________________________________________________
void WorkFrame::DelMolSurf()
{
	int ii;
	for(ii=0;ii<Srfcs.N;ii++)
	{
		Srfcs.x[ii]->clearWF();
		Srfcs.x[ii]->clearMol();
		delete Srfcs.x[ii];
		Srfcs.x[ii]	= 0x0;
	}
	Srfcs.N=0;
}
//_____________________________________________________________________________________________
int WorkFrame::hinparser(vecT<char> &fname)	// чтение данных из hin-файла и сохранение данных в молекулах
{
	FILE *fio;
	vecT<char> str;
	char *token;
	char *_chptr;
	char seps[]   = " ,\t\n";

	vec2T<char> ch2;
	vecT<vec2T<char> > AtT;
	vecT<vecT<int> > Bnds;
	vecT<vecT<char> > BnT;
	vecT<vec3db> xyz;
	vecT<double> chrgs;
	double a;
	vec3db x;
	int bn,bN;
	vecT<char> chs1;
	vecT<int>	bns;
	vecT<int> id_mmff;
	Molecule *cMlc;
	int endmol;

//fpos_t f_pos;

	str.setlen(80);
	//Mls.setmem();

	
	fio	= fopen(fname.x,"r");
	if (fio!=NULL)
	{
	do
	{
		str.x[str.N-2]	= 0;
		fgets(str.x,str.N,fio);	// чтение строки

		token = strtok(str.x,seps);	// выделить отдельные слова
		if(token!=0x0)
		{
			if (strcmp(token,"mol")==0)
			{
				cMlc	= new Molecule;
				//str.x[str.N-2] = '\0';
				endmol	= 1;
				AtT.N	=0;
				chrgs.N	=0;
				xyz.N	=0;
				Bnds.N	=0;
				BnT.N	=0;
				id_mmff.N= 0;
				do
				{
					fgets(str.x,str.N,fio);	// чтение строки
					if((str.x[str.N-2]!='\0')&&(str.x[str.N-2]!='\n'))//&(str.x[str.N-1]!='\0'))	// если строка превышает str.N элементов
					{
						_chptr = reinterpret_cast<char*>(fio->_Placeholder);
						if (_chptr[0] =='\n')//(str.x[str.N-1]!='\0')
						{
							fgetc(fio);
							str.add('\0');
						}else
						{
							// то провести поэлементное чтение пока не обнаружится конец строки
							char ch;
							str.N--;
							ch	= fgetc(fio);
							while(ch!='\n')
							{
								str.add(ch);
								ch	= fgetc(fio);
							}
							/*fgetpos(fio,&f_pos);
							f_pos--;
							fsetpos(fio,&f_pos);
							ch	= fgetc(fio);
							str.N--;
							while(ch!='\n')
							{
								str.add(ch);
								ch	= fgetc(fio);
							}*/
							str.add('\0');
						}
					}

					token = strtok(str.x,seps);	// выделить отдельные слова
					if (strcmp(token,"atom")==0)
					{
						token = strtok( NULL, seps );
						token = strtok( NULL, seps );
						token = strtok( NULL, seps );
						ch2.x[0]	= token[0];
						ch2.x[1]	= token[1];
						AtT.add(ch2);
						token = strtok( NULL, seps );
						if(memcmp(token,"**",2*sizeof(char))!=0)
						{
							bN = atoi(token);
							id_mmff.add(bN);
						}else
						{
							id_mmff.add(0);
						}
						token = strtok( NULL, seps );
						token = strtok( NULL, seps );
						a	= atof(token);
						chrgs.add(a);
						token = strtok( NULL, seps );
						x.x[0]	= atof(token);
						token = strtok( NULL, seps );
						x.x[1]	= atof(token);
						token = strtok( NULL, seps );
						x.x[2]	= atof(token);
						xyz.add(x);
						token = strtok( NULL, seps );
						bN	= atoi(token);
						bns.N	= 0;
						chs1.N	= 0;
						//if (bN>0)
						//{
						for(int i = 0; i<bN;i++)
						{
							token = strtok( NULL, seps );
							bn	= atoi(token)-1;
							bns.add(bn);
							token = strtok( NULL, seps );
							chs1.add(token[0]);
						}
						//}else
						//{
						//	bns.N	= 0;
						//	chs1.N	= 0;
						//}/**/
						Bnds.pad(bns);
						BnT.pad(chs1);
					}else 
					{
						endmol	= strcmp(token,"endmol");
					}
					str.x[str.N-2] = '\0';

				}while(endmol!=0);

				cMlc->Connect.setSize(AtT.N,AtT.N);
				cMlc->id_TpzTbl	= 0;
				cMlc->Atoms.setlen(AtT.N);
				for(int i=0;i<AtT.N;i++)
				{
					cMlc->Atoms.x[i].id_Tot	= i;
					cMlc->Atoms.x[i].r		= xyz.x[i];
					cMlc->Atoms.x[i].id_Tpz	= TableZR.indret(AtT.x[i]);

					if((id_mmff.x[i]!=0)||(chrgs.x[i]!=0))
					{
						cMlc->Atoms.x[i].dat.initdat();
						cMlc->Atoms.x[i].dat.qsetq(chrgs.x[i]);
						cMlc->Atoms.x[i].dat.qsetid(id_mmff.x[i]);
					}

					for(int j =0;j<Bnds.x[i].N;j++)
					{
						bn	= (BnT.x[i].x[j]=='s') ? 1 : (BnT.x[i].x[j]=='d')|(BnT.x[i].x[j]=='a') ? 2 : (BnT.x[i].x[j]=='t') ? 3 : 0;
						cMlc->AddBond(bn,i,Bnds.x[i].x[j]);
					}
				}
				cMlc->Name.pst(fname);

				Mls.add(cMlc);
				cMlc	= 0x0;
			}
		}
	}while(!feof(fio));
	fclose(fio);
	}
	else
	{
		return 1;
	}

	cMlc	= 0x0;
	return 0;
}
//_____________________________________________________________________________________________
int WorkFrame::mrkparser(vecT<char> &fname)	// чтение данных из hin-файла и сохранение данных в молекулах
{
	FILE *fio;
	vecT<char> str;
	char *token;
	char seps[]   = " ,\t\n";

	vec2T<char> ch2;
	vecT<int > At_id;
	vecT<vecT<int> > Bnds;
	vecT<vecT<char> > BnT;
	vecT<vec3db> xyz;
	vecT<double> chrgs;
	double a;
	vec3db x;
	int id_str,id,ia1,ia2,io;
	vecT<char> chs1;
	vecT<int>	bns;
	Molecule *cMlc;
//int endmol;
	int n_at,n_bn;

	fpos_t f_pos;

	str.setlen(160);
	//Mls.setmem();

	cMlc	= 0x0;
	id_str	= -1;
	n_at	= 0;
	n_bn	= 0;
	str		= 0;
	fio	= fopen(fname.x,"r");
	if (fio!=NULL)
	{
		do
		{
			//fgets(str.x,str.N,fio);	// чтение строки
			str.x[0]		= 0;
			str.x[str.N-2]	= 0;
			fgets(str.x,str.N,fio);	// чтение строки
			if((str.x[str.N-2]!='\0'))	// если строка превышает str.N элементов
			{						// то провести поэлементное чтение пока не обнаружится конец строки
				char ch;
				str.N--;
				fgetpos(fio,&f_pos);
				f_pos--;
				fsetpos(fio,&f_pos);
				ch	= fgetc(fio);
				str.N--;
				while(ch!='\n')
				{
					str.add(ch);
					ch	= fgetc(fio);
				}
				str.add('\0');
			}
			id_str++;

			//if((!feof(fio))||(str.N>1))
			{
				token = strtok(str.x,seps);	// выделить отдельные слова
				if(token!=0x0)	
				{
					if(id_str==2)	 // определение числа атомов и числа связей
					{
						n_at	= atoi(token);
						token	= strtok( NULL, seps );
						n_bn	= atoi(token);

						xyz.setmem(n_at);
						At_id.setmem(n_at);
						chrgs.setmem(n_at);
						bns.setmem(n_at);
					}else
					{
						if((id_str>2)&&(id_str<n_at+3))
						{
							//token	= strtok(NULL,seps);	// выделить отдельные слова
							x.x[0]	= atof(token);
							token	= strtok(NULL,seps);	// выделить отдельные слова
							x.x[1]	= atof(token);
							token	= strtok(NULL,seps);	// выделить отдельные слова
							x.x[2]	= atof(token);
							xyz.add(x);

							token	= strtok(NULL,seps);	// выделить отдельные слова
							id		= atoi(token);
							id--;
							At_id.add(id);
							token	= strtok(NULL,seps);	// выделить отдельные слова
							id		= atoi(token);
							bns.add(id);
							token	= strtok(NULL,seps);	// выделить отдельные слова
							token	= strtok(NULL,seps);	// выделить отдельные слова
							id		= atoi(token);
							if(id!=xyz.N) 
							{
								return -1;
							}
							token	= strtok(NULL,seps);	// выделить отдельные слова
							token	= strtok(NULL,seps);	// выделить отдельные слова
							token	= strtok(NULL,seps);	// выделить отдельные слова
							a		= atof(token);
							chrgs.add(a);
						}else
						{
							if(id_str==n_at+3)
							{
								cMlc	= new Molecule;
								cMlc->ReInit(xyz.N);
								cMlc->Name.pst(fname);
								for(int ii=0;ii<xyz.N;ii++)
								{
									cMlc->Atoms.x[ii].r			= xyz.x[ii];
									cMlc->Atoms.x[ii].id_Tot	= ii;
									cMlc->Atoms.x[ii].id_Tpz	= At_id.x[ii];
									if((bns.x[ii]!=0)||(chrgs.x[ii]!=0))
									{
										cMlc->Atoms.x[ii].dat.initdat();
										cMlc->Atoms.x[ii].dat.qsetq(chrgs.x[ii]);
										cMlc->Atoms.x[ii].dat.qsetid(bns.x[ii]);
									}
								}
								cMlc->Atoms.N	= xyz.N;
							}
							if(id_str>=n_at+3)
							{
								//	token	= strtok(NULL,seps);	// выделить отдельные слова
								do
								{
									ia1		= atoi(token);
									token	= strtok(NULL,seps);	// выделить отдельные слова
									ia2		= atoi(token);
									token	= strtok(NULL,seps);	// выделить отдельные слова
									io		= atoi(token);
									ia1--;ia2--;
									cMlc->AddBond(io,ia1,ia2);
									token	= strtok(NULL,seps);	// выделить отдельные слова
								}while(token!=0x0);
							}
						}
					}
				}
			}
		}while(!feof(fio));
		cMlc->Name.pst(fname);
		fclose(fio);
	}
	else
	{
		return 1;
	}
	if(cMlc!=0x0) Mls.add(cMlc);	
	cMlc	= 0x0;
	return 0;
}
//_____________________________________________________________________________________________
int WorkFrame::pdbparser0(vecT<char> &fname)	// чтение данных из pbd-файла и сохранение данных в молекулах (самый прстой вариант)
{
	FILE *fio;
	vecT<char> str;
	vecT<char> atom("ATOM",4);
	vecT<char> hetatom("HETATM",6);
//char *token;
//	char seps[]   = " ,\t\n";

	vec2T<char> ch2;
	vecT<int > At_id;
	vecT<vec2T<char> > AtT;
	vecT<vec2T<char> > AtT_;
	vecT<vecT<int> > Bnds;
	vecT<vecT<char> > BnT;
	vecT<vec3db> xyz;
	vecT<vec3db> xyz_;
	vecT<double> chrgs;
	double a;
	vec3db x;
	int id_str,id,ia1,ia2,io;
	vecT<char> chs1;
	vecT<int>	bns;
	Molecule *cMlc,*cMlc_;
//int endmol;
	int n_at,n_bn;

	fpos_t f_pos;

	str.setlen(160);
	//Mls.setmem();

	cMlc	= 0x0;
	id_str	= -1;
	n_at	= 0;
	n_bn	= 0;
	str		= 0;
	fio	= fopen(fname.x,"r");

	if (fio!=NULL)
	{
		do
		{
			//fgets(str.x,str.N,fio);	// чтение строки
			str.x[str.N-2]	= 0;
			fgets(str.x,str.N,fio);	// чтение строки
			if((str.x[str.N-2]!='\0'))	// если строка превышает str.N элементов
			{						// то провести поэлементное чтение пока не обнаружится конец строки
				char ch;
				str.N--;
				fgetpos(fio,&f_pos);
				f_pos--;
				fsetpos(fio,&f_pos);
				ch	= fgetc(fio);
				str.N--;
				while(ch!='\n')
				{
					str.add(ch);
					ch	= fgetc(fio);
				}
				str.add('\0');
			}
			id_str++;

			if(!feof(fio))
			{
				if(memcmp(str.x,atom.x,4*sizeof(char))==0)
				{
					x.x[0]	= atof(str.x+30);
					x.x[1]	= atof(str.x+38);
					x.x[2]	= atof(str.x+46);

					ch2.x[0]	= str.x[76];
					ch2.x[1]	= str.x[77];
					if(ch2.x[0]==' ') 
					{
						ch2.x[0]	= ch2.x[1];
						ch2.x[1]	= '\0';
					}
					xyz.add(x);
					AtT.add(ch2);
				}
				if(memcmp(str.x,hetatom.x,6*sizeof(char))==0)
				{
					x.x[0]	= atof(str.x+30);
					x.x[1]	= atof(str.x+38);
					x.x[2]	= atof(str.x+46);

					ch2.x[0]	= str.x[76];
					ch2.x[1]	= str.x[77];
					if(ch2.x[0]==' ') 
					{
						ch2.x[0]	= ch2.x[1];
						ch2.x[1]	= '\0';
					}
					xyz_.add(x);
					AtT_.add(ch2);
				}
			}
		}while(!feof(fio));
		fclose(fio);	
		cMlc	= new Molecule;
		cMlc->ReInit(xyz.N);

		for(int ii=0;ii<xyz.N;ii++)
		{
			cMlc->Atoms.x[ii].r			= xyz.x[ii];
			cMlc->Atoms.x[ii].id_Tot	= ii;
			cMlc->Atoms.x[ii].id_Tpz	= TableZR.indret(AtT.x[ii]);
		}
		cMlc->Atoms.N	= xyz.N;
		cMlc->Name.pst(fname);

		for(int ii=1;ii<xyz.N;ii++)
		{
			for(int jj=0;jj<ii;jj++)
			{
				x	= xyz.x[ii]-xyz.x[jj];
				a	= x.sqnr();
				if(a<3.5)
				{
					if(cMlc->Atoms.x[ii].id_Tpz==0)
					{
						if(cMlc->Atoms.x[jj].id_Tpz!=0)
						{
							if(a<2.25)
							{
								cMlc->AddBond(1,ii,jj);
							}
						}
					}else
					{
						if(cMlc->Atoms.x[jj].id_Tpz==0)
						{
							if(a<2.25)
							{
								cMlc->AddBond(1,ii,jj);
							}
						}else
						{
								cMlc->AddBond(1,ii,jj);
						}
					}
				}
			}
		}

		Mls.add(cMlc);

		if (xyz_.N>0)
		{
			cMlc_	= new Molecule;

			xyz	= xyz_;
			AtT	= AtT_;

			cMlc_->ReInit(xyz.N);
			cMlc->Name.pst(fname);

			for(int ii=0;ii<xyz.N;ii++)
			{
				cMlc_->Atoms.x[ii].r			= xyz.x[ii];
				cMlc_->Atoms.x[ii].id_Tot	= ii;
				cMlc_->Atoms.x[ii].id_Tpz	= TableZR.indret(AtT.x[ii]);
			}
			cMlc_->Atoms.N	= xyz.N;

			for(int ii=1;ii<xyz.N;ii++)
			{
				for(int jj=0;jj<ii;jj++)
				{
					x	= xyz.x[ii]-xyz.x[jj];
					a	= x.sqnr();
					if(a<3.5)
					{
						if(cMlc_->Atoms.x[ii].id_Tpz==0)
						{
							if(cMlc_->Atoms.x[jj].id_Tpz!=0)
							{
								if(a<2.25)
								{
									cMlc_->AddBond(1,ii,jj);
								}
							}
						}else
						{
							if(cMlc_->Atoms.x[jj].id_Tpz==0)
							{
								if(a<2.25)
								{
									cMlc_->AddBond(1,ii,jj);
								}
							}else
							{
								cMlc_->AddBond(1,ii,jj);
							}
						}
					}
				}
			}

			Mls.add(cMlc_);
		}
	}
	else
	{
		return 1;
	}
	//if(cMlc!=0x0) Mls.add(cMlc);	
	cMlc_	= cMlc	= 0x0;
	return 0;
}
//_____________________________________________________________________________________________
int WorkFrame::pdbparser1(vecT<char> &fname)	// чтение данных из pbd-файла
{
	// прочесть положения и типы атомов
	// а также названия аминокислот
	// выделить лиганд и другие доп. молеклы
	// использовать CONNECT для установления связей S-S мостиков и связей в лигандах


	FILE *fio;
	vecT<char> str;
	vecT<char> atom("ATOM",4);
	vecT<char> hetatom("HETATM",6);
	vecT<char> connect("CONNECT",7);
	vecT<char> ter("TER",3);
	vecT<char> aminoname(3);
	vecT<char> aminumber(5);
	vecT< vecT <char> > at_nms;
	vecT<char> at_nm;
	vecT<char> chL;
	vecT<int> aminnum;
	char chsL;
	vecT< vecT<char> > aminonames;
//	char *token;
//	char seps[]   = " ,\t\n";

	vec2T<char> ch2;
	vecT<int > At_id,aid;
	vecT<vec2T<char> > AtT;
	vecT<vec2T<char> > AtT_;
	vecT<vecT<int> > Bnds;
	vecT<vecT<char> > BnT;
	vecT<vec3db> xyz;
	vecT<vec3db> xyz_;
	vecT<double> chrgs,chrgs_;

	AminoAcid amin;
	vecT<AminoAcid > amins;

	vecT< vecT< AminoAcid > > chains;


	double a;
	vec3db x;
	int id_str,id,ia1,ia2,io;
	vecT<char> chs1;
	vecT<int>	bns,bns_;
	Molecule *cMlc;
	Molecule *cMlc_;
//int endmol;
	int n_at,n_bn,nstr;

	bool isfrst;
	fpos_t f_pos;


	protein_node *prnd;

	str.setlen(160);
	//Mls.setmem();

	cMlc	= 0x0;
	id_str	= -1;
	n_at	= 0;
	n_bn	= 0;
	str		= 0;
	fio	= fopen(fname.x,"r");
	nstr	= 0;
	do
	{
		fgets(str.x,str.N,fio);	// чтение строки
		nstr++;
	}while(!feof(fio));
	fclose(fio);
	fio	= fopen(fname.x,"r");

	chsL = 'Я';
	isfrst	= false;
	aminumber	= 0;
	chrgs.setmem(nstr);
	bns.setmem(nstr);
	xyz.setmem(nstr);
	AtT.setmem(nstr);
	at_nms.setmem(nstr);
	chrgs_.N = chrgs.N	= 0;
	bns_.N = bns.N	= 0;
	if (fio!=NULL)
	{
		do
		{
			//fgets(str.x,str.N,fio);	// чтение строки
			str.x[str.N-2]	= 0;
			fgets(str.x,str.N,fio);	// чтение строки
			if((str.x[str.N-2]!='\0'))	// если строка превышает str.N элементов
			{						// то провести поэлементное чтение пока не обнаружится конец строки
				char ch;
				str.N--;
				fgetpos(fio,&f_pos);
				f_pos--;
				fsetpos(fio,&f_pos);
				ch	= fgetc(fio);
				str.N--;
				while(ch!='\n')
				{
					str.add(ch);
					ch	= fgetc(fio);
				}
				str.add('\0');
			}
			id_str++;

			if(!feof(fio))
			{
				if(memcmp(str.x,atom.x,4*sizeof(char))==0)
				{
					x.x[0]	= atof(str.x+30);
					x.x[1]	= atof(str.x+38);
					x.x[2]	= atof(str.x+46);

					if(memcmp(str.x+22,aminumber.x,4*sizeof(char))!=0) // проверка смены названия аминокислоты
					{
						if(isfrst)
						{
							amins.pad(amin);
							amin.amin_ch.N	= 0;
							amin.Atoms_id.N	= 0;
						}
						isfrst	= true;
						aminumber.add(str.x+22,4);
						aminumber.add('\0');
						aminoname.add(str.x+17,3);
						aminoname.add('\0');
						aminonames.pad(aminoname);
						amin.amin_ch.pst(aminoname);
						amin.id	= atoi(aminumber.x);
						aminoname.N = 0;
						aminumber.N	= 0;
					}
					if(chsL!=str.x[21]) // проверка смены индекса цепи
					{
						if(chL.N!=0)
						{
							chains.pad(amins);
							amins.N	= 0;
						}
						chsL	= str.x[21];
						chL.add(chsL);
					}

					id	= xyz.N;
					amin.Atoms_id.add(id);

					ch2.x[0]	= str.x[76];
					ch2.x[1]	= str.x[77];
					if(ch2.x[0]==' ') 
					{
						ch2.x[0]	= ch2.x[1];
						ch2.x[1]	= '\0';
					}else
					{
						if(ch2.x[1]==' ') ch2.x[1]	= '\0';
					}

					a	= atof(str.x+69);
					chrgs.add(a);
					id	= atoi(str.x+66);
					bns.add(id);
					xyz.add(x);
					//AtT.add(ch2);

					at_nm.N= 0;
					if((str.x+12)[0]==' ')
					{
						at_nm.add(str.x+13,3);
						at_nm.add('\0');
					}else
					{
						at_nm.add(str.x+12,4);
						at_nm.add('\0');
					}
					at_nms.pad(at_nm);
					if(at_nm.x[0]!=ch2.x[0])
					{
						ch2.x[0] = at_nm.x[0];
						ch2.x[1] = '\0';
					}

					if(ch2.x[0]>90) ch2.x[0]-=32;  // если первая буква маленькая - сделать её большой
					if(ch2.x[1]!='\0') // проверка второй буквы и её исправлений - чтобы была маленькой а не заглавной
					{
						if(ch2.x[1]<97) ch2.x[1]+=32;
					}

					AtT.add(ch2);

				}else
				{
					if(memcmp(str.x,ter.x,3*sizeof(char))==0)
					{
						if(isfrst)
						{
							amins.pad(amin);
							amin.amin_ch.N	= 0;
							amin.Atoms_id.N	= 0;
						}
						isfrst	= false;
						aminumber.add(str.x+22,4);
						aminoname.add(str.x+17,3);
						aminoname.add('\0');
						aminonames.pad(aminoname);
						amin.amin_ch.pst(aminoname);
						amin.id	= atoi(aminumber.x);
						aminoname.N = 0;
						aminumber.N	= 0;
					}
				}
				if(memcmp(str.x,hetatom.x,6*sizeof(char))==0)
				{

					x.x[0]	= atof(str.x+30);
					x.x[1]	= atof(str.x+38);
					x.x[2]	= atof(str.x+46);

					ch2.x[0]	= str.x[76];
					ch2.x[1]	= str.x[77];
					if(ch2.x[0]==' ') 
					{
						ch2.x[0]	= ch2.x[1];
						ch2.x[1]	= '\0';
					}else
					{
						if(ch2.x[1]==' ') ch2.x[1]	= '\0';
					}

					a	= atof(str.x+69);
					chrgs_.add(a);
					id	= atoi(str.x+66);
					bns_.add(id);

					at_nm.N= 0;
					at_nm.add(str.x+12,4);
					at_nm.add('\0');
					if(ch2.x[0]==' ')
					{
						ch2.x[0] = at_nm.x[0];
						ch2.x[1] = at_nm.x[1];
						if(ch2.x[0]==' ') 
						{
							ch2.x[0]	= ch2.x[1];
							ch2.x[1]	= '\0';
						}else
						{
							if(ch2.x[1]==' ') ch2.x[1]	= '\0';
						}
					}

					if(ch2.x[0]>90) ch2.x[0]-=32;  // если первая буква маленькая - сделать её большой
					if(ch2.x[1]!='\0') // проверка второй буквы и её исправлений - чтобы была маленькой а не заглавной
					{
						if(ch2.x[1]<97) ch2.x[1]+=32;
					}

					xyz_.add(x);
					AtT_.add(ch2);
				}
			}
		}while(!feof(fio));
		fclose(fio);	
		if(amins.N!=0) chains.pad(amins);
		cMlc	= new Molecule;
		cMlc->ReInit(xyz.N);

		//cMlc->ch_Leter.add(chL.x[0]);
		

		//cMlc->chains.pad(chains);
		//cMlc->ch_Leter.pst(chL);

		cMlc->mol_type	= PROTEINE;

		/*for(int ii=1;ii<xyz.N;ii++)
		{
			if(cMlc->ch_Leter.x[cMlc->ch_Leter.N-1]!=chL.x[ii])
			{
				cMlc->ch_Leter.add(chL.x[ii]);
			}
		}*/

		for(int ii=0;ii<xyz.N;ii++)
		{
			cMlc->Atoms.x[ii].r			= xyz.x[ii];
			cMlc->Atoms.x[ii].id_Tot	= ii;
			cMlc->Atoms.x[ii].id_Tpz	= TableZR.indret(AtT.x[ii]);
			cMlc->Atoms.x[ii].dat.initdat();
			if((bns.x[ii]!=0)||(chrgs.x[ii]!=0))
			{
				cMlc->Atoms.x[ii].dat.qsetq(chrgs.x[ii]);
				cMlc->Atoms.x[ii].dat.qsetid(bns.x[ii]);
			}

		}
		cMlc->Atoms.N	= xyz.N;
		cMlc->Name.pst(fname);

		prnd	= new protein_node;
		prnd->setProt(chains,chL,*cMlc);
		prnd->id_ml	= Mls.N;

		for(int ii=0;ii<cMlc->Atoms.N;ii++)
		{
			cMlc->Atoms.x[ii].dat.dat->amin->name.pst(at_nms.x[ii]);
		}
		//cMlc->Atoms.x[0].dat.dat->amin.p_atm->parent->parent->delChild(0);
		//delete prnd;

		
		for(int ic=0;ic<chains.N;ic++)
		{
			aid.N=0;
			for(int ia=0;ia<chains.x[ic].N;ia++)
			{
				aid.add(chains.x[ic].x[ia].Atoms_id);
			}
			for(int iic=1;iic<aid.N;iic++)
			{
				int ii	= aid.x[iic];
				for(int jjc=0;jjc<iic;jjc++)
				{
					int jj	= aid.x[jjc];
					x	= xyz.x[ii]-xyz.x[jj];
					a	= x.sqnr();
					if(a<3.5)
					{
						if(cMlc->Atoms.x[ii].id_Tpz==0)
						{
							if(cMlc->Atoms.x[jj].id_Tpz!=0)
							{
								if(a<2.25)
								{
									cMlc->AddBond(1,ii,jj);
								}
							}
						}else
						{
							if(cMlc->Atoms.x[jj].id_Tpz==0)
							{
								if(a<2.25)
								{
									cMlc->AddBond(1,ii,jj);
								}
							}else
							{
								cMlc->AddBond(1,ii,jj);
							}
						}
					}
				}
			}
		}

		//cMlc->setAtoms2Amin();

		Mls.add(cMlc);

		if (xyz_.N>0)
		{
			cMlc_	= new Molecule;

			xyz	= xyz_;
			AtT	= AtT_;
			chrgs	= chrgs_;
			bns		= bns_;

			cMlc_->ReInit(xyz.N);
			cMlc->Name.pst(fname);

			for(int ii=0;ii<xyz.N;ii++)
			{
				cMlc_->Atoms.x[ii].r		= xyz.x[ii];
				cMlc_->Atoms.x[ii].id_Tot	= ii;
				cMlc_->Atoms.x[ii].id_Tpz	= TableZR.indret(AtT.x[ii]);
				if((bns.x[ii]!=0)||(chrgs.x[ii]!=0))
				{
					cMlc->Atoms.x[ii].dat.initdat();
					cMlc->Atoms.x[ii].dat.qsetq(chrgs.x[ii]);
					cMlc->Atoms.x[ii].dat.qsetid(bns.x[ii]);
				}
			}
			cMlc_->Atoms.N	= xyz.N;

			for(int ii=1;ii<xyz.N;ii++)
			{
				for(int jj=0;jj<ii;jj++)
				{
					x	= xyz.x[ii]-xyz.x[jj];
					a	= x.sqnr();
					if(a<3.5)
					{
						if(cMlc_->Atoms.x[ii].id_Tpz==0)
						{
							if(cMlc_->Atoms.x[jj].id_Tpz!=0)
							{
								if(a<2.25)
								{
									cMlc_->AddBond(1,ii,jj);
								}
							}
						}else
						{
							if(cMlc_->Atoms.x[jj].id_Tpz==0)
							{
								if(a<2.25)
								{
									cMlc_->AddBond(1,ii,jj);
								}
							}else
							{
								cMlc_->AddBond(1,ii,jj);
							}
						}
					}
				}
			}

			cMlc_->mol_type	= LIGAND;
			Mls.add(cMlc_);
		}
	}
	else
	{
		return 1;
	}
	//if(cMlc!=0x0) Mls.add(cMlc);	
	cMlc_	= cMlc	= 0x0;
	return 0;
}
//_____________________________________________________________________________________________
int WorkFrame::molparser(vecT<char> &fname)
{
	FILE *fio;
	vecT<char> str;

	vecT<vecT<int> > Bnds;
	vecT<vecT<char> > BnT;
	vec2T<char> ch2;
	vecT<vec3db> xyz;
	vecT<double> chrgs;
	int id,ia1,ia2,io;
	vecT<char> chs1;
	vecT<int>	bns;
	Molecule *cMlc;
	int n_at,n_bn;

	str.setlen(90);

	cMlc	= 0x0;
	n_at	= 0;
	n_bn	= 0;
	str		= 0;
	fio	= fopen(fname.x,"r");

	fgets(str.x,str.N,fio);	// чтение 1 строки
	fgets(str.x,str.N,fio);	// чтение 2 строки
	fgets(str.x,str.N,fio);	// чтение 3 строки
	fgets(str.x,str.N,fio);	// чтение 4 строки
	
	chs1.add(str.x,3);
	chs1.add('\0');
	n_at	= atoi(chs1.x);
	chs1.N=0;
	chs1.add(str.x+3,3);
	chs1.add('\0');
	n_bn	= atoi(chs1.x);

	if(n_at>0)
	{
		xyz.setlen(n_at);
		BnT.setlen(n_at);
		chrgs.setlen(n_at);
		bns.setlen(n_at);
		for(int ii=0;ii<n_at;ii++)
		{
			fgets(str.x,str.N,fio);	// чтение строки
			chs1.N=0;
			chs1.add(str.x,10);
			chs1.add('\0');
			xyz.x[ii].x[0]	= atof(chs1.x);
			chs1.N=0;
			chs1.add(str.x+10,10);
			chs1.add('\0');
			xyz.x[ii].x[1]	= atof(chs1.x);
			chs1.N=0;chs1.add(str.x+20,10);
			chs1.add('\0');
			xyz.x[ii].x[2]	= atof(chs1.x);
			BnT.x[ii].add(str.x+31,2);
			chs1.N=0;
			chs1.add(str.x+70,7);
			chs1.add('\0');
			chrgs.x[ii]	= atof(chs1.x);
			chs1.N=0;
			chs1.add(str.x+79,2);
			chs1.add('\0');
			bns.x[ii]	= atoi(chs1.x);
		}
		cMlc	= new Molecule;
		cMlc->ReInit(n_at);
		for(int ii=0;ii<n_at;ii++)
		{
			cMlc->Atoms.x[ii].r			= xyz.x[ii];
			cMlc->Atoms.x[ii].id_Tot	= ii;
			ch2.x[0]	= BnT.x[ii].x[0];
			ch2.x[1]	= BnT.x[ii].x[1] == ' ' ? '\0' : BnT.x[ii].x[1];
			cMlc->Atoms.x[ii].id_Tpz	= TableZR.indret(ch2);
			if((bns.x[ii]!=0)||(chrgs.x[ii]!=0))
			{
				cMlc->Atoms.x[ii].dat.initdat();
				cMlc->Atoms.x[ii].dat.qsetq(chrgs.x[ii]);
				cMlc->Atoms.x[ii].dat.qsetid(bns.x[ii]);
			}
		}
		cMlc->Atoms.N	= n_at;
		for(int ii=0;ii<n_bn;ii++)
		{
			fgets(str.x,str.N,fio);	// чтение строки
			chs1.N=0;
			chs1.add(str.x,3);
			chs1.add('\0');
			ia1	= atof(chs1.x);
			chs1.N=0;
			chs1.add(str.x+3,3);
			chs1.add('\0');
			ia2	= atof(chs1.x);
			chs1.N=0;
			chs1.add(str.x+6,3);
			chs1.add('\0');
			io	= atof(chs1.x);
			ia1--;ia2--;
			io	= io==4 ? 1 : io;
			cMlc->AddBond(io,ia1,ia2);
		}
		cMlc->Name.pst(fname);
	}else
	{
		fclose(fio);
		return 1;
	}
	fclose(fio);
	if(cMlc!=0x0) Mls.add(cMlc);	
	cMlc	= 0x0;
	return 0;
}
//_____________________________________________________________________________________________
int WorkFrame::xyzparser(vecT<char> &fname)	// чтение данных из xyz-файла
{
	FILE *fio;
	vecT<char> str;
//	char *token;
//	char seps[]   = " ,\t\n";

	fpos_t f_pos;

	vecT< vecT <char> > txtdata;
	int id_str;

	Molecule *cMlc;

	str.setlen(80);

	fio	= fopen(fname.x,"r");


	id_str	= 0;

	if (fio!=NULL)
	{

		do
		{
			//fgets(str.x,str.N,fio);	// чтение строки
			str.x[str.N-2]	= 0;
			fgets(str.x,str.N,fio);	// чтение строки
			if((str.x[str.N-2]!='\0'))	// если строка превышает str.N элементов
			{						// то провести поэлементное чтение пока не обнаружится конец строки
				char ch;
				str.N--;
				fgetpos(fio,&f_pos);
				f_pos--;
				fsetpos(fio,&f_pos);
				ch	= fgetc(fio);
				str.N--;
				while(ch!='\n')
				{
					str.add(ch);
					ch	= fgetc(fio);
				}
				str.add('\0');
			}
			id_str++; // номер прочитанной строки
		}while(!feof(fio));
		fclose(fio);
		txtdata.setmem(id_str);// здесь в id_str - число строк 
		fio	= fopen(fname.x,"r");
		do
		{
			//fgets(str.x,str.N,fio);	// чтение строки
			str.x[str.N-2]	= 0;
			fgets(str.x,str.N,fio);	// чтение строки
			if((str.x[str.N-2]!='\0'))	// если строка превышает str.N элементов
			{						// то провести поэлементное чтение пока не обнаружится конец строки
				char ch;
				str.N--;
				fgetpos(fio,&f_pos);
				f_pos--;
				fsetpos(fio,&f_pos);
				ch	= fgetc(fio);
				str.N--;
				while(ch!='\n')
				{
					str.add(ch);
					ch	= fgetc(fio);
				}
				str.add('\0');
			}
			id_str	= strlen(str.x);
			str.N	= id_str+1;
			txtdata.pad(str);
			str.N	= str.mN;
			str	= 0;
		}while(!feof(fio));
		fclose(fio);
		id_str	= checkxyztype(txtdata);
		cMlc	= new Molecule;
		switch (id_str) 
		{
		case 1:
			{
				if(	xyzpars_1(txtdata,cMlc)!=0) return 1;
				break;
			}
		case 2:
			{
				if(xyzpars_2(txtdata,cMlc)!=0) return 1;
				break;
			}
		case 3:
			{
				if(xyzpars_3(txtdata,cMlc)!=0) return 1;
				break;
			}
		case 4:
			{
				if(xyzpars_4(txtdata,cMlc)!=0) return 1;
				break;
			}case 5:
			{
				if(xyzpars_5(txtdata,cMlc)!=0) return 1;
				break;
			}
		case 6:
			{
				if(xyzpars_6(txtdata,cMlc)!=0) return 1;
				break;
			}
		case 7:
			{
				if(xyzpars_7(txtdata,cMlc)!=0) return 1;
				break;
			}
		default :
			{
				return 1;
				break;
			}
		}
		cMlc->Name.pst(fname);
	}else
	{
		return 1;
	}

	setdistanceconnect(cMlc);
	Mls.add(cMlc);
	cMlc	= 0x0;
	return 0;
}
//_____________________________________________________________________________________________
void WorkFrame::setdistanceconnect(Molecule * cMlc)
{
	int ii,jj;
	vec3db dr;
	double a,b;
	for(ii=0;ii<cMlc->Atoms.N-1;ii++)
	{
		for(jj=ii+1;jj<cMlc->Atoms.N;jj++)
		{
			dr	= cMlc->Atoms.x[jj].r-cMlc->Atoms.x[ii].r;
			a	= dr.sqnr();
			b	= TableZR.Lines.x[cMlc->Atoms.x[jj].id_Tpz].cvlrad+TableZR.Lines.x[cMlc->Atoms.x[ii].id_Tpz].cvlrad;
			b	/= 100;
			b	*= b;
			if(a<b)	
			{
				cMlc->AddBond(1,ii,jj);
			}
			/*
			if(a<3.5)
			{
				if(cMlc->Atoms.x[ii].id_Tpz==0)
				{
					if(cMlc->Atoms.x[jj].id_Tpz!=0)
					{
						if(a<2.25)
						{
							cMlc->AddBond(1,ii,jj);
						}
					}
				}else
				{
					if(cMlc->Atoms.x[jj].id_Tpz==0)
					{
						if(a<2.25)
						{
							cMlc->AddBond(1,ii,jj);
						}
					}else
					{
						cMlc->AddBond(1,ii,jj);
					}
				}
			}*/
		}
	}
}
//_____________________________________________________________________________________________
int WorkFrame::xyzpars_1(vecT <vecT <char> > &txtdata,Molecule *cMlc)
{
	int ii,jj;
	char *token;
	char seps[]   = " ,\t\n";
	vecT<int> types;
	vecT<vec3db> coords;
	vec3db a;
	types.setmem(txtdata.N);
	coords.setmem(txtdata.N);
	for (ii=0;ii<txtdata.N;ii++)
	{
		token = strtok(txtdata.x[ii].x,seps);	// выделить отдельные слова
		if(token!=0x0)
		{
			jj	= atoi(token);
			jj--;
			types.add(jj);
			token	= strtok(NULL,seps);
			a.x[0]	= atof(token);
			token	= strtok(NULL,seps);
			a.x[1]	= atof(token);
			token	= strtok(NULL,seps);
			a.x[2]	= atof(token);

			coords.add(a);
		}
	}
	cMlc->Connect.setSize(types.N,types.N);
	cMlc->id_TpzTbl	= 0;
	cMlc->Atoms.setlen(types.N);
	for(ii=0;ii<coords.N;ii++)
	{
		cMlc->Atoms.x[ii].id_Tot	= ii;
		cMlc->Atoms.x[ii].id_Tpz	= types.x[ii];
		cMlc->Atoms.x[ii].r			= coords.x[ii];
	}
	return 0;
}
//_____________________________________________________________________________________________
int WorkFrame::xyzpars_2(vecT <vecT <char> > &txtdata,Molecule *cMlc)
{
	int ii,jj;
	char *token;
	char seps[]   = " ,\t\n";
	vecT<int > types;
	vec2T<char> tp;
	vecT<vec3db> coords;
	vec3db a;
	types.setmem(txtdata.N);
	coords.setmem(txtdata.N);
	for (ii=0;ii<txtdata.N;ii++)
	{
		token = strtok(txtdata.x[ii].x,seps);	// выделить отдельные слова
		if(token!=0x0)
		{
			tp.x[0] = token[0];
			tp.x[1]	= token[1];
			jj	= TableZR.indret(tp);
			types.add(jj);
			
			token	= strtok(NULL,seps);
			a.x[0]	= atof(token);
			token	= strtok(NULL,seps);
			a.x[1]	= atof(token);
			token	= strtok(NULL,seps);
			a.x[2]	= atof(token);

			coords.add(a);
		}
	}
	cMlc->Connect.setSize(types.N,types.N);
	cMlc->id_TpzTbl	= 0;
	cMlc->Atoms.setlen(types.N);
	for(ii=0;ii<coords.N;ii++)
	{
		cMlc->Atoms.x[ii].id_Tot	= ii;
		cMlc->Atoms.x[ii].id_Tpz	= types.x[ii];
		cMlc->Atoms.x[ii].r			= coords.x[ii];
	}
	return 0;
}
//_____________________________________________________________________________________________
int WorkFrame::xyzpars_3(vecT <vecT <char> > &txtdata,Molecule *cMlc)
{
	int ii,jj;
	char *token;
	char seps[]   = " ,\t\n";
	vecT<int > types;
	//vec2T<char> tp;
	vecT<vec3db> coords;
	vec3db a;
	types.setmem(txtdata.N);
	coords.setmem(txtdata.N);
	for (ii=0;ii<txtdata.N;ii++)
	{
		token = strtok(txtdata.x[ii].x,seps);	// выделить отдельные слова
		if(token!=0x0)
		{
			token	= strtok(NULL,seps);

			jj	= atoi(token);
			jj--;
			//if (TableZR.indret(tp)==)
			types.add(jj);
			
			token	= strtok(NULL,seps);
			a.x[0]	= atof(token);
			token	= strtok(NULL,seps);
			a.x[1]	= atof(token);
			token	= strtok(NULL,seps);
			a.x[2]	= atof(token);

			coords.add(a);
		}
	}
	cMlc->Connect.setSize(types.N,types.N);
	cMlc->id_TpzTbl	= 0;
	cMlc->Atoms.setlen(types.N);
	for(ii=0;ii<coords.N;ii++)
	{
		cMlc->Atoms.x[ii].id_Tot	= ii;
		cMlc->Atoms.x[ii].id_Tpz	= types.x[ii];
		cMlc->Atoms.x[ii].r			= coords.x[ii];
	}
	return 0;
}
//_____________________________________________________________________________________________
int WorkFrame::xyzpars_4(vecT <vecT <char> > &txtdata,Molecule *cMlc)
{
	int ii,jj;
	char *token;
	char seps[]   = " ,\t\n";
	vecT<int > types;
	//vec2T<char> tp;
	vecT<vec3db> coords;
	vec3db a;
	types.setmem(txtdata.N);
	coords.setmem(txtdata.N);
	for (ii=2;ii<txtdata.N;ii++)
	{
		token = strtok(txtdata.x[ii].x,seps);	// выделить отдельные слова
		if(token!=0x0)
		{
			token	= strtok(NULL,seps);

			jj	= atoi(token);
			jj--;
			//if (TableZR.indret(tp)==)
			types.add(jj);
			
			token	= strtok(NULL,seps);
			a.x[0]	= atof(token);
			token	= strtok(NULL,seps);
			a.x[1]	= atof(token);
			token	= strtok(NULL,seps);
			a.x[2]	= atof(token);

			coords.add(a);
		}
	}
	cMlc->Connect.setSize(types.N,types.N);
	cMlc->id_TpzTbl	= 0;
	cMlc->Atoms.setlen(types.N);
	for(ii=0;ii<coords.N;ii++)
	{
		cMlc->Atoms.x[ii].id_Tot	= ii;
		cMlc->Atoms.x[ii].id_Tpz	= types.x[ii];
		cMlc->Atoms.x[ii].r			= coords.x[ii];
	}
	return 0;
}
//_____________________________________________________________________________________________
int WorkFrame::xyzpars_5(vecT <vecT <char> > &txtdata,Molecule *cMlc)
{
	int ii,jj;
	char *token;
	char seps[]   = " ,\t\n";
	vecT<int > types;
	vec2T<char> tp;
	vecT<vec3db> coords;
	vec3db a;
	types.setmem(txtdata.N);
	coords.setmem(txtdata.N);
	for (ii=1;ii<txtdata.N;ii++)
	{
		token = strtok(txtdata.x[ii].x,seps);	// выделить отдельные слова
		if(token!=0x0)
		{

			tp.x[0] = token[0];
			tp.x[1]	= token[1];
			jj	= TableZR.indret(tp);
			types.add(jj);

			token	= strtok(NULL,seps);
						
			token	= strtok(NULL,seps);
			a.x[0]	= atof(token);
			token	= strtok(NULL,seps);
			a.x[1]	= atof(token);
			token	= strtok(NULL,seps);
			a.x[2]	= atof(token);

			coords.add(a);
		}
	}
	cMlc->Connect.setSize(types.N,types.N);
	cMlc->id_TpzTbl	= 0;
	cMlc->Atoms.setlen(types.N);
	for(ii=0;ii<coords.N;ii++)
	{
		cMlc->Atoms.x[ii].id_Tot	= ii;
		cMlc->Atoms.x[ii].id_Tpz	= types.x[ii];
		cMlc->Atoms.x[ii].r			= coords.x[ii];
	}
	return 0;
}
//_____________________________________________________________________________________________
int WorkFrame::xyzpars_6(vecT <vecT <char> > &txtdata,Molecule *cMlc)
{
	int ii,jj;
	char *token;
	char seps[]   = " ,\t\n";
	vecT<int> types;
	vecT<vec3db> coords;
	vec3db a;
	types.setmem(txtdata.N);
	coords.setmem(txtdata.N);
	for (ii=2;ii<txtdata.N;ii++)
	{
		token = strtok(txtdata.x[ii].x,seps);	// выделить отдельные слова
		if(token!=0x0)
		{
			jj	= atoi(token);
			jj--;
			types.add(jj);
			token	= strtok(NULL,seps);
			a.x[0]	= atof(token);
			token	= strtok(NULL,seps);
			a.x[1]	= atof(token);
			token	= strtok(NULL,seps);
			a.x[2]	= atof(token);

			coords.add(a);
		}
	}
	cMlc->Connect.setSize(types.N,types.N);
	cMlc->id_TpzTbl	= 0;
	cMlc->Atoms.setlen(types.N);
	for(ii=0;ii<coords.N;ii++)
	{
		cMlc->Atoms.x[ii].id_Tot	= ii;
		cMlc->Atoms.x[ii].id_Tpz	= types.x[ii];
		cMlc->Atoms.x[ii].r			= coords.x[ii];
	}
	return 0;
}
//_____________________________________________________________________________________________
int WorkFrame::xyzpars_7(vecT <vecT <char> > &txtdata,Molecule *cMlc)
{
	int ii,jj;
	char *token;
	char seps[]   = " ,\t\n";
	vecT<int > types;
	vec2T<char> tp;
	vecT<vec3db> coords;
	vecT<double> chrgs;
	vecT<int> id_mmff;
	vec3db a;
	types.setmem(txtdata.N);
	coords.setmem(txtdata.N);
	chrgs.setmem(txtdata.N);
	id_mmff.setmem(txtdata.N);
	for (ii=2;ii<txtdata.N;ii++)
	{
		token = strtok(txtdata.x[ii].x,seps);	// выделить отдельные слова
		if(token!=0x0)
		{

			tp.x[0] = token[0];
			tp.x[1]	= token[1];
			jj	= TableZR.indret(tp);
			types.add(jj);
						
			token	= strtok(NULL,seps);
			a.x[0]	= atof(token);
			token	= strtok(NULL,seps);
			a.x[1]	= atof(token);
			token	= strtok(NULL,seps);
			a.x[2]	= atof(token);

			coords.add(a);

			token	= strtok(NULL,seps);
			if(token!=0x0)
			{
				a.x[0]	= atof(token);
				chrgs.add(a.x[0]);
				token	= strtok(NULL,seps);
				jj		= atoi(token);
				id_mmff.add(jj);
			}else
			{
				chrgs.add(0.0);
				id_mmff.add(0);
			}
		}
	}
	cMlc->Connect.setSize(types.N,types.N);
	cMlc->id_TpzTbl	= 0;
	cMlc->Atoms.setlen(types.N);
	for(ii=0;ii<coords.N;ii++)
	{
		cMlc->Atoms.x[ii].id_Tot	= ii;
		cMlc->Atoms.x[ii].id_Tpz	= types.x[ii];
		cMlc->Atoms.x[ii].r			= coords.x[ii];
		if((id_mmff.x[ii]!=0)||(chrgs.x[ii]!=0))
		{
			cMlc->Atoms.x[ii].dat.initdat();
			cMlc->Atoms.x[ii].dat.qsetq(chrgs.x[ii]);
			cMlc->Atoms.x[ii].dat.qsetid(id_mmff.x[ii]);
		}
	}
	return 0;
}
//_____________________________________________________________________________________________
int WorkFrame::checkxyztype(vecT <vecT <char> > &txtdata) // определение типа xyz - файла. ворвращаемое число-код типа. возвращение 0 означает нессответсвие ни одному из типов.
{
	// анализ первой строки:
	// если первая строка пустая => это строка коментария -> делаем проверку второй строки на совпадение с фразой 'Atomic Coordinates:' , если совпало - возвращвет тип 6 для файла
	// если первая строка не пустая -> делаем проверку на совпадение первой строки со строкой '----------' -> при совпадении - 5 тип файла
	// в первой строке представлено только число -> проверка второй строки на совпадение с 'transform mrk2xyz' при совпадении - 7 тип файла
	// при несовпадении -> проверка с 'Comment' при совпадении -> 4 тип файла
	// остальные типы не используют коментарии.
	// проверка первого беспробельного слова -> если это число - тип 1 , если атомный символ -> проверка второго беспробельного слова -> если это
	// целое число совпадающее с номером атомного символа - тип 3, если это дробное число - тип 2

	vecT<char> str;

	char *token;
	char seps[]   = " ,\t\n";


	str.pst(txtdata.x[0]);


	token = strtok(str.x,seps);	// выделить отдельные слова

	if(token!=0x0)	
	{
		if(strcmp(token,"------------------------------------------------------------")==0)
		{
			return 5;
		}else
		{
			vecT<char> lstr;
			int N;
			lstr.add(token,strlen(token)+1);

			token = strtok(NULL,seps);
			if(token == 0x0)
			{
				N	= atoi(lstr.x);
				if(N!=0)
				{
					str.pst(txtdata.x[1]);
					token = strtok(str.x,seps);	// выделить отдельные слова
					if(token != 0x0)
					{
					if(strcmp(token,"Comment")==0)
					{
						return 4;
					}else
					{
						if(strcmp(token,"transform")==0)
						{
							token = strtok(NULL,seps);	// выделить отдельные слова
							if(strcmp(token,"mrk2xyz")==0)
							{
								return 7;
							}else return 0;
						}else 
						{
							if(strcmp(token,"Molred")==0)
							{
								return 7;
							}else return 7;
						}
					}
					}else
					{
						return 7;
					}
				}
			}
			else
			{
				N	= atoi(lstr.x);
				if(N>0)
				{
					return 1;
				}else
				{
					{
						bool ch =true;
						for(int ii=0;(ii<strlen(token)&&ch);ii++) ch=token[ii]!='.';
						if (!ch) return 2;
					}
					N	= atoi(token);
					if (N>0)
					{						
						N--;
						switch (lstr.N)
						{
						case 2:
							{
								if(lstr.x[0]==TableZR.Lines.x[N].Ch.x[0])
								{
									return 3;
								}else return 0;
								break;}
						case 3:
							{
								if((lstr.x[0]==TableZR.Lines.x[N].Ch.x[0])&&(lstr.x[1]==TableZR.Lines.x[N].Ch.x[1]))
								{
									return 3;
								}else return 0;
								break;}
						default :
							{return 0;}
						}
						//lstr.pst(TableZR.Lines.x[N].Ch.x,2)
					}
				}
			}
		}
	}else
	{
		if(txtdata.N>1)
		{
			str.pst(txtdata.x[1]);
			token = strtok(str.x,seps);	// выделить отдельные слова
			if(token!=0x0)
			{
				if(strcmp(token,"Atomic")==0)
				{
					token = strtok(NULL,seps);	// выделить отдельные слова
					if(strcmp(token,"Coordinates:")==0)
					{
						return 6;
					}else return 0;
				}
			}else return 0;
		}else
		{
			return 0;
		}
	}

	return 0;
}
//_____________________________________________________________________________________________
bool WorkFrame::readFile(const QString &fileName)
{
	QByteArray qba;
	int lq;
	vecT<char> fnm;
	char	*xc;

	qba	= fileName.toLatin1();
	lq	= qba.length();

	fnm.setlen(lq+1);
	fnm.x[lq]	= '\0';
	for(int i=0;i<lq;i++) fnm.x[i]	= qba[i];

	xc	= &fnm.x[fnm.N-4];

	if(strcmp(xc,"hin")==0)
	{
		if (hinparser(fnm)==1) return false;
	}else
	{
		if(strcmp(xc,"mrk")==0)
		{
			if (mrkparser(fnm)==1) return false;
		}else
		{
			if(strcmp(xc,"pdb")==0)
			{
				if (pdbparser1(fnm)==1) return false;
			}
			else
			{
				if(strcmp(xc,"xyz")==0)
				{
					if (xyzparser(fnm)==1) return false;
				}else 
				{
					if(strcmp(xc,"mol")==0)
					{
						if (molparser(fnm)==1) return false;
					}else return false;
				}
			}
		}
	}

	return true;
}

//_____________________________________________________________________________________________
void WorkFrame::xyzscript(int id_ml, vecT<vecT <char> > &xyzstr)
{
	vecT<char> str1;
	vecT<char> str2("Molred");str2.add('\0');
	char str[80];
	vecT<char> cstr;
	int ii;
	double crd;

	cstr.setmem(80);

	_itoa(this->Mls.x[id_ml]->Atoms.N,str,10);
	str1.add(str);

	xyzstr.setmem(Mls.x[id_ml]->Atoms.N+2);

	xyzstr.pad(str1);
	xyzstr.pad(str2);

	for(ii=0;ii<Mls.x[id_ml]->Atoms.N;ii++)
	{
		cstr.N	= 0;
		cstr.add(' ');
		cstr.add(TableZR.Lines.x[Mls.x[id_ml]->Atoms.x[ii].id_Tpz].Ch.x[0]);
		cstr.add(TableZR.Lines.x[Mls.x[id_ml]->Atoms.x[ii].id_Tpz].Ch.x[1]);
		if(cstr.x[cstr.N-1]=='\0') cstr.x[cstr.N-1]	= ' ';
		cstr.add("  ");

		crd	= Mls.x[id_ml]->Atoms.x[ii].r.x[0];
		_gcvt(crd,8,str);
		cstr.add(str);
		cstr.add("    ");

		crd	= Mls.x[id_ml]->Atoms.x[ii].r.x[1];
		_gcvt(crd,8,str);
		cstr.add(str);
		cstr.add("    ");

		crd	= Mls.x[id_ml]->Atoms.x[ii].r.x[2];
		_gcvt(crd,8,str);
		cstr.add(str);
		cstr.add("    ");

		xyzstr.pad(cstr);
	}
}
//_____________________________________________________________________________________________
void WorkFrame::xyzscript(vecT<vecT <char> > &xyzstr)
{
	vecT<char> str1;
	vecT<char> str2("Molred");str2.add('\0');
	char str[80];
	vecT<char> cstr;
	int ii,jj,na;
	double crd;

	cstr.setmem(80);

	na	= 0;
	for(ii=0;ii<Mls.N;ii++)
	{
		na	+= Mls.x[ii]->Atoms.N;
	}
	_itoa(na,str,10);
	str1.add(str);
	str1.add('\0');

	na	+=2;
	xyzstr.setmem(na);

	xyzstr.pad(str1);
	xyzstr.pad(str2);

	for(jj=0;jj<Mls.N;jj++)
	{
		for(ii=0;ii<Mls.x[jj]->Atoms.N;ii++)
		{
			cstr.N	= 0;
			cstr.add(' ');
			cstr.add(TableZR.Lines.x[Mls.x[jj]->Atoms.x[ii].id_Tpz].Ch.x[0]);
			cstr.add(TableZR.Lines.x[Mls.x[jj]->Atoms.x[ii].id_Tpz].Ch.x[1]);
			if(cstr.x[cstr.N-1]=='\0') cstr.x[cstr.N-1]	= ' ';
			cstr.add("  ");

			crd	= Mls.x[jj]->Atoms.x[ii].r.x[0];
			_gcvt(crd,8,str);
			cstr.add(str);
			cstr.add("    ");

			crd	= Mls.x[jj]->Atoms.x[ii].r.x[1];
			_gcvt(crd,8,str);
			cstr.add(str);
			cstr.add("    ");

			crd	= Mls.x[jj]->Atoms.x[ii].r.x[2];
			_gcvt(crd,8,str);
			cstr.add(str);
			cstr.add("    ");
			cstr.add('\0');

			xyzstr.pad(cstr);
		}
	}
}
//_____________________________________________________________________________________________
void WorkFrame::hinscript(int id_ml,vecT<vecT <char> > &hinstr)	// формирует набор строк с hin- описанием молекулы с номерм 'id-ml'
{
	vecT<char> str1("File cretaed by MolRed ");str1.add('\0');
	vecT<char> str2("+++");str2.add('\0');
	vecT<char> molbeg("mol 1");molbeg.add('\0');
	vecT<char> molend("endmol 1");molend.add('\0');
	vecT<char> atomstr("atom"); 
	vecT<char> tabstr("   ");
	char numstr[50];
	vecT<char> nstr;
	double crd;

	hinstr.N= 0;
	hinstr.pad(str1);
	hinstr.pad(str2);

	hinstr.pad(molbeg);
	int ii,jj,kk,io,id_at,ij;
	for(ii=0;ii<Mls.x[id_ml]->Atoms.N;ii++)
	{
		jj	= hinstr.N;
		hinstr.pad(atomstr);
		hinstr.x[jj].add(tabstr);
		ij	= ii+1;
		_itoa(ij,numstr,10);
		nstr.N = 0;
		nstr.add(numstr);
		nstr.add(" - ");
		ij	= Mls.x[id_ml]->Atoms.x[ii].id_Tpz;
		nstr.add(TableZR.Lines.x[ij].Ch.x,2);
		if(nstr.x[nstr.N-1]=='\0') {nstr.x[nstr.N-1]	= ' ';}
		if(Mls.x[id_ml]->Atoms.x[ii].dat.dat!=0x0)
		{
			_itoa(Mls.x[id_ml]->Atoms.x[ii].dat.dat->id_mmff,numstr,10);
			//nstr.N = 0;
			nstr.add(numstr);
			nstr.add(" - ");

			crd	= Mls.x[id_ml]->Atoms.x[ii].dat.dat->q;
			_gcvt(crd,8,numstr);
			nstr.add(numstr);
			nstr.add("  ");

		}else
		{
			nstr.add(" ** - 0   ");
		}

		crd	= Mls.x[id_ml]->Atoms.x[ii].r.x[0];
		_gcvt(crd,8,numstr);
		nstr.add(numstr);
		nstr.add("  ");

		crd	= Mls.x[id_ml]->Atoms.x[ii].r.x[1];
		_gcvt(crd,8,numstr);
		nstr.add(numstr);
		nstr.add("  ");

		crd	= Mls.x[id_ml]->Atoms.x[ii].r.x[2];
		_gcvt(crd,8,numstr);
		nstr.add(numstr);
		nstr.add(" ");

		ij	= Mls.x[id_ml]->Connect.I.x[ii].N;
		_itoa(ij,numstr,10);
		nstr.add(numstr);
		nstr.add("  ");

		for(kk=0;kk<Mls.x[id_ml]->Connect.I.x[ii].N;kk++)
		{
			id_at	= Mls.x[id_ml]->Connect.I.x[ii].x[kk]+1;
			ij		= Mls.x[id_ml]->Connect.S.x[ii].x[kk]-1;
			io		= Mls.x[id_ml]->Bonds.x[ij].oder;

			_itoa(id_at,numstr,10);
			nstr.add(numstr);
			nstr.add(" ");
			switch (io) 
			{
			case 1 :
				nstr.add("s   ");
				break;
			case 2 :
				nstr.add("d   ");
				break;
			case 3 :
				nstr.add("t   ");
				break;
			case 4 :
				break;
			}
		}
		nstr.add('\0');
		hinstr.x[jj].add(nstr);
	}
	hinstr.pad(molend);
	nstr.N	= 0;
	nstr.add('\0');
	hinstr.pad(nstr);
}
//_____________________________________________________________________________________________
void WorkFrame::hinscript(vecT<vecT <char> > &hinstr)	// формирует набор строк с hin- описанием молекулы с номерм 'id-ml'
{
	vecT<char> str1("File cretaed by MolRed ");str1.add('\0');
	vecT<char> str2("+++");str2.add('\0');
	vecT<char> molbeg("mol ");//molbeg.add('\0');
	vecT<char> molend("endmol ");//molend.add('\0');
	vecT<char> atomstr("atom"); 
	vecT<char> tabstr("   ");
	char numstr[50];
	//char *buffer;
	vecT<char> nstr;
	vecT<char> hst;
	double crd;
	int id_ml;
	//int decimal,sign;

	hinstr.N= 0;
	hinstr.pad(str1);
	hinstr.pad(str2);

	for(id_ml=0;id_ml<Mls.N;id_ml++)
	{
		_itoa((id_ml+1),numstr,10);
		hinstr.pad(molbeg);
		hinstr.x[hinstr.N-1].add(numstr);
		hinstr.x[hinstr.N-1].add('\0');
		int ii,jj,kk,io,id_at,ij;
		for(ii=0;ii<Mls.x[id_ml]->Atoms.N;ii++)
		{
			jj	= hinstr.N;
			hinstr.pad(atomstr);
			hinstr.x[jj].add(tabstr);
			ij	= ii+1;
			_itoa(ij,numstr,10);
			nstr.N = 0;
			nstr.add(numstr);
			nstr.add(" - ");
			ij	= Mls.x[id_ml]->Atoms.x[ii].id_Tpz;
			nstr.add(TableZR.Lines.x[ij].Ch.x,2);
			if(nstr.x[nstr.N-1]=='\0') {nstr.x[nstr.N-1]	= ' ';}
			//nstr.add(" ** - 0   ");
			if(Mls.x[id_ml]->Atoms.x[ii].dat.dat!=0x0)
			{
				_itoa(Mls.x[id_ml]->Atoms.x[ii].dat.dat->id_mmff,numstr,10);
				//nstr.N = 0;
				nstr.add(numstr);
				if(strlen(numstr)==1)
				{
					nstr.add("  - ");
				}else
				{
					nstr.add(" - ");
				}
				

				crd	= Mls.x[id_ml]->Atoms.x[ii].dat.dat->q;
				_gcvt(crd,8,numstr);
				nstr.add(numstr);
				ij	= 14 - strlen(numstr);
				for(int kl=0;kl<ij;kl++){nstr.add(" ");}

			}else
			{
				nstr.add(" ** - 0   ");
			}

			crd	= Mls.x[id_ml]->Atoms.x[ii].r.x[0];
			_gcvt(crd,8,numstr);
			/*buffer	= fcvt(crd,8,&decimal,&sign);
			hst.N= 0;
			hst.add(buffer,9);*/
			hst.N	= 0;
			hst.add(numstr);
			while(hst.N<15){hst.add(" "); }
			nstr.add(hst);
			nstr.add("  ");

			crd	= Mls.x[id_ml]->Atoms.x[ii].r.x[1];
			_gcvt(crd,8,numstr);
			//nstr.add(numstr);
			hst.N	= 0;
			hst.add(numstr);
			while(hst.N<15){hst.add(" "); }
			nstr.add(hst);
			nstr.add("  ");

			crd	= Mls.x[id_ml]->Atoms.x[ii].r.x[2];
			_gcvt(crd,8,numstr);
			//nstr.add(numstr);
			hst.N	= 0;
			hst.add(numstr);
			while(hst.N<15){hst.add(" "); }
			nstr.add(hst);
			nstr.add("  ");

			ij	= Mls.x[id_ml]->Connect.I.x[ii].N;
			_itoa(ij,numstr,10);
			nstr.add(numstr);
			nstr.add("  ");

			for(kk=0;kk<Mls.x[id_ml]->Connect.I.x[ii].N;kk++)
			{
				id_at	= Mls.x[id_ml]->Connect.I.x[ii].x[kk]+1;
				ij		= Mls.x[id_ml]->Connect.S.x[ii].x[kk]-1;
				io		= Mls.x[id_ml]->Bonds.x[ij].oder;

				_itoa(id_at,numstr,10);
				nstr.add(numstr);
				nstr.add(" ");
				switch (io) 
				{
				case 1 :
					nstr.add("s   ");
					break;
				case 2 :
					nstr.add("d   ");
					break;
				case 3 :
					nstr.add("t   ");
					break;
				case 4 :
					break;
				}
			}
			nstr.add('\0');
			hinstr.x[jj].add(nstr);
		}
		_itoa((id_ml+1),numstr,10);
		hinstr.pad(molend);
		hinstr.x[hinstr.N-1].add(numstr);
		hinstr.x[hinstr.N-1].add('\0');
	}
	nstr.N	= 0;
	nstr.add('\0');
	hinstr.pad(nstr);
}
//_____________________________________________________________________________________________
void WorkFrame::mrkscript(vecT<vecT <char> > &mrkstr)	// формирует набор строк с hin- описанием молекулы с номерм 'id-ml'
{
	vecT<char> str1("File cretaed by MolRed ");str1.add('\0');
	vecT<char> str2("+++");str2.add('\0');
	vecT<char> strx;
	vecT<int> ishift;
	char sx[80];
	strx.setlen(81);
	strx.x[strx.N-1] = '\0';
	double crd;

	int ii,jj,kk,na,nb;

	//vecT<Molecule> mols;
	Molecule *mols = new Molecule;
	*mols	= *Mls.x[0];
	//mols.setlen(Mls.N);
	//for(ii=0;ii<Mls.N;ii++)
	//{
	//	mols.x[ii] = *Mls.x[ii];
	//}

	for(ii=1;ii<Mls.N;ii++)
	{
		//mols.x[0].UniMol(mols.x+ii);
		mols->UniMol(Mls.x[ii]);//mols.x+ii);
	}

	na	= mols->Atoms.N;
	nb	= mols->Bonds.N;

	mrkstr.setmem(int(na+nb/5));
	
	_itoa(na,sx,10);
	strx.N	= 0;
	jj	= strlen(sx);
	strx.add(sx,sizeof(char)*jj);
	jj++;
	strx.add(' ');
	for(;jj<6;jj++)	strx.add(' ');
	_itoa(nb,sx,10);
	jj	= strlen(sx)+1;
	strx.add(sx,sizeof(char)*jj);


	mrkstr.add(str1);
	mrkstr.add(str2);
	mrkstr.add(strx);

	nb	= 0;

//	int dem, sgn;

	for(jj=0;jj<mols->Atoms.N;jj++)
	{
		strx.N= 0;

		crd	= mols->Atoms.x[jj].r.x[0];
		if(fabs(crd)>0.1){_gcvt(crd,5,sx);}else{_gcvt(crd,3,sx);}
		na	= strlen(sx);
		strx.add(sx,na);
		na	= strx.N;
		strx.add(' ');
		for(;na<11;na++)	strx.add(' ');

		crd	= mols->Atoms.x[jj].r.x[1];
		if(fabs(crd)>0.1){_gcvt(crd,5,sx);}else{_gcvt(crd,3,sx);}
		na	= strlen(sx);
		strx.add(sx,na);
		na	= strx.N;
		strx.add(' ');
		for(;na<22;na++)	strx.add(' ');

		crd	= mols->Atoms.x[jj].r.x[2];
		if(fabs(crd)>0.1){_gcvt(crd,5,sx);}else{_gcvt(crd,3,sx);}
		na	= strlen(sx);
		strx.add(sx,na);
		na	= strx.N;
		strx.add(' ');
		for(;na<33;na++)	strx.add(' ');

		_itoa((mols->Atoms.x[jj].id_Tpz+1),sx,10);
		na	= strlen(sx);
		strx.add(sx,na);
		na	= strx.N;
		strx.add(' ');
		for(;na<39;na++)	strx.add(' ');

		if(mols->Atoms.x[jj].dat.dat!=0x0)
		{
			_itoa((mols->Atoms.x[jj].dat.dat->id_mmff),sx,10);
			strx.add(sx[0]); // 40
			if(sx[1]!='\0') strx.add(sx[1]); else strx.add(' '); // 41
		}else
		{
			strx.add(' '); // 40
			strx.add(' '); // 41
		}
		strx.add(' ');
		strx.add('0');
		strx.add(' ');


		_itoa(jj+1,sx,10);
		na	= strlen(sx);
		strx.add(sx,na);
		na	= strx.N;
		strx.add(' ');
		for(;na<50;na++)	strx.add(' ');

		strx.add(TableZR.Lines.x[mols->Atoms.x[jj].id_Tpz].Ch.x,2);
		na	= strx.N;
		if(strx.x[na-1]=='\0') {strx.x[na-1]= ' ';} else {strx.add(' ');}
		for(;na<54;na++)	strx.add(' ');


		if(mols->Atoms.x[jj].dat.dat!=0x0)
		{
			strx.add("xxxxxxx ",8); // 62-ой символ
									//символы 63-70 – это парциальный заряд на атом
			crd	= mols->Atoms.x[jj].dat.dat->q;
			if(fabs(crd)>0.1){_gcvt(crd,5,sx);}else{_gcvt(crd,3,sx);}
			na	= strlen(sx);
			strx.add(sx,na);
			na	= strx.N;
			strx.add(' ');
			for(;na<71;na++)	strx.add(' ');
			strx.add('\0');

		}else
		{
			strx.add("xxxxxxx  0.0000          ",26);
		}

		mrkstr.pad(strx);
	}
		

	strx.N= 0;
	for(jj=0;jj<mols->Bonds.N;jj++)
	{
		_itoa(mols->Bonds.x[jj].id_Atoms.x[0]+1,sx,10);
		strx.add("     ",5);
		kk	= strlen(sx)-1;
		for(ii=kk;ii>=0;ii--)
		{
			strx.x[strx.N-kk+ii-1]	= sx[ii];
		}
		strx.add(' ');

		_itoa(mols->Bonds.x[jj].id_Atoms.x[1]+1,sx,10);
		strx.add("     ",5);
		kk	= strlen(sx)-1;
		for(ii=kk;ii>=0;ii--)
		{
			strx.x[strx.N-kk+ii-1]	= sx[ii];
		}
		strx.add(' ');

		_itoa(mols->Bonds.x[jj].oder,sx,10);
		strx.add(' ');
		strx.add(sx[0]);
		strx.add("  ",2);

		if(strx.N>76)
		{
			strx.x[strx.N-1]	= '\0';
			mrkstr.pad(strx);
			strx.N	= 0;
		}
	}
	if(strx.N!=0)
	{
		strx.x[strx.N-1]	= '\0';
		mrkstr.pad(strx);
		strx.N	= 0;
	}

	delete mols;
}
//_____________________________________________________________________________________________
void WorkFrame::mrkscript(int id_ml, vecT<vecT <char> > &mrkstr)	// формирует набор строк с hin- описанием молекулы с номерм 'id-ml'
{
	vecT<char> str1("File cretaed by MolRed ");str1.add('\0');
	vecT<char> str2("+++");str2.add('\0');
	vecT<char> strx;
	vecT<int> ishift;
	char sx[80];
	strx.setlen(81);
	strx.x[strx.N-1] = '\0';
	double crd;

	int ii,jj,kk,na,nb;

	//vecT<Molecule> mols;
	Molecule *mols = new Molecule;
	*mols	= *Mls.x[id_ml];
	//mols.setlen(Mls.N);
	//for(ii=0;ii<Mls.N;ii++)
	//{
	//	mols.x[ii] = *Mls.x[ii];
	//}

	/*for(ii=1;ii<Mls.N;ii++)
	{
		//mols.x[0].UniMol(mols.x+ii);
		mols->UniMol(Mls.x[ii]);//mols.x+ii);
	}*/

	na	= mols->Atoms.N;
	nb	= mols->Bonds.N;

	mrkstr.setmem(int(na+nb/5));
	
	_itoa(na,sx,10);
	strx.N	= 0;
	jj	= strlen(sx);
	strx.add(sx,sizeof(char)*jj);
	jj++;
	strx.add(' ');
	for(;jj<6;jj++)	strx.add(' ');
	_itoa(nb,sx,10);
	jj	= strlen(sx)+1;
	strx.add(sx,sizeof(char)*jj);


	mrkstr.add(str1);
	mrkstr.add(str2);
	mrkstr.add(strx);

	nb	= 0;

//	int dem, sgn;

	for(jj=0;jj<mols->Atoms.N;jj++)
	{
		strx.N= 0;

		crd	= mols->Atoms.x[jj].r.x[0];
		if(fabs(crd)>0.1){_gcvt(crd,5,sx);}else{_gcvt(crd,3,sx);}
		na	= strlen(sx);
		strx.add(sx,na);
		na	= strx.N;
		strx.add(' ');
		for(;na<11;na++)	strx.add(' ');

		crd	= mols->Atoms.x[jj].r.x[1];
		if(fabs(crd)>0.1){_gcvt(crd,5,sx);}else{_gcvt(crd,3,sx);}
		na	= strlen(sx);
		strx.add(sx,na);
		na	= strx.N;
		strx.add(' ');
		for(;na<22;na++)	strx.add(' ');

		crd	= mols->Atoms.x[jj].r.x[2];
		if(fabs(crd)>0.1){_gcvt(crd,5,sx);}else{_gcvt(crd,3,sx);}
		na	= strlen(sx);
		strx.add(sx,na);
		na	= strx.N;
		strx.add(' ');
		for(;na<33;na++)	strx.add(' ');

		_itoa((mols->Atoms.x[jj].id_Tpz+1),sx,10);
		na	= strlen(sx);
		strx.add(sx,na);
		na	= strx.N;
		strx.add(' ');
		for(;na<39;na++)	strx.add(' ');

		if(mols->Atoms.x[jj].dat.dat!=0x0)
		{
			_itoa((mols->Atoms.x[jj].dat.dat->id_mmff),sx,10);
			strx.add(sx[0]); // 40
			if(sx[1]!='\0') strx.add(sx[1]); else strx.add(' '); // 41
		}else
		{
			strx.add(' '); // 40
			strx.add(' '); // 41
		}
		strx.add(' ');
		strx.add('0');
		strx.add(' ');


		_itoa(jj+1,sx,10);
		na	= strlen(sx);
		strx.add(sx,na);
		na	= strx.N;
		strx.add(' ');
		for(;na<50;na++)	strx.add(' ');

		strx.add(TableZR.Lines.x[mols->Atoms.x[jj].id_Tpz].Ch.x,2);
		na	= strx.N;
		if(strx.x[na-1]=='\0') {strx.x[na-1]= ' ';} else {strx.add(' ');}
		for(;na<54;na++)	strx.add(' ');


		if(mols->Atoms.x[jj].dat.dat!=0x0)
		{
			strx.add("xxxxxxx ",8); // 62-ой символ
									//символы 63-70 – это парциальный заряд на атом
			crd	= mols->Atoms.x[jj].dat.dat->q;
			if(fabs(crd)>0.1){_gcvt(crd,5,sx);}else{_gcvt(crd,3,sx);}
			na	= strlen(sx);
			strx.add(sx,na);
			na	= strx.N;
			strx.add(' ');
			for(;na<71;na++)	strx.add(' ');
			strx.add('\0');

		}else
		{
			strx.add("xxxxxxx  0.0000          ",26);
		}

		mrkstr.pad(strx);
	}
		

	strx.N= 0;
	for(jj=0;jj<mols->Bonds.N;jj++)
	{
		_itoa(mols->Bonds.x[jj].id_Atoms.x[0]+1,sx,10);
		strx.add("     ",5);
		kk	= strlen(sx)-1;
		for(ii=kk;ii>=0;ii--)
		{
			strx.x[strx.N-kk+ii-1]	= sx[ii];
		}
		strx.add(' ');

		_itoa(mols->Bonds.x[jj].id_Atoms.x[1]+1,sx,10);
		strx.add("     ",5);
		kk	= strlen(sx)-1;
		for(ii=kk;ii>=0;ii--)
		{
			strx.x[strx.N-kk+ii-1]	= sx[ii];
		}
		strx.add(' ');

		_itoa(mols->Bonds.x[jj].oder,sx,10);
		strx.add(' ');
		strx.add(sx[0]);
		strx.add("  ",2);

		if(strx.N>76)
		{
			strx.x[strx.N-1]	= '\0';
			mrkstr.pad(strx);
			strx.N	= 0;
		}
	}
	if(strx.N!=0)
	{
		strx.x[strx.N-1]	= '\0';
		mrkstr.pad(strx);
		strx.N	= 0;
	}

	delete mols;
}
//_____________________________________________________________________________________________
void WorkFrame::pdbscript(vecT< vecT <char> > &pdbstr)
{
	vecT<char> str1("REMARK File cretaed by MolRed ");str1.add('\0');
	vecT<char> atom("ATOM  ");
	vecT<char> hatom("HETATM");
	vecT<char> ter("TER   ");
	vecT<char> end("END");
	vecT<char> strx;
	vecT<char> xs;
	char sx[80];
	float crd;
	int i_ter;
	char cch;

	strx.setmem(96);

	Molecule *mols;
	mols	= Mls.x[0];
	i_ter	= 1;
	if(mols->mol_type==PROTEINE)
	{

		pdbstr.setmem(mols->Atoms.N+10);
		pdbstr.add(str1);

		strx.N	= 0;
		strx.add(atom);
		for(int ii =0;ii<mols->Atoms.N;ii++)
		{
			if(ii>0)
			{
				if(cch!=mols->Atoms.x[ii].dat.dat->amin->getparent()->getparent()->ch)
				{
					strx.N	= 0;
					strx.add(ter);

					_itoa(ii+i_ter,sx,10);
					strx.add("     ");
					strx.N-=strlen(sx);
					strx.add(sx);
					strx.add("             ");
					strx.N	= 17;
					strx.add(&pdbstr.x[pdbstr.N-1].x[17],11);
					strx.add('\0');
					pdbstr.pad(strx);
					strx.N	= 0;
					strx.add(atom);
					i_ter++;
					cch	= mols->Atoms.x[ii].dat.dat->amin->getparent()->getparent()->ch;
				}
			}else
			{
				cch	= mols->Atoms.x[ii].dat.dat->amin->getparent()->getparent()->ch;
			}
			strx.N	= 6;
			_itoa(ii+i_ter,sx,10);
			strx.add("     ");
			strx.N-=strlen(sx);
			strx.add(sx);
			strx.add(' ');
			strx.add(mols->Atoms.x[ii].dat.dat->amin->name);
			strx.N--;
			strx.add("      ");
			strx.N	= 17;
			strx.add(mols->Atoms.x[ii].dat.dat->amin->getparent()->name);
			strx.N--;
			strx.add("    ");
			strx.N	= 21;
			strx.add(mols->Atoms.x[ii].dat.dat->amin->getparent()->getparent()->ch);
			strx.add("    ");
			_itoa(mols->Atoms.x[ii].dat.dat->amin->getparent()->id_ch,sx,10);
			strx.N-=strlen(sx);
			strx.add(sx);
			strx.add("         ");
			strx.N	= 30;

			crd	= (float)mols->Atoms.x[ii].r.x[0];
			if(fabs(crd)>0.1){_gcvt(crd,5,sx);}
			else
			{
				if(fabs(crd)<=1e-10) crd = 0.0;
				_gcvt(crd,3,sx);
				xs.N	= 0;
				xs.add(sx);
				if(xs.fnd('e')!=-1)
				{
					xs.rem(2,xs.N-3);
					xs.add('\0');
					strcpy(sx,xs.x);
				}
			}
			strx.add("        ");
			strx.N-=strlen(sx);
			strx.add(sx);

			crd	= (float)mols->Atoms.x[ii].r.x[1];
			//if(fabs(crd)>0.1){_gcvt(crd,5,sx);}else{_gcvt(crd,3,sx);}
			if(fabs(crd)>0.1){_gcvt(crd,5,sx);}
			else
			{
				if(fabs(crd)<=1e-10) crd = 0.0;
				_gcvt(crd,3,sx);
				xs.N	= 0;
				xs.add(sx);
				if(xs.fnd('e')!=-1)
				{
					xs.rem(2,xs.N-3);
					xs.add('\0');
					strcpy(sx,xs.x);
				}
			}
			strx.add("        ");
			strx.N-=strlen(sx);
			strx.add(sx);

			crd	= (float)mols->Atoms.x[ii].r.x[2];
			//if(fabs(crd)>0.1){_gcvt(crd,5,sx);}else{_gcvt(crd,3,sx);}
			if(fabs(crd)>0.1){_gcvt(crd,5,sx);}
			else
			{
				if(fabs(crd)<=1e-10) crd = 0.0;
				_gcvt(crd,3,sx);
				xs.N	= 0;
				xs.add(sx);
				if(xs.fnd('e')!=-1)
				{
					xs.rem(2,xs.N-3);
					xs.add('\0');
					strcpy(sx,xs.x);
				}
			}
			strx.add("        ");
			strx.N-=strlen(sx);
			strx.add(sx);

			strx.add("                ");
			strx.N	= 68;
			_itoa(mols->Atoms.x[ii].dat.dat->id_mmff,sx,10);
			strx.N-=strlen(sx);
			strx.add(sx);

			strx.add("           ");
			strx.N	= 75;
			crd	= mols->Atoms.x[ii].dat.dat->q;
			if(fabs(crd)>0.1){_gcvt(crd,5,sx);}
			else
			{
				if(fabs(crd)<=1e-10) crd = 0.0;
				_gcvt(crd,3,sx);
				xs.N	= 0;
				xs.add(sx);
				if(xs.fnd('e')!=-1)
				{
					xs.rem(2,xs.N-3);
					xs.add('\0');
					strcpy(sx,xs.x);
				}
			}
			//_gcvt(crd,3,sx);
			strx.N-=strlen(sx);
			strx.add(sx);

			strx.add("     ");
			strx.N	= 78;
			sx[0]	= TableZR.Lines.x[mols->Atoms.x[ii].id_Tpz].Ch.x[0];
			sx[1]	= TableZR.Lines.x[mols->Atoms.x[ii].id_Tpz].Ch.x[1];
			sx[2]	= '\0';
			strx.N	-= sx[1]=='\0' ? 1 : 2;
			strx.add(sx);
			//strx.N	= 78;
			strx.add('\0');

			pdbstr.pad(strx);
		}
		strx.N	= 0;
		strx.add(ter);
		_itoa(mols->Atoms.N+i_ter,sx,10);
		strx.add("     ");
		strx.N-=strlen(sx);
		strx.add(sx);
		strx.add("                                   ");
		strx.N	= 17;
		strx.add(&pdbstr.x[pdbstr.N-1].x[17],11);
		strx.add('\0');
		pdbstr.pad(strx);



		if(Mls.N>1)
		{
			int kk;
			kk	= Mls.x[0]->Atoms.N+i_ter;
			strx.N	= 0;
			strx.add(hatom);
			for(int jj=1;jj<Mls.N;jj++)
			{
				mols	= Mls.x[jj];
				for(int ii=0;ii<mols->Atoms.N;ii++)
				{
					kk++;
					if(kk<99999)
					{
						strx.N	= 6;
						_itoa(kk,sx,10);
						strx.add("     ");
						strx.N-=strlen(sx);
						strx.add(sx);
						strx.add("  X   XXX X 000          ");
						strx.N	= 30;

						crd	= mols->Atoms.x[ii].r.x[0];
						//if(fabs(crd)>0.1){_gcvt(crd,5,sx);}else{_gcvt(crd,3,sx);}
						if(fabs(crd)>0.1){_gcvt(crd,5,sx);}
						else
						{
							if(fabs(crd)<=1e-10) crd = 0.0;
							_gcvt(crd,3,sx);
							xs.N	= 0;
							xs.add(sx);
							if(xs.fnd('e')!=-1)
							{
								xs.rem(2,xs.N-3);
								xs.add('\0');
								strcpy(sx,xs.x);
							}
						}
						strx.add("        ");
						strx.N-=strlen(sx);
						strx.add(sx);

						crd	= mols->Atoms.x[ii].r.x[1];
						//if(fabs(crd)>0.1){_gcvt(crd,5,sx);}else{_gcvt(crd,3,sx);}
						if(fabs(crd)>0.1){_gcvt(crd,5,sx);}
						else
						{
							if(fabs(crd)<=1e-10) crd = 0.0;
							_gcvt(crd,3,sx);
							xs.N	= 0;
							xs.add(sx);
							if(xs.fnd('e')!=-1)
							{
								xs.rem(2,xs.N-3);
								xs.add('\0');
								strcpy(sx,xs.x);
							}
						}
						strx.add("        ");
						strx.N-=strlen(sx);
						strx.add(sx);

						crd	= mols->Atoms.x[ii].r.x[2];
						//if(fabs(crd)>0.1){_gcvt(crd,5,sx);}else{_gcvt(crd,3,sx);}
						if(fabs(crd)>0.1){_gcvt(crd,5,sx);}
						else
						{
							if(fabs(crd)<=1e-10) crd = 0.0;
							_gcvt(crd,3,sx);
							xs.N	= 0;
							xs.add(sx);
							if(xs.fnd('e')!=-1)
							{
								xs.rem(2,xs.N-3);
								xs.add('\0');
								strcpy(sx,xs.x);
							}
						}
						strx.add("        ");
						strx.N-=strlen(sx);
						strx.add(sx);

						strx.add("                ");
						strx.N	= 68;
						if(mols->Atoms.x[ii].dat.dat!=0x0)
						{
							_itoa(mols->Atoms.x[ii].dat.dat->id_mmff,sx,10);
						}else
						{
							sx[0]	= '-';
							sx[1]	= '1';
							sx[2]	= '\0';
						}
						strx.N-=strlen(sx);
						strx.add(sx);

						strx.add("           ");
						strx.N	= 75;
						if(mols->Atoms.x[ii].dat.dat!=0x0)
						{
							crd	= mols->Atoms.x[ii].dat.dat->q;
							if(fabs(crd)>0.1){_gcvt(crd,5,sx);}
							else
							{
								if(fabs(crd)<=1e-10) crd = 0.0;
								_gcvt(crd,3,sx);
								xs.N	= 0;
								xs.add(sx);
								if(xs.fnd('e')!=-1)
								{
									xs.rem(2,xs.N-3);
									xs.add('\0');
									strcpy(sx,xs.x);
								}
							}
						}else
						{
							sx[0]	= '0';
							sx[1]	= '\0';
						}
						//_gcvt(crd,3,sx);
						strx.N-=strlen(sx);
						strx.add(sx);

						strx.add("     ");
						strx.N	= 78;
						sx[0]	= TableZR.Lines.x[mols->Atoms.x[ii].id_Tpz].Ch.x[0];
						sx[1]	= TableZR.Lines.x[mols->Atoms.x[ii].id_Tpz].Ch.x[1];
						sx[2]	= '\0';
						strx.N	-= sx[1]=='\0' ? 1 : 2;
						strx.add(sx);
						//strx.N	= 78;
						strx.add('\0');
						pdbstr.pad(strx);

					}else
					{
						jj	= Mls.N;
						break;
					}
				}
			}/**/
		}


		strx.N	= 0;
		strx.add(end);
		strx.add('\0');
		pdbstr.pad(strx);
	}else
	{
		pdbstr.N = 0;
	}


	mols	= 0x0;
}
//_____________________________________________________________________________________________
void double2char(double x, char * sx, int pres)
{
	int dec,sgn;
	sx	= _fcvt(x,pres,&dec,&sgn);
	vecT<char> ss;
	ss.add(sx,strlen(sx));
	ss.add('.',dec);
	if(sgn!=0) ss.add('-',0);
	
}

//_____________________________________________________________________________________________
bool WorkFrame::writeFile(const QString &fileName,int id_ml)
{
	FILE *fio;
	char c	= '\n';
	vecT<vecT <char> > hinstr;
	QByteArray qba;
	vecT<char> fnm;
	int lq,inp;

	qba	= fileName.toLatin1();
	lq	= qba.length();

	fnm.setlen(lq+1);
	fnm.x[lq]	= '\0';
	for(int i=0;i<lq;i++) fnm.x[i]	= qba[i];

	inp	= -1;
	for(int i=0;i<lq;i++) 
	{
		fnm.x[i]	= qba[i];
		inp	= fnm.x[i]=='.' ? i : inp;
	}

	if (strcmp(fnm.x+inp,".hin")==0)
	{
		hinscript(id_ml,hinstr);
	}else
	{
		if(strcmp(fnm.x+inp,".xyz")==0)
		{
			xyzscript(id_ml,hinstr);
		}else 
		{
			return false;
		}
	}

	//hinscript(id_ml,hinstr);
	
	fio	= fopen(fnm.x,"w");
	if (fio!=NULL)
	{
		int ii;
		for(ii=0;ii<hinstr.N;ii++)
		{
			fprintf(fio,"%s%c",hinstr.x[ii].x,c);
		}
		fclose(fio);
		return true;
	}
	else
	{
		return false;
	}
}

//_____________________________________________________________________________________________
bool WorkFrame::writeFile(const QString &fileName)
{
	FILE *fio;
	char c	= '\n';
	vecT<vecT <char> > textstr;
	QByteArray qba;
	vecT<char> fnm;
	int lq,inp;
	

	qba	= fileName.toLatin1();
	lq	= qba.length();

	fnm.setlen(lq+1);
	fnm.x[lq]	= '\0';
	inp	= -1;
	for(int i=0;i<lq;i++) 
	{
		fnm.x[i]	= qba[i];
		inp	= fnm.x[i]=='.' ? i : inp;
	}

	if (strcmp(fnm.x+inp,".hin")==0)
	{
		hinscript(textstr);
	}else
	{
		if (strcmp(fnm.x+inp,".mrk")==0)
		{
			mrkscript(textstr);
		}else
		{
			if((strcmp(fnm.x+inp,".xyz")==0))
			{
				xyzscript(textstr);
			}else
			{
				if((strcmp(fnm.x+inp,".pdb")==0))
				{
					pdbscript(textstr);
				}
				else return false;
			}
				
		}
	}
	
	fio	= fopen(fnm.x,"w");
	if (fio!=NULL)
	{
		int ii;
		for(ii=0;ii<textstr.N;ii++)
		{
			fprintf(fio,"%s%c",textstr.x[ii].x,c);
		}
		fclose(fio);
		return true;
	}
	else
	{
		return false;
	}
}
//_____________________________________________________________________________________________
//_____________________________________________________________________________________________



//_____________________________________________________________________________________________
//_____________________________________________________________________________________________



//_____________________________________________________________________________________________
//_____________________________________________________________________________________________


//__________________________________________________________________________________________________

#endif