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

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	mousePressEvent Event. </summary>
	///
	/// <remarks>	Etay Tchechanovski, 1/8/2012. </remarks>
	/// <param name="mouseEvent">	[in] The Event. </param>		
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	keyPressEvent Event. </summary>
	///
	/// <remarks>	Etay Tchechanovski, 1/8/2012. </remarks>
	/// <param name="keyEvent">	[in] The Event. </param>		
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual void keyPressEvent ( QKeyEvent * keyEvent );
	void showAll();
	void removeAll();
	void removeFrame(FrameDraw* toRemove);
	QVector<FrameDraw*> getFrames();
	RectFrame* addRectangle(QPointF point, qreal width, qreal height);
	FrameDraw* addPolygon(QVector<QPointF> points);
	void DrawPoly();
	virtual ~mdiPageScene(void);

	FrameDraw* _lastPoly;
	QVector<QPointF> _pointsForNextPoly;
	enum RectAction { CHANGETOPOLY, DELETEPOINT, ADDPOLY, ADDRECT, REMOVE, ADDWORDRECT, NONE};
	RectAction _action; 
	enum RectView { SHOWN, HIDDEN};
	RectView _frameView; 
	RectFrame* _recentItem;
	PageDoc _pageDoc;

	// for words detection: maps rectangle to text
	QHash<FrameDraw*,HDAQGraphicsTextItem*> _rectFrameTexts;
};

