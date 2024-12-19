#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <regex>
#include <set>
#include <cmath>
#include <stdexcept>
#include <climits>

std::string trim(const std::string& str) {
    size_t end = str.find_last_not_of(" \t");
    return (end == std::string::npos) ? "" : str.substr(0, end + 1);
}