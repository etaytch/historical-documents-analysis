#ifndef HDAPROGRESSBAR_H
#define HDAPROGRESSBAR_H

#include <QWidget>
#include "ui_hdaprogressbar.h"

class HdaProgressBar : public QWidget
{
	Q_OBJECT

public:
	HdaProgressBar(QWidget *parent = 0);	
	~HdaProgressBar();
	int getValue();

private:
	Ui::HdaProgressBar ui;

public slots:
	void setValue(int);
};

#endif // HDAPROGRESSBAR_H
