#ifndef PAGEDOC_H
#define PAGEDOC_H

#include "Page.h"
#include <QVector>
#include <QObject>
#include <QString>
#include <QMetaType>
#include "treeitem.h"
#include "HDAQGraphicsTextItem.h"

class PageDoc : public QObject
{
	Q_OBJECT
public:
	PageDoc(QObject *parent=0);
	PageDoc(const PageDoc &p);
	PageDoc(Page* page,QString man,TreeItem* treeitem, QObject *parent=0);

	void setPage(Page* page)				{_page = page;}
	Page* getPage()	const					{return _page;}
	void setManuscriptName(QString man)		{_man = man;}
	QString getManuscriptName()	const		{return _man;}
	TreeItem* getTreeItem() const;
	void addWord(HDAQGraphicsTextItem*);
	virtual PageDoc& operator=(const PageDoc&);
	virtual ~PageDoc(void){}

private:
	Page* _page;
	QString _man; 
	TreeItem* _treeItem;
	QVector<HDAQGraphicsTextItem*> _words;
};

Q_DECLARE_METATYPE(PageDoc);

#endif // PAGEDOC_H