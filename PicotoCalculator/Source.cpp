#include <windows.h>
#include "WndPila.hpp"
#include <tchar.h>
#include <stdio.h>
#include <math.h>


#define IDM_FILE_RESET 102
#define IDM_FILE_EXIT 103
#define IDM_PROGRAM_HELP 104
#define IDM_FILE_ABOUT 110
#define ID_CLOSE_HELP 200
#define ID_CLOSE_ABOUT 300
#define ID_GITHUB 301

//ID´s
enum {
    ID_EDIT, ID_BOTONIGUAL, ID_BOTONRESET, ID_BOTONRESET2, ID_BOTONSUMAR, ID_BOTONRESTAR,
    ID_BOTONMULTIPLICAR, ID_BOTONDIVIDIR, ID_BOTONPOTENCIA, ID_BOTONRAIZ, ID_BOTONCOMA, ID_BOTONSIGNO, ID_BOTONCERO, ID_BOTON1,
    ID_BOTON2, ID_BOTON3, ID_BOTON4, ID_BOTON5, ID_BOTON6, ID_BOTON7, ID_BOTON8, ID_BOTON9
};

extern WndNodo* Pila;
WndNodo* Pila;
HINSTANCE estancia;
HWND edit;


//Prototipos
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WindowProcedureChild(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WindowProcedureAbout(HWND, UINT, WPARAM, LPARAM);

//funcion para imprimir en pantalla
void imprimirEdit(int i);

//funcion que anade el menu
void anadirMenus(HWND);

//mensajes de info
int mostrarMensajeReset();
int mostrarMensajeReset2();
int mostrarMensajeError();
int mostrarRecuadroAcercaDe();
int confirmarCerradoPrograma();
//Funcion que concatena los numeros en pantalla
double calcular(double primer_num, double segundo_num, int operacion);     //Funcion que realiza las operaciones

//Botones
HWND boton1;
HWND boton2;
HWND boton3;
HWND boton4;
HWND boton5;
HWND boton6;
HWND boton7;
HWND boton8;
HWND boton9;
HWND boton0;
HWND botonComa;
HWND botonSigno;
HWND botonIgual;
HWND botonReset;
HWND botonReset2;
HWND botonSumar;
HWND botonRestar;
HWND botonMultiplicar;
HWND botonDividir;
HWND botonPotencia;
HWND botonRaiz;
HWND botonAceptar;
HWND botonGitHub;


const TCHAR szClassName[] = _T("CodeBlocksWindowsApp");
const TCHAR szChildClassName[] = _T("Temas de Ayuda");
const TCHAR szAboutClassName[] = _T("Acerca de");
const TCHAR iconoPrograma[] = _T("icono.ico");
const TCHAR iconoAyuda[] = _T("ayuda.ico");

BOOL RegistrarClaseEx(UINT Estilo, HINSTANCE hThisInstance, LPCSTR szClassName, LPCSTR NombreMenu, WNDPROC WndProcedimiento, HBRUSH color, LPCSTR direccion_icono) {
    WNDCLASSEX wc;
    estancia = hThisInstance;
    
    HICON icono = (HICON)LoadImage(0, direccion_icono, IMAGE_ICON, 32, 32, LR_DEFAULTSIZE | LR_LOADFROMFILE);

    wc.style = CS_DBLCLKS;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hThisInstance;
    wc.lpszClassName = szClassName;
    wc.lpszMenuName = NULL;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = icono;
    wc.hIconSm = LoadIcon(estancia, IDI_APPLICATION);
    wc.lpfnWndProc = WndProcedimiento;
    wc.hbrBackground = color;


    if (RegisterClassEx(&wc)) {
        return  TRUE;
    }
    return FALSE;
}

int WINAPI WinMain(_In_ HINSTANCE hThisInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpszArgument,
    _In_ int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */



    if (!RegistrarClaseEx(CS_DBLCLKS, hThisInstance, szClassName, NULL, WindowProcedure, (HBRUSH)CreateSolidBrush(RGB(157, 249, 121)), iconoPrograma)) {
        MessageBox(NULL, "No se Pudo Iniciar la Aplicación", "Error", MB_ICONERROR | MB_OK);
        return -1;
    }

    if (!RegistrarClaseEx(CS_DBLCLKS, hThisInstance, szChildClassName, NULL, WindowProcedureChild, (HBRUSH)CreateSolidBrush(RGB(255, 255, 255)), iconoAyuda ) ) {
        MessageBox(NULL, "No se Pudo Iniciar la Aplicación", "Error", MB_ICONERROR | MB_OK);
        return -1;
    }

    if (!RegistrarClaseEx(CS_DBLCLKS, hThisInstance, szAboutClassName, NULL, WindowProcedureAbout, (HBRUSH)CreateSolidBrush(RGB(255, 255, 255)), iconoPrograma)) {
        MessageBox(NULL, "No se Pudo Iniciar la Aplicación", "Error", MB_ICONERROR | MB_OK);
        return -1;
    }

    //Le damos una tonalidad verde al fondo de la app
    

    WndPila_Crear(&Pila);
    //Registramos las clases


    hwnd = CreateWindowEx(
        0,                   /* Extended possibilites for variation */
        szClassName,         /* Classname */
        _T("Picoto Calculator v0.1"),
        WS_OVERLAPPEDWINDOW, /* default window */
        450,       /* Windows decides the position */
        360,       /* where the window ends up on the screen */
        310,                 /* The programs width */
        350,                 /* and height in pixels */
        HWND_DESKTOP,        /* The window is a child-window to desktop */
        NULL,                /* No menu */
        hThisInstance,       /* Program Instance handler */
        NULL                 /* No Window Creation data */
    ); 
    
    WndPila_Insertar(&Pila, hwnd);
    /* Make the window visible on the screen */
    ShowWindow(hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage(&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}



int confirmarCerradoPrograma()
{
    int msgboxID = MessageBox(
        NULL,
        _T("Saldrá del programa, desea continuar?"),
        _T("Salir"),
        MB_ICONEXCLAMATION | MB_YESNO
    );

    if (msgboxID == IDYES)
    {
        WndPila_Vaciar(&Pila);
        PostQuitMessage(0);
    }
    else
    {

    }
    return msgboxID;
}

int mostrarMensajeError()
{
    int msgboxID = MessageBox(
        NULL,
        _T("Elija una operación para continuar, por favor"),
        _T("Seleccione operación"),
        MB_OK
    );

    return msgboxID;
}

int mostrarMensajeReset()
{
    int msgboxID = MessageBox(
        NULL,
        _T("Se borrarán todos los datos y operaciones introducidos"),
        _T("Confirmar Reset"),
        MB_OK
    );

    return msgboxID;
}

int mostrarMensajeReset2()
{
    int msgboxID = MessageBox(
        NULL,
        _T("Se borrará lo último introducido"),
        _T("Confirmar borrado"),
        MB_OK
    );

    return msgboxID;
}

void anadirMenus(HWND hwnd)
{

    HMENU hMenubar;
    HMENU hMenu, hMenu2, hMenu3;

    hMenubar = CreateMenu();
    hMenu = CreateMenu();
    hMenu2 = CreateMenu();
    hMenu3 = CreateMenu();

    AppendMenuW(hMenu, MF_STRING, IDM_FILE_RESET, L"&Resetear");
    AppendMenuW(hMenu, MF_SEPARATOR, 0, NULL);
    AppendMenuW(hMenu, MF_STRING, IDM_FILE_EXIT, L"&Salir");

    AppendMenuW(hMenu2, MF_STRING, 0, L"&En proximas versiones, paciencia!");

    AppendMenuW(hMenu3, MF_STRING, IDM_PROGRAM_HELP, L"&Temas de ayuda");
    AppendMenuW(hMenu3, MF_SEPARATOR, 0, NULL);
    AppendMenuW(hMenu3, MF_STRING, IDM_FILE_ABOUT, L"&Acerca de...");

    AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR)hMenu, L"&Sesion");
    AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR)hMenu2, L"&Edicion");
    AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR)hMenu3, L"&Ayuda");
    SetMenu(hwnd, hMenubar);
}
/*  This function is called by the Windows function DispatchMessage()  */
void imprimirEdit(int i)                        //Funcion que concatena los numeros al hacer clic en los botones
{
    char cadenaEdit[31];                        //Se guarda la cadena de la pantalla
    char numero[3];                             //Variable donde se guardara el numero de la tecla que presionamos
    sprintf_s(numero, "%i", i);                   //Se transforma el numero (i) del tipo entero a una cadena

    GetWindowText(edit, cadenaEdit, 30);        //Se obtiene lo que hay en el edit y se guarda en "CadenaEdit"
    strcat_s(cadenaEdit, numero);                 //Se concatena lo que hay en cadena y lo que hay en "memoria", es decir, el valor de la tecla presionada
    SetWindowText(edit, cadenaEdit);            //Se imprime el nuevo numero en pantalla
}


LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    static HINSTANCE estancia = NULL;
    HWND Wnd;
    //Variables
    char cadenaEditMain[31];
    static int operacion;
    static double operando_1, operando_2, resultado, signo;


    switch (message)
    {

    case WM_CREATE:
    {
        estancia = ((LPCREATESTRUCT)lParam)->hInstance;

        edit = CreateWindowEx(WS_EX_CLIENTEDGE, _T("edit"), 0, ES_RIGHT | ES_NUMBER | WS_BORDER | WS_CHILD | WS_VISIBLE, 20, 30, 250, 55, hwnd, (HMENU)ID_EDIT, estancia, 0);
        
        anadirMenus(hwnd);
        boton1 = CreateWindow("Button", "1", BS_DEFPUSHBUTTON | BS_CENTER | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 20, 90, 40, 25, hwnd, (HMENU)ID_BOTON1, estancia, 0);
        boton2 = CreateWindow("Button", "2", BS_DEFPUSHBUTTON | BS_CENTER | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 65, 90, 40, 25, hwnd, (HMENU)ID_BOTON2, estancia, 0);
        boton3 = CreateWindow("Button", "3", BS_DEFPUSHBUTTON | BS_CENTER | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 110, 90, 40, 25, hwnd, (HMENU)ID_BOTON3, estancia, 0);
        boton4 = CreateWindow("Button", "4", BS_DEFPUSHBUTTON | BS_CENTER | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 20, 120, 40, 25, hwnd, (HMENU)ID_BOTON4, estancia, 0);
        boton5 = CreateWindow("Button", "5", BS_DEFPUSHBUTTON | BS_CENTER | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 65, 120, 40, 25, hwnd, (HMENU)ID_BOTON5, estancia, 0);
        boton6 = CreateWindow("Button", "6", BS_DEFPUSHBUTTON | BS_CENTER | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 110, 120, 40, 25, hwnd, (HMENU)ID_BOTON6, estancia, 0);
        boton7 = CreateWindow("Button", "7", BS_DEFPUSHBUTTON | BS_CENTER | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 20, 150, 40, 25, hwnd, (HMENU)ID_BOTON7, estancia, 0);
        boton8 = CreateWindow("Button", "8", BS_DEFPUSHBUTTON | BS_CENTER | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 65, 150, 40, 25, hwnd, (HMENU)ID_BOTON8, estancia, 0);
        boton9 = CreateWindow("Button", "9", BS_DEFPUSHBUTTON | BS_CENTER | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 110, 150, 40, 25, hwnd, (HMENU)ID_BOTON9, estancia, 0);
        boton0 = CreateWindow("Button", "0", BS_DEFPUSHBUTTON | BS_CENTER | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 20, 180, 40, 25, hwnd, (HMENU)ID_BOTONCERO, estancia, 0);
        botonComa = CreateWindow("Button", ",", BS_DEFPUSHBUTTON | BS_CENTER | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 65, 180, 40, 25, hwnd, (HMENU)ID_BOTONCOMA, estancia, 0);
        botonSigno = CreateWindow("Button", "+/-", BS_DEFPUSHBUTTON | BS_CENTER | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 110, 180, 40, 25, hwnd, (HMENU)ID_BOTONSIGNO, estancia, 0);
        botonSumar = CreateWindow("Button", "+", BS_DEFPUSHBUTTON | BS_CENTER | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 200, 90, 60, 25, hwnd, (HMENU)ID_BOTONSUMAR, estancia, 0);
        botonRestar = CreateWindow("Button", "-", BS_DEFPUSHBUTTON | BS_CENTER | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 200, 120, 60, 25, hwnd, (HMENU)ID_BOTONRESTAR, estancia, 0);
        botonMultiplicar = CreateWindow("Button", "*", BS_DEFPUSHBUTTON | BS_CENTER | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 200, 150, 60, 25, hwnd, (HMENU)ID_BOTONMULTIPLICAR, estancia, 0);
        botonDividir = CreateWindow("Button", "/", BS_DEFPUSHBUTTON | BS_CENTER | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 200, 180, 60, 25, hwnd, (HMENU)ID_BOTONDIVIDIR, estancia, 0);
        botonPotencia = CreateWindow("Button", "Pow", BS_DEFPUSHBUTTON | BS_CENTER | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 110, 215, 40, 25, hwnd, (HMENU)ID_BOTONPOTENCIA, estancia, 0);
        botonRaiz = CreateWindow("Button", "Raiz", BS_DEFPUSHBUTTON | BS_CENTER | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 110, 245, 40, 25, hwnd, (HMENU)ID_BOTONRAIZ, estancia, 0);
        botonIgual = CreateWindow("Button", "=", BS_DEFPUSHBUTTON | BS_CENTER | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 20, 220, 80, 45, hwnd, (HMENU)ID_BOTONIGUAL, estancia, 0);
        botonReset = CreateWindow("Button", "C", BS_DEFPUSHBUTTON | BS_CENTER | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 185, 250, 40, 25, hwnd, (HMENU)ID_BOTONRESET, estancia, 0);
        botonReset2 = CreateWindow("Button", "CE", BS_DEFPUSHBUTTON | BS_CENTER | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 235, 250, 40, 25, hwnd, (HMENU)ID_BOTONRESET2, estancia, 0);
        

        //Bloquear el boton "maximizar"
        DWORD dwStyle = (DWORD)GetWindowLong(hwnd, GWL_STYLE);
        dwStyle &= ~WS_MAXIMIZEBOX;
        SetWindowLong(hwnd, GWL_STYLE, (DWORD)dwStyle);
        RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_FRAME | RDW_ERASENOW);

        //Bloquear la opcion de cambiarle el tamaño a la ventana
        dwStyle &= ~WS_SIZEBOX;
        SetWindowLong(hwnd, GWL_STYLE, (DWORD)dwStyle);
        RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_FRAME | RDW_ERASENOW);

    }

    case WM_COMMAND:
    {
        switch (LOWORD(wParam))
        {
        case IDM_FILE_RESET:
            mostrarMensajeReset();
            operando_1 = 0;
            operando_2 = 0;
            operacion = 0;
            SetWindowText(edit, "");
            break;
        case IDM_FILE_EXIT:
            confirmarCerradoPrograma();
            break;
        case IDM_PROGRAM_HELP:
            Wnd = CreateWindowEx(0, szChildClassName, "Temas de Ayuda", WS_OVERLAPPEDWINDOW, 500, 270, 400, 400, hwnd, NULL, estancia, NULL);
            EnableWindow(WndPila_Cima(Pila), FALSE);
            WndPila_Insertar(&Pila, Wnd);
            ShowWindow(Wnd, SW_NORMAL);
            break;
        case IDM_FILE_ABOUT:
            Wnd = CreateWindowEx(0, szAboutClassName, "Acerca de", WS_OVERLAPPEDWINDOW, 500, 270, 400, 400, hwnd, NULL, estancia, NULL);
            EnableWindow(WndPila_Cima(Pila), FALSE);
            WndPila_Insertar(&Pila, Wnd);
            ShowWindow(Wnd, SW_NORMAL);
            break;
        }

        switch (wParam)
        {
        case ID_BOTON1:                
        {
            imprimirEdit(1);
            break;
        }
        case ID_BOTON2:
        {
            imprimirEdit(2);
            break;
        }
        case ID_BOTON3:
        {
            imprimirEdit(3);
            break;
        }
        case ID_BOTON4:
        {
            imprimirEdit(4);
            break;
        }
        case ID_BOTON5:
        {
            imprimirEdit(5);
            break;
        }
        case ID_BOTON6:
        {
            imprimirEdit(6);
            break;
        }
        case ID_BOTON7:
        {
            imprimirEdit(7);
            break;
        }
        case ID_BOTON8:
        {
            imprimirEdit(8);
            break;
        }
        case ID_BOTON9:
        {
            imprimirEdit(9);
            break;
        }
        case ID_BOTONCERO:
        {
            imprimirEdit(0);
            break;
        }
        case ID_BOTONCOMA:
        {
            GetWindowText(edit, cadenaEditMain, 30);        //Se obtiene lo que hay en el edit y se guarda en "CadenaEditMain"
            if (strstr(cadenaEditMain, ".") == NULL)        //Si vemos que no posee una coma se ejecuta lo que hay dentro del if (en caso de que ya tenga una coma lo ignora)
            {
                strcat_s(cadenaEditMain, ".");                //Añade una coma a lo que hay en "CadenaEditMain"
                SetWindowText(edit, cadenaEditMain);        //Se imprime el nuevo numero en el edit
            }
            break;
        }
        case ID_BOTONSIGNO:                                
        {
            GetWindowText(edit, cadenaEditMain, 30);        //Se obtiene lo que hay en el edit y se guarda en "CadenaEditMain"
            signo = atof(cadenaEditMain);                   //Realiza el cambio de tipo en double y lo guarda en "signo"
            signo *= -1;                                     //Multiplica el numero por -1 (CAMBIO DE SIGNO)
            sprintf_s(cadenaEditMain, "%f", signo);           //Guarda en "cadenaEditMain"
            SetWindowText(edit, cadenaEditMain);            //Se actualiza el número en pantalla
            break;
        }
        case ID_BOTONSUMAR:
        {
            operacion = 1;                                    //Sumará el número (lo indica)
            GetWindowText(edit, cadenaEditMain, 30);         //Obtiene el numero ingresado en el edit
            operando_1 = atof(cadenaEditMain);               //Transforma la cadena obtenida en un double y lo guarda en "primer_num"
            SetWindowText(edit, "");                         //Limpia el edit
            break;
        }
        case ID_BOTONRESTAR:
        {
            operacion = 2;                                    //Restará el número (lo indica)
            GetWindowText(edit, cadenaEditMain, 30);
            operando_1 = atof(cadenaEditMain);
            SetWindowText(edit, "");
            break;
        }
        case ID_BOTONMULTIPLICAR:
        {
            operacion = 3;                                    //Multiplicará el número (lo indica)
            GetWindowText(edit, cadenaEditMain, 30);
            operando_1 = atof(cadenaEditMain);
            SetWindowText(edit, "");
            break;
        }
        case ID_BOTONDIVIDIR:
        {
            operacion = 4;                                    //Dividirá el número (lo indica)
            GetWindowText(edit, cadenaEditMain, 30);
            operando_1 = atof(cadenaEditMain);
            SetWindowText(edit, "");
            break;
        }
        case ID_BOTONPOTENCIA:
        {
            operacion = 5;                                    //Potenciará al número
            GetWindowText(edit, cadenaEditMain, 30);
            operando_1 = atof(cadenaEditMain);
            SetWindowText(edit, "");
            break;
        }
        case ID_BOTONRAIZ:
        {
            operacion = 6;                                    //Hallará la raíz del número
            GetWindowText(edit, cadenaEditMain, 30);
            operando_1 = atof(cadenaEditMain);
            SetWindowText(edit, "");
            break;
        }
        case ID_BOTONIGUAL:
        {
            GetWindowText(edit, cadenaEditMain, 30);         //Obtiene el numero de la pantalla
            operando_2 = atof(cadenaEditMain);              //Cambia el tipo de la cadena en double y lo guarda en "segundo_num"
            resultado = calcular(operando_1, operando_2, operacion); //Calculamos el resultado, se le envían "operando_1", "operando_2" y "operacion"
            sprintf_s(cadenaEditMain, "%f", resultado);        //Se cambia el tipo en cadena y lo guarda en la variable
            SetWindowText(edit, cadenaEditMain);             //Se imprime en pantalla el resultado
            //Reseteamos las variables
            operando_1 = 0;
            operando_2 = 0;
            operacion = 0;
            break;
        }
        case ID_BOTONRESET:                                  //Boton que limpia las variables y datos para calcular de nuevo
        {
            mostrarMensajeReset();
            operando_1 = 0;
            operando_2 = 0;
            operacion = 0;
            SetWindowText(edit, "");
            break;
        }
        case ID_BOTONRESET2:                                 //Boton que borra solo el ultimo numero introducido
        {
            mostrarMensajeReset2();
            operando_2 = 0;
            SetWindowText(edit, "");
            break;
        }
        break;
        }
        break;
    }

    case WM_CLOSE:

        confirmarCerradoPrograma();
        break;

    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }

    return 0;
}

