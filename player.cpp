#include "player.hpp"

extern const int window_height;
extern const int window_width;
extern const int size_of_tiles;

player::player() :
	coord(200, 1400), dir(1), plr_size(66, 46), speed(4), vel(2), alive(true), v_vel(0), 
	special_cooldown(0), standing_on_ground(false), prev_loc(0,0), sprite(0),score(0),
	ball_mode(0), portal_timer(0) {}

player::player(const int new_speed, const int new_vel, const int new_height, const int new_width) :
	coord(0, 0), dir(1), alive(true), v_vel(0), special_cooldown(0), speed(new_speed), 
	plr_size(new_width, new_height), vel(new_vel), standing_on_ground(false), prev_loc(0,0),
	sprite(0), score(0), ball_mode(0),portal_timer(0) {}

player::~player() {
	std::cout << "Player Destroyed" << std::endl;
}
sonic::~sonic() {
	std::cout << "Sonic Destroyed" << std::endl;
}
tails::~tails() {
	std::cout << "Tails Destroyed" << std::endl;
}
knuck::~knuck() {
	std::cout << "Knuckles Destroyed" << std::endl;
}

void player::collision(std::vector < std::vector <char> > &layout, std::vector <coordinates> &portals, coordinates border) {
	prev_loc = coord;
	if (coord.y + plr_size.height > border.y - 20) {
		coord.y = 100;
		alive = false;
	}
	if (coord.x + plr_size.width > border.x) {
		coord.x = border.x;
	}
	if (coord.y < 0) {
		coord.y = 0;
	}
	if (coord.x < 0) {
		coord.x = 0;
	}
	// did player hit right side of wall
	
	if (dir == -1) {
		int left_player_border = coord.x / size_of_tiles;
		int feet_loc = (coord.y + plr_size.height -1) / size_of_tiles;
		int head_loc = (coord.y ) / size_of_tiles;


		if (layout[feet_loc][left_player_border] == 'd') {
			int wall_top = feet_loc * size_of_tiles	;
			int wall_bot = wall_top + size_of_tiles	;
			int wall_right = left_player_border * size_of_tiles	 + size_of_tiles	;
			if (coord.x <= wall_right && (coord.y + plr_size.height >= wall_top + 10 && coord.y + plr_size.height <= wall_bot)) {
				
				layout[feet_loc][left_player_border] = 'o';
			}
		}
		if (layout[feet_loc][left_player_border] == 't') {
			int wall_top = feet_loc * size_of_tiles	;
			int wall_bot = wall_top + size_of_tiles	;
			int wall_right = left_player_border * size_of_tiles	 + size_of_tiles	;
			if (coord.x <= wall_right && (coord.y + plr_size.height >= wall_top + 10 && coord.y + plr_size.height <= wall_bot)) {
				if(portal_timer == 0){
					teleport(portals, coordinates(feet_loc, left_player_border));
				//return;
				}
			}
		}
		if (layout[head_loc][left_player_border] == 'd') {

			int wall_top = head_loc * size_of_tiles	;
			int wall_bot = wall_top + size_of_tiles	;
			int wall_right = left_player_border * size_of_tiles	 + size_of_tiles	;
			if (coord.x <= wall_right && coord.y >= wall_top && coord.y < wall_bot) {
				layout[feet_loc][left_player_border] = 'o';

			}
		}


		if (layout[feet_loc][left_player_border] == 'x' || layout[feet_loc][left_player_border] == 'j' || layout[feet_loc][left_player_border] == 's'  ) {
			int wall_top = feet_loc * size_of_tiles	;
			int wall_bot = wall_top + size_of_tiles	;
			int wall_right = left_player_border * size_of_tiles	 + size_of_tiles;
			if (layout[feet_loc][left_player_border] == 'j'){
				wall_top += 53;
				wall_right -= 24;
			}
			if (layout[feet_loc][left_player_border] == 's'){
				wall_top += 49;
			}
			if (coord.x <= wall_right && (coord.y + plr_size.height >= wall_top + 10 && coord.y + plr_size.height <= wall_bot)) {
				coord.x = wall_right + 1;
				if (standing_on_ground == false) {
					coord += coordinates(0,1);
				}
			}
		}
		if (layout[head_loc][left_player_border] == 'x' || layout[head_loc][left_player_border] == 'j' || layout[head_loc][left_player_border] == 's') {

			int wall_top = head_loc * size_of_tiles	;
			int wall_bot = wall_top + size_of_tiles	;
			int wall_right = left_player_border * size_of_tiles	 + size_of_tiles	;
			if (layout[head_loc][left_player_border] == 'j'){
				wall_top += 53;
				wall_right -= 24;
			}
			if (layout[head_loc][left_player_border] == 's'){
				wall_top += 49;
			}
			if (coord.x <= wall_right && coord.y >= wall_top + 10 && coord.y < wall_bot) {
				coord.x = wall_right + 1;
				if (standing_on_ground == false) {
					coord += coordinates(0,1);
				}
			}
		}
	}
	// did player hit left side of wall
	if (dir == 1) {

		int right_player_border = (coord.x + plr_size.width) / size_of_tiles;
		int feet_loc = (coord.y + plr_size.height -1) / size_of_tiles;
		int head_loc = (coord.y ) / size_of_tiles;

		if (layout[feet_loc][right_player_border] == 'd') {
			
			int wall_top = feet_loc * size_of_tiles	;
			int wall_bot = wall_top + size_of_tiles	;
			int wall_left = right_player_border * size_of_tiles	 - plr_size.width;
			if (coord.x >= wall_left && (coord.y + plr_size.height >= wall_top + 10 && coord.y + plr_size.height <= wall_bot)) {
				layout[feet_loc][right_player_border] = 'o';
			}
		}
		if (layout[feet_loc][right_player_border] == 't') {
			
			int wall_top = feet_loc * size_of_tiles	;
			int wall_bot = wall_top + size_of_tiles	;
			int wall_left = right_player_border * size_of_tiles	 - plr_size.width;
			if (coord.x >= wall_left && (coord.y + plr_size.height >= wall_top + 10 && coord.y + plr_size.height <= wall_bot)) {
				if(portal_timer == 0){
					teleport(portals, coordinates(feet_loc, right_player_border));

				}

			}
		}
		if (layout[head_loc][right_player_border] == 'd') {
			
			int wall_top = head_loc * size_of_tiles	;
			int wall_bot = wall_top + size_of_tiles	;
			int wall_left = right_player_border * size_of_tiles	 - plr_size.width;
			if (coord.x >= wall_left && coord.y >= wall_top && coord.y <= wall_bot) {
				layout[head_loc][right_player_border] = 'o';

			}
		}
		if (layout[feet_loc][right_player_border] == 'x' || layout[feet_loc][right_player_border] == 'j' || layout[feet_loc][right_player_border] == 's') {
			
			int wall_top = feet_loc * size_of_tiles;
			int wall_bot = wall_top + size_of_tiles;
			int wall_left = right_player_border * size_of_tiles - plr_size.width;
			if (layout[feet_loc][right_player_border] == 'j'){
				wall_top += 53;
				wall_left += 23;
			}
			if (layout[feet_loc][right_player_border] == 's'){
				wall_top += 49;
			}
			if (coord.x >= wall_left && (coord.y + plr_size.height >= wall_top + 10 && coord.y + plr_size.height <= wall_bot)) {

				coord.x = wall_left - 1;
				if (standing_on_ground == false) {
					coord += coordinates(0,1);
				}
			}
		}
		if (layout[head_loc][right_player_border] == 'x' || layout[head_loc][right_player_border] == 'j' || layout[head_loc][right_player_border] == 's') {
			
			int wall_top = head_loc * size_of_tiles	;
			int wall_bot = wall_top + size_of_tiles	;
			int wall_left = right_player_border * size_of_tiles	 - plr_size.width;
			if (layout[head_loc][right_player_border] == 'j'){
				wall_top += 53;
				wall_left += 23;
			}
			if (layout[head_loc][right_player_border] == 's'){
				wall_top += 49;
			}
			if (coord.x >= wall_left && coord.y >= wall_top && coord.y <= wall_bot) {
				coord.x = wall_left - 1;
				if (standing_on_ground == false) {
					coord += coordinates(0,1);
				}
			}
		}

	}
	// standing is standing on ground?
	int feet_loc = (coord.y + plr_size.height) / size_of_tiles;
	int feet_start = coord.x / size_of_tiles;
	int feet_end = (coord.x + plr_size.width) / size_of_tiles;

	if (layout[feet_loc][feet_start] == 'd' || layout[feet_loc][feet_end] == 'd') {
		
		int wall_top = feet_loc * size_of_tiles;
		int wall_left = feet_start * size_of_tiles;
		int wall_right = wall_left + size_of_tiles;
		if (coord.y + plr_size.height >= wall_top && coord.y + plr_size.height <= wall_top + 20 && (coord.x >= wall_left && coord.x + plr_size.width <= wall_right)) {
			layout[feet_loc][feet_start] = 'o';
		}
	}
	if (layout[feet_loc][feet_start] == 'j') {
		int wall_top = feet_loc * size_of_tiles + 54;
		int wall_left = feet_start * size_of_tiles ;
		int wall_right = wall_left + size_of_tiles;

		if (coord.y + plr_size.height >= wall_top && coord.x >= wall_left + 23 && coord.x <= wall_right - 24) {

			vel = -30;
		}
	}
	if (layout[feet_loc][feet_end] == 'j') {

		int wall_top = feet_loc * size_of_tiles + 54;
		int wall_left = feet_end * size_of_tiles;
		int wall_right = wall_left + size_of_tiles;

		if (coord.y + plr_size.height >= wall_top && (coord.x + plr_size.width >= wall_left +23 && coord.x + plr_size.width <= wall_right -24)) {

			vel = -30;

		}
	}
		if (layout[feet_loc][feet_start] == 's') {
		int wall_top = feet_loc * size_of_tiles + 59;
		int wall_left = feet_start * size_of_tiles ;
		int wall_right = wall_left + size_of_tiles;

		if (coord.y + plr_size.height >= wall_top && coord.x >= wall_left && coord.x <= wall_right) {

			alive = false;
		}
	}
	if (layout[feet_loc][feet_end] == 's') {

		int wall_top = feet_loc * size_of_tiles + 49;
		int wall_left = feet_end * size_of_tiles;
		int wall_right = wall_left + size_of_tiles;

		if (coord.y + plr_size.height >= wall_top && (coord.x + plr_size.width >= wall_left && coord.x + plr_size.width <= wall_right)) {

			alive = false;
		}
	}

	if (layout[feet_loc][feet_start] == 'x') {
		int wall_top = feet_loc * size_of_tiles;
		int wall_left = feet_start * size_of_tiles;
		int wall_right = wall_left + size_of_tiles;

		if (coord.y + plr_size.height >= wall_top  && coord.x >= wall_left && coord.x <= wall_right) {

			coord.y = wall_top - plr_size.height;
			vel = 4;
			standing_on_ground = true;
			if(v_vel == 0){
				ball_mode = false;
			}
		}
	}
	
	if (layout[feet_loc][feet_end] == 'x') {

		int wall_top = feet_loc * size_of_tiles;
		int wall_left = feet_end * size_of_tiles + size_of_tiles;
		int wall_right = wall_left + size_of_tiles;

		if (coord.y + plr_size.height >= wall_top  && (coord.x + plr_size.width >= wall_left && coord.x + plr_size.width <= wall_right)) {

			coord.y = wall_top - plr_size.height +2;
			vel = 4;
			standing_on_ground = true;
			if(v_vel == 0){
				ball_mode = false;
			}
		}
	}

	else {
		coord += coordinates(0,vel);;
		standing_on_ground = false;
	}
	// hit his head to something
	if (standing_on_ground == false) {
		int head_loc = (coord.y +1 ) / size_of_tiles;
		int head_start = coord.x / size_of_tiles;
		int head_end = (coord.x + plr_size.width) / size_of_tiles;

		if (layout[head_loc][head_start] == 'd' || layout[head_loc][head_end] == 'd') {
			int wall_bot = head_loc * size_of_tiles	 + size_of_tiles;
			int wall_left = head_start * size_of_tiles;
			int wall_right = wall_left + size_of_tiles;

			if (coord.y <= wall_bot && coord.y >= wall_bot - 21 && (coord.x + plr_size.width >= wall_left && coord.x <= wall_right)) {
				layout[head_loc][head_start] = 'o';
			}
		}

		if (layout[head_loc][head_start] == 'x' || layout[head_loc][head_end] == 'x' || layout[head_loc][head_start] == 'j' || layout[head_loc][head_end] == 'j') {
			int wall_bot = head_loc * size_of_tiles	 + size_of_tiles;
			int wall_left = head_start * size_of_tiles;
			int wall_right = wall_left + size_of_tiles;
			if(layout[head_loc][head_start] == 'j' || layout[head_loc][head_end] == 'j'){
				wall_left += 23;
				wall_right -= 24;
			}

			if (coord.y <= wall_bot && coord.y >= wall_bot - 21 && (coord.x + plr_size.width >= wall_left && coord.x <= wall_right)) {

				coord.y = wall_bot;
				vel = 10;
			}
		}
	}
	
}

