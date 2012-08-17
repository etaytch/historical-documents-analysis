#include "hdaflowmanager.h"

HdaFlowManager::HdaFlowManager(QObject *parent)
	: QObject(parent)
{	
	connect(this,SIGNAL(callSaveAndReload()),parent,SLOT(saveAndReload()));
}

void HdaFlowManager::addThread(Page* page,QVector<OperationDO*> operations,HdaProgressBar* probar)
{	
	HdaOperationThread* hdaot = new HdaOperationThread(this,page,operations);
	connect(hdaot,SIGNAL(setValue(int)),probar,SLOT(setValue(int)));
	connect(hdaot,SIGNAL(threadDone(HdaOperationThread*)),this,SLOT(removeThread(HdaOperationThread*)));
	connect(hdaot,SIGNAL(saveAndReload()),this,SLOT(saveAndReload()));
	_threads.push_back(hdaot);
	hdaot->start();
}

void HdaFlowManager::saveAndReload()
{
	emit callSaveAndReload();
}

void HdaFlowManager::removeThread(HdaOperationThread* thread)
{
	int pos=-1;	
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
	if(thread)
		delete thread;
}

QVector<HdaOperationThread*> HdaFlowManager::getThreads()
{
	return _threads;
}

HdaFlowManager::~HdaFlowManager()
{

}
