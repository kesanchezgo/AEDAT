# Ordenamiento de burbuja
import random
def bubbleSort(array):

  # se accede a cada elemento de la matriz
  for i in range(len(array)):

    # Copara todos los elementos del array
    for j in range(0, len(array) - i - 1):

      # Compara los dos elementos adyacentes
      # cambiar > a < para ordenar en orden descendente
      if array[j] > array[j + 1]:

        # cambiando los elementos si
        # no están e orden correcto
        temp = array[j]
        array[j] = array[j+1]
        array[j+1] = temp


data = []
size = 100
for i in range (size):
  data.append(random.randint(1,size))

print(data)

bubbleSort(data)

print('Ordenamiento en orden ascendente:')
print(data)