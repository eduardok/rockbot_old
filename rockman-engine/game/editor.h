#define EDIT_AREA_W 608
#define EDIT_AREA_H 592

#define EDIT_W 800
#define EDIT_H 600

void draw_selected_tile_border(SDL_Surface *screen, short int quad_x, short int quad_y) {
	// lateral esquerda
	dest.x = quad_x * TILE_SIZE;
	dest.y = quad_y * TILE_SIZE;
	dest.w = 1;
	dest.h = TILE_SIZE;
	SDL_FillRect(screen, &dest, SDL_MapRGB(screen->format, 180, 0, 0));
	// lateral direita
	dest.x = (quad_x * TILE_SIZE) + TILE_SIZE - 1;
	dest.y = quad_y * TILE_SIZE;
	dest.w = 1;
	dest.h = TILE_SIZE;
	SDL_FillRect(screen, &dest, SDL_MapRGB(screen->format, 180, 0, 0));
	// topo
	dest.x = quad_x * TILE_SIZE;
	dest.y = quad_y * TILE_SIZE;
	dest.w = TILE_SIZE;
	dest.h = 1;
	SDL_FillRect(screen, &dest, SDL_MapRGB(screen->format, 180, 0, 0));
	// base
	dest.x = quad_x * TILE_SIZE;
	dest.y = (quad_y * TILE_SIZE) + TILE_SIZE - 1;
	dest.w = TILE_SIZE;
	dest.h = 1;
	SDL_FillRect(screen, &dest, SDL_MapRGB(screen->format, 180, 0, 0));
}

void clear_tile_border(SDL_Surface *screen, short int quad_x, short int quad_y) {
	// lateral esquerda
	dest.x = quad_x * TILE_SIZE;
	dest.y = quad_y * TILE_SIZE;
	dest.w = 1;
	dest.h = TILE_SIZE;
	SDL_FillRect(screen, &dest, SDL_MapRGB(screen->format, 180, 180, 180));
	// lateral direita
	dest.x = (quad_x * TILE_SIZE) + TILE_SIZE - 1;
	dest.y = quad_y * TILE_SIZE;
	dest.w = 1;
	dest.h = TILE_SIZE;
	SDL_FillRect(screen, &dest, SDL_MapRGB(screen->format, 180, 180, 180));
	// topo
	dest.x = quad_x * TILE_SIZE;
	dest.y = quad_y * TILE_SIZE;
	dest.w = TILE_SIZE;
	dest.h = 1;
	SDL_FillRect(screen, &dest, SDL_MapRGB(screen->format, 180, 180, 180));
	// base
	dest.x = quad_x * TILE_SIZE;
	dest.y = (quad_y * TILE_SIZE) + TILE_SIZE - 1;
	dest.w = TILE_SIZE;
	dest.h = 1;
	SDL_FillRect(screen, &dest, SDL_MapRGB(screen->format, 180, 180, 180));
}

void clear_edit_area(SDL_Surface *screen) {
	// lateral esquerda
	dest.x = 193;
	dest.y = 0;
	dest.w = EDIT_AREA_W;
	dest.h = EDIT_AREA_H;
	SDL_FillRect(screen, &dest, SDL_MapRGB(screen->format, 0, 0, 0));
}



void draw_blocked(short int dx, short int dy, SDL_Surface *screen) {
	SDL_Rect src, dest;
	//printf("DEGUG - x: %d y: %d\n", dx, dy);
	src.x = 0;
	src.y = 0;
	src.w = blocked->w;
	src.h = blocked->h;
	//printf("DEBUG 3\n");
	// parte que vai ser colada
	dest.x = dx * 16;
	dest.y = dy * 16;
	dest.w = blocked->w;
	dest.h = blocked->h;
	//printf("DEBUG 4\n");
	SDL_BlitSurface (blocked, &src, screen, &dest);
}

/*
void clear_blocked(short int real_quadx, short int real_quady, short int quadx, short int quady, SDL_Surface *screen) {
	short int n;
	n = quadx + (quady*MAP_W);
	printf("DEBUG - quadx: %d quady: %d, real_quad_x: %d, real_quad_y: %d\n", quadx, quady, real_quadx, real_quady);
	copy_tile((*(p_map+n)).tile.x, (*(p_map+n)).tile.y, real_quadx, real_quady, find_selected_pallete((*(p_map+n)).pallete, -1), screen);
}
*/



