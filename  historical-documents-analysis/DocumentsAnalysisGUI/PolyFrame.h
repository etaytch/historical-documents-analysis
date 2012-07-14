#pragma once

#include "framedraw.h"
#include <QGraphicsSceneDragDropEvent>
#include <QPainter>
#include <QRectF>
#include <QPolygonF>
#include <algorithm>

class PolyFrame : public FrameDraw
{
	Q_OBJECT

private:
	QVector<QPointF> _points;
	QPolygonF* _poly;

public:
	PolyFrame(mdiPageScene* scene);
	PolyFrame(mdiPageScene* scene, QVector<QPointF> points);
	virtual QRectF boundingRect() const; 
    virtual void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); 
	virtual void mouseMoveEvent ( QGraphicsSceneMouseEvent * event );
    virtual void mouseMoveEvent(QGraphicsSceneDragDropEvent *event);
    virtual void mousePressEvent (QGraphicsSceneMouseEvent * event );
    virtual void mousePressEvent(QGraphicsSceneDragDropEvent *event);
    virtual void mouseReleaseEvent (QGraphicsSceneMouseEvent * event );
	virtual void hoverEnterEvent ( QGraphicsSceneHoverEvent * event ); 
    virtual void hoverLeaveEvent ( QGraphicsSceneHoverEvent * event ); 
	virtual int getType();
	QVector<QPointF> getPoints();
	int getClosestPoint(QPointF mouseOnPoint);
	int distance(QPointF p1, QPointF p2);
	int movingIndex;
	~PolyFrame(void);
};

