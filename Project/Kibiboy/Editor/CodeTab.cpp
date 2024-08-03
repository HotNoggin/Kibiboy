// Includes
#include "CodeTab.h"
#include "../Input/Input.h"
#include <iostream>


void updateCodeTab(EditorState* editor, Cart* cart) {
	// Move caret
	if (hovering(0, 32, 320, 16 * 13) && mouseDown) {
		editor->caret_column = mouseX / 8;
		std::cout << editor->caret_column << "\n";
	}
}


void drawCodeTab(EditorState* editor, Cart* cart, Canvas* canvas) {
	canvas->text(cart->script, WHITE, 0, 32);
	canvas->rect(WHITE, )
}
