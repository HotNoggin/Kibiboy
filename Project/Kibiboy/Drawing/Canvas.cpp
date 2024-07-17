// Includes
#include "Canvas.h"
#include "Sprite.h"
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


// Copy a sprite to the canvas at the specified position
// (place a colored pixel on the canvas for each true pixel on the sprite)
void Canvas::stamp(Sprite sprite, Color color, int x, int y) {
	for (int pixel_x = 0; pixel_x < 16; pixel_x++) {
		for (int pixel_y = 0; pixel_y < 16; pixel_y++) {
			if (sprite.getPixel(pixel_x, pixel_y)) {
				pixel(color, x + pixel_x, y + pixel_y);
			}
		}
	}
}


// Fill a rectangular area of pixels with the specified color
void Canvas::rect(Color color, int x, int y, int w, int h) {
	for (int pixel_x = 0; pixel_x < w; pixel_x++) {
		for (int pixel_y = 0; pixel_y < h; pixel_y++) {
			pixel(color, x + pixel_x, y + pixel_y);
		}
	}
}


// Draw a single pixel to the canvas
void Canvas::pixel(Color color, int x, int y) {
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
	Uint32 pixel = color.asInt(canvasSurface->format);
	*target_pixel = pixel;

	SDL_UnlockSurface(canvasSurface);
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

	// Calculate scaled width and height
	SDL_GetWindowSize(window, &windowWidth, &windowHeight);
	int scale = getScale(windowWidth, windowHeight);

	// Calculate the resulting width and height of the integer scale
	canvasRect.w = WIDTH * scale;
	canvasRect.h = HEIGHT * scale;

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

	SDL_FillRect(windowSurface, NULL, WHITE.asInt(windowSurface->format));
	SDL_BlitScaled(canvasSurface, NULL, windowSurface, &canvasRect);
	SDL_UpdateWindowSurface(window);
}


// Calculate the integer scale of the window based on w and h
int Canvas::getScale(int windowWidth, int windowHeight) {
	// The horizontal integer scale of the window compared to the base size
	int horizontalScale = 1;
	// The vertical integer scale of the window compared to the base size
	int verticalScale = 1;

	// Calculate the integer scale. horizontalScale and verticalScale have a 1:1
	// ratio
	horizontalScale = std::max(windowWidth / WIDTH, 1);
	verticalScale = std::max(windowHeight / HEIGHT, 1);

	return std::min(horizontalScale, verticalScale);
}

Sprite hamsterSprite = Sprite({
	0x0000, 0x0000, 0x070c, 0x0f92,
	0x1ff2, 0x1ff2, 0x1fd6, 0x0fd6,
	0x05f2, 0x05e4, 0x0e08, 0x1e08,
	0x706e, 0x7ffe, 0x0000, 0x0000
});