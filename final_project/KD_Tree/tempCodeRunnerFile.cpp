    std::cout << "Coordenadas de los " << k << " temblores más cercanos:" << std::endl;

    for (const Point& nearest : kNearest) {
        std::cout << "Latitud: " << nearest.x << ", Longitud: " << nearest.y << std::endl;
    }