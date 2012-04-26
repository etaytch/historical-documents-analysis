#include "manuscriptdoc.h"
#include "PageDoc.h"

ManuscriptDoc::ManuscriptDoc(QObject *parent)
	: QObject(parent), Manuscript() 
{
	//_pagesPath = new QVector<QString>();
	_pages = new QVector<PageDoc*>();
}

ManuscriptDoc::~ManuscriptDoc()
{
	delete _pages;
}

void ManuscriptDoc::addPage(PageDoc* page)
{
	_pages->append(page);
}


int ManuscriptDoc::getPageCount()
{
	return _pages->size();
}

PageDoc* ManuscriptDoc::getPageAt(int index)
{
	return _pages->at(index);
}

QString ManuscriptDoc::getManDirPath()
{
	return _manDirPath;
}

void ManuscriptDoc::setManDirPath(QString manDir)
{
	_manDirPath=manDir;
}

QString ManuscriptDoc::getManXmlPath()
{
	return _manXmlPath;
}

void ManuscriptDoc::setProjectXmlPath(QString projXml)
{
	_projectXmlPath = projXml;
}

QString ManuscriptDoc::getProjectXmlPath()
{
	return _projectXmlPath; 
}

void ManuscriptDoc::setManXmlPath(QString manXml)
{
	_manXmlPath = manXml;
}

QVector<PageDoc*>* ManuscriptDoc::getPages()
{
	return this->_pages;
}