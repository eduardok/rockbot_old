#ifndef DIALOGS_H
#define DIALOGS_H


/*
#define DIALOG_MAX_STAGE 20
#define DIALOG_MAX_PLACES 2
#define DIALOG_MAX_PARTS 4

struct struct_dialog {
	char face_filename[20];
	char name[20];
	char phrase[3][23];
};

// n1 is the stage number (0 intro), n2 is the start stage or boss dialog, n4 is the phrase (max of 4)
struct struct_dialog dialog_list[DIALOG_MAX_STAGE][DIALOG_MAX_PLACES];
*/

void init_dialogs() {
	int i, j, k, l;
	char playerName[50];
	char playerFace[50];

	if (game_config.two_players == 2 || game_config.selected_player == 1) {
		sprintf(playerName, "Rockbot");
		sprintf(playerFace, "rockbot.png");
	} else {
		sprintf(playerName, "Betabot");
		sprintf(playerFace, "betabot.png");
	}

	for (i=0; i<DIALOG_MAX_STAGE; i++) {
		for (j=0; j<DIALOG_MAX_PLACES; j++) {
			for (k=0; k<DIALOG_MAX_PARTS; k++) {
				sprintf(dialog_list[i][j][k].face_filename, "\0");
				sprintf(dialog_list[i][j][k].name, "\0");
				for (l=0; l<3; l++) {
					sprintf(dialog_list[i][j][k].phrase[j], "\0");
				}
			}
		}
	}
	// 0 - APE BOT
	sprintf(dialog_list[1][0][0].face_filename, "apebot.png");
	sprintf(dialog_list[1][0][0].name, "Ape Bot");
	sprintf(dialog_list[1][0][0].phrase[0], "UK! UK! WELCOME TO MY");
	sprintf(dialog_list[1][0][0].phrase[1], "JUNGLE. UK!");
	sprintf(dialog_list[1][0][1].face_filename, playerFace);
	sprintf(dialog_list[1][0][1].name, playerName);
	sprintf(dialog_list[1][0][1].phrase[0], "I HOPE YOU HAVE SOME");
	sprintf(dialog_list[1][0][1].phrase[1], "BANANAS WITH YOU,");
	sprintf(dialog_list[1][0][1].phrase[2], "'CAUSE I'LL TAKE IT!");

}

void show_dialog(int n, int place) {
	char phrase[70];
	int k;

	if (strlen(dialog_list[n][place][0].face_filename) <= 0) {
		return;
	}
	for (k=0; k<DIALOG_MAX_PARTS; k++) {
		if (strstr(dialog_list[n][place][k].face_filename, ".png")) {
			//printf("DEBUG.show_dialog, face_filename: %s\n", dialog_list[n][place][k].face_filename);
			sprintf(phrase, "%s\n%s\n%s\0", dialog_list[n][place][k].phrase[0], dialog_list[n][place][k].phrase[1], dialog_list[n][place][k].phrase[2]);
			showDialog(dialog_list[n][place][k].face_filename, phrase);
			resetDialog();
		}
	}
	removeDialog();
	clean_input();
	waitTime(200);
}

#endif // DIALOGS_H
