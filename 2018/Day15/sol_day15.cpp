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

typedef std::pair<int32_t, int32_t> t_pos; // x, y 
typedef std::vector<char> t_line;
typedef std::vector<t_line> t_map;
typedef std::pair<t_pos, int32_t> t_target; // position, fighter idx in list
typedef std::pair<int32_t, t_pos> t_path; // distance, position of next step
typedef std::pair<t_target, t_path> t_targetDistance; // target, path to target
typedef std::pair<t_target, int32_t> t_attacktarget; // target for attacking, hp of target

bool compare_tpos_less(const t_pos &lhs, const t_pos &rhs);
bool compare_ttarget_less(const t_target &lhs, const t_target &rhs);
bool compare_ttargetdistance_less(const t_targetDistance &lhs, const t_targetDistance &rhs);
bool compare_tattacktarget_less(const t_attacktarget &lhs, const t_attacktarget &rhs);

int32_t Part2(std::string str);

class Fighter {
public:
    char m_type;
    t_pos m_pos;
    int32_t m_hp;
    int32_t m_att;

    Fighter(char _type, t_pos _pos, int32_t _att) {
        m_type = _type;
        m_pos = _pos;
        m_hp = 200;
        m_att = _att;
    }

    bool IsDead() {
        if(m_hp <= 0)
            return true;
        else
            return false;
    }

    void GetHit(int32_t att) {
        m_hp -= att;

        return;
    }

    void Move(char d) {
        switch(d) {
            case 'N':
                m_pos.second--;
                break;
            case 'W':
                m_pos.first--;
                break;
            case 'E':
                m_pos.first++;
                break;
            case 'S':
                m_pos.second++;
                break;
        }

        return;
    }

    bool operator < (const Fighter &extfighter) const {
        return (m_pos.second < extfighter.m_pos.second || (m_pos.second == extfighter.m_pos.second && m_pos.first < extfighter.m_pos.first));
    }

    friend std::ostream& operator<< (std::ostream &out, const Fighter &fighter);
};

std::ostream& operator<< (std::ostream &out, const Fighter &fighter)
{
    out << (fighter.m_type == 'E' ? "Elf: " : "Goblin: ") << fighter.m_pos.first << ", " << fighter.m_pos.second 
        << ", " << fighter.m_hp << " hp, att: " << fighter.m_att; 
 
    return out;
}

class Map {
private:
    t_map m_map;
    std::vector<Fighter> m_team;

public:
    Map(std::string infile, int32_t attpower) {
        std::ifstream fin(infile);
        std::vector<char> tmpline;

        std::string line;
        int32_t cnt_y = 0;
        while(std::getline(fin, line)) {
            tmpline.clear();
            for(int32_t idx = 0; idx < line.size(); ++idx) {
                if(line[idx] == 'G' || line[idx] == 'E')
                    m_team.push_back(Fighter(line[idx], std::make_pair(idx, cnt_y), (line[idx] == 'G' ? 3 : attpower)));
                tmpline.push_back(line[idx]);
            }
            m_map.push_back(tmpline);
            cnt_y++;
        }
    }

