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
		const char* nameAttr;
		const char* pathAttr;

		if(elementName == "Name")
		{
			projDoc.setName(element->GetText());
		}
		else if(elementName == "Manuscripts")
		{
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
