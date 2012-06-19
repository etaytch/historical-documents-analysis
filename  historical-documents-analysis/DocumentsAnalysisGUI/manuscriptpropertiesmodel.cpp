#include "manuscriptpropertiesmodel.h"

ManuscriptPropertiesModel::ManuscriptPropertiesModel(ManuscriptDoc* manDoc ,QModelIndex& manIndex, QObject *parent )
	: QAbstractTableModel(parent)
{	
	_manDoc = manDoc;
	_manIndex = manIndex;
}

int ManuscriptPropertiesModel::rowCount(const QModelIndex &parent) const
{		
	return 6;	
}

int ManuscriptPropertiesModel::columnCount(const QModelIndex &parent) const
{
	return 2;
}

QVariant ManuscriptPropertiesModel::data(const QModelIndex &index, int role) const
{
	int row = index.row();
	int col = index.column();
	
	if (role == Qt::DisplayRole)
	{
		if (col==0)
		{
			switch(row)
			{
			case 0 :
				return "Title";
			case 1:
				return "Author";
			case 2:			
				return "Copyist";			
			case 3:			
				return "Region";			
			case 4:			
				return "Language";			
			case 5:			
				return "FontType";					

			default:
				return QVariant();
			}
		}

		if (col==1)
		{
			switch(row)
			{
			case 0:
				return _manDoc->getTitle();
			case 1:
				return _manDoc->getAuthor();
			case 2:			
				return _manDoc->getCopyist();			
			case 3:			
				return _manDoc->getRegion();
			case 4:			
				return _manDoc->getLanguage();
			case 5:			
				return _manDoc->getFontType();
			default:
				return QVariant();
			}
		}
	}
		if (role == Qt::EditRole)
		{
			if (col==1)
			{
				switch(row)
				{
				case 0:
					return _manDoc->getTitle();
				case 1:
					return _manDoc->getAuthor();
				case 2:			
					return _manDoc->getCopyist();			
				case 3:			
					return _manDoc->getRegion();
				case 4:			
					return _manDoc->getLanguage();
				case 5:			
					return _manDoc->getFontType();
				default:
					return QVariant();
				}
			}
		}
	return QVariant();
}

QVariant ManuscriptPropertiesModel::headerData(int section, 
											   Qt::Orientation orientation,
											   int role) const
{
	if (role != Qt::DisplayRole)
		return QVariant();

	if (orientation == Qt::Horizontal) {
		switch (section) {
		case 0:
			return "Property";

		case 1:
			return "Value";

		default:
			return QVariant();
		}
	}
	return QVariant();
}

Qt::ItemFlags ManuscriptPropertiesModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return Qt::ItemIsEnabled;
	if (index.column()==0)
	{
		return Qt::ItemIsSelectable|Qt::ItemIsEnabled; 
	}

	return QAbstractItemModel::flags(index) | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

bool ManuscriptPropertiesModel::setData(const QModelIndex &index,
	const QVariant &value, int role)
{
	int row = index.row();
	int col = index.column();

	if (index.isValid() && role == Qt::EditRole) {
		if (col==1)
		{
			switch(row)
			{
			case 0:
				_manDoc->setTitle(value.toString());
				emit dataChanged(_manIndex,_manIndex);
				return true;
			case 1:
				_manDoc->setAuthor(value.toString());
				emit dataChanged(_manIndex,_manIndex);
				return true;
			case 2:			
				_manDoc->setCopyist(value.toString());
				emit dataChanged(_manIndex,_manIndex);
				return true;			
			case 3:			
				_manDoc->setRegion(value.toString());
				emit dataChanged(_manIndex,_manIndex);
				return true;
			case 4:			
				_manDoc->setLanguage(value.toString());
				emit dataChanged(_manIndex,_manIndex);
				return true;
			case 5:			
				_manDoc->setFontType(value.toString());
				emit dataChanged(_manIndex,_manIndex);
				return true;
			
			default:
				return true;
			}
		}
	}
	return false;
}

ManuscriptPropertiesModel::~ManuscriptPropertiesModel()
{

}
