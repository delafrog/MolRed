#ifndef RDWRFLS_H
#define RDWRFLS_H
// чтение и запись данных из файлов

#include "linalg.h"
#include "datatypes.h"

class QString;
class Surface;

//int hinparser(vecT<Molecule> &Mls);	// чтение данных из hin-файла и сохранение данных в молекулах
//template <class T>
class WorkFrame
{
public:
	SmplTpzlTable	TableZR;	// таблица типов атомов и их параметров
	vecT<Molecule*>	Mls;
	vecT<Protein*>  Prot;

	//vecT<vec2int> id_select;	// номера выделеных атомов в молекулах

	vecT<Surface*>		Srfcs;	// поверхности

	WorkFrame(void);
	~WorkFrame(void);

	void MolSwap(const int &id1,const int &id2);

	void InitMolSurf(ConnectedAtoms *mol);	// инициализация поверхности связанной с молекулой 
	void DelMolSurf(ConnectedAtoms *mol);// удаление поврехности для молекулы mol
	void DelMolSurf(Surface *srf);// удаление поврехности для молекулы mol
	void DelMolSurf();

	int hinparser(vecT<char> &fname);	// чтение данных из hin-файла и сохранение данных в молекулах
	int mrkparser(vecT<char> &fname);	// чтение данных из mrk-файла и сохранение данных в молекулах
	int pdbparser0(vecT<char> &fname);	// чтение данных из pbd-файла и сохранение данных в молекулах (самый прстой вариант)
	int pdbparser1(vecT<char> &fname);	// чтение данных из pbd-файла 
	int molparser(vecT<char> &fname);	// чтение данных из mol-файла
	int xyzparser(vecT<char> &fname);	// чтение данных из xyz-файла
	int checkxyztype(vecT <vecT <char> > &txtdata); // определение типа xyz - файла. ворвращаемое число-код типа. возвращение 0 означает нессответсвие ни одному из типов.
	// парсеры различных типов xyz - файлов
	int xyzpars_1(vecT <vecT <char> > &txtdata,Molecule *cMlc);
	int xyzpars_2(vecT <vecT <char> > &txtdata,Molecule *cMlc);
	int xyzpars_3(vecT <vecT <char> > &txtdata,Molecule *cMlc);
	int xyzpars_4(vecT <vecT <char> > &txtdata,Molecule *cMlc);
	int xyzpars_5(vecT <vecT <char> > &txtdata,Molecule *cMlc);
	int xyzpars_6(vecT <vecT <char> > &txtdata,Molecule *cMlc);
	int xyzpars_7(vecT <vecT <char> > &txtdata,Molecule *cMlc);
	//--
	void setdistanceconnect(Molecule * cMlc);
	bool readFile(const QString &fileName);
	void hinscript(int id_ml,vecT<vecT <char> > &hinstr);	// формирует набор строк с hin- описанием молекулы с номером 'id-ml'
	void hinscript(vecT<vecT <char> > &hinstr);	// формирует набор строк с hin - описанием молекул
	void mrkscript(vecT<vecT <char> > &mrkstr); // формирует набор строк с mrk - описанием молекулы
	void mrkscript(int id_ml,vecT<vecT <char> > &mrkstr); // формирует набор строк с mrk - описанием молекулы с номером 'id-ml'
	void pdbscript(vecT<vecT <char> > &pdbstr); // формирует набор строк с pdb - описанием молекулы
	void xyzscript(int id_ml, vecT<vecT <char> > &xyzstr);
	void xyzscript(vecT<vecT <char> > &xyzstr);
	bool writeFile(const QString &fileName,int id_ml);
	bool writeFile(const QString &fileName);


};

#endif