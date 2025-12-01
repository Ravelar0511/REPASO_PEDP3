//el mismo de arriba pero con una validacion de datos mas fuerte: 
#include <iostream>     // Entrada y salida estándar
#include <string>       // Manejo de strings
#include <vector>       // Lista dinámica de estudiantes
#include <map>          // Agrupación por carrera
#include <algorithm>    // sort, find_if
#include <limits>       // Limpiar buffer
#include <cctype>       // isspace //validar datos de string

using namespace std;

// -----------------------------------------------------
// Struct secundario (propio, separado)
struct InfoAcademica {
    string carrera;
    float promedio;
};

// Struct principal, contiene al secundario
struct Student {
    int id;
    string nombre;
    InfoAcademica info; 
};

// -----------------------------------------------------
// VALIDACIONES
// -----------------------------------------------------

// Entero general
int leerEntero(const string &mensaje) {
    int x;
    while (true) {
        cout << mensaje;
        if (cin >> x) return x;

        cout << "Entrada inválida. Intente de nuevo.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Entero positivo
int leerEnteroPositivo(const string &mensaje) {
    int x;
    while (true) {
        x = leerEntero(mensaje);
        if (x > 0) return x;

        cout << "El valor debe ser un entero positivo.\n";
    }
}

// Float con validación general
float leerFloat(const string &mensaje) {
    float x;
    while (true) {
        cout << mensaje;
        if (cin >> x) return x;

        cout << "Entrada inválida. Ingrese un número decimal.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Float en rango válido (ej: promedio de 0 a 10)
float leerFloatEnRango(const string &mensaje, float min, float max) {
    float x;
    while (true) {
        x = leerFloat(mensaje);
        if (x >= min && x <= max) return x;

        cout << "El valor debe estar entre " << min << " y " << max << ".\n";
    }
}

// String que no esté vacío ni lleno de espacios
string leerString(const string &mensaje) {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string s;
    while (true) {
        cout << mensaje;
        getline(cin, s);

        bool soloEspacios = true;
        for (char c : s)
            if (!isspace(c)) soloEspacios = false;

        if (!s.empty() && !soloEspacios) return s;

        cout << "El texto no puede estar vacío.\n";
    }
}

// -----------------------------------------------------
// PROGRAMA PRINCIPAL
// -----------------------------------------------------

int main() {

    vector<Student> estudiantes;
    map<string, vector<int>> porCarrera;

    int opcion;

    do {
        cout << "\n=== Sistema de Gestion de Estudiantes ===\n";
        cout << "1. Agregar estudiante\n";
        cout << "2. Mostrar estudiantes\n";
        cout << "3. Buscar estudiante por ID\n";
        cout << "4. Filtrar estudiantes por promedio minimo\n";
        cout << "5. Top 3 promedios mas altos\n";
        cout << "6. Salir\n";

        opcion = leerEntero("Seleccione una opcion: ");

        switch (opcion) {

        case 1: {
            Student st;

            // Validación de ID repetido
            while (true) {
                st.id = leerEnteroPositivo("ID del estudiante: ");

                bool repetido = false;
                for (const auto &e : estudiantes) {
                    if (e.id == st.id) {
                        repetido = true;
                        break;
                    }
                }

                if (!repetido) break;

                cout << "Ya existe un estudiante con ese ID.\n";
            }

            st.nombre = leerString("Nombre del estudiante: ");
            st.info.carrera = leerString("Carrera: ");

            // Promedio entre 0 y 10
            st.info.promedio = leerFloatEnRango("Promedio (0 - 10): ", 0, 10);

            estudiantes.push_back(st);
            porCarrera[st.info.carrera].push_back(st.id);

            cout << "Estudiante agregado correctamente.\n";
            break;
        }

        case 2: {
            if (estudiantes.empty()) {
                cout << "No hay estudiantes registrados.\n";
                break;
            }

            cout << "\nLista de estudiantes:\n";
            for (const auto &s : estudiantes) {
                cout << "ID: " << s.id
                     << " | Nombre: " << s.nombre
                     << " | Carrera: " << s.info.carrera
                     << " | Promedio: " << s.info.promedio << "\n";
            }
            break;
        }

        case 3: {
            if (estudiantes.empty()) {
                cout << "No hay estudiantes para buscar.\n";
                break;
            }

            int idBuscar = leerEnteroPositivo("Ingrese el ID a buscar: ");

            auto it = find_if(estudiantes.begin(), estudiantes.end(),
                [&](const Student &s) { return s.id == idBuscar; });

            if (it != estudiantes.end()) {
                cout << "\nEstudiante encontrado:\n";
                cout << "Nombre: " << it->nombre << "\n";
                cout << "Carrera: " << it->info.carrera << "\n";
                cout << "Promedio: " << it->info.promedio << "\n";
            } else {
                cout << "No existe un estudiante con ese ID.\n";
            }
            break;
        }

        case 4: {
            if (estudiantes.empty()) {
                cout << "No hay estudiantes registrados.\n";
                break;
            }

            float minProm = leerFloatEnRango("Promedio minimo (0-10): ", 0, 10);

            bool alguno = false;
            cout << "\nEstudiantes con promedio >= " << minProm << ":\n";

            for (const auto &s : estudiantes) {
                if (s.info.promedio >= minProm) {
                    cout << s.nombre << " (" << s.info.promedio << ")\n";
                    alguno = true;
                }
            }

            if (!alguno) {
                cout << "Ningun estudiante cumple el criterio.\n";
            }

            break;
        }

        case 5: {
            if (estudiantes.empty()) {
                cout << "No hay estudiantes registrados.\n";
                break;
            }

            vector<Student> copia = estudiantes;

            sort(copia.begin(), copia.end(),
                [](const Student &a, const Student &b) {
                    return a.info.promedio > b.info.promedio;
                });

            int limite = min(3, (int)copia.size());

            cout << "\nTop " << limite << " promedios mas altos:\n";
            for (int i = 0; i < limite; i++) {
                cout << copia[i].nombre
                     << " - Promedio: " << copia[i].info.promedio << "\n";
            }

            break;
        }

        case 6:
            cout << "Saliendo del sistema...\n";
            break;

        default:
            cout << "Opcion invalida. Ingrese un numero entre 1 y 6.\n";
        }

    } while (opcion != 6);

    return 0;
}