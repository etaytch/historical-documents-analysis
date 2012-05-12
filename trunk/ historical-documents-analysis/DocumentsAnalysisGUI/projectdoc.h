#ifndef PROJECTDOC_H
#define PROJECTDOC_H

#include <QObject>
#include <QMap>
#include <QPair>

#include "manuscriptdoc.h"

class ProjectDoc 
{

public:
	ProjectDoc();
	virtual ~ProjectDoc();
	void addManuscript(QString name, QString path);
	int getManuscriptCount()							{return _manuscripts.size();}
	QString getName()									{return _name;}
	void setName(QString name)							{_name = name;}
	ManuscriptDoc& getManuscriptAt(int index)			{return *(_manuscripts.begin()+index);}
	ManuscriptDoc& getManuscriptAt(QString manName)		{return _manuscripts[manName];}
	QString getPathAt(int index)						{return *(_paths.begin()+index);}
	QString getPathAt(QString manName)					{return _paths[manName];}
	void addManuscriptPath(QString name, QString path);
	QMap<QString,ManuscriptDoc>& getManuscripts();
	QMap<QString,QString>& getPaths();


private:
	QMap<QString,ManuscriptDoc> _manuscripts;   //<name> ----> <manuscript>
	QMap<QString,QString>		_paths;		    //<name> ----> <Path>				
	QString _name;
};

#endif // PROJECTDOC_H
