#pragma once

// Includes
#include "../Drawing/Canvas.h"
#include "../Cart/Cart.h"
#include <string>
#include <vector>


enum TOOLS {
	TOOL_PENCIL,
	TOOL_RECT,
};


// Holds the state of the editor (things that are not saved)
struct EditorState {
	Uint8 tab = 5;
	Uint8 lastTab = 0;
	Uint8 cursor = 0;
	std::string footerText = "";
	
	// Sprite tab and drawing state

	Uint8 canvasPreviewColor = 0;
	Uint8 spritePreviewColor = 1;
	Uint8 selectedSprite = 1;
	Uint8 spriteSection = 0;
	bool isSpriteEraserOn = false;
	bool isSpriteGridOn = false;
	Uint8 spriteTool = TOOL_PENCIL;

	// Code tab and text cursor state

	std::vector<Uint8> code = {};
	int codeCursorRow = 0;
	int codeCursorColumn = 0;
	int topCodeRow = 0;
	int leftCodeColumn = 0;

	// Console tab and text cursor state

	std::vector<std::string> logs = {
		"Welcome to",
		R"(._..__ ._. .__.  ._. .__.  .___  __  __)",
		R"(| |/ / | | | . \ | | | . \ |   \ \ \/ /)",
		R"(|   /  | | |   / | | |   / |^u^|  \  / )",
		R"(|   \  | | | . \ | | | . \ |   |  | |  )",
		R"(|_|\_\ |_| |___/ |_| |___/ |___|  |_|  )",
		R"(=======================================)",
		"Your teeny tool to make arcade-y games!",
		"",
		"Press [ESC] to enter edit mode, or",
		"Enter HELP to see how to get started!"
		};
	std::vector<Uint8> logColors = { 2, 3, 5, 7, 9, 11, 10, 1, 0, 1, 1};
	std::vector<Uint8> consoleInput = {};
	int consoleCursorRow = 0;
	int consoleCursorColumn = 0;
	int consoleInputIndex = 0;
};


enum EDITOR_TABS {
	EDITOR_TAB_SPRITE,
	EDITOR_TAB_CODE,
	EDITOR_TAB_MAP,
	EDITOR_TAB_AUDIO,
	EDITOR_TAB_MUSIC,
	EDITOR_TAB_CONSOLE
};


enum CURSOR_MODES {
	CURSOR_POINT,
	CURSOR_BRUSH,
	CURSOR_CROSS
};

void updateEditor(Canvas* canvas, EditorState* editor, Cart* cart);
std::string numberAsText(int number, int minLength);
std::vector<std::string> textLines(std::string text);

extern Sprite selector;
