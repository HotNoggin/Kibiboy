#pragma once

// Includes
#include "../Drawing/Canvas.h"
#include "../Cart/Cart.h"


enum TOOLS {
	TOOL_PENCIL,
	TOOL_RECT,
};


struct EditorState {
	Uint8 tab = 0;
	Uint8 cursor = 0;
	
	// Sprite tab and drawing state

	Uint8 canvasColor = 0;
	Uint8 spriteColor = 1;
	Uint8 selectedSprite = 1;
	bool isSpriteEraserOn = false;
	bool isSpriteGridOn = false;
	Uint8 spriteTool = TOOL_PENCIL;
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

extern Sprite selector;
