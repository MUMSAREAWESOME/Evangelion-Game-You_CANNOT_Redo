#include "read.h"
#include <cctype>
#include <fstream>
#include <iostream>

void wait(){
  std::cout << "Enter to continue: ";
  std::cin.ignore();
}

void readLines(const std::string& chapPath){
  int lines = 0;
  std::fstream file;
  file.open(chapPath, std::ios::in);
  std::string line;
  while (std::getline(file, line)){
    if (lines == 10) wait();
    std::cout << line << '\n';
    lines ++;
  } 
}
