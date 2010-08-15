struct coordinate pos;
#define INTRO_STARS_NUMBER 30
struct coordinate star_list[INTRO_STARS_NUMBER], small_star_list[INTRO_STARS_NUMBER];
int run_stars_animation=1;
int timer_intro;

void stop_music();


void restoreColorMap() {
    // restore the colormap
    change_colormap(offscreen, 61, 255, 0, 255);
    change_colormap(offscreen, 62, 55, 255, 0);
    change_colormap(offscreen, 63, 0, 255, 255);
    freeColorCycling();
}


void main_intro() {
	SDL_Surface *spriteCopy, *background;
	char buffer [255];
	blank_screen(game_screen);
	int cut=0;
	#ifndef NINTENDODS
		load_music("bgmusic.mod");
	#endif
	draw_text(MAX_W*0.5-85-RES_DIFF_W, MAX_H*0.5-15,"IN THE YEAR 20XX...", game_screen);


	cut = waitScapeTime(2000);
	if (cut) { restoreColorMap(); return; }

	change_colormap(game_screen, 0, 0, 0, 0);

	int color_pos =  SDL_MapRGB(game_screen->format, 55, 255, 0);;
	blank_screen(game_screen);
	sprintf(buffer, "%sdata/images/scenes/city_intro1.png", FILEPATH);
	background = loadSpriteFile(buffer);
	copy_area(background, 0, 0, background->w, background->h, 10-RES_DIFF_W, 10-RES_DIFF_H, game_screen);
	SDL_FreeSurface(background);
	change_colormap(game_screen, color_pos, 167, 0, 0);
	draw_text(20-RES_DIFF_W/2, 120,"TWO ROBOT HEROES PROTECT TOKYO.", game_screen);
	cut = waitScapeTime(2000);
	if (cut) { restoreColorMap(); return; }

	change_colormap(game_screen, color_pos, 120, 0, 0);
	draw_text(20-RES_DIFF_W/2, 135,"BUT KYOTO LIES IN THE FEAR OF", game_screen);
	cut = waitScapeTime(2000);
	if (cut) { restoreColorMap(); return; }

	change_colormap(game_screen, color_pos, 80, 0, 0);
	draw_text(20-RES_DIFF_W/2, 150,"THE AGE OF INTELIGENT MACHINES,", game_screen);

	cut = waitScapeTime(2000);
	if (cut) { restoreColorMap(); return; }
	change_colormap(game_screen, color_pos, 40, 0, 0);
	draw_text(20-RES_DIFF_W/2, 165,"WITH ONLY THE POLICE TO TRUST.", game_screen);
	cut = waitScapeTime(5000);
	if (cut) { restoreColorMap(); return; }

	change_colormap(game_screen, color_pos, 55, 255, 0);



	blank_screen(game_screen);
	sprintf(buffer, "%sdata/images/scenes/lab_intro1.png", FILEPATH);
	background = loadSpriteFile(buffer);
	SDL_SetColors(background, colormap, 0, COLOR_COUNT);
	copy_area(background, 0, 0, background->w, background->h, 10-RES_DIFF_W, 10, game_screen);
	sprintf(buffer, "%sdata/images/sprites/canotus.png", FILEPATH);

	printf(">> PS2 PASS 0.1\n");

	spriteCopy = loadSpriteFile(buffer);
	printf(">> PS2 PASS 0.2\n");
	SDL_Surface* spriteBG = SDL_CreateRGBSurface(SDL_SWSURFACE, 21, 24, 8, 0, 0, 0, 255);
	printf(">> PS2 PASS 0.3\n");
	//SDL_SetColors(spriteBG, colormap, 0, COLOR_COUNT);

	printf(">> PS2 PASS 0.4\n");
	//void copy_area(SDL_Surface *screen_source, int src_x, int src_y, int src_w, int src_h, int dest_x, int dest_y, SDL_Surface *screen_dest) {
	copy_area(game_screen, 0, 0, 20, 20, 0, 0, spriteBG);
	printf(">> PS2 PASS 0.4.1\n");
	copy_area(game_screen, 226, 82, 21, 24, 0, 0, spriteBG);
	printf(">> PS2 PASS 0.5\n");
	copy_area(spriteCopy, 0, 0, 21, 24, 226-RES_DIFF_W, 82, game_screen);
	printf(">> PS2 PASS 0.6\n");
	SDL_Flip(game_screen);
	printf(">> PS2 PASS 0.7\n");

	struct struct_colorcycle_list *cl_item;
	printf(">> PS2 PASS 0.8\n");
	//add colorcycling
	// first
	colorcycle_n = SDL_MapRGB(game_screen->format, 55, 255, 0);
	printf(">> PS2 PASS 0.9\n");
	cl_item = add_colorcycle_list(colorcycle_n);
	add_colorcycle(cl_item, 1300, 0, 151, 0); // verde
	add_colorcycle(cl_item, 1600, 219, 43, 0); // vermelho
	add_colorcycle(cl_item, 1400, 0, 0, 171); // azul
	// second
	colorcycle_n = SDL_MapRGB(game_screen->format, 255, 0, 255);
	cl_item = add_colorcycle_list(colorcycle_n);
	add_colorcycle(cl_item, 1800, 143, 0, 119); // roxo
	add_colorcycle(cl_item, 1200, 255, 102, 0); // laranja
	add_colorcycle(cl_item, 1600, 230, 255, 0); // amarelo
	// third
	colorcycle_n = SDL_MapRGB(game_screen->format, 0, 255, 255);
	cl_item = add_colorcycle_list(colorcycle_n);
	add_colorcycle(cl_item, 1200, 255, 219, 171); // bege
	add_colorcycle(cl_item, 1600, 255, 155, 59); // laranja
	add_colorcycle(cl_item, 1800, 219, 43, 0); // marrom

	printf(">>PS2.PASS 7\n");

	draw_text(20-RES_DIFF_W/2, 120,"YOUNG SCIENTIST CALLED CANOTUS,", game_screen);
	cut = waitScapeTime(2000);
	if (cut) { restoreColorMap(); return; }
	draw_text(20-RES_DIFF_W/2, 135,"TIRED OF WAIT FOR THE PEACE,", game_screen);
	cut = waitScapeTime(2000);
	if (cut) { restoreColorMap(); return; }
	draw_text(20-RES_DIFF_W/2, 150,"INSPIRATED IN THE TOKYO ONES,", game_screen);
	cut = waitScapeTime(2000);
	if (cut) { restoreColorMap(); return; }

	//copy_area(spriteBG, 0, 0, 21, spriteCopy->h, 226-RES_DIFF_W, 82, game_screen);
	//SDL_FreeSurface(spriteBG);
	copy_area(spriteCopy, 43, 0, 21, spriteCopy->h, 226-RES_DIFF_W, 82, game_screen);
	SDL_FreeSurface(background);
	SDL_FreeSurface(spriteCopy);
	SDL_SetColors(game_screen, colormap, 0, COLOR_COUNT);

	draw_text(20-RES_DIFF_W/2, 165,"DECIDED TO CREATE", game_screen);
	cut = waitScapeTime(2000);
	if (cut) { restoreColorMap(); return; }
	draw_text(20-RES_DIFF_W/2, 180,"TWO NEW HEROES TO HELP OUT!", game_screen);
	cut = waitScapeTime(2000);
	if (cut) { restoreColorMap(); return; }
	blank_area(game_screen, 0, 120, MAX_W, 100);

	sprintf(buffer, "%sdata/images/sprites/sprites_p2.png", FILEPATH);
	spriteCopy = loadSpriteFile(buffer);
	copy_area(spriteCopy, 88, 9, 19,24, 158-RES_DIFF_W, 83, game_screen);
	SDL_FreeSurface(spriteCopy);


	draw_text(20-RES_DIFF_W/2, 120,"WHEN A HORDE OF ROBOT VILAINS", game_screen);
	cut = waitScapeTime(2000);
	if (cut) { restoreColorMap(); return; }

	draw_text(20-RES_DIFF_W/2, 135,"ATTACKS THE CITY, ", game_screen);
	cut = waitScapeTime(2000);
	if (cut) { restoreColorMap(); return; }

	sprintf(buffer, "%sdata/images/sprites/sprites_p1.png", FILEPATH);
	spriteCopy = loadSpriteFile(buffer);
	copy_area(spriteCopy, 88, 9, 19, 24, 34-RES_DIFF_W, 83, game_screen);
	SDL_FreeSurface(spriteCopy);

	draw_text(20-RES_DIFF_W/2, 150,"A FIRST OPPORTUNITY ARISES,", game_screen);
	cut = waitScapeTime(1000);
	if (cut) { restoreColorMap(); return; }
	draw_text(20-RES_DIFF_W/2, 165,"FOR ROCKBOT AND BETABOT", game_screen);
	cut = waitScapeTime(1000);
	if (cut) { restoreColorMap(); return; }
	draw_text(20-RES_DIFF_W/2, 180,"TO FIGHT FOR JUSTICE!", game_screen);
	cut = waitScapeTime(2000);

	restoreColorMap();
}

