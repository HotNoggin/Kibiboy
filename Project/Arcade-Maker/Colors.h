#pragma once

#include <algorithm>
#include <SDL.h>


// A color represented as an rgb value (no alpha)
struct Color {
	int r, g, b;

	Color(uint8_t red, uint8_t green, uint8_t blue);

	// Returns the color as a single integer using the specified format
	// Shorthand for SDL_MapRGB(format, r, g, b);
	Uint32 asInt(SDL_PixelFormat* format);
};

namespace Colors {
	// Color constants
	// A pure black color
	Color BLACK = Color(0x00, 0x00, 0x00);
	// A deep blue color
	Color DARK_BLUE = Color(0x1D, 0x2B, 0x53);
	// A deep purple color
	Color DARK_PURPLE = Color(0x7E, 0x25, 0x53);
	// A deep green color
	Color DARK_GREEN = Color(0x00, 0x87, 0x51);
	// A saturated brown color
	Color BROWN = Color(0xAB, 0x52, 0x36);
	// A deep gray color
	Color DARK_GRAY = Color(0x5F, 0x57, 0x4F);
	// A bright gray color
	Color LIGHT_GRAY = Color(0xC2, 0xC3, 0xC7);
	// An off-white color
	Color WHITE = Color(0xFF, 0xF1, 0xE8);
	// A bright red color
	Color RED = Color(0xFF, 0x00, 0x4D);
	// A bright orange color
	Color ORANGE = Color(0xFF, 0xA3, 0x00);
	// A bright yellow color
	Color YELLOW = Color(0xFF, 0xEC, 0x27);
	// A neon green color
	Color GREEN = Color(0x00, 0xE4, 0x36);
	// A bright blue color
	Color BLUE = Color(0x29, 0xAD, 0xFF);
	// A bright indigo color
	Color LAVENDER = Color(0x83, 0x76, 0x9C);
	// A bright pink color
	Color PINK = Color(0xFF, 0x77, 0xA8);
	// A tan/peach color
	Color PEACH = Color(0xFF, 0xCC, 0xAA);
};