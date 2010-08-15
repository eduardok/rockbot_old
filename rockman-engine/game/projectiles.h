//TODO checar mudanças, tem bastante coisa para ser concertada;
#include <alloca.h>
#ifndef PROJECTILES_H
#define PROJECTILES_H

#define PROJECTILE_PLAYER 0
#define PROJECTILE_NPC 1


short int check_colision_enemy(const short int obj_x, const short int obj_y, const short int obj_w, const short int obj_h, const short int x_inc, const short int y_inc, const short int owner) {
	struct pos p1, p2, p3, p4, npc1, npc2, npc3, npc4;
	struct player_struct *temp_player;
	struct npc_struct *temp_npc;
	short int i;
	int mapScrollX;
        //short int reduce = (obj_w-16)*0.5;
	short int reduce = 0;

	//printf(">>> check_colision_enemy - obj_x: %d, obj_y: %d, obj_w: %d, obj_h: %d, x_inc: %d, y_inc: %d\n", obj_x, obj_y, obj_w, obj_h, x_inc, y_inc);

	if (scrollX >= 0) {
		mapScrollX = scrollX;
	} else {
		mapScrollX = MAP_W*TILE_SIZE -abs(scrollX) - MAX_W;
	}


	p1.x = obj_x + x_inc + reduce;
	p1.y = obj_y + y_inc;

	// ponto 2, baixo/esquerda
	p2.x = obj_x + x_inc + reduce;
	p2.y = obj_y + y_inc + obj_h;

	// ponto 3, topo/direita
	p3.x = obj_x + x_inc + obj_w - reduce;
	p3.y = obj_y + y_inc;

	// ponto 4, baixo/direita
	p4.x = obj_x + x_inc + obj_w - reduce;
	p4.y = obj_y + y_inc + obj_h;

	if (owner == PROJECTILE_PLAYER) {
		// check colision with NPCs
		temp_npc = npc_list;
		//printf("DEBUG.check_colision - NPC search start\n");
		i = 1;
		while (temp_npc != NULL) {
			//printf("DEBUG.check_colision - NPC counter\n");
			if (temp_npc->HP > 0) {
				npc1.x = temp_npc->x;
				npc1.y = temp_npc->y;
				npc2.x = temp_npc->x + temp_npc->sprite_list->w;
				npc2.y = temp_npc->y;
				npc3.x = temp_npc->x;
				npc3.y = temp_npc->y + temp_npc->sprite_list->h;
				npc4.x = temp_npc->x + temp_npc->sprite_list->w;
				npc4.y = temp_npc->y + temp_npc->sprite_list->h;
				//printf(">>> check_colision_enemy - i: %d, p1.x: %d, p1.y: %d, npc1.x: %d, npc1.y: %d\n", i, p1.x, p1.y, npc1.x, npc1.y);
				//printf(">>> check_colision_enemy - i: %d, p4.x: %d, p4.y: %d, npc4.x: %d, npc4.y: %d\n", i, p4.x, p4.y, npc4.x, npc4.y);
				// any point inside NPC is a hit
				if (p1.x >= npc1.x && p1.x <= npc2.x && p1.y >= npc1.y && p1.y
						<= npc3.y) {
					//printf("DEBUG.check_collision - npc hit 1\n");
					return i;
				} else if (p2.x >= npc1.x && p2.x <= npc2.x && p2.y >= npc1.y
						&& p2.y <= npc3.y) {
					//printf("DEBUG.check_collision - npc hit 2\n");
					return i;
				} else if (p3.x >= npc1.x && p3.x <= npc2.x && p3.y >= npc1.y
						&& p3.y <= npc3.y) {
					//printf("DEBUG.check_collision - npc hit 4\n");
					return i;
				} else if (p4.x >= npc1.x && p4.x <= npc2.x && p4.y >= npc1.y
						&& p4.y <= npc3.y) {
					//printf("DEBUG.check_collision - npc hit 4\n");
					return i;
				} else {
					//printf("DEBUG.check_collision - no npc hit\n");
				}
			}
			i++;
			temp_npc = temp_npc->next;
		}
	} else if (owner == PROJECTILE_NPC) {
		// check colision with PLAYERS
		temp_player = player_list;
		//printf("DEBUG.check_colision - NPC search start\n");
		i = 1;
		while (temp_player != NULL) {
			//printf("DEBUG.check_colision PLAYER - x: %d, y: %d, HP: %d\n", temp_player->sprite->x, temp_player->sprite->y, temp_player->HP);
                        if (temp_player->HP > 0) {
                            int diff_h = 0;
                            if (temp_player->sprite->h > PLAYER_H) {
                                diff_h = temp_player->sprite->h-PLAYER_H;
                            }
				npc1.x = temp_player->sprite->x;
                                npc1.y = temp_player->sprite->y+diff_h;
				npc2.x = temp_player->sprite->x + temp_player->sprite->w;
                                npc2.y = temp_player->sprite->y+diff_h;
				npc3.x = temp_player->sprite->x;
				npc3.y = temp_player->sprite->y + temp_player->sprite->h;
				npc4.x = temp_player->sprite->x + temp_player->sprite->w;
				npc4.y = temp_player->sprite->y + temp_player->sprite->h;
				//printf("DEBUG.checkcollsion PLAYER - i: %d, p1.x: %d, p1.y: %d, npc1.x: %d, npc1.y: %d\n", i, p1.x, p1.y, npc1.x, npc1.y);
				// any point inside NPC is a hit
                                if (p1.x >= npc1.x && p1.x <= npc2.x && p1.y >= npc1.y && p1.y <= npc3.y) {
					//printf("DEBUG.check_collision - PLAYER hit 1\n");
					return i;
                                } else if (p2.x >= npc1.x && p2.x <= npc2.x && p2.y >= npc1.y && p2.y <= npc3.y) {
					//printf("DEBUG.check_collision - PLAYER hit 2\n");
					return i;
                                } else if (p3.x >= npc1.x && p3.x <= npc2.x && p3.y >= npc1.y && p3.y <= npc3.y) {
					//printf("DEBUG.check_collision - PLAYER hit 4\n");
					return i;
                                } else if (p4.x >= npc1.x && p4.x <= npc2.x && p4.y >= npc1.y && p4.y <= npc3.y) {
					//printf("DEBUG.check_collision - PLAYER hit 4\n");
					return i;
				} else {
					//printf("DEBUG.check_collision - no PLAYER hit\n");
				}
			}
			i++;
			temp_player = temp_player->next;
		}
	}
	return 0;
}

