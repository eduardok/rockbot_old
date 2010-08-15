#ifndef OBJECT_H
#define OBJECT_H


void show_object_sprites(SDL_Surface *screen, int i) {
	// checks if the Object is near the screen to show it
	//printf("********* check draw object, x: %d, y: %d\n", map.object_list[i].position.x, map.object_list[i].position.y);
	if (map.object_list[i].type == OBJ_DISAPPEARING_BLOCK && map.object_list[i].direction == ANIM_RIGHT) {
		//printf("********* show_object_sprites - hidden object i: %d\n", i);
		return;
	}


	if (map.object_list[i].position.x+16 >= abs(map_pos_x) && map.object_list[i].position.x-16 <= abs(map_pos_x)+RES_W) {
		//printf("********* MUST DRAW - i: %d\n", i);
		SDL_Rect src, dest;

		// copia sprite para a tela
		src.x = 0;
		src.y = 0;
		src.w = map.object_list[i].framesize_w;
		src.h = map.object_list[i].framesize_h;
		// parte que vai ser colada
		dest.x = map.object_list[i].position.x + map_pos_x;
		dest.y = map.object_list[i].position.y + map_pos_y;
		//printf(">>> show_object_sprites - dest.x: %d, dest.y: %d\n", dest.x, dest.y);
		dest.w = map.object_list[i].framesize_w;
		dest.h = map.object_list[i].framesize_h;
		//printf("*** 2 - show_object_sprites - dest.x: %d, dest.y: %d, dest.w: %d, dest.h: %d\n", dest.x, dest.y, dest.w, dest.h);
		SDL_BlitSurface(map.object_list[i].sprite, &src, screen, &dest);
	} else {
		//printf("********* show_object_sprites - out of vision i: %d\n", i);
	}
}


// check colision of Player with Objects
// returns 1 for x block, 2 for y block, 3 for x AND y block and 0 for non-blocking items
short int colision_player_object(struct player_struct *playerObj, const short int x_inc, const short int y_inc) {
	struct pos p1, p2, p3, p4;
	struct pos obj1, obj2, obj3, obj4;
	short int i;
	short int passX=0, passY=0;
	int blocked = 0;


	short int reduce = abs(16-playerObj->sprite->w)*0.5;

	// ponto 3, topo/esquerda
	p1.x = playerObj->sprite->x + reduce;
	p1.y = playerObj->sprite->y;

	//printf(">> colision_player_object, p1.x: %d, p1.y: %d, x_inc: %d, y_inc: %d\n", p1.x, p1.y, x_inc, y_inc);


	// ponto 2, baixo/esquerda
	p2.x = playerObj->sprite->x + reduce;
	p2.y = playerObj->sprite->y + 31;

	// ponto 3, topo/direita
	p3.x = playerObj->sprite->x + playerObj->sprite->w - reduce;
	p3.y = playerObj->sprite->y;

	// ponto 4, baixo/direita
	p4.x = playerObj->sprite->x + playerObj->sprite->w - reduce;
	p4.y = playerObj->sprite->y + 31;

	// fix for ground checking
	p1.y = p1.y - 1;
	p2.y = p2.y - 1;
	p3.y = p3.y - 1;
	p4.y = p4.y - 1;

	for (i=0; i<STAGE_OBJECT_LIMIT; i++) {

		if (map.object_list[i].type != -1 && strstr(map.object_list[i].filename, ".png") != NULL && (map.object_list[i].type != OBJ_DISAPPEARING_BLOCK || map.object_list[i].direction != ANIM_RIGHT)) {
			//printf("*** colision_player_object - obj[%d] is good\n", i);
			obj1.x = map.object_list[i].position.x;
			obj1.y = map.object_list[i].position.y;
			obj2.x = map.object_list[i].position.x;
			obj2.y = map.object_list[i].position.y + map.object_list[i].framesize_h;
			obj3.x = map.object_list[i].position.x + map.object_list[i].framesize_w;
			obj3.y = map.object_list[i].position.y;
			obj4.x = map.object_list[i].position.x + map.object_list[i].framesize_w;
			obj4.y = map.object_list[i].position.y + map.object_list[i].framesize_h;

			/*
			if (i == playerObj->platform_n) {
				printf(">> current-lock - i: %d, obj1.x: %d, obj1.y: %d\n", i, obj1.x, obj1.y);
			}
			*/

			//printf("*** colision_player_object - testing obj[%d], p1.y: %d, obj1.y: %d\n", i, p1.y, obj1.y);

			// any point inside NPC is a hit
			passY = 0;
			passX = 0;

			// check if player is on the X range of object
			if (playerObj->sprite->w > map.object_list[i].framesize_w) {
				if ((obj1.x >= p1.x && obj1.x <= p3.x) || (obj3.x >= p1.x && obj3.x <= p3.x)) {
					passX = 1;
				}
			} else {
				if ((p1.x >= obj1.x && p1.x <= obj3.x) || (p3.x >= obj1.x && p3.x <= obj3.x)) {
					passX = 1;
				}
			}

			// check if player is on the Y range of object
			if (playerObj->sprite->h > map.object_list[i].framesize_h) {
				if ((obj1.y >= p1.y && obj1.y <= p2.y) || (obj2.y >= p1.y && obj2.y <= p2.y)) {
					passY = 1;
				}
			} else {
				if ((p1.y >= obj1.y && p1.y <= obj2.y) || (p2.y >= obj1.y && p2.y <= obj3.y)) {
					passY = 1;
				}
			}

			// player is on the left of the object, and moving to right
			if (passY && p1.x >= obj4.x && p1.x+x_inc <= obj4.x) {
				printf("block X1\n");
				blocked = 1;
			}

			// player is on the right of the object, and moving to left
			if (passY && p3.x <= obj1.x && p3.x+1 >= obj1.x) {
				printf(">> block X2\n");
				blocked = 1;
			}

			// player is under the object and moving to top
			if (passX && p1.y >= obj4.y && p1.y+y_inc <= obj4.y) {
				if (blocked == 0) {
					blocked = 2;
				} else {
					blocked = 3;
				}
			}
			// player is over the object and moving to bottom
			if (passX && p4.y <= obj1.y && p4.y+y_inc >= obj1.y) {
				if (blocked == 0) {
					blocked = 2;
				} else {
					blocked = 3;
				}
			}

			if (map.object_list[i].type == OBJ_MOVING_PLATFORM_UPDOWN || map.object_list[i].type == OBJ_MOVING_PLATFORM_LEFTRIGHT || map.object_list[i].type == OBJ_DISAPPEARING_BLOCK  || map.object_list[i].type == OBJ_FALL_PLATFORM) {
				if ((blocked == 2 || blocked == 3) && p4.y <= obj1.y) {
					playerObj->platform_n = i;
				} else if (blocked == 1) {
					playerObj->platform_n = i;
				}
				if (blocked != 0) {
					return blocked;
				}
			} else if (blocked != 0) {
				if (map.object_list[i].type == OBJ_ENERGY_PILL_SMALL) {
					if (playerObj->HP + 3 <= playerObj->HP_MAX) {
						playerObj->HP += 3;
					} else {
						playerObj->HP = playerObj->HP_MAX;
					}
				} else if (map.object_list[i].type == OBJ_ENERGY_PILL_BIG) {
					if (playerObj->HP + 8 <= playerObj->HP_MAX) {
						playerObj->HP += 8;
					} else {
						playerObj->HP = playerObj->HP_MAX;
					}
				} else if (map.object_list[i].type == OBJ_ENERGY_TANK) {
					playerObj->items.energy_tanks++;
				} else if (map.object_list[i].type == OBJ_WEAPON_TANK) {
					playerObj->items.weapon_tanks++;
				} else if (map.object_list[i].type == OBJ_LIFE) {
					playerObj->items.lifes++;
				}
				map.object_list[i].type = -1;
				SDL_FreeSurface(map.object_list[i].sprite);
				map.object_list[i].sprite = NULL;
				return 0;
			}

		}
	}
	if (blocked == 0 && playerObj->platform_n != -1) {
		printf("got out of platform\n");
		playerObj->platform_n = -1;
	}
	return blocked;
}


