#include "projectdoc.h"

ProjectDoc::ProjectDoc()
{
}

void ProjectDoc::addManuscriptPath(QString name, QString path)
{
	_paths.insert(name,path);
	_manuscripts.insert(name,ManuscriptDoc());
}

void ProjectDoc::removeManuscript(QString name)
{
	_paths.remove(name);
	_manuscripts.remove(name);
}

int ProjectDoc::renameManuscript(QString oldName,QString newName)
{
	if (!_paths.contains(newName))
	{
		_paths[newName] = _paths[oldName];
		_manuscripts[newName] = _manuscripts[oldName];
		_paths.remove(oldName);
		_manuscripts.remove(oldName);
		_manuscripts[newName].setTitle(newName);
	}
	else
	{
		return UNABLE_TO_RENAME;
	}
	return NO_PROJ_ERROR;
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