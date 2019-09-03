#include <iostream>
#include <list>
#include <string>
#include <fstream>
#include <cmath>
#include <cstdint>
#include <limits>

using namespace std;

list<pair<double, double>> loadCoordinates(const string &fileName) {
    list<pair<double, double>> result;

    ifstream file(fileName);

    while(!file.eof()) {
        string fullLine;
        getline(file, fullLine);
        //cout << "Line: '" << fullLine << "'" << endl;

        size_t tabPos = fullLine.find_first_of("\t");

        if(tabPos == string::npos) {
            cout << "  Invalid line: '" << fullLine << "'" << endl;
            continue;
        }

        string xCoord = fullLine.substr(0, tabPos);
        string yCoord = fullLine.substr(tabPos+1);
        //cout << " X str: '" << xCoord << "', Y str: '" << yCoord << "'" << endl;

        result.push_back(make_pair(stod(xCoord), stod(yCoord)));

    }

    return result;
}

double distanceToCircle(double a, double b, double r, double x, double y) {
    return pow(r - sqrt( pow(x - a, 2) + pow(y - b, 2) ), 2);
}

double calculateTotalDistance(const list<pair<double, double>> &coords, double a, double b, double r) {
    double ret = 0;


    for(const auto &p : coords) {
        auto x = p.first;
        auto y = p.second;
        double d = distanceToCircle(a, b, r, x, y);
        //cout << "  " << x << ":" << y << " -> " << d << endl;
        ret += d;
    }
    //cout << "Calculate circle distance (" << a << "," << b <<  "), r: " << r << ". Distance: " << ret << endl;
    return ret;
}

void calculateInitialCenter(const list<pair<double, double>> &coords, double &a, double &b) {
    double sx = 0, sy = 0;
    for(const auto &p : coords) {
        auto x = p.first;
        auto y = p.second;
        sx += x;
        sy += y;
    }
    a = sx / coords.size();
    b = sy / coords.size();

    cout << "calculateInitialCenter " << a << "," << b << endl;
}

void calculateInitialRadius(const list<pair<double, double>> &coords, double a, double b, double &r)
{
    r = 0;

    for(const auto &p : coords) {
        auto x = p.first;
        auto y = p.second;

        double d = sqrt(pow(x - a, 2) + pow(y - b, 2));

        r = max(d, r);
    }

    cout << "calculateInitialRadius (" << a << "," << b << ") : " << r << endl;

}

bool calculateBestCircle(const list<pair<double, double>> &coords, double &a, double &b, double &r) {

    const double STEP_RATIO = 0.999;

    cout << "Total points: " << coords.size() << endl;

    if(coords.empty()) {
        a = 0;
        b = 0;
        r = 0;
        return true;
    }

    calculateInitialCenter(coords, a, b);
    calculateInitialRadius(coords, a, b, r);

    double d = calculateTotalDistance(coords, a, b, r);

    double nr = r;
    double nd = d;

    long long iterations = 0;

    do {
        r = nr;
        d = nd;

        nr = r * STEP_RATIO;
        nd = calculateTotalDistance(coords, a, b, nr);

        iterations++;

    } while (nd < d && r > 0.0);

    cout << "Total iterations: " << iterations << endl;

    return true;
}


int main(int argc, char **argv) {

    if(argc < 2) {
        cout << "Coordinate file not specified. Usage: './test <file.txt>'" << endl;
        return 1;
    }

    cout << "Using file: '" << argv[1] << "'" << endl;

    auto coords = loadCoordinates(argv[1]);

    double x = 0, y = 0, r = 5;

    if(!calculateBestCircle(coords, x, y, r)) {
        cout << "Failed to calculate best matching circle!" << endl;
        return 2;        
    }

    cout << "Best matching circle at (" << x << ", " << y << "), radius: " << r << endl;

    return 0;
}