// Includes
#include <iostream>
#include <SDL.h>
#include <string>
#include "Drawing/Canvas.h"
#include "Application.h"
#include "Drawing/Colors.h"


void runTests(Canvas* canvas);


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

			runTests(canvas);

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


void runTests(Canvas* canvas) {
	// TESTS //
	for (int x = 0; x < Canvas::WIDTH; x++) {
		for (int y = 0; y < Canvas::HEIGHT; y++) {
			// Test pixels
			if ((x + y) % 8 == 0) {
				canvas->pixel(GREEN, x, y);
			}
			if (x % 5 == 0) {
				canvas->pixel(BLACK, x, y);
			}
			if (y % 5 == 0) {
				canvas->pixel(BLACK, x, y);
			}
		}
	}

	for (int x = 0; x < Canvas::WIDTH; x++) {
		for (int y = 0; y < Canvas::HEIGHT; y++) {
			if (x % 32 == 0 && y % 32 == 0) {
				// Test rect
				canvas->rect(BLACK, x, y, 16, 16);

				// Test sprite (Mouse, ©2024 Pineberry Fox, CC0)
				Sprite sprite = {};
				sprite.pixelRows = {
					0x0000, 0x0000, 0x070c, 0x0f92,
					0x1ff2, 0x1ff2, 0x1fd6, 0x0fd6,
					0x05f2, 0x05e4, 0x0e08, 0x1e08,
					0x706e, 0x7ffe, 0x0000, 0x0000
				};

				canvas->stamp(sprite, BROWN, x, y);
			}
		}
	}
}