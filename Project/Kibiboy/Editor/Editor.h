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
	Uint8 tab = 0;
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
	std::vector<Uint8> codepoints = {};
};


enum EDITOR_TABS {
	EDITOR_TAB_SPRITE,
	EDITOR_TAB_CODE,
	EDITOR_TAB_MAP,
	EDITOR_TAB_AUDIO,
	EDITOR_TAB_MUSIC,
	EDITOR_TAB_GAME,
	EDITOR_TAB_CONSOLE
};


enum CURSOR_MODES {
	CURSOR_POINT,
	CURSOR_BRUSH
};

void updateEditor(Canvas* canvas, EditorState* editor, Cart* cart);
std::string numberAsText(int number, int minLength);

extern Sprite selector;
