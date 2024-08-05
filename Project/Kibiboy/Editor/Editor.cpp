// Includes
#include "Editor.h"
#include "../Input/Input.h"
#include "SpriteTab.h"
#include "CodeTab.h"
#include <iostream>


Sprite cursorOutline = Sprite({
	0xf000, 0x9000, 0x9800, 0xc800, 0x4c00, 0x67c0, 0x2060, 0xe030,
	0x2010, 0x10, 0x8078, 0xc088, 0x7128, 0x1d48, 0x718, 0x1f0 });
Sprite cursorFill = Sprite({
	0x0, 0x6000, 0x6000, 0x3000, 0x3000, 0x1800, 0x1f80, 0x1fc0,
	0xdfe0, 0xffe0, 0x7f80, 0x3f70, 0xed0, 0x2b0, 0xe0, 0x0 });

Sprite brushOutline = Sprite({
	0xfe00, 0x8300, 0x8100, 0x8180, 0x82c0, 0x8440, 0xc8c0, 0x7160,
	0x1a30, 0xf18, 0x18c, 0xc6, 0x63, 0x31, 0x19, 0xf });
Sprite brushFill = Sprite({
	0x0, 0x7e00, 0x7e00, 0x7e00, 0x7d00, 0x7b80, 0x7700, 0xe80,
	0x5c0, 0xe0, 0x70, 0x38, 0x1c, 0xe, 0x6, 0x0 });

Sprite kibiBoyIcon = Sprite({
	0xfff0, 0xfff8, 0xfffc, 0xfffe, 0xc003, 0xdffb, 0x1ff8, 0xd7eb,
	0x1c38, 0xde7b, 0x1ff8, 0xc003, 0xffff, 0xfc3f, 0xfe7f, 0xffff });

Sprite selector = Sprite({
	0x0, 0x0, 0x3c3c, 0x3c3c, 0x300c, 0x300c, 0x0, 0x180,
	0x180, 0x0, 0x300c, 0x300c, 0x3c3c, 0x3c3c, 0x0, 0x0 });


Sprite tabIcons[5] = {
	// SPRITE
	Sprite({
		0x1c, 0x3e, 0x7f, 0x1f, 0x1cf, 0x3e6, 0x7f4, 0xff0, 0x1ff0,
		0x3fe0, 0xfc0, 0x6780, 0xf300, 0xfa00, 0xb800, 0xf000}),
	// CODE
	Sprite({
		0x1ffe, 0x2fff, 0x37ff, 0x77ff, 0x7800, 0x7ffc, 0x3116, 0x3ffe,
		0x1003, 0x1fff, 0x1889, 0xefff, 0x8801, 0x8fff, 0x4886, 0x3ffc}),
	// MAP
	Sprite({
		0xdef6, 0xffff, 0xc003, 0x5dba, 0xddbb, 0xddba, 0xc003, 0x5dbb, 
		0xddbb, 0xc002, 0xddbb, 0xddbb, 0x5dba, 0xc003, 0xffff, 0xeddf}),
	// SOUND
	Sprite({
		0xe00, 0xa00, 0xe0e, 0xe00a, 0xaeee, 0xeea0, 0xeee, 0xee0e,
		0xeeee, 0xeeee, 0xeeee, 0xeeee, 0xeeee, 0xeeee, 0xeeee, 0xeeee}),
	// MUSIC
	Sprite({
		0x0, 0x1800, 0x3800, 0x2800, 0x2c3e, 0x21fe, 0x21e2, 0x211e,
		0xe1e2, 0xe102, 0xe102, 0x102, 0x10e, 0x70e, 0x70e, 0x700}),
};


void drawCursor(EditorState* editor, Canvas* canvas);
void updateBaseUI(EditorState* editor);
void drawBaseUI(EditorState* editor, Canvas* canvas);
void drawFooter(EditorState* editor, Canvas* canvas, Cart* cart);


void updateEditor(Canvas* canvas, EditorState* editor, Cart* cart) {
	canvas->clear();
	updateBaseUI(editor);
	switch (editor->tab)
	{
	case EDITOR_TAB_SPRITE:
		updateSpriteTab(editor, cart);
		drawSpriteTab(editor, cart, canvas);
		break;
	case EDITOR_TAB_CODE:
		updateCodeTab(editor, cart);
		drawCodeTab(editor, cart, canvas);
		break;
	default:
		break;
	}
	drawBaseUI(editor, canvas);
	drawFooter(editor, canvas, cart);
	drawCursor(editor, canvas);
}


void drawCursor(EditorState* editor, Canvas* canvas) {
	Sprite outline = cursorOutline;
	Sprite fill = cursorFill;

	switch (editor->cursor)
	{
	case 0:
		outline = cursorOutline;
		fill = cursorFill;
		break;
	case 1:
		outline = brushOutline;
		fill = brushFill;
		break;
	default:
		break;
	}

	if (hovering(0, 0, Canvas::WIDTH, Canvas::HEIGHT)) {
		SDL_ShowCursor(SDL_DISABLE);
	}
	else {
		SDL_ShowCursor(SDL_ENABLE);
	}
	canvas->stamp(fill, WHITE, mouseX, mouseY);
	canvas->stamp(outline, BLACK, mouseX, mouseY);
}


void updateBaseUI(EditorState* editor) {
	// Select tab
	if (hovering(0, 0, 32 * 5, 32) and justClicked) {
		editor->tab = mouseX / 32;
	}
}


void drawBaseUI(EditorState* editor, Canvas* canvas) {
	// Top and bottom bars
	canvas->rect(BLUE, 0, 0, Canvas::WIDTH, 32);
	canvas->rect(BLUE, 0, Canvas::HEIGHT - 32, Canvas::WIDTH, 32);

	// Tabs
	for (int x = 0; x < 5; x++) {
		if (x == editor->tab) {
			// Active tab
			canvas->rect(BLACK, x * 32 + 4, 4, 27, 24);
			canvas->stamp(tabIcons[x], YELLOW, x * 32 + 9, 8);
		}
		else {
			// Inactive tab
			canvas->rect(BLACK, x * 32 + 4, 4, 27, 24);
			if (hovering(x * 32, 0, 32, 32)) {
				canvas->rect(YELLOW, x * 32 + 5, 5, 25, 22);
			}
			else {
				canvas->rect(BLUE, x * 32 + 5, 5, 25, 22);
			}
			canvas->stamp(tabIcons[x], BLACK, x * 32 + 9, 8);
		}
	}
}


void drawFooter(EditorState* editor, Canvas* canvas, Cart* cart) {
	canvas->text(editor->footerText, BLACK, 4, 16 * 14);
	canvas->text("KIBIBOY V0.0.1: " + cart->name, WHITE, 4, 16 * 15);
	editor->footerText = "";
}


// Returns a number as a string with leading zeroes
std::string numberAsText(int number, int minLength) {
	std::string textNumber = std::to_string(number);
	while (textNumber.size() < minLength) {
		textNumber = "0" + textNumber;
	}
	return textNumber;
}


// Returns text as an array of text with one element per line
std::vector<std::string> textLines(std::string text) {
	std::vector<std::string> lines;
	std::string line = "";

	for (int i = 0; i < text.size(); i++) {
		if (text[i] == '\n') {
			lines.push_back(line);
			line = "";
		}
		else {
			line += text[i];
		}
	}

	lines.push_back(line);

	return lines;
}