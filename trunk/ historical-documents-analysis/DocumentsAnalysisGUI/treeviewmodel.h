#ifndef TREEVIEWMODEL_H
#define TREEVIEWMODEL_H

#include <QStandardItemModel>
#include <QVector>
class ManuscriptDoc;
class ProjectDoc;
class Page;
class PageDoc;

class TreeViewModel : public QStandardItemModel
{
	Q_OBJECT

public:
	TreeViewModel(QObject *parent);
	~TreeViewModel();
	void setData(ProjectDoc* data);
	void insertPage(QVector<PageDoc*>* manuscripInfo, QStandardItem* row);

private:
	ProjectDoc* _manuscriptData;
	QList<QStandardItem *> prepareRow(const QString &path,
                                     // const QString &title,
                                     // const QString &region,
									  const std::string &pageCount);
	void IntToString(int i, std::string &s);
	QVariant headerData ( int section, Qt::Orientation orientation, int role ) const;
	
};

#endif // TREEVIEWMODEL_H
