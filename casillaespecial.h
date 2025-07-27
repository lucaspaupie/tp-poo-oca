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
    virtual ~casillaespecial();
    virtual QString accion(jugador& j) override;
    QString getTipo() const;
    static int siguienteOca(int posActual);
};

#endif // CASILLAESPECIAL_H
