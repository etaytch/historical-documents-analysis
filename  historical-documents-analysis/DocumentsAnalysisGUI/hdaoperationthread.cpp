#include "hdaoperationthread.h"

HdaOperationThread::HdaOperationThread(QObject *parent,Page* page,QStringList operations)
	: QThread(parent)
{
	_page=page;
	_operations=operations;
}

void HdaOperationThread::run()
{

}

HdaOperationThread::~HdaOperationThread()
{

}
