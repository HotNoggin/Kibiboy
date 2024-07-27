#pragma once

#include <SDL.h>
#include <algorithm>


// A color represented as an rgb value (no alpha)
struct Color {
	int r, g, b;

	Color();
	Color(Uint8 index);
	Color(Uint8 red, Uint8 green, Uint8 blue);

	// Returns the color as a single integer using the specified format
	// Shorthand for SDL_MapRGB(format, r, g, b);
	Uint32 asInt(SDL_PixelFormat *format);
};


#define BLACK Color(0x09, 0x02, 0x22)
#define BLUE Color(0x44, 0x42, 0xbe)
#define PURPLE Color(0x4a, 0x05, 0x4d)
#define GREEN Color(0x17, 0x51, 0x25)
#define BROWN Color(0x7d, 0x33, 0x06)
#define DARK_GRAY Color(0x3a, 0x35, 0x32)
#define LIGHT_GRAY Color(0xa5, 0xd0, 0xd2)
#define WHITE Color(0xf6, 0xf3, 0xd0)
#define RED Color(0x72, 0x1b, 0x30)
#define ORANGE Color(0xf9, 0x96, 0x16)
#define YELLOW Color(0xff, 0xda, 0x14)
#define LIME Color(0xa8, 0xff, 0x51)
#define TEAL Color(0x24, 0xb2, 0xba)
#define MAGENTA Color(0xa9, 0x34, 0xad)
#define PINK Color(0xf8, 0x6b, 0x89)
#define PEACH Color(0xf6, 0xc0, 0x78)
