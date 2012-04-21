#include "thumbnailsmodel.h"


ThumbNailsModel::ThumbNailsModel(QObject *parent, QString folderPath)
	: QAbstractListModel(parent)
{
	_thumbnails = new QMap<QString,QPixmap>();
	loadImages(folderPath);
}

bool ThumbNailsModel::loadImages(QString manuscriptDir)
{

	QDir manDir(manuscriptDir);
	QStringList imageList = manDir.entryList(QDir::Files); //put all the images names in the folder into a vector  
	foreach(QString imageFileName, imageList)	
	{
		QPixmap image  = QPixmap();
		if (!image.load(manuscriptDir+"/"+imageFileName))
			return false;

		_thumbnails->insert(manuscriptDir+"/"+imageFileName,image.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation));
	}
	return true;
}


ThumbNailsModel::~ThumbNailsModel()
{
	_thumbnails->clear();
	delete _thumbnails;
}

int ThumbNailsModel::rowCount(const QModelIndex &parent) const
{		
	return _thumbnails->size();	
}

int ThumbNailsModel::columnCount(const QModelIndex &parent) const
{		
	return 1;	
}

QVariant ThumbNailsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= _thumbnails->size())
        return QVariant();

	switch( role )
	{
		case Qt::DecorationRole:	
		{
			QMap<QString, QPixmap>::iterator iter;
			iter = _thumbnails->begin();
			iter+=index.row();
			QPixmap  image = iter.value();
			return image;
		}
		case Qt::DisplayRole:
		{      
			
		}
		default:
			return QVariant();
	}
}

QModelIndex ThumbNailsModel::parent( const QModelIndex &index ) const
{
	return QModelIndex();
}

QString ThumbNailsModel::getPagePath(const QModelIndex &index ) const
{
	QMap<QString, QPixmap>::iterator iter;
	iter = _thumbnails->begin();
	iter+=index.row();
	QString  imagePath = iter.key();
	return imagePath;
}

QVariant ThumbNailsModel::headerData(int section, Qt::Orientation orientation,
                                     int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        return QString("Column %1").arg(section);
    else
        return QString("Row %1").arg(section);
}


Qt::ItemFlags ThumbNailsModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

