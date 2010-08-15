#ifndef CONFIG_H
#define CONFIG_H

SDL_Surface *config_img=NULL, *dialog_bg=NULL;
short int menu_pos_x, menu_pos_y;


void showDialog(char face[255], char *lines) {
    char *temp_char;
    char temp_text[2];
    SDL_Surface *temp_img;
    char buffer_file[255];

    int text_x=0, text_y=0;

    if (dialog_bg == NULL) {
        createDialogBG();
    }

    sprintf(buffer_file, "%sdata/images/faces/%s", FILEPATH, face);
    temp_img = loadSpriteFile(buffer_file);
    SDL_SetColors(temp_img, colormap, 0, COLOR_COUNT);
    copy_area(temp_img, 0, 0, temp_img->w, temp_img->h, 8, 9, dialog_bg);

    temp_char = lines;
    // full-line = 27 character, x.ini=7
    // face-lines = 23 characters, x.ini=7+32
    while (*temp_char != '\0') {
            sprintf(temp_text, "%c", *temp_char);
			draw_text(text_x*9+43, text_y*11+9, temp_text, dialog_bg);
            copy_area(dialog_bg, 0, 0, dialog_bg->w, dialog_bg->h, (RES_W-dialog_bg->w)*0.5, 25, game_screen);
            SDL_Flip(game_screen);
            temp_char = temp_char+1;
            text_x++;
            if (*temp_char == '\n') {
                    text_x = 0;
                    text_y++;
                    temp_char = temp_char+1;
            }
			waitTime(5);
    }
    wait_player_key();
}


void setVideoMode(short int fullscreen) {
	SDL_Surface *temp_screen;

	// create a backup of the screen
		temp_screen = SDL_CreateRGBSurface(SDL_SWSURFACE , MAX_W, MAX_H, 8, 0, 0, 0, 0);
	SDL_SetColors(temp_screen, colormap, 0, COLOR_COUNT);
	copy_area(game_screen, 0, 0, MAX_W, MAX_H, 0, 0, temp_screen);
	#ifdef PLAYSTATION
		game_screen = SDL_SetVideoMode(RES_W, RES_H, 8, SDL_HWSURFACE|SDL_DOUBLEBUF);
	#else
		#ifdef NINTENDODS
			game_screen = SDL_SetVideoMode(RES_W, RES_H, 8, SDL_SWSURFACE|SDL_FULLSCREEN|SDL_HWPALETTE);
		#else
			if (fullscreen) {
				game_screen = SDL_SetVideoMode(RES_W, RES_H, 8, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN);
			} else {
				game_screen = SDL_SetVideoMode(RES_W, RES_H, 8, SDL_HWSURFACE|SDL_DOUBLEBUF);
			}
		#endif
	#endif
	// restore the screem backup
	copy_area(temp_screen, 0, 0, MAX_W, MAX_H, 0, 0, game_screen);
	SDL_FreeSurface(temp_screen);
}


void show_credits() {
	SDL_Surface *temp_screen;
	temp_screen = SDL_CreateRGBSurface(SDL_SWSURFACE , config_img->w-10, config_img->h+10, 8, 0, 0, 0, 0);
	SDL_SetColors(config_img, colormap, 0, COLOR_COUNT);
	draw_text(120+menu_pos_x, 10+menu_pos_y, "windowed", game_screen);
	SDL_FreeSurface(temp_screen);
}

void config_showMenu() {
    clean_input();
    char buffer_file[255];

	if (config_img == NULL) {
		sprintf(buffer_file, "%sdata/images/backgrounds/menu.png", FILEPATH);
		config_img = loadSpriteFile(buffer_file);
		SDL_SetColors(config_img, colormap, 0, COLOR_COUNT);
	}

	menu_pos_x = (RES_W-config_img->w)*0.5;
	menu_pos_y = (RES_H-config_img->h)*0.5;
    copy_area(config_img, 0, 0, config_img->w, config_img->h, menu_pos_x, menu_pos_y, game_screen);
}


