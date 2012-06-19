#ifndef MANPROPERTIESMODEL_H
#define MANPROPERTIESMODEL_H

#include <QAbstractListModel>
#include <QLineEdit>
#include "manuscriptdoc.h"

class ManuscriptPropertiesModel : public QAbstractTableModel
{
    Q_OBJECT

public:
	ManuscriptPropertiesModel(ManuscriptDoc *manDoc ,QModelIndex &manIndex, QObject *parent);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole);
 	virtual ~ManuscriptPropertiesModel();


private:
	ManuscriptDoc* _manDoc;
	QModelIndex _manIndex;
};

#endif // MANPROPERTIESMODEL_H
