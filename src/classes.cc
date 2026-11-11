#include "classes.h"
#include <vector>
#include <iostream>  
#include <memory>

Item::Item(const std::string& Type, const int& Amount){
    type = Type;
    amount = Amount;
}

Weapon::Weapon(const int& Damage, const std::string& Name){
    damage = Damage;
    name = Name;
    }

    Player::Player(const std::string& Name, const int& Health){
    name = Name;
    health = Health;
    }

    void Player::Heal(){
    if (inventory[0]->amount > 0 && health < 100){
        health += (100 - health); // Heals player to max health
        inventory[0]->amount --;
        std::cout << "\033[32mHealed to full health!\033[0m\n";
    }
    else if (inventory[0]->amount > 0 && health == 100){
        std::cout << "\033[31mFailed to heal! Already at max health\033[0m\n";
    }
    else{
        std::cout << "\033[31mFailed to heal! Out of heals!\033[0m\n";
    }
}

Enemy::Enemy(const int& Health, const int& Damage, const std::string& Name){
      health = Health;
      damage = Damage;
      name = Name;
    }