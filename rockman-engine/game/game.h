#define JOYVAL 5000
#include "input.h"
#include "format/file_map.h"
#include "npcs.h"

short int player_movement(struct player_struct *pObj, char *myKeyState);


// check colision of Player with NPCs
short int colision_player_npc(struct player_struct *playerObj, const short int x_inc, const short int y_inc) {
	struct npc_struct *temp_npc;
	struct pos p1, p2, p3, p4;
	struct pos npc1, npc2, npc3, npc4;
	short int i;
	short int diffx, diffy;
	temp_npc = npc_list;
	short int passX=0, passY=0;

	short int reduce = abs(16-playerObj->sprite->w)*0.5;
	short int diff_h = playerObj->sprite->h - PLAYER_H;

	//printf(">> colision_player_npc - diff_h: %d\n", diff_h);

	p1.x = playerObj->sprite->x + x_inc + reduce;
	p1.y = playerObj->sprite->y + y_inc + diff_h;

	// ponto 2, baixo/esquerda
	p2.x = playerObj->sprite->x + x_inc + reduce;
	p2.y = playerObj->sprite->y + y_inc + PLAYER_H;

	// ponto 3, topo/direita
	p3.x = playerObj->sprite->x + x_inc + playerObj->sprite->w - reduce;
	p3.y = playerObj->sprite->y + y_inc + diff_h;

	// ponto 4, baixo/direita
	p4.x = playerObj->sprite->x + x_inc + playerObj->sprite->w - reduce;
	p4.y = playerObj->sprite->y + y_inc + PLAYER_H;

	// fix for ground checking
	p1.y = p1.y - 1;
	p2.y = p2.y - 1;
	p3.y = p3.y - 1;
	p4.y = p4.y - 1;


	i = 2;
	if (temp_npc != NULL) {
		while (temp_npc != NULL) {
			if (temp_npc->HP > 0) {
				npc1.x = temp_npc->x;
				npc1.y = temp_npc->y;
				npc2.x = temp_npc->x;
				npc2.y = temp_npc->y+temp_npc->sprite_list->h;
				npc3.x = temp_npc->x+temp_npc->sprite_list->w;
				npc3.y = temp_npc->y;
				npc4.x = temp_npc->x+temp_npc->sprite_list->w;
				npc4.y = temp_npc->y+temp_npc->sprite_list->h;
				// any point inside NPC is a hit
				//printf("--------> colision_player_npc - playerObj->hit_timer: %d\n", playerObj->hit_timer);
				if (playerObj->hit != 1 && playerObj->hit_timer < getTimer()) {
					passY = 0;
					passX = 0;
					// check Y
					if ((p1.y >= npc1.y && p1.y <= npc4.y) || (p4.y >= npc1.y && p4.y <= npc4.y)) {
						passY=1;
					} else if ((npc1.y >= p1.y && npc1.y <= p4.y) || (npc4.y >= p1.y && npc4.y <= p4.y)) {
						passY=1;
					}

					if ((p1.x >= npc1.x && p1.x <= npc4.x) || (p4.x >= npc1.x && p4.x <= npc4.x)) {
						passX=1;
					} else if ((npc1.x >= p1.x && npc1.x <= p4.x) || (npc4.x >= p1.x && npc4.x <= p4.x)) {
						passX=1;
					}
					if (passX == 1 && passY == 1) {
						printf(">> colision_player_npc - player.y: %d, diff_h: %d, p1.y: %d, npc2.y: %d, npc.h: %d, npc.y: %d\n", playerObj->sprite->y, diff_h, p1.y, npc2.y, temp_npc->sprite_list->h, temp_npc->y);
						playerObj->hit = 1;
						playerObj->hit_timer = getTimer()+HIT_INVENCIBLE_TIME;
						//printf("---------> colision_player_npc - player hit, setting hit_timer to: %d\n", playerObj->hit_timer);
						playerObj->HP = playerObj->HP - 3;
						if (p1.x > (npc1.x+temp_npc->sprite_list->w*0.5)) {
							playerObj->sprite->direction = ANIM_LEFT;
						} else {
							playerObj->sprite->direction = ANIM_RIGHT;
						}
						playerObj->sprite->anim_type = ANIM_HIT;
						playerObj->sprite->frame_animation[ANIM_PROCESS] = SDL_GetTicks()+500;
						diffx = (playerObj->sprite->w-16)*0.5;
						diffy = (playerObj->sprite->h-16)*0.5;
						create_hit_animation(playerObj->sprite->x+diffx, playerObj->sprite->y+diffy);
						play_sfx(SFX_PLAYER_HIT);
						return 1;
					}
				}
			}
			i++;
			temp_npc = temp_npc->next;
		}
	}
	return 0;
}



short int checkDelay(struct player_struct *playerObj) {
    long int now_time=0;
    now_time = getTimer();
    if (now_time > playerObj->sprite->move_timer) {
            playerObj->sprite->move_timer=now_time+17;
            return 1;
    }
    return 0;
}



short int execute_attack(struct player_struct *pObj, char *myKeyState) {
    int res;
    if (myKeyState[KEYATTACK]=='1' && pObj->attackButtonReleased==0) {
        //throw_projectile(player_n);
        res = throw_projectile_player(pObj);
        if (res) {
            pObj->attackButtonReleased=1;
			play_sfx(SFX_PLAYER_SHOT);
            return 1;
        }
    }
    return 0;
}


