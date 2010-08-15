#ifndef PLAYER_AND_NPC_H
#define PLAYER_AND_NPC_H

void create_kill_animation(short x, short y);
void create_hit_animation(short x, short y);
void drawExplosion(short int centerX, short int centerY);
void got_weapon(char boss_name[50]);


struct struct_projectile {
	int x;
	int y;
	int x0;
	int y0;
	int y1;
	int timer;
	int status0; // progress
	int status1; // flag for inversion, etc
	short int type;
	short int direction;
	SDL_Surface* sprite;
};

struct struct_move_info {
	unsigned long int time;
	unsigned short int distance;
	unsigned short int status;
	struct coordinate initial_position;
};

struct npc_struct {
	short int HP;
	char name[50];
	short int x, y;
	short int shield;
	struct npc_struct *next;
	short int can_shoot;
	short int shots;
	short int direction;
	short int IA;
	struct struct_move_info move_info;
	struct struct_npcSpriteGraphics *graphics;
	struct sprite_struct *sprite_list;
	unsigned short int is_boss;
	struct struct_projectile projectile;
	int timer;
};

struct struct_items {
	unsigned short int energy_tanks;
	unsigned short int weapon_tanks;
	unsigned short int lifes;
};

struct player_struct {
	short int HP;
	short int HP_MAX;
	char name[20];
	short int x, y;
	short int shield;
	struct sprite_struct *sprite;
	short int jumpButtonReleased;
	short int attackButtonReleased;
	struct player_struct *next;
	short int hit;
	short int direction;
	short int shots;
	short int teleporter;			// holds the teleporting link used last time, so that the user won't use the same one whil not leaving it
	unsigned long int jump_timer;		// holds the time when player jumped, used to calc the jump size if he releases the jump button quickly
	short int jump_mark;
	unsigned int hit_timer;                          // holds the time when player was hit, used to calc the time player will remain invulnerable
	short int platform_n;		// number of the object that player is over. used to move player together with the platform
	char face_filename[50];
	unsigned short int jump_max;
	unsigned short int shots_max;
	struct struct_items items;
};

struct npc_struct *npc_list = NULL;
struct player_struct *pc_list = NULL;


struct npc_struct *add_npc(short int x, short int y) {
	int i;
	struct npc_struct *temp, *new_npc;

	new_npc = (struct npc_struct *)malloc(sizeof(struct npc_struct));
	new_npc->next = NULL;
	new_npc->graphics = NULL;
	new_npc->x = x;
	new_npc->y = y;
	new_npc->shield = 0;
	new_npc->shots = 0;
	new_npc->direction = ANIM_LEFT;
	new_npc->IA = 0;
	new_npc->timer = 0;
	new_npc->move_info.distance = 0;
	new_npc->move_info.time = 0;
	new_npc->move_info.status = 0;
	new_npc->move_info.initial_position.x = 0;
	new_npc->move_info.initial_position.y = 0;
	new_npc->projectile.type = -1;
	new_npc->projectile.x = -1;
	new_npc->projectile.y = -1;
	new_npc->projectile.x0 = -1;
	new_npc->projectile.y0 = -1;
	new_npc->projectile.status0 = 0;
	new_npc->projectile.status1 = 0;
	new_npc->projectile.sprite = NULL;
	new_npc->projectile.direction = ANIM_RIGHT;
	new_npc->is_boss = 0;
	if (npc_list == NULL) {
		npc_list = new_npc;
	} else {
		temp = npc_list;
		i = 1;	// must start in one to count the first element
		if (temp != NULL) {
			while (temp->next != NULL) {
				temp = temp->next;
				i++;
			}
		}
		temp->next = new_npc;
	}
	return new_npc;
}

struct npc_struct *getNPCN(int n) {
	int i;
	struct npc_struct *temp;
	temp = npc_list;
	for (i=0; i<n; i++) {
		// did not reached desired number, return NULL
		if (i<n-1 && temp->next == NULL) {
			return NULL;
		} else if (temp->next != NULL) {
			temp = temp->next;
		}
	}
	return temp;
}

int delete_npc(int n) {
	int i;
	struct npc_struct *temp1=NULL, *temp2=NULL;
	temp1 = npc_list;
	for (i=0; i<n; i++) {
		temp2 = temp1;
		if (temp1->next != NULL) {
			temp1 = temp1->next;
		// failed to reach the desired number, return error
		} else {
			return 0;
		}
	}

	if (temp1 != NULL) {
		temp2->next = temp1->next;
	} else {
		temp2->next = NULL;
	}
	return 1;
}



// modificar game.h->colision_verify para usar a player_list no lugar da sprite_list
// eliminar sprite_list e usar apenas npc->sprite e player->sprite
int add_player(void) {
	int i=0;
	struct player_struct *temp, *new_player;
	new_player = (struct player_struct*)malloc(sizeof(struct player_struct));
	new_player->next=NULL;
	new_player->attackButtonReleased=0;
	new_player->jumpButtonReleased=0;
	new_player->hit = 0;
	new_player->HP = INITIAL_HP;
	new_player->HP_MAX = INITIAL_HP;
	new_player->shots = 0;
	new_player->teleporter = -1;
	new_player->jump_mark = 0;
	new_player->jump_max = 54;
	new_player->shots_max = 3;
	new_player->hit_timer = 0;

	new_player->items.energy_tanks = 0;
	new_player->items.weapon_tanks = 0;
	new_player->items.lifes = 3;

	if (player_list == NULL) {
		player_list = new_player;
		return 0;
	} else {
		temp = player_list;
		for (i=0; temp->next != NULL; i++) {
			temp = temp->next;
		}
		temp->next = new_player;
		return (i+1);
	}
}

struct player_struct *getPlayerN(int n) {
	int i;
	struct player_struct *temp;
	temp = player_list;
	for (i=0; i<n; i++) {
		// did not reached desired number, return NULL
		if (i<n-1 && temp->next == NULL) {
			return NULL;
		} else if (temp->next != NULL) {
			temp = temp->next;
		}
	}
	return temp;
}

int delete_player(int n) {
	int i;
	struct player_struct *temp1=NULL, *temp2=NULL;
	temp1 = player_list;
	for (i=0; i<n; i++) {
		temp2 = temp1;
		if (temp1->next != NULL) {
			temp1 = temp1->next;
		// failed to reach the desired number, return error
		} else {
			return 0;
		}
	}

	if (temp1 != NULL) {
		temp2->next = temp1->next;
	} else {
		temp2->next = NULL;
	}
	return 1;
}

void damage_npc(struct npc_struct *temp_npc, short int damage) {
	temp_npc->HP = temp_npc->HP - damage;
	if (temp_npc->HP <= 0) {
		create_kill_animation(temp_npc->x, temp_npc->y);
		play_sfx(SFX_NPC_HIT);
		if (temp_npc->is_boss == 1) {
			//printf("is boss, must show demo end, npc.x: %d, map_pos_x: %d\n", temp_npc->x, map_pos_x);
			drawExplosion(temp_npc->x+map_pos_x, temp_npc->y);
			got_weapon(temp_npc->name);
			//demo_ending();
		}
	} else {
		create_hit_animation(temp_npc->x, temp_npc->y);
		play_sfx(SFX_NPC_KILLED);
	}
}


#endif // PLAYER_AND_NPC_H
