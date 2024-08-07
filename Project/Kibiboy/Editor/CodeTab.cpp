// Includes
#include "CodeTab.h"
#include "../Input/Input.h"
#include <iostream>

int caretBlinkTime = 0;
int codeIdx = 0;
int codeRow = 0;
int codeColumn = 0;


void fixCaret(int row, int column, EditorState* editor);
void fixCaretByIdx(int index, EditorState* editor);
void scrollToCaret(EditorState* editor);


void updateCodeTab(EditorState* editor, Cart* cart) {
	// Unpack script
	editor->code = stringToCodepoints(cart->script);
	int lineCount = 0;

	// Caret positioning
	if (hovering(4, 32, 308, 16 * 12) && mouseDown) {
		codeColumn = (mouseX - 4) / 8;
		codeRow = ((mouseY - 32) / 16) + editor->topCodeRow;
		fixCaret(codeRow, codeColumn, editor);
		caretBlinkTime = 0;
	}

	std::vector<Uint8>::iterator itr = editor->code.begin();
	std::advance(itr, codeIdx);

	// Typing (control)
	if (keyPress(SDLK_BACKSPACE)) {
		if (codeIdx > 0) {
			std::advance(itr, -1);
			editor->code.erase(itr);
			fixCaretByIdx(codeIdx - 1, editor);
			scrollToCaret(editor);
			caretBlinkTime = 0;
		}
	}
	else if (keyPress(SDLK_RETURN)) {
		editor->code.insert(itr, codepoint('\n'));
		fixCaretByIdx(codeIdx + 1, editor);
		scrollToCaret(editor);
		caretBlinkTime = 0;
	}
	else if (keyPress(SDLK_TAB)) {
		editor->code.insert(itr, codepoint('\t'));
		fixCaretByIdx(codeIdx + 1, editor);
		scrollToCaret(editor);
		caretBlinkTime = 0;
	}

	// Typing (text)
	else {
		std::vector<Uint8> codepoints = {};
		for (int i = 0; i < textEvents.size(); i++) {
			std::string text = textEvents[i];
			for (int ii = 0; ii < text.size(); ii++) {
				codepoints.push_back(codepoint(text[ii]));
			}
		}
		if (codepoints.size() > 0) {
			editor->code.insert(itr, codepoints.begin(), codepoints.end());
			codeColumn += (int)codepoints.size();
			fixCaretByIdx(codeIdx + (int)codepoints.size(), editor);
			scrollToCaret(editor);
			caretBlinkTime = 0;
		}
	}

	// Manual scrolling
	if (scrollWheel != 0) {
		lineCount = (int)textLines(cart->script).size();
		editor->topCodeRow -= scrollWheel;
		if (editor->topCodeRow < 0) {
			editor->topCodeRow = 0;
		}
		if (editor->topCodeRow >= lineCount) {
			editor->topCodeRow = lineCount - 1;
		}
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
		editor->caretColumn * 8 + 4,
		(editor->caretRow - editor->topCodeRow) * 16 + 32,
		8, 16);

	// Code
	std::vector<std::string> lines = textLines(cart->script);
	for (int i = 0; i < 12; i++) {
		if (editor->topCodeRow + i >= lines.size()) {
			break;
		}
		canvas->text(lines[i + editor->topCodeRow], WHITE, 4, 32 + i * 16);
	}
}


// Does the same as fixCaret(), but by index instead of coordinate
void fixCaretByIdx(int index, EditorState* editor) {
	int r = 0;
	int c = 0;

	for (codeIdx = 0; codeIdx < index; codeIdx++) {
		if (editor->code[codeIdx] == codepoint('\n')) {
			r++;
			c = 0;
		}
		else {
			c++;
		}
	}
	editor->caretRow = r;
	editor->caretColumn = c;
}


// Set the codeIdx and editor caret row and column to a valid char
// If column is negative, the caret is put at the end of the previous line
void fixCaret(int row, int column, EditorState* editor) {
	int r = 0; // Actual clickable row
	int c = 0; // Actual clickable column

	// Find the index of the first character in the row
	for (codeIdx = 0; codeIdx < editor->code.size(); codeIdx++) {
		if (r == row - 1 && column < 0) {
			break;
		}
		else if (r == row) {
			break;
		}
		if (characters[editor->code[codeIdx]] == '\n') {
			r++;
		}
	}

	// Find the index of the character at the column or end
	for (codeIdx = codeIdx; codeIdx < editor->code.size(); codeIdx++) {
		if (c == column && column >= 0) {
			break;
		}
		if (editor->code[codeIdx] == codepoint('\n')) {
			break;
		}
		c++;
	}

	editor->caretRow = r;
	editor->caretColumn = c;
}


void scrollToCaret(EditorState* editor) {
	while (editor->caretRow < editor->topCodeRow) {
		editor->topCodeRow--;
	}
	while (editor->caretRow > editor->topCodeRow + 11) {
		editor->topCodeRow++;
	}
}