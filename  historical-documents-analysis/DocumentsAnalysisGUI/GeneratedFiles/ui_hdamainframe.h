/********************************************************************************
** Form generated from reading UI file 'hdamainframe.ui'
**
** Created: Mon 16. Apr 10:32:49 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HDAMAINFRAME_H
#define UI_HDAMAINFRAME_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDockWidget>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QListView>
#include <QtGui/QMainWindow>
#include <QtGui/QMdiArea>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QTreeView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HdaMainFrameClass
{
public:
    QAction *actionNewManuscript;
    QAction *actionOpen_manuscript;
    QAction *actionSave_alll;
    QAction *actionSave_current_file;
    QAction *actionAdd_page;
    QAction *actionRemove_page;
    QAction *actionAdd_manuscript;
    QAction *actionRemove_manuscript;
    QAction *actionQuit;
    QAction *actionQuick_Opertion;
    QAction *actionScedual_batch_job;
    QAction *actionHelp;
    QAction *actionAbout;
    QAction *actionSceduler;
    QAction *actionAlgorithms;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QMdiArea *mdiArea;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuManuscript;
    QMenu *menuView;
    QMenu *menuTools;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *ProjectTree;
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout_2;
    QTreeView *treeView;
    QDockWidget *CurrentManuscriptPages;
    QWidget *dockWidgetContents_2;
    QVBoxLayout *verticalLayout;
    QListView *listView;

    void setupUi(QMainWindow *HdaMainFrameClass)
    {
        if (HdaMainFrameClass->objectName().isEmpty())
            HdaMainFrameClass->setObjectName(QString::fromUtf8("HdaMainFrameClass"));
        HdaMainFrameClass->resize(740, 727);
        HdaMainFrameClass->setDocumentMode(false);
        actionNewManuscript = new QAction(HdaMainFrameClass);
        actionNewManuscript->setObjectName(QString::fromUtf8("actionNewManuscript"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/HdaMainFrame/Resources/toolBarIcons/Actions-document-properties-icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNewManuscript->setIcon(icon);
        actionOpen_manuscript = new QAction(HdaMainFrameClass);
        actionOpen_manuscript->setObjectName(QString::fromUtf8("actionOpen_manuscript"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/HdaMainFrame/Resources/toolBarIcons/Actions-document-open-icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen_manuscript->setIcon(icon1);
        actionSave_alll = new QAction(HdaMainFrameClass);
        actionSave_alll->setObjectName(QString::fromUtf8("actionSave_alll"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/HdaMainFrame/Resources/toolBarIcons/Actions-document-save-all-icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave_alll->setIcon(icon2);
        actionSave_current_file = new QAction(HdaMainFrameClass);
        actionSave_current_file->setObjectName(QString::fromUtf8("actionSave_current_file"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/HdaMainFrame/Resources/toolBarIcons/Actions-document-save-icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave_current_file->setIcon(icon3);
        actionAdd_page = new QAction(HdaMainFrameClass);
        actionAdd_page->setObjectName(QString::fromUtf8("actionAdd_page"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/HdaMainFrame/Resources/toolBarIcons/Actions-document-new-icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAdd_page->setIcon(icon4);
        actionRemove_page = new QAction(HdaMainFrameClass);
        actionRemove_page->setObjectName(QString::fromUtf8("actionRemove_page"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/HdaMainFrame/Resources/toolBarIcons/Actions-document-close-icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRemove_page->setIcon(icon5);
        actionAdd_manuscript = new QAction(HdaMainFrameClass);
        actionAdd_manuscript->setObjectName(QString::fromUtf8("actionAdd_manuscript"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/HdaMainFrame/Resources/toolBarIcons/Actions-tab-new-background-icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAdd_manuscript->setIcon(icon6);
        actionRemove_manuscript = new QAction(HdaMainFrameClass);
        actionRemove_manuscript->setObjectName(QString::fromUtf8("actionRemove_manuscript"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/HdaMainFrame/Resources/toolBarIcons/Actions-tab-close-other-icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRemove_manuscript->setIcon(icon7);
        actionQuit = new QAction(HdaMainFrameClass);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        actionQuick_Opertion = new QAction(HdaMainFrameClass);
        actionQuick_Opertion->setObjectName(QString::fromUtf8("actionQuick_Opertion"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/HdaMainFrame/Resources/toolBarIcons/Actions-quickopen-icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionQuick_Opertion->setIcon(icon8);
        actionScedual_batch_job = new QAction(HdaMainFrameClass);
        actionScedual_batch_job->setObjectName(QString::fromUtf8("actionScedual_batch_job"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/HdaMainFrame/Resources/toolBarIcons/Categories-applications-system-icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionScedual_batch_job->setIcon(icon9);
        actionHelp = new QAction(HdaMainFrameClass);
        actionHelp->setObjectName(QString::fromUtf8("actionHelp"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/HdaMainFrame/Resources/toolBarIcons/Misc-Help-icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionHelp->setIcon(icon10);
        actionAbout = new QAction(HdaMainFrameClass);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/HdaMainFrame/Resources/toolBarIcons/Actions-help-about-icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAbout->setIcon(icon11);
        actionSceduler = new QAction(HdaMainFrameClass);
        actionSceduler->setObjectName(QString::fromUtf8("actionSceduler"));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/HdaMainFrame/Resources/toolBarIcons/Actions-mail-mark-task-icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSceduler->setIcon(icon12);
        actionAlgorithms = new QAction(HdaMainFrameClass);
        actionAlgorithms->setObjectName(QString::fromUtf8("actionAlgorithms"));
        centralWidget = new QWidget(HdaMainFrameClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        mdiArea = new QMdiArea(centralWidget);
        mdiArea->setObjectName(QString::fromUtf8("mdiArea"));
        QFont font;
        font.setStrikeOut(false);
        mdiArea->setFont(font);
        mdiArea->setAcceptDrops(true);

        gridLayout->addWidget(mdiArea, 0, 0, 1, 1);

        HdaMainFrameClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(HdaMainFrameClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 740, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        menuManuscript = new QMenu(menuBar);
        menuManuscript->setObjectName(QString::fromUtf8("menuManuscript"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QString::fromUtf8("menuTools"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        HdaMainFrameClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(HdaMainFrameClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setIconSize(QSize(24, 24));
        HdaMainFrameClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(HdaMainFrameClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        HdaMainFrameClass->setStatusBar(statusBar);
        ProjectTree = new QDockWidget(HdaMainFrameClass);
        ProjectTree->setObjectName(QString::fromUtf8("ProjectTree"));
        ProjectTree->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        verticalLayout_2 = new QVBoxLayout(dockWidgetContents);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        treeView = new QTreeView(dockWidgetContents);
        treeView->setObjectName(QString::fromUtf8("treeView"));

        verticalLayout_2->addWidget(treeView);

        ProjectTree->setWidget(dockWidgetContents);
        HdaMainFrameClass->addDockWidget(static_cast<Qt::DockWidgetArea>(1), ProjectTree);
        CurrentManuscriptPages = new QDockWidget(HdaMainFrameClass);
        CurrentManuscriptPages->setObjectName(QString::fromUtf8("CurrentManuscriptPages"));
        CurrentManuscriptPages->setFeatures(QDockWidget::DockWidgetFeatureMask);
        CurrentManuscriptPages->setAllowedAreas(Qt::BottomDockWidgetArea|Qt::TopDockWidgetArea);
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QString::fromUtf8("dockWidgetContents_2"));
        verticalLayout = new QVBoxLayout(dockWidgetContents_2);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        listView = new QListView(dockWidgetContents_2);
        listView->setObjectName(QString::fromUtf8("listView"));
        listView->setFlow(QListView::LeftToRight);

        verticalLayout->addWidget(listView);

        CurrentManuscriptPages->setWidget(dockWidgetContents_2);
        HdaMainFrameClass->addDockWidget(static_cast<Qt::DockWidgetArea>(8), CurrentManuscriptPages);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuManuscript->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menuTools->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionNewManuscript);
        menuFile->addAction(actionOpen_manuscript);
        menuFile->addAction(actionSave_current_file);
        menuFile->addAction(actionSave_alll);
        menuFile->addAction(actionAdd_manuscript);
        menuFile->addAction(actionRemove_manuscript);
        menuFile->addAction(actionAdd_page);
        menuFile->addAction(actionRemove_page);
        menuFile->addAction(actionQuit);
        menuTools->addAction(actionScedual_batch_job);
        menuTools->addAction(actionQuick_Opertion);
        menuTools->addAction(actionSceduler);
        menuHelp->addAction(actionHelp);
        menuHelp->addAction(actionAbout);
        mainToolBar->addAction(actionNewManuscript);
        mainToolBar->addAction(actionOpen_manuscript);
        mainToolBar->addAction(actionSave_alll);
        mainToolBar->addAction(actionSave_current_file);
        mainToolBar->addAction(actionAdd_page);
        mainToolBar->addAction(actionRemove_page);
        mainToolBar->addAction(actionQuick_Opertion);
        mainToolBar->addAction(actionScedual_batch_job);
        mainToolBar->addAction(actionSceduler);
        mainToolBar->addAction(actionHelp);

        retranslateUi(HdaMainFrameClass);

        QMetaObject::connectSlotsByName(HdaMainFrameClass);
    } // setupUi

    void retranslateUi(QMainWindow *HdaMainFrameClass)
    {
        HdaMainFrameClass->setWindowTitle(QApplication::translate("HdaMainFrameClass", "Historical Documents Analysis", 0, QApplication::UnicodeUTF8));
        actionNewManuscript->setText(QApplication::translate("HdaMainFrameClass", "New Manuscript", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionNewManuscript->setToolTip(QApplication::translate("HdaMainFrameClass", "Create new manuscript", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionNewManuscript->setShortcut(QApplication::translate("HdaMainFrameClass", "Ctrl+N", 0, QApplication::UnicodeUTF8));
        actionOpen_manuscript->setText(QApplication::translate("HdaMainFrameClass", "Open manuscript", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionOpen_manuscript->setToolTip(QApplication::translate("HdaMainFrameClass", "Open manuscript", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionOpen_manuscript->setShortcut(QApplication::translate("HdaMainFrameClass", "Ctrl+O", 0, QApplication::UnicodeUTF8));
        actionSave_alll->setText(QApplication::translate("HdaMainFrameClass", "Save alll ", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionSave_alll->setToolTip(QApplication::translate("HdaMainFrameClass", "Save all", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionSave_alll->setShortcut(QApplication::translate("HdaMainFrameClass", "Ctrl+Shift+S", 0, QApplication::UnicodeUTF8));
        actionSave_current_file->setText(QApplication::translate("HdaMainFrameClass", "save current file", 0, QApplication::UnicodeUTF8));
        actionSave_current_file->setShortcut(QApplication::translate("HdaMainFrameClass", "Ctrl+S", 0, QApplication::UnicodeUTF8));
        actionAdd_page->setText(QApplication::translate("HdaMainFrameClass", "Add page", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionAdd_page->setToolTip(QApplication::translate("HdaMainFrameClass", "Add page", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionAdd_page->setShortcut(QApplication::translate("HdaMainFrameClass", "Ctrl+Shift+A", 0, QApplication::UnicodeUTF8));
        actionRemove_page->setText(QApplication::translate("HdaMainFrameClass", "Remove page", 0, QApplication::UnicodeUTF8));
        actionAdd_manuscript->setText(QApplication::translate("HdaMainFrameClass", "Add manuscript", 0, QApplication::UnicodeUTF8));
        actionRemove_manuscript->setText(QApplication::translate("HdaMainFrameClass", "Remove manuscript", 0, QApplication::UnicodeUTF8));
        actionQuit->setText(QApplication::translate("HdaMainFrameClass", "Quit", 0, QApplication::UnicodeUTF8));
        actionQuick_Opertion->setText(QApplication::translate("HdaMainFrameClass", "Quick Opertion", 0, QApplication::UnicodeUTF8));
        actionScedual_batch_job->setText(QApplication::translate("HdaMainFrameClass", "Scedual batch job", 0, QApplication::UnicodeUTF8));
        actionHelp->setText(QApplication::translate("HdaMainFrameClass", "Help", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("HdaMainFrameClass", "About", 0, QApplication::UnicodeUTF8));
        actionSceduler->setText(QApplication::translate("HdaMainFrameClass", "Sceduler", 0, QApplication::UnicodeUTF8));
        actionAlgorithms->setText(QApplication::translate("HdaMainFrameClass", "Algorithms", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("HdaMainFrameClass", "File", 0, QApplication::UnicodeUTF8));
        menuEdit->setTitle(QApplication::translate("HdaMainFrameClass", "Edit", 0, QApplication::UnicodeUTF8));
        menuManuscript->setTitle(QApplication::translate("HdaMainFrameClass", "Manuscript", 0, QApplication::UnicodeUTF8));
        menuView->setTitle(QApplication::translate("HdaMainFrameClass", "View", 0, QApplication::UnicodeUTF8));
        menuTools->setTitle(QApplication::translate("HdaMainFrameClass", "Tools", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("HdaMainFrameClass", "Help", 0, QApplication::UnicodeUTF8));
        mainToolBar->setWindowTitle(QApplication::translate("HdaMainFrameClass", "Main Tool Bar", 0, QApplication::UnicodeUTF8));
        ProjectTree->setWindowTitle(QApplication::translate("HdaMainFrameClass", "Project Tree", 0, QApplication::UnicodeUTF8));
        CurrentManuscriptPages->setWindowTitle(QApplication::translate("HdaMainFrameClass", "Manuscript Pages", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class HdaMainFrameClass: public Ui_HdaMainFrameClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HDAMAINFRAME_H
