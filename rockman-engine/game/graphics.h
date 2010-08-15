


struct sprite_struct *create_sprite(short int x, short int y, short int sp_w, short int sp_h, SDL_Surface *screen) {
	struct sprite_struct *sprite_list;

	sprite_list = (struct sprite_struct*)malloc(sizeof(struct sprite_struct));
	init_sprite_vars(sprite_list);

	// carrega sprite do player
	sprite_list->x = x;
	sprite_list->y = y;
	sprite_list->w = sp_w;
	sprite_list->h = sp_h;

	src.x = x;
	src.y = y;
	src.w = sp_w;
	src.h = sp_h;
	// parte que vai ser colada
	dest.x = 0;
	dest.y = 0;
	dest.w = sp_w;
	dest.h = sp_h;
	show_sprite(sprite_list, screen);
	return sprite_list;
}


//Limpa a tela. Essa função é necessária já que não podemos utilizar a função SDL_FreeSurface na tela principal, a screen.
void clear_screen(SDL_Surface *screen) {
	// OBS: passar o tamanho da tela para viaráveis para poder usar + de uma resolução
	// parte que vai ser copiada
	src.x = 16;
	src.y = 16;
	src.w = MAX_W;
	src.h = MAX_H;
	// parte que vai ser colada
	dest.x = 0;
	dest.y = 0;
	dest.w = MAX_W;
	dest.h = MAX_H;
	SDL_BlitSurface (offscreen, &src, screen, &dest);
}


//Limpa a tela. Essa função é necessária já que não podemos utilizar a função SDL_FreeSurface na tela principal, a screen.
void clear_area(SDL_Surface *screen, short int x, short int y, short int w, short int h, short int r, short int g, short int b) {
	dest.x = x;
	dest.y = y;
	dest.w = w;
	dest.h = h;
	SDL_FillRect(screen, &dest, SDL_MapRGB(screen->format, r, g, b));
}


void show_npc_sprites(SDL_Surface *screen) {

	//printf("DEBUG - show_npc_sprites START\n");
	struct npc_struct *temp;
	short int x_p=0, y_p=0;

	// define qual a posição da tela onde irá desenhar o sprite
	temp = npc_list;
	while (temp != NULL) {
		if (temp->HP > 0) {
			x_p = temp->x + map_pos_x;
			y_p = temp->y + map_pos_y;

			//printf(">>>>>>> show_npc_sprites - sprite.x: %d, map_pos_x: %d, map_pos_x+RES_W: %d\n", temp->x, abs(map_pos_x), (abs(map_pos_x)+RES_W));
			// checks if the NPC is near the screen to show it
			if (temp->x+16 >= abs(map_pos_x) && temp->x-16 <= abs(map_pos_x)+RES_W) {

				SDL_Rect src, dest;

				src.w = temp->sprite_list->w;
				dest.w = temp->sprite_list->w;
				dest.h = temp->sprite_list->h;
				// copia sprite para a tela
				src.x = 0;
				src.y = 0;
				// área da colagem
				dest.x = x_p;
				dest.y = y_p;
				//printf("++ graphics.h::show_npc_sprites - dest.x: %d, dest.y: %d\n", dest.x, dest.y);

				// verifica se o frame da animação existe, caso contrário, usa o primeiro (0) da lista
				if (temp->sprite_list->sprite_frames[temp->sprite_list->direction][temp->sprite_list->anim_type][temp->sprite_list->anim_pos].frame == NULL) {
					if (temp->sprite_list->sprite_frames[temp->sprite_list->direction][temp->sprite_list->anim_type][0].frame != NULL) {
						//printf("++ graphics.h::show_npc_sprites - reset to pos ZERO\n");
						temp->sprite_list->anim_pos=0;
					} else {
						//printf("++ graphics.h::show_npc_sprites - NPC: %p\n", temp);
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
								} else if (temp->direction == ANIM_RIGHT && temp->x < p1Obj->sprite->x) {
									temp->direction = ANIM_LEFT;
								}
								throw_projectile_npc(temp);
							}
						}
					// reseta animação
					} else {
						temp->sprite_list->anim_pos=0;
						//printf(">>graphics.h::show_npc_sprite - RESET POS direction: %d, anim_type: %d, anim_turn: %d, anim_pos: %d\n", temp->sprite->direction, temp->sprite->anim_type, ANIM_TURN, temp->sprite->anim_pos);
						if (temp->sprite_list->anim_type == ANIM_TURN) {
							if (temp->direction == ANIM_LEFT) {
								temp->direction = ANIM_RIGHT;
							} else {
								temp->direction = ANIM_LEFT;
							}
							temp->sprite_list->anim_type = ANIM_STAND;
						}
						//printf("++ graphics.h::show_npc_sprites - reset to pos ZERO\n");
					}
					//printf("DEBUG - reseting animation\n");
					temp->sprite_list->sprite_frames[temp->sprite_list->direction][temp->sprite_list->anim_type][temp->sprite_list->anim_pos].init=getTimer();
				}
			}
		}
		temp = temp->next;
	}
}