//Limpa a área da tela onde está o sprite
void clear_projectile(struct projectile *projectile_address) {
	struct projectile *temp_list;
	temp_list = projectile_list;

	while (temp_list) {
		// OBS: passar o tamanho da tela para viaráveis para poder usar + de uma resolução
		// parte que vai ser copiada
		if (temp_list == projectile_address) {
			src.x = 0;
			src.y = 0;
			src.w = temp_list->tile->w;
			src.h = temp_list->tile->h;

			// parte que vai ser colada
			//dest.x = x_p + map_pos_x;
			//dest.y = y_p + map_pos_y;
			dest.x = temp_list->x;
			dest.y = temp_list->y - (abs(map_pos_y) - abs(temp_list->map_y));
			//printf("DEBUG.clear_projectile - dest_x: %d, dest_y: %d\n", dest.x, dest.y);
			dest.w = temp_list->tile->w;
			dest.h = temp_list->tile->h;
			//SDL_BlitSurface(temp_list->underscreen, &src, screen, &dest);
		}
		temp_list = temp_list->next;
	}
}

void remove_projectile(struct projectile *projectile_address) {
        struct projectile *temp_list, *temp_ant, *temp_aux;

	temp_list = projectile_list;
	temp_ant = NULL;
	while (temp_list) {
		if (temp_list == projectile_address) {
			if (temp_list->owner_player != NULL) {
				temp_list->owner_player->shots = temp_list->owner_player->shots - 1;
			} else if (temp_list->owner_npc != NULL) {
				temp_list->owner_npc->shots = (temp_list->owner_npc->shots) - 1;
			}

			temp_aux = temp_list->next;
			free(temp_list);
			temp_list = NULL;
			temp_list = temp_aux;
			if (temp_ant != NULL) {
				temp_ant->next = temp_list;
			} else {
				projectile_list = temp_list;
			}
		} else {
			temp_ant = temp_list;
			temp_list = temp_list->next;
		}
	}
}


