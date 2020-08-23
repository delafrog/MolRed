#ifndef ROTAT_H
#define ROTAT_H


//#include<QVector>
//#include<QPushButton>
#include <QDialog>
#include "linalg.h"

class QLineEdit;
class QLabel;


class RotatWin : public QDialog
{
	Q_OBJECT
public:
	RotatWin(QDialog *parent = 0);
	void SetAxis(vec3db &qa_);
	void SetInc(double d);
	void SetDis(vec3db &c);
	void SetAlfa(double a);
	void SetDsp(double a);
	double GetAlfa();
	vec3db GetDis();
	vec3db GetAxis();
	double GetInc();
	double GetDsp();
	void inc();
	void dec();
	void incdis();
	void decdis();
	bool isZeroSpin();
	bool isZeroDisp();

public slots:
	void changhe_angle();
	void changhe_d_angle();
	void changhe_displ();
	void changhe_d_displ();
	void changhe_qax();
	void changhe_qay();
	void changhe_qaz();
	void changhe_cqx();
	void changhe_cqy();
	void changhe_cqz();


signals:
	void changhed();


private:

	void update();

	QLineEdit *angleEdit;

	QLineEdit *d_angleEdit;

	QLineEdit *displEdit;
	QLineEdit *d_displEdit;

	QLineEdit *qaxEdit;
	QLineEdit *qayEdit;
	QLineEdit *qazEdit;

	QLineEdit *cqxEdit;
	QLineEdit *cqyEdit;
	QLineEdit *cqzEdit;

	QLabel	*angleLabel;
	QLabel	*d_angleLabel;
	
	QLabel	*displLabel;
	QLabel	*d_displLabel;

	QLabel	*qaxLabel;
	QLabel	*qayLabel;
	QLabel	*qazLabel;

	QLabel	*cqxLabel;
	QLabel	*cqyLabel;
	QLabel	*cqzLabel;

	vec3db	qa;
	vec3db	qc;

	double  dl,d_dl;

	double d_alf;
	double alf;
};

#endif