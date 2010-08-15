#ifndef NPCS_H
#define NPCS_H

#define IA_STAND 0
#define IA_WAIT 1
#define IA_FOLLOW 2
#define IA_ZIGZAG 3
#define IA_SIDETOSIDE 4
#define IA_SHOT_RAINBOW 5 // for daisiebot, shot rainbow power
#define IA_CROSS_SCREEN 6 // walk till reach the other side or hit a wall
#define IA_SHOT_FLOWER 7 // for daisiebot, shot flower
#define IA_WAIT_TIME 8

#define SHOT_ARC 0
#define SHOT_PROGRESSIVE 1


void show_npc_sprite(SDL_Surface *screen, struct npc_struct *temp) {
	// checks if the NPC is near the screen to show it
	if (temp->HP > 0 && temp->x+16 >= abs(map_pos_x) && temp->x-16 <= abs(map_pos_x)+RES_W) {
		SDL_Rect src, dest;

		// copia sprite para a tela
		src.x = 0;
		src.y = 0;
		src.w = temp->sprite_list->w;
		src.h = temp->sprite_list->h;
		// área da colagem
		dest.x = (temp->x + map_pos_x);
		dest.y = (temp->y + map_pos_y);
		dest.w = temp->sprite_list->w;
		dest.h = temp->sprite_list->h;

		// verifica se o frame da animação existe, caso contrário, usa o primeiro (0) da lista
		//printf("++ graphics.h::show_npc_sprites - direction: %d, type: %d, pos: %d\n", temp->sprite->direction, temp->sprite->anim_type,temp->sprite->anim_pos);
		if (temp->sprite_list->sprite_frames[temp->sprite_list->direction][temp->sprite_list->anim_type][temp->sprite_list->anim_pos].frame == NULL) {
			//printf("++ graphics.h::show_npc_sprites - frame NULL\n");
			if (temp->sprite_list->sprite_frames[temp->sprite_list->direction][temp->sprite_list->anim_type][0].frame != NULL) {
				//printf("++ graphics.h::show_npc_sprites - reset to pos ZERO\n");
				temp->sprite_list->anim_pos=0;
			} else {
				//printf("DEBUG - erro: Não achou frame: direction: %d,  type: %d, pos: %d\n", temp->sprite_list->direction, temp->sprite_list->anim_type, temp->sprite_list->anim_pos);
				temp->sprite_list->anim_type = 0;
				temp->sprite_list->direction = 0;
				temp->sprite_list->anim_pos = 0;
				//return;
			}
		}
		SDL_BlitSurface(temp->sprite_list->sprite_frames[temp->direction][temp->sprite_list->anim_type][temp->sprite_list->anim_pos].frame, &src, screen, &dest);
		// avança a animação
		if (getTimer() - temp->sprite_list->sprite_frames[temp->sprite_list->direction][temp->sprite_list->anim_type][temp->sprite_list->anim_pos].init > abs(temp->sprite_list->sprite_frames[temp->sprite_list->direction][temp->sprite_list->anim_type][temp->sprite_list->anim_pos].duration)) {
			if (temp->sprite_list->sprite_frames[temp->sprite_list->direction][temp->sprite_list->anim_type][temp->sprite_list->anim_pos+1].frame != NULL) {
				temp->sprite_list->anim_pos++;
				// if is last item of this anim_type, and NPC shoots, must shoot
				if (temp->sprite_list->sprite_frames[temp->sprite_list->direction][temp->sprite_list->anim_type][temp->sprite_list->anim_pos+1].frame == NULL) {
					// face to the side the player 1 is - TODO - choose a player with random
					if (temp->can_shoot == 1) {
						if (temp->direction == ANIM_LEFT && temp->x < p1Obj->sprite->x) {
							temp->direction = ANIM_RIGHT;
						} else if (temp->direction == ANIM_RIGHT && temp->x > p1Obj->sprite->x) {
							temp->direction = ANIM_LEFT;
						}
						throw_projectile_npc(temp);
					}
				}
			// reseta animação
			} else {
				temp->sprite_list->anim_pos=0;
				if (temp->sprite_list->anim_type == ANIM_TURN) {
					if (temp->direction == ANIM_LEFT) {
						temp->direction = ANIM_RIGHT;
					} else {
						temp->direction = ANIM_LEFT;
					}
					temp->sprite_list->anim_type = ANIM_STAND;
				}
			}
			temp->sprite_list->sprite_frames[temp->sprite_list->direction][temp->sprite_list->anim_type][temp->sprite_list->anim_pos].init=getTimer();
		}
	}
}