struct projectile *create_projectile(const int tempX, const int tempY) {
	struct projectile *new_item, *temp_list;

	new_item = (struct projectile *)malloc(sizeof(struct projectile));
	temp_list = projectile_list;

	if (!temp_list) {
		projectile_list = new_item;
	} else {
		while (temp_list->next) {
			temp_list = temp_list->next;
		}
		temp_list->next = new_item;
	}

		//temp_list[n].tile = SDL_CreateRGBSurface(SDL_SWSURFACE , 6, 6, 8, 0, 0, 0, 0);
		new_item->tile = normal_projectile;

		//new_item->underscreen = SDL_CreateRGBSurface(SDL_SWSURFACE, new_item->tile->w, new_item->tile->h, 8, 0, 0, 0, 0);
		//SDL_SetColors(new_item->underscreen, colormap, 0, COLOR_COUNT);

		//SDL_Surface *tempSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, new_item->tile->w, new_item->tile->h, 8, 0, 0, 0, 0);
		//new_item->underscreen = SDL_DisplayFormat(tempSurface);
		//SDL_FreeSurface(tempSurface);

		// copia área da tela para o underscreen do sprite
	src.x = tempX;
	src.y = tempY;
	src.w = new_item->tile->w;
	src.h = new_item->tile->h;
	// parte que vai ser colada
	dest.x = 0;
	dest.y = 0;
	dest.w = new_item->tile->w;
	dest.h = new_item->tile->h;
	new_item->next = NULL;
	//SDL_BlitSurface(offscreen, &src, new_item->underscreen, &dest);
	return new_item;
}

void show_projectile(SDL_Surface *screen) {
	//printf("DEBUG.show_projectile - START\n");
	// copia fundo para underscreen
	struct projectile *temp_list;
	temp_list = projectile_list;
	while (temp_list) {
		src.x = temp_list->x - map_pos_x + TILE_SIZE;
		src.y = temp_list->y - map_pos_y + TILE_SIZE;
		src.w = temp_list->tile->w;
		src.h = temp_list->tile->h;
		// parte que vai ser colada
		dest.x = 0;
		dest.y = 0;
		dest.w = temp_list->tile->w;
		dest.h = temp_list->tile->h;
		//SDL_BlitSurface(offscreen, &src, temp_list->underscreen, &dest);
		// copia tile para screen
		src.x = 0;
		src.y = 0;
		src.w = temp_list->tile->w;
		src.h = temp_list->tile->h;
		// parte que vai ser colada
		dest.x = temp_list->x;
		//printf("DEBUG.show_projectile - proj.y: %d, proj.map_y: %d, map_y: %d\n", temp_list[n].y, temp_list[n].map_y, map_pos_y);
		dest.y = temp_list->y
				- (abs(map_pos_y) - abs(temp_list->map_y));
		dest.w = temp_list->tile->w;
		dest.h = temp_list->tile->h;
		SDL_BlitSurface(temp_list->tile, &src, screen, &dest);
		//printf("DEBUG.show_projectile - END\n");
		temp_list = temp_list->next;
	}

}

// TODO - limit also per player
short int throw_projectile_player(struct player_struct *playerObj) {
	//short int i;

	if (playerObj->shots >= playerObj->shots_max) {
		return 0;
	}
	struct projectile *new_proj = create_projectile((playerObj->sprite->x + map_pos_x), (playerObj->sprite->y + map_pos_y + (TILE_SIZE)));
	new_proj->direction = playerObj->sprite->direction;
	new_proj->y = playerObj->sprite->y + map_pos_y + (TILE_SIZE);
	new_proj->x = playerObj->sprite->x + map_pos_x;
	playerObj->shots = playerObj->shots + 1;
	new_proj->owner_player = playerObj;
	new_proj->owner_npc = NULL;
	new_proj->owner = PROJECTILE_PLAYER;
	new_proj->map_x = map_pos_x;
	new_proj->map_y = map_pos_y;
		new_proj->speed = PROJECTILE_SPEED;
	if (new_proj->direction == ANIM_LEFT) {
			new_proj->x -= PROJECTILE_SPEED;
        } else if (new_proj->direction == ANIM_RIGHT) {
            new_proj->x += TILE_SIZE * 2;
        } else if (new_proj->direction == ANIM_LEFT_DIAGONAL) {
			new_proj->x -= PROJECTILE_SPEED;
			new_proj->y -= PROJECTILE_SPEED;
        } else if (new_proj->direction == ANIM_RIGHT_DIAGONAL) {
            new_proj->x += TILE_SIZE * 2;
			new_proj->y -= PROJECTILE_SPEED;
        }
	return 1;
}

