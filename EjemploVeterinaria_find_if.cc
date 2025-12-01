#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <cctype>

using namespace std;

int leerInt(const string &msg) {
    int x;
    while (true) {
        cout << msg;
        if (cin >> x) return x;
        cout << "Valor inválido.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int leerEnteroPos(const string &msg) {
    int x;
    while (true) {
        x = leerInt(msg);
        if (x > 0) return x;
        cout << "Debe ser positivo.\n";
    }
}

string leerTexto(const string &msg) {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string s;

    while (true) {
        cout << msg;
        getline(cin, s);

        bool esp = true;
        for (char c : s)
            if (!isspace(c)) esp = false;

        if (!s.empty() && !esp) return s;

        cout << "No puede estar vacío.\n";
    }
}

struct Mascota {
    string nombre;
    string tipo;
    int edad;
};

int main() {
    vector<Mascota> mascotas;
    int op;

    do {
        cout << "\n==== VETERINARIA ====\n";
        cout << "1. Registrar mascota\n";
        cout << "2. Buscar por nombre\n";
        cout << "3. Buscar mascota mayor a edad X\n";
        cout << "4. Buscar primer animal de un tipo\n";
        cout << "5. Mostrar todas\n";
        cout << "6. Salir\n";

        op = leerInt("Opción: ");

        switch (op) {
        case 1: {
            Mascota m;
            m.nombre = leerTexto("Nombre: ");
            m.tipo = leerTexto("Tipo (perro, gato, etc): ");
            m.edad = leerEnteroPos("Edad: ");
            mascotas.push_back(m);
            break;
        }

        case 2: {
            string n = leerTexto("Nombre a buscar: ");
            auto it = find_if(mascotas.begin(), mascotas.end(),
                [&](const Mascota &m) { return m.nombre == n; });

            if (it != mascotas.end()) {
                cout << "Encontrada: " << it->tipo 
                     << " de " << it->edad << " años.\n";
            } else {
                cout << "No se encontró esa mascota.\n";
            }
            break;
        }

        case 3: {
            int e = leerEnteroPos("Edad mínima: ");
            auto it = find_if(mascotas.begin(), mascotas.end(),
                [&](const Mascota &m) { return m.edad >= e; });

            if (it != mascotas.end()) {
                cout << "Mascota encontrada: " << it->nombre 
                     << " (" << it->edad << " años).\n";
            } else {
                cout << "Ninguna mascota con esa edad.\n";
            }
            break;
        }

        case 4: {
            string t = leerTexto("Tipo: ");
            auto it = find_if(mascotas.begin(), mascotas.end(),
                [&](const Mascota &m) { return m.tipo == t; });

            if (it != mascotas.end()) {
                cout << "Primer " << t << ": " << it->nombre << "\n";
            } else {
                cout << "No se encontró ese tipo.\n";
            }
            break;
        }

        case 5:
            cout << "\nMASCOTAS:\n";
            for (auto &m : mascotas)
                cout << m.nombre << " | " << m.tipo 
                     << " | " << m.edad << "\n";
            break;

        case 6:
            cout << "Saliendo...\n";
            break;

        default:
            cout << "Opción inválida.\n";
        }

    } while (op != 6);

    return 0;
}