void subMenu(int pos) {
	short int optionPicked=0, fim=0;

	clear_area(game_screen, 120+menu_pos_x, 20+menu_pos_y, 120, 120, 0, 0, 0);
	// sound
	if (pos == 0) {
		draw_text(120+menu_pos_x, 10+menu_pos_y, "enabled", game_screen);
		draw_text(120+menu_pos_x, 25+menu_pos_y, "disabled", game_screen);
	// video
#ifndef PLAYSTATION
	} else if (pos == 1) {
		draw_text(120+menu_pos_x, 10+menu_pos_y, "windowed", game_screen);
		draw_text(120+menu_pos_x, 25+menu_pos_y, "fullscreen", game_screen);
	} else if (pos == 2) {
		show_credits();
	}
#else
	//PS2 video
	} else if (pos == 2) {
		draw_text(120+menu_pos_x, 10+menu_pos_y, "filtered", game_screen);
		draw_text(120+menu_pos_x, 25+menu_pos_y, "no-filter", game_screen);
	}
#endif
	clean_input();
	waitTime(200);
	draw_text(110+menu_pos_x, (optionPicked*15)+10+menu_pos_y, ">", game_screen);

	while (!fim) {
		printf("subMenu LOOP\n");
		read_input(0);
		if (keyState[0][KEYY] == '2' || keyState[1][KEYY] == '2') {
			play_sfx(SFX_CURSOR);
			clear_area(game_screen, 110+menu_pos_x, (optionPicked*15)+10+menu_pos_y, 8, 10, 0, 0, 0);
			optionPicked--;
			if (optionPicked < 0) {
				optionPicked = 1;
			}
			draw_text(110+menu_pos_x, (optionPicked*15)+10+menu_pos_y, ">", game_screen);
			waitTime(300);
		} else if (keyState[0][KEYY] == '1' || keyState[1][KEYY] == '1') {
			play_sfx(SFX_CURSOR);
			clear_area(game_screen, 110+menu_pos_x, (optionPicked*15)+10+menu_pos_y, 8, 10, 0, 0, 0);
			optionPicked++;
			if (optionPicked > 1) {
				optionPicked = 0;
			}
			draw_text(110+menu_pos_x, (optionPicked*15)+10+menu_pos_y, ">", game_screen);
			waitTime(300);
		} else if (keyState[0][KEYSTART] == '1' || keyState[1][KEYSTART] == '1') {
			if (pos == 0) {
				if (optionPicked == 0) {
					if (game_config.sound_enabled == 0) {
						#ifndef NINTENDODS
							load_music("bgmusic.mod");
						#endif
					}
					game_config.sound_enabled = 1;
				} else {
					if (game_config.sound_enabled == 1) {
						stop_music();
					}
					game_config.sound_enabled = 0;
				}
			} else if (pos == 1) {
			#ifndef PLAYSTATION
				if (optionPicked == 0) {
					if (game_config.video_fullscreen == 1) {
						setVideoMode(0);
					}
					game_config.video_fullscreen = 0;
				} else {
					if (game_config.video_fullscreen == 0) {
						setVideoMode(1);
					}
					game_config.video_fullscreen = 1;
				}
			#endif
			}
			fim = 1;
		} else if (keyState[0][KEYQUIT] == '1' || keyState[1][KEYQUIT] == '1') {
			printf("subMenu quit\n");
			fim = 1;
		}
		clean_input();
		SDL_Flip(game_screen);
		waitTime(10);
	}
	clean_input();
	waitTime(300);
	clear_area(game_screen, 110+menu_pos_x, 10+menu_pos_y, 120, 120, 0, 0, 0);
	SDL_Flip(game_screen);

}

