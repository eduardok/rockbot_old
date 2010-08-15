#ifndef SOUND_NDS_H
#define SOUND_NDS_H


void draw_text(short int x, short int y, char *text, SDL_Surface *screen);

int previousSFX = 0;

void init_audio() {
	// AUDIO INIT
	mmInitDefaultMem((mm_addr)soundbank_bin);
	mmSelectMode(MM_MODE_C);

	// load the music module
	mmLoad( MOD_FLATOUTLIES );

	// Start playing module
	mmSetModuleVolume(512);
	mmStart( MOD_FLATOUTLIES, MM_PLAY_LOOP );
}


void play_sfx(int sfxN) {
	mmEffectCancel(ndsSFXhandler[previousSFX]);
	ndsSFXhandler[sfxN] = mmEffectEx(&ndsSFX[sfxN]);
	previousSFX = sfxN;
}

void load_all_sfx() {
	int i;
	for (i = 0; i < MSL_BANKSIZE; i++) {
		mmLoadEffect(i);
		mm_sound_effect s;
		s.id = i;
		s.rate = 1024;
		s.handle = 0;
		s.volume = 220;
		s.panning = 128;
		ndsSFX[i] = s;
	}
}

void close_audio() {
	int i;
	for (i = 0; i < MSL_BANKSIZE; i++) {
		mmUnloadEffect(i);
	}
}

void load_music(char *music_file) {}

void sound_loop() {
}

void play_midi_file(char *filename) {}

void stop_music() {}


#endif // SOUND_NDS_H
