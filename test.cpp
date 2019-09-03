#include <iostream>
#include <list>
#include <string>

using namespace std;

list<pair<double, double>> loadCoordinates(const string &fileName) {
    list<pair<double, double>> result;

    return result;
}

bool calculateBestCircle(list<pair<double, double>> coords, double &x, double &y, double &r) {

    return true;
}


int main(int argc, char **argv) {

    if(argc < 2) {
        cout << "Coordinate file not specified. Usage: 'test <file.txt>'" << endl;
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