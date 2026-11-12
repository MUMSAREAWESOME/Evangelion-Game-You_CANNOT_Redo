#include "classes.h"
#include "battle.h"
#include "read.h"
#include <cctype>
#include <iostream>
#include <memory>
#include <vector>

int main() {

  std::unique_ptr<Player> shinji {std::make_unique<Player>("Shinji", 100)};
  std::shared_ptr<Weapon> knife  {std::make_shared<Weapon>(10, "Knife")};
  std::shared_ptr<Item> lclCartridge {std::make_shared<Item>("LCL Cartridge", 3)};
  shinji->weapon = knife;
  shinji->inventory.push_back(lclCartridge);

  char choice;

  while (true) {
    std::cin >> choice;
    choice = std::tolower(choice);

    switch (choice){
      case 'b':
        const int win {Battle(*shinji)};
        switch (win) {
          case 0:
            std::cout << "\033[32mWIN!\033[0m\n";
            break;
          case 1:
            std::cout << "\033[31mLost!\033[0m\n";
            break;
          case 2:
            std::cout << "FLED!\n";
            break;
          default:
            std::cout << "\033[35mHow the fuck did you somehow not win and also not loose or flee?\033[0m\n";
            break;
        }
        break;  
      case 's':
        switch (shinji->chapter){
          case 1:
            readLines("chapter1/p1.txt"); // Read part 1 of chapter 1
            Battle(*shinji);
            readLines("chapter1/p2.txt"); // Read part 2 of chapter 1
            readLines("chapter1/p3.txt"); // Read part 3 of chapter 1
            break;
        }
        break;
    }
  }


  return 0;
}
