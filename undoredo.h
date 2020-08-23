#ifndef UNDOREDO_H
#define UNDOREDO_H




#include <QWidget>
#include <QString>
#include <QtAlgorithms>
#include <QVariant>
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QList>
#include <QTreeView>

#include "linalg.h"
#include "datatypes.h"
class WorkFrame;
class Molecule;
class OpenGLWidget;

class QAction;

//class p_AD;


// коды операций
#define ADD_MOL		 1
#define DEL_MOL		-1
#define ADD_ATM		 2
#define DEL_ATM		-2
#define ADD_BND		 3
#define DEL_BND		-3
#define UNI_MOL		 4
#define SEP_MOL		-4
#define CHG_TYP		 0
#define CHG_BND		 9
#define MOV_ATM		 5
#define MOV_MOL		 6
#define MOV_FRG		 7
#define STOP_OP		 8
#define SWP_ATM		 10
#define SWP_MOL		 11
#define ADD_PAA		 12
#define DEL_PAA	    -12
#define ADD_AMN		 13
#define DEL_AMN		-13
#define ADD_CHN	 	 14
#define DEL_CHN		-14
#define ADD_PRT	 	 15
#define DEL_PRT	 	-15

//--
class undoredo;


class data_op5
{public :
	vec3db dr_at_mv_op;	// смещения атомов текущего шага	код: 5
	vec2int id_at_mv_op;	// номера молекул и атомов смещения	код: 5
};

class data_op6
{public :
	Quaternion<double>  qa_ml_mv_op;// кватернионы вращений молекул	код: 6
	vec3db cq_ml_mv_op;	// координаты центрирования кватерниона вращения молекул  код: 6
	int	id_ml_mv_op;	// номера молекул смещения	код: 6
	vec3db dr_ml_mv_op;	// смещения молекул	код: 6
};

class data_op7
{public :
	Quaternion<double> qa_fr_mv_op;// кватернионы вращений фрагментов	код: 7
	vec3db cq_fr_mv_op;		// координаты центрирования кватерниона вращения фрагмента  код: 7
	vecT<int> id_fr_mv_op;	// номера атомов фрагметов (первый элемент - номер молекулы) код: 7
	vec3db dr_fr_mv_op;		// смещения фрагметов	код: 7
	int id_ml;
};

class data_op12 // данные для 13 операции , описание атома - узла
{
public :
	vec4int id_s;	// номера молекулы, цепи, аминокислоты, куда добавлять атом-узел, а также номер атома
	vecT<char> name;	// имя атома в составе аминокслиты
};

class data_op13 // данные для 13 операции , описание аминокислоты - узла
{
public :
	vec3int id_s;	// номреа молекулы, цепи, аминосилоты -  в массиве цепи.
	vecT<char> name; // имя аминоскилоты
	int id_ch;		// пользовательский номер аминокислоты
};

class data_op14 // данные для 14 операции , описание цепи - узла
{
public :
	vec2int id_s;	// номреа молекулы, цепи -  в массиве протеина.
	char ch; // буква аминоксилты
};
class data_op15 // данные для 14 операции , описание цепи - узла
{
public :
	int id_s;	// номеh молекулы
	vecT<char> protname; // буква аминоксилты
};

class CommandItem // класс описывающий узел дерева описывающего команду или данные команды
{
public:
	CommandItem(const QList<QVariant> &data, CommandItem *parent = 0);// конструктор с заполнением
    ~CommandItem();

	void appendChild(CommandItem *child);	// метод добавления дочернего элемента

	CommandItem *child(int row);	// возвращает указатель на дочерний элемент с номером 'row' в списке текущего элемента
    int childCount() const;			// возвращает количество дочерних элементов
    int columnCount() const;		// возвращает количество столбцов 
    QVariant data(int column) const;// возвращает данные для столбца с номером 'column'
    int row() const;				// возвращает номер текущего элемента в списке родительского
    CommandItem *parent();			// возвращает указатель на родительский элемент

private:
	QList<CommandItem*> childItems;	// список указателей на дочерние элементы
    QList<QVariant>		itemData;	// список данных для текущего элемента
    CommandItem			*parentItem;// указатель на родительский элемент
};

class CmdTrModel : public QAbstractItemModel // модель представления данных в виде дерева
{
    Q_OBJECT
public: 

	CmdTrModel(const QString &data, QObject *parent = 0);
	CmdTrModel(QObject *parent = 0);
    ~CmdTrModel();

    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

