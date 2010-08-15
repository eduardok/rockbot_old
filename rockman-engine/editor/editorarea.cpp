#include "editorarea.h"
#include <stdio.h>
#include <QBrush>
#include <QDir>
#include "defines.h"
#include <QResource>

extern file_game game;
extern file_map map;
extern char FILEPATH[255];

// construtor
EditorArea::EditorArea(QWidget *parent) : QWidget(parent) {
    myParent = parent;
    int i, j;
	strcpy(map.filename, "data/images/tilesets/default.png");
    for (i=0; i<MAP_W; i++) {
        for (j=0; j<MAP_H; j++) {
            map.tiles[i][j].tile1.x = -1;
            map.tiles[i][j].tile1.y = -1;
        }
    }
    temp = 0;
    editor_selectedTileX = 0;
    editor_selectedTileY = 0;
    my_pallete=NULL;
    this->show();
}

void EditorArea::changeTile() {
	printf("DEBUG.changeTile in editor area\n");
	temp = 1;
	repaint();
}

void EditorArea::setInfoPalette(EditorTilePallete *temp_pallete) {
   if (temp_pallete != NULL) {
      printf("DEBUG.EditorArea::setPallete - got pallete\n");
   } else {
      printf("DEBUG.EditorArea::setPallete - null pallete\n");
   }
   my_pallete = temp_pallete;
}

