// Includes
#include "Kibilib.h"


Kibiboy* Kibiboy::instance = NULL;


// Open the lib (add all functions to the lua state)
void openKibilib(lua_State* state) {
	// Add canvas drawing methods
	addFunction(state, *clear, "clear");
	addFunction(state, *pixel, "pixel");
	addFunction(state, *rect, "rect");
	addFunction(state, *stamp, "stamp");
}


// Canvas drawing methods

int clear(lua_State* state) {
	Kibiboy::instance->canvas->clear();
	return 0;
}


int pixel(lua_State* state) {
	Uint8 color = (Uint8)lua_tonumber(state, 1);
	int x = (int)lua_tonumber(state, 2);
	int y = (int)lua_tonumber(state, 3);
	Kibiboy::instance->canvas->pixel(Color(color), x, y);
	return 0;
}


int rect(lua_State* state) {
	Uint8 color = (Uint8)lua_tonumber(state, 1);
	int x = (int)lua_tonumber(state, 2);
	int y = (int)lua_tonumber(state, 2);
	int w = (int)lua_tonumber(state, 2);
	int h = (int)lua_tonumber(state, 2);
	Kibiboy::instance->canvas->rect(Color(color), x, y, w, h);
	return 0;
}


int stamp(lua_State* state) {
	Uint8 sprite = (Uint8)lua_tonumber(state, 1);
	Uint8 color = (Uint8)lua_tonumber(state, 2);
	int x = (int)lua_tonumber(state, 3);
	int y = (int)lua_tonumber(state, 4);

	Kibiboy::instance->canvas->stamp(
		Kibiboy::instance->sprites[sprite], Color(color), x, y);

	return 0;
}


// Adds a global c function to the Lua state
void addFunction(lua_State* state, lua_CFunction function,
	const char* name) {

	lua_pushcfunction(state, function); // Add the pointer to the stack
	lua_setglobal(state, name); // Set global (name) to the last stack item
	lua_remove(state, 1); // Remove the pointer from the stack
}