LRESULT CALLBACK WindowProcedureChild(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HINSTANCE estancia = NULL;
    const wchar_t cadena_texto[] = L"Bienvenido a Picoto Calculator, el uso es bastante fácil. Cuenta con un diseño ergonómico y 6 diferentes funciones: suma, resta, multiplicación, división, raíz y potencia. Espero que la disfrute!";
    switch (message) {
    case WM_CREATE: {
        estancia = ((LPCREATESTRUCT)lParam)->hInstance;
        CreateWindowW(L"static", cadena_texto, WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 20, 80, 345, 200, hWnd, NULL, NULL, NULL);
        botonAceptar = CreateWindow("Button", "Aceptar", BS_DEFPUSHBUTTON | BS_CENTER | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 135, 320, 120, 25, hWnd, (HMENU)ID_CLOSE_HELP, estancia, 0);

        //Bloquear el boton "maximizar"
        DWORD dwStyle = (DWORD)GetWindowLong(hWnd, GWL_STYLE);
        dwStyle &= ~WS_MAXIMIZEBOX;
        SetWindowLong(hWnd, GWL_STYLE, (DWORD)dwStyle);
        RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_FRAME | RDW_ERASENOW);

        //Bloquear la opcion de cambiarle el tamaño a la ventana
        dwStyle &= ~WS_SIZEBOX;
        SetWindowLong(hWnd, GWL_STYLE, (DWORD)dwStyle);
        RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_FRAME | RDW_ERASENOW);
        break;
    }
                  
    case WM_CLOSE: {
        DestroyWindow(WndPila_QuitarCima(&Pila));
        EnableWindow(WndPila_Cima(Pila), TRUE);
        SetFocus(WndPila_Cima(Pila));
        break;
    }
    case WM_COMMAND: {
        switch (wParam){
        case ID_CLOSE_HELP:                                 //Boton que cierra la ventana
        {
            DestroyWindow(WndPila_QuitarCima(&Pila));
            EnableWindow(WndPila_Cima(Pila), TRUE);
            SetFocus(WndPila_Cima(Pila));
            break;
        }
        break;
        }
     break;
    }
    default: {
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    }
    return 0;
}

