#include "Page.h"
#include <opencv2/opencv.hpp>

Page::Page(void)
{
}

void Page::removeBlock(int index)
{
	_blocks.erase(_blocks.begin()+index-1);
}

void Page::loadMat()
{
	if((getMat().cols==0)&&(getMat().rows==0))
	{
		setMat(cv::imread(_name,1));
	}	
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

