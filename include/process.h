#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include "linux_parser.h"
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int pid) :PID_(pid),
 USER_(LinuxParser::User(pid)),
 CPUP_(Process::CpuUtilization()),
 COMMAND_(LinuxParser::Command(pid)),
 TTIME_(LinuxParser::UpTime(pid)) {}
  
  int Pid();                               // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp

  // TODO: Declare any necessary private members
 private:
  int PID_;
 std::string USER_;
 float CPUP_;
 std::string RAM_;
 long TTIME_;
 std::string COMMAND_;
};

#endif
