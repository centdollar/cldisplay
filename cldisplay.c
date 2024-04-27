#include "./cldisplay.h"

int main(int argc, char* argv[]) {

	UNUSED(argv);
	UNUSED(argc);

	// Creates the char buffer for the screen

	Screen * screen = malloc(sizeof(Screen));
	screen->width = WIDTH;
	screen->height = HEIGHT;
	for (size_t i = 0; i < HEIGHT; i++) {
		for(size_t j = 0; j < WIDTH; j++) {
			if(rand()%2) {
				screen->buffer[i*HEIGHT + j] = ' ';
			}
			else {
				screen->buffer[i*HEIGHT + j]  = '#';
			}
		}
	}

	for(size_t i = 0; i < 100; i++){
		printScreen(screen->buffer, screen->height, screen->width);
		conways(screen);
		//printScreen(screen->bufferNext, screen->height, screen->width);
		for (size_t i = 0; i < screen->height; i++) {
			for(size_t j = 0; j < screen->width; j++) {
				screen->buffer[i*screen->height + j] = screen->bufferNext[i*screen->height + j];
			}
		}
		sleep(1);
		printf("\033c");
	}


	printf("Hello World\n");
	free(screen);
	return 0;

}
