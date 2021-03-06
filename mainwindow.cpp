/*
mainwindow.cpp 
реализация методов класса главного окна.
--------------
MolRed.
Copyright @ Zhabin S.N.
ver. 0.0.1
07.2008
*/

#ifndef MAINWINDOW_CPP
#define MAINWINDOW_CPP

//#include <QtOpenGL>
#include <math.h>
#include <QtGui>
#include <QSplitter>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QLabel>
#include <QWidget>
#include <QStatusBar> 
#include <QMessageBox>
#include <QFileDialog>
#include <QTreeView>
#include <QSpinBox>


#include "GLframe.h"
#include "mainwindow.h"
#include "rdwrfls.h"
#include "molbrowse.h"
#include "surface.h"
#include "MendeleevTable.h"
#include "FragmentBrowser.h"
#include "rotat.h"
#include "helpBrowser.h"
#include "undoredo.h"
#include "aminos.h"

#include "ActualSpace.h"

#include "linalg.h"
//#include "linalg.cpp"

#include "graph.h"
/*
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
//--
*/

MainWindow::MainWindow()	// конструктор
{

	//QGLWidget *glWidg	= new QGLWidget;
	glWidg	= new OpenGLWidget;
	statWid	= new QLabel;
	statWidget	= new QWidget;
	treeView	= new TreeView;

	statBut	= new QPushButton;
	showSelBut	= new QPushButton;
	
	treeModel	= new TreeModel;

	treeView->setModel(treeModel);/**/

	mendeleevTable = new MendeleevTable;


	rotatWin	= new RotatWin;

	ActSpc		= new ActualSpace;


	glWidg->setrotwin(rotatWin);
	glWidg->setActSpc(ActSpc);


	glWidg->resize(1000,800);
	glWidg->setFocusPolicy(Qt::StrongFocus);

	//editor->setFocusPolicy(Qt::NoFocus);
	
	//id_cr_op	= 0;


	workFrame	= new WorkFrame;
	treeModel->setWF(workFrame);

	
	undo_redo	= new undoredo;
	undo_redo->setWF(workFrame);
	undo_redo->setGW(glWidg);

	amin		= new Aminos;


	//surface		= new Surface;

	splitterWidget	= new QSplitter;
	splitterWidget1	= new QSplitter;
	splitterWidget2	= new QSplitter;

	spinBox		= new QSpinBox;
	slider		= new QSlider(Qt::Horizontal); 
	//editbutton	= new QPushButton;

	QHBoxLayout *layout	= new QHBoxLayout;
	layout->addWidget(spinBox);
	layout->addWidget(slider);

//	editdialog->setLayout(layout);

	//editbutton->setText(tr("Edit Coordinates"));
	//editbutton->setText(tr("Edit Distance"));
	//editbutton->setText(tr("Edit Angle"));
	//editbutton->setFixedWidth(100);
	//editbutton->setEnabled(false);

	statBut->setText(tr(("Show on scene")));
	statBut->setFixedWidth(100);
	statBut->setEnabled(false);

	showSelBut->setText(tr(("Go to selected")));
	showSelBut->setFixedWidth(100);
	showSelBut->setEnabled(false);


	hBut	= new QPushButton;

	hBut->setText(tr(("hBut")));
	hBut->setFixedWidth(100);
	hBut->setEnabled(true);

	connect(hBut,SIGNAL(clicked()),this,SLOT(hFun()));



	QHBoxLayout *layout2	= new QHBoxLayout;


	layout2->addWidget(statWid);
	layout2->addWidget(statBut);
	layout2->addWidget(showSelBut);
	//layout2->addWidget(hBut);
	layout2->addStretch();


	statWidget->setLayout(layout2);
//	statWidget->setMinimumHeight(30);
//	statWidget->setMaximumHeight(21);

	//splitterWidget2->addWidget(statWidget);
	//splitterWidget2->setMaximumHeight(10);

	/*splitterWidget2->setOrientation(Qt::Horizontal);
	splitterWidget2->addWidget(statWid);
	splitterWidget2->addWidget(statBut);
	splitterWidget2->setStretchFactor(2,1);*/
//	splitterWidget2->addWidget(editbutton);

	splitterWidget1->setOrientation(Qt::Vertical);
	splitterWidget1->addWidget(glWidg);
	splitterWidget1->addWidget(statWidget);//splitterWidget2);
	splitterWidget1->setStretchFactor(0,1);

	

	splitterWidget->setOrientation(Qt::Horizontal);
	//splitterWidget->addWidget(treeView);
	splitterWidget->addWidget(treeView);
	splitterWidget->addWidget(splitterWidget1);	
	splitterWidget->setStretchFactor(1,1);
	//splitterWidget->setSizes();
	
	setCentralWidget(splitterWidget);
	//setCentralWidget(glWidg);
	

	fragmentBrowser		= new FragmentBrowser;


	createFileActions();
	createEditActions();
	createHelpActions();
	createOptionsActions();
	createToolsActions();
	createMenus();

	createToolBars();

	resize(1200,800);

	connect(glWidg,SIGNAL(selectDo()),this,SLOT(statgen()));
	connect(glWidg,SIGNAL(uselDo()),this,SLOT(unselprod()));
	connect(glWidg,SIGNAL(updatestate()),this,SLOT(statgen()));
	connect(glWidg,SIGNAL(deleteDo()),this,SLOT(doDelProc()));
	connect(glWidg,SIGNAL(addbndDo()),this,SLOT(doAddBond()));
	connect(glWidg,SIGNAL(moveDo()),this,SLOT(doMoveAtoms()));
	connect(glWidg,SIGNAL(addfrgDo()),this,SLOT(doAddFrg()));
	connect(glWidg,SIGNAL(addatomDo()),this,SLOT(doAddAtom()));
	connect(glWidg,SIGNAL(rotatDo()),this,SLOT(doMoveMol()));
	connect(glWidg,SIGNAL(movefrgDo()),this,SLOT(doMoveFrg()));

	//connect(mendeleevTable,SIGNAL(id_changed(int)),this,SLOT(doAddAtom(int)));

	connect(spinBox,SIGNAL(valueChanged(int)),slider,SLOT(setValue(int)));
	connect(slider,SIGNAL(valueChanged(int)),spinBox,SLOT(setValue(int)));
	connect(spinBox,SIGNAL(valueChanged(int)),this,SLOT(doAtomMov(int)));
	
//	connect(editbutton,SIGNAL(clicked()),this,SLOT(atomoving()));

	connect(fragmentBrowser,SIGNAL(destroyed()),glWidg,SLOT(FrgBrwOff()));
	connect(fragmentBrowser,SIGNAL(detfrg()),glWidg,SLOT(FrgBrwOn()));
	connect(fragmentBrowser,SIGNAL(desfrg()),glWidg,SLOT(FrgBrwOff()));

	connect(glWidg,SIGNAL(closeFrgBrw()),fragmentBrowser,SLOT(close()));
	connect(glWidg,SIGNAL(closeAtomBrw()),mendeleevTable,SLOT(close()));

	//connect(mendeleevTable,SIGNAL(destroyed()),glWidg,SLOT(AtomBrwOff()));
	connect(mendeleevTable,SIGNAL(detatom()),glWidg,SLOT(AtomBrwOn()));
	connect(mendeleevTable,SIGNAL(desatom()),glWidg,SLOT(AtomBrwOff()));

	connect(rotatWin,SIGNAL(changhed()),glWidg,SLOT(rotatproc()));

	connect(ActSpc,SIGNAL(OnOff_changhe()),glWidg,SLOT(renAS_onoff() ));
	connect(ActSpc,SIGNAL(changhed()),glWidg,SLOT(updtAS() ));
	connect(ActSpc,SIGNAL(rc_set()),glWidg,SLOT(rcAS_set() ));

	connect(treeView,SIGNAL(selready()),this,SLOT(browsel()));
	connect(treeView,SIGNAL(selectMol()),this,SLOT(browselMol()));
	connect(treeView,SIGNAL(changeMol()),this,SLOT(browchgMol()));
	connect(treeView,SIGNAL(changeSurf()),this,SLOT(browchangeSurf()));
	connect(treeView,SIGNAL(changecolorSurf()),this,SLOT(browchangecolorSurf()));



	connect(statBut,SIGNAL(clicked()),glWidg,SLOT(doSelShow()));

	connect(showSelBut,SIGNAL(clicked()),glWidg,SLOT(jump2sel()));
	

	undo_redo->Stop_init();
	glWidg->initmol(workFrame);


	setWindowIcon(QIcon(":/images/mr3.png"));

	statusBar()->showMessage(tr(" "),2000);

	frstmod	= true;

	setCurrentFile("");
	setCurrentDir(".");
	
	loadSettings();
	//op_count	= 0;

	id_ml_srf	= -1;

//	getaminos();

//	glWidg->s_ids	= &sl_ids;
}

void MainWindow::closeEvent(QCloseEvent *event) // обработчик события - закрытия окна.
{
	if (okToContinue())
	{
		saveSettings();
		fragmentBrowser->close();
		mendeleevTable->close();
		rotatWin->close();
		ActSpc->close();
		undo_redo->close();
		event->accept();	//принять событие - закрыть окно.
	}else
	{
		event->ignore();
	}
}

void MainWindow::createFileActions()	
{
	newAction	= new QAction(tr("&New"),this);
	newAction->setIcon(QIcon(":/images/new.png"));
	newAction->setShortcut(QKeySequence::New);
	newAction->setStatusTip(tr("Create a new  file"));
	connect(newAction,SIGNAL(triggered()), this, SLOT(newFile()));

	openAction	= new QAction(tr("&Open"),this);
	openAction->setIcon(QIcon(":/images/open.png"));
	openAction->setShortcut(QKeySequence::Open);
	openAction->setStatusTip(tr("Open an existing  file"));
	connect(openAction,SIGNAL(triggered()), this, SLOT(open()));

	mergeAction	= new QAction(tr("&Merge"),this);
	mergeAction->setIcon(QIcon(":/images/merge.png"));
	mergeAction->setShortcut(tr("Ctrl+M"));
	mergeAction->setStatusTip(tr("Open an existing  file and add into exist scene"));
	connect(mergeAction,SIGNAL(triggered()), this, SLOT(merge()));

	saveAction	= new QAction(tr("&Save"),this);
	saveAction->setIcon(QIcon(":/images/save.png"));
	saveAction->setShortcut(QKeySequence::Save);
	saveAction->setStatusTip(tr("Save a molecule in current file"));
	connect(saveAction,SIGNAL(triggered()), this, SLOT(save()));

	saveAsAction	= new QAction(tr("Save &As..."),this);
	//saveAsAction->setIcon(QIcon":/images/icon.png");
	//saveAsAction->setShortcut(QKeySequence::SaveAs);
	saveAsAction->setStatusTip(tr("Save a molecule in new file"));
	connect(saveAsAction,SIGNAL(triggered()), this, SLOT(saveAs()));

	for(int i=0; i<MaxRecentFiles;++i)
	{
		recentFilesActions[i] = new QAction(this);
		recentFilesActions[i]->setVisible(false);
		connect(recentFilesActions[i],SIGNAL(triggered()),this, SLOT(openRecentFile()));
	}

	exitAction	= new QAction(tr("&Exit"),this);
	exitAction->setShortcut(tr("Ctrl+Q"));
	exitAction->setStatusTip(tr("Exit the MolRed"));
	connect(exitAction,SIGNAL(triggered()), this, SLOT(close()));


	export2vrmlAction	= new QAction(tr("To &VRML"),this);
	export2vrmlAction->setStatusTip(tr("Export current 3D scene to a VRML file"));
	connect(export2vrmlAction,SIGNAL(triggered()), this, SLOT(export2vrml()));


	export2pictureAction	= new QAction(tr("To &JPG Picture"),this);
	export2pictureAction->setStatusTip(tr("Export current 3D scene to a JPG file"));
	connect(export2pictureAction,SIGNAL(triggered()), this, SLOT(export2picture()));

}

