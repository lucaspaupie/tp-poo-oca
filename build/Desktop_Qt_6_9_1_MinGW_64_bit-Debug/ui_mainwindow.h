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
#include <QtWidgets/QComboBox>
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
    QPushButton *btnIniciar;
    QPushButton *btnCerrar;
    QWidget *widgetSelector;
    QLabel *ImgFondoSelec;
    QComboBox *canJugadores;
    QPushButton *confJugadores;
    QLabel *label_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->setEnabled(true);
        MainWindow->resize(800, 600);
        MainWindow->setStyleSheet(QString::fromUtf8("QMainWindow {\n"
"    background-image: url(:/images/iniciar_juego.png);\n"
"    background-repeat: no-repeat;\n"
"    background-position: center;\n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        btnIniciar = new QPushButton(centralwidget);
        btnIniciar->setObjectName("btnIniciar");
        btnIniciar->setGeometry(QRect(310, 420, 211, 71));
        btnIniciar->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: peachpuff;\n"
"    font: bold 16px;\n"
"    border-radius: 15px;\n"
"    padding: 10px 20px;\n"
"}"));
        btnCerrar = new QPushButton(centralwidget);
        btnCerrar->setObjectName("btnCerrar");
        btnCerrar->setGeometry(QRect(10, 430, 111, 51));
        btnCerrar->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	image: url(:/new/prefix1/imagenes/Salir.png);\n"
"    border: none;\n"
"    background-color: transparent;\n"
"    font-size: 24px;\n"
"}\n"
""));
        widgetSelector = new QWidget(centralwidget);
        widgetSelector->setObjectName("widgetSelector");
        widgetSelector->setEnabled(true);
        widgetSelector->setGeometry(QRect(0, 20, 801, 571));
        widgetSelector->setMinimumSize(QSize(801, 571));
        widgetSelector->setStyleSheet(QString::fromUtf8(""));
        ImgFondoSelec = new QLabel(widgetSelector);
        ImgFondoSelec->setObjectName("ImgFondoSelec");
        ImgFondoSelec->setGeometry(QRect(-40, -10, 891, 591));
        ImgFondoSelec->setStyleSheet(QString::fromUtf8("image: url(:/new/prefix1/imagenes/cantJugadores.png);"));
        ImgFondoSelec->setScaledContents(true);
        ImgFondoSelec->setAlignment(Qt::AlignmentFlag::AlignCenter);
        canJugadores = new QComboBox(widgetSelector);
        canJugadores->addItem(QString());
        canJugadores->addItem(QString());
        canJugadores->addItem(QString());
        canJugadores->setObjectName("canJugadores");
        canJugadores->setGeometry(QRect(380, 230, 41, 31));
        confJugadores = new QPushButton(widgetSelector);
        confJugadores->setObjectName("confJugadores");
        confJugadores->setGeometry(QRect(360, 310, 80, 24));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(-2, 0, 811, 581));
        label_2->setStyleSheet(QString::fromUtf8("image: url(:/new/prefix1/imagenes/iniciar_juego.png);"));
        MainWindow->setCentralWidget(centralwidget);
        label_2->raise();
        widgetSelector->raise();
        btnIniciar->raise();
        btnCerrar->raise();
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
        btnIniciar->setText(QCoreApplication::translate("MainWindow", "Iniciar Juego", nullptr));
        btnCerrar->setText(QString());
        ImgFondoSelec->setText(QString());
        canJugadores->setItemText(0, QCoreApplication::translate("MainWindow", "2", nullptr));
        canJugadores->setItemText(1, QCoreApplication::translate("MainWindow", "3", nullptr));
        canJugadores->setItemText(2, QCoreApplication::translate("MainWindow", "4", nullptr));

        confJugadores->setText(QCoreApplication::translate("MainWindow", "Confirmar", nullptr));
        label_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
