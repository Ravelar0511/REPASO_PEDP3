//gestion de empleados con struct, vector, set y find_if y eliminacion
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <algorithm>
using namespace std;

// =====================================
// STRUCTS
// =====================================

struct Departamento {
    string nombre;
    string descripcion;
};

struct Empleado {
    int id;
    string nombre;
    int edad;
    Departamento depto;   // Struct anidado
};

// =====================================
// AGREGAR EMPLEADO
// =====================================

void agregarEmpleado(vector<Empleado> &empleados, 
                     map<int, Departamento> &departamentos, 
                     set<int> &ids) 
{
    Empleado e;
    int idDep;

    cout << "\n=== REGISTRAR EMPLEADO ===\n";

    // ID único usando set
    do {
        cout << "ID del empleado (positivo): ";
        cin >> e.id;
        cin.ignore();
    } while (e.id <= 0 || ids.count(e.id) == 1);

    ids.insert(e.id);

    cout << "Nombre: ";
    getline(cin, e.nombre);

    cout << "Edad: ";
    cin >> e.edad;
    cin.ignore();

    cout << "\nDEPARTAMENTOS DISPONIBLES:\n";
    for (auto &d : departamentos) {
        cout << d.first << ". " << d.second.nombre << " - " << d.second.descripcion << "\n";
    }

    do {
        cout << "Seleccione ID de departamento: ";
        cin >> idDep;
        cin.ignore();
    } while (departamentos.find(idDep) == departamentos.end());

    e.depto = departamentos[idDep];

    // Guardar
    empleados.push_back(e);
}

// =====================================
// BUSCAR EMPLEADO (USANDO find_if)
// =====================================

void buscarEmpleado(const vector<Empleado> &empleados) {
    int b;

    cout << "\nID a buscar: ";
    cin >> b;
    cin.ignore();

    auto it = find_if(empleados.begin(), empleados.end(),
        [&](const Empleado &e){ return e.id == b; });

    if (it != empleados.end()) {
        cout << "\n== EMPLEADO ENCONTRADO ==\n";
        cout << "ID: " << it->id << "\n";
        cout << "Nombre: " << it->nombre << "\n";
        cout << "Edad: " << it->edad << "\n";
        cout << "Departamento: " << it->depto.nombre << "\n";
    } else {
        cout << "No existe empleado con ese ID.\n";
    }
}

// =====================================
// MOSTRAR TODOS
// =====================================

void mostrarTodos(const vector<Empleado> &empleados) {
    cout << "\n=== LISTA DE EMPLEADOS ===\n";

    if (empleados.empty()) {
        cout << "No hay empleados registrados.\n";
        return;
    }

    for (auto &e : empleados) {
        cout << "\nID: " << e.id << "\n";
        cout << "Nombre: " << e.nombre << "\n";
        cout << "Edad: " << e.edad << "\n";
        cout << "Departamento: " << e.depto.nombre << "\n";
    }
}

// =====================================
// ELIMINAR EMPLEADO (USANDO find_if)
// =====================================

void eliminarEmpleado(vector<Empleado> &empleados, set<int> &ids) {
    int b;

    cout << "\nID a eliminar: ";
    cin >> b;
    cin.ignore();

    auto it = find_if(empleados.begin(), empleados.end(),
        [&](const Empleado &e){ return e.id == b; });

    if (it != empleados.end()) {
        ids.erase(it->id);        // quitar ID del set
        empleados.erase(it);      // eliminar del vector
        cout << "Empleado eliminado con éxito.\n";
    } else {
        cout << "No existe un empleado con ese ID.\n";
    }
}

// =====================================
// MAIN
// =====================================

int main() {
    vector<Empleado> empleados;
    set<int> ids;   // IDs únicos

    // MAP de departamentos
    map<int, Departamento> departamentos;
    departamentos[1] = {"Administración", "Gestión de la empresa"};
    departamentos[2] = {"Ventas", "Atención a clientes y ventas"};
    departamentos[3] = {"TI", "Tecnología e informática"};

    int op;

    do {
        cout << "\n====== MENU ======\n";
        cout << "1. Agregar empleado\n";
        cout << "2. Mostrar empleados\n";
        cout << "3. Buscar empleado\n";
        cout << "4. Eliminar empleado\n";
        cout << "5. Salir\n";
        cout << "Opción: ";
        cin >> op;
        cin.ignore();

        switch (op) {
            case 1: agregarEmpleado(empleados, departamentos, ids); break;
            case 2: mostrarTodos(empleados); break;
            case 3: buscarEmpleado(empleados); break;
            case 4: eliminarEmpleado(empleados, ids); break;
        }

    } while (op != 5);

    return 0;
}
