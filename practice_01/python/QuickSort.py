# Ordenamiento de Quiscksort
import random

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
      (array[i], array[j]) = (array[j], array[i])

  # Cambiar el elemento pivote con el elemento mayor especificado por i
  (array[i + 1], array[high]) = (array[high], array[i + 1])

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

data = []
size = 100
for i in range (size):
  data.append(random.randint(1,size))

print(data)

size2 = len(data)

quickSort(data, 0, size2 - 1)

print('Ordenamiento en orden ascendente:')
print(data)