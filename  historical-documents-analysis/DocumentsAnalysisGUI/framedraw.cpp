#include "framedraw.h"
#include <QGraphicsSceneDragDropEvent>
#include <QPainter>
#include <QRectF>
#include <QPolygonF>
#include <algorithm>


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
	action = MOVE; // move by default
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
	//move by default
	qreal dx = event->scenePos().x() - _dragStart.x();
	qreal dy = event->scenePos().y() - _dragStart.y();
	QPointF newPos = event->scenePos() ;
	switch(action)
	{
	case RESIZEBR:
		this->_width += dx ;
		this->_height += dy;
		_dragStart = event->scenePos();
		break;
	case RESIZEBL:
		//that will zero y.
		newPos.setY(_dragStart.y());
		_location += (newPos - _dragStart);
		this->_height += dy;
		this->_width -= dx;
		_dragStart = event->scenePos();
		break;
	case RESIZETR:
		//that will zero x.
		newPos.setX(_dragStart.x());
		_location += (newPos - _dragStart);
		this->_height -= dy;
		this->_width += dx;
		_dragStart = event->scenePos();
		break;
	case RESIZETL:
		_location += (newPos - _dragStart);
		this->_height -= dy;
		this->_width -= dx;
		_dragStart = event->scenePos();
		break;
	default:
		//move
		newPos = event->pos() ;
		_location += (newPos - _dragStart);
		break;
	}
	this->_width = std::max((float)this->_width, (float)10);
	this->_height = std::max((float)this->_height, (float)10);
	this->update(0,0,_width,_height);
	this->setPos(_location);
	this->scene()->update();
}

void FrameDraw::mouseMoveEvent(QGraphicsSceneDragDropEvent* event){ event->setAccepted(false); }

void FrameDraw::mousePressEvent (QGraphicsSceneMouseEvent* event)
{
	event->setAccepted(true);
	_dragStart = event->scenePos();
	//QPointF tleft = this->boundingRect().topLeft();
	//int dx = abs(_dragStart.x());
	//int dy = abs(_dragStart.y());
	if (closeTo(this->boundingRect().bottomRight() , event->pos()))		{ 	action = RESIZEBR;	}
	else if (closeTo(this->boundingRect().topRight() , event->pos()))		{	action = RESIZETR;	}
	else if (closeTo(this->boundingRect().bottomLeft() , event->pos()))	{	action = RESIZEBL;	}
	else if (closeTo(this->boundingRect().topLeft() , event->pos()))		{ 	action = RESIZETL;	}
	else 	{	
		_dragStart = event->pos();
		action = MOVE;	
	}
}

bool FrameDraw::closeTo(QPointF p1, QPointF p2)
{
	int dx = abs(p1.x() - p2.x());
	int dy = abs(p1.y() - p2.y());
	if ((dx < _width*0.25) && (dy < _height*0.25)) return true;
	
	return false;
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
