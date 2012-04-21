#ifndef TREEVIEWMODEL_H
#define TREEVIEWMODEL_H

#include <QStandardItemModel>
#include <QVector>
#include "manuscriptdoc.h"

class TreeViewModel : public QStandardItemModel
{
	Q_OBJECT

public:
	TreeViewModel(QObject *parent);
	~TreeViewModel();
	void setData(QVector<ManuscriptDoc*>* data);
	void insert(ManuscriptDoc* manuscripInfo);

private:
	QVector<ManuscriptDoc*>* _manuscriptData;
	
	
};

#endif // TREEVIEWMODEL_H
