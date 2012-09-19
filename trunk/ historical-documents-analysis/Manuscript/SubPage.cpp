#include "SubPage.h"


SubPage::SubPage(void)
{ }

void SubPage::removeTextLine(int index)
{
	_textlines.erase(_textlines.begin()+index-1);
}

SubPage::~SubPage(void)
{
	vector<TextLine*>::iterator it;
	for(it = _textlines.begin(); it!=_textlines.end();it++)
	{
		delete *it;
	}
}
