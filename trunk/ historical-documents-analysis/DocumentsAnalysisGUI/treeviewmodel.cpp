#include "treeviewmodel.h"

TreeViewModel::TreeViewModel(QObject *parent)
	: QStandardItemModel(parent)
{
	//this->_manuscriptData = new	QVector<ManuscriptDoc*>();
}

TreeViewModel::~TreeViewModel()
{

}

void TreeViewModel::setData(QVector<ManuscriptDoc*>* data)
{
	this->_manuscriptData = data;
	QVector<ManuscriptDoc>::Iterator* it; 
	QVector<ManuscriptDoc>::Iterator* start = this->_manuscriptData->begin();
	QVector<ManuscriptDoc>::Iterator* end = this->_manuscriptData->end();
	for (it = start; it != end ; it++)
	{
		this->insert(*it);
	}
}

void TreeViewModel::insert(ManuscriptDoc* manuscripInfo)
{

}