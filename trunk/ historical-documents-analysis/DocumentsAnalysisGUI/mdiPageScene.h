#pragma once
#include <QGraphicsScene>
class mdiPageScene :
	public QGraphicsScene
{
public:
	mdiPageScene(QObject* parent);
	virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
	virtual ~mdiPageScene(void);
};

