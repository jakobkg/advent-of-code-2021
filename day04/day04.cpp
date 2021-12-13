#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Board {
public:
  Board() {
    this->done = false;
    this->numbers = std::array<std::array<int, 5>, 5>();
    this->drawn = std::array<std::array<bool, 5>, 5>();

    for (auto row : numbers) {
      row.fill(0);
    }

    for (auto row : drawn) {
      row.fill(false);
    }
  }

  Board(std::array<std::array<int, 5>, 5> numbers) {
    this->done = false;
    this->numbers = numbers;
    this->drawn = std::array<std::array<bool, 5>, 5>();

    for (auto row : drawn) {
      row.fill(false);
    }
  }

  Board(Board &&) = default;
  Board(const Board &) = default;
  Board &operator=(Board &&) = default;
  Board &operator=(const Board &) = default;
  ~Board();

  void draw(int number) {
    for (int row = 0; row < 5; row++) {
      for (int col = 0; col < 5; col++) {
        if (numbers[row][col] == number) {
          drawn[row][col] = true;
        }
      }
    }
    // check if done
  }

  void check_if_done() {
    for (auto row : this->numbers) {
    }
  }

private:
  std::array<std::array<int, 5>, 5> numbers;
  std::array<std::array<bool, 5>, 5> drawn;
  bool done;
};

std::vector<int> get_draws(std::string const filename) {
  std::fstream input(filename);
  std::string stringbuf;
  std::stringstream streambuf;
  std::vector<int> resultbuf;

  std::getline(input, stringbuf);
  streambuf.str(stringbuf);

  while (std::getline(streambuf, stringbuf, ',')) {
    resultbuf.push_back(std::stoi(stringbuf));
  }

  return resultbuf;
}

std::vector<std::array<std::array<int, 5>, 5>>
get_boards(std::string const filename) {
  std::fstream input(filename);
  std::string stringbuf;
  std::stringstream streambuf;
  std::array<std::array<int, 5>, 5> boardbuf;
  std::vector<std::array<std::array<int, 5>, 5>> resultbuf;

  int currLine = 0;
  int currCol = 0;

  for (int i = 0; i < 2; i++) {
    std::getline(input, stringbuf);
  }

  while (std::getline(input, stringbuf)) {
    if (stringbuf.size() > 0) {
      streambuf.str(stringbuf);

      while (std::getline(streambuf, stringbuf, ' ')) {
        boardbuf[currLine][currCol] = std::stoi(stringbuf);
        currCol++;
      }

      currLine++;
      currCol = 0;
    } else {
      currLine = 0;
      resultbuf.push_back(boardbuf);
    }
  }

  return resultbuf;
}

int main(int argc, char *argv[]) {
  auto draws = get_draws("input");
  auto boards = get_boards("input");

  return EXIT_SUCCESS;
}
