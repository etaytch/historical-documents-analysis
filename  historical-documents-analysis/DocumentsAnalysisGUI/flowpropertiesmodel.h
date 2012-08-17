#ifndef FLOWPROPERTIESMODEL_H
#define FLOWPROPERTIESMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include "OperationDO.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	FlowPropertiesModel class extends the QAbstractTableModel base class.
///				It responsible on displaying the selected OperationDO' properties.</summary>
///
/// <remarks>	Etay Tchechanovski, 1/5/2012. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

class FlowPropertiesModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	FlowPropertiesModel(QObject *parent);
	FlowPropertiesModel(OperationDO* operationDO, QObject *parent);
	virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
	virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;
    virtual bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole);
	void setOperationDO(OperationDO* oper);
	void clearProperties();

	~FlowPropertiesModel();

protected:
	OperationDO* _operationPropertisDO;
};

#endif // FLOWPROPERTIESMODEL_H
