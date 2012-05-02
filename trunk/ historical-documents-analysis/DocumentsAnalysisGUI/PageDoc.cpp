#include "PageDoc.h"
#include "Page.h"

PageDoc::PageDoc(QObject *parent)
{
	this->_copies = new QVector<PageDoc*>();
}

void PageDoc::setData(Page* page, QString* path)
{
	this->_page = page;
	this->_path = path;
}


PageDoc::~PageDoc(void)
{
	delete this->_page;
}

Page* PageDoc::getPage()
{
	return this->_page;
}

QString* PageDoc::getPath()
{
	return this->_path;
}

QVector<PageDoc*>* PageDoc::getCopies()
{
	return this->_copies;
}

void PageDoc::addCopy(PageDoc* copy)
{
	this->_copies->push_back(copy);
}