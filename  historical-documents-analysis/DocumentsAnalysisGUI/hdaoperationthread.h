#ifndef HDAOPERATIONTHREAD_H
#define HDAOPERATIONTHREAD_H

#include <QThread>
#include <QString>
#include <QStringList>
#include "Page.h"

#include "ImageOperation.h"

class HdaOperationThread : public QThread
{
	Q_OBJECT

public:
	HdaOperationThread(QObject *parent,Page* page,QStringList operations);
	void run();
	~HdaOperationThread();

private:
	Page* _page;
	QStringList _operations;
};

#endif // HDAOPERATIONTHREAD_H
