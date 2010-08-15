#ifndef TRANSFER_H
#define TRANSFER_H

void drawMap3rdLevelWithoutBossDoor(SDL_Surface *screen) {
    extern SDL_Surface *tileset;
    int i, j;

    for (i=0; i<MAP_W; i++) {
        for (j=0; j<MAP_H; j++) {
            if (map.tiles[i][j].tile3.x != -1 && map.tiles[i][j].tile3.y != -1) {
                // must check if the position is visible in the screen
                //printf(">> common.h::drawMap3rdLevel - scrollX: %d, scrollY: %d, posX: %d, posY: %d, MAX_W: %d\n", scrollX, scrollY, (i*TILE_SIZE), (j*16),MAX_W);
				if (i*TILE_SIZE >= -map_pos_x-TILE_SIZE && i*TILE_SIZE <= -map_pos_x+MAX_W+TILE_SIZE) {
                    //printf(">> common.h::drawMap3rdLevel - X OK\n");
                    if (j*TILE_SIZE >= scrollY-TILE_SIZE && j*TILE_SIZE <= scrollY+MAX_H+TILE_SIZE) {
                        //printf(">> common.h::drawMap3rdLevel - Y OK\n");
						if (map.tiles[i][j].locked != TERRAIN_DOOR) {
							copy_area(tileset, map.tiles[i][j].tile3.x*TILE_SIZE, map.tiles[i][j].tile3.y*TILE_SIZE, TILE_SIZE, TILE_SIZE, (i*TILE_SIZE)+map_pos_x, (j*TILE_SIZE)-scrollY, screen);
                        }
                    }
                }
                //copy_area(tileset, map.tiles[i][j].tile2.x*TILE_SIZE, map.tiles[i][j].tile2.y*TILE_SIZE, TILE_SIZE, TILE_SIZE, i*TILE_SIZE, j*TILE_SIZE, offscreen);
            }
        }
    }
}

void redrawBossDoor(int isClose, int nTiles) {
    int tilePieces = nTiles*4;
    int i, j, k, tileCount;

	waitTime(300);
    for (k=0; k<tilePieces; k++) {
        tileCount = nTiles;
        move_screen(game_screen, 0, 0);
        for (i=0; i<MAP_W; i++) {
            for (j=0; j<MAP_H; j++) {
                if (map.tiles[i][j].tile3.x != -1 && map.tiles[i][j].tile3.y != -1) {
                    // must check if the position is visible in the screen
                    //printf(">> common.h::drawMap3rdLevel - scrollX: %d, scrollY: %d, posX: %d, posY: %d, MAX_W: %d\n", scrollX, scrollY, (i*TILE_SIZE), (j*16),MAX_W);
					if (i*TILE_SIZE >= -map_pos_x-TILE_SIZE && i*TILE_SIZE <= -map_pos_x+MAX_W+TILE_SIZE) {
                        //printf(">> common.h::drawMap3rdLevel - X OK\n");
                        if (j*TILE_SIZE >= scrollY-TILE_SIZE && j*TILE_SIZE <= scrollY+MAX_H+TILE_SIZE) {
                            //printf(">> common.h::drawMap3rdLevel - Y OK\n");
							if (map.tiles[i][j].locked == TERRAIN_DOOR) {
                                //printf(">>> tileCount: %f, k*0.25: %f\n", tileCount, (k*0.25));
                                if (isClose == 0) {
                                    if (tileCount > k*0.25) {
										copy_area(tileset, map.tiles[i][j].tile3.x*TILE_SIZE, map.tiles[i][j].tile3.y*TILE_SIZE, TILE_SIZE, TILE_SIZE, (i*TILE_SIZE)+map_pos_x, (j*TILE_SIZE)-scrollY, game_screen);
                                    }
                                } else {
                                    if (tileCount < k*0.25) {
										copy_area(tileset, map.tiles[i][j].tile3.x*TILE_SIZE, map.tiles[i][j].tile3.y*TILE_SIZE, TILE_SIZE, TILE_SIZE, (i*TILE_SIZE)+map_pos_x, (j*TILE_SIZE)-scrollY, game_screen);
                                    }
                                }
                                tileCount--;
                            } else {
								copy_area(tileset, map.tiles[i][j].tile3.x*TILE_SIZE, map.tiles[i][j].tile3.y*TILE_SIZE, TILE_SIZE, TILE_SIZE, (i*TILE_SIZE)+map_pos_x, (j*TILE_SIZE)-scrollY, game_screen);
                            }
                        }
                    }
                    //copy_area(tileset, map.tiles[i][j].tile2.x*TILE_SIZE, map.tiles[i][j].tile2.y*TILE_SIZE, TILE_SIZE, TILE_SIZE, i*TILE_SIZE, j*TILE_SIZE, offscreen);
                }
            }
        }
        show_sprite(p1Obj->sprite, game_screen);
        draw_hp_bar(p1Obj);
        SDL_Flip(game_screen);
        #ifndef NINTENDODS
			waitTime(80);
        #else
			waitTime(1);
        #endif
    }
	waitTime(300);
}

void bossDoorHit(int tileX, int tileY, struct player_struct *playerObj) {
    int i, multi, isLeft=0, upTile, downTile, tilePieces=0;

    printf(">>>> PLAYER HIT THE BOSS DOOR, will move %d\n", RES_W);
    multi = (RES_W)/(TILE_SIZE+playerObj->sprite->w);
    printf(">>>> bossDoorHit - multi: %d\n", multi);

    printf(">>>> PLAYER IS ON LEFT OF BOSS DOOR\n");
    if (playerObj->sprite->x < tileX*TILE_SIZE-TILE_SIZE*0.5) {
        isLeft = 1;
    }
    upTile = tileY;
    for (i=tileY; i>=0; i--) {
		if (map.tiles[tileX][i].locked == TERRAIN_DOOR) {
            upTile = i;
        } else {
            break;
        }
    }
    downTile = tileY;
    for (i=tileY; i<MAP_H; i++) {
		if (map.tiles[tileX][i].locked == TERRAIN_DOOR) {
            downTile = i;
        } else {
            break;
        }
    }
    redrawBossDoor(0, (downTile-upTile+1));
    printf(">>>> tileY: %d, upTile: %d, downTile: %d, tilePieces: %d\n", tileY, upTile, downTile, tilePieces);

    for (i=0; i<RES_W-TILE_SIZE; i++) {
        if (isLeft) {
            map_pos_x -= 1;
			scrollX += 1;
            if (i%multi == 0) {
                playerObj->sprite->x = playerObj->sprite->x+1;
            }
        } else {
            map_pos_x += 1;
			scrollX -= 1;
            if (i%multi == 0) {
                playerObj->sprite->x = playerObj->sprite->x-1;
            }
        }
        move_screen(game_screen, 0, 0);
        drawMap3rdLevelWithoutBossDoor(game_screen);
        show_sprite(playerObj->sprite, game_screen);
        draw_hp_bar(playerObj);
        SDL_Flip(game_screen);
        #ifndef NINTENDODS
			waitTime(6);
        #endif
    }
    redrawBossDoor(1, (downTile-upTile+1));
}


#endif // TRANSFER_H
