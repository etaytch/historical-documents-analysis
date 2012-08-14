#include "flowbinarizemodel.h"

FlowBinarizeModel::FlowBinarizeModel(OperationDO* operationDO, QObject *parent)
	: FlowPropertiesModel(operationDO,parent)
{
}


int FlowBinarizeModel::rowCount(const QModelIndex &parent) const
{		
	return 5;	
}

int FlowBinarizeModel::columnCount(const QModelIndex &parent) const
{
	return 2;
}


QVariant FlowBinarizeModel::data(const QModelIndex &index, int role) const
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
				return QString(_operationPropertisDO->getOperationType());
			case 1:
				return _operationPropertisDO->getThershold();		
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
				return QString(_operationPropertisDO->getOperationType());
			case 1:
				return _operationPropertisDO->getThershold();	
				
			default:
				return QVariant();
			}
		}
	}
	
	return FlowPropertiesModel::data(index, role);
}

QVariant FlowBinarizeModel::headerData(int section, Qt::Orientation orientation,
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

Qt::ItemFlags FlowBinarizeModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return Qt::ItemIsEnabled;
	if (index.column()==0)
	{
		return Qt::ItemIsSelectable|Qt::ItemIsEnabled; 
	}

	return QAbstractItemModel::flags(index) | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

bool FlowBinarizeModel::setData(const QModelIndex &index,
	const QVariant &value, int role)
{
	int row = index.row();
	int col = index.column();

	if (role != Qt::EditRole)
		return false;

	if (col==1)
	{
		switch(row)
		{
			case 0 :
				_operationPropertisDO->setOperationType(value.toString());
				return true;
			case 1:
				_operationPropertisDO->setThershold(value.toFloat());
				return true;
			default:
				return false;
		}
	}

	return false;
}

FlowBinarizeModel::~FlowBinarizeModel()
{

}
