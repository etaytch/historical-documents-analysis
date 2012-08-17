#include "hdamainframe.h"
#include "xmlwriter.h"
#include "Defs.h"
#include "hdadiffwindow.h"
#include "pagechooser.h"

#include <QMdiSubWindow>
#include <QDebug>

HdaMainFrame::HdaMainFrame(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	_project.setName("Default Project");
	modelsInit();
	ui.Properties_dock->setVisible(false);
	_flowManager = new HdaFlowManager(this);
	_flowSchedulerDialog=0;
	
}


/*************************/
/********  SLOTS *********/
/*************************/

void HdaMainFrame::openImageWindowFromThumbView(QModelIndex index)
{
	if (qVariantCanConvert<PageDoc> (index.data(Qt::UserRole)))
	{
		PageDoc page = qVariantValue<PageDoc>(index.data(Qt::UserRole));
		QString pagePath = page.getPage()->getName().c_str();
		foreach (QMdiSubWindow *window, ui.mdiArea->subWindowList())
		{
			if ((static_cast<PageMdiChild*>(window->widget()))->getPath() == pagePath)
			{
				window->setFocus();
				return;
			}
		}
		page.getPage()->loadMat();
		PageMdiChild* p = new PageMdiChild(page,ui.mdiArea);
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
		QString pagePath = page.getPage()->getName().c_str();
		
		foreach (QMdiSubWindow *window, ui.mdiArea->subWindowList())
		{
			if ((static_cast<PageMdiChild*>(window->widget()))->getPath() == pagePath)
			{
				window->setFocus();
				return;
			}
		}

		page.getPage()->loadMat();
		PageMdiChild* p = new PageMdiChild(page,ui.mdiArea);
		ui.mdiArea->addSubWindow(p);
		p->loadFile(pagePath);
		p->show();

	}
}

//TODO
void HdaMainFrame::openProperties(QModelIndex index)
{
	if (qVariantCanConvert<QString> (index.data(Qt::UserRole)))
	{
		QString manName = qVariantValue<QString>(index.data());
		
		_manuscriptPropertiesModel = new ManuscriptPropertiesModel(&_project.getManuscriptAt(manName),index,this);
		_manuscriptPropertiesDelegete = new ManuscriptPropertiesDelegate();
		ui.propertiesTableView->setModel(_manuscriptPropertiesModel);
		ui.propertiesTableView->setItemDelegate(_manuscriptPropertiesDelegete);
		ui.Properties_dock->setVisible(true);
	}
	else if (qVariantCanConvert<PageDoc> (index.data(Qt::UserRole)))
	{
		PageDoc pd = qVariantValue<PageDoc>(index.data(Qt::UserRole));
	}
}


void HdaMainFrame::LoadManuscript(QModelIndex index)
{
	QApplication::setOverrideCursor(Qt::WaitCursor);
	if (qVariantCanConvert<QString> (index.data(Qt::UserRole)))
	{
		QString manName = qVariantValue<QString>(index.data());
		ManuscriptDoc man = _project.getManuscriptAt(manName);
		_manuscriptPagesModel = new ThumbNailsModel(_manuscriptTreeModel->getRootItem(),_project,ui.thumbnailsView);
		ui.thumbnailsView->setModel(_manuscriptPagesModel);
		ui.CurrentManuscriptPages->setWindowTitle(manName+" Pages");
	}	
	QApplication::restoreOverrideCursor();
}


/***************************/
/********  ACTIONS *********/
/***************************/

