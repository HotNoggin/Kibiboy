#pragma once

#include <lua.hpp>
#include <string>


class Cart{
public:
	std::string script = R"(
		
function _boot()
	print("Hello from Lua!")
	frames = 0
end
		
function _update()
	frames = frames + 1
	print("Time elapsed: " .. frames)
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