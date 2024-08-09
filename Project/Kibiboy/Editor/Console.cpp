// Includes
#include "Console.h"
#include "../Input/Input.h"
#include "../Drawing/Character.h"


void updateConsole(EditorState* editor, Cart* cart){
	// Switch to edit mode
	if (keyPress(SDLK_ESCAPE)) {
		editor->tab = editor->lastTab;
	}

	std::vector<Uint8>::iterator itr = editor->consoleInput.begin();
	std::advance(itr, editor->consoleCursorColumn);

	// Typing (control)
	if (keyPress(SDLK_BACKSPACE)) {
		if (editor->consoleCursorColumn > 0) {
			std::advance(itr, -1);
			editor->consoleCursorColumn--;
			editor->consoleInput.erase(itr);
		}
	}
	else if (keyPress(SDLK_TAB)) {
		editor->consoleInput.insert(itr, codepoint('\t'));
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
			editor->consoleInput.insert(itr,
				codepoints.begin(), codepoints.end());
			editor->consoleCursorColumn += (int)codepoints.size();
		}
	}

	// Submitting
	if (keyPress(SDLK_RETURN)) {
		consoleLog("> " + codepointsToString(editor->consoleInput),
			10, editor);
		editor->consoleInput = {};
		editor->consoleCursorColumn = 0;
	}
}


void drawConsole(EditorState* editor, Cart* cart, Canvas* canvas) {
	// Print logs, colored. Expects no new lines!
	int index = 0;
	for (index = 0; index < 16; index++) {
		if (index >= editor->logs.size()) {
			break;
		}
		canvas->text(editor->logs[index], Color(editor->logColors[index]),
			4, index * 16);
	}

	// Current input
	canvas->text("> " + codepointsToString(editor->consoleInput), WHITE,
		4, index * 16);
	
	// Left and right margins
	canvas->rect(BLUE, 0, 0, 3, 256);
	canvas->rect(BLUE, 317, 0, 3, 256);
}


void consoleLog(std::string text, Uint8 color, EditorState* editor) {
	editor->logs.push_back(text);
	editor->logColors.push_back(color);

	while (editor->logs.size() >= 16) {
		editor->logs.erase(editor->logs.begin());
	}
}