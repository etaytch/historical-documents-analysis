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
	void addPage(QString path);
	void setManuscript(Manuscript* manscript);
	int getPageCount();
	QString getPageAt(int index);
	QString getManDirPath();
	void setManDirPath(QString manDir);
	QString getManXmlPath();
	void setManXmlPath(QString manXml);


private:
	Manuscript* _manuscript;
	QVector<QString>* _pagesPath;
	QString _manDirPath;
	QString _manXmlPath;

};

#endif // MANUSCRIPTDOC_H
