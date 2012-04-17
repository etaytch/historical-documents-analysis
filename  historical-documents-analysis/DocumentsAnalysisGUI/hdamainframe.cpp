#include "hdamainframe.h"

HdaMainFrame::HdaMainFrame(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	manuscriptPagesModel = new ThumbNailsModel(this,"man"); 
	ui.thumbnailsView->setModel(manuscriptPagesModel);
}

HdaMainFrame::~HdaMainFrame()
{
	delete manuscriptPagesModel;
}
