#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;

typedef std::vector<int32_t> Data_t;

int32_t Part1(Data_t &data);
int32_t Part2(Data_t &data);

int32_t getFuelSimple(int32_t mass);
int32_t getFuelRecursive(int32_t mass);

int main() {
    Data_t data;

    std::ifstream fin("day1.dat");

    int32_t k;
    while(fin >> k)
        data.push_back(k);
    
    cout << "Part 1 result: " << Part1(data) << endl;
    cout << "Part 2 result: " << Part2(data) << endl;

    return 0;
}

int32_t Part1(Data_t &data) {
    int32_t res = 0;

    for(auto mass: data)
        res = res + getFuelSimple(mass);
    
    return res;
}

int32_t Part2(Data_t &data) {
    int32_t res = 0;

    for(auto mass: data)
        res = res + getFuelRecursive(mass);
        
    return res;
}

int32_t getFuelSimple(int32_t mass) {
    return mass/3 - 2;
}

int32_t getFuelRecursive(int32_t mass) {
    int32_t fuel = getFuelSimple(mass);
    int32_t remainingMass = fuel;

    while(remainingMass > 0) {
        remainingMass = remainingMass/3 - 2;
        if(remainingMass > 0)
            fuel = fuel + remainingMass;
    }

    return fuel;
}