void player::move() {

	const auto state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_D]) {
		coord.x += speed;
		dir = 1;
	}
	if (state[SDL_SCANCODE_A]) {
		coord.x -= speed;
		dir = -1;
	}
	if (state[SDL_SCANCODE_SPACE] && standing_on_ground == true) {
		standing_on_ground = false;
		coord.y--;
		vel = -20;
	}
	if (vel < 4 && standing_on_ground == false) {
		vel += 1;
	}
}

size player::get_size() const {
	return plr_size;
}

void sonic::move() {
	const auto state = SDL_GetKeyboardState(NULL);
	if(portal_timer > 0){
		portal_timer--;
	}
	if (state[SDL_SCANCODE_S] && v_vel == 0 && special_cooldown == 0) {
		
		v_vel = 22;
		special_cooldown = 300;
	}

	if (state[SDL_SCANCODE_D]) {

		coord += coordinates (speed, 0 );
		dir = 1;
	}

	if (state[SDL_SCANCODE_A]) {
		coord -= coordinates (speed, 0 );
		dir = -1;
	}
	if (v_vel > 0) {
		ball_mode = true;
		if (dir == -1) {
			coord -= coordinates (v_vel, 0);
		}
		else {
			coord += coordinates (v_vel, 0);
		}
		v_vel--;
	}

	if (special_cooldown > 0) {
		special_cooldown--;
	}
	if (state[SDL_SCANCODE_SPACE] && standing_on_ground == true) {
		standing_on_ground = false;
		ball_mode = true;
		coord -= coordinates (0, 1);
		vel = -21;
	}
	if (vel < 10 && standing_on_ground == false) {
		vel += 1;
	}
	if(prev_loc == coord){
		moved = false;
	}
	else {
		moved = true;
	}
}

