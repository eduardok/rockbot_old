//------------------- FROM COMMON .H ----------------------------------

void move_screen(SDL_Surface *screen, short int x_inc, short int y_inc);

// copia um tile de um lugar para outro
void copy_tile(const short int tx, const short int ty, const short int dx, const short int dy, SDL_Surface *screen_source, SDL_Surface *screen_dest);

// copia um tile de um lugar para outro
//void copy_area(SDL_Surface *screen_source, short int src_x, short int src_y, short int src_w, short int src_h, short int dest_x, short int dest_y, SDL_Surface *screen_dest);
void copy_area(SDL_Surface *screen_source, int src_x, int src_y, int src_w, int src_h, int dest_x, int dest_y, SDL_Surface *screen_dest);

void draw_matrix(SDL_Surface *screen, short int x, short int y, short int width, short int height);

// retorna paleta usada, ou paleta que corresponde ao número dado
SDL_Surface *find_selected_pallete(short int n, short int level);

// posiciona o ponteiro do arquivo no quadrante dado
void seek_map_pos(short int x, short int y);

void fill_map(SDL_Surface *screen_source, SDL_Surface *screen_dest, short int x, short int y);

void fill_area(SDL_Surface *screen_source, SDL_Surface *screen_dest, short int x, short int y, short int pallete_x, short int pallete_y);

// seta map_width e map_height com o tamanho do arquivo lido
void get_map_size();

void read_map(SDL_Surface *screen, short int adjust, short int draw_borders);

void read_map_tile(SDL_Surface *screen, short int x, short int y, short int adjust);

//Limpa a tela. Essa função é necessária já que não podemos utilizar a função SDL_FreeSurface na tela principal, a screen.
void clear_screen(SDL_Surface *screen);

// Nessa função desenharemos o paddle do jogador...
void draw_sprite(short int sprite_n, SDL_Surface *screen);


//------------------- FROM EDITOR .H ----------------------------------
void draw_edit_screen_border(SDL_Surface *screen);

void draw_selected_tile_border(SDL_Surface *screen, short int quad_x, short int quad_y);

void clear_tile_border(SDL_Surface *screen, short int quad_x, short int quad_y);

void clear_edit_area(SDL_Surface *screen);

void draw_blocked(short int dx, short int dy, SDL_Surface *screen);

void change_pallete(short int inc);

void draw_tools(void);

void save_map(void);

void editor_loop(void);

void create_map(short int width, short int height);

void ask_map(void);

void editor_init(void);



//------------------- FROM GAME .H ----------------------------------


// diz se pode mover o sprite para esta posição ou o local é um muro, etc
short int colision_verify(short int x_inc, short int y_inc, short int sprite_n);
void move_player(struct player_struct *pObj);
short int game_init();
void openInGameMenu();

//------------------- FROM INTRO .H ----------------------------------

void animStars();
void demo_ending();


//------------------- FROM CONFIG.H ----------------------------------

void inGameMenu();
void showDialog(char face[255], char *lines);
void createDialogBG();
void resetDialog();
void removeDialog();
void showCredits();

//------------------- FROM INPUT.H ----------------------------------
void clean_input();

//------------------- FROM GRAPHICS.H ----------------------------------
void draw_text(short int x, short int y, char *text, SDL_Surface *screen);
SDL_Surface *surface_region_from_image(char filename[255], int w, int h);

// TRANSFER.H
void bossDoorHit(int tileX, int tileY, struct player_struct *playerObj);

struct coordinate pick_stage();
