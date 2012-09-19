#ifndef XMLREADER_H
#define XMLREADER_H


#include <QObject>
#include "projectdoc.h"
#include "tinyxml2.h"



class XmlReader : public QObject
{
	Q_OBJECT

public:
	static int getProjectFromXml(QString xmlFilePath, ProjectDoc& projDoc);
	static int getManuscriptFromXml(QString xmlFilePath, ManuscriptDoc& manDoc);

private:
	static void manuscripParsing(tinyxml2::XMLElement* element,ProjectDoc& projDoc);
	static void pageParsing(tinyxml2::XMLElement* element,ManuscriptDoc& manDoc);
	static void pageParsing(tinyxml2::XMLElement* element,Page* page,ManuscriptDoc& manDoc);
	static void blockParsing(tinyxml2::XMLElement* pageElement,Page* page);
	static void textLineParsing(tinyxml2::XMLElement* blockElement,SubPage* block);
	static void rectParsing(tinyxml2::XMLElement* element,TextLine* textline);
	static void upperPointsParsing(tinyxml2::XMLElement* element,TextLine* textline);
	static void lowerPointsParsing(tinyxml2::XMLElement* element,TextLine* textline);	
};

#endif // XMLREADER_H
