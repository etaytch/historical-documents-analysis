#ifndef HDAFLOWMANAGER_H
#define HDAFLOWMANAGER_H

#include <QObject>
#include <QVector>
#include "HdaOperationThread.h"
#include "Page.h"
#include "HdaProgressBar.h"
#include "OperationDO.h"

class HdaFlowManager : public QObject
{
	Q_OBJECT

public:
	HdaFlowManager(QObject *parent);
	void addThread(Page* page,QVector<OperationDO*> operations,HdaProgressBar* probar);
	QVector<HdaOperationThread*> getThreads();
	~HdaFlowManager();

private:
	QVector<HdaOperationThread*> _threads;

signals:
	void updatePage(Page*);
	void callSaveAndReload();
public slots:	
	void removeThread(HdaOperationThread*);
	void saveAndReload();
};

#endif // HDAFLOWMANAGER_H
