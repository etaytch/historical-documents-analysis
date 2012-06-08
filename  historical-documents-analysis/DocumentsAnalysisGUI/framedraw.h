#ifndef FRAMEDRAW_H
#define FRAMEDRAW_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPen>
#include <QMetaobject>

class FrameDraw : public QObject, public QGraphicsItem
{
	Q_OBJECT

public:
	FrameDraw(QGraphicsScene* scene);
	void setGridSpace(int space);
	virtual QRectF boundingRect() const; 
    virtual void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); 
    virtual void mouseMoveEvent ( QGraphicsSceneMouseEvent * event );
    virtual void mouseMoveEvent(QGraphicsSceneDragDropEvent *event);
    virtual void mousePressEvent (QGraphicsSceneMouseEvent * event );
    virtual void mousePressEvent(QGraphicsSceneDragDropEvent *event);
    virtual void mouseReleaseEvent (QGraphicsSceneMouseEvent * event );
	virtual void hoverEnterEvent ( QGraphicsSceneHoverEvent * event ); 
    virtual void hoverLeaveEvent ( QGraphicsSceneHoverEvent * event ); 
	void movePosition(int x, int y);
	QGraphicsScene* _scene;
	QColor  _borderColor; 
    QPen    _borderPen; 
    QPointF _location;
    QPointF _dragStart;
    qreal   _width;
    qreal   _height;
	int action; // 1 is resize, 2 is move
	~FrameDraw();

private:
	
};

#endif // FRAMEDRAW_H
