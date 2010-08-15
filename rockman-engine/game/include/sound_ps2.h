#ifndef SOUND_PS2_H
#define SOUND_PS2_H


#include <stdio.h>
#include <string.h>

#include "sjpcm.h"
#include "cosmitoFileIO.h"
#include "mixer.h"
#include "mixer_thread.h"

extern unsigned char SJPCM[];
extern unsigned int size_SJPCM;




int ofs1;               // offset sample 1
int ofs2;
int sample1Size;
int sample2Size;
char* sample1;
char* sample2;

int m_mixer_playing;            // status : If == 0, mixer is not playing : currently not working
s32 main_thread_id;


void init_audio() {
	int ret;
	main_thread_id = GetThreadId();
	SifInitRpc(0);
	SifExecModuleBuffer(SJPCM, size_SJPCM, 0, NULL, &ret);
	printf(">> sound.h::init_audio - 1\n");
	SjPCM_Init(1);		// sync mode
	printf(">> sound.h::init_audio - SjPCM_Setvol ...\n");
	SjPCM_Setvol(0x3fff);
	ChangeThreadPriority(GetThreadId(), _MIXER_THREAD_PRIORITY);
	Mixer_Init();
}




struct struct_sample *load_sfx(char sfx_file[255]) {
	struct struct_sample *temp_sample;
	FILE *sound;

	temp_sample =  malloc(sizeof(struct struct_sample));

	sound = fopen(sfx_file, "rb");
	if (sound == NULL)
	{
		printf("LOAD_SFX - failed to open wav file '%s'\n", sfx_file);
	} else {
		printf("LOAD_SFX - Loaded file '%s' into memory\n", sfx_file);
	}
	temp_sample->sampleSize = GetFilesize(sound);
	temp_sample->sampleSize = temp_sample->sampleSize - 0x30;               // discard header lenght
	fseek(sound, 0x30, SEEK_SET);                         // discard header itself

	printf("LOAD_SFX - samplesize = %d\n", temp_sample->sampleSize);

	if (!(temp_sample->sample = malloc(temp_sample->sampleSize)))                   // TBD : padding
	{
		fclose(sound);
		printf("LOAD_SFX Error - Couldnt allocate buffer\n");
		SjPCM_Quit();
		return NULL;
	}

	if (!(fread(temp_sample->sample, 1, temp_sample->sampleSize, sound)))
	{
		fclose(sound);
		printf("LOAD_SFX - Error: Cannot read file\n");
		free(temp_sample->sample);
		SjPCM_Quit();
		return NULL;
	}
	fclose(sound);
	return temp_sample;
}

/*
void play_sfx(struct struct_sample *temp_sample) {
	if (game_config.sound_enabled == 1) {
		if (temp_sample != NULL) {
			PlaySample((sint16*)temp_sample->sample, temp_sample->sampleSize, 128, 0);
			//while(IsPlaying() > 0) {
				//RotateThreadReadyQueue(_MIXER_THREAD_PRIORITY);
			//}
		}
	}
}
*/

void play_sfx(int sfx) {
	struct struct_sample *sound;
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
		if (sound != NULL) {
			PlaySample((sint16*)sound->sample, sound->sampleSize, 128, 0);
			//while(IsPlaying() > 0) {
				//RotateThreadReadyQueue(_MIXER_THREAD_PRIORITY);
			//}
		}
	}
}


void load_all_sfx() {
	char buffer[255];

	sprintf(buffer, "%sdata/sfx/%s", FILEPATH, "player_shot.wav");
	sfx_player_shot=load_sfx(buffer);
	sprintf(buffer, "%sdata/sfx/%s", FILEPATH, "player_jump.wav");
	sfx_player_jump=load_sfx(buffer);
	sprintf(buffer, "%sdata/sfx/%s", FILEPATH, "player_hit.wav");
	sfx_player_hit=load_sfx(buffer);
	sprintf(buffer, "%sdata/sfx/%s", FILEPATH, "npc_hit.wav");
	sfx_npc_hit=load_sfx(buffer);
	sprintf(buffer, "%sdata/sfx/%s", FILEPATH, "npc_killed.wav");
	sfx_npc_killed=load_sfx(buffer);
	sprintf(buffer, "%sdata/sfx/%s", FILEPATH, "cursor.wav");
	sfx_cursor=load_sfx(buffer);
	sprintf(buffer, "%sdata/sfx/%s", FILEPATH, "cursor.wav");
	sfx_stage_selected=load_sfx(buffer);
}

void close_audio() {
	Mixer_Terminate();
	SjPCM_Setvol(0);
	SjPCM_Quit();
	free(sfx_player_hit->sample);
	free(sfx_player_hit);

	free(sfx_player_jump->sample);
	free(sfx_player_jump);

	free(sfx_player_shot->sample);
	free(sfx_player_shot);

	free(sfx_npc_hit->sample);
	free(sfx_npc_hit);

	free(sfx_npc_killed->sample);
	free(sfx_npc_killed);

	free(sfx_ui_cursor->sample);
	free(sfx_ui_cursor);

	free(BGMUSIC->sample);
	free(BGMUSIC);


}

void load_music(char *music_file) {
	/*
	char buffer[255];
	if (BGMUSIC==NULL) {
		sprintf(buffer, "%sdata/music/plunge_panther.wav", FILEPATH);
		BGMUSIC = load_sfx(buffer);
		play_sfx(BGMUSIC);
	}
	*/
}


void sound_loop() {
	RotateThreadReadyQueue(_MIXER_THREAD_PRIORITY);
	/*
	if (BGMUSIC!=NULL && IsPlaying() == 0) {
		play_sfx(BGMUSIC);
	}
	*/
}

void stop_music() { }

#endif // SOUND_PS2_H
