#include "mediator.h"
#include <stdio.h>
#include <QFile>
#include <QDir>
#include "format/file_game.h"
#include "format/file_npc.h"
#include "defines.h"

#define EDIT_MODE_NEW 0
#define EDIT_MODE_EDIT 1

extern struct file_game game;

extern char FILEPATH[255];
extern struct file_map map;
extern struct file_map map_backup;

Mediator::Mediator() {
	int i;

	palleteX=0;
	palleteY=0;
	//strcpy(selectedTileset, "data/images/tilesets/default.png");
	selectedTileset = "data/images/tilesets/default.png";
	editMode = EDITMODE_NORMAL;
	editTool = EDITMODE_NORMAL;
	npcGraphicSize_w = 16;
	npcGraphicSize_h = 16;
	NpcAddNumber=0;
	layerLevel=3;
	selectedNPC = -1;
	terrainType = 1;
	editModeNPC = EDIT_MODE_NEW;
	currentMap = 1;
        object_type = 3;
	for (i=0; i<NPC_FRAME_NUMBER; i++) {
		frameset[i]=-1;
		frameset_time[i] = 20;
	}
}

int Mediator::getPalleteX() {
	return palleteX;
}

int Mediator::getPalleteY() {
	return palleteY;
}

void Mediator::setPalleteX(int value) {
	palleteX = value;
}

void Mediator::setPalleteY(int value) {
	palleteY = value;
}

char *Mediator::getPallete() {
   //return currentPallete;
	return selectedTileset;
}

void Mediator::setPallete(char *value) {
	selectedTileset = value;
}



void Mediator::loadMap(int game_n, int map_n) {
    long lSize;
    char filename[255];
	char temp_cent_number[4];

	centNumberFormat(game_n);
	sprintf(temp_cent_number, "%s", centNumber);
	centNumberFormat(map_n);
	//printf("DEBUG.Mediator::loadMap - START\n");
	sprintf(filename, "%s/data/game/game_%s/%s.map", FILEPATH, temp_cent_number, centNumber);
	currentGame = game_n;
	currentMap = map_n;
	//printf("DEBUG.Mediator::loadMap - filename: %s\n", filename);
	FILE *fp = fopen(filename, "rb");
    if (fp) {
		//printf("Loading map file...\n");
        fseek (fp , 0 , SEEK_END);
        lSize = ftell (fp);
        rewind (fp);
        fread(&map, sizeof(file_map), 1, fp);
        fclose(fp);

/*
		for (int i=0; i<STAGE_OBJECT_LIMIT; i++) {
			printf("Cleaning object list %d, value before: %d", i, map.object_list[i].type);
			// removing npc from the map
			map.object_list[i].type = -1;
			printf(", value after: %d\n", map.object_list[i].type);
			map.object_list[i].framesize_w = -1;
			map.object_list[i].framesize_h = -1;
			map.object_list[i].start_point.x = -1;
			map.object_list[i].start_point.y = -1;
		}
*/



    } else {
        printf("DEBUG - no map file, ignoring load.\n");
    }
}


void Mediator::loadGame(int n) {
	long lSize;
	char filename[255];

	centNumberFormat(n);
	sprintf(filename, "%s/data/game/%s.gme", FILEPATH, centNumber);
	FILE *fp = fopen(filename, "rb");
	if (fp) {
		fseek (fp , 0 , SEEK_END);
		lSize = ftell (fp);
		rewind (fp);
		fread(&game, sizeof(game), 1, fp);
		fclose(fp);
		loadMap(n, 1);
	}
}

