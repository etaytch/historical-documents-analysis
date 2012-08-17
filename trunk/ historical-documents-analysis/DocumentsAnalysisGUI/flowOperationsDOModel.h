#ifndef FLOWOPERATIONSDOMODEL_H
#define FLOWOPERATIONSDOMODEL_H

#include <QString>
#include <QPixmap>
#include <QAbstractListModel>
#include <QObject>
#include <QStandardItem>
#include "OperationDO.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	FlowOperationsDOModel class extends the QAbstractListModel base class.
///				It responsible on displaying the selected OperationDOs in the system.</summary>
///
/// <remarks>	Etay Tchechanovski, 1/5/2012. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

class FlowOperationsDOModel : public QAbstractListModel
{
	Q_OBJECT

private:
	QVector<OperationDO*> _operations;
public:	
	FlowOperationsDOModel(QObject *parent,int type);
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
	virtual ~FlowOperationsDOModel();	

};


#endif // FLOWOPERATIONSDOMODEL_H