	//void setupModelData(const Molecule &mol);
	void setUpModelData();//const Molecule &mol,SmplTpzlTable &tbl);
	void updateModel();//const Molecule &mol,SmplTpzlTable &tbl);	// обновить данные
	void clearAllModelData();
	void setUR(undoredo *in_ur){UR=in_ur;}
	void setundo(){unrd = false;}
	void setredo(){unrd	= true;}

private:
    void setupModelData(const QStringList &lines, CommandItem *parent); 

    CommandItem *rootItem; // указатель на самый верхний уровень

	undoredo *UR;

	bool unrd; // идентификатор undo или redo команд
};



class HstrView : public QTreeView
{
	Q_OBJECT
public: 
	HstrView(QWidget *parent = 0);
	~HstrView(){}
};

class undoredo : public QWidget//QDialog
{
	Q_OBJECT
public :
	undoredo(QWidget *parent = 0);
	//undoredo();

	void setWF(WorkFrame	*WF_in) {WF	= WF_in;}
	void setGW(OpenGLWidget	*GW_in) {GW	= GW_in;}
	void setundoptr(QAction *undoAction_in) {undoAction	= undoAction_in;}
	void setredoptr(QAction *redoAction_in) {redoAction	= redoAction_in;}



	void AddMol_init(Molecule *r);	// добавить молекулу
	void DelMol_init(int id_ml);	// удалить молекулу
	//void AddProt_init(Protein *r);	// добавить протеин
	void AddAtm_init(int id_ml);	// добавить нетипизированный атом
	void SwpAtm_init(int id_ml,int &id_at1,int &id_at2);	// swap атомов id_at1 и id_at2
	void SwpMol_init(int id_ml1,int &id_ml2);	// swap молекул id_ml1 и id_ml2
	void DelAtm_init(int id_ml,int &id_at);	// удалить атом
	void AddBnd_init(int id_ml,int &id_at1,int &id_at2);	// добавить связь
	void DelBnd_init(int id_ml,int &id_at1,int &id_at2);	// удалить связь
	void UniMol_init(int &id_ml1,int &id_ml2);	// объединть две молекулы
	void SepMol_init(int &id_ml1,int &id_ml2);//,vecT<int> &id_bn);	//	разъединить молекулу на две
	void ChgTyp_init(int id_ml,int id_at,int id_tp,AtomData * ptr);	// изменить тип атома
	void ChgBnd_init(int id_ml,int &id_at1,int &id_at2,int &id_tp);	// изменить тип связи

	void MovAtm_init(int id_ml,int &id_at,vec3db &dr);	// поступательное смещение атома
	void MovMol_init(int id_ml,vec3db &dr,vec3db &cq,Quaternion<double> &qa);	// смещение и поворот молекулы
	void MovFrg_init(int id_ml,vecT<int> &id_at,vec3db &dr,vec3db &cq,Quaternion<double> &qa);	// смещение и поворот фрагмента

	void DelPaa_init(int id_ml, int id_ch, int id_am, int id_at);	// удалить запись в структуре протеина
	void AddPaa_init(int id_ml, int id_ch, int id_am, int id_at, vecT<char> &name);	// добавить запись в структуре протеина

	void DelAmn_init(int id_ml, int id_ch, int id_am);	// удалить запись в структуре протеина
	void AddAmn_init(int id_ml, int id_ch, int id_am, vecT<char> &name, int id_a);	// удалить запись в структуре протеина

	void DelChn_init(int id_ml, int id_ch);	// удалить запись в структуре протеина
	void AddChn_init(int id_ml, int id_ch, char ch);	// удалить запись в структуре протеина

	void DelPrt_init(int id_ml);	// удалить запись в структуре протеина
	void AddPrt_init(int id_ml, vecT<char> & name);	// удалить запись в структуре протеина

	void Stop_init();


	// методы реализации оперции
	//void AddPrt_op();	// добавить пустой протеин
	void AddMol_op();	// добавить пустую молекулу
	void DelMol_op();	// удалить молекулу
	void AddAtm_op();	// добавить нетипизированный атом
	void SwpAtm_op();	// swap атомов
	void SwpMol_op();	// swap молекул
	void DelAtm_op();	// удалить атом
	void AddBnd_op();	// добавить связь
	void DelBnd_op();	// удалить связь
	void UniMol_op();	// объединть две молекулы
	void SepMol_op();	// разъединить молекулу на две
	void ChgTyp_op();	// изменить тип атома
	void ChgBnd_op();	// изменить тип связи

	void MovAtm_op();	// поступательное смещение атома
	void MovMol_op();	// смещение и поворот молекулы
	void MovFrg_op();	// смещение и поворот фрагмента

	void DelPaa_op();	// удалить запись в структуре протеина
	void AddPaa_op();	// добавить запись в структуре протеина

	void DelAmn_op();	// удалить амино-узел
	void AddAmn_op();	// добавить амино-узел

