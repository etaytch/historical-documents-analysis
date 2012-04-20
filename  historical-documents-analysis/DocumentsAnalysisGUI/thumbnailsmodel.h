#ifndef THUMBNAILSMODEL_H
#define THUMBNAILSMODEL_H


#include <QMap>
#include <QString>
#include <QPixmap>
#include <QAbstractListModel>
#include <QObject>
#include <QDir>
#include <QStandardItem>



class ThumbNailsModel : public QAbstractListModel
{
	Q_OBJECT

private:
	QMap<QString,QPixmap>* _thumbnails;

public:
	ThumbNailsModel(QObject *parent,QString folderPath);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation,
								  int role = Qt::DisplayRole) const;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;
	virtual QModelIndex parent( const QModelIndex &index ) const;
	virtual ~ThumbNailsModel();
	QString getPagePath(const QModelIndex &index ) const;

private:
	bool loadImages(QString manuscriptDir);
};

#endif // THUMBNAILSMODEL_H
