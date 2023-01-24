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
float Process::CpuUtilization() { return 0.0; }

// TODO: Return the command that generated this process
string Process::Command() { return "hey"; }

// TODO: Return this process's memory utilization
string Process::Ram() { return string(); }

// TODO: Return the user (name) that generated this process
string Process::User() { 
  int pid = Pid();
  std::string user = LinuxParser::User(pid);
  return user;
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return 0; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
//bool Process::operator<(Process const& a) const {
//  return true;
//}
