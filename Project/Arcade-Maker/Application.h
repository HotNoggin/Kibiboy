#pragma once

#include <SDL.h>


namespace Application {
	bool initialize(SDL_Window* window, const char* title, int w, int h, int max_w, int max_h);
	void close(SDL_Window* window);
}