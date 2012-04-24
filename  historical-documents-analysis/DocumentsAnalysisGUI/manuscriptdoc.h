#ifndef MANUSCRIPTDOC_H
#define MANUSCRIPTDOC_H

#include <QObject>
#include <QVector>
#include <QString>
#include "Manuscript.h"

class ManuscriptDoc : public QObject , public Manuscript
{
	Q_OBJECT

private:
	QVector<QString>* _pagesPath;
	QString _manDirPath;
	QString _manXmlPath;
	QString _projectXmlPath;

public:
	ManuscriptDoc(QObject *parent);
	virtual ~ManuscriptDoc();
	void addPage(QString path);
	int getPageCount();
	QString getPageAt(int index);
	QString getManDirPath();
	void setManDirPath(QString manDir);
	QString getManXmlPath();
	void setManXmlPath(QString manXml);
	QString getProjectXmlPath();
	void setProjectXmlPath(QString projXml);
	
//manuscript getters setters
public:	

	QString getTitle(){return _title.c_str();}
	void setTitle(QString title){_title = title.toStdString();}
	QString getAuthor(){return _author.c_str();}
	void setAuthor(QString author){_author = author.toStdString();}
	QString getCopyist(){return _copyist.c_str();}
	void setCopyist(QString copyist){_copyist = copyist.toStdString();}
	QString getRegion(){return _region.c_str();}
	void setRegion(QString region){_region = region.toStdString();}
	QString getLanguage(){return _language.c_str();}
	void setLanguage(QString language){_language = language.toStdString();}
	QString getFontType(){return _font_type.c_str();}
	void setFontType(QString font_type){_font_type= font_type.toStdString();}
	
};

#endif // MANUSCRIPTDOC_H
