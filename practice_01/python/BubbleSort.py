import random
import time
import statistics

# Implementación del algoritmo de burbuja en Python
def bubbleSort(array):
    n = len(array)
    for i in range(n):
        # Realiza n-i-1 comparaciones en esta iteración, ya que los i elementos finales ya están en su lugar correcto
        for j in range(0, n - i - 1):
            # Compara los elementos adyacentes
            if array[j] > array[j + 1]:
                # Intercambia los elementos si no están en orden ascendente
                temp = array[j]
                array[j] = array[j + 1]
                array[j + 1] = temp

# Tamaños de entrada para los experimentos
input_sizes = [100, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 20000, 30000, 40000, 50000]
num_repeats = 5

with open("bubble_sort_times.txt", "w") as outputFile:
    # Iterar a través de los diferentes tamaños de entrada
    for size in input_sizes:
        times = [] # Almacenar tiempos para repeticiones

        print(f"Experimentando con tamaño de entrada: {size}")

        # Repetir el experimento varias veces
        for repeat in range(num_repeats):
            data = [random.randint(1, size) for _ in range(size)]

            print(f"Repetición {repeat + 1}/{num_repeats} - Datos generados: {data}")

            # Medir el tiempo antes y después de ejecutar el algoritmo
            start_time = time.time()
            bubbleSort(data)
            end_time = time.time()
            elapsed_time = end_time - start_time
            times.append(elapsed_time) # Almacenar el tiempo en segundos

            print(f"Repetición {repeat + 1}/{num_repeats} - Tiempo transcurrido: {elapsed_time:.6f} segundos")

        # Calcular el promedio y la desviación estándar de los tiempos
        if len(times) >= 2:
            avg_time = statistics.mean(times)
            std_dev = statistics.stdev(times)
        else:
            avg_time = times[0] if times else 0
            std_dev = 0

        # Escribir los resultados en el archivo
        outputFile.write(f"{size}\t{avg_time}\t{std_dev}\n")

        print(f"Experimento con tamaño de entrada {size} completado. Promedio de tiempo: {avg_time:.6f} segundos, Desviación estándar: {std_dev:.6f}")

print("Todos los experimentos completados y resultados guardados en 'bubble_sort_times.txt'")
