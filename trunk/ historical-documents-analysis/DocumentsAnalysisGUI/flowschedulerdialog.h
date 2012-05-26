#ifndef FLOWSCHEDULERDIALOG_H
#define FLOWSCHEDULERDIALOG_H

#include <QDialog>
#include "ui_flowschedulerdialog.h"
#include "TreeViewModel.h"
#include "flowOperationsModel.h"
#include "HdaOperationThread.h"

class FlowSchedulerDialog : public QDialog
{
	Q_OBJECT

public:
	FlowSchedulerDialog(QWidget *parent = 0);
	FlowSchedulerDialog(QWidget *parent, TreeViewModel* model);
	~FlowSchedulerDialog();

private:
	Ui::FlowSchedulerDialog ui;	
	TreeViewModel* _manuscriptTreeModel;
	FlowOperationsModel* _flowOperationsListModel;
	FlowOperationsModel* _flowSelectedOperationsListModel;
	QStringList getSelectedOperations();


public slots:
	void addOperation();
	void startFlow();
	void cancelFlow();
};

#endif // FLOWSCHEDULERDIALOG_H
