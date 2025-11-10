/*
Autor: Nelson Andres Acuña Cambronero
Cédula: 116620490
Fecha inicio: 13/Octubre/2025
Hora inicio: 21:38
Fecha de finalización: 09/11/2025
Hora de finalización: 20:39

*******************SISTEMA DE BIBLIOTECA C++*********************
Su función principal es gestionar los libros de una biblioteca
escolar. Se administrará un catálogo de libros y un registro de
préstamos de libros. Toda esta infomación se almacenará en un
archivo de texto correspondientes a catalogo.txt y prestamos.txt.

Se validará de manera robusta la integridad de los datos ingresados
por el usuario al igual que el manejo de excepciones en caso de ser
necesario por algún dato mal ingraesado o incorrecto.

Podremos registrar nuevos libros, realizar préstamos a alumnos y procesar
devoluciones correspondientes. En todo caso el flujo de datos se torna
mediante una carga y descarga de datos en vectores y que luego se ingresan o
o actualizan al archivo correspondiente.

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
https://en.cppreference.com/w/cpp/algorithm/find.html#Version_3
https://en.cppreference.com/w/cpp/header/sstream.html
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
#include <fstream> //Para manejo de archivos
#include <string> //Para manejo de cadenas
#include <limits> //Para los numeric_limits
#include <algorithm>// Para find_if


using namespace std;
//Estructuras de datos
struct info_libro_catalogo
{
    string id_libro; //Campo numérico de máximo 6 dígitos, no letras, no espacios en blanco
    string titulo_libro; //Nombre del libro debe permitir una o más palabras
    string autor_libro; //Nombre del autor debe permitir una o más palabras
    int copias_disponibles;//No permite números negativos y debe estar en un rango de 1-9 máximo, no letras, no espacios en blanco
};

struct info_prestamo_libro
{
    string id_alumno; //Valor numérico de mínimo/máximo 9 dígitos, no letras, no espacios en blanco
    string id_libro; //Campo numérico de máximo 6 dígitos, no letras, no espacios en blanco
    string nombre_alumno;//Nombre y apellidos, validar que no permita espacios en blanco
    string fecha_prestamo;//Debe generarse automáticamente y con posibilidad de modificarlo, Formato: DD/MM/YYYY

};

//Constantes de uso global
const string arch_catalogo = "catalogo.txt";
const string arch_prestamos = "prestamos.txt";
const int dig_id_libro = 6;
const int dig_id_alumno = 9;
const int agre_registro = 1;
const int act_registros = 2;

//Funciones de vector
vector<info_libro_catalogo> cargar_catalogo(const string&);//Cargar catálogo disponible para mostrarlo
vector<info_prestamo_libro> cargar_prestamos(const string&);//Cargar préstamos para mostrarlo

//Funciones void
void mostrar_error(string&, int&);//Muestra un error y produce un sonido (Realizada)
void val_nomb_tit(string&, string&, string&);//Valida que el dato de nombre o título no se encuentre vacío (Realizada)
void guardar_catalogo(const vector<info_libro_catalogo>&, const int);//Guardar cambios en el catálogo (Realizada)
void guardar_prestamos(const vector<info_prestamo_libro>&);//Guardar nuevo préstamo
void mostrar_menu(int &);//Muestra el menú principal (Realizada)
void devolver_libro(bool&, string&, string&);//Realizar la devolución de libros a la biblioteca
void crea_arch_catalogo();//Crea el archivo de catálogo.txt (Realizada)
void crea_arch_prestamos();//Crea el archivo de préstamos.txt (Realizada)
void validar_id(string&, const int, bool&);//Valida el Id del alumno o del libro en caso de este proyecto (Realizada)
void info_catalogo(bool&, string&, string&, string&, int&, int&);
void fecha(string &, int&);//Función que brinda la fecha en formato: dd/mm/yyyy
void info_prestamo(bool&, string&, string&, string&, string&, int&);//Recauda la información necesaria para agragar un nuevo préstamo

//Funciones de Booleanas
bool pregunta_si_no(bool&, string&);//Procesar Opción S/N (Realizada)
bool buscar_id(const string&);//Valida id del catálogo de libros (Realizada)
bool solo_digitos(const string&);//Valida que un string solo contenga dígitos (Realizada)
//Funciones de string
string limpiar(const string&);

int main()
{
    ///Muestra y lee los acentos de consola o desde el archivo .txt
    SetConsoleOutputCP(1252);
    SetConsoleCP(1252);
    ///Constantes
    ///Variables
    string id_libro = "";
    string titulo_libro = "";
    string autor_libro = "";
    string id_alunmo = "";
    string nombre_alumno = "";
    string fecha_prestamo = "";
    string mensaje = "";
    int tiempo = 0;
    int opc_usuario = 0;
    int copias_disponibles = 0;
    int total_registros = 0;
    bool salir_programa = false;
    vector<info_libro_catalogo> catalogo_libros;
    vector<info_prestamo_libro> registro_prestamos;

    ///Bucle mientras que la opción sea diferenta a 6 = Salir del programa
    do
    {
        ///Se toma la opción del usuario respecto al menú de opciones brindado
        try
        {
            //Mostramos el menú y recibimos la opción del usuario
            mostrar_menu(opc_usuario);

            ///Si el cin entra en fallo (cin.fail()); limpiamos buffer
            if(cin.fail())
            {
                throw runtime_error("Valor inválido, inténtelo de nuevo.");

            }//Fin de if
        }//Fin del try
        ///Se captura alguna error o exception
        catch(const exception& e)
        {
            system("CLS");//Limpia o borra pantalla.
            //Imprimimos el Error a notificar al usuario
            cerr << "Error: " << e.what();
            this_thread::sleep_for(chrono::seconds(1));//Detenemos el programa para mostrar el mensaje
        }//Fin try/catch

        ///Valoramos al opción elegida por el usuario y se destina a su caso respectivo
        switch(opc_usuario)
        {
        case 1:///Ingresar registro al catálogo.
            //Creamos el archivo de prestamos en caso de no existir
            crea_arch_catalogo();
            /*/Cargamos los libros disponibles para realizar préstamos
            cargar_catalogo(arch_catalogo);*/
            //Recopilamos la información necesaria para registrar un nuevo libro en el catálogo
            info_catalogo(salir_programa, id_libro, titulo_libro, autor_libro, copias_disponibles, tiempo);
            break;
        case 2:///Mostrar catálogo.
            system("CLS");//Limpia o borra pantalla.

            //Cargamos la información de los libros al vector
            catalogo_libros = cargar_catalogo(arch_catalogo);

            if(catalogo_libros.size() == 0)
            {
                mensaje = "\nNo se ha ingresado ningún libro al catálogo de la Biblioteca C++";
                tiempo = 3;
                mostrar_error(mensaje, tiempo);
                continue;
            }

            //Linea superior
            cout << left << setfill('=') << setw(132) << "=" << endl;// ancho pantalla 37 caracteres
            //Título
            cout << left << setfill(' ') << setw(132) << "                                                   CATÁLOGO DE LA BIBLIOTECA C++" << endl;// ancho pantalla 132 caracteres

            //Agregamos los encabezados
            //Linea separadora superior
            cout << left << setfill('=') << setw(132) << "=" << endl;
            //Nombres de los encabezados
            cout << left << setfill(' ')<< setw(6) << "  ID"
                 << "|" << setw(56) << "                         TÍTULO"
                 << "|" << setw(55) << "                         AUTOR"
                 << "|" << setw(11) << "DISPONIBLES"
                 << "|" << endl;
            //Linea separadora inferior
            cout << left << setfill('=') << setw(132) << "=" << endl;

            //Mostramos el catálogo disponible, Imprimimos la información del catálogo
            for(const auto& libro : catalogo_libros)
            {
                //Nombres de los encabezados
                cout << left << setfill(' ')<< setw(6) << libro.id_libro
                     << "|" << setw(56) << libro.titulo_libro
                     << "|" << setw(55) << libro.autor_libro
                     << "|" << setw(11) << libro.copias_disponibles
                     << "|" << endl;
            }//Fin del for

            //Linea inferior
            cout << left << setfill('=') << setw(132) << "=" << endl;// ancho pantalla 37 caracteres

            //Se imprime la cantidad total de registros
            cout << "\nTotal de registros: " << catalogo_libros.size() << endl;

            cout << "\n\nPresione ENTER para regresar al menú" << endl;
            system("PAUSE");//Presionar ENTER para regresar al menú
            break;
        case 3:///Registrar nuevo préstamo.
            //Creamos el archivo de prestamos en caso de no existir
            crea_arch_prestamos();
            info_prestamo(salir_programa, id_alunmo, id_libro, nombre_alumno, fecha_prestamo, tiempo);
            break;
        case 4:///Devolver libro.
            system("CLS");//Limpia o borra pantalla
            ///Cargamos el registro de préstamos para mostrarlos
            registro_prestamos = cargar_prestamos(arch_prestamos);

            ///En caso de estar vacíos o no exixtir el archivo regresamos al menú y avisamos al usuario
            if(registro_prestamos.size() == 0)
            {
                mensaje = "\nNo se ha ingresado ningún préstamo aún";
                tiempo = 3;
                mostrar_error(mensaje, tiempo);
                continue;
            }

            ///Llamamos a la función de devolver libros
            devolver_libro(salir_programa, id_alunmo, id_libro);
            break;
        case 5:///Ver historial de préstamos.

            system("CLS");//Limpia o borra pantalla.
            ///Cargamos el registro de préstamos para mostrarlos
            registro_prestamos = cargar_prestamos(arch_prestamos);

            ///En caso de estar vacíos o no exixtir el archivo regresamos al menú y avisamos al usuario
            if(registro_prestamos.size() == 0)
            {
                mensaje = "\nNo se ha ingresado ningún préstamo aún";
                tiempo = 3;
                mostrar_error(mensaje, tiempo);
                continue;
            }

            ///Repitase hasta que el usuario desee regresar al menú principal
            do
            {
                system("CLS");//Limpia o borra pantalla.

                ///Imprimimos el título de la pantalla
                //Linea superior
                cout << left << setfill('=') << setw(86) << "=" << endl;// ancho pantalla 86 caracteres
                //Título
                cout << left << setfill(' ') << setw(86) << "                                HISTORIAL DE PRÉSTAMOS" << endl;// ancho pantalla 86 caracteres

                ///Agregamos los encabezados
                //Linea separadora superior
                cout << left << setfill('=') << setw(86) << "=" << endl;
                //Nombres de los encabezados
                cout << left << setfill(' ')<< setw(9) << "ALUMNO ID"
                     << "|" << setw(55) << "                   NOMBRE DEL ALUMNO"
                     << "|" << setw(8) << "LIBRO ID"
                     << "|" << setw(10) << "  FECHA"
                     << "|" << endl;
                //Linea separadora inferior
                cout << left << setfill('=') << setw(86) << "=" << endl;

                ///Mostramos los préstamos realizados y que se encuentran registrados
                for(const auto& prestamo : registro_prestamos)
                {
                    cout << left << setfill(' ')<< setw(9) << prestamo.id_alumno
                         << "|" << setw(55) << prestamo.nombre_alumno
                         << "|" << setw(8) << prestamo.id_libro
                         << "|" << setw(10) << prestamo.fecha_prestamo
                         << "|" << endl;
                }//Fin del for

                //Linea inferior
                cout << left << setfill('=') << setw(86) << "=" << endl;// ancho pantalla 86 caracteres

                ///Se imprime la cantidad total de registros
                cout << "\nTotal de préstamos registrados: " << registro_prestamos.size() << endl;

                cout << "\n\nPresione ENTER para regresar al menú" << endl;
                system("PAUSE");//Presionar ENTER para regresar al menú
                mensaje = "¿Desea volver al menú principal?";
            }//Fin del Do
            while(!pregunta_si_no(salir_programa, mensaje));
            break;
        case 6:///Salir.
            mensaje = "¿Desea salir del programa?";
            if(pregunta_si_no(salir_programa, mensaje))
            {
                system("CLS");//Limpia o borra pantalla.
                //Linea superior
                cout << left << setfill('=') << setw(36) << "=" << endl;// ancho pantalla 37 caracteres
                //Título
                cout << left << setfill(' ') << setw(36) << "        SALIENDO DEL SISTEMA" << endl;// ancho pantalla 36 caracteres
                //Linea inferior
                cout << left << setfill('=') << setw(36) << "=" << endl;// ancho pantalla 37 caracteres

                //Opciones del menú
                cout << left << setfill(' ') << setw(36) << "\nGracias por usar el Sistema de Biblioteca C++" << endl;
                this_thread::sleep_for(chrono::seconds(1));//Detenemos el programa para mostrar el mensaje
                cout << left << setfill(' ') << setw(36) << "\n¡Hasta pronto!" << endl;
                this_thread::sleep_for(chrono::seconds(2));//Detenemos el programa para mostrar el mensaje
            }
            else
            {
                opc_usuario = 0;
            }

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
Se encarga de buscar los libros disponibles para poder manipularlos dentro del programa
permitiendo visualizarlo o bien editarlos
*/
vector<info_libro_catalogo> cargar_catalogo(const string& nombre_archivo)
{
    ifstream archivo(nombre_archivo);

    vector<info_libro_catalogo> libro_consultado;

    // Verifica si el archivo se abrió correctamente
    if (!archivo)
    {
        cerr << "Error al abrir el archivo para lectura." << endl;
        return libro_consultado;
    }

    string linea;
    int encabezado = 0;
    string copias_disponibles = "";

    // Leer cada línea del archivo y cargarla en el vector
    while (getline(archivo, linea))
    {
        //Mediante esta validación evitamos los encabezados del archivo catalogo.txt
        encabezado++;
        if(encabezado <= 3)
        {
            continue;
        }

        //creamos un objeto a partir de la linea
        istringstream iss(linea);
        //se crea un objeto de la estructura info libro
        info_libro_catalogo libro;

        // Se extraen los datos de la línea y se almacenan en el objeto libro
        //Se obtiene el ID
        getline(iss, libro.id_libro, '|');
        //Se obtiene el título del libro
        getline(iss, libro.titulo_libro, '|');
        //Se obtiene el autor del libro
        getline(iss, libro.autor_libro, '|');

        //Se obtiene las copias disponibles
        getline(iss, copias_disponibles, '|');
        //Convertimos de string a int mediante stoi()
        libro.copias_disponibles = stoi(copias_disponibles);


        //Se agregar la informacion al vector libro consultada
        libro_consultado.push_back(libro);
    }

    // Cierra el archivo
    archivo.close();
    //retornamos el vector con las libros consultadas
    return libro_consultado;
}

