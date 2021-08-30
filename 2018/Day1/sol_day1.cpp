#include <cstdint>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>

using std::cout;
using std::endl;

int32_t Part1(std::vector<int32_t> &data_in);
int32_t Part2(std::vector<int32_t> &data_in);

int main() {
    std::vector<int32_t> data;

    std::ifstream fin("input_day1.dat");

    int k;
    while(fin >> k)
        data.push_back(k);

    cout << "Day 1, part 1: " << Part1(data) << endl;
    cout << "Day 1, part 2: " << Part2(data) << endl;

    return 0;
}

int32_t Part1(std::vector<int32_t> &data_in) {
    int32_t s = 0;

    for(int32_t k: data_in)
        s = s + k;
    
    return s;
}

int32_t Part2(std::vector<int32_t> &data_in) {
    std::set<int32_t> freq;

    int32_t curr_freq = data_in[0];
    int32_t idx = 1;
    while(freq.empty() || freq.find(curr_freq) == freq.end()) {
        freq.insert(curr_freq);
        curr_freq = curr_freq + data_in[idx];
        idx = (idx + 1) % data_in.size();
    }

    return curr_freq;
}