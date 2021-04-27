#include "game.hpp"

void game::select_screen()
{

	ren = wind.get_renderer();
	background.load_img(ren, "textures/background.bmp");

	Image select_screen;
	Image cursor;

	cursor.load_img(ren, "textures/select_arrow.bmp");
	SDL_Rect cursor_loc = {435, 450, 64, 44};
	const auto state = SDL_GetKeyboardState(NULL);
	select_screen.load_img(ren, "textures/char_select.bmp");
	SDL_Rect select_screen_loc = {300, 200, 379 * 2, 124 * 2};

	for (int i = 0;; i++)
	{

		SDL_PumpEvents();
		SDL_RenderClear(ren);
		background.draw(ren, &back, nullptr);
		select_screen.draw(ren, &back, &select_screen_loc);
		cursor.draw(ren, nullptr, &cursor_loc);

		if (chare < 0)
		{
			chare = 2;
		}
		if (chare > 2)
		{
			chare = 0;
		}
		if (state[SDL_SCANCODE_D])
		{
			chare++;
		}
		if (state[SDL_SCANCODE_A])
		{
			chare--;
		}
		if (state[SDL_SCANCODE_E])
		{

			return;
		}
		switch (chare)
		{
		case 0:
		{
			cursor_loc = {435, 450, 64, 44};
			break;
		}
		case 1:
		{
			cursor_loc = {625, 450, 64, 44};
			break;
		}
		case 2:
		{
			cursor_loc = {850, 450, 64, 44};
			break;
		}
		}

		SDL_RenderPresent(ren);

		SDL_Delay(1000 / 5);
	}
}

void game::play_game()
{
	camera cam;
	map first_level; // level
	timer time;
	time.load_numbers(ren);

	const auto state = SDL_GetKeyboardState(NULL);

	first_level.set_tile_name("textures/tiles.png");
	first_level.load_tile(ren);
	first_level.set_layout_file_name("layout.txt");
	first_level.load_layout();

	player *plr;

	if (chare == 0)
	{
		plr = new sonic();
		plr->load_sprites(ren);
	}
	if (chare == 1)
	{
		plr = new tails();
		plr->load_sprites(ren);
	}
	if (chare == 2)
	{
		plr = new knuck();
		plr->load_sprites(ren);
	}

	print_name(plr);
	std::vector<enemy *> badnics;

	badnics.push_back(new slow_enemy(100, 100));
	badnics[0]->left.load_img(ren, "textures/badnik1_left.bmp");
	badnics[0]->right.load_img(ren, "textures/badnik1_right.bmp");
	badnics.push_back(new fast_enemy(500, 900));
	badnics[1]->left.load_img(ren, "textures/badnik2_left.bmp");
	badnics[1]->right.load_img(ren, "textures/badnik2_right.bmp");
	badnics.push_back(new flying_enemy(800, 700));
	badnics[2]->left.load_img(ren, "textures/badnik3_left.bmp");
	badnics[2]->right.load_img(ren, "textures/badnik3_right.bmp");
	badnics.push_back(new flying_enemy(5000, 900));
	badnics[3]->left.load_img(ren, "textures/badnik3_left.bmp");
	badnics[3]->right.load_img(ren, "textures/badnik3_right.bmp");
	badnics.push_back(new slow_enemy(780, 1000));
	badnics[4]->left.load_img(ren, "textures/badnik1_left.bmp");
	badnics[4]->right.load_img(ren, "textures/badnik1_right.bmp");
	badnics.push_back(new fast_enemy(1000, 980));
	badnics[5]->left.load_img(ren, "textures/badnik2_left.bmp");
	badnics[5]->right.load_img(ren, "textures/badnik2_right.bmp");
	badnics.push_back(new flying_enemy(1000, 700));
	badnics[6]->left.load_img(ren, "textures/badnik3_left.bmp");
	badnics[6]->right.load_img(ren, "textures/badnik3_right.bmp");
	badnics.push_back(new flying_enemy(780, 790));
	badnics[7]->left.load_img(ren, "textures/badnik3_left.bmp");
	badnics[7]->right.load_img(ren, "textures/badnik3_right.bmp");
	badnics.push_back(new jumping_enemy(1000, 0));
	badnics[8]->left.load_img(ren, "textures/badnik2_left.bmp");
	badnics[8]->right.load_img(ren, "textures/badnik2_right.bmp");

	for (int i = 0;; ++i)
	{
		time.start();
		cam.set_camera(first_level.get_border(), plr->get_size(), plr->location());

		SDL_PumpEvents();
		SDL_RenderClear(ren);

		plr->set_player_srect();
		plr->set_loc(cam.get_cam());

		plr->set_new_image(i % 5);

		background.draw(ren, &back, nullptr);

		plr->move();
		plr->collision(first_level.layout, first_level.portals, first_level.get_border());
		plr->draw(ren, plr->srect, plr->loc);

		if (state[SDL_SCANCODE_Q])
		{
			delete plr;
			while (badnics.size() > 0)
			{
				delete badnics[0];
				badnics.erase(badnics.begin());
			}
			return;
		}

		for (auto &enemy : badnics)
		{
			if (enemy->alive)
			{
				SDL_Rect enemy_rect = {0, 0, enemy->get_size().width, enemy->get_size().height};
				enemy->collision(first_level.get_layout(), first_level.get_border(), plr);
				enemy->move();
				SDL_Rect enemy_loc = {enemy->coord.x - cam.get_cam().x, enemy->coord.y - cam.get_cam().y, enemy->get_size().width, enemy->get_size().height};
				enemy->main.draw(ren, &enemy_rect, &enemy_loc);
			}
		}

		first_level.draw_layout(ren, cam.get_cam());
		if (plr->alive == false || plr->location().x >= first_level.get_victory_x())
		{
			delete plr;
			while (badnics.size() > 0)
			{
				delete badnics[0];
				badnics.erase(badnics.begin());
			}

			return;
		}
		plr->draw_score(ren, time.numbers);
		time.print_time(ren);
		SDL_RenderPresent(ren);

		SDL_Delay(1000 / 60);
	}
}

bool game::game_over_screen()
{
	Image game_over;
	game_over.load_img(ren, "textures/game_over.bmp");
	const auto state = SDL_GetKeyboardState(NULL);
	for (int i = 0;; i++)
	{

		SDL_PumpEvents();
		SDL_RenderClear(ren);
		background.draw(ren, &back, nullptr);
		game_over.draw(ren, &back, nullptr);
		if (state[SDL_SCANCODE_E])
		{
			return false;
		}
		if (state[SDL_SCANCODE_R])
		{
			return true;
		}
		SDL_RenderPresent(ren);
		SDL_Delay(1000 / 30);
	}
}

void game::play()
{

	bool play_again = true;

	while (play_again == true)
	{
		select_screen();
		play_game();
		play_again = game_over_screen();
	}
}