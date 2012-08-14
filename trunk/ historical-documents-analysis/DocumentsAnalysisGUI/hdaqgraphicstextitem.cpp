#include "hdaqgraphicstextitem.h"
#include <QKeyEvent>

HDAQGraphicsTextItem::HDAQGraphicsTextItem(RectFrame* rect, QString txt)
	: QGraphicsTextItem(txt)
{
	_rect = rect;
}

RectFrame* HDAQGraphicsTextItem::getRect()
{
	return _rect;
}


void HDAQGraphicsTextItem::keyPressEvent ( QKeyEvent * event ) {
	Qt::Key key = (Qt::Key)event->key();
	
	if(key==Qt::Key::Key_Return)
	{
		QString qstr = toPlainText();
		int iii=0;
	}
	else QGraphicsTextItem::keyReleaseEvent(event);
}

HDAQGraphicsTextItem::~HDAQGraphicsTextItem()
{

}