void select_player_number() {
	if (game_config.two_players == 1) {
		draw_text(23, MAX_H*0.5,">", game_screen);
	} else if (game_config.two_players == 2) {
		draw_text(23, (MAX_H*0.5)+13,">", game_screen);
	}
	clean_input();
	waitTime(200);
	while (keyState[0][KEYSTART] != '1' && keyState[1][KEYSTART] != '1') {
		read_input(0);
		if (game_config.two_players == 1 && (keyState[0][KEYY] == '1' || keyState[1][KEYY] == '1')) {
			printf(">> intro.h::select_player_number - cursor DOWN\n");

			play_sfx(SFX_CURSOR);

			clear_area(game_screen, 23, MAX_H*0.5, 8, 10, 0, 0, 0);
			draw_text(23, (MAX_H*0.5)+13,">", game_screen);
			game_config.two_players = 2;
		} else if (game_config.two_players == 2 && (keyState[0][KEYY] == '2' || keyState[1][KEYY] == '2')) {
			printf(">> intro.h::select_player_number - cursor UP\n");
			play_sfx(SFX_CURSOR);
			clear_area(game_screen, 23, (MAX_H*0.5)+13, 8, 10, 0, 0, 0);
			draw_text(23, MAX_H*0.5,">", game_screen);
			game_config.two_players = 1;
		} else if (keyState[0][KEYQUIT] == '1' || keyState[1][KEYQUIT] == '1') {
			leave_game();
		}
	}
}


void select_load_game() {
	int option = 1;
	clean_input();
	waitTime(200);
	clear_area(game_screen, 30, MAX_H*0.5, 100, 46, 0, 0, 0);
	draw_text(30-RES_DIFF_W, (MAX_H*0.5)-RES_DIFF_H,"NEW GAME", game_screen);
	draw_text(30-RES_DIFF_W, (MAX_H*0.5)+13-RES_DIFF_H,"LOAD GAME", game_screen);
	draw_text(23, MAX_H*0.5,">", game_screen);

	while (keyState[0][KEYSTART] != '1' && keyState[1][KEYSTART] != '1') {
		read_input(0);
		if (option == 1 && (keyState[0][KEYY] == '1' || keyState[1][KEYY] == '1')) {
			play_sfx(SFX_CURSOR);
			clear_area(game_screen, 23, MAX_H*0.5, 8, 10, 0, 0, 0);
			draw_text(23, (MAX_H*0.5)+13,">", game_screen);
			option = 2;
		} else if (option == 2 && (keyState[0][KEYY] == '2' || keyState[1][KEYY] == '2')) {
			play_sfx(SFX_CURSOR);
			clear_area(game_screen, 23, (MAX_H*0.5)+13, 8, 10, 0, 0, 0);
			draw_text(23, MAX_H*0.5,">", game_screen);
			option = 1;
		} else if (keyState[0][KEYQUIT] == '1' || keyState[1][KEYQUIT] == '1') {
			leave_game();
		}
	}

	if (option == 2) {
		FILE* fp;
		char tempBuffer[150];
		sprintf(tempBuffer, "%sdata/001.sav", FILEPATH);
		fp = fopen(tempBuffer, "rb");
		if (fp) {
			fread (&save_001, sizeof(struct st_save), 1, fp);
			fclose(fp);
		} else {
			printf("DEBUG - error loading from file '%s'\n", tempBuffer);
		}
	}
}


