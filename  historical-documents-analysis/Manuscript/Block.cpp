#include "Block.h"


Block::Block(void)
{
}

void Block::removeTextLine(int index)
{
	_textlines.erase(_textlines.begin()+index-1);
}

Block::~Block(void)
{
	vector<TextLine*>::iterator it;
	for(it = _textlines.begin(); it!=_textlines.end();it++)
	{
		delete *it;
	}
}