// sound -> enabled, disabled
// video -> full screen, windowed
// ps2 video -> filter 1, filter 2, no-filter
void config_showMainConfig() {
	short int optionPicked=0, fim=0;

	config_showMenu();
	game_config.sound_enabled=1;
	game_config.video_fullscreen=0;
	game_config.video_ps2_filter=0;

	draw_text(20+menu_pos_x, 10+menu_pos_y, "Sound", game_screen);
	draw_text(20+menu_pos_x, 25+menu_pos_y, "Video", game_screen);
	draw_text(20+menu_pos_x, 40+menu_pos_y, "Credits", game_screen);
	clean_input();
	waitTime(200);
	draw_text(10+menu_pos_x, (optionPicked*15)+10+menu_pos_y, ">", game_screen);

	while (!fim) {
		read_input(0);
		if (keyState[0][KEYY] == '2' || keyState[1][KEYY] == '2') {
			printf("config_showMainConfig -> UP\n");
			play_sfx(SFX_CURSOR);
			clear_area(game_screen, 10+menu_pos_x, (optionPicked*15)+10+menu_pos_y, 8, 10, 0, 0, 0);
			optionPicked--;
			if (optionPicked < 0) {
				optionPicked = 1;
			}
			draw_text(10+menu_pos_x, (optionPicked*15)+10+menu_pos_y, ">", game_screen);
			waitTime(300);
		} else if (keyState[0][KEYY] == '1' || keyState[1][KEYY] == '1') {
			printf("config_showMainConfig -> DOWN\n");
			play_sfx(SFX_CURSOR);
			clear_area(game_screen, 10+menu_pos_x, (optionPicked*15)+10+menu_pos_y, 8, 10, 0, 0, 0);
			optionPicked++;
			if (optionPicked > 1) {
				optionPicked = 0;
			}
			draw_text(10+menu_pos_x, (optionPicked*15)+10+menu_pos_y, ">", game_screen);
			waitTime(300);
		} else if (keyState[0][KEYSTART] == '1' || keyState[1][KEYSTART] == '1') {
			subMenu(optionPicked);
		} else if (keyState[0][KEYQUIT] == '1' || keyState[1][KEYQUIT] == '1') {
			printf("config_showMainConfig -> ESC\n");
			fim = 1;
		}
		clean_input();
		SDL_Flip(game_screen);
		waitTime(10);
	}
	clean_input();
	SDL_Flip(game_screen);
	waitTime(200);
}

void mainMenu() {
	SDL_Surface* screenCopy;
	short int optionPicked=0, fim=0;

	screenCopy = SDL_CreateRGBSurface(SDL_SWSURFACE , RES_W, RES_H, 8, 0, 255, 0, 0);
	SDL_SetColors(screenCopy, colormap, 0, COLOR_COUNT);
	copy_area(game_screen, 0, 0, RES_W, RES_H, 0, 0, screenCopy);
	draw_text(40-RES_DIFF_W-8, (MAX_H*0.5)-RES_DIFF_H+(optionPicked*12),">", game_screen);

	while (!fim) {
		read_input(0);
		if (keyState[0][KEYY] == '2' || keyState[1][KEYY] == '2') {
			play_sfx(SFX_CURSOR);
			clear_area(game_screen, 40-RES_DIFF_W-8, (MAX_H*0.5)-RES_DIFF_H+(optionPicked*12), 8, 10, 0, 0, 0);
			optionPicked--;
			if (optionPicked < 0) {
				optionPicked = 3;
			}
			draw_text(40-RES_DIFF_W-8, (MAX_H*0.5)-RES_DIFF_H+(optionPicked*12),">", game_screen);
			waitTime(300);
		} else if (keyState[0][KEYY] == '1' || keyState[1][KEYY] == '1') {
			play_sfx(SFX_CURSOR);
			clear_area(game_screen, 40-RES_DIFF_W-8, (MAX_H*0.5)-RES_DIFF_H+(optionPicked*12), 8, 10, 0, 0, 0);
			optionPicked++;
			if (optionPicked > 3) {
				optionPicked = 0;
			}
			draw_text(40-RES_DIFF_W-8, (MAX_H*0.5)-RES_DIFF_H+(optionPicked*12),">", game_screen);
			waitTime(300);
		} else if (keyState[0][KEYSTART] == '1' || keyState[1][KEYSTART] == '1') {
			if (optionPicked == 1) {
				config_showMainConfig();
				copy_area(screenCopy, 0, 0, RES_W, RES_H, 0, 0, game_screen);
				draw_text(40-RES_DIFF_W-8, (MAX_H*0.5)-RES_DIFF_H+(optionPicked*12),">", game_screen);
			} else if (optionPicked == 2) {
				showCredits();
				copy_area(screenCopy, 0, 0, RES_W, RES_H, 0, 0, game_screen);
				draw_text(40-RES_DIFF_W-8, (MAX_H*0.5)-RES_DIFF_H+(optionPicked*12),">", game_screen);
			} else if (optionPicked == 3) {
				leave_game();
			} else {
				fim = 1;
			}
		} else if (keyState[0][KEYQUIT] == '1' || keyState[1][KEYQUIT] == '1') {
			leave_game();
		}
		clean_input();
		SDL_Flip(game_screen);
		waitTime(10);
	}
	SDL_FreeSurface(screenCopy);
}

