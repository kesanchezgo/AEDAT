import random
import time
import statistics

# Implementación del algoritmo de ordenamiento MergeSort en Python
def mergeSort(array):
    if len(array) > 1:

        # r es el punto donde el array principal es dividido en dos sub-arrays
        r = len(array)//2
        L = array[:r]
        M = array[r:]

        # Ordena las dos mitades
        mergeSort(L)
        mergeSort(M)

        i = j = k = 0

        # Hasta que se alcance cualquiera de los extremos de L o M se selecciona
        # los elementos L y M más grandes y se colocan en la posición correcta en A[p..r]
        while i < len(L) and j < len(M):
            if L[i] < M[j]:
                array[k] = L[i]
                i += 1
            else:
                array[k] = M[j]
                j += 1
            k += 1

        # Cuando L o M se quedan sin elementos,
        # se recogen los elementos restantes y se colocan en A[p..r]
        while i < len(L):
            array[k] = L[i]
            i += 1
            k += 1

        while j < len(M):
            array[k] = M[j]
            j += 1
            k += 1

# Tamaños de entrada para los experimentos
input_sizes = [100, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 20000, 30000, 40000, 50000]
num_repeats = 5

with open("merge_sort_times.txt", "w") as outputFile:
    # Iterar a través de los diferentes tamaños de entrada
    for size in input_sizes:
        times = [] # Almacenar tiempos para repeticiones

        # Repetir el experimento varias veces
        for _ in range(num_repeats):
            data = [random.randint(1, size) for _ in range(size)]

            # Medir el tiempo antes y después de ejecutar el algoritmo
            start_time = time.time()
            mergeSort(data)
            end_time = time.time()
            elapsed_time = end_time - start_time
            times.append(elapsed_time) # Almacenar el tiempo en segundos

        # Calcula el promedio y la desviación estándar solo si hay al menos dos valores
        if len(times) >= 2:
            avg_time = statistics.mean(times)
            std_dev = statistics.stdev(times)
        else:
            avg_time = times[0] if times else 0
            std_dev = 0
        
        # Escribir los resultados en el archivo
        outputFile.write(f"{size}\t{avg_time}\t{std_dev}\n")

print("Experimentos completados y resultados guardados en 'merge_sort_times.txt'")
