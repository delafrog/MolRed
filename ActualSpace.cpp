#ifndef ACTUALSPACE_CPP
#define ACTUALSPACE_CPP

#include<QDialog>
#include<QtGui>
#include<QLabel>
#include<QLineEdit>
#include <QRadioButton>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
//#include<QVector>
//#include<QPushButton>
#include "ActualSpace.h"
#include <math.h>

ActualSpace::ActualSpace(QDialog *parent) : QDialog(parent)
{

	setWindowIcon(QIcon(":/images/actcube.png"));

	QDoubleValidator QDV(this);

	QDV.setNotation(QDoubleValidator::ScientificNotation);


	rc	= 0.0;
	abc	= 1.0;

	rcxLabel	= new QLabel(tr("&x component of center:"));
	rcxEdit		= new QLineEdit;
	rcxLabel->setBuddy(rcxEdit);

	rcyLabel	= new QLabel(tr("&y component of center:"));
	rcyEdit		= new QLineEdit;
	rcyLabel->setBuddy(rcyEdit);

	rczLabel	= new QLabel(tr("&z component of center:"));
	rczEdit		= new QLineEdit;
	rczLabel->setBuddy(rczEdit);

	aLabel		= new QLabel(tr("side &a :"));
	aEdit		= new QLineEdit;
	aLabel->setBuddy(aEdit);

	bLabel		= new QLabel(tr("side &b :"));
	bEdit		= new QLineEdit;
	bLabel->setBuddy(bEdit);

	cLabel		= new QLabel(tr("side &c :"));
	cEdit		= new QLineEdit;
	cLabel->setBuddy(cEdit);

	QHBoxLayout *top0Layout	= new QHBoxLayout;
	top0Layout->addWidget(rcxLabel);
	top0Layout->addWidget(rcxEdit);
	top0Layout->addStretch();
	top0Layout->addWidget(aLabel);
	top0Layout->addWidget(aEdit);
	top0Layout->addStretch();

	QHBoxLayout *top1Layout	= new QHBoxLayout;
	top1Layout->addWidget(rcyLabel);
	top1Layout->addWidget(rcyEdit);
	top1Layout->addStretch();
	top1Layout->addWidget(bLabel);
	top1Layout->addWidget(bEdit);
	top1Layout->addStretch();

	QHBoxLayout *top2Layout	= new QHBoxLayout;
	top2Layout->addWidget(rczLabel);
	top2Layout->addWidget(rczEdit);
	top2Layout->addStretch();
	top2Layout->addWidget(cLabel);
	top2Layout->addWidget(cEdit);
	top2Layout->addStretch();

	OnOffViz	= new QRadioButton(tr("On/Off &Visualization of cube"));
	SetCentr	= new QPushButton(tr("Set Cube2&Orbit"));
	
	QHBoxLayout *top3Layout	= new QHBoxLayout;
	top3Layout->addWidget(OnOffViz);
	top3Layout->addStretch();
	top3Layout->addWidget(SetCentr);
	//top3Layout->addStretch();

	QVBoxLayout *VLayout	= new QVBoxLayout;
	VLayout->addLayout(top0Layout);
	VLayout->addLayout(top1Layout);
	VLayout->addLayout(top2Layout);
	VLayout->addLayout(top3Layout);

	

	

	setLayout(VLayout);

	rcxEdit->setValidator(&QDV);
	rcyEdit->setValidator(&QDV);
	rczEdit->setValidator(&QDV);

	aEdit->setValidator(&QDV);
	bEdit->setValidator(&QDV);
	cEdit->setValidator(&QDV);

	
	


	update();

	connect(rcxEdit,SIGNAL(editingFinished ()),this,SLOT(rcx_changhe()));
	connect(rcyEdit,SIGNAL(editingFinished ()),this,SLOT(rcy_changhe()));
	connect(rczEdit,SIGNAL(editingFinished ()),this,SLOT(rcz_changhe()));

	connect(aEdit,SIGNAL(editingFinished ()),this,SLOT(a_changhe()));
	connect(bEdit,SIGNAL(editingFinished ()),this,SLOT(b_changhe()));
	connect(cEdit,SIGNAL(editingFinished ()),this,SLOT(c_changhe()));

	connect(OnOffViz,SIGNAL(clicked ()),this,SIGNAL(OnOff_changhe()));
	connect(SetCentr,SIGNAL(clicked ()),this,SIGNAL(rc_set()));

	setWindowFlags(Qt::WindowStaysOnTopHint);

	setWindowTitle(tr("Actual Space Cube"));
	
}


void ActualSpace::update()
{
	rcxEdit->setText(QString("%1 ").arg(rc.x[0], 0, 'E', 4));
	rcyEdit->setText(QString("%1 ").arg(rc.x[1], 0, 'E', 4));
	rczEdit->setText(QString("%1 ").arg(rc.x[2], 0, 'E', 4));

	aEdit->setText(QString("%1 ").arg(abc.x[0], 0, 'E', 4));
	bEdit->setText(QString("%1 ").arg(abc.x[1], 0, 'E', 4));
	cEdit->setText(QString("%1 ").arg(abc.x[2], 0, 'E', 4));
}


void ActualSpace::rcx_changhe()
{
	rc.x[0]	= rcxEdit->text().toDouble();
	emit changhed();
}

void ActualSpace::rcy_changhe()
{
	rc.x[1]	= rcyEdit->text().toDouble();
	emit changhed();
}

void ActualSpace::rcz_changhe()
{
	rc.x[2]	= rczEdit->text().toDouble();
	emit changhed();
}

void ActualSpace::a_changhe()
{
	abc.x[0]	= aEdit->text().toDouble();
	emit changhed();
}

void ActualSpace::b_changhe()
{
	abc.x[1]	= bEdit->text().toDouble();
	emit changhed();
}

void ActualSpace::c_changhe()
{
	abc.x[2]	= cEdit->text().toDouble();
	emit changhed();
}

//void ActualSpace::OnOff_changhe()
//{
	//abc.x[2]	= cEdit->text().toDouble();
	//emit changhed();
//}
//void ActualSpace::set_rcx(double x)
//{
//	d_alf	= d_angleEdit->text().toDouble();
//	emit changhed();
//}

#endif