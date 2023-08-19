#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <numeric>
#include <cmath>

using namespace std;

struct City {
    int x;
    int y;
};

struct Route {
    vector<int> path;
    double fitness;
};

double calcularDistancia(const City& city1, const City& city2) {
    int dx = city1.x - city2.x;
    int dy = city1.y - city2.y;
    return sqrt(dx * dx + dy * dy);
}

Route generarRutaAleatoria(int numCiudades) {
    Route ruta;
    for (int i = 0; i < numCiudades; ++i) {
        ruta.path.push_back(i);
    }
    random_shuffle(ruta.path.begin(), ruta.path.end());
    return ruta;
}

void calcularAptitud(Route& ruta, const vector<City>& ciudades) {
    double distanciaTotal = 0.0;
    int numCiudades = ciudades.size();
    for (int i = 0; i < numCiudades - 1; ++i) {
        int indiceCiudad1 = ruta.path[i];
        int indiceCiudad2 = ruta.path[i + 1];
        distanciaTotal += calcularDistancia(ciudades[indiceCiudad1], ciudades[indiceCiudad2]);
    }
    distanciaTotal += calcularDistancia(ciudades[ruta.path[numCiudades - 1]], ciudades[ruta.path[0]]);
    ruta.fitness = distanciaTotal;
}

Route cruzamiento(const Route& padre1, const Route& padre2) {
    int numCiudades = padre1.path.size();
    Route hijo;
    int startPos = rand() % numCiudades;
    int endPos = rand() % numCiudades;

    for (int i = 0; i < numCiudades; ++i) {
        if (startPos < endPos && i > startPos && i < endPos) {
            hijo.path.push_back(padre1.path[i]);
        } else if (startPos > endPos && !(i < startPos && i > endPos)) {
            hijo.path.push_back(padre1.path[i]);
        } else {
            hijo.path.push_back(-1);
        }
    }

    for (int i = 0; i < numCiudades; ++i) {
        if (find(hijo.path.begin(), hijo.path.end(), padre2.path[i]) == hijo.path.end()) {
            for (int j = 0; j < numCiudades; ++j) {
                if (hijo.path[j] == -1) {
                    hijo.path[j] = padre2.path[i];
                    break;
                }
            }
        }
    }

    return hijo;
}

void mutar(Route& ruta, double mutationRate) {
    int numCiudades = ruta.path.size();
    for (int i = 0; i < numCiudades; ++i) {
        if ((double)rand() / RAND_MAX < mutationRate) {
            int indiceIntercambio = rand() % numCiudades;
            swap(ruta.path[i], ruta.path[indiceIntercambio]);
        }
    }
}

Route encontrarMejorRuta(const vector<Route>& poblacion) {
    double mejorAptitud = numeric_limits<double>::max();
    int mejorIndice = -1;
    int POPULATION_SIZE = poblacion.size();
    for (int i = 0; i < POPULATION_SIZE; ++i) {
        if (poblacion[i].fitness < mejorAptitud) {
            mejorAptitud = poblacion[i].fitness;
            mejorIndice = i;
        }
    }
    return poblacion[mejorIndice];
}

int main() {
    // Define las configuraciones de ciudades
    vector<int> configuracionesCiudades = {100, 200, 500, 1000};

    // Configuración del algoritmo genético
    const int MAX_GENERATIONS = 3;
    const double MUTATION_RATE = 0.1;

    // Configuración para medir el tiempo promedio y la desviación estándar
    const int NUM_EXECUTIONS = 5;

    // Inicializa el generador de números aleatorios
    random_device rd;
    mt19937 gen(rd());

    // Ejecuta el algoritmo genético para diferentes configuraciones de ciudades
    for (int numCiudades : configuracionesCiudades) {
        vector<City> ciudades(numCiudades);
        for (int i = 0; i < numCiudades; ++i) {
            ciudades[i].x = gen() % 1000;
            ciudades[i].y = gen() % 1000;
        }

        vector<double> tiemposEjecucion;
        for (int exec = 0; exec < NUM_EXECUTIONS; ++exec) {
            const int POPULATION_SIZE = 10;
            vector<Route> poblacion(POPULATION_SIZE);
            for (int i = 0; i < POPULATION_SIZE; ++i) {
                poblacion[i] = generarRutaAleatoria(numCiudades);
                calcularAptitud(poblacion[i], ciudades);
            }


            auto inicio = chrono::high_resolution_clock::now();

            // Iteraciones del algoritmo genético
            for (int generacion = 0; generacion < MAX_GENERATIONS; ++generacion) {
                vector<Route> nuevaPoblacion;

                // Genera descendencia a través de selección, cruzamiento y mutación
                for (int i = 0; i < numCiudades; ++i) {
                    Route padre1 = encontrarMejorRuta(poblacion);
                    Route padre2 = encontrarMejorRuta(poblacion);
                    Route hijo = cruzamiento(padre1, padre2);
                    mutar(hijo, MUTATION_RATE);
                    calcularAptitud(hijo, ciudades);
                    nuevaPoblacion.push_back(hijo);
                }

                // Reemplaza la antigua población con la nueva población
                poblacion = nuevaPoblacion;
            }

            auto fin = chrono::high_resolution_clock::now();
            chrono::duration<double> tiempoEjecucion = fin - inicio;
            tiemposEjecucion.push_back(tiempoEjecucion.count());
        }

        // Calcula el tiempo promedio y la desviación estándar
        double tiempoPromedio = accumulate(tiemposEjecucion.begin(), tiemposEjecucion.end(), 0.0) / NUM_EXECUTIONS;

        double sumaCuadrados = 0.0;
        for (double tiempo : tiemposEjecucion) {
            sumaCuadrados += pow(tiempo - tiempoPromedio, 2);
        }
        double desviacionEstandar = sqrt(sumaCuadrados / NUM_EXECUTIONS);

        // Imprime los resultados
        cout << "Configuración con " << numCiudades << " ciudades:" << endl;
        cout << "Tiempo promedio de ejecución: " << tiempoPromedio << " segundos" << endl;
        cout << "Desviación estándar de ejecución: " << desviacionEstandar << " segundos" << endl;
        cout << endl;
    }

    return 0;
}
