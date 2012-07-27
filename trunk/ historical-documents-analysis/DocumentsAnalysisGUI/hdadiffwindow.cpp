#include "hdadiffwindow.h"

HdaDiffWindow::HdaDiffWindow(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	_chooseState= CHOOSE_NONE;
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

	 ui.label1->installEventFilter(this);
	 ui.label2->installEventFilter(this);	
	 _chooseState= CHOOSE_NONE;
    _StartPos1 = QPoint(-1,-1);
	_StartPos2 = QPoint(-1,-1);
	_EndPos1   = QPoint(-1,-1);
	_EndPos2   = QPoint(-1,-1);
	_orig_pic1= QPixmap(_pic1);
	_orig_pic2= QPixmap(_pic2);
}

HdaDiffWindow::~HdaDiffWindow()
{
	_chooseState= CHOOSE_END;
}



void HdaDiffWindow::startPressed()
{
	_chooseState= CHOOSE_START;
}
void HdaDiffWindow::endPressed()
{		
	_chooseState= CHOOSE_END;
}
void HdaDiffWindow::comparePressed()
{
	_chooseState= CHOOSE_NONE;
}

 bool HdaDiffWindow::eventFilter(QObject *obj, QEvent *event)
 {
     if (obj == ui.label1) {
		 if (event->type() == QEvent::MouseButtonPress)
		 {
    		QMouseEvent * mouse_event = (QMouseEvent *)event;
			QPoint pos = mouse_event->pos();
			if (_chooseState== CHOOSE_START)
			{
				if (pos == _StartPos1)				
					_StartPos1 = QPoint(-1,-1);
				else
					_StartPos1 = pos;
			}
			else if (_chooseState== CHOOSE_END)
			{
				if (pos == _EndPos1)				
					_EndPos1 = QPoint(-1,-1);
				else
					_EndPos1 = pos;
			}
			_pic1=QPixmap(_orig_pic1);
			QPainter painter(&_pic1);
			if (_StartPos1!= QPoint(-1,-1))
			{
				painter.setBrush(QBrush(Qt::green));
				painter.drawRect(_StartPos1.x()-5, _StartPos1.y()-5, 10, 10);					
			}
			if (_EndPos1!= QPoint(-1,-1))
			{
				painter.setBrush(QBrush(Qt::red));
				painter.drawRect(_EndPos1.x()-5, _EndPos1.y()-5, 10, 10);					
			}			
			ui.label1->setPixmap(_pic1);
            return true;         
		 }
		 else 
             return false;
     } else if(obj == ui.label2){
		 if (event->type() == QEvent::MouseButtonPress)
		 {
			 QMouseEvent * mouse_event = (QMouseEvent *)event;
			QPoint pos = mouse_event->pos();
			if (_chooseState== CHOOSE_START)
			{
				if (pos == _StartPos2)				
					_StartPos2 = QPoint(-1,-1);
				else				
					_StartPos2 = pos;					
				
			}
			else if (_chooseState== CHOOSE_END)
			{
				if (pos == _EndPos2)				
					_EndPos2 = QPoint(-1,-1);
				else				
					_EndPos2 = pos;				
			}
			_pic2=QPixmap(_orig_pic2);
			QPainter painter(&_pic2);
			if (_StartPos2!= QPoint(-1,-1))
			{
				painter.setBrush(QBrush(Qt::green));
				painter.drawRect(_StartPos2.x()-5, _StartPos2.y()-5, 10, 10);					
			}
			if (_EndPos2!= QPoint(-1,-1))
			{
				painter.setBrush(QBrush(Qt::red));
				painter.drawRect(_EndPos2.x()-5, _EndPos2.y()-5, 10, 10);					
			}			
			ui.label2->setPixmap(_pic2);
             return true;         
		 }
		 else 
             return false;
	 }	else {
         // pass the event on to the parent class
         return QDialog::eventFilter(obj, event);
     }
 }