void player::draw(SDL_Renderer* ren, SDL_Rect img, SDL_Rect loc) {
	if(ball_mode){
		sprites[2].draw(ren, &img, &loc);
	}
	else if (dir == 1) {
		sprites[1].draw(ren, &img, &loc);
	}
	else {
		sprites[0].draw(ren, &img, &loc);
	}
}

void tails::move() {

	const auto state = SDL_GetKeyboardState(NULL);

	if (state[SDL_SCANCODE_D]) {
		coord += coordinates (speed, 0 );
		dir = 1;
	}

	if (state[SDL_SCANCODE_A]) {
		coord -= coordinates (speed, 0 );
		dir = -1;
	}

	if (state[SDL_SCANCODE_SPACE] && standing_on_ground == true) {
		standing_on_ground = false;
		coord -= coordinates (0,1);
		if (special_cooldown == 0) {
			vel = -25;
		}
		else
		{
			vel = -21;
		}
	}
	if (state[SDL_SCANCODE_S] && standing_on_ground == false && special_cooldown == 0) {

		special_cooldown = 300;
		vel = -25;

	}
	if (special_cooldown > 0) {
		special_cooldown--;
	}


	if (vel < 10 && standing_on_ground == false) {
		vel += 1;
	}
}

void knuck::move() {

	const auto state = SDL_GetKeyboardState(NULL);

	if (state[SDL_SCANCODE_D]) {
		coord.x += speed;
		dir = 1;
	}
	if (state[SDL_SCANCODE_A]) {
		coord.x -= speed;
		dir = -1;
	}
	if (state[SDL_SCANCODE_SPACE] && standing_on_ground == true) {
		standing_on_ground = false;
		coord.y--;
		vel = -18;
	}
	if (vel < 10 && standing_on_ground == false) {
		vel += 1;
	}
}

