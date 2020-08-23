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


// ���� ��������
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
	vec3db dr_at_mv_op;	// �������� ������ �������� ����	���: 5
	vec2int id_at_mv_op;	// ������ ������� � ������ ��������	���: 5
};

class data_op6
{public :
	Quaternion<double>  qa_ml_mv_op;// ����������� �������� �������	���: 6
	vec3db cq_ml_mv_op;	// ���������� ������������� ����������� �������� �������  ���: 6
	int	id_ml_mv_op;	// ������ ������� ��������	���: 6
	vec3db dr_ml_mv_op;	// �������� �������	���: 6
};

class data_op7
{public :
	Quaternion<double> qa_fr_mv_op;// ����������� �������� ����������	���: 7
	vec3db cq_fr_mv_op;		// ���������� ������������� ����������� �������� ���������  ���: 7
	vecT<int> id_fr_mv_op;	// ������ ������ ��������� (������ ������� - ����� ��������) ���: 7
	vec3db dr_fr_mv_op;		// �������� ���������	���: 7
	int id_ml;
};

class data_op12 // ������ ��� 13 �������� , �������� ����� - ����
{
public :
	vec4int id_s;	// ������ ��������, ����, ������������, ���� ��������� ����-����, � ����� ����� �����
	vecT<char> name;	// ��� ����� � ������� �����������
};

class data_op13 // ������ ��� 13 �������� , �������� ������������ - ����
{
public :
	vec3int id_s;	// ������ ��������, ����, ����������� -  � ������� ����.
	vecT<char> name; // ��� ������������
	int id_ch;		// ���������������� ����� ������������
};

class data_op14 // ������ ��� 14 �������� , �������� ���� - ����
{
public :
	vec2int id_s;	// ������ ��������, ���� -  � ������� ��������.
	char ch; // ����� �����������
};
class data_op15 // ������ ��� 14 �������� , �������� ���� - ����
{
public :
	int id_s;	// ����h ��������
	vecT<char> protname; // ����� �����������
};

class CommandItem // ����� ����������� ���� ������ ������������ ������� ��� ������ �������
{
public:
	CommandItem(const QList<QVariant> &data, CommandItem *parent = 0);// ����������� � �����������
    ~CommandItem();

	void appendChild(CommandItem *child);	// ����� ���������� ��������� ��������

	CommandItem *child(int row);	// ���������� ��������� �� �������� ������� � ������� 'row' � ������ �������� ��������
    int childCount() const;			// ���������� ���������� �������� ���������
    int columnCount() const;		// ���������� ���������� �������� 
    QVariant data(int column) const;// ���������� ������ ��� ������� � ������� 'column'
    int row() const;				// ���������� ����� �������� �������� � ������ �������������
    CommandItem *parent();			// ���������� ��������� �� ������������ �������

private:
	QList<CommandItem*> childItems;	// ������ ���������� �� �������� ��������
    QList<QVariant>		itemData;	// ������ ������ ��� �������� ��������
    CommandItem			*parentItem;// ��������� �� ������������ �������
};

class CmdTrModel : public QAbstractItemModel // ������ ������������� ������ � ���� ������
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
	void updateModel();//const Molecule &mol,SmplTpzlTable &tbl);	// �������� ������
	void clearAllModelData();
	void setUR(undoredo *in_ur){UR=in_ur;}
	void setundo(){unrd = false;}
	void setredo(){unrd	= true;}

