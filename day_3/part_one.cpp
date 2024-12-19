#include "../include/includes.h"

using namespace std;

int main() {
    regex pattern(R"(mul\(\d{1,3},\d{1,3}\))");
    string filename = "list.txt";
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Could not open file '" << filename << "'." << endl;
        return 1;
    }

    vector<string> matches;
    string line;

    while (getline(file, line)) {
        auto words_begin = sregex_iterator(line.begin(), line.end(), pattern);
        auto words_end = sregex_iterator();
        for (auto it = words_begin; it != words_end; ++it) {
            matches.push_back(it->str());
        }
    }

    file.close();

    long total = 0;

    regex number_pattern(R"(\d{1,3})");
    for (const string& match : matches) {
        auto numbers_begin = sregex_iterator(match.begin(), match.end(), number_pattern);
        auto numbers_end = sregex_iterator();

        vector<int> captured_numbers;
        for (auto it = numbers_begin; it != numbers_end; ++it) {
            captured_numbers.push_back(stoi(it->str()));
        }

        if (captured_numbers.size() == 2) {
            total += (captured_numbers[0] * captured_numbers[1]);
        } else {
            cerr << "Error: Expected exactly two numbers in the command." << endl;
        }
    }

    cout << "Sum of Valid Equations: " << total << endl;

    return 0;
}