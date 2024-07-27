#pragma once

// Includes
#include <lua.hpp>
#include <array>
#include "../Drawing/Canvas.h"
#include "../Cart/Cart.h"


// Handles calls to the C++ source from the Lua Script, and holds
// info about the loaded .kibi cart and game state in a singleton
class Kibiboy {
public:
	static Kibiboy* instance;

	Canvas* canvas = NULL;
	Cart* cart = NULL;
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