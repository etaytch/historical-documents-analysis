#include "xmlreader.h"
using namespace tinyxml2;

XmlReader::XmlReader(QObject *parent)
	: QObject(parent)
{

}


int XmlReader::getFromXml(QString xmlFilePath, ProjectDoc& projDoc)
{
	tinyxml2::XMLDocument xmlDoc;
	if (xmlDoc.LoadFile( "dream.xml" )!=XML_NO_ERROR)
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
		const char* attr;
		if(elementName == "Name")
		{
			projDoc.setName(element->GetText());
		}
		else if(elementName == "Manuscripts")
		{
			for(tinyxml2::XMLElement* manElement = element->FirstChildElement("Manuscript"); 
				manElement != NULL; manElement = manElement->NextSiblingElement("Manuscript"))
			{
				attr = manElement->Attribute("name");
				if(attr != NULL)
				{
					//TODO
				}
				attr = manElement->Attribute("path");
				if(attr != NULL)
				{
					//TODO
				}
			}	
		}
		else
		{
			return XML_ERROR_IDENTIFYING_TAG;
		}
	}
	return XML_NO_ERROR;
}

int XmlReader::getFromXml(QString xmlFilePath, ManuscriptDoc& manDoc)
{
	return XML_NO_ERROR;
}

XmlReader::~XmlReader()
{

}
