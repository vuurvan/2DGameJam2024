#pragma once
#include <SFML/Graphics.hpp>
#include "player.hpp"

enum Evasion {
    DODGE,
    PERFECT_DODGE,
    HIT,
    NONE,
};

class Attack {
public:
    Attack(sf::IntRect rect, bool z[3], const Player& player, sf::Int32 before_colliding, sf::Int32 until_inactive, sf::Int32 perfect_time[2]);
    Evasion checkCollide(const sf::IntRect& rect);
private:
    int width;
    bool z_coverage[3];

    sf::IntRect rect;

    const Player& player;

    bool colliding;

    // as milliseconds
    sf::Int32 before_colliding;
    sf::Int32 unil_inactive;
    sf::Int32 perfect_time[2];

    sf::Time since_colliding;
};