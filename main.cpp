/*
Autor: Nelson Andres Acu�a Cambronero
C�dula: 116620490
Fecha inicio: 13/Octubre/2025
Hora inicio: 21:38
Fecha de finalizaci�n: -/-/2025 (A�n sin definir)
Hora de finalizaci�n: 00:00 (A�n sin definir)

*******************SISTEMA DE BIBLIOTECA C++*********************
Su funci�n principal es gestionar los libros de una biblioteca
escolar. Se administrar� un cat�logo de libros y un registro de
pr�stamos de libros. Toda esta infomaci�n se almacenar� en un
archivo de texto (.txt).

Se validar� de manera robusta la integridad de los datos ingresados
por el usuario al igual que el manejo de excepciones en caso de ser
necesario por alg�n dato mal ingresado o incorrecto.

El usuario podr�:
    1. Ingresar registro al cat�logo.
    2. Mostrar cat�logo.
    3. Registrar nuevo pr�stamo.
    4. Devolver libro.
    5. Ver historial de pr�stamos.
    6. Salir.

******************REFERENCIAS BIBLIOGR�FICAS************************
https://ss64.com/tools/locale.html
https://cplusplus.com/reference/clocale/setlocale/?kw=setLocale
https://en.cppreference.com/w/cpp/chrono/c/ctime
https://cplusplus.com/reference/sstream/stringstream/?kw=stringstream
https://cplusplus.com/reference/cstddef/size_t/
https://cplusplus.com/reference/string/string/insert/
https://en.cppreference.com/w/cpp/string/basic_string_view/npos
https://en.cppreference.com/w/cpp/thread/thread/thread.html
https://en.cppreference.com/w/cpp/header/chrono.html
*/

#include <iostream>
#include <locale.h>//Visualizaci�n de acentos en consola
#include <iomanip>//Parte de la librer�a de entrada/salida, utilizado para el setfill() y setw()
#include <conio.h>//Para uso del getch()
#include <vector>//Para trabajar con vectores
#include <ctime>//Para trabajar con la hora y fecha de los registros de transacciones
#include <sstream>//Para trabajar con el stringstream
#include <thread>//Para detener el ciclo del c�digo durante una 'x' cantidad de segundos
#include <chrono>//Para efectuar los segundos al thread
#include <windows.h>//Para manejo del de acentos y caracteres especiales en entrada y salida en windows
#include <fstream> //Para manejo de archivos
#include <sstream> //Para manejo de cadenas
#include <limits> //Para los numeric_limits

using namespace std;
//Estructuras de datos
struct libro_catalogo
{
    int id_libro; //Campo num�rico de m�ximo 6 d�gitos, no letras, no espacios en blanco
    string titulo_libro; //Nombre del libro debe permitir una o m�s palabras
    string autor_libro; //Nombre del autor debe permitir una o m�s palabras
    int copias_disponibles;//No permite n�meros negativos y debe estar en un rango de 1-9 m�ximo, no letras, no espacios en blanco
};

struct prestamo_libro
{
    string id_alunmo; //Valor num�rico de m�nimo/m�ximo 9 d�gitos, no letras, no espacios en blanco
    int id_libro; //Campo num�rico de m�ximo 6 d�gitos, no letras, no espacios en blanco
    string nombre_alumno;//Nombre y apellidos, validar que no permita espacios en blanco
    string fecha_prestamo;//Debe generarse autom�ticamente y con posibilidad de modificarlo, Formato: DD/MM/YYYY

};

//Constantes de uso global
const string arch_catalogo = "catalogo.txt";
const string arch_prestamos = "prestamos.txt";

//Funciones m�nimas requeridas
void cargar_catalogo();//Cargar cat�logo disponible
void guardar_Catalogo();//Guardar cambios en el cat�logo
void cargar_prestamos();//Cargar lista de pr�stamos
void guardar_prestamos();//Guardar nuevo pr�stamo
void mostrar_menu(int &);//Muestra el men� principal (Realizada)
void ing_reg_catalogo();//ingresar_registro_catalogo
void reg_nue_prestamo();//registrar_nuevo_prestamo
void devolver_libro();//Realizar la devoluci�n de libros a la biblioteca
void historial_prestamos();//Ver el historial de pr�stamos

//Funciones Extras
void crea_arch_catalogo();
void crea_arch_prestamos();

