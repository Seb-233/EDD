/*
 * <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
 *  Proyecto Estructuras de datos entrega 0 y 1
 *  Autores: 
 *  Juan Manuel Lopez
 *  Johan Sebastian mendez 
 *  Sebastian Almanza
 *  David Leon
 *  Fecha: Septiembre 2024
 *
 *  Descripcion: 
 *  Este programa interactivo permite gestionar objetos 3D simulados,
 *  representados por vértices y caras. A través de comandos en la consola, 
 *  el usuario puede cargar, listar y modificar estos objetos,
 *  así como realizar operaciones como generar cajas envolventes o encontrar vértices cercanos.
 * <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
 */

#include <iostream>   
#include <string.h>   
#include <string>     
#include <ctype.h>    // Para funciones que manipulan caracteres (como tolower)
#include <vector>     // Para el uso del contenedor vector
#include <sstream>    // Para convertir cadenas a flujos, útil para dividir texto
#include <fstream>    // Para manejar la lectura y escritura de archivos
#include <limits>
#include <algorithm>


using namespace std; 

// Estas estructuras son donde se guardarán los vértices y las caras de los objetos 3D
///////////////////////////////////////////////////////////
struct Vertice { // Estructura que representa un vértice de un objeto 3D
    float px, py, pz; // Coordenadas del vértice en los ejes X, Y, Z
};

struct Cara { // Estructura que representa una cara de un objeto 3D
    vector<int> indicesVertices; // Índices de los vértices que forman la cara
};

struct Malla { // Estructura que representa un objeto 3D con nombre, vértices y caras
    string nombre;
    vector<Vertice> vertices; // Lista de vértices del objeto
    vector<Cara> caras;       // Lista de caras del objeto
};
///////////////////////////////////////////////////////////


// Función para convertir una cadena de texto a minúsculas
string convertirMinusculas(string cadena) {
    for (int i = 0; i < cadena.length(); i++) {
        cadena[i] = tolower(cadena[i]); // Convierte cada carácter a minúsculas
    }
    return cadena;
}

// Función que muestra un menú con los comandos disponibles en el programa
void MostrarAyudaGeneral() {
    cout << "Lista de comandos disponibles:" << endl;
    cout << "  cargar nombre_archivo            - Carga un archivo de objeto 3D en memoria." << endl;
    cout << "  listado                          - Lista todos los objetos cargados en memoria." << endl;
    cout << "  envolvente nombre_objeto          - Genera la caja envolvente de un objeto." << endl;
    cout << "  envolvente                        - Genera la caja envolvente de todos los objetos en memoria." << endl;
    cout << "  descargar nombre_objeto           - Elimina un objeto de la memoria." << endl;
    cout << "  guardar nombre_objeto nombre_archivo - Guarda la información del objeto en un archivo." << endl;
    cout << "  v_cercano px py pz nombre_objeto  - Encuentra el vértice más cercano al punto (px, py, pz) en el objeto." << endl;
    cout << "  v_cercano px py pz               - Encuentra el vértice más cercano al punto (px, py, pz) en todos los objetos." << endl;
    cout << "  v_cercanos_caja nombre_objeto     - Encuentra los vértices más cercanos a las esquinas de la caja envolvente del objeto." << endl;
    cout << "  ruta_corta i1 i2 nombre_objeto    - Encuentra la ruta más corta entre dos vértices en el objeto." << endl;
    cout << "  ruta_corta_centro i1 nombre_objeto- Encuentra la ruta más corta entre un vértice y el centro del objeto." << endl;
    cout << "  salir                             - Termina la ejecución del programa." << endl;
}

// Función que divide una línea de comando en palabras y las devuelve en un vector
vector<string> dividirComando(const string& linea) {
    vector<string> resultado;
    stringstream ss(linea); // Convierte la línea a un stream para procesar palabra por palabra
    string palabra;
    while (ss >> palabra) { // Extrae cada palabra y la almacena en el vector resultado
        resultado.push_back(palabra);
    }
    return resultado;
}

