#pragma once
#include <vector>
#include "attack.hpp"

class CatBoss {
public:
    int update();
private:
    int health;
    std::vector<Attack> activeAttacks;

    void attack();
}