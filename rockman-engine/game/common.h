//#include <variables>		// variáveis comuns ao jogo e ao editor


void show_sprite(struct sprite_struct *sprite_list, SDL_Surface *screen);
struct struct_npcSpriteGraphics *findNPCGraphic(char filename[255]);

// FUNCTIONS PROTOTYPES

short int check_colision(short int obj_x, short int obj_y, short int obj_w, short int obj_h, short int x_inc, short int y_inc);
void damage_npc(struct npc_struct *temp_npc, short int damage);
struct sprite_struct *create_sprite_with_surface(short int x, short int y, short int sp_w, short int sp_h, SDL_Surface *screen);
void add_sprite(short int direction, short int anim_type, short int pos_x, short int pos_y, struct sprite_struct *sprite_list, short int duration, SDL_Surface *image);
void blank_screen(SDL_Surface *screen);
void draw_text(short int x, short int y, char *text, SDL_Surface *screen);
struct struct_colorcycle_list *add_colorcycle_list(short int color_n);
void add_colorcycle(struct struct_colorcycle_list *list, int duration, int r, int g, int b);
void exec_colorcycle(SDL_Surface *screen);
void change_colormap(SDL_Surface *screen, int pos, int r, int g, int b);
// comes from hacked SDL

// ------------------------ FUNÇÕES ----------------------------

#ifdef NINTENDODS
	#define timers2ms(tlow,thigh)(tlow | (thigh<<16)) >> 5


	void StartTicks(void)  {
	   TIMER0_DATA=0;
	   TIMER1_DATA=0;
	   TIMER0_CR=TIMER_ENABLE|TIMER_DIV_1024;
	   TIMER1_CR=TIMER_ENABLE|TIMER_CASCADE;
	}

	Uint32 GetTicks(void) {
	   return timers2ms(TIMER0_DATA, TIMER1_DATA);
	}
#endif

unsigned int getTimer() {
	return SDL_GetTicks();
}

SDL_Surface *loadSpriteFile(const char *buffer) {
	SDL_RWops *rwop;
	SDL_Surface *spriteCopy;
	// carrega paleta
	rwop=SDL_RWFromFile(buffer, "rb");
	if (!rwop) {
                printf("DEBUG.loadSpriteFile - Error in loadSpriteFile: file '%s' not found\n", buffer);
	}
	spriteCopy = IMG_Load_RW(rwop, 1);
	if (!spriteCopy) {
		printf("IMG_LoadPNG_RW: %s\n", IMG_GetError());
	}
	SDL_SetColors(spriteCopy, colormap, 0, COLOR_COUNT);
	return spriteCopy;
}

void move_screen(SDL_Surface *screen, const short int x_inc, const short int y_inc) {
	SDL_Rect src, dest;
	src.x = (map_pos_x*-1) + (x_inc*-1) + TILE_SIZE;
	src.y = (map_pos_y*-1) + (y_inc*-1) + TILE_SIZE;
	src.w = MAX_W;
	src.h = MAX_H;
	// parte que vai ser colada
	dest.x = 0;
	dest.y = 0;
	dest.w = MAX_W;
	dest.h = MAX_H;
	map_pos_x += x_inc;
	map_pos_y += y_inc;
	if (src.x < 0) {
		src.x = 0;
	}

	if (src.y < 0) {
		src.y = 0;
	}
	SDL_BlitSurface(offscreen, &src, screen, &dest);
}


// copia um tile de um lugar para outro
void copy_tile(const short int tx, const short int ty, const short int dx, const short int dy, SDL_Surface *screen_source, SDL_Surface *screen_dest) {
	SDL_Rect src, dest;
	src.x = tx*TILE_SIZE;
	src.y = ty*TILE_SIZE;
	src.w = TILE_SIZE;
	src.h = TILE_SIZE;
	// parte que vai ser colada
	dest.x = dx*TILE_SIZE;
	dest.y = dy*TILE_SIZE;
	dest.w = TILE_SIZE;
	dest.h = TILE_SIZE;
	SDL_BlitSurface (screen_source, &src, screen_dest, &dest);
}


