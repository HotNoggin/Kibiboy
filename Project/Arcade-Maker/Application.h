#pragma once

#include <SDL.h>


// The application class handles window and application operations
class Application {
public:
	SDL_Window* window = NULL;
	bool initialize(const char* title, int w, int h, int max_w, int max_h);
	void close();
};