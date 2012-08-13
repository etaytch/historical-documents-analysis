#include "flowschedulerdialog.h"


#include <qprogressbar.h>
#include "qDebug.h"
#include "hdamainframe.h"
#include "OperationDO.h"
#include "BinarizeOperationDO.h"
#include "FlowBinarizeModel.h"
#include <QModelIndex>

FlowSchedulerDialog::FlowSchedulerDialog(QWidget *parent,TreeViewModel* model)
	: QDialog(parent)
{
	ui.setupUi(this);			
	_flowOperationsListModel = new FlowOperationsListModel(this);
	_flowSelectedOperationsListModel = new FlowOperationsModel(this,1);
	_flowPropertiesModel= new FlowPropertiesModel(this);
	_manuscriptTreeModel = model;
	ui.flowPagesTreeView->setModel(_manuscriptTreeModel);

	ui.flowOperationsListView->setModel(_flowOperationsListModel);
	ui.flowSelectedOperationsListView->setModel(_flowSelectedOperationsListModel);
	ui.flowPropertiesTableView->setModel(_flowPropertiesModel);

	connect(parent,SIGNAL(updateFlowDialogTree(TreeViewModel*)),this,SLOT(updateTree(TreeViewModel*)));

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
	for(int i=0;i<_allOperationsDo.size();i++)
	{
		delete _allOperationsDo.at(i);
	}	
}

void FlowSchedulerDialog::addOperation()
{
	QVariant qvar = _flowPropertiesModel->data(QModelIndex(),Qt::UserRole);
	if (qVariantCanConvert<OperationDO*> (qvar))
	{						
			_flowSelectedOperationsListModel->setData(QModelIndex(),qvar);			
	}
	_flowPropertiesModel->clearProperties();
	ui.flowOperationsListView->clearSelection();


	/*QItemSelectionModel* selectionModel = ui.flowOperationsListView->selectionModel();
	QModelIndexList indexes = selectionModel->selectedIndexes();
	for(int i=0;i<indexes.size();i++){
		QModelIndex currentIndex = indexes.at(i);
		QVariant currentOperationStr = currentIndex.data(Qt::DisplayRole);
		_flowSelectedOperationsListModel->setData(QModelIndex(),currentOperationStr);
		qDebug()<<currentOperationStr;
	}*/
}

QVector<OperationDO*> FlowSchedulerDialog::getSelectedOperations()
{
	QVector<OperationDO*> ans;
	for ( int i = 0 ; i < _flowSelectedOperationsListModel->rowCount() ; ++i )
	{
		QVariant qvar = _flowSelectedOperationsListModel->index( i, 0 ).data( Qt::UserRole );
		if(qVariantCanConvert<OperationDO*>(qvar))
			ans.push_back(qVariantValue<OperationDO*>(qvar));
	}
	return ans;
}

QModelIndexList FlowSchedulerDialog::getCheckedPages(QModelIndexList lst)
{
	QModelIndexList ans;	

	for(int i=0;i<lst.size();i++)
	{		
		QModelIndex currentIndex = lst.at(i);
		if (currentIndex.data(Qt::CheckStateRole)!=0)
		{
			ans.push_back(currentIndex);
		}				
	}
	return ans;
}

