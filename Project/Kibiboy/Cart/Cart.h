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
	print("Hello from Lua!")
	x = 0
	draw_x = -16
	width = 20 * 18
	height = (16 * 16)
	half_y = height / 2
end
		
function _update()
	x = x + 4
	draw_x = ((x) % (width)) - 16
end

function _draw()
	clear()
	
	-- Pixel test
	for pix_x = 0, width do
		for pix_y = 0, height do
			if (pix_x + pix_y) % 16 == 0 then
				pixel(9, pix_x, pix_y)
			end
		end
	end
	
	-- Stamp and rect test
	rect()
	stamp(1, 4, draw_x, half_y)
	
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