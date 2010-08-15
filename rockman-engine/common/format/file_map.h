#ifndef FILE_MAP
#define FILE_MAP

#include <stdio.h>
#include "file_npc.h"
#include "file_object.h"

#define MAP_W 200 // this size was determined by looking at common maps from games
#define MAP_H 13
#define STAGE_NPC_LIMIT 50
#define STAGE_OBJECT_LIMIT 40

// "ground" types
#define TERRAIN_SOLID 1
#define TERRAIN_STAIR 2
#define TERRAIN_DOOR 3
#define TERRAIN_SPIKE 4
#define TERRAIN_WATER 5
#define TERRAIN_ICE 6
#define TERRAIN_MOVE_LEFT 7
#define TERRAIN_MOVE_RIGHT 8
#define TERRAIN_SAND 9


#define OBJ_MOVING_PLATFORM_UPDOWN 0
#define OBJ_MOVING_PLATFORM_LEFTRIGHT 1
#define OBJ_DISAPPEARING_BLOCK 2
#define OBJ_ENERGY_TANK 3
#define OBJ_WEAPON_TANK 4
#define OBJ_ENERGY_PILL_BIG 4
#define OBJ_WEAPON_PILL_BIG 6
#define OBJ_ENERGY_PILL_SMALL 7
#define OBJ_WEAPON_PILL_SMALL 8
#define OBJ_LIFE 9
#define OBJ_FALL_PLATFORM 10

struct tile_pos {
	short int x;
	short int y;
};

// information each point of map holds
struct map_tile {
    short int locked;
    struct tile_pos tile1;                  // position of tile (x and y) in the graphic file (each tile is 16*16)
    struct tile_pos tile2;                  // second level tile. this can be used to create more complex backgrounds
    struct tile_pos tile3;                  // tird level, to be shown over player
};


struct file_map {
    char name[50];
    char filename[50];
    short int bosss_door_x;						// tells what is the X position of boss door. this is used to not scrolling after this point
    struct map_tile tiles[MAP_W][MAP_H];		// map tiles
    struct file_npc npc_list[STAGE_NPC_LIMIT];	// we limit the number of enemies to 50 in the stage
	struct struct_object object_list[STAGE_OBJECT_LIMIT];
};



#endif
