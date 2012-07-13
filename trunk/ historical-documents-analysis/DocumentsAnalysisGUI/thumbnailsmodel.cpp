#include "thumbnailsmodel.h"
#include <QFileInfo>
#include <QFile>


ThumbNailsModel::ThumbNailsModel(TreeItem *rootItem,ProjectDoc proj ,QObject *parent)
	: QAbstractListModel(parent)
{
	_project = proj;
	loadImages(rootItem);
}

ThumbNailsModel::ThumbNailsModel(QObject *parent)
	: QAbstractListModel(parent)
{
}

bool ThumbNailsModel::removeRows(int position, int rows, const QModelIndex &parent)
{
	beginRemoveRows(parent, position, position + rows - 1);
    endRemoveRows();
	return true;
}

bool ThumbNailsModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    beginInsertRows(parent, 0, position + rows - 1);
    endInsertRows();
    return true;
}

void ThumbNailsModel::updateThumbnail(PageDoc pd , TreeItem* child, int checked)
{
	ManuscriptDoc manDoc = _project.getManuscriptAt(pd.getManuscriptName());
	QDir manPagesDir(manDoc.getPagesDirPath());
	QDir manThumbsDir(manDoc.getThumbnailsDirPath());
	if (!manThumbsDir.exists())
	{
		QDir().mkdir(manDoc.getThumbnailsDirPath());
	}

	if(checked)
	{
		QString imageFileName = QFileInfo(QFile(pd.getPage()->getName().c_str())).fileName(); 
		QPixmap image = QPixmap();
		QString thumbPath = manDoc.getThumbnailsDirPath()+"/"+imageFileName; 
		thumbPath = thumbPath.split(".")[0]+".png";
		QString realPath = manDoc.getPagesDirPath()+"/"+imageFileName;
		QFile thumbfile(thumbPath);
		if (thumbfile.exists())
		{
			if (!image.load(thumbPath)) return;
			_thumbnails.insert(realPath,image);
			_pages.insert(realPath,PageDoc(pd.getPage(),pd.getManuscriptName(),child));
		}
		else
		{
			if (!image.load(realPath)) return;		
			image = image.scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation);
			saveThumbnail(thumbPath,image);
			_thumbnails.insert(realPath,image);
			_pages.insert(realPath,PageDoc(pd.getPage(),pd.getManuscriptName(),child));
		}
		insertRows(rowCount(),1,QModelIndex());
	}
	else
	{
		_thumbnails.remove(pd.getPage()->getName().c_str());
		_pages.remove(pd.getPage()->getName().c_str());
		removeRows(rowCount(),1,QModelIndex());
	}
}

bool ThumbNailsModel::loadImages(TreeItem *rootItem)
{
	for(int i=0; i<rootItem->childCount();i++)	
	{
		TreeItem* child = rootItem->child(i);
		if (qVariantCanConvert<PageDoc>(child->data(0)))
		{
			PageDoc pd = qVariantValue<PageDoc>(child->data(0));
			updateThumbnail(pd,child,pd.getPage()->isActive());
		}
		else
		{
		}
		loadImages(child);
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
			return  QVariant::fromValue((_pages.begin()+index.row()).value());
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
