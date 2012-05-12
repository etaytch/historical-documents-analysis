#ifndef HDAMAINFRAME_H
#define HDAMAINFRAME_H
#pragma once

#include <QtGui/QMainWindow>
#include <QString>
#include "ui_hdamainframe.h"
#include "thumbnailsmodel.h"
#include "treeviewmodel.h"
#include "pagemdichild.h"
#include "xmlreader.h"
#include "gui_global.h"


class GUI_EXPORT HdaMainFrame : public QMainWindow
{
	Q_OBJECT

public:
	HdaMainFrame(QWidget *parent = 0, Qt::WFlags flags = 0);
	~HdaMainFrame();

public slots:
	void openImageWindowFromThumbView(QModelIndex index);
	void openImageWindowFromTreeView(QModelIndex index);
	void openProject();	
	void setChiledToOriginalSize();
	void cascadePages();
	void tilePages();
	void LoadManuscript(QModelIndex index);

	
private:
	Ui::HdaMainFrameClass ui;
	ThumbNailsModel* _manuscriptPagesModel;
	ProjectDoc _project;
	TreeViewModel* _manuscriptTreeModel;
};

#endif // HDAMAINFRAME_H
