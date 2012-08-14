#ifndef HDAQGRAPHICSTEXTITEM_H
#define HDAQGRAPHICSTEXTITEM_H

#include <QGraphicsTextItem>
#include "RectFrame.h"

class HDAQGraphicsTextItem : public QGraphicsTextItem
{
	Q_OBJECT

public:
	HDAQGraphicsTextItem(RectFrame* rect,QString txt);
	RectFrame* getRect();	
	~HDAQGraphicsTextItem();

protected:
	void keyPressEvent ( QKeyEvent * event );

private:
	RectFrame* _rect;
};

#endif // HDAQGRAPHICSTEXTITEM_H
