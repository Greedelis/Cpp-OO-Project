#include "map.hpp"

extern const int window_height = 720;
extern const int window_width = 1280;
extern const int size_of_tiles = 75;

coordinates::coordinates(const int new_x, const int new_y) : x(new_x), y(new_y) {}

size::size(const int new_width, const int new_height) : width(new_width), height(new_height) {}

map::map()
{
	tile_size = {0, 0, size_of_tiles, size_of_tiles};
	tile_loc = {0, 0, size_of_tiles, size_of_tiles};
	layout.push_back(std::vector<char>());
}

void map::load_layout()
{

	std::ifstream map_layout(layout_file);

	if (map_layout.fail())
	{
		std::cout << "ERROR: File couldn't be opend" << std::endl;
	}

	char test;
	int i = 0;
	while (!map_layout.eof())
	{

		map_layout.get(test);

		if (test == '\n')
		{
			layout.push_back(std::vector<char>());
			i++;
		}
		else if (test != ' ')
		{	
			if (test == 'w')
			{
				victory_x = size_of_tiles * layout[i].size();
			}
			layout[i].push_back(test);
		}
	}
	layout[layout.size() - 1].pop_back();

	map_layout.close();

	set_border();
	find_portas();
	return;
}

void map::draw_layout(SDL_Renderer *ren, const coordinates &camera)
{

	for (int y = 0; y < layout.size(); y++)
	{
		for (int x = 0; x < layout[y].size(); x++)
		{

			if ((layout[y][x] == 'x' || layout[y][x] == 'y' || layout[y][x] == 'd') && (y * size_of_tiles >= camera.y - size_of_tiles && 
			y * size_of_tiles <= camera.y + window_height) && (x * size_of_tiles >= camera.x - size_of_tiles && 
			x * size_of_tiles <= camera.x + window_width))
			{
				set_tile_size(0);
				SDL_Rect tile_loc = {size_of_tiles * x - camera.x, size_of_tiles * y - camera.y, size_of_tiles, size_of_tiles};
				tile.draw(ren, &tile_size, &tile_loc);
			}
			if (layout[y][x] == 'j' && (y * size_of_tiles >= camera.y - size_of_tiles && y * size_of_tiles <= camera.y + window_height) 
			&& 	(x * size_of_tiles >= camera.x - size_of_tiles && x * size_of_tiles <= camera.x + window_width))
			{
				set_tile_size(2);
				SDL_Rect tile_loc = {size_of_tiles * x - camera.x, size_of_tiles * y - camera.y, size_of_tiles, size_of_tiles};
				tile.draw(ren, &tile_size, &tile_loc);
			}
			if (layout[y][x] == 's' && (y * size_of_tiles >= camera.y - size_of_tiles && y * size_of_tiles <= camera.y + window_height) 
			&& (x * size_of_tiles >= camera.x - size_of_tiles && x * size_of_tiles <= camera.x + window_width))
			{
				set_tile_size(3);
				SDL_Rect tile_loc = {size_of_tiles * x - camera.x, size_of_tiles * y - camera.y, size_of_tiles, size_of_tiles};
				tile.draw(ren, &tile_size, &tile_loc);
			}
			if (layout[y][x] == 't' && (y * size_of_tiles >= camera.y - size_of_tiles && y * size_of_tiles <= camera.y + window_height) 
			&& (x * size_of_tiles >= camera.x - size_of_tiles && x * size_of_tiles <= camera.x + window_width))
			{
				set_tile_size(1);
				SDL_Rect tile_loc = {size_of_tiles * x - camera.x, size_of_tiles * y - camera.y, size_of_tiles, size_of_tiles};
				tile.draw(ren, &tile_size, &tile_loc);
			}
		}
	}
}

void map::set_tile_size(const int &x)
{
	tile_size = tile_size = {x * 75, 0, size_of_tiles, size_of_tiles};
}

void map::load_tile(SDL_Renderer *ren)
{
	tile.load_img(ren, tile_name);
}

void map::set_tile_name(const std::string &new_name)
{
	tile_name = new_name;
}

void map::set_layout_file_name(const std::string &new_name)
{
	layout_file = new_name;
}

std::vector<std::vector<char>> map::get_layout()
{
	return layout;
}

void map::set_border()
{

	int max_y = 0;
	int max_x = 0;

	max_y = layout.size();

	for (unsigned i = 0; i < max_y; i++)
	{
		if (layout[i].size() > max_x)
		{
			max_x = layout[i].size();
		}
	}

	border.x = max_x * size_of_tiles;
	border.y = max_y * size_of_tiles;

	for (unsigned i = 0; i < max_y; i++)
	{
		if (layout[i].size() < max_x)
		{
			for (unsigned y = layout[i].size(); y <= max_x; y++)
			{
				layout[i].push_back(0);
			}
		}
	}
}

coordinates map::get_border() const
{
	return border;
}

void map::find_portas(){

	for(unsigned i = 0; i < layout.size(); i++){
		for(unsigned y = 0; y < layout[i].size(); y++){
			if (layout[i][y] == 't'){
				portals.push_back(coordinates(i,y));
			}
		}
	}

}