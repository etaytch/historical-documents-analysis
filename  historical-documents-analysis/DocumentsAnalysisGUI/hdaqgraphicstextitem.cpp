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

HDAQGraphicsTextItem::~HDAQGraphicsTextItem()
{

}
