#ifndef MANUSCRIPTDOC_H
#define MANUSCRIPTDOC_H

#include <QObject>
#include <QVector>
#include "Manuscript.h"


class ManuscriptDoc : public QObject
{
	Q_OBJECT

public:
	ManuscriptDoc(QObject *parent);
	~ManuscriptDoc();
	void addPage(QString* path);
	void setManuscript(Manuscript* manscript);
	int getPageCount();
	QString* getPageAt(int index);


private:
	Manuscript* _manuscript;
	QVector<QString*>* _pagesPath;
	QString _dir;
};

#endif // MANUSCRIPTDOC_H
