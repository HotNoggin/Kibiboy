#pragma once

#include <SDL.h>



class Canvas {
public:
	// A color represented as an rgb value (no alpha)
	struct Color;

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


// A color represented as an rgb value (no alpha)
struct Color {
	int r, g, b;

	Color(uint8_t red, uint8_t green, uint8_t blue);

	// Returns the color as a single integer using the specified format
	// Shorthand for SDL_MapRGB(format, r, g, b);
	Uint32 asInt(SDL_PixelFormat* format);
};