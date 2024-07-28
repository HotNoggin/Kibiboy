// Includes
#include "CodeTab.h"


void updateCodeTab(EditorState* editor, Cart* cart) {
	
}


void drawCodeTab(EditorState* editor, Cart* cart, Canvas* canvas) {
	canvas->text(cart->script, WHITE, 0, 32);
}