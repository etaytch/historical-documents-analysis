#ifndef HDAFLOWMANAGER_H
#define HDAFLOWMANAGER_H

#include <QObject>
#include <QVector>
#include "HdaOperationThread.h"
#include "Page.h"
#include "HdaProgressBar.h"

class HdaFlowManager : public QObject
{
	Q_OBJECT

public:
	HdaFlowManager(QObject *parent);
	void addThread(Page* page,QStringList operations,HdaProgressBar* probar);
	QVector<HdaOperationThread*> getThreads();
	~HdaFlowManager();

private:
	QVector<HdaOperationThread*> _threads;

signals:
	void updatePage(Page*);
public slots:
	void removeThread(HdaOperationThread*);
};

#endif // HDAFLOWMANAGER_H