/*********** checks if there is a need to scroll the background **********/
void checkScrolling(const short int x_inc, const short int y_inc) {
	int mapScrollX=0;
	int moveX=0, moveY=0;

	if (scrollX >= 0) {
		mapScrollX = scrollX;
	} else {
		mapScrollX = MAP_W*TILE_SIZE -abs(scrollX) - MAX_W;
	}



	if (game_config.two_players == 2) {
		if (x_inc < 0) {
			if ((p2Obj->sprite->x+p2Obj->sprite->w-abs(map_pos_x)) >= MAX_W) {
				move_screen(game_screen, moveX, moveY);
				return;
			}
		}
	}

	// test if map is all locked in the column most to the right
	if (x_inc > 0) {
		//printf(">>>> moving to right, map_pos_x: %d, scrollX: %d, tile-0: %d, tile-end: %d\n", map_pos_x, scrollX, (abs(map_pos_x)/TILE_SIZE), (abs(map_pos_x)/TILE_SIZE+RES_W/TILE_SIZE));
		if (wall_scroll_lock[(abs(map_pos_x)/TILE_SIZE+RES_W/TILE_SIZE)-1] == 1) {
			move_screen(game_screen, moveX, moveY);
			return;
		}
	} else {
		if (wall_scroll_lock[(abs(map_pos_x)/TILE_SIZE)+1] == 1) {
			move_screen(game_screen, moveX, moveY);
			return;
		}
	}


	if (game_config.two_players == 2) {
		if (p1Obj->sprite->x+p1Obj->sprite->w > (MAP_W*16) || p2Obj->sprite->x+p2Obj->sprite->w > (MAP_W*16)) {
			demo_ending();
			return;
		} else if (p1Obj->sprite->x+MAX_W*0.5+1 > (MAP_W*16) || p2Obj->sprite->x+MAX_W*0.5+1 > (MAP_W*16)) {
			move_screen(game_screen, moveX, moveY);
			return;
		}
		if (x_inc > 0 && p1Obj->sprite->x + map_pos_x >= RES_W*0.5 && (p2Obj->sprite->x+map_pos_x) > x_inc) {
			moveX = (x_inc)*-1;
		}
		if (x_inc < 0 && (p1Obj->sprite->x + map_pos_x) < RES_W*0.5 && map_pos_x < 0 && p2Obj->sprite->x+map_pos_x < (RES_W-p2Obj->sprite->w)) {
			moveX = (x_inc)*-1;
		}
		if (y_inc < 0 && (p1Obj->sprite->y + map_pos_y) < MAX_H*0.16666 && map_pos_y < 0 && p2Obj->sprite->y+map_pos_y+16 < (MAX_H-p2Obj->sprite->h)) {
			moveY = (y_inc)*-1;
		}
		if (y_inc > 0 && (p1Obj->sprite->y + map_pos_y) >= MAX_H-48 && ((map_pos_y*-1)+MAX_H+8 <= MAP_H*16) && (p2Obj->sprite->y+map_pos_y > y_inc)) {
			moveY = (y_inc)*-1;
		}
		if (x_inc > 0 && p1Obj->sprite->x + map_pos_x >= RES_W*0.5 && p2Obj->sprite->x+map_pos_x > x_inc) {
			moveX = (x_inc)*-1;
		} else if (x_inc < 0 && (p1Obj->sprite->x + map_pos_x) < RES_W*0.5 && (map_pos_x < 0) && (p1Obj->sprite->x+map_pos_x < RES_W-p2Obj->sprite->w)) {
			moveX = (x_inc)*-1;
		}
	} else {
		if (p1Obj->sprite->x+p1Obj->sprite->w > (MAP_W*16)) {
			demo_ending();
			return;
		} else if (p1Obj->sprite->x+RES_W*0.5+1 > (MAP_W*16)) {
			move_screen(game_screen, moveX, moveY);
			return;
		}
		if (x_inc > 0 && p1Obj->sprite->x + map_pos_x >= RES_W*0.5) {
			moveX = (x_inc)*-1;
		}
		if (x_inc < 0 && (p1Obj->sprite->x + map_pos_x) < RES_W*0.5 && map_pos_x < 0) {
			moveX = (x_inc)*-1;
		}
		if (y_inc < 0 && (p1Obj->sprite->y + map_pos_y) < MAX_H*0.1666 && map_pos_y < 0) {
			moveY = (y_inc)*-1;
		}
		if (y_inc > 0 && (p1Obj->sprite->y + map_pos_y) >= MAX_H-48 && (map_pos_y*-1)+MAX_H+8 <= MAP_H*16) {
			moveY = (y_inc)*-1;
		}
		if (x_inc > 0 && p1Obj->sprite->x + map_pos_x >= RES_W*0.5) {
			moveX = (x_inc)*-1;
		} else if (x_inc < 0 && (p1Obj->sprite->x + map_pos_x) < RES_W*0.5 && map_pos_x < 0) {
			moveX = (x_inc)*-1;
		}
	}
	scrollX += moveX*-1;
	scrollY += moveY*-1;
	//printf("moveX: %d, moveY: %d, scrollX: %d, scrollY: %d\n", moveX, moveY, scrollX, scrollY);
	move_screen(game_screen, moveX, moveY);
}



void anim_npcs() {
	struct npc_struct *temp;
	temp = npc_list;

	while (temp != NULL) {
		move_npc(temp);
		show_npc_sprite(game_screen, temp);
		anim_npc_projectile(temp);
		temp = temp->next;
	}
}

void anim_objects() {
	int i;

	for (i=0; i<STAGE_OBJECT_LIMIT; i++) {
		//printf(">> debug map.object_list[%d] type: %d, filename: %s\n", i, map.object_list[i].type, map.object_list[i].filename);
		if (map.object_list[i].type != -1 && strstr(map.object_list[i].filename, ".png") != NULL) {
			moveObjects(i);
			show_object_sprites(game_screen, i);
		}
	}
}

void anim_players() {
	if (p1Obj->hit_timer < getTimer()) {
		show_sprite(p1Obj->sprite, game_screen);
	} else if (getTimer() % BLINK_SPEED == 0) {
		show_sprite(p1Obj->sprite, game_screen);
	}
	if (game_config.two_players == 2) {
		if (p2Obj->hit_timer < getTimer()) {
			show_sprite(p2Obj->sprite, game_screen);
		} else if (getTimer() % BLINK_SPEED == 0) {
			show_sprite(p2Obj->sprite, game_screen);
		}
	}
}


// verify if the player can move to the desired spot
void update_sprites() {
	if (PAUSED == 0) {
            // clear
            // move

            // this if is duplicated and separated to avoid drawing npcs after in-game menu is shown
            if (PAUSED == 0) {
				move_player(p1Obj);
				if (game_config.two_players > 1) {
					move_player(p2Obj);
				}
				anim_npcs();
				anim_objects();
				anim_players();
                // redraw


				show_animation(game_screen);
				drawMap3rdLevel(game_screen);
				draw_hp_bar(p1Obj);
				if (game_config.two_players == 2) {	// players
					draw_hp_bar(p2Obj);
				}
            }
	} else {
		inGameMenu();
	}
}

int getPlayerNFromObj(struct player_struct *pObj) {
    if (pObj == p1Obj) {
        return 0;
    } else {
        return 1;
    }
}


// TODO - impediro movimento enquanto o dialogo estiver ativo
void move_player(struct player_struct *pObj) {
    int player_n;
    #ifndef PLAYSTATION
        if (!checkDelay(pObj)) {
                return;
        }
    #endif

    //checkInput(myKeyState, player_n);
	//if (ready_animation.n >= ready_animation.repeat_n) {
		read_input(1);
		updateJoyMove();
	//}

    player_n = getPlayerNFromObj(pObj);

    if (keyState[player_n][KEYSTART]=='1') {
		PAUSED = 1;
		openInGameMenu();
    } else if (keyState[player_n][KEYQUIT]=='1') {
		fim = 1;
		return;
    } else {
		player_movement(pObj, keyState[player_n]);
		colision_player_npc(pObj, 0, 0);
		anim_projectiles();
    }
}



SDL_Surface *load_tileset(char *filename) {
	SDL_Surface *spriteCopy;
	char buffer[255];
	sprintf(buffer, "%sdata/images/tilesets/%s", FILEPATH, filename);
	spriteCopy = loadSpriteFile(buffer);
	if (!spriteCopy) {
		printf("ERROR: Could not find file '%s'\n", buffer);
		exit(-1);
	}
	return spriteCopy;
}


