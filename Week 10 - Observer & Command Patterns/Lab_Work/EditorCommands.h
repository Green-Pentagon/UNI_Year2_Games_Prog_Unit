#pragma once
#include "LevelEditor.h"
class LevelEditor; //forward decleration

class EditorCommands
{
protected:
	LevelEditor* editor;

public:
	EditorCommands(LevelEditor* editor);
	virtual void Do() = 0;
	virtual void Undo() = 0;

};

class SetTileCommand : public EditorCommands
{
	int iCell;
	int jCell;
	int tileIndex;
	int previous;

public:
	SetTileCommand(LevelEditor* editor, int iCell, int jCell, int tileIndex) : EditorCommands(editor), iCell(iCell), jCell(jCell), tileIndex(tileIndex) {};
	void Do() override;
	void Undo() override;
};