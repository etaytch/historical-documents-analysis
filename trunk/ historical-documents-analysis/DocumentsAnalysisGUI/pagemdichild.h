
#ifndef PAGEMDICHILD_H
#define PAGEMDICHILD_H

#include <QMdiSubWindow>
#include <QMessageBox>
#include <QApplication>
#include <QPixmap>
#include <QLabel>
#include <QFileDialog>
#include <QCloseEvent>


class PageMdiChild : public QLabel 
{
    Q_OBJECT

private:
	QString _curFile;
	QString _path;
	QPixmap _image;

public:
	PageMdiChild(QString path, QWidget* parent);
	int getOriginalWidth();
	int getOriginalHeight();
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


	virtual ~PageMdiChild();

private:
	void setCurrentFile(const QString &fileName);
	QString strippedName(const QString &fullFileName);

protected:
    void closeEvent(QCloseEvent *event);


};

#endif //PAGEMDICHILD_H
