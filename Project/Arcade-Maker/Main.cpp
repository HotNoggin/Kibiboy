// Includes
#include <stdio.h>
#include <SDL.h>
#include <string>


// Screen dimension constants
const int WINDOW_SURFACE_WIDTH = 320;
const int WINDOW_SURFACE_HEIGHT = 256;
const int DEFAULT_WINDOW_WIDTH = WINDOW_SURFACE_WIDTH * 2;
const int DEFAULT_WINDOW_HEIGHT = WINDOW_SURFACE_HEIGHT * 2;


// Boots SDL and creates a new window
bool init();

// Closes the application and frees media
void close();

// The renderer to handle drawing in the game window
SDL_Renderer* renderer = NULL;
// The window to render to
SDL_Window* window = NULL;


int main(int argc, char* args[]) {
	// Initialize SDL
	if (!init()) {
		printf("SDL failed to initialize. \n");
	}
	else
	{
		// When this is set to true, the rendering loop stops and the application quits
		bool quit = false;

		SDL_Event event;
		SDL_Rect scaleRect;
		scaleRect.x = 0;
		scaleRect.y = 0;

		int windowWidth = 0;
		int windowHeight = 0;

		int horizontalScale = 1;
		int verticalScale = 1;

		SDL_GetWindowSize(window, &windowWidth, &windowHeight);

		// Main Loop
		while (!quit) {

			// 1. Event Handling:
			// Check all polled (queued) events. If there is an event, it is put in "event".
			// SDL_PollEvent returns 0 if there are no events, which will stop the loop
			while (SDL_PollEvent(&event) != 0) {
				// If the event is a quit event, quit!
				if (event.type == SDL_QUIT) {
					quit = true;
				}
				// If the event is a resize event, set the window
				else if (event.type == SDL_WINDOWEVENT) {
					if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
						SDL_GetWindowSize(window, &windowWidth, &windowHeight);
					}
				}
			}

			//2. Drawing:
				
			// Calculate the proper width and height according to the integer scale
			horizontalScale = static_cast<int>(std::max(windowWidth / WINDOW_SURFACE_WIDTH, 1));
			verticalScale = static_cast<int>(std::max(windowHeight / WINDOW_SURFACE_HEIGHT, 1));
			if (horizontalScale > verticalScale) {
				horizontalScale = verticalScale;
			}
			else if (verticalScale > horizontalScale) {
				verticalScale = horizontalScale;
			}
			scaleRect.w = WINDOW_SURFACE_WIDTH * horizontalScale;
			scaleRect.h = WINDOW_SURFACE_HEIGHT * verticalScale;

			// Center the image
			// The x is the window's horizontal center - half of the image width
			// The y is the same, but vertical instead of horizontal
			scaleRect.x = (windowWidth - scaleRect.w) * 0.5;
			scaleRect.y = (windowHeight - scaleRect.h) * 0.5;

			// Clear, draw, and update
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_RenderClear(renderer);
			SDL_RenderPresent(renderer);
		}
	}

	// Free resources and close SDL
	close();
	return 0;
}


bool init() {
	// Init flag, used to return true if successful
	bool success = true;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL failed to initialize. SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		// Create window
		window = SDL_CreateWindow("Arcade Maker", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);

		if (window == NULL)
		{
			printf("SDL Window could not be created. SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			// Create renderer and finish setup
			renderer = SDL_CreateRenderer(window, -1, 0);
			if (renderer == NULL) {
				printf("SDL Renderer could not be created. SDL_Error: %s\n", SDL_GetError());
			}
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_RenderClear(renderer);
			SDL_RenderPresent(renderer);
		}
	}

	return success;
}


void close()
{
	// Destroy window
	SDL_DestroyWindow(window);
	window = NULL;

	// Destroy renderer
	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	// Quit SDL
	SDL_Quit();
}