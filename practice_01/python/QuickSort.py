import random
import time
import statistics

# Función para encontrat la función de partición
def partition(array, low, high):
     # elegir el elementos más a la derecha como pivote
    pivot = array[high]

    # puntero para mayor elemento
    i = low - 1

    # atravesar todos los elementos para
    # comparar cada elemento con el pivote
    for j in range(low, high):
        if array[j] <= pivot:
            # Si se encuenta un elemento más pequeño que el pivote,
            # se cambia por el elemento mayor señalado por i
            i = i + 1
            # Cambio del elemento en i con el elemento j
            array[i], array[j] = array[j], array[i]

    # Cambiar el elemento pivote con el elemento mayor especificado por i
    array[i + 1], array[high] = array[high], array[i + 1]

    # devolver la posicion desde donde se realiza la partición
    return i + 1

# Función para realizar el ordenamiento rápido
def quickSort(array, low, high):
    if low < high:

        # Encuentra el elemento pivote tal que el elemento más pequeño
        # que el pivote esté a la izquierda y el elemento mayor que el pivote
        # esté a la derecha
        pi = partition(array, low, high)

        # método recursivo a la izquierda del pivote
        quickSort(array, low, pi - 1)

        # método recursivo a la derecha del pivote
        quickSort(array, pi + 1, high)

# Tamaños de entrada para los experimentos
input_sizes = [100, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 20000, 30000, 40000, 50000]
num_repeats = 5

with open("quick_sort_times.txt", "w") as outputFile:
    # Iterar a través de los diferentes tamaños de entrada
    for size in input_sizes:
        times = [] # Almacenar tiempos para repeticiones

        # Repetir el experimento varias veces
        for _ in range(num_repeats):
            data = [random.randint(1, size) for _ in range(size)]

            # Medir el tiempo antes y después de ejecutar el algoritmo
            start_time = time.time()
            quickSort(data, 0, size - 1)
            end_time = time.time()
            elapsed_time = end_time - start_time
            times.append(elapsed_time) # Almacenar el tiempo en segundos

        # Calcular el promedio y la desviación estándar de los tiempos
        if len(times) >= 2:
            avg_time = statistics.mean(times)
            std_dev = statistics.stdev(times)
        else:
            avg_time = times[0] if times else 0
            std_dev = 0

        # Escribir los resultados en el archivo
        outputFile.write(f"{size}\t{avg_time}\t{std_dev}\n")

print("Experimentos completados y resultados guardados en 'quick_sort_times.txt'")
