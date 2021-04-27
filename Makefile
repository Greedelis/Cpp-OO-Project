CXXFLAGS = -std=c++17 -g 
LXXFLAGS = -lSDL2main -lSDL2 -lSDL2_image -g

main: main.o player.o SDL.o game.o map.o enemy.o window.o camera.o
	g++ main.o player.o SDL.o game.o map.o enemy.o window.o camera.o -o main $(LXXFLAGS) 

main.exe: main.o player.o SDL.o game.o map.o enemy.o window.o camera.o
	g++ main.o player.o SDL.o game.o map.o enemy.o window.o camera.o -o main.exe $(LXXFLAGS) 
	
main.o: main.cpp
	g++ main.cpp -c $(CXXFLAGS) 
	
player.o: player.cpp
	g++ player.cpp -c $(CXXFLAGS)
	
SDL.o: SDL.cpp
	g++ SDL.cpp -c $(CXXFLAGS)
	
game.o: game.cpp
	g++ game.cpp -c $(CXXFLAGS)
	
map.o: map.cpp
	g++ map.cpp -c $(CXXFLAGS)
	
enemy.o: enemy.cpp
	g++ enemy.cpp -c $(CXXFLAGS)
	
window.o: window.cpp
	g++ window.cpp -c $(CXXFLAGS)
	
camera.o: camera.cpp
	g++ camera.cpp -c $(CXXFLAGS)
