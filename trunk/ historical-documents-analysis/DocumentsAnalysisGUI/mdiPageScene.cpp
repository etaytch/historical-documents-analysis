#include "mdiPageScene.h"
#include "framedraw.h"
#include <QGraphicsSceneMouseEvent>

mdiPageScene::mdiPageScene(QObject* parent):
QGraphicsScene(parent), _action(NONE)
{
	_action = ADD;
}

void mdiPageScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
	QPointF mouseOnPoint = mouseEvent->scenePos();

	if (_action == ADD) this->addItem(new FrameDraw(this, mouseOnPoint));
	_action = NONE;

	QGraphicsScene::mousePressEvent(mouseEvent);
}

void mdiPageScene::removeRect(FrameDraw* toRemove)
{
	this->removeItem((QGraphicsItem*) toRemove);
	delete toRemove;
}

mdiPageScene::~mdiPageScene(void)
{}
