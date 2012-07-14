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
	_borderPen(),
	_borderColor(Qt::black),
    _dragStart(30,30),
	_scene(scene)
{
	_borderPen.setWidth(2);
    _borderPen.setColor(_borderColor);
}

void FrameDraw::removeFromScene()
{
	this->_scene->removeFrame(this);
}

FrameDraw::~FrameDraw()
{}
