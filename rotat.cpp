#ifndef ROTAT_CPP
#define ROTAT_CPP

#include<QDialog>
#include<QtGui>
#include<QLabel>
#include<QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
//#include<QVector>
//#include<QPushButton>

#include <math.h>
#include "rotat.h"

RotatWin::RotatWin(QDialog *parent ) : QDialog(parent)
{

	setWindowIcon(QIcon(":/images/turn.png"));
	setWindowTitle(tr("Rotation Control"));

	QDoubleValidator QDV(this);

	QDV.setNotation(QDoubleValidator::ScientificNotation);

	qa.x[0]	= 1.0;
	qa.x[1]	= 1.0;
	qa.x[2] = 1.0;


	qa.nrml();

	qc	= 0.0;

	alf	= 0.0;
	d_alf	= 0.05;

	dl		= 0.0;
	d_dl	= 0.05;

	angleLabel	= new QLabel(tr("Rotation angle [rad] :"));
	angleEdit	= new QLineEdit;
	angleLabel->setBuddy(angleEdit);

	d_angleLabel	= new QLabel(tr("Increment value of angle [rad] :"));
	d_angleEdit	= new QLineEdit;
	d_angleLabel->setBuddy(d_angleEdit);


	displLabel	= new QLabel(tr("Displacement [Angst] :"));
	displEdit	= new QLineEdit;
	displLabel->setBuddy(angleEdit);

	d_displLabel= new QLabel(tr("Incremnt value of displ.[Angst] :"));
	d_displEdit	= new QLineEdit;
	d_displLabel->setBuddy(angleEdit);

	qaxLabel	= new QLabel(tr("x-proection of rotation axis :"));
	qaxEdit	= new QLineEdit;
	qaxLabel->setBuddy(qaxEdit);

	qayLabel	= new QLabel(tr("y-proection of rotation axis :"));
	qayEdit	= new QLineEdit;
	qayLabel->setBuddy(qayEdit);

	qazLabel	= new QLabel(tr("z-proection of rotation axis :"));
	qazEdit	= new QLineEdit;
	qazLabel->setBuddy(qazEdit);

	cqxLabel	= new QLabel(tr("x-proection of translation vector :"));
	cqxEdit	= new QLineEdit;
	cqxLabel->setBuddy(cqxEdit);

	cqyLabel	= new QLabel(tr("y-proection of translation vector :"));
	cqyEdit	= new QLineEdit;
	cqyLabel->setBuddy(cqyEdit);

	cqzLabel	= new QLabel(tr("z-proection of translation vector :"));
	cqzEdit	= new QLineEdit;
	cqzLabel->setBuddy(cqzEdit);


	QHBoxLayout *top0Layout	= new QHBoxLayout;
	top0Layout->addWidget(displLabel);
	top0Layout->addWidget(displEdit);
	top0Layout->addStretch();
	top0Layout->addWidget(d_displLabel);
	top0Layout->addWidget(d_displEdit);
	top0Layout->addStretch();

	QHBoxLayout *topLayout	= new QHBoxLayout;
	topLayout->addWidget(angleLabel);
	topLayout->addWidget(angleEdit);
	topLayout->addStretch();
	topLayout->addWidget(d_angleLabel);
	topLayout->addWidget(d_angleEdit);
	topLayout->addStretch();

	QHBoxLayout *qx_leftLayout	= new QHBoxLayout;
	qx_leftLayout->addWidget(qaxLabel);
	qx_leftLayout->addWidget(qaxEdit);
	qx_leftLayout->addStretch();

	QHBoxLayout *qy_leftLayout	= new QHBoxLayout;
	qy_leftLayout->addWidget(qayLabel);
	qy_leftLayout->addWidget(qayEdit);
	qy_leftLayout->addStretch();

	QHBoxLayout *qz_leftLayout	= new QHBoxLayout;
	qz_leftLayout->addWidget(qazLabel);
	qz_leftLayout->addWidget(qazEdit);
	qz_leftLayout->addStretch();

	QHBoxLayout *cx_rigthLayout	= new QHBoxLayout;
	cx_rigthLayout->addWidget(cqxLabel);
	cx_rigthLayout->addWidget(cqxEdit);
	cx_rigthLayout->addStretch();

	QHBoxLayout *cy_rigthLayout	= new QHBoxLayout;
	cy_rigthLayout->addWidget(cqyLabel);
	cy_rigthLayout->addWidget(cqyEdit);
	cy_rigthLayout->addStretch();

	QHBoxLayout *cz_rigthLayout	= new QHBoxLayout;
	cz_rigthLayout->addWidget(cqzLabel);
	cz_rigthLayout->addWidget(cqzEdit);
	cz_rigthLayout->addStretch();

	QVBoxLayout *leftLayout	= new QVBoxLayout;
	leftLayout->addLayout(qx_leftLayout);
	leftLayout->addLayout(qy_leftLayout);
	leftLayout->addLayout(qz_leftLayout);

	QVBoxLayout *rigthLayout	= new QVBoxLayout;
	rigthLayout->addLayout(cx_rigthLayout);
	rigthLayout->addLayout(cy_rigthLayout);
	rigthLayout->addLayout(cz_rigthLayout);

	QHBoxLayout *bottomLayout	= new QHBoxLayout;
	bottomLayout->addLayout(leftLayout);
	bottomLayout->addLayout(rigthLayout);

	QVBoxLayout *mainLayout	= new QVBoxLayout;

	mainLayout->addLayout(top0Layout);
	mainLayout->addLayout(topLayout);
	mainLayout->addLayout(bottomLayout);

	setLayout(mainLayout);


	angleEdit->setValidator(&QDV);
	d_angleEdit->setValidator(&QDV);
	qaxEdit->setValidator(&QDV);
	qayEdit->setValidator(&QDV);
	qazEdit->setValidator(&QDV);
	cqxEdit->setValidator(&QDV);
	cqyEdit->setValidator(&QDV);
	cqzEdit->setValidator(&QDV);


	update();


	connect(angleEdit,SIGNAL(editingFinished ()),this,SLOT(changhe_angle()));
	connect(d_angleEdit,SIGNAL(editingFinished ()),this,SLOT(changhe_d_angle()));
	connect(displEdit,SIGNAL(editingFinished ()),this,SLOT(changhe_displ()));
	connect(d_displEdit,SIGNAL(editingFinished ()),this,SLOT(changhe_d_displ()));
	connect(qaxEdit,SIGNAL(editingFinished ()),this,SLOT(changhe_qax()));
	connect(qayEdit,SIGNAL(editingFinished ()),this,SLOT(changhe_qay()));
	connect(qazEdit,SIGNAL(editingFinished ()),this,SLOT(changhe_qaz()));
	connect(cqxEdit,SIGNAL(editingFinished ()),this,SLOT(changhe_cqx()));
	connect(cqyEdit,SIGNAL(editingFinished ()),this,SLOT(changhe_cqy()));
	connect(cqzEdit,SIGNAL(editingFinished ()),this,SLOT(changhe_cqz()));

	setWindowFlags(Qt::WindowStaysOnTopHint);

}

