// Includes
#include <iostream>
#include <SDL.h>
#include <lua.hpp>
#include <string>
#include "Application.h"
#include "Cart/Gameloop.h"
#include "Drawing/Canvas.h"


void runCanvasTests(Canvas* canvas);
void runLuaTests(lua_State* cart);

int offset = 0;

// Hamster ©2024 Pineberry Fox, CC0
Sprite hamsterSprite = {
	hamsterSprite.pixelRows = {
	0x0000, 0x0000, 0x070c, 0x0f92,
	0x1ff2, 0x1ff2, 0x1fd6, 0x0fd6,
	0x05f2, 0x05e4, 0x0e08, 0x1e08,
	0x706e, 0x7ffe, 0x0000, 0x0000
} };


int main(int argc, char* args[]) {

	// Handles application operations like open, close, and window
	Application* app = new Application();
	bool appSuccess = app->initialize("Arcade Maker",
		Canvas::WIDTH, Canvas::HEIGHT,
		Canvas::WIDTH, Canvas::HEIGHT);

	// Handles timing for update and draw calls to the cart
	Gameloop* gameloop = new Gameloop(30);

	// Handles draw methods and displaying the surface to the window
	Canvas* canvas = new Canvas();
	bool canvasSuccess = canvas->initialize(
		SDL_GetWindowPixelFormat(app->window));

	// Handles calls to C++ code from Lua and calls to Lua code from C++
	lua_State* cart = NULL;
	cart = luaL_newstate();

	// Handle failures
	if (!appSuccess) {
		std::cout << "Application failed to initialize.\n";
	}
	else if (!canvasSuccess) {
		std::cout << "Canvas failed to initialize.\n";
	}
	else if (cart == NULL) {
		std::cout << "Failed to create lua state.\n";
	}

	// Total success!
	else
	{
		// When true, the main loop stops and the application quits.
		bool quit = false;
		// The most recent event
		// Set by SDL_PollEvent and checked in the main loop.
		SDL_Event event;

		gameloop->restart();

		// Main Loop
		while (!quit) {
			// Event Handling
			// Check all polled (queued) events.
			// If there is an event, it is put in "event".
			// SDL_PollEvent returns 0 if there are no events.
			while (SDL_PollEvent(&event) != 0) {
				// If the event is a quit event, quit!
				if (event.type == SDL_QUIT) {
					quit = true;
				}
			}

			// Run the update method for every accumulated frame
			gameloop->tick();
			while (gameloop->get_accumulated_frames() > 0) {
				runCanvasTests(canvas);
				gameloop->use_accumulated_frames(1);
			}

			// Draw the canvas to the application window
			canvas->updateScreen(app->window);
		}
	}

	// Free resources and close SDL
	canvas->destroy();
	app->close();
	lua_close(cart);
	delete canvas;
	delete gameloop;
	delete app;
	SDL_Quit();
	return 0;
}


void runLuaTests(lua_State* cart){
	luaL_dostring(cart, "x = 'Hello From Lua!'");
	lua_getglobal(cart, "x");
	std::cout << lua_tostring(cart, -1);
	lua_remove(cart, -1);
}


void runCanvasTests(Canvas* canvas) {
	offset = (offset + 1) % 32;

	canvas->clear();

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

	for (int x = -1; x < 11; x++) {
		for (int y = -1; y < 9; y++) {
			// Test rect
			canvas->rect(BLACK, x * 32 + offset, y * 32 + 8, 16, 16);
			// Test sprite
			canvas->stamp(hamsterSprite, BROWN, x * 32 + offset, y * 32 + 8);
		}
	}
}