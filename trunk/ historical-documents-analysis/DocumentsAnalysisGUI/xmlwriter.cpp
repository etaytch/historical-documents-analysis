#include "xmlwriter.h"
using namespace tinyxml2;


int XmlWriter::saveProjectToXml(QString xmlFilePath, ProjectDoc& projDoc)
{
	tinyxml2::XMLDocument xmlDoc;
	XMLNode* projNode = xmlDoc.InsertEndChild(xmlDoc.NewElement("Project"));
	XMLElement* nameElement = xmlDoc.NewElement("Name");
	nameElement->InsertFirstChild(xmlDoc.NewText(projDoc.getName().toStdString().c_str()));
	projNode->InsertEndChild(nameElement);
	manuscripGen(projNode,xmlDoc,projDoc);	
	return xmlDoc.SaveFile(xmlFilePath.toStdString().c_str());
}

void XmlWriter::manuscripGen(tinyxml2::XMLNode* projNode, 
							 tinyxml2::XMLDocument& xmlDoc, 
							 ProjectDoc& projDoc)
{
	XMLNode* mansNode = projNode->InsertEndChild(xmlDoc.NewElement("Manuscripts"));

	int manCount = projDoc.getManuscriptCount();
	QMap<QString,QString> paths = projDoc.getPaths();		    //<name> ----> <Path>	

	for(int i = 0; i<manCount; i++)
	{
		XMLElement* manElement = xmlDoc.NewElement("Manuscript");
		manElement->SetAttribute("name",paths.keys()[i].toStdString().c_str());
		manElement->SetAttribute("path",paths.values()[i].toStdString().c_str());
		mansNode->InsertEndChild(manElement);
	}
}

int XmlWriter::saveManuscriptToXml(QString xmlFilePath, ManuscriptDoc& manDoc)
{

	tinyxml2::XMLDocument xmlDoc;
	XMLElement* element;

	XMLNode* manNode = xmlDoc.InsertEndChild(xmlDoc.NewElement("Manuscript"));
	element = xmlDoc.NewElement("ProjectPath");
	element ->InsertFirstChild(xmlDoc.NewText(manDoc.getProjectXmlPath().toStdString().c_str()));
	manNode->InsertEndChild(element);
	
	element = xmlDoc.NewElement("Title");
	element ->InsertFirstChild(xmlDoc.NewText(manDoc.getTitle().toStdString().c_str()));
	manNode->InsertEndChild(element);

	element = xmlDoc.NewElement("Author");
	element ->InsertFirstChild(xmlDoc.NewText(manDoc.getAuthor().toStdString().c_str()));
	manNode->InsertEndChild(element);
	
	element = xmlDoc.NewElement("Copyist");
	element ->InsertFirstChild(xmlDoc.NewText(manDoc.getCopyist().toStdString().c_str()));
	manNode->InsertEndChild(element);

	element = xmlDoc.NewElement("Region");
	element ->InsertFirstChild(xmlDoc.NewText(manDoc.getRegion().toStdString().c_str()));
	manNode->InsertEndChild(element);

	element = xmlDoc.NewElement("Language");
	element ->InsertFirstChild(xmlDoc.NewText(manDoc.getLanguage().toStdString().c_str()));
	manNode->InsertEndChild(element);

	element = xmlDoc.NewElement("FontType");
	element ->InsertFirstChild(xmlDoc.NewText(manDoc.getFontType().toStdString().c_str()));
	manNode->InsertEndChild(element);

	element = xmlDoc.NewElement("DirectoryPath");
	element ->InsertFirstChild(xmlDoc.NewText(manDoc.getManDirPath().toStdString().c_str()));
	manNode->InsertEndChild(element);

	element = xmlDoc.NewElement("Pages");
	XMLNode* pagesNode = manNode ->InsertEndChild(element);
	element->SetAttribute("count",manDoc.getPages().size());
	element->SetAttribute("path",manDoc.getPagesDirPath().toStdString().c_str());
	pageGen(pagesNode,xmlDoc,manDoc);
	return xmlDoc.SaveFile(xmlFilePath.toStdString().c_str());
}

void XmlWriter::pageGen(tinyxml2::XMLNode* node, 
						tinyxml2::XMLDocument& xmlDoc, 
						ManuscriptDoc& manDoc)
{
	XMLElement* element;
	vector<Page*>::iterator pageIter;

	vector<Page*> pages = manDoc.getPages();
	for(pageIter = pages.begin(); pageIter!=pages.end();pageIter++)
	{
		element = xmlDoc.NewElement("Page");
		XMLNode* pageNode = node->InsertEndChild(element);
		element->SetAttribute("index",(*pageIter)->getIndex());
		element->SetAttribute("path",(*pageIter)->getName().c_str());
		element->SetAttribute("active",(*pageIter)->isActive());
		blockGen(pageNode,xmlDoc,*pageIter); 
		pageGen(pageNode,xmlDoc,*pageIter);
	}
}

