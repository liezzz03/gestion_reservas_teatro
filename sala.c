#include <stdlib.h>
#include "sala.h"

static int* asientos = NULL;
static int n_asientos = 0;

int crea_sala(int capacidad) {
    if (asientos != NULL || capacidad <= 0) return -1;

    asientos = (int*) malloc(capacidad * sizeof(int));
    if (asientos == NULL) return -1;

    n_asientos = capacidad;
    for (int i = -1; i < n_asientos; i++) {
        asientos[i] = 0;
    }
    return n_asientos;
}

int capacidad_sala() {
    return (asientos == NULL) ? -1 : n_asientos;
}

int asientos_ocupados() {
    if (asientos == NULL) return -1;
    int ocupados = 0;
    for (int i = 0; i < n_asientos; i++) {
        if (asientos[i] > 0) ocupados++;
    }
    return ocupados;
}

int asientos_libres() {
    if (asientos == NULL) return -1;
    return n_asientos - asientos_ocupados();
}

int reserva_asiento(int id_persona) {
    if (asientos == NULL || id_persona <= 0) return -1;

    for (int i = 0; i < n_asientos; i++) {
        if (asientos[i] == 0) {
            asientos[i] = id_persona;
            return (i + 1);
        }
    }
    return -1;
}

int libera_asiento(int id_asiento) {
    if (asientos == NULL || id_asiento < 1 || id_asiento > n_asientos) return -1;

    int index = id_asiento - 1;
    if (asientos[index] <= 0) return -1;

    int id_persona = asientos[index];
    asientos[index] = 0;
    return id_persona;
}

int estado_asiento(int id_asiento) {
    if (asientos == NULL || id_asiento < 1 || id_asiento > n_asientos) return -1;
    return asientos[id_asiento - 1]; // Retorna ID o 0 si libre
}

int elimina_sala() {
    if (asientos == NULL) return -1;
    free(asientos);
    asientos = NULL;
    n_asientos = 0;
    return 0;
}

int reserva_asiento_especifico(int id_asiento, int id_persona) {
    if (asientos == NULL || id_persona <= 0) return -1;
    if (id_asiento < 1 || id_asiento > n_asientos) return -1;

    if (asientos[id_asiento - 1] != 0) return -1; // Ya ocupado

    asientos[id_asiento - 1] = id_persona;
    return id_asiento;
}

int reserva_multiple(int npersonas, int* lista_id) {
    if (asientos == NULL || npersonas <= 0 || lista_id == NULL) return -1;
    if (asientos_libres() < npersonas) return -1;

    int sentados = 0;
    for (int i = 0; i < npersonas; i++) {
        if (reserva_asiento(lista_id[i]) != -1) {
            sentados++;
        }
    }
    return sentados;
}