#include <array>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <utility>
#include <vector>

using std::cout;
using std::endl;

#define GRID_SIZE 300

typedef std::pair<int32_t, int32_t> t_coord;

class FuelCell {
private:
    int64_t m_power;
    int32_t m_row, m_col;

public:
    FuelCell() {
    }

    void FindPowerLevel(int32_t r, int32_t c, int32_t gsn) {
        m_row = r;
        m_col = c;

        int32_t rackID = m_col + 10;
        m_power = (((rackID*m_row + gsn)*rackID)/100 % 10) - 5;
    }

    int64_t GetPower() {
        return m_power;
    }
};

class Grid {
private:
    std::array<std::array<FuelCell, GRID_SIZE>, GRID_SIZE> m_grid;
    int32_t m_gsn;

public:
    Grid(int32_t gsn) : m_gsn(gsn) {
        for(int32_t row = 0; row < GRID_SIZE; ++row)
            for(int32_t col = 0; col < GRID_SIZE; ++col)
                m_grid[col][row].FindPowerLevel(row + 1, col + 1, m_gsn);
    }

    FuelCell getFuelCell(int32_t col, int32_t row) {
        return m_grid[col - 1][row - 1];
    }

    int32_t SumSubGrid(int32_t col, int32_t row, int32_t gridSize) {
        int32_t s = 0;
        int32_t offset = gridSize - 1;
        if(col < 0 || col > GRID_SIZE - offset || row < 0 || row > GRID_SIZE - offset)
            return -1000;

        for(int32_t ity = row; ity <= row + offset; ++ity)
            for(int32_t itx = col; itx <= col + offset; ++itx)
                s = s + m_grid[itx][ity].GetPower();
        return s;
    }

    std::pair<t_coord, int32_t> Part1(int32_t gridSize) {
        int32_t best_col = 0;
        int32_t best_row = 0;
        int32_t best_val = SumSubGrid(best_col, best_row, gridSize);

        for(int32_t ity = 0; ity < GRID_SIZE - (gridSize - 1); ++ity)
            for(int32_t itx = 0; itx < GRID_SIZE - (gridSize - 1); ++itx) {
                int32_t tmp_sum = SumSubGrid(itx, ity, gridSize);
                if(tmp_sum > best_val) {
                    best_val = tmp_sum;
                    best_col = itx;
                    best_row = ity;
                }
            }
        
        return std::make_pair(std::make_pair(best_col + 1, best_row + 1), best_val);
    }

    std::pair<t_coord, int32_t> FindMax(std::array<std::array<int32_t, GRID_SIZE>, GRID_SIZE> &arr, int32_t size) {
        int32_t best_val = arr[0][0];
        t_coord best_pos = std::make_pair(0, 0);

        for(int32_t ity = 0; ity < GRID_SIZE - size + 1; ++ity)
            for(int32_t itx = 0; itx < GRID_SIZE - size + 1; ++itx)
                if(arr[itx][ity] > best_val) {
                    best_val = arr[itx][ity];
                    best_pos = std::make_pair(itx, ity);
                }
        
        return std::make_pair(best_pos, best_val);
    }

    int32_t SumL(std::array<std::array<int32_t, GRID_SIZE>, GRID_SIZE> &arr, int32_t col, int32_t row, int32_t size) {
        int32_t s = 0;

        if(size == 300)
            return 0;

        int32_t offset = size - 1;
        for(int32_t it = row; it <= row + offset; ++it)
            s = s + m_grid[col + offset][it].GetPower();
        for(int32_t it = col; it <= col + offset; ++it)
            s = s + m_grid[it][row + offset].GetPower();
        s = s - m_grid[col + offset][row + offset].GetPower();

        return s;
    }

    std::pair<t_coord, int32_t> Part2() {
        int32_t best_size = 1;
        std::pair<t_coord, int32_t> best_sol = std::make_pair(std::make_pair(0, 0), 0);

        std::array<std::array<int32_t, GRID_SIZE>, GRID_SIZE> sums;
        for(int32_t ity = 0; ity < GRID_SIZE; ++ity)
            for(int32_t itx = 0; itx < GRID_SIZE; ++itx)
                sums[itx][ity] = m_grid[itx][ity].GetPower();
        best_sol = FindMax(sums, 1);

        for(int32_t size = 2; size <= 300; ++size) {
            for(int32_t ity = 0; ity < GRID_SIZE - size + 1; ++ity)
                for(int32_t itx = 0; itx < GRID_SIZE - size + 1; ++itx)
                    sums[itx][ity] = sums[itx][ity] + SumL(sums, itx, ity, size);

            std::pair<t_coord, int32_t> tmp = FindMax(sums, size);
            if(tmp.second > best_sol.second) {
                best_sol = tmp;
                best_size = size;
            }
        }

        best_sol.first.first += 1;
        best_sol.first.second += 1;
        return std::make_pair(best_sol.first, best_size);
    }
};

int main() {
    std::ifstream fin("input_day11.dat");

    int32_t gridSerNum;
    fin >> gridSerNum;

    Grid grid(gridSerNum);

    std::pair<t_coord, int32_t> part1 = grid.Part1(3);
    cout << "Day 11, part 1: " << part1.first.first << ", " << part1.first.second << ", " << part1.second << endl;
    std::pair<t_coord, int32_t> part2 = grid.Part2();
    cout << "Day 11, part 2: " << part2.first.first << ", " << part2.first.second << ", " << part2.second << endl;

    return 0;
}