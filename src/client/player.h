#ifndef __PLAYER_H
#define __PLAYER_H

#include <SFML/Graphics.hpp>

class Player
{
    protected:
    std::unique_ptr<sf::CircleShape> drawable;

    public:
    Player();
    sf::Drawable* getDrawable();
    void setPosition(int x, int y);
};

#endif
