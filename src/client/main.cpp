#include "game.h"

void addPlayers(Game *game)
{
    std::unique_ptr<Player> p0(new Player());
    std::unique_ptr<Player> p1(new Player());

    p0->setPosition(10, 10);
    p1->setPosition(100, 10);

    game->addPlayer(std::move(p0));
    game->addPlayer(std::move(p1));
}

int main(int argc, char **argv)
{
    std::unique_ptr<Game> game(new Game());

    addPlayers(game.get());
    game->startGame();
}
