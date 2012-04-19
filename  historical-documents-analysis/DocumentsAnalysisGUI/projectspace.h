#ifndef PROJECTSPACE_H
#define PROJECTSPACE_H

#include <QObject>
#include "manuscriptdoc.h"

class ProjectSpace : public QObject
{
	Q_OBJECT

private:
	QVector<ManuscriptDoc>* _manuscripts; 

public:
	ProjectSpace(QObject *parent);
	~ProjectSpace();

private:
	
};

#endif // PROJECTSPACE_H
