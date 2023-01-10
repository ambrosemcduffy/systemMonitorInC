#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <vector>
#include <string>

std::vector<long int> convertStringTimeToInt(const std::vector<std::string> &);
float getCpuPercentage();
std::vector<int> getTotalTime(const std::vector<long int> &);
void getSumOfNonIdle(int &, const std::vector<long int> &);
std::vector<unsigned long long int> getCpuUtilization();




class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
};

#endif