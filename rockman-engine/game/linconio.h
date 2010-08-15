#include <termios.h>

void highvideo(void) {
	printf("\033[1m");
}

void normvideo(void) {
	printf("\033[0m");
}

void lowvideo(void) {
	printf("\033[2m");
}

// seta cor do texto
void textcolor(int color) {
	printf("\x1b[3%dm", color);
}

// posiciona o cursor
void gotoxy(int x, int y) {
	printf("\x1b[%d;%dH", y, x);
}

void textbackground(int color) {
	printf("\x1b[4%dm", color);
}

void clrscr(void) {
	printf("\x1B[2J");
}


char getch(void) {
	char ch;
	// from http://www.c-for-dummies.com/lessons/linux/04/
    struct termios new_settings, stored_settings;
    tcgetattr(0,&stored_settings);
    new_settings = stored_settings;
    new_settings.c_lflag &= (~ICANON);
    new_settings.c_cc[VTIME] = 0;
    tcgetattr(0,&stored_settings);
    new_settings.c_cc[VMIN] = 1;
    tcsetattr(0,TCSANOW,&new_settings);

	// getch part
	ch = getchar();

	// from http://www.c-for-dummies.com/lessons/linux/04/
	tcsetattr(0,TCSANOW,&stored_settings);
	return ch;
}

