#include "hdamainframe.h"
#include <QMdiSubWindow>
#include <QDebug>
#include "xmlwriter.h"
#include "Defs.h"

HdaMainFrame::HdaMainFrame(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	_project.setName("Default Project");
	modelsInit();
	ui.Properties_dock->setVisible(false);
	_flowManager = new HdaFlowManager(this);
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
		QString pagePath = page.getPage()->getName().c_str();
		
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
	_flowSchedulerDialog = new FlowSchedulerDialog(this,this->_manuscriptTreeModel);
	connect(_flowManager,SIGNAL(updatePage(Page*)),_flowSchedulerDialog,SLOT(updatePage(Page*)));
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