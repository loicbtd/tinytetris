
#include <ctime>
#include <curses.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "./game.hpp"

using namespace std;

Game::Game()
{
    this->x = 431424;
    this->y = 598356;
    this->r = 427089;
    this->px = 247872;
    this->py = 799248;
    this->c = 348480;
    this->p = 615696;
    this->score = 0;
}

Game::~Game()
{
}

void Game::start()
{
    srand(time(0));
    initscr();
    start_color();

    for (int i = 1; i < 8; i++)
    {
        init_pair(i, i, 0);
    }

    // new_piece();
    // resizeterm(22, 22);
    // noecho();
    // timeout(0);
    // curs_set(0);
    // box(stdscr, 0, 0);
    // runloop();
    // endwin();
}

void Game::newPiece()
{
    y = py = 0;
    p = rand() % 7;
    r = pr = rand() % 4;
    x = px = rand() % (10 - this->num(r, 16));
}

int Game::num(int x, int y)
{
    return 3 & block[p][x] >> y;
}