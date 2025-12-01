// Ejemplo de uso de map, set y find_if sin usar vector
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <algorithm> 
using namespace std;

// -----------------------------------
// Structs
// -----------------------------------

struct Carrera {
    string nombre;
    string facultad;
};

struct Estudiante {
    string nombre;
    int edad;
    Carrera carrera; // Struct anidado
};

// -----------------------------------
// Agregar estudiante
// -----------------------------------

void agregarEstudiante(map<int, Estudiante> &estudiantes, set<int> &ids) {
    int id;
    Estudiante e;

    cout << "\n== Registrar Estudiante ==\n";

    do {
        cout << "ID (entero positivo): ";
        cin >> id;
        cin.ignore();
    } while (id <= 0 || ids.count(id) == 1);

    ids.insert(id);

    cout << "Nombre: ";
    getline(cin, e.nombre);

    cout << "Edad: ";
    cin >> e.edad;
    cin.ignore();

    cout << "Carrera: ";
    getline(cin, e.carrera.nombre);

    cout << "Facultad: ";
    getline(cin, e.carrera.facultad);

    estudiantes[id] = e;
}

// -----------------------------------
// Buscar estudiante por nombre con find_if
// -----------------------------------

void buscarPorNombre(const map<int, Estudiante> &estudiantes) {
    string b;
    cout << "\nIngrese nombre a buscar: ";
    getline(cin, b);

    auto it = find_if(estudiantes.begin(), estudiantes.end(),
        [&](const auto &par) { return par.second.nombre == b; });

    if (it != estudiantes.end()) {
        cout << "\n== ENCONTRADO ==\n";
        cout << "ID: " << it->first << "\n";
        cout << "Nombre: " << it->second.nombre << "\n";
        cout << "Edad: " << it->second.edad << "\n";
        cout << "Carrera: " << it->second.carrera.nombre << "\n";
    } else {
        cout << "No se encontró.\n";
    }
}

// -----------------------------------

void mostrar(const map<int, Estudiante> &estudiantes) {
    cout << "\n=== LISTA DE ESTUDIANTES ===\n";
    for (auto &p : estudiantes) {
        cout << "\nID: " << p.first << "\n";
        cout << "Nombre: " << p.second.nombre << "\n";
        cout << "Edad: " << p.second.edad << "\n";
        cout << "Carrera: " << p.second.carrera.nombre << "\n";
    }
}

// -----------------------------------

int main() {
    map<int, Estudiante> estudiantes;
    set<int> ids;

    int op;

    do {
        cout << "\n1. Agregar estudiante\n";
        cout << "2. Mostrar\n";
        cout << "3. Buscar por nombre\n";
        cout << "4. Salir\n";
        cout << "Opción: ";
        cin >> op;
        cin.ignore();

        switch (op) {
            case 1: agregarEstudiante(estudiantes, ids); break;
            case 2: mostrar(estudiantes); break;
            case 3: buscarPorNombre(estudiantes); break;
        }
    } while (op != 4);

    return 0;
}