// Función para leer una malla (objeto 3D) desde un archivo
Malla LecturaMallas(const string& argumento1) {
    Malla malla;
    ifstream archivo(argumento1); // Abre el archivo
    if (!archivo.is_open()) { // Verifica si el archivo se abrió correctamente
        cout << "Error: No se pudo abrir el archivo " << argumento1 << endl;
        return malla;
    }

    cout << "Leyendo el archivo: " << argumento1 << endl;

    string linea;
    int numVertices = 0;


    // Leer el nombre de la malla
    getline(archivo, malla.nombre);
    cout << "Nombre de la malla: " << malla.nombre << endl;

    // Leer la cantidad de vértices
    archivo >> numVertices;
    cout << "Cantidad de vértices: " << numVertices << endl;

    // Leer y almacenar los vértices
    for (int i = 0; i < numVertices; ++i) {
        Vertice v;
        archivo >> v.px >> v.py >> v.pz; // Lee las coordenadas de cada vértice
        cout << "Vértice " << i << ": " << v.px << ", " << v.py << ", " << v.pz << endl;
        malla.vertices.push_back(v); // Agrega el vértice a la malla
    }

    // Leer y almacenar las caras
    while (true) {
        int numVerticesCara;
        archivo >> numVerticesCara;
        if (numVerticesCara == -1) { // Finaliza cuando encuentra -1
            break;
        }
        Cara c;
        cout << "Número de vértices en la cara: " << numVerticesCara << endl;
        for (int i = 0; i < numVerticesCara; ++i) {
            int indiceVertice;
            archivo >> indiceVertice; // Lee los índices de los vértices de la cara
            c.indicesVertices.push_back(indiceVertice);
        }
        malla.caras.push_back(c); // Agrega la cara a la malla
    }

    archivo.close(); // Cierra el archivo
    cout << "Malla cargada exitosamente: " << malla.nombre << endl;
    return malla;
}

// Función que lista los objetos cargados en memoria
void ListaObjetos() {
    vector<Malla> objetosCargados; // Este vector almacena las mallas cargadas
    if (objetosCargados.empty()) { // Verifica si no hay objetos cargados
        cout << "Ningún objeto ha sido cargado en la memoria." << endl;
        return;
    }

    // Muestra información de los objetos cargados
    cout << "Hay " << objetosCargados.size() << " objetos en memoria: " << endl;
    for (const auto& malla : objetosCargados) {
        cout << "Nombre del objeto: " << malla.nombre << endl;
        cout << "  - Cantidad de vértices: " << malla.vertices.size() << endl;
        cout << "  - Cantidad de caras: " << malla.caras.size() << endl;
    }
}

void calcularCajaEnvolvente(const Malla& malla) {
    if (malla.vertices.empty()) {
        cout << "El objeto " << malla.nombre << " no tiene vértices." << endl;
        return;
    }

    float xmin = numeric_limits<float>::max();
    float ymin = numeric_limits<float>::max();
    float zmin = numeric_limits<float>::max();
    float xmax = numeric_limits<float>::lowest();
    float ymax = numeric_limits<float>::lowest();
    float zmax = numeric_limits<float>::lowest();

    for (const auto& vertice : malla.vertices) {
        if (vertice.px < xmin) xmin = vertice.px;
        if (vertice.py < ymin) ymin = vertice.py;
        if (vertice.pz < zmin) zmin = vertice.pz;
        if (vertice.px > xmax) xmax = vertice.px;
        if (vertice.py > ymax) ymax = vertice.py;
        if (vertice.pz > zmax) zmax = vertice.pz;
    }

    cout << "(Simulación) Caja envolvente para el objeto " << malla.nombre << " generada." << endl;
    cout << "Punto mínimo (xmin, ymin, zmin): (" << xmin << ", " << ymin << ", " << zmin << ")" << endl;
    cout << "Punto máximo (xmax, ymax, zmax): (" << xmax << ", " << ymax << ", " << zmax << ")" << endl;
}


void calcularCajaEnvolventeGlobal(const vector<Malla>& objetosCargados) {
    if (objetosCargados.empty()) {
        cout << "No hay objetos cargados en memoria." << endl;
        return;
    }

    float xmin = numeric_limits<float>::max();
    float ymin = numeric_limits<float>::max();
    float zmin = numeric_limits<float>::max();
    float xmax = numeric_limits<float>::lowest();
    float ymax = numeric_limits<float>::lowest();
    float zmax = numeric_limits<float>::lowest();

    for (const auto& malla : objetosCargados) {
        for (const auto& vertice : malla.vertices) {
            if (vertice.px < xmin) xmin = vertice.px;
            if (vertice.py < ymin) ymin = vertice.py;
            if (vertice.pz < zmin) zmin = vertice.pz;
            if (vertice.px > xmax) xmax = vertice.px;
            if (vertice.py > ymax) ymax = vertice.py;
            if (vertice.pz > zmax) zmax = vertice.pz;
        }
    }

    cout << "(Simulación) Caja envolvente generada para todos los objetos." << endl;
    cout << "Punto mínimo (xmin, ymin, zmin): (" << xmin << ", " << ymin << ", " << zmin << ")" << endl;
    cout << "Punto máximo (xmax, ymax, zmax): (" << xmax << ", " << ymax << ", " << zmax << ")" << endl;
}


