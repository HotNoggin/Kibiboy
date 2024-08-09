// Includes
#include "CodeTab.h"
#include "../Input/Input.h"
#include <iostream>

int caretBlinkTime = 0;
int codeIdx = 0;
int codeRow = 0;
int codeColumn = 0;

void fixCaret(int row, int column, EditorState* editor, Cart* cart);
void fixCaretByIdx(int index, EditorState* editor);
void scrollToCaret(EditorState* editor);
void scrollToFit(int lineCount, int highestLength, EditorState* editor);
int getHighestLength(std::vector<std::string> lines);


void updateCodeTab(EditorState* editor, Cart* cart) {
	// Unpack script
	editor->code = stringToCodepoints(cart->script);
	int lineCount = 0;

	// Caret positioning
	if (hovering(4, 32, 320, 16 * 12)) {
		editor->cursor = 2;
		if (mouseDown) {
			lineCount = (int)textLines(cart->script).size();
			codeColumn = (mouseX - 4) / 8 + editor->leftCodeColumn;
			codeRow = ((mouseY - 32) / 16) + editor->topCodeRow;
			fixCaret(codeRow, codeColumn, editor, cart);
			scrollToCaret(editor);
			caretBlinkTime = 0;
		}
	}
	else {
		editor->cursor = 0;
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
		std::vector<std::string> lines = textLines(cart->script);
		if (isLShiftDown || isRShiftDown) {
			// FIXME: Does not support unicode's variable-length chars!
			// Check number of complete UTF-8 codepoints per line instead!
			int highestLength = getHighestLength(lines);
			editor->leftCodeColumn -= scrollWheel * 3;
			scrollToFit(-1, highestLength, editor);
		}
		else {
			lineCount = (int)lines.size();
			editor->topCodeRow -= scrollWheel;
			scrollToFit(lineCount, -1, editor);
		}
	}

	// Scroll while selecting
	if (hovering(4, 32, 320, 16 * 12)) {
		editor->cursor = CURSOR_CROSS;
		if (mouseDown) {
			if (mouseX >= 312) {
				editor->leftCodeColumn++;
				std::vector<std::string> lines = textLines(cart->script);
				scrollToFit(-1, getHighestLength(lines), editor);
			}
			else if (mouseX < 8) {
				editor->leftCodeColumn--;
				std::vector<std::string> lines = textLines(cart->script);
				scrollToFit(-1, getHighestLength(lines), editor);
			}
		}
	}
	
	// Caret coordinates
	editor->footerText = "Row:" + std::to_string(editor->codeCursorRow) +
		"  Column:" + std::to_string(editor->codeCursorColumn);

	// Pack script
	cart->script = codepointsToString(editor->code);
}


void drawCodeTab(EditorState* editor, Cart* cart, Canvas* canvas) {
	// Caret
	caretBlinkTime = (caretBlinkTime + 1) % 30;
	canvas->rect((caretBlinkTime < 15)? BLUE : BLACK,
		(editor->codeCursorColumn - editor->leftCodeColumn) * 8 + 4 ,
		(editor->codeCursorRow - editor->topCodeRow) * 16 + 32,
		8, 16);

	// Code
	std::vector<std::string> lines = textLines(cart->script);
	for (int i = 0; i < 12; i++) {
		if (editor->topCodeRow + i >= lines.size()) {
			break;
		}
		canvas->text(lines[i + editor->topCodeRow], WHITE, 
			4 - editor->leftCodeColumn * 8, 32 + i * 16);
	}
}


// Does the same as fixCaret(), but by index instead of coordinate
// FIXME: Iterates using fixed-sized chars instead of UTF-8 codepoints!
void fixCaretByIdx(int index, EditorState* editor) {
	int r = 0;
	int c = 0;

	for (codeIdx = 0; codeIdx < index; codeIdx++) {
		if (characters[editor->code[codeIdx]] == '\n') {
			r++;
			c = 0;
		}
		else {
			c++;
		}
	}
	editor->codeCursorRow = r;
	editor->codeCursorColumn = c;
}


// Set the codeIdx and editor caret row and column to a valid char
// If column is negative, the caret is put at the end of the previous line
// FIXME: Iterates using fixed-sized chars instead of UTF-8 codepoints!
void fixCaret(int row, int column, EditorState* editor, Cart* cart) {
	int r = 0; // Actual clickable row
	int c = 0; // Actual clickable column

	std::vector<std::string> lines = textLines(cart->script);

	// Fix by index if the row is past the last line
	if (row >= lines.size()) {
		fixCaretByIdx((int)editor->code.size(), editor);
		return;
	}
	
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

	editor->codeCursorRow = r;
	editor->codeCursorColumn = c;
}


void scrollToCaret(EditorState* editor) {
	while (editor->codeCursorRow < editor->topCodeRow) {
		editor->topCodeRow--;
	}
	while (editor->codeCursorRow > editor->topCodeRow + 11) {
		editor->topCodeRow++;
	}
	while (editor->codeCursorColumn < editor->leftCodeColumn) {
		editor->leftCodeColumn--;
	}
	while (editor->codeCursorColumn > editor->leftCodeColumn + 38) {
		editor->leftCodeColumn++;
	}
}


void scrollToFit(int lineCount, int highestLength, EditorState* editor) {
	if (lineCount >= 0) {
		if (editor->topCodeRow < 0) {
			editor->topCodeRow = 0;
		}
		else if (editor->topCodeRow >= lineCount) {
			editor->topCodeRow = lineCount - 1;
		}
	}

	if (highestLength >= 0) {
		if (editor->leftCodeColumn < 0) {
			editor->leftCodeColumn = 0;
		}
		else if (editor->leftCodeColumn >= highestLength) {
			editor->leftCodeColumn = highestLength - 1;
		}
	}
}


// FIXME: Doesn't work with unicode! This expects fixed char sizes!
int getHighestLength(std::vector<std::string> lines) {
	int highestLength = 0;
	for (int i = 0; i < lines.size(); i++) {
		if (lines[i].length() > highestLength) {
			highestLength = (int)lines[i].length();
		}
	}
	return highestLength;
}