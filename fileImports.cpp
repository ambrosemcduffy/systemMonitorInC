#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <vector>

#include "helperFile.h"

std::string getOsInfo() {
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

int getMemUtilization() {
    /*
    This function returns the cpu utilization
    */
  std::string path = "/proc/meminfo";
  std::ifstream file;
  std::string line;
  std::string key;

  int value;
  int memFree{0};
  int memTotal{0};
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
  }
  return memTotal - memFree;
}

std::string getKernelVersion() {
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


std::map<std::string, std::string> getNumProcesses() {
  std::ifstream file;
  std::string line;
  std::map<std::string, std::string> processDict;
  file.open("/proc/stat");

  while (getline(file, line)) {
    if (line[0] != 'p') {
      continue;
    }
    std::vector<std::string> _keyValueList = split(line, ' ');
    if (_keyValueList[0] == "processes") {
      processDict["processes"] = _keyValueList[1];
    }

    if (_keyValueList[0] == "procs_running") {
      processDict["procs_running"] = _keyValueList[1];
    }
  }
  return processDict;
}

std::string getUpTime() {
  std::ifstream file;
  std::string line;
  file.open("/proc/uptime");
  while (getline(file, line)) {
    return line;
  }
  return line;
}

int main() {
  std::cout << "Current Uptime: " << getUpTime() << std::endl;
  std::cout << "Number of Processes: " << getNumProcesses()["processes"]
            << std::endl;
  std::cout << "Total Number of Processes: "
            << getNumProcesses()["procs_running"] << std::endl;
  std::cout << "Kernel Version: " << getKernelVersion() << std::endl;
  std::cout << "Memory Usage: " << getMemUtilization() << std::endl;
  std::cout << "Operating system in use: " << getOsInfo() << std::endl;
}
