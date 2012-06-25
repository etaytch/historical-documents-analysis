#include "mdiPageScene.h"
#include "framedraw.h"
#include <QGraphicsSceneMouseEvent>

mdiPageScene::mdiPageScene(QObject* parent):
QGraphicsScene(parent), _action(NONE), _frameView(SHOWN)
{
	//delete
	_action = ADD;

}

void mdiPageScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
	QPointF mouseOnPoint = mouseEvent->scenePos();

	if (_action == ADD)
	{
		addRectangle(mouseOnPoint);
	}
	_action = NONE;
	
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

void mdiPageScene::removeRect(FrameDraw* toRemove)
{
	this->removeItem((QGraphicsItem*) toRemove);
	delete toRemove;
}

QVector<FrameDraw*> mdiPageScene::getFrames()
{
	return this->frames;
}

FrameDraw* mdiPageScene::addRectangle(QPointF point)
{
	FrameDraw* frameDraw = new FrameDraw(this, point);
	this->frames.push_back(frameDraw);
			
	this->addItem(frameDraw);
	frameDraw->setShown(true);

	return frameDraw;
}

mdiPageScene::~mdiPageScene(void)
{}
