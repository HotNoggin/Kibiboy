#pragma once

// Includes
#include "Editor.h"

void updateConsole(EditorState* editor, Cart* cart);
void drawConsole(EditorState* editor, Cart* cart, Canvas* canvas);
void consoleLog(std::string text, Uint8 color, EditorState* editor);