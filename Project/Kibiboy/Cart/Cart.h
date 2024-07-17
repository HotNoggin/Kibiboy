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