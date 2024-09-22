#include "../headers/attack.hpp"

Attack::Attack(sf::IntRect rect, bool z[3], const Player& player, sf::Int32 before_colliding, sf::Int32 until_inactive, sf::Int32 perfect_time[2])
: rect(rect), z_coverage(z), player(player), before_colliding(before_colliding), until_inactive(until_inactive), perfect_time(perfect_time) {}

Evasion Attack::checkCollide() {
    if (colliding) {
        if (since_colliding.asMilliseconds() > perfect_time[0] && since_colliding.asMilliseconds() < perfect_time[1]) {
            return Evasion::PERFECT_DODGE;
        }
        if (rect.left+rect.width >= player.rect.left
        && rect.left <= player.rect.left+player.rect.width
        && rect.top+rect.height >= player.rect.top
        && rect.top <= player.rect.top+player.rect.height) {
            return Evasion::HIT;
        }
        return Evasion::DODGE;
    }
    return Evasion::NONE;
}