#pragma once

#include "framedraw.h"
#include <QGraphicsSceneDragDropEvent>
#include <QPainter>
#include <QRectF>
#include <QPolygonF>
#include <algorithm>

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Polygon Frame. </summary>
///
/// <remarks>	Yair Offir, 1/8/2012. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

class PolyFrame : public FrameDraw
{
	Q_OBJECT

private:
	QVector<QPointF> _points;
	QPolygonF* _poly;
	bool _hovered;
	static int MAXDISTANCE;

public:
	PolyFrame(mdiPageScene* scene);
	PolyFrame(mdiPageScene* scene, QVector<QPointF> points);
	virtual QRectF boundingRect() const; 
    virtual void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); 
	virtual void mouseMoveEvent ( QGraphicsSceneMouseEvent * event );
	//if polygon is out of the scene, move it back to the scene.
	QPointF adjustToScene(float x, float y);
    virtual void mouseMoveEvent(QGraphicsSceneDragDropEvent *event);
    virtual void mousePressEvent (QGraphicsSceneMouseEvent * event );
    virtual void mousePressEvent(QGraphicsSceneDragDropEvent *event);
    virtual void mouseReleaseEvent (QGraphicsSceneMouseEvent * event );
	virtual void hoverEnterEvent ( QGraphicsSceneHoverEvent * event ); 
    virtual void hoverLeaveEvent ( QGraphicsSceneHoverEvent * event ); 
	//polygon type is 2.
	virtual int getType();
	//gets a QVector with the polygon points
	QVector<QPointF> getPoints();
	//get the closest Polygon point to the mouseOnPoint point.
	int getClosestPoint(QPointF mouseOnPoint);
	//measures the distance between 2 points.
	int distance(QPointF p1, QPointF p2);
	int movingIndex;
	~PolyFrame(void);
};

