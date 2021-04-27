#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <array>
#include "SDL.hpp"
#include "game.hpp"
#include "map.hpp"
#include "camera.hpp"
#include "enemy.hpp"

class char_name
{
  public:
	virtual void move() = 0;
	virtual std::string get_class_name() = 0;
};

class player : public char_name
{
  protected:
	int portal_timer;
	int dir;
	int v_vel;
	const int speed;
	const size plr_size;
	int special_cooldown;
	coordinates prev_loc;
	int sprite;
	bool moved;
	int score;
	void teleport(std::vector<coordinates>&,const coordinates &curent_portal );
  public:
	int vel;
	bool alive;
	bool ball_mode;
	coordinates coord;
	coordinates last_coord;
	bool standing_on_ground;
	std::array<Image, 3> sprites;

	player();
	player(const int new_speed, const int new_vel, const int new_height, const int new_width);
	virtual ~player();

	SDL_Rect srect;
	SDL_Rect loc;

	void move();
	void set_player_srect();
	void set_new_image(const int &x);
	void set_loc(const coordinates &camera);
	void draw(SDL_Renderer *ren, SDL_Rect img, SDL_Rect loc);
	void collision(std::vector < std::vector <char> > &layout, std::vector <coordinates> &portals, coordinates border);
	std::string get_class_name() { return "Player"; }
	coordinates location() const { return coord; }
	size get_size() const;
	virtual void load_sprites(SDL_Renderer *ren);
	void add_score(const int value)
	{
		score += value;
	}
	void draw_score(SDL_Renderer *ren, Image &numbers);

	friend class enemy;
};

class sonic : public player
{
  public:
	~sonic();
	sonic(const int new_speed = 8, const int new_vel = 4, const int new_height = 35, const int new_width = 25) : player(new_speed, new_vel, new_height, new_width) {}

	void move();
	void load_sprites(SDL_Renderer *ren);
	std::string get_class_name() { return "Sonic"; }
};

class tails : public player
{
  public:
	~tails();
	tails(const int new_speed = 6, const int new_vel = 3, const int new_height = 58, const int new_width = 82) : player(new_speed, new_vel, new_height, new_width) {}

	void move();
	void load_sprites(SDL_Renderer *ren);
	std::string get_class_name() { return "Tails"; }
};
class knuck : public player
{
  public:
	~knuck();
	knuck(const int new_speed = 5, const int new_vel = 6, const int new_height = 70, const int new_width = 52) : player(new_speed, new_vel, new_height, new_width) {}

	void move();
	void load_sprites(SDL_Renderer *ren);
	std::string get_class_name() { return "Knuckles"; }
};

void print_name(char_name *plr);

#endif // PLAYER_HPP_INCLUDED
