#ifndef cadastro_h
#define cadastro_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trade.h"

// struct para login de administradores
struct Login_adm {
    char cpf[11];
    char senha[7];
};

#endif