// copia um tile de um lugar para outro
void copy_area(SDL_Surface *screen_source, int src_x, int src_y, int src_w, int src_h, int dest_x, int dest_y, SDL_Surface *screen_dest) {
	SDL_Rect src, dest;
	src.x = src_x;
	src.y = src_y;
	src.w = src_w;
	src.h = src_h;
	dest.x = dest_x;
	dest.y = dest_y;
	dest.w = src_w;
	dest.h = src_h;
	SDL_BlitSurface(screen_source, &src, screen_dest, &dest);
}

// copia um tile de um lugar para outro
void copy_area_debug(SDL_Surface *screen_source, const short int src_x, const short int src_y, const short int src_w, const short int src_h, const short int dest_x, const short int dest_y, SDL_Surface *screen_dest) {
	SDL_Rect src, dest;
	src.x = src_x;
	src.y = src_y;
	src.w = src_w;
	src.h = src_h;
	dest.x = dest_x;
	dest.y = dest_y;
	dest.w = src_w;
	dest.h = src_h;
	SDL_BlitSurface(screen_source, &src, screen_dest, &dest);
}

void draw_matrix(SDL_Surface *screen, const short int x, const short int y, const short int width, const short int height) {
	// desenha linhas pretas horizontais da matriz
	short int i;

        for (i=y; i<y+height; i+=TILE_SIZE) {
                dest.x = x;
		dest.y = i;
                dest.w = width;
		dest.h = 1;
		SDL_FillRect(screen, &dest, SDL_MapRGB(screen->format, 180, 180, 180));
	}
	// desenha linhas pretas vericais da matriz
        for (i=x; i<x+width; i+=TILE_SIZE) {
                dest.x = i;
                dest.y = y;
		dest.w = 1;
                dest.h = height;
 		SDL_FillRect(screen, &dest, SDL_MapRGB(screen->format, 180, 180, 180));
	}
}




void waitTime(int wait_period) {
	int now_time=0;
	now_time = getTimer();
	wait_period = now_time + wait_period;
	while (now_time < wait_period) {
		now_time = getTimer();
		#ifndef NINTENDODS // NDS is slow, so it does not this to not use too much CPU
			#ifndef PLAYSTATION
				SDL_Delay(1);
			#else
				RotateThreadReadyQueue(_MIXER_THREAD_PRIORITY);
			#endif
		#endif
	}
}



void loadGame() {
	long lSize;
	char buffer[255];
	sprintf(buffer, "%sdata/game/001.gme", FILEPATH);
	FILE *fp = fopen(buffer, "rb");
	if (fp) {
		fseek (fp , 0 , SEEK_END);
		lSize = ftell (fp);
		rewind (fp);
		fread(&game, sizeof(game), 1, fp);
		fclose(fp);
	} else {
		printf("DEBUG - no game file '%s', ignoring load.\n", buffer);
	}
}

void centNumber(const int number, char cent_char[4]) {
	if (number < 10) {
		sprintf(cent_char, "00%d", number);
	} else if (number < 100) {
		sprintf(cent_char, "0%d", number);
	} else {
		sprintf(cent_char, "%d", number);
	}
}

// free all colorcycling variables
void freeColorCycling() {
	return;
	struct struct_colorcycle_list *cl_list_temp, *cl_list_old;
	struct struct_colorcycle *cl_item_temp, *cl_item_old;
	cl_list_temp = colorcycle_list;
	if (cl_list_temp != NULL) {
		while (cl_list_temp) {
			cl_item_temp = cl_list_temp->colorcycle;
			while (cl_item_temp) {
				cl_item_old = cl_item_temp;
				cl_item_temp =cl_item_temp->next;
				free(cl_item_old);
			}
			cl_list_temp->colorcycle = NULL;
			cl_list_old = cl_list_temp;
			cl_list_temp = cl_list_temp->next;
			free(cl_list_old);
			// restore the colormap
			change_colormap(offscreen, 61, 255, 0, 255);
			change_colormap(offscreen, 62, 55, 255, 0);
			change_colormap(offscreen, 63, 0, 255, 255);
		}
	}
	move_screen(game_screen, 0, 0);
	colorcycle_list = NULL;
}

