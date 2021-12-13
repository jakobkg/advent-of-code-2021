#include <bitset>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

template <int width>
std::vector<std::bitset<width>> read_data(std::string const filename) {
  std::fstream input(filename);

  std::vector<std::bitset<width>> data;
  std::string stringbuf;

  while (input >> stringbuf) {
    data.push_back(std::bitset<width>(stringbuf));
  }

  return data;
}

template <int width>
bool most_common_at_position(std::vector<std::bitset<width>> const data,
                             unsigned int const pos) {
  unsigned int sum = 0;

  for (auto element : data) {
    sum += element[pos];
  }

  return sum >= data.size() / 2;
}

template <int width>
std::bitset<width> most_common(std::vector<std::bitset<width>> const data) {
  std::bitset<width> result;

  for (int pos = 0; pos < width; pos++) {
    result.set(pos, most_common_at_position<width>(data, pos));
  }

  return result;
}

template <int width>
bool least_common_at_position(std::vector<std::bitset<width>> const data,
                              unsigned int const pos) {
  unsigned int sum = 0;

  for (auto element : data) {
    sum += element[pos];
  }

  return sum < data.size() / 2;
}

template <int width>
std::bitset<width> least_common(std::vector<std::bitset<width>> const data) {
  std::bitset<width> result;

  for (int pos = 0; pos < width; pos++) {
    result.set(pos, least_common_at_position<width>(data, pos));
  }

  return result;
}

template <int width>
std::bitset<width> oxygen_rating(std::vector<std::bitset<width>> const data) {
  std::bitset<width> result;
  auto mutable_data = data;
  std::vector<std::bitset<width>> tmp_data;
  bool most_common_value;

  for (int pos = width - 1; 0 <= pos; pos--) {
    most_common_value = most_common_at_position<width>(mutable_data, pos);
    std::cout << "Most common element at pos " << pos << ": "
              << most_common_value << std::endl;

    if (mutable_data.size() > 1) {
      for (auto element : mutable_data) {
        if (element[pos] == most_common_value) {
          tmp_data.push_back(element);
        }
      }

      mutable_data = tmp_data;
      tmp_data.clear();
      std::cout << "Remaining elements: " << mutable_data.size() << std::endl;
    }
  }

  std::cout << mutable_data[0].to_string() << std::endl;
  return mutable_data[0];
}

int main(int argc, char *argv[]) {
  std::cout << "Part 1:" << std::endl;

  auto data = read_data<12>("input");
  auto gammabitset = most_common<12>(data);
  auto gamma = gammabitset.to_ulong();
  auto epsilonbitset = least_common<12>(data);
  auto epsilon = epsilonbitset.to_ulong();

  std::cout << "Gamma: " << gamma << std::endl;
  std::cout << "Epsilon: " << epsilon << std::endl;
  std::cout << "Power consumption: " << epsilon * gamma << std::endl;

  std::cout << "Part 2:" << std::endl;

  auto oxygenbitset = oxygen_rating<12>(data);
  std::cout << "Oxygen generator rating: " << oxygenbitset.to_ulong()
            << std::endl;

  return EXIT_SUCCESS;
}