void draw_tools() {
	// monta �rea de ferramentas
	tmp = IMG_Load("./data/img/tools/1leftarrow.png");
	sprite = SDL_DisplayFormat(tmp);
	copy_area(sprite, 0, 0, 16, 16, 0, MAX_H-16, editor_screen);
	tmp = IMG_Load("./data/img/tools/1uparrow.png");
	sprite = SDL_DisplayFormat(tmp);
	copy_area(sprite, 0, 0, 16, 16, 16, MAX_H-16, editor_screen);
	tmp = IMG_Load("./data/img/tools/1downarrow.png");
	sprite = SDL_DisplayFormat(tmp);
	copy_area(sprite, 0, 0, 16, 16, 32, MAX_H-16, editor_screen);
	tmp = IMG_Load("./data/img/tools/1rightarrow.png");
	sprite = SDL_DisplayFormat(tmp);
	copy_area(sprite, 0, 0, 16, 16, 48, MAX_H-16, editor_screen);
	// fill completo
	tmp = IMG_Load("./data/img/tools/fill.png");
	sprite = SDL_DisplayFormat(tmp);
	copy_area(sprite, 0, 0, 16, 16, 64, MAX_H-16, editor_screen);
	// fill �rea
	tmp = IMG_Load("./data/img/tools/color_fill.png");
	sprite = SDL_DisplayFormat(tmp);
	copy_area(sprite, 0, 0, 16, 16, 80, MAX_H-16, editor_screen);
	// mudan�a de paleta
	tmp = IMG_Load("./data/img/tools/colorize.png");
	sprite = SDL_DisplayFormat(tmp);
	copy_area(sprite, 0, 0, 16, 16, 96, MAX_H-16, editor_screen);
	// edi��o de cen�rio
	tmp = IMG_Load("./data/img/tools/edit.png");
	sprite = SDL_DisplayFormat(tmp);
	copy_area(sprite, 0, 0, 16, 16, 0, MAX_H-32, editor_screen);
	// bloqueio
	tmp = IMG_Load("./data/img/tools/blocked.png");
	sprite = SDL_DisplayFormat(tmp);
	copy_area(sprite, 0, 0, 16, 16, 16, MAX_H-32, editor_screen);
	// edi��o de tiles n�vel 2
	tmp = IMG_Load("./data/img/tools/desktop.png");
	sprite = SDL_DisplayFormat(tmp);
	copy_area(sprite, 0, 0, 16, 16, 32, MAX_H-32, editor_screen);
	// save
	tmp = IMG_Load("./data/img/tools/filesave.png");
	sprite = SDL_DisplayFormat(tmp);
	copy_area(sprite, 0, 0, 16, 16, 0, MAX_H-48, editor_screen);
}

/*
void save_map() {
	short int i, j, n=0;
	// posiciona-se no in�cio do arquivo
	fseek(fp_map, 0, SEEK_SET);
	for (i=0; i<MAP_W; i++) {
		for (j=0; j<MAP_H; j++) {
			fseek(fp_map, sizeof(struct quadrant)*n, SEEK_SET);
			fwrite((p_map+n), sizeof(struct quadrant), 1, fp_map);
			n++;
		}
	}
	printf("Mapa salvo!\n");
}
*/

void clear_selected_tool_border() {
	// edi��o normal
	if (edit_tool == 0) {
		clear_tile_border(editor_screen, 0, 35);
	// edi��o de bloqueio
	} else if (edit_tool == 2) {
		clear_tile_border(editor_screen, 1, 35);
	// fill area
	} else if (edit_tool == 1) {
		clear_tile_border(editor_screen, 5, 36);
	} else if (edit_tool == 3) {
		clear_tile_border(editor_screen, 2, 35);
	} else {
		printf("DEBUG edit_tool: %d\n", edit_tool);
	}
}

