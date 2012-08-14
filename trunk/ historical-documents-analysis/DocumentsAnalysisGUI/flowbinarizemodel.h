#ifndef FLOWBINARIZEMODEL_H
#define FLOWBINARIZEMODEL_H

#include <QObject>
#include "FlowPropertiesModel.h"
#include "OperationDO.h"

class FlowBinarizeModel : public FlowPropertiesModel
{
	Q_OBJECT

public:
	FlowBinarizeModel(OperationDO* operationDO, QObject *parent);

	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole);

	~FlowBinarizeModel();

private:

};

#endif // FLOWBINARIZEMODEL_H