void add_sprite(short int direction, short int anim_type, short int pos_x, short int pos_y, struct sprite_struct *sprite_list, short int duration, SDL_Surface *image) {
	short int pos_n=0, i;
	src.x = pos_x*sprite_list->w;
	src.y = pos_y*sprite_list->h;
	src.w = (pos_x*sprite_list->w)+sprite_list->w;
	src.h = (pos_y*sprite_list->h)+sprite_list->h;
	// parte que vai ser colada
	dest.x = 0;
	dest.y = 0;
	dest.w = sprite_list->w;
	dest.h = sprite_list->h;
	for (i=0; i<ANIM_N3 && sprite_list->sprite_frames[direction][anim_type][i].frame != NULL; i++) {
		pos_n++;
	}
	//printf("************* graphics.h::add_sprite - direction: %d, anim_type: %d, anim_pos: %d\n", direction, anim_type, pos_n);
	sprite_list->sprite_frames[direction][anim_type][pos_n].duration=duration;
	//printf("DEBUG.add_sprite - adicionando sprite, pos_n: %d, direction: %d, anim_type: %d, int pos_x: %d, int_pos_y: %d, sprite_id: %d, duration: %d\n", pos_n, direction, anim_type, pos_x, pos_y, sprite_id, sprite_list->sprite_frames[direction][anim_type][pos_n].duration);
	sprite_list->sprite_frames[direction][anim_type][pos_n].frame = SDL_CreateRGBSurface(SDL_SWSURFACE , sprite_list->w, sprite_list->h, 8, 0, 0, 0, 0);
	SDL_SetColors(sprite_list->sprite_frames[direction][anim_type][pos_n].frame, colormap, 0, COLOR_COUNT);
	SDL_FillRect(sprite_list->sprite_frames[direction][anim_type][pos_n].frame, NULL, SDL_MapRGB(game_screen->format, 123, 123, 123));
	SDL_SetColorKey(sprite_list->sprite_frames[direction][anim_type][pos_n].frame, SDL_SRCCOLORKEY, SDL_MapRGB(game_screen->format, 123, 123, 123));
	SDL_BlitSurface(image, &src, sprite_list->sprite_frames[direction][anim_type][pos_n].frame, &dest);
}



// Nessa função desenharemos o paddle do jogador...
void show_sprite(struct sprite_struct *sprite_list, SDL_Surface *screen) {
	short int x_p=0, y_p=0;
	//printf("DEBUG - sprite_n: %d", sprite_n);
	// define qual a posição da tela onde irá desenhar o sprite
	x_p = sprite_list->x + map_pos_x;
	y_p = sprite_list->y + map_pos_y;
	SDL_Rect src, dest;

	src.w = sprite_list->w;
	src.h = sprite_list->h;
	// parte que vai ser colada
	dest.w = sprite_list->w;
	dest.h = sprite_list->h;

	// copia sprite para a tela
	src.x = 0;
	src.y = 0;
	// área da colagem
	dest.x = x_p;
	dest.y = y_p;
	//printf("DEBUG - dest.x: %d, dest.y: %d\n", dest.x, dest.y);
	
	// verifica se o frame da animação existe, caso contrário, usa o primeiro (0) da lista
	//printf(">>graphics.h::show_sprite - direction: %d, anim_type: %d, anim_pos: %d\n", sprite_list->direction, sprite_list->anim_type, sprite_list->anim_pos);
	//printf("DEBUG - sprite_N: %d\n");

	if (sprite_list->sprite_frames[sprite_list->direction][sprite_list->anim_type][sprite_list->anim_pos].frame == NULL) {
		if (sprite_list->sprite_frames[sprite_list->direction][sprite_list->anim_type][0].frame != NULL) {
			sprite_list->anim_pos=0;
		} else {
			//printf("WARNING - erro: Não achou frame para sprite - direction: %d,  type: %d, pos: %d\n", sprite_list->direction, sprite_list->anim_type, sprite_list->anim_pos);
			return;
		}
	}
	// copia o fundo da tela, guardado em .tile, para a tela
	//SDL_BlitSurface(sprite_list->tile, &src, screen, &dest);
	SDL_BlitSurface(sprite_list->sprite_frames[sprite_list->direction][sprite_list->anim_type][sprite_list->anim_pos].frame, &src, screen, &dest);
	// avança a animação
	//printf("############# > show_sprite - duration: %d, time-init: %d\n", sprite_list->sprite_frames[sprite_list->direction][sprite_list->anim_type][sprite_list->anim_pos].duration, (getTimer() - sprite_list->sprite_frames[sprite_list->direction][sprite_list->anim_type][sprite_list->anim_pos].init));
	if (getTimer() - sprite_list->sprite_frames[sprite_list->direction][sprite_list->anim_type][sprite_list->anim_pos].init > sprite_list->sprite_frames[sprite_list->direction][sprite_list->anim_type][sprite_list->anim_pos].duration) {
		if (sprite_list->sprite_frames[sprite_list->direction][sprite_list->anim_type][sprite_list->anim_pos+1].frame != NULL) {
			sprite_list->anim_pos++;
			//printf(">>graphics.h::show_sprite - INC POS direction: %d, anim_type: %d, anim_pos: %d\n", sprite_list->direction, sprite_list->anim_type, sprite_list->anim_pos);
		// reseta animação
		} else {
			sprite_list->anim_pos=0;
			// if is turn, reset to stand (TODO - must be walk, fix it)
		}
		//printf("DEBUG - reseting animation\n");
		sprite_list->sprite_frames[sprite_list->direction][sprite_list->anim_type][sprite_list->anim_pos].init = getTimer();
	}
/*	
	// do not have the frame, try using the first frame of the move
	if (sprite_list->frames[sprite_list->frame_pos[0]][sprite_list->frame_pos[1]] == NULL && sprite_list->frames[sprite_list->frame_pos[0]][0] == NULL) {
		printf("DEBUG - no image in frame[%d][%d]\n", sprite_list->frame_pos[0], sprite_list->frame_pos[1]);
		SDL_BlitSurface(sprite_list->tile, &src, screen, &dest);
	} else {
		if (sprite_list->frames[sprite_list->frame_pos[0]][0] == NULL) {
			sprite_list->frame_pos[1]=0;
		}
		//printf("DEBUG - using frames\n");
		SDL_BlitSurface(sprite_list->frames[sprite_list->frame_pos[0]][sprite_list->frame_pos[1]], &src, screen, &dest);
		if (sprite_list->frames[sprite_list->frame_pos[0]][sprite_list->frame_pos[1]+1] != NULL) {
			sprite_list->frame_pos[1]++;
		} else {
			sprite_list->frame_pos[1]=0;
		}
	}
*/
}

