// Includes
#include "Input.h"
#include <map>
#include <iostream>


// The input events from the previous update() call,
// Used to tell if something was just pressed
std::vector<int> oldEvents = {};
// The input events from the most recent update() call
std::vector<int> events = {};

bool quitQueued = false;

int mouseX = 0;
int mouseY = 0;
int mouseDownX = 0;
int mouseDownY = 0;
bool mouseDown = false;
bool rightMouseDown = false;
bool justClicked = false;

bool isLCtrlDown = false;
bool isRCtrlDown = false;

std::vector<std::string> textEvents = {};
std::vector<int> keyEvents = {};


// Set all input variables according to the SDL input events
void updateInput(SDL_Window* window){
	SDL_Event event;
	justClicked = false;
	textEvents.clear();
	keyEvents.clear();

	// Check against every event in the event queue
	while (SDL_PollEvent(&event) != 0) {

		// QUIT
		if (event.type == SDL_QUIT) {
			quitQueued = true;
		}

		// MOUSE CLICK
		else if (event.type == SDL_MOUSEBUTTONDOWN) {
			if (!mouseDown) {
				justClicked = true;
				mouseDownX = mouseX;
				mouseDownY = mouseY;
			}
			mouseDown = true;
			if (event.button.button == SDL_BUTTON_RIGHT) {
				rightMouseDown = true;
			}
		}
		else if (event.type == SDL_MOUSEBUTTONUP) {
			mouseDown = false;
			if (event.button.button == SDL_BUTTON_RIGHT) {
				rightMouseDown = false;
			}
		}

		// MOUSE POSITION
		else if (event.type == SDL_MOUSEMOTION) {
			int windowWidth = 0;
			int windowHeight = 0;
			SDL_GetWindowSize(window, &windowWidth, &windowHeight);
			int scale = Canvas::getScale(windowWidth, windowHeight);

			int offsetX = (windowWidth - (Canvas::WIDTH * scale)) / 2;
			int offsetY = (windowHeight - (Canvas::HEIGHT * scale)) / 2;
			
			mouseX = (event.motion.x - offsetX) / scale;
			mouseY = (event.motion.y - offsetY) / scale;
		}

		// Text
		else if (event.type == SDL_TEXTINPUT) {
			textEvents.push_back(event.text.text);
		}

		// Control and letter keys
		else if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.scancode == SDL_SCANCODE_LCTRL) {
				isLCtrlDown = true;
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_RCTRL) {
				isRCtrlDown = true;
			}

			else if (event.key.keysym.sym >= SDLK_a &&
				event.key.keysym.sym <= SDLK_z) {
				keyEvents.push_back(event.key.keysym.sym);
			}
		}
		else if (event.type == SDL_KEYUP) {
			if (event.key.keysym.scancode == SDL_SCANCODE_LCTRL) {
				isLCtrlDown = false;
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_RCTRL) {
				isRCtrlDown = false;
			}
		}
	}
}


// Returns true if the mouse position is inside of the bounds
bool hovering(int x, int y, int w, int h) {
	return mouseX >= x && mouseY >= y && mouseX < x + w && mouseY < y + h;
}


// Returns true if the specified key was just pressed this frame
bool keyPress(int keysym) {
	for (int i = 0; i < keyEvents.size(); i++) {
		if (keyEvents[i] == keysym) {
			return true;
		}
	}
	return false;
}