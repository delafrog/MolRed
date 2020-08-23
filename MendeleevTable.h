#ifndef MENDELEEVTABLE_H
#define MENDELEEVTABLE_H

#include<QDialog>
//#include<QVector>
#include<QPushButton>
//#include"linalg.h"


class MendeleevTable : public QDialog
{
	Q_OBJECT
public:
	MendeleevTable(QDialog *parent = 0);
	//~MendeleevTable();
	int getID(){ return selAtomID;}
protected :
	void closeEvent(QCloseEvent* event);
signals:
	void id_changed(int selAtomID);
	void detatom();
	void desatom();
private slots:
	void clik_analize();
	//void my_close();
private:

	int NTotalAtoms;
	QPushButton *Buttons;

	int selAtomID;
	int helpID;

	QFont font_unpressed;//("Helvetica", 12, QFont::Normal);
	QFont font_pressed;//("Helvetica", 15, QFont::Bold);

	//vecT<QPushButton> Buttons;
	//QPushButton *Buttons;
};


#endif