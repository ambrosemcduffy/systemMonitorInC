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
  //std::vector<std::string> arrStringTime = split(line, ' ');
  //std::vector<long int> arrIntTime = convertStringTimeToInt(arrStringTime);
  return getCpuPercentage();
}


std::vector<long int> convertStringTimeToInt(
    const std::vector<std::string> &arrStringTime) {
  std::vector<long int> arrIntTime;
  for (std::string _time : arrStringTime) {
    if (_time == "cpu" || _time == " "){
        continue;
    }
    long int convertedTime;
    std::istringstream mystream(_time);
    mystream >> convertedTime;
    arrIntTime.push_back(convertedTime);
  }
  return arrIntTime;
}

float getCpuPercentage() {
  std::vector<unsigned long long int> prevData = getCpuUtilization();
  unsigned long long int prevTotal = prevData[0];
  unsigned long long int prevIdle = prevData[1];
  std::this_thread::sleep_for(std::chrono::milliseconds(500));

  std::vector<unsigned long long int> currentData = getCpuUtilization();
  unsigned long long int total = currentData[0];
  unsigned long long int idle = currentData[1];

  unsigned long long int completeTotal = total - prevTotal;
  unsigned long long int completeIdle = idle - prevIdle;
  float _total = (float)(completeTotal - completeIdle) /completeTotal;
  return _total;
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

std::vector<unsigned long long int> getCpuUtilization(){
  std::ifstream file;
  file.open("/proc/stat");
  std::string line;
  unsigned long long int _total{0};
  unsigned long long int _idleTime{0};
  while (getline(file, line)){
    std::istringstream mystream(line);
    std::string throwaway;
    mystream >> throwaway;
    unsigned long long int user, nice, system, idle, iowait, irq, softIrq, steal, guest, guestNice;
    mystream >> user >> nice >> system >> idle >> iowait >> irq >> softIrq >> steal >> guest >> guestNice;
    unsigned long long int nonIdleTime = user + nice + system + irq + softIrq + steal;
    unsigned long long int idleTime = idle + iowait;
    _idleTime += idleTime;
    _total += idleTime + nonIdleTime;
    break;
  }
  return {_total, _idleTime};
}