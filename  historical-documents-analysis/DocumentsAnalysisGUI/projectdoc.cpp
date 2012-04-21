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

int ProjectDoc::getManuscriptCount()
{
	return this->_manuscripts->size();
}


ManuscriptDoc* ProjectDoc::getManuscriptAt(int index)
{
	return this->_manuscripts->at(index);
}

QString ProjectDoc::getName()
{
	return name;
}

void ProjectDoc::setName(QString pname)
{
	name = pname;
}