/*
Se encarga de buscar los préstamos que se han realizado
para poder manipularlos dentro del programa
*/
vector<info_prestamo_libro> cargar_prestamos(const string& nombre_archivo)
{
    ifstream archivo(nombre_archivo);

    vector<info_prestamo_libro> prestamo_consultado;

    // Verifica si el archivo se abrió correctamente
    if (!archivo)
    {
        cerr << "Error al abrir el archivo para lectura." << endl;
        return prestamo_consultado;
    }

    string linea;
    string str_id_libro = "";
    int encabezado = 0;

    // Leer cada línea del archivo y cargarla en el vector
    while (getline(archivo, linea))
    {
        //Mediante esta validación evitamos los encabezados del archivo prestamo.txt
        encabezado++;
        if(encabezado <= 3)
        {
            continue;
        }

        //creamos un objeto a partir de la linea
        istringstream iss(linea);
        //se crea un objeto de la estructura info pieza
        info_prestamo_libro prestamo;

        // Se extraen los datos de la línea y se almacenan el vector del préstamo
        //Se obtiene el ID del Alumno
        getline(iss, prestamo.id_alumno, '|');
        //Se obtiene el nombre del alumno
        getline(iss, prestamo.nombre_alumno, '|') ;

        //Se obtiene el id del libro
        getline(iss, str_id_libro, '|');
        //Limpiamos el id del libro de espacios en blanco inecesarios
        prestamo.id_libro = limpiar(str_id_libro);
        //Se obtiene la fecha en que se realizó el préstamo
        getline(iss, prestamo.fecha_prestamo, '|');

        //Se agregar la informacion al vector prestamo consultado
        prestamo_consultado.push_back(prestamo);
    }

    // Cierra el archivo
    archivo.close();
    //retornamos el vector con los prestamos cargados
    return prestamo_consultado;
}