// set default values for game variable
void Mediator::initGameVar() {
    int j, k;
	strcpy (game.name, "My Game");
    sprintf(map.name, "Map 00%d", 1);
    map.bosss_door_x=200;
	sprintf(map.filename, "%s/data/images/tilesets/default.png", FILEPATH);
    for (j=0; j<MAP_W; j++) {
        for (k=0; k<MAP_H; k++) {
            map.tiles[j][k].locked=0;
			map.tiles[j][k].tile1.x=-1;
			map.tiles[j][k].tile1.y=-1;
			map.tiles[j][k].tile2.x=-1;
			map.tiles[j][k].tile2.y=-1;
			map.tiles[j][k].tile3.x=-1;
			map.tiles[j][k].tile3.y=-1;
		}
    }
	for (j=0; j<LINKS_NUMBER; j++) {
		game.map_links[j].link_pos.x= -1;
		game.map_links[j].link_pos.y= -1;
		game.map_links[j].link_dest.x= -1;
		game.map_links[j].link_dest.y= -1;
		game.map_links[j].map_origin = -1;
		game.map_links[j].map_dest = -1;
		game.map_links[j].link_size = 1;
		game.map_links[j].link_type = LINK_HORIZONTAL;
		game.map_links[j].link_bidi = 1;
	}
	for (j=0; j<STAGE_NPC_LIMIT; j++) {
		map.npc_list[j].hp.total = -1;
	}
	for (j=0; j<STAGE_OBJECT_LIMIT; j++) {
		map.object_list[j].type = -1;
		map.object_list[j].timer = -1;
		map.object_list[j].limit = -1;
		map.object_list[j].framesize_w = -1;
		map.object_list[j].framesize_h = -1;
	}
}

void Mediator::createGame() {
	char buffer[255];
	FILE *fp;
	int n;
	//QDir("Folder").exists();
	//QDir().mkdir("MyFolder");
	//QFile f( "f.txt" );
	//if( !f.exists() )
	// position in the last
	// look for a empty game slot
	sprintf(buffer, "%s/data/game/", FILEPATH);
	n = freeSlot(buffer, "gme");

	printf("DEBUG.Mediator::createGame - centNumber: %s\n", centNumber);
	sprintf(buffer, "%s/data/game/game_%s", FILEPATH, centNumber);
	if (!QDir(buffer).exists()) {
		printf("Creating '%s folder\n", buffer);
		QDir().mkdir(buffer);
	} else {
		printf("Folder '%s' already exists", buffer);
	}
	initGameVar();
	// creates the game file
	sprintf(buffer, "data/game/%s.gme", centNumber);
	fp = fopen(buffer, "wb");
	if (fp) {
		fwrite(&game, sizeof(game), 1, fp);
		fclose(fp);
		printf("Mediator::createGame - Created game file '%s'\n", buffer);
	} else {
		printf("ERROR: Can't open file '%s' to write\n", buffer);
	}
	// creates the map file
	sprintf(buffer, "%s/data/game/game_%s/001.map", FILEPATH, centNumber);
	fp = fopen(buffer, "wb");
	if (fp) {
		fwrite(&map, sizeof(map), 1, fp);
		fclose(fp);
		printf("Mediator::createGame - Created map file '%s'\n", buffer);
	} else {
		printf("ERROR: Can't open file '%s' to write\n", buffer);
	}
}


void Mediator::centNumberFormat(int n) {
	if (n >= 100) {
		sprintf(centNumber, "%d\0", n);
	} else if (n >= 10) {
		sprintf(centNumber, "0%d\0", n);
	} else {
		sprintf(centNumber, "00%d\0", n);
	}
	//printf("DEBUG.Mediator::centNumberFormat - centNumber: %s\n", centNumber);
}

int Mediator::freeSlot(char *dir, char *extension) {
	int i;
	char filename[255];
	for (i=1; i<99; i++) {
		centNumberFormat(i);
		sprintf(filename, "%s/%s.%s", dir, centNumber, extension);
		//printf("DEBUG - searching for dir: '%s', number: '%s'', extension: '%s'', filename: '%s'\n", dir, centNumber, extension, filename);
		QFile file(filename);
		if (!file.exists()) {
			return i;
		}
	}
	return -1;
}

void Mediator::resetMap(int map_n) {
	int j, k;

	sprintf(map.name, "Map 00%d", map_n);
	map.bosss_door_x=200;
	sprintf(map.filename, "%s/data/images/tilesets/default.png", FILEPATH);
	for (j=0; j<MAP_W; j++) {
		for (k=0; k<MAP_H; k++) {
			map.tiles[j][k].locked=0;
			map.tiles[j][k].tile1.x=-1;
			map.tiles[j][k].tile1.y=-1;
			map.tiles[j][k].tile2.x=-1;
			map.tiles[j][k].tile2.y=-1;
			map.tiles[j][k].tile3.x=-1;
			map.tiles[j][k].tile3.y=-1;
		}
	}
	for (j=0; j<STAGE_NPC_LIMIT; j++) {
		map.npc_list[j].hp.total = -1;
	}
}

