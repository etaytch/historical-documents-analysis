#include "thumbnailsmodel.h"


ThumbNailsModel::ThumbNailsModel(ManuscriptDoc& man,QObject *parent)
	: QAbstractListModel(parent)
{
	_man = man;
	loadImages();
}

ThumbNailsModel::ThumbNailsModel(QObject *parent)
	: QAbstractListModel(parent)
{
}

bool ThumbNailsModel::loadImages()
{
	
	QDir manPagesDir(_man.getPagesDirPath());
	QDir manThumbsDir(_man.getThumbnailsDirPath());

	//create thumnails folder if it doesnt exist
	if (!manThumbsDir.exists())
	{
		QDir().mkdir(_man.getThumbnailsDirPath());
	}

	QStringList imageList = manPagesDir.entryList(QDir::Files); //put all the images names in the folder into a vector  
	foreach(QString imageFileName, imageList)	
	{
		QPixmap image = QPixmap();
		QString thumbPath = _man.getThumbnailsDirPath()+"/"+imageFileName; 
		thumbPath = thumbPath.split(".")[0]+".png";
		QString realPath = _man.getPagesDirPath()+"/"+imageFileName; 

		QFile thumbfile(thumbPath);
		if (thumbfile.exists())
		{
			if (!image.load(thumbPath))
				return false;
			_thumbnails.insert(realPath,image);
		}
		else
		{
			if (!image.load(realPath))
				return false;		
			image = image.scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation);
			saveThumbnail(thumbPath,image);
			_thumbnails.insert(realPath,image);
		}
	}
	return true;
}

void ThumbNailsModel::saveThumbnail(QString thumbPath,QPixmap& thumbPixMap)
{
	thumbPixMap.save(thumbPath,"PNG");
}

ThumbNailsModel::~ThumbNailsModel()
{
	_thumbnails.clear();
}

int ThumbNailsModel::rowCount(const QModelIndex &parent) const
{		
	return _thumbnails.size();	
}

int ThumbNailsModel::columnCount(const QModelIndex &parent) const
{		
	return 1;	
}

QVariant ThumbNailsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= _thumbnails.size())
        return QVariant();

	switch( role )
	{
		case Qt::DecorationRole:	
		{
			QPixmap  image = (_thumbnails.begin()+index.row()).value();
			return image;
		}
		case Qt::UserRole:
		{
			return  (_thumbnails.begin()+index.row()).key();
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
	QString  imagePath = (_thumbnails.begin()+index.row()).key();
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

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}
