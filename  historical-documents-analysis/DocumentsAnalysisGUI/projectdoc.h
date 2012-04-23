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
	void addManuscript(ManuscriptDoc* manuscript);
	int getManuscriptCount();
	QString getName();
	void setName(QString pname);
	ManuscriptDoc* getManuscriptAt(int index);
	void addManuscriptPath(QString name, QString path);


private:
	QMap<QPair<QString,QString>,ManuscriptDoc*>* _manuscripts;
	QString name;
};

#endif // PROJECTDOC_H
