#ifndef MENDELEEVTABLE_CPP
#define MENDELEEVTABLE_CPP

#include<QtGui>
#include <QHBoxLayout>
#include <QVBoxLayout>
//#include<QVector>
//#include"linalg.h"
#include"MendeleevTable.h"

MendeleevTable::MendeleevTable(QDialog *parent ) : QDialog(parent)
{

	NTotalAtoms	 = 110;
	Buttons	= new  QPushButton [NTotalAtoms];//QPushButton [NTotalAtoms];	
	//Buttons.(NTotalAtoms);
	Buttons[0].setText(tr("H"));
	Buttons[1].setText(tr("He")); 
	Buttons[2].setText(tr("Li")); 
	Buttons[3].setText(tr("Be")); 
	Buttons[4].setText(tr("B"));  
	Buttons[5].setText(tr("C"));  
	Buttons[6].setText(tr("N"));
	Buttons[7].setText(tr("O"));  
	Buttons[8].setText(tr("F"));  
	Buttons[9].setText(tr("Ne")); 
	Buttons[10].setText(tr("Na")); 
	Buttons[11].setText(tr("Mg")); 
	Buttons[12].setText(tr("Al")); 
	Buttons[13].setText(tr("Si")); 
	Buttons[14].setText(tr("P"));  
	Buttons[15].setText(tr("S"));
	Buttons[16].setText(tr("Cl")); 
	Buttons[17].setText(tr("Ar")); 
	Buttons[18].setText(tr("K"));  
	Buttons[19].setText(tr("Ca")); 
	Buttons[20].setText(tr("Sc")); 
	Buttons[21].setText(tr("Ti")); 
	Buttons[22].setText(tr("V"));  
	Buttons[23].setText(tr("Cr")); 
	Buttons[24].setText(tr("Mn")); 
	Buttons[25].setText(tr("Fe")); 
	Buttons[26].setText(tr("Co")); 
	Buttons[27].setText(tr("Ni")); 
	Buttons[28].setText(tr("Cu")); 
	Buttons[29].setText(tr("Zn")); 
	Buttons[30].setText(tr("Ga")); 
	Buttons[31].setText(tr("Ge")); 
	Buttons[32].setText(tr("As")); 
	Buttons[33].setText(tr("Se")); 
	Buttons[34].setText(tr("Br")); 
	Buttons[35].setText(tr("Kr")); 
	Buttons[36].setText(tr("Rb")); 
	Buttons[37].setText(tr("Sr")); 
	Buttons[38].setText(tr("Y"));  
	Buttons[39].setText(tr("Zr")); 
	Buttons[40].setText(tr("Nb")); 
	Buttons[41].setText(tr("Mo")); 
	Buttons[42].setText(tr("Tc")); 
	Buttons[43].setText(tr("Ru")); 
	Buttons[44].setText(tr("Rh")); 
	Buttons[45].setText(tr("Pd")); 
	Buttons[46].setText(tr("Ag")); 
	Buttons[47].setText(tr("Cd")); 
	Buttons[48].setText(tr("In")); 
	Buttons[49].setText(tr("Sn")); 
	Buttons[50].setText(tr("Sb")); 
	Buttons[51].setText(tr("Te")); 
	Buttons[52].setText(tr("I")); 
	Buttons[53].setText(tr("Xe")); 
	Buttons[54].setText(tr("Cs")); 
	Buttons[55].setText(tr("Ba")); 
	Buttons[56].setText(tr("La")); 
	Buttons[57].setText(tr("Ce")); 
	Buttons[58].setText(tr("Pr")); 
	Buttons[59].setText(tr("Nd")); 
	Buttons[60].setText(tr("Pm")); 
	Buttons[61].setText(tr("Sm")); 
	Buttons[62].setText(tr("Eu")); 
	Buttons[63].setText(tr("Gd")); 
	Buttons[64].setText(tr("Tb")); 
	Buttons[65].setText(tr("Dy")); 
	Buttons[66].setText(tr("Ho")); 
	Buttons[67].setText(tr("Er")); 
	Buttons[68].setText(tr("Tm")); 
	Buttons[69].setText(tr("Yb")); 
	Buttons[70].setText(tr("Lu")); 
	Buttons[71].setText(tr("Hf")); 
	Buttons[72].setText(tr("Ta")); 
	Buttons[73].setText(tr("W")); 
	Buttons[74].setText(tr("Re")); 
	Buttons[75].setText(tr("Os")); 
	Buttons[76].setText(tr("Ir")); 
	Buttons[77].setText(tr("Pt")); 
	Buttons[78].setText(tr("Au")); 
	Buttons[79].setText(tr("Hg")); 
	Buttons[80].setText(tr("Tl")); 
	Buttons[81].setText(tr("Pb")); 
	Buttons[82].setText(tr("Bi")); 
	Buttons[83].setText(tr("Po")); 
	Buttons[84].setText(tr("At")); 
	Buttons[85].setText(tr("Rn")); 
	Buttons[86].setText(tr("Fr")); 
	Buttons[87].setText(tr("Ra")); 
	Buttons[88].setText(tr("Ac")); 
	Buttons[89].setText(tr("Th")); 
	Buttons[90].setText(tr("Pa")); 
	Buttons[91].setText(tr("U"));  
	Buttons[92].setText(tr("Np")); 
	Buttons[93].setText(tr("Pu")); 
	Buttons[94].setText(tr("Am")); 
	Buttons[95].setText(tr("Cm")); 
	Buttons[96].setText(tr("Bk")); 
	Buttons[97].setText(tr("Cf")); 
	Buttons[98].setText(tr("Es")); 
	Buttons[99].setText(tr("Fm")); 
	Buttons[100].setText(tr("Md")); 
	Buttons[101].setText(tr("No")); 
	Buttons[102].setText(tr("Lr")); 
	Buttons[103].setText(tr("Rf")); 
	Buttons[104].setText(tr("Db")); 
	Buttons[105].setText(tr("Sg")); 
	Buttons[106].setText(tr("Bh")); 
	Buttons[107].setText(tr("Hs")); 
	Buttons[108].setText(tr("Mt")); 
	Buttons[109].setText(tr("Ds")); 
	//Buttons[110].setText(tr("Rg")); 

	int ii;
	for(ii =0;ii<NTotalAtoms;ii++)
	{
		Buttons[ii].setFixedWidth(36);
	}

	setWindowTitle(tr("Add Atom"));

	QVBoxLayout *Vlayout =new QVBoxLayout;

	QHBoxLayout *layout	= new QHBoxLayout [12];
	layout[0].addWidget(&Buttons[0]);
	layout[0].addStretch();
	layout[0].addWidget(&Buttons[1]);
	
	for(ii =2;ii<9;ii++)
	{
		layout[1].addWidget(&Buttons[ii]);
	}
	layout[1].addStretch();
	layout[1].addWidget(&Buttons[9]);
	
	for(ii =10;ii<17;ii++)
	{
		layout[2].addWidget(&Buttons[ii]);
	}
	layout[2].addStretch();
	layout[2].addWidget(&Buttons[17]);
	
	for(ii =18;ii<28;ii++)
	{
		layout[3].addWidget(&Buttons[ii]);
	}
	layout[3].addStretch();
	//layout[3].addWidget(&Buttons[27]);

	for(ii =28;ii<35;ii++)
	{
		layout[4].addWidget(&Buttons[ii]);
	}
	layout[4].addStretch();
	layout[4].addWidget(&Buttons[35]);
	
	for(ii =36;ii<46;ii++)
	{
		layout[5].addWidget(&Buttons[ii]);
	}
	layout[5].addStretch();
	
	for(ii =46;ii<53;ii++)
	{
		layout[6].addWidget(&Buttons[ii]);
	}
	layout[6].addStretch();
	layout[6].addWidget(&Buttons[53]);


	for(ii =54;ii<57;ii++)
	{
		layout[7].addWidget(&Buttons[ii]);
	}
	for(ii =71;ii<78;ii++)
	{
		layout[7].addWidget(&Buttons[ii]);
	}
	layout[7].addStretch();
	//layout[6].addWidget(&Buttons[53]);

	for(ii =78;ii<85;ii++)
	{
		layout[8].addWidget(&Buttons[ii]);
	}
	layout[8].addStretch();
	layout[8].addWidget(&Buttons[85]);


	for(ii =86;ii<89;ii++)
	{
		layout[9].addWidget(&Buttons[ii]);
	}
	for(ii =103;ii<110;ii++)
	{
		layout[9].addWidget(&Buttons[ii]);
	}
	layout[9].addStretch();

	for(ii =57;ii<71;ii++)
	{
		Buttons[ii].setFixedWidth(24);
		layout[10].addWidget(&Buttons[ii]);
	}
	layout[10].addStretch();

	for(ii =89;ii<103;ii++)
	{
		Buttons[ii].setFixedWidth(24);
		layout[11].addWidget(&Buttons[ii]);
	}
	layout[11].addStretch();


	
    for (ii=0;ii<10;ii++)
	{
		Vlayout->addLayout(&layout[ii]);
	}
	
	Vlayout->addStretch();

	Vlayout->addLayout(&layout[10]);
	Vlayout->addLayout(&layout[11]);

	//Vlayout->addStretch();

	setLayout(Vlayout);


	for (ii=0;ii<110;ii++)
	{
		connect(&Buttons[ii],SIGNAL(pressed()),this,SLOT(clik_analize()));
		//connect(&Buttons[ii],SIGNAL(clicked()),this,SLOT(my_close()));
	}

	selAtomID	= -1;
	helpID		= -1;

	setWindowIcon(QIcon(":/images/atom.png"));
	setWindowFlags(Qt::WindowStaysOnTopHint);

	font_unpressed.setBold(false);
	//font_unpressed.setWeight(10);
	font_pressed.setBold(true);
	//font_pressed.setWeight(15);

	/*for (ii=0;ii<110;ii++)
	{
		Buttons[ii].setFont(font_unpressed);
	}*/


}

void MendeleevTable::clik_analize()
{
	int id_old;
	bool ch = true;
	int ii;
	for(ii=0;(ii<NTotalAtoms)&&(ch);ii++)
	{
		ch = !(Buttons[ii].isDown());
	}
	ii--;
	helpID	= (!ch) ? ii : -1;
	id_old	= selAtomID;
	selAtomID	= helpID;

	if (id_old!=-1){ Buttons[id_old].setFont(font_unpressed);}
	Buttons[selAtomID].setFont(font_pressed);

	emit detatom();
}
void MendeleevTable::closeEvent(QCloseEvent * event)
{
	emit desatom();
	if(selAtomID!=-1)	Buttons[selAtomID].setFont(font_unpressed);
	selAtomID	= -1;
	event->accept();
}

/*void MendeleevTable::my_close()
{
	selAtomID	= helpID;
	emit id_changed(selAtomID);
	close();
}*/

#endif