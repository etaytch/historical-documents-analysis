#include "mdiPageScene.h"
#include "framedraw.h"
#include "PolyFrame.h"
#include "RectFrame.h"
#include "HDAQGraphicsTextItem.h"
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <qDebug>

mdiPageScene::mdiPageScene(QObject* parent):
QGraphicsScene(parent), _action(NONE), _frameView(SHOWN), _pointsForNextPoly(), _lastPoly(0), _recentItem(0)
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
		if (_lastPoly != 0)
		{
			_lastPoly->removeFromScene();
		}
		_lastPoly = this->addPolygon(_pointsForNextPoly);
	}

	if (_action == ADDWORDRECT)
	{
		//addRectangle(mouseOnPoint);
		HDAQGraphicsTextItem* txt = new HDAQGraphicsTextItem(QString("BLA"));
		txt->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable | QGraphicsItem::ItemIsMovable);
		txt->setTextInteractionFlags(Qt::TextEditorInteraction);
		txt->setPos(mouseOnPoint.x(), mouseOnPoint.y()-30);				
		this->addItem(txt);
		RectFrame* rct = addRectangle(mouseOnPoint);
		_recentItem = rct;
		_action = NONE;
	}
	
	QGraphicsScene::mousePressEvent(mouseEvent);
}

void mdiPageScene::keyPressEvent ( QKeyEvent * keyEvent )
{
	Qt::Key key = (Qt::Key)keyEvent->key();
	
	if((key==Qt::Key::Key_Left)||(key==Qt::Key::Key_Right))
	{
		if(_recentItem)
		{
			QPointF qp = _recentItem->pos();
			
			if(key==Qt::Key::Key_Left)
			{				
				qp.setX(qp.x()-20);
				_recentItem->setPos(qp);
				_recentItem->update();						
				this->update();				
			}
			else
			{				
				qp.setX(qp.x()+20);
				_recentItem->setPos(qp);
				_recentItem->update();
				this->update();
			}
		}	
		else QGraphicsScene::keyPressEvent(keyEvent);
	}
	else QGraphicsScene::keyPressEvent(keyEvent);


	
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
	if (points.size() > 0) 
	{
		FrameDraw* frameDraw = new PolyFrame(this, points);
		this->addItem(frameDraw);
		return frameDraw;
	}
	return 0;
}

void mdiPageScene::DrawPoly()
{
	_lastPoly = 0;
	_action = NONE;
	//addPolygon(_pointsForNextPoly);
	_pointsForNextPoly.clear();

}

mdiPageScene::~mdiPageScene(void)
{}
