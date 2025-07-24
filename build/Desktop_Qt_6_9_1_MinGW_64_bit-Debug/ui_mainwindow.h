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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *comienzo;
    QPushButton *botoncomenzar;
    QPushButton *botoncerrar;
    QWidget *seleccionpjs;
    QComboBox *numpj;
    QPushButton *siguiente;
    QLabel *label;
    QWidget *tablero;
    QLabel *labelDado;
    QPushButton *BTdado;
    QLabel *Jugador_1;
    QLabel *Jugador_2;
    QLabel *Jugador_3;
    QLabel *Jugador_4;
    QLabel *label_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->setEnabled(true);
        MainWindow->resize(1280, 720);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(0, 0, 1441, 721));
        comienzo = new QWidget();
        comienzo->setObjectName("comienzo");
        comienzo->setMinimumSize(QSize(1591, 0));
        comienzo->setStyleSheet(QString::fromUtf8("#comienzo{\n"
"background-image: url(:/new/prefix1/imagenes/iniciar_juego.png);\n"
"background-repeat: no-repeat;\n"
"}\n"
""));
        botoncomenzar = new QPushButton(comienzo);
        botoncomenzar->setObjectName("botoncomenzar");
        botoncomenzar->setGeometry(QRect(500, 570, 271, 81));
        botoncomenzar->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        botoncomenzar->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"border: none;"));
        botoncerrar = new QPushButton(comienzo);
        botoncerrar->setObjectName("botoncerrar");
        botoncerrar->setGeometry(QRect(30, 640, 41, 41));
        botoncerrar->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        botoncerrar->setStyleSheet(QString::fromUtf8("#botoncerrar{\n"
"background-image: url(:/new/prefix1/imagenes/Salir.png);\n"
"background-color: transparent;\n"
"background-repeat: no-repeat;\n"
"}"));
        stackedWidget->addWidget(comienzo);
        botoncerrar->raise();
        botoncomenzar->raise();
        seleccionpjs = new QWidget();
        seleccionpjs->setObjectName("seleccionpjs");
        seleccionpjs->setStyleSheet(QString::fromUtf8("#seleccionpjs{\n"
"background-image: url(:/new/prefix1/imagenes/cantJugadores.png);\n"
"\n"
"}"));
        numpj = new QComboBox(seleccionpjs);
        numpj->addItem(QString());
        numpj->addItem(QString());
        numpj->addItem(QString());
        numpj->setObjectName("numpj");
        numpj->setGeometry(QRect(600, 300, 101, 41));
        numpj->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        numpj->setStyleSheet(QString::fromUtf8("background-image: transparent;"));
        siguiente = new QPushButton(seleccionpjs);
        siguiente->setObjectName("siguiente");
        siguiente->setGeometry(QRect(590, 460, 120, 160));
        siguiente->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        siguiente->setStyleSheet(QString::fromUtf8("background-image: url(:/new/prefix1/imagenes/c4.png);\n"
"background-color: transparent;\n"
"background-repeat: no-repeat;\n"
" background-position: center;\n"
""));
        label = new QLabel(seleccionpjs);
        label->setObjectName("label");
        label->setGeometry(QRect(490, 390, 321, 51));
        stackedWidget->addWidget(seleccionpjs);
        tablero = new QWidget();
        tablero->setObjectName("tablero");
        tablero->setStyleSheet(QString::fromUtf8("#tablero{\n"
"background-image: url(:/new/prefix1/imagenes/tablero.png);\n"
"}"));
        labelDado = new QLabel(tablero);
        labelDado->setObjectName("labelDado");
        labelDado->setGeometry(QRect(1100, 300, 121, 121));
        labelDado->setMinimumSize(QSize(100, 100));
        labelDado->setCursor(QCursor(Qt::CursorShape::ArrowCursor));
        labelDado->setScaledContents(true);
        BTdado = new QPushButton(tablero);
        BTdado->setObjectName("BTdado");
        BTdado->setGeometry(QRect(1100, 490, 121, 161));
        BTdado->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        BTdado->setStyleSheet(QString::fromUtf8("#BTdado{\n"
"background-color: transparent;\n"
"}"));
        Jugador_1 = new QLabel(tablero);
        Jugador_1->setObjectName("Jugador_1");
        Jugador_1->setGeometry(QRect(140, 600, 49, 31));
        Jugador_1->setStyleSheet(QString::fromUtf8(""));
        Jugador_2 = new QLabel(tablero);
        Jugador_2->setObjectName("Jugador_2");
        Jugador_2->setGeometry(QRect(140, 630, 49, 41));
        Jugador_2->setStyleSheet(QString::fromUtf8(""));
        Jugador_3 = new QLabel(tablero);
        Jugador_3->setObjectName("Jugador_3");
        Jugador_3->setGeometry(QRect(140, 680, 49, 31));
        Jugador_3->setStyleSheet(QString::fromUtf8(""));
        Jugador_4 = new QLabel(tablero);
        Jugador_4->setObjectName("Jugador_4");
        Jugador_4->setGeometry(QRect(140, 660, 49, 31));
        Jugador_4->setStyleSheet(QString::fromUtf8(""));
        label_2 = new QLabel(tablero);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(950, 300, 49, 16));
        stackedWidget->addWidget(tablero);
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        botoncomenzar->setText(QString());
        botoncerrar->setText(QString());
        numpj->setItemText(0, QCoreApplication::translate("MainWindow", "2", nullptr));
        numpj->setItemText(1, QCoreApplication::translate("MainWindow", "3", nullptr));
        numpj->setItemText(2, QCoreApplication::translate("MainWindow", "4", nullptr));

        siguiente->setText(QString());
        label->setText(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:11pt; font-weight:700; color:#000000;\">Clickea el C4 para comenzar!</span></p></body></html>", nullptr));
        labelDado->setText(QString());
        BTdado->setText(QString());
        Jugador_1->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><img src=\":/new/prefix1/imagenes/CS2_AK-47_Inventory_3.png\"/></p></body></html>", nullptr));
        Jugador_2->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><img src=\":/new/prefix1/imagenes/CS2_Glock-18_Inventory.png\"/></p></body></html>", nullptr));
        Jugador_3->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><img src=\":/new/prefix1/imagenes/CS2_M4A1-S_Inventory.png\"/></p></body></html>", nullptr));
        Jugador_4->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><img src=\":/new/prefix1/imagenes/CS2_USP-S_Inventory.png\"/></p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
