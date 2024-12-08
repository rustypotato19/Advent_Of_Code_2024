#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  // clear terminal
  system("clear");

  vector<string> lines;

  vector<string> leftList;
  vector<string> rightList;

  cout << "Preparing lists..." << endl;

  ifstream listFile("list.txt");

  string line;
  while (getline(listFile, line)) {
    lines.push_back(line);
  }

  cout << "Lists are ready." << endl;

  // split the list into two lists
  for (const auto &line : lines) {
    size_t pos = line.find(" ");
    leftList.push_back(line.substr(0, pos));
    rightList.push_back(line.substr(pos + 1));
  }

  // sort the lists
  cout << "Sorting lists..." << endl;
  sort(leftList.begin(), leftList.end());
  sort(rightList.begin(), rightList.end());
  cout << "Lists are sorted." << endl;

  // output the lists
  cout << "Outputting lists..." << endl;

  // find positive difference between the two lists
  vector<int> differences;

  for (int i = 0; i < lines.size(); i++) {

    int difference = stoi(leftList[i]) - stoi(rightList[i]);
    cout << leftList[i] << rightList[i] << " "
         << (difference < 0 ? -difference : difference) << endl;
    if (difference < 0) {
      difference = -difference;
    }
    differences.push_back(difference);
  }

  int totalDifference = 0;
  // get and print total difference
  for (const auto &item : differences) {
    totalDifference += item;
  }
  cout << "Total difference: " << totalDifference << endl;

  // close the files
  listFile.close();

  return 0;
}