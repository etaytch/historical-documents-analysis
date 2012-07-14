#include "mdiPageScene.h"
#include "framedraw.h"
#include "PolyFrame.h"
#include "RectFrame.h"
#include <QGraphicsSceneMouseEvent>

mdiPageScene::mdiPageScene(QObject* parent):
QGraphicsScene(parent), _action(NONE), _frameView(SHOWN), _pointsForNextPoly()
{}

void mdiPageScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
	QPointF mouseOnPoint = mouseEvent->scenePos();

	if (_action == ADDRECT)
	{
		addRectangle(mouseOnPoint);
		_action = NONE;
	}

	if (_action == ADDPOLY)
	{
		_pointsForNextPoly.push_back(mouseOnPoint);
	}
	
	QGraphicsScene::mousePressEvent(mouseEvent);
}

void mdiPageScene::showAll()
{
	QVector<FrameDraw*>::Iterator iter;
	for( iter = this->frames.begin(); iter != this->frames.end() ; ++iter)
	{
		FrameDraw* frame = *iter;
		if (!frame->isShown())
		{
			this->addItem(frame);
			frame->setShown(true);
		}
	}
}

void mdiPageScene::removeAll()
{
	QVector<FrameDraw*>::Iterator iter;
	for( iter = this->frames.begin(); iter != this->frames.end() ; ++iter)
	{
		FrameDraw* frame = *iter;
		if (frame->isShown())
		{
			this->removeItem(frame);
			frame->setShown(false);
		}
	}
}

void mdiPageScene::removeFrame(FrameDraw* toRemove)
{
	this->removeItem((QGraphicsItem*) toRemove);
	this->frames.remove(this->frames.indexOf(toRemove));
	delete toRemove;
}

QVector<FrameDraw*> mdiPageScene::getFrames()
{
	return this->frames;
}

RectFrame* mdiPageScene::addRectangle(QPointF point)
{
	RectFrame* frame = new RectFrame(this, point);
	this->frames.push_back(frame);
			
	this->addItem(frame);
	frame->setShown(true);

	return frame;
}

FrameDraw* mdiPageScene::addPolygon(QVector<QPointF> points)
{
	FrameDraw* frameDraw = 0;
	if (points.size() > 0) frameDraw = new PolyFrame(this, points);
	else frameDraw = new PolyFrame(this);
	this->frames.push_back(frameDraw);
			
	this->addItem(frameDraw);
	frameDraw->setShown(true);

	return frameDraw;
}

void mdiPageScene::DrawPoly()
{
	_action = NONE;
	addPolygon(_pointsForNextPoly);
	_pointsForNextPoly.clear();

}

mdiPageScene::~mdiPageScene(void)
{}
