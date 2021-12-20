#include <array>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <vector>

std::array<unsigned long long int, 9> read_data(std::string filename) {
  std::fstream input(filename);
  std::vector<unsigned char> databuf;
  std::array<unsigned long long int, 9> countbuf;
  countbuf.fill(0);
  std::string stringbuf;

  while (std::getline(input, stringbuf, ',')) {
    databuf.push_back(std::stoi(stringbuf));
  }

  for (auto fish : databuf) {
    countbuf[fish]++;
  }

  return countbuf;
}

unsigned long long int
simulate(std::array<unsigned long long int, 9> const initial_state,
         int const days) {
  std::array<unsigned long long int, 9> today = initial_state, tomorrow;
  tomorrow.fill(0);

  for (int day = 0; day < days; day++) {
    for (int i = 1; i < 9; i++) {
      tomorrow[i - 1] = today[i];
    }

    tomorrow[6] += today[0];
    tomorrow[8] += today[0];

    today = tomorrow;
    tomorrow.fill(0);
  }

  unsigned long long int sum = 0;
  for (auto count : today) {
    sum += count;
  }

  return sum;
}

int main(int argc, char *argv[]) {
  auto initial_state = read_data("input");

  std::cout << "Part 1: " << simulate(initial_state, 80)
            << " fish after 80 days" << std::endl;
  std::cout << "Part 2: " << simulate(initial_state, 256)
            << " fish after 256 days" << std::endl;
  return EXIT_SUCCESS;
}
