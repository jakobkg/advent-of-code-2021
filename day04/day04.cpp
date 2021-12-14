#include <algorithm>
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
    this->marked = std::array<std::array<bool, 5>, 5>();

    for (auto row : numbers) {
      row.fill(0);
    }

    for (auto row : marked) {
      row.fill(false);
    }
  }

  Board(std::array<std::array<int, 5>, 5> numbers) {
    this->done = false;
    this->numbers = numbers;
    this->marked = std::array<std::array<bool, 5>, 5>();

    for (auto row : marked) {
      row.fill(false);
    }
  }

  Board(Board &&) = default;
  Board(const Board &) = default;
  Board &operator=(Board &&) = default;
  Board &operator=(const Board &) = default;
  ~Board() = default;

  void mark(int number) {
    for (int row = 0; row < 5; row++) {
      for (int col = 0; col < 5; col++) {
        if (numbers[row][col] == number) {
          marked[row][col] = true;
        }
      }
    }
    this->check_if_done();
  }

  void check_if_done() {
    for (int i = 0; i < 5; i++) {
      if (std::all_of(this->marked[i].begin(), this->marked[i].end(),
                      [](bool b) { return b; })) {
        this->done = true;
        return;
      }
      int j = 0;
      for (; j < 5; j++) {
        if (!this->marked[i][j]) {
          break;
        }
      }
      if (j == 5) {
        this->done = true;
        return;
      }
    }
  }

  bool is_done() const { return this->done; }

  std::array<std::array<int, 5>, 5> get_numbers() const {
    return this->numbers;
  }

private:
  std::array<std::array<int, 5>, 5> numbers;
  std::array<std::array<bool, 5>, 5> marked;
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

std::ostream &operator<<(std::ostream &out, const Board board) {
  for (auto row : board.get_numbers()) {
    for (auto number : row) {
      out << number << ' ';
    }
    out << std::endl;
  }

  return out;
}

std::vector<Board> get_boards(std::string const filename) {
  std::fstream input(filename);
  std::string stringbuf;
  std::stringstream streambuf;
  std::array<std::array<int, 5>, 5> boardbuf;
  std::vector<Board> resultbuf;

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
      resultbuf.push_back(Board(boardbuf));
    }
  }

  return resultbuf;
}

int main(int argc, char *argv[]) {
  auto draws = get_draws("input");
  auto boards = get_boards("input");
  bool done = false;
  Board winner;

  for (Board board : boards) {
    std::cout << board << std::endl << std::endl;
  }
  /*
    for (auto draw : draws) {
      for (auto board : boards) {
        board.mark(draw);

        if (board.is_done()) {
          winner = board;
          done = true;
          break;
        }
      }

      if (done) {
        break;
      }
    }

    std::cout << winner << std::endl; */

  return EXIT_SUCCESS;
}
