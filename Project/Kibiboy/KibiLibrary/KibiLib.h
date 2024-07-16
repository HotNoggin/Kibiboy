#pragma once

// Includes
#include <lua.hpp>
#include <array>
#include "../Drawing/Canvas.h"


// Handles calls to the C++ source from the Lua Script, and holds
// info about the loaded .kibi cart and game state in a singleton
class Kibiboy {
public:
	static Kibiboy* instance;

	Canvas* canvas = NULL;

	// Image data loaded from a .kibi cart
	std::array<Sprite, 256> sprites = {
		// Empty sprite, used to erase
		Sprite(),
		// Hamster ©2024 Pineberry Fox, CC0
		Sprite({
		0x0000, 0x0000, 0x070c, 0x0f92,
		0x1ff2, 0x1ff2, 0x1fd6, 0x0fd6,
		0x05f2, 0x05e4, 0x0e08, 0x1e08,
		0x706e, 0x7ffe, 0x0000, 0x0000
		})
	};
};


// Canvas drawing methods

int clear(lua_State* state);
int pixel(lua_State* state);
int rect(lua_State* state);
int stamp(lua_State* state);


// Library initialization methods
void openKibilib(lua_State* state);
void addFunction(lua_State* state, lua_CFunction function,
	const char* name);