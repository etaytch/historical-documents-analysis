#include "PageDoc.h"

PageDoc::PageDoc(QObject *parent)
{
	_page = 0;
}

PageDoc::PageDoc(Page* page,QString man,TreeItem* treeitem,QObject *parent)
{
	_page = page;
	_man = man;
	_treeItem=treeitem;
}

PageDoc::PageDoc(const PageDoc &p)
{
	_page = p._page;
	_man = p._man;
}

TreeItem* PageDoc::getTreeItem()
{
	return _treeItem;
}

