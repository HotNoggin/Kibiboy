#pragma once

// Includes
#include <SDL.h>
#include <array>
#include <map>


class Character {
public:
	std::array<Uint8, 16> pixelRows = {};
	Character();
	Character(std::array<Uint8, 16> pixels);
	bool getPixel(Uint8 x, Uint8 y);
};

extern std::map<char, Character> font;