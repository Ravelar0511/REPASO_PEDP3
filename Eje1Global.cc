/* Ejercicio Completo: Sistema de Gestión de Jugadores de un Videojuego Online
Una empresa de videojuegos quiere administrar información de los jugadores registrados en un juego RPG online.
Cada jugador tiene:
· id (int)
· nombre (string)
· nivel (int)
· clase (string) ej: "Guerrero", "Mago", "Arquero"
· poder (int)  una medida general de fuerza

Requerimientos del programa
1. Guardar todos los jugadores en un set<Player> ordenado por id.
2. Crear un map<string, set<int>> que clasifique jugadores por clase (ej: todos los IDs de los magos).
3. Crear un unordered_map<int, Player> para acceder rápidamente a los datos de un jugador por su ID.
4. Generar un vector con todos los niveles para ordenarlos con sort y poder calcular estadísticas.
5. Buscar si un nivel específico existe usando binary_search.
6. Filtrar jugadores cuyo poder sea mayor a cierto valor.
7. Mostrar el top 3 de jugadores más fuertes usando ordenamiento por poder (descendente).*/


//ejemplo de arriba usando sed map e ingreso de datos del usuario: 
#include <iostream>        // Uso: cin, cout, endl
#include <set>             // Uso: set<Player>, set<int>
#include <map>             // Uso: map<string, set<int>>
#include <unordered_map>   // Uso: unordered_map<int, Player>
#include <vector>          // Uso: vector<int>, vector<Player>
#include <algorithm>       // Uso: sort(), binary_search(), copy_if()
#include <string>          // Uso: string, getline()
#include <limits>          // Uso: numeric_limits para limpiar buffers

using namespace std;

struct Player {
    int id;
    string nombre;
    int nivel;
    string clase;
    int poder;
};

struct OrdenarPorID {
    bool operator()(const Player& a, const Player& b) const {
        return a.id < b.id;
    }
};

// Función para validar enteros positivos
int leerEnteroPositivo(string mensaje) {
    int valor;
    while (true) {
        cout << mensaje;
        if (cin >> valor && valor > 0) {
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            return valor;
        }
        cout << "Entrada inválida. Debe ser un número entero positivo.\n";
        cin.clear();
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
    }
}

// Leer cadena no vacía
string leerCadena(string mensaje) {
    string s;
    while (true) {
        cout << mensaje;
        getline(cin, s);
        if (!s.empty()) return s;
        cout << "El campo no puede estar vacío.\n";
    }
}