/*
void editor_loop() {
	short int quad_x, quad_y, real_quad_x, real_quad_y;
	int mouse_x, mouse_y;
	short int n;
	// checa por eventos no mouse
	SDL_PumpEvents(); //Checa por eventos ...
	// clicou o botão do mouse
	// TODO - mudar pra qdo solta o botão do mouse
	if (SDL_GetMouseState(&mouse_x, &mouse_y)&SDL_BUTTON(1)) {
		// tem 5 slots na esquerda que são da paleta de tiles
		// pega as coordenadas do clique e calcula em que quadrante foi isso
		real_quad_x = mouse_x / TILE_SIZE;
		real_quad_y = mouse_y / TILE_SIZE;
		// �rea dos tiles
		if (mouse_x <= PALLETE_W && mouse_y <= PALLETE_H) {
			// seleciona tile
			//printf("DEBUG - Área da paleta\n");
			clear_tile_border(editor_screen, sel_pallete.x, sel_pallete.y);
			sel_pallete.x = real_quad_x;
			sel_pallete.y = real_quad_y;
			draw_selected_tile_border(editor_screen, real_quad_x, real_quad_y);
			SDL_Flip(editor_screen);
			// escreve isso no arquivo
		// tem um quadrante que � o de ferramentas e barra de rolagem
		} else if (mouse_x <= PALLETE_W && mouse_y > PALLETE_H) {
			printf("DEBUG - tools\n");
			// screen left
			//printf("DEBUG - map_pos_x: %d, map_pos_y: %d\n", map_pos_x, map_pos_y);
			if (real_quad_x == 0 && real_quad_y == 36) {
				//printf("left\n");
				if (map_pos_x > 0) {
					clear_edit_area(editor_screen);
					copy_area(offscreen, map_pos_x-EDIT_AREA_W, map_pos_y, EDIT_AREA_W, EDIT_AREA_H, 192, 0, editor_screen);
					SDL_Flip(editor_screen);
					map_pos_x -= EDIT_AREA_W;
				}
			} else if (real_quad_x == 3 && real_quad_y == 36) {
				//printf("right\n");
				if (map_pos_x < (MAP_W*16)-EDIT_AREA_W) {
					clear_edit_area(editor_screen);
					copy_area(offscreen, map_pos_x+EDIT_AREA_W, map_pos_y, EDIT_AREA_W, EDIT_AREA_H, 192, 0, editor_screen);
					SDL_Flip(editor_screen);
					map_pos_x += EDIT_AREA_W;
				}
			} else if (real_quad_x == 2 && real_quad_y == 36) {
				//printf("down\n");
				if (map_pos_y < (MAP_H*16)-EDIT_AREA_H) {
					clear_edit_area(editor_screen);
					copy_area(offscreen, map_pos_x, map_pos_y+EDIT_AREA_H, EDIT_AREA_W, EDIT_AREA_H, 192, 0, editor_screen);
					SDL_Flip(editor_screen);
					map_pos_y += EDIT_AREA_H;
				}
			} else if (real_quad_x == 1 && real_quad_y == 36) {
				//printf("up\n");
				if (map_pos_y > 0) {
					clear_edit_area(editor_screen);
					copy_area(offscreen, map_pos_x, map_pos_y-EDIT_AREA_H, EDIT_AREA_W, EDIT_AREA_H, 192, 0, editor_screen);
					SDL_Flip(editor_screen);
					map_pos_y -= EDIT_AREA_H;
				}
			// TOOL - FILL COMPLETO
			} else if (real_quad_x == 4 && real_quad_y == 36) {
				printf("fill-full!\n");
				fill_map(find_selected_pallete(-1, -1), offscreen, sel_pallete.x, sel_pallete.y);
				copy_area(offscreen, map_pos_x, map_pos_y, EDIT_AREA_W, EDIT_AREA_H, 192, 0, editor_screen);
				SDL_Flip(editor_screen);
			// TOOL - FILL AREA
			} else if (real_quad_x == 5 && real_quad_y == 36) {
				//printf("fill-area!\n");
				clear_selected_tool_border();
				draw_selected_tile_border(editor_screen, 5, 36);
				SDL_Flip(editor_screen);
				edit_tool = 1;
			// MUDANÇA DE PALETA DE TILES
			} else if (real_quad_x == 6 && real_quad_y == 36) {
				//printf("change-pallete!\n");
				change_pallete(1);
			// muda modo de edição para edição de blocos ou edição normal
			} else if (real_quad_x == 0 && real_quad_y == 35) {
				printf("TOOL: edit-mode!\n");
				clear_selected_tool_border();
				draw_selected_tile_border(editor_screen, 0, 35);
				// se esta voltando da edição nível 2, muda transparências
				edit_tool = 0;
				change_pallete(0);
				SDL_Flip(editor_screen);
			// muda para edição de bloqueio
			} else if (real_quad_x == 1 && real_quad_y == 35) {
				printf("TOOL: block-mode!\n");
				clear_selected_tool_border();
				draw_selected_tile_border(editor_screen, 1, 35);
				edit_tool = 2;
				change_pallete(0);
				SDL_Flip(editor_screen);
			// muda para edição de nível 2 de tiles
			} else if (real_quad_x == 2 && real_quad_y == 35) {
				printf("TOOL: level2-mode!\n");
				clear_selected_tool_border();
				draw_selected_tile_border(editor_screen, 2, 35);
				// se está vindo da edição nível 1, muda transparências
				edit_tool = 3;
				change_pallete(0);
				SDL_Flip(editor_screen);
			// save
			} else if (real_quad_x == 0 && real_quad_y == 34) {
				printf("save-map!\n");
				save_map();
			}
			SDL_Delay(200);
			//printf("DEBUG - map_pos_x: %d, map_pos_y: %d\n", map_pos_x, map_pos_y);
		} else {
			//printf("DEBUG - area de edicao\n");
			// pega as coordenadas do clique e calcula em que quadrante foi isso
			quad_x = (mouse_x - PALLETE_W + map_pos_x) / TILE_SIZE;
			quad_y = (mouse_y + map_pos_y) / TILE_SIZE;
			//printf("DEBUG - area do editor\n");
			// precisa estar dentro da area possivel do mapa
			printf("DEBUG - map_pos_x: %d, map_pos_y: %d, quad_x: %d, quad_y: %d, real_quad_x: %d, real_quad_y: %d, map_width: %d, map_height: %d\n", map_pos_x, map_pos_y, quad_x, quad_y, real_quad_x, real_quad_y, MAP_W, MAP_H);
			if (edit_tool == 0) {
				if (quad_x < MAP_W && quad_y*16-map_pos_y < EDIT_AREA_H) {
					// copia tile para a area clicada
					copy_tile(sel_pallete.x, sel_pallete.y, real_quad_x, real_quad_y, find_selected_pallete(-1, -1), editor_screen);
					copy_tile(sel_pallete.x, sel_pallete.y, quad_x, quad_y, find_selected_pallete(-1, -1), offscreen);
					SDL_Flip(editor_screen);
					// guarda dados na memoria
					n = quad_x + (quad_y*MAP_W);
					(*(p_map+n)).tile.x = sel_pallete.x;
					(*(p_map+n)).tile.y = sel_pallete.y;
					(*(p_map+n)).pallete = selected_pallete;
				} else {
					printf("Out\n");
				}
			// edicao de tiles nivel 2
			} else if (edit_tool == 3) {
				if (quad_x < MAP_W && quad_y*16-map_pos_y < EDIT_AREA_H) {
					// vazio, seta paleta para -1
					if ((sel_pallete.x == 0 && sel_pallete.y == 0) || (sel_pallete.x < 6 && sel_pallete.y > 6) || (sel_pallete.y > 15)) {
						printf("DEBUG - vazio\n");
						// copia tile para a area clicada
						n = quad_x + (quad_y*MAP_W);
						(*(p_map+n)).tile2.x = -1;
						(*(p_map+n)).tile2.y = -1;
						// limpa cenario
						copy_tile((*(p_map+n)).tile.x, (*(p_map+n)).tile.y, real_quad_x, real_quad_y, find_selected_pallete(-1, 0), editor_screen);
						copy_tile((*(p_map+n)).tile.x, (*(p_map+n)).tile.y, quad_x, quad_y, find_selected_pallete(-1, 0), offscreen);
						SDL_Flip(editor_screen);
					} else {
						printf("DEBUG - cheio\n");
						copy_tile(sel_pallete.x, sel_pallete.y, real_quad_x, real_quad_y, find_selected_pallete(-1, -1), editor_screen);
						copy_tile(sel_pallete.x, sel_pallete.y, quad_x, quad_y, find_selected_pallete(-1, -1), offscreen);
						SDL_Flip(editor_screen);
						// guarda dados na memoria
						n = quad_x + (quad_y*MAP_W);
						(*(p_map+n)).tile2.x = sel_pallete.x;
						(*(p_map+n)).tile2.y = sel_pallete.y;
						(*(p_map+n)).pallete2 = selected_pallete;
					}
				} else {
					printf("Out\n");
				}
			// faz preenchimento de area
			} else if (edit_tool == 1) {
				printf("fill �rea!\n");
				fill_area(find_selected_pallete(-1, -1), offscreen, quad_x, quad_y, sel_pallete.x, sel_pallete.y);
				copy_area(offscreen, map_pos_x, map_pos_y, EDIT_AREA_W, EDIT_AREA_H, 192, 0, editor_screen);
				SDL_Flip(editor_screen);
				edit_tool = 0;
			// faz bloqueio
			} else if (edit_tool == 2) {
				printf("blocking 1\n");
				// bloqueio
				n = quad_x + (quad_y*MAP_W);
				if ((*(p_map+n)).blocked == 0) {
					draw_blocked(real_quad_x, real_quad_y, editor_screen);
					(*(p_map+n)).blocked = 1;
				} else {
					clear_blocked(real_quad_x, real_quad_y, quad_x, quad_y, editor_screen);
					(*(p_map+n)).blocked = 0;
				}
				SDL_Delay(100);
				SDL_Flip(editor_screen);
			} else {
				printf("Erro: tool inválida: '%d'\n", edit_tool);
			}
		}
		SDL_Delay(10);
		//printf("DEBUG - quadrantex: %d quadrantey: %d\n", quad_x, quad_y);
	}
	SDL_PumpEvents(); //Checa por eventos do teclado...
	if ((keystate = SDL_GetKeyState(NULL))!=NULL) {
		if (keystate[SDLK_ESCAPE] || keystate[SDLK_q]) { //Checa o teclado para o pressionamento de ESC ou q...
			printf("\nsaindo...\n");
			fim = 1; 	//... se ESC ou q foi pressionado, sai do jogo...
		}
	}
}



void create_map(short int width, short int height) {
	short int i, j, n=0;
	// cria arquivo
	fp_map = fopen("./data/maps/map01.dat", "wb+");
	// enche o mapa com a estrutura de tiles
	quad.tile.x = 0;
	quad.tile.y = 0;
	quad.event = 0;
	quad.tile2.x = -1;
	quad.tile2.y = -1;
	for (j=0; j<height; j++) {
		for (i=0; i<width; i++) {
			fseek(fp_map, sizeof(struct quadrant)*n, SEEK_SET);
			fwrite(&quad, sizeof(struct quadrant), 1, fp_map);
			n++;
		}
	}
	// escreve tamanho do mapa no final
	fwrite(&width, sizeof(int), 1, fp_map);
	fwrite(&height, sizeof(int), 1, fp_map);
}
*/



