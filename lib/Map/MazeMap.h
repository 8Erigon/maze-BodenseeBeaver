#include <cstdint>
#ifndef map_h
#define map_h

enum tileColor {
	white,
	blue,
	black
};

enum skyDirection{
	north = 0,
	south = 1,
	west = 2,
	east = 3
};

/*uint8_t statt bool um victims zu speichern:
NULL = undefiniert,
0b00000000 = keine Wand,
0b10000000 = Wand,
0b11000000 = Victim an Wand; */
struct wallsOfTile{  
	uint8_t north;
	uint8_t east;
	uint8_t south;
	uint8_t west;
};

class Map{ 
	public: 
	Map();
	wallsOfTile getWalls(int x, int y) {
		wallsOfTile walls; 
		walls.north = horizontalWall[x][y+1]; 
		walls.east = verticalWall[x+1][y]; 
		walls.south = horizontalWall[x][y]; 
		walls.west = verticalWall[x][y]; 
		return walls; 
	};
	void setWall(int x, int y, skyDirection seite, uint8_t wall){
		if(seite < 2){
			horizontalWall[x][y + seite] = wall;
		}else{
			verticalWall[x][y + (seite - 2)] = wall;
		}
	};
	tileColor floor[10][10];
	uint8_t horizontalWall[10][10];
	uint8_t verticalWall[10][10];
};


#endif