void draw_text(short int x, short int y, char *text, SDL_Surface *screen) {
	SDL_Color font_color = {255,255,255};
	SDL_Rect text_pos={x, y, 0, 0};
	if (!font) {
		printf("TTF_OpenFont: %s\n", TTF_GetError());
		exit(-1);
		// handle error
	}
	SDL_Surface* textSF = TTF_RenderText_Solid(font, text, font_color);
	SDL_BlitSurface(textSF, 0, screen, &text_pos);
	SDL_FreeSurface(textSF);
	SDL_Flip(game_screen);
}



void blank_screen(SDL_Surface *screen) {
	//printf("DEBUG - filling screen with black\n");
	SDL_FillRect(screen, NULL, SDL_MapRGB(game_screen->format, 0, 0, 0));
	SDL_Flip(screen);
}

void blank_area(SDL_Surface *screen, short int x, short int y, short int w, short int h) {
	printf("DEBUG - filling screen with black\n");
	dest.x = x;
	dest.y = y;
	dest.w = w;
	dest.h = h;
	SDL_FillRect(screen, &dest, SDL_MapRGB(game_screen->format, 0, 0, 0));
	SDL_Flip(screen);
}



void show_animation(SDL_Surface *screen) {
	struct animation_sprite_struct *temp, *temp_prev, *temp_old;
	temp = animation_list;
	temp_prev = NULL;
	//printf("DEBUG.show_animation - START\n");
	while (temp != NULL) {
		src.w = temp->frame->tile->h;
		src.h = temp->frame->tile->h;
		// parte que vai ser colada
		dest.w = temp->frame->tile->h;
		dest.h = 16;

		//printf("DEBUG.show_animation - looping throught animations\n");
		src.x = temp->animation_pos*temp->frame->w;
		//src.x = 0;
		src.y = 0;
		src.w = temp->frame->w;
		src.h = temp->frame->h;
		// parte que vai ser colada
		dest.x = temp->x + map_pos_x;
		dest.y = temp->y + map_pos_y;
		dest.w = temp->frame->w;
		dest.h = temp->frame->h;

		//printf("DEBUG frame->background - src.x: %d, src.y: %d, src.w: %d, src.h: %d\n", src.x, src.y, src.w, src.h);
		//printf("DEBUG frame->background - dest.x: %d, dest.y: %d, dest.w: %d, dest.h: %d\n", dest.x, dest.y, dest.w, dest.h);
		SDL_BlitSurface (temp->frame->tile, &src, screen, &dest);
		//printf(">> ANIMATION - timer passed time: %d, duration: %d\n", (getTimer()-temp->init), temp->frame->duration);
		if (getTimer()-temp->init > temp->frame->duration) {
			temp->animation_pos = temp->animation_pos + 1;
			//printf(">> ANIMATION - tile-w: %d, frame->w: %d, n_division: %d\n", temp->frame->tile->w, temp->frame->w, (temp->frame->tile->w/temp->frame->w-1));
			if (temp->animation_pos > (temp->frame->tile->w/temp->frame->w-1)) {
				//printf(">> ANIMATION - reset pos\n");
				temp->animation_pos = 0;
				temp->animation_loop_count++;
				//printf("DEBUG - temp->animation_loop_count: %d, temp->animation_loops: %d\n", temp->animation_loop_count, temp->animation_loops);
			} else {
				//printf(">> ANIMATION - advance pos\n");
			}
			temp->init=getTimer();
		}
		//printf("DEBUG.show_animation - temp->animation_pos: %d\n", temp->animation_pos);
		// if finished, remove animation from animation_list
		if (temp->animation_loop_count >= temp->animation_loops) {
			//printf(">> ANIMATION - finishing\n");
			if (temp_prev != NULL) {
				temp_prev->next = temp->next;
			} else { // if does not have a previous value, means it is the start of the list
				animation_list = temp->next;
			}
			temp_old = temp;
			free(temp);
			temp = NULL;
			temp_prev = NULL;
			temp = temp_old->next;

		} else {
			temp_prev = temp;
			temp = temp->next;
		}
	}
}


