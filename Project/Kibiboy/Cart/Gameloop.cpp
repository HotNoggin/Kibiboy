#include "Gameloop.h"
#include <iostream>

// The gameloop maintains a fixed update frequency.
// It can determine when to update based on the elapsed time.


Gameloop::Gameloop() {}


Gameloop::Gameloop(Uint64 fps) {
	if (fps > 0) {
		timestep = (Uint64)(1000 * (1.0f / fps));
	}
}


// Reset the elapsed time
void Gameloop::restart() {
	accumulatedTime = 0;
	currentTime = SDL_GetTicks64();
}


// Save the elapsed time
void Gameloop::tick() {
	Uint64 newTime = SDL_GetTicks64();
	Uint64 frameTime = newTime - currentTime;
	currentTime = newTime;
	accumulatedTime += frameTime;
}


// Returns the number of frames in the accumulated time
Uint64 Gameloop::get_accumulated_frames() {
	return accumulatedTime / timestep;
}


// Removes the proper number of frame time from the accumulated time
void Gameloop::use_accumulated_frames(Uint64 frames) {
	accumulatedTime -= frames * timestep;
}