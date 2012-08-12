#ifndef FLOWSCHEDULERDIALOG_H
#define FLOWSCHEDULERDIALOG_H

#include <QDialog>
#include <QVector>
#include <QModelIndexList>
#include "ui_flowschedulerdialog.h"
#include "TreeViewModel.h"
#include "flowOperationsModel.h"
#include "flowOperationsListModel.h"
#include "FlowPropertiesModel.h"
#include "HdaOperationThread.h"
#include "hdaprogressbar.h"

class FlowSchedulerDialog : public QDialog
{
	Q_OBJECT

public:
	FlowSchedulerDialog(QWidget *parent = 0);
	FlowPropertiesModel* getOperationPropertiesModel(OperationDO* operationDO);
	FlowSchedulerDialog(QWidget *parent, TreeViewModel* model);
	~FlowSchedulerDialog();

private:
	Ui::FlowSchedulerDialog ui;	
	TreeViewModel* _manuscriptTreeModel;
	FlowOperationsListModel* _flowOperationsListModel;
	FlowOperationsModel* _flowSelectedOperationsListModel;
	FlowPropertiesModel* _flowPropertiesModel;
	QVector<HdaProgressBar*> _progressBars;

	QModelIndexList getCheckedPages(QModelIndexList lst);
	QVector<OperationDO*> getSelectedOperations();
	OperationDO* createOperationDO(QString type);
	

public slots:
	void addOperation();
	void startFlow();
	void cancelFlow();
	void clearDone();
	void moveUp();
	void moveDown();
	void updatePage(Page*);
	void showProperties(QModelIndex index);
};

#endif // FLOWSCHEDULERDIALOG_H