void MainWindow::createEditActions()	
{
	undoAction	= new QAction(tr("&Undo"),this);
	undoAction->setIcon(QIcon(":/images/undo.png"));
	undoAction->setShortcut(QKeySequence::Undo);
	undoAction->setStatusTip(tr("Undo action"));
	undoAction->setEnabled(false);
	connect(undoAction,SIGNAL(triggered()), this, SLOT(undoDo()));
	undo_redo->setundoptr(undoAction);

	redoAction	= new QAction(tr("&Redo"),this);
	redoAction->setIcon(QIcon(":/images/redo.png"));
	redoAction->setShortcut(QKeySequence::Redo);
	redoAction->setStatusTip(tr("Redo action"));
	redoAction->setEnabled(false);
	connect(redoAction,SIGNAL(triggered()), this, SLOT(redoDo()));
	undo_redo->setredoptr(redoAction);

	undoredoAction	= new QAction(tr("Undo/Redo &Viewer"),this);
	undoredoAction->setIcon(QIcon(":/images/undoredo.png"));
	undoredoAction->setStatusTip(tr("Show window with command history"));
	connect(undoredoAction,SIGNAL(triggered()), this, SLOT(undredhis()));

	frameSelect	= new QAction(tr("&Frame Select"),this);
	frameSelect->setShortcut(tr("R"));
	frameSelect->setIcon(QIcon(":/images/frame.png"));
	frameSelect->setStatusTip(tr("Switch to frame select mode"));
	connect(frameSelect,SIGNAL(triggered()),glWidg,SLOT(frameSel()));
//	connect(frameSelect,SIGNAL(triggered()),this,SLOT(nonmolSel()));

	narrowSelect	= new QAction(tr("&Atom Select"),this);
	narrowSelect->setShortcut(tr("N"));
	narrowSelect->setIcon(QIcon(":/images/narr.png"));
	narrowSelect->setStatusTip(tr("Switch to atom select mode"));
	connect(narrowSelect,SIGNAL(triggered()),glWidg,SLOT(narrowSel()));
//	connect(narrowSelect,SIGNAL(triggered()),this,SLOT(nonmolSel()));


	selectMol	= new QAction(tr("&Molecule Select"),this);
	selectMol->setShortcut(tr("M"));
	selectMol->setIcon(QIcon(":/images/selmol.png"));
	selectMol->setStatusTip(tr("Switch to molecule select mode. "));
	connect(selectMol,SIGNAL(triggered()),glWidg,SLOT(moleculeSel()));
//	connect(selectMol,SIGNAL(triggered()),glWidg,SLOT(narrowSel()));


	invertSelection	= new QAction(tr("&Invert Selection"),this);
	invertSelection->setShortcut(tr("I"));
	invertSelection->setIcon(QIcon(":/images/invsel1.png"));
	invertSelection->setStatusTip(tr("Invert selection "));
	connect(invertSelection,SIGNAL(triggered()),glWidg,SLOT(invertSel()));
//	connect(selectMol,SIGNAL(triggered()),glWidg,SLOT(narrowSel()));

	addAtom		= new QAction(tr("Add &Atom"),this);
	addAtom->setShortcut(tr("A"));
	addAtom->setIcon(QIcon(":/images/atom.png"));
	addAtom->setStatusTip(tr("Open dialog window for adding an atom"));
	connect(addAtom,SIGNAL(triggered()),this,SLOT(addAtomDialog()));

	addBond		= new QAction(tr("Add or Remove &Bond"),this);
	addBond->setShortcut(tr("B"));
	addBond->setIcon(QIcon(":/images/bond1.png"));
	addBond->setStatusTip(tr("Add or remove bond between two selected atoms"));
	addBond->setEnabled(false);
	connect(addBond,SIGNAL(triggered()),this,SLOT(doAddBond()));


	deleteSelection		= new QAction(tr("&Delete Selected"),this);
	deleteSelection->setShortcut(tr("Del"));
	deleteSelection->setIcon(QIcon(":/images/delete.png"));
	deleteSelection->setStatusTip(tr("Delete selected atoms or molecules"));
	connect(deleteSelection,SIGNAL(triggered()),this,SLOT(doDelProc()));

	addFragment	= new QAction(tr("Add &Fragment"),this);
	addFragment->setShortcut(tr("F"));
	addFragment->setIcon(QIcon(":/images/fragm1.png"));
	addFragment->setStatusTip(tr("Open window for adding a molecular fragment"));
	connect(addFragment,SIGNAL(triggered()),this,SLOT(addFragmentDialog()));

	separateMol	= new QAction(tr("&Splite Molecule"),this);
	separateMol->setShortcut(tr("S"));
	separateMol->setIcon(QIcon(":/images/sepmol.png"));
	separateMol->setStatusTip(tr("Splite molecule on unbonding submolecules"));
	separateMol->setEnabled(false);
	connect(separateMol,SIGNAL(triggered()),this,SLOT(doSepMol()));

	unionMols	= new QAction(tr("&Unate Molecules"),this);
	unionMols->setShortcut(tr("U"));
	unionMols->setIcon(QIcon(":/images/unimol.png"));
	unionMols->setStatusTip(tr("Unate molecules into one molecule"));
	unionMols->setEnabled(false);
	connect(unionMols,SIGNAL(triggered()),this,SLOT(doUniMols()));


	doTurnAction	= new QAction(tr("&Turn Selected"),this);
	doTurnAction->setIcon(QIcon(":/images/turn.png"));
	doTurnAction->setStatusTip(tr("Switch to mode for turn a molecule or selected fragment."));
	doTurnAction->setEnabled(false);
	connect(doTurnAction,SIGNAL(triggered()),this,SLOT(rotatOn()));

	doActSpcAction	= new QAction(tr("&Actual Space"),this);
	doActSpcAction->setIcon(QIcon(":/images/actcube.png"));
	doActSpcAction->setStatusTip(tr("Show the actual space cube dialog window."));
	doActSpcAction->setEnabled(true);
	connect(doActSpcAction,SIGNAL(triggered()),this,SLOT(ActSpcOn()));
}

void MainWindow::createHelpActions()	
{
	AboutAction	= new QAction(tr("&About"),this);
	//exitAction->setShortcut(tr("Ctrl+Q"));
	//AboutAction->setShortcut(QKeySequence::HelpContents);
	AboutAction->setIcon(QIcon(":/images/mr3.png"));

	AboutAction->setStatusTip(tr("About programm MolRed"));
	connect(AboutAction,SIGNAL(triggered()), this, SLOT(about()));


	HelpAction= new QAction(tr("&Help"),this);
	HelpAction->setShortcut(QKeySequence::HelpContents);
	connect(HelpAction,SIGNAL(triggered()), this, SLOT(help()));

}
void MainWindow::createOptionsActions()	
{
	displayWireAction	= new QAction(tr("&Wire"),this);
	displayWireAction->setShortcut(tr("W"));
	displayWireAction->setStatusTip(tr("Change display mode to wire for all molecules"));
	connect(displayWireAction,SIGNAL(triggered()), this, SLOT(selectWire()));

	displayBallStickAction	= new QAction(tr("&Ball and Stick"),this);
	displayBallStickAction->setShortcut(tr("O"));
	displayBallStickAction->setStatusTip(tr("Change display mode to ball and stick for all molecules"));
	connect(displayBallStickAction,SIGNAL(triggered()),this, SLOT(selectBallStick()));

	OrthoPerspAction	= new QAction(tr("Switch to Otrographic &Projection"),this);
	OrthoPerspAction->setIcon(QIcon(":/images/ortho.png"));
	OrthoPerspAction->setStatusTip(tr("Change projection from orthographic to pecrspctive and vice versa. (Current projection is perspective)"));
	connect(OrthoPerspAction,SIGNAL(triggered()),this, SLOT(ghangeprojection()));

	renderAtChAction	= new QAction(tr("Draw atom`s types"),this);
	renderAtChAction->setIcon(QIcon(":/images/ch.png"));
	renderAtChAction->setStatusTip(tr("Draw atom`s types"));
	connect(renderAtChAction,SIGNAL(triggered()),glWidg, SLOT(renderAtCh_on()));

	un_renderAtChAction	= new QAction(tr("Turn off atom`s types"),this);
	un_renderAtChAction->setIcon(QIcon(":/images/unch.png"));
	un_renderAtChAction->setStatusTip(tr("Turn off atom`s types"));
	connect(un_renderAtChAction,SIGNAL(triggered()),glWidg, SLOT(renderAtCh_off()));


	bkgdColorAction	= new QAction(tr("Change background color"),this);
	//un_renderAtChAction->setIcon(QIcon(":/images/unch.png"));
	//un_renderAtChAction->setStatusTip(tr("Turn off atom`s types"));
	connect(bkgdColorAction,SIGNAL(triggered()),glWidg, SLOT(changefoncolor()));

}
void MainWindow::createToolsActions()	
{
	surfaceBuildAction	= new QAction(tr("Build &Surface"),this);
	surfaceBuildAction->setShortcut(tr("T"));
	surfaceBuildAction->setIcon(QIcon(":/images/surf.png"));
	surfaceBuildAction->setStatusTip(tr("Build triangulated surface of SES around molecule"));
	surfaceBuildAction->setEnabled(false);
	connect(surfaceBuildAction,SIGNAL(triggered()),this,SLOT(buildSurf()));
}


void MainWindow::createMenus()
{
	fileMenu	= menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(newAction);
	fileMenu->addAction(openAction);
	fileMenu->addAction(mergeAction);
	fileMenu->addAction(saveAction);
	fileMenu->addAction(saveAsAction);
	separatorAction = fileMenu->addSeparator();
	exportSubMenu	= fileMenu->addMenu(tr("&Export"));
	exportSubMenu->addAction(export2vrmlAction);
	exportSubMenu->addAction(export2pictureAction);
	separatorAction = fileMenu->addSeparator();

	for(int i=0;i<MaxRecentFiles;++i)
	{
		fileMenu->addAction(recentFilesActions[i]);
	}

	fileMenu->addSeparator();
	fileMenu->addAction(exitAction);

	editMenu	= menuBar()->addMenu(tr("&Edit"));
	editMenu->addAction(undoAction);
	editMenu->addAction(redoAction);
	editMenu->addAction(undoredoAction);
	editMenu->addSeparator();
	editMenu->addAction(deleteSelection);
	editMenu->addAction(invertSelection);
	editMenu->addSeparator();
	editMenu->addAction(frameSelect);
	editMenu->addAction(narrowSelect);
	editMenu->addAction(selectMol);
	editMenu->addSeparator();
	editMenu->addAction(addAtom);
	editMenu->addAction(addBond);
	editMenu->addAction(addFragment);
	editMenu->addSeparator();
	editMenu->addAction(separateMol);
	editMenu->addAction(unionMols);
	editMenu->addSeparator();
	editMenu->addAction(doTurnAction);

	toolsMenu	= menuBar()->addMenu(tr("&Tools"));
	toolsMenu->addAction(surfaceBuildAction);
	
	
	optionsMenu	= menuBar()->addMenu(tr("&Options"));

	displaySubMenu	= optionsMenu->addMenu(tr("&Display"));
	displaySubMenu->addAction(displayWireAction);
	displaySubMenu->addAction(displayBallStickAction);
	displaySubMenu->addSeparator();
	displaySubMenu->addAction(OrthoPerspAction);
	displaySubMenu->addSeparator();
	displaySubMenu->addAction(renderAtChAction);
	displaySubMenu->addAction(un_renderAtChAction);
	displaySubMenu->addSeparator();
	displaySubMenu->addAction(bkgdColorAction);
	displaySubMenu->addSeparator();
	displaySubMenu->addAction(doActSpcAction);
	

	menuBar()->addSeparator();

	helpMenu	= menuBar()->addMenu(tr("&Help"));
	helpMenu->addAction(AboutAction);
	helpMenu->addAction(HelpAction);


	//contextMenu1 = QMenu

}


void MainWindow::hFun()
{
	Graph Gr;
	vecT<int> tps;
	tps.setlen(workFrame->Mls.x[0]->Atoms.N);
	for(int ii=0;ii<tps.mN;ii++)
	{
		tps.x[ii]	= workFrame->Mls.x[0]->Atoms.x[ii].id_Tpz;
	}

	Gr.setVertexes(tps);
	Gr.setAdjacency(workFrame->Mls.x[0]->Connect);
}


void MainWindow::about()
{
	QMessageBox::about(this,tr("About MolRed"),
		tr("<h2>MolRed ver. 2.5.6 </h2>"
		//"<p> Copyright &copy; 2011 Zhabin.S.N. "
		//"<p>   2011 Zhabin.S.N. "
		//"<p> MolRed - Molecular Redactor: programm for visualization and editing molecules. "));
		"<p> Authors: S.N.Zhabin, V.B.Sulimov "
		"<p>Copyright (C) 2009-2011 Dimonta, Ltd."
		"<p>All rights reserved."
		"<p> "
		"<p>MolRed - Molecule editor: the molecular structure visualization and editing program"));
}



