#ifndef XMLWRITER_H
#define XMLWRITER_H

#include <QObject>
#include "ProjectDoc.h"
#include "tinyxml2.h"
//#include "stdafx.h"

class XmlWriter : public QObject
{
	Q_OBJECT

public:
	static int saveProjectToXml(QString xmlFilePath, ProjectDoc& projDoc);
	static int saveManuscriptToXml(QString xmlFilePath, ManuscriptDoc& manDoc);

private:
	static void manuscripGen(tinyxml2::XMLElement* element,ProjectDoc& projDoc);
	static void pageGen(tinyxml2::XMLElement* element,ManuscriptDoc& manDoc);
	static void pageGen(tinyxml2::XMLElement* element,Page* page,ManuscriptDoc& manDoc);
	static void blockGen(tinyxml2::XMLElement* pageElement,Page* page);
	static void textLineGen(tinyxml2::XMLElement* blockElement,Block* block);
	static void rectGen(tinyxml2::XMLElement* element,TextLine* textline);
	static void upperPointsGen(tinyxml2::XMLElement* element,TextLine* textline);
	static void lowerPointsGen(tinyxml2::XMLElement* element,TextLine* textline);	
};

#endif // XMLWRITER_H
