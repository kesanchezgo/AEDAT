// Insertion sort in C++

#include <iostream>
#include<ctime>
using namespace std;

// Función para imprimir un arreglo
void printArray(int array[], int size) {
  for (int i = 0; i < size; i++) {
    cout << array[i] << " ";
  }
  cout << endl;
}

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
  const int size = 100;
  int data[size];
	srand(time(0));
  for(int i = 0; i < size; i++){
  	data[i] =  (rand() % size);
  }
  int len = sizeof(data) / sizeof(data[0]);
  insertionSort(data, len);
  cout << "Ordenamiento en orden ascendente::\n";
  printArray(data, len);
}