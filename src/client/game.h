#ifndef __GAME_H
#define __GAME_H

#include <memory>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "player.h"

class Game
{
    protected:
    std::unique_ptr<sf::RenderWindow> window;
    std::unique_ptr<sf::TcpSocket> clientSocket;
    std::vector<std::unique_ptr<Player>> players;

    void connect();
    void requestState();
    void recvUpdate();

    public:
    Game();
    void startGame();
    void addPlayer(std::unique_ptr<Player> player);
};

#endif
