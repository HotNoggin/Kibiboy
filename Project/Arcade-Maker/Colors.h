#pragma once

#include <algorithm>
#include <SDL.h>


// A color represented as an rgb value (no alpha)
struct Color {
	int r, g, b;

	Color();
	Color(uint8_t red, uint8_t green, uint8_t blue);

	// Returns the color as a single integer using the specified format
	// Shorthand for SDL_MapRGB(format, r, g, b);
	Uint32 asInt(SDL_PixelFormat* format);
};

namespace Colors {
	// Color constants
	// A pure black color
	extern Color BLACK;
	// A deep blue color
	extern Color DARK_BLUE;
	// A deep purple color
	extern Color DARK_PURPLE;
	// A deep green color
	extern Color DARK_GREEN;
	// A saturated brown color
	extern Color BROWN;
	// A deep gray color
	extern Color DARK_GRAY;
	// A bright gray color
	extern Color LIGHT_GRAY;
	// An off-white color
	extern Color WHITE;
	// A bright red color
	extern Color RED;
	// A bright orange color
	extern Color ORANGE;
	// A bright yellow color
	extern Color YELLOW;
	// A neon green color
	extern Color GREEN;
	// A bright blue color
	extern Color BLUE;
	// A bright indigo color
	extern Color LAVENDER;
	// A bright pink color
	extern Color PINK;
	// A tan/peach color
	extern Color PEACH;
};