//Funciones de validaci�n
bool regresar_menu(bool&, string&);//Procesar Opci�n S/N (Realizada)

int main()
{
    //Muestra y lee los acentos de consola o desde el archivo .txt
    SetConsoleOutputCP(1252);
    SetConsoleCP(1252);
    //Constantes
    //Variables
    int opc_usuario = 0;
    string mensaje = "";
    bool salir_programa = false;

    do
    {
        try
        {
            //Mostramos el men� y recibimos la opci�n del usuario
            mostrar_menu(opc_usuario);
            //Si el cin entra en fallo (cin.fail()); limpiamos buffer
            if(cin.fail())
            {
                cin.clear();//Limpia el fallo del cin.fail()
                cin.ignore(100, '\n'); //Ignora el buffer restante hasta el ENTER
                throw runtime_error("Valor inv�lido, int�ntelo de nuevo.");

            }
        }
        catch(const exception& e)
        {
            system("CLS");//Limpia o borra pantalla.
            //Imprimimos el Error a notificar al usuario
            cerr << "Error: " << e.what();
            this_thread::sleep_for(chrono::seconds(1));//Detenemos el programa para mostrar el mensaje
        }


        //Valoramos al opci�n elegida por el usuario y se destina a su caso respectivo
        switch(opc_usuario)
        {
        case 1://Ingresar registro al cat�logo.
            crea_arch_catalogo();
            break;
        case 2://Mostrar cat�logo.
            break;
        case 3://Registrar nuevo pr�stamo.
            crea_arch_prestamos();
            break;
        case 4://Devolver libro.
            break;
        case 5://Ver historial de pr�stamos.
            break;
        case 6://Salir.
            mensaje = "�Desea salir del programa?";
            if(regresar_menu(salir_programa, mensaje))
            {
                system("CLS");//Limpia o borra pantalla.
                //Linea superior
                cout << left << setfill('=') << setw(36) << "=" << endl;// ancho pantalla 37 caracteres
                //T�tulo
                cout << left << setfill(' ') << setw(36) << "        SALIENDO DEL SISTEMA" << endl;// ancho pantalla 36 caracteres
                //Linea inferior
                cout << left << setfill('=') << setw(36) << "=" << endl;// ancho pantalla 37 caracteres

                //Opciones del men�
                cout << left << setfill(' ') << setw(36) << "\nGracias por usar el Sistema de Biblioteca C++" << endl;
                this_thread::sleep_for(chrono::seconds(1));//Detenemos el programa para mostrar el mensaje
                cout << left << setfill(' ') << setw(36) << "\n�Hasta pronto!" << endl;
                this_thread::sleep_for(chrono::seconds(2));//Detenemos el programa para mostrar el mensaje
            }
            else
            {
                opc_usuario = 0;
            }

            break;
        default://Dato fuera del rango
            system("CLS");//Limpia o borra pantalla.
            cout << "Opci�n inv�lida: int�ntelo de nuevo." << endl;
            this_thread::sleep_for(chrono::seconds(1));//Detenemos el programa para mostrar el mensaje
            break;
        }
    }
    while(opc_usuario != 6);//Fin Do/While que valida salir del programa
    return 0;
}

//Desarrolo de funciones