void draw_horizontal_hp_bar(short int y_adjust, short int right, short int hp, SDL_Surface *screen) {
	short int x, y, i;
	short int r, g, b;
	if (right != 1) {
		x = 33;
		r = 127;
		g = 11;
		b = 0;
	} else {
		x = 163;
		r = 255;
		g = 102;
		b = 0;
	}
	printf("-->> draw_horizontal_hp_bar - x: %d, y: %d, r: %d, g: %d, b: %d <<--\n", x, y_adjust, r, g, b);
	clear_area(screen, x, y_adjust, 63, 11, 0, 0, 0);
	clear_area(screen, x+1, 1+y_adjust, 61, 9, r, g, b);
	for (i=0; i<hp; i++) {
		y = ((28-i)*2+1);
		clear_area(screen, x+y+1, 3+y_adjust, 1, 5, 255, 255, 255);
	}
}


void openInGameMenu() {
	SDL_Surface *energy_img;

	clean_input();
	if (config_img != NULL) {
		SDL_FreeSurface(config_img);
		config_img = NULL;
	}

	config_showMenu();
	char buffer_file[255];
	sprintf(buffer_file, "%sdata/images/items.png", FILEPATH);
	energy_img = loadSpriteFile(buffer_file);
	SDL_SetColors(energy_img, colormap, 0, COLOR_COUNT);
	copy_area(energy_img, 0, 0, TILE_SIZE, TILE_SIZE, 10, MAX_H-78, config_img); // energy tnak
	copy_area(energy_img, 48, 0, TILE_SIZE, TILE_SIZE, 47, MAX_H-78, config_img); // weapons tank
	copy_area(energy_img, 16, 0, TILE_SIZE, TILE_SIZE, 82, MAX_H-78, config_img);  // player1 face
	if (game_config.two_players > 1) {
		copy_area(energy_img, 0, 0, TILE_SIZE, TILE_SIZE, 140, MAX_H-78, config_img); // energy tank
		copy_area(energy_img, 48, 0, TILE_SIZE, TILE_SIZE, 177, MAX_H-78, config_img); // weapons tank
		copy_area(energy_img, 32, 0, TILE_SIZE, TILE_SIZE, 212, MAX_H-78, config_img); // player2 face
	}
	SDL_FreeSurface(energy_img);
	waitTime(50);
	SDL_Flip(game_screen);
}

