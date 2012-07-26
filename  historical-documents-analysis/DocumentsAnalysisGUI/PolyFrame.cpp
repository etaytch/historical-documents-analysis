#include "PolyFrame.h"
#include "mdiPageScene.h"
#include <algorithm>

int PolyFrame::MAXDISTANCE = 10;

PolyFrame::PolyFrame(mdiPageScene* scene, QVector<QPointF> points) :
	FrameDraw(scene),
	_points(),
	_hovered(false)
{
	_points = points;
	_poly = new QPolygonF(_points);

	this->setAcceptHoverEvents(true);
}

QRectF PolyFrame::boundingRect() const
{ 
	QRectF bounding = this->_poly->boundingRect();
	QPointF topleft = bounding.topLeft();
	bounding.moveTopLeft(QPointF(topleft.x() -MAXDISTANCE,topleft.y() -MAXDISTANCE));
	bounding.setWidth(	bounding.width()	+ (2 * MAXDISTANCE));
	bounding.setHeight(	bounding.height()	+ (2 * MAXDISTANCE));
	return bounding;
}

void PolyFrame::paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	_borderPen.setColor( _borderColor );
    _borderPen.setStyle(Qt::SolidLine);

    painter->setPen(_borderPen);

    QBrush background (QColor::fromRgb(255,255,255,0), Qt::SolidPattern);
    painter->setBrush( background);


	painter->drawPolygon(*_poly);

	if (_hovered)
	{
		_borderPen.setColor(Qt::black);
		_borderPen.setStyle(Qt::DotLine);
		painter->setPen(_borderPen);
		painter->setBrush( background);
		for (int i = 0; i < _points.size() ; i++)
		{
			painter->drawEllipse(this->_points.at(i),MAXDISTANCE,MAXDISTANCE);
		}
		
	}
}

void PolyFrame::mouseMoveEvent (QGraphicsSceneMouseEvent* event)
{
	qreal dx = event->scenePos().x() - _dragStart.x();
	qreal dy = event->scenePos().y() - _dragStart.y();
	//MOVING
	if (movingIndex < 0) 
	{
		for (int i = 0; i < _points.size() ; i++)
		{
			float x = _points.at(i).x()+dx;
			float y = _points.at(i).y() + dy;
			_points.replace(i, adjustToScene(x,y));
		}
	}
	//MOVING A POINT
	else
	{
		float x = _points.at(movingIndex).x()+dx;
		float y = _points.at(movingIndex).y() + dy;
		_points.replace(movingIndex, adjustToScene(x,y));
	}
	delete this->_poly;
	this->_poly = new QPolygonF(_points);
	this->update(this->_poly->boundingRect());
	this->scene()->update();
	_dragStart = event->scenePos();
}

QPointF PolyFrame::adjustToScene(float x, float y)
{
	x = std::max((float)x,(float)0);
	y = std::max((float)y,(float)0);
	x = std::min((float)x,(float)this->scene()->sceneRect().width());
	y = std::min((float)y,(float)this->scene()->sceneRect().height());
	return QPointF(x,y);
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

	if (this->_scene->_action == mdiPageScene::CHANGETOPOLY)
	{
		this->_scene->_action = mdiPageScene::NONE;
	}

	if (this->_scene->_action == mdiPageScene::DELETEPOINT) 
	{
		if (this->_points.size() > 3)
		{
			int toDelete = getClosestPoint(event->scenePos());
			if (toDelete != -1)
			{
				this->_points.remove(toDelete);
				delete this->_poly;
				this->_poly = new QPolygonF(_points);
				this->update(this->_poly->boundingRect());
				this->scene()->update();
			}
		}
		this->_scene->_action = mdiPageScene::NONE;
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
	if (closestDist < MAXDISTANCE) return closest;

	return -1;
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
	_hovered = true;
	_borderColor = Qt::red;
	this->update(this->boundingRect());
}

void PolyFrame::hoverLeaveEvent ( QGraphicsSceneHoverEvent * event )
{
	_hovered = false;
	_borderColor = Qt::black;
    this->update(this->boundingRect());
	this->scene()->update();
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
