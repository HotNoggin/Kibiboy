#pragma once

// Includes
#include <lua.hpp>
#include <string>
#include "../Drawing/Sprite.h"


// Used for calls to the Lua cart from the C++ source.
// Also holds the Lua script and manages the state.
class Cart{
public:
	std::string script = R"(
function _boot()

end

function _update()

end

function _draw()

end
)";

	// Image data loaded from a .kibi cart
	std::array<Sprite, 256> sprites = {
		// Ignored sprite, used to erase
		Sprite({
			0xffff, 0xffff, 0xc003, 0xc003,
			0xcc33, 0xce73, 0xc7e3, 0xc3c3,
			0xc3c3, 0xc7e3, 0xce73, 0xcc33,
			0xc003, 0xc003, 0xffff, 0xffff}),
		// Kibiboy Logo!
		Sprite({
			0xfff0, 0xfff8, 0xfffc, 0xfffe,
			0xc003, 0xdffb, 0x1ff8, 0xd7eb,
			0x1c38, 0xde7b, 0x1ff8, 0xc003,
			0xffff, 0xfc3f, 0xfe7f, 0xffff })
	};

	// Flag data loaded from a .kibi cart
	std::array<Uint8, 256> flags = {};

	lua_State* state = NULL;

	void run();
	void runFunction(const char* function);
	bool initialize();
	void close();
	void clearStack();

	void boot();
	void update();
	void draw();
};