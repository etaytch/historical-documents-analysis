#include "newmandialog.h"

createManuscriptDialog::createManuscriptDialog(ManuscriptDoc* man, QWidget *parent)
	: QDialog(parent)
{
	_manDoc = man;
	ui.setupUi(this);
}

void createManuscriptDialog::fillData()
{
	_manDoc->setTitle(ui.TitleLineEdit->text());
	_manDoc->setAuthor(ui.AuthorLineEdit->text());
	_manDoc->setCopyist(ui.CopyistLineEdit->text());
	_manDoc->setRegion(ui.RegionLineEdit->text());
	_manDoc->setLanguage(ui.LanguageLineEdit->text());
	_manDoc->setFontType(ui.FontTypeLineEdit->text());
	_manDoc->setManXmlPath(ui.pathLineEdit->text());
}

createManuscriptDialog::~createManuscriptDialog()
{

}
