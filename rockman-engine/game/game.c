/***************************************************************************
                          main.c  -  description
                             -------------------
    begin                : Seg Set  1 20:03:07 BRT 2003
    copyright            : (C) 2003 by Iuri Fiedoruk
	email                : protoman@upperland.net
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

/*
todo:
- colocar opções/etc em arquivos .cfg
- fazer verificador de existência de arquivos
- fazer editor de telas dentro do jogo
- separar as coisas em units
- scrolling de tela
*/

//#define FILEPATH ""

/*
#ifdef PLAYSTATION
	//sprintf(FILEPATH, "%s", "mc0:ds/");
	sprintf(FILEPATH, "%s", "mc0:ds/");
#else
	#ifdef WIN32
		sprintf(FILEPATH, "%s", "");
	#else
		sprintf(FILEPATH, "%s", "./");
	#endif
#endif
*/


char FILEPATH[255];


#ifdef PLAYSTATION
	#include "ps2_modules.h"
	struct struct_sample {
		char *sample;
		int sampleSize;
	};
	struct struct_sample *sfx_player_hit, *sfx_player_jump, *sfx_player_shot, *sfx_npc_hit, *sfx_npc_killed, *sfx_ui_cursor, *BGMUSIC=NULL;
#endif


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>				// Standard IO - Padrão ANSI-C
#include <stdlib.h>				// Standard Lib - Padrão ANSI-C
#include <string.h>				// Biblioteca string.h - para o uso da função stcmp.

#include <SDL/SDL.h>				//Include da SDL
#include <SDL/SDL_image.h>		//Include da biblioteca SDL_Image
#include <SDL/SDL_mixer.h>	// Include da biblioteca SDL_Mixer
#include <SDL/SDL_ttf.h>		// Include da biblioteca SDL_ttf
#include <SDL/SDL_endian.h>
#include <SDL/SDL_mixer.h>


// contador para temporização de dialogo que evita repetição do teclado
int dialog_wait=0;
// indica se dialogo está ativo e qual o dialogo que está ativo
int dialog_active = 0;
SDL_Rect srcrect;
SDL_Event event;

SDL_Joystick *joystick1, *joystick2;
TTF_Font *font=NULL;
char *keyState[2];

Mix_Music *music = NULL;
//Mix_Chunk *music = NULL;
char *sample;
int sample_size;

#ifdef NINTENDODS
	#include <nds.h>
	#include <stdio.h>
	#include <nds/arm9/console.h>
	#include <nds/arm9/ndsmotion.h>
	#include <fat.h>
	#include <unistd.h>
	#include <malloc.h>
	#include <maxmod9.h>
	#include "soundbank.h"
	#include "soundbank_bin.h"


extern u8 __end__[];        // end of static code and data
extern u8 __eheap_end[];    // farthest point to which the heap will grow

u8* getHeapStart() {
   return __end__;
}
u8* getHeapEnd() {
   return (u8*)sbrk(0);
}
u8* getHeapLimit() {
   return __eheap_end;
}
int getMemUsed() {
   struct mallinfo mi = mallinfo();
   return mi.uordblks;
}
int getMemFree() {
   struct mallinfo mi = mallinfo();
   return mi.fordblks + (getHeapLimit() - getHeapEnd());
}


mm_sound_effect ndsSFX[MSL_BANKSIZE];
mm_sfxhand ndsSFXhandler[MSL_BANKSIZE];


#endif

SDL_Surface *game_screen;


// includes que precisam das variáveis declaradas acima
#include "include/types.h"
#include "include/sound.h"
#include "common.h"			// funções comuns ao jogo e ao editor
#include "projectiles.h"
#include "graphics.h"		// funções comuns ao jogo e ao editor
#include "object.h"
#include "game.h"			// funções do jogo
#include "include/config.h"
#include "intro.h"
#include "include/transfer.h"
#include "../common/dialogs.h"


int k;

