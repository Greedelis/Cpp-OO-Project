#include "camera.hpp"
#include "player.hpp"

extern const int window_height;
extern const int window_width;

coordinates camera::cam;

void camera::set_camera(coordinates border, size plr_size, coordinates plr_loc)
{

	cam.x = plr_loc.x + plr_size.width / 2 - window_width / 2;
	cam.y = plr_loc.y + plr_size.height / 2 - window_height / 2;

	if (cam.x < 0)
	{
		cam.x = 0;
	}
	if (cam.x + window_width > border.x)
	{
		cam = border - coordinates(window_width, 0);
		//cam.x = border.x - window_width;
	}
	if (cam.y < 0)
	{
		cam.y = 0;
	}
	if (cam.y + window_height > border.y)
	{
		cam.y = border.y - window_height; // when I am trying to do the same, as with x
										  // it just dosent want to work, for some reason
	}
}

void timer::print_time(SDL_Renderer *ren)
{

	int min = frame / 3600;
	int sec = frame % 3600 / 60;
	std::string min_text = std::to_string(min);
	std::string sec_text = std::to_string(sec);
	std::string time_text = min_text + ":" + sec_text;
	//print_something("time", time_text);

	set_number(min / 10 + 2);
	set_loc(0);
	numbers.draw(ren, &srect, &loc);
	set_number(min % 10 + 2);
	set_loc(1);
	numbers.draw(ren, &srect, &loc);
	set_number(0);
	set_loc(2);
	numbers.draw(ren, &srect, &loc);
	set_number(sec / 10 + 2);
	set_loc(3);
	numbers.draw(ren, &srect, &loc);
	set_number(sec % 10 + 2);
	set_loc(4);
	numbers.draw(ren, &srect, &loc);
}