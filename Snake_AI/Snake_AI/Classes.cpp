#include "Classes.h"

// 实现方法

Coord::Coord() : x(0), y(0), step(0) {}
Coord::Coord(int _x, int _y, int _step) : x(_x), y(_y), step(_step) {}

bool Coord::operator ==(const Coord &t) const
{
    return (x == t.x) && (y == t.y);
}
bool Coord::operator !=(const Coord &t) const
{
    return (x != t.x) || (y != t.y);
}
bool Coord::operator <(const Coord &t) const
{
    return x == t.x ? y < t.y : x < t.x;
}

Food::Food() : color(RED), exist(true) {}
Food::~Food() { color = LIGHTGRAY, exist = false; }

void Food::randCoord(int limit_x, int limit_y)
{
    coord.x = rand() % limit_x;
    coord.y = rand() % limit_y;
}

Snake::Snake() : color(WHITE), direct(UP), length(0), speed(0) {}

void Snake::move()
{
    Coord head = body.front();
    switch(direct)
    {
    case UP:
        head.y--;
        break;
    case DOWN:
        head.y++;
        break;
    case LEFT:
        head.x--;
        break;
    case RIGHT:
        head.x++;
        break;
    case NONE:
        head.x = head.x;
    }
    body.pop_back();       // 尾巴出列
    body.push_front(head); // 新头入列
}
void Snake::turnDirect(direct_t cmd = NONE)
{
    if(cmd == UP && direct != DOWN ||
       cmd == LEFT && direct != RIGHT ||
       cmd == DOWN && direct != UP ||
       cmd == RIGHT && direct != LEFT)
        direct = cmd;
}
