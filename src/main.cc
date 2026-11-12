#include "classes.h"
#include "battle.h"
#include "read.h"
#include <cctype>
#include <iostream>
#include <memory>
#include <vector>

void shop(int& money, std::shared_ptr<Weapon>& weapon, std::shared_ptr<Item>& health){
  char choice;
  std::cout << "(B)uy gun [50$], B(u)y a heal [1$]: ";
  choice = std::tolower(choice);
  switch (choice){
    case 'b':
      if (money >= 50 && weapon->name != "Rifle"){
        money -= 50;
        std::shared_ptr<Weapon> gun {std::make_shared<Weapon>(20, "Rifle")};
        weapon = gun;
        std::cout << "Bought a gun! Replaced knife!\n";
      }
      else{
        std::cout << "You are too poor to afford a gun!\n";
      }
      break;
    case 'u':
      if (money >= 1 && health->amount < 3){
        money -= 1;
        health->amount ++;
        std::cout << "Bought 1 heal!\n";
      }
      else{
        std::cout << "You are too poor to afford one heal!\n";
      }
      break;
    default:
      std::cout << "Choice not recognisedn";
      break;
  }
}


int main() {

  std::unique_ptr<Player> shinji {std::make_unique<Player>("Shinji", 100)};
  std::shared_ptr<Weapon> knife  {std::make_shared<Weapon>(10, "Knife")};
  std::shared_ptr<Item> lclCartridge {std::make_shared<Item>("LCL Cartridge", 3)};
  shinji->weapon = knife;
  shinji->inventory.push_back(lclCartridge);

  char choice;

  while (true) {
    std::cout << "(B)attle, (R)ead story, (S)hop: ";
    std::cin >> choice;
    choice = std::tolower(choice);
    if (choice == 'b'){     
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
    }
    else if (choice == 'r'){
      int win;
      switch (shinji->chapter){
        case 1:
          readLines("chapter1/p1.txt"); // Read part 1 of chapter 1
          while (true){
            win = Battle(*shinji);
            if (win == 0) break;
            else {
              std::cout << "You must win the battle to continue!\n";
              shinji->health = 100;
              continue;
            }
          }
          readLines("chapter1/p2.txt"); // Read part 2 of chapter 1
          readLines("chapter1/p3.txt"); // Read part 3 of chapter 1
          shinji->money += 15; // For reading my horrid writing!
          shinji->chapter ++;
          break;
        default:
          std::cout << "You are currently at an unreachable chapter! Resetting to start of the story!\n";
          shinji->chapter = 1;
          break;
      }
    }
    else if (choice == 's'){
      shop(shinji->money, shinji->weapon, shinji->inventory.front());
    }
    else{
      std::cout << "Input not found!\n";
      continue;
    }
  }
  
  return 0;
}
