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
	_treeItem = p.getTreeItem();
}

TreeItem* PageDoc::getTreeItem() const
{
	return _treeItem;
}

void PageDoc::addWord(HDAQGraphicsTextItem* txtItem)
{
	_words.push_back(txtItem);
}

PageDoc& PageDoc::operator=(const PageDoc& p) {
	_page = p.getPage();
	_man = p.getManuscriptName();
	_treeItem = p.getTreeItem();
	return *this;
}