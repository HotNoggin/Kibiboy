// Includes
#include "Console.h"
#include "../Input/Input.h"
#include "../Drawing/Character.h"


void updateConsole(EditorState* editor, Cart* cart){
	// Switch to edit mode
	if (keyPress(SDLK_ESCAPE)) {
		editor->tab = editor->lastTab;
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
	canvas->text(codepointsToString(editor->consoleInput), WHITE,
		4, index * 16);
	
	// Left and right margins
	canvas->rect(BLUE, 0, 0, 3, 256);
	canvas->rect(BLUE, 316, 0, 3, 256);
}


void consoleLog(std::string text, Uint8 color, EditorState* editor) {
	editor->logs.push_back(text);
	editor->logColors.push_back(color);

	while (editor->logs.size() >= 16) {
		editor->logs.erase(editor->logs.begin());
	}
}