#include "processor.h"

#include <fstream>
#include <sstream>
#include <thread>
#include <vector>

#include "helperFile.h"

// TODO: Return the aggregate CPU utilization

float Processor::Utilization() { return getCpuPercentage(); }

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
  float _total = (float)(completeTotal - completeIdle) / completeTotal;
  return _total;
}

std::vector<unsigned long long int> getCpuUtilization() {
  std::ifstream file;
  file.open("/proc/stat");
  std::string line;
  unsigned long long int _total{0};
  unsigned long long int _idleTime{0};
  while (getline(file, line)) {
    std::istringstream mystream(line);
    std::string throwaway;
    mystream >> throwaway;
    unsigned long long int user, nice, system, idle, iowait, irq, softIrq,
        steal, guest, guestNice;
    mystream >> user >> nice >> system >> idle >> iowait >> irq >> softIrq >>
        steal >> guest >> guestNice;
    unsigned long long int nonIdleTime =
        user + nice + system + irq + softIrq + steal;
    unsigned long long int idleTime = idle + iowait;
    _idleTime += idleTime;
    _total += idleTime + nonIdleTime;
    break;
  }
  return {_total, _idleTime};
}