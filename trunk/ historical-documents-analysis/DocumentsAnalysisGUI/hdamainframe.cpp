#include "hdamainframe.h"

HdaMainFrame::HdaMainFrame(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	_openPages = new QMap<QString,QWidget>();
	_manuscriptPagesModel = new ThumbNailsModel(this,"man/Pages"); 
	ui.thumbnailsView->setModel(_manuscriptPagesModel);
}

HdaMainFrame::~HdaMainFrame()
{
	delete _manuscriptPagesModel;
}
