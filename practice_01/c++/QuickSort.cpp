#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <ctime>
#include <numeric>
#include <cmath>

// función para intercambiar elementos
void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

// función para reorganizar el arreglo (encontrar el punto de partición)
int partition(int array[], int low, int high) {
    
  // seleccionar el elemento más a la derecha como pivote
  int pivote = array[high];
  
  // puntero para el elemento mayor
  int i = (low - 1);

  // recorrer cada elemento del arreglo
  // compararlos con el pivote
  for (int j = low; j < high; j++) {
    if (array[j] <= pivote) {
        
      // si se encuentra un elemento menor que el pivote
      // intercambiarlo con el elemento mayor señalado por i
      i++;
      
      // intercambiar el elemento en i con el elemento en j
      swap(&array[i], &array[j]);
    }
  }
  
  // intercambiar el pivote con el elemento mayor en i
  swap(&array[i + 1], &array[high]);
  
  // devolver el punto de partición
  return (i + 1);
}

void quickSort(int array[], int low, int high) {
  if (low < high) {
      
    // encontrar el elemento pivote de modo que
    // los elementos menores que el pivote estén a la izquierda del pivote
    // los elementos mayores que el pivote estén a la derecha del pivote
    int pi = partition(array, low, high);

    // llamada recursiva a la izquierda del pivote
    quickSort(array, low, pi - 1);

    // llamada recursiva a la derecha del pivote
    quickSort(array, pi + 1, high);
  }
}


int main() {
    std::vector<int> input_sizes = {100, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 20000, 30000, 40000, 50000};
    int num_repeats = 5;

    std::ofstream outputFile;
    outputFile.open("quick_sort_times.txt");

    for (int size : input_sizes) {
        std::vector<double> times;

        for (int i = 0; i < num_repeats; ++i) {
            int data[size];
            srand(time(0));
            for (int j = 0; j < size; ++j) {
                data[j] = rand() % size;
            }

            auto start_time = std::chrono::high_resolution_clock::now();
            quickSort(data, 0, size - 1);
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
