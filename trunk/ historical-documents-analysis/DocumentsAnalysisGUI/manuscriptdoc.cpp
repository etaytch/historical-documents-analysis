#include "manuscriptdoc.h"

ManuscriptDoc::ManuscriptDoc(QObject *parent)
	: QObject(parent), Manuscript() 
{
	_pagesPath = new QVector<QString>();
}

ManuscriptDoc::~ManuscriptDoc()
{
	delete _pagesPath;
}

void ManuscriptDoc::addPage(QString path)
{
	_pagesPath->append(path);
}


int ManuscriptDoc::getPageCount()
{
	return _pagesPath->size();
}

QString ManuscriptDoc::getPageAt(int index)
{
	return _pagesPath->at(index);
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
