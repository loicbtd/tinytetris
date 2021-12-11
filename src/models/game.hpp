#include <string>
#include <vector>

using namespace std;

class Game
{

protected:
    int x;
    int y;
    int r;
    int px;
    int py;
    int pr;
    int c;
    int p;
    int tick;
    int board[20][10] = {0};
    int block[7][4] = {{this->x, this->y, this->x, this->y}, {this->r, this->p, this->r, this->p}, {this->c, this->c, this->c, this->c}, {599636, 431376, 598336, 432192}, {411985, 610832, 415808, 595540}, {this->px, this->py, this->px, this->py}, {614928, 399424, 615744, 428369}};
    int score;

public:
    Game();
    virtual ~Game();
    void start();

private:
    void newPiece();
    int num(int, int);
};
