// Includes
#include <stdio.h>
#include <SDL.h>
#include <string>
#include "Canvas.h"
#include "Application.h"



// The renderer to handle drawing in the game window
SDL_Renderer* renderer = NULL;
// The window to render to
SDL_Window* window = NULL;


int main(int argc, char* args[]) {

	// Initialize SDL
	if (!Application::initialize(window, "Arcade Maker", 
		Canvas::CANVAS_WIDTH, Canvas:: CANVAS_HEIGHT,
		Canvas::CANVAS_WIDTH, Canvas::CANVAS_HEIGHT)) {
		printf("Application failed to initialize. \n");
	}
	else
	{
		// When this is set to true, the rendering loop stops and the application quits
		bool quit = false;

		SDL_Event event;
		SDL_Surface* canvasSurface = NULL;
		canvasSurface = Canvas::createCanvasSurface();

		if (canvasSurface == NULL) {
			printf("Canvas surface failed to initialize. SDL Error: %s\n", SDL_GetError());
		}
		else {
		
			// Main Loop
			while (!quit) {

				// 1. Event Handling:
				// Check all polled (queued) events. If there is an event, it is put in "event".
				// SDL_PollEvent returns 0 if there are no events, which will stop the loop
				while (SDL_PollEvent(&event) != 0) {
					// If the event is a quit event, quit!
					if (event.type == SDL_QUIT) {
						quit = true;
					}
				}

				Canvas::updateScreen(window, canvasSurface);
			}
		}
	}

	// Free resources and close SDL
	Application::close(window);
	return 0;
}

