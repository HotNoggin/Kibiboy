#pragma once

#include <SDL.h>
#include "Colors.h"


class Canvas {
public:
	// Screen dimension constants
	static const int WIDTH = 320;
	static const int HEIGHT = 256;

	// The surface that this canvas displays and draws to
	SDL_Surface* canvasSurface;
	// The color used to fill the canvas in clear()

	bool initialize(Uint32 format);
	void clear();
	void pixel(Color* color, int x, int y);
	void updateScreen(SDL_Window* window);
	void destroy();
};
