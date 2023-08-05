// Bubble sort en C++

#include <iostream>
#include<ctime>
using namespace std;

// perform bubble sort
void bubbleSort(int array[], int size) {

  // bucle para acceder a cada elemento del arreglo
  for (int step = 0; step < size; ++step) {
      
    // bucle para comparar elementos del arreglo
    for (int i = 0; i < size - step; ++i) {

      // comparar dos elementos adyacentes
      // cambiar > a < para ordenar en orden descendente
      if (array[i] > array[i + 1]) {

        //intercambio de elementos si los elementos no están en el orden deseado
        int temp = array[i];
        array[i] = array[i + 1];
        array[i + 1] = temp;
      }
    }
  }
}

// impresión arreglo
void printArray(int array[], int size) {
  for (int i = 0; i < size; ++i) {
    cout << " " << array[i];
  }
  cout << "\n";
}

int main() {

	const int size = 100;
  int data[size];
	srand(time(0));
  for(int i = 0; i < size; i++){
  	data[i] =  (rand() % size);
  }
  
  // encontrar la longitud del arreglo 
  int len = sizeof(data) / sizeof(data[0]);
  bubbleSort(data, len);
  len = sizeof(data) / sizeof(data[0]);
  cout << "Ordenamiento en orden ascendente:\n";  
  printArray(data, len);
}