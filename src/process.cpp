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
  std::string path = "/proc/" + std::to_string(pid) + "/stat";
  std::ifstream file;
  file.open(path);
  std::string line;
  std::vector<std::string>  _arr;
  while(getline(file, line)){
    _arr = split(line, ' ');
  }

  long _jiffie;
  int cnt{0};
  std::vector<long> _jiffies;
  for (std::string jiffie:_arr){
    std::istringstream mystream(jiffie);
    if(cnt == 14 || cnt == 22){
      mystream >> _jiffie;
      _jiffies.push_back(_jiffie);
    }
    cnt ++;
  }

  int tempHz = 1000000;
  long totalTime = _jiffies[0] + _jiffies[1];
  totalTime = totalTime + _jiffies[3] + _jiffies[4];
  long seconds = UpTime() - (_jiffies[5]/tempHz);
  long cpuUsage = 100 * ((totalTime/tempHz/seconds));
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

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
//bool Process::operator<(Process const& a) const {
//  return true;
//}
