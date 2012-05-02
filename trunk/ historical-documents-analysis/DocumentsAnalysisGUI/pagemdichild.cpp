#include "PageMdiChild.h"

PageMdiChild::PageMdiChild(QWidget* parent) : QLabel(parent), _image() 
{
	 setAttribute(Qt::WA_DeleteOnClose);
	 setBackgroundRole(QPalette::Base);
	 setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
     setScaledContents(true);
}

int PageMdiChild::getOriginalWidth()
{
	return _image.width();
}

int PageMdiChild::getOriginalHeight()
{
	return _image.height();
}

bool PageMdiChild::loadFile(const QString &fileName)
{
	QApplication::setOverrideCursor(Qt::WaitCursor);
    if (!_image.load(fileName)) 
	{
        QMessageBox::warning(this, tr("MDI"),
                             tr("Cannot read image %1")
                             .arg(fileName));
        return false;
    }
	setPixmap(_image);
    QApplication::restoreOverrideCursor();
    setCurrentFile(fileName);
	setOriginalSize();
	return true;
}

bool PageMdiChild::save()
{
   return saveFile(_curFile);
}

bool PageMdiChild::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),_curFile);
    if (fileName.isEmpty())
        return false;
    return saveFile(fileName);
}

bool PageMdiChild::saveFile(const QString &fileName)
{
	return true;
}

QPixmap PageMdiChild::getImage()
{
	return _image;
}
void PageMdiChild::closeEvent(QCloseEvent *p_event)
{

    p_event->accept();

}

void PageMdiChild::setOriginalSize()
{
	((QMdiSubWindow*)parentWidget())->resize(getOriginalWidth(),getOriginalHeight());
}

void PageMdiChild::setCurrentFile(const QString &fileName)
{
    _curFile = QFileInfo(fileName).canonicalFilePath();
    setWindowModified(false);
    setWindowTitle(friendlyCurrentFile() + "[*]");
}

QString PageMdiChild::friendlyCurrentFile()
{
    return strippedName(_curFile);
}

QString PageMdiChild::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

PageMdiChild::~PageMdiChild()
{
}
