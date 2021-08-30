#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <utility>
#include <vector>

using std::cout;
using std::endl;

typedef std::vector<std::vector<char>> t_map;
typedef std::pair<int32_t, int32_t> t_pos;

class Cart {
public:
    int32_t m_posx, m_posy;
    char m_dir;
    char m_turn;
    int32_t m_id;

    Cart(int32_t px, int32_t py, char dr, int32_t id) {
        m_posx = px;
        m_posy = py;
        m_turn = 'L';
        m_id = id;

        switch(dr) {
            case '>':
                m_dir = 'E';
                break;
            case 'v':
                m_dir = 'S';
                break;
            case '^':
                m_dir = 'N';
                break;
            case '<':
                m_dir = 'W';
                break;
        }
    }

    void MoveNext(const t_map &map) {
        switch(m_dir) {
            case 'N':
                m_posy--;
                switch(map[m_posy][m_posx]) {
                    case '/':
                        m_dir = 'E';
                        break;
                    case '\\':
                        m_dir = 'W';
                        break;
                    case '+':
                        switch(m_turn) {
                            case 'L':
                                m_dir = 'W';
                                m_turn = 'S';
                                break;
                            case 'S':
                                m_dir = 'N';
                                m_turn = 'R';
                                break;
                            case 'R':
                                m_dir = 'E';
                                m_turn = 'L';
                                break;
                        }
                        break;
                }
                break;
            case 'E':
                m_posx++;
                switch(map[m_posy][m_posx]) {
                    case '/':
                        m_dir = 'N';
                        break;
                    case '\\':
                        m_dir = 'S';
                        break;
                    case '+':
                        switch(m_turn) {
                            case 'L':
                                m_dir = 'N';
                                m_turn = 'S';
                                break;
                            case 'S':
                                m_dir = 'E';
                                m_turn = 'R';
                                break;
                            case 'R':
                                m_dir = 'S';
                                m_turn = 'L';
                                break;
                        }
                        break;
                }                
                break;
            case 'S':
                m_posy++;
                switch(map[m_posy][m_posx]) {
                    case '/':
                        m_dir = 'W';
                        break;
                    case '\\':
                        m_dir = 'E';
                        break;
                    case '+':
                        switch(m_turn) {
                            case 'L':
                                m_dir = 'E';
                                m_turn = 'S';
                                break;
                            case 'S':
                                m_dir = 'S';
                                m_turn = 'R';
                                break;
                            case 'R':
                                m_dir = 'W';
                                m_turn = 'L';
                                break;
                        }
                        break;
                }                
                break;
            case 'W':
                m_posx--;
                switch(map[m_posy][m_posx]) {
                    case '/':
                        m_dir = 'S';
                        break;
                    case '\\':
                        m_dir = 'N';
                        break;
                    case '+':
                        switch(m_turn) {
                            case 'L':
                                m_dir = 'S';
                                m_turn = 'S';
                                break;
                            case 'S':
                                m_dir = 'W';
                                m_turn = 'R';
                                break;
                            case 'R':
                                m_dir = 'N';
                                m_turn = 'L';
                                break;
                        }
                        break;
                }                
                break;
        }
    }

    bool operator < (const Cart &extcart) const {
        return (m_posy < extcart.m_posy || (m_posy == extcart.m_posy && m_posx < extcart.m_posx));
    }

    bool operator == (const Cart &extcart) const {
        return (m_posy == extcart.m_posy && m_posx == extcart.m_posx);
    }
};

void PrintMap(const t_map &rmap, const std::vector<Cart> &carts);

t_pos Part1(const t_map &rmap, std::vector<Cart> carts);
t_pos Part2(const t_map &rmap, std::vector<Cart> carts);

int main() {
    std::vector<Cart> carts;
    t_map railroad_map;

    std::ifstream fin("input_day13.dat");
    std::string line;
    std::vector<char> tmpline;
    int32_t cnt_y = 0;
    int32_t cart_id = 1;
    while(std::getline(fin, line)) {
        tmpline.clear();
        for(int32_t idx = 0; idx < line.size(); ++idx) {
            if(line[idx] == '<' || line[idx] == '>') {
                carts.push_back(Cart(idx, cnt_y, line[idx], cart_id));
                tmpline.push_back('-');
                cart_id++;
            }
            else if(line[idx] == 'v' || line[idx] == '^') {
                carts.push_back(Cart(idx, cnt_y, line[idx], cart_id));
                tmpline.push_back('|');
                cart_id++;
            }
            else {
                tmpline.push_back(line[idx]);
            }
        }
        railroad_map.push_back(tmpline);
        cnt_y++;
    }

    t_pos p1 = Part1(railroad_map, carts);
    cout << "Day 13, part 1: " << p1.first << " " << p1.second << endl;
    t_pos p2 = Part2(railroad_map, carts);
    cout << "Day 13, part 2: " << p2.first << " " << p2.second << endl;

    return 0;
}

t_pos Part1(const t_map &rmap, std::vector<Cart> carts) {
    int32_t tick = 0;
    while(1) {
        std::sort(carts.begin(), carts.end());

        for(int32_t idx = 0; idx < carts.size(); ++idx) {
            carts[idx].MoveNext(rmap);
            for(int32_t idx2 = 0; idx2 < carts.size(); ++idx2) {
                if((carts[idx] == carts[idx2]) && (carts[idx].m_id != carts[idx2].m_id)) {
                    return std::make_pair(carts[idx].m_posx, carts[idx].m_posy);
                }
            }
        }
    }

    return std::make_pair(0, 0);
}

t_pos Part2(const t_map &rmap, std::vector<Cart> carts) {
    int32_t tick = 0;
    while(carts.size() > 1) {
        std::sort(carts.begin(), carts.end());

        for(int32_t idx = 0; idx < carts.size(); ++idx) {
            carts[idx].MoveNext(rmap);
            for(int32_t idx2 = 0; idx2 < carts.size(); ++idx2) {
                if((carts[idx] == carts[idx2]) && (carts[idx].m_id != carts[idx2].m_id)) {
                    if(idx < idx2) {
                        carts.erase(carts.begin() + idx2);
                        carts.erase(carts.begin() + idx);
                    }
                    else {
                        carts.erase(carts.begin() + idx);
                        carts.erase(carts.begin() + idx2);
                        idx--;
                    }
                    idx--;
                }
            }
        }
    }

    return std::make_pair(carts[0].m_posx, carts[0].m_posy);
}

void PrintMap(const t_map &rmap, const std::vector<Cart> &carts) {
    int32_t cnt_cart = 0;
    int32_t cnt_map = 0;
    while(cnt_map < rmap.size()) {
        if(cnt_map < carts[cnt_cart].m_posy || cnt_cart == carts.size()) {
            std::copy(rmap[cnt_map].begin(), rmap[cnt_map].end(), std::ostream_iterator<char>(std::cout, ""));
            cout << endl;
        }
        else {
            for(int32_t idx = 0; idx < rmap[cnt_map].size(); ++idx) {
                if(idx == carts[cnt_cart].m_posx && cnt_map == carts[cnt_cart].m_posy) {
                    switch(carts[cnt_cart].m_dir) {
                        case 'N':
                            cout << '^';
                            break;
                        case 'E':
                            cout << '>';
                            break;
                        case 'S':
                            cout << 'v';
                            break;
                        case 'W':
                            cout << '<';
                            break;
                    }
                    cnt_cart++;
                }
                else {
                    cout << rmap[cnt_map][idx];
                }
            }
            cout << endl;
        }
        cnt_map++;
    }

    return;
}