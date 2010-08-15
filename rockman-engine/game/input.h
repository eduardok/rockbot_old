#define KEYX 0
#define KEYY 1
#define KEYJUMP 2
#define KEYATTACK 3
#define KEYQUIT 4
#define KEYSTART 5

/*
 PC - PS2-USB joystick
 TRIANGLE: 0
 CIRCLE: 1
 x: 2
 SQUARE: 3
 L2: 4
 R2: 5
 L1: 6
 L2: 7
 SELECT: 8
 START: 9
 L3: 10
 R3: 11
 */

#ifndef PLAYSTATION
#define JOY_TRIANGLE 0
#define JOY_CIRCLE 1
#define JOY_X 2
#define JOY_SQUARE 3
#define JOY_L2 4
#define JOY_R2 5
#define JOY_L1 6
#define JOY_R1 7
#define JOY_SELECT 8
#define JOY_START 9
#define JOY_L3 10
#define JOY_R3 11
#else
#ifdef NINTENDODS
#define JOY_TRIANGLE 3
#define JOY_CIRCLE 2
#define JOY_X 1
#define JOY_SQUARE 0
#define JOY_L2 7
#define JOY_R2 9
#define JOY_L1 6
#define JOY_R1 8
#define JOY_SELECT 4
#define JOY_START 5
#define JOY_L3 10
#define JOY_R3 11
#else
#define JOY_TRIANGLE 3
#define JOY_CIRCLE 2
#define JOY_X 1
#define JOY_SQUARE 0
#define JOY_L2 7
#define JOY_R2 9
#define JOY_L1 6
#define JOY_R1 8
#define JOY_SELECT 4
#define JOY_START 5
#define JOY_L3 10
#define JOY_R3 11
#endif
#endif

void updateJoyMove();


void clean_input() {
	int i;
	for (i = 0; i < KEYNUMBER; i++) {
		keyState[0][i] = '0';
		keyState[1][i] = '0';
	}
}

void read_input(int game_mode) {

	clean_input();
	
#ifndef NINTENDODS

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
			break;
		case SDL_JOYAXISMOTION:
			if (event.jaxis.axis == 0) {
				if (event.jaxis.value < -JOYVAL) {
					MOVE_RIGHT[event.jaxis.which] = 0;
					MOVE_LEFT[event.jaxis.which] = 1;
				} else if (event.jaxis.value > JOYVAL) {
					MOVE_LEFT[event.jaxis.which] = 0;
					MOVE_RIGHT[event.jaxis.which] = 1;
				} else if (event.jaxis.value < 700 || event.jaxis.value > -700) {
					MOVE_LEFT[event.jaxis.which] = 0;
					MOVE_RIGHT[event.jaxis.which] = 0;
				}
			}
			if (event.jaxis.axis == 1) {
				if (event.jaxis.value < -JOYVAL) {
					MOVE_DOWN[event.jaxis.which] = 0;
					MOVE_UP[event.jaxis.which] = 1;
				} else if (event.jaxis.value > JOYVAL) {
					MOVE_UP[event.jaxis.which] = 0;
					MOVE_DOWN[event.jaxis.which] = 1;
				} else if (event.jaxis.value < 700 || event.jaxis.value > -700) {
					MOVE_UP[event.jaxis.which] = 0;
					MOVE_DOWN[event.jaxis.which] = 0;
				}
			}
			break;

			// TODO - use SDL_JOYBUTTONUP to measure the time of jump
		case SDL_JOYBUTTONDOWN:
			printf("DEBUG - button pressed, number: %d, witch: %d\n", event.jbutton.button, event.jbutton.which);
			if (event.jbutton.button == JOY_X) {
				keyState[event.jbutton.which][KEYJUMP] = '1';
				if (game_mode == 1) {
					struct player_struct *playerObj = getPlayerN(event.jbutton.which);
					playerObj->jump_timer = SDL_GetTicks();
				}
			}
			if (event.jbutton.button == JOY_START) {
				keyState[event.jbutton.which][KEYSTART] = '1';
			}
			if (event.jbutton.button == JOY_SELECT) {
				keyState[event.jbutton.which][KEYQUIT] = '1';
			}
			if (event.jbutton.button == JOY_SQUARE) {
				keyState[event.jbutton.which][KEYATTACK] = '1';
			}
			if (event.jbutton.button == JOY_TRIANGLE) {
				game_config.sound_enabled = !game_config.sound_enabled;
			}

			break;
		case SDL_JOYBUTTONUP:
			//printf("DEBUG - button released, number: %d\n", event.jbutton.button);
			if (game_mode == 1 && event.jbutton.button == JOY_X) {
				struct player_struct *playerObj = getPlayerN(event.jbutton.which);
				if ((playerObj->jump_timer + 300 > SDL_GetTicks()) && (playerObj->sprite->frame_animation[ANIM_STATUS] == 1)) {
					playerObj->sprite->frame_animation[ANIM_STATUS] = 2;
					playerObj->jump_mark = playerObj->sprite->frame_animation[ANIM_PROCESS];
					playerObj->sprite->frame_animation[ANIM_PROCESS] = 0;
				}
			}
			break;
		case SDL_QUIT:
			leave_game();
			exit(-1);

		}
		//printf(">>>>> keystate[0]: %s, keystate[1]: %s\n", keyState[0], keyState[1]);
	}

