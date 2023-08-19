#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <numeric>
#include <algorithm>

const int numIterations = 5; // Número de iteraciones
const int numAnts = 20;

std::vector<std::vector<double>> distance; // Matriz de distancias entre ciudades
std::vector<std::vector<double>> pheromones; // Matriz de feromonas entre ciudades

double alpha = 1.0; // Peso de la visibilidad
double beta = 2.0;  // Peso de las feromonas

double rho = 0.1;   // Tasa de evaporación de feromonas

// Inicialización de la matriz de distancias y de feromonas (puedes personalizar esto)
void initialize(int numCities) {
   // Inicializar la matriz de distancias con valores ficticios
    for (int i = 0; i < numCities; ++i) {
        for (int j = 0; j < numCities; ++j) {
            distance[i][j] = i != j ? (i + 1) * 10 + (j + 1) * 5 : 0;
        }
    }

    // Inicializar la matriz de feromonas con un valor inicial (por ejemplo, 0.1)
    for (int i = 0; i < numCities; ++i) {
        for (int j = 0; j < numCities; ++j) {
            pheromones[i][j] = 0.1;
        }
    }
}

// Función para calcular la probabilidad de moverse de una ciudad a otra
double calculateProbability(int fromCity, int toCity, const std::vector<bool>& visited) {
    double visibility = 1.0 / distance[fromCity][toCity];
    double pheromone = pow(pheromones[fromCity][toCity], alpha);
    
    return visibility * pheromone;
}

// Función para seleccionar la siguiente ciudad basada en las probabilidades
int selectNextCity(int ant, int currentCity, const std::vector<bool>& visited, int numCities) {
    double totalProbabilities = 0.0;
    std::vector<double> probabilities(numCities, 0.0);

    for (int i = 0; i < numCities; ++i) {
        if (!visited[i]) {
            probabilities[i] = calculateProbability(currentCity, i, visited);
            totalProbabilities += probabilities[i];
        }
    }

    double randomValue = (double)rand() / RAND_MAX * totalProbabilities;
    double cumulativeProb = 0.0;

    for (int i = 0; i < numCities; ++i) {
        if (!visited[i]) {
            cumulativeProb += probabilities[i];
            if (cumulativeProb >= randomValue) {
                return i;
            }
        }
    }

    // Si algo sale mal, simplemente seleccionamos la primera ciudad no visitada
    for (int i = 0; i < numCities; ++i) {
        if (!visited[i]) {
            return i;
        }
    }

    return -1; // No deberíamos llegar aquí
}

// Función para actualizar las feromonas después de cada iteración
void updatePheromones(const std::vector<std::vector<int>>& antPaths, int numCities) {
    for (int i = 0; i < numCities; ++i) {
        for (int j = 0; j < numCities; ++j) {
            pheromones[i][j] *= (1.0 - rho);
        }
    }

    for (int ant = 0; ant < numAnts; ++ant) {
        double contribution = 1.0 / distance[antPaths[ant][numCities - 1]][antPaths[ant][0]];
        for (int i = 0; i < numCities - 1; ++i) {
            contribution += 1.0 / distance[antPaths[ant][i]][antPaths[ant][i + 1]];
        }

        for (int i = 0; i < numCities - 1; ++i) {
            pheromones[antPaths[ant][i]][antPaths[ant][i + 1]] += contribution;
        }
        pheromones[antPaths[ant][numCities - 1]][antPaths[ant][0]] += contribution;
    }
}

int main() {
    srand(time(nullptr));

    std::vector<int> numCitiesList = {100, 200, 500,1000};

    for (int numCities : numCitiesList) {
        distance.assign(numCities, std::vector<double>(numCities, 0.0));
        pheromones.assign(numCities, std::vector<double>(numCities, 0.1));

        initialize(numCities);

        std::vector<std::vector<int>> antPaths(numAnts, std::vector<int>(numCities));
        std::vector<int> bestPath;
        double bestDistance = 1e9; // Inicializar con un valor grande

        std::vector<double> executionTimes;

        for (int iteration = 0; iteration < numIterations; ++iteration) {
            auto startTime = std::chrono::high_resolution_clock::now();
            for (int ant = 0; ant < numAnts; ++ant) {
                std::vector<bool> visited(numCities, false);
                int currentCity = rand() % numCities;
                antPaths[ant][0] = currentCity;
                visited[currentCity] = true;

                for (int i = 1; i < numCities; ++i) {
                    int nextCity = selectNextCity(ant, currentCity, visited, numCities);
                    antPaths[ant][i] = nextCity;
                    visited[nextCity] = true;
                    currentCity = nextCity;
                }
            }

            // Actualizar la mejor solución encontrada
            for (int ant = 0; ant < numAnts; ++ant) {
                double totalDistance = 0.0;
                for (int i = 0; i < numCities - 1; ++i) {
                    totalDistance += distance[antPaths[ant][i]][antPaths[ant][i + 1]];
                }
                totalDistance += distance[antPaths[ant][numCities - 1]][antPaths[ant][0]];

                if (totalDistance < bestDistance) {
                    bestDistance = totalDistance;
                    bestPath = antPaths[ant];
                }
            }
        
            auto endTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duration = endTime - startTime;
            executionTimes.push_back(duration.count());

            updatePheromones(antPaths,numCities);
        }

        // Calcular estadísticas de tiempo
        double meanTime = std::accumulate(executionTimes.begin(), executionTimes.end(), 0.0) / executionTimes.size();
        double sumOfSquares = std::inner_product(executionTimes.begin(), executionTimes.end(), executionTimes.begin(), 0.0);
        double stdDeviation = std::sqrt(sumOfSquares / executionTimes.size() - meanTime * meanTime);

        // Imprimir resultados para esta cantidad de ciudades
        std::cout << "Cantidad de ciudades: " << numCities << std::endl;
        std::cout << "Tiempo medio: " << meanTime << " segundos" << std::endl;
        std::cout << "Desviación estándar: " << stdDeviation << " segundos" << std::endl;
        //std::cout << "Mejor distancia: " << bestDistance << std::endl;
        //std::cout << "Mejor recorrido:";
        for (int city : bestPath) {
            //std::cout << " " << city;
        }
        std::cout << std::endl;
    }

    return 0;
}
