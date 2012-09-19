#include "Page.h"
#include <opencv2/opencv.hpp>


void Page::removeSubPage(int index)
{
	_subpages.erase(_subpages.begin()+index-1);
}

void Page::loadMat(){
	if ( !_cached ){
		setMat(cv::imread(_name,1));
		_cached = true ;
	}	
}

Page::~Page(void){
	vector<SubPage*>::iterator siter;

	for(siter = _subpages.begin(); siter != _subpages.end(); siter++){
		delete *siter;
	}

	vector<Page*>::iterator piter ;
	for( piter = _pages.begin(); piter != _pages.end(); piter++)
	{
		delete *piter;
	}

}

