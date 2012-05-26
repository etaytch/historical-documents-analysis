#ifndef HDAFLOWMANAGER_H
#define HDAFLOWMANAGER_H

#include <QObject>
#include <QVector>
#include "HdaOperationThread.h"
#include "Page.h"

class HdaFlowManager : public QObject
{
	Q_OBJECT

public:
	HdaFlowManager(QObject *parent);
	void addThread(Page* page,QStringList operations);
	QVector<HdaOperationThread*> getThreads();
	~HdaFlowManager();

private:
	QVector<HdaOperationThread*> _threads;

signals:
	void addWidget(HdaOperationThread*);
};

#endif // HDAFLOWMANAGER_H