/*
Muestra el error cometido en ciertos tipos de mensajes
*/
void mostrar_error(string& mensaje, int& tiempo)
{
    cout << '\a';
    cout << mensaje;
    this_thread::sleep_for(chrono::seconds(tiempo));
    cout << string(mensaje.length(), '\b') << string(mensaje.length(), ' ') << string(mensaje.length(), '\b');
}

/*
Valida que el título del libro no esté vacío, o que contenga solo espacios en blanco o
tabulaciones.
*/
void val_nomb_tit(string& str_dato, string& mensaje_error, string& mensa_dato)
{
    // Se asegura que el dato ingresado no esté vacío
    do
    {
        try
        {
            // Solicita el dato al usuario
            cout << mensa_dato;
            getline(cin, str_dato);

            // Verifica si el dato está vacío
            if (str_dato.empty())
            {
                throw runtime_error(mensaje_error);
            }
        }
        catch (const runtime_error& e)
        {
            // Muestra el mensaje de error
            cout << "\nError: " << e.what() << endl;

            // Pausa breve para que el usuario lea el mensaje
            this_thread::sleep_for(chrono::seconds(1));

            // Reinicia el dato
            str_dato = "";

            // Limpia la pantalla (solo en sistemas compatibles con system("CLS"))
            system("CLS");
        }
    }
    while (str_dato.empty());
}

