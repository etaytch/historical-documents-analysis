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
}
