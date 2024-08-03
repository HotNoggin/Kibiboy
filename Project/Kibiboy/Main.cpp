// Includes
#include <iostream>
#include <SDL.h>
#include <lua.hpp>
#include <lualib.h>
#include <string>
#include "Application.h"
#include "Cart/Gameloop.h"
#include "Cart/Cart.h"
#include "KibiLibrary/Kibilib.h"
#include "Drawing/Canvas.h"
#include "Input/Input.h"
#include "Editor/Editor.h"


int main(int argc, char* args[]) {
	// Handles application operations like open, close, and window
	Application* app = new Application();
	bool appSuccess = app->initialize("Kibiboy",
		Canvas::WIDTH, Canvas::HEIGHT,
		Canvas::WIDTH, Canvas::HEIGHT);

	// Handles the Lua script and calls to it from the C++ source
	Cart* cart = new Cart();
	bool cartSuccess = cart->initialize();
	
	// Handles calls to C++ source from the Lua script, and holds cart data
	Kibiboy::instance = new Kibiboy();
	
	// Handles draw methods and displaying the surface to the window
	Canvas* canvas = new Canvas();
	bool canvasSuccess = canvas->initialize(
		SDL_GetWindowPixelFormat(app->window));
	
	// Handles timing for update and draw calls to the cart
	Gameloop* gameloop = new Gameloop(30);

	// Handles editor data that is not saved to the cart
	EditorState* editor = new EditorState();
	
	// Handle failures
	if (!appSuccess) {
		std::cout << "Application failed to initialize.\n";
	}
	else if (!canvasSuccess) {
		std::cout << "Canvas failed to initialize.\n";
	}
	else if (!cartSuccess) {
		std::cout << "Failed to create cart interface.\n";
	}

	// Total success!
	else
	{
		gameloop->restart();
		cart->run();
		cart->boot();
		Kibiboy::instance->canvas = canvas;
		Kibiboy::instance->cart = cart;

		// Main Loop
		while (!quitQueued) {
			// Event Handling
			// Check all polled (queued) events.
			// If there is an event, it is put in "event".
			// SDL_PollEvent returns 0 if there are no events.
			

			// Run the update and draw methods for every accumulated frame
			gameloop->tick();
			while (gameloop->get_accumulated_frames() > 0) {
				updateInput(app->window);
				updateEditor(canvas, editor, cart);
				cart->update();
				cart->draw();
				int type = lua_getglobal(cart->state, "frames");
				cart->clearStack();
				gameloop->use_accumulated_frames(1);
			}

			// Draw the canvas to the application window
			canvas->updateScreen(app->window);
		}
	}

	// Free resources and close SDL
	canvas->destroy();
	cart->close();
	app->close();
	delete canvas;
	delete gameloop;
	delete Kibiboy::instance;
	delete app;
	SDL_Quit();
	return 0;
}
