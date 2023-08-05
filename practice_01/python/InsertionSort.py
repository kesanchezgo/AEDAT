import random
import time
import statistics

# Implementación del algoritmo de ordenamiento de inserción en Python
def insertionSort(array):
    for step in range(1, len(array)):
        key = array[step]
        j = step - 1

        # Compara la llave con cada uno de los elementos a la izquierda hasta encontrar un elemento más pequeño que el
        while j >= 0 and key < array[j]:
            array[j + 1] = array[j]
            j = j - 1

        # Colocar la llave después del elemento justo más pequeño que él
        array[j + 1] = key

# Tamaños de entrada para los experimentos
input_sizes = [100, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 20000, 30000, 40000, 50000]
num_repeats = 5

with open("insertion_sort_times.txt", "w") as outputFile:
    # Iterar a través de los diferentes tamaños de entrada
    for size in input_sizes:
        times = [] # Almacenar tiempos para repeticiones

        # Repetir el experimento varias veces
        for _ in range(num_repeats):
            data = [random.randint(1, size) for _ in range(size)]

            # Medir el tiempo antes y después de ejecutar el algoritmo
            start_time = time.time()
            insertionSort(data)
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

print("Experimentos completados y resultados guardados en 'insertion_sort_times.txt'")
