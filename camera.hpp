#pragma once

#include <vector>
#include "SDL.hpp"
#include "game.hpp"
#include "map.hpp"
#include "player.hpp"

class camera
{

	static coordinates cam;

  public:
	coordinates get_cam() const { return cam; }

	static void set_camera(coordinates border, size plr_size, coordinates plr_loc);
};

class timer
{
	int frame;

  public:
	Image numbers;
	timer() : frame(0)
	{
		srect = {0, 0, 8, 13};
		loc = {0, 0, 8, 13};
	}
	void start()
	{
		frame++;
	}
	SDL_Rect srect;
	SDL_Rect loc;
	void print_time(SDL_Renderer *ren);
	void set_number(const int &x)
	{
		srect = {x * 8, 0, 8, 13};
	}
	void set_loc(const int &numb)
	{
		loc = {40 + numb * 8, 40, 8, 13};
	}
	void load_numbers(SDL_Renderer *ren)
	{
		numbers.load_img(ren, "textures/number.png");
	}
};