void loadMap(const int game_n, const int map_n) {
    int i, j, k;
    int column_locked = 1;
    long lSize;
    char cent1[4];
	char cent2[4];
    char filename[255];
	char buffer[255];

    centNumber(game_n, cent1);
    centNumber(map_n, cent2);
	sprintf(filename, "%sdata/game/game_%s/%s.map", FILEPATH, cent1, cent2);

    //free old colorcycling
    freeColorCycling();


    FILE *fp = fopen(filename, "rb");
    if (fp) {
            fseek (fp , 0 , SEEK_END);
            lSize = ftell (fp);
            rewind (fp);
            fread(&map, sizeof(struct file_map), 1, fp);
            fclose(fp);

            // ---------------- SET THE SCROLL LOCK ------------------ //
            for (i=0; i<MAP_W; i++) {
                column_locked = 1;
                for (j=0; j<MAP_H; j++) {
					if (map.tiles[i][j].locked != 1 && map.tiles[i][j].locked != TERRAIN_DOOR) {
                        column_locked=0;
                        break;
                    }
                }
                wall_scroll_lock[i] = column_locked;
            }


            // ---------------- LOAD MAP NPCS START ------------------ //

            struct npc_struct *temp_npc, *old_temp_npc;
            int npc_pos_y;
            struct struct_npcSpriteGraphics *npc_graphics=NULL;

            // free the old npc list
            if (npc_list != NULL) {
                    temp_npc = npc_list;
                    while (temp_npc) {
							// free the sprite_list from npc
							for (i=0; i<ANIM_N1; i++) {
								for (j=0; j<ANIM_N2; j++) {
									for (k=0; k<ANIM_N3; k++) {
										if (temp_npc->sprite_list->sprite_frames[i][j][k].frame != NULL) {
											SDL_FreeSurface(temp_npc->sprite_list->sprite_frames[i][j][k].frame);
										}
									}
								}

							}
							free(temp_npc->sprite_list);
                            old_temp_npc = temp_npc;
                            temp_npc = temp_npc->next;
                            free(old_temp_npc);
                    }
                    npc_list = NULL;
            }
			// free the old npc graphics list
            struct struct_npcSpriteGraphics *temp_graphic, *old_graphic;
            if (npcSpriteGraphics != NULL) {
                    temp_graphic = npcSpriteGraphics;
                    while (temp_graphic) {
							SDL_FreeSurface(temp_graphic->sprite);
							old_graphic = temp_graphic;
                            temp_graphic = temp_graphic->next;
                            free(old_graphic);
                            old_graphic = NULL;
                    }
            }
            npcSpriteGraphics = NULL;
            int npcCount=0;

            for (k=0; k<STAGE_NPC_LIMIT; k++) {
                    if (map.npc_list[k].hp.total != -1) {
                            npc_pos_y = (map.npc_list[k].start_point.y)*16;
                            npc_graphics = findNPCGraphic(map.npc_list[k].filename);
                            if (npc_graphics != NULL) {
									temp_npc = add_npc(map.npc_list[k].start_point.x*16, npc_pos_y);
                                    temp_npc->graphics = npc_graphics;
                                    if (temp_npc == NULL) {
                                            printf("************ ERROR: NPC for numer %d not found!!\n", npcCount);
                                    } else {
                                            npcCount++;
                                            temp_npc->HP = map.npc_list[k].hp.total;
                                            temp_npc->shield = map.npc_list[k].have_shield;
                                            temp_npc->IA = map.npc_list[k].IA;
                                            temp_npc->shots = 0;
                                            temp_npc->can_shoot = map.npc_list[k].can_shoot;
											//printf(">> loadMap, npc[%d].is_boss: %d\n", k, map.npc_list[k].is_boss);
											temp_npc->is_boss = map.npc_list[k].is_boss;
                                            sprintf(temp_npc->name, "%s", map.npc_list[k].name);


                                            // IURI - aqui tem que ser totalmente refeito. os sprites devem ficar em graphic, e os npcs apenas devem referenciar o endereço
                                            // depois, devemos remover totalmente sprite lista e usar apenas os valores dentro de player e npc/graphic

                                            temp_npc->sprite_list = create_sprite_with_surface(map.npc_list[k].start_point.x, map.npc_list[k].start_point.y, npc_graphics->w, npc_graphics->h, game_screen);

                                            for (i=0; i<NPC_FRAME_NUMBER; i++) {
                                                    if (npc_graphics->frameset[i] != -1) {
                                                            add_sprite(ANIM_LEFT, npc_graphics->frameset[i], i, 0, temp_npc->sprite_list, npc_graphics->frameset_time[i], npc_graphics->sprite);
                                                            add_sprite(ANIM_RIGHT, npc_graphics->frameset[i], i, 1, temp_npc->sprite_list, npc_graphics->frameset_time[i], npc_graphics->sprite);
                                                    }
                                            }
                                    }
                            }
                    }
            }


			for (k=0; k<STAGE_OBJECT_LIMIT; k++) {
				map.object_list[k].sprite = NULL;
				map.object_list[k].timer = 0;
				map.object_list[k].distance = 0;
				map.object_list[k].position.x = map.object_list[k].start_point.x*TILE_SIZE;
				map.object_list[k].position.y = map.object_list[k].start_point.y*TILE_SIZE;
				if (map.object_list[k].type != -1 && strstr(map.object_list[k].filename, ".png") != NULL) {
					sprintf(buffer, "%sdata/images/sprites/objects/%s", FILEPATH, map.object_list[k].filename);
					//printf("***** object[%d] - type: %d, filename: '%s', buffer: '%s'\n", k, map.object_list[k].type, map.object_list[k].filename, buffer);
					printf("***** loadMap - object[%d] - x: %d, y: %d, type: %d, filename: %s\n", k, map.object_list[k].start_point.x, map.object_list[k].start_point.y, map.object_list[k].type, map.object_list[k].filename);
					map.object_list[k].sprite = surface_region_from_image(buffer, map.object_list[k].framesize_w, map.object_list[k].framesize_h);
					if (map.object_list[k].sprite == NULL) {
						printf(">>> loadMap - error creating sprite for object %d, filename: %s\n", k, map.object_list[k].filename);
						map.object_list[k].type = -1;
					}
				}
			}
            // ---------------- LOAD MAP NPCS END ------------------ //

            currentMap = map_n;
            currentGame = game_n;


            struct struct_colorcycle_list *cl_item;
            //add colorcycling

            // first
            colorcycle_n = SDL_MapRGB(tileset->format, 55, 255, 0);
            cl_item = add_colorcycle_list(colorcycle_n);
            add_colorcycle(cl_item, 200, 255, 155, 59); // laranja
            add_colorcycle(cl_item, 200, 219, 43, 0); // marrom
            add_colorcycle(cl_item, 200, 255, 219, 171); // bege
            // second
            colorcycle_n = SDL_MapRGB(tileset->format, 255, 0, 255);
            cl_item = add_colorcycle_list(colorcycle_n);
            add_colorcycle(cl_item, 200, 219, 43, 0); // marrom
            add_colorcycle(cl_item, 200, 255, 219, 171); // bege
            add_colorcycle(cl_item, 200, 255, 155, 59); // laranja
            // third
            colorcycle_n = SDL_MapRGB(tileset->format, 0, 255, 255);
            cl_item = add_colorcycle_list(colorcycle_n);
            add_colorcycle(cl_item, 200, 255, 219, 171); // bege
            add_colorcycle(cl_item, 200, 255, 155, 59); // laranja
            add_colorcycle(cl_item, 200, 219, 43, 0); // marrom

    } else {
    #ifdef NINTENDODS
            int text_pos_y=1;
            char debug_buffer[255];
            sprintf(debug_buffer, "loadMap - no map file gn: %d, mn: %d", game_n, map_n);
            draw_text(4, (text_pos_y*12), debug_buffer, game_screen);
            while(1);
    #endif
            printf("DEBUG - no map file, ignoring load.\n");
    }
}





