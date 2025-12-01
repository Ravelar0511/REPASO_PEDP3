//gestion de libros con struct anidado, map y vector, busqueda con find_if
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm> // find_if
using namespace std;

// ================================
// Structs
// ================================

struct Categoria {
    string nombre;
    string descripcion;
};

struct Libro {
    string titulo;
    string autor;
    int anio;
    Categoria categoria; // struct anidado
};

// ================================
// Función para agregar libro
// ================================

void agregarLibro(vector<Libro> &libros, map<int, Categoria> &categorias) {
    Libro l;
    int idCat;

    cout << "\n--- Registrar Libro ---\n";

    do {
        cout << "Título: ";
        getline(cin, l.titulo);
    } while (l.titulo.empty());

    do {
        cout << "Autor: ";
        getline(cin, l.autor);
    } while (l.autor.empty());

    do {
        cout << "Año (1900 - 2025): ";
        cin >> l.anio;
        cin.ignore();
    } while (l.anio < 1900 || l.anio > 2025);

    // Mostrar categorías
    cout << "\nCATEGORÍAS DISPONIBLES:\n";
    for (auto &c : categorias) {
        cout << c.first << ". " << c.second.nombre << "\n";
    }

    // Elegir categoría
    do {
        cout << "Seleccione ID de categoría: ";
        cin >> idCat;
        cin.ignore();
    } while (categorias.find(idCat) == categorias.end());

    l.categoria = categorias[idCat];

    libros.push_back(l);
}

// ================================
// Buscar libro con find_if
// ================================

void buscarLibro(const vector<Libro> &libros) {
    string buscar;

    cout << "\nIngrese título a buscar: ";
    getline(cin, buscar);

    auto it = find_if(libros.begin(), libros.end(),
        [&](const Libro &l){ return l.titulo == buscar; });

    if (it != libros.end()) {
        cout << "\n== LIBRO ENCONTRADO ==\n";
        cout << "Título: " << it->titulo << "\n";
        cout << "Autor: " << it->autor << "\n";
        cout << "Año: " << it->anio << "\n";
        cout << "Categoría: " << it->categoria.nombre << "\n";
    } else {
        cout << "\nNo se encontró el libro.\n";
    }
}

// ================================
// Mostrar libros
// ================================

void mostrarLibros(const vector<Libro> &libros) {
    cout << "\n=== LISTA DE LIBROS ===\n";

    for (size_t i = 0; i < libros.size(); i++) {
        cout << "\nLibro #" << i + 1 << "\n";
        cout << "Título: " << libros[i].titulo << "\n";
        cout << "Autor: " << libros[i].autor << "\n";
        cout << "Año: " << libros[i].anio << "\n";
        cout << "Categoría: " << libros[i].categoria.nombre << "\n";
        cout << "Descripción: " << libros[i].categoria.descripcion << "\n";
    }
}

// ================================
// MAIN
// ================================

int main() {

    vector<Libro> libros;
    map<int, Categoria> categorias;

    // Creación de categorías sin constantes
    categorias[1] = {"Fantasía", "Historias con elementos mágicos"};
    categorias[2] = {"Ciencia Ficción", "Tecnología y futuro"};
    categorias[3] = {"Terror", "Relatos de miedo"};

    int opcion;

    do {
        cout << "\n1. Agregar libro\n";
        cout << "2. Mostrar libros\n";
        cout << "3. Buscar libro\n";
        cout << "4. Salir\n";
        cout << "Opción: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: agregarLibro(libros, categorias); break;
            case 2: mostrarLibros(libros); break;
            case 3: buscarLibro(libros); break;
        }

    } while (opcion != 4);

    return 0;
}
