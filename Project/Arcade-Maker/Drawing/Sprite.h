#pragma once

#include <SDL.h>


class Sprite {
	Uint16 pixelRows[16];

	bool getPixel(Uint8 x, Uint8 y);
};