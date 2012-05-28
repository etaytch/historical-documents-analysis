#ifndef HDAOPERATIONTHREAD_H
#define HDAOPERATIONTHREAD_H

#include <QThread>
#include <QString>
#include <QStringList>
#include <opencv/cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include "GlobalBinarizer.h"
#include "LocalBinarizer.h"
#include "OtsulBinarizer.h"
#include "RadialBinarizer.h"
#include "Page.h"



class HdaOperationThread : public QThread
{
	Q_OBJECT

public:
	//typedef void (HdaOperationThread::*_fUpdateValue)  (int);
	HdaOperationThread(QObject *parent,Page* page,QStringList operations);
	void run();
	DImage* doOperation(Binarizer* bin, Page* page/*,_fUpdateValue f*/);
	Binarizer* getOperation(QString oper);
	void updateValue(int);
	Page* getPage();

	~HdaOperationThread();

private:
	Page* _page;
	QStringList _operations;

public slots:
	void onDone();

signals:
	void setValue(int);
	void threadDone(HdaOperationThread*);
};

#endif // HDAOPERATIONTHREAD_H
