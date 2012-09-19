#include "xmlreader.h"
using namespace tinyxml2;


int XmlReader::getProjectFromXml(QString xmlFilePath, ProjectDoc& projDoc)
{
	tinyxml2::XMLDocument xmlDoc;
	if (xmlDoc.LoadFile(xmlFilePath.toStdString().c_str())!=XML_NO_ERROR)
	{
		return xmlDoc.ErrorID(); 
	}
	
	XMLElement* root = xmlDoc.FirstChildElement("Project");
	if(root == NULL)
	{
		return XML_ERROR_ELEMENT_MISMATCH;
	}

	for(tinyxml2::XMLElement* element = root->FirstChildElement(); 
		element != NULL; element = element->NextSiblingElement())
	{
		string elementName = element->Value();
		if(elementName == "Name")
		{
			projDoc.setName(element->GetText());
		}
		else if(elementName == "Manuscripts")
		{
			manuscripParsing(element,projDoc);	
		}
		else
		{
			return XML_ERROR_IDENTIFYING_TAG;
		}
	}
	return XML_NO_ERROR;
}

void XmlReader::manuscripParsing(tinyxml2::XMLElement* element,ProjectDoc& projDoc)
{
	const char* nameAttr;
	const char* pathAttr;

	for(tinyxml2::XMLElement* manElement = element->FirstChildElement("Manuscript"); 
		manElement != NULL; manElement = manElement->NextSiblingElement("Manuscript"))
	{
		nameAttr = manElement->Attribute("name");
		if(nameAttr != NULL)
		{
			pathAttr = manElement->Attribute("path");
			if(pathAttr != NULL)
			{
				projDoc.addManuscriptPath(nameAttr,pathAttr);
			}
		}
	}
}

int XmlReader::getManuscriptFromXml(QString xmlFilePath, ManuscriptDoc& manDoc)
{
	tinyxml2::XMLDocument xmlDoc;	
	if (xmlDoc.LoadFile(xmlFilePath.toStdString().c_str())!=XML_NO_ERROR)
	{
		return xmlDoc.ErrorID(); 
	}
	XMLElement* root = xmlDoc.FirstChildElement("Manuscript");
	if(root == NULL)
	{
		return XML_ERROR_ELEMENT_MISMATCH;
	}

	for(tinyxml2::XMLElement* element = root->FirstChildElement(); 
		element != NULL; element = element->NextSiblingElement())
	{
		string elementName = element->Value();
		if(elementName == "ProjectPath")
		{
			manDoc.setProjectXmlPath(element->GetText());
		}
		else if(elementName == "Title")
		{
			manDoc.setTitle(element->GetText());
		}
		else if(elementName == "Author")
		{
			manDoc.setAuthor(element->GetText());
		}
		else if(elementName == "Copyist")
		{
			manDoc.setCopyist(element->GetText());
		}
		else if(elementName == "Region")
		{
			manDoc.setRegion(element->GetText());
		}
		else if(elementName == "Language")
		{
			manDoc.setLanguage(element->GetText());
		}
		else if(elementName == "FontType")
		{
			manDoc.setFontType(element->GetText());
		}
		else if(elementName == "DirectoryPath")
		{
			manDoc.setManDirPath(element->GetText());
		}
		else if(elementName == "Pages")
		{
			pageParsing(element,manDoc);		
		}
		else
		{
			return XML_ERROR_IDENTIFYING_TAG;
		}
	}
	return XML_NO_ERROR;
}

void XmlReader::pageParsing(tinyxml2::XMLElement* element,ManuscriptDoc& manDoc)
{
	Page* page = 0;

	for(tinyxml2::XMLElement* pageElement = element->FirstChildElement("Page"); 
		pageElement != NULL; pageElement = pageElement->NextSiblingElement("Page"))
	{
		page = new Page(); 

		const char* indexAttr;
		const char* pathAttr;
		const char*	activeAttr;
		//page init
		indexAttr = pageElement->Attribute("index");
		if(indexAttr != NULL)
		{
			page->setIndex(atoi(indexAttr));		
		}
		pathAttr = pageElement->Attribute("path");
		if(indexAttr != NULL)
		{
			page->setName(pathAttr);
		}

		activeAttr = pageElement->Attribute("active");
		if(activeAttr != NULL)
		{
			page->setActiveState(atoi(activeAttr));
		}

		blockParsing(pageElement,page); 
		manDoc.addPage(page);
		pageParsing(pageElement,page,manDoc);
	}	
}

