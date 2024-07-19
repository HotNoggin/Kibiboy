#pragma once

#include "Colors.h"
#include "Sprite.h"
#include "Character.h"
#include <SDL.h>


class Canvas {
public:
	// Screen dimension constants
	static const int WIDTH = 320;
	static const int HEIGHT = 256;

	// The surface that this canvas displays and draws to
	SDL_Surface* canvasSurface;

	bool initialize(Uint32 format);
	void clear();
	void pixel(Color color, int x, int y);
	void rect(Color color, int x, int y, int w, int h);
	void stamp(Sprite sprite, Color color, int x, int y);
	void glyph(char character, Color color, int x, int y);
	void updateScreen(SDL_Window* window);
	static int getScale(int windowWidth, int windowHeight);
	void destroy();
};


// Hamster ©2024 Pineberry Fox, CC0
extern Sprite hamsterSprite;