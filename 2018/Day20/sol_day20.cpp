#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <utility>
#include <vector>

using std::cout;
using std::endl;

typedef std::pair<int32_t, int32_t> t_coord;
typedef std::map<t_coord, int32_t> t_map;

void GenerateMap(const std::string input, int32_t &idx, t_coord start, t_map &map);
t_coord MoveDirection(char dir);

int32_t Part1(const t_map &map);
int32_t Part2(const t_map &map);

int main() {
    std::ifstream fin("input_day20.dat");

    std::string input;
    std::getline(fin, input);

    t_map map;
    map.emplace(std::make_pair(0, 0), 0);


    int32_t idx = 1;
    GenerateMap(input, idx, std::make_pair(0, 0), map);

    cout << "Day 20, part 1: " << Part1(map) << endl;
    cout << "Day 20, part 2: " << Part2(map) << endl;

    return 0;
}

int32_t Part1(const t_map &map) {
    int32_t dist = 0;

    for(auto &k: map)
        if(k.second > dist)
            dist = k.second;
    
    return dist;
}

int32_t Part2(const t_map &map) {
    int32_t cnt = 0;

    for(auto &k: map)
        if(k.second >= 1000)
            cnt++;
    
    return cnt;
}

t_coord MoveDirection(char dir) {
    t_coord res = std::make_pair(0, 0);

    switch(dir) {
        case 'N':
            res.second = 1;
            break;
        case 'W':
            res.first = -1;
            break;
        case 'E':
            res.first = 1;
            break;
        case 'S':
            res.second = -1;
            break;
    }

    return res;
}

void GenerateMap(const std::string input, int32_t &idx, t_coord start, t_map &map) {
    std::vector<t_coord> stack;
    stack.clear();

    t_coord curr_coord = start;
    t_coord old_coord = start;
    t_coord delta = std::make_pair(0, 0);
    while(input[idx] != '$') {
        switch(input[idx]) {
            case 'N':
            case 'W':
            case 'E':
            case 'S':
                delta = MoveDirection(input[idx]);
                old_coord = curr_coord;
                curr_coord.first += delta.first;
                curr_coord.second += delta.second;
                if(map.find(curr_coord) != map.end()) {
                    if(map[old_coord] + 1 < map[curr_coord])
                        map[curr_coord] = map[old_coord] + 1;
                }
                else {
                    map.emplace(curr_coord, map[old_coord] + 1);
                }
                break;
            case '(':
                stack.push_back(curr_coord);
                break;
            case '|':
                curr_coord = *(stack.end() - 1);
                break;
            case ')':
                curr_coord = *(stack.end() - 1);
                stack.pop_back();
                break;
        }
        idx++;
    }

    return;
}