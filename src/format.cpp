#include "format.h"
#include <chrono>
#include <string>
#include <sstream>
#include <ctime>

#include <iostream>
#include <iomanip>

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
    int hours = seconds/3600;
    int minutes = (seconds % 3600)/60;
    int secs = seconds % 60;

    std::tm tm_struct;
    tm_struct.tm_hour = hours;
    tm_struct.tm_min = minutes;
    tm_struct.tm_sec = secs;

    std::stringstream ss;
    ss << std::put_time(&tm_struct, "%H:%M:%S");
    return ss.str();
}

