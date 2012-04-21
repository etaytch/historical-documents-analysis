#include "hdamainframe.h"
#include <QMdiSubWindow>


HdaMainFrame::HdaMainFrame(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	_manuscriptPagesModel = new ThumbNailsModel(this,"man/Pages");
	ui.thumbnailsView->setModel(_manuscriptPagesModel);
	//tree init:

}

void HdaMainFrame::openImageWindow(QModelIndex index)
{
	PageMdiChild* p = new PageMdiChild(ui.mdiArea);
	QString pagePath = _manuscriptPagesModel->getPagePath(index);
	ui.mdiArea->addSubWindow(p);

	p->loadFile(pagePath);
	p->show();
}

void HdaMainFrame::loadProjectFromXml(QModelIndex index)
{

}

void HdaMainFrame::setChiledToOriginalSize()
{
	 qobject_cast<PageMdiChild*>
		(ui.mdiArea->currentSubWindow()->widget())->setOriginalSize();
}


HdaMainFrame::~HdaMainFrame()
{
	QMap<QString, PageMdiChild*>::iterator iter;
}
