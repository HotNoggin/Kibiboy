// Includes
#include <string>
#include <iostream>
#include "Application.h"


// Initializes SDL, creates a window, and returns true if successful.
// window: the pointer to point to the created window
// title: the name of the window to display
// w: the width of the window
// h: the height of the window
// min_w: the minimim width of the window
// min_h: the minimum height of the window
bool Application::initialize(const char* title, int w, int h, int min_w, int min_h) {
	// Init flag, used to return true if successful
	bool success = true;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) < 0)
	{
		std::cout << "SDL failed to initialize. SDL_Error: \n";
		std::cout << SDL_GetError();
		success = false;
	}


	// Create the window with the proper size and minimum size
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h,
		SDL_WINDOW_RESIZABLE);

	if (window == NULL) {
		std::cout << "SDL failed to create window. SDL_Error: \n";
		std::cout << SDL_GetError();
		success = false;
	}
	else {
		SDL_SetWindowMinimumSize(window, min_w, min_h);
	}

	return success;
}


// Destroys the window and quits SDL
void Application::close() {
	// Free surface
	SDL_FreeSurface(SDL_GetWindowSurface(window));
	// Destroy window
	SDL_DestroyWindow(window);
	window = NULL;

	// Quit SDL
	SDL_Quit();
}