#ifndef HDADIFFWINDOW_H
#define HDADIFFWINDOW_H

#include <QWidget>
#include "ui_hdadiffwindow.h"
#include "PageDoc.h"

class HdaDiffWindow : public QDialog
{
	Q_OBJECT

public:
	HdaDiffWindow(QWidget *parent = 0);
	HdaDiffWindow(PageDoc page1, PageDoc page2, QWidget *parent = 0);
	~HdaDiffWindow();

private:
	Ui::HdaDiffWindow ui;
	PageDoc _page1;
	PageDoc _page2;
	QPixmap _pic1;
	QPixmap _pic2;

};

#endif // HDADIFFWINDOW_H
