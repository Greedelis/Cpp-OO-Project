#ifndef WINDOW_HPP_INCLUDED
#define WINDOW_HPP_INCLUDED

#include <SDL2/SDL.h>
#include <string>
#include <iostream>
#include "map.hpp"

class window {
public:
	SDL_Window* win;
	SDL_Renderer* ren;

	window();
	~window();
	void create_window();
	void create_renderer();
	SDL_Renderer *get_renderer() const { return ren; }

};
#endif // WINDOW_HPP_INCLUDED
