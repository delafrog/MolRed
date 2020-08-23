/*
mainwindow.h 
определеине класса главного окна.
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
	void open(char *fname); // открыть файл с заданым именем - при передаче имени файла из п\операционной системы при запуске программы
	void open(QString fname); // открыть файл с заданым именем - при передаче имени файла из п\операционной системы при запуске программы
	void imag2file(QString fname); // 
protected :
	void closeEvent(QCloseEvent *event);
private slots :
	void about();	// выдача окна с кратким описанием программы.
	void newFile(); // новый файл
	void open();	// октрыть файл
	void merge();	// открыть файл и добавить молекулу в существующую сцену
	bool save();	// сохранить файл
	bool saveAs();	// сохранить файл как...
	void selectBallStick(); // выбрать режим шаров и палочек
	void selectWire();	// выбрать режим решётки
	void statgen();
	void selprod();	// обработка данных о выделенных атомах - выделение номера атома и номера молекулы
	void unselprod(); // коррекция данных о выделенных атомах
	void buildSurf();// построение поверхности
	void openRecentFile();

	void export2vrml();	// экспорт сцены в vrml-файл
	void export2picture(); // экспорт сцены в jpg файл


	void addAtomDialog(); // вызов диалога для добавления атома
	void addFragmentDialog(); // вызов диалога для добавления фрагмента

	void doAddFrg();	// добавить фрагмент выбранный в браузере
	void doAddMol(Molecule *mol);	// добавление молекулы по указателю 'mol'
	//void doAddProt(Protein *prot);	// добавление протеина по указателю 'prot'
	//void doAddMol_(Molecule *mol);	// добавление молекулы по указателю 'mol'
	void doDelMol(int id_ml); // удаление молекулы
	void doDelMol_(int id_ml); // удаление молекулы
	void doAddAtom(int id); // добавление выбранного атома
	void doAddAtom(); // добавление выбранного атома
	void doDelAtom(); // удаление атома
	void doAddBond(); // добавление связи
	void doMoveAtoms(); // смещение нобора атомов
	void doUniMols(); // объединение двух молекул
	void doSepMol();	// разъединить молекулу
	void doMoveMol();	// поворот - движение молекулы
	void doMoveFrg();	// смещение фрагмента молекулы
//	void atomoving(); // обработка кнопки editbutton - изменение координат атомов
//	void doAtomMov(int fi); // изменение геометрии
	void undoDo();
	void redoDo();
	void doDelProc();

	void ghangeprojection();// смена типа проекции

	void rotatOn();	// включение режима поворота молекулы при редактировании

	void ActSpcOn(); // включение границ "актуальной области" - куба

	void undredhis(); // вызов окна с историей команд пользователя

	void help();

	void browsel();// обработка выделененого содержания в окне молбраузера
	void browselMol();
	void browchgMol();
	void browchangeSurf();
	void browchangecolorSurf();

	void hFun();
	
private :	// закрытые методы и члены

	void selsort();		// сортировка номеров выбранных атомов в порядке убывания

	void selMolDet();	// определение выделенных молекул

	bool okToContinue();

	void setCurrentFile(const QString &fileName);
	void updateRecentFileActions();
	QString StrippedName(const QString &fullfileName);
	QString GetDirName(const QString &fullfileName);	
	void setCurrentDir(const QString &dirName);

	void loadSettings(); // чтение параметров установок

	void saveSettings(); // запись параметров установок

	//void createActions();	// создание объектов действий подпутктов меню

	bool loadFile(const QString &fileName);
	bool saveFile(const QString &fileName);
	//bool saveFile(const QString &fileName);

	void createFileActions();	// создание объектов действий подпутктов меню
	void createEditActions();	// создание объектов действий подпутктов меню
	void createHelpActions();	// создание объектов действий подпутктов меню
	void createToolsActions();	// создание объектов действий подпутктов меню

	void createMenus();		// создание объектов пунктов меню

	void getaminos();
	//void setCurrentFileName(const QString &fileName);

	void createToolBars();	// создание кнокок быстрого доступа к инструментам
	
	void createOptionsActions();	// создание объектов действий подпунтктов меню

	int id_ml_srf;

	vecT<int> idn,ids;
	//int n_k;

	int addAtom_ID; // номер атома выбранного для добавления
	vecT<int> sel_ids_ml;

	bool frstmod;	// флаг сохранения данных

	vecT<vec2int> sl_ids; // номера выделенных атомов и молекул (первый элемент - номер молекулы в которой выделен атом с номером второго элемента)
	
	WorkFrame	*workFrame;
	OpenGLWidget *glWidg;
	//Surface		*surface;
	QLabel		*statWid;
	QWidget		*statWidget;
	QPushButton *statBut;
	QPushButton *showSelBut; // кнопка переключения вида к быделенному фрагменту
 
	QPushButton *hBut;	// вспомогательная кнопка для режима отладки

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

	//QString progDir; // директория запуска программы
	// указатели на соответвующие объекты - элементы меню
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

	// указатель на разделитель центральной области
	QSplitter *splitterWidget,*splitterWidget1,*splitterWidget2;

	// указатели на соответвующие объекты - действия подпунктов меню
	// действия меню File
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