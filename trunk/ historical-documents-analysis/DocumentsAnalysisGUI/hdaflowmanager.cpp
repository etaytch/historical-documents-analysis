#include "hdaflowmanager.h"

HdaFlowManager::HdaFlowManager(QObject *parent)
	: QObject(parent)
{	
}

void HdaFlowManager::addThread(Page* page,QStringList operations,HdaProgressBar* probar)
{	
	HdaOperationThread* hdaot = new HdaOperationThread(this,page,operations);
	connect(hdaot,SIGNAL(setValue(int)),probar,SLOT(setValue(int)));
	connect(hdaot,SIGNAL(threadDone(HdaOperationThread*)),this,SLOT(removeThread(HdaOperationThread*)));
	_threads.push_back(hdaot);
	hdaot->start();
}

void HdaFlowManager::removeThread(HdaOperationThread* thread)
{
	int pos=-1;
	emit updatePage(thread->getPage());
	for(int i=0;i<_threads.size();i++)
	{
		if(_threads.at(i)==thread)
		{
			pos=i;
			break;
		}
	}
	if(pos>=0)
	{
		_threads.remove(pos);
	}
}

QVector<HdaOperationThread*> HdaFlowManager::getThreads()
{
	return _threads;
}

HdaFlowManager::~HdaFlowManager()
{

}
