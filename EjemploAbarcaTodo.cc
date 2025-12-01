// Ejemplo completo que abarca struct, vector, set y find_if
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <algorithm>
using namespace std;

struct Propietario {
    string nombre;
    string direccion;
};

struct Vehiculo {
    string placa;
    string marca;
    int anio;
    Propietario propietario; // anidado
};

void agregarVehiculo(vector<Vehiculo> &v, set<string> &placas) {
    Vehiculo x;

    cout << "\n== Registrar Vehículo ==\n";

    do {
        cout << "Placa: ";
        getline(cin, x.placa);
    } while (x.placa.empty() || placas.count(x.placa));

    placas.insert(x.placa);

    cout << "Marca: ";
    getline(cin, x.marca);

    cout << "Año: ";
    cin >> x.anio;
    cin.ignore();

    cout << "Nombre del propietario: ";
    getline(cin, x.propietario.nombre);

    cout << "Dirección: ";
    getline(cin, x.propietario.direccion);

    v.push_back(x);
}

void buscarVehiculo(const vector<Vehiculo> &v) {
    string b;

    cout << "\nPlaca a buscar: ";
    getline(cin, b);

    auto it = find_if(v.begin(), v.end(),
        [&](const Vehiculo &x){ return x.placa == b; });

    if (it != v.end()) {
        cout << "\n== ENCONTRADO ==\n";
        cout << "Placa: " << it->placa << "\n";
        cout << "Marca: " << it->marca << "\n";
        cout << "Año: " << it->anio << "\n";
        cout << "Propietario: " << it->propietario.nombre << "\n";
    } else {
        cout << "No existe.\n";
    }
}

void mostrar(const vector<Vehiculo> &v) {
    cout << "\n=== VEHÍCULOS REGISTRADOS ===\n";
    for (auto &x : v) {
        cout << "\nPlaca: " << x.placa << "\n";
        cout << "Marca: " << x.marca << "\n";
        cout << "Año: " << x.anio << "\n";
        cout << "Propietario: " << x.propietario.nombre << "\n";
    }
}

int main() {
    vector<Vehiculo> vehiculos;
    set<string> placas;

    int op;

    do {
        cout << "\n1. Agregar\n2. Mostrar\n3. Buscar\n4. Salir\nOpción: ";
        cin >> op;
        cin.ignore();

        switch (op) {
            case 1: agregarVehiculo(vehiculos, placas); break;
            case 2: mostrar(vehiculos); break;
            case 3: buscarVehiculo(vehiculos); break;
        }
    } while (op != 4);
}
