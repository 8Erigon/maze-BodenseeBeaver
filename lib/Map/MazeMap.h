#include <cstdint>
#ifndef map_h
#define map_h

#define mapLenght 10
#define mapWidth 10
enum tileColor {
	white,
	blue,
	black
};

enum skyDirection{
	north = 0,
	south = 1,
	west = 2,
struct wallsOfTile{  
	uint8_t north;
	uint8_t east;
	uint8_t sout
	east = 3
};

/*uint8_t statt bool um victims zu speichern:
NULL = undefiniert,
0b00000000 = keine Wand,
0b10000000 = Wand,
0b11000000 = Victim an Wand; 
NEIN schnell > speichereffizienz*/
/*
@details uint8_t for each of the 4 directions. For Walls or Victims.
*/h;
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
	victimsOfTile getVictims(int x, int y) {
		wallsOfTile victims; 
		victims.north = horizontalVictim[x][y+1][0]; 
		victims.east = verticalVictim[x+1][y][0]; 
		victims.south = horizontalVictim[x][y][1]; 
		victims.west = verticalVictim[x][y][1]; 
		return victims; 
	};	
	/*
	@param xy coorsinate of the tile
	@param seite side fo the tile on which the wall is
	*/
	void setWall(int x, int y, skyDirection seite, bool wall){
		if(seite % 2){
			horizontalWall[x][y + seite] = wall;
		}else{
			verticalWall[x][y + (seite - 2)] = wall;
		}
	};
	/*
	@param xy coorsinate of the tile
	@param seite side fo the tile on which the victims is
	*/
	void setVictim(int x, int y, skyDirection seite, uint8_t victim){
		uint8_t sideOfWall;
		if(seite >= 2){
			sideofWall = 1;
		}
		if(seite % 2){
			horizontalVictim[x][y + seite][] = victim;
		}else{
			verticalVictim[x][y + (seite - 2)][] = victim;
		}
	};
	tileColor floor[mapWidth][mapLenght];
	bool horizontalWall[mapWidth][mapLenght];
	bool verticalWall[mapWidth][mapLenght];
	/*
	@param 3rd_index 0=west side; 1=east side
	@details Victim on a side of a vertical wall
	*/
	uint8_t verticalVictim[mapWidth][mapLenght][2];
	/*
	@param 3rd_index 0=south side; 1=north side
	@details Victim on a side of a horizontal wall
	*/
	uint8_t horizontalVictim[mapWidth][mapLenght][2];
};


#endif