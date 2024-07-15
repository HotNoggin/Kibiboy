#include "Cart.h"
#include "iostream"
#include <string>


// Creates a new lua state
bool Cart::initialize() {
	state = luaL_newstate();
	if (state == NULL) {
		std::cout << "Failed to create lua state.\n";
		return false;
	}

	luaL_openlibs(state);

	return true;
}	


// Destroys the lua state
void Cart::close() {
	lua_close(state);
}


// Runs the lua script.
void Cart::run() {
	luaL_dostring(state, script.c_str());
}


// Executes the lua method with the specified name.
// Does not take parameters or return anything.
void Cart::runFunction(const char* function) {
	clearStack();
	lua_getglobal(state, function); // Function to be called
	if lua_isfunction(state, -1) {
		lua_pcall(state, 0, 0, 0);
	}
	clearStack();
}


// Erases every element from the lua stack.
void Cart::clearStack() {
	lua_pop(state, lua_gettop(state));
}

// Shorthand to execute _boot in the cart
void Cart::boot() {
	runFunction("_boot");
}

// Shorthand to execute _update in the cart
void Cart::update() {
	runFunction("_update");
}

// Shorthand to execute _draw in the cart
void Cart::draw() {
	runFunction("_draw");
}