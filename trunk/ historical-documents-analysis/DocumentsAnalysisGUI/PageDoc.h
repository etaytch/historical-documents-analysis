#ifndef PAGEDOC_H
#define PAGEDOC_H

#include "Page.h"
#include <QVector>
#include <QObject>
#include <QString>
#include <QMetaType>

class PageDoc : public QObject
{
	Q_OBJECT
public:
	PageDoc(QObject *parent=0);
	PageDoc(const PageDoc &p);
	PageDoc(Page* page,QString man,QObject *parent=0);
	void setPage(Page* page)				{_page = page;}
	Page* getPage()							{return _page;}
	void setManuscriptName(QString man)		{_man = man;}
	QString getManuscriptName()				{return _man;}
	virtual ~PageDoc(void){}

private:
	Page* _page;
	QString _man; 
};

Q_DECLARE_METATYPE(PageDoc);

#endif // PAGEDOC_H