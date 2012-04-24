#include "xmlreader.h"
using namespace tinyxml2;

XmlReader::XmlReader(QObject *parent)
	: QObject(parent)
{

}


int XmlReader::getFromXml(QString xmlFilePath, ProjectDoc& projDoc)
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

int XmlReader::getFromXml(QString xmlFilePath, ManuscriptDoc& manDoc)
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
	for(tinyxml2::XMLElement* pageElement = element->FirstChildElement("Page"); 
		pageElement != NULL; pageElement = pageElement->NextSiblingElement("Page"))
	{
		const char* indexAttr;
		const char* pathAttr;
		//page init
		indexAttr = pageElement->Attribute("index");
		if(indexAttr != NULL)
		{
			//page index init 
		}
		pathAttr = pageElement->Attribute("path");
		if(indexAttr != NULL)
		{
			//page path init 					
		}
		blockParsing(pageElement,manDoc);
	}
}

void XmlReader::blockParsing(tinyxml2::XMLElement* pageElement,ManuscriptDoc& manDoc)
{
	for(tinyxml2::XMLElement* blockElement = pageElement->FirstChildElement("Block"); 
		blockElement != NULL; blockElement = blockElement->NextSiblingElement("Block"))
	{
		const char* typeAttr;
		//block init
		typeAttr = pageElement->Attribute("type");
		if(typeAttr != NULL)
		{
			//block type init
		}
		textLineParsing(blockElement,manDoc);
		
	}
}

void XmlReader::textLineParsing(tinyxml2::XMLElement* blockElement,ManuscriptDoc& manDoc)
{
	for(tinyxml2::XMLElement* textLineElement = blockElement->FirstChildElement("TextLine"); 
		textLineElement != NULL; textLineElement = textLineElement->NextSiblingElement("TextLine"))
	{
		for(tinyxml2::XMLElement* element = textLineElement ->FirstChildElement(); 
			element != NULL; element = element->NextSiblingElement())
		{
			string elementName = element->Value();
			if(elementName == "Rect")
			{
				rectParsing(element,manDoc);
			}
			else if(elementName == "UpperPoints")
			{
				upperPointsParsing(element,manDoc);
			}
			else if(elementName == "LowerPoints")
			{
				lowerPointsParsing(element,manDoc);
			}
		}
	}
}

void XmlReader::rectParsing(tinyxml2::XMLElement* element,ManuscriptDoc& manDoc)
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
					//textline rect init
				}
			}
		}
	}
}
void XmlReader::upperPointsParsing(tinyxml2::XMLElement* element,ManuscriptDoc& manDoc)
{
	for(tinyxml2::XMLElement* pointElement = element ->FirstChildElement("Point"); 
		pointElement != NULL; pointElement= pointElement->NextSiblingElement("Point"))
	{
		const char* xAttr;
		const char* yAttr;

		xAttr = element->Attribute("x");
		if(xAttr != NULL)
		{
			yAttr = element->Attribute("y");
			if(yAttr != NULL)
			{
				//text line upper point init
			}
		}
	}
}


void XmlReader::lowerPointsParsing(tinyxml2::XMLElement* element,ManuscriptDoc& manDoc)
{
	for(tinyxml2::XMLElement* pointElement = element ->FirstChildElement("Point"); 
		pointElement != NULL; pointElement= pointElement->NextSiblingElement("Point"))
	{
		const char* xAttr;
		const char* yAttr;

		xAttr = element->Attribute("x");
		if(xAttr != NULL)
		{
			yAttr = element->Attribute("y");
			if(yAttr != NULL)
			{
				//text line upper point init
			}
		}
	}
}

XmlReader::~XmlReader()
{

}