    t_path FindPath(t_pos start, t_pos target, std::vector<std::vector<char>> map) {
        int rows = map.size();
        int cols = map[0].size();

        // map_tmp tracks the number of steps required for each position
        std::vector<std::vector<int> > map_tmp(rows, std::vector<int>(cols,-1));
        map_tmp[start.second][start.first] = 0;

        // map_prev tracks the position previous to each map position
        std::vector<std::vector<t_pos> > map_prev(rows, std::vector<t_pos>(cols));

        // queue for position handling, initially only has starting position
        std::vector<t_pos> qu;
        qu.push_back(start);

        t_pos pos_curr, pos_prev;

        if(start.first == target.first && start.second == target.second) { // already there
//            cout << "Starting position is on the target." << endl;
//            cout << "Path length equal to 0." << endl;
            return std::make_pair(0, start);
        }

        int step_count = 0;
        while(qu.size() > 0 && map_tmp[target.second][target.first] == -1) {
            step_count++;
            pos_curr = qu[0];
            qu.erase(qu.begin());
            pos_prev = pos_curr;

            pos_curr.second--; // first we try going north
            if(m_map[pos_curr.second][pos_curr.first] == '.' && map_tmp[pos_curr.second][pos_curr.first] == -1) { 
                map_tmp[pos_curr.second][pos_curr.first] = map_tmp[pos_prev.second][pos_prev.first] + 1;
                qu.push_back(pos_curr);
                map_prev[pos_curr.second][pos_curr.first] = pos_prev;
            }

            pos_curr = pos_prev;
            pos_curr.first--; // west (reading order)
            if(m_map[pos_curr.second][pos_curr.first] == '.' && map_tmp[pos_curr.second][pos_curr.first] == -1) {
                map_tmp[pos_curr.second][pos_curr.first] = map_tmp[pos_prev.second][pos_prev.first] + 1;
                qu.push_back(pos_curr);
                map_prev[pos_curr.second][pos_curr.first] = pos_prev;
            }

            pos_curr = pos_prev;
            pos_curr.first++; // east
            if(m_map[pos_curr.second][pos_curr.first] == '.' && map_tmp[pos_curr.second][pos_curr.first] == -1) {
                map_tmp[pos_curr.second][pos_curr.first] = map_tmp[pos_prev.second][pos_prev.first] + 1;
                qu.push_back(pos_curr);
                map_prev[pos_curr.second][pos_curr.first] = pos_prev;
            }

            pos_curr = pos_prev; // finally south
            pos_curr.second++;
            if(m_map[pos_curr.second][pos_curr.first] == '.' && map_tmp[pos_curr.second][pos_curr.first] == -1) {
                map_tmp[pos_curr.second][pos_curr.first] = map_tmp[pos_prev.second][pos_prev.first] + 1;
                qu.push_back(pos_curr);
                map_prev[pos_curr.second][pos_curr.first] = pos_prev;
            }
        }

        if(map_tmp[target.second][target.first] == -1) 
            return std::make_pair(-1, std::make_pair(0, 0));

        t_pos step = target;
        while(map_prev[step.second][step.first] != start)
            step = map_prev[step.second][step.first];

        return std::make_pair(map_tmp[target.second][target.first], step);
    }

    void PrintMap() {
        for(auto &k: m_map) {
            std::copy(k.begin(), k.end(), std::ostream_iterator<char>(std::cout, ""));
            cout << endl;
        }

        return;
    }

    void PrintFighters() {
        for(auto &k: m_team)
            cout << k << endl;
        
        return;
    }

    int32_t CountGoblins() {
        int32_t s = 0;

        for(auto &k: m_team)
            if(k.m_type == 'G')
                s++;
        
        return s;
    }

    int32_t CountElves() {
        int32_t s = 0;

        for(auto &k: m_team)
            if(k.m_type == 'E')
                s++;
        
        return s;
    }

    char GetMoveDir(t_pos start_pos, t_pos next_step) {
        if(start_pos.first == next_step.first) {
            if(next_step.second < start_pos.second)
                return 'N';
            else
                return 'S';
        }
        else {
            if(next_step.first < start_pos.first)
                return 'W';
            else
                return 'E';
        }
    }

    int32_t GetTotalHP() {
        int32_t s = 0;
        for(auto &k: m_team)
            s = s + k.m_hp;
        
        return s;
    }

    int32_t ManhattanDistance(const t_pos &start, const t_pos &end) {
        return abs(start.first - end.first) + abs(start.second - end.second);
    }

