#include "Game.h"

// 寻找最优路线
direct_t Game::getNextAICmd()
{
    direct_t cmd = NONE;
    if(!isAI)
        return cmd;
    // 如果能找到食物
    if(canFindFood(snake.body.front()))
    {
        Game simulate = *this;     // 模拟状态
        while(simulate.food.exist)
        {
            simulate.snake.turnDirect(simulate.nextCmdToFood());
            simulate.snake.move();
            simulate.eatFood();
        }
        // 如果吃完还能找到尾巴(到尾巴的距离大于1)
        if(simulate.bfs(simulate.snake.body.front(), simulate.snake.body.back()) > 1)
            cmd = nextCmdToFood();    // 真正去吃
        else
            cmd = nextCmdToTail();    // 吃完了找不到
    }
    else
        cmd = nextCmdToFarAway(snake.body.front());   // 找不到
    return cmd;
}

// 返回可用的指令,必须是周围4点
direct_t Game::retCmd(Coord nextPoint)
{
    direct_t cmd = NONE;
    int dx = nextPoint.x - snake.body.front().x;
    int dy = nextPoint.y - snake.body.front().y;
    if(dx == 0 && dy < 0) cmd = UP;
    if(dx == 0 && dy > 0) cmd = DOWN;
    if(dx < 0 && dy == 0) cmd = LEFT;
    if(dx > 0 && dy == 0) cmd = RIGHT;
    return cmd;
}
// BFS寻路算法
// 存在路径返回步数，不存在返回-1
int Game::bfs(const Coord &_beg, const Coord &_end)
{
    if(_beg == _end)
        return 0;
    std::queue<Coord> bfs_que;
    std::set<Coord> set;
    bfs_que.push(_beg);
    for(const auto &iter : snake.body)
        set.insert(iter);
    // 如果终点是尾巴就可把尾巴设为可走的结点
    if(&_end == &snake.body.back())
        set.erase(_end);
    while(!bfs_que.empty())
    {
        for(auto k : next)
        {
            Coord tmp_coord;
            tmp_coord.x = bfs_que.front().x + k[0];
            tmp_coord.y = bfs_que.front().y + k[1];
            // 超出地图进入下次循环
            if(!inBorder(tmp_coord)) continue;
            // 无障碍没有走过的结点加入队列
            if(!set.count(tmp_coord))
            {
                tmp_coord.step = bfs_que.front().step + 1;
                set.insert(tmp_coord);
                bfs_que.push(tmp_coord);
            }
            // 到达目标返回步数
            if(tmp_coord == _end) return tmp_coord.step;
        }
        bfs_que.pop();
    }
    return -1;
}
// 最短距离吃食物
direct_t Game::nextCmdToFood()
{
    // 得到头部周围4点
    Coord aroundPoint[4];
    for(int i = 0; i < 4; i++)
    {
        aroundPoint[i].x = snake.body.front().x + next[i][0];
        aroundPoint[i].y = snake.body.front().y + next[i][1];
        if(!inBorder(aroundPoint[i]) || onSnakeExceptTail(aroundPoint[i])) // *特殊处理尾巴
            aroundPoint[i].step = -1;
        else
            aroundPoint[i].step = bfs(aroundPoint[i], food.coord);
    }
    // 选出最近的走
    int min_step_index = 0;
    for(int i = 1; i < 4; i++)
    {
        // 是0表示是食物直接走
        // 如果是-1不参与比较
        if(aroundPoint[min_step_index].step == -1)
            min_step_index = i;
        if(aroundPoint[i].step != -1)
            if(aroundPoint[i].step < aroundPoint[min_step_index].step)
                min_step_index = i;
    }
    direct_t ret = NONE;
    // 返回操作，找不到食物就返回NONE什么都不做
    if(aroundPoint[min_step_index].step >= 0)
        ret = retCmd(aroundPoint[min_step_index]);
    return ret;
}
// 最远距离追尾巴
direct_t Game::nextCmdToTail()
{
    // 得到头部周围4点
    Coord aroundPoint[4];
    for(int i = 0; i < 4; i++)
    {
        aroundPoint[i].x = snake.body.front().x + next[i][0];
        aroundPoint[i].y = snake.body.front().y + next[i][1];
        if(inBorder(aroundPoint[i]) && !onSnakeExceptTail(aroundPoint[i])) //	*特殊处理尾巴
            aroundPoint[i].step = bfs(aroundPoint[i], snake.body.back());
        else
            aroundPoint[i].step = -1;
    }
    // 选出最远的点
    int max_step_index = 0;
    for(int i = 1; i < 4; i++)
    {
        // 是0表示是食物直接走
        // 如果是-1不参与比较
        if(aroundPoint[max_step_index].step == -1)
            max_step_index = i;
        if(aroundPoint[i].step != -1)
            if(aroundPoint[i].step > aroundPoint[max_step_index].step)
                max_step_index = i;
    }
    direct_t ret = NONE;
    // 返回操作，找不到食物就返回NONE什么都不做
    if(aroundPoint[max_step_index].step != -1)
        ret = retCmd(aroundPoint[max_step_index]);
    return ret;
}
// 远离食物
direct_t Game::nextCmdToFarAway(const Coord &coord)
{
    // 得到周围四点距离
    Coord aroundPoint[4];
    for(int i = 0; i < 4; i++)
    {
        aroundPoint[i].x = snake.body.front().x + next[i][0];
        aroundPoint[i].y = snake.body.front().y + next[i][1];
        // 距离,有障碍的点置为-1
        if(canFindTail(aroundPoint[i]) && inBorder(aroundPoint[i]) && !onSnakeExceptTail(aroundPoint[i]))
            aroundPoint[i].step = getDistance(aroundPoint[i], coord);
        else // 这里蛇尾应设置为可行
            aroundPoint[i].step = -1;
    }
    // 能到尾巴,远离食物
    // 另一种策略是选离尾巴远的
    int max_step_index = 0;
    for(int i = 1; i < 4; i++)
        if((aroundPoint[i].step >= aroundPoint[max_step_index].step))
            max_step_index = i;
    direct_t ret = NONE;
    // 返回操作，找不到食物就返回NONE什么都不做
    if(aroundPoint[max_step_index].step != -1)
        ret = retCmd(aroundPoint[max_step_index]);
    return ret;
}
// 存在到尾巴的路径
bool Game::canFindTail(Coord _beg)
{
    return bfs(_beg, snake.body.back()) >= 0;
}
// 存在到食物的路径
bool Game::canFindFood(Coord _beg)
{
    return bfs(_beg, food.coord) >= 0;
}