void MainWindow::createToolBars()
{
	fileToolBar	= addToolBar(tr("&File"));
	fileToolBar->addAction(newAction);
	fileToolBar->addAction(openAction);
	fileToolBar->addAction(mergeAction);
	fileToolBar->addAction(saveAction);
	editToolBar	= addToolBar(tr("&Edit"));
	editToolBar->addAction(undoAction);
	editToolBar->addAction(redoAction);
	editToolBar->addSeparator();
	editToolBar->addAction(deleteSelection);
	editToolBar->addAction(invertSelection);
	editToolBar->addSeparator();
	editToolBar->addAction(frameSelect);
	editToolBar->addAction(narrowSelect);
	editToolBar->addAction(selectMol);
	editToolBar->addSeparator();
	editToolBar->addAction(addAtom);
	editToolBar->addAction(addBond);
	editToolBar->addAction(addFragment);
	editToolBar->addSeparator();
	editToolBar->addAction(separateMol);
	editToolBar->addAction(unionMols);
	editToolBar->addSeparator();
	editToolBar->addAction(doTurnAction);
	toolsToolBar	= addToolBar(tr("&Tools"));
	toolsToolBar->addAction(surfaceBuildAction);

	optionsToolBar	= addToolBar(tr("&Options"));
	optionsToolBar->addAction(OrthoPerspAction);
	optionsToolBar->addSeparator();
	optionsToolBar->addAction(renderAtChAction);
	optionsToolBar->addAction(un_renderAtChAction);
	optionsToolBar->addSeparator();
	optionsToolBar->addAction(doActSpcAction);
	
}

void MainWindow::help()
{
	const QDir doc("doc");
	QString path = doc.absolutePath();
	//QMessageBox::about(this,tr("Path:"),path);
	HelpBrowser::showPage(path,"index.html");
}

void MainWindow::browsel()
{
	glWidg->unselprod(treeView->getselatoms());
	glWidg->selAnalize();
	statgen();
	glWidg->rendScene();
	glWidg->update();
}

void MainWindow::browselMol()
{
	glWidg->unselprod(treeView->getselatoms());
	glWidg->selAnalize();
	glWidg->selectMols();
	statgen();
	glWidg->rendScene();
	glWidg->update();
}

void MainWindow::browchgMol()
{
	vecT<vec2int> idas;
	idas	= treeView->getselatoms();
	workFrame->Mls.x[idas.x[0].x[0]]->drawtype	= !workFrame->Mls.x[idas.x[0].x[0]]->drawtype;
	glWidg->rendScene();
	glWidg->update();
}

void MainWindow::browchangecolorSurf()
{
	vecT<int> ids;
	int tp,ii;
	double tsp;
	vec3int col;
	Surface *srf;

	ids	= treeView->getselsurfaces();
	col	= treeView->getcolor();

	for(ii=0;ii<ids.N;ii++)
	{
		srf	= workFrame->Srfcs.x[ids.x[ii]];
		//srf->setviztype(tp);
		tp	= srf->getviztype();
		tsp	= srf->gettransp();
		srf->setcolor(col);
		glWidg->rendSurface(srf,ids.x[ii],tp,tsp);
	}
	treeModel->updateModel();
	glWidg->rendScene();
	glWidg->update();
}

void MainWindow::browchangeSurf()
{
	vecT<int> ids;
	int tp,ii;
	double tsp;
	Surface *srf;

	ids	= treeView->getselsurfaces();
	tp	= treeView->get_s_type();

	for(ii=0;ii<ids.N;ii++)
	{
		srf	= workFrame->Srfcs.x[ids.x[ii]];
		//srf->setviztype(tp);
		
	

		switch (tp)
		{
		case 0 :
			{
				tsp	= srf->gettransp();
				glWidg->rendSurface(srf,ids.x[ii],tp,tsp);
			}
		case 1:
			{
				tsp	= srf->gettransp();
				glWidg->rendSurface(srf,ids.x[ii],tp,tsp);
				break;
			}
		case 2:
			{
				tsp	= srf->gettransp();
				glWidg->rendSurface(srf,ids.x[ii],tp,tsp);
				break;
			}
		case 3:
			{
				workFrame->DelMolSurf(srf);
				break;
			}
		case 4:
			{
				tsp	= srf->gettransp();
				tsp	= tsp == 1.0 ? 0.5 : 1.0;
				tp	= srf->getviztype();
				glWidg->rendSurface(srf,ids.x[ii],tp,tsp);
				//workFrame->DelMolSurf(srf);
				break;
			}
		}
	}

	glWidg->SurfModifyOn();
	treeModel->updateModel();
	glWidg->rendScene();
	glWidg->update();
	glWidg->SurfModifyOff();
}

