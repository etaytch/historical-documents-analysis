#include "framedraw.h"
#include <QGraphicsSceneDragDropEvent>
#include <QPainter>
#include <QRectF>
#include <QPolygonF>


FrameDraw::FrameDraw(QGraphicsScene* scene)	: 
	QObject(),
	QGraphicsItem(),
	_borderColor(Qt::black),
	_borderPen(),
    _location(30,30),
    _dragStart(30,30),
    _width(100),
    _height(50)
{
	action = 1; // resize by default
	_scene = scene;

	_borderPen.setWidth(2);
    _borderPen.setColor(_borderColor);

	this->setAcceptHoverEvents(true);
}

QRectF FrameDraw::boundingRect() const
{ 
	return QRectF(0,0,_width + _borderPen.width()*0.5 ,_height);
}

void FrameDraw::paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	_borderPen.setColor( _borderColor );
    _borderPen.setStyle(Qt::SolidLine);

    painter->setPen(_borderPen);

    QBrush background (QColor::fromRgb(255,255,255,0), Qt::SolidPattern);
    painter->setBrush( background);


	QPointF topLeft (0, 0);
    QPointF bottomRight ( _width, _height );

    QRectF rect (topLeft, bottomRight);
	
    painter->drawRoundRect(rect,0,0);
	setPos(_location);

}

void FrameDraw::mouseMoveEvent (QGraphicsSceneMouseEvent* event)
{
	//resize
	if (action == 1){
		qreal dx = event->pos().x() - _dragStart.x();
		qreal dy = event->pos().y() - _dragStart.y();
		this->_width += dx ;
		this->_height += dy;
		this->update(3,3,_width,_height);
		_dragStart = event->pos();
	}
	//move
	if (action == 2){
		QPointF newPos = event->pos() ;
		_location += (newPos - _dragStart);
		this->setPos(_location);
		
	}
	this->scene()->update();
}

void FrameDraw::mouseMoveEvent(QGraphicsSceneDragDropEvent* event){ event->setAccepted(false); }
void FrameDraw::mousePressEvent (QGraphicsSceneMouseEvent* event)
{
	event->setAccepted(true);
	_dragStart = event->pos();
	QPointF tleft = this->boundingRect().topLeft();
	int dx = abs(_dragStart.x());
	int dy = abs(_dragStart.y());
	if ((dx < _width*0.5) &&
		(dy < _height*0.5)) 
	{
		//move
		action = 2;
	}
	else 
	{
		//resize
		action = 1;
	}
}

void FrameDraw::mousePressEvent(QGraphicsSceneDragDropEvent* event){ event->setAccepted(false); }
void FrameDraw::mouseReleaseEvent (QGraphicsSceneMouseEvent* event)
{
	event->setAccepted(true);
	_scene->removeItem(this);
	_scene->addItem(this);
}

void FrameDraw::hoverEnterEvent ( QGraphicsSceneHoverEvent * event )
{
	_borderColor = Qt::red;
    this->update(0,0,_width,_height);
}

void FrameDraw::hoverLeaveEvent ( QGraphicsSceneHoverEvent * event )
{
	_borderColor = Qt::black;
    this->update(0,0,_width,_height);
}

FrameDraw::~FrameDraw()
{

}
