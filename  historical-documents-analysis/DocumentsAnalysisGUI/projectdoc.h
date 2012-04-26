#ifndef PROJECTDOC_H
#define PROJECTDOC_H

#include <QObject>
#include <QMap>
#include <QPair>

#include "manuscriptdoc.h"

class ProjectDoc : public QObject
{
	Q_OBJECT

public:
	ProjectDoc(QObject *parent);
	~ProjectDoc();
	void addManuscript(ManuscriptDoc* man,QString name, QString path);
	int getManuscriptCount();
	QString getName();
	void setName(QString pname);
	ManuscriptDoc* getManuscriptAt(int index);
	void addManuscriptPath(QString name, QString path);
	QMap<QPair<QString,QString>,ManuscriptDoc*>* getManuscripts();

private:
	QMap<QPair<QString,QString>,ManuscriptDoc*>* _manuscripts;
	QString name;
};

#endif // PROJECTDOC_H