void EditorArea::paintEvent(QPaintEvent *) {
    int i, j, pos;
    QPainter painter(this);
    QLineF *line;
    QString *filename;
    //printf("DEBUG - EditorArea.paintEvent\n");
    // draw the picked tile in the tileset
    //QLine *line;
    //QLineF line(10.0, 80.0, 90.0, 20.0);
    QRectF target(QPoint(10, 20), QSize(30, 30));
    QRectF source(QPoint(100, 100), QSize(30, 30));
    char buffer[255];

    filename = new QString("");
	filename->append(my_pallete->getPallete());
    QPixmap image(*filename);
    if (image.isNull()) {
        printf("ERROR: EditorArea::paintEvent - Could not load image file '%s'\n", qPrintable(*filename));
    }
    // draw tiles
    for (i=0; i<MAP_W; i++) {
        for (j=0; j<MAP_H; j++) {
            // level one
            if (map.tiles[i][j].tile1.x != -1 && map.tiles[i][j].tile1.y != -1) {
                QRectF target(QPoint(i*16, j*16), QSize(16, 16));
                QRectF source(QPoint((map.tiles[i][j].tile1.x*16), (map.tiles[i][j].tile1.y*16)), QSize(16, 16));
                painter.drawPixmap(target, image, source);
            }
            // level two
            if (dataExchanger->layerLevel == 2 || dataExchanger->layerLevel == 3) {
                    //printf(">> EditorArea::paintEvent - SHOW TILES LEVEL 2\n");
                    if (map.tiles[i][j].tile2.x != -1 && map.tiles[i][j].tile2.y != -1) {
                        QRectF target(QPoint(i*16, j*16), QSize(16, 16));
                        QRectF source(QPoint((map.tiles[i][j].tile2.x*16), (map.tiles[i][j].tile2.y*16)), QSize(16, 16));
                        painter.drawPixmap(target, image, source);
                    }
            }
            if (dataExchanger->layerLevel == 3) {
                    if (map.tiles[i][j].tile3.x != -1 && map.tiles[i][j].tile3.y != -1) {
                        QRectF target(QPoint(i*16, j*16), QSize(16, 16));
                        QRectF source(QPoint((map.tiles[i][j].tile3.x*16), (map.tiles[i][j].tile3.y*16)), QSize(16, 16));
                        painter.drawPixmap(target, image, source);
                    }
            }
			// locked areas, stairs, doors, etc
			if (map.tiles[i][j].locked != 0 && dataExchanger->editTool == EDITMODE_LOCK) {
                    // transparent rectangle
					//painter.setBrush(QColor(255, 0, 0, 30));
					//painter.drawRect(i*16, j*16, 16, 16);
                    // red border
                    painter.setBrush(Qt::NoBrush);
                    painter.setPen(QColor(255, 0, 0, 255));
                    painter.drawRect(i*16, j*16, 16, 16);
					// terrain type icon
					QString terrainIcon;
					QResource::registerResource("resources/icons/icons.qrc");
					if (map.tiles[i][j].locked == 1) {
						terrainIcon = QString::fromUtf8(":/toolbar_icons/Lock"); // solid
					} else if (map.tiles[i][j].locked == 2) {
						terrainIcon = QString(":/toolbar_icons/stairs.png"); // stairs
					} else if (map.tiles[i][j].locked == 3) {
						terrainIcon = QString(":/toolbar_icons/object-order-lower.png"); // door
					} else if (map.tiles[i][j].locked == 4) {
						terrainIcon = QString(":/toolbar_icons/edit-delete.png"); // spikes
					} else if (map.tiles[i][j].locked == 5) {
						terrainIcon = QString(":/toolbar_icons/flag-blue.png"); // water
					} else if (map.tiles[i][j].locked == 6) {
						terrainIcon = QString(":/toolbar_icons/flag-green.png"); // ice
					} else if (map.tiles[i][j].locked == 7) {
						terrainIcon = QString(":/toolbar_icons/arrow-left.png"); // move left
					} else if (map.tiles[i][j].locked == 8) {
						terrainIcon = QString(":/toolbar_icons/arrow-right.png"); // move right
					}
					QPixmap terrainImage(terrainIcon);
					if (terrainImage.isNull()) {
						printf("ERROR: EditorArea::paintEvent - terrainType - Could not load image file '%s'\n", qPrintable(terrainIcon));
					} else {
						terrainIcon.resize(16);
						painter.setOpacity(0.7);
						QRectF target(QPoint(i*16, j*16), QSize(16, 16));
						QRectF source(QPoint(0, 0), QSize(terrainImage.width (), terrainImage.height ()));
						painter.drawPixmap(target, terrainImage, source);
					}
					painter.setOpacity(1.0);
			}
        }
    }
    painter.setPen(QColor(120, 120, 120));
    for (i=1; i<MAP_W; i++) {
        pos = i*16-1;
        //QLineF line(0, 800, 16, 800);
        // linhas horizontais
        line = new QLineF(pos, 0, pos, MAP_H*16-1);
        painter.drawLine(*line);
    }
    for (i=1; i<MAP_H; i++) {
        pos = i*16-1;
        //QLineF line(0, 800, 16, 800);
        // linhas verticais
        line = new QLineF(0, pos, MAP_W*16-1, pos);
        painter.drawLine(*line);
    }
    // draw links
    printf("editoMode: %d, EDITMODE_NORMAL: %d, editTool: %d, EDITMODE_LINK_DEST: %d\n", dataExchanger->editMode, EDITMODE_NORMAL, dataExchanger->editTool, EDITMODE_LINK_DEST);
    if (dataExchanger->editMode == EDITMODE_NORMAL && (dataExchanger->editTool == EDITMODE_LINK_DEST || dataExchanger->editTool == EDITMODE_LINK)) {
            printf("EditorArea::paintEvent - showing links\n");
            for (i=0; i<LINKS_NUMBER; i++) {
                    if (dataExchanger->currentMap == game.map_links[i].map_origin && game.map_links[i].link_pos.x != -1 && game.map_links[i].link_pos.y != -1) {
                            // transparent blue rectangle
                            painter.setBrush(QColor(0, 0, 255, 180));
                            painter.drawRect(game.map_links[i].link_pos.x*16, game.map_links[i].link_pos.y*16, 16, 16);
                            // blue border
                            painter.setBrush(Qt::NoBrush);
                            painter.setPen(QColor(0, 0, 255, 255));
                            painter.drawRect(game.map_links[i].link_pos.x*16, game.map_links[i].link_pos.y*16, 16, 16);
                    } else if (dataExchanger->currentMap == game.map_links[i].map_dest && game.map_links[i].link_dest.x != -1 && game.map_links[i].link_dest.y != -1) {
                            // transparent cyan rectangle
                            painter.setBrush(QColor(0, 255, 255, 180));
                            painter.drawRect(game.map_links[i].link_dest.x*16, game.map_links[i].link_dest.y*16, 16, 16);
                            // cyan border
                            painter.setBrush(Qt::NoBrush);
                            painter.setPen(QColor(0, 255, 255, 255));
                            painter.drawRect(game.map_links[i].link_dest.x*16, game.map_links[i].link_dest.y*16, 16, 16);
                    }
            }
    }
    // draw NPCs
    //if (dataExchanger->editMode == EDITMODE_ADDNPC) {
    for (j=0; j<STAGE_NPC_LIMIT; j++) {
            //printf("DEBUG - looking for npcs - hp.totoal: %d\n", map.npc_list[j].hp.total);
            if (map.npc_list[j].hp.total >= 0) {
					//printf("DEBUG.EditorArea::paintEvent - must draw NPC %d\n", j);
					sprintf(buffer, "%s/data/images/sprites/enemies/%s", FILEPATH, map.npc_list[j].filename);
                    QPixmap temp_image(buffer);
                    if (temp_image.isNull()) {
						printf("EditorArea::paintEvent - Could not load NPC image file '%s', npc.hp: %d\n", buffer, map.npc_list[j].hp.total);
					} else {
                            QRectF target(QPoint(map.npc_list[j].start_point.x*16, map.npc_list[j].start_point.y*16), QSize(map.npc_list[j].framesize_w, map.npc_list[j].framesize_h));
                            QRectF source(QPoint(0, 0), QSize(map.npc_list[j].framesize_w, map.npc_list[j].framesize_h));
                            painter.drawPixmap(target, temp_image, source);
                    }
            }
    }
    //}

	// draw Objects
	for (j=0; j<STAGE_OBJECT_LIMIT; j++) {
			//printf("DEBUG - looking for npcs - hp.totoal: %d\n", map.npc_list[j].hp.total);
			if (map.object_list[j].type >= 0) {
				//printf("DEBUG.EditorArea::paintEvent - must draw OBJECT %d, type: %d\n", j, map.object_list[j].type);
				sprintf(buffer, "%s/data/images/sprites/objects/%s", FILEPATH, map.object_list[j].filename);
				QPixmap temp_image(buffer);
				if (temp_image.isNull()) {
						//printf("EditorArea::paintEvent DEBUG.Editor - Could not load OBJECT image file '%s'\n", buffer);
						painter.setBrush(QColor(255, 255, 255, 180));
						painter.drawRect(map.object_list[j].start_point.x*16, map.object_list[j].start_point.y*16, 16, 16);
				} else {
						QRectF target(QPoint(map.object_list[j].start_point.x*16, map.object_list[j].start_point.y*16), QSize(map.object_list[j].framesize_w, map.object_list[j].framesize_h));
						QRectF source(QPoint(0, 0), QSize(map.object_list[j].framesize_w, map.object_list[j].framesize_h));
						painter.drawPixmap(target, temp_image, source);
				}
			}
	}


   QSize resizeMe(MAP_W*16, MAP_H*16);
   this->resize(resizeMe);
   myParent->adjustSize();
   //myParent->setGeometry(tempRect);
}

