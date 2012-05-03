#include "Page.h"


Page::Page(void)
{
}

void Page::removeBlock(int index)
{
	_blocks.erase(_blocks.begin()+index-1);
}

Page::~Page(void)
{
}
