#include "system.h"

#include <unistd.h>

#include <cstddef>
#include <fstream>
#include <regex>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "helperFile.h"
#include "process.h"
#include "processor.h"
#include "format.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;
/*You need to complete the mentioned TODOs in order to satisfy the rubric
criteria "The student will be able to extract and display basic data about the
system."

You need to properly format the uptime. Refer to the comments mentioned in
format. cpp for formatting the uptime.*/

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { return processes_; }

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() {
  /*
This function get the kernel verison
of the linux OS
*/
  std::string line;
  std::string kernelVersion;

  std::ifstream file;
  file.open("/proc/version");
  if (file) {
    while (getline(file, line)) {
      std::string kernelVersion = split(split(line, ' ')[2], '-')[0];
      return kernelVersion;
    }
  }
  return kernelVersion;
}

// TODO: Return the system's memory utilization
float System::MemoryUtilization() {
  /*
This function returns the cpu utilization
*/
  std::string path = "/proc/meminfo";
  std::ifstream file;
  std::string line;
  std::string key;

  int value;
  float memFree{0};
  float memTotal{0};
  float buffer{0};
  float cached{0};
  file.open(path);

  while (getline(file, line)) {
    std::stringstream mystream(line);
    mystream >> key >> value;
    if (key == "MemTotal:") {
      memTotal += value;
    }
    if (key == "MemFree:") {
      memFree += value;
    }

    if (key == "Buffers:") {
      buffer += value;
    }
    if (key == "Cached:") {
      cached += value;
    }
  }
  float totalUsedMemory = (memTotal - memFree);
  float noncacheBuffer = (totalUsedMemory-(buffer+cached))/memTotal;
  return noncacheBuffer;
}

// TODO: Return the operating system name
std::string System::OperatingSystem() {
  std::string path = "/etc/os-release";
  std::string line;
  std::string key;
  std::string value;
  std::ifstream file;

  file.open(path);
  while (getline(file, line)) {
    replace(line.begin(), line.end(), ' ', '_');
    replace(line.begin(), line.end(), '=', '_');
    replace(line.begin(), line.end(), '"', ' ');
    std::istringstream mystream(line);
    while (mystream >> key >> value) {
      if (key == "PRETTY_NAME_") {
        return value;
      }
    }
  }
  return value;
}

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() {
  std::ifstream file;
  std::string line;
  int _runningProcesses;

  file.open("/proc/stat");
  while (getline(file, line)) {
    if (line[0] != 'p') {
      continue;
    }
    std::vector<std::string> _keyValueList = split(line, ' ');
    if (_keyValueList[0] == "procs_running") {
      std::istringstream mystream(_keyValueList[1]);
      mystream >> _runningProcesses;
      return _runningProcesses;
    }
  }
  return _runningProcesses;
}

// TODO: Return the total number of processes on the system
int System::TotalProcesses() {
  std::ifstream file;
  std::string line;

  file.open("/proc/stat");
  int total;
  while (getline(file, line)) {
    if (line[0] != 'p') {
      continue;
    }
    std::vector<std::string> _keyValueList = split(line, ' ');
    if (_keyValueList[0] == "processes") {
      std::istringstream mystream(_keyValueList[1]);
      mystream >> total;
      return total;
    }
  }
  return total;
}

// TODO: Return the number of seconds since the system started running
long int System::UpTime() {
  std::ifstream file;
  std::string line;
  long int _uptime;
  file.open("/proc/uptime");
  while (getline(file, line)) {
    std::istringstream mystream(split(line, '.')[0]);
    mystream >> _uptime;
    return _uptime;
  }
  return _uptime;
}
