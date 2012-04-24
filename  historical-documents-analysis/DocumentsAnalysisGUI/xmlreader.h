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
	virtual ~XmlReader();

private:
	static void manuscripParsing(tinyxml2::XMLElement* element,ProjectDoc& projDoc);
	static void pageParsing(tinyxml2::XMLElement* element,ManuscriptDoc& manDoc);
	static void blockParsing(tinyxml2::XMLElement* pageElement,ManuscriptDoc& manDoc);
	static void textLineParsing(tinyxml2::XMLElement* blockElement,ManuscriptDoc& manDoc);
	static void rectParsing(tinyxml2::XMLElement* element,ManuscriptDoc& manDoc);
	static void upperPointsParsing(tinyxml2::XMLElement* element,ManuscriptDoc& manDoc);
	static void lowerPointsParsing(tinyxml2::XMLElement* element,ManuscriptDoc& manDoc);
	
};

#endif // XMLREADER_H
