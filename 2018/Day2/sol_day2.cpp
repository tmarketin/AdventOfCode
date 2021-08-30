#include <algorithm>
#include <array>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <utility>

using std::cout;
using std::endl;

std::array<int32_t, 2> LetterCount(std::string &s);
std::pair<int32_t, int32_t> StringDistance(std::string str1, std::string str2);

int32_t Part1(std::map<std::string, std::array<int32_t, 2>> &data);
std::string Part2(std::map<std::string, std::array<int32_t, 2>> &data);

int main() {
    std::map<std::string, std::array<int32_t, 2>> dict;
    std::ifstream fin("input_day2.dat");

    std::string s;
    while(fin >> s)
        dict.emplace(s, LetterCount(s));
    
    cout << "Day 2, part 1: " << Part1(dict) << endl;
    cout << "Day 2, part 2: " << Part2(dict) << endl;

    return 0;
}

int32_t Part1(std::map<std::string, std::array<int32_t, 2>> &data) {
    int32_t cnt2 = 0;
    int32_t cnt3 = 0;

    for(auto &x: data) {
        if(x.second[0] > 0)
            cnt2++;
        if(x.second[1] > 0)
            cnt3++;
    }

    return cnt2*cnt3;
}

std::string Part2(std::map<std::string, std::array<int32_t, 2>> &data) {
    for(auto &el1: data) {
        for(auto &el2: data) {
            std::pair<int32_t, int32_t> dist = StringDistance(el1.first, el2.first);
            if(dist.first == 1) {
                return el2.first.substr(0, dist.second) + el2.first.substr(dist.second + 1);
            }
        }
    }

    return 0;
}

std::array<int32_t, 2> LetterCount(std::string &s) {
    std::array<int32_t, 2> res = {0, 0};

    for(char c = 'a'; c <= 'z'; c++) {
        int32_t count = std::count(s.begin(), s.end(), c);
        if(count == 2)
            res[0]++;
        else if(count ==3)
            res[1]++;
    }

    return res;
}

std::pair<int32_t, int32_t> StringDistance(std::string str1, std::string str2) {
    std::pair<int32_t, int32_t> res = {0, -1};

    for(int32_t idx = 0; idx < str1.length(); ++idx) {
        if(str1[idx] != str2[idx]) {
            res.first = res.first + 1;
            res.second = idx;
        }

        if(res.first == 2)
            return res;
    }

    return res;
}