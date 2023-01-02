#include "processor.h"

#include <fstream>
#include <sstream>
#include <thread>
#include <vector>

#include "helperFile.h"

// TODO: Return the aggregate CPU utilization

float Processor::Utilization() {
  std::ifstream file;
  file.open("/proc/stat");

  std::string line;
  getline(file, line);
  std::vector<std::string> arrStringTime = split(line, ' ');
  std::vector<long int> arrIntTime = convertStringTimeToInt(arrStringTime);
  float percentage = getCpuPercentage(arrIntTime);
  std::cout << percentage << std::endl;
  return percentage;
}


std::vector<long int> convertStringTimeToInt(
    const std::vector<std::string> &arrStringTime) {
  std::vector<long int> arrIntTime;
  for (std::string _time : arrStringTime) {
    if (_time == "cpu" || _time == " "){
        continue;
    }
    std::cout << _time << " ";
    long int convertedTime;
    std::istringstream mystream(_time);
    mystream >> convertedTime;
    arrIntTime.push_back(convertedTime);
  }
  std::cout << "\n";
  return arrIntTime;
}

float getCpuPercentage(const std::vector<long int> &arrIntTime) {
  std::vector<int> prevData = getTotalTime(arrIntTime);
  int prevTotal = prevData[0];
  int prevIdle = prevData[1];
  std::cout << "printing previous Data " << prevData[0] << " " << prevData[1] << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(500));

  std::vector<int> currentData = getTotalTime(arrIntTime);
  std::cout << "printing current Data " << currentData[0] << " " << currentData[1] << std::endl;
  int total = currentData[0];
  int idle = currentData[1];

  int completeTotal = total - prevTotal;
  int completeIdle = idle - prevIdle;
  std::cout << "printing complete total and idle" << std::endl;
  std::cout << completeIdle << " " << completeTotal << std::endl;
  return static_cast<float>((completeTotal - completeIdle) / completeTotal);
}

std::vector<int> getTotalTime(const std::vector< long int> &arrIntTime) {
  int Idle = arrIntTime[4] + arrIntTime[5];
  int NonIdle;
  getSumOfNonIdle(NonIdle, arrIntTime);
  return {(Idle + NonIdle), Idle};
}

void getSumOfNonIdle(int &NonIdle, const std::vector<long int> &arrIntTime) {
  for (int i; i < static_cast<int>(arrIntTime.size()); i++) {
    if (i == 4 || i == 5) {
      continue;
    }
    if (i > 7) {
      break;
    }
    NonIdle += arrIntTime[i];
  }
}
