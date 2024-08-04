// Includes
#include "CodeTab.h"
#include "../Input/Input.h"
#include <iostream>

int caretBlinkTime = 0;
int codeIdx = 0;
int codeRow = 0;
int codeColumn = 0;


void fixCaret(int row, int column, EditorState* editor);


void updateCodeTab(EditorState* editor, Cart* cart) {
	// Unpack script
	editor->code = stringToCodepoints(cart->script);

	// Caret positioning
	if (hovering(4, 32, 308, 16 * 12) && mouseDown) {
		codeColumn = (mouseX - 4) / 8;
		codeRow = ((mouseY - 32) / 16) + editor->topRow;
		fixCaret(codeRow, codeColumn, editor);
		caretBlinkTime = 0;
	}

	std::vector<Uint8>::iterator itr = editor->code.begin();
	std::advance(itr, codeIdx);

	// Typing (control)
	if (keyPress(SDLK_BACKSPACE)) {
		std::advance(itr, -1);
		editor->code.erase(itr);
		--codeColumn;
		fixCaret(codeRow, codeColumn, editor);
		caretBlinkTime = 0;
		std::cout << "BACK\n";
	}
	
	else {
		// Typing (text)
		std::vector<Uint8> codepoints = {};
		for (int i = 0; i < textEvents.size(); i++) {
			std::string text = textEvents[i];
			for (int ii = 0; ii < text.size(); ii++) {
				codepoints.push_back(codepoint(text[ii]));
			}
		}
		editor->code.insert(itr, codepoints.begin(), codepoints.end());
		codeColumn += (int)codepoints.size();
		fixCaret(codeRow, codeColumn, editor);
		caretBlinkTime = 0;
	}

	// Caret coordinates
	editor->footerText = "Row:" + std::to_string(editor->caretRow) +
		"  Column:" + std::to_string(editor->caretColumn);

	// Pack script
	cart->script = codepointsToString(editor->code);
}


void drawCodeTab(EditorState* editor, Cart* cart, Canvas* canvas) {
	// Caret
	caretBlinkTime = (caretBlinkTime + 1) % 30;
	canvas->rect((caretBlinkTime < 15)? BLUE : BLACK,
		editor->caretColumn * 8 + 4, editor->caretRow * 16 + 32, 8, 16);

	// Code
	canvas->text(cart->script, WHITE, 4, 32);
}


// Set the codeIdx and editor caret row and column to a valid char
void fixCaret(int row, int column, EditorState* editor) {
	int r = 0; // Actual clickable row
	int c = 0; // Actual clickable column

	// Find the index of the first character in the row
	for (codeIdx = 0; codeIdx < editor->code.size(); codeIdx++) {
		if (r == row) {
			break;
		}
		if (characters[editor->code[codeIdx]] == '\n') {
			r += 1;
		}
	}

	// Find the index of the character at the column or end
	for (codeIdx = codeIdx; codeIdx < editor->code.size(); codeIdx++) {
		if (c == column) {
			break;
		}
		if (characters[editor->code[codeIdx]] == '\n') {
			break;
		}
		c++;
	}

	editor->caretRow = r;
	editor->caretColumn = c;
}