void EditorArea::mouseMoveEvent(QMouseEvent *event) {
	QPoint pnt = event->pos();
	if (editor_selectedTileX != pnt.x()/16 || editor_selectedTileY != pnt.y()/16) {
		mousePressEvent(event);
	}
}

void EditorArea::mousePressEvent(QMouseEvent *event) {
    int i;
    int foundNPC = -1;

	printf("INSIDE EditorArea::mousePressEvent, editMode: %d, editTool: %d, EDITMODE_NPC: %d\n", dataExchanger->editMode, dataExchanger->editTool,EDITMODE_NPC);

    QPoint pnt = event->pos();
    editor_selectedTileX = pnt.x()/16;
    editor_selectedTileY = pnt.y()/16;
	//printf("DEBUG - selectedTileX: %d, selectedTileY: %d, edit-stairs: %d\n", editor_selectedTileX, editor_selectedTileY, EDITMODE_STAIRS);
	if (dataExchanger->editMode == EDITMODE_NORMAL) {
		if (dataExchanger->editTool == EDITMODE_NORMAL) {
			if (dataExchanger->layerLevel == 1) {
				map.tiles[editor_selectedTileX][editor_selectedTileY].tile1.x = dataExchanger->getPalleteX();
				map.tiles[editor_selectedTileX][editor_selectedTileY].tile1.y = dataExchanger->getPalleteY();
			} else if (dataExchanger->layerLevel == 2) {
				map.tiles[editor_selectedTileX][editor_selectedTileY].tile2.x = dataExchanger->getPalleteX();
				map.tiles[editor_selectedTileX][editor_selectedTileY].tile2.y = dataExchanger->getPalleteY();
			} else if (dataExchanger->layerLevel == 3) {
				printf(">> EditorArea::mousePressEvent - placing tile 3\n");
				map.tiles[editor_selectedTileX][editor_selectedTileY].tile3.x = dataExchanger->getPalleteX();
				map.tiles[editor_selectedTileX][editor_selectedTileY].tile3.y = dataExchanger->getPalleteY();
			}
		} else if (dataExchanger->editTool == EDITMODE_ERASER) {
			if (dataExchanger->layerLevel == 1) {
				map.tiles[editor_selectedTileX][editor_selectedTileY].tile1.x = -1;
				map.tiles[editor_selectedTileX][editor_selectedTileY].tile1.y = -1;
			} else if (dataExchanger->layerLevel == 2) {
				map.tiles[editor_selectedTileX][editor_selectedTileY].tile2.x = -1;
				map.tiles[editor_selectedTileX][editor_selectedTileY].tile2.y = -1;
			} else if (dataExchanger->layerLevel == 3) {
				map.tiles[editor_selectedTileX][editor_selectedTileY].tile3.x = -1;
				map.tiles[editor_selectedTileX][editor_selectedTileY].tile3.y = -1;
			}
		} else if (dataExchanger->editTool == EDITMODE_LOCK) {
			if (map.tiles[editor_selectedTileX][editor_selectedTileY].locked == 0) {
				map.tiles[editor_selectedTileX][editor_selectedTileY].locked = dataExchanger->terrainType;
			} else {
				map.tiles[editor_selectedTileX][editor_selectedTileY].locked = 0;
			}

	} else if (dataExchanger->editTool == EDITMODE_FILL) {
			fill_area();
	} else if (dataExchanger->editTool == EDITMODE_LINK) {
			//fill_area();
			printf(">> EditorArea::mousePressEvent - LINK\n");
			// checks if a link in this position already exits to remove it
			for (i=0; i<LINKS_NUMBER; i++) {
				if ((game.map_links[i].map_origin == dataExchanger->currentMap && game.map_links[i].link_pos.x == editor_selectedTileX && game.map_links[i].link_pos.y == editor_selectedTileY) || (game.map_links[i].map_dest == dataExchanger->currentMap && game.map_links[i].link_dest.x == editor_selectedTileX && game.map_links[i].link_dest.y == editor_selectedTileY)) {
					game.map_links[i].map_origin = -1;
					game.map_links[i].map_dest = -1;
					printf(">> EditorArea::mousePressEvent - REMOVE LINK\n");
					repaint();
					return;
				}
			}
			// search for a free slot
			int freeSlot = -1;
			for (i=0; i<LINKS_NUMBER; i++) {
				if (game.map_links[i].map_origin == -1) {
					printf(">> EditorArea::mousePressEvent - FOUND FREE LINK SLOT\n");
					// TODO - use free slot, check if none is free, warn user
					dataExchanger->editTool = EDITMODE_LINK_DEST;
					// map loading must save map
					game.map_links[i].map_origin = dataExchanger->currentMap;
					game.map_links[i].link_pos.x=editor_selectedTileX;
					game.map_links[i].link_pos.y=editor_selectedTileY;
					game.map_links[i].link_size = 1;
					game.map_links[i].link_type = LINK_VERTICAL;			// can be LINK_VERTICAL OR LINK_HORIZONTAL
					game.map_links[i].link_bidi=1;							// indicates if it is bidirecional
					game.map_links[i].is_door=0;							// if it is a door, it is not bidiand willmake door sound and show animation of door opening/closing
					freeSlot = i;
					break;
				} else {
					printf("Link position %d used by %d\n", i, game.map_links[i].map_origin);
				}
			}
			if (freeSlot == -1) {
				QMessageBox::warning(this, "Error", "All link slots already used.");
			}
		}  else if (dataExchanger->editTool == EDITMODE_LINK_DEST) {
			//fill_area();
			printf(">> EditorArea::mousePressEvent - LINK-DEST\n");
			for (i=0; i<LINKS_NUMBER; i++) {
				if (game.map_links[i].map_origin != -1 && (game.map_links[i].map_dest == -1)) {
					printf(">> EditorArea::mousePressEvent - LINK-DEST - found origin\n");
					// TODO - use free slot, check if none is free, warn user
					// use map_backup variable
					game.map_links[i].link_dest.x=editor_selectedTileX;
					game.map_links[i].link_dest.y=editor_selectedTileY;
					game.map_links[i].map_dest = dataExchanger->currentMap;
					dataExchanger->editTool = EDITMODE_LINK;
					break;
				}
			}
		}
	} else if (dataExchanger->editMode == EDITMODE_NPC) {
		printf(">> EditorArea::mousePressEvent - EDITMODE_NPC\n");
		for (i=0; i<STAGE_NPC_LIMIT; i++) {
			// removing npc from the map
			if (map.npc_list[i].hp.total != -1 && map.npc_list[i].start_point.x == editor_selectedTileX &&  map.npc_list[i].start_point.y == editor_selectedTileY) {
				foundNPC=i;
				break;
			}
			// must check is one npc is selected in the list to add it
		}
		printf(">> EDITMODE_NPC, foundNPC: %d\n", foundNPC);
		if (dataExchanger->editTool == EDITMODE_ERASER && foundNPC != -1) {
			printf(">> EditorArea::mousePressEvent - Removing NPC\n");
			map.npc_list[foundNPC].hp.total = -1;
			map.npc_list[foundNPC].start_point.x = -1;
			map.npc_list[foundNPC].start_point.y = -1;
			foundNPC=1;
		} else if (dataExchanger->editTool == EDITMODE_NORMAL && foundNPC == -1 && dataExchanger->selectedNPC != -1) {
			printf(">> EditorArea::mousePressEvent - Adding NPC\n");
			addNpcToMap(editor_selectedTileX, editor_selectedTileY);
		} else if (dataExchanger->editTool == EDITMODE_NORMAL && foundNPC != -1 && dataExchanger->selectedNPC != -1) {
			printf(">> EditorArea::mousePressEvent - Adding NPC - place already taken\n");
		}
	} else if (dataExchanger->editMode == EDITMODE_OBJECT) {
		printf(">> EditorArea::mousePressEvent - EDITMODE_OBJECT\n");
		for (i=0; i<STAGE_OBJECT_LIMIT; i++) {
			// removing npc from the map
			if (map.object_list[i].type != -1 && map.object_list[i].start_point.x == editor_selectedTileX &&  map.object_list[i].start_point.y == editor_selectedTileY) {
				foundNPC=i;
				break;
			}
			// must check is one npc is selected in the list to add it
		}
		printf(">> EDITMODE_OBJECT, foundObject: %d, dataExchanger->selectedNPC: %d\n", foundNPC, dataExchanger->selectedNPC);
		if (foundNPC != -1) {
			printf(">> EditorArea::mousePressEvent - Removing Object\n");
			map.object_list[foundNPC].type = -1;
			map.object_list[foundNPC].start_point.x = -1;
			map.object_list[foundNPC].start_point.y = -1;
			foundNPC=1;
		} else {
			if (dataExchanger->selectedNPC != -1) {
				printf(">> EditorArea::mousePressEvent - Adding Object\n");
				addObjectToMap(editor_selectedTileX, editor_selectedTileY);
			} else {
				printf(">> EditorArea::mousePressEvent - No object selected to be placed\n");
			}
		}
	}
    temp = 1;
    repaint();
}


