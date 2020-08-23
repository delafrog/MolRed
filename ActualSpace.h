#ifndef ACTUALSPACE_H
#define ACTUALSPACE_H


//#include<QVector>
//#include<QPushButton>
#include <QDialog>
#include "linalg.h"

class QLineEdit;
class QLabel;
class QRadioButton;
class QPushButton;


class ActualSpace : public QDialog
{
	Q_OBJECT
public:
	ActualSpace(QDialog *parent = 0);

	vec3db getrc(){return rc;}
	vec3db getabc() {return abc;}

	void set_rc(vec3db &r){rc = r; update(); emit changhed();}
	//void set_rcx(double x);

public slots:
	void rcx_changhe();
	void rcy_changhe();
	void rcz_changhe();
	void a_changhe();
	void b_changhe();
	void c_changhe();


signals:
	void changhed();
	void OnOff_changhe();
	void rc_set();

	
private:

	QLineEdit *rcxEdit;
	QLineEdit *rcyEdit;
	QLineEdit *rczEdit;

	QLineEdit *aEdit;
	QLineEdit *bEdit;
	QLineEdit *cEdit;

	QLabel	*rcxLabel;
	QLabel	*rcyLabel;
	QLabel	*rczLabel;

	QLabel	*aLabel;
	QLabel	*bLabel;
	QLabel	*cLabel;

	QRadioButton *OnOffViz;	// переключатель видимости актуальной области
	QPushButton *SetCentr;	// кнопка установления центра куба в центр обриты навигации


	void update();

	vec3db rc;	// координаты центра 
	vec3db abc;	// стороны паралелипипеда
};

#endif