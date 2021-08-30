#include <cstdint>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>

using std::cout;
using std::endl;

std::string Part1(std::string data);
int32_t Part2(std::string data);


// refactor using stacks or one pass through string
int main() {
    std::string data;

    std::ifstream fin("input_day5.dat");
    std::getline(fin, data);

    std::string p1sol = Part1(data);
    cout << "Day 5, part 1: " << p1sol.size() << endl;
    cout << "Day 5, part 2: " << Part2(p1sol) << endl;

    return 0;
}

std::string Part1(std::string str) {
    int32_t old_len = 0;

    while(old_len != str.size()) {
        old_len = str.size();
        for(char c = 'a'; c <= 'z'; ++c) {
            std::regex rgx_left(std::string() + static_cast<char>(c) + static_cast<char>(c - 32));
            std::regex rgx_right(std::string() + static_cast<char>(c - 32) + static_cast<char>(c));
            str = std::regex_replace(std::regex_replace(str, rgx_left, ""), rgx_right, "");
        }
    }

    return str;
}

int32_t Part2(std::string data) {
    int32_t min_len = data.size();
    char min_char;
    for(char rmchar = 'a'; rmchar <= 'z'; ++rmchar) {
        std::regex rgx_element(std::string() + "[" + static_cast<char>(rmchar) + static_cast<char>(rmchar - 32) + "]");
        std::string str = std::regex_replace(data, rgx_element, "");
        int32_t curr_len = Part1(str).size();
        if(min_len > curr_len) {
            min_len = curr_len;
            min_char = rmchar;
        }
    }
    return min_len;
}