#include "hdaprogressbar.h"

HdaProgressBar::HdaProgressBar(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

void HdaProgressBar::setProgressBarValue(int value)
{
	ui.progressBar->setValue(value);
}
HdaProgressBar::~HdaProgressBar()
{

}
