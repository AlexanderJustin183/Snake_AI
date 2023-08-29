
#ifndef SNAKE_AI_DEFS_H
#define SNAKE_AI_DEFS_H

// C++头文件
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <list>
#include <queue>
#include <set>
#include <sstream>
#include <random>
// C头文件
#include <conio.h>
#include <dos.h>
#include <graphics.h>
#include <Windows.h>
// #define USE_WT   // temp

#ifdef _MSC_VER
#ifdef USE_WT
#pragma comment(linker, "/SUBSYSTEM:windows")    // 隐藏黑窗口
#pragma comment(linker, "/ENTRY:mainCRTStartup") // 使用`main()`而不是`WinMain()`
#endif  // USE_WT
#pragma comment(lib, "winmm.lib")
#pragma warning(disable : 4996)  //
#pragma warning(disable : 6031)  // 消除警告
#pragma warning(disable : 4326)  //
#endif  // _MSC_VER

// 参数定义
const bool DEBUG = true;       // 调试信息
const int WINDOW_WIDTH = 640;  // 窗口宽度
const int WINDOW_HEIGHT = 480; // 窗口高度
const int MAP_ROW_NUM = 20;    // 地图行数
const int MAP_COL_NUM = 20;    // 地图列数
const int GRID_GAP = 2;        // 格子间隙
const int GRID = (WINDOW_HEIGHT / MAP_COL_NUM);// 大格子宽度
const int SMALL_GRID = (GRID - 2 * GRID_GAP);  // 小格子宽度
const double SPEED_AI = 20;               // 蛇AI速度
const double SPEED_NORMAL = 1.5;          // 蛇正常速度

const int next[4][2] = {
        {1,  0},
        {0,  1},
        {-1, 0},
        {0,  -1}
};       // 右下左上

#endif  // SNAKE_AI_DEFS_H
