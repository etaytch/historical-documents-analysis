#include "hdamainframe.h"
#include <QMdiSubWindow>


HdaMainFrame::HdaMainFrame(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	_project.setName("Default Project");
	modelsInit();
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


/***************************/
/********  ACTIONS *********/
/***************************/

void HdaMainFrame::openProject()
{
	cleanProject();
	QString fileName = QFileDialog::getOpenFileName(this,"Open project","","Project File (*.xml)");
	if (fileName.isEmpty() || fileName.isNull()) return;

	//project parsing
	if (XmlReader::getProjectFromXml(fileName,_project)!= tinyxml2::XML_NO_ERROR)
	{
		QMessageBox::critical(this, "Error",
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
	modelsInit();
}

void HdaMainFrame::openManuscript()
{
	cleanProject();
	addManuscript();
}

void HdaMainFrame::removeManuscript()
{

}

void HdaMainFrame::addManuscript()
{
	QString fileName = QFileDialog::getOpenFileName(this,"Open Manuscript","","Manuscript File (*.xml)");
	if (fileName.isEmpty() || fileName.isNull()) return;

	//create a default project for the manuscript
	_project.setName("Default Project");
	_project.addManuscriptPath(fileName,fileName);
	//manuscript parsing
	if (XmlReader::getManuscriptFromXml(fileName,_project.getManuscripts()[fileName])!= tinyxml2::XML_NO_ERROR)
	{
		QMessageBox::critical(this, "Error",
                             QString("%1 isn't a manuscript file, or it is corrupted.")
							 .arg(QFileInfo(fileName).fileName()));
		_project.removeManuscript(fileName);
		return;
	}
	//manuscript name update
	QString manTitle = _project.getManuscripts()[fileName].getTitle();
	if (_project.renameManuscript(fileName,_project.getManuscripts()[fileName].getTitle())!=NO_PROJ_ERROR)
	{
		QMessageBox::warning(this, "Error", "The project already contains \""+manTitle+"\",\n the operation wil be ignored.");
		_project.removeManuscript(fileName);
	}

	modelsInit();
}

void HdaMainFrame::addPage()
{

}

void HdaMainFrame::removePage()
{

}
	 
void HdaMainFrame::save()
{

}

void HdaMainFrame::saveAll()
{

}

void HdaMainFrame::help()
{

}

void HdaMainFrame::quit()
{

}

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


/***********************************/
/********  PRIVATE METHODS *********/
/***********************************/

void HdaMainFrame::modelsInit()
{
	if (!_manuscriptTreeModel)
	{
		delete _manuscriptTreeModel;
	}
	this->_manuscriptTreeModel = new TreeViewModel(_project,ui.treeView);
	ui.treeView->setModel(this->_manuscriptTreeModel);
	if (_project.getManuscriptCount()>0)
	{
		_manuscriptPagesModel = new ThumbNailsModel(_project.getManuscriptAt(0),ui.thumbnailsView);
	}
	else
	{
		_manuscriptPagesModel = new ThumbNailsModel(ui.thumbnailsView);
	}
	ui.thumbnailsView->setModel(_manuscriptPagesModel);
}

void HdaMainFrame::cleanProject()
{
	_project = ProjectDoc();
	_manuscriptTreeModel = 0;
	_manuscriptPagesModel = 0;
}

void HdaMainFrame::openFlowDialog()
{

}

HdaMainFrame::~HdaMainFrame()
{
	if (!_manuscriptPagesModel)
		delete _manuscriptPagesModel;
	if (!_manuscriptPagesModel)
		delete _manuscriptTreeModel;
}

