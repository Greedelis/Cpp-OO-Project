#ifndef MAP_HPP_INCLUDED
#define MAP_HPP_INCLUDED

#include "SDL.hpp"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>

class coordinates
{

  public:
	coordinates() {}
	coordinates(const int new_x, const int new_y);
	int x;
	int y;

	coordinates operator+(const coordinates &new_coord) const
	{
		return coordinates(x + new_coord.x, y + new_coord.y);
	}
	coordinates operator-(const coordinates &new_coord) const
	{
		return coordinates(x - new_coord.x, y - new_coord.y);
	}

	bool operator==(const coordinates &new_coord) const
	{
		if (x == new_coord.x && y == new_coord.y)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool operator!=(const coordinates &new_coord) const
	{
		if (x != new_coord.x && y != new_coord.y)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	coordinates &operator+=(const coordinates &new_coord)
	{

		x += new_coord.x;
		y += new_coord.y;
		return *this;
	}
	coordinates &operator-=(const coordinates &new_coord)
	{

		x -= new_coord.x;
		y -= new_coord.y;
		return *this;
	}
};

class size
{

  public:
	size() {}
	size(const int new_widht, const int new_heigth);

	int width;
	int height;
};

class map
{
	coordinates border;
	Image tile;
	SDL_Rect tile_size;
	SDL_Rect tile_loc;
	std::string tile_name;
	std::string layout_file;
	int victory_x;

  public:
  	std::vector<coordinates> portals;
	std::vector<std::vector<char>> layout;
	map();
	void load_tile(SDL_Renderer *ren);
	void load_layout();
	void draw_layout(SDL_Renderer *ren, const coordinates &camera);
	void set_tile_name(const std::string &new_mane);
	void set_layout_file_name(const std::string &new_name);
	void set_border();
	coordinates get_border() const;
	std::vector<std::vector<char>> get_layout();
	int get_victory_x() const { return victory_x; }
	void set_tile_size(const int &x);
	void find_portas();
};

#endif // MAP_HPP_INCLUDED
