#include "framedraw.h"
#include <QGraphicsSceneDragDropEvent>
#include <QPainter>
#include <QRectF>
#include <QPolygonF>
#include <algorithm>
#include "mdiPageScene.h"


FrameDraw::FrameDraw(mdiPageScene* scene) : 
	QObject(),
	QGraphicsItem(),
	_shown(false)
{
	_scene = scene;	
}

bool FrameDraw::isShown()
{
	return _shown;
}

void FrameDraw::setShown(bool shown)
{
	_shown = shown;
}

void FrameDraw::removeFromScene()
{
	this->_scene->removeItem(this);
}

FrameDraw::~FrameDraw()
{

}
