
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

    resizeterm(22, 22);
    noecho();
    timeout(0);
    curs_set(0);
    box(stdscr, 0, 0);
    this->runLoop();
    endwin();
}

int Game::num(int x, int y)
{
    return 3 & block[p][x] >> y;
}

void Game::newPiece()
{
    y = py = 0;
    p = rand() % 7;
    r = pr = rand() % 4;
    x = px = rand() % (10 - this->num(r, 16));
}

void Game::frame()
{
    for (int i = 0; i < 20; i++)
    {
        move(1 + i, 1); // otherwise the box won't draw
        for (int j = 0; j < 10; j++)
        {
            board[i][j] && attron(262176 | board[i][j] << 8);
            printw("  ");
            attroff(262176 | board[i][j] << 8);
        }
    }
    move(21, 1);
    printw("Score: %d", score);
    refresh();
}

void Game::setPiece(int x, int y, int r, int v)
{
    for (int i = 0; i < 8; i += 2)
    {
        board[this->num(r, i * 2) + y][this->num(r, (i * 2) + 2) + x] = v;
    }
}

int Game::updatePiece()
{
    this->setPiece(px, py, pr, 0);
    this->setPiece(px = x, py = y, pr = r, p + 1);
}

void Game::removeLine()
{
    for (int row = y; row <= y + this->num(r, 18); row++)
    {
        c = 1;
        for (int i = 0; i < 10; i++)
        {
            c *= board[row][i];
        }
        if (!c)
        {
            continue;
        }
        for (int i = row - 1; i > 0; i--)
        {
            memcpy(&board[i + 1][0], &board[i][0], 40);
        }
        memset(&board[0][0], 0, 10);
        score++;
    }
}

int Game::checkHit(int x, int y, int r)
{
    if (y + this->num(r, 18) > 19)
    {
        return 1;
    }
    this->setPiece(px, py, pr, 0);
    c = 0;
    for (int i = 0; i < 8; i += 2)
    {
        board[y + this->num(r, i * 2)][x + this->num(r, (i * 2) + 2)] && c++;
    }
    this->setPiece(px, py, pr, p + 1);
    return c;
}

int Game::doTick()
{
    if (++tick > 30)
    {
        tick = 0;
        if (this->checkHit(x, y + 1, r))
        {
            if (!y)
            {
                return 0;
            }
            this->removeLine();
            this->newPiece();
        }
        else
        {
            y++;
            this->updatePiece();
        }
    }
    return 1;
}

void Game::runLoop()
{
    while (this->doTick())
    {
        usleep(10000);
        if ((c = getch()) == 'a' && x > 0 && !this->checkHit(x - 1, y, r))
        {
            x--;
        }
        if (c == 'd' && x + this->num(r, 16) < 9 && !this->checkHit(x + 1, y, r))
        {
            x++;
        }
        if (c == 's')
        {
            while (!this->checkHit(x, y + 1, r))
            {
                y++;
                this->updatePiece();
            }
            this->removeLine();
            this->newPiece();
        }
        if (c == 'w')
        {
            ++r %= 4;
            while (x + this->num(r, 16) > 9)
            {
                x--;
            }
            if (this->checkHit(x, y, r))
            {
                x = px;
                r = pr;
            }
        }
        if (c == 'q')
        {
            return;
        }
        this->updatePiece();
        this->frame();
    }
}