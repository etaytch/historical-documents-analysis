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
	static void saveToFile(ProjectDoc& project);	

private:	
};

#endif // XMLWRITER_H
