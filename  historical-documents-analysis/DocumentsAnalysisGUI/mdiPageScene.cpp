#include "mdiPageScene.h"
#include <QGraphicsSceneMouseEvent>

mdiPageScene::mdiPageScene(QObject* parent):
QGraphicsScene(parent)
{}

void mdiPageScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
	QPointF mouseOnPoint = mouseEvent->scenePos();
	QGraphicsScene::mousePressEvent(mouseEvent);
}

mdiPageScene::~mdiPageScene(void)
{}
