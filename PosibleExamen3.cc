// Gestión de vehículos con struct anidado, map, set y find_if sin vector
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <algorithm>
using namespace std;

// ==============================
// STRUCTS
// ==============================

struct Propietario {
    string nombre;
    string ciudad;
};

struct Vehiculo {
    string placa;
    string marca;
    int anio;
    Propietario prop;   // struct anidado
};

// ==============================
// AGREGAR (map + set)
// ==============================

void agregarVehiculo(map<string, Vehiculo> &vehiculos, set<string> &placas) {
    Vehiculo v;

    cout << "\n=== AGREGAR VEHÍCULO ===\n";

    do {
        cout << "Placa: ";
        getline(cin, v.placa);
    } while (v.placa.empty() || placas.count(v.placa));

    placas.insert(v.placa);

    cout << "Marca: ";
    getline(cin, v.marca);

    cout << "Año: ";
    cin >> v.anio;
    cin.ignore();

    cout << "Nombre del propietario: ";
    getline(cin, v.prop.nombre);

    cout << "Ciudad del propietario: ";
    getline(cin, v.prop.ciudad);

    vehiculos[v.placa] = v;
}

// ==============================
// BUSCAR (find_if en map)
// ==============================

void buscarVehiculo(const map<string, Vehiculo> &vehiculos) {
    string b;

    cout << "\nPlaca a buscar: ";
    getline(cin, b);

    auto it = vehiculos.find(b);

    if (it != vehiculos.end()) {
        cout << "\n== ENCONTRADO ==\n";
        cout << "Placa: " << it->second.placa << "\n";
        cout << "Marca: " << it->second.marca << "\n";
        cout << "Año: " << it->second.anio << "\n";
        cout << "Propietario: " << it->second.prop.nombre << "\n";
    } else {
        cout << "No se encontró la placa.\n";
    }
}

// ==============================
// MOSTRAR
// ==============================

void mostrar(const map<string, Vehiculo> &vehiculos) {
    cout << "\n=== VEHÍCULOS REGISTRADOS ===\n";
    for (auto &v : vehiculos) {
        cout << "\nPlaca: " << v.second.placa << "\n";
        cout << "Marca: " << v.second.marca << "\n";
        cout << "Año: " << v.second.anio << "\n";
        cout << "Propietario: " << v.second.prop.nombre << "\n";
    }
}

// ==============================
// ELIMINAR (del map y del set)
// ==============================

void eliminarVehiculo(map<string, Vehiculo> &vehiculos, set<string> &placas) {
    string b;

    cout << "\nPlaca a eliminar: ";
    getline(cin, b);

    auto it = vehiculos.find(b);

    if (it != vehiculos.end()) {
        placas.erase(b);
        vehiculos.erase(it);
        cout << "Vehículo eliminado.\n";
    } else {
        cout << "No existe esa placa.\n";
    }
}

// ==============================
// MAIN
// ==============================

int main() {
    map<string, Vehiculo> vehiculos;
    set<string> placas;

    int op;

    do {
        cout << "\n1. Agregar\n2. Mostrar\n3. Buscar\n4. Eliminar\n5. Salir\nOpción: ";
        cin >> op;
        cin.ignore();

        switch (op) {
            case 1: agregarVehiculo(vehiculos, placas); break;
            case 2: mostrar(vehiculos); break;
            case 3: buscarVehiculo(vehiculos); break;
            case 4: eliminarVehiculo(vehiculos, placas); break;
        }

    } while (op != 5);

    return 0;
}
