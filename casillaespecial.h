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
    casillaespecial() = default;
    // Métodos de serialización BINARIA
    // Solo necesitamos el amigo, la sobrecarga es la misma firma
    friend QDataStream &operator<<(QDataStream &out, const casillaespecial &c);
    friend QDataStream &operator>>(QDataStream &in, casillaespecial &c);
};

#endif // CASILLAESPECIAL_H