void Mediator::addMap() {
	char filename[255];
	char buffer[255];
	int n;
	FILE *fp;

	centNumberFormat(currentGame);
	sprintf(filename, "%s/data/game/game_%s/", FILEPATH, centNumber);
	printf("DEBUG.Mediator::addMap - filename: %s\n", filename);
	n = freeSlot(filename, "map");
	resetMap(n);
	// creates the map file
	centNumberFormat(n);
	sprintf(buffer, "%s/%s.map", filename, centNumber);
	printf("DEBUG.Mediator::addMap - buffer: %s\n", buffer);
	fp = fopen(buffer, "wb");
	if (fp) {
		fwrite(&map, sizeof(map), 1, fp);
		fclose(fp);
		printf("Mediator::createGame - Created map file '%s'\n", buffer);
	} else {
		printf("ERROR: Can't open file '%s' to write\n", buffer);
	}
	loadMap(currentGame, currentMap);
}

void Mediator::getGameName(int n) {
	long lSize;
	char filename[255];
	centNumberFormat(n);
	struct file_game temp_game;
	sprintf(filename, "%s/data/game/%s.gme", FILEPATH, centNumber);
	FILE *fp = fopen(filename, "rb");
	if (fp) {
		fseek (fp , 0 , SEEK_END);
		lSize = ftell (fp);
		rewind (fp);
		fread(&temp_game, sizeof(temp_game), 1, fp);
		fclose(fp);
		printf("DEBUG;Mediator::getGameName - temp_game.name: %s\n", temp_game.name);
		sprintf(gameName, "%s", temp_game.name);
	} else {
		printf("DEBUG.Mediator::getGameName - Error opening file '%s'.\n",filename);
		sprintf(gameName, "");
	}
}



void Mediator::placeNpc(int posx, int posy, int npc_n) {
	struct file_npc temp_npc;
	char filename[255];
	char buffer[255];

	centNumberFormat(currentGame);
	sprintf(filename, "%s/data/game/game_%s", FILEPATH, centNumber);
	//printf("DEBUG.Mediator::placeNpc - dir: %s\n", filename);
	if (selectedNPC < 1) {
		printf(">>>> ERROR: selectedNPC '%d' invalid.\n", selectedNPC);
		return;
	} else {
		printf(">>>> WARNING: Adding selectedNPC '%d'.\n", selectedNPC);
	}
	centNumberFormat(selectedNPC);
	sprintf(buffer, "%s/%s.npc", filename, centNumber);
	printf("DEBUG.Mediator::placeNpc - filename: %s\n", buffer);
	FILE *fp = fopen(buffer, "rb");
	if (fp) {
		fread(&temp_npc, sizeof(file_npc), 1, fp);
		fclose(fp);
	} else {
		printf(">>>>>> DEBUG - no NPC file, ignoring load.\n");
		return;
	}
	
	map.npc_list[npc_n].behavior_mode = temp_npc.behavior_mode;
	map.npc_list[npc_n].facing = temp_npc.facing;
	sprintf(map.npc_list[npc_n].filename, "%s", temp_npc.filename);

	map.npc_list[npc_n].framesize_w = temp_npc.framesize_w;
	map.npc_list[npc_n].framesize_h = temp_npc.framesize_h;
	//printf(">>>> DEBUG filesize 1: %d, filesize 2: %d\n", temp_npc.filesize, map.npc_list[npc_n].filesize);
	//printf(">>>> DEBUG temp_npc.hp: %d\n", map.npc_list[npc_n].hp.total);
	map.npc_list[npc_n].hp.current = temp_npc.hp.current;
	map.npc_list[npc_n].hp.total = temp_npc.hp.total;
	printf(">>>> DEBUG npc_n: %d, map.npc.hp: %d\n", npc_n, map.npc_list[npc_n].hp.total);
	sprintf(map.npc_list[npc_n].name, "%s", temp_npc.name);
	map.npc_list[npc_n].start_point.x = posx;
	map.npc_list[npc_n].start_point.y = posy;
	map.npc_list[npc_n].vision_reach = temp_npc.vision_reach;
	map.npc_list[npc_n].walk_range = temp_npc.walk_range;
	map.npc_list[npc_n].can_shoot = temp_npc.can_shoot;
	map.npc_list[npc_n].is_boss = temp_npc.is_boss;
	map.npc_list[npc_n].have_shield = temp_npc.have_shield;
	printf(">>>> DEBUG npc.IA: %d\n", temp_npc.IA);
	map.npc_list[npc_n].IA = temp_npc.IA;
}