/*
Esta se encarga de almacenar en el archivo catalogo.txt toda la infomación referente a los libros de la
biblioteca en caso de que se agrege un nuevo registro o se actualice toda la información de este
*/
void guardar_catalogo(const vector<info_libro_catalogo>& nuevo_libro, const int lectura_archivo)
{
    ofstream archivo;

    ///Validamos de que forma se abrirá el archivo
    switch(lectura_archivo)
    {
    case 1://agregar un nuevo registro al final: ios::app
        archivo.open(arch_catalogo, ios::app);
        break;
    case 2://Actualizar los registros del archivo: ios::trunc
        archivo.open(arch_catalogo, ios::trunc);
        break;
    default://Opción de apertura no válida
        system("CLS");//Se limpia pantalla
        cout << "Opción de apertura no válida" << endl;
        system("PAUSE");//Se detiene la pantalla
        break;
    }

    ///Agregamos los encabezados en caso de no estar
    crea_arch_catalogo();

    ///Si el archivo se creó o abrió correctamente
    if(archivo.is_open())
    {
        archivo.seekp(0, ios::end); //Nos mueve el puntero a la ultima ubicacion del catalogo.txt
        streampos pos_puntero = archivo.tellp();

        ///Guardamos la información del libro en el catalogo.txt
        for (const auto& libro : nuevo_libro)
        {
            //Se imprime la información del vector en el archivo de catálogo.txt según el formáto de los encabezados
            archivo << left << setfill(' ')<< setw(6) << libro.id_libro
                    << "|" << setw(56) << libro.titulo_libro
                    << "|" << setw(55) << libro.autor_libro
                    << "|" << setw(11) << libro.copias_disponibles
                    << "|" << endl;

            ///imprime unicamente cuando se agregan nuevos registros, no cuando se actualizan
            if(lectura_archivo == 1)
            {
                ///Se anuncia que se guardó correctamente la información en catálogo.txt
                cout << "Libro \"" + libro.titulo_libro + "\" (ID: " + libro.id_libro + ") registrado con éxito" << endl;
                this_thread::sleep_for(chrono::seconds(2));//Detenemos el programa para mostrar el mensaje
            }//fin if
        }

        /// Cierra el archivo
        archivo.close();
    }//Fin if
    ///En caso de que no se haya creado correctamente o abierto el archivo
    else
    {
        //En caso de que no se pueda crear el archivo
        cout << "Error: No se pudo crear el archivo" << endl;
        this_thread::sleep_for(chrono::seconds(1));//Detenemos el programa para mostrar el mensaje
        system("CLS");//Limpia pantalla
    }//Fin if/else
}

/*
Esta se encarga de almacenar en el archivo catalogo.txt toda la infomación referente a los libros de la
biblioteca
*/
void guardar_prestamos(const vector<info_prestamo_libro>& nuevo_prestamo, const int lectura_archivo)
{
    ofstream archivo;

    ///Validamos de que forma se abrirá el archivo
    switch(lectura_archivo)
    {
    case 1://agregar un nuevo registro al final: ios::app
        archivo.open(arch_prestamos, ios::app);
        break;
    case 2://Actualizar los registros del archivo: ios::trunc
        archivo.open(arch_prestamos, ios::trunc);
        break;
    default://Opción de apertura no válida
        system("CLS");//Se limpia pantalla
        cout << "Opción de apertura no válida" << endl;
        system("PAUSE");//Se detiene la pantalla
        break;
    }

    ///Agregamos los encabezados en caso de no estar
    crea_arch_prestamos();

    ///Si el archivo se creó o abrió correctamente
    if(archivo.is_open())
    {
        archivo.seekp(0, ios::end); //Nos mueve el puntero a la ultima ubicacion del catalogo.txt
        streampos pos_puntero = archivo.tellp();

        ///Guardamos la información del préstamo en el prestamo.txt
        for (const auto& prestamo : nuevo_prestamo)
        {
            //Se imprime la información del vector en el archivo de catálogo.txt según el formáto de los encabezados
            archivo << left << setfill(' ') << setw(9) << prestamo.id_alumno
                    << "|" << setw(55) << prestamo.nombre_alumno
                    << "|" << setw(8) << prestamo.id_libro
                    << "|" << setw(10) << prestamo.fecha_prestamo
                    << "|" << endl;
        }//Fin del for

        /// Cierra el archivo
        archivo.close();
    }//Fin del if
    ///En caso de que no se haya creado correctamente o abierto el archivo
    else
    {
        //En caso de que no se pueda crear el archivo
        cout << "Error: No se pudo crear el archivo" << endl;
        this_thread::sleep_for(chrono::seconds(1));//Detenemos el programa para mostrar el mensaje
        system("CLS");//Limpia pantalla
    }//Fin del if/else
}

/*
Muestra el Menú Principal y recibe la opción elegida
por el usuario
*/
void mostrar_menu(int &opc_usuario)
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

    ///Si el cin entra en fallo (cin.fail()); limpiamos buffer

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

}//Fin de la función menu_principal