short int game_init(struct coordinate stage) {
	SDL_Surface *temp_surface;

	clear_area(game_screen, 0, 0, MAX_W, MAX_H, 0, 0, 0);
	waitScapeTime(50);

	PAUSED = 0;

    srcrect.w = 0;
    srcrect.h = 0;
	srcrect.x = 600;
	srcrect.y = 20;
	char buffer [255];

	tileset = load_tileset("default.png");
	if (!tileset) {
		draw_text(4, 16,"ERROR LOADING TILESET", game_screen);
		printf("ERRO: no tileset\n");
		exit(-1);
	}

	initGameVar();
	loadGame();
	npc_list=NULL;

	blank_screen(game_screen);

	STAGE_N = stage.y*3 + stage.x + 1;
	printf(">>> DEBUG - stage.x: %d, stage.y: %d, map_n: %d\n", stage.x, stage.y, STAGE_N);
	loadMap(1, STAGE_N);
	blank_screen(game_screen);



	// creates offscree. it is of the map size plus 32 for managing map-change scrolling
	offscreen = SDL_CreateRGBSurface(SDL_SWSURFACE , MAP_W*16+32, MAP_H*16+32, 8, 0, 0, 0, 0);
	SDL_SetColors(offscreen, colormap, 0, COLOR_COUNT);


	// new animation system
	//add_sprite(short int direction, short int anim_type, short int pos_x, short int pos_y, short int sprite_id)
	clear_area(game_screen, 0, 0, MAX_W, MAX_H, 0, 0, 0);

	if (game_config.two_players == 2 || game_config.selected_player == 1) {
		sprintf(buffer, "%sdata/images/sprites/sprites_p1.png", FILEPATH);
		temp_surface = surfaceFromFile(buffer);
		clear_area(game_screen, 0, 0, MAX_W, MAX_H, 0, 0, 0);

		int p1n = add_player();
		p1Obj = getPlayerN(p1n);
		sprintf(p1Obj->name, "Rockbot");
		sprintf(p1Obj->face_filename, "rockbot.png");

		p1Obj->sprite = create_sprite(20, 0, 29, 32, game_screen);
		//add_sprite(short int direction, short int anim_type, short int pos_x, short int pos_y, short int sprite_id, short int duration)
		// STAND
		add_sprite(ANIM_RIGHT, ANIM_STAND, 3, 0, p1Obj->sprite, 5000, temp_surface);
		add_sprite(ANIM_RIGHT, ANIM_STAND, 4, 0, p1Obj->sprite, 100, temp_surface);
		add_sprite(ANIM_LEFT, ANIM_STAND, 3, 1, p1Obj->sprite, 5000, temp_surface);
		add_sprite(ANIM_LEFT, ANIM_STAND, 4, 1, p1Obj->sprite, 100, temp_surface);
		// WALK
		add_sprite(ANIM_RIGHT, ANIM_WALK, 6, 0, p1Obj->sprite, 100, temp_surface);
		add_sprite(ANIM_RIGHT, ANIM_WALK, 7, 0, p1Obj->sprite, 100, temp_surface);
		add_sprite(ANIM_RIGHT, ANIM_WALK, 8, 0, p1Obj->sprite, 100, temp_surface);
		add_sprite(ANIM_LEFT, ANIM_WALK, 6, 1, p1Obj->sprite, 100, temp_surface);
		add_sprite(ANIM_LEFT, ANIM_WALK, 7, 1, p1Obj->sprite, 100, temp_surface);
		add_sprite(ANIM_LEFT, ANIM_WALK, 8, 1, p1Obj->sprite, 100, temp_surface);
		// JUMP
		add_sprite(ANIM_RIGHT, ANIM_JUMP, 9, 0, p1Obj->sprite, 100, temp_surface);
		add_sprite(ANIM_LEFT, ANIM_JUMP, 9, 1, p1Obj->sprite, 100, temp_surface);
		// ATTACK
		add_sprite(ANIM_RIGHT, ANIM_ATTACK, 11, 0, p1Obj->sprite, 100, temp_surface);
		add_sprite(ANIM_LEFT, ANIM_ATTACK, 11, 1, p1Obj->sprite, 100, temp_surface);
		// ATTACK + JUMP
		add_sprite(ANIM_RIGHT, ANIM_JUMP_ATTACK, 10, 0, p1Obj->sprite, 80, temp_surface);
		add_sprite(ANIM_LEFT, ANIM_JUMP_ATTACK, 10, 1, p1Obj->sprite, 80, temp_surface);
		// ATTACK + WALK
		add_sprite(ANIM_RIGHT, ANIM_WALK_ATTACK, 12, 0, p1Obj->sprite, 100, temp_surface);
		add_sprite(ANIM_RIGHT, ANIM_WALK_ATTACK, 13, 0, p1Obj->sprite, 100, temp_surface);
		add_sprite(ANIM_RIGHT, ANIM_WALK_ATTACK, 14, 0, p1Obj->sprite, 100, temp_surface);
		add_sprite(ANIM_LEFT, ANIM_WALK_ATTACK, 12, 1, p1Obj->sprite, 100, temp_surface);
		add_sprite(ANIM_LEFT, ANIM_WALK_ATTACK, 13, 1, p1Obj->sprite, 100, temp_surface);
		add_sprite(ANIM_LEFT, ANIM_WALK_ATTACK, 14, 1, p1Obj->sprite, 100, temp_surface);
		// HIT
		add_sprite(ANIM_LEFT, ANIM_HIT, 15, 1, p1Obj->sprite, 100, temp_surface);
		add_sprite(ANIM_RIGHT, ANIM_HIT, 15, 0, p1Obj->sprite, 100, temp_surface);
		// TELEPORT
		add_sprite(ANIM_RIGHT, ANIM_TELEPORT, 0, 0, p1Obj->sprite, 750, temp_surface);
		add_sprite(ANIM_RIGHT, ANIM_TELEPORT, 1, 0, p1Obj->sprite, 300, temp_surface);
		add_sprite(ANIM_RIGHT, ANIM_TELEPORT, 2, 0, p1Obj->sprite, 150, temp_surface);
		// STAIRS
		add_sprite(ANIM_RIGHT, ANIM_STAIRS, 17, 0, p1Obj->sprite, 5000, temp_surface);
		add_sprite(ANIM_LEFT, ANIM_STAIRS, 17, 1, p1Obj->sprite, 5000, temp_surface);
		// stairs semi
		add_sprite(ANIM_RIGHT, ANIM_STAIRS_SEMI, 18, 0, p1Obj->sprite, 5000, temp_surface);
		add_sprite(ANIM_RIGHT, ANIM_STAIRS_SEMI, 18, 1, p1Obj->sprite, 5000, temp_surface);
		add_sprite(ANIM_LEFT, ANIM_STAIRS_SEMI, 18, 0, p1Obj->sprite, 5000, temp_surface);
		add_sprite(ANIM_LEFT, ANIM_STAIRS_SEMI, 18, 1, p1Obj->sprite, 5000, temp_surface);
		add_sprite(ANIM_RIGHT, ANIM_STAIRS, 17, 0, p1Obj->sprite, 5000, temp_surface);
		add_sprite(ANIM_LEFT, ANIM_STAIRS, 17, 1, p1Obj->sprite, 5000, temp_surface);
		// stairs + move
		add_sprite(ANIM_RIGHT, ANIM_STAIRS_MOVE, 17, 0, p1Obj->sprite, 200, temp_surface);
		add_sprite(ANIM_RIGHT, ANIM_STAIRS_MOVE, 17, 1, p1Obj->sprite, 200, temp_surface);
		add_sprite(ANIM_LEFT, ANIM_STAIRS_MOVE, 17, 0, p1Obj->sprite, 200, temp_surface);
		add_sprite(ANIM_LEFT, ANIM_STAIRS_MOVE, 17, 1, p1Obj->sprite, 200, temp_surface);
		// stairs + attack
		add_sprite(ANIM_LEFT, ANIM_STAIRS_ATTACK, 19, 1, p1Obj->sprite, 200, temp_surface);
		add_sprite(ANIM_RIGHT, ANIM_STAIRS_ATTACK, 19, 0, p1Obj->sprite, 200, temp_surface);
		SDL_FreeSurface(temp_surface);

		p1Obj->sprite->direction = ANIM_RIGHT;
		p1Obj->sprite->anim_type = ANIM_TELEPORT;
		p1Obj->sprite->move_timer=getTimer()+17;
	} else {
		printf(">> game.h - loading p2 sprites...\n");


		sprintf(buffer, "%sdata/images/sprites/sprites_p2.png", FILEPATH);
		temp_surface = surfaceFromFile(buffer);
		//create_sprite(short int x, short int y, short int sp_w, short int sp_h, short int n, char filename[50], SDL_Surface *screen)

		struct player_struct *destPObj;

		if (game_config.two_players == 2) {
			printf(">> game.h - two-player mode\n");
			int p2n = add_player();
			p2Obj = getPlayerN(p2n);
			p2Obj->sprite = create_sprite(50, 0, 29, 32, game_screen);
			destPObj = p2Obj;
		} else {
			printf(">> game.h - one-player mode\n");
			int p1n = add_player();
			p1Obj = getPlayerN(p1n);
			p1Obj->sprite = create_sprite(20, 0, 29, 32, game_screen);
			destPObj = p1Obj;
			p2Obj = NULL;
		}

		destPObj->jump_max = 46;
		destPObj->shots_max = 6;
		sprintf(destPObj->name, "Betabot");
		sprintf(destPObj->face_filename, "betabot.png");

		//add_sprite(short int direction, short int anim_type, short int pos_x, short int pos_y, short int sprite_id)
		// STAND
				add_sprite(ANIM_RIGHT, ANIM_STAND, 3, 0, destPObj->sprite, 5000, temp_surface);
				add_sprite(ANIM_RIGHT, ANIM_STAND, 4, 0, destPObj->sprite, 500, temp_surface);
				add_sprite(ANIM_LEFT, ANIM_STAND, 3, 1, destPObj->sprite, 5000, temp_surface);
				add_sprite(ANIM_LEFT, ANIM_STAND, 4, 1, destPObj->sprite, 500, temp_surface);
		// WALK
				add_sprite(ANIM_RIGHT, ANIM_WALK, 6, 0, destPObj->sprite, 500, temp_surface);
				add_sprite(ANIM_RIGHT, ANIM_WALK, 7, 0, destPObj->sprite, 500, temp_surface);
				add_sprite(ANIM_RIGHT, ANIM_WALK, 8, 0, destPObj->sprite, 500, temp_surface);
				add_sprite(ANIM_LEFT, ANIM_WALK, 6, 1, destPObj->sprite, 500, temp_surface);
				add_sprite(ANIM_LEFT, ANIM_WALK, 7, 1, destPObj->sprite, 500, temp_surface);
				add_sprite(ANIM_LEFT, ANIM_WALK, 8, 1, destPObj->sprite, 500, temp_surface);
		// JUMP
				add_sprite(ANIM_RIGHT, ANIM_JUMP, 9, 0, destPObj->sprite, 500, temp_surface);
				add_sprite(ANIM_LEFT, ANIM_JUMP, 9, 1, destPObj->sprite, 500, temp_surface);
		// ATTACK
				add_sprite(ANIM_RIGHT, ANIM_ATTACK, 11, 0, destPObj->sprite, 500, temp_surface);
				add_sprite(ANIM_LEFT, ANIM_ATTACK, 11, 1, destPObj->sprite, 500, temp_surface);
		// ATTACK + JUMP
				add_sprite(ANIM_RIGHT, ANIM_JUMP_ATTACK, 10, 0, destPObj->sprite, 300, temp_surface);
				add_sprite(ANIM_LEFT, ANIM_JUMP_ATTACK, 10, 1, destPObj->sprite, 300, temp_surface);

		// ATTACK + WALK
				add_sprite(ANIM_RIGHT, ANIM_WALK_ATTACK, 12, 0, destPObj->sprite, 500, temp_surface);
				add_sprite(ANIM_RIGHT, ANIM_WALK_ATTACK, 13, 0, destPObj->sprite, 500, temp_surface);
				add_sprite(ANIM_RIGHT, ANIM_WALK_ATTACK, 14, 0, destPObj->sprite, 500, temp_surface);
				add_sprite(ANIM_LEFT, ANIM_WALK_ATTACK, 12, 1, destPObj->sprite, 500, temp_surface);
				add_sprite(ANIM_LEFT, ANIM_WALK_ATTACK, 13, 1, destPObj->sprite, 500, temp_surface);
				add_sprite(ANIM_LEFT, ANIM_WALK_ATTACK, 14, 1, destPObj->sprite, 500, temp_surface);
		// HIT
				add_sprite(ANIM_LEFT, ANIM_HIT, 15, 1, destPObj->sprite, 500, temp_surface);
				add_sprite(ANIM_RIGHT, ANIM_HIT, 15, 0, destPObj->sprite, 500, temp_surface);

		// TELEPORT
				add_sprite(ANIM_RIGHT, ANIM_TELEPORT, 0, 0, destPObj->sprite, 400, temp_surface);
				add_sprite(ANIM_RIGHT, ANIM_TELEPORT, 1, 0, destPObj->sprite, 300, temp_surface);
				add_sprite(ANIM_RIGHT, ANIM_TELEPORT, 2, 0, destPObj->sprite, 200, temp_surface);
		// STAIRS
				add_sprite(ANIM_RIGHT, ANIM_STAIRS, 17, 0, destPObj->sprite, 5000, temp_surface);
				add_sprite(ANIM_LEFT, ANIM_STAIRS, 17, 1, destPObj->sprite, 5000, temp_surface);
				add_sprite(ANIM_RIGHT, ANIM_STAIRS_SEMI, 18, 0, destPObj->sprite, 5000, temp_surface);
				add_sprite(ANIM_LEFT, ANIM_STAIRS_SEMI, 18, 1, destPObj->sprite, 5000, temp_surface);

		// stairs + move
				add_sprite(ANIM_RIGHT, ANIM_STAIRS_MOVE, 17, 0, destPObj->sprite, 200, temp_surface);
				add_sprite(ANIM_LEFT, ANIM_STAIRS_MOVE, 17, 0, destPObj->sprite, 200, temp_surface);
				add_sprite(ANIM_RIGHT, ANIM_STAIRS_MOVE, 17, 1, destPObj->sprite, 200, temp_surface);
				add_sprite(ANIM_LEFT, ANIM_STAIRS_MOVE, 17, 1, destPObj->sprite, 200, temp_surface);
		// stairs + attack
				add_sprite(ANIM_RIGHT, ANIM_STAIRS_ATTACK, 19, 0, destPObj->sprite, 200, temp_surface);
				add_sprite(ANIM_LEFT, ANIM_STAIRS_ATTACK, 19, 1, destPObj->sprite, 200, temp_surface);

				destPObj->sprite->direction = ANIM_RIGHT;
				destPObj->sprite->anim_type = ANIM_TELEPORT;
				destPObj->sprite->move_timer=getTimer()+17;
			SDL_FreeSurface(temp_surface);
        }


	sprintf(buffer, "%sdata/images/sprites/projectile_normal.png", FILEPATH);
	normal_projectile = surface_from_image(buffer);


	clear_area(game_screen, 0, 0, MAX_W, MAX_H, 0, 0, 0);
	sprintf(buffer, "%sdata/images/tilesets/hit.png", FILEPATH);

	hit_frame = create_animation_frame(buffer, 16, 16);
	hit_frame->duration = 300;

	clear_area(game_screen, 0, 0, MAX_W, MAX_H, 0, 0, 0);
	sprintf(buffer, "%sdata/images/tilesets/ready.png", FILEPATH);

	ready_frame = create_animation_frame(buffer, 60, 13);
	ready_frame->duration = 500;

	clear_area(game_screen, 0, 0, MAX_W, MAX_H, 0, 0, 0);
	sprintf(buffer, "%sdata/images/tilesets/explosion_16.png", FILEPATH);

	kill_frame = create_animation_frame(buffer, 16, 16);
	kill_frame->duration = 400;

	p1_warning = create_simple_sprite(16, 10);
	draw_text(0, 0, "P1", p1_warning->sprite);
	p2_warning = create_simple_sprite(16, 10);
	draw_text(0, 0, "P2", p2_warning->sprite);


	clear_area(game_screen, 0, 0, MAX_W, MAX_H, 0, 0, 0);
	drawMap(offscreen, 0);
	map_pos_x = 0;
	map_pos_y = 0;
	move_screen(game_screen, scrollX, scrollY);
	return 1;

}