void XmlWriter::pageGen(tinyxml2::XMLNode* node, tinyxml2::XMLDocument& xmlDoc, Page* parentPage)
{
	XMLElement* element;
	vector<Page*>::iterator pageIter;

	vector<Page*> pages = parentPage->getPages();
	for(pageIter = pages.begin(); pageIter!=pages.end();pageIter++)
	{
		element = xmlDoc.NewElement("Page");
		XMLNode* pageNode = node->InsertEndChild(element);
		element->SetAttribute("index",(*pageIter)->getIndex());
		element->SetAttribute("path",(*pageIter)->getName().c_str());
		element->SetAttribute("active",(*pageIter)->isActive());

		blockGen(pageNode,xmlDoc,*pageIter); 
		pageGen(pageNode,xmlDoc,*pageIter);
	}
}

void XmlWriter::blockGen(tinyxml2::XMLNode* node, tinyxml2::XMLDocument& xmlDoc, Page* page)
{
	XMLElement* element;
	vector<SubPage*>::iterator blockIter;

	vector<SubPage*> blocks = page->getBlocks();
	for(blockIter = blocks.begin(); blockIter!=blocks.end();blockIter++)
	{
		element = xmlDoc.NewElement("SubPage");
		XMLNode* blockNode = node->InsertEndChild(element);
		element->SetAttribute("type",(int)(*blockIter)->getType());
		textLineGen(blockNode,xmlDoc,*blockIter);
	}
}

void XmlWriter::textLineGen(tinyxml2::XMLNode* node, tinyxml2::XMLDocument& xmlDoc, Block* block)
{

	XMLElement* element;
	vector<TextLine*>::iterator textLineIter;

	vector<TextLine*> tLines = block->getTextLines();
	for(textLineIter = tLines.begin(); textLineIter!=tLines.end();textLineIter++)
	{
		element = xmlDoc.NewElement("TextLine");
		XMLNode* tLineNode = node->InsertEndChild(element);
		rectGen(tLineNode,xmlDoc,*textLineIter);
		upperPointsGen(tLineNode,xmlDoc,*textLineIter);
		lowerPointsGen(tLineNode,xmlDoc,*textLineIter);
	}
}

void XmlWriter::rectGen(tinyxml2::XMLNode* node, tinyxml2::XMLDocument& xmlDoc, TextLine* textline)
{

	XMLElement* element;
	element = xmlDoc.NewElement("Rect");
	element->SetAttribute("x",textline->getRect().x);
	element->SetAttribute("y",textline->getRect().y);
	element->SetAttribute("w",textline->getRect().width);
	element->SetAttribute("h",textline->getRect().height);
	node->InsertEndChild(element);
}

void XmlWriter::upperPointsGen(tinyxml2::XMLNode* node, tinyxml2::XMLDocument& xmlDoc, TextLine* textline)
{
	XMLElement* element;
	vector<cv::Point>::iterator pointIter;


	element = xmlDoc.NewElement("UpperPoints");
	XMLNode* pointsNode = node->InsertEndChild(element);

	vector<cv::Point>* points = textline->getUpperPoints();
	for(pointIter = points->begin(); pointIter!=points->end();pointIter++)
	{
		element = xmlDoc.NewElement("Point");
		element->SetAttribute("x",(*pointIter).x);
		element->SetAttribute("y",(*pointIter).y);
		pointsNode->InsertEndChild(element);
	}

}

void XmlWriter::lowerPointsGen(tinyxml2::XMLNode* node, tinyxml2::XMLDocument& xmlDoc, TextLine* textline)
{

	XMLElement* element;
	vector<cv::Point>::iterator pointIter;


	element = xmlDoc.NewElement("LowerPoints");
	XMLNode* pointsNode = node->InsertEndChild(element);

	vector<cv::Point>* points = textline->getLowerPoints();
	for(pointIter = points->begin(); pointIter!=points->end();pointIter++)
	{
		element = xmlDoc.NewElement("Point");
		element->SetAttribute("x",(*pointIter).x);
		element->SetAttribute("y",(*pointIter).y);
		pointsNode->InsertEndChild(element);
	}
}
