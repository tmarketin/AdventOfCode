#include <cstdint>
#include <fstream>
#include <iostream>
#include <queue>
#include <regex>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using std::cout;
using std::endl;

typedef std::pair<int32_t, int32_t> t_coord;
typedef std::pair<int32_t, int32_t> t_limits;

class InputData {
public:
    char m_fc; // fixed coordinate, x or y
    int32_t m_fc_val; // fixed coord value
    t_limits m_range; // other coord range

    InputData(std::string in) {
        std::regex rgx(R"([xy=,.])");
    
        m_fc = in[0];
        std::istringstream iss(std::regex_replace(in, rgx, " "));
        iss >> m_fc_val >> m_range.first >> m_range.second;
    }

    friend std::ostream& operator<< (std::ostream &out, const InputData &inc);
};

std::ostream& operator<< (std::ostream &out, const InputData &inc)
{
    cout << inc.m_fc << " = " << inc.m_fc_val << ", " << (inc.m_fc == 'x' ? 'y' : 'x')
         << " = " << inc.m_range.first << " - " << inc.m_range.second << endl;
    return out;
}

class Map {
public:
    std::vector<std::vector<char>> m_map;
    t_coord m_source;
    t_coord m_min, m_max;
    std::pair<int32_t, int32_t> m_size;

    Map(std::vector<InputData> &ins) {
        m_source = std::make_pair(500, 0);
        t_limits range_x = (ins[0].m_fc == 'x' ? std::make_pair(ins[0].m_fc_val, ins[0].m_fc_val) : std::make_pair(ins[0].m_range.first, ins[0].m_range.first));
        t_limits range_y = (ins[0].m_fc == 'y' ? std::make_pair(ins[0].m_fc_val, ins[0].m_fc_val) : std::make_pair(ins[0].m_range.first, ins[0].m_range.first));

        for(const auto &k: ins) {
            if(k.m_fc == 'x') {
                if(k.m_fc_val < range_x.first)
                    range_x.first = k.m_fc_val;
                if(k.m_fc_val > range_x.second)
                    range_x.second = k.m_fc_val;
                if(k.m_range.first < range_y.first)
                    range_y.first = k.m_range.first;
                if(k.m_range.second > range_y.second)
                    range_y.second = k.m_range.second;
            }
            if(k.m_fc == 'y') {
                if(k.m_fc_val < range_y.first)
                    range_y.first = k.m_fc_val;
                if(k.m_fc_val > range_y.second)
                    range_y.second = k.m_fc_val;
                if(k.m_range.first < range_x.first)
                    range_x.first = k.m_range.first;
                if(k.m_range.second > range_x.second)
                    range_x.second = k.m_range.second;
            }
        }

//        cout << "Ranges: " << endl << range_x.first << ", " << range_x.second << endl;
//        cout << range_y.first << ", " << range_y.second << endl << endl;

        m_min = std::make_pair(range_x.first - 1, range_y.first - 1);
        m_max = std::make_pair(range_x.second, range_y.second);
        m_size = std::make_pair(m_max.first - m_min.first + 2, m_max.second - m_min.second + 1);

        for(auto &k: ins) {
            k.m_fc_val = k.m_fc_val - (k.m_fc == 'x' ? m_min.first : m_min.second);
            k.m_range.first = k.m_range.first - (k.m_fc == 'x' ? m_min.second : m_min.first);
            k.m_range.second = k.m_range.second - (k.m_fc == 'x' ? m_min.second : m_min.first);
        }

        m_map.resize(m_size.second);
        for(auto &k: m_map) {
            k.resize(m_size.first);
            std::fill(k.begin(), k.end(), '.');
        }

        for(const auto &k: ins) {
            for(int32_t idx = k.m_range.first; idx <= k.m_range.second; ++idx) {
                if(k.m_fc == 'x')
                    m_map[idx][k.m_fc_val] = '#';
                else
                    m_map[k.m_fc_val][idx] = '#';
            }
        }

        m_source.first -= m_min.first;
        m_map[m_source.second][m_source.first] = '+';
//        cout << "Source: " << m_source.first << ", " << m_source.second << endl;

    }

    void FillWater() {
        std::queue<t_coord> que;
        que.push(m_source);

        while(que.size() > 0) {
            t_coord curr_source = que.front();
            que.pop();

            // already under water
            if(m_map[curr_source.second][curr_source.first] != '+')
                continue;

            // flow down
            t_coord curr_bottom = curr_source;
            while(curr_bottom.second + 1 < m_size.second && m_map[curr_bottom.second + 1][curr_bottom.first] == '.') {
                curr_bottom.second++;
                m_map[curr_bottom.second][curr_bottom.first] = '|';
            }
            if(curr_bottom.second + 1 >= m_size.second || m_map[curr_bottom.second + 1][curr_bottom.first] == '+' || m_map[curr_bottom.second + 1][curr_bottom.first] == '-')
                continue;

            // fill with water
            t_limits lim;
            bool check_left = true;
            bool check_right = true;
            while(check_left && check_right) {
                lim.first = curr_bottom.first;
                lim.second = curr_bottom.first;

                // look left
                while(m_map[curr_bottom.second][lim.first - 1] != '#') {
                    lim.first--;
                    if(m_map[curr_bottom.second + 1][lim.first] == '.') {
                        que.push(std::make_pair(lim.first, curr_bottom.second));
                        m_map[curr_bottom.second][lim.first] = '+';
                        check_left = false;
                        break;
                    }
                }
                // look right
                while(m_map[curr_bottom.second][lim.second + 1] != '#') {
                    lim.second++;
                    if(m_map[curr_bottom.second + 1][lim.second] == '.') {
                        que.push(std::make_pair(lim.second, curr_bottom.second));
                        m_map[curr_bottom.second][lim.second] = '+';
                        check_right = false;
                        break;
                    }
                }

                // fill line
                if(check_left && check_right) {
                    for(int32_t idx = lim.first; idx <= lim.second; ++idx)
                        m_map[curr_bottom.second][idx] = '~';
                }
                else {
                    for(int32_t idx = lim.first + (check_left ? 0 : 1); idx < lim.second + (check_right ? 1 : 0); ++idx)
                        m_map[curr_bottom.second][idx] = '-';
                }
                curr_bottom.second--;
            }
        }

        return;
    }

    int32_t Part1() {
        int32_t s = 0;
        for(int32_t idx_row = 1; idx_row < m_size.second; ++idx_row)
            for(int32_t idx_col = 0; idx_col < m_size.first; ++idx_col)
                if(m_map[idx_row][idx_col] == '+' || m_map[idx_row][idx_col] == '-' || m_map[idx_row][idx_col] == '|' || m_map[idx_row][idx_col] == '~')
                    s++;
        return s;
    }

    int32_t Part2() {
        int32_t s = 0;
        for(int32_t idx_row = 1; idx_row < m_size.second; ++idx_row)
            for(int32_t idx_col = 0; idx_col < m_size.first; ++idx_col)
                if(m_map[idx_row][idx_col] == '~')
                    s++;
        return s;
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
    std::ifstream fin("input_day17.dat");
    std::vector<InputData> inputs;

    std::string line;
    while(std::getline(fin, line))
        inputs.push_back(InputData(line));

    Map map(inputs);
    map.FillWater();

    cout << "Day 17, part 1: " << map.Part1() << endl;
    cout << "Day 17, part 2: " << map.Part2() << endl;

    return 0;
}