short int checkStairs(const int px, const int py, const int pw, const int ph) {
	int map_tile_x, map_tile_y, diff_w;
	diff_w = (pw-16)*0.5;
	map_tile_x = (px+diff_w)/16;
	map_tile_y = (py+ph)/16;
	if (map.tiles[map_tile_x][map_tile_y].locked == 2) {
		return map_tile_x;
	}
	map_tile_x = (px+pw-diff_w)/16;
	if (map.tiles[map_tile_x][map_tile_y].locked == 2) {
		return map_tile_x;
	}
	return -1;
}

/*
test_map_colision - return values:
0 - free
1 - block X only
2 - block Y only
3 - block X and Y
*/
short int test_map_colision(struct player_struct *playerObj, const short int incx, const short int incy) {
	// test colision with objects
	//printf(">> test_map_colision.START\n");
	int res_colision_object = colision_player_object(playerObj, incx, incy);

	if (res_colision_object != 0) {
		//printf(">> test_map_colision - res_colision_object: %d\n", res_colision_object);
		return res_colision_object;
	}
    int px = playerObj->sprite->x;
    int py = playerObj->sprite->y;
    int pw = playerObj->sprite->w;
    int ph = playerObj->sprite->h;
    short int diff=0, i, map_tile_x, map_tile_y, map_tile_y_curr=0, diff_w=0, diff_h=0;
    short int block=0; // holds the result. 0 is no blocking, 1 is blocking x, 2 is blocking y, 3 is blocking both x and y
    struct simple_sprite *warning;
    int diff_players;
    struct player_struct *playerObjAux;
    // first, test for xinc

    if (pw > 21) {
        diff_w = abs(ph-21);
    }
    if (ph > PLAYER_H) {
        diff_h = abs(ph-PLAYER_H);
    }

	//printf("incx: %d, px: %d, map_pos_x: %d, scrollX: %d\n", incx, px, map_pos_x, scrollX);

    if (incx != 0) {
        if (game_config.two_players == 2) {
            if (playerObj == p1Obj) {
                playerObjAux = p2Obj;
            } else {
                playerObjAux = p1Obj;
            }
            //if ((incx > 0 && abs(playerObj->sprite->x-(px+incx+pw)) >= MAX_W) || (incx < 0 && abs(playerObj->sprite->x+playerObj->sprite->w-(px+incx)) >= MAX_W)) {
            diff_players = abs(abs(px+incx)-abs(playerObjAux->sprite->x));
            if (diff_players > MAX_W-pw) {
				if (playerObj == p1Obj) {
					warning = p2_warning;
				} else {
					warning = p1_warning;
				}
				show_simple_sprite(game_screen, warning, playerObjAux->sprite->x+4, playerObjAux->sprite->y-10);
				block = 1;
            }
        }
        if (incx > 0 && px+incx > MAP_W*16) {
                block = 1;
        } else if (incx < 0 && px+incx+map_pos_x <= 0) {
                block = 1;
        } else {
            if (incx > 0) {
                map_tile_x = (px+pw+incx-diff_w)/16;
            } else {
                map_tile_x = (px+incx+diff_w)/16;
            }
            map_tile_y = (py+diff_h)/16;
            diff = (py-(incy+1)+ph)/16-map_tile_y;
            for (i=0; i<=diff; i++) {
				// TODO DEAL WITH TERRAIN TYPE
				if (map.tiles[map_tile_x][map_tile_y+i].locked > 0 && map.tiles[map_tile_x][map_tile_y+i].locked != TERRAIN_DOOR && map.tiles[map_tile_x][map_tile_y+i].locked != TERRAIN_STAIR) {
                    block = 1;
                    //break;
				} else if (incx > 0 && map.tiles[map_tile_x][map_tile_y+i].locked == TERRAIN_DOOR) {
                    bossDoorHit(map_tile_x, map_tile_y+i, playerObj);
                    return 0;
				} else if (map.tiles[map_tile_x+i][map_tile_y].locked == TERRAIN_SPIKE) {
					if (playerObj->HP-4 > 0) {
						playerObj->HP -= 4;
					} else {
						playerObj->HP = 0;
					}
				}
            }
        }
    }

    if (incy != 0) {
            if (incy > 0 && py+incy+ph-6 >= MAX_H) {
                    if (block == 0) {
                            block = 2;
                    } else {
                            block = 3;
                    }
            } else if (incy < 0 && py+incy <= 0) {
                    if (block == 0) {
                            block = 2;
                    } else {
                            block = 3;
                    }
            } else {
                    if (incy > 0) {
                            map_tile_y = (py-1+ph+incy)/16;
                            map_tile_y_curr = (py-1+ph)/16;
                    } else {
                            map_tile_y = (py-1+incy)/16;
                    }
                    map_tile_x = (px+diff_w)/16;
                    diff = (px+pw-diff_w)/16-map_tile_x;
                    for (i=0; i<=diff; i++) {
							if (map.tiles[map_tile_x+i][map_tile_y].locked > 0 && map.tiles[map_tile_x][map_tile_y+i].locked != TERRAIN_STAIR) {
								// TODO DEAL WITH TERRAIN TYPE
								if (block == 0) {
									if (map.tiles[map_tile_x+i][map_tile_y].locked == TERRAIN_MOVE_LEFT) {
										if (PLATFORM_COUNTER < 4) {
											PLATFORM_COUNTER++;
										} else {
											playerObj->sprite->x -= 1;
											PLATFORM_COUNTER = 0;
										}
									} else if (map.tiles[map_tile_x+i][map_tile_y].locked == TERRAIN_MOVE_RIGHT) {
										if (PLATFORM_COUNTER < 4) {
											PLATFORM_COUNTER++;
										} else {
											playerObj->sprite->x += 1;
											PLATFORM_COUNTER = 0;
										}
									} else if (map.tiles[map_tile_x+i][map_tile_y].locked == TERRAIN_SPIKE) {
										if (playerObj->HP-4 > 0) {
											playerObj->HP -= 4;
										} else {
											playerObj->HP = 0;
										}
									}
									block = 2;
								} else {
									block = 3;
								}
								break;
                            } else if (incy > 0 && map.tiles[map_tile_x+i][map_tile_y_curr].locked != 2 && map.tiles[map_tile_x+i][map_tile_y].locked == 2) {
								if (block == 0) {
									block = 4;
								} else {
									block = 5;
								}
								break;
							} else if (map.tiles[map_tile_x+i][map_tile_y].locked == TERRAIN_DOOR) {
                                bossDoorHit(map_tile_x+i, map_tile_y, playerObj);
                            }
                    }
            }
    }
    return block;
}