void loadTempMap(const int game_n, const int map_n) {
	char cent1[4];
	char cent2[4];
	char filename[255];

	centNumber(game_n, cent1);
	centNumber(map_n, cent2);
	sprintf(filename, "%sdata/game/game_%s/%s.map", FILEPATH, cent1, cent2);
	//printf("DEBUG.drawMapLastLine - filename: %s\n", filename);
	FILE *fp = fopen(filename, "rb");
	if (fp) {
		//printf("Loading map file...\n");
		fseek (fp , 0 , SEEK_END);
		rewind (fp);
		fread(&temp_map, sizeof(struct file_map), 1, fp);
		fclose(fp);
	} else {
		printf("DEBUG - no map file, ignoring load.\n");
	}
}


void freeMap(struct file_map my_map) {
	int j, k;

	sprintf(map.name, " ");
	my_map.bosss_door_x=999;
	sprintf(map.filename, "%sdata/images/tilesets/default.png", FILEPATH);
	for (j=0; j<MAP_W; j++) {
		for (k=0; k<MAP_H; k++) {
			my_map.tiles[j][k].locked=0;
			my_map.tiles[j][k].tile1.x=-1;
			my_map.tiles[j][k].tile1.y=-1;
			my_map.tiles[j][k].tile2.x=-1;
			my_map.tiles[j][k].tile2.y=-1;
		}
	}
	/*
	for (j=0; j<STAGE_NPC_LIMIT; j++) {
		map.npc_list[j]
	}
	*/

}

