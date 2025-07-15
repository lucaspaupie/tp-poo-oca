#include "mainwindow.h"
#include <QLabel>
#include <QPixmap>
#include <QDebug>
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QLabel *imagenLabel = new QLabel(this); // Crea una etiqueta para mostrar la imagen
    imagenLabel->setGeometry(100, 100, 128, 128); // Posición y tamaño de la imagen

    QPixmap skin("escritorio/skins/2"); // Ruta a la imagen (puede ser otra)
    imagenLabel->setPixmap(skin.scaled(imagenLabel->size(), Qt::KeepAspectRatio));

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_btntirarDado_clicked()
{
    qDebug("Se tiró el dado!");
}