short int test_map_teleport() {
	int i, k;
	int lim1, lim2, lim3, lim4;
	int diff_w;
	int temp_x, temp_y, temp_map_n=0, player_x=0, player_y, transition_type=0;
	struct player_struct *playerObj, *pObj2;
	int MUST_TELEPORT = 0;
	int teleport_n;
	int px, py, pw, ph;
	int player_in_n=0;
	struct simple_sprite *warning;

	for (k=0; k<game_config.two_players; k++) {
		playerObj = getPlayerN(k);
		px = playerObj->sprite->x;
		py = playerObj->sprite->y;
		pw = playerObj->sprite->w;
		ph = playerObj->sprite->h;

                diff_w = (pw-16)*0.5;
                px = px+(pw*0.5);
                py = py+(ph*0.5)+(ph*0.25);
		for (i=0; i<LINKS_NUMBER; i++) {
			if (game.map_links[i].map_origin != -1) {
				if ((game.map_links[i].map_origin == currentMap && game.map_links[i].link_pos.x != -1) || (game.map_links[i].map_dest == currentMap && game.map_links[i].link_bidi == 1 && game.map_links[i].link_dest.x != -1)) {
					if ((game.map_links[i].map_origin == currentMap && game.map_links[i].link_pos.x != -1)) {
						temp_x = game.map_links[i].link_pos.x;
						temp_y = game.map_links[i].link_pos.y;
						temp_map_n = game.map_links[i].map_dest;
						player_x = game.map_links[i].link_dest.x;
						player_y = game.map_links[i].link_dest.y;
						if (game.map_links[i].link_pos.y > game.map_links[i].link_dest.y) {
							transition_type = TRANSITION_TOP_TO_BOTTOM;
						} else if (game.map_links[i].link_pos.y < game.map_links[i].link_dest.y) {
							transition_type = TRANSITION_BOTTOM_TO_TOP;
						}
					} else {
						temp_x = game.map_links[i].link_dest.x;
						temp_y = game.map_links[i].link_dest.y;
						temp_map_n = game.map_links[i].map_origin;
						player_x = game.map_links[i].link_pos.x;
						player_y = game.map_links[i].link_pos.y;
						if (game.map_links[i].link_pos.y < game.map_links[i].link_dest.y) {
							transition_type = TRANSITION_TOP_TO_BOTTOM;
						} else if (game.map_links[i].link_pos.y > game.map_links[i].link_dest.y) {
							transition_type = TRANSITION_BOTTOM_TO_TOP;
						}
					}

					lim1 = temp_x*16;
					lim2 = ((temp_x+game.map_links[i].link_size)*16)+pw;
					lim3 = (temp_y)*16;
					lim4 = ((temp_y)*16)+16;
					if ((px >= lim1 && px <= lim2) && ((py > lim3 && py < lim4))) {
						if (playerObj->teleporter == -1) {
							MUST_TELEPORT++;
							teleport_n = i;
							player_in_n = k;
							break;
						} else {
							playerObj->teleporter = -1;
						}
					}
				}
			}
		}

		if (MUST_TELEPORT > 0 && MUST_TELEPORT != game_config.two_players) {
			if (player_in_n == 0) {
				playerObj = getPlayerN(1);
				warning = p2_warning;
			} else {
				playerObj = getPlayerN(0);
				warning = p1_warning;
			}
			show_simple_sprite(game_screen, warning, playerObj->sprite->x+4, playerObj->sprite->y-10);
			//show_simple_sprite(game_screen, p1_warning, 20, 20);
		} else if (MUST_TELEPORT == game_config.two_players) {
			//clear_all_projectiles(game_screen);
			remove_all_projectiles();
			// --------------------->>>>>>>>>>>>>>>>>>>>>>>>>>>>
			// TODO - define according to the condition, try to maintain it
			//playerObj->sprite->anim_type = ANIM_STAIRS;
			// --------------------->>>>>>>>>>>>>>>>>>>>>>>>>>>>
			int dest_x = (player_x*16)-scrollX;



			int max_pos_x = MAP_W*16-MAX_W;
			if (dest_x > max_pos_x) {
				dest_x = max_pos_x;
			}
			if (dest_x < 0) {
				dest_x = 0;
			}



			// must move the map, so that the dest position in screen is equal to player_real_pos_x
			int new_map_pos_x;
			int playerRealXPos = playerObj->sprite->x + map_pos_x;

			new_map_pos_x = ((player_x*16))-playerRealXPos;
			if (new_map_pos_x < 0) {
				new_map_pos_x = 0;
			} else if (new_map_pos_x > MAP_W*16) {
				new_map_pos_x = MAP_W*16;
			}

			int diff_h=6;

			if (playerObj->sprite->w > 30) {
				diff_h = abs(playerObj->sprite->h-30);
			}
			new_map_pos_x -= diff_h;

			transitionScreen(transition_type, temp_map_n, new_map_pos_x);

			map_pos_x = -new_map_pos_x;
			scrollX = 0;
			move_screen(game_screen, 0, 0);

			//loadMap(currentGame, temp_map_n);
			//drawMap(offscreen, 0);


			playerObj->sprite->x = playerRealXPos+new_map_pos_x;
			if (k == 0) {
				pObj2 = getPlayerN(1);
			} else {
				pObj2 = getPlayerN(0);
			}
			pObj2->sprite->x = playerRealXPos+new_map_pos_x;
			playerObj->teleporter = i;
			pObj2->teleporter = i;
			break;
		}
	}
	return 0;
}



