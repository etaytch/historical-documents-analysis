#ifndef FLOWSCHEDULERDIALOG_H
#define FLOWSCHEDULERDIALOG_H

#include <QDialog>
#include <QVector>
#include "ui_flowschedulerdialog.h"
#include "TreeViewModel.h"
#include "flowOperationsModel.h"
#include "HdaOperationThread.h"
#include "hdaprogressbar.h"

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
	QVector<HdaProgressBar*> _progressBars;

public slots:
	void addOperation();
	void startFlow();
	void cancelFlow();
	void clearDone();
	void updatePage(Page*);
};

#endif // FLOWSCHEDULERDIALOG_H
