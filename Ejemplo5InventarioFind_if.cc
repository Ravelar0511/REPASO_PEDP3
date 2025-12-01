#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <cctype>

using namespace std;

// ------------------------------------
// VALIDACIONES
// ------------------------------------
int leerEntero(const string &msg) {
    int x;
    while (true) {
        cout << msg;
        if (cin >> x) return x;
        cout << "Valor inválido.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int leerEnteroPositivo(const string &msg) {
    int x;
    while (true) {
        x = leerEntero(msg);
        if (x > 0) return x;
        cout << "Debe ser un número positivo.\n";
    }
}

float leerFloat(const string &msg) {
    float x;
    while (true) {
        cout << msg;
        if (cin >> x) return x;
        cout << "Valor inválido.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

float leerFloatPositivo(const string &msg) {
    float x;
    while (true) {
        x = leerFloat(msg);
        if (x > 0) return x;
        cout << "Debe ser positivo.\n";
    }
}

string leerString(const string &msg) {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string s;

    while (true) {
        cout << msg;
        getline(cin, s);

        bool soloEsp = true;
        for (char c : s)
            if (!isspace(c)) soloEsp = false;

        if (!s.empty() && !soloEsp) return s;

        cout << "El texto no puede estar vacío.\n";
    }
}

// ------------------------------------
// PROGRAMA PRINCIPAL: INVENTARIO
// ------------------------------------
struct Producto {
    int id;
    string nombre;
    string categoria;
    float precio;
};

int main() {
    vector<Producto> productos;
    int opcion;

    do {
        cout << "\n==== SISTEMA DE INVENTARIO ====\n";
        cout << "1. Agregar producto\n";
        cout << "2. Buscar por ID\n";
        cout << "3. Buscar por nombre\n";
        cout << "4. Buscar por categoria\n";
        cout << "5. Mostrar inventario\n";
        cout << "6. Salir\n";

        opcion = leerEntero("Seleccione: ");

        switch (opcion) {

        case 1: {
            Producto p;

            while (true) {
                p.id = leerEnteroPositivo("ID del producto: ");

                auto it = find_if(productos.begin(), productos.end(),
                    [&](const Producto &x) { return x.id == p.id; });

                if (it == productos.end()) break;

                cout << "Ese ID ya existe.\n";
            }

            p.nombre = leerString("Nombre: ");
            p.categoria = leerString("Categoria: ");
            p.precio = leerFloatPositivo("Precio: ");

            productos.push_back(p);
            cout << "Producto agregado.\n";
            break;
        }

        case 2: {
            if (productos.empty()) {
                cout << "No hay productos.\n";
                break;
            }

            int idBuscar = leerEnteroPositivo("ID a buscar: ");
            auto it = find_if(productos.begin(), productos.end(),
                [&](const Producto &x) { return x.id == idBuscar; });

            if (it != productos.end()) {
                cout << "Encontrado: " << it->nombre 
                     << " | $" << it->precio << "\n";
            } else {
                cout << "No existe ese ID.\n";
            }
            break;
        }

        case 3: {
            if (productos.empty()) {
                cout << "No hay productos.\n";
                break;
            }

            string n = leerString("Nombre exacto: ");

            auto it = find_if(productos.begin(), productos.end(),
                [&](const Producto &x) { return x.nombre == n; });

            if (it != productos.end()) {
                cout << "Producto encontrado: " << it->id 
                     << " | $" << it->precio << "\n";
            } else {
                cout << "No existe ese nombre.\n";
            }
            break;
        }

        case 4: {
            if (productos.empty()) {
                cout << "No hay productos.\n";
                break;
            }

            string c = leerString("Categoria: ");

            auto it = find_if(productos.begin(), productos.end(),
                [&](const Producto &x) { return x.categoria == c; });

            if (it != productos.end()) {
                cout << "Primer producto en categoria '" << c 
                     << "': " << it->nombre << "\n";
            } else {
                cout << "No hay productos de esa categoria.\n";
            }
            break;
        }

        case 5: {
            cout << "\nINVENTARIO:\n";
            for (auto &p : productos)
                cout << p.id << " | " << p.nombre 
                     << " | " << p.categoria 
                     << " | $" << p.precio << "\n";
            break;
        }

        case 6:
            cout << "Adios...\n";
            break;

        default:
            cout << "Opcion invalida.\n";
        }
    } while (opcion != 6);

    return 0;
}