void draw_hp_bar(struct player_struct *playerObj) {
	short int x, y, i;
	short int r, g, b;
        if (playerObj == p1Obj) {
		x = 10;
		r = 127;
		g = 11;
		b = 0;
	} else {
		x = MAX_W-20;
		r = 255;
		g = 102;
		b = 0;
	}
	clear_area(game_screen, x, 10, 11, 63, 0, 0, 0);
	clear_area(game_screen, x+1, 11, 9, 61, r, g, b);
        for (i=0; i<playerObj->HP; i++) {
            y = ((28-i)*2+1)+11;
            clear_area(game_screen, x+3, y, 5, 1, 255, 255, 255);
	}
}


void create_hit_animation(short x, short y) {
	struct animation_sprite_struct *hit_animation;
	hit_animation = create_animation(x, y, hit_frame);
	hit_animation->animation_loops = 3;
}


void create_kill_animation(short x, short y) {
	//printf("DEBUG.create_kill_animation - START\n");
	struct animation_sprite_struct *kill_animation;
	kill_animation = create_animation(x, y, kill_frame);
	kill_animation->animation_loops = 2;
}

void change_colormap(SDL_Surface *screen, int pos, int r, int g, int b) {
	int res;
	colormap[pos].r = r;
	colormap[pos].g = g;
	colormap[pos].b = b;
	res = SDL_SetColors(screen, colormap, 0, COLOR_COUNT);
}



struct struct_colorcycle_list *add_colorcycle_list(short int color_n) {
	struct struct_colorcycle_list *temp_list;
	struct struct_colorcycle_list *new_cl_list=NULL;

	new_cl_list = (struct struct_colorcycle_list*)malloc(sizeof(struct struct_colorcycle_list));
	new_cl_list->colorcycle = NULL;
	new_cl_list->colorcycle_current = NULL;
	new_cl_list->next = NULL;
	new_cl_list->map_color = color_n;
	if (!colorcycle_list) {
		colorcycle_list = new_cl_list;
	} else {
		temp_list = colorcycle_list;
		while (temp_list->next) {
			temp_list = temp_list->next;
		}
		temp_list->next = new_cl_list;
	}
	return new_cl_list;
}

void add_colorcycle(struct struct_colorcycle_list *list, int duration, int r, int g, int b) {
	struct struct_colorcycle *temp=NULL;
	struct struct_colorcycle *new_colorcycle=NULL;

	//printf(">> add_colorcycle.cl_item: %p\n", list);

	new_colorcycle = (struct struct_colorcycle*)malloc(sizeof(struct struct_colorcycle));
	new_colorcycle->r = r;
	new_colorcycle->g = g;
	new_colorcycle->b = b;
	new_colorcycle->duration = duration;
	new_colorcycle->timer_ini = -1;
	new_colorcycle->next = NULL;

	temp = list->colorcycle;
	// first item in the list
	if (temp == NULL) {
		//printf(">>add_colorcycle - list->colorcycl is NULL\n");
		list->colorcycle = new_colorcycle;
	} else {
		//printf(">>add_colorcycle - list->colorcycl exists\n");
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = new_colorcycle;
	}
}

