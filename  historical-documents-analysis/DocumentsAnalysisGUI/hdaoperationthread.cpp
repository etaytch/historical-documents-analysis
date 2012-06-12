#include "hdaoperationthread.h"
#include <stdio.h>
#include <QFileInfo>

using namespace cv;

HdaOperationThread::HdaOperationThread(QObject *parent,Page* page,QStringList operations)
	: QThread(parent)
{
	_page=page;
	_operations=operations;
	connect(this,SIGNAL(finished()),this,SLOT(onDone()));
}

DImage* HdaOperationThread::doOperation(Binarizer* bin, Page* page/*,_fUpdateValue f*/)
{
//	(this->*f)(1);
	return page->binarize(*bin);
}

Binarizer* HdaOperationThread::getOperation(QString oper)
{
	if(oper==QString("Global Binarizer"))
	{		
		return new GlobalBinarizer(150);
	}	
	if(oper==QString("Otsul Binarizer"))
	{
		return new OtsulBinarizer();
	}
	if(oper==QString("Radial Binarizer"))
	{
		return new RadialBinarizer();
	}
}
void HdaOperationThread::updateValue(int val)
{

}

void HdaOperationThread::run()
{
	Page* workingPage = _page;

	int counter=0;

	for(int i=0;i<_operations.size();i++)
	{
//		_fUpdateValue f = updateValue;
		//(this->*f)(1);
		// current operation as QString
		QString oper = _operations.at(i);
		// current operation object
		Binarizer* bin = getOperation(oper);
		// resulted DImage
		DImage* newImage = doOperation(bin,workingPage/*,f*/);

		// creating new page for the resulted DImage
		Page* newPage = new Page();
		newPage->setMat(newImage->getMat());

		QFileInfo fi(workingPage->getName().c_str());	
		QString originalSuffix = fi.completeSuffix();
		vector<int> compression_params;
    
		/*if((originalSuffix.toLower()=="jpg")||(originalSuffix.toLower()=="jpeg"))
		{
			compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);		
		}
		else if(originalSuffix.toLower()=="png")
		{
			compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
			compression_params.push_back(9);    	
		}	*/

		compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
		compression_params.push_back(9);
		// setting new page' filename
		QString newPageName = workingPage->getName().c_str();
		newPageName = newPageName.replace("."+originalSuffix,QString("_"+oper)+QString(".png")/*+originalSuffix*/);
		newPage->setName(newPageName.toStdString());
		workingPage->addPage(newPage);	

		try{
			imwrite(newPage->getName(), newPage->getMat(), compression_params);
		}
	
		catch (std::runtime_error& ex) {
			fprintf(stderr, "Exception converting image to PNG format: %s\n", ex.what());        
		}

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