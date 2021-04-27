#ifndef SDL_HPP_INCLUDED
#define SDL_HPP_INCLUDED

#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"
#include <string>
#include <iostream>

class Image {

	SDL_Texture* texture;
public:
	Image();
	~Image();
	void draw(SDL_Renderer* ren, SDL_Rect* srect, SDL_Rect* drect) const;
	void load_img(SDL_Renderer* ren, const std::string& filename);

};

#endif // SDL_HPP_INCLUDED