void exec_colorcycle(SDL_Surface *screen) {
	int n=0;
	struct struct_colorcycle_list *temp_list;
	temp_list = colorcycle_list;

	while (temp_list) {
		//printf(">>> exec_colorcycle - temp_list loop, n: %d\n", n);
		n++;
		if (temp_list->colorcycle != NULL) {
			if (temp_list->colorcycle_current == NULL) {
				//printf(">>graphic.h::exec_colorcycle - colorcycle_current is NULL, SET\n");
				temp_list->colorcycle_current = temp_list->colorcycle;
			} else if (temp_list->colorcycle_current->timer_ini + temp_list->colorcycle_current->duration < SDL_GetTicks()) {
				if (temp_list->colorcycle_current->next == NULL) {
					//printf(">>graphic.h::exec_colorcycle - colorcycle_current->next is NULL, SET\n");
					temp_list->colorcycle_current = temp_list->colorcycle;
				} else {
					//printf(">>graphic.h::exec_colorcycle - 1. go next colorcycle_current, current: %p, next: %p\n", temp_list->colorcycle_current, temp_list->colorcycle_current->next);
					temp_list->colorcycle_current = temp_list->colorcycle_current->next;
					//printf(">>graphic.h::exec_colorcycle - 2. go next colorcycle_current, current: %p, next: %p\n", temp_list->colorcycle_current, temp_list->colorcycle_current->next);
				}
				//printf(">>graphic.h::exec_colorcycle - color_n: %d, duration: %d, r: %d, g: %d, b: %d\n", temp_list->map_color,temp_list-> colorcycle_current->duration, temp_list->colorcycle_current->r, temp_list->colorcycle_current->g, temp_list->colorcycle_current->b);
				if (screen == NULL) {
					change_colormap(offscreen, temp_list->map_color, temp_list->colorcycle_current->r, temp_list->colorcycle_current->g, temp_list->colorcycle_current->b);
					move_screen(game_screen, 0, 0);
				} else {
					change_colormap(screen, temp_list->map_color, temp_list->colorcycle_current->r, temp_list->colorcycle_current->g, temp_list->colorcycle_current->b);
				}
				temp_list->colorcycle_current->timer_ini = SDL_GetTicks();
			//} else {
				//printf(">>graphic.h::exec_colorcycle - WAIT - now: %ld, expected: %ld\n", SDL_GetTicks(), (temp_list->colorcycle_current->timer_ini + temp_list->colorcycle_current->duration));
			}
		} else {
			printf(">>graphic.h::exec_colorcycle - colorcycle_list is NULL - ERROR\n");
			exit(-1);
		}
		temp_list = temp_list->next;
	}
}

SDL_Surface *surface_from_image(char filename[255]) {
	SDL_Surface *tile;
	SDL_RWops *rwop;

	rwop=SDL_RWFromFile(filename, "rb");
	if (!rwop) {
		printf("Error in surface_from_image: '%s' file not found\n", filename);
		exit(-1);
	}
	tile=IMG_Load_RW(rwop, 1);
	//printf("<< tile: %p\n", tile);
	SDL_SetColors(tile, colormap, 0, COLOR_COUNT);
	//printf("<< tile: %p\n", tile);
	return tile;
}

SDL_Surface *surface_region_from_image(char filename[255], int w, int h) {
	SDL_Surface *tile;
	SDL_RWops *rwop;


	//printf(">>>surface_region_from_image - filename: '%s', w: %d, h: %d\n", filename, w, h);
	rwop=SDL_RWFromFile(filename, "rb");
	if (!rwop) {
		printf("Error in surface_region_from_image: '%s' file not found\n", filename);
		//exit(-1);
		return NULL;
	}
	tile=IMG_Load_RW(rwop, 1);
	SDL_SetColors(tile, colormap, 0, COLOR_COUNT);
	//printf("<< tile: %p\n", tile);
	return tile;
}



struct simple_sprite *create_simple_sprite(short int w, short int h) {
	struct simple_sprite *new_sprite;
	//printf(">>graphics.h::create_simple_sprite - w: %d, h: %d\n", w, h);
	new_sprite = (struct simple_sprite*)malloc(sizeof(struct simple_sprite));
	new_sprite->sprite = NULL;
	new_sprite->sprite = SDL_CreateRGBSurface(SDL_SWSURFACE , w, h, 8, 0, 0, 0, 0);
	//printf(">>graphics.h::create_simple_sprite - sp: %p, sp->sprite: %p, sp->w: %d, sp->h: %d\n", new_sprite, new_sprite->sprite, new_sprite->sprite->w, new_sprite->sprite->h);
	//SDL_FillRect(new_sprite->sprite, NULL, SDL_MapRGB(game_screen->format, 123, 123, 123));
	//SDL_SetColorKey(new_sprite->sprite, SDL_SRCCOLORKEY, SDL_MapRGB(game_screen->format, 123, 123, 123));
	SDL_SetColors(new_sprite->sprite, colormap, 0, COLOR_COUNT);
	return new_sprite;
}


