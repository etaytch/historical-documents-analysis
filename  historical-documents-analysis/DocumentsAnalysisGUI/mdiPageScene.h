#pragma once
#include <QGraphicsScene>
class mdiPageScene :
	public QGraphicsScene
{
public:
	enum RectAction { ADD, REMOVE, NONE};
	RectAction _action; 
	mdiPageScene(QObject* parent);
	virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
	virtual ~mdiPageScene(void);
};

