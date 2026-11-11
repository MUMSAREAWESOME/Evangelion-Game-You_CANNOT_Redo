#include <cctype>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <vector>

class Item{
  public:
    std::string type;
    int amount;

    Item(const std::string& Type, const int& Amount){
      type = Type;
      amount = Amount;
    }
};

class Weapon{
  public:
    int damage;
    std::string name;

    Weapon(const int& Damage, const std::string& Name){
      damage = Damage;
      name = Name;
    }
};

class Player {
  public:
    std::vector<std::shared_ptr<Item>> inventory;
    std::string name;
    int health;
    std::shared_ptr<Weapon> weapon;

    Player(const std::string& Name, const int& Health){
      name = Name;
      health = Health;
    }

    void Heal(){
      if (inventory[0]->amount > 0 && health < 100){
        health += (100 - health); // Heals player to max health
        inventory[0]->amount --;
        std::cout << "Healed to full health!\n";
      }
      else if (inventory[0]->amount > 0 && health == 100){
        std::cout << "Failed to heal! Already at max health\n";
      }
      else{
        std::cout << "Failed to heal! Out of heals!\n";
      }
    }
};


class Enemy{
  public:
    int health;
    int damage;
    std::string name;

    Enemy(const int& Health, const int& Damage, const std::string& Name){
      health = Health;
      damage = Damage;
      name = Name;
    }
};



int randomRange(const int& a, const int& b){
     std::random_device rd; // obtain a random number from hardware
     std::mt19937 gen(rd()); // seed the generator
     std::uniform_int_distribution<> distr(a, b); // define the range

     return distr(gen);
} 


void attack(Enemy& enemy, Player& player, const bool& target){

  if (enemy.health < 0) return;
  
  if (target){
    int failChance = randomRange(1, 100);

    if (failChance > 25 && failChance < 90){
      enemy.health -= player.weapon->damage;
      std::cout << "You damaged the enemy!\n";
    }
    else if (failChance >= 90){
      enemy.health -= (player.weapon->damage * 2);
      std::cout << "Critical Hit!\n";
    }
    else{
      std::cout << "You fumbled the attack!\n";
    }
  }
  else{
    int failChance = randomRange(1, 100);

    if (failChance > 25){
      player.health -= enemy.damage;
      std::cout << "Took " << enemy.damage << " damage!\n";
    }
    else if (failChance >= 95){
      player.health -= enemy.damage + 2;
      std::cout << "Enemy got a CRIT! Lost: " << enemy.damage + 2 << " health!" << '\n';
    }
    else{
      std::cout << "Enemy fumbled the attack!\n";
    }
  }
}

int Battle(Player& player){
  Enemy *enemy = new Enemy(85, 10, "Angel"); // Make an enemy on the heap (Manual Mother Fucker!)
  bool playerTurn {true};
  bool run {true};
  int win = 3;
  while (run){
    char choice;
    std::cout << "(A)ttack?: ";
    std::cin >> choice;
    choice = std::tolower(choice);

    if (enemy->health <= 0){
      win = 0;
      run = false;
    }
    else if (player.health <= 0){
      win = 1;
      run = false;
    }

    switch (choice) {
      case 'a':
        attack(*enemy, player, playerTurn);
        break;
      case 'h':
        player.Heal();
        continue;
      case 'c':
        std::cout << "Your health: " << player.health << "\nEnemy health: " << enemy->health << "Your damage: " << player.weapon->damage << "\nYour heals left: " << player.inventory[0]->amount;
        continue;
      case 'f':
        std::cout << "You fled!\n";
        run = false;
        break;
      default:
        std::cout << "Could not find!\n";
    }
  }
  
  delete enemy; // Remove enemy from the heap

  switch (win){
    case 0:
      return 0;
    case 1:
      return 1;
    case 2:
      return 2;
  }

  return 3;
}


int main() {

  std::unique_ptr<Player> shinji {std::make_unique<Player>("Shinji", 100)};
  std::shared_ptr<Weapon> knife  {std::make_shared<Weapon>(10, "Knife")};
  std::shared_ptr<Item> lclCartridge {std::make_shared<Item>("LCL Cartridge", 3)};
  shinji->weapon = knife;
  shinji->inventory[0] = lclCartridge;

  while (true){
    Battle(*shinji);
  }
  
  return 0;
}