void move_npc(struct npc_struct *temp_npc) {
	int mapScrollX;
	// only move npcs that are in the current screen and are alive
	/*
	if (scrollX >= 0) {
		mapScrollX = scrollX;
	} else {
		mapScrollX = MAP_W*TILE_SIZE -abs(scrollX) - MAX_W;
	}
	*/

	//printf(">> move_npc - map_pos_x: %d\n", map_pos_x);

	/*
	if (map_pos_x < 0) {
		mapScrollX = -map_pos_x;
	} else {
		//mapScrollX = MAP_W*TILE_SIZE + map_pos_x - MAX_W;
		mapScrollX = -map_pos_x;
	}
	*/
	mapScrollX = -map_pos_x;

	//printf(">> move_npc - temp_npc->name: %s, temp_npc->HP: %d, temp_npc->x: %d, mapScrollX: %d, mapScrollX+RES_W: %d\n", temp_npc->name, temp_npc->HP, temp_npc->x, mapScrollX, (mapScrollX+RES_W));

	//>> move_npc - temp_npc->name: Daisie Bot, temp_npc->HP: 15, temp_npc->x: -1, mapScrollX: 0, mapScrollX+RES_W: 320

	if (temp_npc->HP > 0 && temp_npc->x >= mapScrollX-TILE_SIZE*2 && temp_npc->x <= mapScrollX+RES_W+TILE_SIZE*2) {
		//printf(">> move_npc - temp_npc->name: %s should move\n", temp_npc->name);
		if (temp_npc->is_boss == 1) {
			//printf(">> move_npc - boss IA\n");
			if (strstr(temp_npc->name, "Daisie")) {
				//printf(">> move_npc - boss IA - DAISIEBOT\n");
				execIADaisiebot(temp_npc);
			}
		} else {
			if (temp_npc->IA == IA_ZIGZAG) {
				if (temp_npc->move_info.time < getTimer()) {
					if (temp_npc->sprite_list->anim_type != ANIM_TURN) {
						if (temp_npc->direction == ANIM_LEFT) {
							temp_npc->x -= NPC_STEP;
						} else {
							temp_npc->x += NPC_STEP;
						}
						temp_npc->move_info.distance += NPC_STEP;
					}
					temp_npc->move_info.time = getTimer()+10;
					if (temp_npc->move_info.distance > 80) {
						temp_npc->sprite_list->anim_type = ANIM_TURN;
						temp_npc->sprite_list->anim_pos = 0;
						temp_npc->move_info.distance = 0;
						temp_npc->move_info.time = getTimer()+200;
					}
				}
			}
		}
	}
}

void shot_rainbow(struct npc_struct *temp_npc) {
	if (temp_npc->projectile.x != -1 && temp_npc->projectile.y != -1) {
		printf(">> shot_rainbow() - can't start\n");
		return;
	}
	char tempBuffer[255];

	printf(">> shot rainbow\n");
	temp_npc->projectile.type = SHOT_ARC;
	temp_npc->projectile.direction = temp_npc->direction;
	temp_npc->projectile.x = temp_npc->x;
	temp_npc->projectile.y = temp_npc->y + temp_npc->sprite_list->w;
	if (temp_npc->direction == ANIM_LEFT) {
		temp_npc->projectile.x0 = temp_npc->x - RES_W/3;
	} else {
		temp_npc->projectile.x0 = temp_npc->x + RES_W/3;
	}
	temp_npc->projectile.y0 = temp_npc->projectile.y;
	temp_npc->projectile.y1 = temp_npc->projectile.y;
	sprintf(tempBuffer, "%sdata/images/projectiles/rainbow.png", FILEPATH);
	temp_npc->projectile.sprite = surface_from_image(tempBuffer);
	temp_npc->projectile.timer = getTimer() + 10;
}


