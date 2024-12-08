#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <regex>

using namespace std;

int main() {
    regex mul_pattern(R"(mul\(\d{1,3},\d{1,3}\))");
    regex dont_pattern(R"(don't\(\))");
    regex do_pattern(R"(do\(\))");
    regex combined_pattern(R"(mul\(\d{1,3},\d{1,3}\)|don't\(\)|do\(\))");
    regex number_pattern(R"(\d{1,3})");

    string filename = "list.txt";
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Could not open file '" << filename << "'." << endl;
        return 1;
    }

    long total = 0;
    bool allow_mul = true;
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();

    std::sregex_iterator iter(content.begin(), content.end(), combined_pattern);
    std::sregex_iterator end;

    while (iter != end) {
        string match = iter->str();
        if (regex_match(match, dont_pattern)) {
            allow_mul = false;
        } else if (regex_match(match, do_pattern)) {
            allow_mul = true;
        } else if (allow_mul && regex_match(match, mul_pattern)) {
            std::sregex_iterator numbers_begin(match.begin(), match.end(), number_pattern);
            std::sregex_iterator numbers_end;

            vector<int> captured_numbers;
            for (std::sregex_iterator num_it = numbers_begin; num_it != numbers_end; ++num_it) {
                captured_numbers.push_back(stoi(num_it->str()));
            }

            if (captured_numbers.size() == 2) {
                total += (captured_numbers[0] * captured_numbers[1]);
            }
        }
        ++iter;
    }

    cout << total << endl;
    return 0;
}
