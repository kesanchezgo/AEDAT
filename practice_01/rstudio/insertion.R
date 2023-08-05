# Cargar librerías necesarias
library(ggplot2)

# Cargar los datos de los archivos
go_insertion_data <- read.table("C:/Unidad/proyectos/OTROS/MAESTRIA/AEDAT/practice_01/goland/insertion_sort_times.txt")
cpp_insertion_data <- read.table("C:/Unidad/proyectos/OTROS/MAESTRIA/AEDAT/practice_01/c++/insertion_sort_times.txt")
py_insertion_data <- read.table("C:/Unidad/proyectos/OTROS/MAESTRIA/AEDAT/practice_01/python/insertion_sort_times.txt")

# Renombrar las columnas
colnames(go_insertion_data) <- c("Tamaño", "TiempoPromedio", "DesviacionEstandar")
colnames(cpp_insertion_data) <- c("Tamaño", "TiempoPromedio", "DesviacionEstandar")
colnames(py_insertion_data) <- c("Tamaño", "TiempoPromedio", "DesviacionEstandar")

# Combinar todos los datos en un solo data frame
all_data <- rbind(
  data.frame(leyenda = "Goland", go_insertion_data),
  data.frame(leyenda = "C++", cpp_insertion_data),
  data.frame(leyenda = "Python", py_insertion_data)
)

# Graficar los resultados usando ggplot2
ggplot(all_data, aes(x = Tamaño, y = TiempoPromedio, color = leyenda, group = leyenda)) +
  geom_line(size = 1) +
  geom_errorbar(aes(ymin = TiempoPromedio - DesviacionEstandar, ymax = TiempoPromedio + DesviacionEstandar), width = 0.1) +
  labs(x = "Tamaño de entrada", y = "Tiempo promedio (segundos)",
       title = "Comparación de Lenguajes - Insertion Sort") +
  scale_color_manual(values = c("blue", "red", "green")) +
  theme_minimal()
