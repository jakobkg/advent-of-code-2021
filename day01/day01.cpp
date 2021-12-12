#include <fstream>
#include <iostream>
#include <string.h>
#include <vector>
#include <numeric>

std::vector<int> read(std::string filename) {
  std::ifstream input(filename);
  std::vector<int> data;
  int buf;

  while (input >> buf) {
    data.push_back(buf);
  }

  return data;
}

int sumIncreasing(std::vector<int> const data) {
  unsigned int sum = 0;

  for (int offset = 0; offset < data.size() - 1; offset++) {
    if (data[offset + 1] > data[offset]) {
      sum++;
    }
  }

  return sum;
}

int sumIncreasingSlidingWindow(std::vector<int> const data) {
  int sum = 0;

  int nextWindow, window;

  for (int offset = 0; offset < data.size() - 3; offset++) {
    window = 0;
    nextWindow = 0;
    for (int step = 0; step < 3; step++) {
      window += data[offset + step];
      nextWindow += data[offset + step + 1];
    }

    if (nextWindow > window)
      sum++;
  }

  return sum;
}

int main(int argc, char *argv[]) {
  auto input = read("input");
  std::cout << "Part 1: " << sumIncreasing(input) << std::endl;
  std::cout << "Part 2: " << sumIncreasingSlidingWindow(input) << std::endl;
  return 0;
}
