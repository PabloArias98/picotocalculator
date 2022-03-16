#include "WndPila.hpp"

void WndPila_Crear(WndNodo** CimaPila) {
    *CimaPila = NULL;
}

void WndPila_Insertar(WndNodo** CimaPila, HWND Ventana) {
    WndNodo* NuevoNodo = NULL;
    NuevoNodo = (WndNodo*)malloc(sizeof(WndNodo));
    if (NuevoNodo != NULL) {
        NuevoNodo->Ventana = Ventana;
        NuevoNodo->Siguiente = (*CimaPila);
        (*CimaPila) = NuevoNodo;
    }
    else {

    }

}

HWND WndPila_Cima(WndNodo* CimaPila) {
    return CimaPila->Ventana;
}

void WndPila_EliminarCima(WndNodo** CimaPila) {
    if (!WndPila_esVacia(*CimaPila)) {
        WndNodo* Auxiliar = (*CimaPila);
        *CimaPila = (*CimaPila)->Siguiente;
        DestroyWindow(Auxiliar->Ventana);
        Auxiliar->Siguiente = NULL;
        free(Auxiliar);
    }
}

HWND WndPila_QuitarCima(WndNodo** CimaPila) {
    if (!WndPila_esVacia(*CimaPila)) {
        HWND Ventana;
        Ventana = WndPila_Cima(*CimaPila);
        WndPila_EliminarCima(CimaPila);
        return Ventana;
    }
    return NULL;
}

void WndPila_Vaciar(WndNodo** CimaPila) {
    while (!WndPila_esVacia(*CimaPila)) {
        WndPila_EliminarCima(CimaPila);
    }
}

BOOL WndPila_esVacia(WndNodo* CimaPila) {
    return (CimaPila == NULL);
}

int WndPila_nElementos(WndNodo* CimaPila) {
    WndNodo* Auxiliar = CimaPila;
    int Conteo = 0;
    while (Auxiliar != NULL) {
        Auxiliar = Auxiliar->Siguiente;
        Conteo++;
    }
    return Conteo;
}

