#ifndef PAGEDOC_H
#define PAGEDOC_H

class Page;
class QString;
class PageDoc;
#include <QVector>
#include <QObject>

class PageDoc : public QObject
{
public:
	PageDoc(QObject *parent);
	void setData(Page* page, QString* path);
	~PageDoc(void);
	Page* getPage();
	QString* getPath();
	QVector<PageDoc*>* getCopies();
	void addCopy(PageDoc* copy);
private:
	QString* _path;
	Page* _page;
	QVector<PageDoc*>* _copies;
};

#endif // PAGEDOC_H