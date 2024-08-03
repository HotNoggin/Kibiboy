#pragma once

// Includes
#include <SDL.h>
#include <array>
#include <map>
#include <vector>
#include <string>


class Character {
public:
	std::array<Uint8, 16> pixelRows = {};
	Character();
	Character(std::array<Uint8, 16> pixels);
	bool getPixel(Uint8 x, Uint8 y);
};

extern std::map<char, Character> font;
extern std::array<char, 256> characters;

Uint8 codepoint(char c);
std::vector<Uint8> stringToCodepoints(std::string text);