#include "flowOperationsListModel.h"

FlowOperationsListModel::FlowOperationsListModel(QObject *parent) : QAbstractListModel(parent)
{			
	_operationsList<<"Global Binarizer"<<"Radial Binarizer"<<"Otsul Binarizer";		
}

int FlowOperationsListModel::rowCount(const QModelIndex &parent) const
{
	return _operationsList.size();
}

int FlowOperationsListModel::columnCount(const QModelIndex &parent) const
{
	return 1;
}
	
QVariant FlowOperationsListModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
    return QVariant();

	if (index.row() >= rowCount())
		return QVariant();

	if (role == Qt::DisplayRole)
		return _operationsList.at(index.row());
		
	else
		return QVariant();
}

bool FlowOperationsListModel::setData(const QModelIndex &index,
                            const QVariant &value, int role)
{
	if (role == Qt::EditRole) {											
		_operationsList<<value.toString();
		emit dataChanged(createIndex(0,0), createIndex(_operationsList.size(),0));		
	}
 
	return false;
}


QVariant FlowOperationsListModel::headerData(int section, Qt::Orientation orientation,
								int role) const
{
	if (role != Qt::DisplayRole)
		return QVariant();

	if (orientation == Qt::Horizontal)
		return QString("Operations");
	else
		return QVariant();
}

Qt::ItemFlags FlowOperationsListModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return Qt::ItemIsEnabled;

	return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

QModelIndex FlowOperationsListModel::parent( const QModelIndex &index ) const
{
	return QModelIndex();
}

FlowOperationsListModel::~FlowOperationsListModel()
{
}