void show_simple_sprite(SDL_Surface *screen, struct simple_sprite *temp, short int x, short int y) {
	//printf(">>graphics.h::show_simple_sprite - x: %d, y: %d\n", x, y);
	src.w = temp->sprite->w;
	src.h = temp->sprite->h;
	// parte que vai ser colada
	dest.w = temp->sprite->w;
	dest.h = temp->sprite->h;


	//printf("DEBUG.show_animation - looping throught animations\n");
	src.x = 0;
	src.y = 0;
	src.w = temp->sprite->w;
	src.h = temp->sprite->h;
	// parte que vai ser colada
	dest.x = x + map_pos_x;
	dest.y = y + map_pos_y;
	dest.w = temp->sprite->w;
	dest.h = temp->sprite->h;
	temp->x = x;
	temp->y = y;
	//printf(">>graphics.h::show_simple_sprite -  sprite->screen - src.x: %d, src.y: %d, src.w: %d, src.h: %d\n", src.x, src.y, src.w, src.h);
	//printf(">>graphics.h::show_simple_sprite -  sprite->screen- dest.x: %d, dest.y: %d, dest.w: %d, dest.h: %d\n", dest.x, dest.y, dest.w, dest.h);
	SDL_BlitSurface (temp->sprite, &src, screen, &dest);
}


/*
void rasterCircle(int x0, int y0, int radius) {
	int f = 1 - radius;
	int ddF_x = 1;
	int ddF_y = -2 * radius;
	int x = 0;
	int y = radius;

	setPixel(x0, y0 + radius);
	setPixel(x0, y0 - radius);
	setPixel(x0 + radius, y0);
	setPixel(x0 - radius, y0);

	while(x < y) {
		// ddF_x == 2 * x + 1;
		// ddF_y == -2 * y;
		// f == x*x + y*y - radius*radius + 2*x - y + 1;
		if(f >= 0) {
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;
		setPixel(x0 + x, y0 + y);
		setPixel(x0 - x, y0 + y);
		setPixel(x0 + x, y0 - y);
		setPixel(x0 - x, y0 - y);
		setPixel(x0 + y, y0 + x);
		setPixel(x0 - y, y0 + x);
		setPixel(x0 + y, y0 - x);
		setPixel(x0 - y, y0 - x);
	}
}
*/



struct struct_npcSpriteGraphics *createNPCGraphic(short int sp_w, short int sp_h, char filename[255]) {
	struct struct_npcSpriteGraphics *new_sprite;
	struct struct_npcSpriteGraphics *temp_sprite_pos;
	SDL_RWops *rwop;

	new_sprite = (struct struct_npcSpriteGraphics*)malloc(sizeof(struct struct_npcSpriteGraphics));
	sprintf(new_sprite->filename, "%sdata/images/sprites/enemies/%s", FILEPATH, filename);
	new_sprite->next = NULL;
	new_sprite->w = sp_w;
	new_sprite->h = sp_h;
	// carrega paleta
	rwop=SDL_RWFromFile(new_sprite->filename, "rb");
	if (!rwop) {
		printf("Error in createNPCGraphic: '%s' file not found\n", new_sprite->filename);
		exit(-1);
	} else {
		//printf("#### createNPCGraphic - criando sprite para: %s\n", new_sprite->filename);
	}
	new_sprite->sprite = IMG_Load_RW(rwop, 1);
	if (npcSpriteGraphics == NULL) {
		//printf("#### createNPCGraphic - placing NPC in the start of the list\n");
		npcSpriteGraphics = new_sprite;
	} else {
		//printf("#### createNPCGraphic - placing NPC somewhere in the middle of the list\n");
		temp_sprite_pos = npcSpriteGraphics;
		while (temp_sprite_pos->next != NULL) {
			temp_sprite_pos = (struct struct_npcSpriteGraphics *)temp_sprite_pos->next;
		}
		temp_sprite_pos->next = new_sprite;
	}
	//printf("#### createNPCGraphic - new sprite: %p\n", new_sprite);
	return new_sprite;
}

struct struct_npcSpriteGraphics *createNPCGraphicFromFile(char filename[255]) {
	char buffer[255], number[4];
	int npc_n=1, i;
	int finished=0;
	FILE *fp;
	struct file_npc temp_npc;
	struct struct_npcSpriteGraphics *temp_graphic;