void player_jump(struct player_struct *playerObj, char *myKeyState, int x_inc, int y_inc, const short int animation_st_type, const short int animation_atk_type) {
    int res=0, i;

    if (playerObj->sprite->anim_type == ANIM_TELEPORT) {
        return;
    }


    if (playerObj->sprite->anim_type == ANIM_JUMP_ATTACK) {
        if (getTimer() - playerObj->sprite->sprite_frames[playerObj->sprite->direction][playerObj->sprite->anim_type][playerObj->sprite->anim_pos].init > playerObj->sprite->sprite_frames[playerObj->sprite->direction][playerObj->sprite->anim_type][playerObj->sprite->anim_pos].duration - 1) {
            playerObj->sprite->anim_type = animation_st_type;
            playerObj->sprite->sprite_frames[playerObj->sprite->direction][playerObj->sprite->anim_type][playerObj->sprite->anim_pos].init = getTimer();
        }
    }
    // adjust speed. if more near jump max point, more slow
	int jump_speed;
    if (playerObj->sprite->frame_animation[ANIM_STATUS] != 2) {
		jump_speed = (playerObj->jump_max-playerObj->sprite->frame_animation[ANIM_PROCESS])/JUMP_SPEED_STEPS;
    } else {
        if (playerObj->sprite->frame_animation[ANIM_PROCESS] < playerObj->jump_mark) {
            jump_speed = (playerObj->jump_mark-playerObj->sprite->frame_animation[ANIM_PROCESS])/JUMP_SPEED_STEPS;
        } else {
			jump_speed = playerObj->jump_max/JUMP_SPEED_STEPS;
        }
    }
    if (jump_speed <= 0) {
        jump_speed = 1;
	} else if (jump_speed > MAX_JUMP_SPEED) {
		jump_speed = MAX_JUMP_SPEED;
    }
    if (y_inc > 0) {
        y_inc = jump_speed;
    } else {
        y_inc = -jump_speed;
    }

	res = test_map_colision(playerObj, x_inc, y_inc);
    // if step is greater than one and is falling (y_inc > 0) and blocked, try again with lower steps
    if (y_inc > 0 && (res == 3 || res == 2)) {
        int n=1;
        for (i=y_inc; i>0; i--) {
			res = test_map_colision(playerObj, x_inc, i);
            if (res != 2 && res != 3) {
                y_inc=i;
                break;
            }
            n++;
        }
    }


    if (playerObj->sprite->anim_type == ANIM_STAIRS || playerObj->sprite->anim_type == ANIM_STAIRS_SEMI || playerObj->sprite->anim_type == ANIM_STAIRS_MOVE || playerObj->sprite->anim_type == ANIM_STAIRS_ATTACK) {
        if (myKeyState[KEYJUMP]=='1') {
            playerObj->sprite->frame_animation[ANIM_STATUS] = 2;
            playerObj->sprite->frame_animation[ANIM_PROCESS] = 0;
            playerObj->sprite->anim_type = ANIM_JUMP;
            return;
        }
        return;
    }
    // JUMP - check if button was released
    if (myKeyState[KEYJUMP]=='0' && playerObj->jumpButtonReleased==1) {
            playerObj->jumpButtonReleased=0;
    }
    // jumping
    if (myKeyState[KEYJUMP]=='1' && playerObj->sprite->frame_animation[ANIM_STATUS] == 0 && playerObj->jumpButtonReleased == 0) {
            playerObj->sprite->frame_animation[ANIM_STATUS] = 1;
            playerObj->sprite->anim_type = ANIM_JUMP;
    // no gound, fall
    } else if (playerObj->sprite->frame_animation[ANIM_STATUS] == 0 && res != 2 && res != 3 && res != 4 && res != 5) {
            playerObj->sprite->frame_animation[ANIM_STATUS] = 2;
    // goind up in jump, free path
    } else if (playerObj->sprite->frame_animation[ANIM_STATUS] == 1 && res != 2 && res != 3) {
            // reached maximum on jump
			if (playerObj->sprite->frame_animation[ANIM_PROCESS] >= playerObj->jump_max) {
                    playerObj->sprite->frame_animation[ANIM_STATUS] = ANIM_JUMP;
                    playerObj->sprite->frame_animation[ANIM_PROCESS] = 0;
					playerObj->jump_mark = playerObj->jump_max;
            } else {
                    playerObj->sprite->frame_animation[ANIM_PROCESS] = playerObj->sprite->frame_animation[ANIM_PROCESS] + abs(y_inc);
            }
    // goind up in jump, hit something
    } else if (playerObj->sprite->frame_animation[ANIM_STATUS] == 1 && (res == 2 || res == 3)) {
            playerObj->sprite->frame_animation[ANIM_STATUS] = ANIM_JUMP;
            playerObj->sprite->frame_animation[ANIM_PROCESS] = 0;
            playerObj->jump_mark = playerObj->sprite->frame_animation[ANIM_PROCESS];
    // already falling, can fall more
    } else if (playerObj->sprite->frame_animation[ANIM_STATUS] == 2 && res != 2 && res != 3) {
            if (playerObj->sprite->anim_type != ANIM_JUMP && playerObj->sprite->anim_type != ANIM_JUMP_ATTACK) {
                    playerObj->sprite->anim_type = ANIM_JUMP;
            }
            // do nothing
    // already falling, hit the ground
    } else if (playerObj->sprite->frame_animation[ANIM_STATUS] == 2 && (res == 2 || res == 3)) {
            playerObj->sprite->frame_animation[ANIM_STATUS] = 0;
            playerObj->sprite->frame_animation[ANIM_PROCESS] = 0;
			play_sfx(SFX_PLAYER_JUMP);
            if (playerObj->sprite->anim_type == ANIM_JUMP_ATTACK) {
                    playerObj->sprite->anim_type = ANIM_STAND;
            }
    }
    // jumped over a stair
    if (playerObj->sprite->anim_type == ANIM_JUMP) {
            if (res == 4 || res == 5) {
                    playerObj->sprite->frame_animation[ANIM_STATUS] = 0;
                    playerObj->sprite->frame_animation[ANIM_PROCESS] = 0;
            }
    }
    if (y_inc != 0 && (res == 0 || res == 1)) {
		playerObj->sprite->y = playerObj->sprite->y + y_inc;
    }
}