void MainWindow::getaminos()
{
	int ii;
	QString	fileName;
	WorkFrame wfr;
	vecT<char> dir("amns/");
	vecT<char> ext(".hin");
	vecT<char> str;
	for(ii=0;ii<amin->aminos.N;ii++)
	{
		str.N=0;
		str.add(dir);
		str.add(amin->aminos.x[ii].Name);
		str.add(ext);
		str.add('\0');

		fileName.clear();
		fileName.append(str.x);
		wfr.Mls.N	= 0;
		wfr.readFile(fileName);
		amin->SetAminoAcid(ii,*wfr.Mls.x[0]);
	}
}
bool MainWindow::okToContinue()
{
	if(isWindowModified())
	{
		int r	= QMessageBox::warning(this,tr("MolRed"), tr("The current structures has been modified. \n Do you want to save your changes?"),
			QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
		if (r==QMessageBox::Yes)
		{
			return save();
		}else
			if (r==QMessageBox::Cancel)
			{
				return false;
			}
	}
	return true;
}
void MainWindow::setCurrentFile(const QString &fileName)
{
	curFile	= fileName;
	setWindowModified(false);

	QString shownName	= "Untitled";
	if(!curFile.isEmpty())
	{
		shownName	= StrippedName(curFile);
		setCurrentDir(GetDirName(curFile));
		recentFiles.removeAll(curFile);
		recentFiles.prepend(curFile);
		updateRecentFileActions();
	}
	setWindowTitle(tr("%1[*] - %2").arg(shownName).arg(tr("Molred")));
}

void MainWindow::setCurrentDir(const QString &dirName)
{
	curDir	= dirName;
	/*setWindowModified(false);

	QString shownName	= "Untitled";
	if(!curFile.isEmpty())
	{
		shownName	= StrippedName(curFile);
		recentFiles.removeAll(curFile);
		recentFiles.prepend(curFile);
		updateRecentFileActions();
	}
	setWindowTitle(tr("%1[*] - %2").arg(shownName).arg(tr("Molred")));*/
}

void MainWindow::updateRecentFileActions()
{
	QMutableStringListIterator i(recentFiles);
	while(i.hasNext())
	{
		if(!QFile::exists(i.next()))
		{
			i.remove();
		}
	}
	for(int j=0;j<MaxRecentFiles;++j)
	{
		if(j<recentFiles.count())
		{
			QString text = tr("&%1 %2").arg(j+1).arg(StrippedName(recentFiles[j]));
			recentFilesActions[j]->setText(text);
			recentFilesActions[j]->setData(recentFiles[j]);
			recentFilesActions[j]->setVisible(true);
		}else
		{
			recentFilesActions[j]->setVisible(false);
		}
	}
	separatorAction->setVisible(!recentFiles.isEmpty());

}
QString MainWindow::StrippedName(const QString &fullfileName)
{
	return QFileInfo(fullfileName).fileName();
}
QString MainWindow::GetDirName(const QString &fullfileName)
{
	return QFileInfo(fullfileName).absolutePath();
}
void MainWindow::newFile()
{
	if(okToContinue())
	{
		workFrame->Mls.N=0;
		workFrame->DelMolSurf();
//		workFrame->id_select.N=0;
		treeModel->updateModel();
		undo_redo->reset_all();
		vec3db r0,r1;
		r0	= 0.0;
		r1	= r0;
		r1.x[2]= 10;
		
		glWidg->setCamera(r0,r1);
		glWidg->clearSelPar();
		glWidg->rendScene();//genScene();
		glWidg->renderAtCh_off();
		glWidg->setIsSurf(false);
		glWidg->update();
		setCurrentFile("");
	}
}


void MainWindow::loadSettings()
{
	FILE *fio;
	vecT<char> str;
	char	*xc;

	QString dirName;

	str.setlen(1000);
	fio	= fopen("settings.txt","r");
	if (fio!=NULL)
	{
		do
		{
			fgets(str.x,str.N,fio);	// чтение строки
			xc	= str.x;
			if (memcmp(str.x,"Current dir : ",14*sizeof(char))==0)
			{
				xc = str.x+14;
				dirName.append(xc);
				setCurrentDir(dirName);
			}
		}while(!feof(fio));
		fclose(fio);	
	}
}


void MainWindow::saveSettings()
{
	FILE *fio;
	vecT<char> str;
	QChar	*xc;
	int ii;

	str.add("Current dir : ",14);
	
	xc	= curDir.data();

	for(ii=0;ii<curDir.length();ii++)
	{
		str.add(xc[ii].toLatin1());
	}
	str.add('\0');

	fio	= fopen("settings.txt","w");
	if (fio!=NULL)
	{
		fprintf(fio,"%s","Settings for Molred \n");
		fprintf(fio,"%s","\n");
		fprintf(fio,"%s",str.x);
		fclose(fio);	
	}
}

void MainWindow::open()
{
	if(okToContinue())
	{
		QString	fileName	= QFileDialog::getOpenFileName(this,tr("Open Molecule"),curDir,
			tr("Molecule structures files (*.hin *.pdb *.mrk *.xyz *.mol)"));
		if(!fileName.isEmpty())
		{
			workFrame->Mls.N=0;
//			workFrame->id_select.N=0;
			treeModel->updateModel();
			//id_cr_op	= 1;
			undo_redo->reset_all();
			loadFile(fileName);
			setCurrentFile(fileName);
		}
	}
}

void MainWindow::openRecentFile()
{

	QAction *action = qobject_cast<QAction *>(sender());
	if (action)
	{
		//loadFile(action->data().toString());

		workFrame->Mls.N=0;
//		workFrame->id_select.N=0;
		treeModel->updateModel();
		//id_cr_op	= 1;
		undo_redo->reset_all();

		QString	fileName(action->data().toString());
		loadFile(fileName);
		setCurrentFile(fileName);
	}
}

void MainWindow::open(char *fname)
{
	workFrame->Mls.N=0;
//	workFrame->id_select.N=0;
	treeModel->updateModel();
	//id_cr_op	= 1;
	undo_redo->reset_all();

	QString	fileName(fname);
	loadFile(fileName);
	setCurrentFile(fileName);
}

void MainWindow::open(QString fname)
{
	workFrame->Mls.N=0;
//	workFrame->id_select.N=0;
	treeModel->updateModel();
	//id_cr_op	= 1;
	undo_redo->reset_all();

	//QString	fileName(fname);
	loadFile(fname);
	setCurrentFile(fname);
}

void MainWindow::merge()
{
	QString	fileName	= QFileDialog::getOpenFileName(this,tr("Open Molecule"),curDir,
		tr("Molecule structures files (*.hin *.pdb *.mrk *.xyz *.mol)"));
	if(!fileName.isEmpty())
	{
		loadFile(fileName);
		//setCurrentDir(GetDirName(curFile));
		setWindowModified(true);
	}
}
bool MainWindow::save()
{
	if(curFile.isEmpty())
	{
		return saveAs();
	}else
	{
		if (frstmod)
		{
			int r	= QMessageBox::warning(this,tr("MolRed"), tr("The current structures has been modified. \n Do you want to save your changes in current file (Yes) or in another one (Save)?"),
			QMessageBox::Yes|QMessageBox::Save|QMessageBox::Cancel,QMessageBox::Cancel);
			if (r==QMessageBox::Yes)
			{
				if (saveFile(curFile))
				{
					frstmod	= false;
					return true;
				}else
				{
					return false;
				}
			}else
			if (r==QMessageBox::No)
			{
				if (saveAs())
				{
					frstmod	= false;
					return true;
				}else
				{
					return false;
				}
			}else
			if(r==QMessageBox::Cancel)
			{
				return false;
			}
		}else
		return saveFile(curFile);
	}
	return false;
}

bool MainWindow::saveAs()
{
	QString	fileName	= QFileDialog::getSaveFileName(this,tr("Save Molecule As"),curDir,
			tr("Molecule structures files (*.hin *.mrk *.xyz *.pdb)"));
	if(fileName.isEmpty())
	{
		return false;
	}
	return saveFile(fileName);
}

bool MainWindow::saveFile(const QString &fileName)
{
	if(!workFrame->writeFile(fileName))
	{
		statusBar()->showMessage(tr("Saving canceled."),2000);
		return false;
	}
	setCurrentFile(fileName);
	statusBar()->showMessage(tr("Molecule saved"),2000);
	return true;
}

bool MainWindow::loadFile(const QString &fileName)
{
	//int mN	= workFrame->Mls.N;
	WorkFrame *wfr = new WorkFrame;
	Molecule *mol;
	//mol	= new Molecule;
	if(!wfr->readFile(fileName))
	{
		statusBar()->showMessage(tr("Loading canceled."),2000);
		return false;
	}
	statusBar()->showMessage(tr("File Loaded."),2000);
	//delete treeModel->rootItem;
	/*for(int i=mN;i<workFrame->Mls.N;i++)
	{
		treeModel->setUpModelData(workFrame->Mls.x[i],workFrame->TableZR);
	}*/
	
	int ii;
	QString shortfN;

	shortfN	= StrippedName(fileName);
	//shortfN.toLatin1();
	
	//glWidg->initmol(workFrame);
	for(ii=0;ii<wfr->Mls.N;ii++)
	{
		//mol	= new Molecule;
		mol	= wfr->Mls.x[ii];
		mol->Name.N	= 0;
		mol->Name.add(shortfN.toLatin1());
		mol->Name.add('\0');
		doAddMol(mol);
		wfr->Mls.x[ii]	= 0x0;
	}


	/*workFrame->Mls.x[0]->p_prt->getChild(1)->getChild(71)->delChild(4);
	p_atm	= new atom_node;
	p_atm->atom = &workFrame->Mls.x[0]->Atoms.x[649];
	workFrame->Mls.x[0]->p_prt->getChild(1)->getChild(71)->addChild(p_atm);
	workFrame->Mls.x[0]->p_prt->getChild(1)->getChild(71)->delChild(11);
*/
	/*for(ii=0;ii<wfr.Prot.N;ii++)
	{
		prt	= new Protein;
		*prt	= *wfr.Prot.x[ii];
		doAddProt(prt);
	}*/
	//glWidg->initmol(workFrame);
	vec3db r0,r1;
	r0	= vec3db(0.0,0.0,0.0);//
	ii	= workFrame->Mls.N-wfr->Mls.N;
	for(;ii<workFrame->Mls.N;ii++)
	{
		r0	+= workFrame->Mls.x[ii]->getGCM();
	}
	r0	/= (double)wfr->Mls.N;
	//workFrame->Mls.N>0 ? wfr.Mls.x[0]->getGCM() : vec3db(0.0,0.0,0.0);
	r1	= r0;
	double d;
	d	= workFrame->Mls.N>0 ? 3*workFrame->Mls.x[workFrame->Mls.N-1]->getMSz() : 3.0;
	r1.x[2]	-= d;

	delete wfr;

	glWidg->setCamera(r0,r1);
	glWidg->rendScene();//genScene();
	glWidg->update();
	//imag2file();
	return true;
}

void MainWindow::imag2file(QString fname)
{
	QImage img;
	QImageWriter imgwr;
	glWidg->rendScene();//genScene();
	glWidg->update();
	img	= glWidg->grabFrameBuffer();
	imgwr.setFileName(fname);
	imgwr.setQuality(85);
	imgwr.setFormat("jpg");
	imgwr.write(img);
}

void MainWindow::export2vrml()
{
	//glWidg->rendPrmtv();
	//glWidg->rendScene();
}

void MainWindow::export2picture()
{
	QString	fileName	= QFileDialog::getSaveFileName(this,tr("Export scene to a jpg "),curDir,
			tr("JPG files (*.jpg )"));
	if (!fileName.isEmpty())
	{
		imag2file(fileName);
	}
}


void MainWindow::selectBallStick()
{
	int ii;
	for(ii=0;ii<workFrame->Mls.N;ii++)
	{
		workFrame->Mls.x[ii]->drawtype	= 0;
	}
	for(ii=0;ii<workFrame->Prot.N;ii++)
	{
			workFrame->Prot.x[ii]->drawtype	= 0;
	}
	glWidg->rendScene();//genScene();//*workFrame);
	glWidg->update();
//	glWidg->draw();
}


void MainWindow::selectWire()
{
//	glWidg->genWrScene();//*workFrame);
	int ii;
	for(ii=0;ii<workFrame->Mls.N;ii++)
	{
		workFrame->Mls.x[ii]->drawtype	= 1;
	}
	for(ii=0;ii<workFrame->Prot.N;ii++)
	{
			workFrame->Prot.x[ii]->drawtype	= 1;
	}
	glWidg->rendScene();
	glWidg->update();
//	glWidg->draw();
}

void MainWindow::addAtomDialog()
{
	mendeleevTable->show();
}
void MainWindow::addFragmentDialog()
{
	fragmentBrowser->show();
	//glWidg->FrgBrwOn();
}
void MainWindow::doAddFrg()
{
	WorkFrame	*wF;
	wF	= fragmentBrowser->getwrkFrm();
	wF->Mls.x[0]->setGCM(glWidg->gettv());
	Molecule *mol;
	mol	= new Molecule;
	*mol	= *wF->Mls.x[0];
	doAddMol(mol);
	setWindowModified(true);
}
void MainWindow::ActSpcOn()
{
	ActSpc->show();
}

void MainWindow::undredhis()
{
	undo_redo->show();
}
void MainWindow::rotatOn()
{
	vec3db qc;
	int id_ml;
	Molecule *lmol;

	rotatWin->show();
	id_ml	= glWidg->sel_idm.x[0];

	lmol	= reinterpret_cast<Molecule *> (glWidg->mols.x[id_ml]);

	qc	= lmol->getGCM();
	rotatWin->SetDis(qc);
	glWidg->setrwr(true);
	glWidg->setmolcrd(id_ml);
	glWidg->clearQuat();
	glWidg->update();
}

void MainWindow::doAddMol(Molecule *mol)
{
	if(!undoAction->isEnabled()) undoAction->setEnabled(true);
	undo_redo->chesk_reset();//if(operations.N!=id_cr_op) reset_op();
	undo_redo->AddMol_init(mol);	// инициализация добавления новой молекулы 
	undo_redo->AddMol_op();	// добавить молекулу
	undo_redo->inc_cur_pos();	// увеличение индикатора текущей операции

	/*int id_ml,ii,n_at;
	vec3db rc;
	id_ml	= workFrame->Mls.N-1;
	for(ii=0;ii<mol->Atoms.N;ii++)
	{
		undo_redo->AddAtm_init(id_ml);//mol->Atoms.x[ii].id_Tpz);
		undo_redo->AddAtm_op();
		undo_redo->inc_cur_pos();	// увеличение индикатора текущей операции
		n_at	= workFrame->Mls.x[id_ml]->Atoms.N-1;	// номер добавленого атома - атомы добавляются в конец массива
		undo_redo->ChgTyp_init(id_ml,n_at,mol->Atoms.x[ii].id_Tpz);	// инициализация данных для изменения типа атома
		undo_redo->ChgTyp_op();// выполнение изменения типа атома
		undo_redo->inc_cur_pos();	// увеличение индикатора
		undo_redo->MovAtm_init(id_ml,n_at,mol->Atoms.x[ii].r); // инициализация смещения атома в центр вращения
		undo_redo->MovAtm_op();	// смещения
		undo_redo->inc_cur_pos();	// увеличение индикатора
	}

	int id_at1,id_at2,io;
	for(ii=0;ii<mol->Bonds.N;ii++)
	{
		id_at1	= mol->Bonds.x[ii].id_Atoms.x[0];
		id_at2	= mol->Bonds.x[ii].id_Atoms.x[1];
		undo_redo->AddBnd_init(id_ml,id_at1,id_at2);
		undo_redo->AddBnd_op();
		undo_redo->inc_cur_pos();
		n_at	= workFrame->Mls.x[id_ml]->Bonds.N-1;
		io		= mol->Bonds.x[ii].oder;
		undo_redo->ChgBnd_init(id_ml,id_at1,id_at2,io);  //undo_redo->ChgBnd_init(int id_ml,int &id_bn,int &id_tp)	// изменить тип связи
		undo_redo->ChgBnd_op();
		undo_redo->inc_cur_pos();
	}
		
	//workFrame->Mls.x[id_ml]=*mol;
	//treeModel->setUpModelData(workFrame->Mls.x[id_ml],workFrame->TableZR);
	
*/
	treeModel->updateModel();

	undo_redo->Stop_init();
	glWidg->rendScene();//genScene();
	glWidg->update();
}

/*void MainWindow::doAddProt(Protein *prot)
{
	if(!undoAction->isEnabled()) undoAction->setEnabled(true);
	undo_redo->chesk_reset();	//if(operations.N!=id_cr_op) reset_op();
	undo_redo->AddProt_init(prot);	// инициализация добавления нового протеина 
	undo_redo->AddMol_op();		// добавить протеин
	undo_redo->inc_cur_pos();	// увеличение индикатора текущей операции

	treeModel->updateModel();

	undo_redo->Stop_init();
	glWidg->rendScene();//genScene();
	glWidg->update();
}*/
/*void MainWindow::doAddMol_(Molecule *mol)
{
	undoredo->AddMol_init(mol);	// инициализация добавления новой молекулы (пустой)
	undoredo->undoredo->AddMol_op();	// добавить пустую молекулу
	undo_redo->inc_cur_pos();	// увеличение индикатора текущей операции
	int id_ml,ii,n_at;
	vec3db rc;
	id_ml	= workFrame->Mls.N-1;
	for(ii=0;ii<mol->Atoms.N;ii++)
	{
		undo_redo->AddAtm_init(id_ml);//mol->Atoms.x[ii].id_Tpz);
		undo_redo->AddAtm_op();
		undo_redo->inc_cur_pos();	// увеличение индикатора текущей операции
		n_at	= workFrame->Mls.x[id_ml]->Atoms.N-1;	// номер добавленого атома - атомы добавляются в конец массива
		undo_redo->ChgTyp_init(id_ml,n_at,mol->Atoms.x[ii].id_Tpz);	// инициализация данных для изменения типа атома
		undo_redo->ChgTyp_op();// выполнение изменения типа атома
		undo_redo->inc_cur_pos();	// увеличение индикатора
		undo_redo->MovAtm_init(id_ml,n_at,mol->Atoms.x[ii].r); // инициализация смещения атома в центр вращения
		undo_redo->MovAtm_op();	// смещения
		undo_redo->inc_cur_pos();	// увеличение индикатора
	}

	int id_at1,id_at2,io;
	for(ii=0;ii<mol->Bonds.N;ii++)
	{
		id_at1	= mol->Bonds.x[ii].id_Atoms.x[0];
		id_at2	= mol->Bonds.x[ii].id_Atoms.x[1];
		undo_redo->AddBnd_init(id_ml,id_at1,id_at2);
		undo_redo->AddBnd_op();
		undo_redo->inc_cur_pos();
		n_at	= workFrame->Mls.x[id_ml]->Bonds.N-1;
		io		= mol->Bonds.x[ii].oder;
		undo_redo->ChgBnd_init(id_ml,id_at1,id_at2,io);  //undo_redo->ChgBnd_init(int id_ml,int &id_bn,int &id_tp)	// изменить тип связи
		undo_redo->ChgBnd_op();
		undo_redo->inc_cur_pos();
	}
}*/


void MainWindow::doDelMol(int id_ml)
{
	undo_redo->chesk_reset();

	int jj;
	//int id_at,jj,ib,io,id_at1,id_at2;
	//vec3db rc;

	vecT<int> ids_mlat;
	glWidg->check_Selected_ids(ids_mlat);
	glWidg->del_Selected_ids(ids_mlat);

	jj	= workFrame->Mls.N-1;
	if(jj!=id_ml)
	{
		undo_redo->SwpMol_init(id_ml,jj);
		undo_redo->SwpMol_op();
		undo_redo->inc_cur_pos();
		id_ml	= jj;
	}

	undo_redo->DelMol_init(id_ml);
	undo_redo->DelMol_op();
	undo_redo->inc_cur_pos();



	/*for(id_at=workFrame->Mls.x[id_ml]->Atoms.N-1;id_at>=0;id_at--)
	{
		jj	= 0;
		while(workFrame->Mls.x[id_ml]->Connect.I.x[id_at].N!=0)
		{
			ib	= workFrame->Mls.x[id_ml]->Connect.S.x[id_at].x[jj];
			if(ib !=0)
			{
				ib--;
				io	= 1;//workFrame->Mls.x[id_ml]->Bonds.x[ib].oder;
				id_at1	= workFrame->Mls.x[id_ml]->Bonds.x[ib].id_Atoms.x[0];
				id_at2	= workFrame->Mls.x[id_ml]->Bonds.x[ib].id_Atoms.x[1];
				undo_redo->ChgBnd_init(id_ml,id_at1,id_at2,io);
				undo_redo->ChgBnd_op();
				undo_redo->inc_cur_pos();
				undo_redo->DelBnd_init(id_ml,id_at1,id_at2);
				undo_redo->DelBnd_op();
				undo_redo->inc_cur_pos();
			}
		}
		rc	= workFrame->Mls.x[id_ml]->Atoms.x[id_at].r;
		rc	*= -1;
		undo_redo->MovAtm_init(id_ml,id_at,rc);
		undo_redo->MovAtm_op();	// смещения
		undo_redo->inc_cur_pos();	// увеличение индикатора

		undo_redo->ChgTyp_init(id_ml,id_at,0);	// инициализация данных для изменения типа атома
		undo_redo->ChgTyp_op();// выполнение изменения типа атома
		undo_redo->inc_cur_pos();	// увеличение индикатора

		undo_redo->DelAtm_init(id_ml,id_at);
		undo_redo->DelAtm_op();
		undo_redo->inc_cur_pos();
	}
	// удалить молекулу у которой не осталось ни одного атома
	undo_redo->DelMol_init(id_ml);
	undo_redo->DelMol_op();
	undo_redo->inc_cur_pos();*/

	undo_redo->Stop_init();
	treeModel->updateModel();
	glWidg->rendScene();//genScene();
	glWidg->update();
}

void MainWindow::doDelMol_(int id_ml)
{
	int jj;



	jj	= workFrame->Mls.N-1;
	if(jj!=id_ml)
	{
		undo_redo->SwpMol_init(id_ml,jj);
		undo_redo->SwpMol_op();
		undo_redo->inc_cur_pos();
		id_ml	= jj;
	}
	
	undo_redo->DelMol_init(id_ml);
	undo_redo->DelMol_op();
	undo_redo->inc_cur_pos();

	if ((id_ml==id_ml_srf))
	{
		glWidg->setIsSurf(false);
	}
}

void MainWindow::doAddAtom(int id) // добавление выбранного атома
{
	if(!undoAction->isEnabled()) undoAction->setEnabled(true);
	undo_redo->chesk_reset();
	int n_at,id_ml;
	//AtomData * ptr;

	undo_redo->AddMol_init(0x0);	// инициализация добавления новой молекулы (пустой)
	undo_redo->AddMol_op();	// добавить пустую молекулу
	undo_redo->inc_cur_pos();	// увеличение индикатора текущей операции

	id_ml	= workFrame->Mls.N-1;
	undo_redo->AddAtm_init(id_ml);	// инициализация данных для добавления атома в молекулу с номером 0
	undo_redo->AddAtm_op();	// выполнение добавления атома 
	n_at	= workFrame->Mls.x[id_ml]->Atoms.N-1;	// номер добавленого атома - атомы добавляются в конец массива
	//vec2int opr;
	//opr.x[0]	= 0;
	//opr.x[1]	= n_at;
	//id_at_dl_op.add(opr);
	//id_ml_dl_op.add(0);	// инициализация обратной операции - удаления добавленого атома

	undo_redo->inc_cur_pos();	// увеличение индикатора текущей операции
	undo_redo->ChgTyp_init(id_ml,n_at,id,0x0);	// инициализация данных для изменения типа атома
	undo_redo->ChgTyp_op();// выполнение изменения типа атома
	undo_redo->inc_cur_pos();	// увеличение индикатора

	vec3db rc;
	rc	= glWidg->getrc();
	rc	+= glWidg->getFocPos();

	undo_redo->MovAtm_init(id_ml,n_at,rc); // инициализация смещения атома в центр вращения
	undo_redo->MovAtm_op();	// смещения
	undo_redo->inc_cur_pos();	// увеличение индикатора

	treeModel->updateModel();//workFrame->Mls.x[id_ml],workFrame->TableZR);
	undo_redo->Stop_init();

	glWidg->rendScene();//genScene();	
	glWidg->update();
	/*vec3db rc;
	vec3db fp;
	rc	= glWidg->getrc();
	fp	= glWidg->getFocPos();
	workFrame->Mls.x[0].AtomIns(id);
	workFrame->Mls.x[0]->Atoms.x[workFrame->Mls.x[0]->Atoms.N-1].r = rc+fp;
	glWidg->rendScene();//genScene();
	*/
}

void MainWindow::doAddAtom() // добавление выбранного атома
{
	if(!undoAction->isEnabled()) undoAction->setEnabled(true);
	undo_redo->chesk_reset();
	int n_at,id_ml,id,id1;
	id	= mendeleevTable->getID();	// получить номер типа выбранного атома

	id1	= glWidg->getAtId();
	if(id1==-1)
	{
		Molecule *mol	= new Molecule;

		mol->ReInit(1);
		mol->AtomIns(id);
		mol->Atoms.x[0].r	= glWidg->gettv();

		undo_redo->AddMol_init(mol);	// инициализация добавления новой молекулы
		undo_redo->AddMol_op();	// добавить молекулу
		undo_redo->inc_cur_pos();	// увеличение индикатора текущей операции
	}else
	{
		id_ml	= glWidg->getMlId();
		if (glWidg->getAddTp()==0)
		{
			glWidg->clrIds();
			undo_redo->ChgTyp_init(id_ml,id1,id,0x0);
			undo_redo->ChgTyp_op();
			undo_redo->inc_cur_pos();
		}else
		{
			glWidg->clrIds();
			undo_redo->AddAtm_init(id_ml);
			undo_redo->AddAtm_op();	// добавить атом
			undo_redo->inc_cur_pos();	// увеличение индикатора текущей операции

			n_at	= workFrame->Mls.x[id_ml]->Atoms.N-1;

			undo_redo->ChgTyp_init(id_ml,n_at,id,0x0);	// инициализация данных для изменения типа атома
			undo_redo->ChgTyp_op();// выполнение изменения типа атома
			undo_redo->inc_cur_pos();	// увеличение индикатора

			vec3db rc;
			rc	= workFrame->Mls.x[id_ml]->Atoms.x[id1].r;
			glWidg->get3Dfrom2D(rc);
			rc	= glWidg->gettv();
			//rc	+= glWidg->getFocPos();

			undo_redo->MovAtm_init(id_ml,n_at,rc); // инициализация смещения атома 
			undo_redo->MovAtm_op();	// смещение
			undo_redo->inc_cur_pos();	// увеличение индикатора


			undo_redo->AddBnd_init(id_ml,id1,n_at);
			undo_redo->AddBnd_op();
			undo_redo->inc_cur_pos();
		}
	}

	treeModel->updateModel();//workFrame->Mls.x[id_ml],workFrame->TableZR);
	undo_redo->Stop_init();
	glWidg->rendScene();//genScene();	
	glWidg->update();
	setWindowModified(true);
}


void MainWindow::doDelProc()
{
	if(glWidg->select_id.N>0)
	{
		if(!undoAction->isEnabled()) undoAction->setEnabled(true);
		if(glWidg->sel_idm.N!=0)//(glWidg->getMolSel())
		{
			int ii;
			undo_redo->chesk_reset();
			for(ii=glWidg->sel_idm.N-1;ii>=0;ii--)
			{
				doDelMol_(glWidg->sel_idm.x[ii]);
			}
			undo_redo->Stop_init();
			treeModel->updateModel();//workFrame->Mls.x[id_ml],workFrame->TableZR);
			glWidg->s_id.N	= 0;
			glWidg->selAnalize();
			glWidg->sel_idm.N = 0;
			statgen();
			glWidg->rendScene();//genScene();	
			glWidg->update();
		}
		else
		{
			doDelAtom();
		}
		setWindowModified(true);
	}
}

void MainWindow::doDelAtom() // удаление выделенных атомов
{
	if (glWidg->select_id.N!=0)
	{
		undo_redo->chesk_reset();
		vec3db rc;
		int id_ml,id_at,ii,jj,ib,io,id_at1,id_at2;
		Molecule *lmol;
		glWidg->selsort();
		//unselprod()
		vecT<int> ids_mlat;
		glWidg->check_Selected_ids(ids_mlat);
		glWidg->del_Selected_ids(ids_mlat);
		for( ii=0;ii<glWidg->select_id.N;ii++)
		{
			id_ml	= glWidg->select_id.x[ii].x[0];
			lmol	= reinterpret_cast< Molecule *> (glWidg->mols.x[id_ml]);
			id_at1	= glWidg->select_id.x[ii].x[1];
			id_at2	= lmol->Atoms.N-1;

			if(id_at1!=id_at2)
			{	// удаляемый атом перемещается ("свопится") в конец массива
				undo_redo->SwpAtm_init(id_ml,id_at1,id_at2);
				undo_redo->SwpAtm_op();
				undo_redo->inc_cur_pos();
				glWidg->select_id.x[ii].x[1]	= id_at	= id_at2;
			}else
			{
				id_at	= id_at1;
			}
			jj	= 0;
			// в id_at - номер последнего атома, который теперь нужно удалить
			while(lmol->Connect.I.x[id_at].N!=0)
			{
				//jj++;
				ib	= lmol->Connect.S.x[id_at].x[jj];
				if(ib !=0)
				{
					ib--;
					io	= 1;//workFrame->Mls.x[id_ml]->Bonds.x[ib].oder;
					id_at1	= lmol->Bonds.x[ib].id_Atoms.x[0];
					id_at2	= lmol->Bonds.x[ib].id_Atoms.x[1];
					undo_redo->ChgBnd_init(id_ml,id_at1,id_at2,io);
					undo_redo->ChgBnd_op();
					undo_redo->inc_cur_pos();
					undo_redo->DelBnd_init(id_ml,id_at1,id_at2);
					undo_redo->DelBnd_op();
					undo_redo->inc_cur_pos();
				}
			}
			rc	= lmol->Atoms.x[id_at].r;
			rc	*= -1;
			undo_redo->MovAtm_init(id_ml,id_at,rc);
			undo_redo->MovAtm_op();	// смещения
			undo_redo->inc_cur_pos();	// увеличение индикатора

			if(lmol->mol_type==PROTEINE)
			{
				atom_node * p_atm	= lmol->Atoms.x[id_at].dat.dat->amin;
				jj		= p_atm->parent->parent->id;
				io		= p_atm->parent->id;
				id_at2	= p_atm->id;
				undo_redo->DelPaa_init(id_ml,jj, io, id_at2);//lmol->Atoms.x[id_at].dat.dat->amin); ///  инициализация удаления атом-узла
				undo_redo->DelPaa_op();
				undo_redo->inc_cur_pos();

				if(lmol->p_prt->childs.x[jj]->childs.x[io]->childs.N==0)
				{
					undo_redo->DelAmn_init(id_ml,jj,io);
					undo_redo->DelAmn_op();
					undo_redo->inc_cur_pos();
					if(lmol->p_prt->childs.x[jj]->childs.N==0)
					{
						undo_redo->DelChn_init(id_ml,jj);
						undo_redo->DelChn_op();
						undo_redo->inc_cur_pos();
						if(lmol->p_prt->childs.N==0)
						{
							undo_redo->DelPrt_init(id_ml);
							undo_redo->DelPrt_op();
							undo_redo->inc_cur_pos();
						}
					}
				}
			}

			undo_redo->ChgTyp_init(id_ml,id_at,0,0x0);	// инициализация данных для изменения типа атома
			undo_redo->ChgTyp_op();// выполнение изменения типа атома
			undo_redo->inc_cur_pos();	// увеличение индикатора

			undo_redo->DelAtm_init(id_ml,id_at);
			undo_redo->DelAtm_op();
			undo_redo->inc_cur_pos();

			if(lmol->Atoms.N==0)
			{
				// удалить молекулу у которой не осталось ни одного атома
				jj	= workFrame->Mls.N-1;
				if(id_ml!=jj)
				{
					undo_redo->SwpMol_init(id_ml,jj);
					undo_redo->SwpMol_op();
					undo_redo->inc_cur_pos();
					id_ml	= jj;
				}
				undo_redo->DelMol_init(id_ml);
				undo_redo->DelMol_op();
				undo_redo->inc_cur_pos();
			}
				/*vecT<vecT<int> > ida;
				workFrame->Mls.x[id_ml]->SepMolInd(ida);
				if(ida.N>1)
				{
					// произвести разделение на ida.N молекул
					vecT<Molecule>  mols;
					workFrame->Mls.x[id_ml]->SepMol(mols,ida);
					for(jj=0;jj<mols.N;jj++)
					{
						doAddMol_(mols.x+jj);
					}
					doDelMol(id_ml);
				}*/
		}
		
		undo_redo->Stop_init();
		//sl_ids.N		= 0;
		//glWidg->select_id.N	= 0;
		glWidg->s_id.N	= 0;
		glWidg->selAnalize();
		treeModel->updateModel();
		glWidg->rendScene();//genScene();
		glWidg->update();
	}
}

void MainWindow::doAddBond() // добавление связи
{
	if (glWidg->select_id.N==2)
	{
		/*if(sl_ids.x[0].x[0]!=sl_ids.x[1].x[0])
		{
			int id_ml1,id_ml2,n_at;
			id_ml1	= sl_ids.x[0].x[0];
			id_ml2	= sl_ids.x[1].x[0];	
			if(id_ml2<id_ml1)
			{
				int id;
				id		= id_ml2;
				id_ml2	= id_ml1;
				id_ml1	= id;
				id		= sl_ids.x[1].x[1];
				sl_ids.x[1].x[1]	= sl_ids.x[0].x[1];
				sl_ids.x[0].x[1]	= id;
			}
			n_at	= workFrame->Mls.x[id_ml1]->Atoms.N;

			undo_redo->UniMol_init(id_ml1,id_ml2);	// объединить две молекулы
			undo_redo->UniMol_op();
			undo_redo->inc_cur_pos();
			//selprod();
			sl_ids.x[1].x[0]	= sl_ids.x[0].x[0]	= id_ml1;	// установлен номер молекулы с меньшим значением
			sl_ids.x[1].x[1]	+= n_at;	// номер атома второй молекулы при объединении с перовй принимает значение большее на число атомов в первой молекуле
			unselprod();
		}*/
		if(glWidg->select_id.x[0].x[0]==glWidg->select_id.x[1].x[0])
		{

			undo_redo->chesk_reset();
			int id_ml,id_at1,id_at2;
			Molecule *lmol;
			id_ml	= glWidg->select_id.x[0].x[0];
			id_at1	= glWidg->select_id.x[0].x[1];
			id_at2	= glWidg->select_id.x[1].x[1];

			lmol	= reinterpret_cast<Molecule *> (glWidg->mols.x[id_ml]);

			//showfull_infile(workFrame->Mls.x[id_ml]->Connect,"Cn1.txt");

			if (lmol->Connect.get(id_at1,id_at2)==0)
			{
				undo_redo->AddBnd_init(id_ml,id_at1,id_at2);
				undo_redo->AddBnd_op();
				undo_redo->inc_cur_pos();
			}else
			{
				int ib,io;
				ib	= lmol->Connect.get(id_at1,id_at2)-1;
				io	= lmol->Bonds.x[ib].oder;
				if (io<3)
				{
					io++;
					undo_redo->ChgBnd_init(id_ml,id_at1,id_at2,io);
					undo_redo->ChgBnd_op();
					undo_redo->inc_cur_pos();
				}else
				{
					io	= 1;
					undo_redo->ChgBnd_init(id_ml,id_at1,id_at2,io);
					undo_redo->ChgBnd_op();
					undo_redo->inc_cur_pos();
					undo_redo->DelBnd_init(id_ml,id_at1,id_at2);
					undo_redo->DelBnd_op();
					undo_redo->inc_cur_pos();
					/*if(!workFrame->Mls.x[id_ml]->ComTest(id_at1,id_at2))
					{// разъединить молекулу на две
					SepMol_init(id_ml);
					SepMol_op();
					undo_redo->inc_cur_pos();
					sl_ids.x[1].x[0]	= workFrame->Mls.N-1;
					sl_ids.x[1].x[1]	-= workFrame->Mls.x[id_ml]->Atoms.N;
					unselprod();
					}*/
				}
			}
		}
		undo_redo->Stop_init();
		treeModel->updateModel();
		glWidg->rendScene();//genScene();
		glWidg->update();
		setWindowModified(true);
	}
}

void MainWindow::doUniMols() // объединение двух молекул
{
	if(glWidg->sel_idm.N>1)//(glWidg->getMolSel())
	{
		int ii,jj,id_ml1,id_ml2;
		undo_redo->chesk_reset();
		id_ml1	= glWidg->sel_idm.x[0]; //номер первой выделнной молекулы
		//Molecule * lmol;
		for(ii=glWidg->sel_idm.N-1;ii>=1;ii--)
		{
			//jj	= glWidg->mols.N-1; // номер  выделенной последней молекулы
			jj	= workFrame->Mls.N-1; // номер  выделенной последней молекулы
			id_ml2	= glWidg->sel_idm.x[ii];	// номер текущей выбранной молекулы
			if(jj!=id_ml2)  // если молекула не последняя в массиве, то переместить её в конец массива
			{
				undo_redo->SwpMol_init(id_ml2,jj);
				undo_redo->SwpMol_op();
				undo_redo->inc_cur_pos();
				id_ml2	= jj;
			}
			undo_redo->UniMol_init(id_ml1,id_ml2);	// объединить две молекулы
			undo_redo->UniMol_op();
			undo_redo->inc_cur_pos();
			undo_redo->DelMol_init(id_ml2);
			undo_redo->DelMol_op();
			undo_redo->inc_cur_pos();
			//glWidg->setmols(workFrame->Mls);
			//doDelMol_(sel_ids_ml.x[ii]);
		}
	undo_redo->Stop_init();
	treeModel->updateModel();
	glWidg->s_id.N	= 0;
	glWidg->selAnalize();
	glWidg->sel_idm.N	= 0;
	glWidg->rendScene();//genScene();
	glWidg->update();
	setWindowModified(true);
	statgen();
	}
}

void MainWindow::doSepMol()	// разъединить молекулу
{
	if(glWidg->sel_idm.N==1)
	{
		int id_ml,ii,jj,kk,ll,ib,io;
		vecT<vecT<int> > id_ats;
		id_ml	= glWidg->sel_idm.x[0];
		Molecule *lmol;
		lmol	= reinterpret_cast<Molecule *> (glWidg->mols.x[id_ml]);
		lmol->SepMolInd(id_ats); // в id_ats поместить номер атомов соединённых связями
		if (id_ats.N>1)
		{

			vecT<Molecule* > mols;
			vecT<int> id_inv;	// инвесная нумерация атомов в новой молекуле
			mols.setlen(id_ats.N);
			id_inv.setlen(lmol->Atoms.N);

			for(ii=0;ii<id_ats.N;ii++)
			{
				id_inv	= -1;
				mols.x[ii]	= new Molecule;
				mols.x[ii]->ReInit(id_ats.x[ii].N);
				mols.x[ii]->Atoms.N	= id_ats.x[ii].N;
				for(jj=0;jj<id_ats.x[ii].N;jj++)// копирование данных об атомах
				{
					kk	= id_ats.x[ii].x[jj];
					mols.x[ii]->Atoms.x[jj]	= workFrame->Mls.x[id_ml]->Atoms.x[kk];
					mols.x[ii]->Atoms.x[jj].id_Tot	= jj;
					id_inv.x[kk]	= jj;
				}
				for(jj=0;jj<id_ats.x[ii].N;jj++)// перенос данных о связях
				{
					kk	= id_ats.x[ii].x[jj]; // jj - номер атома в новой молекуле, kk - номер атома в исходной молекуле
					for(ll=0;ll<lmol->Connect.I.x[kk].N;ll++) 
					{
						ib	= lmol->Connect.S.x[kk].x[ll]-1;	// номер связи в исходной молекуле
						io	=lmol->Bonds.x[ib].oder; // порядок связи
						ib	= id_inv.x[lmol->Connect.I.x[kk].x[ll]];
						mols.x[ii]->AddBond(io,jj,ib); // добавление связи в новой молекуле
					}
				}
			}

			jj	= glWidg->mols.N-1;
			if(jj!=id_ml)
			{
				undo_redo->SwpMol_init(id_ml,jj);
				undo_redo->SwpMol_op();
				undo_redo->inc_cur_pos();
				id_ml	= jj;
			}
			undo_redo->DelMol_init(id_ml);
			undo_redo->DelMol_op();
			undo_redo->inc_cur_pos();

			for(ii=0;ii<mols.N;ii++)
			{
				undo_redo->AddMol_init(mols.x[ii]);	// инициализация добавления новой молекулы 
				undo_redo->AddMol_op();	// добавить молекулу
				undo_redo->inc_cur_pos();
			}

			undo_redo->Stop_init();
			treeModel->updateModel();
			glWidg->s_id.N	= 0;
			glWidg->selAnalize();
			glWidg->sel_idm.N	= 0;
			glWidg->rendScene();//genScene();
			glWidg->update();
		}
		setWindowModified(true);
		statgen();
	}
}

void MainWindow::doMoveAtoms()
{
	undo_redo->chesk_reset();
	int ii,id_ml,id_at;
	vec3db dr;
	if (glWidg->sel_xyz.N!=glWidg->select_id.N) exit(0);
	for(ii=0;ii<glWidg->sel_xyz.N;ii++)
	{
		id_ml	= glWidg->select_id.x[ii].x[0];
		id_at	= glWidg->select_id.x[ii].x[1];
		dr		= glWidg->sel_xyz.x[ii];
		undo_redo->MovAtm_init(id_ml,id_at,dr);
		//undo_redo->MovAtm_op();
		undo_redo->inc_cur_pos();
	}
	undo_redo->Stop_init();
	setWindowModified(true);
}

/*void MainWindow::doAtomMov(int fi) // изменение геометрии
{
	int id_b;
	vecT<int> idm;
	id_b	= workFrame->Mls.x[0]->Connect.get(glWidg->s_id.x[1],glWidg->s_id.x[2]); // номер связи
	if(id_b!=-1)
	{
		workFrame->Mls.x[0]->SubMol(idm,glWidg->s_id.x[2],id_b);
	}
	if (idm.N>0)
	{
		// определеить локальный базис и перейти в него
		// произвести поворот до указанного угла - для атомов idm.
		// вызвать построение сцены
	}
}*/

void MainWindow::doMoveMol()
{
	undo_redo->chesk_reset();
	int id_ml;

	double sn;
	vec3db dr,p0(rotatWin->GetDis()),p(rotatWin->GetAxis());
	Quaternion<double> qa;

	id_ml	= glWidg->sel_idm.x[0];//id_ml_mv_op.x[ii];
	sn		= rotatWin->GetAlfa()/2.0;
	qa.x[0]	= cos(sn);
	sn		= sin(sn);
	qa.x[1]	= sn*p.x[0];
	qa.x[2]	= sn*p.x[1];
	qa.x[3]	= sn*p.x[2];

	dr	= rotatWin->GetAxis()*rotatWin->GetDsp();

	rotatWin->SetAlfa(0.0);
	rotatWin->SetDsp(0.0);

	undo_redo->MovMol_init(id_ml,dr,p0,qa);
	undo_redo->MovMol_op();
	undo_redo->inc_cur_pos();
	undo_redo->Stop_init();
	glWidg->rendScene();//genScene();
	glWidg->update();
	setWindowModified(true);
}

void MainWindow::doMoveFrg()
{
	undo_redo->chesk_reset();
	int id_ml,id_at;

	double sn;
	vec3db dr,p0,p(glWidg->getAxs());
	Quaternion<double> qa;

	id_ml	= glWidg->getIdMlBl();
	sn		= glWidg->getAlf()/2;
	qa.x[0]	= cos(sn);
	sn		= sin(sn);
	qa.x[1]	= sn*p.x[0];
	qa.x[2]	= sn*p.x[1];
	qa.x[3]	= sn*p.x[2];

	dr	= glWidg->getPnr();

	id_at	= glWidg->getIdAtBl();

	p0	= workFrame->Mls.x[id_ml]->Atoms.x[id_at].r;

	glWidg->setAlf(0.0);

	undo_redo->MovFrg_init(id_ml,glWidg->ids_bl,dr,p0,qa);
	undo_redo->MovFrg_op();
	glWidg->ids_bl.N= 0;
	undo_redo->inc_cur_pos();
	undo_redo->Stop_init();
	glWidg->rendScene();//genScene();
	glWidg->update();
	statgen();
	setWindowModified(true);
}

void MainWindow::ghangeprojection()
{
	if (glWidg->getproj())
	{
		OrthoPerspAction->setText(tr("Switch to Otrographic &Projection"));
		OrthoPerspAction->setIcon(QIcon(":/images/ortho.png"));
		OrthoPerspAction->setStatusTip(tr("Change projection from orthographic to pecrspctive and vice versa. (Current projection is perspective)"));
		glWidg->setproj(false);
		//glWidg->rendScene();//genScene();
		glWidg->reprojGL();
		glWidg->update();
	}else
	{
		OrthoPerspAction->setText(tr("Switch to Perspective &Projection"));
		OrthoPerspAction->setIcon(QIcon(":/images/persp.png"));
		OrthoPerspAction->setStatusTip(tr("Change projection from orthographic to pecrspctive and vice versa. (Current projection is orthographic)"));
		glWidg->setproj(true);
		//glWidg->rendScene();//genScene();
		glWidg->reprojGL();
		glWidg->update();
	}
}


void MainWindow::undoDo()
{
	undo_redo->Back_op();
	treeModel->updateModel();
	glWidg->rendScene();//genScene();
	glWidg->update();
	statgen();
}
void MainWindow::redoDo()
{
	undo_redo->Frwd_op();
	treeModel->updateModel();
	glWidg->rendScene();//genScene();
	glWidg->update();
	statgen();
}

void MainWindow::selMolDet()
{
	sel_ids_ml.N	= 0;
	if(sl_ids.N>0)
	{
		vecT<int> id_mls;
		int ii,jj,kk,mm;
		kk	= -2;
		//sel_ids_ml.N	= 0;
		for(ii=0;ii<sl_ids.N;ii++)
		{
			jj	= sl_ids.x[ii].x[0]; // номер молекулы
			if(jj!=kk)	// если номер не совпадает с номером на предыдущей операции
			{
				mm	= sel_ids_ml.fnd(jj); // найти номер в массиве ранее найденых номеров
				if(mm==-1)	// если это новый номер
				{
					sel_ids_ml.add(jj);	// добавить новый номер в массив
				}
				kk	= jj;	// сохранить номер молекулы 
			}
		}
		sel_ids_ml.sort();
		kk	= 0;
		for(ii=0;ii<sel_ids_ml.N;ii++)
		{
			kk+=workFrame->Mls.x[sel_ids_ml.x[ii]]->Atoms.N;
		}
		if(sl_ids.mN<kk) sl_ids.setmem(kk);
		sl_ids.N	= kk;
		kk	= 0;
		for(ii=0;ii<sel_ids_ml.N;ii++)
		{
			for(jj=workFrame->Mls.x[sel_ids_ml.x[ii]]->Atoms.N-1;jj>=0;jj--)
			{
				sl_ids.x[kk].x[0]	= sel_ids_ml.x[ii];
				sl_ids.x[kk].x[1]	= jj;
				kk++;
			}
		}
		unselprod();
		/*if(sel_ids_ml.N!=0)
		{
			//if(!surfaceBuildAction->isEnabled()) surfaceBuildAction->setEnabled(true);
			//isRotat	= false;
			//RW->setVisible(false);
		}*/
	}
	glWidg->rendScene();//genScene();
	glWidg->update();
}

void MainWindow::selprod()	// обработка данных о выделенных атомах - выделение номера атома и номера молекулы
{
	/*if(glWidg->s_id.N!=0)
	{
		vecT<int> r_id;	// массив с номерами начала новых молекул при сплошной нумерации всех атомов сцены
		vec2int loc;
		int id_c,jj;	
		id_c	= 0;
		r_id.setlen(workFrame->Mls.N);

		if (sl_ids.mN < workFrame->Mls.N) sl_ids.setmem(workFrame->Mls.N);
		for(jj=0;jj<r_id.N;jj++)
		{
			id_c	+= workFrame->Mls.x[jj]->Atoms.N;
			r_id.x[jj]	= id_c;
		}
		
		sl_ids.N	= 0;
		for(int ii=0;ii<glWidg->s_id.N;ii++)
		{
			id_c	= glWidg->s_id.x[ii];
			for(jj=0;(jj<r_id.N)&(id_c>=r_id.x[jj]);jj++);
			if(jj!=r_id.N)
			{
				loc.x[0]	= jj; // номер молекулы
				loc.x[1]	= jj>0 ? id_c-r_id.x[jj-1]: id_c ; // номер атома в тек. молекуле

				sl_ids.add(loc);
			}
		}
	}
	else
	{
		sl_ids.N	= 0;
	}
	glWidg->s_ids	= &sl_ids;
	for(int ii=0;ii<sl_ids.N;ii++)
	{
		workFrame->Mls.x[sl_ids.x[ii].x[0]]->ids.add(sl_ids.x[ii].x[1]);
	}
	//s_id.N	= 0;*/
}

void MainWindow::unselprod() // коррекция данных о выделенных атомах
{
	if(sl_ids.N!=0)
	{
		int ii,jj;
		vecT<int> r_id;	// массив с номерами начала новых молекул при сплошной нумерации всех атомов сцены

		r_id.setlen(workFrame->Mls.N);

		ii	= 0;
		for(jj=1;jj<r_id.N;jj++)
		{
			ii	+= workFrame->Mls.x[jj-1]->Atoms.N;
			r_id.x[jj]	= ii;
		}
		if(glWidg->s_id.mN<sl_ids.N) glWidg->s_id.setmem(sl_ids.N);
		glWidg->s_id.N	= sl_ids.N;
		for(ii=0;ii<sl_ids.N;ii++)
		{
			jj	= sl_ids.x[ii].x[0];
			glWidg->s_id.x[ii]	= r_id.x[jj]+sl_ids.x[ii].x[1];
		}
	}
}

void MainWindow::statgen()
{
	//selprod();
	if(glWidg->getMolSel())
	{
		selMolDet();
		if (glWidg->sel_idm.N>0)
		{		
			if(glWidg->sel_idm.N==1)
			{
				unionMols->setEnabled(false);
				separateMol->setEnabled(true);

				doTurnAction->setEnabled(true);
				surfaceBuildAction->setEnabled(true);
			}else
			{
				unionMols->setEnabled(true);
				separateMol->setEnabled(false);

				doTurnAction->setEnabled(false);
				surfaceBuildAction->setEnabled(false);
			}
		}else
		{
			unionMols->setEnabled(false);
			separateMol->setEnabled(false);
			doTurnAction->setEnabled(false);
			surfaceBuildAction->setEnabled(false);

			rotatWin->setVisible(false);
			glWidg->setrwr(false);
			glWidg->update();
		}
	}else
	{
		if(surfaceBuildAction->isEnabled())	surfaceBuildAction->setEnabled(false);
		if(unionMols->isEnabled())		unionMols->setEnabled(false);
		if(separateMol->isEnabled())	separateMol->setEnabled(false);
		if(doTurnAction->isEnabled())	doTurnAction->setEnabled(false);
		rotatWin->setVisible(false);
		glWidg->setrwr(false);
		glWidg->update();
		sel_ids_ml.N= 0;
	}

	if(glWidg->select_id.N!=0)
	{
		//doTurnAction->setEnabled(true);
		showSelBut->setEnabled(true);

		if((glWidg->select_id.N>1)&&(glWidg->select_id.N<5))
		{
			statBut->setEnabled(true);
		}else
		{
			statBut->setEnabled(false);
		}

		if(glWidg->select_id.N==2)
		{
			if(glWidg->select_id.x[0].x[0]==glWidg->select_id.x[1].x[0])
			{
				addBond->setEnabled(true);
				glWidg->setBL(true);
				glWidg->setidmlbl();//glWidg->select_id.x[1].x[0],glWidg->select_id.x[0].x[1],glWidg->select_id.x[1].x[1]);
			}else
			{
				addBond->setEnabled(false);
				glWidg->setBL(false);
				glWidg->setidmlbl(-1,-1,-1);
			}
		}else
		{
			if(addBond->isEnabled()) addBond->setEnabled(false);
			glWidg->setBL(false);
			glWidg->setidmlbl(-1,-1,-1);

			if(glWidg->select_id.N==3)
			{
				if((glWidg->select_id.x[0].x[0]==glWidg->select_id.x[1].x[0])&&(glWidg->select_id.x[1].x[0]==glWidg->select_id.x[2].x[0]))
				{
					glWidg->setVA(true);
					glWidg->setidmlva();//sl_ids.x[1].x[0],sl_ids.x[0].x[1],sl_ids.x[1].x[1],sl_ids.x[2].x[1]);
				}else
				{
					glWidg->setVA(false);
					glWidg->setidmlva(-1,-1,-1,-1);
				}
			}else
			{
				glWidg->setVA(false);
				glWidg->setidmlva(-1,-1,-1,-1);

				if(glWidg->select_id.N==4)
				{
					if((glWidg->select_id.x[0].x[0]==glWidg->select_id.x[1].x[0])&&(glWidg->select_id.x[1].x[0]==glWidg->select_id.x[2].x[0])&&(glWidg->select_id.x[2].x[0]==glWidg->select_id.x[3].x[0]))
					{
						glWidg->setTA(true);
						glWidg->setidmlta();//sl_ids.x[1].x[0],sl_ids.x[0].x[1],sl_ids.x[1].x[1],sl_ids.x[2].x[1],sl_ids.x[3].x[1]);
					}else
					{
						glWidg->setTA(false);
						glWidg->setidmlta(-1,-1,-1,-1,-1);
					}
				}else
				{
					glWidg->setTA(false);
					glWidg->setidmlta(-1,-1,-1,-1,-1);
				}
			}
		}
		if(!undoAction->isEnabled()) undoAction->setEnabled(true);

		QString Atp;
		QString nstr;
		vec2T<char> Ch;
		vec3db xyz;
		int it,ia,imol;

	//	editbutton->setEnabled(true);

		switch (glWidg->select_id.N)
		{
			case 1:
			{
				ia	= glWidg->select_id.x[0].x[1];
				imol= glWidg->select_id.x[0].x[0];
				it	= glWidg->mols.x[imol]->Atoms.x[ia].id_Tpz;
				xyz	= glWidg->mols.x[imol]->Atoms.x[ia].r;
				Ch	= workFrame->TableZR.Lines.x[it].Ch;
				Atp.append(tr("One atom selected : ("));
				Atp.append(Ch.x[0]);
				if (Ch.x[1]!=0) Atp.append(Ch.x[1]);
				//nstr.append(" %l ");
				//nstr.arg(xyz.x[0],0,'g',3);
				nstr	= QString("%1").arg((ia+1));
				Atp.append(nstr);
				Atp.append(tr(") ; X Y Z : "));
				nstr	= QString(" %1").arg(xyz.x[0],0,'g',5);
				Atp.append(nstr);
				nstr	= QString("  %1").arg(xyz.x[1],0,'g',5);
				Atp.append(nstr);
				nstr	= QString("  %1.").arg(xyz.x[2],0,'g',5);
				Atp.append(nstr);
				if( (static_cast <Molecule *> (glWidg->mols.x[imol]) )->mol_type == PROTEINE)
				{
					atom_node * ptr	= glWidg->mols.x[imol]->Atoms.x[ia].dat.dat->amin;
					nstr	= QString(tr(" Aminoacid: "));//.arg(xyz.x[2],0,'g',5);
					Atp.append(nstr);
					nstr	= QString(ptr->getparent()->name.x);
					Atp.append(nstr);
					nstr	= QString(" %1,").arg(ptr->getparent()->id_ch);
					Atp.append(nstr);
					nstr	= QString(tr(" Chain: "));//.arg(xyz.x[2],0,'g',5);
					Atp.append(nstr);
					nstr    = QString(QChar(ptr->getparent()->getparent()->ch));
					Atp.append(nstr);
					nstr	= QString(" %1.").arg(ptr->getparent()->getparent()->id+1);//.arg(xyz.x[2],0,'g',5);
					Atp.append(nstr);
				}
				statWid->setText(Atp);
//				editbutton->setText(tr("Edit Coordinates"));
				break;
			}
			case 2:
			{
				vec2T<char> Ch2;
				vec3db xyz2;
				int it2,ia2,imol2;
				double dst;


				ia	= glWidg->select_id.x[0].x[1];
				imol= glWidg->select_id.x[0].x[0];
				it	= glWidg->mols.x[imol]->Atoms.x[ia].id_Tpz;
				xyz	= glWidg->mols.x[imol]->Atoms.x[ia].r;
				Ch	= workFrame->TableZR.Lines.x[it].Ch;


				ia2	= glWidg->select_id.x[1].x[1];
				imol2= glWidg->select_id.x[1].x[0];
				it2	= glWidg->mols.x[imol2]->Atoms.x[ia2].id_Tpz;
				xyz2= glWidg->mols.x[imol2]->Atoms.x[ia2].r;
				Ch2	= workFrame->TableZR.Lines.x[it2].Ch;

				xyz2-= xyz;
				dst	= sqrt(xyz2.scpr(xyz2));

				Atp.append(tr("Two atoms selected : ("));

				Atp.append(Ch.x[0]);
				if (Ch.x[1]!=0) Atp.append(Ch.x[1]);
				nstr	= QString("%1").arg((ia+1));
				Atp.append(nstr);

				Atp.append(tr("-"));
				Atp.append(Ch2.x[0]);
				if (Ch2.x[1]!=0) Atp.append(Ch2.x[1]);
				nstr	= QString("%1").arg((ia2+1));
				Atp.append(nstr);
				Atp.append(tr(") ; distance : "));
				nstr	= QString(" %1 .").arg(dst,0,'g',5);
				Atp.append(nstr);
				statWid->setText(Atp);
	//			editbutton->setText(tr("Edit Distance"));

				break;
			}
			case 3:
			{
				vec2T<char> Ch2;
				vec3db xyz2;
				int it2,ia2,imol2;
				double dst2;

				vec2T<char> Ch3;
				vec3db xyz3;
				int it3,ia3,imol3;
				double dst3,fi;

				ia	= glWidg->select_id.x[0].x[1];
				imol= glWidg->select_id.x[0].x[0];
				it	= glWidg->mols.x[imol]->Atoms.x[ia].id_Tpz;
				xyz	= glWidg->mols.x[imol]->Atoms.x[ia].r;
				Ch	= workFrame->TableZR.Lines.x[it].Ch;


				ia2	= glWidg->select_id.x[1].x[1];
				imol2= glWidg->select_id.x[1].x[0];
				it2	= glWidg->mols.x[imol2]->Atoms.x[ia2].id_Tpz;
				xyz2= glWidg->mols.x[imol2]->Atoms.x[ia2].r;
				Ch2	= workFrame->TableZR.Lines.x[it2].Ch;

				ia3	= glWidg->select_id.x[2].x[1];
				imol3= glWidg->select_id.x[2].x[0];
				it3	= glWidg->mols.x[imol3]->Atoms.x[ia3].id_Tpz;
				xyz3= glWidg->mols.x[imol3]->Atoms.x[ia3].r;
				Ch3	= workFrame->TableZR.Lines.x[it3].Ch;

				xyz3 -= xyz2;
				dst3 =  sqrt(xyz3.scpr(xyz3));
				xyz2 -= xyz;
				dst2 =  sqrt(xyz2.scpr(xyz2));

				fi	= 180*acos(-xyz3.scpr(xyz2)/(dst2*dst3))/3.1415926535897932384626433832795;


				Atp.append(tr("Three atoms selected : ("));

				Atp.append(Ch.x[0]);
				if (Ch.x[1]!=0) Atp.append(Ch.x[1]);
				nstr	= QString("%1").arg((ia+1));
				Atp.append(nstr);

				Atp.append(tr("-"));
				Atp.append(Ch2.x[0]);
				if (Ch2.x[1]!=0) Atp.append(Ch2.x[1]);
				nstr	= QString("%1").arg((ia2+1));
				Atp.append(nstr);
				Atp.append(tr("-"));
				Atp.append(Ch3.x[0]);
				if (Ch3.x[1]!=0) Atp.append(Ch3.x[1]);
				nstr	= QString("%1").arg((ia3+1));
				Atp.append(nstr);

				Atp.append(tr(") ; valence angle : "));
				nstr	= QString(" %1 .").arg(fi,0,'g',5);
				Atp.append(nstr);
				statWid->setText(Atp);
//				editbutton->setText(tr("Edit Angle"));

				break;
			}
			case 4:
			{
				vec2T<char> Ch2;
				vec3db xyz2;
				int it2,ia2,imol2;
				
				vec2T<char> Ch3;
				vec3db xyz3;
				int it3,ia3,imol3;		

				vec2T<char> Ch4;
				vec3db xyz4;
				int it4,ia4,imol4;
				double dst1,dst2,fi;

				vec3db n1,n2;


				ia	= glWidg->select_id.x[0].x[1];
				imol= glWidg->select_id.x[0].x[0];
				it	= glWidg->mols.x[imol]->Atoms.x[ia].id_Tpz;
				xyz	= glWidg->mols.x[imol]->Atoms.x[ia].r;
				Ch	= workFrame->TableZR.Lines.x[it].Ch;


				ia2	= glWidg->select_id.x[1].x[1];
				imol2= glWidg->select_id.x[1].x[0];
				it2	= glWidg->mols.x[imol2]->Atoms.x[ia2].id_Tpz;
				xyz2= glWidg->mols.x[imol2]->Atoms.x[ia2].r;
				Ch2	= workFrame->TableZR.Lines.x[it2].Ch;

				ia3	= glWidg->select_id.x[2].x[1];
				imol3= glWidg->select_id.x[2].x[0];
				it3	= glWidg->mols.x[imol3]->Atoms.x[ia3].id_Tpz;
				xyz3= glWidg->mols.x[imol3]->Atoms.x[ia3].r;
				Ch3	= workFrame->TableZR.Lines.x[it3].Ch;

				ia4	= glWidg->select_id.x[3].x[1];
				imol4= glWidg->select_id.x[3].x[0];
				it4	= glWidg->mols.x[imol4]->Atoms.x[ia4].id_Tpz;
				xyz4= glWidg->mols.x[imol4]->Atoms.x[ia4].r;
				Ch4	= workFrame->TableZR.Lines.x[it4].Ch;

				xyz4 -= xyz3;
				xyz3 -= xyz2;
				xyz2 -= xyz;

				n1.crss(xyz4,xyz3);
				n2.crss(xyz3,xyz2);

				dst1 =  sqrt(n1.scpr(n1));
				dst2 =  sqrt(n2.scpr(n2));

				fi	= 180*acos(n1.scpr(n2)/(dst1*dst2))/3.1415926535897932384626433832795;
	
				Atp.append(tr("Four atoms selected : ("));

				Atp.append(Ch.x[0]);
				if (Ch.x[1]!=0) Atp.append(Ch.x[1]);
				nstr	= QString("%1").arg((ia+1));
				Atp.append(nstr);

				Atp.append(tr("-"));
				Atp.append(Ch2.x[0]);
				if (Ch2.x[1]!=0) Atp.append(Ch2.x[1]);
				nstr	= QString("%1").arg((ia2+1));
				Atp.append(nstr);
				Atp.append(tr("-"));
				Atp.append(Ch3.x[0]);
				if (Ch3.x[1]!=0) Atp.append(Ch3.x[1]);
				nstr	= QString("%1").arg((ia3+1));
				Atp.append(nstr);
				Atp.append(tr("-"));
				Atp.append(Ch4.x[0]);
				if (Ch4.x[1]!=0) Atp.append(Ch4.x[1]);
				nstr	= QString("%1").arg((ia4+1));
				Atp.append(nstr);

				Atp.append(tr(") ; torsion angle : "));
				nstr	= QString(" %1 .").arg(fi,0,'g',5);
				Atp.append(nstr);
				statWid->setText(Atp);
//				editbutton->setText(tr("Edit Angle"));


				break;
			}
			default:
			{
//				editbutton->setEnabled(false);
				Atp.append("Selected more than a four atoms");
				statWid->setText(Atp);
				break;
			}
		}
	}
	else
	{
		statBut->setEnabled(false);
		showSelBut->setEnabled(false);
		addBond->setEnabled(false);
		statWid->clear();
	}
}

void MainWindow::buildSurf()// построение поверхности
{
	int ii;
	vecT<int> id_srf;
	for (ii=0;ii<glWidg->sel_idm.N;ii++)
	{
		id_srf.add(workFrame->Srfcs.N);
		workFrame->InitMolSurf(glWidg->mols.x[glWidg->sel_idm.x[ii]]);

		workFrame->Srfcs.x[ii]->SetGL(glWidg);
	}

	//connect(workFrame->Srfcs.x[0],SIGNAL(RdrCrSrf()),this,SLOT(genCrSurf()));
	for(ii=0;ii<id_srf.N;ii++)
	{
		workFrame->Srfcs.x[id_srf.x[ii]]->BuildSurface();
		//glWidg->genSurfScene(surface);
		//glWidg->rendSurface(workFrame->Srfcs.x[id_srf.x[ii]],0
	}

	glWidg->SurfModifyOn();
	glWidg->rendScene();
	glWidg->update();
	glWidg->SurfModifyOff();
	treeModel->updateModel();
	//surface->SetWorkframe(workFrame);
	/*workFrame.surface->BuildSurface(glWidg->sel_idm.x[0]);
	glWidg->genSurfScene(surface);
	glWidg->update();
	id_ml_srf	= glWidg->sel_idm.x[0];*/

/*	Molecule * mol;


	mol	= workFrame->Mls.x[0];

	mol->ids.setlen(2);
	mol->ids.x[0]=0;
	mol->ids.x[0]=1;*/

	//glWidg->rendAtoms(mol);
	//glWidg->rendBonds(mol);
	//glWidg->rendWire(mol);
	
//	workFrame->Mls.x[sel_ids_ml.x[0]]->InitSurface(workFrame->TableZR);
//	workFrame->Mls.x[sel_ids_ml.x[0]]->surf->BuildSurface();


}
/*void MainWindow::setCurrentFileName(const QString &fileName)
{
	curFile	= fileName;
/*	setWindowModified(false);

	QString showName	= "Untitled";
	if(!curFile.isEmpty())
	{
		showName	= strippedName(curFile);
		recentFiles.removeAll(curFile);
		recentFiles.prepend(curFile);
		updateRecentFileActions();
	}
	setWindowTitle(tr("%1[+] - %2").arg(showName).arg(tr("Spreadsheet")));*/
//}


void MainWindow::selsort()
{
	if(sl_ids.N>0)
	{
		vecT<vecT<int> > xx;
		xx.setmem(sl_ids.N);
		vecT<int> id_mls;
		int ii,jj,kk,mm;
		kk	= -2;
		xx.setlen(workFrame->Mls.N);
		for(ii=0;ii<sl_ids.N;ii++)
		{
			jj	= sl_ids.x[ii].x[0]; // номер молекулы
			xx.x[jj].add(sl_ids.x[ii].x[1]);
			if(jj!=kk)	// если номер не совпадает с номером на предыдущей операции
			{
				mm	= id_mls.fnd(jj); // найти номер в массиве ранее найденых номеров
				if(mm==-1)	// если это новый номер
				{
					id_mls.add(jj);	// добавить новый номер в массив
				}
				kk	= jj;	// сохранить номер молекулы 
			}
		}
		id_mls.sort();
		for(ii=0;ii<id_mls.N;ii++)
		{
			jj	= id_mls.x[ii];
			xx.x[jj].sort();
		}
		mm	= 0;
		for(ii=id_mls.N-1;ii>=0;ii--)
		{
			jj	= id_mls.x[ii];
			for(kk=xx.x[jj].N-1;kk>=0;kk--)
			{
				sl_ids.x[mm].x[0]	= jj;
				sl_ids.x[mm].x[1]	= xx.x[jj].x[kk];
				mm++;
			}
		}
	}
}

/*bool MainWindow::save()
{
	if(curFile.isEmpty())
	{
		return saveAs();
	}else
	{
		return saveFile(curFile);
	}
}

bool MainWindow::saveFile(const QString &fileName)
{
	if(!spreadsheet->writeFile(fileName))
	{
		statusBar()->showMessage(tr("Saving canceled."),2000);
		return false;
	}
	setCurrentFileName(fileName);
	statusBar()->showMessage(tr("File Saved."),2000);
	return true;
}/**/




/*vecT<int> in1,in2,in3,in4;

		for(jj=0;jj<id_at_tp_op.N;jj++)
		{
			if(id_at_tp_op.x[jj].x[0]==id_ml)
			{
				if(id_at_tp_op.x[jj].x[1]==id_at) {in1.add(jj);}
				if(id_at_tp_op.x[jj].x[1]==kk) {in2.add(jj);}
			}
		}
		for(jj=0;jj<in1.N;jj++)	id_at_tp_op.x[in1.x[jj]].x[1]	= kk;
		for(jj=0;jj<in2.N;jj++)	id_at_tp_op.x[in2.x[jj]].x[1]	= id_at;
		in1.N	= in2.N	= 0;

		for(jj=0;jj<id_at_dl_op.N;jj++)
		{
			if(id_at_dl_op.x[jj].x[0]==id_ml)
			{
				if(id_at_dl_op.x[jj].x[1]==id_at) {in1.add(jj);}
				if(id_at_dl_op.x[jj].x[1]==kk) {in2.add(jj);}
			}
		}
		for(jj=0;jj<in1.N;jj++)	id_at_dl_op.x[in1.x[jj]].x[1]	= kk;
		for(jj=0;jj<in2.N;jj++)	id_at_dl_op.x[in2.x[jj]].x[1]	= id_at;
		in1.N	= in2.N	= in3.N = in4.N	= 0;

		for(jj=0;jj<id_bn_br_op.N;jj++)
		{
			if(id_bn_br_op.x[jj].x[0]==id_ml)
			{
				if(id_bn_br_op.x[jj].x[1]==id_at) {in1.add(jj);}
				if(id_bn_br_op.x[jj].x[2]==id_at) {in2.add(jj);}
				if(id_bn_br_op.x[jj].x[1]==kk) {in3.add(jj);}
				if(id_bn_br_op.x[jj].x[2]==kk) {in4.add(jj);}
			}
		}
		for(jj=0;jj<in1.N;jj++)	id_bn_br_op.x[in1.x[jj]].x[1]	= kk;
		for(jj=0;jj<in2.N;jj++)	id_bn_br_op.x[in2.x[jj]].x[2]	= kk;
		for(jj=0;jj<in3.N;jj++)	id_bn_br_op.x[in3.x[jj]].x[1]	= id_at;
		for(jj=0;jj<in4.N;jj++)	id_bn_br_op.x[in4.x[jj]].x[2]	= id_at;
		in1.N	= in2.N	= in3.N = in4.N	= 0;

		for(jj=0;jj<id_at_mv_op.N;jj++)
		{
			if(id_at_mv_op.x[jj].x[0]==id_ml)
			{
				if(id_at_mv_op.x[jj].x[1]==id_at) {in1.add(jj);}
				if(id_at_mv_op.x[jj].x[1]==kk) {in2.add(jj);}
			}
		}
		for(jj=0;jj<in1.N;jj++)	id_at_mv_op.x[in1.x[jj]].x[1]	= kk;
		for(jj=0;jj<in2.N;jj++)	id_at_mv_op.x[in2.x[jj]].x[1]	= id_at;
		in1.N	= in2.N	= 0;*/







/**/
#endif