void EditorArea::fill_area() {
	int i, j;
	int filled1=0;
	int filled2=0;
	int originalX, originalY;
	short int *searchX, *searchY;

	if (dataExchanger->layerLevel == 1) {
		originalX = map.tiles[editor_selectedTileX][editor_selectedTileY].tile1.x;
		originalY = map.tiles[editor_selectedTileX][editor_selectedTileY].tile1.y;
	} else if (dataExchanger->layerLevel == 2) {
		originalX = map.tiles[editor_selectedTileX][editor_selectedTileY].tile2.x;
		originalY = map.tiles[editor_selectedTileX][editor_selectedTileY].tile2.y;
	} else if (dataExchanger->layerLevel == 3) {
		originalX = map.tiles[editor_selectedTileX][editor_selectedTileY].tile3.x;
		originalY = map.tiles[editor_selectedTileX][editor_selectedTileY].tile3.y;
	}
	// área a esquerda
	for (i=editor_selectedTileX; i>=0; i--) {
		// área acima
		filled1 = 0;
		filled2 = 0;
		for (j=editor_selectedTileY; j>=0; j--) {
			if (dataExchanger->layerLevel == 1) {
				searchX = &map.tiles[i][j].tile1.x;
				searchY = &map.tiles[i][j].tile1.y;
			} else if (dataExchanger->layerLevel == 2) {
				searchX = &map.tiles[i][j].tile2.x;
				searchY = &map.tiles[i][j].tile2.y;
			} else if (dataExchanger->layerLevel == 3) {
				searchX = &map.tiles[i][j].tile3.x;
				searchY = &map.tiles[i][j].tile3.y;
			}
			//printf("DEBUG.EditorArea::i: %d, j: %d, fill_area - tile.x: %d, tile;y: %d, originalX: %d, originalY: %d\n", i, j, map.tiles[i][j].tile1.x, map.tiles[i][j].tile1.y, originalX, originalY);
			if (*searchX == originalX && *searchY == originalY) {
				*searchX = dataExchanger->getPalleteX();
				*searchY = dataExchanger->getPalleteY();
				filled1 = 1;
			} else {
				printf("1.not filling\n");
				break;
			}
		}
		// área abaixo
		for (j=editor_selectedTileY+1; j<MAP_H; j++) {
			if (dataExchanger->layerLevel == 1) {
				searchX = &map.tiles[i][j].tile1.x;
				searchY = &map.tiles[i][j].tile1.y;
			} else if (dataExchanger->layerLevel == 2) {
				searchX = &map.tiles[i][j].tile2.x;
				searchY = &map.tiles[i][j].tile2.y;
			} else if (dataExchanger->layerLevel == 3) {
				searchX = &map.tiles[i][j].tile3.x;
				searchY = &map.tiles[i][j].tile3.y;
			}
			if (*searchX == originalX && *searchY == originalY) {
				*searchX = dataExchanger->getPalleteX();
				*searchY = dataExchanger->getPalleteY();
				filled2 = 1;
			} else {
				printf("2.not filling\n");
				break;
			}
		}
		if (filled1 == 0 && filled2 == 0) {
			break;
		}

	}
	// area a direita
	for (i=editor_selectedTileX+1; i<MAP_W; i++) {
		filled1 = 0;
		filled2 = 0;
		for (j=editor_selectedTileY; j>=0; j--) {
			//printf("DEBUG.EditorArea::i: %d, j: %d, fill_area - tile.x: %d, tile;y: %d, originalX: %d, originalY: %d\n", i, j, map.tiles[i][j].tile1.x, map.tiles[i][j].tile1.y, originalX, originalY);
			if (dataExchanger->layerLevel == 1) {
				searchX = &map.tiles[i][j].tile1.x;
				searchY = &map.tiles[i][j].tile1.y;
			} else if (dataExchanger->layerLevel == 2) {
				searchX = &map.tiles[i][j].tile2.x;
				searchY = &map.tiles[i][j].tile2.y;
			} else if (dataExchanger->layerLevel == 3) {
				searchX = &map.tiles[i][j].tile3.x;
				searchY = &map.tiles[i][j].tile3.y;
			}
			if (*searchX == originalX && *searchY == originalY) {
				*searchX = dataExchanger->getPalleteX();
				*searchY = dataExchanger->getPalleteY();
				filled1 = 1;
			} else {
				printf("3.not filling\n");
				break;
			}
		}
		// área abaixo
		for (j=editor_selectedTileY+1; j<MAP_H; j++) {
			if (dataExchanger->layerLevel == 1) {
				searchX = &map.tiles[i][j].tile1.x;
				searchY = &map.tiles[i][j].tile1.y;
			} else if (dataExchanger->layerLevel == 2) {
				searchX = &map.tiles[i][j].tile2.x;
				searchY = &map.tiles[i][j].tile2.y;
			} else if (dataExchanger->layerLevel == 3) {
				searchX = &map.tiles[i][j].tile3.x;
				searchY = &map.tiles[i][j].tile3.y;
			}
			if (*searchX == originalX && *searchY == originalY) {
				*searchX = dataExchanger->getPalleteX();
				*searchY = dataExchanger->getPalleteY();
				filled2 = 1;
			} else {
				printf("4.not filling\n");
				break;
			}
		}
		if (filled1 == 0 || filled2 == 0) {
			break;
		}
	}
}