void move_highlight(int x_inc, int y_inc, SDL_Surface *s_light, SDL_Surface *s_dark, struct coordinate *highlight_pos) {
	copy_area(s_dark, 0, 0, s_dark->w, s_dark->h, highlight_pos->x, highlight_pos->y, game_screen);
	highlight_pos->x += x_inc;
	highlight_pos->y += y_inc;
	copy_area(s_light, 0, 0, s_light->w, s_light->h, highlight_pos->x, highlight_pos->y, game_screen);
	SDL_Flip(game_screen);
}




void place_face(char filename[50], char botname[20], short int posx, short int posy) {
    // TODO - calculate the text position according to it's strlen
    int txtPosX, txtPosY;
    SDL_Surface *spriteCopy;
    char buffer [255];

    sprintf(buffer, "%sdata/images/faces/%s", FILEPATH, filename);
    spriteCopy = loadSpriteFile(buffer);
    copy_area(spriteCopy, 0, 0, spriteCopy->w, spriteCopy->h, posx*80+63-RES_DIFF_W, posy*60+26-RES_DIFF_H, game_screen);
    free(spriteCopy);
    txtPosX = posx*80+76-RES_DIFF_W-(strlen(botname)*7)*0.5;
    txtPosY = posy*60+66-RES_DIFF_H;
    draw_text(txtPosX, txtPosY, botname, game_screen);
}


int animate_highlight(SDL_Surface *white, SDL_Surface *current) {
    if (getTimer() > timer_intro) {
        timer_intro = getTimer()+200;
        if (current == white) {
            return 1;
        } else {
            return 0;
        }
    } else {
        if (current == white) {
            return 0;
        } else {
            return 1;
        }
    }
}

void draw_eyes(int x, int y, SDL_Surface *eyes) {
    int posX, posY;
    if (x == 1) {
        posX = 11;
    } else if (x == 0) {
        posX = 9;
    } else {
        posX = 13;
    }
    if (y == 1) {
		posY = 18;
    } else if (y == 0) {
		posY = 16;
    } else {
		posY = 20;
    }
	if (game_config.selected_player == 2) {
		posY -= 3;
	}
    posX = posX+80+63-RES_DIFF_W;
    posY = posY+60+26-RES_DIFF_H;
    copy_area(eyes, 0, 0, eyes->w, eyes->h, posX, posY, game_screen);
}

struct coordinate stage_select() {
	char buffer [255];
	SDL_Surface *spriteCopy, *s_light=NULL, *s_dark, *eyes_surface, *eyes_bg, *light_mode;
	struct coordinate spacing, highlight_pos;
	int selection_end=0;
	clean_input();
	waitTime(300);

	pos.x = 1;
	pos.y = 1;
	spacing.x = 80;
	spacing.y = 60;
	highlight_pos.x = 135-RES_DIFF_W;
	highlight_pos.y = 78-RES_DIFF_H;
	blank_screen(game_screen);
	light_mode = s_light;


	sprintf(buffer, "%sdata/images/backgrounds/stage_select.png", FILEPATH);
	spriteCopy = loadSpriteFile(buffer);
	copy_area(spriteCopy, 0, 0, MAX_W, spriteCopy->w, -RES_DIFF_W, -RES_DIFF_H, game_screen);


	if (save_001.stages[0] == 0) {
		place_face("apebot.png", "APE", 0, 0);
	}
	if (save_001.stages[1] == 0) {
		place_face("daisiebot.png", "DAISIE", 1, 0);
	}
	if (save_001.stages[2] == 0) {
		place_face("seahorsebot.png", "SEAHORSE", 2, 0);
	}
	if (save_001.stages[3] == 0) {
		place_face("mummybot.png", "MUMMY", 0, 1);
	}
	if (save_001.stages[5] == 0) {
		place_face("magebot.png", "MAGE", 2, 1);
	}
	if (save_001.stages[6] == 0) {
		place_face("dynamitebot.png", "DYNAMITE", 0, 2);
	}
	if (save_001.stages[7] == 0) {
		place_face("spikebot.png", "SPIKE", 1, 2);
	}
	if (save_001.stages[8] == 0) {
		place_face("technobot.png", "TECHNO", 2, 2);
	}

	if (game_config.selected_player == 1) {
		place_face("rockbot_no_eyes.png", "", 1, 1);
	} else {
		place_face("betabot_no_eyes.png", "", 1, 1);
	}
	sprintf(buffer, "%sdata/images/backgrounds/stage_select_highlighted.png", FILEPATH);
	s_light = loadSpriteFile(buffer);
	sprintf(buffer, "%sdata/images/backgrounds/stage_select_darkned.png", FILEPATH);
	s_dark = loadSpriteFile(buffer);
	light_mode = s_light;

	if (game_config.selected_player == 1) {
		sprintf(buffer, "%sdata/images/faces/rockbot_eyes.png", FILEPATH);
	} else {
		sprintf(buffer, "%sdata/images/faces/betabot_eyes.png", FILEPATH);
	}
	eyes_surface = loadSpriteFile(buffer);
	eyes_bg = SDL_CreateRGBSurface(SDL_SWSURFACE , 32, 32, 8, 0, 0, 0, 0);
	SDL_SetColors(eyes_bg, colormap, 0, COLOR_COUNT);
	copy_area(game_screen, (80+63-RES_DIFF_W), (60+26-RES_DIFF_H), 32, 32, 0, 0, eyes_bg);

