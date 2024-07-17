// Includes
#include "SpriteTab.h"
#include "../Input/Input.h"


void updateSpriteTab(EditorState* editor, Cart* cart){
	// Get sprite
	Sprite* selected = NULL;
	selected = &cart->sprites[editor->selectedSprite];
	if (selected == NULL) {
		return;
	}

	// Sprite pixel editing
	if (hovering(0, 32, 16 * 8, 16 * 8) and justClicked) {
		int x = mouseX / 8;
		int y = (mouseY - 32) / 8;
		selected->setPixel(!selected->getPixel(x, y), x, y);
	}
}


void drawSpriteTab(EditorState* editor, Cart* cart, Canvas* canvas){
	// Background
	canvas->rect(editor->canvasColor, 0, 32, 16 * 8, 16 * 8);

	// Get sprite
	Sprite* selected = NULL;
	selected = &cart->sprites[editor->selectedSprite];
	if (selected == NULL) {
		return;
	}

	// Draw sprite at 8x size
	for (int x = 0; x < 16; x++) {
		for (int y = 0; y < 16; y++) {
			if (selected->getPixel(x, y)) {
				canvas->rect(editor->spriteColor, x * 8, y * 8 + 32, 8, 8);
			}
		}
	}
}