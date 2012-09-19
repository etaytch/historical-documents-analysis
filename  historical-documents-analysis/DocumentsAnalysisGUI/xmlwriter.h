#ifndef XMLWRITER_H
#define XMLWRITER_H

#include <QObject>
#include "ProjectDoc.h"
#include "tinyxml2.h"

class XmlWriter : public QObject
{
	Q_OBJECT

public:
	static int saveProjectToXml(QString xmlFilePath, ProjectDoc& projDoc);
	static int saveManuscriptToXml(QString xmlFilePath, ManuscriptDoc& manDoc);

private:
	static void manuscripGen(tinyxml2::XMLNode* projNode, tinyxml2::XMLDocument& xmlDoc, ProjectDoc& projDoc);
	
	static void pageGen(tinyxml2::XMLNode* node, tinyxml2::XMLDocument& xmlDoc, ManuscriptDoc& manDoc);
	static void pageGen(tinyxml2::XMLNode* node, tinyxml2::XMLDocument& xmlDoc, Page* page);
	static void blockGen(tinyxml2::XMLNode* node, tinyxml2::XMLDocument& xmlDoc, Page* page);
	static void textLineGen(tinyxml2::XMLNode* node, tinyxml2::XMLDocument& xmlDoc, SubPage* block);
	static void rectGen(tinyxml2::XMLNode* node, tinyxml2::XMLDocument& xmlDoc, TextLine* textline);
	static void upperPointsGen(tinyxml2::XMLNode* node, tinyxml2::XMLDocument& xmlDoc, TextLine* textline);
	static void lowerPointsGen(tinyxml2::XMLNode* node, tinyxml2::XMLDocument& xmlDoc, TextLine* textline);	
};

#endif // XMLWRITER_H
