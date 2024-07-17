#include "Colors.h"


Color::Color() {
	r = 0;
	g = 0;
	b = 0;
}


// Construct a new color with the given r, g, and b (0-255 each)
Color::Color(Uint8 red, Uint8 green, Uint8 blue) {
	r = red;
	g = green;
	b = blue;
}


// Construct a new color based on the 16-color Kibiboy palette
Color::Color(Uint8 index) {
	Color colors[16] = {
		BLACK, WHITE, RED, PINK, BROWN, ORANGE, PEACH, YELLOW,
		GREEN, LIME, BLUE, TEAL, PURPLE, MAGENTA, DARK_GRAY, LIGHT_GRAY
	};

	Color selected = colors[index % 16];

	r = selected.r;
	g = selected.g;
	b = selected.b;
}


// Combines and returns the color's RGB as an SDL int color
Uint32 Color::asInt(SDL_PixelFormat *format) {
	return SDL_MapRGB(format, r, g, b);
}
