#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include <iostream>
#include <string>
#include "player.hpp"
#include "SDL.hpp"
#include "window.hpp"
#include "map.hpp"
#include "vector"
#include "enemy.hpp"
#include "camera.hpp"

template <typename T>
void print_something(const std::string &text, const T &something){
	std::cout << text << " : " << something << std::endl;
}

class game {
	Image background;
	window wind;
	SDL_Renderer *ren;
	int chare;
	SDL_Rect back;
public:

	game() : chare(0) {
		back = { 0, 0, 1920, 1080 };
	};
	void play();
	void select_screen();
	void play_game();
	bool game_over_screen();
};
#endif // GAME_HPP_INCLUDED
