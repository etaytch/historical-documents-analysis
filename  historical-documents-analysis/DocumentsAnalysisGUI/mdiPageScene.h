#pragma once
#include <QGraphicsScene>
#include "PageDoc.h"
class FrameDraw;
class RectFrame;

class mdiPageScene :
	public QGraphicsScene
{
public:
	
	mdiPageScene(QObject* parent, PageDoc& page);
	virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
	virtual void keyPressEvent ( QKeyEvent * keyEvent );
	void showAll();
	void removeAll();
	void removeFrame(FrameDraw* toRemove);
	QVector<FrameDraw*> getFrames();
	RectFrame* addRectangle(QPointF point);
	FrameDraw* addPolygon(QVector<QPointF> points);
	void DrawPoly();
	virtual ~mdiPageScene(void);

	FrameDraw* _lastPoly;
	QVector<QPointF> _pointsForNextPoly;
	enum RectAction { CHANGETOPOLY, DELETEPOINT, ADDPOLY, ADDRECT, REMOVE, ADDWORDRECT, NONE};
	RectAction _action; 
	enum RectView { SHOWN, HIDDEN};
	RectView _frameView; 
	QGraphicsItem* _recentItem;
	PageDoc _pageDoc;
};