// TODO - limit also per player
void throw_projectile_npc(struct npc_struct *npcObj) {
	//short int i;
	//printf(">>>>>>> throw_projectile_npc - can npc ");
	if (npcObj->shots <= 0) {
		// search for a free slot
		//printf(">>>>>>> throw_projectile_npc - search for a free slot");
                struct projectile *new_proj = create_projectile((npcObj->x + map_pos_x + (TILE_SIZE) *0.5), (npcObj->y + map_pos_y + (TILE_SIZE) *0.5));
		//printf(">>>>>>> throw_projectile_npc - FOUND free slot");
		new_proj->direction = npcObj->direction;
                new_proj->y = npcObj->y + map_pos_y + (TILE_SIZE) *0.5;
                new_proj->x = npcObj->x + map_pos_x + (TILE_SIZE) *0.5;
		//printf("DEBUG - x: %d, y: %d\n", new_proj->x, new_proj->y);
		new_proj->owner = PROJECTILE_NPC;
		new_proj->map_x = map_pos_x;
		new_proj->map_y = map_pos_y;
		npcObj->shots = npcObj->shots + 1;
		new_proj->owner_player = NULL;
		new_proj->owner_npc = npcObj;
                new_proj->speed = 6;
                if (new_proj->direction == ANIM_LEFT) {
                    new_proj->x -= 6;
                } else if (new_proj->direction == ANIM_RIGHT) {
                    new_proj->x += TILE_SIZE * 2;
                } else if (new_proj->direction == ANIM_LEFT_DIAGONAL) {
                    new_proj->x -= 6;
                    new_proj->y -= 6;
                } else if (new_proj->direction == ANIM_RIGHT_DIAGONAL) {
                    new_proj->x += TILE_SIZE * 2;
                    new_proj->y -= 6;
                }
                //printf("DEBUG.throw_projectile_npc - creating projectile\n");
	}
}