private:
    void setupModelData(const QStringList &lines, CommandItem *parent); 

    CommandItem *rootItem; // ��������� �� ����� ������� �������

	undoredo *UR;

	bool unrd; // ������������� undo ��� redo ������
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



	void AddMol_init(Molecule *r);	// �������� ��������
	void DelMol_init(int id_ml);	// ������� ��������
	//void AddProt_init(Protein *r);	// �������� �������
	void AddAtm_init(int id_ml);	// �������� ���������������� ����
	void SwpAtm_init(int id_ml,int &id_at1,int &id_at2);	// swap ������ id_at1 � id_at2
	void SwpMol_init(int id_ml1,int &id_ml2);	// swap ������� id_ml1 � id_ml2
	void DelAtm_init(int id_ml,int &id_at);	// ������� ����
	void AddBnd_init(int id_ml,int &id_at1,int &id_at2);	// �������� �����
	void DelBnd_init(int id_ml,int &id_at1,int &id_at2);	// ������� �����
	void UniMol_init(int &id_ml1,int &id_ml2);	// ��������� ��� ��������
	void SepMol_init(int &id_ml1,int &id_ml2);//,vecT<int> &id_bn);	//	����������� �������� �� ���
	void ChgTyp_init(int id_ml,int id_at,int id_tp,AtomData * ptr);	// �������� ��� �����
	void ChgBnd_init(int id_ml,int &id_at1,int &id_at2,int &id_tp);	// �������� ��� �����

	void MovAtm_init(int id_ml,int &id_at,vec3db &dr);	// �������������� �������� �����
	void MovMol_init(int id_ml,vec3db &dr,vec3db &cq,Quaternion<double> &qa);	// �������� � ������� ��������
	void MovFrg_init(int id_ml,vecT<int> &id_at,vec3db &dr,vec3db &cq,Quaternion<double> &qa);	// �������� � ������� ���������

	void DelPaa_init(int id_ml, int id_ch, int id_am, int id_at);	// ������� ������ � ��������� ��������
	void AddPaa_init(int id_ml, int id_ch, int id_am, int id_at, vecT<char> &name);	// �������� ������ � ��������� ��������

	void DelAmn_init(int id_ml, int id_ch, int id_am);	// ������� ������ � ��������� ��������
	void AddAmn_init(int id_ml, int id_ch, int id_am, vecT<char> &name, int id_a);	// ������� ������ � ��������� ��������

	void DelChn_init(int id_ml, int id_ch);	// ������� ������ � ��������� ��������
	void AddChn_init(int id_ml, int id_ch, char ch);	// ������� ������ � ��������� ��������

	void DelPrt_init(int id_ml);	// ������� ������ � ��������� ��������
	void AddPrt_init(int id_ml, vecT<char> & name);	// ������� ������ � ��������� ��������

	void Stop_init();


	// ������ ���������� �������
	//void AddPrt_op();	// �������� ������ �������
	void AddMol_op();	// �������� ������ ��������
	void DelMol_op();	// ������� ��������
	void AddAtm_op();	// �������� ���������������� ����
	void SwpAtm_op();	// swap ������
	void SwpMol_op();	// swap �������
	void DelAtm_op();	// ������� ����
	void AddBnd_op();	// �������� �����
	void DelBnd_op();	// ������� �����
	void UniMol_op();	// ��������� ��� ��������
	void SepMol_op();	// ����������� �������� �� ���
	void ChgTyp_op();	// �������� ��� �����
	void ChgBnd_op();	// �������� ��� �����

	void MovAtm_op();	// �������������� �������� �����
	void MovMol_op();	// �������� � ������� ��������
	void MovFrg_op();	// �������� � ������� ���������

	void DelPaa_op();	// ������� ������ � ��������� ��������
	void AddPaa_op();	// �������� ������ � ��������� ��������

	void DelAmn_op();	// ������� �����-����
	void AddAmn_op();	// �������� �����-����

	void DelChn_op();	// ������� ����-����
	void AddChn_op();	// �������� ����-����

	void DelPrt_op();	// ������� �������-����
	void AddPrt_op();	// �������� �������-����

	void Frwd_op();	// ���������� �������� ����� �� ������ ��������
	void Back_op();	// ���������� �������� ����� �� ������ �������

	void reset_op();	// ����� �������� ��������� ������� �� �������� ��������� ���������� ��������

	void reset_all();	// ����� ���� ��������

	void chesk_reset();
	void inc_cur_pos(){id_cr_op++;}

	//vecT<vec2int> & get_operations(){return operations;}




	vecT<vec2int> operations;	// ������ ������-����� �������� (����� (���) �������� � ����� �������� ������� � ��������������� �������)
