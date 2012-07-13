#include "pagechooser.h"

#include <QTreeView>
#include <QMessageBox> 

PageChooser::PageChooser(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	_model1 = 0;
	_model2 = 0;
}

PageChooser::PageChooser(TreeViewModel* model1, TreeViewModel* model2, QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	_model1 = model1;
	_model2 = model2;
	ui.treeView1->setModel(_model1);
	ui.treeView2->setModel(_model2);
}
PageChooser::~PageChooser()
{

}


//need to take care of bugs!!!!
void PageChooser::checkAccept()
{
	if ((_model1!=0)&&(_model2!=0))
	{
		if ((ui.treeView1->selectionModel()->selectedIndexes().size()>=0) && 
			(ui.treeView2->selectionModel()->selectedIndexes().size()>=0) &&
			(qVariantCanConvert<PageDoc>(ui.treeView1->selectionModel()->selectedIndexes().at(0).data(Qt::UserRole)))&&
			(qVariantCanConvert<PageDoc>(ui.treeView2->selectionModel()->selectedIndexes().at(0).data(Qt::UserRole))))
		{
			_selectedPages.first = qVariantValue<PageDoc>(ui.treeView1->selectionModel()->selectedIndexes().at(0).data(Qt::UserRole));
			_selectedPages.second = qVariantValue<PageDoc>(ui.treeView2->selectionModel()->selectedIndexes().at(0).data(Qt::UserRole));
			accept();
		}
		else
		{
			 QMessageBox msgBox;
			 msgBox.setText("You didn't select page from each tree");
			 msgBox.setInformativeText("please select the pages you wish to compare.");
			 msgBox.setStandardButtons(QMessageBox::Ok);
			 msgBox.setDefaultButton(QMessageBox::Ok);
			 int ret = msgBox.exec();
		}
	}
}