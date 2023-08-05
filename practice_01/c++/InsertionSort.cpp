#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <ctime>
#include <numeric>
#include <cmath>

// Implementación del algoritmo de inserción en C++
void insertionSort(int array[], int size) {
    for (int step = 1; step < size; step++) {
        int key = array[step];
        int j = step - 1;

         // Compara la llave con cada uno de los elementos a la izquierda hasta encontrar un elemento más pequeño que el
        while (key < array[j] && j >= 0) {
            array[j + 1] = array[j];
            --j;
        }
        array[j + 1] = key;
    }
}

int main() {
    std::vector<int> input_sizes = {100, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 20000, 30000, 40000, 50000};
    int num_repeats = 5;

    std::ofstream outputFile;
    outputFile.open("insertion_sort_times.txt");

    for (int size : input_sizes) {
        std::vector<double> times;

        for (int i = 0; i < num_repeats; ++i) {
            int data[size];
            srand(time(0));
            for (int j = 0; j < size; ++j) {
                data[j] = rand() % size;
            }

            auto start_time = std::chrono::high_resolution_clock::now();
            insertionSort(data, size);
            auto end_time = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed_time = end_time - start_time;
            times.push_back(elapsed_time.count());
        }

        double avg_time = std::accumulate(times.begin(), times.end(), 0.0) / num_repeats;
        double variance = 0.0;
        for (double time : times) {
            variance += std::pow(time - avg_time, 2);
        }
        double std_dev = std::sqrt(variance / num_repeats);

        outputFile << size << "\t" << avg_time << "\t" << std_dev << "\n";
    }

    outputFile.close();

    return 0;
}
