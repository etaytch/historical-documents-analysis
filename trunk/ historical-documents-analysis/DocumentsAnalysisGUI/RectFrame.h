#pragma once
#include "framedraw.h"
#include <QGraphicsSceneDragDropEvent>
#include <QPainter>
#include <QRectF>
#include <QPolygonF>
#include <algorithm>

class RectFrame: public FrameDraw
{
	Q_OBJECT

public:
	RectFrame(mdiPageScene* scene, QPointF point, qreal width, qreal height);
	virtual QRectF boundingRect() const; 
    virtual void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); 
	virtual void mouseMoveEvent ( QGraphicsSceneMouseEvent * event );
    virtual void mouseMoveEvent(QGraphicsSceneDragDropEvent *event);
    virtual void mousePressEvent (QGraphicsSceneMouseEvent * event );
    virtual void mousePressEvent(QGraphicsSceneDragDropEvent *event);
    virtual void mouseReleaseEvent (QGraphicsSceneMouseEvent * event );
	virtual void hoverEnterEvent ( QGraphicsSceneHoverEvent * event ); 
    virtual void hoverLeaveEvent ( QGraphicsSceneHoverEvent * event ); 
	bool closeTo(QPointF p1, QPointF p2);
	void movePosition(int x, int y);
	QPointF getPos();
	void setWidth(int width);
	qreal getWidth();	
	void setHeight(int height);
	qreal getHeight();
	~RectFrame(void);

private:
	static int MAXHEIGHT;
	static int MAXWIDTH;
    QPointF _location;
    qreal   _width;
    qreal   _height;
	bool _hovered;
	//move, resize top right, resize top left, resize bottom right, resize bottom left
	enum mouseAction { MOVE, RESIZETR, RESIZETL, RESIZEBR, RESIZEBL};
	mouseAction action; 

};

