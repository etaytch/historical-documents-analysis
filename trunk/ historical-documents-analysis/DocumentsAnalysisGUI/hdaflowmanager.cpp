#include "hdaflowmanager.h"

HdaFlowManager::HdaFlowManager(QObject *parent)
	: QObject(parent)
{	
}

void HdaFlowManager::addThread(Page* page,QStringList operations,HdaProgressBar* probar)
{	
	HdaOperationThread* hdaot = new HdaOperationThread(this,page,operations);
	connect(hdaot,SIGNAL(setValue(int)),probar,SLOT(setValue(int)));
	_threads.push_back(hdaot);
	hdaot->start();
}

QVector<HdaOperationThread*> HdaFlowManager::getThreads()
{
	return _threads;
}

HdaFlowManager::~HdaFlowManager()
{

}