	copy_area(s_light, 0, 0, s_light->w, s_light->h, highlight_pos.x, highlight_pos.y, game_screen);
	SDL_Flip(game_screen);
	draw_text(MAX_W*0.5-45-RES_DIFF_W, 5-RES_DIFF_H,"PRESS START", game_screen);

	clean_input();
	draw_eyes(pos.x, pos.y, eyes_surface);
	waitTime(200);

	while (selection_end == 0) {
		read_input(0);
		//printf(">> intro.h::stage_select - pos.x: %d, pos.y: %d\n", pos.x, pos.y);
		//printf(">> intro.h::stage_select - keyState[0][KEYSTART]: %c,  keyState[1][KEYSTART]: %c\n", keyState[0][KEYSTART], keyState[1][KEYSTART]);
		if (pos.y < 2 && (keyState[0][KEYY] == '1' || keyState[1][KEYY] == '1')) {
					copy_area(eyes_bg, 0, 0, 32, 32, 80+63-RES_DIFF_W, 60+26-RES_DIFF_H, game_screen);
					pos.y++;
					draw_eyes(pos.x, pos.y, eyes_surface);
					play_sfx(SFX_CURSOR);
					move_highlight(0, spacing.y, s_light, s_dark, &highlight_pos);
					waitTime(200);
					clean_input();
		} else if (pos.y > 0 && (keyState[0][KEYY] == '2' || keyState[1][KEYY] == '2')) {
					copy_area(eyes_bg, 0, 0, 32, 32, 80+63-RES_DIFF_W, 60+26-RES_DIFF_H, game_screen);
					pos.y--;
					draw_eyes(pos.x, pos.y, eyes_surface);
					play_sfx(SFX_CURSOR);
					move_highlight(0, -spacing.y, s_light, s_dark, &highlight_pos);
					waitTime(200);
					clean_input();
		} else if (pos.x > 0 && (keyState[0][KEYX] == '2' || keyState[1][KEYX] == '2')) {
					copy_area(eyes_bg, 0, 0, 32, 32, 80+63-RES_DIFF_W, 60+26-RES_DIFF_H, game_screen);
					pos.x--;
					draw_eyes(pos.x, pos.y, eyes_surface);
					play_sfx(SFX_CURSOR);
					move_highlight(-spacing.x, 0, s_light, s_dark, &highlight_pos);
					waitTime(200);
					clean_input();
		} else if (pos.x < 2 && (keyState[0][KEYX] == '1' || keyState[1][KEYX] == '1')) {
					copy_area(eyes_bg, 0, 0, 32, 32, 80+63-RES_DIFF_W, 60+26-RES_DIFF_H, game_screen);
					pos.x++;
					draw_eyes(pos.x, pos.y, eyes_surface);
					play_sfx(SFX_CURSOR);
					move_highlight(spacing.x, 0, s_light, s_dark, &highlight_pos);
					waitTime(200);
					clean_input();
		} else if (keyState[0][KEYQUIT] == '1' || keyState[1][KEYQUIT] == '1') {
			leave_game();
		} else if ((keyState[0][KEYSTART] == '1' || keyState[1][KEYSTART] == '1') && (pos.x != 1 || pos.y != 1)) {
			selection_end = 1;
		}
		if (animate_highlight(s_light, light_mode) == 0) {
			light_mode = s_light;
		} else {
			light_mode = s_dark;
		}
		move_highlight(0, 0, light_mode, s_dark, &highlight_pos);
	}
	SDL_FreeSurface(s_light);
	SDL_FreeSurface(s_dark);
	SDL_FreeSurface(eyes_surface);
	SDL_FreeSurface(eyes_bg);
	light_mode = NULL;
	// do fade
	stop_music();
	play_sfx(SFX_STAGE_SELECTED);
	blink_screen(255, 255, 255);
	SDL_FreeSurface(spriteCopy);
	printf(">> stage_select - pos;x: %d, pos.y: %d\n", pos.x, pos.y);
	return pos;
}

void drawStar(short int x, short int y, short int size) {
	dest.x = x;
	dest.y = y;
	dest.w = size;
	dest.h = size;
	if (size >= 3) {
                SDL_FillRect(game_screen, &dest, SDL_MapRGB(game_screen->format, 160, 160, 160));
	} else {
                SDL_FillRect(game_screen, &dest, SDL_MapRGB(game_screen->format, 250, 250, 250));
	}
}

void eraseStar(short int x, short int y, short int size) {
	dest.x = x;
	dest.y = y;
	dest.w = size;
	dest.h = size;
	SDL_FillRect(game_screen, &dest, SDL_MapRGB(game_screen->format, 0, 0, 0));
}


// random a position for each star
void initStars() {
	int i;
	for (i=0; i<INTRO_STARS_NUMBER; i++) {
		star_list[i].x = rand() % 320;
		if (i % 2 == 0) {
			star_list[i].y = rand() % 46;
		} else {
			star_list[i].y = rand() % 53 + 145;
		}
	}
	for (i=0; i<INTRO_STARS_NUMBER; i++) {
		small_star_list[i].x = rand() % 320;
		if (i % 2 == 0) {
			small_star_list[i].y = rand() % 46;
		} else {
			small_star_list[i].y = rand() % 53 + 145;
		}
	}
}



void waitTimeWithStars(int wait_period) {
	int now_time=0;
	now_time = getTimer();
	wait_period = now_time + wait_period;
	while (now_time < wait_period) {
		now_time = getTimer();
		#ifndef NINTENDODS
			waitTime(1);
		#endif
		animStars();
	}
}


