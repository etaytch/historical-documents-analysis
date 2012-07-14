#ifndef FRAMEDRAW_H
#define FRAMEDRAW_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPen>
#include <QMetaobject>
class mdiPageScene;

class FrameDraw : public QObject, public QGraphicsItem
{
	Q_OBJECT

public:
	FrameDraw(mdiPageScene* scene);
	virtual void removeFromScene();
	~FrameDraw();
	
	mdiPageScene* _scene;
};

#endif // FRAMEDRAW_H
