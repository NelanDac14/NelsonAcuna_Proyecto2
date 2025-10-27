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
struct info_libro_catalogo
{
    string id_libro; //Campo num�rico de m�ximo 6 d�gitos, no letras, no espacios en blanco
    string titulo_libro; //Nombre del libro debe permitir una o m�s palabras
    string autor_libro; //Nombre del autor debe permitir una o m�s palabras
    int copias_disponibles;//No permite n�meros negativos y debe estar en un rango de 1-9 m�ximo, no letras, no espacios en blanco
};

struct info_prestamo_libro
{
    string id_alunmo; //Valor num�rico de m�nimo/m�ximo 9 d�gitos, no letras, no espacios en blanco
    int id_libro; //Campo num�rico de m�ximo 6 d�gitos, no letras, no espacios en blanco
    string nombre_alumno;//Nombre y apellidos, validar que no permita espacios en blanco
    string fecha_prestamo;//Debe generarse autom�ticamente y con posibilidad de modificarlo, Formato: DD/MM/YYYY

};

//Constantes de uso global
const string arch_catalogo = "catalogo.txt";
const string arch_prestamos = "prestamos.txt";
const int dig_id_libro = 6;
const int dig_id_alumno = 9;

//Funciones de vector
vector<info_libro_catalogo> cargar_catalogo(const string&);//Cargar cat�logo disponible para mostrarlo

//Funciones void
void mostrar_error(string&);//Muestra un error y produce un sonido (Realizada)
void val_nomb_tit(string&, string&, string&);//Valida que el dato de nombre o t�tulo no se encuentre vac�o (Realizada)
void guardar_catalogo(const vector<info_libro_catalogo>&);//Guardar cambios en el cat�logo (Realizada)
void cargar_prestamos();//Cargar lista de pr�stamos
void guardar_prestamos();//Guardar nuevo pr�stamo
void mostrar_menu(int &);//Muestra el men� principal (Realizada)
void ing_reg_catalogo();//ingresar_registro_catalogo
void reg_nue_prestamo();//registrar_nuevo_prestamo
void devolver_libro();//Realizar la devoluci�n de libros a la biblioteca
void historial_prestamos();//Ver el historial de pr�stamos
void mostrar_catalogo(const string);
void crea_arch_catalogo();//Crea el archivo de cat�logo.txt (Realizada)
void crea_arch_prestamos();//Crea el archivo de pr�stamos.txt (Realizada)
void validar_id(string&, const int, bool&);//Valida el Id del alumno o del libro en caso de este proyecto (Realizada)
void info_catalogo(bool&, string&, string&, string&, int&);

//Funciones de Booleanas
bool regresar_menu(bool&, string&);//Procesar Opci�n S/N (Realizada)
bool buscar_id(const string&);//Valida id del cat�logo de libros (Realizada)
bool solo_digitos(const string&);//Valida que un string solo contenga d�gitos (Realizada)

