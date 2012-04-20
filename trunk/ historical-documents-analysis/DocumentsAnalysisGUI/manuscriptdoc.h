#ifndef MANUSCRIPTDOC_H
#define MANUSCRIPTDOC_H

#include <QObject>
#include <QVector>
#include "Manuscript.h"


class ManuscriptDoc : public QObject
{
	Q_OBJECT

private:
	Manuscript _manuscript;
	QVector<QString>* _pagesPath;  //need to be tree
	QString _dir;

	


public:
	ManuscriptDoc(QObject *parent);

	~ManuscriptDoc();

private:
	
};

#endif // MANUSCRIPTDOC_H
