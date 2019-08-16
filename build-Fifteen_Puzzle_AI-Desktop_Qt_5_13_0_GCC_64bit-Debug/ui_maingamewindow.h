/********************************************************************************
** Form generated from reading UI file 'maingamewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINGAMEWINDOW_H
#define UI_MAINGAMEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainGameWindow
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainGameWindow)
    {
        if (MainGameWindow->objectName().isEmpty())
            MainGameWindow->setObjectName(QString::fromUtf8("MainGameWindow"));
        MainGameWindow->resize(400, 300);
        menuBar = new QMenuBar(MainGameWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        MainGameWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainGameWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainGameWindow->addToolBar(mainToolBar);
        centralWidget = new QWidget(MainGameWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        MainGameWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainGameWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainGameWindow->setStatusBar(statusBar);

        retranslateUi(MainGameWindow);

        QMetaObject::connectSlotsByName(MainGameWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainGameWindow)
    {
        MainGameWindow->setWindowTitle(QCoreApplication::translate("MainGameWindow", "MainGameWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainGameWindow: public Ui_MainGameWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINGAMEWINDOW_H
