#ifndef BINARIZEOPERATIONDO_H
#define BINARIZEOPERATIONDO_H

#include "OperationDO.h"
#include <QModelIndex>

class BinarizeOperationDO : public OperationDO
{
	Q_OBJECT

public:
	BinarizeOperationDO(QString type);
	~BinarizeOperationDO();

protected:
	QVariant data(const QModelIndex &index, int role) const;
	bool setData(const QModelIndex &index, const QVariant &value, int role);
	int rowCount(const QModelIndex &parent) const;
	int columnCount(const QModelIndex &parent) const;

private:
};

#endif // BINARIZEOPERATIONDO_H
