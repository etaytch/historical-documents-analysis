#ifndef PAGECHOOSER_H
#define PAGECHOOSER_H

#include <QDialog>
#include "ui_pagechooser.h"
#include "treeviewmodel.h"

#include <QPair>

class PageChooser : public QDialog
{
	Q_OBJECT

public:
	PageChooser(QWidget *parent = 0);
	PageChooser(TreeViewModel *model1, TreeViewModel *model2 ,QWidget *parent = 0);
	QPair<PageDoc,PageDoc> getSelectedPages(){return _selectedPages;}
	~PageChooser();

public slots:
	void checkAccept();

private:
	Ui::PageChooser ui;
	TreeViewModel* _model1;
	TreeViewModel* _model2;
	QPair<PageDoc,PageDoc> _selectedPages;
};

#endif // PAGECHOOSER_H