/*
Función encargada de realizar una devolución de prestamo
de un libro, borra el registro de prestamos.txt y aumente el
disponible de libros en el catalogo.txt
*/
void devolver_libro(bool& bool_id_correcto, string& id_alumno, string& id_libro)
{
    ///Reinicializamos la variables de referencia
    bool_id_correcto = false;
    id_alumno = "";
    id_libro = "";
    ///Variables locales
    bool borrar_prestamo = false;
    string mensaje = "";
    ///Cargamos el catálogo de libros
    vector<info_libro_catalogo> catalogo_libros = cargar_catalogo(arch_catalogo);
    //Cargamos el registro de préstamos
    vector<info_prestamo_libro> registro_prestamos = cargar_prestamos(arch_prestamos);

    ///Repetimos en caso de que el usuario no desee regresar al menú principal
    do
    {
        ///Imprimimos el encabezado de la pantalla devolver préstamo
        system("CLS");//Limpia o borra pantalla.
        //Agregamos el título de la pantalla ancho = 72
        //Linea separadora superior
        cout << left << setfill('=') << setw(72) << "=" << endl;
        //Título de la pantalla
        cout << left << setfill(' ')<< setw(72) << "                           DEVOLVER LIBRO" << endl;//14 Caracteres
        //Linea separadora inferior
        cout << left << setfill('=') << setw(72) << "=" << endl;

        ///Solicitamo la información necesaria para la devolución del libro
        //Solicitamos y validamos el ID del alumno
        do
        {
            cout << left << setfill(' ') << "\nIngrese el ID de alumno (9 dígitos): ";
            validar_id(id_alumno, dig_id_alumno, bool_id_correcto);//Validamos que el id cumple con lo requrido

        }//Fin do
        while(!bool_id_correcto);//Fin del do/while

        //Solicitamos y validamos el ID del libro
        do
        {
            cout << left << setfill(' ') << "Ingrese el ID del libro (6 dígitos): ";
            validar_id(id_libro, dig_id_libro, bool_id_correcto);//Validamos que el id cumple con lo requrido

        }//Fin do
        while(!bool_id_correcto);//Fin del do/While

        ///Procedemos a la validación y existencia de lo solicitado en sus respectivos (archivos_nombre).txt
        //Buscamos y validamos si existe el id del alumno en el archivo prestamos.txt
        //Buscamos y validamos si existe el id del libro en el archivo prestamos.txt
        auto it_prestamo = find_if(registro_prestamos.begin(), registro_prestamos.end(),
                                   [&id_alumno, &id_libro](const info_prestamo_libro& prestamo)
        {
            return prestamo.id_alumno == id_alumno && prestamo.id_libro == id_libro;
        });//Fin del find_if()

        // Verificamos que el libro a devolver exista dentro del catálogo y para obtener su nombre según su ID
        auto it_libro = find_if(catalogo_libros.begin(), catalogo_libros.end(),
                                [&id_libro](const info_libro_catalogo& libro)
        {
            // Comparamos el ID ingresado con el ID de cada libro en el catálogo
            return libro.id_libro == id_libro;
        });//Fin del find_if()

        // Si se encuentra el préstamo, se muestra su información
        if(it_prestamo != registro_prestamos.end())
        {
            //Si se encuentra el libro se procede a mostrar la información completa
            if(it_libro != catalogo_libros.end())
            {
                //Mostamos el préstamo encontrado
                cout << "\nPréstamo encontrado:" << endl;
                cout << "Alumno        : " << limpiar((*it_prestamo).nombre_alumno) << " (ID: " + (*it_prestamo).id_alumno + ")" << endl;
                cout << "Libro         : " << limpiar((*it_libro).titulo_libro) << " (ID: " + (*it_prestamo).id_libro + ")" << endl;
                cout << "Fecha préstamo: " << (*it_prestamo).fecha_prestamo << endl;

                system("PAUSE");//Detenemos la pantalla hasta el ENTER

                ///Preguntamos al usuario si desea confirmar la devolución del libro
                mensaje = "¿Confirmar devolución?";
                if(pregunta_si_no(borrar_prestamo, mensaje))
                {
                    // Eliminamos el registro del préstamo del vector
                    registro_prestamos.erase(it_prestamo);

                    // Aquí puedes guardar el vector actualizado en el archivo prestamos.txt
                    guardar_prestamos(registro_prestamos, act_registros);

                    ///Aumentamos la cantidas disponible del libro para actualizarla en el archivo de catálogo.txt
                    (*it_libro).copias_disponibles++;

                    ///Guardamos el catálogo actualizado
                    guardar_catalogo(catalogo_libros, act_registros);

                    cout << "\nLibro " + limpiar((*it_libro).titulo_libro) + " devuelto con éxito." << endl;
                    cout << "\nCopias disponibles actualizadas: " << (*it_libro).copias_disponibles << endl;
                    this_thread::sleep_for(chrono::seconds(2));
                }//Fin del if
            }//Fin del if
            else
            {
                //Mostramos al usuario que no existe el libro dentro del catálogo.txt
                cout << "\nEl ID ingresado no corresponde a ningún libro en el catálogo." << endl;
                // Pausa breve para que el usuario lea el mensaje
                this_thread::sleep_for(chrono::seconds(2));
            }
        }//fin del if
        else
        {
            //Mostramos al usuario que no existe el libro dentro del catálogo.txt
            cout << "\nEl ID del alumno ingresado no coincide a ningún registro de préstamos." << endl;
            // Pausa breve para que el usuario lea el mensaje
            this_thread::sleep_for(chrono::seconds(2));
        }
        //Preguntamos al usuario si desea regresar al menú principa
        mensaje = "¿Desea regresar al menú principal?";
    }//fin del do
    while(!pregunta_si_no(bool_id_correcto, mensaje));//Fin del do/while
}

