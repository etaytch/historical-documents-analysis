#include "PageDoc.h"

PageDoc::PageDoc(QObject *parent)
{
	_page = 0;
}

PageDoc::PageDoc(Page* page,QString man,QObject *parent)
{
	_page = page;
	_man = man;
}

PageDoc::PageDoc(const PageDoc &p)
{
	_page = p._page;
	_man = p._man;
}


