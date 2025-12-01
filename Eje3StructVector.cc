//sistema de estudiantes struct anidado con validacion de datos basica:
#include <iostream>     // Entrada y salida estándar
#include <string>       // Manejo de strings
#include <vector>       // Lista dinámica de estudiantes
#include <map>          // Agrupación por carrera
#include <algorithm>    // sort y find_if
#include <limits>       // Limpiar buffer

using namespace std;

// Struct independiente con elementos propios
struct InfoAcademica {
    string carrera;
    float promedio;
};

// Struct principal que incluye el struct anterior (anidación separada)
struct Student {
    int id;
    string nombre;
    InfoAcademica info;   // Anidado pero declarado afuera
};

// Funciones de validación -------------------------------

int leerEntero(const string &mensaje) {
    int x;
    while (true) {
        cout << mensaje;
        if (cin >> x) return x;

        cout << "Error: ingrese un numero valido.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

float leerFloat(const string &mensaje) {
    float x;
    while (true) {
        cout << mensaje;
        if (cin >> x) return x;

        cout << "Error: ingrese un numero decimal valido.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

string leerString(const string &mensaje) {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string s;
    while (true) {
        cout << mensaje;
        getline(cin, s);
        if (!s.empty()) return s;

        cout << "Error: el campo no puede estar vacio.\n";
    }
}

// Programa principal ------------------------------------

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
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {

            case 1: {
                Student st;

                st.id = leerEntero("Ingrese el ID del estudiante: ");
                st.nombre = leerString("Ingrese el nombre del estudiante: ");
                st.info.carrera = leerString("Ingrese la carrera: ");
                st.info.promedio = leerFloat("Ingrese el promedio: ");

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

                cout << "\nLista de estudiantes registrados:\n";
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

                int idBuscar = leerEntero("Ingrese el ID a buscar: ");

                auto it = find_if(estudiantes.begin(), estudiantes.end(),
                    [&](const Student &s) { return s.id == idBuscar; });

                if (it != estudiantes.end()) {
                    cout << "\nEstudiante encontrado:\n";
                    cout << "Nombre: " << it->nombre << "\n";
                    cout << "Carrera: " << it->info.carrera << "\n";
                    cout << "Promedio: " << it->info.promedio << "\n";
                } else {
                    cout << "No se encontro un estudiante con ese ID.\n";
                }
                break;
            }

            case 4: {
                if (estudiantes.empty()) {
                    cout << "No hay estudiantes registrados.\n";
                    break;
                }

                float minProm = leerFloat("Promedio minimo: ");

                cout << "\nEstudiantes con promedio >= " << minProm << ":\n";
                bool alguno = false;

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

                cout << "\nTop " << limite << " mejores promedios:\n";
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
                cout << "Opcion invalida.\n";
        }

    } while (opcion != 6);

    return 0;
}