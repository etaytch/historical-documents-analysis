#ifndef _TEXTLINE_H 
#define _TEXTLINE_H 

#include "DImage.h"

using namespace cv ;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Text line class extends a DImmage and hold the property of a text line </summary>
///
/// <remarks>	El Sana, 2/9/2012. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

class TextLine : public DImage {
	Rect   _rect ;
	vector<Point>* _upper;
	vector<Point>* _lower;

public:
	TextLine();
	~TextLine();
	Point getUpper(int index);
	Point getLower(int index);
	void setPoints(Point upper,Point lower);
	void setRect(int x,int y,int height,int width);
	Rect getRect();
};

#endif 