void player::set_player_srect() {
	srect = { 0, 0, get_size().width/2,get_size().height/2 };
}
void player::set_new_image(const int &x) {
	if (moved == false){
		sprite = 0;
	}
	else {
		if (x==0){
			sprite++;
		}
		if(standing_on_ground && sprite > 7){
				sprite = 0;
		}
		else if (sprite > 4){
			sprite = 0;
		}
	}
	if (standing_on_ground){
		srect = { sprite * 25, 0, get_size().width,get_size().height };
	}
	else {
		srect = { sprite * 26, 0, get_size().width,get_size().height };
	}
}
void player::set_loc(const coordinates &camera) {
	loc = { coord.x - camera.x, coord.y - camera.y, plr_size.width, plr_size.height };
}

void print_name(char_name* plr) {
	std::cout << "Player chose: " << plr->get_class_name() << std::endl;
}

void player::load_sprites(SDL_Renderer* ren){
	std::cout<<"ERROR: Player is not selected"<<std::endl;
}
void sonic::load_sprites(SDL_Renderer* ren){

	sprites[0].load_img(ren,"textures/sonic_left.png");
	sprites[1].load_img(ren,"textures/sonic_right.png");
	sprites[2].load_img(ren,"textures/sonic_ball.png");

}
void tails::load_sprites(SDL_Renderer* ren){
	sprites[0].load_img(ren,"textures/tails_left.png");
	sprites[1].load_img(ren,"textures/tails_right.png");
	sprites[2].load_img(ren,"textures/tails_ball.png");

}
void knuck::load_sprites(SDL_Renderer* ren){
	sprites[0].load_img(ren,"textures/knuck_left.png");
	sprites[1].load_img(ren,"textures/knuck_right.png");
	sprites[2].load_img(ren,"textures/knuck_ball.png");
}