void moveObjects(int i) {

	if (map.object_list[i].type == OBJ_MOVING_PLATFORM_LEFTRIGHT) {
		if (map.object_list[i].timer < getTimer()) {
			// for now, move 4 tiles
			if (map.object_list[i].distance < 4*TILE_SIZE)  {
				if (map.object_list[i].direction == ANIM_RIGHT) {
					map.object_list[i].position.x += 2;
					if (p1Obj->platform_n == i) {
						p1Obj->sprite->x += 2;
					}
				} else {
					map.object_list[i].position.x -= 2;
					if (p1Obj->platform_n == i) {
						p1Obj->sprite->x -= 2;
					}
				}
				map.object_list[i].distance++;
				map.object_list[i].timer = getTimer()+30;
			} else {
				map.object_list[i].distance = 0;
				if (map.object_list[i].direction == ANIM_RIGHT) {
					map.object_list[i].direction = ANIM_LEFT;
				} else {
					map.object_list[i].direction = ANIM_RIGHT;
				}
			}
		}
	} else if (map.object_list[i].type == OBJ_MOVING_PLATFORM_UPDOWN) {
		if (map.object_list[i].timer < getTimer()) {
			// for now, move 4 tiles
			if (map.object_list[i].distance < 4*TILE_SIZE)  {
				if (map.object_list[i].direction == ANIM_RIGHT) {
					map.object_list[i].position.y += 2;
					if (p1Obj->platform_n == i) {
						p1Obj->sprite->y += 2;
					}
				} else {
					map.object_list[i].position.y -= 2;
					if (p1Obj->platform_n == i) {
						p1Obj->sprite->y -= 2;
					}
				}
				map.object_list[i].distance++;
				map.object_list[i].timer = getTimer()+30;
			} else {
				map.object_list[i].distance = 0;
				if (map.object_list[i].direction == ANIM_RIGHT) {
					map.object_list[i].direction = ANIM_LEFT;
				} else {
					map.object_list[i].direction = ANIM_RIGHT;
				}
			}
		}
	} else if (map.object_list[i].type == OBJ_DISAPPEARING_BLOCK) {
		if (map.object_list[i].timer < getTimer()) {
			if (map.object_list[i].direction == ANIM_RIGHT) {
				map.object_list[i].direction = ANIM_LEFT;
				map.object_list[i].timer = getTimer() + 1000;
			} else {
				map.object_list[i].direction = ANIM_RIGHT;
				map.object_list[i].timer = getTimer() + 2000;
				// difference of time between blocks
				if (map.object_list[i].speed > 0) {
					map.object_list[i].timer += map.object_list[i].speed;
					map.object_list[i].speed = 0;
				}
			}
		}
	}
}


#endif // OBJECT_H
