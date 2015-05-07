#include"BombGame.h"

int main()
{
	BombGame game;
	std::unique_ptr<Menu> menu(new Menu);

	game.setMenu(menu);
	
	int opt(0);

	while (!opt)
	{
		opt=game.DisplayMenu();
		opt=game.OptionDetail(opt);
	}

	return 0;
}