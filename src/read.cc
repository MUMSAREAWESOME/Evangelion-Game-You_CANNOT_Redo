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

void readLines(const int& chapter){
  int lines = 0;
  std::fstream file;
  switch (chapter) {
    case 1:
      file.open("chapter1.txt", std::ios::in);
      break;
    default:
      file.open("backstory.txt", std::ios::in);
  }
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
