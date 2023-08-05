# Ordenamiento de MergeSort
import random
def mergeSort(array):
    if len(array) > 1:

        #  r es el punto donde el array principal es dividido en dos sub-arrays
        r = len(array)//2
        L = array[:r]
        M = array[r:]

        # Ordena las dos mitades
        mergeSort(L)
        mergeSort(M)

        i = j = k = 0

        # Hasta que se alcance cualquiera de los extremos de L o M se selecciona
        # los elementos L y M más grandes y se coloca en la posición correcta en A[p..r]
        while i < len(L) and j < len(M):
            if L[i] < M[j]:
                array[k] = L[i]
                i += 1
            else:
                array[k] = M[j]
                j += 1
            k += 1

        # Cuando L o M se qued sin elementos,
        # se recogen los elementos restamtes y se colocan en A[p..r]
        while i < len(L):
            array[k] = L[i]
            i += 1
            k += 1

        while j < len(M):
            array[k] = M[j]
            j += 1
            k += 1

# Driver program
if __name__ == '__main__':
  data = []
  size = 100
  for i in range (size):
    data.append(random.randint(1,size))

  print(data)

  mergeSort(data)

  print('Ordenamiento en orden ascendente:')
  print(data)