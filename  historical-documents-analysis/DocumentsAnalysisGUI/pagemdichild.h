
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
	QPixmap _image;
	void setCurrentFile(const QString &fileName);
	QString strippedName(const QString &fullFileName);


public:
    PageMdiChild();
    bool loadFile(const QString &fileName);
    bool save();
    bool saveAs();
	void setOriginalSize();
    bool saveFile(const QString &fileName);
	QPixmap getImage();
    QString userFriendlyCurrentFile();
    QString currentFile() { return _curFile; }
	virtual ~PageMdiChild();

protected:
    void closeEvent(QCloseEvent *event);


};

#endif //PAGEMDICHILD_H
