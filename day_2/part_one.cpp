#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

vector<int> parseLine(const string& line) {
    vector<int> numbers;
    stringstream ss(line);
    int num;
    while (ss >> num) {
        numbers.push_back(num);
    }
    return numbers;
}

bool isSafe(const vector<int>& report) {
    if (report.size() < 2) {
        return true;
    }

    bool increasing = report[1] > report[0];

    for (size_t i = 1; i < report.size(); ++i) {
        int diff = report[i] - report[i - 1];

        if (abs(diff) < 1 || abs(diff) > 3) {
            return false;
        }

        if ((increasing && report[i] < report[i - 1]) || (!increasing && report[i] > report[i - 1])) {
            return false;
        }
    }

    return true;
}

int main() {
    string filename = "file.txt";
    ifstream file(filename);

    if (!file) {
        cerr << "Error: Could not open file '" << filename << "'." << endl;
        return 1;
    }

    vector<string> full_file;
    string line;

    while (getline(file, line)) {
        full_file.push_back(line);
    }
    file.close();

    int safeCount = 0;

    for (const string& reportLine : full_file) {
        vector<int> report = parseLine(reportLine);

        if (isSafe(report)) {
            ++safeCount;
        }
    }

    cout << "Number of safe reports: " << safeCount << endl;

    return 0;
}