    int32_t Part1() {
        std::vector<t_target> targetPosList;
        std::vector<t_targetDistance> targetDistanceList;
        std::vector<t_attacktarget> attackTargetList;
        t_pos tmpPos;

        int32_t round_count = 0;
        while(1) {
            std::sort(m_team.begin(), m_team.end());

            for(auto current_fighter = m_team.begin(); current_fighter != m_team.end(); ++current_fighter) {
                targetPosList.clear();
                targetDistanceList.clear();

                if(CountElves() == 0 || CountGoblins() == 0) {
                    return round_count*GetTotalHP();
                }

                for(auto poss_target = m_team.begin(); poss_target != m_team.end(); ++poss_target) {
                    if(current_fighter->m_type != poss_target->m_type) {
                        if(m_map[poss_target->m_pos.second - 1][poss_target->m_pos.first] == '.')
                            targetPosList.push_back(std::make_pair(std::make_pair(poss_target->m_pos.first, poss_target->m_pos.second - 1), std::distance(m_team.begin(), poss_target)));
                        if(m_map[poss_target->m_pos.second][poss_target->m_pos.first - 1] == '.')
                            targetPosList.push_back(std::make_pair(std::make_pair(poss_target->m_pos.first - 1, poss_target->m_pos.second), std::distance(m_team.begin(), poss_target)));
                        if(m_map[poss_target->m_pos.second][poss_target->m_pos.first + 1] == '.')
                            targetPosList.push_back(std::make_pair(std::make_pair(poss_target->m_pos.first + 1, poss_target->m_pos.second), std::distance(m_team.begin(), poss_target)));
                        if(m_map[poss_target->m_pos.second + 1][poss_target->m_pos.first] == '.')
                            targetPosList.push_back(std::make_pair(std::make_pair(poss_target->m_pos.first, poss_target->m_pos.second + 1), std::distance(m_team.begin(), poss_target)));
                        if(ManhattanDistance(current_fighter->m_pos, poss_target->m_pos) == 1)
                            targetPosList.push_back(std::make_pair(current_fighter->m_pos, std::distance(m_team.begin(), poss_target)));
                    }
                }
                std::sort(targetPosList.begin(), targetPosList.end(), compare_ttarget_less);

                for(auto &target: targetPosList) {
                    t_path step = FindPath(current_fighter->m_pos, target.first, m_map);
                    if(step.first != -1)
                        targetDistanceList.push_back(std::make_pair(target, step));
                }

                if(targetDistanceList.size() == 0)
                    continue;

                std::sort(targetDistanceList.begin(), targetDistanceList.end(), compare_ttargetdistance_less);

                if(targetDistanceList[0].second.first > 0) { // move
                    t_pos start_pos = current_fighter->m_pos;
                    t_pos next_step = targetDistanceList[0].second.second;
                    char direction = GetMoveDir(start_pos, next_step);

                    m_map[next_step.second][next_step.first] = current_fighter->m_type;
                    m_map[start_pos.second][start_pos.first] = '.';
                    current_fighter->Move(direction);
                }

                attackTargetList.clear();
                for(auto poss_target = m_team.begin(); poss_target != m_team.end(); ++poss_target) {
                    if(current_fighter->m_type != poss_target->m_type) {
                        if(ManhattanDistance(current_fighter->m_pos, poss_target->m_pos) == 1)
                            attackTargetList.push_back(std::make_pair(std::make_pair(poss_target->m_pos, std::distance(m_team.begin(), poss_target)), poss_target->m_hp));
                    }
                }  

                if(attackTargetList.size() > 0) {
                    std::sort(attackTargetList.begin(), attackTargetList.end(), compare_tattacktarget_less);

                    int32_t idx = attackTargetList[0].first.second;
                    m_team[idx].GetHit(current_fighter->m_att);
                    if(m_team[idx].IsDead()) {
                        m_map[m_team[idx].m_pos.second][m_team[idx].m_pos.first] = '.';
                        m_team.erase(m_team.begin() + idx);
                        if(std::distance(m_team.begin(), current_fighter) > idx)
                            current_fighter--;
                    }
                }
            }
            round_count++;
        }

        return round_count*GetTotalHP();
    }
};

int main() {
    Map battlefield("input_day15.dat", 3);

    cout << "Day 15, part 1: " << battlefield.Part1() << endl;
    cout << "Day 15, part 2: " << Part2("input_day15.dat") << endl;

    return 0;
}

int32_t Part2(std::string str) {
    int32_t att = 3;
    int32_t res = 0;

    while(1) {
        Map bfield(str, att);
        int32_t init_elves = bfield.CountElves();

        res = bfield.Part1();
        if(bfield.CountElves() == init_elves)
            break;
        
        att++;
    }

    return res;
}

bool compare_tpos_less(const t_pos &lhs, const t_pos &rhs) {
    return (lhs.second < rhs.second || (lhs.second == rhs.second && lhs.first < rhs.first));
}

bool compare_ttarget_less(const t_target &lhs, const t_target &rhs) {
    return compare_tpos_less(lhs.first, rhs.first);
}

bool compare_ttargetdistance_less(const t_targetDistance &lhs, const t_targetDistance &rhs) {
    return (lhs.second.first < rhs.second.first || (lhs.second.first == rhs.second.first && compare_tpos_less(lhs.first.first, rhs.first.first)));
}

bool compare_tattacktarget_less(const t_attacktarget &lhs, const t_attacktarget &rhs) {
    return (lhs.second < rhs.second || compare_ttarget_less(lhs.first, rhs.first));
}