short int player_movement(struct player_struct *playerObj, char *myKeyState) {
	short int x_inc=0;
	short int y_inc=0;
	short int step=MOVE_STEP;
	short int res;
	short int attacking=0;
	short int animation_st_type=ANIM_STAND;
	short int animation_atk_type=ANIM_ATTACK;

	// if was hit
	if (playerObj->sprite->anim_type == ANIM_HIT) {
		playerObj->sprite->frame_animation[ANIM_PROCESS] += 1;
		if (SDL_GetTicks() > playerObj->sprite->frame_animation[ANIM_PROCESS]) {
			playerObj->sprite->anim_type = ANIM_STAND;
			playerObj->sprite->frame_animation[ANIM_PROCESS] = 0;
			playerObj->sprite->frame_animation[ANIM_STATUS] = 0;
			playerObj->jumpButtonReleased=0;
			playerObj->hit = 0;
		} else {
			if (playerObj->sprite->direction == ANIM_LEFT) {
				x_inc = step;
			} else {
				x_inc = -step;
			}
			y_inc = step*2;
			res = test_map_colision(playerObj, x_inc, y_inc);
			//0 is no blocking, 1 is blocking x, 2 is blocking y, 3 is blocking both x and y
			if (res != 1 && res != 3) {
				playerObj->x = playerObj->x + x_inc;
				playerObj->sprite->x = playerObj->sprite->x + x_inc;
			}
			if (res != 2 && res != 3) {
				printf("+++ Y_INC 2\n");
				playerObj->y = playerObj->y + y_inc;
				playerObj->sprite->y = playerObj->sprite->y + y_inc;
			}
		}
		move_screen(game_screen, 0, 0);
		return 0;
	}


	// only move horizontaly is player is not on teleport
	if (playerObj->sprite->anim_type != ANIM_TELEPORT) {
		if (myKeyState[KEYX] == '1') {
			x_inc = step;
		} else if (myKeyState[KEYX] == '2') {
			x_inc = -step;
		}
	}
	// if player is not jumping or above/on a staircase, he is always trying to fall
	y_inc = step*2;
	//printf(">> 1 - p.move.x: %c, x_inc: %d\n", myKeyState[KEYX], x_inc);

	// JUMP - check if button was released
	if (myKeyState[KEYATTACK]=='0' && playerObj->attackButtonReleased==1) {
		playerObj->attackButtonReleased=0;
	}
	//verify if still not reached the jump maximum
	if (playerObj->sprite->anim_type == ANIM_TELEPORT) {
		y_inc = step*2;
	} else if (myKeyState[KEYJUMP]=='1' && playerObj->sprite->frame_animation[ANIM_STATUS] == 0 && playerObj->jumpButtonReleased == 0) {
		playerObj->jumpButtonReleased=1;
		y_inc = -step*2;
		playerObj->sprite->anim_type = ANIM_JUMP;
		playerObj->sprite->frame_animation[ANIM_STATUS] = 1;
		playerObj->sprite->frame_animation[ANIM_PROCESS] += step;
	} else if (playerObj->sprite->frame_animation[ANIM_STATUS] == 2) {
		// can fall
		y_inc = step*2;
	} else if (playerObj->sprite->frame_animation[ANIM_STATUS] == 1) {
		// can fall
		y_inc = -step*2;
	}

	if (x_inc != 0 || y_inc != 0) {
		res = test_map_colision(playerObj, x_inc, y_inc);
		test_map_teleport();
		if (playerObj->sprite->anim_type == ANIM_TELEPORT && res != 2 && res != 3) {
			playerObj->sprite->y = playerObj->sprite->y + y_inc;
		}
		if (x_inc != 0 && (playerObj->sprite->anim_type == ANIM_STAIRS || playerObj->sprite->anim_type == ANIM_STAIRS_MOVE || playerObj->sprite->anim_type == ANIM_STAIRS_SEMI || playerObj->sprite->anim_type == ANIM_STAIRS_ATTACK)) {
			if (x_inc < 0) {
				playerObj->sprite->direction = ANIM_LEFT;
			} else {
				playerObj->sprite->direction = ANIM_RIGHT;
			}
			animation_atk_type = ANIM_STAIRS_ATTACK;
			animation_st_type = ANIM_STAIRS;
		} else if (x_inc == 0 && (playerObj->sprite->anim_type == ANIM_STAIRS || playerObj->sprite->anim_type == ANIM_STAIRS_MOVE || playerObj->sprite->anim_type == ANIM_STAIRS_SEMI || playerObj->sprite->anim_type == ANIM_STAIRS_ATTACK)) {
			animation_atk_type = ANIM_STAIRS_ATTACK;
			animation_st_type = ANIM_STAIRS;
		} else if (x_inc != 0 && (res == 0 || res == 2 || res == 4)) {
			//printf(">> 3 - p.move.x: %c, x_inc: %d\n", myKeyState[KEYX], x_inc);
			if (x_inc < 0) {
				playerObj->sprite->direction = ANIM_LEFT;
			} else {
				playerObj->sprite->direction = ANIM_RIGHT;
			}
			playerObj->sprite->x = playerObj->sprite->x + x_inc;
			animation_st_type = ANIM_WALK;
			animation_atk_type = ANIM_WALK_ATTACK;
		} else {
			animation_atk_type = ANIM_ATTACK;
			animation_st_type = ANIM_STAND;
		}



		// checks if attack must be finished
		if (playerObj->sprite->anim_type == ANIM_WALK_ATTACK || playerObj->sprite->anim_type == ANIM_JUMP_ATTACK ||  playerObj->sprite->anim_type == ANIM_ATTACK || playerObj->sprite->anim_type == ANIM_STAIRS_ATTACK) {
			if (getTimer() - playerObj->sprite->sprite_frames[playerObj->sprite->direction][playerObj->sprite->anim_type][playerObj->sprite->anim_pos].init > playerObj->sprite->sprite_frames[playerObj->sprite->direction][playerObj->sprite->anim_type][playerObj->sprite->anim_pos].duration - 1) {
				playerObj->sprite->anim_type = animation_st_type;
				playerObj->sprite->sprite_frames[playerObj->sprite->direction][playerObj->sprite->anim_type][playerObj->sprite->anim_pos].init = getTimer();
			}
		} else if (playerObj->sprite->anim_type != ANIM_TELEPORT && playerObj->sprite->anim_type != ANIM_STAIRS && playerObj->sprite->anim_type != ANIM_STAIRS_SEMI && playerObj->sprite->anim_type != ANIM_STAIRS_MOVE && playerObj->sprite->anim_type != ANIM_STAIRS_ATTACK && playerObj->sprite->frame_animation[ANIM_STATUS] == 0 && playerObj->sprite->anim_type != animation_st_type) {
			playerObj->sprite->anim_type = animation_st_type;
		}
		// check if player is attacking
                if (playerObj->sprite->anim_type != ANIM_TELEPORT && execute_attack(playerObj, myKeyState)) {
			attacking = 1;
		} else {
			if (myKeyState[KEYATTACK]=='0' && playerObj->attackButtonReleased==1) {
				playerObj->attackButtonReleased=0;
			}
			attacking = 0;
		}

		// teleporting end
		if (playerObj->sprite->anim_type == ANIM_TELEPORT && (res == 2 || res == 3)) {
			if (attacking == 1) {
				playerObj->sprite->sprite_frames[playerObj->sprite->direction][playerObj->sprite->anim_type][playerObj->sprite->anim_pos].init = getTimer();
				playerObj->sprite->anim_type = animation_atk_type;
			} else {
				playerObj->sprite->anim_type = animation_st_type;
			}
			// TODO - must set the two players to stand in order to show the dialog
			playerObj->sprite->frame_animation[ANIM_STATUS] = 0;
			playerObj->sprite->frame_animation[ANIM_PROCESS] = 0;
			move_screen(game_screen, 0, 0);
			show_sprite(playerObj->sprite, game_screen);
			if (stage_start == 0) {
				show_dialog(STAGE_N, 0);
			}
		} else {
			player_jump(playerObj, myKeyState, x_inc, y_inc, animation_st_type, animation_atk_type);
			if (attacking == 1) {
				playerObj->sprite->sprite_frames[playerObj->sprite->direction][playerObj->sprite->anim_type][playerObj->sprite->anim_pos].init = getTimer();
				if (playerObj->sprite->anim_type == ANIM_STAIRS || playerObj->sprite->anim_type == ANIM_STAIRS_SEMI || playerObj->sprite->anim_type == ANIM_STAIRS_MOVE || playerObj->sprite->anim_type == ANIM_STAIRS_ATTACK) {
					playerObj->sprite->anim_type = ANIM_STAIRS_ATTACK;
					playerObj->sprite->frame_animation[ANIM_STATUS] = 0;
					playerObj->sprite->frame_animation[ANIM_PROCESS] = 0;
				} else if (playerObj->sprite->frame_animation[ANIM_STATUS] != 0) {
					playerObj->sprite->anim_type = ANIM_JUMP_ATTACK;
				} else {
					playerObj->sprite->anim_type = animation_atk_type;
					playerObj->sprite->frame_animation[ANIM_STATUS] = 0;
					playerObj->sprite->frame_animation[ANIM_PROCESS] = 0;
				}

			}
		}
		if (res != 3 && res != 5) {
			checkScrolling(x_inc, y_inc);
		} else {
			move_screen(game_screen, 0, 0);
		}
		y_inc = 1;
		// check if out of stairs
		if (playerObj->sprite->anim_type == ANIM_STAIRS || playerObj->sprite->anim_type == ANIM_STAIRS_SEMI || playerObj->sprite->anim_type == ANIM_STAIRS_MOVE || playerObj->sprite->anim_type == ANIM_STAIRS_ATTACK) {
			if (checkStairs(playerObj->sprite->x, playerObj->sprite->y-y_inc, playerObj->sprite->w, playerObj->sprite->h) == -1 && checkStairs(playerObj->sprite->x, playerObj->sprite->y-y_inc, playerObj->sprite->w, playerObj->sprite->h) == -1) {
				playerObj->sprite->anim_type = ANIM_JUMP;
			}
		}
		if (myKeyState[KEYY]=='1') {
			res = checkStairs(playerObj->sprite->x, playerObj->sprite->y+y_inc, playerObj->sprite->w, playerObj->sprite->h);
			if (res != -1) {
				if (checkStairs(playerObj->sprite->x, playerObj->sprite->y-y_inc-4, playerObj->sprite->w, playerObj->sprite->h) == -1) {
					playerObj->sprite->anim_type = ANIM_STAIRS_SEMI;
				} else {
					playerObj->sprite->anim_type = ANIM_STAIRS_MOVE;
				}
				playerObj->sprite->x = res*16-6;
				playerObj->sprite->y = playerObj->sprite->y + y_inc;
				test_map_teleport();
			} else {
				if (playerObj->sprite->anim_type == ANIM_STAIRS || playerObj->sprite->anim_type == ANIM_STAIRS_SEMI || playerObj->sprite->anim_type == ANIM_STAIRS_MOVE || playerObj->sprite->anim_type == ANIM_STAIRS_ATTACK) {
					playerObj->sprite->anim_type = ANIM_STAND;
				}
			}
		} else if (myKeyState[KEYY]=='2') {
			res = checkStairs(playerObj->sprite->x, playerObj->sprite->y-y_inc, playerObj->sprite->w, playerObj->sprite->h);
			if (res != -1) {
                                if (checkStairs(playerObj->sprite->x, playerObj->sprite->y-y_inc-(playerObj->sprite->h*0.5), playerObj->sprite->w, playerObj->sprite->h) == -1) {
					playerObj->sprite->anim_type = ANIM_STAIRS_SEMI;
				} else {
					playerObj->sprite->anim_type = ANIM_STAIRS_MOVE;
				}
				playerObj->sprite->x = res*16-6;
				if (playerObj->sprite->y - y_inc + TILE_SIZE >= 0) {
					playerObj->sprite->y = playerObj->sprite->y - y_inc;
					test_map_teleport();
				}

			} else {
				if (playerObj->sprite->anim_type == ANIM_STAIRS || playerObj->sprite->anim_type == ANIM_STAIRS_SEMI || playerObj->sprite->anim_type == ANIM_STAIRS_MOVE || playerObj->sprite->anim_type == ANIM_STAIRS_ATTACK) {
					playerObj->sprite->anim_type = ANIM_STAND;
					playerObj->sprite->anim_pos = 0;
				}
			}
		} else if (playerObj->sprite->anim_type == ANIM_STAIRS_MOVE) {
			playerObj->sprite->anim_type = ANIM_STAIRS;
			playerObj->sprite->anim_pos = 0;
		}

	}
	return 1;
}

