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
extern int mouseDownX;
extern int mouseDownY;
extern bool mouseDown;
extern bool rightMouseDown;
extern bool justClicked;
extern int scrollWheel;

extern bool isLCtrlDown;
extern bool isRCtrlDown;

extern std::vector<std::string> textEvents;

extern std::vector<int> keyEvents;

void updateInput(SDL_Window* window);
bool hovering(int x, int y, int w, int h);

bool keyPress(int keysym);

enum INPUT_EVENTS {
	BUTTON_LEFT,
	BUTTON_RIGHT,
	BUTTON_UP,
	BUTTON_DOWN,
	BUTTON_A,
	BUTTON_B,
};