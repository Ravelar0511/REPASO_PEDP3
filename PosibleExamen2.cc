// Gestión de cursos con struct anidado, vector, set y find_if
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <algorithm>
using namespace std;

// =================================
// STRUCTS
// =================================

struct Area {
    string nombre;
    string descripcion;
};

struct Curso {
    int id;
    string nombre;
    int uv;
    Area area; // struct anidado
};

// =================================
// AGREGAR
// =================================

void agregarCurso(vector<Curso> &cursos, map<int, Area> &areas, set<int> &ids) {
    Curso c;
    int idArea;

    cout << "\n=== NUEVO CURSO ===\n";

    do {
        cout << "ID del curso: ";
        cin >> c.id;
        cin.ignore();
    } while (c.id <= 0 || ids.count(c.id));

    ids.insert(c.id);

    cout << "Nombre del curso: ";
    getline(cin, c.nombre);

    cout << "Unidades valorativas: ";
    cin >> c.uv;
    cin.ignore();

    cout << "\nAREAS DISPONIBLES:\n";
    for (auto &a : areas)
        cout << a.first << ". " << a.second.nombre << "\n";

    do {
        cout << "Seleccione área: ";
        cin >> idArea;
        cin.ignore();
    } while (areas.find(idArea) == areas.end());

    c.area = areas[idArea];

    cursos.push_back(c);
}

// =================================
// BUSCAR
// =================================

void buscarCurso(const vector<Curso> &cursos) {
    int b;
    cout << "\nID a buscar: ";
    cin >> b;
    cin.ignore();

    auto it = find_if(cursos.begin(), cursos.end(),
        [&](const Curso &c){ return c.id == b; });

    if (it != cursos.end()) {
        cout << "\n== ENCONTRADO ==\n";
        cout << "ID: " << it->id << "\n";
        cout << "Nombre: " << it->nombre << "\n";
        cout << "UV: " << it->uv << "\n";
        cout << "Área: " << it->area.nombre << "\n";
    } else {
        cout << "No existe.\n";
    }
}

// =================================
// MOSTRAR
// =================================

void mostrar(const vector<Curso> &cursos) {
    cout << "\n=== LISTA DE CURSOS ===\n";
    for (auto &c : cursos) {
        cout << "\nID: " << c.id << "\n";
        cout << "Curso: " << c.nombre << "\n";
        cout << "UV: " << c.uv << "\n";
        cout << "Área: " << c.area.nombre << "\n";
    }
}

// =================================
// ELIMINAR
// =================================

void eliminarCurso(vector<Curso> &cursos, set<int> &ids) {
    int b;
    cout << "\nID a eliminar: ";
    cin >> b;
    cin.ignore();

    auto it = find_if(cursos.begin(), cursos.end(),
        [&](const Curso &c){ return c.id == b; });

    if (it != cursos.end()) {
        ids.erase(it->id);
        cursos.erase(it);
        cout << "Curso eliminado.\n";
    } else {
        cout << "No existe el curso.\n";
    }
}

// =================================
// MAIN
// =================================

int main() {
    vector<Curso> cursos;
    set<int> ids;

    map<int, Area> areas;
    areas[1] = {"Ciencias Básicas", "Matemáticas y Física"};
    areas[2] = {"Ingeniería", "Cursos técnicos"};
    areas[3] = {"Humanidades", "Artes, letras y sociedad"};

    int op;

    do {
        cout << "\n1. Agregar\n2. Mostrar\n3. Buscar\n4. Eliminar\n5. Salir\nOpción: ";
        cin >> op;
        cin.ignore();

        switch (op) {
            case 1: agregarCurso(cursos, areas, ids); break;
            case 2: mostrar(cursos); break;
            case 3: buscarCurso(cursos); break;
            case 4: eliminarCurso(cursos, ids); break;
        }

    } while (op != 5);

    return 0;
}
