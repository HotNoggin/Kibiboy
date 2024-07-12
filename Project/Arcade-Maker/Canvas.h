#pragma once

#include <SDL.h>



namespace Canvas {
	// A color represented as an rgb value (no alpha)
	struct Color;

	// Screen dimension constants
	const int CANVAS_WIDTH = 320;
	const int CANVAS_HEIGHT = 256;

	SDL_Surface* createCanvasSurface();
	void updateScreen(SDL_Window* window, SDL_Surface* surface);
}