void animStars() {
	int i;
	//printf(">> animStars - LOOP\n");
	for (i=0; i<INTRO_STARS_NUMBER; i++) {
		eraseStar(star_list[i].x, star_list[i].y, 2);
		eraseStar(small_star_list[i].x, small_star_list[i].y, 3);
		star_list[i].x -= ANIM_STARS_STEP;
		if (star_list[i].x <= 0) {
			star_list[i].x = 320+ANIM_STARS_STEP;
			if (i % 2 == 0) {
				star_list[i].y = rand() % 46;
			} else {
				star_list[i].y = rand() % 53 + 145;
			}
		}
		small_star_list[i].x -= ANIM_STARS_SMALL_STEP;
		if (small_star_list[i].x <= 0) {
			small_star_list[i].x = 320+ANIM_STARS_SMALL_STEP;
			if (i % 2 == 0) {
				small_star_list[i].y = rand() % 46;
			} else {
				small_star_list[i].y = rand() % 53 + 145;
			}
		}
	}
	for (i=0; i<INTRO_STARS_NUMBER; i++) {
		drawStar(star_list[i].x, star_list[i].y, 2);
		drawStar(small_star_list[i].x, small_star_list[i].y, 3);
	}
	SDL_Flip(game_screen);
	#ifndef NINTENDODS
		waitTime(10);
	#endif
}

void boss_intro(struct coordinate pos) {
	char buffer [255], letter[2], botname[50];
	SDL_Surface *spriteCopy, *boss_bg, *bgCopy;
	struct coordinate boss_pos, sprite_size;
	int intro_frames_n = 1, intro_frames_rollback=0;
	boss_pos.x = 20;
	boss_pos.y = -37;
	int text_x = MAX_W*0.5 - 60;
	int i;

	blank_screen(game_screen);
	sprintf(buffer, "%sdata/images/backgrounds/stage_boss_intro.png", FILEPATH);
	spriteCopy = loadSpriteFile(buffer);
	copy_area(spriteCopy, 0, 0, spriteCopy->w, spriteCopy->h, 0, 0, game_screen);
	SDL_FreeSurface(spriteCopy);

	bgCopy = SDL_CreateRGBSurface(SDL_SWSURFACE , MAX_W, MAX_H, 8, 0, 0, 0, 0);
	SDL_SetColors(bgCopy, colormap, 0, COLOR_COUNT);
	copy_area(game_screen, 0, 0, game_screen->w, game_screen->h, 0, 0, bgCopy);
	SDL_Flip(game_screen);



	if (pos.x == 0 && pos.y == 1) {
		sprintf(buffer, "%sdata/images/sprites/spikebot.png", FILEPATH);
		sprite_size.x = 35;
		sprite_size.y = 39;
		intro_frames_n = 4;
		sprintf(botname, "SPIKE BOT");
	} else if (pos.x == 1 && pos.y == 0) {
		sprintf(buffer, "%sdata/images/sprites/daisiebot.png", FILEPATH);
		sprite_size.x = 34;
		sprite_size.y = 37;
		intro_frames_n = 3;
		sprintf(botname, "DAISIE BOT");
	} else if (pos.x == 0 && pos.y == 2) {
		sprintf(buffer, "%sdata/images/sprites/dynamitebot.png", FILEPATH);
		sprite_size.x = 44;
		sprite_size.y = 40;
		intro_frames_n = 3;
		intro_frames_rollback = 1;
		sprintf(botname, "DYNAMITE BOT");
	} else if (pos.x == 2 && pos.y == 2) {
		sprintf(buffer, "%sdata/images/sprites/enemies/technobot.png", FILEPATH);
		sprite_size.x = 37;
		sprite_size.y = 34;
		intro_frames_n = 3;
		sprintf(botname, "TECHNO BOT");
		intro_frames_rollback = 1;
	} else if (pos.x == 2 && pos.y == 0) {
		sprintf(buffer, "%sdata/images/sprites/mummybot.png", FILEPATH);
		sprite_size.x = 30;
		sprite_size.y = 36;
		intro_frames_n = 2;
		sprintf(botname, "MUMMY BOT");
	} else {
		sprintf(buffer, "%sdata/images/sprites/apebot.png", FILEPATH);
		sprite_size.x = 40;
                sprite_size.y = 32;
		intro_frames_n = 5;
		sprintf(botname, "APE BOT");
	}

	spriteCopy = loadSpriteFile(buffer);
	boss_bg = SDL_CreateRGBSurface(SDL_SWSURFACE , sprite_size.x, sprite_size.y, 8, 0, 0, 0, 0);
	SDL_SetColors(boss_bg, colormap, 0, COLOR_COUNT);
	copy_area(bgCopy, boss_pos.x, 80, sprite_size.x, sprite_size.y, 0, 0, boss_bg);


	initStars();

	while (boss_pos.y < 88) {
		copy_area(boss_bg, 0, 0, sprite_size.x, sprite_size.y, boss_pos.x, boss_pos.y, game_screen);
		boss_pos.y += 2;
		copy_area(bgCopy, boss_pos.x, boss_pos.y, sprite_size.x, sprite_size.y, 0, 0, boss_bg);
		copy_area(spriteCopy, 0, 0, sprite_size.x, sprite_size.y, boss_pos.x, boss_pos.y, game_screen);
		SDL_Flip(game_screen);
		waitTimeWithStars(20);
	}
	waitTimeWithStars(500);
	if (intro_frames_n > 1) {
		for (i=0; i<intro_frames_n; i++) {
			copy_area(boss_bg, 0, 0, spriteCopy->w, spriteCopy->h, boss_pos.x, boss_pos.y, game_screen);
			copy_area(spriteCopy, i*sprite_size.x, 0, sprite_size.x, sprite_size.y, boss_pos.x, boss_pos.y, game_screen);
			waitTimeWithStars(150);
		}
		if (intro_frames_rollback == 1) {
			for (i=intro_frames_n-1; i>=0; i--) {
				copy_area(boss_bg, 0, 0, spriteCopy->w, spriteCopy->h, boss_pos.x, boss_pos.y, game_screen);
				copy_area(spriteCopy, i*sprite_size.x, 0, sprite_size.x, sprite_size.y, boss_pos.x, boss_pos.y, game_screen);
				waitTimeWithStars(150);
			}
		}
	}
	for (i=0; i<strlen(botname); i++) {
		sprintf(letter, "%c", botname[i]);
		waitTimeWithStars(100);
		draw_text(text_x, 118, letter, game_screen);
		text_x += 8;
	}
	waitTimeWithStars(2000);
	//Mix_FreeChunk(sfx_boss_intro);
	SDL_FreeSurface(bgCopy);
	SDL_FreeSurface(boss_bg);
	SDL_FreeSurface(spriteCopy);
	run_stars_animation=0;
}




