// Includes
#include "SpriteTab.h"
#include "../Input/Input.h"
#include <iostream>


void updateSpriteTab(EditorState* editor, Cart* cart){
	// Get sprite
	Sprite* selected = NULL;
	selected = &cart->sprites[editor->selectedSprite];
	if (selected == NULL) {
		cart->sprites[editor->selectedSprite] = Sprite();
		selected = &cart->sprites[editor->selectedSprite];
	}

	// Sprite pixel editing
	if (hovering(0, 32, 16 * 8, 16 * 8) and mouseDown) {
		int x = mouseX / 8;
		int y = (mouseY - 32) / 8;
		selected->setPixel(!editor->eraseEnabled, x , y);
	}

	// Draw / Erase mode
	else if (hovering(16 * 8, 32, 32, 32) and justClicked) {
		editor->eraseEnabled = !editor->eraseEnabled;
	}

	// Sprite selection
	else if (hovering(160, 32, 16 * 8, 16 * 8) and justClicked) {
		int x = (mouseX - 160) / 32;
		int y = (mouseY - 32) / 32;
		int index = (y * 4) + (x % 4);
		editor->selectedSprite = index;

		Sprite* selected = NULL;
		selected = &cart->sprites[editor->selectedSprite];
	}

	// Color selection
	else if (hovering(16 * 12, 160, 128, 64) and justClicked) {
		int x = (mouseX - 16 * 12) / 16;
		int y = (mouseY - 160) / 16;
		int index = (y * 8) + (x % 8);

		// Set canvas color if selecting from top 16 colors
		if (index < 16) {
			editor->canvasColor = index % 16;
		}
		// Set sprite color if selecting from bottom 16 colors
		else {
			editor->spriteColor = index % 16;
		}
	}
}


void drawSpriteTab(EditorState* editor, Cart* cart, Canvas* canvas){
	// Background
	canvas->rect(editor->canvasColor, 0, 32, 16 * 8, 16 * 8);

	// Sprite selection menu
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			int index = (y * 4) + (x % 4);

			Color iconColor = WHITE;
			Color lineColor = WHITE;
			Color rectColor = BLACK;

			if (index == editor->selectedSprite) {
				iconColor = YELLOW;
				lineColor = YELLOW;
				rectColor = BLACK;
			}
			else {
				iconColor = WHITE;
				lineColor = BLACK;
				rectColor = BLUE;
			}

			canvas->rect(lineColor, x * 32 + 160, y * 32 + 32, 32, 32);
			canvas->rect(rectColor, x * 32 + 162, y * 32 + 34, 28, 28);
			canvas->stamp(cart->sprites[index], iconColor,
				x * 32 + 160 + 8, y * 32 + 32 + 8);
		}
	}

	// Tool selection menu
	canvas->stamp(hamsterSprite, editor->eraseEnabled? BLUE : YELLOW,
		16 * 8 + 8, 40);

	// Color selection menu
	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 4; y++) {
			int index = (y * 8) + (x % 8);
			canvas->rect(Color(index),
				x * 16 + 16 * 12 + 2, y * 16 + 162, 12, 12);
			
			// Selected colors
			if (index % 16 == editor->canvasColor && index < 16) {
				canvas->stamp(hamsterSprite,
					index % 16 == 0 ? WHITE : BLACK,
					x * 16 + 16 * 12, y * 16 + 160);
			}
			if (index % 16 == editor->spriteColor && index > 15) {
				canvas->stamp(hamsterSprite,
					index % 16 == 0 ? WHITE : BLACK,
					x * 16 + 16 * 12, y * 16 + 160);
			}
			
		}
	}

	// Get sprite
	Sprite* selected = NULL;
	selected = &cart->sprites[editor->selectedSprite];
	if (selected == NULL) {
		return;
	}

	// Sprite at 8x size
	for (int x = 0; x < 16; x++) {
		for (int y = 0; y < 16; y++) {
			if (selected->getPixel(x, y)) {
				canvas->rect(editor->spriteColor, x * 8, y * 8 + 32, 8, 8);
			}
		}
	}
}