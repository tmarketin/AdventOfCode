#include <fstream>
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <utility>
#include <vector>

using std::cout;
using std::endl;

class OrbitNode {
private:
  std::string object;
  uint16_t nChildren;

public:
  OrbitNode * parent;
  std::vector<OrbitNode *> children;
  uint32_t nOrbits;

  OrbitNode(std::string objectName) : object(objectName) {
    parent = nullptr;
    children.clear();
    nChildren = 0;
    nOrbits = 0;

    return;
  }

  void setParent(OrbitNode * p) {
    parent = p;

    return;
  }

  void addChild(OrbitNode * p) {
    children.push_back(p);
    nChildren++;

    return;
  }

  std::string getName() {
    return object;
  }

  OrbitNode * getParent() {
    return parent;
  }
};

class OrbitNodeTree {
private:
  OrbitNode * root;

public:
  OrbitNodeTree(OrbitNode * p) : root(p) {
    return;
  }

  OrbitNode * getRoot() {
    return root;
  }

  void print(OrbitNode * p) {
    cout << "Name: " << p->getName() << ", # of orbits: " << p->nOrbits <<  endl;
    cout << "Children : ";
    if(p->children.empty()) {
      cout << "none" << endl;
    }
    else {
      for(auto k: p->children)
        cout << k->getName() << " ";
      cout << endl;
    }

    for(auto k: p->children)
      print(k);
  }

  void setOrbitNumbers(OrbitNode *p, uint32_t num) {
    p-> nOrbits = num;
    for(auto k: p->children)
      setOrbitNumbers(k, num + 1);
    
    return;
  }

  uint32_t getTotalOrbitNumber(OrbitNode * p) {
    uint32_t num = p->nOrbits;
    for(auto k: p->children)
      num += getTotalOrbitNumber(k);
    
    return num;
  }

};

typedef std::pair<std::string, std::string> OrbitPair_t;
typedef std::vector<OrbitPair_t> OrbitPairList_t;
typedef std::map<std::string, OrbitNode *> OrbitNodeMap_t;

void loadData(const std::string &fname, OrbitPairList_t &list);
void fillMap(OrbitNodeMap_t & nodeMap, const OrbitPairList_t & list);
void connectMap(OrbitNodeMap_t & nodeMap, const OrbitPairList_t & list);

uint32_t shortestPath(OrbitNodeMap_t nodeMap, std::string start, std::string end);

int main() {
  OrbitPairList_t orbitPairList;
  loadData("input_day6.dat", orbitPairList);

  OrbitNodeMap_t nodeMap;
  fillMap(nodeMap, orbitPairList);
  connectMap(nodeMap, orbitPairList);

  OrbitNodeTree orbitTree(nodeMap["COM"]);
  orbitTree.setOrbitNumbers(orbitTree.getRoot(), 0);

  cout << "Part 1: " << orbitTree.getTotalOrbitNumber(orbitTree.getRoot()) << endl;

  cout << "Part 2: " << shortestPath(nodeMap, "YOU", "SAN") << endl;

  return 0;
}

void loadData(const std::string &fname, OrbitPairList_t &list) {
  std::ifstream infile(fname);

  std::string line;
  while(getline(infile, line)) {
    size_t delimPos = line.find_first_of(")");
    list.push_back(std::make_pair(line.substr(0, delimPos), line.substr(delimPos + 1)));
  }

  return;
}

void fillMap(OrbitNodeMap_t & nodeMap, const OrbitPairList_t & list) {
  for(auto k: list) {
    if(nodeMap.find(k.first) == nodeMap.end())
      nodeMap[k.first] = new OrbitNode(k.first);

    if(nodeMap.find(k.second) == nodeMap.end())
      nodeMap[k.second] = new OrbitNode(k.second);

  }

  return;
}

void connectMap(OrbitNodeMap_t & nodeMap, const OrbitPairList_t & list) {
  for(auto k: list) {
    nodeMap[k.first]->addChild(nodeMap[k.second]);
    nodeMap[k.second]->setParent(nodeMap[k.first]);
  }

  return;
}

uint32_t shortestPath(OrbitNodeMap_t nodeMap, std::string start, std::string end) {
  std::stack<std::string> startPath;
  std::stack<std::string> endPath;

  OrbitNode * p = nullptr;
  p = nodeMap[start];
  while(p->getName() != "COM") {
    startPath.push(p->getName());
    p = p->parent;
  }

  p = nodeMap[end];
  while(p->getName() != "COM") {
    endPath.push(p->getName());
    p = p->parent;
  }

  while(startPath.top() == endPath.top()) {
    startPath.pop();
    endPath.pop();
  }

  return startPath.size() + endPath.size() - 2;
}