void anim_projectiles() {
	short colid_enemy;
	struct npc_struct *temp_npc;
	struct player_struct *playerObj;
	short int diffx, diffy;
	struct projectile *temp_list;
	temp_list = projectile_list;
	short int must_remove;

	//printf("+++++++++ anim_projectiles - START\n");
	while (temp_list) {
		must_remove = 0;
		//printf("DEBUG.anim_projectiles i: %d\n", i);
		clear_projectile(temp_list);

				if (temp_list->direction == ANIM_LEFT) {
					temp_list->x -= temp_list->speed;
				} else if (temp_list->direction == ANIM_RIGHT) {
					temp_list->x += temp_list->speed;
				} else if (temp_list->direction == ANIM_LEFT_DIAGONAL) {
					temp_list->x -= temp_list->speed;
					temp_list->y -= temp_list->speed;
				} else if (temp_list->direction == ANIM_RIGHT_DIAGONAL) {
					temp_list->x += temp_list->speed;
					temp_list->y -= temp_list->speed;
				}

		show_projectile(game_screen);
		colid_enemy = check_colision_enemy(temp_list->x - map_pos_x, temp_list->y - map_pos_y, 4, 4, temp_list->speed, 0, temp_list->owner);
		// remove sprites out of screen
		if (temp_list->x < (temp_list->speed * 2) || temp_list->x > MAX_W + temp_list->speed) {
					clear_projectile(temp_list);
					must_remove = 1;
                    //check_colision(short int obj_x, short int obj_y, short int obj_w, short int obj_h, short int x_inc, short int y_inc)
                } else if (temp_list->y < (temp_list->speed * 2) || temp_list->y > MAX_H + temp_list->speed) {
					clear_projectile(temp_list);
					must_remove = 1;
		} else if (colid_enemy > 0) {
                    if (temp_list->owner == PROJECTILE_PLAYER) {
                        temp_npc = getNPCN(colid_enemy - 1);
                        // checks if the npc have a shiled and if frame animation is #0 (stand with shield)
                        if (temp_npc->shield == 0 || (temp_npc->shield == 1 && temp_npc->sprite_list->anim_pos != 0)) {
                            damage_npc(temp_npc, 1);
                            must_remove = 1;
                        // front shield
                        } else if (temp_npc->shield == 2 && temp_list->direction == temp_npc->direction) {
                            damage_npc(temp_npc, 1);
                            must_remove = 1;
                        } else {
                            if (temp_list->direction == ANIM_LEFT) {
                                temp_list->direction = ANIM_RIGHT_DIAGONAL;
                            } else {
                                temp_list->direction = ANIM_LEFT_DIAGONAL;
                            }
                        }
                    } else if (temp_list->owner == PROJECTILE_NPC) {
                        playerObj = getPlayerN(colid_enemy - 1);
                        if (playerObj->hit_timer < getTimer() && playerObj->hit != 1) {
                            playerObj->hit = 1;
                            playerObj->hit_timer = getTimer()+HIT_INVENCIBLE_TIME;
                            playerObj->HP = playerObj->HP - 1;
                            playerObj->sprite->anim_type = ANIM_HIT;
                            playerObj->sprite->frame_animation[ANIM_PROCESS] = SDL_GetTicks() + 300;
                            diffx = (playerObj->sprite->w - 16) *0.5;
                            diffy = (playerObj->sprite->h - 16) *0.5;
                            create_hit_animation(playerObj->sprite->x + diffx, playerObj->sprite->y + diffy);
							play_sfx(SFX_PLAYER_HIT);
                        }
                    }
					clear_projectile(temp_list);
				}
                if (must_remove == 1) {
                        remove_projectile(temp_list);
                }
		temp_list = temp_list->next;
	}

	//printf("DEBUG.anim_projectiles 6\n");
}


void clear_all_projectiles(SDL_Surface *screen) {
	struct projectile *aux, *temp_list;

	temp_list = projectile_list;
	while (temp_list) {
		aux = temp_list;

		// OBS: passar o tamanho da tela para viaráveis para poder usar + de uma resolução
		// parte que vai ser copiada

		src.x = 0;
		src.y = 0;
		src.w = temp_list->tile->w;
		src.h = temp_list->tile->h;

		// parte que vai ser colada
		//dest.x = x_p + map_pos_x;
		//dest.y = y_p + map_pos_y;
		dest.x = temp_list->x;
		dest.y = temp_list->y - (abs(map_pos_y) - abs(temp_list->map_y));
		//printf("DEBUG.clear_projectile - dest_x: %d, dest_y: %d\n", dest.x, dest.y);
		dest.w = temp_list->tile->w;
		dest.h = temp_list->tile->h;
		//SDL_BlitSurface(temp_list->underscreen, &src, screen, &dest);

		free(aux);
		aux = NULL;
		temp_list = temp_list->next;
		//printf("DEBUG.clear_projectile - END\n");
	}
}





void remove_all_projectiles() {
	struct projectile *ant, *temp_list;

	//clear_all_projectiles(screen);

	temp_list = projectile_list;
	// position at the end, to remove the last element
	if (temp_list != NULL) {
		while (temp_list) {
			ant = temp_list;
			temp_list = temp_list->next;
			if (ant->owner_player) {
				ant->owner_player->shots = ant->owner_player->shots - 1;
				ant->owner_player = NULL;
			}
			if (ant->owner_npc) {
				ant->owner_npc->shots = ant->owner_npc->shots - 1;
				ant->owner_npc = NULL;
			}
			//SDL_FreeSurface(ant->underscreen);
			ant->tile = NULL;
			free(ant);
		}
	}
	projectile_list = NULL;
}


#endif // PROJECTILES_H
