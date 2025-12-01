#include <iostream>
#include <vector>
#include <string>
using namespace std;

// ======================
// Structs separados
// ======================

struct Categoria {
    string nombre;
    string descripcion;
};

struct Pelicula {
    string titulo;
    int anio;
    Categoria categoria; // struct anidado
};

// ======================
// Funciones
// ======================

void ingresarPelicula(vector<Pelicula> &peliculas) {
    Pelicula p;

    cout << "\n--- Registro de Película ---\n";

    // VALIDACIÓN DENTRO DE LA FUNCIÓN
    do {
        cout << "Título: ";
        getline(cin, p.titulo);
    } while (p.titulo.empty());

    do {
        cout << "Año (1900 - 2025): ";
        cin >> p.anio;
        cin.ignore();
    } while (p.anio < 1900 || p.anio > 2025);

    // Datos de la categoría
    do {
        cout << "Categoría: ";
        getline(cin, p.categoria.nombre);
    } while (p.categoria.nombre.empty());

    do {
        cout << "Descripción de categoría: ";
        getline(cin, p.categoria.descripcion);
    } while (p.categoria.descripcion.empty());

    peliculas.push_back(p);
}

void mostrarPeliculas(const vector<Pelicula> &peliculas) {
    cout << "\n===== LISTA DE PELÍCULAS =====\n";
    
    for (size_t i = 0; i < peliculas.size(); i++) {
        cout << "\nPelícula #" << i + 1 << "\n";
        cout << "Título: " << peliculas[i].titulo << "\n";
        cout << "Año: " << peliculas[i].anio << "\n";
        cout << "Categoría: " << peliculas[i].categoria.nombre << "\n";
        cout << "Descripción: " << peliculas[i].categoria.descripcion << "\n";
    }
}

int main() {
    vector<Pelicula> peliculas;
    int opcion;

    do {
        cout << "\n1. Agregar Película\n";
        cout << "2. Mostrar Películas\n";
        cout << "3. Salir\n";
        cout << "Opción: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                ingresarPelicula(peliculas);
                break;
            case 2:
                mostrarPeliculas(peliculas);
                break;
        }

    } while (opcion != 3);

    return 0;
}