	while (!finished) {
		centNumber(npc_n, number);
		sprintf(buffer, "%sdata/game/game_001/%s.npc", FILEPATH, number);
		fp = fopen(buffer, "rb");
		if (!fp) {
			finished = 1;
		} else {
			fread(&temp_npc, sizeof(struct file_npc), 1, fp);
			fclose(fp);
			sprintf(buffer, "%sdata/images/tilesets/npc/%s", FILEPATH, temp_npc.filename);
			if (!strcmp(filename, temp_npc.filename)) {
				temp_graphic = createNPCGraphic(temp_npc.framesize_w, temp_npc.framesize_h, temp_npc.filename);
				for (i=0; i<NPC_FRAME_NUMBER; i++) {
					if (temp_npc.frameset[i] != -1) {
						temp_graphic->frameset[i] = temp_npc.frameset[i];
						temp_graphic->frameset_time[i] = temp_npc.frameset_time[i];
					} else {
						temp_graphic->frameset[i] = -1;
						temp_graphic->frameset_time[i] = -1;
					}
				}
				return temp_graphic;
			}
		}
		npc_n++;
	}
	return NULL;
}

struct struct_npcSpriteGraphics *findNPCGraphic(char filename[255]) {
	struct struct_npcSpriteGraphics *temp_sprite_pos;
	temp_sprite_pos = npcSpriteGraphics;
	char buffer_filename[255];

	while (temp_sprite_pos) {
		sprintf(buffer_filename, "%sdata/images/sprites/enemies/%s", FILEPATH, filename);
		//printf(">> struct_npcSpriteGraphics - comparing '%s' to '%s'\n", buffer_filename, temp_sprite_pos->filename);
		if (!strcmp(buffer_filename, temp_sprite_pos->filename)) {
			return temp_sprite_pos;
		}
		temp_sprite_pos = temp_sprite_pos->next;
	}
	// got here and did not found the graphic, create it
	//printf(">> struct_npcSpriteGraphics - Did not found graphic for %s, creating.\n", filename);
	return createNPCGraphicFromFile(filename);
}



SDL_Surface *surfaceFromFile(char filename[255]) {
	SDL_RWops *rwop;

	// carrega paleta
	rwop=SDL_RWFromFile(filename, "rb");
	if (!rwop) {
		printf("Error in surfaceFromFile: '%s' file not found\n",filename);
		exit(-1);
	}
	return IMG_Load_RW(rwop, 1);
}

struct sprite_struct *create_sprite_with_surface(short int x, short int y, short int sp_w, short int sp_h, SDL_Surface *screen) {
	// carrega sprite do player
	struct sprite_struct *sprite_list;

	sprite_list = (struct sprite_struct*)malloc(sizeof(struct sprite_struct));
	init_sprite_vars(sprite_list);

	sprite_list->x = x;
	sprite_list->y = y;
	sprite_list->w = sp_w;
	sprite_list->h = sp_h;

	src.w = sp_w;
	src.h = sp_h;
	// parte que vai ser colada
	dest.w = sp_w;
	dest.h = sp_h;
	show_sprite(sprite_list, screen);
	return sprite_list;
}



void showReadyAnimation() {
	int i;
	char buffer_filename[255];
	SDL_Surface* readyImg;
	sprintf(buffer_filename, "%sdata/images/tilesets/ready.png", FILEPATH);
	readyImg = surfaceFromFile(buffer_filename);

	SDL_Surface* readyBg = SDL_CreateRGBSurface(SDL_SWSURFACE, readyImg->w, readyImg->h, 8, 0, 0, 0, 255);
	SDL_SetColors(readyBg, colormap, 0, COLOR_COUNT);

	src.w = 46;
	src.h = 13;
	dest.w = 46;
	dest.h = 13;
	dest.x = (RES_W*0.5)-26+map_pos_x;
	dest.y = (RES_H*0.5)-6+map_pos_y;
	src.x = 0;
	src.y = 0;

	copy_area(game_screen, dest.x, dest.y, readyBg->w, readyBg->h, 0, 0, readyBg);

	for (i=0; i<4; i++) {
		// go ahread to loop
		SDL_BlitSurface(readyImg, &src, game_screen, &dest);
		SDL_Flip(game_screen);
		waitTime(400);
		SDL_BlitSurface(readyBg, &src, game_screen, &dest);
		SDL_Flip(game_screen);
		waitTime(400);
    }

	SDL_FreeSurface(readyImg);
	SDL_FreeSurface(readyBg);
}

