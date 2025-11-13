#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Circle {
    double x, y, r;
};

bool isPointInCircle(double px, double py, const Circle& c) {
    double dx = px - c.x;
    double dy = py - c.y;
    return dx * dx + dy * dy <= c.r * c.r;
}

bool isPointInAllCircles(double px, double py, const vector<Circle>& circles) {
    for (const auto& circle : circles) {
        if (!isPointInCircle(px, py, circle)) {
            return false;
        }
    }
    return true;
}

void getBoundingBox(const vector<Circle>& circles, 
                    double& xMin, double& xMax, 
                    double& yMin, double& yMax) {
    xMin = circles[0].x - circles[0].r;
    xMax = circles[0].x + circles[0].r;
    yMin = circles[0].y - circles[0].r;
    yMax = circles[0].y + circles[0].r;
    
    for (const auto& circle : circles) {
        xMin = min(xMin, circle.x - circle.r);
        xMax = max(xMax, circle.x + circle.r);
        yMin = min(yMin, circle.y - circle.r);
        yMax = max(yMax, circle.y + circle.r);
    }
}

double monteCarlo(const vector<Circle>& circles, 
                  long long n, 
                  double xMin, double xMax, 
                  double yMin, double yMax) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> xDist(xMin, xMax);
    uniform_real_distribution<double> yDist(yMin, yMax);
    
    long long m = 0;
    
    for (long long i = 0; i < n; i++) {
        double x = xDist(gen);
        double y = yDist(gen);
        
        if (isPointInAllCircles(x, y, circles)) {
            m++;
        }
    }
    
    double rectArea = (xMax - xMin) * (yMax - yMin);
    return (double)m / n * rectArea;
}

#ifndef EXPERIMENTS_MODE
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    vector<Circle> circles(3);
    
    for (int i = 0; i < 3; i++) {
        cin >> circles[i].x >> circles[i].y >> circles[i].r;
    }
    
    double xMin, xMax, yMin, yMax;
    getBoundingBox(circles, xMin, xMax, yMin, yMax);
    
    long long n = 10000000;
    
    double area = monteCarlo(circles, n, xMin, xMax, yMin, yMax);
    
    cout << fixed << setprecision(20) << area << endl;
    
    return 0;
}
#endif

