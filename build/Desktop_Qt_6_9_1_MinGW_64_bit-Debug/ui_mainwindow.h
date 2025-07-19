/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *BTdado;
    QLabel *labelDado;
    QLabel *labelDado2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1146, 617);
        MainWindow->setMinimumSize(QSize(100, 100));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        BTdado = new QPushButton(centralwidget);
        BTdado->setObjectName("BTdado");
        BTdado->setGeometry(QRect(940, 360, 161, 191));
        BTdado->setMinimumSize(QSize(0, 0));
        QFont font;
        font.setFamilies({QString::fromUtf8("Malgun Gothic")});
        font.setPointSize(12);
        BTdado->setFont(font);
        BTdado->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        BTdado->setMouseTracking(false);
        BTdado->setCheckable(false);
        BTdado->setAutoRepeat(false);
        BTdado->setAutoExclusive(false);
        BTdado->setAutoDefault(false);
        labelDado = new QLabel(centralwidget);
        labelDado->setObjectName("labelDado");
        labelDado->setGeometry(QRect(910, 210, 100, 100));
        labelDado->setMinimumSize(QSize(100, 100));
        labelDado2 = new QLabel(centralwidget);
        labelDado2->setObjectName("labelDado2");
        labelDado2->setGeometry(QRect(920, 170, 100, 100));
        labelDado2->setMinimumSize(QSize(100, 100));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1146, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        BTdado->setText(QCoreApplication::translate("MainWindow", "BTdado", nullptr));
        labelDado->setText(QString());
        labelDado2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
