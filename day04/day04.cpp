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
    this->bingo = false;
    this->numbers = std::array<std::array<int, 5>, 5>();
    this->marked = std::array<std::array<bool, 5>, 5>();
  }

  Board(std::array<std::array<int, 5>, 5> numbers) {
    this->bingo = false;
    this->numbers = numbers;
    this->marked = std::array<std::array<bool, 5>, 5>();
  }

  Board(Board &&) = default;
  Board(const Board &) = default;
  Board &operator=(Board &&) = default;
  Board &operator=(const Board &) = default;
  ~Board() = default;

  friend std::ostream &operator<<(std::ostream &out, const Board &board) {
    for (auto row : board.getNumbers()) {
      for (auto number : row) {
        out << number << ' ';
      }
      out << std::endl;
    }

    return out;
  }

  void mark(int number) {
    for (int row = 0; row < 5; row++) {
      for (int col = 0; col < 5; col++) {
        if (this->numbers[row][col] == number) {
          this->marked[row][col] = true;
        }
      }
    }
    this->checkIfDone();
  }

  bool hasBingo() const { return this->bingo; }

  std::array<std::array<int, 5>, 5> getNumbers() const { return this->numbers; }

  int calculateScore(int drawn) const {
    int sum = 0;

    for (int row = 0; row < 5; row++) {
      for (int col = 0; col < 5; col++) {
        if (!this->marked[row][col]) {
          sum += this->numbers[row][col];
        }
      }
    }

    return sum * drawn;
  }

private:
  std::array<std::array<int, 5>, 5> numbers;
  std::array<std::array<bool, 5>, 5> marked;
  bool bingo;

  void checkIfDone() {
    for (auto row : this->marked) {
      if (std::all_of(row.begin(), row.end(), [](bool b) { return b; })) {
        this->bingo = true;
        return;
      }
    }

    std::array<std::array<bool, 5>, 5> tmp;

    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        tmp[j][i] = this->marked[i][j];
      }
    }

    for (auto col : tmp) {
      if (std::all_of(col.begin(), col.end(), [](bool b) { return b; })) {
        this->bingo = true;
        return;
      }
    }
  }
};

std::vector<int> getDraws(std::string const filename) {
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

std::vector<Board> getBoards(std::string const filename) {
  std::fstream input(filename);
  std::string stringbuf;
  int numbuf;
  std::array<std::array<int, 5>, 5> boardbuf = {{0}};
  std::vector<Board> resultbuf;

  int currLine = 0;
  int currCol = 0;

  for (int i = 0; i < 2; i++) {
    std::getline(input, stringbuf);
  }

  while (std::getline(input, stringbuf)) {
    if (stringbuf.size() > 0) {
      for (std::istringstream num_iss(stringbuf); num_iss >> numbuf;) {
        boardbuf[currLine][currCol] = numbuf;
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

std::pair<Board, int> firstWinner(std::vector<int> const draws,
                                  std::vector<Board> const boards) {
  std::vector<Board> boardscopy = boards;
  for (int draw : draws) {
    for (Board &board : boardscopy) {
      board.mark(draw);

      if (board.hasBingo()) {
        return std::pair<Board, int>(board, draw);
      }
    }
  }

  return std::pair<Board, int>();
}

std::pair<Board, int> lastWinner(std::vector<int> const draws,
                                 std::vector<Board> const boards) {
  std::vector<Board> boardscopy = boards;
  int lastdraw, winners = 0;
  Board lastWinningBoard;

  for (int draw : draws) {
    for (Board &board : boardscopy) {
      if (!board.hasBingo()) {
        board.mark(draw);
        if (board.hasBingo()) {
          winners++;
          lastWinningBoard = board;
          lastdraw = draw;
        }
      }
    }

    if (winners == boardscopy.size()) {
      break;
    }
  }

  return std::pair<Board, int>(lastWinningBoard, lastdraw);
}

int main(int argc, char *argv[]) {
  auto draws = getDraws("input");
  auto boards = getBoards("input");

  std::cout << "Part 1" << std::endl;
  auto firstwin = firstWinner(draws, boards);
  auto winner = firstwin.first;
  auto final_draw = firstwin.second;
  std::cout << "The first winning board was:\n" << winner << std::endl;
  std::cout << "The score of this board is "
            << winner.calculateScore(final_draw) << std::endl;

  std::cout << "\nPart 2" << std::endl;
  auto lastwin = lastWinner(draws, boards);
  winner = lastwin.first;
  final_draw = lastwin.second;
  std::cout << "The last winning board was:\n" << winner << std::endl;
  std::cout << "The score of this board is "
            << winner.calculateScore(final_draw) << std::endl;
  return EXIT_SUCCESS;
}