void intro_presents() {
    SDL_Surface *tempImg;
    char tempBuffer[255];

	clear_area(game_screen, 0, 0, RES_W, RES_H, 0, 0, 0);
	SDL_Flip(game_screen);

	sprintf(tempBuffer, "%sdata/images/presents.png", FILEPATH);

	tempImg = surfaceFromFile(tempBuffer);

	SDL_SetColors(tempImg, colormap, 0, COLOR_COUNT);
	copy_area(tempImg, 0, 0, tempImg->w, tempImg->h, RES_W*0.5-tempImg->w*0.5, RES_H*0.5-tempImg->h*0.5, game_screen);
	SDL_Flip(game_screen);
	SDL_FreeSurface(tempImg);
	SDL_Flip(game_screen);
	waitScapeTime(1600);


	blank_screen(game_screen);
}


// mostra tela de introdução, até alguém apertar start/enter
// a partir daí, mostra tela de seleção de personagem
struct coordinate intro_screen() {
	char buffer [255];
	SDL_Surface *spriteCopy;

	waitTime(100);
	intro_presents();

	waitTime(100);
	main_intro();

	clean_input();
	waitTime(200);
	clean_input();

	blank_screen(game_screen);

	// PARTE 1 - TITLE SCREEN
	sprintf(buffer, "%sdata/images/logo.png", FILEPATH);
	spriteCopy = loadSpriteFile(buffer);

	copy_area(spriteCopy, 0, 0, MAX_W, spriteCopy->w, -RES_DIFF_W, -RES_DIFF_H, game_screen);

	SDL_FreeSurface(spriteCopy);

	draw_text(8, 50,"KYOTO EVOLUTION!!", game_screen);

	draw_text(40-RES_DIFF_W, (MAX_H*0.5)-RES_DIFF_H,"Game Start", game_screen);
	draw_text(40-RES_DIFF_W, (MAX_H*0.5+12)-RES_DIFF_H,"Options", game_screen);
	draw_text(40-RES_DIFF_W, (MAX_H*0.5+24)-RES_DIFF_H,"Credits", game_screen);
	draw_text(40-RES_DIFF_W, (MAX_H*0.5+36)-RES_DIFF_H,"Quit", game_screen);

	draw_text(40-RES_DIFF_W, (RES_H-30),"(C) 2009/2010 UPPERLAND STUDIO", game_screen);
	draw_text(40-RES_DIFF_W, (RES_H-20),"DESIGN GREENNEKO WEB&DESIGN", game_screen);
	draw_text(40-RES_DIFF_W, (RES_H-10),"AND OTHERS", game_screen);


	SDL_Flip(game_screen);
	mainMenu();

	select_load_game();


#ifndef NINTENDODS
	#ifdef PLAYSTAION
		if (joystick2) {
			clear_area(game_screen, 30, MAX_H*0.5, 100, 46, 0, 0, 0);
			draw_text(30-RES_DIFF_W, (MAX_H*0.5)-RES_DIFF_H,"ONE PLAYER", game_screen);
			draw_text(30-RES_DIFF_W, (MAX_H*0.5)+13-RES_DIFF_H,"TWO PLAYERS", game_screen);
			//printf("DEBUG.intro_screen - game_config.two_players: %d\n", game_config.two_players);
			select_player_number();
		}
	#else
		if (joystick1 || joystick2) {
			clear_area(game_screen, 30, MAX_H*0.5, 100, 46, 0, 0, 0);
			draw_text(30-RES_DIFF_W, (MAX_H*0.5)-RES_DIFF_H,"ONE PLAYER", game_screen);
			draw_text(30-RES_DIFF_W, (MAX_H*0.5)+13-RES_DIFF_H,"TWO PLAYERS", game_screen);
			//printf("DEBUG.intro_screen - game_config.two_players: %d\n", game_config.two_players);
			select_player_number();
		}
	#endif
#endif

	if (game_config.two_players == 1) {
		select_player();
	}

	return pick_stage();
}

struct coordinate pick_stage() {
	blank_screen(game_screen);
	struct coordinate pos = stage_select();
	printf(">> pick_stage - pos.x: %d, pos.y: %d\n", pos.x, pos.y);
	boss_intro(pos);
	clean_input();
	waitTime(100);
	return pos;
}

