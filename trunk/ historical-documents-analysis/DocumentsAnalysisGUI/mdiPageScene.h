#pragma once
#include <QGraphicsScene>
class FrameDraw;
class RectFrame;

class mdiPageScene :
	public QGraphicsScene
{
public:
	
	mdiPageScene(QObject* parent);
	virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
	void showAll();
	void removeAll();
	void removeFrame(FrameDraw* toRemove);
	QVector<FrameDraw*> getFrames();
	RectFrame* addRectangle(QPointF point);
	FrameDraw* addPolygon(QVector<QPointF> points);
	void DrawPoly();
	virtual ~mdiPageScene(void);

	QVector<QPointF> _pointsForNextPoly;
	enum RectAction { ADDPOLY, ADDRECT, REMOVE, NONE};
	RectAction _action; 
	enum RectView { SHOWN, HIDDEN};
	RectView _frameView; 
};

