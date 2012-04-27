#ifndef HDAMAINFRAME_H
#define HDAMAINFRAME_H
#pragma once

#include <QtGui/QMainWindow>
#include "ui_hdamainframe.h"
#include "thumbnailsmodel.h"
#include "treeviewmodel.h"
#include "pagemdichild.h"
#include "gui_global.h"

class GUI_EXPORT HdaMainFrame : public QMainWindow
{
	Q_OBJECT

public:
	HdaMainFrame(QWidget *parent = 0, Qt::WFlags flags = 0);
	~HdaMainFrame();

public slots:
	void openImageWindow(QModelIndex index);
	void loadProjectFromXml(QModelIndex index);	
	void setChiledToOriginalSize();
	void LoadManuscript(QModelIndex index);
	
private:
	Ui::HdaMainFrameClass ui;
	ThumbNailsModel* _manuscriptPagesModel;
	TreeViewModel* _manuscriptTreeModel;
};

#endif // HDAMAINFRAME_H
