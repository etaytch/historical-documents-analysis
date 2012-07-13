#include "hdadiffwindow.h"

HdaDiffWindow::HdaDiffWindow(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

HdaDiffWindow::HdaDiffWindow(PageDoc page1, PageDoc page2, QWidget *parent)
	:QDialog(parent)
{
	ui.setupUi(this);
	Mat d1,d2;
	_page1 = page1;
	_page2 = page2;
	QString page1Path = _page1.getPage()->getName().c_str();
	QString page2Path = _page2.getPage()->getName().c_str();
	_page1.getPage()->loadMat();
	_page2.getPage()->loadMat();

	 cvtColor(_page1.getPage()->getMat(),d1,CV_BGR2RGB);
     QImage image1((uchar*)d1.data, d1.cols, d1.rows,QImage::Format_RGB888);
	 _pic1 = QPixmap::fromImage(image1);  
	 ui.label1->setPixmap(_pic1);

	cvtColor(_page2.getPage()->getMat(),d2,CV_BGR2RGB);
     QImage image2((uchar*)d2.data, d2.cols, d2.rows,QImage::Format_RGB888);
	 _pic2 = QPixmap::fromImage(image2);
	 ui.label2->setPixmap(_pic2);
}

HdaDiffWindow::~HdaDiffWindow()
{

}

