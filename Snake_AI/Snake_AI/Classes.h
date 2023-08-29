
#ifndef SNAKE_AI_CLASSES_H
#define SNAKE_AI_CLASSES_H

#include "Defs.h"

//////////////////////// 游戏结构 //////////////////////////////////

enum direct_t
{
    NONE = 0x00,
    RIGHT = 77,
    DOWN = 80,
    LEFT = 75,
    UP = 72
};

// 坐标
struct Coord
{
    int x, y, step;
    Coord();
    Coord(int, int, int = 0);
    bool operator ==(const Coord &) const;
    bool operator !=(const Coord &) const;
    bool operator <(const Coord &) const;
};

//////////////////////// 各类实现 //////////////////////////////////

// 食物
class Food
{
public:
    COLORREF color;
    Coord coord; // 食物坐标
    bool exist;      // 存在食物
    Food();
    ~Food();
    // 产生(0,0)~(limit_x,limit_y)的坐标
    void randCoord(int, int);
};

// 蛇
class Snake
{
public:
    COLORREF color;
    int length;            // 蛇长度
    double speed;          // 蛇速度
    std::list<Coord> body; // 蛇身坐标
    direct_t direct;         // 蛇当前方向
    Snake();
    // 蛇移动
    void move();
    // 蛇转向
    void turnDirect(direct_t);
};

#endif  // SNAKE_AI_CLASSES_H