void HdaMainFrame::openProject(QString fileName)
{
	cleanProject();	
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

void HdaMainFrame::openProject()
{
	_filename = QFileDialog::getOpenFileName(this,"Open project","","Project File (*.xml)");
	openProject(_filename);
}

void HdaMainFrame::openManuscript()
{
	cleanProject();
	addManuscript();
}

void HdaMainFrame::removeManuscript()
{

}

void HdaMainFrame::binarize()
{
	
}

void HdaMainFrame::addManuscript()
{
	QString fileName = QFileDialog::getOpenFileName(this,"Open Manuscript","","Manuscript File (*.xml)");
	if (fileName.isEmpty() || fileName.isNull()) return;

	//create a default project for the manuscript
	_project.setName(DEFAULT_PROJECT);
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
	QMap<QString,QString>::iterator manPathIter;
	saveProject();
	for(manPathIter=_project.getPaths().begin();
		manPathIter!= _project.getPaths().end();
		manPathIter++)
	{

		QString path = manPathIter.value();
		QString name = manPathIter.key();
		saveManuscript(path,name);
	}
}

void HdaMainFrame::saveProjectAs()
{

	QString fileName = QFileDialog::getSaveFileName(this,"Save Project as","","Project File (*.xml)");
	if (fileName.isEmpty() || fileName.isNull()) return;
	ProjectDoc pr = _manuscriptTreeModel->_project;

	//manuscript parsing
	if (XmlWriter::saveProjectToXml(fileName,pr)!= tinyxml2::XML_NO_ERROR)
	{
		QMessageBox::critical(this, "Error",
                              QString("%1 project seems to be currapted corrupted.")
							  .arg(pr.getName()));
		return;
	}
}

void HdaMainFrame::saveProject()
{
	ProjectDoc pr = _manuscriptTreeModel->_project;
	if (pr.getName()!=DEFAULT_PROJECT)
	{
		XmlWriter::saveProjectToXml(pr.getName()+".xml",pr);
	}
	else
		saveProjectAs();
	
}

void HdaMainFrame::saveManuscript(QString path,QString manName)
{
	XmlWriter::saveManuscriptToXml(path,_project.getManuscripts()[manName]);
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


void HdaMainFrame::drawRectangle()
{
	qobject_cast<PageMdiChild*>
		(ui.mdiArea->currentSubWindow()->widget())->setAddRectangle();
}

void HdaMainFrame::callWordDetector()
{
	qobject_cast<PageMdiChild*>
		(ui.mdiArea->currentSubWindow()->widget())->setWordDetectorRectangle();
}



void HdaMainFrame::drawPolygon(bool start)
{
	PageMdiChild* child = qobject_cast<PageMdiChild*>
								(ui.mdiArea->currentSubWindow()->widget()); 
	if (start)
	{
		child->setAddPolygon();
	}
	else
	{
		child->drawPolygon();
	}
}

void HdaMainFrame::deleteFrame()
{
	
	PageMdiChild* child = qobject_cast<PageMdiChild*>
								(ui.mdiArea->currentSubWindow()->widget());
	child->setRemove();

}

void HdaMainFrame::showFrames(bool show)
{
	PageMdiChild* child = qobject_cast<PageMdiChild*>
								(ui.mdiArea->currentSubWindow()->widget()); 
	if (show)
	{
		child->showAllFrames();
	}
	else
	{
		child->removeAllFrames();
	}

}

void HdaMainFrame::openDiff()
{
	PageChooser* pc = new PageChooser(this->_manuscriptTreeModel,this->_manuscriptTreeModel,this);
	if (pc->exec()==QDialog::Accepted)
	{
		HdaDiffWindow* diffWindow = new HdaDiffWindow(pc->getSelectedPages().first,pc->getSelectedPages().second ,this);
		diffWindow->exec();
		delete diffWindow;
	}
	delete pc;
}


void HdaMainFrame::openFlowDialog()
{	
	if(_flowSchedulerDialog==0)
	{
		_flowSchedulerDialog = new FlowSchedulerDialog(this,this->_manuscriptTreeModel);
		connect(_flowManager,SIGNAL(updatePage(Page*)),_flowSchedulerDialog,SLOT(updatePage(Page*)));
	}
	_flowSchedulerDialog->show();
}

HdaFlowManager* HdaMainFrame::getFlowManager()
{
	return _flowManager;
}


HdaMainFrame::~HdaMainFrame()
{
	if (!_manuscriptPagesModel)
		delete _manuscriptPagesModel;
	if (!_manuscriptPagesModel)
		delete _manuscriptTreeModel;
	if (!_flowManager)
		delete _flowManager;
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
	_manuscriptTreeModel = new TreeViewModel(_project,ui.treeView);
	ui.treeView->setModel(_manuscriptTreeModel);

	if (_project.getManuscriptCount()>0)
	{
		_manuscriptPagesModel = new ThumbNailsModel(_manuscriptTreeModel->getRootItem(),_project,ui.thumbnailsView);
	}
	else
	{
		_manuscriptPagesModel = new ThumbNailsModel(ui.thumbnailsView);
	}
	
	connect(_manuscriptTreeModel, 
			SIGNAL(updateThumbnails(PageDoc,TreeItem*,int)),
            _manuscriptPagesModel, 
			SLOT(updateThumbnail(PageDoc,TreeItem*,int)));

	ui.thumbnailsView->setModel(_manuscriptPagesModel);
}

void HdaMainFrame::cleanProject()
{
	_project = ProjectDoc();
	_manuscriptTreeModel = 0;
	_manuscriptPagesModel = 0;
}

void HdaMainFrame::saveAndReload()
{
	_lock.lock();	
	saveAll();
	openProject(_filename);
	//emit updateFlowDialogTree(_manuscriptTreeModel);
	_lock.unlock();
}