// Función principal donde se ejecuta el programa
int main() {

    vector<Malla> objetosCargados; 
    string comando;

    cout << "Bienvenido a la aplicación de modelado de objetos 3D." << endl;
    cout << "Para obtener ayuda sobre un comando específico, ingrese 'ayuda comando'." << endl;

    bool ejecutando = true;

    // Bucle interactivo que espera comandos del usuario
    while (ejecutando) {

        cout<<"Bandera1"<<endl;
        cout << "$ ";  // Indicador de la consola
        getline(cin, comando);  // Leer comando completo del usuario

        convertirMinusculas(comando);
        cout<<comando<<endl;
        coutt<<"Bandera2"<<endl;

        // Dividir el comando en palabras
        vector<string> argumentos = dividirComando(comando);

        if (argumentos.empty()) {
            continue;  // Si no hay entrada, continuar
        }

        string accion = argumentos[0];  // Primer palabra es el comando
        string argumento1 = (argumentos.size() > 1) ? argumentos[1] : "";  // Primer argumento
        string argumento2 = (argumentos.size() > 2) ? argumentos[2] : "";  // Segundo argumento


        // Procesar los comandos
        if (accion == "ayuda") {
            MostrarAyudaGeneral();
            cout<<endl;
        } else if (accion == "cargar") {
            // Simulación de carga de malla
            cout << "(Simulación) Comando 'cargar' ejecutado con el archivo: " << argumento1 << endl;
            Malla malla = LecturaMallas(argumento1);

            // Mostrar malla cargada
            cout << endl << "Nombre de la malla: " << malla.nombre << endl;
            cout << "Cantidad de vértices: " << malla.vertices.size() << endl;
            cout << "Cantidad de caras: " << malla.caras.size() << endl;

             objetosCargados.push_back(malla); 

        } else if (accion == "listado") {
            // Simulación de listado de objetos
            cout << "(Simulación) Listado de objetos cargados en memoria." << endl;
            ListaObjetos();

            cout<<endl;
            
        } else if (accion == "envolvente") {
            if (argumento1.empty()) {
                calcularCajaEnvolventeGlobal(objetosCargados);
            } else {
                auto it = find_if(objetosCargados.begin(), objetosCargados.end(), [&argumento1](const Malla& malla) {
                    return malla.nombre == argumento1;
                });
                if (it != objetosCargados.end()) {
                    calcularCajaEnvolvente(*it);
                } else {
                    cout << "El objeto " << argumento1 << " no ha sido cargado en memoria." << endl;
                }
            }


        } else if (accion == "descargar") {
            // Simulación de descarga de objeto
            cout << "(Simulación) Objeto descargado: " << argumento1 << endl;

        } else if (accion == "guardar") {
            // Simulación de guardado de objeto en archivo
            cout << "(Simulación) Objeto " << argumento1 << " guardado en el archivo " << argumento2 << endl;

        } else if (accion == "v_cercano") {
            // Simulación de búsqueda de vértice más cercano
            if (!argumento1.empty() && !argumento2.empty()) {
                cout << "(Simulación) Vértice más cercano al punto (" << argumento1 << ", " << argumento2 << ") encontrado en el objeto." << endl;
            } else {
                cout << "(Error) Faltan argumentos para el comando 'v_cercano'." << endl;
            }

        } else if (accion == "v_cercanos_caja") {
            // Simulación de búsqueda de vértices más cercanos a las esquinas de la caja envolvente
            cout << "(Simulación) Vértices más cercanos a las esquinas de la caja envolvente del objeto: " << argumento1 << endl;

        } else if (accion == "ruta_corta") {
            // Simulación de cálculo de la ruta más corta entre dos vértices
            cout << "(Simulación) Ruta más corta entre los vértices " << argumento1 << " y " << argumento2 << " en el objeto." << endl;

        } else if (accion == "ruta_corta_centro") {
            // Simulación de cálculo de la ruta más corta desde un vértice al centro del objeto
            cout << "(Simulación) Ruta más corta desde el vértice " << argumento1 << " al centro del objeto." << endl;

        } else if (accion == "salir") {
            // Finalizar la ejecución del programa
            cout << "Saliendo del programa..." << endl;
            ejecutando = false;

        } else {
            // Mensaje de error en caso de comando no reconocido
            cout << "(Error) Comando no reconocido." << endl;
        }
    }

    return 0;
}