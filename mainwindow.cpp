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
    miDado = new dado();  // Crear instancia del dado
    miDado2 = new dado();

    // Conectar el botón que lanza el dado (ejemplo si tienes un botón llamado btnTirar)
    connect(ui->BTdado, &QPushButton::clicked, this, &MainWindow::BTdado);


}
MainWindow::~MainWindow()
{
    delete ui;
    delete miDado;
    delete miDado2;
}

void MainWindow::BTdado()
{
    int resultado1 = miDado->tirar();
    int resultado2 = miDado2->tirar();

    qDebug() << "Dado 1:" << resultado1 << " | Dado 2:" << resultado2;

    QString rutaImagen1 = QString(":/imagenes/imagenes/dado%1.png").arg(resultado1);
    QString rutaImagen2 = QString(":/imagenes/imagenes/dado%1.png").arg(resultado2);

    QPixmap skin1(rutaImagen1);
    QPixmap skin2(rutaImagen2);

    if (skin1.isNull()) qDebug() << "❌ ERROR: No se pudo cargar imagen dado 1.";
    if (skin2.isNull()) qDebug() << "❌ ERROR: No se pudo cargar imagen dado 2.";

    if (!ui->labelDado || !ui->labelDado2) {
        qDebug() << "❌ QLabel no encontrado.";
        return;
    }

    ui->labelDado->setPixmap(skin1.scaled(ui->labelDado->size(), Qt::KeepAspectRatio));
    ui->labelDado2->setPixmap(skin2.scaled(ui->labelDado2->size(), Qt::KeepAspectRatio));
}

