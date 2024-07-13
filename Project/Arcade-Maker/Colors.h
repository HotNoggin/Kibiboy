#pragma once

#include <SDL.h>
#include <algorithm>


// A color represented as an rgb value (no alpha)
struct Color {
	int r, g, b;

	Color();
	Color(uint8_t red, uint8_t green, uint8_t blue);

	// Returns the color as a single integer using the specified format
	// Shorthand for SDL_MapRGB(format, r, g, b);
	Uint32 asInt(SDL_PixelFormat *format);
};


#define BLACK Color(0, 0, 0)
#define DARK_BLUE Color(0, 0, 139)
#define DARK_PURPLE Color(75, 0, 130)
#define DARK_GREEN Color(0, 100, 0)
#define BROWN Color(139, 69, 19)
#define DARK_GRAY Color(169, 169, 169)
#define LIGHT_GRAY Color(211, 211, 211)
#define WHITE Color(255, 255, 255)
#define RED Color(255, 0, 0)
#define ORANGE Color(255, 165, 0)
#define YELLOW Color(255, 255, 0)
#define GREEN Color(0, 128, 0)
#define BLUE Color(0, 0, 255)
#define LAVENDER Color(138, 43, 226)
#define PINK Color(255, 192, 203)
#define PEACH Color(255, 218, 185)