void EditorArea::saveMap(int game_n, int map_n) {
	char filename[255], buffer[255];
	char temp_cent_number[4];
/*
	int j;
	for (j=0; j<STAGE_NPC_LIMIT; j++) {
		map.npc_list[j].hp.total = -1;
	}
*/
/*	int j, k;
    for (j=0; j<MAP_W; j++) {
        for (k=0; k<MAP_H; k++) {
			if ((map.tiles[j][k].tile1.x != -1 || map.tiles[j][k].tile1.y) != -1 && (map.tiles[j][k].tile1.x != 0 || map.tiles[j][k].tile1.y != 0)) {
                printf("SAVE - tile1.x: %d, tile1.y: %d\n", map.tiles[j][k].tile1.x, map.tiles[j][k].tile1.y);
            }
        }
    }
*/




	dataExchanger->centNumberFormat(game_n);
	sprintf(temp_cent_number, "%s", dataExchanger->centNumber);
	dataExchanger->centNumberFormat(map_n);

	sprintf(buffer, "%s/data/game/game_%s/", FILEPATH, temp_cent_number);
	if (!QDir(buffer).exists()) {
		//printf("Creating '%s folder\n", buffer);
		QDir().mkdir(buffer);
	}

	sprintf(filename, "%s/data/game/game_%s/%s.map", FILEPATH, temp_cent_number, dataExchanger->centNumber);
	//printf("DEBUG.EditorArea::saveMap - filename: %s\n", filename);
    FILE *fp = fopen(filename, "wb");
	fwrite(&map, sizeof(map), 1, fp);
    fclose(fp);
}

