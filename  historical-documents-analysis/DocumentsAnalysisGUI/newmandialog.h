#ifndef NEWMANDIALOG_H
#define NEWMANDIALOG_H

#include <QDialog>
#include "ui_newmandialog.h"
#include "manuscriptdoc.h"

class createManuscriptDialog : public QDialog
{
	Q_OBJECT

public:
	createManuscriptDialog(ManuscriptDoc* man, QWidget *parent = 0);
	~createManuscriptDialog();

private:
	ManuscriptDoc* _manDoc;
	Ui::createManuscriptDialog ui;

public  slots:
	void fillData();
};

#endif // NEWMANDIALOG_H
