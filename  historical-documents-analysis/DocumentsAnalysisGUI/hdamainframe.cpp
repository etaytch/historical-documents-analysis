#include "hdamainframe.h"
#include <QMdiSubWindow>


HdaMainFrame::HdaMainFrame(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	//_openPages = new QMap<QString,PageMdiChild>();
	_manuscriptPagesModel = new ThumbNailsModel(this,"man/Pages"); 
	ui.thumbnailsView->setModel(_manuscriptPagesModel);	
}

void HdaMainFrame::openImageWindow(QModelIndex index)
{
	PageMdiChild* p = new PageMdiChild();
	QString pagePath = _manuscriptPagesModel->getPagePath(index);
	p->loadFile(pagePath);
	ui.mdiArea->addSubWindow(p);
	p->show();
	//_openPages->insert(pagePath,p);
}


HdaMainFrame::~HdaMainFrame()
{
	QMap<QString, PageMdiChild*>::iterator iter;
	
	/*
	for(iter =_openPages->begin(); iter!=_openPages->end(); iter++)
	{
		delete (*iter);
	}
	delete _manuscriptPagesModel;
	*/		
}
