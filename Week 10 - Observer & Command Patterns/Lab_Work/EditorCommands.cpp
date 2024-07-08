#pragma once
#include "EditorCommands.h"
#include "LevelEditor.h"

EditorCommands::EditorCommands(LevelEditor* editor) {
	this->editor = editor;
};

void SetTileCommand::Do() {
	previous = editor->GetLevel()->GetCellTexture(iCell,jCell);
	editor->GetLevel()->SetCellTexture(iCell, jCell, tileIndex);
};

void SetTileCommand::Undo() {
	editor->GetLevel()->SetCellTexture(iCell, jCell, previous);
};