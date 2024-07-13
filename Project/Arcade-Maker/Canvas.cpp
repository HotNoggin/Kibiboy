// Includes
#include "Canvas.h"
#include <algorithm>
#include <iostream>
#include <stdint.h>


bool Canvas::initialize(Uint32 format) {
	bool success = true;
	canvasSurface = SDL_CreateRGBSurfaceWithFormat(0, Canvas::WIDTH,
                                                 Canvas::HEIGHT, 32, format);

	if (canvasSurface == NULL) {
		success = false;
		std::cout << "Canvas failed to create surface. SDL_Error:\n";
		std::cout << SDL_GetError();
	} else {
		clear();
	}

	return success;
}


void Canvas::destroy() { SDL_FreeSurface(canvasSurface); }


void Canvas::clear() {
	SDL_FillRect(canvasSurface, NULL, BLACK.asInt(canvasSurface->format));
}


// Draw a single pixel to the canvas
void Canvas::pixel(Color* color, int x, int y) {
	// Don't draw if out of bounds
	if (x < 0 || x >= canvasSurface->w || y < 0 || y >= canvasSurface->h) {
		return;
	}

	SDL_LockSurface(canvasSurface);
	// Calculate the location of the pixel
	Uint32* const target_pixel = (Uint32*)((Uint8*)canvasSurface->pixels
		+ y * canvasSurface->pitch
		+ x * canvasSurface->format->BytesPerPixel);

	// Set the target pixel's value to the color as an int 
	Uint32 pixel = color->asInt(canvasSurface->format);
	*target_pixel = pixel;

	SDL_UnlockSurface(canvasSurface);
}


void Canvas::updateScreen(SDL_Window *window) {
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

	// Calculate the integer scale. horizontalScale and verticalScale have a 1:1
	// ratio
	horizontalScale = std::max(windowWidth / WIDTH, 1);
	verticalScale = std::max(windowHeight / HEIGHT, 1);
	if (horizontalScale > verticalScale) {
		horizontalScale = verticalScale;
	} else if (verticalScale > horizontalScale) {
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
	SDL_Surface *windowSurface = NULL;
	windowSurface = SDL_GetWindowSurface(window);

	if (windowSurface == NULL) {
	std::cout << "Canvas failed to get SDL window surface. SDL_Error: \n";
		std::cout << SDL_GetError();
		return;
	}

	SDL_FillRect(windowSurface, NULL,
		SDL_MapRGB(windowSurface->format, WHITE.r, WHITE.g, WHITE.b));
	SDL_BlitScaled(canvasSurface, NULL, windowSurface, &canvasRect);
	SDL_UpdateWindowSurface(window);
}
