#include <algorithm>
#include <array>
#include <cstdint>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <regex>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#define REGISTER_SIZE 6

using std::cout;
using std::endl;

typedef std::array<uint64_t, REGISTER_SIZE> t_reg;
typedef std::array<uint64_t, 3> t_comm;
typedef std::map<std::string, std::function<void(t_reg &, const t_comm &)>> t_functionMap;

// instructions
void addr(t_reg &regs, const t_comm &comm);
void addi(t_reg &regs, const t_comm &comm);

void mulr(t_reg &regs, const t_comm &comm);
void muli(t_reg &regs, const t_comm &comm);

void banr(t_reg &regs, const t_comm &comm);
void bani(t_reg &regs, const t_comm &comm);
void borr(t_reg &regs, const t_comm &comm);
void bori(t_reg &regs, const t_comm &comm);

void setr(t_reg &regs, const t_comm &comm);
void seti(t_reg &regs, const t_comm &comm);

void gtir(t_reg &regs, const t_comm &comm);
void gtri(t_reg &regs, const t_comm &comm);
void gtrr(t_reg &regs, const t_comm &comm);

void eqir(t_reg &regs, const t_comm &comm);
void eqri(t_reg &regs, const t_comm &comm);
void eqrr(t_reg &regs, const t_comm &comm);

class Instruction {
public:
    std::string m_inst;
    t_comm m_comm;

    Instruction(std::string line) {
        std::istringstream iss(line);

        iss >> m_inst >> m_comm[0] >> m_comm[1] >> m_comm[2];
    }

    friend std::ostream& operator<< (std::ostream &out, const Instruction &inc);
};

std::ostream& operator<< (std::ostream &out, const Instruction &inc)
{
    cout << inc.m_inst << " " << inc.m_comm[0] << " " << inc.m_comm[1] << " " << inc.m_comm[2];

    return out;
}

void PrintArray(const t_reg &reg);
int64_t SimulateProgram(t_reg reg);

uint64_t Part1(int64_t ipreg, t_reg &regs, std::vector<Instruction> &program, t_functionMap &fnc);
uint64_t Part2(int64_t ipreg, t_reg &regs, std::vector<Instruction> &program, t_functionMap &fnc);

int main() {
    std::string line, fline;
    int64_t ipreg = -1;
    std::vector<Instruction> program;

    t_functionMap fnc = { {"addr", addr}, {"addi", addi},  {"mulr", mulr}, {"muli", muli}, {"banr", banr}, 
        {"bani", bani}, {"borr", borr}, {"bori", bori}, {"setr", setr}, {"seti", seti}, {"gtir", gtir}, 
        {"gtri", gtri}, {"gtrr", gtrr}, {"eqir", eqir}, {"eqri", eqri}, {"eqrr", eqrr}};

    t_reg regs_part1 = {0, 0, 0, 0, 0, 0};
    SimulateProgram(regs_part1);
    exit(1);

    std::ifstream fin("input_day21.dat");
    std::getline(fin, line);

    std::istringstream iss(line);
    iss >> fline >> ipreg;

    while(std::getline(fin, line))
        program.push_back(Instruction(line));

    cout << "Day 21, part 1: " << Part1(ipreg, regs_part1, program, fnc) << endl;
    cout << "Day 21, part 2: " << Part2(ipreg, regs_part1, program, fnc) << endl;

    return 0;
}

uint64_t Part1(int64_t ipreg, t_reg &regs, std::vector<Instruction> &program, t_functionMap &fnc) {
    uint64_t ip_counter = 0;
    int64_t ip = 0;

    while(ip >= 0 && ip < program.size()) {
        regs[ipreg] = ip;
        fnc[program[ip].m_inst](regs, program[ip].m_comm);
        ip_counter++;
        ip = regs[ipreg];
        ip++;
        if(ip == 28)
            break;
    }

    return regs[5];
}

