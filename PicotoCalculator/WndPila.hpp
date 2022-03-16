#ifndef WNDPILA_HPP
#define WNDPILA_HPP

#include <windows.h>

typedef struct _WndNodo {
    HWND Ventana;
    struct _WndNodo* Siguiente;
}WndNodo;

void    WndPila_Crear(WndNodo** CimaPila);
void    WndPila_Insertar(WndNodo** CimaPila, HWND ventana);
HWND    WndPila_Cima(WndNodo* CimaPila);
HWND    WndPila_QuitarCima(WndNodo** CimaPila);
void    WndPila_EliminarCima(WndNodo** CimaPila);
void    WndPila_Vaciar(WndNodo** CimaPila);
BOOL    WndPila_esVacia(WndNodo* CimaPila);
int     WndPila_nElementos(WndNodo* CimaPila);


#endif // WNDPILA_HPP
