#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;

class Node{
public:
    int32_t m_no_nodes;
    int32_t m_no_meta;
    std::vector<Node *> nodes;
    std::vector<int32_t> meta;

    Node(std::vector<int32_t> &data, int32_t &start) {
        m_no_nodes = data[start];
        m_no_meta = data[start + 1];

        start = start + 2;
        for(int32_t idx = 0; idx < m_no_nodes; ++idx)
            nodes.push_back(new Node(data, start));

        for(int32_t idx = start; idx < start + m_no_meta; ++idx)
            meta.push_back(data[idx]);
        start = start + m_no_meta;
    }

    int32_t SumMeta() {
        int32_t s = 0;

        for(int32_t &k: meta)
            s = s + k;
        
        return s;
    }

    int32_t GetNumberNodes() {
        return m_no_nodes;
    }
};

Node * CreateTree(std::vector<int32_t> &input);

int32_t Part1(Node *node);
int32_t Part2(Node *node);

int main() {
    int32_t tmp;
    std::vector<int32_t> data;

    std::ifstream fin("input_day8.dat");
    while(fin >> tmp)
        data.push_back(tmp);
    
    Node *root = CreateTree(data);

    cout << "Day 8, part 1: " << Part1(root) << endl;
    cout << "Day 8, part 2: " << Part2(root) << endl;

    return 0;
}
int32_t Part1(Node *node) {
    int32_t s = 0;

    if(node->m_no_nodes > 0) {
        for(int32_t idx = 0; idx < node->m_no_nodes; ++idx)
            s = s + Part1(node->nodes[idx]);
    }

    return s + node->SumMeta();
}

int32_t Part2(Node *node) {
    int32_t s = 0;

    if(node->m_no_nodes == 0) {
        s = node->SumMeta();
    }
    else {
        for(int32_t idx = 0; idx < node->m_no_meta; ++idx) {
            if(node->meta[idx] <= node->m_no_nodes)
                s = s + Part2(node->nodes[node->meta[idx] - 1]);
        }
    }

    return s;
}

Node * CreateTree(std::vector<int32_t> &input) {
    int32_t start = 0;
    Node *root = new Node(input, start);

    return root;
}