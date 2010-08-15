#ifndef FILE_GAME
#define FILE_GAME

#define LINKS_NUMBER 40

#include "file_map.h"
#include "shared.h"

struct map_link {
	struct tile_pos link_pos;				// position in map of origin
	struct tile_pos link_dest;				// position in map of destiny
	short int map_origin;			// number of origin map
	short int map_dest;			// number of destiny map
	unsigned short int link_size;			// size of it, in tiles
	unsigned short int link_type;			// can be LINK_VERTICAL OR LINK_HORIZONTAL
	unsigned short int link_bidi;			// indicates if it is bidirecional
	unsigned short int is_door;				// if it is a door, it is not bidiand willmake door sound and show animation of door opening/closing
};

struct struct_stage {
	char boss_name[50];
	char boss_face_filename[50];
	char boss_sprites_filename[50];
	char bgMusic[100];
	struct coordinate initial_point;
	unsigned short int initial_map_number;
	struct coordinate zone_point;
};


struct struct_zone {
	char bg_filename[100];					// background image filename
	struct struct_stage stages[8];
};


struct file_game {
	char name[50];
	struct map_link map_links[LINKS_NUMBER];// links from the map to another one (two for each map is more than enought)
	struct struct_zone zones[3];			// stage select, castle 1 and castle 2
};



#endif
