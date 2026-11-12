#include "read.h"
#include <cctype>
#include <fstream>
#include <iostream>

void wait(){
  char a;
  while (true){
    std::cin >> a;
    a = std::tolower(a);
    if (a == 'c') break;
    else continue;
  }
}

void readLines(const std::string& chapPath){
  int lines = 0;
  std::fstream file;
  file.open(chapPath, std::ios::in);
  std::string line;
  while (std::getline(file, line)){
    if (lines == 10){
      wait();
    }
    else{
      std::cout << line << '\n';
    }
  } 
}
