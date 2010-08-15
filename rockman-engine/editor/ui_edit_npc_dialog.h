/********************************************************************************
** Form generated from reading UI file 'edit_npc_dialog.ui'
**
** Created: Sat Mar 13 16:59:41 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDIT_NPC_DIALOG_H
#define UI_EDIT_NPC_DIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "npcpreviewarea.h"

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLineEdit *NpcName;
    QLabel *label_3;
    QSpinBox *NpcHP;
    QLabel *label_8;
    QComboBox *npcListCombobox;
    QLabel *label_10;
    QSpinBox *npcGraphicSizeSpin;
    QVBoxLayout *verticalLayout_2;
    npcPreviewArea *npcPreviewAreaWidget;
    QComboBox *comboBox;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(638, 478);
        buttonBox = new QDialogButtonBox(Dialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(10, 440, 621, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        horizontalLayoutWidget = new QWidget(Dialog);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 10, 621, 421));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_2 = new QLabel(horizontalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        NpcName = new QLineEdit(horizontalLayoutWidget);
        NpcName->setObjectName(QString::fromUtf8("NpcName"));

        gridLayout->addWidget(NpcName, 0, 1, 1, 2);

        label_3 = new QLabel(horizontalLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        NpcHP = new QSpinBox(horizontalLayoutWidget);
        NpcHP->setObjectName(QString::fromUtf8("NpcHP"));
        NpcHP->setValue(5);

        gridLayout->addWidget(NpcHP, 1, 2, 1, 1);

        label_8 = new QLabel(horizontalLayoutWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout->addWidget(label_8, 2, 0, 1, 1);

        npcListCombobox = new QComboBox(horizontalLayoutWidget);
        npcListCombobox->setObjectName(QString::fromUtf8("npcListCombobox"));

        gridLayout->addWidget(npcListCombobox, 2, 2, 1, 1);

        label_10 = new QLabel(horizontalLayoutWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout->addWidget(label_10, 3, 0, 1, 2);

        npcGraphicSizeSpin = new QSpinBox(horizontalLayoutWidget);
        npcGraphicSizeSpin->setObjectName(QString::fromUtf8("npcGraphicSizeSpin"));
        npcGraphicSizeSpin->setMinimum(16);
        npcGraphicSizeSpin->setMaximum(64);

        gridLayout->addWidget(npcGraphicSizeSpin, 3, 2, 1, 1);


        verticalLayout->addLayout(gridLayout);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(-1, -1, -1, 0);
        npcPreviewAreaWidget = new npcPreviewArea(horizontalLayoutWidget);
        npcPreviewAreaWidget->setObjectName(QString::fromUtf8("npcPreviewAreaWidget"));

        verticalLayout_2->addWidget(npcPreviewAreaWidget);

        comboBox = new QComboBox(horizontalLayoutWidget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        verticalLayout_2->addWidget(comboBox);


        horizontalLayout->addLayout(verticalLayout_2);


        retranslateUi(Dialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), Dialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Dialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Dialog", "Name:", 0, QApplication::UnicodeUTF8));
        NpcName->setText(QApplication::translate("Dialog", "My NPC", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Dialog", "Hit Points:", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("Dialog", "Graphic:", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("Dialog", "Graphic Size: ", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDIT_NPC_DIALOG_H
