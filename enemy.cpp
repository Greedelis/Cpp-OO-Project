#include "enemy.hpp"

extern const int size_of_tiles;

enemy::enemy() : coord(770, 1400), dir(-1), enemy_size(36, 58), vel(3), speed(2), alive(true) {}

enemy::enemy(int new_x, int new_y, int new_speed, int new_height, int new_width) : dir(-1), vel(3), alive(true), speed(new_speed), enemy_size(new_height, new_width)
{
	coord.x = new_x;
	coord.y = new_y;
}

enemy::~enemy()
{
	std::cout << "Enemy destroyed" << std::endl;
}
fast_enemy::~fast_enemy()
{
	std::cout << "Fast Enemy destroyed" << std::endl;
}
slow_enemy::~slow_enemy()
{
	std::cout << "Slow Enemy destroyed" << std::endl;
}
flying_enemy::~flying_enemy()
{
	std::cout << "Flying Enemy destroyed" << std::endl;
}
void enemy::collision(const std::vector<std::vector<char>> &layout, const coordinates &border, player *&plr)
{

	if (dir == 1)
	{
		main = right;
	}
	else if (dir == -1)
	{
		main = left;
	}

	check_if_in_boundries(border);

	if (plr->location().y + plr->get_size().height >= coord.y && plr->location().y + plr->get_size().height <= coord.y + 10 && ((plr->location().x >= coord.x && plr->location().x <= coord.x + enemy_size.width) || (plr->location().x + plr->get_size().width >= coord.x && plr->location().x + plr->get_size().width <= coord.x + enemy_size.width)))
	{
		alive = false;
		plr->vel = -10;
		plr->coord.y -= 1;
		plr->standing_on_ground = false;
		plr->add_score(100);
	}
	else if (((plr->location().x >= coord.x && plr->location().x <= coord.x + enemy_size.width) || (plr->location().x + plr->get_size().width >= coord.x && plr->location().x + plr->get_size().width <= coord.x + enemy_size.width)) && plr->location().y + plr->get_size().height >= coord.y && plr->location().y <= coord.y + enemy_size.height)
	{
		if (plr->ball_mode)
		{
			alive = false;
			plr->add_score(100);
		}
		else
		{
			plr->alive = false;
		}
	}

	int feet_loc = (coord.y + enemy_size.height) / size_of_tiles;
	int feet_start = coord.x / size_of_tiles;
	int feet_end = (coord.x + enemy_size.width) / size_of_tiles;

	if (layout[feet_loc][feet_start] == 'x' || layout[feet_loc][feet_end] == 'x')
	{

		int wall_top = feet_loc * size_of_tiles;
		int wall_left = feet_start * size_of_tiles;
		int wall_right = wall_left + size_of_tiles;

		if (coord.y + enemy_size.height >= wall_top && coord.y + enemy_size.height <= wall_top + 20 && (coord.x >= wall_left - 1 && coord.x + enemy_size.width <= wall_right + 1))
		{

			coord.y = wall_top - enemy_size.height;
			vel = 10;
			standing_on_ground = true;
		}
	}
	else
	{
		coord.y += vel;
		standing_on_ground = false;
	}

	if (standing_on_ground == false)
	{
		int head_loc = coord.y / size_of_tiles;
		int head_start = coord.x / size_of_tiles;
		int head_end = (coord.x + enemy_size.width) / size_of_tiles;

		if (layout[head_loc][head_start] == 'x' || layout[head_loc][head_end] == 'x')
		{
			int wall_bot = head_loc * size_of_tiles + size_of_tiles;
			int wall_left = head_start * size_of_tiles;
			int wall_right = wall_left + size_of_tiles;

			if (coord.y <= wall_bot && coord.y >= wall_bot - 20 && (coord.x + enemy_size.width >= wall_left && coord.x <= wall_right))
			{

				coord.y = wall_bot;
				vel = 10;
			}
		}
	}

	if (dir == -1)
	{
		int left_enemy_border = coord.x / size_of_tiles;
		int feet_loc = (coord.y + enemy_size.height - 1) / size_of_tiles;

		if (layout[feet_loc][left_enemy_border] == 'x')
		{

			int wall_top = feet_loc * size_of_tiles;
			int wall_bot = wall_top + size_of_tiles;
			int wall_right = left_enemy_border * size_of_tiles + size_of_tiles;

			if (coord.x <= wall_right && (coord.y + enemy_size.height >= wall_top + 10 && coord.y + enemy_size.height <= wall_bot))
			{

				coord.x = wall_right + 1;
				dir = 1;
			}
		}
	}

	if (dir == 1)
	{

		int right_enemy_border = (coord.x + enemy_size.width) / size_of_tiles;
		int feet_loc = (coord.y + enemy_size.height - 1) / size_of_tiles;

		if (layout[feet_loc][right_enemy_border] == 'x')
		{

			int wall_top = feet_loc * size_of_tiles;
			int wall_bot = wall_top + size_of_tiles;
			int wall_left = right_enemy_border * size_of_tiles;
			if (coord.x >= wall_left - enemy_size.width && (coord.y + enemy_size.height >= wall_top + 10 && coord.y + enemy_size.height <= wall_bot))
			{

				coord.x = wall_left - enemy_size.width - 1;
				dir = -1;
			}
		}
	}
}