void EditorArea::saveGame(int game_n) {
	char filename[255];
	if (game_n == 0) {
		game_n++;
	}


	// ******************* HARDCODED VARIABLES ******************* //
	sprintf(game.zones[0].bg_filename, "%s", "stage_select.png");
	game.zones[0].stages[0].initial_map_number = 1;
	game.zones[0].stages[0].initial_point.x = 0;
	game.zones[0].stages[0].initial_point.y = 0;
	// ******************* HARDCODED VARIABLES ******************* //

	//printf("DEBUG.EditorArea::saveGame - game_n: %d, map_n: %d\n", game_n, dataExchanger->currentMap);
	dataExchanger->centNumberFormat(game_n);
	sprintf(filename, "%s/data/game/%s.gme", FILEPATH, dataExchanger->centNumber);

	FILE *fp = fopen(filename, "wb");
	fwrite(&game, sizeof(game), 1, fp);
	fclose(fp);

	saveMap(game_n, dataExchanger->currentMap);
}

void EditorArea::addNpcToMap(int posx, int posy) {
	int i;
	// checks if there is a npc in this position
	for (i=0; i<STAGE_NPC_LIMIT; i++) {
		if (map.npc_list[i].hp.total != -1 && map.npc_list[i].start_point.x == posx && map.npc_list[i].start_point.y == posy) {
			QMessageBox msgBox;
			msgBox.setText("There is a NPC in this point already");
			msgBox.exec();
			return;
		}
	}

	for (i=0; i<STAGE_NPC_LIMIT; i++) {
		if (map.npc_list[i].hp.total == -1) {
			//printf("DEBUG.EditorArea::addNpcToMap - adding npc to position %d in list.\n", i);
			//printf("DEBUG.EditorArea::addNpcToMap - 1.i: %d, npc.hp: %d\n", i, map.npc_list[i].hp.total);
			dataExchanger->placeNpc(posx, posy, i);
			//printf("DEBUG.EditorArea::addNpcToMap - 2.npc.hp: %d\n", map.npc_list[i].hp.total);
			return;
		}
	}
}

void EditorArea::addObjectToMap(int posx, int posy) {
	int i;
	// checks if there is a npc in this position
	for (i=0; i<STAGE_OBJECT_LIMIT; i++) {
		if (map.object_list[i].type != -1 && map.object_list[i].start_point.x == posx && map.object_list[i].start_point.y == posy) {
			QMessageBox msgBox;
			msgBox.setText("There is a Object in this point already");
			msgBox.exec();
			return;
		}
	}

	for (i=0; i<STAGE_OBJECT_LIMIT; i++) {
		if (map.object_list[i].type == -1) {
			//printf("DEBUG.EditorArea::addObjectToMap - adding object to position %d in list.\n", i);
			printf("DEBUG.EditorArea::addObjectToMap - 1.i: %d, object.type: %d\n", i, map.object_list[i].type);
			dataExchanger->placeObject(posx, posy, i);
			printf("DEBUG.EditorArea::addObjectToMap - 2.object.type: %d\n", map.object_list[i].type);
			return;
		}
	}
}
