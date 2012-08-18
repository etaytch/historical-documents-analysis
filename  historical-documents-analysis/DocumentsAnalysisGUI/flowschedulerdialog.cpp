#include "flowschedulerdialog.h"


#include <qprogressbar.h>
#include "qDebug.h"
#include "hdamainframe.h"
#include "OperationDO.h"
#include "BinarizeOperationDO.h"
#include <QModelIndex>

FlowSchedulerDialog::FlowSchedulerDialog(QWidget *parent,TreeViewModel* model)
	: QDialog(parent)
{
	ui.setupUi(this);			
	_flowOperationsListModel = new FlowOperationsListModel(this);
	_flowSelectedOperationsListModel = new FlowOperationsDOModel(this,1);
	_flowPropertiesModel= new FlowPropertiesModel(this);
	_manuscriptTreeModel = model;
	ui.flowPagesTreeView->setModel(_manuscriptTreeModel);

	ui.flowOperationsListView->setModel(_flowOperationsListModel);
	ui.flowSelectedOperationsListView->setModel(_flowSelectedOperationsListModel);
	ui.flowPropertiesTableView->setModel(_flowPropertiesModel);

	// updates pages tree when a job is done
	connect(parent,SIGNAL(updateFlowDialogTree(TreeViewModel*)),this,SLOT(updateTree(TreeViewModel*)));
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
	// takes the current OperationDO from the _flowPropertiesModel and adds it to the 
	// _flowSelectedOperationsListModel 	 
	QVariant qvar = _flowPropertiesModel->data(QModelIndex(),Qt::UserRole);
	if (qVariantCanConvert<OperationDO*> (qvar))
	{						
			_flowSelectedOperationsListModel->setData(QModelIndex(),qvar);			
	}
	_flowPropertiesModel->clearProperties();
	ui.flowOperationsListView->clearSelection();
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
	QVector<OperationDO*> selectedOperations = getSelectedOperations();

	ui.flowPagesTreeView->selectAll();
	QItemSelectionModel* pagesSelectionModel = ui.flowPagesTreeView->selectionModel();			
	QModelIndexList pagesIndexes = pagesSelectionModel->selectedIndexes();

	QModelIndexList checkedPagesIndexes = getCheckedPages(pagesIndexes);
	ui.flowPagesTreeView->clearSelection();

	/*  for each selected page:
		- load the Mat
		- add ProgressBar to the current jobs view
		- create a thread and start it
	*/
	QSize sz(340, 35);
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
						
			QListWidgetItem* s = new QListWidgetItem(QString(""),ui.listWidget);			
            s->setSizeHint(sz);

			ui.listWidget->addItem(s);
			ui.listWidget->setItemWidget(s,probar);


			//ui.verticalLayout->addWidget(probar);
			//ui.verticalLayout->update();
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
	QVector<QListWidgetItem*> itemsToDelete;
	QVector<HdaProgressBar*> probarsToKeep;
	int size = ui.listWidget->count();
	int i=0;
	while(i<ui.listWidget->count())
	{
		QListWidgetItem* item = ui.listWidget->item(i);
		HdaProgressBar* probar = (HdaProgressBar*)ui.listWidget->itemWidget(item);		
		if(probar->getValue()>=100)
		{
			//itemsToDelete.push_back(item);
			delete ui.listWidget->takeItem(i);
			delete probar;
		}
		else
		{
			i++;
			probarsToKeep.push_back(probar);
		}
	}	
	_progressBars = probarsToKeep;	
}


OperationDO* FlowSchedulerDialog::createOperationDO(QString type)
{	
	OperationDO* ans = new BinarizeOperationDO(type);
	_allOperationsDo.push_back(ans);
	return ans;
}

void FlowSchedulerDialog::showProperties(QModelIndex index)
{		
	if (index.isValid()) 
	{		
		QVariant qvar = index.model()->data(index,Qt::UserRole);
		OperationDO* operDO;
		// if the user selected an operation from the selectedOperations - take the exist OperationDO
		if (qVariantCanConvert<OperationDO*> (qvar))
		{							
			operDO = qVariantValue<OperationDO*>(qvar);
		}
		// otherwise, create a new OperationDO
		else 
		{			
			operDO = createOperationDO(index.model()->data(index,Qt::DisplayRole).toString());
		}
		_flowPropertiesModel->setOperationDO(operDO);	
		ui.flowPropertiesTableView->setModel(0);		
		ui.flowPropertiesTableView->setModel(_flowPropertiesModel);		
	}
}

void FlowSchedulerDialog::updateTree(TreeViewModel* updatedModel)
{
	_manuscriptTreeModel = updatedModel;
	ui.flowPagesTreeView->setModel(0);
	ui.flowPagesTreeView->setModel(_manuscriptTreeModel);	
}
