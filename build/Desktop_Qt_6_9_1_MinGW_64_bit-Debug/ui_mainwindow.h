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
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTextEdit *labelResultado;
    QLabel *label;
    QPushButton *btnIniciar;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        MainWindow->setStyleSheet(QString::fromUtf8("QMainWindow {\n"
"    background-image: url(:/images/iniciar_juego.png);\n"
"    background-repeat: no-repeat;\n"
"    background-position: center;\n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        labelResultado = new QTextEdit(centralwidget);
        labelResultado->setObjectName("labelResultado");
        labelResultado->setGeometry(QRect(340, 120, 104, 70));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(-40, -110, 891, 771));
        label->setStyleSheet(QString::fromUtf8("image: url(:/new/prefix1/imagenes/iniciar_juego.png);"));
        btnIniciar = new QPushButton(centralwidget);
        btnIniciar->setObjectName("btnIniciar");
        btnIniciar->setGeometry(QRect(310, 400, 181, 61));
        btnIniciar->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: peachpuff;\n"
"    font: bold 16px;\n"
"    border-radius: 15px;\n"
"    padding: 10px 20px;\n"
"}"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
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
        label->setText(QString());
        btnIniciar->setText(QCoreApplication::translate("MainWindow", "Iniciar Juego", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
