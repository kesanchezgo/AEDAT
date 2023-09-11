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
    

    return 0;
}
