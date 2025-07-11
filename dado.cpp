#include "dado.h"
#include <cstdlib>
#include <ctime>

int dado::tirar() {
    return rand() % 6+1;
}
