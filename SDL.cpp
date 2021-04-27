#include "SDL.hpp"
#include <iostream>

Image::Image() :
	texture(nullptr) {}

Image :: ~Image() {
	SDL_DestroyTexture(texture);
}

void Image::draw(SDL_Renderer* ren, SDL_Rect* srect, SDL_Rect* drect) const{
	SDL_RenderCopy(ren, texture, srect, drect);
}

void Image::load_img(SDL_Renderer* ren, const std::string& filename) {
	SDL_Surface* surface = IMG_Load(filename.c_str());

	if (surface) {
		texture = SDL_CreateTextureFromSurface(ren, surface);

		SDL_FreeSurface(surface);
	}
}
