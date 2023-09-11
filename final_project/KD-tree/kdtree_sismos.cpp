#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>
#include <random>
#include <fstream>
#include <chrono>

struct Point {
    double x, y;
    double m;
    Point(double x, double y, double m) : x(x), y(y), m(m) {}
};

struct Node {
    Point point;
    Node* left;
    Node* right;
    Node(Point p) : point(p), left(nullptr), right(nullptr) {}
};

class KDTree {
public:
    KDTree() : root(nullptr) {}

    void insert(Point point) {
        root = insert(root, point, 0);
    }

    std::vector<Point> findKNearest(Point target, int k) {
        nearestPoints.clear();
        nearestDistances.clear();
        findKNearest(root, target, k, 0);
        return nearestPoints;
    }

private:
    Node* root;
    std::vector<Point> nearestPoints;
    std::vector<double> nearestDistances;

    Node* insert(Node* node, Point point, int depth) {
        if (node == nullptr) {
            return new Node(point);
        }

        int cd = depth % 2; // Alternating dimension (0 for x, 1 for y)

        if ((cd == 0 && point.x < node->point.x) || (cd == 1 && point.y < node->point.y)) {
            node->left = insert(node->left, point, depth + 1);
        } else {
            node->right = insert(node->right, point, depth + 1);
        }

        return node;
    }

    void findKNearest(Node* node, Point target, int k, int depth) {
        if (node == nullptr) {
            return;
        }

        double distance = calcDistance(node->point, target);

        if (nearestPoints.size() < k) {
            nearestPoints.push_back(node->point);
            nearestDistances.push_back(distance);
            adjustHeap(nearestDistances, nearestPoints, nearestPoints.size() - 1);
        } else if (distance < nearestDistances.front()) {
            nearestPoints[0] = node->point;
            nearestDistances[0] = distance;
            adjustHeap(nearestDistances, nearestPoints, 0);
        }

        int cd = depth % 2; // Alternating dimension (0 for x, 1 for y)

        if ((cd == 0 && target.x < node->point.x) || (cd == 1 && target.y < node->point.y)) {
            findKNearest(node->left, target, k, depth + 1);
        } else {
            findKNearest(node->right, target, k, depth + 1);
        }

        double splitDistance;
        if (cd == 0) {
            splitDistance = std::abs(target.x - node->point.x);
        } else {
            splitDistance = std::abs(target.y - node->point.y);
        }

        if (splitDistance < nearestDistances.front()) {
            if ((cd == 0 && target.x < node->point.x) || (cd == 1 && target.y < node->point.y)) {
                findKNearest(node->right, target, k, depth + 1);
            } else {
                findKNearest(node->left, target, k, depth + 1);
            }
        }
    }

    double calcDistance(Point a, Point b) {
        return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
    }

    void adjustHeap(std::vector<double>& distances, std::vector<Point>& points, int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (distances[index] < distances[parent]) {
                std::swap(distances[index], distances[parent]);
                std::swap(points[index], points[parent]);
                index = parent;
            } else {
                break;
            }
        }
    }
};

int main() {
    KDTree tree;
    // Generar datos de ejemplo para la ciudad de Arequipa
    //std::random_device rd;
    //std::mt19937 gen(rd());
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine gen(seed); // Usa el reloj del sistema como semilla
    std::uniform_real_distribution<> latDist(-16.5000, -16.1000); // Latitud de Arequipa
    std::uniform_real_distribution<> lonDist(-71.7000, -71.2000); // Longitud de Arequipa
    std::uniform_real_distribution<> magDist(5, 9); //Magnitud aleatoria entre 3.0 y 7.0

    int numPoints = 60; // Cantidad de puntos de ejemplo
    std::ofstream outputFile("temblores.csv"); // Abre un archivo para escribir datos

    for (int i = 0; i < numPoints; ++i) {
        double lat = latDist(gen);
        double lon = lonDist(gen);
        double mag = magDist(gen);
        tree.insert(Point(lat, lon, mag));

    }

     // Definir el punto objetivo para la búsqueda de vecinos cercanos
    Point target(-16.409047, -71.537451, 0); // Utiliza una de las coordenadas de Arequipa como objetivo

    int k = 6; // Número de vecinos cercanos a buscar
    std::vector<Point> kNearest = tree.findKNearest(target, k);

    /* std::cout << "Los " << k << " puntos más cercanos a (" << target.x << ", " << target.y << "):" << std::endl;
    for (const Point& nearest : kNearest) {
        std::cout << "Latitud: " << nearest.x << ", Longitud: " << nearest.y << std::endl;
    } */

    std::cout << "Cantidad de temblores cercanos al Centro Historico de Arequipa (-16.409, -71.5375): " << kNearest.size() << std::endl;
    std::cout << "Coordenadas de los " << k << " temblores mas cercanos:" << std::endl;
     outputFile << "Latitud" << "," << "Longitud" << "," << "Magnitud" << std::endl;
    for (const Point& nearest : kNearest) {
        std::cout << "Latitud: " << nearest.x << ", Longitud: " << nearest.y << ", Magnitud: " << nearest.m << std::endl;
         // Escribe las coordenadas y la magnitud en el archivo
        outputFile << nearest.x << "," << nearest.y << "," << nearest.m << std::endl;
    }
    outputFile.close(); // Cierra el archivo

    return 0;
}
