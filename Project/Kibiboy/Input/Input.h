#pragma once

// Includes
#include "../Drawing/Canvas.h"
#include <SDL.h>
#include <vector>


extern std::vector<int> oldEvents;
extern std::vector<int> events;

extern bool quitQueued;

extern int mouseX;
extern int mouseY;
extern bool mouseDown;
extern bool justClicked;

void updateInput(SDL_Window* window);

enum INPUT_EVENTS {
	KEY_A,
	// meh maybe later
};