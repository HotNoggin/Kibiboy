// Using standard i/o and SDL
#include <stdio.h>
#include <SDL.h>

const int VIEWPORT_WIDTH = 640;
const int VIEWPORT_HEIGHT = 480;


int main(int argc, char* args[]) {
	//Set up the window and the surface to draw to the window.
	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;

	//Initialize SDL, log error if it fails.
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL failed to initialize. SDL_Error: %s \n", SDL_GetError());
	}

	else
	{
		//Create the window, log error if it fails.
		window = SDL_CreateWindow("Arcade Maker", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			VIEWPORT_WIDTH, VIEWPORT_HEIGHT, SDL_WINDOW_SHOWN);

		if (window == NULL)
		{
			printf("Failed to create new window. SDL_Error: %s\n", SDL_GetError());
		}

		else
		{
			//Fill and update the screen surface
			screenSurface = SDL_GetWindowSurface(window);
			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
			SDL_UpdateWindowSurface(window);

			//Hack to get window to stay up
			SDL_Event e; bool quit = false; while (quit == false) {
				while (SDL_PollEvent(&e)) { if (e.type == SDL_QUIT) quit = true; } }
		}
	}

	//Destroy window, quit, and terminate
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
	
}