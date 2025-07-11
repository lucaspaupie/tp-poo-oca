#ifndef CASILLAESPECIAL_H
#define CASILLAESPECIAL_H

#include "casilla.h"
#include <QString>
class casillaespecial: public casilla
{

private:
    QString tipo;
public:
    casillaespecial(int numero, const QString& tipo);

    void accion(jugador& j ) override;
};

#endif // CASILLAESPECIAL_H
