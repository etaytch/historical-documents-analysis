#ifndef XMLREADER_H
#define XMLREADER_H

#include <QObject>
#include "projectdoc.h"
#include "manuscriptdoc.h"
#include "tinyxml2.h"

class XmlReader : public QObject
{
	Q_OBJECT

public:
	XmlReader(QObject *parent);
	static int getFromXml(QString xmlFilePath, ProjectDoc& projDoc);
	static int getFromXml(QString xmlFilePath, ManuscriptDoc& manDoc);
	~XmlReader();

private:
	
};

#endif // XMLREADER_H
