#ifndef FILE_NPC_H
#define FILE_NPC_H

#include "shared.h"



#define NPC_FACE_LEFT 0
#define NPC_FACE_RIGHT 1

#define NPC_FRAME_NUMBER 50





struct file_npc {
	char name[50];
    struct hit_points hp;
	short int behavior_mode;              // defines how it behavies (kink of AI*)
	short int vision_reach;               // defines the distances it can see enemies
	short int walk_range;                 // defines how long from the start point it can go
	short int facing;                     // defines the side npc is facing before start moving (also used by LINEWALK behavior)
    struct coordinate start_point;
	char filename[50];						// graphic file used on it
	//int filesize;
	int frameset[NPC_FRAME_NUMBER];				// holds information about the type of each frame
	int frameset_time[NPC_FRAME_NUMBER];		// the number of milisseconds this frame leasts
	int framesize_w;
	int framesize_h;
	int can_shoot;
	int have_shield;
	unsigned short int is_boss;
	int IA;										// IA types: no_move, wait, attack, zig-zag (loop), side to side (origin to direction)
};

#endif // FILE_NPC_H
