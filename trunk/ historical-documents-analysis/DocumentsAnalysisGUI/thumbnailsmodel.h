#ifndef THUMBNAILSMODEL_H
#define THUMBNAILSMODEL_H


#include <QMap>
#include <QString>
#include <QPixmap>
#include <QFile>
#include <QBuffer>
#include <QAbstractListModel>
#include <QObject>
#include <QDir>
#include <QStandardItem>
#include "treeitem.h"
#include "projectdoc.h"
#include "PageDoc.h"



class ThumbNailsModel : public QAbstractListModel
{
	Q_OBJECT

private:
	ProjectDoc _project;
	QMap<QString,QPixmap> _thumbnails;
	QMap<QString,PageDoc> _pages;

public:
	ThumbNailsModel(TreeItem *rootItem,ProjectDoc proj ,QObject *parent=0);
	ThumbNailsModel(QObject *parent=0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex &parent = QModelIndex()) const;
	bool removeRows(int position, int rows, const QModelIndex &parent);
	bool insertRows(int position, int rows, const QModelIndex &parent);
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation,
								  int role = Qt::DisplayRole) const;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;
	virtual QModelIndex parent( const QModelIndex &index ) const;
	virtual ~ThumbNailsModel();
	QString getPagePath(const QModelIndex &index ) const;

public slots:
	void updateThumbnail(PageDoc,TreeItem*,int);

private: //metods
	bool loadImages(TreeItem *rootItem);
	void saveThumbnail(QString thumbPath,QPixmap&);
};

#endif // THUMBNAILSMODEL_H
