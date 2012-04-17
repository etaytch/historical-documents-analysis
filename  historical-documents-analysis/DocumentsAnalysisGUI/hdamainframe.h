#ifndef HDAMAINFRAME_H
#define HDAMAINFRAME_H

#include <QtGui/QMainWindow>
#include "ui_hdamainframe.h"
#include "thumbnailsmodel.h"

class HdaMainFrame : public QMainWindow
{
	Q_OBJECT

public:
	HdaMainFrame(QWidget *parent = 0, Qt::WFlags flags = 0);
	~HdaMainFrame();

private:
	Ui::HdaMainFrameClass ui;
	ThumbNailsModel* manuscriptPagesModel;

};

#endif // HDAMAINFRAME_H