//private:
	vecT<Molecule *> ml_br_dl_op;	// ������ �� ����������� ����������� � ��������� �������.
	vecT<int> id_ml_dl_op;		// ������ ������� ����������� ��������	���: -1
	//vecT<Protein *> pr_br_dl_op;	// ������ �� ����������� ����������� � ��������� ���������.
	//vecT<int> id_pr_dl_op;		// ������ ��������� ����������� ��������	���: -12
	vecT<vec3int> id_at_sw_op;	// ������ ������� � ������ ��� �������� swap
	vecT<vec2int> id_ml_sw_op;	// ������ �������  ��� �������� swap
	vecT<int> id_at_br_op;		// ������ ������� �������� �����	���: 2
	vecT<vec2int> id_at_dl_op;	// ������ ������� � ������ ����������� �����	���: -2
	vecT<vec3int> id_bn_br_op;	// ������ ������� � ������ �������� �����	���: 3
	vecT<vec3int> id_bn_dl_op;	// ������ ������� � ������ ����������� �����	���: -3
	vecT<vec2int> id_ml_un_op;	// ������ ������� �������	���: 4
	vecT<int> id_ml_sp_op;		// ������ ������� ������������	���: -4
	vecT<vec3int> id_at_tp_op;	// ������ �������, ������ � ����� ����� ��� ��������� ���� �����	���: 0
	vecT<vec4int> id_bn_tp_op;	// ������ �������, ������ ������ � ����� ����� ��� ��������� ���� �����	���: 9
	vecT<AtomData * > ptr_dat_op;		// ������ ���������� � ������� ������;

	//vecT<vec4int> id_pr_aa_op; // ������ ��������, ����, ������������, ���� ��������� ����-����, � ����� ����� �����
	//vecT<vec4int> id_pr_dl_op; // ������ ��������, ����, ������������, ���� ��������� ����-����, � ����� ����� �����

	vecT<data_op12> id_pr_at_op; // ������ ��������, ����, ������������, ���� ��������� ����-����, � ����� ����� �����

	vecT<data_op13> id_pr_am_op; // ������ ��������, ���� � ����������� ������������

	vecT<data_op14> id_pr_ch_op; // ������ ��������, � ����������� ����

	vecT<data_op15> id_pr_pr_op; // ����� �������� 



	vecT<data_op5> at_mv_op;
	//vecT<vec3db> dr_at_mv_op;	// �������� ������ �������� ����	���: 5
	//vecT<vec2int> id_at_mv_op;	// ������ ������� � ������ ��������	���: 5

	vecT<data_op6> ml_mv_op;
//	vecT<Quaternion<double> > qa_ml_mv_op;// ����������� �������� �������	���: 6
//	vecT<vec3db> cq_ml_mv_op;	// ���������� ������������� ����������� �������� �������  ���: 6
//	vecT<int>	id_ml_mv_op;	// ������ ������� ��������	���: 6
//	vecT<vec3db> dr_ml_mv_op;	// �������� �������	���: 6
	

	vecT<data_op7> fr_mv_op;
//	vecT<Quaternion<double> > qa_fr_mv_op;// ����������� �������� ����������	���: 7
//	vecT<vec3db> cq_fr_mv_op;		// ���������� ������������� ����������� �������� ���������  ���: 7
//	vecT<vecT<int> > id_fr_mv_op;	// ������ ������ ��������� (������ ������� - ����� ��������) ���: 7
//	vecT<vec3db> dr_fr_mv_op;		// �������� ���������	���: 7

	int id_cr_op;	// ����� ������� ��������.
	int op_count;	// ����� �������� �� ����������


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