//TRANSITION_TOP_TO_BOTTOM, TRANSITION_BOTTOM_TO_TOP
void transitionScreen(short int type, short int map_n, short int adjust_x) {
	SDL_Surface *temp_screen;
	short int i, j;
	struct player_struct *p1;

	//printf(">>>>>>>>>>> transitionScreen.adjust_x: %d, map_n: %d, type: %d\n", adjust_x, map_n, type);
	// draw the offscreen with the new loaded map
	loadMap(currentGame, map_n);
	drawMap(offscreen, 0);

	if (type == TRANSITION_TOP_TO_BOTTOM || type == TRANSITION_BOTTOM_TO_TOP) {
		temp_screen = SDL_CreateRGBSurface(SDL_SWSURFACE, MAX_W, MAX_H*2, 8, 255, 255, 0, 0);
		SDL_SetColors(temp_screen, colormap, 0, COLOR_COUNT);
		// copy current screen to temp
		if (type == TRANSITION_TOP_TO_BOTTOM) {
			copy_area(game_screen, 0, 0, MAX_W, MAX_H, 0, 0, temp_screen);
		} else if (type == TRANSITION_BOTTOM_TO_TOP) {
			copy_area(game_screen, 0, 0, MAX_W, MAX_H, 0, MAX_H, temp_screen);
		}
		// copy the new screen to the temp_area
		if (type == TRANSITION_TOP_TO_BOTTOM) {
			copy_area(offscreen, TILE_SIZE+adjust_x, TILE_SIZE, MAX_W, MAX_H, 0, MAX_H, temp_screen);
		} else if (type == TRANSITION_BOTTOM_TO_TOP) {
			copy_area(offscreen, TILE_SIZE+adjust_x, TILE_SIZE, MAX_W, MAX_H, 0, 0, temp_screen);
		}

		// now, show the transition
		for (i=0; i<MAX_H; i++) {
			if (type == TRANSITION_TOP_TO_BOTTOM) {
				copy_area(temp_screen, 0, i, MAX_W, MAX_H, 0, 0, game_screen);
			} else if (type == TRANSITION_BOTTOM_TO_TOP) {
				copy_area(temp_screen, 0, MAX_H-i, MAX_W, MAX_H, 0, 0, game_screen);
			}
			exec_colorcycle(temp_screen);
			for (j=0; j<game_config.two_players; j++) {	// players
				p1 = getPlayerN(j);
				if (type == TRANSITION_TOP_TO_BOTTOM) {
					if (p1->sprite->y > TILE_SIZE) {
						p1->sprite->y = p1->sprite->y - 1;
						p1->y = p1->y - 1;
					}
				} else if (type == TRANSITION_BOTTOM_TO_TOP) {
					if (p1->sprite->y < MAX_H-TILE_SIZE*2) {
						p1->sprite->y = p1->sprite->y + 1;
						p1->y = p1->y + 1;
					}
				}
				//printf("*********** i: %d, p1->sprite->y: %d\n", i, p1->sprite->y);
				show_sprite(p1->sprite, game_screen);
			}
			SDL_Flip(game_screen);
			waitTime(6);
		}
		SDL_FreeSurface(temp_screen);
	}

}

void blink_screen(int r, int g, int b) {
    int i;
    SDL_Surface *tmp, *screen_copy;

	screen_copy = SDL_CreateRGBSurface(SDL_SWSURFACE , game_screen->w, game_screen->h, 32, 0, 0, 0, 0);
    copy_area(game_screen, 0, 0, game_screen->w, game_screen->h, 0, 0, screen_copy);

    tmp=SDL_DisplayFormat(game_screen);
    SDL_FillRect(tmp, 0, SDL_MapRGB(game_screen->format, r, g, b));
    /*
     for 32 bits-color
    for (i=0; i<99; i++) {
        SDL_SetAlpha(tmp, SDL_SRCALPHA, i);
        SDL_BlitSurface(tmp, 0, game_screen, 0);
        SDL_Flip(game_screen);
		waitTime(1);
    }
    for (i=99; i>=0; i--) {
        SDL_SetAlpha(tmp, SDL_SRCALPHA, i);
        SDL_BlitSurface(screen_copy, 0, game_screen, 0);
        SDL_BlitSurface(tmp, 0, game_screen, 0);
        SDL_Flip(game_screen);
		waitTime(1);
    }
    for (i=0; i<99; i++) {
        SDL_SetAlpha(tmp, SDL_SRCALPHA, i);
        SDL_BlitSurface(tmp, 0, game_screen, 0);
        SDL_Flip(game_screen);
		waitTime(1);
    }
    */
    for (i=0; i<4; i++) {
        SDL_BlitSurface(tmp, 0, game_screen, 0);
        SDL_Flip(game_screen);
		waitTime(80);

        SDL_BlitSurface(screen_copy, 0, game_screen, 0);
        SDL_Flip(game_screen);
		waitTime(80);
    }
    SDL_FreeSurface(screen_copy);
    SDL_FreeSurface(tmp);
}


void show_error(int ERROR_LEVEL, char *error_message) {
	if (ERROR_LEVEL == WARNING) {
		draw_text(10, 10, error_message, game_screen);
		waitTime(1000);
	} else {
		blank_screen(game_screen);
		draw_text(10, 10, error_message, game_screen);
		waitTime(5000);
	}
}
