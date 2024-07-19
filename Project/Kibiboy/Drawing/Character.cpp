// Includes
#include "Character.h"


Character::Character() {
	pixelRows = {};
}


Character::Character(std::array<Uint8, 16> pixels) {
	pixelRows = pixels;
}


// Returns true if there is a pixel at the pixel coordinate.
// Coordinates range from top-left (0, 0) to bottom-right (7, 15).
bool Character::getPixel(Uint8 x, Uint8 y) {
	if (x < 0 || y < 0 || x > 7 || y > 7) {
		return false;
	}
	return pixelRows[y] & (1 << (7 - x));
}


std::map<char, Character> font = {
	{'A', Character()},
	{'B', Character()},
	{'C', Character()},
	//... This is the format! Make a way to export sprites,
	// as strings, to the console, in this format
};