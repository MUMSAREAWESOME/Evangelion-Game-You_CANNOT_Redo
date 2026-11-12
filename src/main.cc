#include "classes.h"
#include "battle.h"
#include "read.h"
#include <iostream>
#include <memory>
#include <vector>

int main() {

  std::unique_ptr<Player> shinji {std::make_unique<Player>("Shinji", 100)};
  std::shared_ptr<Weapon> knife  {std::make_shared<Weapon>(10, "Knife")};
  std::shared_ptr<Item> lclCartridge {std::make_shared<Item>("LCL Cartridge", 3)};
  shinji->weapon = knife;
  shinji->inventory.push_back(lclCartridge);

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

  readLines(1);
  
  return 0;
}
