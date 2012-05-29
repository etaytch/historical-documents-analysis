#include "PageMdiChild.h"
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QRect>

PageMdiChild::PageMdiChild(QString path, QWidget* parent) : QGraphicsView(), _image(), _imageScene(this), _imagePixMap(), _lastRect(0), rectDraw(false)
{
	 setAttribute(Qt::WA_DeleteOnClose);
	 setBackgroundRole(QPalette::Base);
	 setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	 this->setScene(&this->_imageScene);
	 _path = path;
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
        QMessageBox::warning(this, tr("Error"),
                             tr("Cannot read image %1")
                             .arg(fileName));
		QApplication::restoreOverrideCursor();
		return false;
    }
	this->_imagePixMap.setPixmap(_image);
	this->_imageScene.addItem(&_imagePixMap);

	
	//test
	this->_lastDraw = new FrameDraw(&_imageScene);
	this->_imageScene.addItem(this->_lastDraw);
	this->_lastDraw = new FrameDraw(&_imageScene);
	this->_imageScene.addItem(this->_lastDraw);
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