uint64_t Part2(int64_t ipreg, t_reg &regs, std::vector<Instruction> &program, t_functionMap &fnc) {
    int64_t max = 0;
    int64_t max_cnt = 0;

    for(uint64_t idx = 0; idx <= 16777215; ++idx) {
        t_reg regs = {idx, 0, 0, 0, 0, 0};
        int64_t tmpcnt = SimulateProgram(regs);
        if(tmpcnt > max_cnt) {
            max_cnt = tmpcnt;
            max = idx;
        }
    }

    return max;
}

int64_t SimulateProgram(t_reg reg) {
    int64_t cnt = 0;
    do {    
        cnt++;
        if(cnt == 200)
            return -1;

        PrintArray(reg);
        reg[1] = reg[5] | 65536;
        reg[5] = 10678677;

        while(true) {
            reg[4] = reg[1] & 0x000000ff;
            reg[5] = ((reg[4] + reg[5]) & 0x00ffffff)*65899 & 0x00ffffff;

            if(256 > reg[1])
                break;

            for(reg[4] = 0; reg[3] <= reg[1]; ++reg[4]) {
                reg[3] = (reg[4] + 1)*256;
            }
            reg[1] = reg[4];
//            reg[1] = reg[1]/256;
        }
    } while (reg[5] != reg[0]);

    return cnt;
}

void PrintArray(const t_reg &reg) {
    for(uint64_t idx = 0; idx < REGISTER_SIZE; ++idx)
        cout << reg[idx] << " ";
    cout << endl;

    return;
}

void addr(t_reg &regs, const t_comm &comm) {
    regs[comm[2]] = regs[comm[0]] + regs[comm[1]];

    return;
}

void addi(t_reg &regs, const t_comm &comm) {
    regs[comm[2]] = regs[comm[0]] + comm[1];

    return;
}

void mulr(t_reg &regs, const t_comm &comm) {
    regs[comm[2]] = regs[comm[0]]*regs[comm[1]];

    return;
}

void muli(t_reg &regs, const t_comm &comm) {
    regs[comm[2]] = regs[comm[0]]*comm[1];

    return;
}

void banr(t_reg &regs, const t_comm &comm) {
    regs[comm[2]] = regs[comm[0]] & regs[comm[1]];

    return;
}

void bani(t_reg &regs, const t_comm &comm) {
    regs[comm[2]] = regs[comm[0]] & comm[1];

    return;
}

void borr(t_reg &regs, const t_comm &comm) {
    regs[comm[2]] = regs[comm[0]] | regs[comm[1]];

    return;
}

void bori(t_reg &regs, const t_comm &comm) {
    regs[comm[2]] = regs[comm[0]] | comm[1];

    return;
}

void setr(t_reg &regs, const t_comm &comm) {
    regs[comm[2]] = regs[comm[0]];

    return;
}

void seti(t_reg &regs, const t_comm &comm) {
    regs[comm[2]] = comm[0];

    return;
}

void gtir(t_reg &regs, const t_comm &comm) {
    regs[comm[2]] = (comm[0] > regs[comm[1]] ? 1 : 0);

    return;
}

void gtri(t_reg &regs, const t_comm &comm) {
    regs[comm[2]] = (regs[comm[0]] > comm[1] ? 1: 0);

    return;
}

void gtrr(t_reg &regs, const t_comm &comm) {
    regs[comm[2]] = (regs[comm[0]] > regs[comm[1]] ? 1 : 0);

    return;
}

void eqir(t_reg &regs, const t_comm &comm) {
    regs[comm[2]] = (comm[0] == regs[comm[1]] ? 1 : 0);

    return;
}

void eqri(t_reg &regs, const t_comm &comm) {
    regs[comm[2]] = (regs[comm[0]] == comm[1] ? 1 : 0);

    return;
}

void eqrr(t_reg &regs, const t_comm &comm) {
    regs[comm[2]] = (regs[comm[0]] == regs[comm[1]] ? 1 : 0);

    return;
}