void drawMap(SDL_Surface *screen, const short int adjust) {
	short int i, j, real_quad_x;
	//printf("DEBUG.drawMap 1\n");
	extern SDL_Surface *tileset;


	for (i=0; i<MAP_W; i++) {
		for (j=0; j<MAP_H; j++) {
			real_quad_x = i + adjust;
			if (map.tiles[i][j].tile1.x != -1 && map.tiles[i][j].tile1.y != -1) {
				//printf("DEBUG.drawMap - tile[%d][%d].x %d, y %d\n", i, j, map.tiles[i][j].tile1.x, map.tiles[i][j].tile1.y);
				if (!tileset) {
					//printf("DEBUG.drawMap - no tileset");
				}
				if (!screen) {
					//printf("DEBUG.drawMap - no screen");
				}
				if (!offscreen) {
					//printf("DEBUG.drawMap - no offscreen");
				}
				copy_area(tileset, map.tiles[i][j].tile1.x*TILE_SIZE, map.tiles[i][j].tile1.y*TILE_SIZE, TILE_SIZE, TILE_SIZE, real_quad_x*TILE_SIZE+TILE_SIZE, j*TILE_SIZE+TILE_SIZE, offscreen);
			}
			if (map.tiles[i][j].tile2.x != -1 && map.tiles[i][j].tile2.y != -1) {
				copy_area(tileset, map.tiles[i][j].tile2.x*TILE_SIZE, map.tiles[i][j].tile2.y*TILE_SIZE, TILE_SIZE, TILE_SIZE, real_quad_x*TILE_SIZE+TILE_SIZE, j*TILE_SIZE+TILE_SIZE, offscreen);
			}
		}
	}
	copy_area_debug(screen, 0, 0, MAP_W*TILE_SIZE, MAP_H*TILE_SIZE, 0, 0, offscreen);
}

void drawMap3rdLevel(SDL_Surface *screen) {
	extern SDL_Surface *tileset;
	int i, j;

	for (i=0; i<MAP_W; i++) {
		for (j=0; j<MAP_H; j++) {
			if (map.tiles[i][j].tile3.x != -1 && map.tiles[i][j].tile3.y != -1) {
				// must check if the position is visible in the screen
				//printf(">> common.h::drawMap3rdLevel - scrollX: %d, scrollY: %d, posX: %d, posY: %d, MAX_W: %d\n", scrollX, scrollY, (i*TILE_SIZE), (j*16),MAX_W);
				//printf(">> common.h::drawMap3rdLevel - scrollX: %d, map_pos_x:  %d\n", scrollX, map_pos_x);
				if (i*TILE_SIZE >= -map_pos_x-TILE_SIZE && i*TILE_SIZE <= -map_pos_x+MAX_W+TILE_SIZE) {
					//printf(">> common.h::drawMap3rdLevel - X OK\n");
					if (j*TILE_SIZE >= scrollY-TILE_SIZE && j*TILE_SIZE <= scrollY+MAX_H+TILE_SIZE) {
						//printf(">> common.h::drawMap3rdLevel - Y OK\n");
						copy_area(tileset, map.tiles[i][j].tile3.x*TILE_SIZE, map.tiles[i][j].tile3.y*TILE_SIZE, TILE_SIZE, TILE_SIZE, (i*TILE_SIZE)+map_pos_x, (j*TILE_SIZE)-scrollY, screen);
					}
				}
				//copy_area(tileset, map.tiles[i][j].tile2.x*TILE_SIZE, map.tiles[i][j].tile2.y*TILE_SIZE, TILE_SIZE, TILE_SIZE, i*TILE_SIZE, j*TILE_SIZE, offscreen);
			}
		}
	}
}


