#include <array>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define FIELD_SIZE 50
#define MAP_SIZE (FIELD_SIZE + 2)

using std::cout;
using std::endl;

class Map {
public:
    std::array<std::array<char, MAP_SIZE>, MAP_SIZE> m_map;
    std::array<std::array<char, MAP_SIZE>, MAP_SIZE> m_initMap;

    Map(std::string str) {
        for(auto &k: m_map)
            std::fill(k.begin(), k.end(), '/');

        std::ifstream fin(str);

        std::string line;
        int32_t row = 1;
        while(std::getline(fin, line)) {
            for(int32_t idx = 1; idx <= FIELD_SIZE; ++idx)
                m_map[row][idx] = line[idx-1];
                row++;
        }

        m_initMap = m_map;

        return;
    }

    void Reset() {
        m_map = m_initMap;

        return;
    }

    int32_t CountAcres(int32_t row, int32_t col, char test) {
        int32_t cnt = 0;
        for(int32_t r = row - 1; r <= row + 1; ++r)
            for(int32_t c = col - 1; c <= col + 1; ++c)
                if(m_map[r][c] == test)
                    cnt++;
        
        return cnt;
    }

    void Iterate() {
        std::array<std::array<char, MAP_SIZE>, MAP_SIZE> tmpMap = m_map;

        for(int32_t row = 1; row <= FIELD_SIZE; ++row) {
            for(int32_t col = 1; col <= FIELD_SIZE; ++col) {
                if(tmpMap[row][col] == '.' && CountAcres(row, col, '|') >= 3)
                    tmpMap[row][col] = '|';
                else if(tmpMap[row][col] == '|' && CountAcres(row, col, '#') >= 3)
                    tmpMap[row][col] = '#';
                else if(tmpMap[row][col] == '#' && (CountAcres(row, col, '|') == 0 || CountAcres(row, col, '#') == 1))
                    tmpMap[row][col] = '.';
            }
        }
        m_map = tmpMap;

        return;
    }

    int32_t Part1(int32_t iterCount) {
        for(int32_t iter = 0; iter < iterCount; ++iter)
            this->Iterate();
        
        int32_t cnt_wood = 0;
        int32_t cnt_lumber = 0;
        for(int32_t row = 1; row <= FIELD_SIZE; ++row) {
            for(int32_t col = 1; col <= FIELD_SIZE; ++col) {
                if(m_map[row][col] == '|')
                    cnt_wood++;
                if(m_map[row][col] == '#')
                    cnt_lumber++;
            }
        }

        return cnt_wood*cnt_lumber;
    }

    int32_t Part2(int64_t iterCount) {
        std::vector<int32_t> values;

        values.push_back(Part1(0));
        int32_t tmpVal;
        int32_t dist, first;
        bool check = false;
        while(! check) {
            tmpVal = Part1(1);
            auto it = values.end();
            for(it = values.end() - 1; it != values.begin(); --it) {
                if(*it == tmpVal) {
                    check = true;
                    break;
                }
            }
            if(check && (*(it - 1) == *(values.end() - 1)) && (*(it - 2) == *(values.end() - 2))) {
                first = std::distance(values.begin(), it);
                dist = std::distance(it, values.end());
                break;
            }
            else {
                check = false;
                values.push_back(tmpVal);
            }
        }

        return values[first + ((iterCount - first) % dist)];
    }

    friend std::ostream& operator<< (std::ostream &out, const Map &map);
};

std::ostream& operator<< (std::ostream &out, const Map &map)
{
    for(auto &k: map.m_map) {
        std::copy(k.begin(), k.end(), std::ostream_iterator<char>(std::cout, ""));
        cout << endl;
    }
    return out;
}

int main() {
    Map map("input_day18.dat");

    cout << "Day 18, part 1: " << map.Part1(10) << endl;
    map.Reset();
    cout << "Day 18, part 2: " << map.Part2(1000000000) << endl;


    return 0;
}
