#include "player.h"

Player::Player()
{
    drawable = std::unique_ptr<sf::CircleShape>(new sf::CircleShape(25));
}

sf::Drawable* Player::getDrawable()
{
    return drawable.get();
}

void Player::setPosition(int x, int y)
{
    drawable->setPosition(x, y);
}
