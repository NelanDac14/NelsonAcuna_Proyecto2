/*
Autor: Nelson Andres Acuña Cambronero
Cédula: 116620490
Fecha inicio: 13/Octubre/2025
Hora inicio: 21:38
Fecha de finalización: -/-/2025 (Aún sin definir)
Hora de finalización: 00:00 (Aún sin definir)

*******************SISTEMA DE BIBLIOTECA C++*********************
Su función principal es gestionar los libros de una biblioteca
escolar. Se administrará un catálogo de libros y un registro de
préstamos de libros. Toda esta infomación se almacenará en un
archivo de texto (.txt).

Se validará de manera robusta la integridad de los datos ingresados
por el usuario al igual que el manejo de excepciones en caso de ser
necesario por algún dato mal ingresado o incorrecto.

El usuario podrá:
    1. Ingresar registro al catálogo.
    2. Mostrar catálogo.
    3. Registrar nuevo préstamo.
    4. Devolver libro.
    5. Ver historial de préstamos.
    6. Salir.

******************REFERENCIAS BIBLIOGRÁFICAS************************
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
#include <locale.h>//Visualización de acentos en consola
#include <iomanip>//Parte de la librería de entrada/salida, utilizado para el setfill() y setw()
#include <conio.h>//Para uso del getch()
#include <vector>//Para trabajar con vectores
#include <ctime>//Para trabajar con la hora y fecha de los registros de transacciones
#include <sstream>//Para trabajar con el stringstream
#include <thread>//Para detener el ciclo del código durante una 'x' cantidad de segundos
#include <chrono>//Para efectuar los segundos al thread
#include <windows.h>//Para manejo del de acentos y caracteres especiales en entrada y salida en windows

using namespace std;
//Estructuras de datos
struct libro_catalogo
{
    int id_libro; //Campo numérico de máximo 6 dígitos, no letras, no espacios en blanco
    string titulo_libro; //Nombre del libro debe permitir una o más palabras
    string autor_libro; //Nombre del autor debe permitir una o más palabras
    int copias_disponibles;//No permite números negativos y debe estar en un rango de 1-9 máximo, no letras, no espacios en blanco
};

struct prestamo_libro
{
    string id_alunmo; //Valor numérico de mínimo/máximo 9 dígitos, no letras, no espacios en blanco
    int id_libro; //Campo numérico de máximo 6 dígitos, no letras, no espacios en blanco
    string nombre_alumno;//Nombre y apellidos, validar que no permita espacios en blanco
    string fecha_prestamo;//Debe generarse automáticamente y con posibilidad de modificarlo, Formato: DD/MM/YYYY

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
            //Mostramos el menú y recibimos la opción del usuario
            menu_principal(opc_usuario);
            //Si el cin entra en fallo (cin.fail()); limpiamos buffer
            if(cin.fail())
            {
                cin.clear();//Limpia el fallo del cin.fail()
                cin.ignore(100 , '\n');//Ignora el buffer restante hasta el ENTER
                throw runtime_error("Valor inválido, inténtelo de nuevo.");

            }
        }
        catch(const exception& e)
        {
            system("CLS");//Limpia o borra pantalla.
            //Imprimimos el Error a notificar al usuario
            cerr << "Error: " << e.what();
            this_thread::sleep_for(chrono::seconds(1));//Detenemos el programa para mostrar el mensaje
        }


        //Valoramos al opción elegida por el usuario y se destina a su caso respectivo
        switch(opc_usuario)
        {
        case 1://Ingresar registro al catálogo.
            break;
        case 2://Mostrar catálogo.
            break;
        case 3://Registrar nuevo préstamo.
            break;
        case 4://Devolver libro.
            break;
        case 5://Ver historial de préstamos.
            break;
        case 6://Salir.
            break;
        default://Dato fuera del rango
            system("CLS");//Limpia o borra pantalla.
            cout << "Opción inválida: inténtelo de nuevo." << endl;
            this_thread::sleep_for(chrono::seconds(1));//Detenemos el programa para mostrar el mensaje
            break;
        }
    }
    while(opc_usuario != 6);//Fin Do/While que valida salir del programa
    return 0;
}

//Desarrolo de funciones

/*
Muestra el Menú Principal y recibe la opción elegida
por el usuario
*/
void menu_principal(int &opc_usuario)
{
    system("CLS");//Limpia o borra pantalla.
    //Linea superior
    cout << left << setfill('=') << setw(37) << "=" << endl;// ancho pantalla 37 caracteres
    //Título
    cout << left << setfill(' ') << setw(37) << "      SISTEMA DE BIBLIOTECA C++" << endl;// ancho pantalla 36 caracteres
    //Linea inferior
    cout << left << setfill('=') << setw(37) << "=" << endl;// ancho pantalla 37 caracteres

    //Opciones del menú
    cout << left << setfill(' ') << setw(37) << "\n1. Ingresar registro al catálogo." << endl;
    cout << left << setfill(' ') << setw(37) << "2. Mostrar catálogo." << endl;
    cout << left << setfill(' ') << setw(37) << "3. Registrar nuevo préstamo." << endl;
    cout << left << setfill(' ') << setw(37) << "4. Devolver libro." << endl;
    cout << left << setfill(' ') << setw(37) << "5. Ver historial de préstamos." << endl;
    cout << left << setfill(' ') << setw(37) << "6. Salir." << endl;

    //Solicitamos la opción al usuario
    cout << left << "\nIngrese una opción: ";
    cin >> opc_usuario;
}//Fin de la función menu_principal

