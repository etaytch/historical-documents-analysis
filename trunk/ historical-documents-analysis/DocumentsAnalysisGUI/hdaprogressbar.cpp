#include "hdaprogressbar.h"

HdaProgressBar::HdaProgressBar(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

void HdaProgressBar::setValue(int value)
{
	ui.progressBar->setValue(value);
}
HdaProgressBar::~HdaProgressBar()
{

}
