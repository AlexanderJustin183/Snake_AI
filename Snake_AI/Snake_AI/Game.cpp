#include "Game.h"

Game::Game() : started(false), isAI(true) { init(); }

// 调节AI
void Game::switchAI()
{
    isAI = !isAI;
}

// 游戏初始化
void Game::init()
{
    srand((unsigned int)time(nullptr) + rand());
    adjustSpeed();
    snake.length = 3;
    snake.direct = UP;
    while(!snake.body.empty())
        snake.body.pop_back();
    Coord body(MAP_ROW_NUM / 2, MAP_COL_NUM / 2);
    for(int i = 0; i < snake.length; i++)
    {
        snake.body.push_back(body);
        body.y++;
    }
    food.randCoord(MAP_COL_NUM, MAP_ROW_NUM);
}
// 开始
void Game::start()
{
    started = true;
}
// 画边界
void Game::drawBorder()
{
    setlinecolor(WHITE);
    rectangle(0, 0, WINDOW_WIDTH - 1, WINDOW_HEIGHT);
    line(WINDOW_HEIGHT, 0, WINDOW_HEIGHT, WINDOW_HEIGHT);
}
// 画地图
void Game::drawMap()
{
    setfillcolor(DARKGRAY);
    solidrectangle(0, 0, GRID * MAP_COL_NUM, GRID * MAP_ROW_NUM);
    setcolor(LIGHTGRAY);
    // 食物
    setfillcolor(food.color);
    fillrectangle(food.coord.x * GRID + GRID_GAP, food.coord.y * GRID + GRID_GAP, (food.coord.x + 1) * GRID - GRID_GAP,
                  (food.coord.y + 1) * GRID - GRID_GAP);
    // 蛇
    Coord temp = snake.body.front();
    for(const auto &iter : snake.body)
    {
        if(iter == snake.body.front())
            setfillcolor(LIGHTBLUE);
        else
            setfillcolor(snake.color);
        solidrectangle(iter.x * GRID + GRID_GAP, iter.y * GRID + GRID_GAP, (iter.x + 1) * GRID - GRID_GAP,
                       (iter.y + 1) * GRID - GRID_GAP);
        // 缝隙
        int iter_x = iter.x * GRID + GRID_GAP;
        int iter_y = iter.y * GRID + GRID_GAP;
        int temp_x = temp.x * GRID + GRID_GAP;
        int temp_y = temp.y * GRID + GRID_GAP;
        if(temp.x == iter.x)
        {
            if(iter.y > temp.y) solidrectangle(temp_x, temp_y + SMALL_GRID, iter_x + SMALL_GRID, iter_y);
            if(iter.y < temp.y) solidrectangle(iter_x, iter_y + SMALL_GRID, temp_x + SMALL_GRID, temp_y);
        }
        if(temp.y == iter.y)
        {
            if(iter.x > temp.x) solidrectangle(temp_x + SMALL_GRID, temp_y, iter_x, iter_y + SMALL_GRID);
            if(iter.x < temp.x) solidrectangle(iter_x + SMALL_GRID, iter_y, temp_x, temp_y + SMALL_GRID);
        }
        temp = iter;
    }
}
#pragma clang diagnostic push
#pragma ide diagnostic ignored "Simplify"
// 绘制调试相关信息
void Game::showDebugInfo()
{
    if(DEBUG)
    {
        // 填充黑色底
        setfillcolor(BLACK);
        solidrectangle(1 + WINDOW_HEIGHT, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
        
        TCHAR temp[21];
        
        // 尺寸信息
        _stprintf_s(temp, _T("%d×%d地图"), MAP_COL_NUM, MAP_ROW_NUM);
        settextcolor(WHITE);
        outtextxy(WINDOW_HEIGHT + 12, 21, temp);
        
        // AI状态信息
        const TCHAR *str_ai = _T("手动模式");
        if(isAI)
        {
            str_ai = _T("AI模式");
        }
        outtextxy(WINDOW_HEIGHT + 12, 50, str_ai);
        
        // 速度信息
        _stprintf_s(temp, _T("速度: %.1lf"), snake.speed);
        outtextxy(WINDOW_HEIGHT + 12, 80, temp);
        
        // 蛇长度信息
        _stprintf_s(temp, _T("长度: %d/%d"), snake.length, MAP_COL_NUM * MAP_ROW_NUM);
        outtextxy(WINDOW_HEIGHT + 12, 110, temp);
        
        // 保存结点
        const Coord &snakeHead = snake.body.front();
        const Coord &snakeTail = snake.body.back();
        
        // 测试
        _stprintf_s(temp, _T("DEBUG1: %d"), bfs(snakeHead, snakeTail));
        outtextxy(WINDOW_HEIGHT + 12, 140, temp);
        
        // 食物坐标
        _stprintf_s(temp, _T("食物: (%d,%d)"), food.coord.x, food.coord.y);
        outtextxy(WINDOW_HEIGHT + 12, 180, temp);
        
        // 蛇头坐标
        _stprintf_s(temp, _T("蛇头: (%d,%d)"), snakeHead.x, snakeHead.y);
        outtextxy(WINDOW_HEIGHT + 12, 205, temp);
        
        // 蛇尾坐标
        _stprintf_s(temp, _T("蛇尾: (%d,%d)"), snakeTail.x, snakeTail.y);
        outtextxy(WINDOW_HEIGHT + 12, 230, temp);
        
        const TCHAR *str_dir;
        // 方向
        switch(snake.direct)
        {
        case RIGHT:
            str_dir = _T("RIGHT");
            break;
        case DOWN:
            str_dir = _T("DOWN");
            break;
        case LEFT:
            str_dir = _T("LEFT");
            break;
        case UP:
            str_dir = _T("UP");
            break;
        default:
            str_dir = _T("None");
        }
        outtextxy(WINDOW_HEIGHT + 12, 260, str_dir);
        
        settextcolor(CYAN);
        outtextxy(WINDOW_HEIGHT + 12, 290, _T("使用BFS搜索算法"));
        outtextxy(WINDOW_HEIGHT + 12, 310, _T("作者:"));
        outtextxy(WINDOW_HEIGHT + 12, 330, _T("  AlexanderJustin"));
        outtextxy(WINDOW_HEIGHT + 12, 350, _T("(fork @柯西丶不是你)"));
        outtextxy(WINDOW_HEIGHT + 12, 370, _T("图形库: EasyX"));
    }
}
#pragma clang diagnostic pop

// 游戏开始画面
void Game::showStartScreen() const
{
    setcolor(LIGHTGRAY);
    // line(WINDOW_HEIGHT, 0, WINDOW_HEIGHT, WINDOW_HEIGHT);
    setfillcolor(BLACK);
    settextcolor(RGB(255, 0, 0));
    const TCHAR *str_end = _T("按任意键开始游戏");
    outtextxy(WINDOW_HEIGHT / 2 - textwidth(str_end) / 2, WINDOW_HEIGHT / 2 - textheight(str_end) / 2, str_end);
}
// 游戏结束画面
void Game::showGameOverScreen() const
{
    setcolor(LIGHTGRAY);
    // line(WINDOW_HEIGHT, 0, WINDOW_HEIGHT, WINDOW_HEIGHT);
    setfillcolor(BLACK);
    settextcolor(RGB(255, 0, 0));
    const TCHAR *str_end = _T("GAME OVER!");
    if(isWin())
        str_end = _T("YOU WIN!");
    outtextxy(WINDOW_HEIGHT / 2 - textwidth(str_end) / 2, WINDOW_HEIGHT / 2 - textheight(str_end) / 2, str_end);
}
// 吃食物
void Game::eatFood()
{
    Coord head = snake.body.front();
    if(head == food.coord)
    {
        food.exist = false;
        snake.body.push_back(snake.body.back());
        snake.length++;
    }
}
// 产生食物
void Game::createFood()
{
    if(!food.exist)
    {
        while(true)
        {
            food.randCoord(MAP_COL_NUM, MAP_ROW_NUM);
            if(!onSnake(food.coord))
                break;
        }
        food.exist = true;
    }
}
// 判断游戏结束
bool Game::isGameOver()
{
    Coord head = snake.body.front();
    if(!inBorder(head) || onSnakeExceptHead(head) || isWin())
        return true;
    return false;
}
// 是否吃满食物
bool Game::isWin() const
{
    return snake.length >= MAP_COL_NUM * MAP_ROW_NUM;
}
void Game::adjustSpeed()
{
    if(isAI)
        snake.speed = SPEED_AI;
    else
        snake.speed = SPEED_NORMAL;
    // hello world
}
// 两点距离
int Game::getDistance(Coord _a, Coord _b)
{
    //return abs(_a.x - _b.x) + abs(_a.y - _b.y); // 曼哈顿距离
    return (int)sqrt(pow(_a.x - _b.x, 2) + pow(_a.y - _b.y, 2));   // 欧氏距离
}
// 坐标在蛇上/包括蛇头蛇尾
bool Game::onSnake(Coord coord)
{
    return any_of(snake.body.begin(), snake.body.end(), [&coord](Coord _coord) { return _coord == coord; });
}
// 坐标在蛇上/不包括蛇头
bool Game::onSnakeExceptHead(Coord coord)
{
    auto beg = snake.body.begin();
    ++beg;
    return any_of(beg, snake.body.end(), [&coord](Coord _coord) { return _coord == coord; });
}
// 坐标在蛇上/不包括蛇尾
bool Game::onSnakeExceptTail(Coord coord)
{
    auto end = snake.body.end();
    --end;
    return any_of(snake.body.begin(), end, [&coord](Coord _coord) { return _coord == coord; });
}
// 坐标在方框里
bool Game::inBorder(Coord coord)
{
    return (coord.x >= 0 && coord.x < MAP_COL_NUM && coord.y >= 0 && coord.y < MAP_ROW_NUM);
}