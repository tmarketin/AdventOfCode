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

typedef std::array<uint32_t, REGISTER_SIZE> t_reg;
typedef std::array<uint32_t, 3> t_comm;
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

uint32_t Part1(int32_t ipreg, t_reg &regs, std::vector<Instruction> &program, t_functionMap &fnc);

int main() {
    std::string line, fline;
    int32_t ipreg = -1;
    std::vector<Instruction> program;

    t_functionMap fnc = { {"addr", addr}, {"addi", addi},  {"mulr", mulr}, {"muli", muli}, {"banr", banr}, 
        {"bani", bani}, {"borr", borr}, {"bori", bori}, {"setr", setr}, {"seti", seti}, {"gtir", gtir}, 
        {"gtri", gtri}, {"gtrr", gtrr}, {"eqir", eqir}, {"eqri", eqri}, {"eqrr", eqrr}};

    t_reg regs_part1 = {0, 0, 0, 0, 0, 0};
    t_reg regs_part2 = {1, 0, 0, 0, 0, 0};

    std::ifstream fin("input_day19.dat");
    std::getline(fin, line);

    std::istringstream iss(line);
    iss >> fline >> ipreg;

    while(std::getline(fin, line))
        program.push_back(Instruction(line));
    
//    cout << "Day 19, part 1: " << Part1(ipreg, regs_part1, program, fnc) << endl;
    cout << "Day 19, part 2: " << Part1(ipreg, regs_part2, program, fnc) << endl;

    return 0;
}

uint32_t Part1(int32_t ipreg, t_reg &regs, std::vector<Instruction> &program, t_functionMap &fnc) {
    int32_t ip = 0;

    while(ip >= 0 && ip < program.size()) {
        cout << ip << " " << program[ip] << endl;
        regs[ipreg] = ip;
        fnc[program[ip].m_inst](regs, program[ip].m_comm);
        ip = regs[ipreg];
        PrintArray(regs);
        ip++;
    }

    return regs[0];
}

void PrintArray(const t_reg &reg) {
    for(uint32_t idx = 0; idx < REGISTER_SIZE; ++idx)
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