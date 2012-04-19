#ifndef MANUSCRIPTDOC_H
#define MANUSCRIPTDOC_H

#include <QObject>
#include <QVector>


class ManuscriptDoc : public QObject
{
	Q_OBJECT

private:
	
	int _size;
	QVector<QString>* _pagesPath;  //need to be tree
	QString _dir;
	QString _name;
	


public:
	ManuscriptDoc(QObject *parent);
	~ManuscriptDoc();

private:
	
};

#endif // MANUSCRIPTDOC_H
