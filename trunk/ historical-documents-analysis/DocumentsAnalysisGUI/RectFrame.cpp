#include "RectFrame.h"
#include "mdiPageScene.h"

RectFrame::RectFrame(mdiPageScene* scene, QPointF point) :
	FrameDraw(scene),
	_borderColor(Qt::black),
	_borderPen(),
    _dragStart(30,30),
    _width(25),
    _height(25),
	_hovered(false)
{
	_location = point;
	action = MOVE; // move by default
	_scene = scene;

	_borderPen.setWidth(2);
    _borderPen.setColor(_borderColor);

	this->setAcceptHoverEvents(true);
}

QRectF RectFrame::boundingRect() const
{ 
	return QRectF(0,0,_width + _borderPen.width()*0.5 ,_height);
}

void RectFrame::paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

	if (_hovered)
	{
		_borderPen.setColor(Qt::black);
		_borderPen.setStyle(Qt::DotLine);
		painter->setPen(_borderPen);
		painter->setBrush( background);
		painter->drawRoundRect(QRectF(0,0,_width*0.25 ,_height*0.25));
		painter->drawRoundRect(QRectF(_width-(_width*0.25),0,_width*0.25 ,_height*0.25));
		painter->drawRoundRect(QRectF(0,_height-(_height*0.25),_width*0.25 ,_height*0.25));
		painter->drawRoundRect(QRectF(_width- (_width*0.25),_height-(_height*0.25),_width*0.25 ,_height*0.25));
	}

}


void RectFrame::mouseMoveEvent (QGraphicsSceneMouseEvent* event)
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

	//align to scene
	_location.setX(std::max((float)_location.x(),(float)0));
	_location.setY(std::max((float) _location.y(),(float)0));
	_location.setX(std::min((float) _location.x(), (float) this->scene()->sceneRect().width()));
	_location.setY(std::min((float) _location.y(), (float) this->scene()->sceneRect().height()));
	if ((_location.x() + this->_width) > this->scene()->sceneRect().width())
	{
		if (action == MOVE) _location.setX(this->scene()->sceneRect().width() - this->_width);
		else this->_width = this->scene()->sceneRect().width() - _location.x();
	}
	if ((_location.y() + this->_height) > this->scene()->sceneRect().height())
	{
		if (action == MOVE) _location.setY(this->scene()->sceneRect().height() - this->_height);
		else this->_height = this->scene()->sceneRect().height() - _location.y();
	}
	//
	this->update(0,0,_width,_height);
	this->setPos(_location);
	this->scene()->update();
}

void RectFrame::mouseMoveEvent(QGraphicsSceneDragDropEvent* event){ event->setAccepted(false); }

void RectFrame::mousePressEvent (QGraphicsSceneMouseEvent* event)
{
	event->setAccepted(true);
	if (this->_scene->_action == mdiPageScene::REMOVE) 
	{
		this->_scene->_action = mdiPageScene::NONE;
		this->removeFromScene();
		return;
	}
	_dragStart = event->scenePos();
	if (closeTo(this->boundingRect().bottomRight() , event->pos()))		{ 	action = RESIZEBR;	}
	else if (closeTo(this->boundingRect().topRight() , event->pos()))		{	action = RESIZETR;	}
	else if (closeTo(this->boundingRect().bottomLeft() , event->pos()))	{	action = RESIZEBL;	}
	else if (closeTo(this->boundingRect().topLeft() , event->pos()))		{ 	action = RESIZETL;	}
	else 	{	
		_dragStart = event->pos();
		action = MOVE;	
	}
}

bool RectFrame::closeTo(QPointF p1, QPointF p2)
{
	int dx = abs(p1.x() - p2.x());
	int dy = abs(p1.y() - p2.y());
	if ((dx < _width*0.25) && (dy < _height*0.25)) return true;
	
	return false;
}

void RectFrame::mousePressEvent(QGraphicsSceneDragDropEvent* event){ event->setAccepted(false); }

void RectFrame::mouseReleaseEvent (QGraphicsSceneMouseEvent* event)
{
	event->setAccepted(true);
	_scene->removeItem(this);
	_scene->addItem(this);
}

void RectFrame::hoverEnterEvent ( QGraphicsSceneHoverEvent * event )
{
	_hovered = true;
	_borderColor = Qt::red;
    this->update(0,0,_width,_height);
}

void RectFrame::hoverLeaveEvent ( QGraphicsSceneHoverEvent * event )
{
	_hovered = false;
	_borderColor = Qt::black;
    this->update(0,0,_width,_height);
}

QPointF RectFrame::getPos()
{
	return this->_location;
}

qreal RectFrame::getWidth()
{
	return this->_width;
}

void RectFrame::setWidth(int width)
{
	this->_width = width;
	this->update(0,0,_width,_height);
}

qreal RectFrame::getHeight()
{
	return this->_height;
}

void RectFrame::setHeight(int height)
{
	this->_height = height;
	this->update(0,0,_width,_height);
}

RectFrame::~RectFrame(void)
{
}