void demo_ending() {
	int textPosY = 12;
	blank_screen(game_screen);
	draw_text(10-RES_DIFF_W, textPosY,"CONGRATULATIONS, YOU FINISHED", game_screen);
	textPosY += 12;
	draw_text(10-RES_DIFF_W, textPosY,"THE ROCKBOT BETA 6 GAME DEMO.", game_screen);
	textPosY += 12;
	draw_text(10-RES_DIFF_W, textPosY,"THIS GAME IS PRESENTED BY:", game_screen);
	textPosY += 12;
	draw_text(10-RES_DIFF_W, textPosY,"UPPERLAND & GREENNEKO", game_screen);
	textPosY += 20;

	draw_text(10-RES_DIFF_W, textPosY,"DEVELOPER: IURI FIEDORUK", game_screen);
	textPosY += 12;
	draw_text(10-RES_DIFF_W, textPosY,"DESIGN: ARIS K. S. FIEDORUK", game_screen);
	textPosY += 12;
	draw_text(10-RES_DIFF_W, textPosY,"COLABORATORS: RODRIGO M. HAHN,", game_screen);
	textPosY += 12;
	draw_text(10-RES_DIFF_W, textPosY,"DEMETRIO NETO AND", game_screen);
	textPosY += 12;
	draw_text(10-RES_DIFF_W, textPosY,"GIO AKIRA FAGANELLO", game_screen);
	textPosY += 20;
	draw_text(10-RES_DIFF_W, textPosY,"THANKS TO PS2DEV, DSDEV,", game_screen);
	textPosY += 12;
	draw_text(10-RES_DIFF_W, textPosY,"PS2DEV, GPF, OPENXDK, NOKIA QT,", game_screen);
	textPosY += 12;
	draw_text(10-RES_DIFF_W, textPosY,"SDL, LINUX, GIMP AND INKSCAPE.", game_screen);
	textPosY += 20;
	draw_text(10-RES_DIFF_W, textPosY,"PRESS START", game_screen);
	wait_player_start();
	leave_game();
	exit(-1);
}

void drawExplosion(short int centerX, short int centerY) {
	unsigned int timerInit, timerProgress;
	char tempBuffer[100];
	int distance=0, mode=0;
	SDL_Surface *tempImg;
	int accel=1;

	timerInit = getTimer();

	sprintf(tempBuffer, "%sdata/images/tilesets/explosion_boss.png", FILEPATH);
	tempImg = surfaceFromFile(tempBuffer);
	SDL_SetColors(tempImg, colormap, 0, COLOR_COUNT);
	p1Obj->sprite->anim_type = ANIM_STAND;
	SDL_Flip(game_screen);
	while (getTimer() < timerInit+2000) {
		move_screen(game_screen, 0, 0);
		show_sprite(p1Obj->sprite, game_screen);
		copy_area(tempImg, TILE_SIZE*mode, 0, tempImg->w/3, tempImg->h, centerX+distance, centerY, game_screen);
		copy_area(tempImg, TILE_SIZE*mode, 0, tempImg->w/3, tempImg->h, centerX-distance, centerY, game_screen);
		copy_area(tempImg, TILE_SIZE*mode, 0, tempImg->w/3, tempImg->h, centerX, centerY+distance, game_screen);
		copy_area(tempImg, TILE_SIZE*mode, 0, tempImg->w/3, tempImg->h, centerX, centerY-distance, game_screen);
		copy_area(tempImg, TILE_SIZE*mode, 0, tempImg->w/3, tempImg->h, centerX+distance, centerY+distance, game_screen);
		copy_area(tempImg, TILE_SIZE*mode, 0, tempImg->w/3, tempImg->h, centerX-distance, centerY+distance, game_screen);
		copy_area(tempImg, TILE_SIZE*mode, 0, tempImg->w/3, tempImg->h, centerX+distance, centerY-distance, game_screen);
		copy_area(tempImg, TILE_SIZE*mode, 0, tempImg->w/3, tempImg->h, centerX-distance, centerY-distance, game_screen);
		distance += 2;
		if (distance % 20 == 0) {
			if (mode+1 <= 2) {
				mode++;
			} else {
				mode = 0;
			}
			if (accel +1 <= 5) {
				accel++;
			}
		}
		SDL_Flip(game_screen);
		waitTime(10);
	}
	SDL_FreeSurface(tempImg);
}

void drawImplosion(short int centerX, short int centerY) {
	unsigned int timerInit, timerProgress;
	char tempBuffer[100];
	int distance=RES_W*0.5, mode=0;
	SDL_Surface *tempImg;
	int accel=1;

	timerInit = getTimer();

	sprintf(tempBuffer, "%sdata/images/tilesets/explosion_boss.png", FILEPATH);
	tempImg = surfaceFromFile(tempBuffer);
	SDL_SetColors(tempImg, colormap, 0, COLOR_COUNT);
	SDL_Flip(game_screen);
	centerX -= tempImg->w/6;
	centerY -= tempImg->h/2;
	while (distance > 0) {
		move_screen(game_screen, 0, 0);
		show_sprite(p1Obj->sprite, game_screen);
		copy_area(tempImg, TILE_SIZE*mode, 0, tempImg->w/3, tempImg->h, centerX+distance, centerY, game_screen);
		copy_area(tempImg, TILE_SIZE*mode, 0, tempImg->w/3, tempImg->h, centerX-distance, centerY, game_screen);
		copy_area(tempImg, TILE_SIZE*mode, 0, tempImg->w/3, tempImg->h, centerX, centerY+distance, game_screen);
		copy_area(tempImg, TILE_SIZE*mode, 0, tempImg->w/3, tempImg->h, centerX, centerY-distance, game_screen);
		copy_area(tempImg, TILE_SIZE*mode, 0, tempImg->w/3, tempImg->h, centerX+distance, centerY+distance, game_screen);
		copy_area(tempImg, TILE_SIZE*mode, 0, tempImg->w/3, tempImg->h, centerX-distance, centerY+distance, game_screen);
		copy_area(tempImg, TILE_SIZE*mode, 0, tempImg->w/3, tempImg->h, centerX+distance, centerY-distance, game_screen);
		copy_area(tempImg, TILE_SIZE*mode, 0, tempImg->w/3, tempImg->h, centerX-distance, centerY-distance, game_screen);
		distance -= 2;
		if (distance % 20 == 0) {
			if (mode+1 <= 2) {
				mode++;
			} else {
				mode = 0;
			}
			if (accel +1 <= 5) {
				accel++;
			}
		}
		SDL_Flip(game_screen);
		waitTime(10);
	}
	SDL_FreeSurface(tempImg);
}


