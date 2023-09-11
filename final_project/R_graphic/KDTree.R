# Cargar las bibliotecas necesarias
library(leaflet)
library(readr)

# Leer los datos desde el archivo CSV
data <- read.csv("C:/Unidad/proyectos/OTROS/MAESTRIA/AEDAT/final_project/KD_Tree/temblores.csv", sep = ",")

# Visualizar una muestra de los datos leídos
head(data)

# Convertir la columna "Magnitud" a un vector numérico
data$Magnitud <- as.numeric(as.character(data$Magnitud))

# Crear un mapa
m <- leaflet(data) %>%
  addTiles() %>%
  addCircleMarkers(
    lng = ~Longitud,
    lat = ~Latitud,
    radius = ~Magnitud * 3,  # Ajusta el valor multiplicador según tu preferencia
    color = ~colorNumeric(palette = "Reds", domain = data$Magnitud)(Magnitud),
    label = ~Magnitud,  # Puedes mostrar la magnitud como etiqueta si lo deseas
    fill = TRUE,
    fillOpacity = 0.6
  )

# Coordenadas del Centro Histórico de Arequipa
centroHistoricoLat <- -16.409047
centroHistoricoLon <- -71.537451

# Agregar un marcador en el Centro Histórico
m <- m %>%
  addMarkers(
    lng = centroHistoricoLon,
    lat = centroHistoricoLat,
    label = "Centro Histórico de Arequipa"
  )

# Mostrar el mapa de calor con el marcador del Centro Histórico
m
