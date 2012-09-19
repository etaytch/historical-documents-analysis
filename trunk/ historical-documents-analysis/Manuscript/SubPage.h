#ifndef __SUBPAGE_H_
#define __SUBPAGE_H_
#include <vector>
#include <opencv/cv.h>
#include <opencv2/core/core.hpp>
#include "manuscript_global.h"
#include "TextLine.h"
#include "ConnectedComponent.h"

using namespace cv ;

class MANUSCRIPT_EXPORT SubPage {
protected:
	Mat    _image  ;
	byte   _type   ;
	byte   _status ;
	byte   _layout ;
	vector<TextLine*>            _textlines  ; 
	vector<ConnectedComponent*>  _components ;

public:
	SubPage(void);
	~SubPage(void);

	void setMat(Mat& mat)    { _image = mat ; } 
	Mat  getMat()            { return _image ; }

	// Block status 
	static const byte INCLUDE_TEXTLINES  = 0x01 ;
	static const byte INCLUDE_COMPONENTS = 0x02 ;
	// Block type 
	static const byte TYPE_TEXT_BLOCK  = 1 ;
	static const byte TYPE_IMAGE_BLOCK = 2 ;
	static const byte TYPE_DRAW_BLOCK  = 3 ;
	// Layout options 
	static const byte LAYOUT_MAIN   = 1 ;
	static const byte LAYOUT_MARGIN = 2 ;
	
	void setType(byte t)   { _type = t ;    } 
	byte getType()         { return _type ; }

	bool textLinesIncluded()                         { return _status & INCLUDE_TEXTLINES ; }
	bool componentsIncluded()                        { return _status & INCLUDE_COMPONENTS ; }

	void setTextLinesIncluded()                      { _status &= INCLUDE_TEXTLINES ; }
	void setComponentsIncluded()                     { _status &= INCLUDE_COMPONENTS ; }

	void setTextLines (vector<TextLine*> textlines ) {_textlines = textlines;}
	vector<TextLine*> getTextLines()                 {return _textlines;}
	void addTextLine(TextLine* t)                    {_textlines.push_back(t);}
	void removeTextLine(int index);

};

#endif 
