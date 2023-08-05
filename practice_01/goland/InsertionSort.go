package main

import (
	"fmt"
	"math"
	"math/rand"
	"os"
	"time"
)

// Implementación del algoritmo de ordenamiento de inserción en Go
func insertionSort(array []int) {
	for step := 1; step < len(array); step++ {
		key := array[step]
		j := step - 1

		// Compara la llave con cada uno de los elementos a la izquierda hasta encontrar un elemento más pequeño que el
		for j >= 0 && key < array[j] {
			array[j+1] = array[j]
			j = j - 1
		}

		// Colocar la llave después del elemento justo más pequeño que él
		array[j+1] = key
	}
}

// Función para calcular el promedio de un slice de float64
func calculateMean(data []float64) float64 {
	sum := 0.0
	for _, value := range data {
		sum += value
	}
	return sum / float64(len(data))
}

// Función para calcular la desviación estándar de un slice de float64
func calculateStdDev(data []float64, mean float64) float64 {
	sum := 0.0
	for _, value := range data {
		diff := value - mean
		sum += diff * diff
	}
	variance := sum / float64(len(data))
	return math.Sqrt(variance)
}

func main() {
	rand.Seed(time.Now().UnixNano())

	// Tamaños de entrada para los experimentos
	inputSizes := []int{100, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 20000, 30000, 40000, 50000}
	numRepeats := 5

	outputFile, err := os.Create("insertion_sort_times.txt")
	if err != nil {
		fmt.Println("Error al crear el archivo:", err)
		return
	}
	defer outputFile.Close()

	// Iterar a través de los diferentes tamaños de entrada
	for _, size := range inputSizes {
		var times []float64 // Almacenar tiempos para repeticiones

		// Repetir el experimento varias veces
		for i := 0; i < numRepeats; i++ {
			data := make([]int, size)
			for j := 0; j < size; j++ {
				data[j] = rand.Intn(size) + 1
			}

			// Medir el tiempo antes y después de ejecutar el algoritmo
			startTime := time.Now()
			insertionSort(data)
			endTime := time.Now()
			elapsedTime := endTime.Sub(startTime).Seconds()
			times = append(times, elapsedTime) // Almacenar el tiempo en segundos
		}

		// Calcular el promedio y la desviación estándar de los tiempos manualmente
		var avgTime float64
		var stdDev float64
		if len(times) >= 2 {
			avgTime = calculateMean(times)
			stdDev = calculateStdDev(times, avgTime)
		} else {
			if len(times) == 1 {
				avgTime = times[0]
			}
			stdDev = 0
		}

		// Escribir los resultados en el archivo
		outputFile.WriteString(fmt.Sprintf("%d\t%f\t%f\n", size, avgTime, stdDev))
	}

	fmt.Println("Experimentos completados y resultados guardados en 'insertion_sort_times.txt'")
}
