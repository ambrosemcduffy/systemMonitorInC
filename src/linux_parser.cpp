#include "linux_parser.h"
#include "helperFile.h"

#include <dirent.h>
#include <unistd.h>

#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
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

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
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

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
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
  float noncacheBuffer = (totalUsedMemory - (buffer + cached)) / memTotal;
  return noncacheBuffer;
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime(){
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

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid [[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {}; }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
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

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
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

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid [[maybe_unused]]) { return string(); }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid [[maybe_unused]]) { return string(); }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
//string LinuxParser::Uid(int pid [[maybe_unused]]) { return string(); }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function

std::string LinuxParser::Uid(int pid){
  std::string newPid = std::to_string(pid);
  std::string uidPath = "/proc/" + newPid + "/status";
  std::ifstream file;
  std::string line;

  std::string key;
  std::string value = "fart";

  file.open(uidPath);

  while (getline(file, line)){
    std::istringstream mystream(line);
    mystream >> key >> value;
    if (key == "Uid:"){
      return value;
    }
  }
  return value;
}

string LinuxParser::User(int pid) {
  std::string line;
  std::ifstream file;
  file.open("/etc/passwd");
  while (getline(file, line)){
    std::vector<std::string> _arglist = split(line, ':');
    if (_arglist[2] == Uid(pid)){
      return _arglist[0];
    }
  }
  return " ";
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid [[maybe_unused]]) { return 0; }
