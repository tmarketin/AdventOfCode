#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

using std::cout;
using std::endl;

class Node {
private:
    int64_t m_value;
    class Node *m_prev, *m_next;

public:
    Node (int64_t v): m_value(v), m_prev(nullptr), m_next(nullptr) {
    }

    Node(int64_t v, Node *l, Node *r): m_value(v), m_prev(l), m_next(r) {
    }

    int64_t GetVal() {
        return this->m_value;
    }

    Node * GetPrevious() {
        return this->m_prev;
    }

    Node * GetNext() {
        return this->m_next;
    }

    void SetPrev(Node *p) {
        this->m_prev = p;

        return;
    }

    void SetNext(Node *n) {
        this->m_next = n;
        
        return;
    }
};

class Game {
private:
    int64_t m_players;
    int64_t m_marbles;
    std::vector<int64_t> score;
    Node * m_root;
    Node * m_current;

public:
    Game(int64_t p, int64_t m) : m_players(p), m_marbles(m) {
        score.resize(m_players);
        std::fill(score.begin(), score.end(), 0);

        m_root = new Node(0);
        m_root->SetPrev(m_root);
        m_root->SetNext(m_root);
        m_current = m_root;

        for(int64_t it = 1; it <= m_marbles; ++it) {
            if(it % 23 == 0) {
                for(int64_t itp = 0; itp < 7; ++itp)
                    m_current = m_current->GetPrevious();
                score[it % m_players] += it + (m_current->GetVal());
                m_current = DeleteNode(m_current);

            }
            else {
                m_current = AddNode(it, m_current->GetNext());
            }
        }
    }

    Node * AddNode(int64_t val, Node * node) {
        Node * tmp = new Node(val, node, node->GetNext());
        node->SetNext(tmp);
        (tmp->GetNext())->SetPrev(tmp);

        return tmp;
    }

    Node * DeleteNode(Node *node) {
        Node * tmp;

        (node->GetPrevious())->SetNext(node->GetNext());
        (node->GetNext())->SetPrev(node->GetPrevious());

        tmp = node->GetNext();

        delete node;

        return tmp;
    }

    int64_t GetMaxVal() {
        return *(std::max_element(score.begin(), score.end()));
    }

    void Printout() {
        Node *tmp = m_current;

        do {
            cout << tmp->GetVal() << " ";
            tmp = tmp->GetNext();
        } while(tmp != m_current);
        cout << endl;

        return;
    }
};

int main() {
    std::string line;
    std::ifstream fin("input_day9.dat");
    std::getline(fin, line);

    std::regex rgx(R"([a-z;])");
    line = std::regex_replace(line, rgx, "");

    int64_t players, marbles;
    std::istringstream iss(line);
    iss >> players >> marbles;

    Game *part1 = new Game(players, marbles);
    Game *part2 = new Game(players, 100*marbles);

    cout << "Day 9, part 1: " << part1->GetMaxVal() << endl;
    cout << "Day 9, part 2: " << part2->GetMaxVal() << endl;

    return 0;
}