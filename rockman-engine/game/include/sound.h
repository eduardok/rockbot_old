#ifndef SOUND_H
#define SOUND_H

/*
#ifdef PLAYSTATION
    #include "include/sound_ps2.h"
#else
*/
	#ifdef NINTENDODS
        #include "include/sound_nds.h"
    #endif
//#endif

//#ifndef PLAYSTATION
#ifndef NINTENDODS

#include <SDL/SDL_mixer.h>




void play_sfx(int sfx) {
	Mix_Chunk *sound;
	if (sfx == SFX_NPC_HIT) {
		sound = sfx_npc_hit;
	} else if (sfx == SFX_NPC_KILLED) {
		sound = sfx_npc_killed;
	} else if (sfx == SFX_PLAYER_HIT) {
		sound = sfx_player_hit;
	} else if (sfx == SFX_PLAYER_SHOT) {
		sound = sfx_player_shot;
	} else if (sfx == SFX_PLAYER_JUMP) {
		sound = sfx_player_jump;
	} else if (sfx == SFX_CURSOR) {
		sound = sfx_cursor;
	} else if (sfx == SFX_STAGE_SELECTED) {
		sound = sfx_stage_selected;
	}
	if (game_config.sound_enabled == 1) {
		Mix_PlayChannel(1, sound, 0);
	}
}


void load_all_sfx() {
	char buffer[255];

	sprintf(buffer, "%sdata/sfx/%s", FILEPATH, "player_shot.wav");
	sfx_player_shot = Mix_LoadWAV(buffer);
	sprintf(buffer, "%sdata/sfx/%s", FILEPATH, "player_jump.wav");
	sfx_player_jump = Mix_LoadWAV(buffer);
	if (!sfx_player_jump) {
			printf("\n<< ERROR: Unable to load WAV. Error: %s\n", Mix_GetError());
	}
	sprintf(buffer, "%sdata/sfx/%s", FILEPATH, "player_hit.wav");
	sfx_player_hit = Mix_LoadWAV(buffer);
	if (!sfx_player_hit) {
			printf("\n<< ERROR: Unable to load WAV. Error: %s\n", Mix_GetError());
	}
	sprintf(buffer, "%sdata/sfx/%s", FILEPATH, "npc_hit.wav");
	sfx_npc_hit = Mix_LoadWAV(buffer);
	if (!sfx_npc_hit) {
			printf("\n<< ERROR: Unable to load WAV. Error: %s\n", Mix_GetError());
	}
	sprintf(buffer, "%sdata/sfx/%s", FILEPATH, "npc_killed.wav");
	sfx_npc_killed = Mix_LoadWAV(buffer);
	if (!sfx_npc_killed) {
			printf("\n<< ERROR: Unable to load WAV. Error: %s\n", Mix_GetError());
	}
	sprintf(buffer, "%sdata/sfx/%s", FILEPATH, "cursor.wav");
	sfx_cursor = Mix_LoadWAV(buffer);
	if (!sfx_cursor) {
			printf("\n<< ERROR: Unable to load WAV. Error: %s\n", Mix_GetError());
	}
	sprintf(buffer, "%sdata/sfx/%s", FILEPATH, "stage_selected.wav");
	sfx_stage_selected = Mix_LoadWAV(buffer);
	if (!sfx_stage_selected) {
			printf("\n<< ERROR: Unable to load WAV. Error: %s\n", Mix_GetError());
	}
	//Mix_Volume(-1, MIX_MAX_VOLUME);
}


void load_sfx(char sfx_file[255], Mix_Chunk *sound) {
	char buffer[255];
	SDL_RWops *fileRW;

	sprintf(buffer, "%sdata/sfx/%s", FILEPATH, sfx_file);
	//printf(">>sound.h - loading '%s' sfx file...", buffer);
	fileRW = SDL_RWFromFile(buffer, "rb");
	if (!fileRW) {
		fprintf(stderr, "\n<< ERROR: Could not open '%s' file.\n", buffer);
	}
	sound = Mix_LoadWAV_RW(fileRW, 1);
	if (sound == NULL) {
		fprintf(stderr, "\n<< ERROR: Unable to load WAV. Error: %s\n", Mix_GetError());
	} else {
		printf("done!\n");
	}
}



void init_audio() {
        if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
                printf("Couldn't open audio: %s\n", SDL_GetError());
		exit(-1);
	}
}

void load_music(char *music_file) {
	char buffer[255];

	if (music != NULL) {
		Mix_HaltMusic();
		Mix_FreeMusic(music);
		music = NULL;
	}
	sprintf(buffer, "%sdata/music/%s", FILEPATH, music_file);
	//printf(">>sound.h::load_music - filepath: %s, music_file: %s, buffer: %s\n", FILEPATH, music_file, buffer);
	music=Mix_LoadMUS(buffer);
	if (!music) {
		printf("Mix_LoadMUS(\"%s\"): %s\n", music_file, Mix_GetError());
		exit(-1);
		// this might be a critical error...
	}
	// toca a música
	if (Mix_PlayMusic(music, -1) == -1) {
		printf("<<<<<<<<<<<<< Mix_PlayMusic: %s\n", Mix_GetError());
		// well, there's no music, but most games don't break without music...
		exit(-1);
	}
	Mix_VolumeMusic(50);
}




void stop_music() {
	if (music != NULL) {
		Mix_HaltMusic();
		Mix_FreeMusic(music);
		music = NULL;
	}
}

void close_audio() {
	Mix_FreeMusic(music);
	Mix_CloseAudio();
}

void sound_loop() {}

#endif
//#endif

#endif // SOUND_H