int main() {

    set<Player, OrdenarPorID> jugadores;       // Requiere <set>
    map<string, set<int>> jugadoresPorClase;   // Requiere <map> y <set>
    unordered_map<int, Player> accesoRapido;   // Requiere <unordered_map>

    while (true) {
        cout << "\n=============================\n";
        cout << "     MENU DE OPCIONES\n";
        cout << "=============================\n";
        cout << "1) Agregar jugador\n";
        cout << "2) Buscar jugador por ID\n";
        cout << "3) Mostrar jugadores por clase\n";
        cout << "4) Ordenar niveles y buscar uno\n";
        cout << "5) Filtrar jugadores por poder\n";
        cout << "6) Top 3 jugadores mas fuertes\n";
        cout << "7) Salir\n";
        cout << "Seleccione una opcion: ";

        int opcion;
        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            cout << "Opcion invalida.\n";
            continue;
        }
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');

        // -------------------------------------------
        // 1) AGREGAR JUGADOR
        // -------------------------------------------
        if (opcion == 1) {

            Player p;

            p.id = leerEnteroPositivo("ID del jugador: ");

            if (accesoRapido.count(p.id)) {
                cout << "Ya existe un jugador con ese ID.\n";
                continue;
            }

            p.nombre = leerCadena("Nombre: ");
            p.nivel = leerEnteroPositivo("Nivel (entero positivo): ");
            p.clase = leerCadena("Clase (Guerrero, Mago, Arquero): ");
            p.poder = leerEnteroPositivo("Poder: ");

            jugadores.insert(p);
            accesoRapido[p.id] = p;
            jugadoresPorClase[p.clase].insert(p.id);

            cout << "Jugador agregado correctamente.\n";
        }

        // -------------------------------------------
        // 2) BUSCAR POR ID
        // -------------------------------------------
        else if (opcion == 2) {

            if (accesoRapido.empty()) {
                cout << "No hay jugadores registrados.\n";
                continue;
            }

            int id = leerEnteroPositivo("Ingrese ID a buscar: ");

            if (accesoRapido.count(id)) {
                const Player& p = accesoRapido[id];
                cout << "\nJugador encontrado:\n";
                cout << "ID: " << p.id << " | Nombre: " << p.nombre
                     << " | Nivel: " << p.nivel << " | Clase: " << p.clase
                     << " | Poder: " << p.poder << endl;
            } else {
                cout << "No existe un jugador con ese ID.\n";
            }
        }

        // -------------------------------------------
        // 3) MOSTRAR POR CLASE
        // -------------------------------------------
        else if (opcion == 3) {

            if (jugadoresPorClase.empty()) {
                cout << "No hay clases ni jugadores registrados.\n";
                continue;
            }

            cout << "\n--- Jugadores por clase ---\n";
            for (const auto& par : jugadoresPorClase) {
                cout << par.first << ": ";
                if (par.second.empty()) {
                    cout << "(vacio)\n";
                } else {
                    for (int id : par.second) cout << id << " ";
                    cout << endl;
                }
            }
        }

        // -------------------------------------------
        // 4) ORDENAR NIVELES + BINARY_SEARCH
        // -------------------------------------------
        else if (opcion == 4) {

            if (jugadores.empty()) {
                cout << "No hay jugadores registrados.\n";
                continue;
            }

            vector<int> niveles;     // Uso de <vector>
            for (const auto& p : jugadores) niveles.push_back(p.nivel);

            sort(niveles.begin(), niveles.end()); // Uso de <algorithm>

            cout << "\nNiveles ordenados: ";
            for (int n : niveles) cout << n << " ";
            cout << endl;

            int nivelB = leerEnteroPositivo("Buscar nivel: ");

            bool existe = binary_search(niveles.begin(), niveles.end(), nivelB);

            cout << (existe ? "Nivel encontrado.\n" : "Nivel no encontrado.\n");
        }

        // -------------------------------------------
        // 5) FILTRAR POR PODER
        // -------------------------------------------
        else if (opcion == 5) {

            if (jugadores.empty()) {
                cout << "No hay jugadores registrados.\n";
                continue;
            }

            int minP = leerEnteroPositivo("Mostrar jugadores con poder mayor a: ");

            vector<Player> filtrados;

            copy_if(jugadores.begin(), jugadores.end(), back_inserter(filtrados),
                    [&](const Player& p) { return p.poder > minP; });

            if (filtrados.empty()) {
                cout << "No hay jugadores con poder mayor a " << minP << ".\n";
                continue;
            }

            cout << "\nJugadores filtrados:\n";
            for (const auto& p : filtrados) {
                cout << "- " << p.nombre << " | Poder: " << p.poder << endl;
            }
        }

        // -------------------------------------------
        // 6) TOP 3 JUGADORES MAS FUERTES
        // -------------------------------------------
        else if (opcion == 6) {

            if (jugadores.empty()) {
                cout << "No hay jugadores registrados.\n";
                continue;
            }

            vector<Player> lista(jugadores.begin(), jugadores.end());

            sort(lista.begin(), lista.end(),
                [](const Player& a, const Player& b) {
                    return a.poder > b.poder;
                });

            cout << "\n--- TOP 3 JUGADORES MAS FUERTES ---\n";
            for (int i = 0; i < 3 && i < lista.size(); i++) {
                cout << i + 1 << ") " << lista[i].nombre
                     << " - Poder: " << lista[i].poder << endl;
            }
        }

        // -------------------------------------------
        // SALIR
        // -------------------------------------------
        else if (opcion == 7) {
            cout << "Saliendo...\n";
            break;
        }

        else {
            cout << "Opcion invalida.\n";
        }
    }

    return 0;
}