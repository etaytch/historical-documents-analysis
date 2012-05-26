#ifndef HDAPROGRESSBAR_H
#define HDAPROGRESSBAR_H

#include <QWidget>
#include "ui_hdaprogressbar.h"

class HdaProgressBar : public QWidget
{
	Q_OBJECT

public:
	HdaProgressBar(QWidget *parent = 0);
	void setProgressBarValue(int value);
	~HdaProgressBar();

private:
	Ui::HdaProgressBar ui;
};

#endif // HDAPROGRESSBAR_H
