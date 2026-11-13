#pragma once
#include <string>
#include <vector>
#include <memory>

class Item{
    public:
        std::string type;
        int amount;

    Item(const std::string& Type, const int& Amount);
};

class Weapon{
    public:
        int damage;
        std::string name;

    Weapon(const int& Damage, const std::string& Name);
};

class Player {
    public:
        std::vector<std::shared_ptr<Item>> inventory;
        std::string name;
        int health;
        std::shared_ptr<Weapon> weapon;
        int chapter {1};
        bool badEnding;
        int money {0};

    Player(const std::string& Name, const int& Health);

    void Heal();
};


class Enemy{
  public:
    int health;
    int damage;
    std::string name;

    Enemy(const int& Health, const int& Damage, const std::string& Name);
};
