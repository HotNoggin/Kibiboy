// Includes
#include "SpriteTab.h"
#include "../Input/Input.h"
#include <iostream>


Sprite eraserIcon = Sprite({
	0x0, 0x60, 0xf0, 0x1f8, 0x3fc, 0x7fe, 0xfff, 0x1fff,
	0x2ffe, 0x47fc, 0x83f8, 0x81f0, 0x40e0, 0x2040, 0x1080, 0xf00 });

Sprite gridIcon = Sprite({
	0xffff, 0x8421, 0x8421, 0x8421, 0x8421, 0xffff, 0x8421, 0x8421,
	0x8421, 0x8421, 0xffff, 0x8421, 0x8421, 0x8421, 0x8421, 0xffff });


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
		selected->setPixel(!editor->isSpriteEraserOn, x , y);
	}

	// Draw / Erase mode
	else if (hovering(16 * 8, 32, 32, 32) and justClicked) {
		editor->isSpriteEraserOn = !editor->isSpriteEraserOn;
	}

	// Rect tool
	else if (hovering(16 * 8, 64, 32, 32) and justClicked) {
		std::cout << "Click!\n";
		if (editor->spriteTool == TOOL_PENCIL) {
			std::cout << "RECT\n";
			editor->spriteTool = TOOL_RECT;
		}
		else {
			editor->spriteTool = TOOL_PENCIL;
			std::cout << "PENCIL\n";
		}
	}

	// Canvas grid
	else if (hovering(16 * 8, 96, 32, 32) and justClicked) {
		editor->isSpriteGridOn = !editor->isSpriteGridOn;
	}

	// Sprite selection
	else if (hovering(160, 32, 16 * 8, 16 * 8) and justClicked) {
		int x = (mouseX - 160) / 32;
		int y = (mouseY - 32) / 32;
		int index = (editor->spriteSection * 16) + (y * 4) + (x % 4);
		editor->selectedSprite = index;
		selected = &cart->sprites[editor->selectedSprite];
	}

	// Section selection
	else if (hovering(16 * 18, 32, 32, 16 * 8) and justClicked) {
		int x = (mouseX - 16 *18) / 16;
		int y = (mouseY - 32) / 16;
		int index = (y * 2) + (x % 2);
		editor->spriteSection = index;
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

	// Export (Made for debugging and engine dev only)
	// Only exports the first page (first 16 sprites)
	if ((isLCtrlDown || isRCtrlDown) && keyPress(SDLK_e)) {
		std::cout << "Exporting Sprites...\n";

		// Iterate over every sprite in the cart
		for (int i = 0; i < 16; i++) {
			Sprite sprite = cart->sprites[i];
			// Start
			std::cout << "Sprite({";

			// Export every pixel row in hex form, followed by a comma
			for (int row = 0; row < 16; row++) {
				std::cout << "0x" << std::hex << sprite.pixelRows[row];
				if (row < 15) {
					std::cout << ", ";
				}
			}
			// End
			std::cout << "}), \n";
		}
	}

	// Cursor
	if (hovering(0, 32, 16 * 8, 16 * 8)) {
		editor->cursor = CURSOR_BRUSH;
	}
	else {
		editor->cursor = CURSOR_POINT;
	}
}


void drawSpriteTab(EditorState* editor, Cart* cart, Canvas* canvas){
	// Sprite canvas background
	canvas->rect(editor->canvasColor, 0, 32, 16 * 8, 16 * 8);

	// Sprite selection menu
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			int index = (editor->spriteSection * 16) + (y * 4) + (x % 4);

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
			canvas->stamp(
				cart->sprites[index],
				iconColor, x * 32 + 160 + 8, y * 32 + 32 + 8);
		}
	}

	// Section selection menu
	for (int x = 0; x < 2; x++) {
		for (int y = 0; y < 8; y++) {
			int index = (y * 2) + (x % 2);
			canvas->rect( index == editor->spriteSection ? YELLOW : BLUE,
				x * 16 + 16 * 18 + 2, y * 16 + 32 + 2, 12, 12);
		}
	}

	// Tool selection menu
	canvas->stamp(eraserIcon, editor->isSpriteEraserOn? YELLOW : BLUE,
		16 * 8 + 8, 40);
	canvas->stamp(hamsterSprite,
		editor->spriteTool == TOOL_RECT ? YELLOW : BLUE,
		16 * 8 + 8, 72);
	canvas->stamp(gridIcon,
		editor->isSpriteGridOn ? YELLOW : BLUE,
		16 * 8 + 8, 104);

	// Color selection menu
	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 4; y++) {
			int index = (y * 8) + (x % 8);
			canvas->rect(Color(index),
				x * 16 + 16 * 12 + 2, y * 16 + 162, 12, 12);
			
			// Selected colors
			if (index % 16 == editor->canvasColor && index < 16) {
				canvas->stamp(selector,
					index % 16 == 0 ? WHITE : BLACK,
					x * 16 + 16 * 12, y * 16 + 160);
			}
			if (index % 16 == editor->spriteColor && index > 15) {
				canvas->stamp(selector,
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

	// Sprite canvas grid
	if (editor->isSpriteGridOn) {
		for (int x = 0; x < 5; x++) {
			canvas->rect(editor->spriteColor, x * 32, 32, 1, 16 * 8);
		}
		for (int y = 0; y < 5; y++) {
			canvas->rect(editor->spriteColor, 0, y * 32 + 32, 16 * 8, 1);
		}
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