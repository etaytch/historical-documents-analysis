#include "hdaoperationthread.h"
#include <stdio.h>
#include <QFileInfo>
#include "BinarizeOperationDO.h"

using namespace cv;

HdaOperationThread::HdaOperationThread(QObject *parent,Page* page,QVector<OperationDO*> operations)
	: QThread(parent)
{
	_page=page;
	_operations=operations;
	connect(this,SIGNAL(finished()),this,SLOT(onDone()));
}

Mat HdaOperationThread::doOperation(Binarizer* bin, Page* page)
{
	return di::binarize(*bin, page->getMat());
}

Binarizer* HdaOperationThread::getOperation(OperationDO* oper)
{
	if(oper->getOperationType()==QString("Global Binarizer"))
	{		
		return new GlobalBinarizer(((BinarizeOperationDO*)oper)->getThershold());
	}	
	if(oper->getOperationType()==QString("Otsul Binarizer"))
	{
		return new OtsulBinarizer();
	}
	if(oper->getOperationType()==QString("Radial Binarizer"))
	{
		return new RadialBinarizer();
	}
}


void HdaOperationThread::run()
{
	Page* workingPage = _page;

	int counter=0;

	for(int i=0;i<_operations.size();i++)
	{
		// current OperationDO
		OperationDO* oper = _operations.at(i);
		// current operation object
		Binarizer* bin = getOperation(oper);
		// resulted DImage
		Mat newImage = doOperation(bin,workingPage/*,f*/);

		// creating new page for the resulted DImage
		Page* newPage = new Page();
		newPage->setIndex(1);
		newPage->setMat(newImage);

		// saving to file
		QFileInfo fi(workingPage->getName().c_str());	
		QString originalSuffix = fi.completeSuffix();
		vector<int> compression_params;

		compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
		compression_params.push_back(9);
		// setting new page' filename
		QString newPageName = workingPage->getName().c_str();
		newPageName = newPageName.replace("."+originalSuffix,QString("_"+oper->getOperationType()+"_threshold_")+QString::number(oper->getThershold())+QString(".png")/*+originalSuffix*/);
		newPage->setName(newPageName.toStdString());
		workingPage->addPage(newPage);	

		try{
			imwrite(newPage->getName(), newPage->getMat(), compression_params);
		}
	
		catch (std::runtime_error& ex) {
			fprintf(stderr, "Exception converting image to PNG format: %s\n", ex.what());        
		}

		// sets the ProgressBar, currently for demonstration only
		for(int i=1;i<=(100/_operations.size());i++)
		{
			Sleep(33);
			counter++;
			emit setValue(counter);
		}

		// moving to the next operation
		workingPage = newPage;
		Sleep(2000);
	}
	// save project and reload
	emit saveAndReload();
	
}

void HdaOperationThread::onDone()
{
	emit setValue(100);
	emit threadDone(this);
}

Page* HdaOperationThread::getPage()
{
	return _page;
}

HdaOperationThread::~HdaOperationThread()
{

}
