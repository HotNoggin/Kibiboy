#pragma once

// Includes
#include <SDL.h>
#include <chrono>

using namespace std::chrono;


class Gameloop {
public:
	Gameloop();
	Gameloop(Uint64 fps);
	// The duration of a single frame in milliseconds.
	Uint64 timestep = 33;
	// Remaining time since last use in milliseconds.
	// tick() must be called for this to update.
	Uint64 accumulatedTime = 0;
	// SDL application time in millliseconds.
	// tick() must be called for this to update.
	Uint64 currentTime = 0;

	void restart();
	void tick();
	Uint64 get_accumulated_frames();
	void use_accumulated_frames(Uint64 count);
};