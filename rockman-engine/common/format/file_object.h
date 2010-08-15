#ifndef FILE_OBJECT_H
#define FILE_OBJECT_H

#ifndef SDL_Surface
	#include "SDL/SDL.h"
#endif

struct struct_object {
	char name[20];
	char filename[50];						// graphic file used on it
	short int type;
	unsigned long int timer;				// used as time for disapearing block
	unsigned short int speed;				// used as speed for moving platform
	unsigned short int limit;				// used as range (pixels) for moving platform, visible time for disapearing block
	unsigned short int direction;			// used to check if moving away from oiginalpoint or moving to it
	unsigned short int distance;
	unsigned short int framesize_w;
	unsigned short int framesize_h;
	struct coordinate start_point;
	struct coordinate position;
	SDL_Surface *sprite;
	// TODO - adicionar colorcycle
};


#endif // FILE_OBJECT_H
