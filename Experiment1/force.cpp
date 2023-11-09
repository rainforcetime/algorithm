#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>

using namespace std;

struct Point {
    int x;
    int y;
};

// 计算两点之间的斜率
double calculateSlope(const Point& a, const Point& b) {
    if (a.x == b.x) {
        return INFINITY; // 无穷大，垂直线段
    }
    return static_cast<double>(b.y - a.y) / (b.x - a.x);
}

// 检查点c是否在ab线段的左侧
bool isLeftTurn(const Point& a, const Point& b, const Point& c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x) > 0;
}

// 使用斜率方法解决凸包问题
void convexHullBySlope(vector<Point>& points, int numPoints) {
    int n = points.size();

    if (n < 3) {
        cout << "Convex hull cannot be formed" << endl;
        return;
    }

    vector<Point> convexHull;
    ofstream outFile;

    ostringstream filenameStream;
    filenameStream << "convex_hull_" << numPoints << "_points.txt";
    string outputFilename = filenameStream.str();

    outFile.open(outputFilename);

    for (int i = 0; i < n; i++) {
        Point a = points[i];
        bool onLeft = false, onRight = false;

        for (int j = 0; j < n; j++) {
            if (i != j) {
                Point b = points[j];
                double slope = calculateSlope(a, b);
                int leftCount = 0, rightCount = 0;

                for (int k = 0; k < n; k++) {
                    if (k != i && k != j) {
                        Point c = points[k];
                        if (isLeftTurn(a, b, c)) {
                            leftCount++;
                        } else {
                            rightCount++;
                        }
                    }
                }

                if (leftCount == n - 2 || rightCount == n - 2) {
                    if (slope == INFINITY) {
                        if (a.x < b.x) {
                            onRight = true;
                        } else {
                            onLeft = true;
                        }
                    } else if (a.x == b.x) {
                        if (a.y < b.y) {
                            onRight = true;
                        } else {
                            onLeft = true;
                        }
                    } else if (a.x < b.x) {
                        onLeft = true;
                    } else {
                        onRight = true;
                    }
                }
            }
        }

        if (onLeft && onRight) {
            convexHull.push_back(a);
        }
    }

    cout << "Convex hull points:" << endl;
    for (const Point& p : convexHull) {
        cout << "(" << p.x << ", " << p.y << ")" << endl;
        outFile << p.x << " " << p.y << endl;
    }

    outFile.close();
}

//int main() {
//    int n = 100000; // 假设有100个点
//    vector<Point> points(n);
//
//    // 从文件中读取点的数量和坐标并填充到点数组中
//    ifstream file("random_points_100000.txt");
//    if (!file.is_open()) {
//        cerr << "File open error" << endl;
//        return 1;
//    }
//
//    for (int i = 0; i < n; i++) {
//        if (!(file >> points[i].x >> points[i].y)) {
//            cerr << "File read error" << endl;
//            file.close();
//            return 1;
//        }
//    }
//
//    file.close();
//
//    convexHullBySlope(points, n);
//
//    return 0;
//}

