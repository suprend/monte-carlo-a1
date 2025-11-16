#define EXPERIMENTS_MODE
#include "main.cpp"
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;

const double S_EXACT = 0.9445171859;
const double SQRT_5_2 = sqrt(5.0) / 2.0;

pair<double, long long> monteCarloWithCount(const vector<Circle>& circles, 
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
    double area = (double)m / n * rectArea;
    
    return {area, m};
}

int main() {
    vector<Circle> circles(3);
    circles[0] = {1.0, 1.0, 1.0};
    circles[1] = {1.5, 2.0, SQRT_5_2};
    circles[2] = {2.0, 1.5, SQRT_5_2};
    
    vector<long long> nValues;
    for (long long n = 100; n <= 100000; n += 500) {
        nValues.push_back(n);
    }
    for (long long extra : {10000LL, 50000LL, 100000LL}) {
        if (find(nValues.begin(), nValues.end(), extra) == nValues.end()) {
            nValues.push_back(extra);
        }
    }
    sort(nValues.begin(), nValues.end());
    
    ofstream wideFile("data/results_wide.csv");
    ofstream tightFile("data/results_tight.csv");
    
    wideFile << "rect,N,M,S_est,abs_err,rel_err\n";
    tightFile << "rect,N,M,S_est,abs_err,rel_err\n";
    
    double wideXMin = 0.0, wideXMax = 3.12;
    double wideYMin = 0.0, wideYMax = 3.12;
    
    const double tightMin = 2.0 - SQRT_5_2; // точные границы пересечения по осям
    double tightXMin = tightMin, tightXMax = 2.0;
    double tightYMin = tightMin, tightYMax = 2.0;
    
    for (long long n : nValues) {
        auto [wideS, wideM] = monteCarloWithCount(circles, n, wideXMin, wideXMax, wideYMin, wideYMax);
        double wideAbsErr = abs(wideS - S_EXACT);
        double wideRelErr = wideAbsErr / S_EXACT;
        
        wideFile << fixed << setprecision(20);
        wideFile << "wide," << n << "," << wideM << "," << wideS << "," 
                 << wideAbsErr << "," << wideRelErr << "\n";
        
        auto [tightS, tightM] = monteCarloWithCount(circles, n, tightXMin, tightXMax, tightYMin, tightYMax);
        double tightAbsErr = abs(tightS - S_EXACT);
        double tightRelErr = tightAbsErr / S_EXACT;
        
        tightFile << fixed << setprecision(20);
        tightFile << "tight," << n << "," << tightM << "," << tightS << "," 
                  << tightAbsErr << "," << tightRelErr << "\n";
    }
    
    wideFile.close();
    tightFile.close();
    
    return 0;
}
