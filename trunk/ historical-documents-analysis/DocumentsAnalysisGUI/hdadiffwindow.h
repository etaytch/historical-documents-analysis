#ifndef HDADIFFWINDOW_H
#define HDADIFFWINDOW_H

#include <QWidget>
#include <QSize>
#include <QMouseEvent>
#include <QPainter>
#include "ui_hdadiffwindow.h"
#include "PageDoc.h"

enum ChooseState {CHOOSE_NONE, CHOOSE_START,CHOOSE_END};

class HdaDiffWindow : public QDialog
{
	Q_OBJECT

public:
	HdaDiffWindow(QWidget *parent = 0);
	HdaDiffWindow(PageDoc page1, PageDoc page2, QWidget *parent = 0);
	
	~HdaDiffWindow();
public slots:
    void startPressed();
	void endPressed();
	void comparePressed();
	void zoomIn1();
	void zoomIn2();
	void zoomOut1();
	void zoomOut2();
private:
	Ui::HdaDiffWindow ui;
	PageDoc _page1;
	PageDoc _page2;
	QPixmap _pic1;
	QPixmap _pic2;
	QPixmap _orig_pic1;
	QPixmap _orig_pic2;
	ChooseState _chooseState;
	QPoint _StartPos1;
	QPoint _StartPos2;
	QPoint _EndPos1;
	QPoint _EndPos2;

	bool samePoint(QPoint p1,QPoint p2);
	void scaleImage(QPixmap* pixMap,QLabel* lable,double ratio);
protected:
	 bool eventFilter(QObject *obj, QEvent *ev);

};

#endif // HDADIFFWINDOW_H
