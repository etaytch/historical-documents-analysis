#ifndef HDAQGRAPHICSTEXTITEM_H
#define HDAQGRAPHICSTEXTITEM_H

#include <QGraphicsTextItem>
#include "RectFrame.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	HDAQGraphicsTextItem class displays a Rect + text. </summary>
///
/// <remarks>	Etay Tchechanovski and Eliav Ben Zaken, 1/8/2012. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

class HDAQGraphicsTextItem : public QGraphicsTextItem
{
	Q_OBJECT

public:
	HDAQGraphicsTextItem(RectFrame* rect,QString txt);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Returns the RectFrame</summary>
	///
	/// <remarks>	Etay Tchechanovski and Eliav Ben Zaken, 1/8/2012. </remarks>
	/// <returns>	The Progress Bar's value. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	RectFrame* getRect();	
	~HDAQGraphicsTextItem();

protected:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Catchs a keyPressEvent to save the text </summary>
	///
	/// <remarks>	Etay Tchechanovski and Eliav Ben Zaken, 1/8/2012. </remarks>
	/// <param name="event">	[in] The event. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void keyPressEvent ( QKeyEvent * event );

private:
	RectFrame* _rect;
};

#endif // HDAQGRAPHICSTEXTITEM_H
