#include "manuscriptdoc.h"

ManuscriptDoc::ManuscriptDoc(QObject *parent)
	: QObject(parent)
{
	_pagesPath = new QVector<QString>();
	_manuscript = 0;
}

ManuscriptDoc::~ManuscriptDoc()
{
	delete _pagesPath;
	delete _manuscript;
}

void ManuscriptDoc::addPage(QString path)
{
	_pagesPath->append(path);
}

void ManuscriptDoc::setManuscript(Manuscript* manuscript)
{
	_manuscript = manuscript;
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

void ManuscriptDoc::setManXmlPath(QString manXml)
{
	_manXmlPath = manXml;
}
