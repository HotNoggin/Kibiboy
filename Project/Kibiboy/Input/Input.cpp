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
bool mouseDown = false;
bool justClicked = false;


// Set all input variables according to the SDL input events
void updateInput(SDL_Window* window){
	SDL_Event event;
	justClicked = false;

	// Check against every event in the event queue
	while (SDL_PollEvent(&event) != 0) {

		// QUIT
		if (event.type == SDL_QUIT) {
			quitQueued = true;
		}

		// MOUSE
		else if (event.type == SDL_MOUSEBUTTONDOWN) {
			if (!mouseDown) {
				justClicked = true;
			}
			mouseDown = true;
		}
		else if (event.type == SDL_MOUSEBUTTONUP) {
			mouseDown = false;
		}
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
	}
}


bool hovering(int x, int y, int w, int h) {
	return mouseX >= x && mouseY >= y && mouseX < x + w && mouseY < y + h;
}