void inGameMenu() {
	char tempChr[10];
	short int fim=0;

	draw_text(10, 10, "ENERGY:", config_img);
	draw_text(10, 40, "WEAPONS:", config_img);
	draw_text(10, MAX_H-90, "ITEMS:", config_img);
	draw_text(10, 24, "P1:", config_img);
	sprintf(tempChr, "x%d", p1Obj->items.energy_tanks);
	draw_text(27, MAX_H-72, tempChr, config_img); // energy thank p1
	sprintf(tempChr, "x%d", p1Obj->items.weapon_tanks);
	draw_text(64, MAX_H-72, tempChr, config_img); // weapons tank p1
	sprintf(tempChr, "x%d", p1Obj->items.lifes);
	draw_text(100, MAX_H-72, tempChr, config_img); // lifes p1
	draw_horizontal_hp_bar(22, 0, p1Obj->HP, config_img);

	if (game_config.two_players > 1) {
		draw_text(140, 24, "P2:", config_img);
		sprintf(tempChr, "x%d", p2Obj->items.energy_tanks);
		draw_text(159, MAX_H-72, tempChr, config_img); // energy thank p1
		sprintf(tempChr, "x%d", p2Obj->items.weapon_tanks);
		draw_text(196, MAX_H-72, tempChr, config_img); // weapons tank p1
		sprintf(tempChr, "x%d", p2Obj->items.lifes);
		draw_text(230, MAX_H-72, tempChr, config_img); // lifes p2
                draw_horizontal_hp_bar(22, 1, p2Obj->HP, config_img);
	}

	copy_area(config_img, 0, 0, config_img->w, config_img->h, menu_pos_x, menu_pos_y, game_screen);
	SDL_Flip(game_screen);
	waitTime(500);

	while (!fim) {
		read_input(0);
		if (keyState[0][KEYJUMP] == '1' || keyState[1][KEYJUMP] == '1') {
			fim = 1;
		} else if (keyState[0][KEYSTART] == '1' || keyState[1][KEYSTART] == '1') {
			fim = 1;
		}
		clean_input();
		copy_area(config_img, 0, 0, config_img->w, config_img->h, menu_pos_x, menu_pos_y, game_screen);
		SDL_Flip(game_screen);
		waitTime(100);
	}
	printf("inGameMenu.fim\n");
	PAUSED = 0;
	clean_input();
	waitTime(250);
}

void createDialogBG() {
	SDL_Surface *temp_img;
	char buffer_file[255];

	sprintf(buffer_file, "%sdata/images/backgrounds/menu.png", FILEPATH);
	temp_img = loadSpriteFile(buffer_file);
	SDL_SetColors(temp_img, colormap, 0, COLOR_COUNT);
	dialog_bg = SDL_CreateRGBSurface(SDL_SWSURFACE , temp_img->w, 50, 8, 0, 0, 0, 0);
	SDL_SetColors(dialog_bg, colormap, 0, COLOR_COUNT);
	copy_area(temp_img, 0, 0, temp_img->w, 25, 0, 0, dialog_bg);
	copy_area(temp_img, 0, temp_img->h-25, temp_img->w, 25, 0, 25, dialog_bg);
	SDL_FreeSurface(temp_img);
}


void resetDialog() {
	clear_area(dialog_bg, 5, 5, dialog_bg->w-10, dialog_bg->h-10, 0, 0, 0);
}

void removeDialog() {

}

void showCredits() {
    config_showMenu();
    draw_text(40, 30, "Rockbot 0.1", game_screen);
    draw_text(40, 40, "Code Licensed under GPL v2", game_screen);
    draw_text(40, 50, "Images C. Commons Share Alike", game_screen);
    draw_text(40, 60, "Music under several licenses", game_screen);
    draw_text(40, 80, "Lead Game Developer:", game_screen);
    draw_text(42, 90, "Iuri Fiedoruk", game_screen);
    draw_text(40, 100, "Lead Design Developer:", game_screen);
    draw_text(42, 110, "Arismeire K. S. Fiedoruk", game_screen);
    draw_text(40, 120, "Helper Coders:", game_screen);
    draw_text(42, 130, "Demetrio Neto", game_screen);
    draw_text(40, 140, "Helper Artists:", game_screen);
	draw_text(42, 150, "Rodrigo Hahn, Akira Faganello", game_screen);
    clean_input();
    waitTime(300);
    while (!fim) {
        read_input(0);
        if (keyState[0][KEYJUMP] == '1' || keyState[1][KEYJUMP] == '1') {
                fim = 1;
        } else if (keyState[0][KEYSTART] == '1' || keyState[1][KEYSTART] == '1') {
                fim = 1;
        } else if (keyState[0][KEYQUIT] == '1' || keyState[1][KEYQUIT] == '1') {
                fim = 1;
        }
    }
    clean_input();
    waitTime(400);
}


