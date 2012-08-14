#include "flowpropertiesmodel.h"

FlowPropertiesModel::FlowPropertiesModel(QObject *parent)
	: QAbstractTableModel(parent)
{
	_operationPropertisDO=0;
}

FlowPropertiesModel::FlowPropertiesModel(OperationDO* operationDO, QObject *parent)
	: QAbstractTableModel(parent)
{
	_operationPropertisDO = operationDO;

}

int FlowPropertiesModel::rowCount(const QModelIndex &parent) const
{
	if(_operationPropertisDO)
		return _operationPropertisDO->rowCount(parent);
	return 0;
}

int FlowPropertiesModel::columnCount(const QModelIndex &parent) const
{
	if(_operationPropertisDO)
		return _operationPropertisDO->columnCount(parent);
	return 0;
}

QVariant FlowPropertiesModel::data(const QModelIndex &index, int role) const
{
	if(_operationPropertisDO)			
	{
		if (role == Qt::DisplayRole)
		{
			return _operationPropertisDO->data(index,role);
		}
		if (role == Qt::UserRole)
		{
			return QVariant::fromValue(_operationPropertisDO);
		}
	}
	return QVariant();
}

QVariant FlowPropertiesModel::headerData(int section, Qt::Orientation orientation,
                    int role) const
{
	return QVariant();
}

Qt::ItemFlags FlowPropertiesModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return Qt::ItemIsEnabled;
	if (index.column()==0)
	{
		return Qt::ItemIsSelectable|Qt::ItemIsEnabled; 
	}

	return QAbstractItemModel::flags(index) | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

bool FlowPropertiesModel::setData(const QModelIndex &index, const QVariant &value,
                int role)
{
	if(index.isValid())
	{
		bool ans =  _operationPropertisDO->setData(index, value,role);		
		emit dataChanged(createIndex(0,0),createIndex(rowCount(),columnCount()));
		return ans;
	}
	
	return false;
}
void FlowPropertiesModel::setOperationDO(OperationDO* oper)
{
	_operationPropertisDO = oper;
	emit dataChanged(createIndex(0,0),createIndex(rowCount(),columnCount()));
}

void FlowPropertiesModel::clearProperties()
{
	int rowsBefore = rowCount();
	int columnBefore = columnCount();
	_operationPropertisDO=0;
	emit dataChanged(createIndex(0,0),createIndex(rowsBefore,columnBefore));
}

FlowPropertiesModel::~FlowPropertiesModel()
{

}
