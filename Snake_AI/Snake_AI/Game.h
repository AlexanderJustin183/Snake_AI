
#ifndef SNAKE_AI_GAME_H
#define SNAKE_AI_GAME_H

#include "Classes.h"

class Game
{
public:
    bool isAI;
    bool started;
    Snake snake;
    Food food;
    Game();
    void init();
    void start();
    void drawBorder();
    void drawMap();
    void showDebugInfo();
    void eatFood();
    void createFood();
    bool isGameOver();
    bool isWin() const;
    void showGameOverScreen() const;
    void showStartScreen() const;
    void switchAI();
    int bfs(const Coord &_beg, const Coord &_end);
    bool canFindTail(Coord);
    bool canFindFood(Coord);
    direct_t getNextAICmd();
    direct_t nextCmdToFood();
    direct_t nextCmdToTail();
    direct_t nextCmdToFarAway(const Coord &);
    direct_t retCmd(Coord);
    void adjustSpeed();
    static int getDistance(Coord, Coord);
    bool onSnake(Coord);
    bool onSnakeExceptHead(Coord);
    bool onSnakeExceptTail(Coord);
    static bool inBorder(Coord);
};


#endif  // SNAKE_AI_GAME_H
