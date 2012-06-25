#include "PageMdiChild.h"
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QRect>

PageMdiChild::PageMdiChild(QString path, QWidget* parent) : 
QGraphicsView(), 
	_image(), 
	_imageScene(this), 
	_imagePixMap()
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

QVector<FrameDraw*> PageMdiChild::getFrames()
{
	return this->_imageScene.getFrames();
}

void PageMdiChild::showAllFrames()
{
	this->_imageScene.showAll();
}

void PageMdiChild::removeAllFrames()
{
	this->_imageScene.removeAll();
}

void PageMdiChild::addRectangle(int x, int y, int width, int height)
{
	FrameDraw* newFrame = this->_imageScene.addRectangle(QPointF(x,y));
	newFrame->setWidth(width);
	newFrame->setHeight(height);
}

PageMdiChild::~PageMdiChild()
{
}
