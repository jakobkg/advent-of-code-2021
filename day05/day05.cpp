#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Line {
public:
  Line(std::pair<int, int> const start, std::pair<int, int> const end) {
    this->start = start;
    this->end = end;
    calcStep();
    this->diagonal = this->step.first != 0 && this->step.second != 0;
  }
  Line(Line &&) = default;
  Line(const Line &) = default;
  Line &operator=(Line &&) = default;
  Line &operator=(const Line &) = default;
  ~Line() = default;

  std::pair<int, int> start;
  std::pair<int, int> end;
  std::pair<int, int> step;
  bool diagonal;

  void calcStep() {
    this->step.first = this->start.first < this->end.first   ? 1
                       : this->start.first > this->end.first ? -1
                                                             : 0;
    this->step.second = this->start.second < this->end.second   ? 1
                        : this->start.second > this->end.second ? -1
                                                                : 0;
  }
};

std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>
read_data(std::string const filename) {
  std::fstream input(filename);
  std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> data;
  std::string stringbuf, numbuf;
  std::pair<int, int> start, end;
  int counter = 0;

  while (std::getline(input, stringbuf, ',')) {
    std::istringstream iss(stringbuf);

    while (iss >> numbuf) {
      if (numbuf.compare("->") != 0) {
        switch (counter) {
        case 0:
          start.first = std::stoi(numbuf);
          counter++;
          break;
        case 1:
          start.second = std::stoi(numbuf);
          counter++;
          break;
        case 2:
          end.first = std::stoi(numbuf);
          counter++;
          break;
        case 3:
          end.second = std::stoi(numbuf);
          counter = 0;
          data.push_back(
              std::pair<std::pair<int, int>, std::pair<int, int>>(start, end));
          break;
        }
      }
    }
  }

  return data;
}

std::vector<Line> points_to_lines(
    std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> const
        points) {
  std::vector<Line> lines;

  for (auto &endpoints : points) {
    lines.push_back(Line(endpoints.first, endpoints.second));
  }

  return lines;
}

template <int size>
std::vector<std::vector<int>> vent_data_from_lines(std::vector<Line> lines) {
  std::vector<std::vector<int>> data;
  data.resize(size);
  for (auto &row : data) {
    row.resize(size);
  }
  std::pair<int, int> cursor;

  for (Line line : lines) {
    for (auto cursor = line.start; cursor != line.end;) {
      data[cursor.first][cursor.second]++;
      cursor.first += line.step.first;
      cursor.second += line.step.second;
    }
    data[line.end.first][line.end.second]++;
  }

  return data;
}

int main(int argc, char *argv[]) {
  auto points = read_data("input");
  auto lines = points_to_lines(points);
  auto vent_data = vent_data_from_lines<1000>(lines);
  int num = 0;

  for (auto &row : vent_data) {
    for (auto &datapoint : row) {
      if (datapoint > 1) {
        num++;
      }
    }
  }

  std::cout << num << std::endl;

  return EXIT_SUCCESS;
}
