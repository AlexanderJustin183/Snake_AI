#include "Defs.h"
#include "Game.h"

int main()
{
#ifdef USE_WT
	initgraph((DEBUG ? WINDOW_WIDTH : WINDOW_HEIGHT + 1), WINDOW_HEIGHT + 1, SHOWCONSOLE);
	ShowWindow(GetConsoleWindow(), SW_HIDE);
#else
	initgraph((DEBUG ? WINDOW_WIDTH : WINDOW_HEIGHT + 1), WINDOW_HEIGHT + 1);
#endif  // USE_WT
	Game game;
	BeginBatchDraw();
	// 主循环
	while (true)
	{
		if (!game.started || game.isGameOver())
		{
			game.drawMap();
			game.showDebugInfo();
			game.drawBorder();
			if (!game.started) game.showStartScreen();
			else game.showGameOverScreen();
			FlushBatchDraw();
			if(!_kbhit()) continue; // 替换_getch(),防止黑屏
			cleardevice();
			if (!game.started) game.start();
			else game.init();
		}

		if (_kbhit())
		{
			char key = (char)_getch();
			if (key == 'a')
			{
				game.switchAI();
				game.adjustSpeed();
			}
		}

		game.eatFood();
		game.createFood();
		if (_kbhit() && !game.isAI)
			game.snake.turnDirect((direct_t)(char)_getch());
		else
			game.snake.turnDirect(game.getNextAICmd());
		game.snake.move();

		cleardevice();

		game.drawMap();
		game.showDebugInfo();
		game.drawBorder();

		FlushBatchDraw();

		Sleep(200 / (DWORD)game.snake.speed);
	}
}