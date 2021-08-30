#include <array>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <vector>

#define FIELD_SIZE 1000

using std::cout;
using std::endl;

class InputElement{
private:
    int32_t id;
    int32_t offset_x, offset_y;
    int32_t size_x, size_y;

public:
    InputElement(std::string &str) {
        std::regex rgx1("[#@:,x]");
        std::string out = std::regex_replace(str, rgx1, " ");

        std::istringstream iss(out);
        iss >> this->id >> this->offset_x >> this->offset_y >> this->size_x >> this->size_y;
    }

    void Print() {
        cout << this->id << "\n" << this->offset_x << " " << this->offset_y << "\n" << this->size_x 
             << " " << this->size_y << endl;

        return;
    }

    void Fill(int32_t f_num[FIELD_SIZE][FIELD_SIZE], int32_t f_id[FIELD_SIZE][FIELD_SIZE], std::vector<int32_t> &overlap) {
        for(int32_t col = this->offset_x; col <= this->offset_x + this->size_x - 1; ++col)
            for(int32_t row = this->offset_y; row <= this->offset_y + this->size_y - 1; ++row) {
                f_num[row][col]++;
                if(f_id[row][col] != 0) {
                    overlap[f_id[row][col] - 1] = 1;
                    overlap[this->id - 1] = 1;
                }
                f_id[row][col] = this->id;
            }
    }
};

void PrintField(int32_t f[FIELD_SIZE][FIELD_SIZE]);

int32_t Part1(int32_t f[FIELD_SIZE][FIELD_SIZE]);
int32_t Part2(std::vector<int32_t> &overlap);

int main() {
    int32_t field_num[FIELD_SIZE][FIELD_SIZE] = {0};
    int32_t field_id[FIELD_SIZE][FIELD_SIZE] = {0};

    std::string line;
    std::vector<InputElement> data;
    std::vector<int32_t> overlap;

    std::ifstream fin("input_day3.dat");

    while(std::getline(fin, line)) {
        data.push_back(InputElement(line));
        overlap.push_back(0);
    }
    
    for(auto &x: data)
        x.Fill(field_num, field_id, overlap);

    cout << "Day 3, part 1: " << Part1(field_num) << endl;
    cout << "Day 3, part 2: " << Part2(overlap) << endl;

    return 0;
}

int32_t Part1(int32_t f[FIELD_SIZE][FIELD_SIZE]) {
    int32_t s = 0;

    for(int32_t col = 0; col < FIELD_SIZE; ++col)
        for(int32_t row = 0; row < FIELD_SIZE; ++row)
            if(f[row][col] > 1)
                s++;
    return s;
}

int32_t Part2(std::vector<int32_t> &overlap) {
    for(int32_t idx = 0; idx < overlap.size(); ++idx)
        if(overlap[idx] == 0)
            return idx + 1;
    
    return 0;
}

void PrintField(int32_t f[FIELD_SIZE][FIELD_SIZE]) {
    for(int32_t row = 0; row < FIELD_SIZE; ++row) {
        for(int32_t col = 0; col < FIELD_SIZE; ++col)
            cout << f[row][col];
        cout << endl;
    }

    return;
}