/*
Crea el archivo catálogo.txt y coloca los encabezados
*/
void crea_arch_catalogo()
{
    //Creamos el archivo de catálogo.txt
    ofstream archivo(arch_catalogo, ios::app | ios::binary);
    //Si el se creo correctamente
    if(archivo.is_open())
    {
        archivo.seekp(0, ios::end); //Nos mueve el puntero a la ultima ubicacion del catálogo.txt
        streampos pos_puntero = archivo.tellp();
        // Verifica si el archivo está vacío para agregar encabezados
        if (pos_puntero == 0)
        {
            //Agregamos los encabezados
            //Linea separadora superior
            archivo << left << setfill('=') << setw(132) << "=" << endl;
            //Nombres de los encabezados
            archivo << left << setfill(' ')<< setw(6) << "  ID"
                    << "|" << setw(56) << "                         TÍTULO"
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
        // Verifica si el archivo está vacío para agregar encabezados
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

/*
Esta función recibe un id y validad que cumpla con que sea dígitos y no
letras, además de que cumpla con la cantidad de dígitos requeridos,
no más, no menos, en caso de cumplir con lo establecido retorna en el
id_correcto = true
*/
void validar_id(string& id, const int cant_digitos, bool& id_correcto)
{
    id = ""; // Reinicia el valor del ID
    id_correcto = false; // Estado inicial: ID no válido

    try
    {
        //Recibimos el id
        cin >> id;

        ///Si el cin entra en fallo (cin.fail()); limpiamos buffer
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Verifica si ocurrió un error en la entrada
        if (cin.fail())
        {
            throw runtime_error("Entrada inválida: error de lectura.");
        }

        // Verifica si la cadena está vacía
        if (id.empty())
        {
            throw runtime_error("ID inválido: no se ingresó ningún valor.");
        }

        // Verifica que todos los caracteres sean dígitos
        if (!solo_digitos(id))
        {
            throw runtime_error("ID inválido: solo se permiten dígitos.");
        }

        // Verifica que la longitud del ID sea exactamente la requerida
        if (id.length() != cant_digitos)
        {
            throw runtime_error("ID inválido: debe contener exactamente " + to_string(cant_digitos) + " dígitos.");
        }

        // Si todas las validaciones pasan, el ID es correcto
        id_correcto = true;
    }
    catch (const runtime_error& e)
    {
        // Reinicia el valor del ID y su estado
        id = "";
        id_correcto = false;

        // Muestra el mensaje de error
        cout << "\nError: " << e.what() << endl;
        this_thread::sleep_for(chrono::seconds(5));
        system("CLS");
    }
}//Fin validar_cedula(string& id)

/*
Optiene del usuario toda la información necesaria para agragar un nuevo libro a la biblioteca de c++
*/
void info_catalogo(bool& volver_menu, string& id_libro, string& tit_libro, string& autor_libro, int& copias_dis, int& tiempo)
{
    //creamos un vector para almacenar la información de nuevos libros
    vector<info_libro_catalogo> nuevo_libro;
    string mensa_dato = "";//Mensaje del dato que se solicita al usuario
    string mensaje = "";//Mensaje de validar SÍ o NO
    string mensaje_error = "";//Mensaje de error
    tiempo = 0;
    bool id_correcto = false;//Estado de la comprobación del ID conrrespondiente (libro o estudiante)

    ///Repite hasta que el usuario decida regresar al menú principal
    do
    {

        system("CLS");//Limpia o borra pantalla.
        //Agregamos el título de la pantalla ancho = 39
        //Linea separadora superior
        cout << left << setfill('=') << setw(39) << "=" << endl;
        //Título de la pantalla
        cout << left << setfill(' ')<< setw(39) << "     INGRESAR REGISTRO AL CATÁLOGO" << endl;//29 Caracteres
        //Linea separadora inferior
        cout << left << setfill('=') << setw(39) << "=" << endl;

        //Creamos un nuevo libro de estructura ya definida
        info_libro_catalogo info_libro;

        ///Solicitamos y validamos los datos necesarios para ingresar un nuevo registro al catálogo
        //Validación del ID del libro
        do
        {
            cout << left << setfill(' ') << "\nIngrese el ID del libro (6 dígitos): ";
            validar_id(id_libro, dig_id_libro, id_correcto);//Validamos que el id cumple con lo requrido
            ///Si el cin entra en fallo (cin.fail()); limpiamos buffer

            //Busca el id en el arch_catalogo Catálogo.txt;
            if(buscar_id(id_libro))
            {
                mensaje_error = "El Id: " + id_libro + " ya fue registrado anteriormente.";
                mostrar_error(mensaje_error, tiempo);
                id_correcto = false;
            }//Fin if

        }//Fin do
        while(!id_correcto);

        //Agregamos el Id del libro a la estructura
        info_libro.id_libro = id_libro;

        //Validación del título
        mensaje_error = "Valor inválido: El título no puede estar vacío.";
        mensa_dato = "Ingrese título: ";
        val_nomb_tit(tit_libro, mensaje_error, mensa_dato);

        //Agregamos el título del libro a la estructura
        info_libro.titulo_libro = tit_libro;

        //Validación del autor
        mensaje_error = "Valor inválido: El autor no puede estar vacío.";
        mensa_dato = "Ingrese autor: ";
        val_nomb_tit(autor_libro, mensaje_error, mensa_dato);

        //Agregamos el autor del libro a la estructura
        info_libro.autor_libro = autor_libro;

        //Validación de cantidad de copia disponibles
        do
        {
            cout << left << setfill(' ') << "Ingrese el número de copias disponibles: ";
            try
            {
                cin >> copias_dis;

                if(cin.fail())//dato diferente a tipo int
                {
                    throw runtime_error("No se admiten letras, solo números");
                }
                else if(copias_dis < 0 || copias_dis > 9)
                {
                    throw runtime_error("El valor debe estar en un rango de 0 a 9");
                }
            }
            catch(const runtime_error& e)
            {
                //Manejamo el mensaje que se mostrará en caso de que se haga el error de usuario
                cout << "Error: "   << e.what() << endl;
                this_thread::sleep_for(chrono::seconds(1));//Detenemos el programa para mostrar el mensaje
                system("CLS");//Limpia pantalla
            }
        }
        while(cin.fail() || copias_dis < 0 || copias_dis > 9);

        //Agregamos las copias disponibles del libro a la estructura
        info_libro.copias_disponibles = copias_dis;

        ///Se agrega el libro al vector para su debido registro
        nuevo_libro.push_back(info_libro);

        system("CLS");//Borramos pantalla

        ///Imprimimos lo que se va a guardar en el catalogo.txt
        for (const auto& libro : nuevo_libro)
        {

            //Linea separadora superior
            cout << left << setfill('-') << setw(132) << "-" << endl;
            cout << left << setfill(' ') << "Id del libro: " << libro.id_libro << endl;
            cout << left << setfill(' ') << "Título del libro: " << libro.titulo_libro << endl;
            cout << left << setfill(' ') << "Autor del libro: " << libro.autor_libro << endl;
            cout << left << setfill(' ') << "Cantidad disponible: " << libro.copias_disponibles << endl;
            //Linea separadora inferior
            cout << left << setfill('-') << setw(132) << "-" << endl;
        }

        system("PAUSE");//Pausamos pantalla

        //Añadimos el mensaje de regresar al menú
        mensaje = "¿Desea regresar al menú principal?";
    }
    while(!pregunta_si_no(volver_menu, mensaje));//Fin del do/while

    ///Guardamos la información de los libros en el catalogo.txt
    guardar_catalogo(nuevo_libro, agre_registro);

}

/*
Esta función nos brinda una fecha, con la posibilidad de editarla si el usuario así lo decide
*/
void fecha(string& fecha, int& int_tiempo)
{
    ///Variables locales
    string mensaje = "";
    int_tiempo = 2;
    char modificar = ' ';
    bool si_no = false;

    ///Obtiene el tiempo actual en segundos
    time_t hora_actual = time(0);

    ///Convierte el tiempo actual a una estructura tm con la fecha local
    tm* tiempo = localtime(&hora_actual);//"tm" significa time

    //Arreglos de caracteres para almacenar la fecha formateadas
    char char_fecha[11];

    ///Formateamos la fecha usando la estructura de tiempo local
    strftime(char_fecha, sizeof(char_fecha), "%d/%m/%Y", tiempo);//Formateamos la fecha strftime(buffer[x], maxSiza, format, timeStruct)

    //Asigna los valores formateados a las variables de salida
    fecha = char_fecha;

    //Imprimimos la fecha
    cout << fecha << endl;

    system("PAUSE"); //Pausamos el programa al ENTER
    system("CLS"); //Borramos pantalla

    /// Preguntar si desea modificarla
    mensaje = "¿Desea modificar la fecha? (S/N): ";
    if(pregunta_si_no(si_no,mensaje))
    {
        string nueva_fecha = "";
        bool formato_valido = false;

        do
        {
            system("CLS"); //Limpiamos pantalla
            cout << "Ingrese la nueva fecha en formato (DD/MM/YYYY): ";
            //Recibimos la nueva fecha
            cin >> nueva_fecha;

            ///Si el cin entra en fallo (cin.fail()); limpiamos buffer
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            /// Validación básica de formato
            if (nueva_fecha.length() == 10 &&
                    nueva_fecha[2] == '/' &&
                    nueva_fecha[5] == '/')
            {
                //El formato es valido = true
                formato_valido = true;
                //Asignamos la nueva fecha a la fecha que se mostrará
                fecha = nueva_fecha;
            }
            else
            {
                //Asignamos el mensaje de error
                mensaje =  "Formato inválido. Intente de nuevo.";
                //Mostramos el error
                mostrar_error(mensaje, int_tiempo);
            }
        } //Repitase mientras formato valido = false
        while (!formato_valido);
    }
}

/*
Esta función reune del usuario los datos necesarios para agregar un nuevo préstamo al archivo prestamo.txt
*/
void info_prestamo(bool& volver_menu, string& id_alumno, string& id_libro, string& nomb_alumno, string& fecha_prest, int& tiempo)
{
    ///Cargamos los datos de los archivos a los vectores
    //creamos un vector para almacenar la información de nuevos libros
    vector<info_prestamo_libro> nuevo_prestamo;
    //creamos un vector para almacenar la información del catálogo de libros
    vector<info_libro_catalogo> catalogo_libros;
    //Pasamos la información al vector
    catalogo_libros = cargar_catalogo(arch_catalogo);
    string mensa_dato = "";//Mensaje del dato que se solicita al usuario
    string mensaje = "";//Mensaje de validar SÍ o NO
    string mensaje_error = "";//Mensaje de error
    bool id_correcto = false;//Estado de la comprobación del ID conrrespondiente (libro o estudiante)

    ///Bucle de regresar al menú principal
    do
    {
        system("CLS");//Limpia o borra pantalla.
        //Agregamos el título de la pantalla ancho = 39
        //Linea separadora superior
        cout << left << setfill('=') << setw(39) << "=" << endl;
        //Título de la pantalla
        cout << left << setfill(' ')<< setw(39) << "       REGISTRAR NUEVO PRÉSTAMO" << endl;//24 Caracteres
        //Linea separadora inferior
        cout << left << setfill('=') << setw(39) << "=" << endl;

        //Estructura del préstamo
        info_prestamo_libro informacion_prestamo;

        //Validación del ID del alumno
        do
        {
            cout << left << setfill(' ') << "\nIngrese el ID de alumno (9 dígitos): ";
            validar_id(id_alumno, dig_id_alumno, id_correcto);//Validamos que el id cumple con lo requrido

        }//Fin do
        while(!id_correcto);

        //Agregamos la información a la estructura
        informacion_prestamo.id_alumno = id_alumno;

        //Validación del nombre del alumno
        mensaje_error = "No se ingresó ningún valor.";
        mensa_dato = "Ingrese nombre del alumno: ";
        val_nomb_tit(nomb_alumno, mensaje_error, mensa_dato);

        //Agregamos la información a la estructura
        informacion_prestamo.nombre_alumno = nomb_alumno;

        //Validación del ID del libro
        do
        {
            cout << left << setfill(' ') << "Ingrese el ID del libro (6 dígitos): ";
            validar_id(id_libro, dig_id_libro, id_correcto);//Validamos que el id cumple con lo requrido

        }//Fin do
        while(!id_correcto);

        //Agregamos la información a la estructura
        informacion_prestamo.id_libro = id_libro;

        //Imprimimos fecha
        cout << "Ingrese fecha (DD/MM/YYYY): ";
        fecha(fecha_prest, tiempo);

        informacion_prestamo.fecha_prestamo = fecha_prest;

        // Verificamos que el libro solicitado exista dentro del catálogo
        // Utilizamos find_if para buscar el libro por su ID dentro del vector catalogo_libros
        auto iterador = find_if(catalogo_libros.begin(), catalogo_libros.end(),
                                [&id_libro](const info_libro_catalogo& libro)
        {
            // Comparamos el ID ingresado con el ID de cada libro en el catálogo
            return libro.id_libro == id_libro;
        });

        // Si se encuentra el libro, se muestra su información
        if (iterador != catalogo_libros.end())
        {
            //Se valida que hayan libros disponibles para prestar
            if((*iterador).copias_disponibles > 0)
            {
                // Accedemos al libro encontrado mediante el iterador
                cout << "\nLibro encontrado:" << endl;
                // Se imprime el título del libro
                cout << "Título     : " << (*iterador).titulo_libro << endl;
                // Se imprime la cantidad de copias disponibles
                cout << "Disponibles: " << (*iterador).copias_disponibles << endl;

                // Pausa breve para que el usuario lea el mensaje
                this_thread::sleep_for(chrono::seconds(2));

                //Preguntamos al usuario si desea guardar el nuevo préstamo
                mensaje = "¿Confirmar préstamo?";
                if(pregunta_si_no(volver_menu, mensaje))
                {
                    ///Se agrega el prestamo al vector para su debido registro
                    nuevo_prestamo.push_back(informacion_prestamo);

                    ///Procedemos a guardar la información del préstamo a registrar
                    guardar_prestamos(nuevo_prestamo, agre_registro);

                    //Reducimos la cantida disponible del libro para actualizarla en el archivo de catálogo.txt
                    (*iterador).copias_disponibles--;

                    cout << "Préstamo registrado: " << endl;

                    ///Imprimimos lo que se va a guardar en el catalogo.txt
                    for (const auto& prestamo : nuevo_prestamo)
                    {
                        //Imprimimos la información del préstamo que se registró
                        cout << left << setfill(' ') << "Alumno ID: " << prestamo.id_alumno << endl;
                        cout << left << setfill(' ') << "Libro ID : " << prestamo.id_libro << endl;
                        cout << left << setfill(' ') << "Fecha    : " << prestamo.fecha_prestamo << endl;
                    }//Fin for

                    ///Informamos al usuarios cuantos libros restan disponibles de ID en la Biblioteca C++
                    cout << "Ahora quedan " << (*iterador).copias_disponibles << " copias disponibles." << endl;

                    //Actualizamos el catálogo.txt de la Biblioteca C++
                    guardar_catalogo(catalogo_libros, act_registros);

                    ///Limpiamos el vector en caso de que deseen ingresar otro préstamo
                    nuevo_prestamo.clear();
                }//Fin if
            }//Fin if
            else
            {

                string mensaje = "No hay copias de este libro en este momento. ¿Desea solicitar otro libro?";
                if (!pregunta_si_no(volver_menu, mensaje))
                {
                    // Si el usuario no desea consultar otro libro, se regresa al menú principal
                    volver_menu = true;
                }//Fin if
            }//Fin else
        }//Fin if
        else
        {
            // Si no se encuentra el libro, se muestra un mensaje de advertencia
            cout << "\nEl ID ingresado no corresponde a ningún libro en el catálogo." << endl;
            // Pausa breve para que el usuario lea el mensaje
            this_thread::sleep_for(chrono::seconds(1));
            // Se pregunta al usuario si desea consultar otro libro
            string mensaje = "¿Desea consultar otro libro?";
            if (!pregunta_si_no(volver_menu, mensaje))
            {
                // Si el usuario no desea consultar otro libro, se regresa al menú principal
                volver_menu = true;
            }//Fin if
        }//Fin else

        // Pausa breve para que el usuario lea el mensaje
        this_thread::sleep_for(chrono::seconds(2));

        //Añadimos el mensaje de regresar al menú
        mensaje = "¿Desea regresar al menú principal?";
    }//Fin del Do
    while(!pregunta_si_no(volver_menu, mensaje));
}

/*
Valida si el usuario desea regresar al menú principal
*/
bool pregunta_si_no(bool& salir_programa, string& mensaje)
{
    char opc_usuario;

    ///Do/While que repite la pregunta mientra el usuario digite un valor inválido
    do
    {
        system("CLS"); //Limpiamos pantalla
        //Realizamos la pregunta de respuesta "Sí" o "No"
        cout << "\n" + mensaje + " Digite 'S' para sí o 'N' para no." << endl;
        cout << "R/: ";

        ///Validamos la respuesta del usuario media Try/Catch
        try
        {
            //Recibimos la opción del usuario
            cin >> opc_usuario;
            ///Si el cin entra en fallo (cin.fail()); limpiamos buffer
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (cin.fail())
            {
                throw runtime_error("Entrada inválida: Digite 'S' para sí o 'N' para no.");
            }

            //Convertimos lo ingresado por el usuario a mayúscula por cualquier duda
            opc_usuario = toupper(opc_usuario);

            switch(opc_usuario)
            {
            case 'S':
                //Responde sí a la pregunta realizada.
                return true;
                salir_programa = true;
                break;
            case 'N':
                //Responde no a la pregunta realizada.
                return false;
                salir_programa = false;
                break;
            default://Opción por defautl
                throw runtime_error("Entrada inválida: Digite 'S' para sí o 'N' para no.");
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

/*Busca el id dentro del archivo catálogo.txt
y valida que no se repita la información.

- Es true cuando Sí encuentra un Id en el archivo catálogo.txt
- Es false cuando No encuentra un Id en el archivo catálogo.txt
*/
bool buscar_id(const string& id_digitado)
{

    //Variables
    string linea_archivo;//obtiene la linea dentro el archivo catálogo.txt
    string id_archivo;//obtiene el id proveniente del archivo catálogo.txt

    //Leemos el archivo de catálogo.txt
    ifstream archivo(arch_catalogo);
    //Validamos que exista y se pueda abrir
    if (!archivo.is_open())
    {
        //En caso de que no se pueda abrir
        cerr << "Error: No se pudo abrir el archivo.\n";
        /*Como no se puede abrir, no se puede comparar por
        lo tanto es "false"*/
        return false;
    }

    /*Mientras haya lineas a escanear en "archivo",
    adquierase la linea y guardece en "linea_archivo*/
    while (getline(archivo, linea_archivo))
    {
        /*Creamos un StringStream para que la linea
        obtenida del archivo catálogo.txt, pueda ser
        tratada como una cadena de caracteres (char)*/
        stringstream st_stream(linea_archivo);

        /*Se lee hasta el primer '|' del archivo catálogo.txt
        y se almacena en "id_archivo"*/
        if (getline(st_stream, id_archivo, '|'))
        {
            /*Compara el id digitada por el usuario
            a la que se obtiene del archivo catálogo.txt*/
            if (id_digitado == id_archivo)
            {
                /*Regresa que si existe el id en el
                archivo catálogo.txt osea es igual a "true"*/
                return true;
            }
        }
    }

    /*Devuelve "false" en caso de no existir la cédula dentro del
    archivo catálogo.txt*/
    return false;
}

/*
Función que valida que un string contenga solo números
*/
bool solo_digitos(const string& texto)
{
    //Para cada 'c' dentro de 'texto
    for (char c : texto)
    {
        //Si alguno 'c' es caracter entonce
        if (!isdigit(c))
        {
            //Retornamos falso, no cumple que solo dígitos
            return false;
        }
    }
    //Cumple que solo contiene dígitos
    return true;
}



/*
Función que nos permite limpiar un string de espacios no deseados
*/
string limpiar(const string& str_dato)
{
    // Busca la primera posición que no sea espacio
    size_t inicio = str_dato.find_first_not_of(" \t\r\n");

    // Busca la última posición que no sea espacio
    size_t fin = str_dato.find_last_not_of(" \t\r\n");

    // Si no se encontró ningún carácter válido, retorna cadena vacía
    if (inicio == string::npos) return "";

    // Retorna la subcadena limpia (sin espacios externos)
    return str_dato.substr(inicio, fin - inicio + 1);
}

//
