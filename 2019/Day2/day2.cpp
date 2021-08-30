#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>

using std::cout;
using std::endl;

typedef std::map<int32_t, int32_t> Data_t;

int32_t Part1(Data_t data);
int32_t Part2(Data_t data);

int32_t runProgram(Data_t data, int32_t noun, int32_t verb);
void printMap(Data_t &data);

int main() {
    std::ifstream fin("day2.dat");

    Data_t data;
    std::string line;
    int32_t idx = 0;
    while(getline(fin, line, ',')) {
        data.insert({idx++, std::stoi(line)});
    }

    cout << "Part 1: " << Part1(data) << endl;
    cout << "Part 2: " << Part2(data) << endl;

    return 0;
}

int32_t Part1(Data_t data) {
    return runProgram(data, 12, 2);
}

int32_t Part2(Data_t data) {
    for(int32_t noun = 0; noun <= 99; noun++) {
        for(int32_t verb = 0; verb <= 99; verb++) {
            if(runProgram(data, noun, verb) == 19690720) {
                return 100*noun + verb;
            }
        }
    }

    return 0;
}

int32_t runProgram(Data_t data, int32_t noun, int32_t verb) {
    size_t idx = 0;
    data[1] = noun;
    data[2] = verb;

    while(data[idx] != 99) {
        switch (data[idx]) {
            case 1:
                data[data[idx + 3]] = data[data[idx + 1]] + data[data[idx + 2]];
                idx += 4;
                break;
            case 2:
                data[data[idx + 3]] = data[data[idx + 1]]*data[data[idx + 2]];
                idx += 4;
                break;
            case 99:
            default:
                break;
        }

    }
    return data[0];
}

void printMap(Data_t &data) {
    for(auto const & item: data)
        cout << item.first << " " << item.second << endl;
    return;
}