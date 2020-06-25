#include <string>

#include "format.h"

using std::string;
using std::to_string;


// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
  
    int hours=seconds/3600;
    seconds=seconds%3600;
    int mins=seconds/60;
    int secs= seconds%60;
  
    string H,M,S;
    H=to_string(hours);
    M=to_string(mins);
    S=to_string(secs);

    if (hours<10 && mins<10 && secs<10){
       return "0"+ to_string(hours)+ ':'+"0"+to_string(mins)+':'+"0"+to_string(secs);
    }
     if(hours<10){
      H= "0"+to_string(hours);
    } if(mins<10){
      M="0"+to_string(mins);
    } if (secs<10){
      S="0"+to_string(secs);
    }

    return H + ':'+ M +':'+ S; 
  }