void FlowSchedulerDialog::startFlow()
{
	//getCheckedPages();
	QVector<OperationDO*> selectedOperations = getSelectedOperations();

	ui.flowPagesTreeView->selectAll();
	QItemSelectionModel* pagesSelectionModel = ui.flowPagesTreeView->selectionModel();			
	QModelIndexList pagesIndexes = pagesSelectionModel->selectedIndexes();

	QModelIndexList checkedPagesIndexes = getCheckedPages(pagesIndexes);
	ui.flowPagesTreeView->clearSelection();

	for(int i=0;i<checkedPagesIndexes .size();i++){
		QModelIndex currentIndex = checkedPagesIndexes.at(i);
		if (qVariantCanConvert<PageDoc> (currentIndex.data(Qt::UserRole)))
		{
			QVariant currentPage = currentIndex.data(Qt::UserRole);
			PageDoc pd = qVariantValue<PageDoc>(currentPage);
			HdaMainFrame* mainFrame = (static_cast<HdaMainFrame*>(parent())); 		
			Page* page = pd.getPage();
			page->loadMat();

			HdaProgressBar* probar = new HdaProgressBar();
			probar->setValue(0);
			probar->setTitle(page->getName().c_str());			
			ui.verticalLayout->addWidget(probar);
			ui.verticalLayout->update();
			_progressBars.push_back(probar);
			mainFrame->getFlowManager()->addThread(pd.getPage(),selectedOperations,probar);
		}

	}
}
void FlowSchedulerDialog::moveUp()
{
	QModelIndexList indexes = ui.flowSelectedOperationsListView->selectionModel()->selectedIndexes();
	if(indexes.size()>0)
	{
		_flowSelectedOperationsListModel->setData(indexes.at(0),QVariant(),Qt::UserRole+1);
	}
}

void FlowSchedulerDialog::moveDown()
{
	QModelIndexList indexes = ui.flowSelectedOperationsListView->selectionModel()->selectedIndexes();
	if(indexes.size()>0)
	{
		_flowSelectedOperationsListModel->setData(indexes.at(0),QVariant(),Qt::UserRole+2);
	}
}

void FlowSchedulerDialog::cancelFlow()
{
	close();
}

void FlowSchedulerDialog::clearOperations()
{
	int rows = _flowSelectedOperationsListModel->rowCount();
	for(int i=0;i<rows;i++)
	{
		_flowSelectedOperationsListModel->removeRows(0, 1, QModelIndex());
	}
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


OperationDO* FlowSchedulerDialog::createOperationDO(QString type)
{	
	OperationDO* ans = new BinarizeOperationDO(type);
	_allOperationsDo.push_back(ans);
	return ans;
}

void FlowSchedulerDialog::showProperties(QModelIndex index)
{	
	//QModelIndexList indexes = ui.flowOperationsListView->selectionModel()->selectedIndexes();		
	
	if (index.isValid()) 
	{
		//QVariant qvar = index.model()->data(index,Qt::DisplayRole);
		//QString oper = qvar.toString();
		QVariant qvar = index.model()->data(index,Qt::UserRole);
		OperationDO* operDO;
		if (qVariantCanConvert<OperationDO*> (qvar))
		{							
			operDO = qVariantValue<OperationDO*>(qvar);
		}
		else 
		{			
			operDO = createOperationDO(index.model()->data(index,Qt::DisplayRole).toString());
		}
		_flowPropertiesModel->setOperationDO(operDO);	
		ui.flowPropertiesTableView->setModel(0);		
		ui.flowPropertiesTableView->setModel(_flowPropertiesModel);		

		/*
		OperationDO* operationDO = new OperationDO();
		operationDO->setOperationType(oper);
		if(_flowPropertiesModel)
			delete _flowPropertiesModel;
		_flowPropertiesModel = getOperationPropertiesModel(operationDO);
		ui.flowPropertiesTableView->setModel(_flowPropertiesModel);
		*/
	}
}

FlowPropertiesModel* FlowSchedulerDialog::getOperationPropertiesModel(OperationDO* operationDO)
{
	if(operationDO->getOperationType()==QString("Global Binarizer"))
	{
		return new FlowBinarizeModel(operationDO,this);
	}
	return new FlowPropertiesModel(operationDO,this);
}

void FlowSchedulerDialog::updateTree(TreeViewModel* updatedModel)
{
	_manuscriptTreeModel = updatedModel;
	ui.flowPagesTreeView->setModel(0);
	ui.flowPagesTreeView->setModel(_manuscriptTreeModel);	
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