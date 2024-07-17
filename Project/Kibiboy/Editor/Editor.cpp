// Includes
#include "Editor.h"
#include "../Input/Input.h"
#include "SpriteTab.h"
#include <iostream>


void drawCursor(Canvas* canvas);
void updateBaseUI(EditorState* editor);
void drawBaseUI(EditorState* editor, Canvas* canvas);


void updateEditor(Canvas* canvas, EditorState* editor, Cart* cart) {
	canvas->clear();
	updateBaseUI(editor);
	drawBaseUI(editor, canvas);
	switch (editor->tab)
	{
	case EDITOR_TAB_SPRITE:
		updateSpriteTab(editor, cart);
		drawSpriteTab(editor, cart, canvas);
		break;
	default:
		break;
	}
	drawCursor(canvas);
}


void drawCursor(Canvas* canvas) {
	if (hovering(0, 0, Canvas::WIDTH, Canvas::HEIGHT)) {
		SDL_ShowCursor(SDL_DISABLE);
	}
	else {
		SDL_ShowCursor(SDL_ENABLE);
	}
	canvas->rect(BLACK, mouseX, mouseY, 8, 8);
	canvas->rect(WHITE, mouseX + 1, mouseY + 1, 6, 6);
}


void updateBaseUI(EditorState* editor) {
	// Select tab
	if (hovering(0, 0, 32 * 5, 32) and justClicked) {
		editor->tab = mouseX / 32;
	}
}


void drawBaseUI(EditorState* editor, Canvas* canvas) {
	// Top and bottom bars
	canvas->rect(BLUE, 0, 0, Canvas::WIDTH, 32);
	canvas->rect(BLUE, 0, Canvas::HEIGHT - 32, Canvas::WIDTH, 32);

	// Tabs
	for (int x = 0; x < 5; x++) {
		if (x == editor->tab) {
			// Active tab
			canvas->rect(BLACK, x * 32 + 4, 4, 27, 24);
			canvas->stamp(hamsterSprite, YELLOW, x * 32 + 8, 8);
		}
		else {
			// Inactive tab
			canvas->rect(BLACK, x * 32 + 4, 4, 27, 24);
			if (hovering(x * 32, 0, 32, 32)) {
				canvas->rect(YELLOW, x * 32 + 5, 5, 25, 22);
			}
			else {
				canvas->rect(BLUE, x * 32 + 5, 5, 25, 22);
			}
			canvas->stamp(hamsterSprite, BLACK, x * 32 + 8, 8);
		}
	}
}