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
	vector<Block*>::iterator blockIter;
	vector<Page*>::iterator pageIterator;

	for(blockIter = _blocks.begin(); blockIter!=_blocks.end(); blockIter++)
	{
		delete *blockIter;
	}

	for(pageIterator = _pages.begin(); pageIterator!=_pages.end(); pageIterator++)
	{
		delete *pageIterator;
	}

}

