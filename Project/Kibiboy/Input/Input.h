#pragma once

// Includes
#include "../Drawing/Canvas.h"
#include <SDL.h>
#include <vector>
#include <string>


extern std::vector<int> oldEvents;
extern std::vector<int> events;

extern bool quitQueued;

extern int mouseX;
extern int mouseY;
extern bool mouseDown;
extern bool justClicked;

extern bool isCtrlDown;

extern std::vector<std::string> textEvents;

void updateInput(SDL_Window* window);
bool hovering(int x, int y, int w, int h);

enum INPUT_EVENTS {
	BUTTON_LEFT,
	BUTTON_RIGHT,
	BUTTON_UP,
	BUTTON_DOWN,
	BUTTON_A,
	BUTTON_B,
};