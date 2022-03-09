#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <math.h>

//ID´s
enum {ID_EDIT, ID_BOTONIGUAL, ID_BOTONRESET, ID_BOTONRESET2, ID_BOTONSUMAR, ID_BOTONRESTAR, ID_BOTONMULTIPLICAR, ID_BOTONDIVIDIR, ID_BOTONCOMA, ID_BOTONSIGNO, ID_BOTONCERO, ID_BOTON1, ID_BOTON2, ID_BOTON3, ID_BOTON4, ID_BOTON5, ID_BOTON6, ID_BOTON7, ID_BOTON8, ID_BOTON9};


//Prototipos
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

//funcion para imprimir en pantalla
void imprimirEdit (int i);

//mensajes de info
int mostrarMensajeReset();
int mostrarMensajeReset2();
int mostrarMensajeError();
int confirmarCerradoPrograma();                                                 //Funcion que concatena los numeros en pantalla
double calcular (double primer_num, double segundo_num, int operacion);     //Funcion que realiza las operaciones

HINSTANCE estancia;
HWND edit;

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


char szClassName[ ] = "CodeBlocksWindowsApp";

int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    estancia = hThisInstance;

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */

    wincl.hIcon = (HICON)LoadImage(NULL, "icono.ico", IMAGE_ICON, 32,32,LR_LOADFROMFILE);;
    wincl.hIconSm = LoadIcon (estancia, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */


    //Le damos una tonalidad verde al fondo de la app
    wincl.hbrBackground = (HBRUSH) CreateSolidBrush (RGB(157, 249, 121));

    if (!RegisterClassEx (&wincl))
        return 0;

    hwnd = CreateWindowEx (
               0,                   /* Extended possibilites for variation */
               szClassName,         /* Classname */
               "Picoto Calculator v0.1",
               WS_OVERLAPPEDWINDOW, /* default window */
               CW_USEDEFAULT,       /* Windows decides the position */
               CW_USEDEFAULT,       /* where the window ends up on the screen */
               310,                 /* The programs width */
               350,                 /* and height in pixels */
               HWND_DESKTOP,        /* The window is a child-window to desktop */
               NULL,                /* No menu */
               hThisInstance,       /* Program Instance handler */
               NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;

    //Variables
    char cadenaEditMain [31];
    static int operacion;
    static double operando_1, operando_2, resultado, signo;


    switch (message)
    {
    case WM_CREATE:
    {
        //Componentes
        edit = CreateWindowEx (WS_EX_CLIENTEDGE, "edit", 0, ES_RIGHT | ES_NUMBER | WS_BORDER | WS_CHILD | WS_VISIBLE, 20, 30, 250, 55, hwnd, (HMENU)ID_EDIT, estancia, 0);

        boton1 = CreateWindow ("Button", "1", BS_DEFPUSHBUTTON | BS_CENTER | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 20, 90, 40, 25, hwnd, (HMENU) ID_BOTON1, estancia, 0);
        boton2 = CreateWindow ("Button", "2", BS_DEFPUSHBUTTON | BS_CENTER | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 65, 90, 40, 25, hwnd, (HMENU) ID_BOTON2, estancia, 0);
        boton3 = CreateWindow ("Button", "3", BS_DEFPUSHBUTTON | BS_CENTER | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 110, 90, 40, 25, hwnd, (HMENU) ID_BOTON3, estancia, 0);
        boton4 = CreateWindow ("Button", "4", BS_DEFPUSHBUTTON | BS_CENTER | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 20, 120, 40, 25, hwnd, (HMENU) ID_BOTON4, estancia, 0);
        boton5 = CreateWindow ("Button", "5", BS_DEFPUSHBUTTON | BS_CENTER | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 65, 120, 40, 25, hwnd, (HMENU) ID_BOTON5, estancia, 0);
        boton6 = CreateWindow ("Button", "6", BS_DEFPUSHBUTTON | BS_CENTER | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 110, 120, 40, 25, hwnd, (HMENU) ID_BOTON6, estancia, 0);
        boton7 = CreateWindow ("Button", "7", BS_DEFPUSHBUTTON | BS_CENTER | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 20, 150, 40, 25, hwnd, (HMENU) ID_BOTON7, estancia, 0);
        boton8 = CreateWindow ("Button", "8", BS_DEFPUSHBUTTON | BS_CENTER | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 65, 150, 40, 25, hwnd, (HMENU) ID_BOTON8, estancia, 0);
        boton9 = CreateWindow ("Button", "9", BS_DEFPUSHBUTTON | BS_CENTER | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 110, 150, 40, 25, hwnd, (HMENU) ID_BOTON9, estancia, 0);
        boton0 = CreateWindow ("Button", "0", BS_DEFPUSHBUTTON | BS_CENTER | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 20, 180, 40, 25, hwnd, (HMENU) ID_BOTONCERO, estancia, 0);
        botonComa = CreateWindow ("Button", ",", BS_DEFPUSHBUTTON | BS_CENTER | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 65, 180, 40, 25, hwnd, (HMENU) ID_BOTONCOMA, estancia, 0);
        botonSigno = CreateWindow ("Button", "+/-", BS_DEFPUSHBUTTON | BS_CENTER | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 110, 180, 40, 25, hwnd, (HMENU) ID_BOTONSIGNO, estancia, 0);
        botonSumar = CreateWindow ("Button", "+", BS_DEFPUSHBUTTON | BS_CENTER | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 200, 90, 60, 25, hwnd, (HMENU) ID_BOTONSUMAR, estancia, 0);
        botonRestar = CreateWindow ("Button", "-", BS_DEFPUSHBUTTON | BS_CENTER | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 200, 120, 60, 25, hwnd, (HMENU) ID_BOTONRESTAR, estancia, 0);
        botonMultiplicar = CreateWindow ("Button", "*", BS_DEFPUSHBUTTON | BS_CENTER | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 200, 150, 60, 25, hwnd, (HMENU) ID_BOTONMULTIPLICAR, estancia, 0);
        botonDividir = CreateWindow ("Button", "/", BS_DEFPUSHBUTTON | BS_CENTER | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 200, 180, 60, 25, hwnd, (HMENU) ID_BOTONDIVIDIR, estancia, 0);
        botonIgual = CreateWindow ("Button", "=", BS_DEFPUSHBUTTON | BS_CENTER | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 20, 220, 80, 45, hwnd, (HMENU) ID_BOTONIGUAL, estancia, 0);
        botonReset = CreateWindow ("Button", "C", BS_DEFPUSHBUTTON | BS_CENTER | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 185, 250, 40, 25, hwnd, (HMENU) ID_BOTONRESET, estancia, 0);
        botonReset2 = CreateWindow ("Button", "CE", BS_DEFPUSHBUTTON | BS_CENTER | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 235, 250, 40, 25, hwnd, (HMENU) ID_BOTONRESET2, estancia, 0);

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
        switch (wParam)
        {
        case ID_BOTON1:                  //Al presionar el boton 1 se llama a la funcion "imprimirEdit" y se le envia el valor "1" que es lo que queremos que se concatene a lo que ya haya en el edit
        {
            imprimirEdit (1);
            break;
        }
        case ID_BOTON2:
        {
            imprimirEdit (2);
            break;
        }
        case ID_BOTON3:
        {
            imprimirEdit (3);
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
            GetWindowText (edit, cadenaEditMain, 30);        //Se obtiene lo que hay en el edit y se guarda en "CadenaEditMain"
            if (strstr (cadenaEditMain, ".") == NULL)        //Si vemos que no posee una coma se ejecuta lo que hay dentro del if (en caso de que ya tenga una coma lo ignora)
            {
                strcat (cadenaEditMain, ".");                //Añade una coma a lo que hay en "CadenaEditMain"
                SetWindowText (edit, cadenaEditMain);        //Se imprime el nuevo numero en el edit
            }
            break;
        }
        case ID_BOTONSIGNO:                                  //Boton para cambiar el signo
        {
            GetWindowText (edit, cadenaEditMain, 30);        //Se obtiene lo que hay en el edit y se guarda en "CadenaEditMain"
            signo = atof (cadenaEditMain);                   //Realiza el cambio de tipo en double y lo guarda en "signo"
            signo *= -1;                                     //Multiplica el numero por -1 (CAMBIO DE SIGNO)
            sprintf (cadenaEditMain, "%f", signo);           //Guarda en "cadenaEditMain"
            SetWindowText (edit, cadenaEditMain);            //Se actualiza el número en pantalla
            break;
        }
        case ID_BOTONSUMAR:
        {
            operacion = 1;                                    //Sumará el número (lo indica)
            GetWindowText (edit, cadenaEditMain, 30);         //Obtiene el numero ingresado en el edit
            operando_1 = atof (cadenaEditMain);               //Transforma la cadena obtenida en un double y lo guarda en "primer_num"
            SetWindowText (edit, "");                         //Limpia el edit
            break;
        }
        case ID_BOTONRESTAR:
        {
            operacion = 2;                                    //Restará el número (lo indica)
            GetWindowText (edit, cadenaEditMain, 30);
            operando_1 = atof (cadenaEditMain);
            SetWindowText (edit, "");
            break;
        }
        case ID_BOTONMULTIPLICAR:
        {
            operacion = 3;                                    //Multiplicará el número (lo indica)
            GetWindowText (edit, cadenaEditMain, 30);
            operando_1 = atof (cadenaEditMain);
            SetWindowText (edit, "");
            break;
        }
        case ID_BOTONDIVIDIR:
        {
            operacion = 4;                                    //Dividirá el número (lo indica)
            GetWindowText (edit, cadenaEditMain, 30);
            operando_1 = atof (cadenaEditMain);
            SetWindowText (edit, "");
            break;
        }
        case ID_BOTONIGUAL:
        {
            GetWindowText (edit, cadenaEditMain, 30);         //Obtiene el numero de la pantalla
            operando_2 = atof (cadenaEditMain);              //Cambia el tipo de la cadena en double y lo guarda en "segundo_num"
            resultado = calcular (operando_1, operando_2, operacion); //Calculamos el resultado, se le envían "operando_1", "operando_2" y "operacion"
            sprintf (cadenaEditMain, "%f", resultado);        //Se cambia el tipo en cadena y lo guarda en la variable
            SetWindowText (edit, cadenaEditMain);             //Se imprime en pantalla el resultado
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
            SetWindowText (edit, "");
            break;
        }
        case ID_BOTONRESET2:                                 //Boton que borra solo el ultimo numero introducido
        {
            mostrarMensajeReset2();
            operando_2 = 0;
            SetWindowText (edit, "");
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
        return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

int confirmarCerradoPrograma()
{
    int msgboxID = MessageBox(
                       NULL,
                       "Saldrá del programa, desea continuar?",
                       "Salir",
                       MB_ICONEXCLAMATION | MB_YESNO
                   );

    if (msgboxID == IDYES)
    {
        PostQuitMessage (0);
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
                       "Elija una operación para continuar, por favor",
                       "Seleccione operación",
                       MB_OK
                   );

    if (msgboxID == IDOK)
    {

    }

    return msgboxID;
}

int mostrarMensajeReset()
{
    int msgboxID = MessageBox(
                       NULL,
                       "Se borrarán todos los datos y operaciones introducidos",
                       "Confirmar Reset",
                       MB_OK
                   );

    if (msgboxID == IDOK)
    {

    }

    return msgboxID;
}

int mostrarMensajeReset2()
{
    int msgboxID = MessageBox(
                       NULL,
                       "Se borrará lo último introducido",
                       "Confirmar borrado",
                       MB_OK
                   );

    if (msgboxID == IDOK)
    {

    }

    return msgboxID;
}

void imprimirEdit (int i)                        //Funcion que concatena los numeros al hacer clic en los botones
{
    char cadenaEdit [31];                        //Se guarda la cadena de la pantalla
    char numero [3];                             //Variable donde se guardara el numero de la tecla que presionamos
    sprintf (numero, "%i", i);                   //Se transforma el numero (i) del tipo entero a una cadena

    GetWindowText (edit, cadenaEdit, 30);        //Se obtiene lo que hay en el edit y se guarda en "CadenaEdit"
    strcat (cadenaEdit, numero);                 //Se concatena lo que hay en cadena y lo que hay en "memoria", es decir, el valor de la tecla presionada
    SetWindowText (edit, cadenaEdit);            //Se imprime el nuevo numero en pantalla
}

double calcular (double op_1, double op_2, int operacion)   //Funcion para calcular
{
    double resultado;                                                    //Variable donde se guardara el resultado (sera lo que se retorne)

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
    default:                                                         //Si no se realiza ninguna operacion se imprime en el label un mensaje, con esto sabriamos si ha habido algun error
    {
        mostrarMensajeError();
        break;
    }
    }

    return resultado;                                                    //Devuelve el resultado
}
