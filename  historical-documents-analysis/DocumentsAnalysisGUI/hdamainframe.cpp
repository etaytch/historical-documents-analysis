#include "hdamainframe.h"
#include <QMdiSubWindow>


HdaMainFrame::HdaMainFrame(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);	
}


/*************************/
/********  SLOTS *********/
/*************************/

void HdaMainFrame::openImageWindowFromThumbView(QModelIndex index)
{
	if (qVariantCanConvert<QString> (index.data(Qt::UserRole)))
	{
		QString pagePath = qVariantValue<QString>(index.data(Qt::UserRole));
		foreach (QMdiSubWindow *window, ui.mdiArea->subWindowList())
		{
			if ((static_cast<PageMdiChild*>(window->widget()))->getPath() == pagePath)
			{
				window->setFocus();
				return;
			}
		}
		PageMdiChild* p = new PageMdiChild(pagePath,ui.mdiArea);
		ui.mdiArea->addSubWindow(p);
		p->loadFile(pagePath);
		p->show();

	}

}

void HdaMainFrame::openImageWindowFromTreeView(QModelIndex index)
{
	if (qVariantCanConvert<PageDoc> (index.data(Qt::UserRole)))
	{
		PageDoc page = qVariantValue<PageDoc>(index.data(Qt::UserRole));
		QString pagePath = _project.getManuscriptAt(page.getManuscriptName()).getPagesDirPath()+
															"/"+page.getPage()->getName().c_str();
		
		foreach (QMdiSubWindow *window, ui.mdiArea->subWindowList())
		{
			if ((static_cast<PageMdiChild*>(window->widget()))->getPath() == pagePath)
			{
				window->setFocus();
				return;
			}
		}
		PageMdiChild* p = new PageMdiChild(pagePath,ui.mdiArea);
		ui.mdiArea->addSubWindow(p);
		p->loadFile(pagePath);
		p->show();

	}
}


void HdaMainFrame::LoadManuscript(QModelIndex index)
{
	QApplication::setOverrideCursor(Qt::WaitCursor);
	if (qVariantCanConvert<QString> (index.data(Qt::UserRole)))
	{
		QString manName = qVariantValue<QString>(index.data());
		ManuscriptDoc man = _project.getManuscriptAt(manName);
		_manuscriptPagesModel = new ThumbNailsModel(man,ui.thumbnailsView);
		ui.thumbnailsView->setModel(_manuscriptPagesModel);
		ui.CurrentManuscriptPages->setWindowTitle(manName+" Pages");
	}	
	QApplication::restoreOverrideCursor();
}


void HdaMainFrame::openProject()
{
	QString fileName = QFileDialog::getOpenFileName(this,"Open project","","Project File (*.xml)");
	
	//project parsing
	if (XmlReader::getProjectFromXml(fileName,_project)!= tinyxml2::XML_NO_ERROR)
	{
		QMessageBox::warning(this, "Error",
                             QString("%1 isn't a project file, or it is corrupted.")
							 .arg(QFileInfo(fileName).fileName()));
		return;
	}
	
	//manuscripts parsing
	QMap<QString,QString>::iterator manPathIter;
	for(manPathIter=_project.getPaths().begin();
		manPathIter!= _project.getPaths().end();
		manPathIter++)
	{
		QString path = manPathIter.value();
		QString name = manPathIter.key();
		XmlReader::getManuscriptFromXml(path,_project.getManuscripts()[name]);
	}

	//tree init:
	this->_manuscriptTreeModel = new TreeViewModel(_project,ui.treeView);
	ui.treeView->setModel(this->_manuscriptTreeModel);

}


/***************************/
/********  ACTIONS *********/
/***************************/

void HdaMainFrame::setChiledToOriginalSize()
{
	 qobject_cast<PageMdiChild*>
		(ui.mdiArea->currentSubWindow()->widget())->setOriginalSize();
}


void HdaMainFrame::cascadePages()
{
	ui.mdiArea->cascadeSubWindows();
}

void HdaMainFrame::tilePages()
{
	ui.mdiArea->tileSubWindows();
}

HdaMainFrame::~HdaMainFrame()
{
	QMap<QString, PageMdiChild*>::iterator iter;
}