void player::draw_score(SDL_Renderer *ren, Image &numbers){
	//print_something("score", score);
	std::vector<int> number;
	int temp = score;
	while (temp != 0){
		number.push_back(temp%10);
		temp /= 10;
	}
	if(score == 0){
		number.push_back(0);
	}
	int i = 0;
	reverse(number.begin(), number.end());
	for(auto it = number.begin(); it != number.end(); ++it){
		SDL_Rect num_srect = {(*it + 2) * 8, 0, 8, 13};
		SDL_Rect num_loc = {40 + i * 8, 60, 8, 13};
		numbers.draw(ren, &num_srect, &num_loc);
		i++;
	}
}

void player::teleport(std::vector<coordinates> &portal_locs, const coordinates &curent_portal ){
	portal_timer = 200;
	int portal_number = 0;
	for(unsigned i = 0; i < portal_locs.size(); i++){
		if(portal_locs[i].x == curent_portal.x && portal_locs[i].y == curent_portal.y ){
			portal_number = i;
			
			break;
		}
	}
	for(unsigned i = 0; i < portal_locs.size(); i++){
		if(portal_number != i){

			coord.y = portal_locs[i].x * size_of_tiles;
			coord.x = portal_locs[i].y * size_of_tiles + size_of_tiles/2;
			break;
		}
	}
	

}
