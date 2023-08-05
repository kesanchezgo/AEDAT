#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <ctime>
#include <numeric>
#include <cmath>

// Implementación del algoritmo de burbuja en C++
void bubbleSort(int array[], int size) {
    for (int step = 0; step < size; ++step) {
        for (int i = 0; i < size - step - 1; ++i) {
            // Compara dos elementos adyacentes
            if (array[i] > array[i + 1]) {
                // Intercambia los elementos si no están en orden ascendente
                int temp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;
            }
        }
    }
}

int main() {
    // Tamaños de entrada para los experimentos
    std::vector<int> input_sizes = {100, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 20000, 30000, 40000, 50000};
    int num_repeats = 5; // Número de repeticiones para obtener el promedio

    std::ofstream outputFile;
    outputFile.open("bubble_sort_times.txt"); // Abrir archivo para escritura

    // Iterar a través de los diferentes tamaños de entrada
    for (int size : input_sizes) {
        std::vector<double> times; // Almacenar tiempos para repeticiones

        // Repetir el experimento varias veces
        for (int i = 0; i < num_repeats; ++i) {
            int data[size];
            srand(time(0));

            // Generar datos aleatorios para el tamaño de entrada actual
            for (int j = 0; j < size; ++j) {
                data[j] = rand() % size;
            }

            // Medir el tiempo antes y después de ejecutar el algoritmo
            auto start_time = std::chrono::high_resolution_clock::now();
            bubbleSort(data, size);
            auto end_time = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed_time = end_time - start_time;
            times.push_back(elapsed_time.count()); // Almacenar el tiempo en segundos
        }

        // Calcular el promedio y la desviación estándar de los tiempos
        double avg_time = std::accumulate(times.begin(), times.end(), 0.0) / num_repeats;
        double variance = 0.0;
        for (double time : times) {
            variance += std::pow(time - avg_time, 2);
        }
        double std_dev = std::sqrt(variance / num_repeats);
        
        // Escribir los resultados en el archivo
        outputFile << size << "\t" << avg_time << "\t" << std_dev << "\n";
    }

    outputFile.close(); // Cerrar archivo

    return 0;
}
