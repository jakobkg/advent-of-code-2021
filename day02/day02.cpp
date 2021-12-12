#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

unsigned int horizontalPos, depth = 0;

const bool stringsAreEqual(std::string const &one, std::string const &other) {
  return one.compare(other) == 0;
}

std::vector<std::pair<std::string, int>>
read_input(std::string const filename) {
  std::vector<std::pair<std::string, int>> data;
  std::ifstream input(filename);
  std::string linebuf;
  std::string segment;
  std::stringstream linestream;
  std::pair<std::string, int> segments;
  bool first = true;

  while (std::getline(input, linebuf)) {
    linestream = std::stringstream(linebuf);
    while (std::getline(linestream, segment, ' ')) {
      if (first) {
        segments.first = segment;
      } else {
        segments.second = std::stoi(segment);
      }
      first = !first;
    }

    data.push_back(segments);
  }

  return data;
}

const std::pair<int, int>
part1(std::vector<std::pair<std::string, int>> const data) {
  std::pair<int, int> result(0, 0);

  for (auto step : data) {
    if (stringsAreEqual(step.first, "up")) {
      result.second -= step.second;
    } else if (stringsAreEqual(step.first, "down")) {
      result.second += step.second;
    } else if (stringsAreEqual(step.first, "forward")) {
      result.first += step.second;
    }
  }

  return result;
}

const std::pair<int, int>
part2(std::vector<std::pair<std::string, int>> const data) {
  int aim = 0;
  std::pair<int, int> result(0, 0);

  for (auto step : data) {
    if (stringsAreEqual(step.first, "up")) {
      aim -= step.second;
    } else if (stringsAreEqual(step.first, "down")) {
      aim += step.second;
    } else if (stringsAreEqual(step.first, "forward")) {
      result.first += step.second;
      result.second += step.second * aim;
    }
  }

  return result;
}

int main(int argc, char *argv[]) {
  const auto data = read_input("input");
  std::pair<int, int> tmp;

  tmp = part1(data);
  std::cout << "Part 1:\nFinal horizontal position: " << tmp.first << std::endl;
  std::cout << "Final depth: " << tmp.second << std::endl;
  std::cout << "Multiplied: " << tmp.first * tmp.second << std::endl;

  tmp = part2(data);
  std::cout << "Part 2:\nFinal horizontal position: " << tmp.first << std::endl;
  std::cout << "Final depth: " << tmp.second << std::endl;
  std::cout << "Multiplied: " << tmp.first * tmp.second << std::endl;
  return EXIT_SUCCESS;
}
