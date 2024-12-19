#include "../include/includes.h"

using namespace std;

int main() {
    // Clear terminal
    system("clear");

    vector<string> lines;
    vector<string> leftList;
    vector<string> rightList;

    cout << "Preparing lists..." << endl;

    // Read the input file
    ifstream listFile("list.txt");
    string line;
    while (getline(listFile, line)) {
        lines.push_back(line);
    }

    cout << "Lists are ready." << endl;

    // Split the list into two lists
    for (const auto& line : lines) {
        size_t pos = line.find(" ");
        leftList.push_back(line.substr(0, pos));
        rightList.push_back(line.substr(pos + 1));
    }

    // Convert rightList to integers and count occurrences
    map<int, int> rightCount;
    for (const auto& numStr : rightList) {
        int num = stoi(numStr);
        rightCount[num]++;
    }

    // Calculate similarity score
    int totalScore = 0;
    for (const auto& numStr : leftList) {
        int num = stoi(numStr);
        if (rightCount.find(num) != rightCount.end()) {
            int occurrences = rightCount[num];
            totalScore += num * occurrences; // Multiply number by its occurrences
        }
    }

    // Print the similarity score
    cout << "Total Similarity Score: " << totalScore << endl;

    return 0;
}
