#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"




using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() { return   PID_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
    long Totaltime=  LinuxParser::ActiveJiffies(PID_);
    long elapsed_time= LinuxParser::UpTime(PID_);
    if(elapsed_time>0)
    CPUP_=100.0*((Totaltime/ sysconf(_SC_CLK_TCK))/elapsed_time);
    else 
        CPUP_=100.0*(Totaltime/ sysconf(_SC_CLK_TCK));
    return CPUP_;  }

// TODO: Return the command that generated this process
string Process::Command() { return COMMAND_;}

// TODO: Return this process's memory utilization
string Process::Ram() { 
    RAM_=LinuxParser::Ram(PID_);
  return RAM_; }

// TODO: Return the user (name) that generated this process
string Process::User() { return USER_; }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return TTIME_; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { return   CPUP_ < (a.CPUP_) ;}
