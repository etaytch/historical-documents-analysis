#include "projectdoc.h"

ProjectDoc::ProjectDoc(QObject *parent)
	: QObject(parent)
{
	this->_manuscripts = new QVector<ManuscriptDoc*>();
}

ProjectDoc::~ProjectDoc()
{
	delete this->_manuscripts;
}

void ProjectDoc::addManuscript(ManuscriptDoc* manuscript)
{
	this->_manuscripts->append(manuscript);
}