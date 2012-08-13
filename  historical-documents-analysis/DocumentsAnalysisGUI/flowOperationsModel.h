#ifndef FLOWOPERATIONSMODEL_H
#define FLOWOPERATIONSMODEL_H

#include <QString>
#include <QPixmap>
#include <QAbstractListModel>
#include <QObject>
#include <QStandardItem>
#include "OperationDO.h"


class FlowOperationsModel : public QAbstractListModel
{
	Q_OBJECT

private:
	QVector<OperationDO*> _operations;
public:	
	FlowOperationsModel(QObject *parent,int type);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
	virtual bool setData(const QModelIndex &index, const QVariant &value,
		             int role = Qt::EditRole);
    virtual QVariant headerData(int section, Qt::Orientation orientation,
								  int role = Qt::DisplayRole) const;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;
	virtual QModelIndex parent( const QModelIndex &index ) const;	
	virtual bool removeRows(int position, int rows, const QModelIndex & parent);
	virtual ~FlowOperationsModel();	

};


#endif // FLOWOPERATIONSMODEL_H