// set default values for game variable
void initGameVar() {
	short int j, k;
	strcpy (game.name, "My Game");
	sprintf(map.name, "Map 00%d", 1);
	map.bosss_door_x=200;
	sprintf(map.filename, "%sdata/images/tilesets/default.png", FILEPATH);
	for (j=0; j<MAP_W; j++) {
		for (k=0; k<MAP_H; k++) {
			map.tiles[j][k].locked=0;
			map.tiles[j][k].tile1.x=-1;
			map.tiles[j][k].tile1.y=-1;
			map.tiles[j][k].tile2.x=-1;
			map.tiles[j][k].tile2.y=-1;
		}
	}
}

// free variables
void leave_game() {
	struct player_struct *temp, *temp_old;
	struct npc_struct *ntemp, *ntemp_old;
	struct animation_sprite_struct *temp_anim, *old_temp_anim;
	int k;

	// free player list
	temp = player_list;
	if (temp != NULL) {
		while (temp != NULL) {
			temp_old = temp;
			temp = temp->next;
			free(temp_old);
		}
	}
	// free npc list
	ntemp = npc_list;
	if (ntemp != NULL) {
		while (ntemp) {
			ntemp_old = ntemp;
			ntemp = ntemp->next;
			free(ntemp_old);
		}
	}
	// free animation list
	temp_anim = animation_list;
	if (temp_anim != NULL) {
		while (temp_anim != NULL) {
			old_temp_anim = temp_anim;
			temp_anim = temp_anim->next;
			if (old_temp_anim->frame->tile != NULL) {
				free(old_temp_anim->frame->tile);
				old_temp_anim->frame->tile = NULL;
			}
			free(old_temp_anim);
		}
	}
	// free projectiles
	free(normal_projectile);
	if (keyState[0] != NULL) {
		free(keyState[0]);
	}
	if (keyState[1] != NULL) {
		free(keyState[1]);
	}
	// free objects graphics
	for (k=0; k<STAGE_OBJECT_LIMIT; k++) {
		if (map.object_list[k].sprite != NULL) {
			SDL_FreeSurface(map.object_list[k].sprite);
		}
	}
	SDL_FreeSurface(tileset);
	SDL_FreeSurface(game_screen);
	SDL_FreeSurface(offscreen);
#ifndef NINTENDODS
	if (joystick1) {
		SDL_JoystickClose(joystick1);
	}
#endif
	TTF_CloseFont(font);
	close_audio();
	TTF_Quit();
	SDL_QuitSubSystem(SDL_INIT_VIDEO|SDL_INIT_JOYSTICK);

/*
#ifdef PLAYSTATION
	if (!strncmp(argv[0], "cdfs", 4) || !strncmp(argv[0], "cdrom", 5)) {
		CDVD_Stop();
	}
#endif
*/

#ifdef NINTENDODS
	fclose (stdout);
#endif

	exit(-1);
}

void init_sprite_vars(struct sprite_struct *sprite_list) {
	short int i, j, k;
	sprite_list->frame_pos[0]=0;
	sprite_list->frame_pos[1]=0;
	sprite_list->frame_timer=0;
	//sprite_list->jumpButtonReleased=0;
	//sprite_list->attackButtonReleased=0;
	sprite_list->frame_animation[0]=0;
	sprite_list->frame_animation[1]=0;
	sprite_list->visible=1;
	// new animation system
	sprite_list->direction=0;
	sprite_list->anim_type=0;
	sprite_list->anim_pos=0;

	for (i=0; i<ANIM_N1; i++) {
		for (j=0; j<ANIM_N2; j++) {
			for (k=0; k<ANIM_N3; k++) {
				sprite_list->sprite_frames[i][j][k].frame=NULL;
				sprite_list->sprite_frames[i][j][k].duration=0;
				sprite_list->sprite_frames[i][j][k].init = 0;
			}
		}
	}
	sprite_list->anim_status.move_type = ANIM_STAND;
	for (i=0; i<ANIM_N3; i++) {
		sprite_list->anim_status.move_status[i]=0;
		sprite_list->anim_status.move_frame[i]=0;
	}
}