void flying_enemy::collision(const std::vector<std::vector<char>> &layout, const coordinates &border, player *&plr)
{

	if (dir == 1)
	{
		main = right;
	}
	else if (dir == -1)
	{
		main = left;
	}

	check_if_in_boundries(border);

	if (plr->location().y + plr->get_size().height >= coord.y && plr->location().y + plr->get_size().height <= coord.y + 10 && ((plr->location().x >= coord.x && plr->location().x <= coord.x + enemy_size.width) || (plr->location().x + plr->get_size().width >= coord.x && plr->location().x + plr->get_size().width <= coord.x + enemy_size.width)))
	{
		alive = false;
		plr->vel = -10;
		plr->coord.y - 1;
		plr->standing_on_ground = false;
		plr->add_score(150);
	}
	else if (((plr->location().x >= coord.x && plr->location().x <= coord.x + enemy_size.width) || (plr->location().x + plr->get_size().width >= coord.x && plr->location().x + plr->get_size().width <= coord.x + enemy_size.width)) && plr->location().y + plr->get_size().height >= coord.y && plr->location().y <= coord.y + enemy_size.height)
	{
		if (plr->ball_mode)
		{
			alive = false;
			plr->add_score(100);
		}
		else
		{
			plr->alive = false;
		}
	}

	if (dir == 1)
	{
		main = right;
	}
	else if (dir == -1)
	{
		main = left;
	}

	if (dir == -1)
	{
		int left_enemy_border = coord.x / size_of_tiles;
		int feet_loc = (coord.y + enemy_size.height - 1) / size_of_tiles;

		if (layout[feet_loc][left_enemy_border] == 'x')
		{

			int wall_top = feet_loc * size_of_tiles;
			int wall_bot = wall_top + size_of_tiles;
			int wall_right = left_enemy_border * size_of_tiles + size_of_tiles;

			if (coord.x <= wall_right && (coord.y + enemy_size.height >= wall_top + 10 && coord.y + enemy_size.height <= wall_bot))
			{

				coord.x = wall_right + 1;
				dir = 1;
			}
		}
	}

	if (dir == 1)
	{

		int right_enemy_border = (coord.x + enemy_size.width) / size_of_tiles;
		int feet_loc = (coord.y + enemy_size.height - 1) / size_of_tiles;

		if (layout[feet_loc][right_enemy_border] == 'x')
		{

			int wall_top = feet_loc * size_of_tiles;
			int wall_bot = wall_top + size_of_tiles;
			int wall_left = right_enemy_border * size_of_tiles;
			if (coord.x >= wall_left - enemy_size.width && (coord.y + enemy_size.height >= wall_top + 10 && coord.y + enemy_size.height <= wall_bot))
			{

				coord.x = wall_left - enemy_size.width - 1;
				dir = -1;
			}
		}
	}
}

void enemy::move()
{
	if (standing_on_ground == false)
	{
		if (dir == 1)
		{
			coord.x += 1;
		}
		else
		{
			coord.x -= 1;
		}
	}
	else
	{
		if (dir == 1)
		{
			coord.x += speed;
		}
		else
		{
			coord.x -= speed;
		}
	}
}
void flying_enemy::move()
{
	if (dir == 1)
	{
		coord.x += speed;
	}
	else
	{
		coord.x -= speed;
	}
}

size enemy::get_size() const
{
	return enemy_size;
}

void enemy::check_if_in_boundries(const coordinates &border)
{

	if (coord.y > border.y)
	{
		coord.y = border.y;
		alive = false;
	}
	if (coord.x > border.x)
	{
		coord.x = border.x - enemy_size.width;
		dir = -1;
	}
	if (coord.y < 0)
	{
		coord.y = 0;
	}
	if (coord.x < 0)
	{
		coord.x = 0;
		dir = 1;
	}
}
void jumping_enemy::move()
{
	if (vel < 7)
	{
		vel++;
	}
	if (standing_on_ground == false)
	{
		if (dir == 1)
		{
			coord.x += 4;
		}
		else
		{
			coord.x -= 4;
		}
	}
	else
	{
		if (dir == 1)
		{
			coord.x += speed;
		}
		else
		{
			coord.x -= speed;
		}
	}
	if (standing_on_ground == true)
	{
		standing_on_ground = false;
		coord.y--;
		vel = -20;
	}
}
