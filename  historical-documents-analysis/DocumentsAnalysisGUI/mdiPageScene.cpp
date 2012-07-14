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
	QList<QGraphicsItem*> sceneFrames = this->items();
	QList<QGraphicsItem*>::Iterator iter;
	for( iter = sceneFrames.begin(); iter != sceneFrames.end() ; ++iter)
	{
		QGraphicsItem* frame = dynamic_cast<FrameDraw*>(*iter);
		if (frame != 0) frame->setVisible(true);
	}
}

void mdiPageScene::removeAll()
{
	QList<QGraphicsItem*> sceneFrames = this->items();
	QList<QGraphicsItem*>::Iterator iter;
	for( iter = sceneFrames.begin(); iter != sceneFrames.end() ; ++iter)
	{
		QGraphicsItem* frame = dynamic_cast<FrameDraw*>(*iter);
		if (frame != 0)frame->setVisible(false);
	}
}

void mdiPageScene::removeFrame(FrameDraw* toRemove)
{
	this->removeItem((QGraphicsItem*) toRemove);
	delete toRemove;
}

QVector<FrameDraw*> mdiPageScene::getFrames()
{
	QVector<FrameDraw*> allFrames;
	QList<QGraphicsItem*> sceneFrames = this->items();
	QList<QGraphicsItem*>::Iterator iter;
	for( iter = sceneFrames.begin(); iter != sceneFrames.end() ; ++iter)
	{
		FrameDraw* frame = dynamic_cast<FrameDraw*>(*iter);
		if (frame != 0) allFrames.push_back(frame);
	}

	return allFrames;
}

RectFrame* mdiPageScene::addRectangle(QPointF point)
{
	RectFrame* frame = new RectFrame(this, point);

	this->addItem(frame);

	return frame;
}

FrameDraw* mdiPageScene::addPolygon(QVector<QPointF> points)
{
	FrameDraw* frameDraw = 0;
	if (points.size() > 0) frameDraw = new PolyFrame(this, points);
	else frameDraw = new PolyFrame(this);
			
	this->addItem(frameDraw);

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