void anim_arc_projectile(struct npc_struct *temp_npc) {
	int tempY, diffY;
	//(X -Xo)² + (Y- Yo)² = R²
	//(x - a)2 + (y - b)2 = r2
	// y - y0 = raiz(raio² - (x-x0)²);
	//// y = raiz(raio² - (x-x0)²) + y0;
	if (temp_npc->projectile.x != -1 && temp_npc->projectile.y != -1) {
		printf(">> anim_arc_projectile.START\n");
		if (temp_npc->projectile.timer > getTimer()) {
			copy_area(temp_npc->projectile.sprite, 0, 0, temp_npc->projectile.sprite->w, temp_npc->projectile.sprite->h, temp_npc->projectile.x+map_pos_x, temp_npc->projectile.y1, game_screen);
			return;
		}
		tempY = temp_npc->projectile.y;

		if (temp_npc->projectile.direction == ANIM_LEFT) {
			temp_npc->projectile.x-= MOVE_STEP;
		} else {
			temp_npc->projectile.x+= MOVE_STEP;
		}

		int part1, part2, part3;
		part1 = pow((RES_W/3),2);
		part2 = pow((temp_npc->projectile.x - temp_npc->projectile.x0), 2);
		part3 = temp_npc->projectile.y0;
		//printf(">> part1: %d, temp_npc->projectile.x: %d, temp_npc->projectile.x0: %d, part2: %d, part3: %d\n", part1, temp_npc->projectile.x, temp_npc->projectile.x0, part2, part3);

		temp_npc->projectile.y = sqrt(part1 - part2) + part3;
		diffY = tempY-temp_npc->projectile.y;

		// check colision
		//colid_enemy = check_colision_enemy(temp_list->x - map_pos_x, temp_list->y - map_pos_y, 4, 4, temp_list->speed, 0, temp_list->owner);
		//short int check_colision_enemy(const short int obj_x, const short int obj_y, const short int obj_w, const short int obj_h, const short int x_inc, const short int y_inc, const short int owner) {
		int colid_enemy = check_colision_enemy(temp_npc->projectile.x, temp_npc->projectile.y1, temp_npc->projectile.sprite->w, temp_npc->projectile.sprite->h, MOVE_STEP, diffY, PROJECTILE_NPC);
		if (colid_enemy > 0) {
			struct player_struct *playerObj;
			playerObj = getPlayerN(colid_enemy - 1);
			if (playerObj->hit_timer < getTimer() && playerObj->hit != 1) {
				playerObj->hit = 1;
				playerObj->hit_timer = getTimer()+HIT_INVENCIBLE_TIME;
				playerObj->HP = playerObj->HP - 1;
				playerObj->sprite->anim_type = ANIM_HIT;
				playerObj->sprite->frame_animation[ANIM_PROCESS] = SDL_GetTicks() + 300;
				int diffx = (playerObj->sprite->w - 16) *0.5;
				int diffy = (playerObj->sprite->h - 16) *0.5;
				create_hit_animation(playerObj->sprite->x + diffx, playerObj->sprite->y + diffy);
				play_sfx(SFX_PLAYER_HIT);
			}
			temp_npc->projectile.x = -1;
			temp_npc->projectile.y = -1;
			SDL_FreeSurface(temp_npc->projectile.sprite);
			return;
		}


		temp_npc->projectile.y1 += diffY;
		if (temp_npc->projectile.y < 0) {
			temp_npc->projectile.x = -1;
			temp_npc->projectile.y = -1;
			SDL_FreeSurface(temp_npc->projectile.sprite);
			return;
		} else {
			temp_npc->projectile.timer = getTimer() + 10;
			copy_area(temp_npc->projectile.sprite, 0, 0, temp_npc->projectile.sprite->w, temp_npc->projectile.sprite->h, temp_npc->projectile.x+map_pos_x, temp_npc->projectile.y1, game_screen);
		}
	}
}

void anim_npc_projectile(struct npc_struct *temp_npc) {
	if (temp_npc->projectile.type == SHOT_PROGRESSIVE) {
		anim_progressive_projectile(temp_npc);
	} else if (temp_npc->projectile.type == SHOT_ARC) {
		anim_arc_projectile(temp_npc);
	}
}

