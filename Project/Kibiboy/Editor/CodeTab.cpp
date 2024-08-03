// Includes
#include "CodeTab.h"
#include "../Input/Input.h"
#include <iostream>

int caretBlinkTime = 0;


void updateCodeTab(EditorState* editor, Cart* cart) {
	// Caret positioning
	if (hovering(4, 32, 308, 16 * 12) && mouseDown) {
		editor->caretColumn = (mouseX - 4) / 8;
		editor->caretRow = ((mouseY - 32) / 16) + editor->topRow;
		caretBlinkTime = 0;
	}

	// Caret coordinates
	editor->footerText = "Row:" + std::to_string(editor->caretRow) +
		"  Column:" + std::to_string(editor->caretColumn);
}


void drawCodeTab(EditorState* editor, Cart* cart, Canvas* canvas) {
	// Caret
	caretBlinkTime = (caretBlinkTime + 1) % 30;
	canvas->rect((caretBlinkTime < 15)? BLUE : BLACK,
		editor->caretColumn * 8 + 4, editor->caretRow * 16 + 32, 8, 16);

	// Code
	canvas->text(cart->script, WHITE, 4, 32);
}
