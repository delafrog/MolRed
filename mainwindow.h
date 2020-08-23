/*
mainwindow.h 
����������� ������ �������� ����.
--------------
MolRed.
Copyright @ Zhabin S.N.
ver. 0.0.1
07.2008
*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "linalg.h"
//#include "graph.h"

//#include <QSplitter>


class QSplitter;
class WorkFrame;
class OpenGLWidget;
class QLabel;
class QWidget;
class TreeView;
//class BrowseModel;
class TreeModel;
class Surface;
class MendeleevTable;
class QSpinBox;
class QSlider;
class QPushButton;
class FragmentBrowser;
class Molecule;
class RotatWin;
class HelpBrowser;
class undoredo;
class Aminos;
class Graph;
class ActualSpace;

class MainWindow : public QMainWindow	
{
	Q_OBJECT

public :
	MainWindow();
	void open(char *fname); // ������� ���� � ������� ������ - ��� �������� ����� ����� �� �\������������ ������� ��� ������� ���������
	void open(QString fname); // ������� ���� � ������� ������ - ��� �������� ����� ����� �� �\������������ ������� ��� ������� ���������
	void imag2file(QString fname); // 
protected :
	void closeEvent(QCloseEvent *event);
private slots :
	void about();	// ������ ���� � ������� ��������� ���������.
	void newFile(); // ����� ����
	void open();	// ������� ����
	void merge();	// ������� ���� � �������� �������� � ������������ �����
	bool save();	// ��������� ����
	bool saveAs();	// ��������� ���� ���...
	void selectBallStick(); // ������� ����� ����� � �������
	void selectWire();	// ������� ����� �������
	void statgen();
	void selprod();	// ��������� ������ � ���������� ������ - ��������� ������ ����� � ������ ��������
	void unselprod(); // ��������� ������ � ���������� ������
	void buildSurf();// ���������� �����������
	void openRecentFile();

	void export2vrml();	// ������� ����� � vrml-����
	void export2picture(); // ������� ����� � jpg ����


	void addAtomDialog(); // ����� ������� ��� ���������� �����
	void addFragmentDialog(); // ����� ������� ��� ���������� ���������

	void doAddFrg();	// �������� �������� ��������� � ��������
	void doAddMol(Molecule *mol);	// ���������� �������� �� ��������� 'mol'
	//void doAddProt(Protein *prot);	// ���������� �������� �� ��������� 'prot'
	//void doAddMol_(Molecule *mol);	// ���������� �������� �� ��������� 'mol'
	void doDelMol(int id_ml); // �������� ��������
	void doDelMol_(int id_ml); // �������� ��������
	void doAddAtom(int id); // ���������� ���������� �����
	void doAddAtom(); // ���������� ���������� �����
	void doDelAtom(); // �������� �����
	void doAddBond(); // ���������� �����
	void doMoveAtoms(); // �������� ������ ������
	void doUniMols(); // ����������� ���� �������
	void doSepMol();	// ����������� ��������
	void doMoveMol();	// ������� - �������� ��������
	void doMoveFrg();	// �������� ��������� ��������
//	void atomoving(); // ��������� ������ editbutton - ��������� ��������� ������
//	void doAtomMov(int fi); // ��������� ���������
	void undoDo();
	void redoDo();
	void doDelProc();

	void ghangeprojection();// ����� ���� ��������

	void rotatOn();	// ��������� ������ �������� �������� ��� ��������������

	void ActSpcOn(); // ��������� ������ "���������� �������" - ����

	void undredhis(); // ����� ���� � �������� ������ ������������

	void help();

	void browsel();// ��������� ������������ ���������� � ���� �����������
	void browselMol();
	void browchgMol();
	void browchangeSurf();
	void browchangecolorSurf();

	void hFun();
	
private :	// �������� ������ � �����

	void selsort();		// ���������� ������� ��������� ������ � ������� ��������

	void selMolDet();	// ����������� ���������� �������

	bool okToContinue();

	void setCurrentFile(const QString &fileName);
	void updateRecentFileActions();
	QString StrippedName(const QString &fullfileName);
	QString GetDirName(const QString &fullfileName);	
	void setCurrentDir(const QString &dirName);

	void loadSettings(); // ������ ���������� ���������

	void saveSettings(); // ������ ���������� ���������

	//void createActions();	// �������� �������� �������� ���������� ����

	bool loadFile(const QString &fileName);
	bool saveFile(const QString &fileName);
	//bool saveFile(const QString &fileName);

	void createFileActions();	// �������� �������� �������� ���������� ����
	void createEditActions();	// �������� �������� �������� ���������� ����
	void createHelpActions();	// �������� �������� �������� ���������� ����
	void createToolsActions();	// �������� �������� �������� ���������� ����

	void createMenus();		// �������� �������� ������� ����

	void getaminos();
	//void setCurrentFileName(const QString &fileName);

	void createToolBars();	// �������� ������ �������� ������� � ������������
	
	void createOptionsActions();	// �������� �������� �������� ����������� ����

	int id_ml_srf;

	vecT<int> idn,ids;
	//int n_k;

	int addAtom_ID; // ����� ����� ���������� ��� ����������
	vecT<int> sel_ids_ml;

	bool frstmod;	// ���� ���������� ������

	vecT<vec2int> sl_ids; // ������ ���������� ������ � ������� (������ ������� - ����� �������� � ������� ������� ���� � ������� ������� ��������)
	
	WorkFrame	*workFrame;
	OpenGLWidget *glWidg;
	//Surface		*surface;
	QLabel		*statWid;
	QWidget		*statWidget;
	QPushButton *statBut;
	QPushButton *showSelBut; // ������ ������������ ���� � ����������� ���������
 
	QPushButton *hBut;	// ��������������� ������ ��� ������ �������

	TreeView	*treeView;

	QSpinBox	*spinBox;
	QSlider		*slider;
	//QPushButton *editbutton;
	//QDialog		*editdialog;

	FragmentBrowser *fragmentBrowser;

	MendeleevTable *mendeleevTable;

	TreeModel	*treeModel;

	RotatWin	*rotatWin;

	ActualSpace *ActSpc;

	undoredo	*undo_redo;

	Aminos		*amin;

	//HelpBrowser *helpbrowser;
	
	//BrowseModel *browseModel;

	QStringList recentFiles;
	QString curFile;
	QString curDir;

	//QString progDir; // ���������� ������� ���������
	// ��������� �� ������������� ������� - �������� ����
	QMenu *fileMenu;
	QMenu *editMenu;
	QMenu *toolsMenu;
	QMenu *optionsMenu;
	QMenu *displaySubMenu;	
	QMenu *helpMenu;

	QMenu *exportSubMenu;
	//--------------
	//QMenu *contextMenu1;
	//QAction *contextselectAction1;

	// ��������� �� ����������� ����������� �������
	QSplitter *splitterWidget,*splitterWidget1,*splitterWidget2;

	// ��������� �� ������������� ������� - �������� ���������� ����
	// �������� ���� File
	QAction *newAction;
	QAction *openAction;
	QAction *mergeAction;
	QAction *saveAction;
	QAction *saveAsAction;

	QAction *export2vrmlAction;
	QAction *export2pictureAction;

	enum{MaxRecentFiles = 15};
	QAction *recentFilesActions[MaxRecentFiles];
	QAction *separatorAction;

	QAction *exitAction;

	//--------------
	QAction *undoAction;
	QAction *redoAction;
	QAction *undoredoAction;
	QAction *frameSelect;
	QAction *narrowSelect;
	QAction *separateMol;
	QAction *unionMols;
	QAction *selectMol;
	QAction *invertSelection;

	QAction *deleteSelection;

	//--------------

	QAction *displayWireAction;
	QAction *displayBallStickAction;

	//--------------
	QAction *surfaceBuildAction;

	//--------------
	QAction *OrthoPerspAction;

	QAction *renderAtChAction;
	QAction *un_renderAtChAction;

	//--------------
	QAction *bkgdColorAction;

	//--------------
	QAction *addAtom;
	QAction *addBond;
	
	QAction *addFragment;
	//--------------
	
	QAction *doTurnAction;
	//--------------
	QAction *doActSpcAction;
	//--------------

	QAction *AboutAction;
	QAction *HelpAction;

	//********************************************
	QToolBar *fileToolBar;
	QToolBar *editToolBar;
	QToolBar *toolsToolBar;
	QToolBar *optionsToolBar;

};


#endif