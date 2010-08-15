#ifndef MEDIATOR_H
#define MEDIATOR_H
#include <QString>
#include "format/file_npc.h"


class Mediator {
private:
	int palleteX;
	int palleteY;
	char *selectedTileset;

public:
	char gameName[50];
	char centNumber[4];
	int currentGame;
	int currentMap;
	//QString *NpcPreviewFile;
	char addNpcFilename[255];
	int NpcAddNumber;
	int layerLevel;
	int selectedNPC;
	int editMode;
	int editTool;
	int editModeNPC;
	int frameset[NPC_FRAME_NUMBER];				// holds information about the type of each frame
	int frameset_time[NPC_FRAME_NUMBER];		// the number of milisseconds this frame leasts
	int object_type;
	int terrainType;

	Mediator();
	int getPalleteX();
	int getPalleteY();
	void setPalleteX(int value);
	void setPalleteY(int value);
	char *getPallete();
	void setPallete(char *value);
	void initGameVar();
	void loadGame(int n);

	void loadMap(int game_n, int map_n);
	int npcGraphicSize_w;
	int npcGraphicSize_h;
	void createGame();
	int freeSlot(char *dir, char *extension);
	void centNumberFormat(int n);
	void getGameName(int n);
	void addMap();
	void resetMap(int);
	void placeNpc(int posx, int posy, int npc_n);
	void addObject(char name[20], char filename[50], unsigned short int type, unsigned short int timer, unsigned short int limit, unsigned short int, unsigned short int);
	void placeObject(unsigned short int , unsigned short int, unsigned short int);
};


#endif // MEDIATOR_H