#ifndef PLAYSTATION
	SDL_PumpEvents(); //Checa por eventos do teclado...
	int pk_n = 0;
	if (game_config.two_players == 2) {
		pk_n = 1;
	}
	keyRead = SDL_GetKeyState(NULL);
	if (keyRead[SDLK_ESCAPE] || keyRead[SDLK_q]) { //Checa o teclado para o pressionamento de ESC ou q...
		//printf("\nsaindo...\n");
		//fim = 1; 	//... se ESC ou q foi pressionado, sai do jogo...
		keyState[pk_n][KEYQUIT] = '1';
	}
	if (keyRead[SDLK_UP]) {
		MOVE_DOWN[pk_n] = 0;
		MOVE_UP[pk_n] = 2;
	} else if (keyRead[SDLK_DOWN]) {
		MOVE_DOWN[pk_n] = 2;
		MOVE_UP[pk_n] = 0;
	} else {
		if (MOVE_DOWN[pk_n] == 2) {
			MOVE_DOWN[pk_n] = 0;
		}
		if (MOVE_UP[pk_n] == 2) {
			MOVE_UP[pk_n] = 0;
		}
	}
	if (keyRead[SDLK_LEFT]) {
		MOVE_LEFT[pk_n] = 2;
		MOVE_RIGHT[pk_n] = 0;
	} else if (keyRead[SDLK_RIGHT]) {
		MOVE_LEFT[pk_n] = 0;
		MOVE_RIGHT[pk_n] = 2;
	} else {
		if (MOVE_LEFT[pk_n] == 2) {
			MOVE_LEFT[pk_n] = 0;
		}
		if (MOVE_RIGHT[pk_n] == 2) {
			MOVE_RIGHT[pk_n] = 0;
		}
	}
	if (keyRead[SDLK_x]) {
		//joy_jump=1;
		keyState[pk_n][KEYJUMP] = '1';
	}
	if (keyRead[SDLK_a]) {
		keyState[pk_n][KEYATTACK] = '1';
	}
	if (keyRead[SDLK_RETURN]) {
		keyState[pk_n][KEYSTART] = '1';
	}
#endif
	if (game_mode != 1) {
		updateJoyMove();
	}
