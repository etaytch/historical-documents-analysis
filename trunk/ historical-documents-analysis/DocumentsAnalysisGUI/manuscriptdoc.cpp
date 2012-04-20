#include "manuscriptdoc.h"

ManuscriptDoc::ManuscriptDoc(QObject *parent)
	: QObject(parent)
{
	this->_pagesPath = new QVector<QString*>();
	this->_manuscript = 0;
}

ManuscriptDoc::~ManuscriptDoc()
{
	delete this->_pagesPath;
	delete this->_manuscript;
}

void ManuscriptDoc::addPage(QString* path)
{
	this->_pagesPath->append(path);
}

void ManuscriptDoc::setManuscript(Manuscript* manuscript)
{
	this->_manuscript = manuscript;
}

int ManuscriptDoc::getPageCount()
{
	return this->_pagesPath->size();
}

QString* ManuscriptDoc::getPageAt(int index)
{
	return this->_pagesPath->at(index);
}