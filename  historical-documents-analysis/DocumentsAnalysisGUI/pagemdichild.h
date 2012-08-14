
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
	void showAllFrames();
	void removeAllFrames();
	void addRectangle(int x, int y, int width, int height);
	void addPolygon(QVector<QPointF> points);
	void setAddPolygon();
	void PageMdiChild::setDeletePoint();
	void PageMdiChild::setChangeRectToPoly();	
	void drawPolygon();
	void setAddRectangle();
	void setWordDetectorRectangle();
	void setRemove();
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