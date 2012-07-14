#include "framedraw.h"
#include <QGraphicsSceneDragDropEvent>
#include <QPainter>
#include <QRectF>
#include <QPolygonF>
#include <algorithm>
#include "mdiPageScene.h"


FrameDraw::FrameDraw(mdiPageScene* scene) : 
	QObject(),
	QGraphicsItem()
{
	_scene = scene;	
}

void FrameDraw::removeFromScene()
{
	this->_scene->removeFrame(this);
}

FrameDraw::~FrameDraw()
{

}