int main(int argc, char *argv[]) {
	SDL_RWops *fileRW;

	game_config.sound_enabled = 1;


	sprintf(FILEPATH, "%s", "");

	#ifdef PLAYSTATION
		SifIopReset("rom0:UDNL rom0:EELOADCNF",0);
		while(!SifIopSync());
		fioExit();
		SifExitIopHeap();
		SifLoadFileExit();
		SifExitRpc();
		SifExitCmd();
		SifInitRpc(0);
		FlushCache(0);
		FlushCache(2);

		ee_thread_status_t main_thread_status;
		int main_id = GetThreadId();
		ReferThreadStatus(main_id, &main_thread_status);
		ChangeThreadPriority(main_id, 64);

		//SifResetIop();

		PS2loadMinimal();
		PS2loadUSB();
		if (!strncmp(argv[0], "cdfs", 4) || !strncmp(argv[0], "cdrom", 5)) {
			PS2loadCD();
			sprintf(FILEPATH, "%s", "cdfs:");
		}
		// USED FOR DEBUG
		//sprintf(FILEPATH, "%s", "mass:/ps2/rockbot/");
		//printf("DEBUG - path: %s\n", argv[0]);
	#else
		#ifndef WIN32
			#ifdef NINTENDODS
				sprintf(FILEPATH, "%s", "/Apps/Rockbot/");
			#else
				strncpy (FILEPATH, argv[0], strlen(argv[0])-7);
				printf("Linux: set FILEPATH: %s\n", FILEPATH);
			#endif
		#endif
	#endif

#ifdef NINTENDODS
	if (!fatInitDefault()) {
		iprintf("NDS: fatInitDefault failed.\n");
		while (1);
	}
	motion_init();
#endif


	keyState[0] = (char *)malloc(KEYNUMBER * sizeof(char));
	keyState[1] = (char *)malloc(KEYNUMBER * sizeof(char));
	char buffer [255];
#ifdef NINTENDODS
	StartTicks();
	if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
#else
	if ( SDL_Init(SDL_INIT_VIDEO|SDL_INIT_JOYSTICK|SDL_INIT_TIMER|SDL_INIT_AUDIO) < 0 ) {
#endif
		printf("SDL Error\n");
		printf("Unable to init SDL: %s\n", SDL_GetError());
	}

	TTF_Init();
	#ifdef WIN32
		sprintf(buffer, "%sdata/fonts/kongtext.ttf", FILEPATH);
	#else
		sprintf(buffer, "%sdata/fonts/kongtext.ttf", FILEPATH);
	#endif
	fileRW = SDL_RWFromFile(buffer, "rb");
	if (!fileRW) {
		printf("Error opening '%s' font\n", buffer);
		return 0;
	}
	font = TTF_OpenFontRW(fileRW, 1, 8);


	RES_DIFF_W = (MAX_W-RES_W)*0.5;
	RES_DIFF_H = (MAX_H-RES_H)*0.5;

	#ifdef PLAYSTATION
		game_screen = SDL_SetVideoMode(RES_W, RES_H, 8, SDL_HWSURFACE|SDL_DOUBLEBUF);
	#else
		#ifdef NINTENDODS
			game_screen = SDL_SetVideoMode(RES_W, RES_H, 8, SDL_SWSURFACE|SDL_FULLSCREEN|SDL_HWPALETTE);
		#else
			game_screen = SDL_SetVideoMode(RES_W, RES_H, 8, SDL_HWSURFACE|SDL_DOUBLEBUF);
			SDL_WM_SetCaption(PROJECT_NAME,"Icon Title");
		#endif
	#endif
	SDL_SetColors(game_screen, colormap, 0, COLOR_COUNT);


	init_audio();

	//printf("There are %d joysticks attached\n", SDL_NumJoysticks());
	SDL_JoystickEventState(SDL_ENABLE);
	joystick1 = SDL_JoystickOpen(0);
	if (joystick1) {
		printf("Opened Joystick 0\n");
	} else {
		printf("Couldn't open Joystick 1\n");
	}
	joystick2 = SDL_JoystickOpen(1);
	if (joystick2) {
		printf("Opened Joystick 1\n");
	} else {
		printf("Couldn't open Joystick 2\n");
	}
	atexit(SDL_Quit);
	SDL_ShowCursor( SDL_DISABLE );

	init_main_vars();
	load_all_sfx();

	struct coordinate picked_stage;
	picked_stage = intro_screen();
	// 0.0: apebot, 0.1: daisiebot, 0.2: seahorsebot
	// 1.0: mummy, 1.1: NONE (skull castle), 1.2: magebot
	// 2.0: dynamitebot, 2.1: spikebot, 2.2: technobot

	if (game_init(picked_stage) == 0) {
		#ifdef NINTENDODS
			sprintf(buffer, "game_init failed - free: %d", getMemFree());
		#else
			sprintf(buffer, "Game_init() failed");
		#endif
		show_error(CRITICAL, buffer);
		exit(-1);
	}

	SDL_Flip(game_screen);

    srcrect.y = 0;
    srcrect.w = 50;
    srcrect.h = 10;

#ifndef NINTENDODS
	SDL_EnableKeyRepeat(50, 50);
	load_music("bgmusic.mod");
#endif

	init_dialogs();
	drawMap3rdLevel(game_screen);
	showReadyAnimation();

	while (fim == 0) {

		exec_colorcycle(game_screen);
		update_sprites();
		sound_loop();
		SDL_Flip(game_screen);

		#ifdef PLAYSTATION
				RotateThreadReadyQueue(_MIXER_THREAD_PRIORITY);
		#endif
		/*
		#ifdef NINTENDODS
			sprintf(buffer, "freeMem: %d", getMemFree());
			draw_text(4, RES_H-20, buffer, game_screen);
		#endif
		*/
	}
	leave_game();


	return(0);
}
