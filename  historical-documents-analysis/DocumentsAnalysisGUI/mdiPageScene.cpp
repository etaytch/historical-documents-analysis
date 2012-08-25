#include "mdiPageScene.h"
#include "framedraw.h"
#include "PolyFrame.h"
#include "RectFrame.h"
#include "HDAQGraphicsTextItem.h"
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <qDebug>

mdiPageScene::mdiPageScene(QObject* parent, PageDoc& page):
QGraphicsScene(parent), _action(NONE), _frameView(SHOWN), _pointsForNextPoly(), _lastPoly(0), _recentItem(0), _pageDoc(page)
{}

void mdiPageScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
	QPointF mouseOnPoint = mouseEvent->scenePos();

	//add rectangle
	if (_action == ADDRECT)
	{
		addRectangle(mouseOnPoint, 25, 25);
		_action = NONE;
	}

	//add polygon
	if (_action == ADDPOLY)
	{
		_pointsForNextPoly.push_back(mouseOnPoint);
		if (_lastPoly != 0)
		{
			_lastPoly->removeFromScene();
		}
		_lastPoly = this->addPolygon(_pointsForNextPoly);
	}

	// Word Detection:
	if (_action == ADDWORDRECT)
	{		
		// create Rectangle + Text, add to scene and to map
		RectFrame* rct = addRectangle(mouseOnPoint, 35, 35);
		_recentItem = rct;
		HDAQGraphicsTextItem* txt = new HDAQGraphicsTextItem(rct,QString("Title"));
		txt->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable | QGraphicsItem::ItemIsMovable);
		txt->setTextInteractionFlags(Qt::TextEditorInteraction);
		txt->setPos(mouseOnPoint.x(), mouseOnPoint.y()-30);				
		this->addItem(txt);
		_rectFrameTexts[rct]=txt;
		_pageDoc.addWord(txt);
		_action = NONE;
	}
	
	QGraphicsScene::mousePressEvent(mouseEvent);
}

void mdiPageScene::keyPressEvent ( QKeyEvent * keyEvent )
{
	Qt::Key key = (Qt::Key)keyEvent->key();
	
	// increase / decrease rectangle's size
	if((key==Qt::Key::Key_Left)||(key==Qt::Key::Key_Right))
	{
		if(_recentItem)
		{
			QPointF qp = _recentItem->pos();
			
			if(key==Qt::Key::Key_Left)
			{		
				_recentItem->setWidth(_recentItem->getWidth()-20);
				_recentItem->setHeight(_recentItem->getHeight()-20);
				this->update();				
			}
			else
			{	
				_recentItem->setWidth(_recentItem->getWidth()+20);
				_recentItem->setHeight(_recentItem->getHeight()+20);
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
	// remove from map
	if(_rectFrameTexts.contains(toRemove))
	{
		QGraphicsItem* txt = _rectFrameTexts.value(toRemove);
		this->removeItem(txt);		
		_rectFrameTexts.remove(toRemove);
		delete txt;
	}
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

RectFrame* mdiPageScene::addRectangle(QPointF point, qreal width, qreal height)
{
	RectFrame* frame = new RectFrame(this, point,width,height);

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
