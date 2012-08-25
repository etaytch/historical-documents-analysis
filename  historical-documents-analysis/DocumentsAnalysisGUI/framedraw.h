#ifndef FRAMEDRAW_H
#define FRAMEDRAW_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPen>
#include <QMetaobject>
class mdiPageScene;
////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	all graphic items base class.. </summary>
///
/// <remarks>	Yair Offir, 1/8/2012. </remarks>		
////////////////////////////////////////////////////////////////////////////////////////////////////
class FrameDraw : public QObject, public QGraphicsItem
{
	Q_OBJECT

public:
	FrameDraw(mdiPageScene* scene);
	virtual void removeFromScene();
	~FrameDraw();
	
protected:
	mdiPageScene* _scene;
	QPointF _dragStart;
	QPen    _borderPen;
	QColor  _borderColor;
};

#endif // FRAMEDRAW_H
