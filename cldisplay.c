#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>

#define WIDTH 100
#define HEIGHT 30

#define UNUSED(x) (void)(x)


typedef struct Screen {

	unsigned int width;
	unsigned int height;
	char buffer[WIDTH*HEIGHT];
	char bufferNext[WIDTH*HEIGHT];
} Screen;


void printScreen(char *buffer, const unsigned int height, const unsigned int width);

void printScreen(char *buffer, const unsigned int height, const unsigned int width) {
	
	for (size_t i = 0; i < height; i++) {
		char buf[width + 1];
		for(size_t j = 0; j < width; j++) {
			buf[j] = *(buffer + i*height + j);
		}
		puts(buf);
	}
}

void conways(Screen* screen);

void conways(Screen* screen) {
	char live = '#';
	char dead = ' ';	
	for (size_t i = 0; i < screen->height; i++) {
		for(size_t j = 0; j < screen->width; j++) {
			char cell = (screen->buffer[i*screen->height + j]);
			char upbor = screen->buffer[i*screen->height + j - screen->width];
			char downbor = screen->buffer[i*screen->height + j + screen->width];
			char leftbor = screen->buffer[i*screen->height + j - 1];
			char rightbor = screen->buffer[i*screen->height + j + 1];
			int numLiveNeighbors = 0;
			char nextCell = ' ';
			if(upbor == live) {
				numLiveNeighbors++;
			}
			if(downbor == live) {
				numLiveNeighbors++;
			}
			if(leftbor == live) {
				numLiveNeighbors++;
			}
			if(rightbor == live) {
				numLiveNeighbors++;
			}
			if(numLiveNeighbors > 4) {
				printf("ERROR");
			}
			if(cell == live) {
				if(numLiveNeighbors < 2){
					nextCell = dead;	
				}
				if(numLiveNeighbors == 2 || numLiveNeighbors == 3){
					nextCell = live;	
				}
				if(numLiveNeighbors > 3){
					nextCell = dead;	
				}
			}
			else {
				if(numLiveNeighbors == 3) {
					nextCell = live;
				}
			}
			screen->bufferNext[i*screen->height + j] = nextCell;
		}
	}

}

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
