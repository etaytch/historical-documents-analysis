#include "RectFrame.h"
#include "mdiPageScene.h"
#include <QVector>

int RectFrame::MAXHEIGHT = 10;
int RectFrame::MAXWIDTH = 10;

RectFrame::RectFrame(mdiPageScene* scene, QPointF point, qreal width, qreal height) :
	FrameDraw(scene),
    _width(width),
    _height(height),
	_hovered(false)
{
	_location = point;
	action = MOVE; // move by default

	this->setPos(_location);

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
		painter->drawRoundRect(QRectF(0,0, std::min((float) (_width*0.25), (float)MAXWIDTH) , std::min((float) (_height*0.25), (float)MAXHEIGHT)));
		painter->drawRoundRect(QRectF(_width-std::min((float) (_width*0.25), (float)MAXWIDTH),0,std::min((float) (_width*0.25), (float)MAXWIDTH) ,std::min((float) (_height*0.25), (float)MAXHEIGHT)));
		painter->drawRoundRect(QRectF(0,_height-std::min((float) (_height*0.25), (float)MAXHEIGHT),std::min((float) (_width*0.25), (float)MAXWIDTH) ,std::min((float) (_height*0.25), (float)MAXHEIGHT)));
		painter->drawRoundRect(QRectF(_width- std::min((float) (_width*0.25), (float)MAXWIDTH),_height-std::min((float) (_height*0.25), (float)MAXHEIGHT),std::min((float) (_width*0.25), (float)MAXWIDTH) ,std::min((float) (_height*0.25), (float)MAXHEIGHT)));
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
		if (action == MOVE) _location.setX(this->scene()->sceneRect().width() - this->_width - 1);
		else this->_width = this->scene()->sceneRect().width() - _location.x();
	}
	if ((_location.y() + this->_height) > this->scene()->sceneRect().height())
	{
		if (action == MOVE) _location.setY(this->scene()->sceneRect().height() - this->_height - 1);
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

	if (this->_scene->_action == mdiPageScene::CHANGETOPOLY) 
	{
		QVector<QPointF> points;
		points.push_back(mapToScene(0,0));
		points.push_back(mapToScene(_width,0));
		points.push_back(mapToScene(_width,_height));
		points.push_back(mapToScene(0,_height));		
		this->_scene->addPolygon(points);
		this->_scene->_action = mdiPageScene::NONE;
		this->removeFromScene();
		return;
	}

	if (this->_scene->_action == mdiPageScene::DELETEPOINT)
	{
		this->_scene->_action = mdiPageScene::NONE;
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
	return ((dx < _width*0.25) && (dx < MAXWIDTH) && (dy < _height*0.25) && (dy < MAXHEIGHT));
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
	return mapToScene(this->_location);
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