void RotatWin::update()
{
	angleEdit->setText(QString("%1 ").arg(alf, 0, 'E', 4));
	d_angleEdit->setText(QString("%1 ").arg(d_alf, 0, 'E', 4));

	displEdit->setText(QString("%1 ").arg(dl, 0, 'E', 4));
	d_displEdit->setText(QString("%1 ").arg(d_dl, 0, 'E', 4));

	qaxEdit->setText(QString("%1 ").arg(qa.x[0], 0, 'E', 4));
	qayEdit->setText(QString("%1 ").arg(qa.x[1], 0, 'E', 4));
	qazEdit->setText(QString("%1 ").arg(qa.x[2], 0, 'E', 4));

	cqxEdit->setText(QString("%1 ").arg(qc.x[0], 0, 'E', 4));
	cqyEdit->setText(QString("%1 ").arg(qc.x[1], 0, 'E', 4));
	cqzEdit->setText(QString("%1 ").arg(qc.x[2], 0, 'E', 4));
}


void RotatWin::SetDis(vec3db &c)
{
	qc	= c;
	update();
	//emit changhed();
}
void RotatWin::SetAxis(vec3db &qa_)
{
	qa	= qa_;
	update();
	//emit changhed();
}
void RotatWin::SetInc(double d)
{
	d_alf	= d;
	update();
}
void RotatWin::SetAlfa(double a)
{
	alf	= a;
	update();
}

void RotatWin::SetDsp(double a)
{
	dl	= a;
	update();
}

double RotatWin::GetInc()
{
	return d_alf;
}

double RotatWin::GetAlfa()
{
	return alf;	
}

vec3db RotatWin::GetDis()
{
	return qc;	
}

double RotatWin::GetDsp()
{
	return dl;	
}
vec3db RotatWin::GetAxis()
{
	vec3db ax(qa.x[0],qa.x[1],qa.x[2]);
	return ax;	
}

void RotatWin::inc()
{
	alf	+=d_alf;
	update();
	emit changhed();
}

void RotatWin::dec()
{
	alf	-=d_alf;
	update();
	emit changhed();
}

void RotatWin::incdis()
{
	dl	+=d_dl;
	update();
	emit changhed();
}

void RotatWin::decdis()
{
	dl	-=d_dl;
	update();
	emit changhed();
}

void RotatWin::changhe_angle()
{
	alf	= angleEdit->text().toDouble();
	emit changhed();
}

void RotatWin::changhe_displ()
{
	dl	= displEdit->text().toDouble();
	emit changhed();
}

void RotatWin::changhe_d_displ()
{
	d_dl	= d_displEdit->text().toDouble();
	emit changhed();
}

void RotatWin::changhe_d_angle()
{
	d_alf	= d_angleEdit->text().toDouble();
	emit changhed();
}

void RotatWin::changhe_qax()
{
	qa.x[0]	= qaxEdit->text().toDouble();
	emit changhed();
}
void RotatWin::changhe_qay()
{
	qa.x[1]	= qayEdit->text().toDouble();
	emit changhed();
}
void RotatWin::changhe_qaz()
{
	qa.x[2]	= qazEdit->text().toDouble();
	emit changhed();
}

void RotatWin::changhe_cqx()
{
	qc.x[0]	= cqxEdit->text().toDouble();
	emit changhed();
}
void RotatWin::changhe_cqy()
{
	qc.x[1]	= cqyEdit->text().toDouble();
	emit changhed();
}
void RotatWin::changhe_cqz()
{
	qc.x[2]	= cqzEdit->text().toDouble();
	emit changhed();
}
bool RotatWin::isZeroSpin()
{
	return fabs(alf)<1e-13;//(alf<d_alf)&&(alf>-d_alf);
}

bool RotatWin::isZeroDisp()
{
	return fabs(dl)<1e-13;//(alf<d_alf)&&(alf>-d_alf);
}
#endif