int main()
{
    //Muestra y lee los acentos de consola o desde el archivo .txt
    SetConsoleOutputCP(1252);
    SetConsoleCP(1252);
    //Constantes
    //Variables
    string id_libro = "";
    string titulo_libro = "";
    string autor_libro = "";
    int copias_disponibles = 0;
    string id_alunmo = "";
    string nombre_alumno = "";
    string fecha_prestamo = "";
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
                // Limpieza previa del b�fer para evitar entradas residuales
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
            info_catalogo(salir_programa, id_libro, titulo_libro, autor_libro, copias_disponibles);
            break;
        case 2://Mostrar cat�logo.
                system("CLS");//Limpia o borra pantalla.
                //Linea superior
                cout << left << setfill('=') << setw(132) << "=" << endl;// ancho pantalla 37 caracteres
                //T�tulo
                cout << left << setfill(' ') << setw(132) << "                                                   CAT�LOGO DE LA BIBLIOTECA C++" << endl;// ancho pantalla 36 caracteres

                //Mostramos el cat�logo disponible
                mostrar_catalogo(arch_catalogo);

                cout << "\n\nPresione ENTER para regresar al men�" << endl;
                system("PAUSE");//Presionar ENTER para regresar al men�
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
Muestra el error cometido en ciertos tipos de mensajes
*/
void mostrar_error(string& mensaje)
{
    cout << '\a';
    cout << mensaje;
    this_thread::sleep_for(chrono::seconds(1));
    cout << string(mensaje.length(), '\b') << string(mensaje.length(), ' ') << string(mensaje.length(), '\b');
}

/*
Valida que el t�tulo del libro no est� vac�o, o que contenga solo espacios en blanco o
tabulaciones.
*/
void val_nomb_tit(string& str_dato, string& mensaje_error, string& mensa_dato)
{
    // Se asegura que el dato ingresado no est� vac�o
    do
    {
        try
        {
            // Solicita el dato al usuario
            cout << mensa_dato;
            getline(cin, str_dato);

            // Verifica si el dato est� vac�o
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

    // Limpieza previa del b�fer para evitar entradas residuales
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
        //Realizamos la pregunta de respuesta "S�" o "No"
        cout << "\n" + mensaje + " Digite 'S' para s� o 'N' para no." << endl;
        cout << "R/: ";
        //Validamos la respuesta del usuario media Try/Catch
        try
        {
            //Recibimos la opci�n del usuario
            cin >> opc_usuario;
            // Limpieza previa del b�fer para evitar entradas residuales
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            //Convertimos lo ingresado por el usuario a may�scula por cualquier duda
            opc_usuario = toupper(opc_usuario);
            if (cin.fail())
            {
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

            // Limpieza previa del b�fer para evitar entradas residuales
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

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

/*
Esta funci�n recibe un id y validad que cumpla con que sea d�gitos y no
letras, adem�s de que cumpla con la cantidad de d�gitos requeridos,
no m�s, no menos, en caso de cumplir con lo establecido retorna en el
id_correcto = true
*/
void validar_id(string& id, const int cant_digitos, bool& id_correcto)
{
    id = ""; // Reinicia el valor del ID
    id_correcto = false; // Estado inicial: ID no v�lido

    try
    {
        //Recibimos el id
        cin >> id;
        // Limpieza previa del b�fer para evitar entradas residuales
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Verifica si ocurri� un error en la entrada
        if (cin.fail())
        {
            throw runtime_error("Entrada inv�lida: error de lectura.");
        }

        // Verifica si la cadena est� vac�a
        if (id.empty())
        {
            throw runtime_error("ID inv�lido: no se ingres� ning�n valor.");
        }

        // Verifica que todos los caracteres sean d�gitos
        if (!solo_digitos(id))
        {
            throw runtime_error("ID inv�lido: solo se permiten d�gitos.");
        }

        // Verifica que la longitud del ID sea exactamente la requerida
        if (id.length() != cant_digitos)
        {
            throw runtime_error("ID inv�lido: debe contener exactamente " + to_string(cant_digitos) + " d�gitos.");
        }

        // Si todas las validaciones pasan, el ID es correcto
        id_correcto = true;
    }
    catch (const runtime_error& e)
    {
        // Restablece el estado del flujo de entrada
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Reinicia el valor del ID y su estado
        id = "";
        id_correcto = false;

        // Muestra el mensaje de error
        cout << "\nError: " << e.what() << endl;
        this_thread::sleep_for(chrono::seconds(1));
        system("CLS");
    }
}//Fin validar_cedula(string& id)

/*
Optiene del usuario toda la informaci�n necesaria para agragar un nuevo libro a la biblioteca de c++
*/
void info_catalogo(bool& volver_menu, string& id_libro, string& tit_libro, string& autor_libro, int& copias_dis)
{
    //creamos un vector para almacenar la informaci�n de nuevos libros
    vector<info_libro_catalogo> nuevo_libro;
    string mensa_dato;//Mensaje del dato que se solicita al usuario
    string mensaje;//Mensaje de validar S� o NO
    string mensaje_error;//Mensaje de error
    bool id_correcto = false;//Estado de la comprobaci�n del ID conrrespondiente (libro o estudiante)

    //Repite hasta que el usuario decida regresar al men� principal
    do
    {
        system("CLS");//Limpia o borra pantalla.
        //Agregamos el t�tulo de la pantalla ancho = 39
        //Linea separadora superior
        cout << left << setfill('=') << setw(39) << "=" << endl;
        //T�tulo de la pantalla
        cout << left << setfill(' ')<< setw(39) << "     INGRESAR REGISTRO AL CAT�LOGO" << endl;//29 Caracteres
        //Linea separadora inferior
        cout << left << setfill('=') << setw(39) << "=" << endl;

        //Creamos un nuevo libro de estructura ya definida
        info_libro_catalogo info_libro;

        //Validaci�n del ID del libro
        do
        {
            cout << left << setfill(' ') << "\nIngrese el ID del libro (6 d�gitos): ";
            validar_id(id_libro, dig_id_libro, id_correcto);//Validamos que el id cumple con lo requrido

            //Busca el id en el arch_catalogo Cat�logo.txt;
            if(buscar_id(id_libro))
            {
                mensaje_error = "El Id: " + id_libro + " ya fue registrado anteriormente.";
                mostrar_error(mensaje_error);
                id_correcto = false;
            }//Fin if

        }//Fin do
        while(!id_correcto);

        //Agregamos el Id del libro a la estructura
        info_libro.id_libro = id_libro;

        //Validaci�n del t�tulo
        mensaje_error = "Valor inv�lido: El t�tulo no puede estar vac�o.";
        mensa_dato = "Ingrese t�tulo: ";
        val_nomb_tit(tit_libro, mensaje_error, mensa_dato);

        //Agregamos el t�tulo del libro a la estructura
        info_libro.titulo_libro = tit_libro;

        //Validaci�n del autor
        mensaje_error = "Valor inv�lido: El autor no puede estar vac�o.";
        mensa_dato = "Ingrese autor: ";
        val_nomb_tit(autor_libro, mensaje_error, mensa_dato);

        //Agregamos el autor del libro a la estructura
        info_libro.autor_libro = autor_libro;

        //Validaci�n de cantidad de copia disponibles
        do
        {
            cout << left << setfill(' ') << "Ingrese el n�mero de copias disponibles: ";
            try
            {
                cin >> copias_dis;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if(cin.fail())//dato diferente a tipo int
                {
                    // Limpieza previa del b�fer para evitar entradas residuales
                    cin.clear();
                    throw runtime_error("No se admiten letras, solo n�meros");
                }
                else if(copias_dis < 0 || copias_dis > 9)
                {
                    throw runtime_error("El valor debe estar en un rango de 0 a 9");
                }
            }
            catch(const runtime_error& e)
            {
                //Manejamo el mensaje que se mostrar� en caso de que se haga el error de usuario
                cout << "Error: "   << e.what() << endl;
                this_thread::sleep_for(chrono::seconds(1));//Detenemos el programa para mostrar el mensaje
                system("CLS");//Limpia pantalla
            }
        }
        while(cin.fail() || copias_dis < 0 || copias_dis > 9);

        //Agregamos las copias disponibles del libro a la estructura
        info_libro.copias_disponibles = copias_dis;

        //Se agrega el libro al vector para su debido registro
        nuevo_libro.push_back(info_libro);

        //Imprimimos lo que se va a guardar en el catalogo.txt
        for (const auto& libro : nuevo_libro)
        {

            //Linea separadora superior
            cout << left << setfill('-') << setw(132) << "-" << endl;
            cout << left << setfill(' ') << "Id del libro: " << libro.id_libro << endl;
            cout << left << setfill(' ') << "T�tulo del libro: " << libro.titulo_libro << endl;
            cout << left << setfill(' ') << "Autor del libro: " << libro.autor_libro << endl;
            cout << left << setfill(' ') << "Cantidad disponible: " << libro.copias_disponibles << endl;
            //Linea separadora inferior
            cout << left << setfill('-') << setw(132) << "-" << endl;
        }

        //A�adimos el mensaje de regresar al men�
        mensaje = "�Desea regresar al men� principal?";
    }
    while(!regresar_menu(volver_menu, mensaje));

    //Guardamos la informaci�n de los libros en el cat�logo.txt
    guardar_catalogo(nuevo_libro);

}

/*
Esta se encarga de almacenar en el archivo catalogo.txt toda la infomaci�n referente a los libros de la
biblioteca
*/
void guardar_catalogo(const vector<info_libro_catalogo>& nuevo_libro)
{
    {
        //Creamos o abrimos el archivo catalogo
        ofstream archivo(arch_catalogo, ios::app);
        //Si el se cre� o abri� correctamente
        if(archivo.is_open())
        {
            archivo.seekp(0, ios::end); //Nos mueve el puntero a la ultima ubicacion del catalogo.txt
            streampos pos_puntero = archivo.tellp();

            //Guardamos la informaci�n del estudiante en el catalogo.txt
            for (const auto& libro : nuevo_libro)
            {
                //Se imprime la informaci�n del vector en el archivo de cat�logo.txt seg�n el form�to de los encabezados
                archivo << left << setfill(' ')<< setw(6) << libro.id_libro
                        << "|" << setw(56) << libro.titulo_libro
                        << "|" << setw(55) << libro.autor_libro
                        << "|" << setw(11) << libro.copias_disponibles
                        << "|" << endl;
                //Se anuncia que se guard� correctamente la informaci�n en cat�logo.txt
                cout << "Libro \"" + libro.titulo_libro + "\" (ID: " + libro.id_libro + ") registrado con �xito" << endl;
            }

            this_thread::sleep_for(chrono::seconds(2));//Detenemos el programa para mostrar el mensaje
            system("CLS");//Limpia pantalla
            // Cierra el archivo
            archivo.close();
        }
        else
        {
            //En caso de que no se pueda crear el archivo
            cout << "Error: No se pudo crear el archivo" << endl;
            this_thread::sleep_for(chrono::seconds(1));//Detenemos el programa para mostrar el mensaje
            system("CLS");//Limpia pantalla
        }
    }
}

/*Busca el id dentro del archivo cat�logo.txt
y valida que no se repita la informaci�n.

- Es true cuando S� encuentra un Id en el archivo cat�logo.txt
- Es false cuando No encuentra un Id en el archivo cat�logo.txt
*/
bool buscar_id(const string& id_digitado)
{

    //Variables
    string linea_archivo;//obtiene la linea dentro el archivo cat�logo.txt
    string id_archivo;//obtiene el id proveniente del archivo cat�logo.txt

    //Leemos el archivo de cat�logo.txt
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
        obtenida del archivo cat�logo.txt, pueda ser
        tratada como una cadena de caracteres (char)*/
        stringstream st_stream(linea_archivo);

        /*Se lee hasta el primer '|' del archivo cat�logo.txt
        y se almacena en "id_archivo"*/
        if (getline(st_stream, id_archivo, '|'))
        {
            /*Compara el id digitada por el usuario
            a la que se obtiene del archivo cat�logo.txt*/
            if (id_digitado == id_archivo)
            {
                /*Regresa que si existe el id en el
                archivo cat�logo.txt osea es igual a "true"*/
                return true;
            }
        }
    }

    /*Devuelve "false" en caso de no existir la c�dula dentro del
    archivo cat�logo.txt*/
    return false;
}

/*
Se encarga de buscar los libros disponibles para poder manipularlos dentro del programa
permitiendo visualizarlo o bien
*/
vector<info_libro_catalogo> cargar_catalogo(const string& nombre_archivo)
{
    ifstream archivo(nombre_archivo);

    vector<info_libro_catalogo> libro_consultado;

    // Verifica si el archivo se abri� correctamente
    if (!archivo)
    {
        cerr << "Error al abrir el archivo para lectura." << endl;
        return libro_consultado;
    }

    string linea;

    // Leer cada l�nea del archivo y cargarla en el vector
    while (getline(archivo, linea))
    {
        //creamos un objeto a partir de la linea
        istringstream iss(linea);
        //se crea un objeto de la estructura info pieza
        info_libro_catalogo libro;

        // Se extraen los datos de la l�nea y se almacenan en el objeto pieza
        //Se obtiene el ID
        getline(iss, libro.id_libro, ' ');
        iss.ignore(); // Ignorar el espacio despu�s del n�mero
        //Se obtiene el t�tulo del libro
        getline(iss, libro.titulo_libro, '|') ;
        //Se obtiene el autor del libro
        iss >> libro.autor_libro;
        iss.ignore(std::numeric_limits<std::streamsize>::max(), '|'); // Ignorar el espacio despu�s del n�mero
        //Se obtiene la cantidad de libros disponibles
        iss >> libro.copias_disponibles;
        iss.ignore(std::numeric_limits<std::streamsize>::max(), '|'); // Ignorar el espacio despu�s del n�mero

        //Se agregar la informacion al vector pieza consultada
        libro_consultado.push_back(libro);
    }

    // Cierra el archivo
    archivo.close();
    //retornamos el vector con las piezas consultadas
    return libro_consultado;
}

//Mostrar Cat�logo de libros
void mostrar_catalogo(const string nombre_archivo)
{
    int cant_registros = 0;

    ifstream archivo(nombre_archivo);

    // Verifica si el archivo se abri� correctamente
    if (!archivo)
    {
        cerr << "Error al abrir el archivo para lectura." << endl;
        return;
    }

    string linea;
    // Lee y muestra cada l�nea del archivo
    while (getline(archivo, linea))
    {
        cout << linea << endl;
        cant_registros++;
    }

    // Cierra el archivo
    archivo.close();

    //Linea inferior
    cout << left << setfill('=') << setw(132) << "=" << endl;// ancho pantalla 37 caracteres
    //Imprimimos la cantidad de registros dentro del archivo cat�logo.txt
    cout << "\nTotal del registros: " << cant_registros - 3 << endl;
} //mostrar_catalogo()

/*
Funci�n que valida que un string contenga solo n�meros
*/
bool solo_digitos(const string& texto)
{
    //Para cada 'c' dentro de 'texto
    for (char c : texto)
    {
        //Si alguno 'c' es caracter entonce
        if (!isdigit(c))
        {
            //Retornamos falso, no cumple que solo d�gitos
            return false;
        }
    }
    //Cumple que solo contiene d�gitos
    return true;
}

//
