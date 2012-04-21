#ifndef PROJECTDOC_H
#define PROJECTDOC_H

#include <QObject>
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


private:
	QVector<ManuscriptDoc*>* _manuscripts; 
	QString name;
};

#endif // PROJECTDOC_H
