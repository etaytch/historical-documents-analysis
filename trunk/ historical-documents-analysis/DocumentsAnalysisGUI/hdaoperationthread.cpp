#include "hdaoperationthread.h"
#include "GlobalBinarizer.h"
#include <opencv/cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
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

void HdaOperationThread::run()
{
	GlobalBinarizer gb(77);
	DImage* d=_page->binarize(gb);
	
	Page* newPage = new Page();
	newPage->setMat(d->getMat());

	QFileInfo fi(_page->getName().c_str());	
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
	QString newPageName = _page->getName().c_str();
	newPageName = newPageName.replace("."+originalSuffix,QString("_globalBinarizer")+QString(".png")/*+originalSuffix*/);
	newPage->setName(newPageName.toStdString());
	_page->addPage(newPage);	
	
	try{
		imwrite(newPage->getName(), newPage->getMat(), compression_params);
	}
	
    catch (std::runtime_error& ex) {
        fprintf(stderr, "Exception converting image to PNG format: %s\n", ex.what());        
    }

	for(int i=1;i<=99;i++)
	{
		Sleep(100);
		emit setValue(i);
	}

}

void HdaOperationThread::onDone()
{
	emit setValue(100);
}

HdaOperationThread::~HdaOperationThread()
{

}
