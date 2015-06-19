#include"BombGame.h"

int main()
{
	while (true)
	{
		BombGame *game(new BombGame);
		game->startMenu();
		game->startGame();
		game->showResult();
		delete game;
	}

	return 0;
}
