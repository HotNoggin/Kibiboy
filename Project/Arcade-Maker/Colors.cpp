#include "Colors.h"

Color::Color(uint8_t red, uint8_t green, uint8_t blue) {
	r = red;
	g = green;
	b = blue;
}


Uint32 Color::asInt(SDL_PixelFormat* format) {
	return SDL_MapRGB(format, r, g, b);
}