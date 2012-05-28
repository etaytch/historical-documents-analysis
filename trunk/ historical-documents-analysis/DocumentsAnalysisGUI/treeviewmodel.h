#ifndef TREEVIEWMODEL_H
#define TREEVIEWMODEL_H

#include <QStandardItemModel>
#include <QVector>
#include <QMap>
#include "treeitem.h"
#include "projectdoc.h"
#include "PageDoc.h"



class TreeViewModel : public QAbstractItemModel
{
	Q_OBJECT

public:
    TreeViewModel(ProjectDoc& pd ,QObject *parent = 0);
	virtual ~TreeViewModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
	QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
	bool setHeaderData(int section, Qt::Orientation orientation,
                       const QVariant &value, int role = Qt::EditRole);
	bool insertColumns(int position, int columns,
                       const QModelIndex &parent = QModelIndex());
    bool removeColumns(int position, int columns,
                       const QModelIndex &parent = QModelIndex());
    bool insertRows(int position, int rows,
                    const QModelIndex &parent = QModelIndex());
    bool removeRows(int position, int rows,
                    const QModelIndex &parent = QModelIndex());
    Qt::ItemFlags flags(const QModelIndex & index) const;
	QModelIndex parent(const QModelIndex &index) const;
	QModelIndex index(int row, int column, const QModelIndex &parent) const;
	TreeItem *getItem(const QModelIndex &index) const;

	ProjectDoc _project;
private:

	
	TreeItem   *_rootItem;

private: //methods
	void setupModel (TreeItem *parent);
	void setUpPages (Page* page ,QString manName,TreeItem* treeItem);
	
	
signals:
    void editCompleted(const QString &);

};

#endif // TREEVIEWMODEL_H