void editor_init() {
	SDL_Surface *spriteCopy;

	// pede pelo mapa

	//fp_map = fopen("./data/maps/map01.dat", "rb+");
	//get_map_size();


	// inicializa tela
	editor_screen = SDL_SetVideoMode(EDIT_W, EDIT_H, 16, SDL_SWSURFACE);
	// nao conseguiu criar tela, retorna erro
	if (editor_screen == NULL) {
		fprintf(stderr, "Unable to set %dx%d video: %s\n", EDIT_W, EDIT_H, SDL_GetError());
		exit(1);
	}

	SDL_UpdateRect(editor_screen, 0, 0, EDIT_W, EDIT_H);
	SDL_WM_SetCaption("DS Project - EDITOR", "MAXIMIZE ME");


	draw_tools();

	// cria offscreen para scrolling
	offscreen = SDL_CreateRGBSurface (SDL_HWSURFACE , MAP_W*16, MAP_H*16, 16, 0, 0, 0, 0);


	// posicao da paleta - posiciona bem embaixo da tela
	p_pos[2].x = 0;
	p_pos[2].y = 0;

	tmp = IMG_Load("./data/img/tools/lockoverlay.gif");
	blocked = SDL_DisplayFormat(tmp);
	copy_area(sprite, 0, 0, 16, 16, 1, MAX_H-50, editor_screen);


	// monta area de edicao
	draw_matrix(editor_screen, 192, 0, EDIT_W, EDIT_H);
	//draw_sprite(pallete, 2, editor_screen);

	draw_matrix(editor_screen, 0, 511, 192, 128);

	// indica tile selecionado
	draw_selected_tile_border(editor_screen, 0, 0);

	// indica tool selecionada
	draw_selected_tile_border(editor_screen, 0, 35);


	SDL_Flip(editor_screen); //Atualiza a superficie screen, desenhando o frame na tela.
}



