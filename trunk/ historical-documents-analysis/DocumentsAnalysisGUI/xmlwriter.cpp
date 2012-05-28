#include "xmlwriter.h"

void XmlWriter::saveToFile(ProjectDoc& project)
{

	tinyxml2::XMLDocument xmlDoc;
	/*
	xmlDoc.fir

	TiXmlDocument doc;
    TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "", "" );
    doc.LinkEndChild( decl );
    
    TiXmlElement * element = new TiXmlElement( "Hello" );
    doc.LinkEndChild( element );
    
    TiXmlText * text = new TiXmlText( "World" );
    element->LinkEndChild( text );
    
    dump_to_stdout( &doc );
    doc.SaveFile( "madeByHand2.xml" );

	qDebug()<<project.getName();
	QList<QString> keys = project.getManuscripts().keys();

	for(int i=0;i<keys.size();i++)
	{
		ManuscriptDoc md = project.getManuscripts().value(keys.at(i));		
		QString str = "key: "+keys.at(i)+":"+md.getTitle();
		qDebug()<<str;
	}
	*/
}