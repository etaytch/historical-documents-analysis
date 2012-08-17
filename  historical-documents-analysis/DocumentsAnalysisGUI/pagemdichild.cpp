#include "PageMdiChild.h"
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QImage>
#include <QRect>
#include "RectFrame.h"

PageMdiChild::PageMdiChild(PageDoc& page, QWidget* parent) : 
QGraphicsView(), 
	_imageScene(this,page), 
	_imagePixMap()
{
	 Mat d;
	 setAttribute(Qt::WA_DeleteOnClose);
	 setBackgroundRole(QPalette::Base);
	 setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	 this->setScene(&this->_imageScene);
	 _page = page;
	 cvtColor(_page.getPage()->getMat(),d,CV_BGR2RGB);
     QImage image((uchar*)d.data, d.cols, d.rows,QImage::Format_RGB888);
	 _image = QPixmap::fromImage(image); 
	 _path = page.getPage()->getName().c_str();		
	 SetCenter(QPointF(500.0, 500.0));
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
	RectFrame* newFrame = this->_imageScene.addRectangle(QPointF(x,y),width,height);
	newFrame->setWidth(width);
	newFrame->setHeight(height);
}

void PageMdiChild::addPolygon(QVector<QPointF> points)
{
	this->_imageScene.addPolygon(points);
}

void PageMdiChild::setAddPolygon()
{
	this->_imageScene._action = mdiPageScene::RectAction::ADDPOLY;
}

void PageMdiChild::setAddRectangle()
{
	this->_imageScene._action = mdiPageScene::RectAction::ADDRECT;
}

void PageMdiChild::setWordDetectorRectangle()
{
	this->_imageScene._action = mdiPageScene::RectAction::ADDWORDRECT;
}

void PageMdiChild::setRemove()
{
	this->_imageScene._action = mdiPageScene::RectAction::REMOVE;
}

void PageMdiChild::setNone()
{
	this->_imageScene._action = mdiPageScene::RectAction::NONE;
}

void PageMdiChild::setDeletePoint()
{
	this->_imageScene._action = mdiPageScene::RectAction::DELETEPOINT;
}

void PageMdiChild::setChangeRectToPoly()
{
	this->_imageScene._action = mdiPageScene::RectAction::CHANGETOPOLY;
}

void PageMdiChild::drawPolygon()
{
	this->_imageScene.DrawPoly();
}

QPointF PageMdiChild::GetCenter() { return CurrentCenterPoint; }

void PageMdiChild::SetCenter(const QPointF& centerPoint) {
    //Get the rectangle of the visible area in scene coords
    QRectF visibleArea = mapToScene(rect()).boundingRect();
 
    //Get the scene area
    QRectF sceneBounds = sceneRect();
 
    double boundX = visibleArea.width() / 2.0;
    double boundY = visibleArea.height() / 2.0;
    double boundWidth = sceneBounds.width() - 2.0 * boundX;
    double boundHeight = sceneBounds.height() - 2.0 * boundY;
 
    //The max boundary that the centerPoint can be to
    QRectF bounds(boundX, boundY, boundWidth, boundHeight);
 
    if(bounds.contains(centerPoint)) {
        //We are within the bounds
        CurrentCenterPoint = centerPoint;
    } else {
        //We need to clamp or use the center of the screen
        if(visibleArea.contains(sceneBounds)) {
            //Use the center of scene ie. we can see the whole scene
            CurrentCenterPoint = sceneBounds.center();
        } else {
 
            CurrentCenterPoint = centerPoint;
 
            //We need to clamp the center. The centerPoint is too large
            if(centerPoint.x() > bounds.x() + bounds.width()) {
                CurrentCenterPoint.setX(bounds.x() + bounds.width());
            } else if(centerPoint.x() < bounds.x()) {
                CurrentCenterPoint.setX(bounds.x());
            }
 
            if(centerPoint.y() > bounds.y() + bounds.height()) {
                CurrentCenterPoint.setY(bounds.y() + bounds.height());
            } else if(centerPoint.y() < bounds.y()) {
                CurrentCenterPoint.setY(bounds.y());
            }
 
        }
    }
 
    //Update the scrollbars
    centerOn(CurrentCenterPoint);
}

void PageMdiChild::wheelEvent(QWheelEvent* event)
{
	if (!(QApplication::keyboardModifiers() && Qt::ControlModifier)) return;
	//Get the position of the mouse before scaling, in scene coords
    QPointF pointBeforeScale(mapToScene(event->pos()));
 
    //Get the original screen centerpoint
    QPointF screenCenter = GetCenter(); //CurrentCenterPoint; //(visRect.center());
 
    //Scale the view ie. do the zoom
    double scaleFactor = 1.15; //How fast we zoom
    if(event->delta() > 0) {
        //Zoom in
        scale(scaleFactor, scaleFactor);
    } else {
        //Zooming out
        scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    }
 
    //Get the position after scaling, in scene coords
    QPointF pointAfterScale(mapToScene(event->pos()));
 
    //Get the offset of how the screen moved
    QPointF offset = pointBeforeScale - pointAfterScale;
 
    //Adjust to the new center for correct zooming
    QPointF newCenter = screenCenter + offset;
    SetCenter(newCenter);
}

PageMdiChild::~PageMdiChild()
{
}
