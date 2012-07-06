#include "PolyFrame.h"
#include "mdiPageScene.h"
#include <algorithm>

PolyFrame::PolyFrame(mdiPageScene* scene) :
	FrameDraw(scene),
	_borderColor(Qt::black),
	_borderPen(),
    _dragStart(30,30),
	_points()
{
	//test
	_points.push_back(QPointF(20,50));
	_points.push_back(QPointF(20,90));
	_points.push_back(QPointF(60,110));
	_points.push_back(QPointF(60,50));
	//endtest
	_poly = new QPolygonF(_points);

	_scene = scene;

	_borderPen.setWidth(2);
    _borderPen.setColor(_borderColor);

	this->setAcceptHoverEvents(true);
}

PolyFrame::PolyFrame(mdiPageScene* scene, QVector<QPointF> points) :
	FrameDraw(scene),
	_borderColor(Qt::black),
	_borderPen(),
    _dragStart(30,30),
	_points()
{
	_points = points;
	_poly = new QPolygonF(_points);

	_scene = scene;

	_borderPen.setWidth(2);
    _borderPen.setColor(_borderColor);

	this->setAcceptHoverEvents(true);
}

QRectF PolyFrame::boundingRect() const
{ 
	return this->_poly->boundingRect();
}

void PolyFrame::paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	_borderPen.setColor( _borderColor );
    _borderPen.setStyle(Qt::SolidLine);

    painter->setPen(_borderPen);

    QBrush background (QColor::fromRgb(255,255,255,0), Qt::SolidPattern);
    painter->setBrush( background);


	painter->drawPolygon(*_poly);
}

void PolyFrame::mouseMoveEvent (QGraphicsSceneMouseEvent* event)
{
	qreal dx = event->scenePos().x() - _dragStart.x();
	qreal dy = event->scenePos().y() - _dragStart.y();
	float x = _points.at(movingIndex).x()+dx;
	float y = _points.at(movingIndex).y() + dy;
	//align to scene
	x = std::max((float)x,(float)0);
	y = std::max((float)y,(float)0);
	x = std::min((float)x,(float)this->scene()->sceneRect().width());
	y = std::min((float)y,(float)this->scene()->sceneRect().height());
	//
	_points.replace(movingIndex, QPointF(x,y));
	delete this->_poly;
	this->_poly = new QPolygonF(_points);
	this->update(this->_poly->boundingRect());
	this->scene()->update();
	_dragStart = event->scenePos();
}

void PolyFrame::mouseMoveEvent(QGraphicsSceneDragDropEvent* event){ event->setAccepted(false); }

void PolyFrame::mousePressEvent (QGraphicsSceneMouseEvent* event)
{
	event->setAccepted(true);
	if (this->_scene->_action == mdiPageScene::REMOVE) 
	{
		this->_scene->_action = mdiPageScene::NONE;
		this->removeFromScene();
		return;
	}
	_dragStart = event->scenePos();
	movingIndex = getClosestPoint(event->scenePos());

}

int PolyFrame::getClosestPoint(QPointF mouseOnPoint)
{
	int closest = 0;
	double closestDist = distance(mouseOnPoint, _points.at(closest));
	for (int i = 1; i < _points.size() ; i++)
	{
		double currentDistance = distance(mouseOnPoint, _points.at(i));
		if (currentDistance < closestDist)
		{
			closest = i;
			closestDist = currentDistance;
		}
	}

	return closest;
}

int PolyFrame::distance(QPointF p1, QPointF p2)
{
	return sqrt( pow(p1.x()-p2.x(),2) + pow(p1.y()-p2.y(),2));
}

void PolyFrame::mousePressEvent(QGraphicsSceneDragDropEvent* event){ event->setAccepted(false); }

void PolyFrame::mouseReleaseEvent (QGraphicsSceneMouseEvent* event)
{
	event->setAccepted(true);
	_scene->removeItem(this);
	_scene->addItem(this);
}

void PolyFrame::hoverEnterEvent ( QGraphicsSceneHoverEvent * event )
{
	_borderColor = Qt::red;
	this->update(this->boundingRect());
}

void PolyFrame::hoverLeaveEvent ( QGraphicsSceneHoverEvent * event )
{
	_borderColor = Qt::black;
    this->update(this->boundingRect());
}

int PolyFrame::getType()
{
	return 2;
}

QVector<QPointF> PolyFrame::getPoints()
{
	return this->_points;
}

PolyFrame::~PolyFrame(void)
{
	delete this->_poly;
}
