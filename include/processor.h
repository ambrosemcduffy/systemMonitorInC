#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <string>
#include <vector>

float getCpuPercentage();
std::vector<unsigned long long int> getCpuUtilization();

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
};

#endif