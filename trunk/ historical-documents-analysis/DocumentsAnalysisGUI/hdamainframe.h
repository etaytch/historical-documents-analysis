#ifndef HDAMAINFRAME_H
#define HDAMAINFRAME_H
#pragma once

#include <QtGui/QMainWindow>
#include "ui_hdamainframe.h"
#include "thumbnailsmodel.h"
#include "gui_global.h"

class GUI_EXPORT HdaMainFrame : public QMainWindow
{
	Q_OBJECT

public:
	HdaMainFrame(QWidget *parent = 0, Qt::WFlags flags = 0);
	~HdaMainFrame();

private:
	Ui::HdaMainFrameClass ui;
	ThumbNailsModel* _manuscriptPagesModel;
	QMap<QString,QWidget>* _openPages;

};

#endif // HDAMAINFRAME_H
