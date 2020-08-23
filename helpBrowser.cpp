#ifndef HELPBROWSER_CPP
#define HELPBROWSER_CPP

#include <QtGui>
#include <QWidget>
#include <QTextBrowser>
#include <QPushButton>
#include <QString>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "helpBrowser.h"

HelpBrowser::HelpBrowser(const QString &path,const QString &page, QWidget *parent) : QWidget(parent)
{

	setAttribute(Qt::WA_DeleteOnClose);
	setAttribute(Qt::WA_GroupLeader);

	textBrowser	= new QTextBrowser;

	homeButton	= new QPushButton(tr("&Home"));
	backButton	= new QPushButton(tr("&Back"));
	closeButton	= new QPushButton(tr("&Close"));
	closeButton->setShortcut(tr("Ecs"));

	QHBoxLayout *buttonLayout = new QHBoxLayout;
	buttonLayout->addWidget(homeButton);
	buttonLayout->addWidget(backButton);
	buttonLayout->addStretch();
	buttonLayout->addWidget(closeButton);


	QVBoxLayout *mainLayout	= new QVBoxLayout;
	mainLayout->addLayout(buttonLayout);
	mainLayout->addWidget(textBrowser);
	setLayout(mainLayout);

	connect(homeButton,SIGNAL(clicked()),textBrowser,SLOT(home()));
	connect(backButton,SIGNAL(clicked()),textBrowser,SLOT(backward()));
	connect(closeButton,SIGNAL(clicked()),this,SLOT(close()));
	connect(textBrowser,SIGNAL(sourceChanghed(const QUrl &)),this,SLOT(updateWindowTitle()));

	textBrowser->setSearchPaths(QStringList()<<path);//<<":/images"<<":/doc/index.files");
	textBrowser->setSource(page);

	setWindowIcon(QIcon(":/images/mr3.png"));
}

void HelpBrowser::updateWindowTitle()
{
	setWindowTitle(tr("Help: %1").arg(textBrowser->documentTitle()));
}

void HelpBrowser::showPage(const QString &path, const QString &page)
{
	HelpBrowser *browser = new HelpBrowser(path,page);
	browser->resize(500,400);
	browser->show();
}

#endif