LRESULT CALLBACK WindowProcedureAbout(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HINSTANCE estancia = NULL;
    const wchar_t cadena_texto[] = L"Picoto Calculator v0.5 final version - marzo de 2022, gracias por usar este programa, especial agradecimiento a Alien-Z y a Carlos Obregón por la inspiración y sobretodo a ti por usar este programa, saludos!";
    switch (message) {
    case WM_CREATE: {
        estancia = ((LPCREATESTRUCT)lParam)->hInstance;
        CreateWindowW(L"static", cadena_texto, WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 20, 80, 345, 200, hWnd, NULL, NULL, NULL);
        botonAceptar = CreateWindow("Button", "Aceptar", BS_DEFPUSHBUTTON | BS_CENTER | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 55, 320, 120, 25, hWnd, (HMENU)ID_CLOSE_ABOUT, estancia, 0);
        botonGitHub = CreateWindow("Button", "Mi perfil de GitHub", BS_DEFPUSHBUTTON | BS_CENTER | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 200, 320, 130, 25, hWnd, (HMENU)ID_GITHUB, estancia, 0);

        //Bloquear el boton "maximizar"
        DWORD dwStyle = (DWORD)GetWindowLong(hWnd, GWL_STYLE);
        dwStyle &= ~WS_MAXIMIZEBOX;
        SetWindowLong(hWnd, GWL_STYLE, (DWORD)dwStyle);
        RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_FRAME | RDW_ERASENOW);

        //Bloquear la opcion de cambiarle el tamaño a la ventana
        dwStyle &= ~WS_SIZEBOX;
        SetWindowLong(hWnd, GWL_STYLE, (DWORD)dwStyle);
        RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_FRAME | RDW_ERASENOW);
        break;
    }

    case WM_CLOSE: {
        DestroyWindow(WndPila_QuitarCima(&Pila));
        EnableWindow(WndPila_Cima(Pila), TRUE);
        SetFocus(WndPila_Cima(Pila));
        break;
    }
    case WM_COMMAND: {
        switch (wParam) {
        case ID_CLOSE_ABOUT:                                 //Boton que cierra la ventana
        {
            DestroyWindow(WndPila_QuitarCima(&Pila));
            EnableWindow(WndPila_Cima(Pila), TRUE);
            SetFocus(WndPila_Cima(Pila));
            break;
        }
        case ID_GITHUB:                                 //Boton que cierra la ventana
        {
            ShellExecute(NULL, "open", "https://github.com/PabloArias98", NULL, NULL, SW_SHOWNORMAL);
            break;
        }
        break;
        }
        break;
    }
    default: {
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    }
    return 0;
}

double calcular(double op_1, double op_2, int operacion)   //Funcion para calcular
{
    double resultado = 0;                                                    //Variable donde se guardara el resultado (sera lo que se retorne)

    switch (operacion)                                                   //Ver lo que hay en la variable "operacion"
    {
    case 1:
    {
        resultado = op_1 + op_2;
        break;
    }
    case 2:
    {
        resultado = op_1 - op_2;
        break;
    }
    case 3:
    {
        resultado = op_1 * op_2;
        break;
    }
    case 4:
    {
        resultado = op_1 / op_2;
        break;
    }
    case 5:
    {
        resultado = pow(op_1, op_2);
        break;
    }
    case 6:
    {
        resultado = pow(op_1, 1 / op_2);
        break;
    }
    default:                                                         //Si no se realiza ninguna operacion se imprime en el label un mensaje, con esto sabriamos si ha habido algun error
    {

        break;
    }
    }

    return resultado;                                                    //Devuelve el resultado
}
