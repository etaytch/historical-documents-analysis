
#ifndef PAGEMDICHILD_H
#define PAGEMDICHILD_H

#include <QMdiSubWindow>
#include <QMessageBox>
#include <QApplication>
#include <QPixmap>
#include <QGraphicsView>
#include <QFileDialog>
#include <QCloseEvent>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include "framedraw.h"
#include "PageDoc.h"
#include "mdiPageScene.h"

class PageMdiChild : public QGraphicsView 
{
    Q_OBJECT

private:
	QString _curFile;
	QString _path;
	QPixmap _image;
	PageDoc _page;
	mdiPageScene _imageScene;
	QGraphicsPixmapItem _imagePixMap;

public:
	PageMdiChild(PageDoc& path, QWidget* parent);
	int getOriginalWidth();
	int getOriginalHeight();
	virtual void wheelEvent(QWheelEvent* event);
	void SetCenter(const QPointF& centerPoint);
	QPointF GetCenter();
    bool loadFile(const QString &fileName);
    bool save();
    bool saveAs();
	void setOriginalSize();
    bool saveFile(const QString &fileName);
	QPixmap getImage();
    QString friendlyCurrentFile();
    QString currentFile()		{ return _curFile; }
	QString getPath()			{return _path;}
    void setPath(QString path)	{ _path = path; }
	QVector<FrameDraw*> getFrames();
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	shows all graphic items. </summary>
	///
	/// <remarks>	Yair Offir, 1/8/2012. </remarks>		
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void showAllFrames();
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	unshows all graphic items. </summary>
	///
	/// <remarks>	Yair Offir, 1/8/2012. </remarks>		
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void removeAllFrames();
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	creates and adds a new rectangle. </summary>
	///
	/// <remarks>	Yair Offir, 1/8/2012. </remarks>		
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void addRectangle(int x, int y, int width, int height);
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	creates and adds a new polygon. </summary>
	///
	/// <remarks>	Yair Offir, 1/8/2012. </remarks>		
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void addPolygon(QVector<QPointF> points);
	//sets _action to ADDPOLY. when the next click will be performed, a new dot will be added to the poly.
	void setAddPolygon();
	//sets _action to DELETEPOINT. when the next click will be performed(if close enough), 
	//one of the polygons points will be deleted.
	void PageMdiChild::setDeletePoint();
	//sets _action to CHANGETOPOLY. when the next click will be performed, 
	//the clicked rectangle will be transformed into a polygon.
	void PageMdiChild::setChangeRectToPoly();	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	draws a new polygon (when one is created this function is called. </summary>
	///
	/// <remarks>	Yair Offir, 1/8/2012. </remarks>		
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void drawPolygon();
	////sets _action to ADDRECT. when the next click will be performed, a new rectangle will be added.
	void setAddRectangle();
	void setWordDetectorRectangle();
	//sets _action to REMOVE. when the next click will be performed, 
	//the clicked graphics item will be deleted.
	void setRemove();
	//sets _action to NONE
	void setNone();
	virtual ~PageMdiChild();

private:
	void setCurrentFile(const QString &fileName);
	QString strippedName(const QString &fullFileName);
	QPointF CurrentCenterPoint;
	
protected:
    void closeEvent(QCloseEvent *event);


};

#endif //PAGEMDICHILD_H