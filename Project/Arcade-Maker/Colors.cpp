#include "Colors.h"


Color::Color() {
	r = 0;
	g = 0;
	b = 0;
}


Color::Color(uint8_t red, uint8_t green, uint8_t blue) {
	r = red;
	g = green;
	b = blue;
}


Uint32 Color::asInt(SDL_PixelFormat* format) {
	return SDL_MapRGB(format, r, g, b);
}


// Color constants
// A pure black color
Color Colors::BLACK = Color(0x00, 0x00, 0x00);
// A deep blue color
Color Colors::DARK_BLUE = Color(0x1D, 0x2B, 0x53);
// A deep purple color
Color Colors::DARK_PURPLE = Color(0x7E, 0x25, 0x53);
// A deep green color
Color Colors::DARK_GREEN = Color(0x00, 0x87, 0x51);
// A saturated brown color
Color Colors::BROWN = Color(0xAB, 0x52, 0x36);
// A deep gray color
Color Colors::DARK_GRAY = Color(0x5F, 0x57, 0x4F);
// A bright gray color
Color Colors::LIGHT_GRAY = Color(0xC2, 0xC3, 0xC7);
// An off-white color
Color Colors::WHITE = Color(0xFF, 0xF1, 0xE8);
// A bright red color
Color Colors::RED = Color(0xFF, 0x00, 0x4D);
// A bright orange color
Color Colors::ORANGE = Color(0xFF, 0xA3, 0x00);
// A bright yellow color
Color Colors::YELLOW = Color(0xFF, 0xEC, 0x27);
// A neon green color
Color Colors::GREEN = Color(0x00, 0xE4, 0x36);
// A bright blue color
Color Colors::BLUE = Color(0x29, 0xAD, 0xFF);
// A bright indigo color
Color Colors::LAVENDER = Color(0x83, 0x76, 0x9C);
// A bright pink color
Color Colors::PINK = Color(0xFF, 0x77, 0xA8);
// A tan/peach color
Color Colors::PEACH = Color(0xFF, 0xCC, 0xAA);
