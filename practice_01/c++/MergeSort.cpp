#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <ctime>
#include <numeric>
#include <cmath>

// Fusiona dos subarreglos L y M en arr
void merge(int arr[], int p, int q, int r) {
    // Crear L ← A[p..q] y M ← A[q+1..r]
    int n1 = q - p + 1;
    int n2 = r - q;

    int L[n1], M[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[p + i];
    for (int j = 0; j < n2; j++)
        M[j] = arr[q + 1 + j];

    // Mantener el índice actual de los subarreglos y el arreglo principal
    int i, j, k;
    i = 0;
    j = 0;
    k = p;

    // Hasta que alcancemos el final de L o M, seleccionamos el mayor entre
    // los elementos de L y M y los colocamos en la posición correcta en A[p..r]
    while (i < n1 && j < n2) {
        if (L[i] <= M[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = M[j];
            j++;
        }
        k++;
    }

    // Cuando nos quedamos sin elementos en L o M,
    // recogemos los elementos restantes y los colocamos en A[p..r]
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = M[j];
        j++;
        k++;
    }
}

// Divide el arreglo en dos subarreglos, los ordena y los fusiona
void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        // m es el punto donde el arreglo se divide en dos subarreglos
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        // Fusiona los subarreglos ordenados
        merge(arr, l, m, r);
    }
}


int main() {
    std::vector<int> input_sizes = {100, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 20000, 30000, 40000, 50000};
    int num_repeats = 5;

    std::ofstream outputFile;
    outputFile.open("merge_sort_times.txt");

    for (int size : input_sizes) {
        std::vector<double> times;

        for (int i = 0; i < num_repeats; ++i) {
            int data[size];
            srand(time(0));
            for (int j = 0; j < size; ++j) {
                data[j] = rand() % size;
            }

            auto start_time = std::chrono::high_resolution_clock::now();
            mergeSort(data, 0, size - 1);
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
