#ifndef HELPBROWSER_H
#define HELPBROWSER_H


#include <QWidget>
class QTextBrowser;
class QPushButton;
class QString;



class HelpBrowser : public QWidget
{
	Q_OBJECT

public:
	HelpBrowser(const QString &path,const QString &page, QWidget *parent =0);
	static void showPage(const QString &path, const QString &page);

private slots:
	void updateWindowTitle();

private:
	QTextBrowser *textBrowser;
	QPushButton *homeButton;
	QPushButton *backButton;
	QPushButton *closeButton;
};

#endif