#include "projectdoc.h"

ProjectDoc::ProjectDoc(QObject *parent)
	: QObject(parent)
{
	_manuscripts = new QMap<QPair<QString, QString>,ManuscriptDoc*>();
}

int ProjectDoc::getManuscriptCount()
{
	return _manuscripts->size();
}

ManuscriptDoc* ProjectDoc::getManuscriptAt(int index)
{
	return *(_manuscripts->begin()+index);
}

QString ProjectDoc::getName()
{
	return name;
}

void ProjectDoc::setName(QString pname)
{
	name = pname;
}

void ProjectDoc::addManuscriptPath(QString name, QString path)
{
	_manuscripts->insert(QPair<QString,QString>(name,path),0);
}

ProjectDoc::~ProjectDoc()
{
	QMap<QPair<QString,QString>,ManuscriptDoc*>::iterator iter;
	for(iter=_manuscripts->begin();iter!=_manuscripts->end();iter++)
	{
		delete (iter.value());
	}
	_manuscripts->clear();
}