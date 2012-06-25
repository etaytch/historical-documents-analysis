#ifndef FRAMEDRAW_H
#define FRAMEDRAW_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPen>
#include <QMetaobject>
class mdiPageScene;

class FrameDraw : public QObject, public QGraphicsItem
{
	Q_OBJECT

public:
	FrameDraw(mdiPageScene* scene, QPointF point);
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
	bool closeTo(QPointF p1, QPointF p2);
	void movePosition(int x, int y);
	bool isShown();
	void setShown(bool shown);
	QPointF getPos();
	void FrameDraw::setWidth(int width);
	int getWidth();	
	void FrameDraw::setHeight(int height);
	int getHeight();
	void removeFromScene();
	~FrameDraw();

	mdiPageScene* _scene;
	QColor  _borderColor; 
    QPen    _borderPen; 
    QPointF _location;
    QPointF _dragStart;
    qreal   _width;
    qreal   _height;
	bool _shown;
	//move, resize top right, resize top left, resize bottom right, resize bottom left
	enum mouseAction { MOVE, RESIZETR, RESIZETL, RESIZEBR, RESIZEBL};
	mouseAction action; 
	

private:
	
};

#endif // FRAMEDRAW_H
