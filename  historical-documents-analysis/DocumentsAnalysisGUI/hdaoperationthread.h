#ifndef HDAOPERATIONTHREAD_H
#define HDAOPERATIONTHREAD_H

#include <QThread>
#include <QString>
#include <QVector>
#include <opencv/cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include "GlobalBinarizer.h"
#include "LocalBinarizer.h"
#include "OtsulBinarizer.h"
#include "RadialBinarizer.h"
#include "Page.h"
#include "OperationDO.h"



class HdaOperationThread : public QThread
{
	Q_OBJECT

public:	
	HdaOperationThread(QObject *parent,Page* page,QVector<OperationDO*> operations);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Starts the thread. </summary>
	///
	/// <remarks>	Etay Tchechanovski, 1/5/2012. </remarks>	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void run();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Perform the Operation. </summary>
	///
	/// <remarks>	Etay Tchechanovski, 1/5/2012. </remarks>	
	/// <param name="bin">	[in] The Binarizer. </param>
	/// <param name="page">	[in] The Page. </param>
	/// <returns>	The DImage* result. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	DImage* doOperation(Binarizer* bin, Page* page);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Returns Operation. </summary>
	///
	/// <remarks>	Etay Tchechanovski, 1/5/2012. </remarks>	
	/// <param name="operation">	[in] The OperationDO. </param>
	/// <returns>	The Operation. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	Binarizer* getOperation(OperationDO* operation);	

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Returns the Page. </summary>
	///
	/// <remarks>	Etay Tchechanovski, 1/5/2012. </remarks>		
	/// <returns>	The Page. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	Page* getPage();

	~HdaOperationThread();

private:
	Page* _page;
	QVector<OperationDO*> _operations;

public slots:

	void onDone();

signals:
	void setValue(int);
	void threadDone(HdaOperationThread*);
	void saveAndReload();
};

#endif // HDAOPERATIONTHREAD_H
