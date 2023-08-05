package main

import (
	"fmt"
	"math"
	"math/rand"
	"os"
	"time"
)

// Implementación del algoritmo de ordenamiento MergeSort en Go
func mergeSort(array []int) {
	if len(array) > 1 {
		// r es el punto donde el array principal es dividido en dos sub-arrays
		r := len(array) / 2
		L := array[:r]
		M := array[r:]

		// Ordena las dos mitades
		mergeSort(L)
		mergeSort(M)

		i, j, k := 0, 0, 0

		// Hasta que se alcance cualquiera de los extremos de L o M se selecciona
		// los elementos L y M más grandes y se colocan en la posición correcta en array
		for i < len(L) && j < len(M) {
			if L[i] < M[j] {
				array[k] = L[i]
				i++
			} else {
				array[k] = M[j]
				j++
			}
			k++
		}

		// Cuando L o M se quedan sin elementos,
		// se recogen los elementos restantes y se colocan en array
		for i < len(L) {
			array[k] = L[i]
			i++
			k++
		}

		for j < len(M) {
			array[k] = M[j]
			j++
			k++
		}
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

	outputFile, err := os.Create("merge_sort_times.txt")
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
			mergeSort(data)
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

	fmt.Println("Experimentos completados y resultados guardados en 'merge_sort_times.txt'")
}
