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
	return QRectF(0,0,_width,_height);
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
	
	//QPolygonF poly(_points);
	//painter->drawPolyline(poly);

    painter->drawRoundRect(rect,0,0);

}

void FrameDraw::mouseMoveEvent (QGraphicsSceneMouseEvent* event)
{
	//resize
	if (action == 1){
		qreal dx = event->pos().x() - _dragStart.x();
		qreal dy = event->pos().y() - _dragStart.y();
		this->_width += dx ;
		this->_height += dy;
		this->update(0,0,_width,_height);
	
		_dragStart = event->pos();
	}
	//move
	if (action == 2){
		QPointF newPos = event->pos() ;
		_location += (newPos - _dragStart);
		this->setPos(_location);	
	}
}

void FrameDraw::mouseMoveEvent(QGraphicsSceneDragDropEvent* event){ event->setAccepted(false); }
void FrameDraw::mousePressEvent (QGraphicsSceneMouseEvent* event)
{
	event->setAccepted(true);
	_dragStart = event->pos();
	int dx = abs(_location.x() - _dragStart.x());
	int dy = abs(_location.y() - _dragStart.y());
	/*if ((dx < _width*0.25) &&
		(dy < _height*0.25)) action = 1;
	else action = 2;*/
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
