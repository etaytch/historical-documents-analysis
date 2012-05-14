#ifndef PROJECTDOC_H
#define PROJECTDOC_H

#include <QObject>
#include <QMap>
#include <QPair>
#include <QMessageBox>
#include "manuscriptdoc.h"

enum PROJ_ERR { 
	NO_PROJ_ERROR =0,
	UNABLE_TO_RENAME
};

class ProjectDoc 
{

public:
	ProjectDoc();
	virtual ~ProjectDoc();
	int getManuscriptCount()							{return _manuscripts.size();}
	QString getName()									{return _name;}
	void setName(QString name)							{_name = name;}
	ManuscriptDoc& getManuscriptAt(int index)			{return *(_manuscripts.begin()+index);}
	ManuscriptDoc& getManuscriptAt(QString manName)		{return _manuscripts[manName];}
	QString getPathAt(int index)						{return *(_paths.begin()+index);}
	QString getPathAt(QString manName)					{return _paths[manName];}
	void addManuscriptPath(QString name, QString path);
	void removeManuscript(QString name);
	int renameManuscript(QString oldName,QString newName);
	QMap<QString,ManuscriptDoc>& getManuscripts();
	QMap<QString,QString>& getPaths();


private:
	QMap<QString,ManuscriptDoc> _manuscripts;   //<name> ----> <manuscript>
	QMap<QString,QString>		_paths;		    //<name> ----> <Path>				
	QString _name;
};


#endif // PROJECTDOC_H
