#include <iostream>
#include "game.h"

Game::Game()
{
    window = std::unique_ptr<sf::RenderWindow>(
        new sf::RenderWindow(
            sf::VideoMode(800, 600),
            "infraverse"
        )
    );

    clientSocket = std::unique_ptr<sf::TcpSocket>(new sf::TcpSocket());
}

void Game::connect()
{
    if (clientSocket->connect("127.0.0.1", 1234) != sf::Socket::Done)
    {
        std::cout << "Failed to connect" << std::endl;
        window->close();
    }
    clientSocket->setBlocking(false);
}

void Game::requestState()
{
    // FIXME - Handle partial sends
    clientSocket->setBlocking(true);

    uint8_t buf[] = {0x42, 0x1, 0x0};
    if (clientSocket->send(buf, sizeof(buf)) != sf::Socket::Done)
    {
        std::cout << "Failed to send!" << std::endl;
    }
    clientSocket->setBlocking(false);
}

void Game::recvUpdate()
{
    uint8_t buf[16] = {0x0};
    size_t bufRecvLen;
    switch (clientSocket->receive(buf, 16, bufRecvLen))
    {
        case sf::Socket::Done:
            std::cout << "Received update from server;"
                      << " magic=" << unsigned(buf[0])
                      << " command=" << unsigned(buf[2])
                      << " length=" << unsigned(buf[1])
                      << std::endl;
            break;
        case sf::Socket::Error:
            std::cout << "Error occured reading from socket!" << std::endl;
            window->close();
            break;
        default:
            break;
    }
}

void Game::startGame()
{
    this->connect();
    this->requestState();

    while (window->isOpen())
    {
        window->clear(sf::Color::Blue);

        for (std::vector<std::unique_ptr<Player>>::iterator it = players.begin(); it != players.end(); ++it)
        {
            window->draw(*(*it)->getDrawable());
        }

        window->display();

        this->recvUpdate();

        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window->close();
            }
        }
    }
}

void Game::addPlayer(std::unique_ptr<Player> player)
{
    players.push_back(std::move(player));
}
