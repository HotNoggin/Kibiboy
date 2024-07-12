#pragma once

#include <SDL.h>



class Canvas {
public:
	// A color represented as an rgb value (no alpha)
	struct Color;

	// The surface that this canvas displays and draws to
	SDL_Surface* canvasSurface;

	// Screen dimension constants
	static const int WIDTH = 320;
	static const int HEIGHT = 256;

	bool initialize();
	void updateScreen(SDL_Window* window);
	void destroy();
};


// A color represented as an rgb value (no alpha)
struct Color {
	int r, g, b;
	Color(uint8_t red, uint8_t green, uint8_t blue);
};