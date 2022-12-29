#ifndef HELPER_FILE_H
#define HELPER_FILE_H

#include <string>
#include <vector>
#include <iostream>

std::vector<std::string> split(std::string, char);
std::string slice(std::string &&, const int &&, const int &&);
void printArray(const std::vector<std::string> &);

#endif
