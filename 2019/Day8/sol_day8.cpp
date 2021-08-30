#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define MAX_WIDTH 25
#define MAX_HEIGHT 6
#define MAX_LAYER_LEN MAX_WIDTH*MAX_HEIGHT

using std::cout;
using std::endl;

typedef std::string Layer_t;
typedef std::vector<Layer_t> Image_t;

void loadImage(std::string fname, Image_t & image);
void printLayer(const Layer_t layer);

int32_t part1(const Image_t image);
void part2(Image_t image);

int main() {
  Image_t image;

  loadImage("input_day8.dat", image);

  cout << "Part 1: " << part1(image) << endl;
  part2(image);

  return 0;
}

int32_t part1(const Image_t image) {
  std::vector<int32_t> zeroCounts;

  for(auto k: image)
    zeroCounts.push_back(std::count(k.begin(), k.end(), '0'));
  
  size_t minPos = std::distance(zeroCounts.begin(), std::min_element(zeroCounts.begin(), zeroCounts.end()));

  return std::count(image[minPos].begin(), image[minPos].end(), '1')*std::count(image[minPos].begin(), image[minPos].end(), '2');
}

void part2(Image_t image) {
  Layer_t & finalImage = image[0];

  cout << image.size() << "  " << finalImage.size() << endl;

  for(size_t layerIdx = 1; layerIdx < image.size(); layerIdx++) {
    for(size_t charIdx = 0; charIdx < finalImage.size(); charIdx++) {
      if(finalImage[charIdx] == '2' && image[layerIdx][charIdx] != '2') {
        finalImage[charIdx] = image[layerIdx][charIdx];
      }
    }
  }

  printLayer(finalImage);

  return;
}

void printLayer(const Layer_t layer) {
  size_t initPos = 0;

  while(initPos < layer.size()) {
    for(auto k: layer.substr(initPos, MAX_WIDTH)) {
      if(k == '0')
        cout << ' ';
      else if(k == '1')
        cout << '#';
      else
        cout << ' ';
    }
    cout << endl;
    initPos += MAX_WIDTH;
  }

  return;
}

void loadImage(std::string fname, Image_t & image) {
  std::ifstream infile(fname);

  std::string inputData;
  std::getline(infile, inputData);

  while(!inputData.empty()) {
    image.push_back(inputData.substr(0, MAX_LAYER_LEN));
    inputData.erase(0, MAX_LAYER_LEN);
  }

  return;
}