#include "binarizeoperationdo.h"

BinarizeOperationDO::BinarizeOperationDO(QString type)
	: OperationDO(type)
{	 
}

int BinarizeOperationDO::rowCount(const QModelIndex &parent) const
{
	return 5;
}

int BinarizeOperationDO::columnCount(const QModelIndex &parent) const
{
	return 2;
}

bool BinarizeOperationDO::setData(const QModelIndex &index, const QVariant &value, int role)
{
	int row = index.row();
	int col = index.column();

	if (role == Qt::EditRole)
	{
		if (col==1)
		{
			switch(row)
			{
				case 0:
					_operationType = value.toString();
					return true;

				case 1:
					_thershold = value.toFloat();	
					return true;
				
				default:
					return false;
			}
		}
	}

}
QVariant BinarizeOperationDO::data(const QModelIndex &index, int role) const
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
				return "Type";
			case 1:
				return "Thershold";	
			default:
				return QVariant();
			}
		}

		if (col==1)
		{						
			switch(row)
			{
			case 0:
				return _operationType;
			case 1:
				return _thershold;		
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
				return _operationType;
			case 1:
				return _thershold;	
				
			default:
				return QVariant();
			}
		}
	}
	return QVariant();
}

BinarizeOperationDO::~BinarizeOperationDO()
{

}
