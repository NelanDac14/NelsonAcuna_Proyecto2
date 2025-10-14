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

//Funciones
void menu_principal(int &);
void ing_reg_catalogo();//ingresar_registro_catalogo

int main()
{
    //Muestra y lee los acentos de consola o desde el archivo .txt
    SetConsoleOutputCP(1252);
    SetConsoleCP(1252);
    //Constantes
    //Variables
    int opc_usuario = 0;

    do
    {
        try
        {
            //Mostramos el men� y recibimos la opci�n del usuario
            menu_principal(opc_usuario);
            //Si el cin entra en fallo (cin.fail()); limpiamos buffer
            if(cin.fail())
            {
                cin.clear();//Limpia el fallo del cin.fail()
                cin.ignore(100 , '\n');//Ignora el buffer restante hasta el ENTER
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
            break;
        case 2://Mostrar cat�logo.
            break;
        case 3://Registrar nuevo pr�stamo.
            break;
        case 4://Devolver libro.
            break;
        case 5://Ver historial de pr�stamos.
            break;
        case 6://Salir.
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
void menu_principal(int &opc_usuario)
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

