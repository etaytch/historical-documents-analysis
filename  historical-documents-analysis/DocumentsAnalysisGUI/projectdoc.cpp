#include "projectdoc.h"

ProjectDoc::ProjectDoc()
{
}

void ProjectDoc::addManuscriptPath(QString name, QString path)
{
	_paths.insert(name,path);
	_manuscripts.insert(name,ManuscriptDoc());
}

QMap<QString,QString>& ProjectDoc::getPaths()
{
	return _paths;
}

QMap<QString,ManuscriptDoc>& ProjectDoc::getManuscripts()
{
	return _manuscripts;
}

ProjectDoc::~ProjectDoc()
{
	_manuscripts.clear();
}