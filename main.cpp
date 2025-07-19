#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow w;
    w.show();  // 👈 Esto muestra tu ventana principal

    return app.exec();  // Qt entra en el loop principal
}
