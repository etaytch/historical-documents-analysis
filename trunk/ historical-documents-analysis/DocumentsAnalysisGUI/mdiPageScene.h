#pragma once
#include <QGraphicsScene>
class FrameDraw;

class mdiPageScene :
	public QGraphicsScene
{
public:
	
	mdiPageScene(QObject* parent);
	virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
	void removeRect(FrameDraw* toRemove);
	virtual ~mdiPageScene(void);

	enum RectAction { ADD, REMOVE, NONE};
	RectAction _action; 
};