void XmlReader::pageParsing(tinyxml2::XMLElement* element,Page* parentPage,ManuscriptDoc& manDoc)
{
	Page* page = 0;

	for(tinyxml2::XMLElement* pageElement = element->FirstChildElement("Page"); 
		pageElement != NULL; pageElement = pageElement->NextSiblingElement("Page"))
	{
		page = new Page(); 

		const char* indexAttr;
		const char* pathAttr;
		const char*	activeAttr;
		//page init
		indexAttr = pageElement->Attribute("index");
		if(indexAttr != NULL)
		{
			page->setIndex(atoi(indexAttr));		
		}
		pathAttr = pageElement->Attribute("path");
		if(indexAttr != NULL)
		{
			page->setName(pathAttr);
		}
		activeAttr = pageElement->Attribute("active");
		if(activeAttr != NULL)
		{
			page->setActiveState(atoi(activeAttr));
		}
		blockParsing(pageElement,page); 
		parentPage->addPage(page);
		pageParsing(pageElement,page,manDoc);
	}	
}

void XmlReader::blockParsing(tinyxml2::XMLElement* pageElement,Page* page)
{
	

	for(tinyxml2::XMLElement* blockElement = pageElement->FirstChildElement("SubPage"); 
		blockElement != NULL; blockElement = blockElement->NextSiblingElement("SubPage"))
	{
		SubPage* sub_page = new SubPage();
		const char* typeAttr;
		typeAttr = blockElement->Attribute("type");
		if(typeAttr != NULL)
		{
			sub_page->setType(atoi(typeAttr));
		}
		textLineParsing(blockElement,sub_page);	
		page->addBlock(sub_page);
	}

	
}

void XmlReader::textLineParsing(tinyxml2::XMLElement* blockElement,Block* block)
{
	for(tinyxml2::XMLElement* textLineElement = blockElement->FirstChildElement("TextLine"); 
		textLineElement != NULL; textLineElement = textLineElement->NextSiblingElement("TextLine"))
	{
		TextLine* textline = new TextLine();
		for(tinyxml2::XMLElement* element = textLineElement ->FirstChildElement(); 
			element != NULL; element = element->NextSiblingElement())
		{
			string elementName = element->Value();
			if(elementName == "Rect")
			{
				rectParsing(element,textline);
			}
			else if(elementName == "UpperPoints")
			{
				upperPointsParsing(element,textline);
			}
			else if(elementName == "LowerPoints")
			{
				lowerPointsParsing(element,textline);
			}
		}
		block->addTextLine(textline);
	}
	
}

void XmlReader::rectParsing(tinyxml2::XMLElement* element,TextLine* textline)
{
	const char* xAttr;
	const char* yAttr;
	const char* wAttr;
	const char* hAttr;
	
	xAttr = element->Attribute("x");
	if(xAttr != NULL)
	{
		yAttr = element->Attribute("y");
		if(yAttr != NULL)
		{
			wAttr = element->Attribute("w");
			if(wAttr != NULL)
			{
				hAttr = element->Attribute("h");
				if(hAttr != NULL)
				{
					textline->setRect(atoi(xAttr),atoi(yAttr),atoi(wAttr),atoi(hAttr));
				}
			}
		}
	}
}

void XmlReader::upperPointsParsing(tinyxml2::XMLElement* element,TextLine* textline)
{
	for(tinyxml2::XMLElement* pointElement = element ->FirstChildElement("Point"); 
		pointElement != NULL; pointElement= pointElement->NextSiblingElement("Point"))
	{
		const char* xAttr;
		const char* yAttr;
		
		xAttr = pointElement->Attribute("x");
		if(xAttr != NULL)
		{
			yAttr = pointElement->Attribute("y");
			if(yAttr != NULL)
			{
				textline->setUpperPoint(atoi(xAttr),atoi(yAttr));
			}
		}
	}
}

void XmlReader::lowerPointsParsing(tinyxml2::XMLElement* element,TextLine* textline)
{
	for(tinyxml2::XMLElement* pointElement = element ->FirstChildElement("Point"); 
		pointElement != NULL; pointElement= pointElement->NextSiblingElement("Point"))
	{
		const char* xAttr;
		const char* yAttr;

		xAttr = pointElement->Attribute("x");
		if(xAttr != NULL)
		{
			yAttr = pointElement->Attribute("y");
			if(yAttr != NULL)
			{
				textline->setLowerPoint(atoi(xAttr),atoi(yAttr));
			}
		}
	}
}