/*
Muestra el Men� Principal y recibe la opci�n elegida
por el usuario
*/
void mostrar_menu(int &opc_usuario)
{
    system("CLS");//Limpia o borra pantalla.
    //Linea superior
    cout << left << setfill('=') << setw(37) << "=" << endl;// ancho pantalla 37 caracteres
    //T�tulo
    cout << left << setfill(' ') << setw(37) << "      SISTEMA DE BIBLIOTECA C++" << endl;// ancho pantalla 36 caracteres
    //Linea inferior
    cout << left << setfill('=') << setw(37) << "=" << endl;// ancho pantalla 37 caracteres

    //Opciones del men�
    cout << left << setfill(' ') << setw(37) << "\n1. Ingresar registro al cat�logo." << endl;
    cout << left << setfill(' ') << setw(37) << "2. Mostrar cat�logo." << endl;
    cout << left << setfill(' ') << setw(37) << "3. Registrar nuevo pr�stamo." << endl;
    cout << left << setfill(' ') << setw(37) << "4. Devolver libro." << endl;
    cout << left << setfill(' ') << setw(37) << "5. Ver historial de pr�stamos." << endl;
    cout << left << setfill(' ') << setw(37) << "6. Salir." << endl;

    //Solicitamos la opci�n al usuario
    cout << left << "\nIngrese una opci�n: ";
    cin >> opc_usuario;
}//Fin de la funci�n menu_principal
/*
Valida si el usuario desea regresar al men� principal
*/
bool regresar_menu(bool& salir_programa, string& mensaje)
{
    char opc_usuario = ' ';

    //Do/While que repite la pregunta mientra el usuario digite un valor inv�lido
    do
    {
        system("CLS");//Limpia o borra pantalla.
        //Realizamos la pregunta de respuesta "S�" o "No"
        cout << "\n" + mensaje + " Digite 'S' para s� o 'N' para no." << endl;
        cout << "R/: ";
        //Validamos la respuesta del usuario media Try/Catch
        try
        {
            cin >> opc_usuario;
            //Convertimos lo ingresado por el usuario a may�scula por cualquier duda
            opc_usuario = toupper(opc_usuario);
            if (cin.fail())
            {
                cin.clear();//Limpiamos el fallo del cin.fail()
                cin.ignore(100, '\n');//Ignora el buffer restante hasta el ENTER
                throw runtime_error("Entrada inv�lida: Digite 'S' para s� o 'N' para no.");
            }

            switch(opc_usuario)
            {
            case 'S':
                //Responde s� a la pregunta realizada.
                return true;
                salir_programa = true;
                break;
            case 'N':
                //Responde no a la pregunta realizada.
                return false;
                salir_programa = false;
                break;
            default://Opci�n por defautl
                throw runtime_error("Entrada inv�lida: Digite 'S' para s� o 'N' para no.");
                break;
            }

        }
        catch(const exception& e)
        {
            system("CLS");//Limpia o borra pantalla.
            //Imprimimos el error capturado
            cerr << "Error: " << e.what() << endl;
            this_thread::sleep_for(chrono::seconds(1));//Detenemos el programa para mostrar el mensaje
        }



    }
    while(opc_usuario != 'S' && opc_usuario != 'N');

    return false;
}


/*
Crea el archivo cat�logo.txt y coloca los encabezados
*/
void crea_arch_catalogo()
{
    //Creamos el archivo de cat�logo.txt
    ofstream archivo(arch_catalogo, ios::app | ios::binary);
    //Si el se creo correctamente
    if(archivo.is_open())
    {
        archivo.seekp(0, ios::end); //Nos mueve el puntero a la ultima ubicacion del cat�logo.txt
        streampos pos_puntero = archivo.tellp();
        // Verifica si el archivo est� vac�o para agregar encabezados
        if (pos_puntero == 0)
        {
            //Agregamos los encabezados
            //Linea separadora superior
            archivo << left << setfill('=') << setw(132) << "=" << endl;
            //Nombres de los encabezados
            archivo << left << setfill(' ')<< setw(6) << "  ID"
                    << "|" << setw(56) << "                         T�TULO"
                    << "|" << setw(55) << "                         AUTOR"
                    << "|" << setw(11) << "DISPONIBLES"
                    << "|" << endl;
            //Linea separadora inferior
            archivo << left << setfill('=') << setw(132) << "=" << endl;
        }
    }
}

/*
Crea el archivo prestamos.txt y coloca los encabezados
*/
void crea_arch_prestamos()
{
    //Creamos el archivo de prestamos.txt
    ofstream archivo(arch_prestamos, ios::app | ios::binary);
    //Si el se creo correctamente
    if(archivo.is_open())
    {
        archivo.seekp(0, ios::end); //Nos mueve el puntero a la ultima ubicacion del prestamos.txt
        streampos pos_puntero = archivo.tellp();
        // Verifica si el archivo est� vac�o para agregar encabezados
        if (pos_puntero == 0)
        {
            //Agregamos los encabezados
            //Linea separadora superior
            archivo << left << setfill('=') << setw(86) << "=" << endl;
            //Nombres de los encabezados
            archivo << left << setfill(' ')<< setw(9) << "ALUMNO ID"
                    << "|" << setw(55) << "                   NOMBRE DEL ALUMNO"
                    << "|" << setw(8) << "LIBRO ID"
                    << "|" << setw(10) << "  FECHA"
                    << "|" << endl;
            //Linea separadora inferior
            archivo << left << setfill('=') << setw(86) << "=" << endl;
        }
    }
}

