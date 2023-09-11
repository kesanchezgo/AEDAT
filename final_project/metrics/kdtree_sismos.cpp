#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>
#include <random>

struct Point {
    double x, y;
    Point(double x, double y) : x(x), y(y) {}
};

struct LabeledPoint {
    double x, y;
    int label;
    LabeledPoint(double x, double y, int label) : x(x), y(y), label(label) {}
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
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> latDist(-16.5000, -16.1000); // Latitud de Arequipa
    std::uniform_real_distribution<> lonDist(-71.7000, -71.2000); // Longitud de Arequipa
    std::vector<LabeledPoint> labeledPoints;

    int numPoints = 50; // Cantidad de puntos de ejemplo
    for (int i = 0; i < numPoints; ++i) {
        double lat = latDist(gen);
        double lon = lonDist(gen);
        int label = rand() % 2; // Genera etiquetas aleatorias (0 o 1)
        labeledPoints.push_back(LabeledPoint(lat, lon, label));
        tree.insert(Point(lat, lon));
    }

     // Definir el punto objetivo para la búsqueda de vecinos cercanos
    Point target(-16.409047, -71.537451); // Utiliza una de las coordenadas de Arequipa como objetivo

    int k = 5; // Número de vecinos cercanos a buscar
    std::vector<Point> kNearest = tree.findKNearest(target, k);

    std::cout << "Los " << k << " puntos más cercanos a (" << target.x << ", " << target.y << "):" << std::endl;
    for (const Point& nearest : kNearest) {
        std::cout << "Latitud: " << nearest.x << ", Longitud: " << nearest.y << std::endl;
    }

    int truePositives = 0;
int falsePositives = 0;
int falseNegatives = 0;

for (const LabeledPoint& labeledPoint : labeledPoints) {
    std::vector<Point> kNearest = tree.findKNearest(Point(labeledPoint.x, labeledPoint.y), k);

    int predictedLabel = 0; // Supongamos que inicialmente se predice como clase 0
    // Calcular la clase más común entre los k vecinos más cercanos
    int count0 = 0;
    int count1 = 0;
    for (const Point& nearest : kNearest) {
        // Encuentra la etiqueta correspondiente a este punto en los datos etiquetados
        for (const LabeledPoint& labeled : labeledPoints) {
            if (labeled.x == nearest.x && labeled.y == nearest.y) {
                if (labeled.label == 0) {
                    count0++;
                } else {
                    count1++;
                }
                break;
            }
        }
    }
    if (count1 > count0) {
        predictedLabel = 1;
    }

    // Comparar con la etiqueta real
    if (predictedLabel == labeledPoint.label) {
        if (predictedLabel == 1) {
            truePositives++;
        }
    } else {
        if (predictedLabel == 1) {
            falsePositives++;
        } else {
            falseNegatives++;
        }
    }
}

double precision = static_cast<double>(truePositives) / (truePositives + falsePositives);
double recall = static_cast<double>(truePositives) / (truePositives + falseNegatives);
double f1Score = 2 * (precision * recall) / (precision + recall);

std::cout << "Precision: " << precision << std::endl;
std::cout << "Recall: " << recall << std::endl;
std::cout << "F1-Score: " << f1Score << std::endl;
std::cout << "Accuracy: " << static_cast<double>(truePositives) / labeledPoints.size() << std::endl;

return 0;
}
