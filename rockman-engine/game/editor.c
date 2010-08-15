/***************************************************************************
                          main.c  -  description
                             -------------------
    begin                : Seg Set  1 20:03:07 BRT 2003
    copyright            : (C) 2003 by Iuri Fiedoruk
    email                : iuri.f@terra.com.br
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <SDL/SDL.h>		//Include do SDL
#include <SDL/SDL_image.h>	//Include da biblioteca SDL_Image
#include <SDL/SDL_mixer.h>	// Include da biblioteca SDL_Mixer
#include <stdio.h>			// Standard IO - Padrão ANSI-C
#include <stdlib.h>			// Standard Lib - Padrão ANSI-C
#include <string.h>			// Biblioteca string.h - para o uso da função stcmp.
#include "linconio.h"		// cores, getch, etc

SDL_Rect srcrect;

// includes que precisam das variáveis declaradas acima
#include <common.h>		// funções comuns ao jogo e ao editor
#include <editor.h>	    // funções de edição
//#include <game.h>		// funções do jogo





int main(int argc, char *argv[]) {
	// inicializa SDL
	if ( SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO) < 0 ) {
		fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
		exit(1);
	} else {
		printf("SDL Initialized!\n");
	}

	editor_init();
	// loop
	while (fim == 0) {
		//move_player();
		editor_loop();
		SDL_Delay(10);
	}

	fclose(fp_map);
	free(p_map);

	atexit(SDL_Quit);
	return EXIT_SUCCESS;
}
