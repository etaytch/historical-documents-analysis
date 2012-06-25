#pragma once
#include <QGraphicsScene>
class FrameDraw;

class mdiPageScene :
	public QGraphicsScene
{
public:
	
	mdiPageScene(QObject* parent);
	virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
	void showAll();
	void removeAll();
	void removeRect(FrameDraw* toRemove);
	QVector<FrameDraw*> getFrames();
	virtual ~mdiPageScene(void);

	QVector<FrameDraw*> frames;
	enum RectAction { ADD, REMOVE, NONE};
	RectAction _action; 
	enum RectView { SHOWN, HIDDEN};
	RectView _frameView; 
};