void execIADaisiebot(struct npc_struct *temp_npc) {
	//printf(">> execIADaisiebot.START, temp_npc->projectile.type: %d\n", temp_npc->projectile.type);

	unsigned short int shot_type=IA_SHOT_RAINBOW;

	if (temp_npc->move_info.status == IA_WAIT_TIME) {
		if (temp_npc->timer < getTimer()) {
			temp_npc->move_info.status = IA_STAND;
		} else {
			return;
		}
	}

	// stand -> shot rainbow -> cross screen -> use flowers
	if (temp_npc->move_info.status == IA_STAND) {
		temp_npc->move_info.status = IA_CROSS_SCREEN;
		return;
	}

	if (temp_npc->move_info.status == IA_SHOT_RAINBOW) {
		shot_rainbow(temp_npc);
		temp_npc->move_info.status = IA_CROSS_SCREEN;
		temp_npc->move_info.initial_position.x = temp_npc->x;
		temp_npc->move_info.initial_position.y = temp_npc->y;
		temp_npc->move_info.status = IA_WAIT_TIME;
		temp_npc->timer = getTimer()+300;
	}

	if (temp_npc->move_info.status == IA_SHOT_FLOWER) {
		shot_flower(temp_npc);
		temp_npc->projectile.timer = getTimer()+60;
		temp_npc->move_info.initial_position.x = temp_npc->x;
		temp_npc->move_info.initial_position.y = temp_npc->y;
		temp_npc->move_info.status = IA_WAIT_TIME;
		temp_npc->timer = getTimer()+3000;
	}

	// TODO: move to generic npc, once more will use it
	if (temp_npc->move_info.status == IA_CROSS_SCREEN) {
		// check if must stop/invert
		//printf(">> execIADaisiebot.MOVE\n");
		if (temp_npc->move_info.time <= getTimer()) {
			temp_npc->move_info.time = getTimer() + 10;
			if (temp_npc->direction == ANIM_LEFT) {
				if (temp_npc->x-NPC_STEP > 0) {
					temp_npc->x-= NPC_STEP;
				} else {
					IAInvertDirection(temp_npc);
					if (shot_type == IA_SHOT_RAINBOW) {
						shot_type = IA_SHOT_FLOWER;
					} else {
						shot_type = IA_SHOT_RAINBOW;
					}
					temp_npc->move_info.status = shot_type;
				}
			} else {
				if (temp_npc->x+NPC_STEP < RES_W) {
					temp_npc->x+= NPC_STEP;
				} else {
					printf(">> IA Invert 2\n");
					IAInvertDirection(temp_npc);
					temp_npc->move_info.status = shot_type;
				}
			}
		}
	}
}


void IAInvertDirection(struct npc_struct *temp_npc) {
	if (temp_npc->direction == ANIM_LEFT) {
		temp_npc->direction = ANIM_RIGHT;
	} else {
		temp_npc->direction = ANIM_LEFT;
	}
	temp_npc->move_info.status = IA_STAND;
}


int check_projectile_colision(struct npc_struct *temp_npc, int x, int y, int xinc, int yinc, int w, int h) {
	// check colision
	//colid_enemy = check_colision_enemy(temp_list->x - map_pos_x, temp_list->y - map_pos_y, 4, 4, temp_list->speed, 0, temp_list->owner);
	//short int check_colision_enemy(const short int obj_x, const short int obj_y, const short int obj_w, const short int obj_h, const short int x_inc, const short int y_inc, const short int owner) {
	int colid_enemy = check_colision_enemy(x, y, w, h, xinc, yinc, PROJECTILE_NPC);
	if (colid_enemy > 0) {
		struct player_struct *playerObj;
		playerObj = getPlayerN(colid_enemy - 1);
		if (playerObj->hit_timer < getTimer() && playerObj->hit != 1) {
			playerObj->hit = 1;
			playerObj->hit_timer = getTimer()+HIT_INVENCIBLE_TIME;
			playerObj->HP = playerObj->HP - 1;
			playerObj->sprite->anim_type = ANIM_HIT;
			playerObj->sprite->frame_animation[ANIM_PROCESS] = SDL_GetTicks() + 300;
			int diffx = (playerObj->sprite->w - 16) *0.5;
			int diffy = (playerObj->sprite->h - 16) *0.5;
			create_hit_animation(playerObj->sprite->x + diffx, playerObj->sprite->y + diffy);
			play_sfx(SFX_PLAYER_HIT);
		}
		temp_npc->projectile.x = -1;
		temp_npc->projectile.y = -1;
		SDL_FreeSurface(temp_npc->projectile.sprite);
		return 1;
	}
	return 0;
}


