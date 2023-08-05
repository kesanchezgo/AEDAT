# Ordenamiento de inserción
import random
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

data = []
size = 100
for i in range (size):
  data.append(random.randint(1,size))

print(data)

insertionSort(data)

print('Ordenamiento en orden ascendente:')
print(data)