// Includes
#include <algorithm>
#include <stdint.h>
#include "Canvas.h"


namespace Canvas {


	// A color represented as an rgb value (no alpha)
	struct Color {
		int r, g, b;

		Color(uint8_t red, uint8_t green, uint8_t blue) {
			r = red;
			g = green;
			b = blue;
		}
	};


	// Color constants
	// A pure black color
	const Color COLOR_BLACK = Color(0x00, 0x00, 0x00);
	// A deep blue color
	const Color COLOR_DARK_BLUE = Color(0x1D, 0x2B, 0x53);
	// A deep purple color
	const Color COLOR_DARK_PURPLE = Color(0x7E, 0x25, 0x53);
	// A deep green color
	const Color COLOR_DARK_GREEN = Color(0x00, 0x87, 0x51);
	// A saturated brown color
	const Color COLOR_BROWN = Color(0xAB, 0x52, 0x36);
	// A deep gray color
	const Color COLOR_DARK_GRAY = Color(0x5F, 0x57, 0x4F);
	// A bright gray color
	const Color COLOR_LIGHT_GRAY = Color(0xC2, 0xC3, 0xC7);
	// An off-white color
	const Color COLOR_WHITE = Color(0xFF, 0xF1, 0xE8);
	// A bright red color
	const Color COLOR_RED = Color(0xFF, 0x00, 0x4D);
	// A bright orange color
	const Color COLOR_ORANGE = Color(0xFF, 0xA3, 0x00);
	// A bright yellow color
	const Color COLOR_YELLOW = Color(0xFF, 0xEC, 0x27);
	// A neon green color
	const Color COLOR_GREEN = Color(0x00, 0xE4, 0x36);
	// A bright blue color
	const Color COLOR_BLUE = Color(0x29, 0xAD, 0xFF);
	// A bright indigo color
	const Color COLOR_LAVENDER = Color(0x83, 0x76, 0x9C);
	// A bright pink color
	const Color COLOR_PINK = Color(0xFF, 0x77, 0xA8);
	// A tan/peach color
	const Color COLOR_PEACH = Color(0xFF, 0xCC, 0xAA);


	SDL_Surface* createCanvasSurface() {
		return SDL_CreateRGBSurface(0,
			Canvas::CANVAS_WIDTH, Canvas::CANVAS_HEIGHT,
			32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
	}


	void updateScreen(SDL_Window* window, SDL_Surface* surface) {
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
		horizontalScale = static_cast<int>(std::max(windowWidth / CANVAS_WIDTH, 1));
		verticalScale = static_cast<int>(std::max(windowHeight / CANVAS_HEIGHT, 1));
		if (horizontalScale > verticalScale) {
			horizontalScale = verticalScale;
		}
		else if (verticalScale > horizontalScale) {
			verticalScale = horizontalScale;
		}
		// Calculate the resulting width and height of the integer scale
		canvasRect.w = CANVAS_WIDTH * horizontalScale;
		canvasRect.h = CANVAS_HEIGHT * verticalScale;

		// Center the image
		// The x is the window's horizontal center - half of the image width
		// The y is the same, but vertical instead of horizontal
		canvasRect.x = (windowWidth - canvasRect.w) / 2;
		canvasRect.y = (windowHeight - canvasRect.h) / 2;

		// Clear, draw, and update
		SDL_Surface* windowSurface = NULL;
		windowSurface = SDL_GetWindowSurface(window);
		if (windowSurface == NULL) {
			printf("Failed to get SDL window surface. SDL_Error: %s\n", SDL_GetError());
		}
		else {
			SDL_FillRect(windowSurface, NULL, SDL_MapRGB(windowSurface->format,
				COLOR_BLACK.r, COLOR_BLACK.g, COLOR_BLACK.b));
			SDL_BlitScaled(surface, NULL, windowSurface, &canvasRect);
		}
	}
}