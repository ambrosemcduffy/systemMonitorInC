#include "helperFile.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> split(std::string token, char delimiter) {
  std::vector<std::string> tokens;
  std::istringstream mystream(token);
  while (std::getline(mystream, token, delimiter)) {
    tokens.push_back(token);
  }
  return tokens;
}

std::string slice(std::string &&token, const int &&index1, const int &&index2) {
  std::string newToken(token.begin() + index1, token.end() - index2);
  return newToken;
}

void printArray(const std::vector<std::string> &arr) {
  for (auto i : arr) {
    std::cout << i << std::endl;
  }
}
