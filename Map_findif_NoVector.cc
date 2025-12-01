//gestión de productos con struct anidado y map, busqueda con find_if sin usar vector
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

// ===================================
// Structs separadas
// ===================================

struct Proveedor {
    string nombre;
    string telefono;
};

struct Producto {
    string nombre;
    double precio;
    Proveedor proveedor; // anidado
};

// ===================================
// Función para agregar producto
// ===================================

void agregarProducto(map<int, Producto> &productos) {
    Producto p;
    int id;

    cout << "\nID del producto (número entero): ";
    cin >> id;
    cin.ignore();

    do {
        cout << "Nombre del producto: ";
        getline(cin, p.nombre);
    } while (p.nombre.empty());

    do {
        cout << "Precio (>0): ";
        cin >> p.precio;
        cin.ignore();
    } while (p.precio <= 0);

    // Proveedor
    do {
        cout << "Proveedor: ";
        getline(cin, p.proveedor.nombre);
    } while (p.proveedor.nombre.empty());

    do {
        cout << "Teléfono proveedor: ";
        getline(cin, p.proveedor.telefono);
    } while (p.proveedor.telefono.empty());

    productos[id] = p;
}

// ===================================
// Buscar producto usando find_if
// ===================================

void buscarProducto(const map<int, Producto> &productos) {
    string buscar;
    cout << "\nNombre del producto a buscar: ";
    getline(cin, buscar);

    auto it = find_if(productos.begin(), productos.end(),
        [&](const pair<int, Producto> &par){
            return par.second.nombre == buscar;
        });

    if (it != productos.end()) {
        cout << "\n== PRODUCTO ENCONTRADO ==\n";
        cout << "ID: " << it->first << "\n";
        cout << "Nombre: " << it->second.nombre << "\n";
        cout << "Precio: " << it->second.precio << "\n";
        cout << "Proveedor: " << it->second.proveedor.nombre << "\n";
    } else {
        cout << "\nProducto no encontrado.\n";
    }
}

// ===================================
// Mostrar todos
// ===================================

void mostrarProductos(const map<int, Producto> &productos) {
    cout << "\n=== PRODUCTOS ===\n";

    for (auto &p : productos) {
        cout << "\nID: " << p.first << "\n";
        cout << "Nombre: " << p.second.nombre << "\n";
        cout << "Precio: " << p.second.precio << "\n";
        cout << "Proveedor: " << p.second.proveedor.nombre << "\n";
        cout << "Teléfono: " << p.second.proveedor.telefono << "\n";
    }
}

// ===================================
// MAIN
// ===================================

int main() {

    map<int, Producto> productos;
    int opcion;

    do {
        cout << "\n1. Agregar producto\n";
        cout << "2. Mostrar productos\n";
        cout << "3. Buscar producto\n";
        cout << "4. Salir\n";
        cout << "Opción: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: agregarProducto(productos); break;
            case 2: mostrarProductos(productos); break;
            case 3: buscarProducto(productos); break;
        }

    } while (opcion != 4);

    return 0;
}
