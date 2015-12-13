#include "game.h"

int main(int argc, char **argv)
{
    std::unique_ptr<Game> game(new Game());
    game->startGame();
}