// ----------------------------------------------- ANIMATION ----------------------------------------------------- //

struct animation_frame *create_animation_frame(char filename[50], const short int w, const short int h) {
	struct animation_frame *new_frame;
	SDL_RWops *rwop;

	new_frame = (struct animation_frame*)malloc(sizeof(struct animation_frame));
	new_frame->duration=100;
	new_frame->w = w;
	new_frame->h = h;
	rwop=SDL_RWFromFile(filename, "rb");
	if (!rwop) {
		printf("Error in create_sprite: '%s' file not found\n", filename);
		exit(-1);
	//} else {
		//printf("DEBUG - criando sprite para: %s\n", filename);
	}
	//new_frame->tile=IMG_LoadPNG_RW(rwop);
	new_frame->tile = IMG_Load_RW(rwop, 1);
	return new_frame;
}


struct animation_frame *create_animation_frame_from_sdlarea(const short int w, const short int h) {
	struct animation_frame *new_frame;
	new_frame = (struct animation_frame*)malloc(sizeof(struct animation_frame));
	new_frame->duration=100;
	new_frame->w = w;
	new_frame->h = h;
	new_frame->tile = SDL_CreateRGBSurface(SDL_SWSURFACE , 30, 30, 8, 0, 0, 0, 0);
	return new_frame;
}


struct animation_sprite_struct *create_animation(const short int x, const short int y, struct animation_frame *frame) {
	struct animation_sprite_struct *new_anim, *temp;
	new_anim = (struct animation_sprite_struct*)malloc(sizeof(struct animation_sprite_struct));
	new_anim->x = x;
	new_anim->y = y;
	new_anim->animation_pos = 0;
	new_anim->animation_loops = 1;
	new_anim->init = 0;
	new_anim->animation_loop_count = 1;
	new_anim->next = NULL;
	new_anim->frame = frame;

	//printf("DEBUG.create_animation - temp->y: %d\n", new_anim->y);
	src.x = new_anim->x + map_pos_x;
	src.y = new_anim->y + map_pos_y;
	src.w = new_anim->frame->tile->w;
	src.h = new_anim->frame->tile->h;
	// parte que vai ser colada
	dest.x = 0;
	dest.y = 0;
	dest.w = new_anim->frame->tile->h;
	dest.h = TILE_SIZE;
	//new_anim->frame = create_animation_frame(filename, w, h);
	// the max animation frames is 5, but we must check is less than that by the image total width
	if (animation_list == NULL) {
		animation_list = new_anim;
	} else {
		temp = animation_list;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = new_anim;
	}
	return new_anim;
}



void init_main_vars() {
	int i;
	//printf("DEBUG.init_main_vars - START\n");
	game_config.two_players = 1;
	game_config.selected_player = 1;
	//printf("DEBUG.init_main_vars - game_config.two_players: %d\n", game_config.two_players);
	save_001.finished_stages = 0;
	for (i=0; i<DIALOG_MAX_STAGE; i++) {
		save_001.stages[i] = 0;
	}
	save_001.items.energy_tanks = 0;
	save_001.items.weapon_tanks = 0;
	save_001.items.lifes = 0;

	// HARDCODED VARS - BEGIN

/*
char boss_name[80];
char boss_sprites_filename[100];
char boss_face_filename[100];
int initial_map;
*/

	// just to avoid having trash in the variables
	for (i=0; i<DIALOG_MAX_STAGE; i++) {
		stages[i].initial_map = 1;
		sprintf(stages[i].boss_name, "");
		sprintf(stages[i].boss_sprites_filename, "");
		sprintf(stages[i].boss_face_filename, "");
	}
	// APEBOT
	stages[1].initial_map = 1;
	sprintf(stages[1].boss_name, "Apebot");
	sprintf(stages[1].boss_sprites_filename, "apebot.png");
	sprintf(stages[1].boss_face_filename, "apebot.png");


	// HARDCODED VARS - END
}

void reset_colormap() {
    colormap[0].r = 117;
    colormap[0].g = 117;
    colormap[0].b = 117;


}

