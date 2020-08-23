/*
main.cpp 
загрузка и запуск приложения.
--------------
MolRed.
Copyright @ Zhabin S.N.
ver. 2.5.2
08.2011
*/


#include <QApplication>
#include <QMessageBox>
#include <fstream>

#include "GLframe.h"
#include "mainwindow.h"
#include "datatypes.h"
#include "rdwrfls.h"
#include "linalg.h"
//#include "linalg.cpp"

//#include "datatypestemplate.cpp"
//#include <Vector>



int main(int argc, char *argv[]) 
{ 
	//Molecule mol1(100);
	//SmplTpzlTable Table;

/*	WorkFrame A;

	vecT<char> fname;
	fname.add("1AKJ_lig.hin");

	A.hinparser(fname);/**/


	QApplication app(argc, argv,true);
	MainWindow *mainWin =  new MainWindow;
	//QMessageBox::warning(mainWin, QObject::tr("MolRed"),  QObject::tr(argv[0]),	QMessageBox::Yes);
	//if (argc==2){	QMessageBox::warning(mainWin, QObject::tr("MolRed"),  QObject::tr(argv[1]),	QMessageBox::Yes);}
	if (argc==2)
	{
		//QMessageBox::warning(mainWin, QObject::tr("MolRed"),  QObject::tr(argv[1]),	QMessageBox::Yes);
		mainWin->open(QObject::tr(argv[1]));
	}

	if (argc==3)
	{
		mainWin->open(QObject::tr(argv[1]));
		mainWin->show();
		QString fname = QObject::tr(argv[1]);
		int ln	= fname.lastIndexOf('.');
		fname.truncate(ln);
		fname.append(QString(".jpg"));
		mainWin->imag2file(fname);
		return 0;
	}


	mainWin->show();
	return app.exec();
	//return 0;
}