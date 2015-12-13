#include <iostream>
#include "game.h"
#include "update.h"

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

std::unique_ptr<Update> Game::recvUpdate()
{
    uint8_t buf[16] = {0x0};
    size_t bufRecvLen;
    switch (clientSocket->receive(buf, 16, bufRecvLen))
    {
        case sf::Socket::Done:
            return std::unique_ptr<Update>(new Update(buf));

        case sf::Socket::Error:
            std::cout << "Error occured reading from socket!" << std::endl;
            window->close();
            return nullptr;

        default:
            return nullptr;
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

        std::unique_ptr<Update> update = this->recvUpdate();
        if (update != nullptr)
        {
            this->handleUpdate(std::move(update));
        }

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

void Game::handleUpdate(std::unique_ptr<Update> update)
{
    switch (update->getUpdateId())
    {
        case UPD_PLAYER_NEW:
            this->handleUpdatePlayerNew(std::move(update));
            break;
        default:
            std::cout << "Update Not Implemented:"
                      << unsigned(update->getUpdateId())
                      << std::endl;
            break;
    }
}

void Game::handleUpdatePlayerNew(std::unique_ptr<Update> update)
{
    std::unique_ptr<Player> player(new Player());
    player->setPosition(update->getArgument(0), update->getArgument(1));
    this->addPlayer(std::move(player));
}

void Game::addPlayer(std::unique_ptr<Player> player)
{
    players.push_back(std::move(player));
}
