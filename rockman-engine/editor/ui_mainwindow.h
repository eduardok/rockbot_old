/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Wed Aug 11 19:48:57 2010
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QToolBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "editorarea.h"
#include "editortilepallete.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAbout;
    QAction *actionCopy;
    QAction *actionPaste;
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionQuit;
    QAction *actionSave;
    QAction *actionNormal_Edit;
    QAction *actionLock_Edit;
    QAction *actionEraser;
    QAction *actionAdd;
    QAction *actionFill;
    QAction *actionLink;
    QAction *actionStairs;
    QAction *actionEdit_NPC;
    QAction *actionEdit_Tileset;
    QAction *actionLayer_Level;
    QAction *actionOne;
    QAction *actionTwo;
    QAction *actionThree;
    QAction *actionAdd_Object;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QToolBox *toolBox;
    QWidget *page_map;
    QWidget *verticalWidget;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *comboBox;
    QHBoxLayout *horizontalLayout_4;
    QComboBox *mapListCombo;
    QPushButton *pushButton;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_2;
    EditorTilePallete *pallete;
    QWidget *Terrain;
    QListWidget *listWidget_2;
    QWidget *page_npc;
    QListWidget *listWidget;
    QPushButton *editNPCButton;
    QPushButton *newNPCButton;
    QWidget *page_Link;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout_2;
    QComboBox *link_orientation_combobox;
    QLabel *label_2;
    QLabel *label_3;
    QSpinBox *link_size_spinbox;
    QLabel *label_4;
    QCheckBox *link_bidi_checkbox;
    QLabel *label_5;
    QCheckBox *link_isdoor_checkbox;
    QWidget *page_objects;
    QPushButton *editObjectButton;
    QPushButton *newObjectButton;
    QListWidget *objectListWidget;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    EditorArea *editArea;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QToolBar *editToolBar;
    QMenuBar *menuBar;
    QMenu *menuFILE;
    QMenu *menuHelp;
    QMenu *menuEdit;
    QMenu *menuView;
    QMenu *menuLevel;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(869, 645);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionCopy = new QAction(MainWindow);
        actionCopy->setObjectName(QString::fromUtf8("actionCopy"));
        actionPaste = new QAction(MainWindow);
        actionPaste->setObjectName(QString::fromUtf8("actionPaste"));
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/toolbar_icons/New"), QSize(), QIcon::Normal, QIcon::On);
        actionNew->setIcon(icon);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/toolbar_icons/Open"), QSize(), QIcon::Normal, QIcon::Off);
        icon1.addFile(QString::fromUtf8(":/toolbar_icons/Save"), QSize(), QIcon::Normal, QIcon::On);
        actionOpen->setIcon(icon1);
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/toolbar_icons/Save"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon2);
        actionNormal_Edit = new QAction(MainWindow);
        actionNormal_Edit->setObjectName(QString::fromUtf8("actionNormal_Edit"));
        actionNormal_Edit->setCheckable(true);
        actionNormal_Edit->setChecked(true);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/toolbar_icons/draw-freehand.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon3.addFile(QString::fromUtf8(":/toolbar_icons/draw-freehand.png"), QSize(), QIcon::Normal, QIcon::On);
        actionNormal_Edit->setIcon(icon3);
        actionLock_Edit = new QAction(MainWindow);
        actionLock_Edit->setObjectName(QString::fromUtf8("actionLock_Edit"));
        actionLock_Edit->setCheckable(true);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/toolbar_icons/Lock"), QSize(), QIcon::Normal, QIcon::On);
        actionLock_Edit->setIcon(icon4);
        actionEraser = new QAction(MainWindow);
        actionEraser->setObjectName(QString::fromUtf8("actionEraser"));
        actionEraser->setCheckable(true);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/toolbar_icons/draw-eraser.png"), QSize(), QIcon::Normal, QIcon::On);
        actionEraser->setIcon(icon5);
        actionAdd = new QAction(MainWindow);
        actionAdd->setObjectName(QString::fromUtf8("actionAdd"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/toolbar_icons/list-add.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAdd->setIcon(icon6);
        actionFill = new QAction(MainWindow);
        actionFill->setObjectName(QString::fromUtf8("actionFill"));
        actionFill->setCheckable(true);
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/toolbar_icons/Fill"), QSize(), QIcon::Normal, QIcon::Off);
        actionFill->setIcon(icon7);
        actionLink = new QAction(MainWindow);
        actionLink->setObjectName(QString::fromUtf8("actionLink"));
        actionLink->setCheckable(true);
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/toolbar_icons/connect_no.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLink->setIcon(icon8);
        actionStairs = new QAction(MainWindow);
        actionStairs->setObjectName(QString::fromUtf8("actionStairs"));
        actionStairs->setCheckable(true);
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/toolbar_icons/stairs.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionStairs->setIcon(icon9);
        actionEdit_NPC = new QAction(MainWindow);
        actionEdit_NPC->setObjectName(QString::fromUtf8("actionEdit_NPC"));
        actionEdit_NPC->setCheckable(true);
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/toolbar_icons/im-user.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionEdit_NPC->setIcon(icon10);
        actionEdit_Tileset = new QAction(MainWindow);
        actionEdit_Tileset->setObjectName(QString::fromUtf8("actionEdit_Tileset"));
        actionEdit_Tileset->setCheckable(true);
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/toolbar_icons/format-stroke-color.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionEdit_Tileset->setIcon(icon11);
        actionLayer_Level = new QAction(MainWindow);
        actionLayer_Level->setObjectName(QString::fromUtf8("actionLayer_Level"));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/toolbar_icons/format-list-ordered.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLayer_Level->setIcon(icon12);
        actionOne = new QAction(MainWindow);
        actionOne->setObjectName(QString::fromUtf8("actionOne"));
        actionTwo = new QAction(MainWindow);
        actionTwo->setObjectName(QString::fromUtf8("actionTwo"));
        actionThree = new QAction(MainWindow);
        actionThree->setObjectName(QString::fromUtf8("actionThree"));
        actionAdd_Object = new QAction(MainWindow);
        actionAdd_Object->setObjectName(QString::fromUtf8("actionAdd_Object"));
        actionAdd_Object->setCheckable(true);
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/toolbar_icons/media-playlist-shuffle.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAdd_Object->setIcon(icon13);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetMinimumSize);
        horizontalLayout_2->setContentsMargins(0, 0, -1, -1);

        verticalLayout->addLayout(horizontalLayout_2);

        toolBox = new QToolBox(centralWidget);
        toolBox->setObjectName(QString::fromUtf8("toolBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(toolBox->sizePolicy().hasHeightForWidth());
        toolBox->setSizePolicy(sizePolicy1);
        toolBox->setMaximumSize(QSize(400, 16777215));
        page_map = new QWidget();
        page_map->setObjectName(QString::fromUtf8("page_map"));
        page_map->setGeometry(QRect(0, 0, 390, 365));
        verticalWidget = new QWidget(page_map);
        verticalWidget->setObjectName(QString::fromUtf8("verticalWidget"));
        verticalWidget->setGeometry(QRect(0, 0, 391, 290));
        verticalWidget->setMaximumSize(QSize(16777215, 290));
        verticalLayout_3 = new QVBoxLayout(verticalWidget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(-1, 10, -1, 10);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, -1, -1, 0);
        label = new QLabel(verticalWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        comboBox = new QComboBox(verticalWidget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        horizontalLayout->addWidget(comboBox);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setSizeConstraint(QLayout::SetMinimumSize);
        mapListCombo = new QComboBox(verticalWidget);
        mapListCombo->setObjectName(QString::fromUtf8("mapListCombo"));

        horizontalLayout_4->addWidget(mapListCombo);

        pushButton = new QPushButton(verticalWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout_4->addWidget(pushButton);


        verticalLayout_3->addLayout(horizontalLayout_4);

        scrollArea_2 = new QScrollArea(verticalWidget);
        scrollArea_2->setObjectName(QString::fromUtf8("scrollArea_2"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(scrollArea_2->sizePolicy().hasHeightForWidth());
        scrollArea_2->setSizePolicy(sizePolicy2);
        scrollArea_2->setWidgetResizable(false);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 284, 75));
        pallete = new EditorTilePallete(scrollAreaWidgetContents_2);
        pallete->setObjectName(QString::fromUtf8("pallete"));
        pallete->setGeometry(QRect(10, 0, 241, 71));
        sizePolicy2.setHeightForWidth(pallete->sizePolicy().hasHeightForWidth());
        pallete->setSizePolicy(sizePolicy2);
        pallete->setMinimumSize(QSize(100, 50));
        scrollArea_2->setWidget(scrollAreaWidgetContents_2);

        verticalLayout_3->addWidget(scrollArea_2);

        toolBox->addItem(page_map, QString::fromUtf8("Map Edit"));
        Terrain = new QWidget();
        Terrain->setObjectName(QString::fromUtf8("Terrain"));
        Terrain->setGeometry(QRect(0, 0, 390, 365));
        listWidget_2 = new QListWidget(Terrain);
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/toolbar_icons/Lock"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(listWidget_2);
        __qlistwidgetitem->setIcon(icon14);
        QListWidgetItem *__qlistwidgetitem1 = new QListWidgetItem(listWidget_2);
        __qlistwidgetitem1->setIcon(icon9);
        QIcon icon15;
        icon15.addFile(QString::fromUtf8(":/toolbar_icons/object-order-lower.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem2 = new QListWidgetItem(listWidget_2);
        __qlistwidgetitem2->setIcon(icon15);
        QIcon icon16;
        icon16.addFile(QString::fromUtf8(":/toolbar_icons/edit-delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem3 = new QListWidgetItem(listWidget_2);
        __qlistwidgetitem3->setIcon(icon16);
        QIcon icon17;
        icon17.addFile(QString::fromUtf8(":/toolbar_icons/flag-blue.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem4 = new QListWidgetItem(listWidget_2);
        __qlistwidgetitem4->setIcon(icon17);
        QIcon icon18;
        icon18.addFile(QString::fromUtf8(":/toolbar_icons/flag-green.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem5 = new QListWidgetItem(listWidget_2);
        __qlistwidgetitem5->setIcon(icon18);
        QIcon icon19;
        icon19.addFile(QString::fromUtf8(":/toolbar_icons/arrow-left.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem6 = new QListWidgetItem(listWidget_2);
        __qlistwidgetitem6->setIcon(icon19);
        QIcon icon20;
        icon20.addFile(QString::fromUtf8(":/toolbar_icons/arrow-right.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem7 = new QListWidgetItem(listWidget_2);
        __qlistwidgetitem7->setIcon(icon20);
        listWidget_2->setObjectName(QString::fromUtf8("listWidget_2"));
        listWidget_2->setGeometry(QRect(0, 0, 401, 361));
        toolBox->addItem(Terrain, QString::fromUtf8("Terrain"));
        page_npc = new QWidget();
        page_npc->setObjectName(QString::fromUtf8("page_npc"));
        page_npc->setGeometry(QRect(0, 0, 100, 30));
        sizePolicy2.setHeightForWidth(page_npc->sizePolicy().hasHeightForWidth());
        page_npc->setSizePolicy(sizePolicy2);
        listWidget = new QListWidget(page_npc);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(2, 2, 391, 191));
        editNPCButton = new QPushButton(page_npc);
        editNPCButton->setObjectName(QString::fromUtf8("editNPCButton"));
        editNPCButton->setEnabled(false);
        editNPCButton->setGeometry(QRect(100, 200, 81, 23));
        newNPCButton = new QPushButton(page_npc);
        newNPCButton->setObjectName(QString::fromUtf8("newNPCButton"));
        newNPCButton->setGeometry(QRect(10, 200, 81, 23));
        toolBox->addItem(page_npc, QString::fromUtf8("NPC Edit"));
        page_Link = new QWidget();
        page_Link->setObjectName(QString::fromUtf8("page_Link"));
        page_Link->setGeometry(QRect(0, 0, 100, 30));
        gridLayoutWidget = new QWidget(page_Link);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 10, 371, 311));
        gridLayout_2 = new QGridLayout(gridLayoutWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        link_orientation_combobox = new QComboBox(gridLayoutWidget);
        link_orientation_combobox->setObjectName(QString::fromUtf8("link_orientation_combobox"));

        gridLayout_2->addWidget(link_orientation_combobox, 0, 1, 1, 1);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 0, 0, 1, 1);

        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 1, 0, 1, 1);

        link_size_spinbox = new QSpinBox(gridLayoutWidget);
        link_size_spinbox->setObjectName(QString::fromUtf8("link_size_spinbox"));
        link_size_spinbox->setMinimum(1);
        link_size_spinbox->setMaximum(6);

        gridLayout_2->addWidget(link_size_spinbox, 1, 1, 1, 1);

        label_4 = new QLabel(gridLayoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 2, 0, 1, 1);

        link_bidi_checkbox = new QCheckBox(gridLayoutWidget);
        link_bidi_checkbox->setObjectName(QString::fromUtf8("link_bidi_checkbox"));

        gridLayout_2->addWidget(link_bidi_checkbox, 2, 1, 1, 1);

        label_5 = new QLabel(gridLayoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 3, 0, 1, 1);

        link_isdoor_checkbox = new QCheckBox(gridLayoutWidget);
        link_isdoor_checkbox->setObjectName(QString::fromUtf8("link_isdoor_checkbox"));

        gridLayout_2->addWidget(link_isdoor_checkbox, 3, 1, 1, 1);

        toolBox->addItem(page_Link, QString::fromUtf8("Link Options"));
        page_objects = new QWidget();
        page_objects->setObjectName(QString::fromUtf8("page_objects"));
        page_objects->setGeometry(QRect(0, 0, 100, 30));
        editObjectButton = new QPushButton(page_objects);
        editObjectButton->setObjectName(QString::fromUtf8("editObjectButton"));
        editObjectButton->setEnabled(false);
        editObjectButton->setGeometry(QRect(120, 200, 101, 23));
        newObjectButton = new QPushButton(page_objects);
        newObjectButton->setObjectName(QString::fromUtf8("newObjectButton"));
        newObjectButton->setGeometry(QRect(8, 200, 101, 23));
        objectListWidget = new QListWidget(page_objects);
        objectListWidget->setObjectName(QString::fromUtf8("objectListWidget"));
        objectListWidget->setGeometry(QRect(0, 2, 391, 191));
        toolBox->addItem(page_objects, QString::fromUtf8("Object Edit"));

        verticalLayout->addWidget(toolBox);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea->setWidgetResizable(false);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 192, 142));
        sizePolicy2.setHeightForWidth(scrollAreaWidgetContents->sizePolicy().hasHeightForWidth());
        scrollAreaWidgetContents->setSizePolicy(sizePolicy2);
        editArea = new EditorArea(scrollAreaWidgetContents);
        editArea->setObjectName(QString::fromUtf8("editArea"));
        editArea->setGeometry(QRect(0, 0, 211, 161));
        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout->addWidget(scrollArea, 0, 1, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        editToolBar = new QToolBar(MainWindow);
        editToolBar->setObjectName(QString::fromUtf8("editToolBar"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(editToolBar->sizePolicy().hasHeightForWidth());
        editToolBar->setSizePolicy(sizePolicy3);
        MainWindow->addToolBar(Qt::TopToolBarArea, editToolBar);
        MainWindow->insertToolBarBreak(editToolBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 869, 23));
        menuFILE = new QMenu(menuBar);
        menuFILE->setObjectName(QString::fromUtf8("menuFILE"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        menuLevel = new QMenu(menuView);
        menuLevel->setObjectName(QString::fromUtf8("menuLevel"));
        MainWindow->setMenuBar(menuBar);

        mainToolBar->addAction(actionNew);
        mainToolBar->addAction(actionOpen);
        mainToolBar->addAction(actionSave);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionEdit_Tileset);
        mainToolBar->addAction(actionEdit_NPC);
        mainToolBar->addAction(actionAdd_Object);
        editToolBar->addAction(actionNormal_Edit);
        editToolBar->addAction(actionLock_Edit);
        editToolBar->addAction(actionEraser);
        editToolBar->addAction(actionFill);
        editToolBar->addSeparator();
        editToolBar->addAction(actionLink);
        menuBar->addAction(menuFILE->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFILE->addAction(actionNew);
        menuFILE->addAction(actionOpen);
        menuFILE->addAction(actionSave);
        menuFILE->addSeparator();
        menuFILE->addAction(actionQuit);
        menuHelp->addAction(actionAbout);
        menuEdit->addAction(actionCopy);
        menuEdit->addAction(actionPaste);
        menuView->addAction(menuLevel->menuAction());
        menuLevel->addAction(actionOne);
        menuLevel->addAction(actionTwo);
        menuLevel->addAction(actionThree);

        retranslateUi(MainWindow);

        toolBox->setCurrentIndex(0);
        comboBox->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Rockbot Editor 0.1 b6", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("MainWindow", "About", 0, QApplication::UnicodeUTF8));
        actionCopy->setText(QApplication::translate("MainWindow", "Copy", 0, QApplication::UnicodeUTF8));
        actionPaste->setText(QApplication::translate("MainWindow", "Paste", 0, QApplication::UnicodeUTF8));
        actionNew->setText(QApplication::translate("MainWindow", "New", 0, QApplication::UnicodeUTF8));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", 0, QApplication::UnicodeUTF8));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", 0, QApplication::UnicodeUTF8));
        actionSave->setText(QApplication::translate("MainWindow", "Save", 0, QApplication::UnicodeUTF8));
        actionNormal_Edit->setText(QApplication::translate("MainWindow", "Normal Edit", 0, QApplication::UnicodeUTF8));
        actionLock_Edit->setText(QApplication::translate("MainWindow", "Lock Edit", 0, QApplication::UnicodeUTF8));
        actionEraser->setText(QApplication::translate("MainWindow", "Eraser", 0, QApplication::UnicodeUTF8));
        actionAdd->setText(QApplication::translate("MainWindow", "Add", 0, QApplication::UnicodeUTF8));
        actionFill->setText(QApplication::translate("MainWindow", "Fill", 0, QApplication::UnicodeUTF8));
        actionLink->setText(QApplication::translate("MainWindow", "Link", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionLink->setToolTip(QApplication::translate("MainWindow", "Link Maps", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionStairs->setText(QApplication::translate("MainWindow", "Stairs", 0, QApplication::UnicodeUTF8));
        actionEdit_NPC->setText(QApplication::translate("MainWindow", "Edit NPC", 0, QApplication::UnicodeUTF8));
        actionEdit_Tileset->setText(QApplication::translate("MainWindow", "Edit Tileset", 0, QApplication::UnicodeUTF8));
        actionLayer_Level->setText(QApplication::translate("MainWindow", "Layer Level", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionLayer_Level->setToolTip(QApplication::translate("MainWindow", "Layer Level", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionOne->setText(QApplication::translate("MainWindow", "one", 0, QApplication::UnicodeUTF8));
        actionTwo->setText(QApplication::translate("MainWindow", "two", 0, QApplication::UnicodeUTF8));
        actionThree->setText(QApplication::translate("MainWindow", "three", 0, QApplication::UnicodeUTF8));
        actionAdd_Object->setText(QApplication::translate("MainWindow", "Add Object", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionAdd_Object->setToolTip(QApplication::translate("MainWindow", "Add Object", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label->setText(QApplication::translate("MainWindow", "Level:", 0, QApplication::UnicodeUTF8));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "3", 0, QApplication::UnicodeUTF8)
        );
        pushButton->setText(QApplication::translate("MainWindow", "New", 0, QApplication::UnicodeUTF8));
        toolBox->setItemText(toolBox->indexOf(page_map), QApplication::translate("MainWindow", "Map Edit", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = listWidget_2->isSortingEnabled();
        listWidget_2->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget_2->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("MainWindow", "Solid", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem1 = listWidget_2->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("MainWindow", "Stairs", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem2 = listWidget_2->item(2);
        ___qlistwidgetitem2->setText(QApplication::translate("MainWindow", "Door", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem3 = listWidget_2->item(3);
        ___qlistwidgetitem3->setText(QApplication::translate("MainWindow", "Spikes", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem4 = listWidget_2->item(4);
        ___qlistwidgetitem4->setText(QApplication::translate("MainWindow", "Water", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem5 = listWidget_2->item(5);
        ___qlistwidgetitem5->setText(QApplication::translate("MainWindow", "Ice", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem6 = listWidget_2->item(6);
        ___qlistwidgetitem6->setText(QApplication::translate("MainWindow", "Move to Left", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem7 = listWidget_2->item(7);
        ___qlistwidgetitem7->setText(QApplication::translate("MainWindow", "Move to Right", 0, QApplication::UnicodeUTF8));
        listWidget_2->setSortingEnabled(__sortingEnabled);

        toolBox->setItemText(toolBox->indexOf(Terrain), QApplication::translate("MainWindow", "Terrain", 0, QApplication::UnicodeUTF8));
        editNPCButton->setText(QApplication::translate("MainWindow", "Edit NPC", 0, QApplication::UnicodeUTF8));
        newNPCButton->setText(QApplication::translate("MainWindow", "New NPC", 0, QApplication::UnicodeUTF8));
        toolBox->setItemText(toolBox->indexOf(page_npc), QApplication::translate("MainWindow", "NPC Edit", 0, QApplication::UnicodeUTF8));
        link_orientation_combobox->clear();
        link_orientation_combobox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Horizontal", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Vertical", 0, QApplication::UnicodeUTF8)
        );
        label_2->setText(QApplication::translate("MainWindow", "Orientation:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "Size:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "Bi-Direcional:", 0, QApplication::UnicodeUTF8));
        link_bidi_checkbox->setText(QString());
        label_5->setText(QApplication::translate("MainWindow", "Is Door:", 0, QApplication::UnicodeUTF8));
        link_isdoor_checkbox->setText(QString());
        toolBox->setItemText(toolBox->indexOf(page_Link), QApplication::translate("MainWindow", "Link Options", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        page_objects->setToolTip(QApplication::translate("MainWindow", "Object Options", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        editObjectButton->setText(QApplication::translate("MainWindow", "Edit Object", 0, QApplication::UnicodeUTF8));
        newObjectButton->setText(QApplication::translate("MainWindow", "New Object", 0, QApplication::UnicodeUTF8));
        toolBox->setItemText(toolBox->indexOf(page_objects), QApplication::translate("MainWindow", "Object Edit", 0, QApplication::UnicodeUTF8));
        editToolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0, QApplication::UnicodeUTF8));
        menuFILE->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0, QApplication::UnicodeUTF8));
        menuEdit->setTitle(QApplication::translate("MainWindow", "Edit", 0, QApplication::UnicodeUTF8));
        menuView->setTitle(QApplication::translate("MainWindow", "View", 0, QApplication::UnicodeUTF8));
        menuLevel->setTitle(QApplication::translate("MainWindow", "Level", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
