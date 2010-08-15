void build_pallete(char filename[50], SDL_Surface *pallete) {
	// carrega paleta
	tmp = IMG_Load(filename);
	sprite = SDL_DisplayFormat(tmp);
	// monta paleta
	draw_matrix(sprite, 0, 0, 192, 256);
	copy_area(sprite, 0, 0, 192, 256, 0, 0, pallete);
	draw_matrix(sprite, 192, 0, 192, 256);
	copy_area(sprite, 192, 0, 192, 256, 0, 257, pallete);
}

SDL_Surface *find_selected_pallete() {
	if (selected_pallete == 0) {
		return pallete;
	} else if (selected_pallete == 1) {
		return pallete1;
	}
}

void change_pallete() {
	if (selected_pallete < 1) {
		selected_pallete += 1;
	} else {
		selected_pallete = 0;
	}
	// mostra nova paleta na tela
	copy_area(find_selected_pallete(), 0, 0, 192, 512, 0, 0, editor_screen);
}
