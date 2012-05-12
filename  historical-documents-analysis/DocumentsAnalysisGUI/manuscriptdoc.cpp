#include "manuscriptdoc.h"
#include "PageDoc.h"

ManuscriptDoc::ManuscriptDoc()
	:  Manuscript() 
{
}

ManuscriptDoc::~ManuscriptDoc()
{

}

QString ManuscriptDoc::getManDirPath()
{
	return _manDirPath;
}

QString ManuscriptDoc::getPagesDirPath()
{
	return  _manDirPath+PAGES;
}

QString ManuscriptDoc::getThumbnailsDirPath()
{
	return  _manDirPath+THUMBNAILS;
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
