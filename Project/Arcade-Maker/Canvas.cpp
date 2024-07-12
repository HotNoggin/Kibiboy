// Includes
#include <algorithm>
#include <stdint.h>
#include <iostream>
#include "Canvas.h"

	
Color::Color(uint8_t red, uint8_t green, uint8_t blue) {
	r = red;
	g = green;
	b = blue;
}


// Color constants
// A pure black color
const Color BLACK = Color(0x00, 0x00, 0x00);
// A deep blue color
const Color DARK_BLUE = Color(0x1D, 0x2B, 0x53);
// A deep purple color
const Color DARK_PURPLE = Color(0x7E, 0x25, 0x53);
// A deep green color
const Color DARK_GREEN = Color(0x00, 0x87, 0x51);
// A saturated brown color
const Color BROWN = Color(0xAB, 0x52, 0x36);
// A deep gray color
const Color DARK_GRAY = Color(0x5F, 0x57, 0x4F);
// A bright gray color
const Color LIGHT_GRAY = Color(0xC2, 0xC3, 0xC7);
// An off-white color
const Color WHITE = Color(0xFF, 0xF1, 0xE8);
// A bright red color
const Color RED = Color(0xFF, 0x00, 0x4D);
// A bright orange color
const Color ORANGE = Color(0xFF, 0xA3, 0x00);
// A bright yellow color
const Color YELLOW = Color(0xFF, 0xEC, 0x27);
// A neon green color
const Color GREEN = Color(0x00, 0xE4, 0x36);
// A bright blue color
const Color BLUE = Color(0x29, 0xAD, 0xFF);
// A bright indigo color
const Color LAVENDER = Color(0x83, 0x76, 0x9C);
// A bright pink color
const Color PINK = Color(0xFF, 0x77, 0xA8);
// A tan/peach color
const Color PEACH = Color(0xFF, 0xCC, 0xAA);


bool Canvas::initialize() {
	bool success = true;
	canvasSurface = SDL_CreateRGBSurface(0,
		Canvas::WIDTH, Canvas::HEIGHT,
		32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
	if (canvasSurface == NULL) {
		success = false;
		std::cout << "Canvas failed to create surface. SDL_Error:\n";
		std::cout << SDL_GetError();
	}
	else {
		clear();
	}

	return success;
}


void Canvas::destroy() {
	SDL_FreeSurface(canvasSurface);
}


void Canvas::clear() {
	SDL_FillRect(canvasSurface, NULL, SDL_MapRGB(canvasSurface->format,
		BLACK.r, BLACK.g, BLACK.b));
}


void Canvas::updateScreen(SDL_Window* window) {
	if (window == NULL) {
		std::cout << "The window passed to the canvas is invalid. SDL_Error:\n";
		std::cout << SDL_GetError();
		return;
	}

	// The rect representing the size and position of the scaled canvas
	SDL_Rect canvasRect = {};
	canvasRect.x = 0;
	canvasRect.y = 0;

	// The width of the window to draw to
	int windowWidth = 0;
	// The height of the window to draw to
	int windowHeight = 0;

	// The horizontal integer scale of the window compared to the base size
	int horizontalScale = 1;
	// The vertical integer scale of the window compared to the base size
	int verticalScale = 1;

	SDL_GetWindowSize(window, &windowWidth, &windowHeight);

	// Calculate the integer scale. horizontalScale and verticalScale have a 1:1 ratio
	horizontalScale = std::max(windowWidth / WIDTH, 1);
	verticalScale = std::max(windowHeight / HEIGHT, 1);
	if (horizontalScale > verticalScale) {
		horizontalScale = verticalScale;
	}
	else if (verticalScale > horizontalScale) {
		verticalScale = horizontalScale;
	}
	// Calculate the resulting width and height of the integer scale
	canvasRect.w = WIDTH * horizontalScale;
	canvasRect.h = HEIGHT * verticalScale;

	// Center the image
	// The x is the window's horizontal center - half of the image width
	// The y is the same, but vertical instead of horizontal
	canvasRect.x = (windowWidth - canvasRect.w) / 2;
	canvasRect.y = (windowHeight - canvasRect.h) / 2;

	// Clear, draw, and update
	SDL_Surface* windowSurface = NULL;
	windowSurface = SDL_GetWindowSurface(window);

	if (windowSurface == NULL) {
		std::cout << "Canvas failed to get SDL window surface. SDL_Error: \n";
		std::cout << SDL_GetError();
		return;
	}

	
	SDL_FillRect(windowSurface, NULL, SDL_MapRGB(windowSurface->format,
		WHITE.r, WHITE.g, WHITE.b));
	SDL_BlitScaled(canvasSurface, NULL, windowSurface, &canvasRect);
	SDL_UpdateWindowSurface(window);
}