void draw_lights_select_player(SDL_Surface* lights, int mode, int adjustX, int adjustY) {
	int posX, invPosX;

	posX = 6;
	invPosX = 0;

	//printf(">>draw_lights_select_player - game_config.selected_player: %d, adjustX: %d, adjustY: %d\n", game_config.selected_player, adjustX, adjustY);

	if (game_config.selected_player == 1) {
		// light for p1
		copy_area(lights, posX, 0, lights->h, lights->h, adjustX+2, adjustY+2, game_screen);
		copy_area(lights, posX, 0, lights->h, lights->h, adjustX+2, adjustY+88, game_screen);
		copy_area(lights, posX, 0, lights->h, lights->h, adjustX+248, adjustY+2, game_screen);
		copy_area(lights, posX, 0, lights->h, lights->h, adjustX+248, adjustY+88, game_screen);
		// black for p2
		copy_area(lights, invPosX, 0, lights->h, lights->h, adjustX+2, adjustY+98, game_screen);
		copy_area(lights, invPosX, 0, lights->h, lights->h, adjustX+2, adjustY+184, game_screen);
		copy_area(lights, invPosX, 0, lights->h, lights->h, adjustX+248, adjustY+98, game_screen);
		copy_area(lights, invPosX, 0, lights->h, lights->h, adjustX+248, adjustY+184, game_screen);
	} else {
		// light for p2
		copy_area(lights, posX, 0, lights->h, lights->h, adjustX+2, adjustY+98, game_screen);
		copy_area(lights, posX, 0, lights->h, lights->h, adjustX+2, adjustY+184, game_screen);
		copy_area(lights, posX, 0, lights->h, lights->h, adjustX+248, adjustY+98, game_screen);
		copy_area(lights, posX, 0, lights->h, lights->h, adjustX+248, adjustY+184, game_screen);
		// black for p1
		copy_area(lights, invPosX, 0, lights->h, lights->h, adjustX+2, adjustY+2, game_screen);
		copy_area(lights, invPosX, 0, lights->h, lights->h, adjustX+2, adjustY+88, game_screen);
		copy_area(lights, invPosX, 0, lights->h, lights->h, adjustX+248, adjustY+2, game_screen);
		copy_area(lights, invPosX, 0, lights->h, lights->h, adjustX+248, adjustY+88, game_screen);
	}

	SDL_Flip(game_screen);
}

void select_player() {
	SDL_Surface* tempImg;
	SDL_Surface* lights;
	char tempBuffer[255];
	int adjustX, adjustY;


	sprintf(tempBuffer, "%sdata/images/backgrounds/player_select.png", FILEPATH);
	tempImg = surfaceFromFile(tempBuffer);
	blank_screen(game_screen);
	adjustX = (RES_W-tempImg->w)*0.5;
	adjustY = (RES_H-tempImg->h)*0.5;
	copy_area(tempImg, 0, 0, tempImg->w, tempImg->h, adjustX, adjustY, game_screen);
	SDL_Flip(game_screen);

	sprintf(tempBuffer, "%sdata/images/backgrounds/lights.png", FILEPATH);
	lights = surfaceFromFile(tempBuffer);

	clean_input();
	waitTime(200);
	while (keyState[0][KEYSTART] != '1' && keyState[1][KEYSTART] != '1') {
		read_input(0);
		if (game_config.selected_player == 1 && (keyState[0][KEYY] == '1' || keyState[1][KEYY] == '1')) {
			printf(">> intro.h::select_player - cursor DOWN\n");
			play_sfx(SFX_CURSOR);
			game_config.selected_player = 2;
		} else if (game_config.selected_player == 2 && (keyState[0][KEYY] == '2' || keyState[1][KEYY] == '2')) {
			printf(">> intro.h::select_player - cursor UP\n");
			play_sfx(SFX_CURSOR);
			game_config.selected_player = 1;
		} else if (keyState[0][KEYQUIT] == '1' || keyState[1][KEYQUIT] == '1') {
			leave_game();
		}
		draw_lights_select_player(lights, 0, adjustX, adjustY);
	}
}


#endif // CONFIG_H