// TODO - remove all projectiles
void got_weapon(char boss_name[50]) {
	int fim=0;
	int player_n = 0;
	int i;
	char tempBuffer[150];


	save_001.stages[STAGE_N-1] = 1;
	FILE* fp;
	sprintf(tempBuffer, "%sdata/001.sav", FILEPATH);
	fp = fopen(tempBuffer, "wb");
	if (fp) {
		fwrite (&save_001, sizeof(struct st_save), 1, fp);
		fclose(fp);
	} else {
		printf("DEBUG - error saving to file '%s'\n", tempBuffer);
	}
	// 1st part - player walk to screen center and jumps
	//printf(">> got_weapon - real.p.x: %d\n", (p1Obj->sprite->x+map_pos_x));
	p1Obj->sprite->anim_type = ANIM_WALK;
	while (fim == 0) {
		if (p1Obj->sprite->x+map_pos_x > RES_W/2) {
			keyState[player_n][KEYX] = '2';
		} else {
			keyState[player_n][KEYX] = '1';
		}
		move_screen(game_screen, 0, 0);
		player_movement(p1Obj, keyState[player_n]);
		show_sprite(p1Obj->sprite, game_screen);
		//printf(">> keyState[player_n][KEYX]: %c, p1Obj->sprite->x+map_pos_x: %d, RES_W/2: %d\n", keyState[player_n][KEYX], (p1Obj->sprite->x+map_pos_x), RES_W/2);
		if (keyState[player_n][KEYX] == '1' && p1Obj->sprite->x+map_pos_x >= (RES_W/2)-TILE_SIZE) {
			fim = 1;
		} else if (keyState[player_n][KEYX] == '2' && p1Obj->sprite->x+map_pos_x < (RES_W/2)-p1Obj->sprite->w) {
			fim = 1;
		}
		SDL_Flip(game_screen);
		waitTime(30);
	}
	// 2nd part energy goes to player
	p1Obj->sprite->anim_type = ANIM_JUMP;
	int originalY = p1Obj->sprite->y;
	while (p1Obj->sprite->y > RES_H * 0.3) {
		move_screen(game_screen, 0, 0);
		p1Obj->sprite->y -= 2;
		show_sprite(p1Obj->sprite, game_screen);
		SDL_Flip(game_screen);
		waitTime(15);
	}
	drawImplosion(p1Obj->sprite->x+map_pos_x+14, p1Obj->sprite->y+15);
	while (p1Obj->sprite->y < originalY) {
		move_screen(game_screen, 0, 0);
		p1Obj->sprite->y += 2;
		show_sprite(p1Obj->sprite, game_screen);
		SDL_Flip(game_screen);
		waitTime(10);
	}
	move_screen(game_screen, 0, 0);
	p1Obj->sprite->anim_type = ANIM_STAND;
	show_sprite(p1Obj->sprite, game_screen);
	SDL_Flip(game_screen);
	waitTime(1000);
	p1Obj->sprite->anim_type = ANIM_TELEPORT;
	while (p1Obj->sprite->y > -p1Obj->sprite->h) {
		move_screen(game_screen, 0, 0);
		p1Obj->sprite->y -= 2;
		show_sprite(p1Obj->sprite, game_screen);
		SDL_Flip(game_screen);
		waitTime(5);
	}
	// 3. show the you got weapon
	SDL_Surface *tempImg;


	int text_x = MAX_W*0.5 - 60;
	char letter[2];
	char weaponName[100];

	blank_screen(game_screen);
	sprintf(tempBuffer, "%sdata/images/backgrounds/stage_boss_intro.png", FILEPATH);
	tempImg = loadSpriteFile(tempBuffer);
	copy_area(tempImg, 0, 0, tempImg->w, tempImg->h, 0, 0, game_screen);
	p1Obj->sprite->x = 40;
	p1Obj->sprite->y = 88;
	scrollX = 0;
	map_pos_x = 0;
	p1Obj->sprite->anim_type = ANIM_ATTACK;
	show_sprite(p1Obj->sprite, game_screen);
	SDL_Flip(game_screen);

	initStars();


	if (strstr(boss_name, "Daisie Bot")) {
		sprintf(weaponName, "YOU GOT FLOWER RAINBOW");
	} else {
		sprintf(weaponName, "OOOPS - NONAME WEAPON");
	}

	for (i=0; i<strlen(weaponName); i++) {
		sprintf(letter, "%c", weaponName[i]);
		waitTimeWithStars(80);
		draw_text(text_x, 100, letter, game_screen);
		text_x += 8;
	}
	int timeInit = getTimer() + 2000;
	while (timeInit > getTimer()) {
		waitTimeWithStars(20);
	}

	// 4. select a new stage and load it
	p1Obj->sprite->anim_type = ANIM_TELEPORT;
	p1Obj->sprite->x = RES_H * 0.2;
	p1Obj->sprite->y = RES_H * 0.5;
	SDL_Flip(game_screen);
	SDL_FreeSurface(tempImg);
	struct coordinate pos;

	pos = pick_stage();
	p1Obj->sprite->x = 80;
	p1Obj->sprite->y = TILE_SIZE;
	p1Obj->x = 80;
	p1Obj->y = TILE_SIZE;
	scrollX = 0;
	map_pos_x = 0;

	blank_screen(game_screen);

	STAGE_N = pos.y*3 + pos.x + 1;
	printf(">>> DEBUG.got_weapon - stage.x: %d, stage.y: %d, map_n: %d\n", pos.x, pos.y, STAGE_N);


	loadMap(1, STAGE_N);
	drawMap(offscreen, 0);
	load_music("bgmusic.mod");
	map_pos_x = 0;
	map_pos_y = 0;
	move_screen(game_screen, 0, 0);
}
