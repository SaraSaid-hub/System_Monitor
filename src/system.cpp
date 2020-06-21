#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { 
  vector<int> Processes_pid=LinuxParser::Pids();
  for (int i=0; i<Processes_pid.size();i++ ){
    processes_.push_back(Process(Processes_pid[i]));
  }
  sort(processes_.begin(),processes_.end(),[](Process p1, Process p2){return p1<p2;});
  return processes_; }

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() {
  Kernel_=LinuxParser::Kernel();
  return Kernel_ ; }

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { 
  Memory_= LinuxParser::MemoryUtilization();
   return Memory_; }

// TODO: Return the operating system name
std::string System::OperatingSystem() { 
  OS_=LinuxParser::OperatingSystem();
    return OS_ ;   }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() {
  RunningProcesses_=LinuxParser::RunningProcesses();

     return RunningProcesses_; }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() {
  TotalProcesses_=LinuxParser::TotalProcesses();

     return TotalProcesses_; }

// TODO: Return the number of seconds since the system started running
long int System::UpTime() {  
    UpTime_=LinuxParser::UpTime();
    return UpTime_; }
