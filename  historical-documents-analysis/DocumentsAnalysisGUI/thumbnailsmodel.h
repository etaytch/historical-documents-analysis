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
#include "manuscriptdoc.h"



class ThumbNailsModel : public QAbstractListModel
{
	Q_OBJECT

private:
	ManuscriptDoc _man;
	QMap<QString,QPixmap> _thumbnails;

public:
	ThumbNailsModel(ManuscriptDoc& man,QObject *parent=0);
	ThumbNailsModel(QObject *parent=0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation,
								  int role = Qt::DisplayRole) const;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;
	virtual QModelIndex parent( const QModelIndex &index ) const;
	virtual ~ThumbNailsModel();
	QString getPagePath(const QModelIndex &index ) const;

private: //metods
	bool loadImages();
	void saveThumbnail(QString thumbPath,QPixmap&);
};

#endif // THUMBNAILSMODEL_H
