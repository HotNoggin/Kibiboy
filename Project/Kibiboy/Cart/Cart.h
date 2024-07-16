#pragma once

// Includes
#include <lua.hpp>
#include <string>


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