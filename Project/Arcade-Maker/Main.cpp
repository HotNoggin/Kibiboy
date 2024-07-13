// Includes
#include <iostream>
#include <SDL.h>
#include <string>
#include "Canvas.h"
#include "Application.h"
#include "Colors.h"


int main(int argc, char* args[]) {

	// Initialize SDL and launch the application
	Application* app = new Application();
	bool appSuccess = app->initialize("Arcade Maker",
		Canvas::WIDTH, Canvas::HEIGHT,
		Canvas::WIDTH, Canvas::HEIGHT);
	// Create and initialize the canvas
	Canvas* canvas = new Canvas();
	bool canvasSuccess = canvas->initialize(SDL_GetWindowPixelFormat(app->window));

	// Handle failures
	if (!appSuccess) {
		std::cout << "Application failed to initialize.\n";
	}
	else if (!canvasSuccess) {
		std::cout << "Canvas failed to initialize.\n";
	}

	// Total success!
	else
	{
		// When this is set to true, the rendering loop stops and the application quits
		bool quit = false;
		// The most recent event, to be set by SDL_PollEvent and checked in the main loop
		SDL_Event event;

		// Main Loop
		while (!quit) {

			// Event Handling
			// Check all polled (queued) events. If there is an event, it is put in "event".
			// SDL_PollEvent returns 0 if there are no events, which will stop the loop
			while (SDL_PollEvent(&event) != 0) {
				// If the event is a quit event, quit!
				if (event.type == SDL_QUIT) {
					quit = true;
				}
			}

			// Drawing test

			// Draw the canvas to the application window
			canvas->updateScreen(app->window);
		}
	}

	// Free resources and close SDL
	canvas->destroy();
	app->close();
	delete canvas;
	delete app;
	SDL_Quit();
	return 0;
}

