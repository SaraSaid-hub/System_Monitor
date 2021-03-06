#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os,version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version>> kernel;
  }
  return kernel;
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
  string line;
  string key;
  float value;
  float Total_mem;
  float Free_mem;
  float perc_Used_mem;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "MemTotal:") {
          
          Total_mem= value;
        }
        else if(key == "MemFree:"){
              Free_mem=value;
              perc_Used_mem=(Total_mem - Free_mem)/(Total_mem);
              return perc_Used_mem;
        }
      }
    }
  }
  return 0.0;
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() {
  
  long time;
  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> time;

  }
  return time;
   }



// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) {
  
  string PID= std::to_string(pid);
  string line;
  long utime,stime,cutime,cstime;
  long Total_time;
  string s;
  int i=0;
  std::ifstream stream(kProcDirectory + PID + kStatFilename);
  if (stream.is_open()) {
    
   while(std::getline(stream, line)) {

     std::istringstream linestream(line);
       
       while(linestream >> s){

        if(i==13){
            utime=std::stol(s) ;
        }
        else if(i==14){
            stime=std::stol(s); 
        }
        else if(i==15){
            cutime=std::stol(s) ;
        }

         else if(i==16){
           cstime=std::stol(s) ;
          Total_time=utime+stime+cutime+cstime;
          return Total_time;
         }
         i++;
       }
      
    }
    
    
  }
  return 0;  
  
   }



// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  
  string line;
  string key;
  string cpu_value;
  vector<string> v;

  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    
   std::getline(stream, line);
   std::istringstream linestream(line);
     linestream >> key;
     if (key=="cpu"){
       while(linestream >> cpu_value){
       v.push_back(cpu_value);
       }
       return v;
     }  

  }
  return {};
   }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  
  string line;
  string key;
  int value;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "processes") {
          
          return value;
        }
      }
    }
  }
  
  return 0;
   }

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  
  string line;
  string key;
  int value;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "procs_running") {
          
          return value;
        }
      }
    }
  }
  
  return 0;
   }

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 
  
  string PID= std::to_string(pid);
  string line;
  std::ifstream stream(kProcDirectory + PID + kCmdlineFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> line;
  }
  return line; 
   }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) {
  
  string PID= std::to_string(pid);
  string line;
  string key;
  string value;
  std::ifstream filestream(kProcDirectory + PID + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "VmSize:") {
      int mem_megabyte=(std::stoi(value))/1000;
      string mem=std::to_string(mem_megabyte);
          return mem;
        }
      }
    }
  }
  return "";
   }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) {
  
   string PID= std::to_string(pid);
  string line;
  string key;
  string value;
  std::ifstream filestream(kProcDirectory + PID + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value ;
        if (key == "Uid:") {
      
          return value;
        }
    }
  }
  return value;
   }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
  
   string uid=Uid(pid);
  string line;
  string user;
  string var;
  string UID;
  std::ifstream filestream(kPasswordPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      linestream >> user >> var >> UID ;
        if (UID == uid) {
      
          return user;
        }
      
    }
  }
  return user;
  }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 
  
   string PID= std::to_string(pid);
  string line;
  int i=0;
  long time;
  string s;
  std::ifstream stream(kProcDirectory + PID + kStatFilename);
  if (stream.is_open()) {
    
   while(std::getline(stream, line)) {

     std::istringstream linestream(line);
     
       
       while(linestream >> s){

         if(i==21){
           time=std::stol(s) ;
           auto start_time_s = time / sysconf(_SC_CLK_TCK);
          return (UpTime() - (start_time_s));
         }
         i++;
       }
       
    }
    
  }
  return 0;
   }
