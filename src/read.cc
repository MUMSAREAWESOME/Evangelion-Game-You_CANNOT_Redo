#include "read.h"
#include <cctype>
#include <fstream>
#include <iostream>

void wait(){
  while (true){
    std::cout << "Enter to continue: ";
    std::cin.ignore();
    break;
  }
}

void readLines(const std::string& chapPath){
  int lines = 0;
  std::fstream file;
  file.open(chapPath, std::ios::in);
  std::string line;
  std::cin.ignore();
  while (std::getline(file, line)){
    if (lines == 5) wait();
    std::cout << line << '\n';
    lines ++;
  } 
}
