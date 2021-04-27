#ifndef ENEMY_HPP_INCLUDED
#define ENEMY_HPP_INCLUDED

#include <vector>
#include "SDL.hpp"
#include "game.hpp"
#include "map.hpp"
#include "player.hpp"

class player;

class enemy {

protected:
	const int speed;
	int dir;
	int vel;
	const size enemy_size;
	bool standing_on_ground;
	
public:
	enemy();
	enemy(const int new_speed, const int new_height, const int new_width, const int new_x, const int new_y);
	virtual ~enemy();
	coordinates coord;
	bool alive;
	Image left,
		right,
		main;

	size get_size() const;
	virtual void collision(const std::vector < std::vector <char> > &layout,const coordinates &border, player* &plr);
	virtual void move();
	void check_if_in_boundries(const coordinates &border);

};

class fast_enemy : public enemy {
	
	
public:
	fast_enemy(const int new_x = 1000, const int new_y = 400, const int new_speed = 4, const int new_height = 58, const int new_width = 34) : enemy(new_x, new_y, new_speed, new_height, new_width) {}
	~fast_enemy();
};

class slow_enemy : public enemy {

public:
	slow_enemy(const int new_x = 50, const int new_y = 50, const int new_speed = 4, const int new_height = 58, const int new_width = 34) : enemy(new_x, new_y, new_speed, new_height, new_width) {}
	~slow_enemy();
};

class flying_enemy : public enemy {

public:
	flying_enemy(const int new_x = 500, const int new_y = 200, const int new_speed = 4, const int new_height = 94, const int new_width = 36) : enemy(new_x, new_y, new_speed, new_height, new_width) {}
	void collision(const std::vector < std::vector <char> > &layout, const coordinates &border, player* &plr);
	void move();
	~flying_enemy();
};

class jumping_enemy : public enemy {
public:
	jumping_enemy(const int new_x = 500, const int new_y = 200, const int new_speed = 4,const int new_height = 58, const int new_width = 34) : enemy(new_x, new_y, new_speed, new_height, new_width) {}
	void move();
};

#endif // ENEMY_HPP_INCLUDED
