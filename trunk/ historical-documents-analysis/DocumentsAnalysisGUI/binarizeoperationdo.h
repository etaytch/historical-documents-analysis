#ifndef BINARIZEOPERATIONDO_H
#define BINARIZEOPERATIONDO_H

#include "OperationDO.h"
#include <QModelIndex>

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	BinarizeOperationDO class extends the OperationDO class to represent 
///				a Binarize operation. </summary>
///
/// <remarks>	Etay Tchechanovski, 1/5/2012. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

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