	void DelChn_op();	// удалить цепь-узел
	void AddChn_op();	// добавить цепь-узел

	void DelPrt_op();	// удалить протеин-узел
	void AddPrt_op();	// добавить протеин-узел

	void Frwd_op();	// реализация операции вперёд по списку операций
	void Back_op();	// реализация операции назад по списку опеаций

	void reset_op();	// сброс операций описанных впереди от текущего положения индикатора операций

	void reset_all();	// сброс всех операций

	void chesk_reset();
	void inc_cur_pos(){id_cr_op++;}

	//vecT<vec2int> & get_operations(){return operations;}




	vecT<vec2int> operations;	// массив вектор-кодов операций (номер (код) операции и номер элемента массива с соотвествующими данными)
//private:
	vecT<Molecule *> ml_br_dl_op;	// массив со структурами добавляемых и удаляемых молекул.
	vecT<int> id_ml_dl_op;		// номера молекул уничтожения молекулы	код: -1
	//vecT<Protein *> pr_br_dl_op;	// массив со структурами добавляемых и удаляемых протеинов.
	//vecT<int> id_pr_dl_op;		// номера протеинов уничтожения протеина	код: -12
	vecT<vec3int> id_at_sw_op;	// номера молекул и атомов для операции swap
	vecT<vec2int> id_ml_sw_op;	// номера молекул  для операции swap
	vecT<int> id_at_br_op;		// номера молекул рождения атома	код: 2
	vecT<vec2int> id_at_dl_op;	// номера молекул и атомов уничтожения атома	код: -2
	vecT<vec3int> id_bn_br_op;	// номера молекул и атомов рождения связи	код: 3
	vecT<vec3int> id_bn_dl_op;	// номера молекул и атомов уничтожения связи	код: -3
	vecT<vec2int> id_ml_un_op;	// номера молекул слияния	код: 4
	vecT<int> id_ml_sp_op;		// номера молекул разъединения	код: -4
	vecT<vec3int> id_at_tp_op;	// номера молекул, атомов и новых типов для изменения типа атома	код: 0
	vecT<vec4int> id_bn_tp_op;	// номера молекул, атомов связей и новых типов для изменения типа связи	код: 9
	vecT<AtomData * > ptr_dat_op;		// массив указателей с данными атомов;

	//vecT<vec4int> id_pr_aa_op; // номера молекулы, цепи, аминокислоты, куда добавлять атом-узел, а также номер атома
	//vecT<vec4int> id_pr_dl_op; // номера молекулы, цепи, аминокислоты, куда добавлять атом-узел, а также номер атома

	vecT<data_op12> id_pr_at_op; // номера молекулы, цепи, аминокислоты, куда добавлять атом-узел, а также номер атома

	vecT<data_op13> id_pr_am_op; // номера молекулы, цепи и добавляемой аминокислоты

	vecT<data_op14> id_pr_ch_op; // номера молекулы, и добавляемой цепи

	vecT<data_op15> id_pr_pr_op; // номер молекулы 



	vecT<data_op5> at_mv_op;
	//vecT<vec3db> dr_at_mv_op;	// смещения атомов текущего шага	код: 5
	//vecT<vec2int> id_at_mv_op;	// номера молекул и атомов смещения	код: 5

	vecT<data_op6> ml_mv_op;
//	vecT<Quaternion<double> > qa_ml_mv_op;// кватернионы вращений молекул	код: 6
//	vecT<vec3db> cq_ml_mv_op;	// координаты центрирования кватерниона вращения молекул  код: 6
//	vecT<int>	id_ml_mv_op;	// номера молекул смещения	код: 6
//	vecT<vec3db> dr_ml_mv_op;	// смещения молекул	код: 6
	

	vecT<data_op7> fr_mv_op;
//	vecT<Quaternion<double> > qa_fr_mv_op;// кватернионы вращений фрагментов	код: 7
//	vecT<vec3db> cq_fr_mv_op;		// координаты центрирования кватерниона вращения фрагмента  код: 7
//	vecT<vecT<int> > id_fr_mv_op;	// номера атомов фрагметов (первый элемент - номер молекулы) код: 7
//	vecT<vec3db> dr_fr_mv_op;		// смещения фрагметов	код: 7

	int id_cr_op;	// номер текущей операции.
	int op_count;	// номер операции от сохранённой


	WorkFrame	*WF;
	OpenGLWidget *GW;
//	RotatWin	*RW;

	QAction *undoAction;
	QAction *redoAction;

	CmdTrModel * unmodel;
	HstrView * unhistory;

	CmdTrModel * rdmodel;
	HstrView * rdhistory;

};
#endif