#else
        scanKeys();
        u16 keys = keysHeld();
        if (keys & KEY_LEFT) {
                keyState[0][KEYX]='2';
        } else if (keys & KEY_RIGHT) {
                keyState[0][KEYX]='1';
        }
        if (keys & KEY_UP) {
                keyState[0][KEYY]='2';
        } else if (keys & KEY_DOWN) {
                keyState[0][KEYY]='1';
        }
        if (keys & KEY_A) {
                keyState[0][KEYJUMP]='1';
        }
        if (keys & KEY_B) {
                keyState[0][KEYATTACK]='1';
        }
        if (keys & KEY_START) {
                keyState[0][KEYSTART]='1';
        }
#endif
}

void updateJoyMove() {
    int player_n;
    for (player_n = 0; player_n < game_config.two_players; player_n++) {
        if (MOVE_LEFT[player_n]) {
                keyState[player_n][KEYX] = '2';
        }
        if (MOVE_RIGHT[player_n]) {
                keyState[player_n][KEYX] = '1';
        }
        if (MOVE_UP[player_n]) {
                keyState[player_n][KEYY] = '2';
        }
        if (MOVE_DOWN[player_n]) {
                keyState[player_n][KEYY] = '1';
        }
    }
}

void wait_player_start() {
	printf("DEBUG.wait_player_start - START\n");

	// this small wait is meant to not get keystrokes still in execution (kind of wait to clear the cache)
	waitTime(50);

	//printf("DEBUG.wait_player_start - after delay\n");
	while (1) {
		read_input(0);
		//printf("DEBUG.wait_player_start - myKeyState1: %s, myKeyState2: %s\n", keyState[0], keyState[1]);
		if (keyState[0][KEYSTART] == '1' || keyState[1][KEYSTART] == '1') {
			//printf("DEBUG.intro_screen - KEYSTART - leaving title\n");
			break;
		} else if (keyState[0][KEYQUIT] == '1' || keyState[1][KEYQUIT] == '1') {
			//printf("DEBUG - pressed ESC 1\n");
			leave_game();
			exit(-1);
		}
                exec_colorcycle(game_screen);
	}
}


void wait_player_key() {
    // this small wait is meant to not get keystrokes still in execution (kind of wait to clear the cache)
    waitTime(50);

    //printf("DEBUG.wait_player_start - after delay\n");
    while (1) {
            read_input(0);
            //printf("DEBUG.wait_player_start - myKeyState1: %s, myKeyState2: %s\n", keyState[0], keyState[1]);
            if (keyState[0][KEYSTART] == '1' || keyState[1][KEYSTART] == '1') {
                //printf("DEBUG.intro_screen - KEYSTART - leaving title\n");
                break;
            } else if (keyState[0][KEYJUMP] == '1' || keyState[1][KEYJUMP] == '1') {
                break;
            } else if (keyState[0][KEYATTACK] == '1' || keyState[1][KEYATTACK] == '1') {
                break;
            } else if (keyState[0][KEYQUIT] == '1' || keyState[1][KEYQUIT] == '1') {
                //printf("DEBUG - pressed ESC 1\n");
                leave_game();
                exit(-1);
            }
            exec_colorcycle(game_screen);
    }
}

int waitScapeTime(int wait_period) {
	//SDL_Delay(50);
#ifndef PLAYSTATION
	waitTime(50);
#endif
	int now_time = 0;
	now_time = getTimer();
	wait_period = now_time + wait_period;
	while (now_time < wait_period) {
		read_input(0);
		if (keyState[0][KEYSTART] == '1' || keyState[1][KEYSTART] == '1') {
			return 1;
		} else if (keyState[0][KEYQUIT] == '1' || keyState[1][KEYQUIT] == '1') {
			//printf("DEBUG - pressed ESC 2\n");
			leave_game();
			exit(-1);
		}
		now_time = getTimer();
		exec_colorcycle(game_screen);
#ifdef PLAYSTATION
		RotateThreadReadyQueue(_MIXER_THREAD_PRIORITY);
#endif
	}
	return 0;
}
