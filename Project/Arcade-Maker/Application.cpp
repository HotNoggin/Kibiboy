// Includes
#include <SDL.h>
#include <string>
#include "Application.h"


// The Application namespace handles window and application operations
namespace Application {


	// Initializes SDL, creates a window, and returns true if successful.
	// window: the pointer to point to the created window
	// title: the name of the window to display
	// w: the width of the window
	// h: the height of the window
	// min_w: the minimim width of the window
	// min_h: the minimum height of the window
	bool initialize(SDL_Window* window, const char* title, int w, int h, int min_w, int min_h) {
		// Init flag, used to return true if successful
		bool success = true;

		// Initialize SDL
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) < 0)
		{
			printf("SDL failed to initialize. SDL_Error: %s\n", SDL_GetError());
			success = false;
		}


		// Create the window with the proper size and minimum size
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h,
			SDL_WINDOW_RESIZABLE);

		if (window == NULL) {
			printf("SDL failed to create window. SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else {
			SDL_SetWindowMinimumSize(window, min_w, min_h);
		}

		return success;
	}


	// Destroys the window and quits SDL
	void close(SDL_Window* window) {
		// Destroy window
		SDL_DestroyWindow(window);
		window = NULL;

		// Quit SDL
		SDL_Quit();
	}
}