#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include "helpFile.h"
//void readMemUtilization(){}


using namespace std;
string getOsInfo(){
    string path = "/etc/os-release";
    string line;
    string key;
    string value;
    ifstream file;

    file.open(path);
    while (getline(file, line)){
        replace(line.begin(), line.end(), ' ', '_');
        replace(line.begin(), line.end(), '=', '_');
        replace(line.begin(), line.end(), '"', ' ');
        istringstream mystream(line);
        while(mystream >> key >> value){
            if (key == "PRETTY_NAME_"){
                return value;
            }
        }
    }
    return value;
}


int getMemUtilization(){
    string path = "/proc/meminfo";
    ifstream file;
    string line;
    string key;
    
    int value; 
    int memFree{0};
    int memTotal{0};
    file.open(path);
    
    while (getline(file, line)){
        stringstream mystream(line);
        mystream >> key >> value;
        if (key == "MemTotal:"){
            memTotal += value;
        }
        if (key == "MemFree:"){
            memFree += value;
        }
    }
    return memTotal - memFree;
}


string getKernelVersion(){
    string line;
    string version;
    string path = "/proc/version";
    ifstream file;
    file.open(path);
    if (file){
        while (getline(file, line)){
            vector<string> _arr1 = split(line, ' ');
            printArray(_arr1);
            //vector<string> elementArray = split(_arr1[2], '-');
            //version = elementArray[0];
            //return slice(std::move(version), std::move(0), std::move(0));
        }
    }
    return version;

}


int main(){
    std::cout << getKernelVersion() << std::endl;;
    //std::cout << getMemUtilization() << std::endl;
    //std::cout << getOsInfo() << std::endl;
}