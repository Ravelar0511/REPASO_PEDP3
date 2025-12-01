// Sistema de gestión de vehículos
#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <string>
#include <limits>

using namespace std;

// =============================
// STRUCTS SEPARADOS Y ANIDADOS
// =============================

// Struct independiente (motor)
struct Engine {
    string tipo;   // Gasolina, Diesel, Electrico
    int caballos;  // HP
};

// Struct principal que contiene el struct Engine
struct Vehicle {
    int id;
    string marca;
    string modelo;
    int año;
    Engine motor;   // ANIDADO, PERO SEPARADO
};

// Para ordenar vehículos por ID dentro del set
struct OrdenarPorID {
    bool operator()(const Vehicle& a, const Vehicle& b) const {
        return a.id < b.id;
    }
};

// =============================
// VALIDACIONES
// =============================
int leerEnteroPositivo(string msg) {
    int n;
    while (true) {
        cout << msg;
        if (cin >> n && n > 0) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return n;
        }
        cout << "Valor inválido. Intente de nuevo.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

string leerTexto(string msg) {
    string s;
    cout << msg;
    getline(cin, s);

    while (s.empty()) {
        cout << "El texto no puede estar vacío. Ingrese de nuevo: ";
        getline(cin, s);
    }
    return s;
}

// =============================
// PROGRAMA PRINCIPAL
// =============================
int main() {

    set<Vehicle, OrdenarPorID> vehiculos;
    unordered_map<int, Vehicle> accesoRapido;

    while (true) {
        cout << "\n===== MENU =====\n";
        cout << "1) Registrar vehículo\n";
        cout << "2) Buscar vehículo por ID\n";
        cout << "3) Mostrar vehículos por año (ordenados)\n";
        cout << "4) Filtrar por potencia del motor\n";
        cout << "5) Salir\n";
        cout << "Opción: ";

        int op;
        if (!(cin >> op)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Opción inválida.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpia buffer

        // -----------------------------------------
        // 1) REGISTRAR VEHÍCULO
        // -----------------------------------------
        if (op == 1) {

            Vehicle v;

            v.id = leerEnteroPositivo("ID del vehículo: ");

            if (accesoRapido.count(v.id)) {
                cout << "Ya existe un vehículo con ese ID.\n";
                continue;
            }

            v.marca = leerTexto("Marca: ");
            v.modelo = leerTexto("Modelo: ");
            v.año = leerEnteroPositivo("Año del vehículo: ");

            cout << "\n=== Datos del motor ===\n";
            v.motor.tipo = leerTexto("Tipo de motor (Gasolina/Diesel/Electrico): ");
            v.motor.caballos = leerEnteroPositivo("Caballos de fuerza (HP): ");

            vehiculos.insert(v);
            accesoRapido[v.id] = v;

            cout << "Vehículo registrado correctamente.\n";
        }

        // -----------------------------------------
        // 2) BUSCAR VEHÍCULO POR ID
        // -----------------------------------------
        else if (op == 2) {

            if (vehiculos.empty()) {
                cout << "No hay vehículos registrados.\n";
                continue;
            }

            int id = leerEnteroPositivo("ID a buscar: ");

            if (!accesoRapido.count(id)) {
                cout << "No existe un vehículo con ese ID.\n";
                continue;
            }

            const Vehicle& v = accesoRapido[id];

            cout << "\nVehículo encontrado:\n";
            cout << "ID: " << v.id
                 << "\nMarca: " << v.marca
                 << "\nModelo: " << v.modelo
                 << "\nAño: " << v.año
                 << "\nMotor: " << v.motor.tipo << " - " << v.motor.caballos << " HP\n";
        }

        // -----------------------------------------
        // 3) MOSTRAR AÑOS ORDENADOS
        // -----------------------------------------
        else if (op == 3) {

            if (vehiculos.empty()) {
                cout << "No hay vehículos registrados.\n";
                continue;
            }

            vector<int> años;
            for (const auto& v : vehiculos)
                años.push_back(v.año);

            sort(años.begin(), años.end());

            cout << "\nAños registrados (ordenados): ";
            for (int a : años) cout << a << " ";
            cout << "\n";

            int buscarAño = leerEnteroPositivo("Año a buscar: ");

            if (binary_search(años.begin(), años.end(), buscarAño))
                cout << "El año existe en la base de datos.\n";
            else
                cout << "El año no está registrado.\n";
        }

        // -----------------------------------------
        // 4) FILTRAR POR CABALLOS DE FUERZA
        // -----------------------------------------
        else if (op == 4) {

            if (vehiculos.empty()) {
                cout << "No hay vehículos registrados.\n";
                continue;
            }

            int minHP = leerEnteroPositivo("Mostrar vehículos con más de X HP: ");

            vector<Vehicle> filtrados;

            copy_if(vehiculos.begin(), vehiculos.end(), back_inserter(filtrados),
                [&](const Vehicle& v) { return v.motor.caballos > minHP; });

            if (filtrados.empty()) {
                cout << "No hay vehículos con más de " << minHP << " HP.\n";
                continue;
            }

            cout << "\nVehículos filtrados:\n";
            for (const auto& v : filtrados) {
                cout << v.marca << " " << v.modelo
                     << " - " << v.motor.caballos << " HP\n";
            }
        }

        // -----------------------------------------
        // 5) SALIR
        // -----------------------------------------
        else if (op == 5) {
            cout << "Saliendo...\n";
            break;
        }

        else {
            cout << "Opción inválida.\n";
        }
    }

    return 0;
}