void shot_flower(struct npc_struct *temp_npc) {
	printf(">> shot_flower()\n");
	if (temp_npc->projectile.x != -1 && temp_npc->projectile.y != -1) {
		printf(">> shot_flower() - can't start\n");
		return;
	}
	char tempBuffer[255];

	temp_npc->projectile.type = SHOT_PROGRESSIVE;
	temp_npc->projectile.direction = temp_npc->direction;
	temp_npc->projectile.x = temp_npc->x;
	sprintf(tempBuffer, "%sdata/images/projectiles/flower.png", FILEPATH);
	temp_npc->projectile.sprite = surface_from_image(tempBuffer);

	temp_npc->projectile.x = temp_npc->x + temp_npc->sprite_list->w/2;
	temp_npc->projectile.y = temp_npc->y + temp_npc->sprite_list->h - temp_npc->projectile.sprite->h/2;
	temp_npc->projectile.x0 = temp_npc->projectile.x;
	temp_npc->projectile.y0 = temp_npc->projectile.y;
	temp_npc->projectile.timer = getTimer() + 30;
	printf(">> shot_flower() - x: %d, y: %d\n", temp_npc->projectile.x, temp_npc->projectile.y);
}

void anim_progressive_projectile(struct npc_struct *temp_npc) {
	if (temp_npc->projectile.x == -1 && temp_npc->projectile.y == -1) {
		return;
	}
	//printf(">> anim_progressive_projectile() - x: %d, y: %d, status0: %d\n", temp_npc->projectile.x, temp_npc->projectile.y, temp_npc->projectile.status0);
	int frameW = temp_npc->projectile.sprite->w/5;
	int frameH = temp_npc->projectile.sprite->h/2;


	if (temp_npc->projectile.timer > getTimer()) {
		//printf("copy_area A - dest.x: %d, dest.y: %d\n", temp_npc->projectile.x, temp_npc->projectile.y);
		copy_area(temp_npc->projectile.sprite, temp_npc->projectile.status0*(frameW), 0, frameW, frameH, temp_npc->projectile.x+map_pos_x, temp_npc->projectile.y, game_screen);
		return;
	}


	if (check_projectile_colision(temp_npc, temp_npc->projectile.x, temp_npc->projectile.y, 0, 0, frameW, frameH)) {
		return;
	}

	int diffX = abs(temp_npc->projectile.x-temp_npc->projectile.x0);
	if (diffX < -TILE_SIZE || diffX > RES_W+TILE_SIZE) {
		//printf("*** destroy projectile\n");
		temp_npc->projectile.x = -1;
		temp_npc->projectile.y = -1;
		SDL_FreeSurface(temp_npc->projectile.sprite);
		return;
	}
	//printf("copy_area B - dest.x: %d, dest.y: %d, temp_npc->projectile.status0: %d\n", temp_npc->projectile.x, temp_npc->projectile.y, temp_npc->projectile.status0);
	copy_area(temp_npc->projectile.sprite, temp_npc->projectile.status0*(frameW), 0, frameW, frameH, temp_npc->projectile.x+map_pos_x, temp_npc->projectile.y, game_screen);

	temp_npc->projectile.timer = getTimer() + 120;

	if (temp_npc->projectile.status0 == 4) {
		temp_npc->projectile.status1 = 1;
	} else if (temp_npc->projectile.status0 == 0) {
		if (temp_npc->projectile.direction == ANIM_LEFT) {
			temp_npc->projectile.x-= TILE_SIZE*2;
		} else {
			temp_npc->projectile.x+= TILE_SIZE*2;
		}
		temp_npc->projectile.status1 = 0;
	}
	if (temp_npc->projectile.status1 == 0) {
		temp_npc->projectile.status0++;
	} else {
		temp_npc->projectile.status0--;
	}
}



#endif // NPCS_H


