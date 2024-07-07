// Includes
#include <stdio.h>
#include <SDL.h>
#include <string>


// Screen dimension constants
const int CANVAS_WIDTH = 320;
const int CANVAS_HEIGHT = 256;
// Double the canvas size + 64px of padding
const int DEFAULT_WINDOW_WIDTH = CANVAS_WIDTH * 2 + 64;
const int DEFAULT_WINDOW_HEIGHT = CANVAS_HEIGHT * 2 + 64;


// A color represented as an rgb value (no alpha)
struct Color {
	int r, g, b;

	Color(int red, int green, int blue) {
		r = red;
		g = green;
		b = blue;
	}
};

// Color constants
const Color COLOR_BLACK = Color(0x00, 0x00, 0x00);
const Color COLOR_DARK_BLUE = Color(0x1D, 0x2B, 0x53);
const Color COLOR_DARK_PURPLE = Color(0x7E, 0x25, 0x53);
const Color COLOR_DARK_GREEN = Color(0x00, 0x87, 0x51);
const Color COLOR_BROWN = Color(0xAB, 0x52, 0x36);
const Color COLOR_DARK_GRAY = Color(0x5F, 0x57, 0x4F);
const Color COLOR_LIGHT_GRAY = Color(0xC2, 0xC3, 0xC7);
const Color COLOR_WHITE = Color(0xFF, 0xF1, 0xE8);
const Color COLOR_RED = Color(0xFF, 0x00, 0x4D);
const Color COLOR_ORANGE = Color(0xFF, 0xA3, 0x00);
const Color COLOR_YELLOW = Color(0xFF, 0xEC, 0x27);
const Color COLOR_GREEN = Color(0x00, 0xE4, 0x36);
const Color COLOR_BLUE = Color(0x29, 0xAD, 0xFF);
const Color COLOR_LAVENDER = Color(0x83, 0x76, 0x9C);
const Color COLOR_PINK = Color(0xFF, 0x77, 0xA8);
const Color COLOR_PEACH = Color(0xFF, 0xCC, 0xAA);


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
		SDL_Rect canvasRect;
		canvasRect.x = 0;
		canvasRect.y = 0;

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
			horizontalScale = static_cast<int>(std::max(windowWidth / CANVAS_WIDTH, 1));
			verticalScale = static_cast<int>(std::max(windowHeight / CANVAS_HEIGHT, 1));
			if (horizontalScale > verticalScale) {
				horizontalScale = verticalScale;
			}
			else if (verticalScale > horizontalScale) {
				verticalScale = horizontalScale;
			}
			canvasRect.w = CANVAS_WIDTH * horizontalScale;
			canvasRect.h = CANVAS_HEIGHT * verticalScale;

			// Center the image
			// The x is the window's horizontal center - half of the image width
			// The y is the same, but vertical instead of horizontal
			canvasRect.x = (windowWidth - canvasRect.w) * 0.5;
			canvasRect.y = (windowHeight - canvasRect.h) * 0.5;

			// Clear, draw, and update
			// Black background
			SDL_SetRenderDrawColor(renderer,
				COLOR_DARK_GRAY.r, COLOR_DARK_GRAY.g, COLOR_DARK_GRAY.b, SDL_ALPHA_OPAQUE);
			SDL_RenderClear(renderer);
			// Dark purple window
			SDL_SetRenderDrawColor(renderer,
				COLOR_BLACK.r, COLOR_BLACK.g, COLOR_BLACK.b, SDL_ALPHA_OPAQUE);
			SDL_RenderFillRect(renderer, &canvasRect);
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
			SDL_SetWindowMinimumSize(window, CANVAS_WIDTH, CANVAS_HEIGHT);
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
			if (renderer == NULL) {
				printf("SDL Renderer could not be created. SDL_Error: %s\n", SDL_GetError());
			}
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