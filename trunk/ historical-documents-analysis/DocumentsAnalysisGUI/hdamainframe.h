#ifndef HDAMAINFRAME_H
#define HDAMAINFRAME_H
#pragma once

#include <QtGui/QMainWindow>
#include <QString>
#include "ui_hdamainframe.h"
#include "FlowSchedulerDialog.h"
#include "thumbnailsmodel.h"
#include "treeviewmodel.h"
#include "pagemdichild.h"
#include "xmlreader.h"
#include "gui_global.h"
#include "HdaFlowManager.h"

class FlowSchedulerDialog;
class GUI_EXPORT HdaMainFrame : public QMainWindow
{
	Q_OBJECT

public:
	HdaMainFrame(QWidget *parent = 0, Qt::WFlags flags = 0);
	HdaFlowManager* getFlowManager();
	~HdaMainFrame();

public slots:
	void LoadManuscript(QModelIndex index);
	void openImageWindowFromThumbView(QModelIndex index);
	void openImageWindowFromTreeView(QModelIndex index);

	//Actions slots 
	void openProject();	
	void openManuscript();	
	void removeManuscript();
	void addManuscript();
	void addPage();
	void removePage();
	void save();
	void saveAll();
	void quit();
	void help();
	void setChiledToOriginalSize();
	void cascadePages();
	void tilePages();
	void openFlowDialog();	

private:
	Ui::HdaMainFrameClass ui;
	FlowSchedulerDialog* _flowSchedulerDialog;
	ProjectDoc _project;
	ThumbNailsModel* _manuscriptPagesModel;
	TreeViewModel* _manuscriptTreeModel;
	
	HdaFlowManager* _flowManager;
	

private: //methods
	void modelsInit();
	void cleanProject();
};

#endif // HDAMAINFRAME_H
