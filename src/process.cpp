#include "process.h"
#include <unistd.h>
#include "helperFile.h"

#include <cctype>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;


void Process::setPid(int pid){
  this->_pid = pid;
}
// TODO: Return this process's ID
int Process::Pid() {return this->_pid;}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() {
  int pid = this->Pid();
  std::string path = LinuxParser::kProcDirectory + std::to_string(pid) + LinuxParser::kStatFilename;
  std::ifstream file(path);
  std::string line;
  vector<string> values;
  while (getline(file, line)){
    vector<string> elements = split(line, ' ');
    for (auto element:elements){
      values.push_back(element);
    }
  }
  vector<string> uptimeElements;
  string utime = values[15];
  string stime = values[16];
  string cutime = values[17];
  string cstime = values[18];
  string startTime = values[23];
  string uptime;
  string newLine;
  std::ifstream uptimeFile("/proc/uptime");

  while(getline(uptimeFile, line)){
    vector<string> uptimeElements = split(line, ' ');
    uptime = uptimeElements[0];
  }

  long hertz = sysconf(_SC_CLK_TCK);
  float _uptime = stof(uptime);
  long totalTime = stol(utime) + stol(stime);
  totalTime = totalTime + stol(cutime) + stol(cstime);
  float secounds = _uptime - (stof(startTime)/hertz);
  float cpuUsage = (float)100 * (float)((totalTime/hertz/secounds));
  return cpuUsage;
}

// TODO: Return the command that generated this process
string Process::Command() { 
  int pid = Pid();
  return LinuxParser::Command(pid);
}

// TODO: Return this process's memory utilization
string Process::Ram() {
  int pid = Pid();
  return LinuxParser::Ram(pid);
}

// TODO: Return the user (name) that generated this process
string Process::User() { 
  int pid = Pid();
  std::string user = LinuxParser::User(pid);
  return user;
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { 
  int pid = Pid();
  return LinuxParser::UpTime(pid);
}


bool Process::operator<(Process & a) {
  return a.CpuUtilization() < CpuUtilization();
}
