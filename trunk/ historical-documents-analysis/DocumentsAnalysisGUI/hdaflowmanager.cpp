#include "hdaflowmanager.h"

HdaFlowManager::HdaFlowManager(QObject *parent)
	: QObject(parent)
{	
}

void HdaFlowManager::addThread(Page* page,QStringList operations)
{
	HdaOperationThread* hdaot = new HdaOperationThread(this,page,operations);
	_threads.push_back(hdaot);
	hdaot->run();
}

QVector<HdaOperationThread*> HdaFlowManager::getThreads()
{
	return _threads;
}

HdaFlowManager::~HdaFlowManager()
{

}
