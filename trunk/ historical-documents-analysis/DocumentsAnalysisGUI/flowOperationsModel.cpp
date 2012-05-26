#include "flowOperationsModel.h"

	FlowOperationsModel::FlowOperationsModel(QObject *parent,int type) : QAbstractListModel(parent)
	{
		if(type==0)
		{
			stringList.push_back(QString("a"));
			stringList.push_back(QString("b"));
			stringList.push_back(QString("c"));
			stringList.push_back(QString("d"));
			stringList.push_back(QString("e"));
		}
		
	}

    int FlowOperationsModel::rowCount(const QModelIndex &parent) const
	{
		return stringList.size();
	}

	int FlowOperationsModel::columnCount(const QModelIndex &parent) const
	{
		return 1;
	}
	
    QVariant FlowOperationsModel::data(const QModelIndex &index, int role) const
	{
		if (!index.isValid())
        return QVariant();

		if (index.row() >= rowCount())
			return QVariant();

		if (role == Qt::DisplayRole)
			return stringList.at(index.row());
		else
			return QVariant();
	}

	bool FlowOperationsModel::setData(const QModelIndex &index,
                              const QVariant &value, int role)
	{
		if (index.isValid() && role == Qt::EditRole) {

			stringList.replace(index.row(), value.toString());
			emit dataChanged(index, index);
			return true;
		}
		else
		{
			stringList.push_back(value.toString());
			emit dataChanged(createIndex(stringList.size(),0), createIndex(stringList.size(),0));
			return true;
		}
 
		return false;
	}


    QVariant FlowOperationsModel::headerData(int section, Qt::Orientation orientation,
								  int role) const
	{
		if (role != Qt::DisplayRole)
			return QVariant();

		if (orientation == Qt::Horizontal)
			return QString("Column %1").arg(section);
		else
			return QString("Row %1").arg(section);
	}

    Qt::ItemFlags FlowOperationsModel::flags(const QModelIndex &index) const
	{
		if (!index.isValid())
			return Qt::ItemIsEnabled;

		return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
	}

	QModelIndex FlowOperationsModel::parent( const QModelIndex &index ) const
	{
		return QModelIndex();
	}

	FlowOperationsModel::~FlowOperationsModel()
	{
	}
