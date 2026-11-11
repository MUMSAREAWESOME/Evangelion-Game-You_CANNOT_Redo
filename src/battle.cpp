#include "battle.h"
#include "classes.h"
#include <cctype>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <vector>

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
      std::cout << "\033[34mYou damaged the enemy!\033[0m\n";
    }
    else if (failChance >= 90){
      enemy.health -= (player.weapon->damage * 2);
      std::cout << "\033[33mCritical Hit!\033[0m\n";
    }
    else{
      std::cout << "\033[31mYou fumbled the attack!\033[0m\n";
    }
  }
  // \033 is the ANSI escape char. It can be used with a [ and the corresponding code to change the text colour
  else{
    int failChance = randomRange(1, 100);

    if (failChance > 25){
      player.health -= enemy.damage;
      std::cout << "\033[31mTook " << enemy.damage << " damage!\033[0m\n";
    }
    else if (failChance >= 95){
      player.health -= enemy.damage + 2;
      std::cout << "\033[31mEnemy got a CRIT! Lost: " << enemy.damage + 2 << " health!\033[0m" << '\n';
    }
    else{
      std::cout << "\033[31mEnemy fumbled the attack!\033[0m\n";
    }
  }
}

int Battle(Player& player){
  Enemy *enemy = new Enemy(85, 10, "Angel"); // Make an enemy on the heap (Manual Mother Fucker!)
  bool playerTurn {true};
  bool run {true};
  int win = 3;
  
  while (run){
    if (enemy->health <= 0){
      win = 0;
      run = false;
    }
    else if (player.health <= 0){
      win = 1;
      run = false;
    }


    if (playerTurn){
      char choice;
      std::cout << "(A)ttack, (C)heck, (H)eal, (F)lee: ";
      std::cin >> choice;
      choice = std::tolower(choice);
      switch (choice) {
        case 'a':
          attack(*enemy, player, playerTurn);
          playerTurn = false;
          break;
        case 'h':
          player.Heal();
          continue;
        case 'c':
          std::cout << "Your health: " << player.health << "\nEnemy health: " << enemy->health << "\nYour damage: " << player.weapon->damage << "\nYour heals left: " << player.inventory[0]->amount << '\n';
          continue;
        case 'f':
          std::cout << "You fled!\n";
          run = false;
          win = 2;
          break;
        default:
          std::cout << "Could not find!\n";
          continue;
      }
    }
    else{
      attack(*enemy, player, playerTurn);
      playerTurn = true;
    }
  }
  
  delete enemy; // Remove enemy from the heap

  if (win == 0) return 0;
  else if (win == 2) return 2;
  else return 1;
}