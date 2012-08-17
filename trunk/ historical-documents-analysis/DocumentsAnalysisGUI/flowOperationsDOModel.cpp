#include "flowOperationsDOModel.h"

FlowOperationsDOModel::FlowOperationsDOModel(QObject *parent,int type) : QAbstractListModel(parent)
{	
}

int FlowOperationsDOModel::rowCount(const QModelIndex &parent) const
{
	return _operations.size();
}

int FlowOperationsDOModel::columnCount(const QModelIndex &parent) const
{
	return 1;
}
	
QVariant FlowOperationsDOModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
    return QVariant();

	if (index.row() >= rowCount())
		return QVariant();

	if (role == Qt::DisplayRole)
		return _operations.at(index.row())->getOperationType();
		
	else if (role == Qt::UserRole)		
		return QVariant::fromValue(_operations.at(index.row()));
		
	else
		return QVariant();
}

bool FlowOperationsDOModel::setData(const QModelIndex &index,
                            const QVariant &value, int role)
{
	
	int row = index.row();
	int col = index.column();

	if (role == Qt::EditRole) 
	{
		if (qVariantCanConvert<OperationDO*> (value))
		{						
				
			_operations.push_back(qVariantValue<OperationDO*>(value));
			emit dataChanged(createIndex(_operations.size(),0), createIndex(_operations.size(),0));
		}
	}
	else if (index.isValid() && role == Qt::UserRole+1) 
	{
		if(row>0 && rowCount()>1)
		{
			OperationDO* fst = _operations[row-1];
			_operations[row-1] = _operations[row];
			_operations[row] = fst;
			emit dataChanged(createIndex(0,0), createIndex(_operations.size(),0));
		}
	}

	else if (index.isValid() && role == Qt::UserRole+2) 
	{
		if(row<rowCount()-1 && rowCount()>1)
		{
			OperationDO* fst = _operations[row+1];
			_operations[row+1] = _operations[row];
			_operations[row] = fst;
			emit dataChanged(createIndex(0,0), createIndex(_operations.size(),0));
		}
	}
		
		
	/*if (index.isValid() && role == Qt::EditRole) {

		stringList.replace(index.row(), value.toString());
		emit dataChanged(index, index);
		return true;
	}
	else
	{
		stringList.push_back(value.toString());
		emit dataChanged(createIndex(stringList.size(),0), createIndex(stringList.size(),0));
		return true;
	}*/
 
	return false;
}


QVariant FlowOperationsDOModel::headerData(int section, Qt::Orientation orientation,
								int role) const
{
	if (role != Qt::DisplayRole)
		return QVariant();

	if (orientation == Qt::Horizontal)
		return QString("Operations");
	else
		return QVariant();
}

Qt::ItemFlags FlowOperationsDOModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return Qt::ItemIsEnabled;

	return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

QModelIndex FlowOperationsDOModel::parent( const QModelIndex &index ) const
{
	return QModelIndex();
}

bool FlowOperationsDOModel::removeRows(int position, int rows, const QModelIndex &parent)
{
	beginRemoveRows(parent, position, position + rows - 1);
	_operations.remove(position);
    endRemoveRows();
	return true;
}

FlowOperationsDOModel::~FlowOperationsDOModel()
{
}
