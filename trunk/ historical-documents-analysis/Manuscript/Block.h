#ifndef __BLOCK_H_
#define __BLOKC_H_
#include "DImage.h" 
#include "TextLine.h"

class MANUSCRIPT_EXPORT Block : DImage {
protected:
	byte   _type   ;
	vector<TextLine*> _textlines ; 
public:
	Block(void);
	~Block(void);

	static const byte TEXT_BLOCK  = 1 ;
	static const byte IMAGE_BLOCK = 2 ;
	static const byte DRAW_BLOCK  = 3 ;
	
	void setType(byte t)   { _type = t ;    } 
	byte getType()         { return _type ; }
	void setTextLines (vector<TextLine*> textlines ) {_textlines = textlines;}
	vector<TextLine*> getTextLines (){return _textlines;}
	void addTextLine(TextLine* t){_textlines.push_back(t);}
	void removeTextLine(int index);

};

#endif 