void Mediator::addObject(char name[20], char filename[50], unsigned short int type, unsigned short int timer, unsigned short int limit, unsigned short int framesize_w, unsigned short int framesize_h) {
	char buffer[255];
	struct struct_object temp_object;
	int n;

	sprintf(temp_object.name, "%s", name);
	sprintf(temp_object.filename, "%s", filename);
	temp_object.type = type;
	temp_object.timer = timer;
	temp_object.limit = limit;
	printf("DEBUG.Mediator::addObject - object.filename: '%s'', arg.filename: '%s'\n", temp_object.filename, filename);
	centNumberFormat(currentGame);
	sprintf(filename, "%s/data/game/game_%s", FILEPATH, centNumber);
	//printf("DEBUG.Mediator::addObject - dir: %s\n", filename);
	n = freeSlot(filename, "obj");
	sprintf(buffer, "%s/%s.obj", filename, centNumber);
	printf("DEBUG.Mediator::addObject - filename: '%s', name: '%s'\n", buffer, temp_object.name);
	temp_object.framesize_w = framesize_w;
	temp_object.framesize_h = framesize_h;
	printf("DEBUG.Mediator::addObject - framesize_w: %d, framesize_h: %d\n", framesize_w, framesize_h);
	FILE *fp = fopen(buffer, "wb");
	if (fp) {
		fwrite(&temp_object, sizeof(struct_object), 1, fp);
		fclose(fp);
	} else {
		printf("DEBUG - no map file, ignoring load.\n");
	}
}

void Mediator::placeObject(unsigned short int posx, unsigned short int posy, unsigned short int object_n) {
	struct struct_object temp_object;
	char filename[255];
	char buffer[255];

	centNumberFormat(currentGame);
	sprintf(filename, "%s/data/game/game_%s", FILEPATH, centNumber);
	//printf("DEBUG.Mediator::placeObject - dir: %s\n", filename);
	if (selectedNPC < 1) {
		printf(">>>> ERROR: selectedObject '%d' invalid.\n", selectedNPC);
		return;
	} else {
		printf(">>>> WARNING: Adding selectedObject '%d'.\n", selectedNPC);
	}
	centNumberFormat(selectedNPC);
	sprintf(buffer, "%s/%s.obj", filename, centNumber);
	FILE *fp = fopen(buffer, "rb");
	if (fp) {
		fread(&temp_object, sizeof(struct_object), 1, fp);
		fclose(fp);
	} else {
		printf(">>>>>> DEBUG - no Object file, ignoring load.\n");
		return;
	}
	printf("DEBUG.Mediator::placeObject - filename: %s, type: %d\n", buffer, temp_object.type);

	sprintf(map.object_list[object_n].filename, "%s", temp_object.filename);
	map.object_list[object_n].framesize_w = temp_object.framesize_w;
	map.object_list[object_n].framesize_h = temp_object.framesize_h;
	sprintf(map.object_list[object_n].name, "%s", temp_object.name);
	map.object_list[object_n].start_point.x = posx;
	map.object_list[object_n].start_point.y = posy;

	map.object_list[object_n].type = temp_object.type;
	map.object_list[object_n].timer = temp_object.timer;
	map.object_list[object_n].limit = temp_object.limit;
	map.object_list[object_n].speed = temp_object.speed;
}
