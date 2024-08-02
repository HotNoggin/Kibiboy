// Includes
#include "CodeTab.h"
#include "../Input/Input.h"


void updateCodeTab(EditorState* editor, Cart* cart) {
	if (hovering(0, 32, 320, 16 * 13) && mouseDown) {

	}
}


void drawCodeTab(EditorState* editor, Cart* cart, Canvas* canvas) {
	canvas->text(cart->script, WHITE, 0, 32);
}