#include "treeviewmodel.h"
#include "projectdoc.h"
#include "manuscriptdoc.h"
#include "projectdoc.h"
#include "Page.h"
#include <cmath>
#include "PageDoc.h"

TreeViewModel::TreeViewModel(QObject *parent)
	: QStandardItemModel(parent)
{
	ProjectDoc* proj = new ProjectDoc(this);
	ManuscriptDoc* man = new ManuscriptDoc(this);
	man->setManDirPath("manPath");
	PageDoc* page = new PageDoc(this);
	page->setData(0, new QString("page1path") );
	man->addPage(page);
	PageDoc* copy = new PageDoc(this);
	copy->setData(0, new QString("page1copypath") );
	page->addCopy(copy);
	proj->addManuscript(man, "kaki1", man->getManDirPath());
	man = new ManuscriptDoc(this);
	man->setManDirPath("man2Path");
	page = new PageDoc(this);
	page->setData(0, new QString("page2path") );
	man->addPage(page);
	page = new PageDoc(this);
	page->setData(0, new QString("page3path") );
	man->addPage(page);
	proj->addManuscript(man, "kaki2", man->getManDirPath());
	setData(proj);
}

TreeViewModel::~TreeViewModel()
{
}

QVariant TreeViewModel::headerData ( int section, Qt::Orientation orientation, int role ) const
{
if (orientation == Qt::Horizontal) {
if (role != Qt::DisplayRole)
return QVariant();
switch (section) {
case 0: return tr("Manuscript");
case 1: return tr("Page Count");
default: return QVariant();
}
}
return QAbstractItemModel::headerData(section, orientation, role);

}

void TreeViewModel::setData(ProjectDoc* data)
{
	
	string pageCount = "";
	this->_manuscriptData = data;
	//clear data
	this->clear();
	//get root level
	QStandardItem* root = this->invisibleRootItem();
	//iterate on all manuscripts and add them to tree
	QMap<QPair<QString,QString>,ManuscriptDoc*>::iterator iter;
	for(iter=data->getManuscripts()->begin();iter!=data->getManuscripts()->end();iter++)
	{
		ManuscriptDoc* manuscriptDoc = *iter;
		IntToString(manuscriptDoc->getPageCount(), pageCount);
		QList<QStandardItem *> manRow = prepareRow(manuscriptDoc->getManDirPath(), pageCount);
		root->appendRow(manRow);
		//insert manuscripts page data recursively		
		this->insertPage(manuscriptDoc->getPages(), manRow.first());
	}
}

void TreeViewModel::insertPage(QVector<PageDoc*>* pages, QStandardItem* row)
{
	//iterate on the same level and call recursively on children pages
	for(int i = 0 ; i < pages->size(); i++)
	{
		PageDoc* page = pages->at(i);
		QList<QStandardItem *> pageRow = prepareRow(*(page->getPath()), "test");
		row->appendRow(pageRow);
		this->insertPage(page->getCopies(), pageRow.first());


	}
}

QList<QStandardItem *> TreeViewModel::prepareRow(const QString &path,
                                              //  const QString &title,
                                              //  const QString &region,
												const string &pageCount)
{
    QList<QStandardItem *> rowItems;
    rowItems << new QStandardItem(path);
    //rowItems << new QStandardItem(title);
    //rowItems << new QStandardItem(region);
	rowItems << new QStandardItem(QString::fromStdString(pageCount));
    return rowItems;
}

void TreeViewModel::IntToString(int i, std::string & s)
{
    s = "";
    if (i == 0)
    {
        s = "0";
        return;
    }
    if (i < 0)
    {
        s += '-';
        i = -i;
    }
    int count = log10((double) i);
    while (count >= 0)
    {
        s += ('0' + i/pow(10.0, count));
        i -= static_cast<int>(i/pow(10.0,count)) * static_cast<int>(pow(10.0,count));
        count--;
    }
}