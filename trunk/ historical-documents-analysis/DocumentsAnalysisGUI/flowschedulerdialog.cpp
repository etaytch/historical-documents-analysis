#include "flowschedulerdialog.h"


#include <qprogressbar.h>
#include "qDebug.h"
#include "hdamainframe.h"

FlowSchedulerDialog::FlowSchedulerDialog(QWidget *parent,TreeViewModel* model)
	: QDialog(parent)
{
	ui.setupUi(this);		
	_flowOperationsListModel = new FlowOperationsModel(this,0);
	_flowSelectedOperationsListModel = new FlowOperationsModel(this,1);
	_manuscriptTreeModel = model;
	ui.flowPagesTreeView->setModel(_manuscriptTreeModel);

	ui.flowOperationsListView->setModel(_flowOperationsListModel);
	ui.flowSelectedOperationsListView->setModel(_flowSelectedOperationsListModel);

	/*
	QProgressBar* probar1 = new QProgressBar();
	ui.verticalLayout->addWidget(probar1);
	QProgressBar* probar2 = new QProgressBar();
	ui.verticalLayout->addWidget(probar2);
	QProgressBar* probar3 = new QProgressBar();
	ui.verticalLayout->addWidget(probar3);
	QProgressBar* probar4 = new QProgressBar();
	ui.verticalLayout->addWidget(probar4);
	QProgressBar* probar5 = new QProgressBar();
	ui.verticalLayout->addWidget(probar5);
	*/
}

FlowSchedulerDialog::FlowSchedulerDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);	
}

FlowSchedulerDialog::~FlowSchedulerDialog()
{	
}


void FlowSchedulerDialog::addOperation()
{
	
	QItemSelectionModel* selectionModel = ui.flowOperationsListView->selectionModel();
	QModelIndexList indexes = selectionModel->selectedIndexes();
	for(int i=0;i<indexes.size();i++){
		QModelIndex currentIndex = indexes.at(i);
		QVariant currentOperationStr = currentIndex.data(Qt::DisplayRole);
		_flowSelectedOperationsListModel->setData(QModelIndex(),currentOperationStr);
		qDebug()<<currentOperationStr;
	}
}

QStringList FlowSchedulerDialog::getSelectedOperations()
{
	QStringList ans;
	for ( int i = 0 ; i < _flowSelectedOperationsListModel->rowCount() ; ++i )
	{
	  ans << _flowSelectedOperationsListModel->index( i, 0 ).data( Qt::DisplayRole ).toString() ;
	}
	return ans;
}

void FlowSchedulerDialog::startFlow()
{
	QStringList selectedOperations = getSelectedOperations();
	
	QItemSelectionModel* pagesSelectionModel = ui.flowPagesTreeView->selectionModel();
	QModelIndexList pagesIndexes = pagesSelectionModel->selectedIndexes();
	for(int i=0;i<pagesIndexes .size();i++){
		QModelIndex currentIndex = pagesIndexes.at(i);
		if (qVariantCanConvert<PageDoc> (currentIndex.data(Qt::UserRole)))
		{
			QVariant currentPage = currentIndex.data(Qt::UserRole);
			PageDoc pd = qVariantValue<PageDoc>(currentPage);
			HdaMainFrame* mainFrame = (static_cast<HdaMainFrame*>(parent())); 		
			Page* page = pd.getPage();
			page->loadMat();

			HdaProgressBar* probar = new HdaProgressBar();
			probar->setValue(0);
			ui.verticalLayout->addWidget(probar);
			_progressBars.push_back(probar);
			mainFrame->getFlowManager()->addThread(pd.getPage(),selectedOperations,probar);
		}

	}
}
void FlowSchedulerDialog::cancelFlow()
{
	
}

void FlowSchedulerDialog::clearDone()
{
	QVector<HdaProgressBar*> newProgressVector;
	for(int i=0;i<_progressBars.size();i++)
	{
		HdaProgressBar* currentProgBar = _progressBars.at(i);
		if(currentProgBar->getValue()>=100)
		{
			ui.verticalLayout->removeWidget(currentProgBar);
			delete currentProgBar;
		}
		else
		{
			newProgressVector.push_back(currentProgBar);
		}
	}	
	_progressBars = newProgressVector;
}

void FlowSchedulerDialog::updatePage(Page* page)
{

	
	//for ( int i = 0 ; i < _manuscriptTreeModel->rowCount() ; ++i )
	//{		
	//	QModelIndex currentIndex = _manuscriptTreeModel->index( i, 0,QModelIndex());		
	//	//ans << _flowSelectedOperationsListModel->index( i, 0 ).data( Qt::DisplayRole ).toString() ;
	//	QVariant currentPage = currentIndex.data(Qt::UserRole);

	//	TreeItem* item = _manuscriptTreeModel->getItem(currentIndex);
	//	
	//	for(int j=0;j<item->childCount();j++)
	//	{			
	//		TreeItem* childItem = item->child(j);
	//		QVariant child = childItem->data(0);
	//		if (qVariantCanConvert<PageDoc> (child))
	//		{				
	//			PageDoc pd = qVariantValue<PageDoc>(child);
	//		}
	//	}




	//	if (qVariantCanConvert<PageDoc> (currentIndex.data(Qt::UserRole)))
	//	{
	//		QVariant currentPage = currentIndex.data(Qt::UserRole);
	//		PageDoc pd = qVariantValue<PageDoc>(currentPage);
	//		if(pd.getPage()==page){
	//			int rf=5;
	//		}
	//	}


	  //ans << _flowSelectedOperationsListModel->index( i, 0 ).data( Qt::DisplayRole ).toString() ;
	//}
}