#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;


struct Libro {
    string titulo;
    string autor;
    int vecesPrestado;
    int copiasDisponibles;
    float indicePopularidad;
};


map<string, map<string, Libro>> bibliotecas;


void solicitarInformacionLibro(Libro& libro) {
    cout << "Ingrese el titulo: ";
    getline(cin, libro.titulo);

    cout << "Ingrese el autor: ";
    getline(cin, libro.autor);

    cout << "veces prestado: ";
    cin >> libro.vecesPrestado;

    cout << "copias disponibles: ";
    cin >> libro.copiasDisponibles;

    cin.ignore();
}


void calcularIndiceDePopularidad(Libro& libro) {
    libro.indicePopularidad =
        static_cast<float>(libro.vecesPrestado) / (libro.copiasDisponibles + 1);
}



void buscarLibrosPorPalabraClave(const map<string, map<string, Libro>>& bibliotecas,
                                 const string& palabraClave)
{
    cout << "\n RESULTADOS DE BUSQUEDA \n";

    for (const auto& parBib : bibliotecas) {
        const string& nombreBiblioteca = parBib.first;
        const auto& libros = parBib.second;

        for (const auto& parLibro : libros) {
            const Libro& libro = parLibro.second;

            if (libro.titulo.find(palabraClave) != string::npos ||
                libro.autor.find(palabraClave) != string::npos)
            {
                cout << "Biblioteca: " << nombreBiblioteca << endl;
                cout << "Titulo: " << libro.titulo << endl;
                cout << "Autor: " << libro.autor << endl;
                cout << "veces prestado: " << libro.vecesPrestado << endl;
                cout << "Copias disponibles: " << libro.copiasDisponibles << endl;
                cout << "indice popularidad: " << libro.indicePopularidad << "\n\n";
            }
        }
    }
}



void obtenerTop5LibrosMasPopulares(const map<string, map<string, Libro>>& bibliotecas) {
    vector<Libro> todosLosLibros;

    for (const auto& parBib : bibliotecas) {
        for (const auto& parLibro : parBib.second) {
            todosLosLibros.push_back(parLibro.second);
        }
    }

    sort(todosLosLibros.begin(), todosLosLibros.end(),
         [](const Libro& a, const Libro& b) {
            return a.indicePopularidad > b.indicePopularidad;
         });

    cout << "\n=== TOP 5 LIBROS MÁS POPULARES ===\n";

    int limite = min(5, (int)todosLosLibros.size());
    for (int i = 0; i < limite; i++) {
        const Libro& libro = todosLosLibros[i];
        cout << i + 1 << ". " << libro.titulo
             << " Popularidad: " << libro.indicePopularidad << endl;
    }
}



bool copiarLibroEntreBibliotecas(map<string, map<string, Libro>>& bibliotecas,const string& origen,
                                 const string& destino,const string& tituloLibro)
{
    if (bibliotecas.find(origen) == bibliotecas.end() ||
        bibliotecas.find(destino) == bibliotecas.end())
    {
        return false;
    }

    auto& librosOrigen = bibliotecas[origen];
    auto itLibro = librosOrigen.find(tituloLibro);

    if (itLibro == librosOrigen.end()) {
        return false;
    }

    bibliotecas[destino][tituloLibro] = itLibro->second;
    return true;
}


void menu() {
    int opcion;
    do {
        cout << "\n========= MENU PRINCIPAL =========\n";
        cout << "1. Agregar biblioteca\n";
        cout << "2. Agregar libro a biblioteca\n";
        cout << "3. Buscar libros por palabra clave\n";
        cout << "4. Mostrar Top 5 libros mas populares\n";
        cout << "5. Copiar un libro entre bibliotecas\n";
        cout << "6. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        if (opcion == 1) {
            string nombre;
            cout << "Ingrese nombre de la biblioteca: ";
            getline(cin, nombre);
            bibliotecas[nombre] = map<string, Libro>();

        } else if (opcion == 2) {
            string nombre;
            cout << "Biblioteca destino: ";
            getline(cin, nombre);

            if (bibliotecas.find(nombre) == bibliotecas.end()) {
                cout << "No existe esa biblioteca.\n";
                continue;
            }

            Libro libro;
            solicitarInformacionLibro(libro);
            calcularIndiceDePopularidad(libro);

            bibliotecas[nombre][libro.titulo] = libro;

        } else if (opcion == 3) {
            string clave;
            cout << "Ingrese palabra clave para buscar (titulo o autor): ";
            getline(cin, clave);
            buscarLibrosPorPalabraClave(bibliotecas, clave);

        } else if (opcion == 4) {
            obtenerTop5LibrosMasPopulares(bibliotecas);

        } else if (opcion == 5) {
            string origen, destino, titulo;
            cout << "Biblioteca origen: ";
            getline(cin, origen);
            cout << "Biblioteca destino: ";
            getline(cin, destino);
            cout << "Titulo del libro: ";
            getline(cin, titulo);

            if (copiarLibroEntreBibliotecas(bibliotecas, origen, destino, titulo)) {
                cout << "Libro copiado exitosamente.\n";
            } else {
                cout << "No fue posible copiar el libro.\n";
            }

        }

    } while (opcion != 6);
}


int main() {
    menu();
    return 0;
}
